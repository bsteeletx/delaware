#include "Noel.h"


Noel::Noel(void)
{

}


Noel::~Noel(void)
{
}


void Noel::init(AnimatedSprite *Symbol, unsigned short state)
{
	Text TempText = Text();
	DirLocation.init("noel/");

#if (PLATFORM != MOBILE)
	FirstCardPos[WEST].init(31.5f, 36.75f);
	FirstCardPos[NORTH].init(31.0f, 36.5f);
	FirstCardPos[EAST].init(34.0f, 37.0f);
	FirstCardPos[SOUTH].init(35.4f, 44.5f);
#else
	FirstCardPos[WEST].init(32.5f, 40.5f);
	FirstCardPos[NORTH].init(30.0f, 45.0f);
	FirstCardPos[EAST].init(29.5f, 40.5f);
	FirstCardPos[SOUTH].init(32.45f, 38.ff);
#endif
	Text TempDir = DirLocation;

	setNumberData();
	setNumberPrio();
	setNumberLoc();
	setSizeNumbers();

	if (state == 0)
		initNumbers();

	TempText.init("background.png");
	TempDir += TempText;
	Background->parentInit(TempDir);

	TempDir = DirLocation;
	TempText.setString("menu");
	TempDir += TempText;
	InGameMenuButton->init(0, TempDir);
	BCBubble->init(DirLocation, 5.25f);

	for (int i = 0; i < 4; i++)
		AllPlayers[i]->init(DirLocation, 5.0f, 5.0f);
	
	Point TempPoint = Point();
	TempPoint.setCoords(-1.0f, 1.0f);
	AllPlayers[WEST]->offsetBidNumberBy(TempPoint);
	TempPoint.addToY(-1.0f);
	AllPlayers[WEST]->offsetPassBy(TempPoint);
	TempPoint.setCoords(0.0f, -2.5f);
	AllPlayers[NORTH]->offsetBidNumberBy(TempPoint);
	TempPoint.setCoords(0.0f, -3.0f);
	AllPlayers[NORTH]->offsetPassBy(TempPoint);
	TempPoint.setCoords(2.0f, 0.75f);
	AllPlayers[EAST]->offsetBidNumberBy(TempPoint);
	TempPoint.setCoords(2.5f, 0.0f);
	AllPlayers[EAST]->offsetPassBy(TempPoint);
	TempPoint.setCoords(0.0f, 3.0f);
	AllPlayers[SOUTH]->offsetBidNumberBy(TempPoint);
	TempPoint.setCoords(1.0f, 2.5f);
	AllPlayers[SOUTH]->offsetPassBy(TempPoint);

	TSBubble->init(DirLocation);
	
	if (state != MENU)
		AllCards->init(DirLocation, state);

	Theme::init(Symbol, NOEL, state);
}

void Noel::initNumbers(void)
{
	Theme::initNumbers(DirLocation);
}

void Noel::setNumberLoc(void)
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

void Noel::setSizeNumbers(void)
{
	Theme::setSizeNumbers();
	//BCBubble->BidValue.setSize(5.25f);
	BidScore->setSize(3.0f);
}

Point Noel::getFirstCardPos(unsigned short player)
{
	return FirstCardPos[player];
}