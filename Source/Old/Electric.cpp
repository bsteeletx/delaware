#include "Electric.h"


Electric::Electric(void)
{

}


Electric::~Electric(void)
{
}


void Electric::init(AnimatedSprite *Symbol, unsigned short state)
{
	DirLocation.init("electric/");
	Point OffsetBidNumbers[4];
	Point OffsetPassBid[4];
	Text TempDir = DirLocation;
	Text ButtonText;

#if (PLATFORM != MOBILE)
	FirstCardPos[WEST].init(27.5f, 33.5f);
	FirstCardPos[NORTH].init(28.0f, 41.0f);
	FirstCardPos[EAST].init(32.0f, 40.5f);
	FirstCardPos[SOUTH].init(26.0f, 40.0f);
#else
	FirstCardPos[WEST].init(27.5f, 41.0f);
	FirstCardPos[NORTH].init(28.0f, 40.0f);
	FirstCardPos[EAST].init(39.0f, 47.5f);
	FirstCardPos[SOUTH].init(32.0f, 47.5f);
#endif

	setNumberData();
	setNumberPrio();
	setNumberLoc();
	setSizeNumbers();

	if (state == 0)
		initNumbers();

	Background->parentInit(DirLocation);

	ButtonText.init("menu");
	TempDir += ButtonText;
	InGameMenuButton->init(0, TempDir);
	BCBubble->init(DirLocation, 5.25f);

	for (int i = 0; i < 4; i++)
		AllPlayers[i]->init(DirLocation, 0.0f, 0.0f);
	
#if (PLATFORM != MOBILE)
	OffsetBidNumbers[WEST].addToY(3.0f);
	OffsetPassBid[WEST].addToY(1.0f);
#endif

	//*OffsetBidNumbers[WEST] += Point(5.0f, 0.0f);
	//*OffsetPassBid[WEST] += Point(5.0f, 0.0f);
	Point Temp;
	Temp.init(5.0f, 0.0f);
	AllPlayers[WEST]->offsetBidNumberBy(Temp);
	AllPlayers[WEST]->offsetPassBy(Temp);
	Temp.addToX(-4.0f);
	AllPlayers[SOUTH]->offsetBidNumberBy(Temp);
	
	TSBubble->init(DirLocation);
	
	if (state != MENU)
		AllCards->init(DirLocation, state);

	Theme::init(Symbol, ELECTRIC, state);
}

void Electric::initNumbers(void)
{
	Theme::initNumbers(DirLocation);
}

void Electric::setNumberLoc(void)
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

void Electric::setSizeNumbers(void)
{
	Theme::setSizeNumbers();
	//BCBubble->BidValue.setSize(5.25f);
	BidScore->setSize(3.0f);
}

Point Electric::getFirstCardPos(unsigned short player)
{
	return FirstCardPos[player];
}