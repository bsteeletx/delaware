#include "Green.h"
#include "agk.h"

Green::Green(void)
	: Theme()
{

}


Green::~Green(void)
{
}

void Green::init(AnimatedSprite *Symbol, unsigned short state)
{
	Text ButtonText = Text();
	Text TempDir = Text();

	DirLocation.init("green/");
	ButtonText.init("menu");
	TempDir = DirLocation;

#if (PLATFORM != MOBILE)
	FirstCardPos[WEST].init(32.5f, 36.75f);
	FirstCardPos[NORTH].init(30.0f, 40.5f);
	FirstCardPos[EAST].init(29.5f, 37.0f);
	FirstCardPos[SOUTH].init(32.4f, 39.5f);
#else
	FirstCardPos[WEST].init(32.5f, 40.5f);
	FirstCardPos[NORTH].init(30.0f, 45.0f);
	FirstCardPos[EAST].init(29.5f, 40.5f);
	FirstCardPos[SOUTH].init(32.4f, 38.5f);
#endif
	
	setNumberData();
	setNumberPrio();
	setNumberLoc();
	setSizeNumbers();

	if (state == 0)
		initNumbers();

	Symbol->incrementFrame();
	agk::Sync();

	Background->parentInit(DirLocation);
	TempDir += ButtonText;
	InGameMenuButton->init(0, TempDir);

	InGameMenuButton->init(0, TempDir);
	BCBubble->init(DirLocation, 6.25f);

	for (int i = 0; i < 4; i++)
		AllPlayers[i]->init(DirLocation, 5.0f, 5.0f);
		
	TSBubble->init(DirLocation);
		
	if (state != MENU)
		AllCards->init(DirLocation, state);

	Theme::init(Symbol, GREEN, state);
}

void Green::initNumbers(void)
{
	Theme::initNumbers(DirLocation);
}

void Green::setNumberLoc(void)
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

void Green::setSizeNumbers(void)
{
	Theme::setSizeNumbers();
	//BCBubble->BidValue.setSize(5.25f);
	BidScore->setSize(2.5f);
}