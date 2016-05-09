#ifndef _LoveMutex_H_
#define _LoveMutex_H_
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
class CLoveMutex
{
public:
	CLoveMutex();
	~CLoveMutex();

	void enter();
	void leave();
private:
	pthread_mutex_t m_mutex;
};
#endif