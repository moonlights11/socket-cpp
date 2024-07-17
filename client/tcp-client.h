#ifndef _TCPCLIENT_H
#define _TCPCLIENT_H
 
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <string>
#include <unistd.h>
#include <netdb.h>
 
#define BUFF_SIZE 1024
 
using std::cout;
using std::cin;
using std::endl;
using std::string;
 
class TcpClient{
	private:
		int clnt_sock;			//客户端的socket
		struct sockaddr_in serv_addr;	//客户端的连接服务器的网络地址结构
		char buf[BUFF_SIZE];		//客户端的读写缓冲区
		int buf_len;			//客户端的读写长度
	public:
		TcpClient();//构造函数
		~TcpClient();//析构函数
 
		/**
		 * 初始化客户端
		 * ip_addr:	ipv4的地址
		 * port:	通信的端口号
		 */
		bool InitClient();
 
		/*
		 * 连接服务器
		 * */
		bool Connect(const string& ip_addr , const string& post);
 
		/*
		 * 读取缓冲区的数据
		 * */
		int Read();
 
		/*
		 * 写入数据
		 * str:需要发送的数据
		 * */
		void Write(const string& str);
 
		/*
		 * 关闭socket
		 * */
		void CloseClientSock();
 
};
 
#endif //TCPCLIENT_H