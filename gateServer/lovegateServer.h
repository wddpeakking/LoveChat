#ifndef _Lovechat_Gate_H_
#define _Lovechat_Gate_H_

#include "../lovelib/lovetcp.h"
#include "../lovelib/loveThread.h"
class CLoveGateServer : public CLoveTcp,public CLoveThread
{
public:
	typedef std::vector<int> VectInt;

	CLoveGateServer();
	~CLoveGateServer();
	virtual void run()=0;
private:
	void Init();



private:
	VectInt m_vectClientConnect;
	
};
#endif