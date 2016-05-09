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
CLoveThread::ThreadStatus CLoveThread::GetStatues()
{
	return m_statues;
}

void CLoveThread::trminate()
{
	if (m_statues == en_Running)
	{
		pthread_cancle(m_thread);
		m_statues = en_Wait;
	}
	
}
void CLoveThread::Isrunning()
{
	return m_statues == en_Running;
}

void CLoveThread::wait()
{
	if (m_statues == en_Running)
	{
		int nRet = pthread_join(m_thread);
		switch (nRet)
		{
		case 0:m_statues = en_Wait;break;
		case EINVAL:		//thread is not join
		case ESRCH:			// no thread found with this id
		case EDEADLK:		//Deadlock detected or calling thread  waits for itself
		default:			//unknow thread join error
		}
		if (m_statues != en_Terminate)
		{
			//thread did not finished 
		}
	}
	
}

void CLoveThread::start()
{
	if (pthread_create(&m_thread,NULL,ProxyFun,this) != 0)
	{
		m_statues = en_UnKnow;
	}
	m_statues = en_Running;
}