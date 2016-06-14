#include "lovetcp.h"
#include "lovelog.h"

CLoveTcp::CLoveTcp()
{

}
CLoveTcp::~CLoveTcp()
{

}
void CLoveTcp::Init()
{

}

bool CLoveTcp::CreateSocket()
{
	if((m_nSocket = socket(AF_INET,SOCK_STREAM,0))==-1)  
	{
		LogErrorMsg("create socket error");
		return false;
	}
	if (setnonblocking(m_nSocket) == -1)
	{
		LogErrorMsg("setnonblocking error");
	}
	int nSock = 0;
	if (setsockopt(m_nSocket,SOL_SOCKET,SO_REUSEADDR,&nSock,sizeof(nSock)) < 0)
	{
		/* code */
		LogErrorMsg("setsockopt failed");
	}
	m_nEpoll = epoll_create1(EPOLL_CLOEXEC);
	if (EpollAdd(m_nSocket) == false)
	{
		return false;
	};
	return true;
}
bool CLoveTcp::BindSocket(int nPort)
{
	struct sockaddr_in server_addr;
	memset(&server_addr,0,sizeof(struct sockaddr_in));
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	server_addr.sin_port=htons(nPort);
	if(bind(m_nSocket,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr))==-1) 
	{ 
		LogErrorMsg("bin socket error");
		return false; 
	} 
	return true;
}
bool CLoveTcp::ListenSocket()
{
	if( listen( m_nSocket, 1024*1024 ) == -1 )  
	{  
		LogErrorMsg("listen socket error");  
		return false;  
	}  
	return true;
}
bool CLoveTcp::Connect(std::string& strIp,int nPort)
{
	if (strIp.empty())
	{
		LogErrorMsg("the IP is socket error");  
		return false;
	}
	struct sockaddr_in server_addr;
	memset(&server_addr,0,sizeof(struct sockaddr_in));
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=inet_addr(strIp.c_str());
	server_addr.sin_port=htons(nPort);
	socklen_t nLen = 0;
	if (int nConnect = connect(m_nSocket,(struct sockaddr *)(&server_addr),nLen) == -1)
	{
		LogErrorMsg("connect server error  serverIp=%s,port=%d",strIp.c_str(),nPort);  
		return false;
	}
	return true;
}
int CLoveTcp::SendMsg(int nScoket,char* szBuf,int nLen)
{

}
int CLoveTcp::RecvMsg(int nScoket,char* szBuf,int nLen)
{

}

int CLoveTcp::Accept(sockaddr_in& addr)
{
	int nConnect = -1;
	socklen_t nLen = sizeof(struct sockaddr);
	if ((nConnect = accept(m_nSocket,(struct sockaddr*)&addr, &nLen)) == -1)
	{
		LogErrorMsg("accept error");  
	}
	return nConnect;
}

