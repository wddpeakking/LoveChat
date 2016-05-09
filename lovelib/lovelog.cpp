#include "lovelog.h"
#include <string.h>
#include <stdarg.h>
#include <stddef.h>
CLog::CLog()
{
	m_fp = fopen("Log.log","w+");
	if (m_fp)
	{
		fprintf(m_fp,"Log is start...");
	}

}
CLog::~CLog()
{

}

void CLog::SetLevel(LogLevel enLevel)
{
	m_enLevel = enLevel;
}
void CLog::LogTrace(const char* format,...)
{
	if (format == NULL || m_fp == NULL || m_enLevel > en_Trace)
	{
		return;
	}
	char szBuf[512] = {0};
	strcpy(szBuf,"--Trace:\t\t");
	va_list arg;
	va_start(arg,format);
	vsprintf(szBuf+strlen(szBuf),format,arg);
	va_end(arg);
	fprintf(m_fp,"%s",szBuf);
	fflush(m_fp);

}
void CLog::LogDebug(const char* format,...)
{
	if (format == NULL || m_fp == NULL || m_enLevel > en_Debug)
	{
		return;
	}
	char szBuf[512] = {0};
	strcpy(szBuf,"--Debug:\t\t");
	va_list arg;
	va_start(arg,format);
	vsprintf(szBuf+strlen(szBuf),format,arg);
	va_end(arg);
	fprintf(m_fp,"%s",szBuf);
	fflush(m_fp);
}
void CLog::LogInfo(const char* format,...)
{
	if (format == NULL || m_fp == NULL || m_enLevel > en_Info)
	{
		return;
	}
	char szBuf[512] = {0};
	strcpy(szBuf,"--Info:\t\t");
	va_list arg;
	va_start(arg,format);
	vsprintf(szBuf+strlen(szBuf),format,arg);
	va_end(arg);
	fprintf(m_fp,"%s",szBuf);
	fflush(m_fp);
}
void CLog::LogWarning(const char* format,...)
{
	if (format == NULL || m_fp == NULL || m_enLevel > en_Warning)
	{
		return;
	}
	char szBuf[512] = {0};
	strcpy(szBuf,"--Warning:\t\t");
	va_list arg;
	va_start(arg,format);
	vsprintf(szBuf+strlen(szBuf),format,arg);
	va_end(arg);
	fprintf(m_fp,"%s",szBuf);
	fflush(m_fp);
}
void CLog::LogError(const char* format,...)
{
	if (format == NULL || m_fp == NULL || m_enLevel > en_Error)
	{
		return;
	}
	char szBuf[512] = {0};
	strcpy(szBuf,"--Error:\t\t");
	va_list arg;
	va_start(arg,format);
	vsprintf(szBuf+strlen(szBuf),format,arg);
	va_end(arg);
	fprintf(m_fp,"%s",szBuf);
	fflush(m_fp);
}