#include "tcp-server.h"
 
int main(int argc ,char* argv[]){
 
	if(argc != 2){
		cout<<"Usage : "<<argv[0]<<" <PORT>"<<endl;
		return -1;
	}
 
	TcpServer tcp_server;
	//初始化服务器
	bool init_res = tcp_server.InitServer(argv[1]);
	if(!init_res){
		cout<<"服务器初始化失败"<<endl;
		return -1;
	}
	//接受客户端的连接，现在模拟只接受一个客户端的情况
	bool accept_res = tcp_server.Accept();
	if(!accept_res){
		return -2;
	}
	
	//开始回声
	while(1){
		if(tcp_server.Read() == 0){
			cout<<"客户端退出了"<<endl;
			break;
		}
		tcp_server.Write();
	}
	tcp_server.CloseServerSock();
	tcp_server.CloseClientSock();
 
	return 0;
}