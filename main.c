#include <stdio.h>
#include <stdlib.h>

#include "pd_api.h"

#include "game.h"

#ifdef _WINDLL
__declspec(dllexport)
#endif
int eventHandler(PlaydateAPI* playdate, PDSystemEvent event, uint32_t arg)
{
	if ( event == kEventInit )
	{
		setPDPtr(playdate);
		playdate->display->setRefreshRate(50);
		playdate->system->setUpdateCallback(update, NULL);
		setupGame();
	}
	if ( event == kEventTerminate )
	{
		terminate();
	}
	
	return 0;
}
