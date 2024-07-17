#include "tcp-client.h"
 
int main(int argc , char* argv[]){
 
	TcpClient tcp_client;
	bool ope_res = tcp_client.InitClient();
	if(!ope_res){
		return -1;
	}
	ope_res = tcp_client.Connect(argv[1] , argv[2]);
	if(!ope_res){
		return -2;
	}
 
	cout<<"开始发送数据（输入q退出）"<<endl;
	while(1){
		string str;
		cin>>str;
		if(!strcmp(str.c_str() , "q")){
			break;
		}
		tcp_client.Write(str);
		if(tcp_client.Read() <= 0){
			break;
		}
	}
	tcp_client.CloseClientSock();
 
	return 0;
}