#include "Card.h"
#include "../template.h"

Card::Card()
{
	isRotated = false;
	rotateAmount = 0.0f;
    cardBackImageNumber[0] = 0;
    cardBackImageNumber[1] = 0;
    cardBackImageNumber[2] = 0;
}

Card::Card(short unsigned int frontImageNumber, short unsigned int backImageNumber)
{
	isRotated = false;
	rotateAmount = 0.0f;
}

Card::~Card(void)
{

}

void Card::init(Text FilePath, short int rankNum, short int suitNum)
{
    unsigned int parentImgNum = 0;
    Text ParentFileName = Text();
	Text CardFileName = Text();
	Text BaseFileName = Text();
	Text FrontFileName = Text();
	Text BackFileNameBase = Text();
	Text BackFileName = Text();
	Text OutlinedFileName = Text();
	Text Rank = Text();
	Text Suit = Text();
	Text Extension = Text();
	Text OutlineExtension = Text();

	ParentFileName = FilePath;
	CardFileName.init("Cards.png");
	ParentFileName += CardFileName;

	Extension.init(".png");
	OutlineExtension.init("_m");

	if (!rankNum && !suitNum)
	{
        ParentImage->parentInit(FilePath);
		parentImgNum = ParentImage->getImageNumber();
	}
	
	Rank = getRank(rankNum);
	Suit = getSuit(suitNum);

	//Set all of the names to the base
	BaseFileName = Rank;
	FrontFileName = BaseFileName;
	OutlinedFileName = BaseFileName;
	
	//front is easies
	FrontFileName += Extension;
	Front->subInit(parentImgNum, FrontFileName);

	//outline isn't too much more difficult
	OutlinedFileName += OutlineExtension;
	OutlinedFileName += Extension;
	Outlined->subInit(parentImgNum, OutlinedFileName);

	//back is a little more difficult due to Ancient, which might be abstracted out someday
	BackFileNameBase.init("card_back2.png");
	
	//check to see if multiple cardbacks exist

	if (agk::GetFileExists(BackFileNameBase.getString()))
	{
#if (OS == IOS)
		short int tempNum = arc4random() % 3;
#else
		short tempNum = agk::Random(0, 2);
#endif
		Text Buffer;
		multipleBack = true;
        
		BackFileNameBase.setString("card_back");

		if (tempNum != 0)
		{
			Buffer.init(agk::Str(tempNum+1));
			BackFileNameBase += Buffer;
		}
	}
	else
    {
		BackFileNameBase.setString("card_back");
		multipleBack = false;
    }
    
	BackFileName = BackFileNameBase;
	BackFileName += Extension;
	Back->subInit(parentImgNum, BackFileName);

	//setup all of the other values
    rank = rankNum;
	suit = suitNum;
	cardValue = suitNum*20 + rankNum;

	//setup sounds
	Cards[0]->init("sounds/cardshuffle1.wav");
	Cards[1]->init("sounds/cardshuffle2withbridge.wav");
	Cards[2]->init("sounds/cardshuffle3.wav");
	Cards[3]->init("sounds/cardslide2.wav");
	Cards[4]->init("sounds/cardslide1.wav");
	Cards[5]->init("sounds/cardslide3.wav");
	Cards[6]->init("sounds/cardslide4.wav");
	Cards[7]->init("sounds/cardslide5.wav");
	Cards[8]->init("sounds/cardbridge1.wav");
	Cards[9]->init("sounds/gettingcardsstraightend.wav");

	Trump[4]->init("sounds/glassbreak1.wav");
	Trump[3]->init("sounds/glassbreak2.wav");
	Trump[2]->init("sounds/glassbreak3.wav");
	Trump[1]->init("sounds/carcrash1.wav");
	Trump[0]->init("sounds/dynamite1.wav");
}

void Card::playSound(unsigned int sound)
{
	Cards[sound - 1]->play();
}

unsigned short Card::getValue(void)
{
	return cardValue;
}

