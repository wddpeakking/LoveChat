#include "loveloginServer.h"
#include "../lovelib/lovelog.h"


CServerAccep::run()
{
	CLoveChatLoginServer* pServer = static_cast<CLoveChatLoginServer>(m_pTcpServer);
	if (pServer != NULL)
	{
		while (true)
		{
			sockaddr_in addr;
			int nConnect = m_pTcpServer->Accept(addr);
			if (nConnect > 0)
			{
				m_pTcpServer->EpollAdd(nConnect);
				LogInfoMsg("the client:\t%s\t connect to server",inet_ntoa(addr.sin_addr));
				//add to server
			}
		}
	}
}

CServerSend::run()
{
	CLoveChatLoginServer* pServer = static_cast<CLoveChatLoginServer>(m_pTcpServer);
	if (pServer != NULL)
	{
		while (true)
		{
			if (!pServer->IsNeedSend())
			{
				continue;
			}
			int nSend = m_pTcpServer->SendMsg();
		}
	}
}

CServerRecv::run()
{
	CLoveChatLoginServer* pServer = static_cast<CLoveChatLoginServer>(m_pTcpServer);
	
	while (true)
	{
		if (!pServer->IsNeedRecv())
		{
			continue;
		}
		char szBuf = [1024];
		memset(szBuf,0,1024);
		int nRead = recv(events[i].events.data.fd,szBuf,1024);
		if (nRead > 0)
		{
			std::cout<<"Recv msg:\t"<<szBuf<<std::endl;
		}
		else if (nRead == 0 )
		{
			close(events[i].events.data.fd);

			if( pServer->EpollDel(events[i].events.data.fd) == false )  
			{
				LogErrorMsg("epoll_ctl error");  
				exit(1);
			}
			//delete from list

			//notify dataserver user loginout
			//pServer->SendMsg();

		}
		else{

		}
	}
	
}

CLoveChatLoginServer::CLoveChatLoginServer()
{
	Init();
}
CLoveChatLoginServer::~CLoveChatLoginServer()
{

}

void CLoveChatLoginServer::Init()
{
	if (CreateSocket() == false)
	{
		LogErrorMsg("<CLoveChatLoginServer::init()> CreateSocket() == false");
		return;
	}
	if (BindSocket(9999) == false)
	{
		LogErrorMsg("<CLoveChatLoginServer::init()> BindSocket() == false");
		return;
	}
	if (ListenSocket() == false)
	{
		LogErrorMsg("<CLoveChatLoginServer::init()> ListenSocket() == false");
		return;
	}
	//创建监听线程
	m_pAccept = new CServerAccep(this);
	m_pAccept->start();

	//创建接收线程
	m_pRecv = new CServerRecv(this);
	m_pRecv->start();

	//创建发送线程
	m_pSend = new CServerSend(this);
	m_pSend->start();
}

void CLoveChatLoginServer::run()
{
	int nEpollfsd = 0;
	int nMaxEpoll = 1024*1024;
	struct epoll_event events[1024*1024];
	while(true)
	{
		int nEpollWaitFd = 0;
		if( ( nEpollWaitFd = epoll_wait( m_nEpoll, events, nEpollfsd, -1 ) ) == -1 )  
		{  
			LogErrorMsg("epoll_ctl error");  
			continue; 
		}  
		for (int i=0;i<nEpollWaitFd;++i)
		{
			//send data
			if (events[i].events & EPOLLOUT)
			{
				m_sendList.push_front(events[i].events.fd);
			}
			else if(events[i].events & EPOLLIN)
			{
				m_recvList.push_front(events[i].events.fd);
			}
			else
			{

			}
		}
	}
}

bool CLoveChatLoginServer::IsNeedRecv()
{
	if (m_recvList.size()>=1)
	{
		return true;
	}
	return false;
}
bool CLoveChatLoginServer::IsNeedSend()
{
	if (m_pSend.size()>=1)
	{
		return true;
	}
	return false;
}