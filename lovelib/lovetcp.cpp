#include "lovetcp.h"

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <fcntl.h>

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
	        	/* code */
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
					if( epoll_ctl( nEpoll, EPOLL_CTL_ADD, nConnect, &ev ) < 0 )  
					{
						LogErrorMsg("epoll_ctl error");  
						exit(1);
					}
					LogInfoMsg("the client:\t%s\t connect to server",inet_ntoa(cliaddr.sin_addr));
					nEpollfsd++;
	        	}
	        	else
	        	{
	        		//read message

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


int CLoveTcp::setnonblocking( int fd )  
{  
    if( fcntl( fd, F_SETFL, fcntl( fd, F_GETFD, 0 )|O_NONBLOCK ) == -1 )  
    {  
        LogErrorMsg("setnonblocking error"); 
        return -1;  
    }  
    return 0;  
}  