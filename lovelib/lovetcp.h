#ifndef _LoveChat_UDP_H_
#define _LoveChat_UDP_H_
/*  
	tcp 提供消息的读取和发送
*/

class CLoveTcp
{
	enum TCPType
	{
		en_Client,
		en_Server,
		en_Other
	};
public:
	CLoveTcp();
	~CLoveTcp();
public:
	void StartTcp(TCPType type=en_Server,const std::string& strIp="",int nPort=9999);
private:
	void Init(); 
private:
	int m_nSocket;
};
#endif