Point Card::getLocation(void)
{
	Point ReturnPoint;

	ReturnPoint.init(getX(), getY());

	return ReturnPoint;
}

unsigned int Card::getFrontImage()
{
    return Front->getImageNumber();
}

unsigned int Card::getBackImage()
{
    return Back->getImageNumber();
}

unsigned int Card::getOutlineImage()
{
    return Outlined->getImageNumber();
}

bool Card::getIsOutlined(void)
{
	return isTrump;
}

bool Card::getFaceDirection(void)
{
	return isFaceDown;
}

Text Card::getSuit(short int suitNum)
{
	Text ReturnText;

	switch(suitNum)
	{
	case 0:
		ReturnText.init("hearts");
		break;
	case 1:
		ReturnText.init("clubs");
		break;
	case 2:
		ReturnText.init("diamonds");
		break;
	case 3:
		ReturnText.init("spades");
		break;
	}

	return ReturnText;

}

Text Card::getRank(short int rankNum)
{
	Text ReturnText;

	switch(rankNum)
	{
	case 0:
		ReturnText.init("ace");
		break;
	case 1:
		ReturnText.init("10");
		break;
	case 2:
		ReturnText.init("king");
		break;
	case 3:
		ReturnText.init("queen");
		break;
	case 4:
		ReturnText.init("jack");
		break;
	}

	return ReturnText;
}

void Card::turnFaceDown(void)
{
	Front->setVisible(false);
	Outlined->setVisible(false);
	Back->setVisible(true);
	
	isFaceDown = true;
}

void Card::turnFaceUp(void)
{
	Back->setVisible(false);
	
	if (isTrump)
		Outlined->setVisible(true);
	else
		Front->setVisible(true);

	isFaceDown = false;

}

void Card::rotateLeft()
{
	rotate(270.0f, false);
	rotatedLeft = true;
}

void Card::rotateRight()
{
	rotate(90.0f, false);
	rotatedRight = true;
}

float Card::getRotationAmount(void)
{
	return rotateAmount;
}

void Card::unRotate()
{
	Front->setAngle(0.0f);
	Back->setAngle(0.0f);
	Outlined->setAngle(0.0f);
	rotateAmount = 0.0f;
	isRotated = false;
	rotatedLeft = false;
	rotatedRight = false;
}

bool Card::getIsRotated()
{
	return isRotated;
}

float Card::getX(void)
{
	return Front->getX();
}

float Card::getY(void)
{
	return Front->getY();
}

bool Card::isRotatedLeft(void)
{
	return rotatedLeft;
}

bool Card::isRotatedRight(void)
{
	return rotatedRight;
}

void Card::rotate(float amount, bool additive)
{
	isRotated = true;
	rotateAmount = amount;

	if (additive)
		rotateAmount += amount;

	Front->setAngle(rotateAmount);
	Back->setAngle(rotateAmount);
	Outlined->setAngle(rotateAmount);
}

void Card::raiseHeight()
{
	Front->setY((float)(SOUTH_LOC_Y - (100.0f*(50.0f/1024.0f))));  //TODO: CHECK THESE VALUES
	Outlined->setY((float)(SOUTH_LOC_Y - (100.0f*(50.0f/1024.0f))));
	Back->setY((float)(SOUTH_LOC_Y - (100.0f*(50.0f/1024.0f))));
}

void Card::resetHeight(void)
{
	Front->setY((float) SOUTH_LOC_Y);
	Back->setY((float) SOUTH_LOC_Y);
	Outlined->setY((float) SOUTH_LOC_Y);
}

void Card::unOutlineCard(void)
{
	isTrump = false;
	Outlined->setVisible(false);

	if(!isFaceDown)
		Front->setVisible(false);
	else
		Front->setVisible(true);
}

void Card::outlineCard(void)
{
	Front->setVisible(false);
	Outlined->setVisible(!isFaceDown);
	
	isTrump = true;
}

