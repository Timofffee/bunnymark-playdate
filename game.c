#include <stdlib.h>
#include <stdio.h>
#include "game.h"

#define MAX_BUNNIES 50000

static PlaydateAPI* pd = NULL;

typedef struct Vector2
{
    float x;
	float y;
} Vector2;

typedef struct Bunny
{
    Vector2 position;
    Vector2 speed;
} Bunny;

Bunny *bunnies = NULL;
int bunniesCount = 0;
char *countText = NULL;
int pressed = 0;

// cached images
LCDBitmap *texBunny = NULL;;


void setPDPtr(PlaydateAPI* p) { pd = p; }


LCDBitmap *loadImageAtPath(const char *path)
{
	pd->system->logToConsole("Load '%s'", path);
	const char *outErr = NULL;
	LCDBitmap *img = pd->graphics->loadBitmap(path, &outErr);
	if ( outErr != NULL ) {
		pd->system->logToConsole("Error loading image at path '%s': %s", path, outErr);
	}
	pd->system->logToConsole("Loaded '%s': %s", path, outErr);
	return img;
}

// game initialization
void setupGame(void)
{
	pd->system->logToConsole("setupGame");
	srand(pd->system->getSecondsSinceEpoch(NULL));

	bunnies = pd->system->realloc(NULL, sizeof(Bunny) * MAX_BUNNIES);

	texBunny = loadImageAtPath("images/wabbit_alpha");

	bunniesCount = 0;
}


void instantiateBunnies(void)
{
	for (int i = 0; i < 100; i++)
	{
		if (bunniesCount < MAX_BUNNIES)
		{
			bunnies[bunniesCount].position.x = 200.0f;
			bunnies[bunniesCount].position.y = 120.0f;
			bunnies[bunniesCount].speed.x = (float)(rand() % 500 - 250)/50.0f;
			bunnies[bunniesCount].speed.y = (float)(rand() % 500 - 250)/50.0f;
			bunniesCount++;
		}
	}
}


void checkButtons(void)
{
	PDButtons pushed;
	pd->system->getButtonState(&pushed, NULL, NULL);

	pressed = ( pushed & kButtonA || pushed & kButtonB );
	if (pressed)
	{
		instantiateBunnies();
	}
}


void updateBunnies(void)
{
	for (int i = 0; i < bunniesCount; i++)
	{
		bunnies[i].position.x += bunnies[i].speed.x;
		bunnies[i].position.y += bunnies[i].speed.y;

		if (((bunnies[i].position.x + 8) > 400) ||
			((bunnies[i].position.x + 8) < 0)) bunnies[i].speed.x *= -1;
		if (((bunnies[i].position.y + 8) > 240) ||
			((bunnies[i].position.y + 8 - 40) < 0)) bunnies[i].speed.y *= -1;
	}
}


void drawBunnies(void)
{
	pd->graphics->clear(kColorWhite);

	for (int i = 0; i < bunniesCount; i++)
	{
		pd->graphics->drawBitmap(texBunny, (int)bunnies[i].position.x, (int)bunnies[i].position.y, 0);
	}

	if (pressed)
	{
		int rX = rand() % 4 - 2;
		int rY = rand() % 4 - 2;

		pd->graphics->drawRect(5 + rX, 5 + rY, 390 + rX, 230 + rY, kColorBlack);

		pd->system->drawFPS(10 + rX, 10 + rY);

		pd->system->formatString(&countText, "bunnies: %d", bunniesCount);
		pd->graphics->drawText(countText, strlen(countText), kASCIIEncoding, 120 + rX, 10 + rY);
		countText = pd->system->realloc(countText, 0);
	}
	else
	{
		pd->graphics->drawRect(5, 5, 390, 230, kColorBlack);

		pd->system->drawFPS(10,10);

		pd->system->formatString(&countText, "bunnies: %d", bunniesCount);
		pd->graphics->drawText(countText, strlen(countText), kASCIIEncoding, 120, 10);
		countText = pd->system->realloc(countText, 0);
	}
}


// main update function
int update(void* ud)
{
	checkButtons();
	updateBunnies();
	drawBunnies();

	return 1;
}
