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
	void StartTcp(TCPType type=en_Server,const std::string& strIp="",int nPort=9999);
private:
	void Init(); 

	int setnonblocking( int fd );
private:
	int m_nSocket;
};
#endif