void Card::revealAllCardsFrom(Player *Selected)
{
	for (short int i = 0; i < Selected->getCardsInHand(); i++)
		Selected->getCard(i)->turnFaceUp();
}

bool Card::updateCardLoc(short int turn)
{//sending one at a time to the center
	bool rotateRight = false;
	bool rotateLeft = false;
	float destinationX = 50.0f;
	float destinationY = 50.0f;
	float moveX;
	float moveY;
	float curXLocation = getX();
	float curYLocation = getY();
	float speed = 15.0f;
	float cardWidth = 1.76f;
	
	//offset(62.5f, 87.5f);
#if (OS != IOS)
	unsigned short randomSound = agk::Random(4, 8);
#else
    unsigned short randomSound = (arc4random() % 5) + 4;
#endif

	playSound(randomSound);

	if (turn != SOUTH)
		turnFaceUp();

	switch (turn)
	{
	case WEST:
		destinationX -= 20.0f;
		destinationY -= 10.0f;
		rotateRight = true;
		break;
	case NORTH:
		destinationX -= 7.8f;
		destinationY -= 20.0f;
		break;
	case EAST:
		destinationX += 5.0f;
		destinationY -= 10.0f;
		rotateLeft = true;
		break;
	case SOUTH:
		destinationX -= 7.8f;
		//destinationY += 10.0f;
		break;
	default:
		break;
	}

	if (destinationX < curXLocation)
	{//have to go negative to reach destination
		if ((curXLocation - destinationX) / speed > cardWidth)
			moveX = (destinationX - curXLocation) / speed; //normal movement rate, negative
		else if (curXLocation - cardWidth >= destinationX)
			moveX = -cardWidth; //slower movement rate
		else
			moveX = destinationX - curXLocation; //even out to destination, will be negative
	}
	else
	{ //have to go positive to reach destination
		if ((destinationX - curXLocation) / speed > cardWidth)
			moveX = (destinationX - curXLocation) / speed; //nomal movement rate
		else if (curXLocation + cardWidth <= destinationX)  
			moveX = cardWidth;
		else
			moveX = destinationX - curXLocation;
	}
		
	if (destinationY < curYLocation)
	{
		if ((curYLocation - destinationY) / speed > cardWidth)
			moveY = (destinationY - curYLocation) / speed;
		else if (curYLocation - cardWidth >= destinationY)
			moveY = -cardWidth;
		else
			moveY = destinationY - curYLocation;
	}
	else
	{
		if ((destinationY - curYLocation) / speed > cardWidth)
			moveY = (destinationY - curYLocation) / speed;
		else if (curYLocation + cardWidth <= destinationY)
			moveY = cardWidth;
		else if (curYLocation + cardWidth > destinationY)  //don't need to check if it's less than or equal to because it's default at 10
			moveY = destinationY - curYLocation;
	}

#if (OS != IOS)
	rotate((float)(agk::Random(0, 45)+agk::Random(0, 45)));
#else
    rotate((float) ((arc4random() % 46) + (arc4random() % 46)));
#endif

	if (curXLocation != 0.0f)
	{
		Point MoveTo;
		MoveTo.init(curXLocation + moveX, curYLocation + moveY);
		setPosition(MoveTo);
	}
	else
	{
		Point MoveTo;
		MoveTo.init(destinationX, destinationY);
		setPosition(MoveTo);
		return true;
	}
	
	if ((fabsf(moveX) <= 0.000001f) && (fabsf(moveY) <= 0.00001f))
		return true;
	else
		return false;
}

