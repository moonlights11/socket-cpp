#include "tcp-server.h"
 
TcpServer::TcpServer():serv_sock(-1),clnt_sock(-1){
	cout<<"TCP服务器的构造函数"<<endl;
}
 
TcpServer::~TcpServer(){
	cout<<"TCP服务器的析构函数"<<endl;
}
 
bool TcpServer::InitServer(const string& port){
 
	//先判断服务是否已经开启
	if(serv_sock > 0){
		CloseServerSock();
		serv_sock = -1;
	}
 
	//创建服务器中的服务端socket
	serv_sock = socket(PF_INET , SOCK_STREAM , 0);//PF_INET指定网络协议格式 为ipv4，SOCK_STREAM指代的是tcp链接
	if(serv_sock == -1){
		cout<<"服务器创建监听套接字失败，socket() error!"<<endl;
		return false; 
	}	
 
	//绑定服务端的socket到相应的网络地址结构中
	memset(&serv_addr , 0 , sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(port.c_str()));
	if(bind(serv_sock , (struct sockaddr*)& serv_addr , sizeof(serv_addr)) == -1){
		cout<<"服务器绑定套接字失败，bind() error!"<<endl;
		//关闭服务端的socket
		CloseServerSock();
		return false;
 
	}
 
	//开始监听服务端的套接字
	if(listen(serv_sock , 5) == -1){
		cout<<"服务端监听套接字失败，listen() error!"<<endl;
		//关闭服务端的socket
		CloseServerSock();
		return false;
	}
 
	cout<<"服务端初始化完成，开始接受客户端的连接..."<<endl;
	return true;
}
 
bool TcpServer::Accept(){
	//判断服务端是否已经开启了socket
	if(serv_sock == -1){
		cout<<"服务器中未开启监听的socket!"<<endl;
		return false;
	}
	//获取网络地址结构的长度
	clnt_addr_len = sizeof(clnt_addr);
	clnt_sock = accept(serv_sock , (struct sockaddr*)& clnt_addr , &clnt_addr_len);
	
	if(clnt_sock == -1){
		cout<<"服务器无法接受客户端的连接"<<endl;
		return false;
	}
	return true;
}
 
void TcpServer::CloseServerSock(){
	if(serv_sock > 0){
		close(serv_sock);
		serv_sock = -1;
	}
}
 
void TcpServer::CloseClientSock(){
	if(clnt_sock > 0){
		close(clnt_sock);
		serv_sock = -1;
	}
}
 
int TcpServer::Read(){
	if(clnt_sock == -1){
		cout<<"未有客户端进行连接"<<endl;
		return 0;
	}
	buf_len = read(clnt_sock , buf , BUFF_SZIE);
	if(buf_len == 0){
		//对端断开了连接,关闭对端
		CloseClientSock();
		return buf_len;
	}
	buf[buf_len] = 0;
	cout<<"【"<<clnt_sock<<"】说："<<buf<<endl;
	return buf_len;
}
 
void TcpServer::Write(){
	if(clnt_sock == -1){
		cout<<"未有客户端进行连接，写入失败"<<endl;
	}else{
		write(clnt_sock , buf , buf_len);
	}
}