bool CLoveTcp::EpollAdd(int nFd)
{
	struct epoll_event ev;
	ev.data.fd = nFd;
	ev.events = EPOLLIN | EPOLLET;
	if( epoll_ctl( m_nEpoll, EPOLL_CTL_ADD, nFd, &ev ) < 0 )  
	{
		LogErrorMsg("epoll_ctl error");  
		return false; 
	}
	return false;
}
bool CLoveTcp::EpollDel(int nFd)
{
	struct epoll_event ev;
	ev.data.fd = nFd;
	ev.events = EPOLLIN | EPOLLET;
	if( epoll_ctl( m_nEpoll, EPOLL_CTL_DEL, nFd, &ev ) < 0 )  
	{
		LogErrorMsg("epoll_del error");  
		return false; 
	}
	return true;
}
bool CLoveTcp::EpollMod(int nFd)
{
	struct epoll_event ev;
	ev.data.fd = nFd;
	ev.events = EPOLLIN | EPOLLET;
	if( epoll_ctl( m_nEpoll, EPOLL_CTL_MOD, nFd, &ev ) < 0 )  
	{
		LogErrorMsg("epoll_del error");  
		return false; 
	}
	return true;
}
bool CLoveTcp::CloseSocket(int nfd)
{
	close(nfd);
}
int CLoveTcp::GetSocket()const
{
	return m_nSocket;
}
/*
void CLoveTcp::StartTcp(TCPType type,const std::string& strIp,int nPort)
{
	if((m_nSocket = socket(AF_INET,SOCK_STREAM,0))==-1)  
	{
		LogErrorMsg("create socket error");
		exit(1);
	}

	if (setnonblocking(m_nSocket) == -1)
	{
		LogErrorMsg("setnonblocking error");
	}

	//epoll
	int nMaxEpoll = 1024*1024;
	int nEpoll = epoll_create(nMaxEpoll);
	struct epoll_event ev,events[nMaxEpoll];

	struct sockaddr_in server_addr;
	memset(&server_addr,0,sizeof(struct sockaddr_in));
	server_addr.sin_family=AF_INET;
	if (type == en_Server)
	{
		server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
		server_addr.sin_port=htons(nPort);
		if(bind(m_nSocket,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr))==-1) 
		{ 
			LogErrorMsg("bin socket error");
			exit(1); 
		} 
		
		if( listen( m_nSocket, 1024*1024 ) == -1 )  
		{  
			LogErrorMsg("listen socket error");  
			exit(1);  
		}  
		//add server socket to epoll
		int nEpollfsd = 0;
		ev.events = EPOLLIN | EPOLLET;
		ev.data.fd = m_nSocket;
		if( epoll_ctl( nEpoll, EPOLL_CTL_ADD, m_nSocket, &ev ) < 0 )  
		{
			LogErrorMsg("epoll_ctl error");  
			exit(1);  
		}

		nEpollfsd++;

		while(1)
		{
			int nEpollWaitFd = 0;
			if( ( nEpollWaitFd = epoll_wait( nEpoll, events, nEpollfsd, -1 ) ) == -1 )  
	        {  
				LogErrorMsg("epoll_ctl error");  
				continue; 
	        }  
			for (int i=0;i<nEpollWaitFd;++i)
			{

	        	if( events[i].data.fd == m_nSocket && nEpollfsd < nMaxEpoll )
	        	{
					int nConnect = -1;
					sockaddr_in clientAddr;
					socklen_t nLen = sizeof(struct sockaddr);
					if ((nConnect = accept(m_nSocket,(struct sockaddr*)&clientAddr, &nLen)) == -1)
					{
						LogErrorMsg("accept error");  
						continue;
					}
					setnonblocking(nConnect);
					ev.data.fd = nConnect;
					ev.events = EPOLLIN | EPOLLET;
					if( epoll_ctl( nEpoll, EPOLL_CTL_ADD, nConnect, &ev ) < 0 )  
					{
						LogErrorMsg("epoll_ctl error");  
						exit(1);
					}
					LogInfoMsg("the client:\t%s\t connect to server",inet_ntoa(cliaddr.sin_addr));
					nEpollfsd++;
	        	}
				//send data
	        	else if (events[i].events & EPOLLOUT)
	        	{

	        	}
				else if(events[i].events & EPOLLIN)
	        	{
	        		//read message
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
						ev.data.fd = 
						events[i].events.data.fd
						if( epoll_ctl( nEpoll, EPOLL_CTL_DEL, events[i].events.data.fd, &ev ) < 0 )  
						{
							LogErrorMsg("epoll_ctl error");  
							exit(1);
						}

					}
	        	}
				else
				{
				}
	        }
		}
	}
	else if (type == en_Client)
	{
		server_addr.sin_addr.s_addr=inet_addr(strIp.c_str());
		server_addr.sin_port=htons(nPort);
	}
	else
	{

	}
}
*/

int CLoveTcp::setnonblocking( int fd )  
{  
    if( fcntl( fd, F_SETFL, fcntl( fd, F_GETFD, 0 )|O_NONBLOCK ) == -1 )  
    {  
        LogErrorMsg("setnonblocking error"); 
        return -1;  
    }  
    return 0;  
}  