#ifndef _TCPSERVER_H
#define _TCPSERVER_H
 
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>
#include <cstring>
#include <unistd.h>
 
#define BUFF_SZIE 1024
 
using std::cout;
using std::endl;
using std::cin;
using std::string;
 
class TcpServer{
	private:
		struct sockaddr_in serv_addr;//服务器中服务端的网络地址结构
		struct sockaddr_in clnt_addr;//服务端中客户端的网络地址结构
		socklen_t clnt_addr_len;//服务器中客户端的网络地址结构的长度
		char buf[BUFF_SZIE];//读写缓冲区
		int buf_len;//读取的字节长度
	public:
		int serv_sock;//服务器中服务端的socket描述符
		int clnt_sock;//服务器中客户端的socket描述符
 
	private:
	public:
		//构造函数
		TcpServer();
		//析构函数
		~TcpServer();
 
		/*
		 * 初始化服务器
		 * 服务端地址使用INADDR_ANY
		 * port:端口号
		 * */
		bool InitServer(const string& port);
 
		/*
		 * 阻塞接受客户端的连接
		 * */
		bool Accept();
 
		/**
		 * 关闭服务器中服务端的套接字
		 */
		void CloseServerSock();
 
		/*
		 * 关闭服务器中客户端的套接字
		 * */
		void CloseClientSock();
 
		/*
		 * 读取客户端的数据
		 * */
		int Read();		
 
		/**
		 * 回写客户端的数据
		 */
		void Write();
};
#endif //TCPSERVER_H