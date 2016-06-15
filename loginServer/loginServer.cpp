#ifndef _Lovechat_Login_Main_
#define _Lovechat_Login_Main_
#include "../lovelib/lovelog.h"
#include "loveloginServer.h"
#include "loveloginClient.h"
#include <iostream>
int main(int argc, char const *argv[])
{
	/* code */
	LogTraceMsg("loginserver start begin...");
	CLoveChatLoginServer loginServer;
	loginServer.start();
	LogTraceMsg("loginserver start end...");

	LogTraceMsg("loginclient start begin...");
	CLoveChatLoginClient loginClient;
	loginClient.start();
	LogTraceMsg("loginclient start end...");

	return 0;
}

#endif