#ifndef _Lovechat_Gate_Main_
#define _Lovechat_Gate_Main_
#include "../lovelib/lovelog.h"
#include "lovegateServer.h"
#include <iostream>
int main(int argc, char const *argv[])
{
	/* code */
	LogTraceMsg("gateserver start begin...");
	CLoveGateServer server;
	server.start();
	LogTraceMsg("gateserver closed!");
	return 0;
}

#endif