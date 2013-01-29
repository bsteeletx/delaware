#include "Bubbles.h"
#include "agk.h"

Bubbles::Bubbles(void)
{
	Bid = new Numbers();
	BidPass = new Sprite();
	ParentImage = new Sprite();
}


Bubbles::~Bubbles(void)
{
}

void Bubbles::init(Text ThemeDir, unsigned short playerID, bool  setIsBidBubble, float offsetGraphics)
{
	isBidBubble = setIsBidBubble;
	Text FileNameToLoad;
	Text ParentFileName = ThemeDir;

	FileNameToLoad.init("BidBubble.png");
	ParentFileName += FileNameToLoad;

	if (ParentFileName == ParentImage->getFilename()) //no changes
		return;

	ParentImage->parentInit(ParentFileName);

	switch (playerID)
	{
	case WEST:
		if (isBidBubble)
			FileNameToLoad.setString("west_bid.png");
		else
			FileNameToLoad.setString("west_meld.png");
		break;
	case NORTH:
		if (isBidBubble)
			FileNameToLoad.setString("north_bid.png");
		else
			FileNameToLoad.setString("north_meld.png");
		break;
	case EAST:
		if (isBidBubble)
			FileNameToLoad.setString("east_bid.png");
		else
			FileNameToLoad.setString("east_meld.png");
		break;
	case SOUTH:
		if (isBidBubble)
			FileNameToLoad.setString("south_bid.png");
		else
			FileNameToLoad.setString("south_meld.png");
		break;
	}
    
	Sprite::subInit(ParentImage->getImageNumber(), FileNameToLoad);
    
	Bid->init(ThemeDir);
	Bid->setSize(39.0f);

	BidPass->setSize(19.5f);

	FileNameToLoad = ThemeDir;
	FileNameToLoad.setString("pass_bid.png");
	BidPass->subInit(ParentImage->getImageNumber(), FileNameToLoad);

	switch (playerID)
	{
	case WEST:
		if (isBidBubble)
		{
			setPosition(14.5f + offsetGraphics, 12.0f);
	
			Bid->setLocation(2, 26.0f, 32.0f);
			Bid->setLocation(1, 32.0f, 32.0f);
			Bid->setLocation(0, 38.0f, 32.0f);

			BidPass->setPosition(26.0f, 25.0f);
		}
		else
			setPosition(19.5, 7.0);
		break;
	case NORTH:
		if (isBidBubble)
		{
			setPosition(30.0f, 13.0f + offsetGraphics);

			Bid->setLocation(2, 40.5f, 31.5f);
			Bid->setLocation(1, 46.5f, 31.5f);
			Bid->setLocation(0, 52.5f, 31.5f);

			BidPass->setPosition(35.25f, 29.0f);
		}
		else
			setPosition(19.5f, 7.0f);

		break;
	case EAST: //EAST IS NEGATIVE!
		if (isBidBubble)
		{
			setPosition(46.0f - offsetGraphics, 12.0f);

			Bid->setLocation(2, 54.5f, 32.0f);
			Bid->setLocation(1, 60.5f, 32.0f);
			Bid->setLocation(0, 66.5f, 32.0f);

			BidPass->setPosition(54.0f, 25.0f);
		}
		else
			setPosition(22.0f, 8.0f);
		break;
	case SOUTH:
		//SOUTH IS NEGATIVE!!!
		if (isBidBubble)
		{
			setPosition(30.0f, 35.0f - offsetGraphics);

			Bid->setLocation(2, 40.5f, 32.0f);
			Bid->setLocation(1, 46.5f, 32.0f);
			Bid->setLocation(0, 52.5f, 58.0f);

			BidPass->setPosition(40.0f, 51.0f);
			break;
		}
		else
			setPosition(23.5, 14.5);
	}
    
	hide();
}

void Bubbles::hide(void)
{
	setVisible(false);
	Bid->hideAll();
	BidPass->setVisible(false);
}

void Bubbles::setDepth(short unsigned int value)
{
	Sprite::setDepth(value);
	Bid->setDepth(value - 1);
	BidPass->setDepth(value - 1);
}

void Bubbles::show(short bidValue)
{
	setVisible(true);

	if (bidValue > 49)
	{
		Bid->setValue(bidValue);
		Bid->showAll();
	}
	else if (!bidValue)
		BidPass->setVisible(true);
}

void Bubbles::offsetBidNumberBy(Point Location)
{
	float x = Location.getX();
	float y = Location.getY();

	for (int i = 0; i < 3; i++)
		Bid->setLocation(i, Bid->getX(i) + x, Bid->getY(i) + y);
}

void Bubbles::offsetPassBy(Point Location)
{
	float x = Location.getX();
	float y = Location.getY();
	Point BidPassPoint;

	BidPassPoint.init(BidPass->getX() + x, BidPass->getY() + y);

	BidPass->setPosition(BidPassPoint);
}

void Bubbles::offsetBidNumberBy(float x, float y)
{
	for (int i = 0; i < 3; i++)
		Bid->setLocation(i, Bid->getX(i) + x, Bid->getY(i) + y);
}

void Bubbles::offsetPassBy(float x, float y)
{
	Point BidPassPoint;

	BidPassPoint.init(BidPass->getX() + x, BidPass->getY() + y);

	BidPass->setPosition(BidPassPoint);
}

void Bubbles::offsetMeldBubbleBy(float x, float y)
{
	Point Position = Sprite::getPosition();

	if (!isBidBubble)
	{
		Position.addToX(x);
		Position.addToY(y);
		Sprite::setPosition(Position);
	}
}