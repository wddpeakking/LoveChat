#ifndef _LoveChat_Log_H_
#define _LoveChat_Log_H_

#include <stdio.h>
#include "single.h" 

class CLog :public CSingleton<CLog>
{
public:
	CLog();
	~CLog();
	enum LogLevel
	{
		en_Trace,
		en_Debug,
		en_Info,
		en_Warning,
		en_Error,
		en_All
	};
	void SetLevel(LogLevel enLevel);
	void LogTrace(const char* format,...);
	void LogDebug(const char* format,...);
	void LogInfo(const char* format,...);
	void LogWarning(const char* format,...);
	void LogError(const char* format,...);
private:
	FILE* m_fp;				//file 
	LogLevel m_enLevel;		//warning level
};

#define LogTraceMsg(msg,...)\
	CLog::GetInstance()->LogTrace(msg);
#define LogDebugMsg(msg,...)\
	CLog::GetInstance()->LogDebug(msg);
#define LogInfoMsg(msg,...)\
	CLog::GetInstance()->LogInfo(msg);
#define LogWarningMsg(msg,...)\
	CLog::GetInstance()->LogWarning(msg);
#define LogErrorMsg(msg,...)\
	CLog::GetInstance()->LogError(msg);
#endif