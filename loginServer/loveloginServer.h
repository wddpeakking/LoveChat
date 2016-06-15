#ifndef _lovechat_loveLoginServer_H_
#define _lovechat_loveLoginServer_H_
#include "../lovelib/lovetcp.h"
#include "../lovelib/loveThread.h"
#include "../lovelib/type.h"

//accept thread
class CServerAccep : public CLoveThread
{
public:
	CServerAccep(CLoveTcp* pTcp)
		:m_pTcpServer(pTcp){};
	~CServerAccep(){};

	virtual void run();
private:
	CLoveTcp* m_pTcpServer;
};

//send thread
class CServerSend : public CLoveThread
{
public:
	CServerSend(CLoveTcp* pTcp):m_pTcpServer(pTcp){};
	~CServerSend(){};
	virtual void run();
private:
	CLoveTcp* m_pTcpServer;
};
//recv thread
class CServerRecv : public CLoveThread 
{
public:
	CServerRecv(CLoveTcp* pTcp):m_pTcpServer(pTcp){};
	~CServerRecv(){};
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
public:
	bool IsNeedRecv();
	bool IsNeedSend();
	bool AddNewConnect(int nConnect);
	bool DeleteConnect(int nConnect);

private:
	void Init();

private:
	CServerAccep* m_pAccept;
	CServerSend* m_pSend;
	CServerRecv* m_pRecv;

	FunType::ListInt m_recvList;
	FunType::ListPairIntStr m_sendList;
	std::map<int,int> m_connMap;

};
#endif