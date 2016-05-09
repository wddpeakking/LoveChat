#include "loveThread.h"
static void* ProxyFun(void* pFun)
{
	if (pFun)
	{
		CLoveThread* pThread = static_cast<CLoveThread*>(pFun);
		if (pThread)
		{
			pThread->run();
		}
	}
}

CLoveThread::CLoveThread()
{

}
CLoveThread::~CLoveThread()
{

}
void CLoveThread::trminate()
{

}
void CLoveThread::Isrunning()
{

}
void CLoveThread::start()
{
	if (pthread_create(&m_thread,NULL,ProxyFun,this) != 0)
	{

	}
}