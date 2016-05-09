#include "../lovelib/lovelog.h"
#include "lovechatClient.h"
int main(int argc, char const *argv[])
{
	/* code */
	LogTraceMsg("start chat client...");
	CChatClient* pchatClient = new CChatClient();
	if (pchatClient)
	{
		/* code */
		pchatClient->printClassName();
		
	}
	delete pchatClient;
	return 0;
}