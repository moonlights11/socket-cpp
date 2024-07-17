#include "tcp-client.h"
 
in_addr GetHostByName(const string& ip_addr){
	struct hostent* host;
	host = gethostbyname(ip_addr.c_str());
	struct in_addr _sin_addr;
	memset(&_sin_addr , 0 , sizeof(_sin_addr));
	if(!host){
		return _sin_addr;
	}
	_sin_addr = (*(struct in_addr*)host->h_addr_list[0]);
	return _sin_addr;
}
 
TcpClient::TcpClient():clnt_sock(-1),buf_len(0){
 
}
 
TcpClient::~TcpClient(){
 
}
 
bool TcpClient::InitClient(){
	if(clnt_sock != -1){
		CloseClientSock();
	}
	clnt_sock = socket(PF_INET , SOCK_STREAM , 0);
	if(clnt_sock == -1){
		cout<<"客户端创建socket失败，socket() error!"<<endl;
		return false;
	}
	cout<<"客户端创建socket成功！"<<endl;
	return true;
}
 
bool TcpClient::Connect(const string& ip_addr , const string& port){
	if(clnt_sock == -1){
		cout<<"客户端没有创建socket，无法连接服务器！"<<endl;
		return false;
	}
	//开始连接服务器
	memset(&serv_addr , 0 , sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr = GetHostByName(ip_addr);
	serv_addr.sin_port = htons(atoi(port.c_str()));
 
	if(connect(clnt_sock , (struct sockaddr*)& serv_addr , sizeof(serv_addr)) == -1){
		CloseClientSock();
		cout<<"连接服务器失败"<<endl;
		return false;
	}
	cout<<"连接服务器成功..."<<endl;
	return true;
}
 
int TcpClient::Read(){
	if(clnt_sock < 0){
		cout<<"客户端未开启socket，无法读取"<<endl;
		return -1;
	}
	buf_len  = read(clnt_sock , buf , BUFF_SIZE);
	if(buf_len == 0){
		cout<<"对端已关闭socket,无法继续读取"<<endl;
		CloseClientSock();
		return buf_len;
	}
	buf[buf_len] = 0;
	cout<<"服务器说："<<buf<<endl;
	return buf_len;
}
 
void TcpClient::Write(const string& str){
	if(clnt_sock < 0){
		cout<<"客户端未开启socket，写入失败！"<<endl;
	}else{
		write(clnt_sock , str.c_str() , str.size());	
	}
}
 
void TcpClient::CloseClientSock(){
	if(clnt_sock > 0){
		close(clnt_sock);
	}
	clnt_sock = -1;
}