#include "lovegateServer.h"
#include "../lovelib/lovelog.h"

CLoveGateServer::CLoveGateServer()
{
	Init();
}
CLoveGateServer::~CLoveGateServer()
{

}

void CLoveGateServer::run()
{
	typedef std::vector<epoll_event> VectEpollEvent;
	VectEpollEvent vectEvents(64);
	while (m_bRunning)
	{
		int nEpollWait = epoll_wait(m_nEpoll,&*(vectEvents),vectEvents.size(),-1);
		if (-1 == nEpollWait)
		{
			if (errno != EINTR)
			{
				LogErrorMsg("<CLoveGateServer::run> epoll_wait error return -1 && errno != EINTR");
				break;
			}
			continue;
		}
		else if (0 == nEpollWait)
		{
			continue;	
		}
		else if ((size_t)nEpollWait == vectEvents.size())
		{
			vectEvents.resize(vectEvents.size()*2);
		}
		else
		{
			for (int i = 0; i < nEpollWait; ++i)
			{
				/* code */
				if (vectEvents[i].data.fd = m_nSocket)
				{
					/* code */ 
					int nConnect = -1;
					sockaddr_in clientAddr;
					socklen_t nLen = sizeof(struct sockaddr);
					if ((nConnect = accept(m_nSocket,(struct sockaddr*)&clientAddr, &nLen)) == -1)
					{
						LogErrorMsg("accept error");  
						continue;
					}
					setnonblocking(nConnect);
					if (EpollDel(nConnect) == false)
					{

					}
					m_vectClientConnect.push_back(nConnect);
					LogInfoMsg("<CLoveGateServer::run>the client:\t%s\t connect to server",inet_ntoa(cliaddr.sin_addr));
				
				}
				else if (events[i].events & EPOLLOUT) //write
				{
					/* code */
				}
				else if(events[i].events & EPOLLIN)//read
				{
					int nfd = events[i].data.fd;
					if (nfd < 0)
					{	
						continue;
					}
				}
				else
				{

				}
			}
		}
	}
}

void CLoveGateServer::Init()
{
	if (CreateSocket() == false)
	{
		LogErrorMsg("<CLoveGateServer::Init> create socket failed!");
		return;
	}
	int nPort = 9999;
	if(BindSocket(9999) == false)
	{
		LogErrorMsg("<CLoveGateServer::Init> bind socket failed,port=%d!",nPort);
		return;
	}
	if(ListenSocket() == fasle)
	{
		LogErrorMsg("<CLoveGateServer::Init> ListenSocket failed!");
		return;
	}
}