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
	//epoll Ä£ÐÍ
	int nEpoll = epoll_create(256);
	struct epoll_event ev,events[128];

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
		
		if( listen( m_nSocket, MAXBACK ) == -1 )  
		{  
			LogErrorMsg("listen socket error");  
			exit(1);  
		}  
		
	}
	else if (type == en_Client)
	{
		server_addr.sin_addr.s_addr=inet_addr(strIp.c_str());
		server_addr.sin_port=htons(nPort);
	}


}