#include "loveThread.h"
#include <errno.h>

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
CLoveThread::ThreadStatus CLoveThread::GetStatues()
{
	return m_statues;
}

void CLoveThread::trminate()
{
	if (m_statues == CLoveThread::en_Running)
	{
		pthread_cancel(m_thread);
		m_statues = en_Wait;
	}
	
}
bool CLoveThread::Isrunning()
{
	return m_statues == CLoveThread::en_Running;
}

void CLoveThread::wait()
{
	if (m_statues == CLoveThread::en_Running)
	{
		void *pStatus = NULL;
		int nRet = pthread_join(m_thread,&pStatus);
		switch (nRet)
		{
		case 0:m_statues = CLoveThread::en_Wait;break;
		case EINVAL:		//thread is not join
		case ESRCH:			// no thread found with this id
		case EDEADLK:		//Deadlock detected or calling thread  waits for itself
		default:break;			//unknow thread join error
		}
		if (m_statues != CLoveThread::en_Terminate)
		{
			//thread did not finished 
		}
	}
	
}

void CLoveThread::start()
{
	if (pthread_create(&m_thread,NULL,ProxyFun,this) != 0)
	{
		m_statues = CLoveThread::en_UnKnow;
	}
	m_statues = CLoveThread::en_Running;
}