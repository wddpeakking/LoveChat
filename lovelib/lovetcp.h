#ifndef _LoveChat_UDP_H_
#define _LoveChat_UDP_H_

#include <iostream>

class CLoveTcp
{
public:
	CLoveTcp();
	~CLoveTcp();

	enum TCPType
	{
		en_Client,
		en_Server,
		en_Other
	};
public:

	bool CreateSocket();
	bool BindSocket(int nPort);
	bool ListenSocket();
	bool Connect(std::string& strIp,int nPort);
	int SendMsg(int nScoket,char* szBuf,int nLen);
	int RecvMsg(int nScoket,char* szBuf,int nLen);
	bool EpollAdd(int nFd);
	bool EpollDel(int nFd);
	bool EpollMod(int nFd);
	bool CloseSocket();
	void StartTcp(TCPType type=en_Server,const std::string& strIp="",int nPort=9999);
private:
	void Init(); 

	int setnonblocking( int fd );
private:
	int m_nSocket;
	int m_nEpoll;
};
#endif