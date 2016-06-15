#ifndef _lovechat_LoginClient_H_
#define _lovechat_LoginClient_H_
#include "../lovelib/loveThread.h"
#include "../lovelib/lovetcp.h"


//send thread
class CClientSend : public CLoveThread
{
public:
	CClientSend(CLoveTcp* pTcp):m_pTcpServer(pTcp){};
	~CClientSend(){};
	virtual void run();
private:
	CLoveTcp* m_pTcpServer;
};
//recv thread
class CClientRecv : public CLoveThread 
{
public:
	CClientRecv(CLoveTcp* pTcp):m_pTcpServer(pTcp){};
	~CClientRecv(){};
	virtual void run();
private:
	CLoveTcp* m_pTcpServer;
};

class CLoveChatLoginClient : public CLoveTcp ,public CLoveThread
{
public:
	CLoveChatLoginClient();
	~CLoveChatLoginClient();

	virtual void run();

	bool IsNeedRecv();
	bool IsNeedSend();
private:
	void Init();

private:
	CClientRecv* m_pRecv;
	CClientSend* m_pSend;

	std::list<int> m_sendList;
	std::list<int> m_recvList;

};
#endif