Card *Card::updateCardPos(Player *South, short int topSuit, short int topRank, short int leadSuit, short int trump, short int firstPlay)
{
	float mouseX = agk::GetPointerX();
	//float mouseY = agk::GetPointerY();
	short int cardSel;
	short int maxCards = South->getCardsInHand();
	Card *Selected;
	//Deck test;
	bool raiseCard = true;
	bool trumped;

	if (leadSuit != topSuit)
		trumped = true;
	else
		trumped = false;

	//if (mouseX - SOUTH_LOC_X < 0)
		//cardSel = 0;
	cardSel = (short int) ((mouseX - (SOUTH_LOC_X + ((10 - (maxCards / 2)) * CARDWIDTHS))) / CARDWIDTHS);
	
	if (cardSel > maxCards - 1)
        cardSel = maxCards - 1;
	else if (cardSel < 0)
		cardSel = 0;

	Selected = South->getCard(cardSel);
	//make sure selection is valid
	if (firstPlay % 4 != 0)
	{//not first to play
		//check if player has to beat top play
		//check that player has suit
		if (South->getNumOfCardsInRange(-1, leadSuit))
		{//player has suit
			if (Selected->getSuit() != leadSuit)
				raiseCard = false;
			else
			{//has suit, check to see if player has a higher ranked card
				if ((topRank != ACE) && !trumped)
				{//has suit, !trumped, and lead was not an ACE
					short int count = 0;
					
					for (short int i = 1; i < topRank + 1; i++)
						count += South->getNumOfCardsInRange(topRank - i, leadSuit);
					if (count)
					{//has suit, !trumped, lead was not an ACE, and Player has cards that can beat topRank
						if (Selected->getRank() >= topRank)
							raiseCard = false;
					}//no else as if player cannot beat top rank, all cards in suit are valid7
				}//has suit, !trumped, lead WAS an ACE, anything in suit is okay
				//has suit, trumped, anything in suit is okay
			}
		}
		else
		{//player does not have suit, must trump
			if (South->getNumOfCardsInRange(-1, trump))
			{//player has trump
				if (Selected->getSuit() != trump)
					raiseCard = false;
				if (trumped)
				{//already trumped, must beat it if possible
					if (topRank != ACE)
					{//can you beat it?
						short int count = 0;
					
						for (short int i = 1; i < topRank + 1; i++)
							count += South->getNumOfCardsInRange(topRank - i, trump);
						if (count)
						{//can beat topRank
							if (Selected->getRank() >= topRank)
								raiseCard = false;
						}//can't beat, in trump section
					}//topRank IS an Ace, cannot beat, already in trump section
				}//not already trumped, already in trump section, can play anything
			}//if player doesn't have trump, can play anything
		}
	}//first to play, can play anything

	if (raiseCard)
		Selected->raiseHeight();

	for (short int i = 0; i < maxCards; i++)
	{
		if (South->getCard(i)->getY() != SOUTH_LOC_Y)
			if (i !=  cardSel)
				South->getCard(i)->resetHeight();
	}	

	if (raiseCard)
		return South->getCard(cardSel);
	else
		return NULL;
}

short int Card::getRank()
{
	return rank;
}

short int Card::getSuit()
{
	return suit;
}

void Card::setSize(float value)
{
	Front->setSize(value);
	Back->setSize(value);
	Outlined->setSize(value);
}

void Card::offset(float x, float y)
{
	Front->setOffset(x, y);
	Back->setOffset(x, y);
	Outlined->setOffset(x, y);
}

void Card::setDepth(unsigned short int value)
{
	Front->setDepth(value);
	Back->setDepth(value);
	Outlined->setDepth(value);
}

void Card::setPosition(Point Location)
{
	Front->setPosition(Location);
	Back->setPosition(Location);
	Outlined->setPosition(Location);
}

void Card::setPosition(float x, float y)
{
	Front->setPosition(x, y);
	Back->setPosition(x, y);
	Outlined->setPosition(x, y);
}

void Card::show(void)
{
	Front->setVisible(!isFaceDown && !isTrump);
	Outlined->setVisible(!isFaceDown && isTrump);
	Back->setVisible(isFaceDown);
}

void Card::hide(void)
{
	Front->setVisible(false);
	Outlined->setVisible(false);
	Back->setVisible(false);
}