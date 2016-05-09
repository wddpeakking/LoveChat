#incdef _LoveThread_H_
#define _LoveThread_H_

class CLoveThread
{
public:
	CLoveThread();
	~CLoveThread();
	
	void start();
	void trminate();
	void Isrunning();
	virtual void run()=0;
private:
	pthread_t m_thread;
£ý
#endif