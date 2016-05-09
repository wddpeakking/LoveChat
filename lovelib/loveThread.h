#incdef _LoveThread_H_
#define _LoveThread_H_

class CLoveThread
{
public:
	enum ThreadStatus
	{
		en_UnKnow,
		en_Running,
		en_Terminate,
		en_Wait
	};

	CLoveThread();
	~CLoveThread();
	
	void start();
	void trminate();
	void Isrunning();
	void wait();
	CLoveThread::ThreadStatus GetStatues();
	virtual void run()=0;
private:
	pthread_t m_thread;
	ThreadStatus m_statues;
£ý
#endif