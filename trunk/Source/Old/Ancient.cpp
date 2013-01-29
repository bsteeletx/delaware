#include "Ancient.h"
#include "agk.h"


Ancient::Ancient(void)
	: Theme()
{
	//DirLocation = new Text("ancient/");
}

Ancient::~Ancient(void)
{
}

void Ancient::init(AnimatedSprite *Symbol, unsigned short state)
{
	DirLocation.init("ancient/");

	Text TempDir = DirLocation;
	Text ButtonText = Text();

	ButtonText.init("menu");

#if (PLATFORM != MOBILE)
	FirstCardPos[WEST].init(27.5f, 33.75f);
	FirstCardPos[NORTH].init(24.75f, 37.5f);
	FirstCardPos[EAST].init(25.0f, 32.0f);
	FirstCardPos[SOUTH].init(28.25f, 38.0f);
#else
	FirstCardPos[WEST].init(27.5f, 36.25f);
	FirstCardPos[NORTH].init(24.75f, 41.5f);
	FirstCardPos[EAST].init(25.0f, 36.6f);
	FirstCardPos[SOUTH].init(28.25f, 37.0f);
#endif


	setNumberData();
	setNumberPrio();
	setNumberLoc();
	setSizeNumbers();

	if (state == LOADING)
		initNumbers();

	Background->parentInit(DirLocation);

	TempDir += ButtonText;
	InGameMenuButton->init(0, TempDir);
	BCBubble->init(DirLocation, 5.25f);

	for (int i = 0; i < 4; i++)
	{
		Point *NumberOffset = new Point();
		
#if (PLATFORM == MOBILE)
		NumberOffset->init(38.0f, 32.0f);
#endif
		AllPlayers[i]->init(DirLocation, 0.0f, 0.0f);
	}
	
	TSBubble->init(DirLocation);
	
	if (state != MENU)
		AllCards->init(DirLocation, state);

	AllPlayers[NORTH]->offsetMeldBubbleBy(0.0f, -15.0f);
	AllPlayers[EAST]->offsetMeldBubbleBy(0.0f, -10.0f);

	Theme::init(Symbol, ANCIENT, state);
}

void Ancient::initNumbers(void)
{
	Theme::initNumbers(DirLocation);
}

void Ancient::setNumberLoc(void)
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

void Ancient::setSizeNumbers(void)
{
	Theme::setSizeNumbers();
	//BCBubble->BidValue.setSize(5.25f);
	BidScore->setSize(3.0f);
}

Point Ancient::getFirstCardPos(unsigned short player)
{
	return FirstCardPos[player];
}