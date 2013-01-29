#include "Red.h"
#include "agk.h"


Red::Red(void)
	: Theme()
{
	
}

Red::~Red(void)
{
}

void Red::init(AnimatedSprite *Symbol, unsigned short state)
{
	DirLocation.init("red/");

#if (PLATFORM != MOBILE)
	FirstCardPos[WEST].init(36.5f, 32.5f);
	FirstCardPos[NORTH].init(28.0f, 40.5f);
	FirstCardPos[EAST].init(28.25f, 40.5f);
	FirstCardPos[SOUTH].init(28.25f, 40.25f);
#else
	FirstCardPos[WEST].init(35.5f, 36.75f);
	FirstCardPos[NORTH].init(27.0f, 45.0f);
	FirstCardPos[EAST].init(28.25f, 45.75f);
	FirstCardPos[SOUTH].init(28.25f, 39.0f);
#endif

	Text TempDir = DirLocation;
	Text ButtonBaseName = Text();

	ButtonBaseName.init("background.png");

	setNumberData();
	setNumberPrio();
	setNumberLoc();
	setSizeNumbers();

	if (state == LOADING)
		initNumbers();

	TempDir += ButtonBaseName;
	Background->parentInit(TempDir);

	TempDir = DirLocation;
	ButtonBaseName.setString("menu");
	TempDir += ButtonBaseName;
	InGameMenuButton->init(0, TempDir);
	BCBubble->init(DirLocation, 5.25f);

	for (int i = 0; i < 4; i++)
	{
		AllPlayers[i]->init(DirLocation, 5.0f, 5.0f);
		AllPlayers[i]->offsetBidNumberBy(-0.5f, 0.0f);
	}

	TSBubble->init(DirLocation);
	
	if (state != MENU)
		AllCards->init(DirLocation, state);

	Theme::init(Symbol, RED, state);
}

void Red::initNumbers(void)
{
	Theme::initNumbers(DirLocation);
}

void Red::setNumberLoc(void)
{
	float offset = 0.0f;
    
#if (PLATFORM == MOBILE)
    offset = 0.25f;
#endif
	
	for (int i = 0; i < 3; i++)
	{
		BidScore->setLocation(i, 84.5f - ((2.5f + offset) * i), 70.0f - (offset * 2), 0); //added 1 space
		VScore->setLocation(i, 8.25f - (2.0f * i), 10.0f, -5.75f, -0.6f);
		HScore->setLocation(i, 18.75f - (2.0f * i), 10.0f, -5.75f, -0.6f); //
		VMeld->setLocation(i, 4.9f - (1.5f * i), 71.25f, 0); //
		HMeld->setLocation(i, 9.9f - (1.5f * i), 71.25, 0); //0, 0.5
		V2Get->setLocation(i, 15.25f - (1.5f * i), 71.25f, 0); 
		H2Get->setLocation(i, 20.25f - (1.5f * i), 71.25f, 0);
	}
}

void Red::setSizeNumbers(void)
{
	Theme::setSizeNumbers();
	//BCBubble->BidValue.setSize(5.25f);
	BidScore->setSize(3.0f);
}

Point Red::getFirstCardPos(unsigned short player)
{
	return FirstCardPos[player];
}