#include "loveMutex.h"

CLoveMutex::CLoveMutex()
{
	pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr,PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&m_mutex,&attr);
	pthread_mutexattr_destroy(&attr);
}
CLoveMutex::~CLoveMutex()
{
	pthread_mutex_destroy(&m_mutex);
}

void CLoveMutex::enter()
{
	if (pthread_mutex_lock(&m_mutex) !=0 )
	{
		//lock error
	}
}
void CLoveMutex::leave()
{
	if (pthread_mutex_unlock(&m_mutex) !=0 )
	{
		//lock error
	}
}