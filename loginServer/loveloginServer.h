#ifndef _lovechat_loveLoginServer_H_
#define _lovechat_loveLoginServer_H_
#include "../lovelib/lovetcp.h"

//accept thread
class CAccep : public CLoveThread
{
public:
	CAccep(CLoveTcp* pTcp)
		:m_pTcpServer(pTcp){};
	~CAccep(){};

	virtual void run();
private:
	CLoveTcp* m_pTcpServer;
};

//send thread
class CSend : public CLoveThread
{
public:
	CSend(CLoveTcp* pTcp):m_pTcpServer(pTcp){};
	~CSend(){};
	virtual void run();
private:
	CLoveTcp* m_pTcpServer;
};
//recv thread
class CRecv : public CLoveThread 
{
public:
	CRecv(CLoveTcp* pTcp):m_pTcpServer(pTcp){};
	~CRecv(){};
	virtual void run();
private:
	CLoveTcp* m_pTcpServer;
};
class CLoveChatLoginServer : public CLoveTcp : public CLoveThread
{
public:
	CLoveChatLoginServer();
	~CLoveChatLoginServer();

	virtual void run();

private:
	void Init();

private:
	CAccep* m_pAccept;
	CSend* m_pSend;
	CRecv* m_pRecv;

	std::list<int> m_recvList;
	std::list<int> m_sendList;
	std::list<int> m_connList;
};
#endif