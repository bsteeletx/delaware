#include "Player.h"
#include "agk.h"

bool Player::hasPassed[4];
unsigned short Player::bid;
short Player::meldBid[4];

Player::Player(void)
{
	pMeld = -1;

	roundRobin = false;
		
	for (short int i = 0; i < 4; i++)
		for (short int j = 0; j < 5; j++)
			known[j][i] = -1;

	for (short int i = 0; i < 4; i++)
	{
		trumpingSuit[i] = false;
		runIn[i] = false;
		marriageIn[i] = false;
		meldBid[i] = -1;
	}

	numOfBids = 0;
	saveBid = false;
	doubleRun = false;
	strongestRun = 4;
	strongSuit = 4;

	leftID = -1;
	partnerID = -1;
	rightID = -1;
}

void Player::reset()
{
	pMeld = -1;

	for (int i = 0; i < 4; i++)
		meldBid[i] = -1;

	roundRobin = false;
	
	Hand.clear();

	for (short int i = 0; i < 4; i++)
		for (short int j = 0; j < 5; j++)
			known[j][i] = -1;

	for (short int i = 0; i < 4; i++)
	{
		trumpingSuit[i] = false;
		runIn[i] = false;
		marriageIn[i] = false;
	}

	numOfBids = 0;
	saveBid = false;
	doubleRun = false;
	strongestRun = 4;
	strongSuit = 4;
}

unsigned short Player::getLeftID(void)
{
	return leftID;
}

unsigned short Player::getPartnerID(void)
{
	return partnerID;
}

unsigned short Player::getRightID(void)
{
	return rightID;
}

short int Player::getNumOfBids()
{
	return numOfBids;
}

void Player::resetKnown()
{
	for (short int i = 0; i < 5; i++)
		for (short int j = 0; j < 4; j++)
			this->known[i][j] = -1;
}

bool Player::getSuitState(short int suit)
{
	return trumpingSuit[suit];
}

bool Player::getRoundRobin()
{
	return this->roundRobin;
}

void Player::toggleSaveBid()
{
	saveBid = !saveBid;
}

bool Player::getSaveBid()
{
	return this->saveBid;
}

void Player::incrementNumOfBids()
{
	numOfBids++;
}

Player::~Player(void)
{
}

void Player::setMeldBid(unsigned short int value)
{
	meldBid[playerID] = value;
}

short int Player::getMeldBid()
{
	if (meldBid < 0)
		return 0;

	return this->meldBid[playerID];
}

void Player::addToMeld(short int x)
{
	pMeld += x;
}

void Player::clearHand(void)
{
	Hand.clear();
}

void Player::clearMeld(void)
{
	pMeld = -1;
}

void Player::dealToHand(Card *FourCardDeal[4])
{
	for (short int i = 0; i < 4; i++)
		Hand.push_back(FourCardDeal[i]);
}

/*void Player::incrementHandPlaceholder()
{
	this->handPlaceholder++;
}

short int Player::getHandPlaceholder()
{
	return this->handPlaceholder;
}*/

bool Player::findCard(Card CardToFind)
{
	for (short int i = 0; i < 20; i++)
		if (Hand[i]->getRank() == CardToFind.getRank())
			return true;
	
	return false;
}

short int Player::getPMeld(void)
{
	return pMeld;
}

void Player::removeCardFromHand(Card *CardPlayed)
{
	for (unsigned int i = 0; i < Hand.size(); i++)
	{
		if (Hand[i] == CardPlayed)
			Hand.erase(Hand.begin() + i);
	}
}

Card *Player::getCard(short int value)
{
	if (value < 0)
		return NULL;
	else if (value > 19)
		return NULL;

	return Hand[value];
}

Card *Player::getCardFromPlayerHand(unsigned short rank, unsigned short suit)
{
	for (unsigned int i = 0; i < Hand.size(); i++)
	{
		if (Hand[i]->getSuit() == suit)
		{
			if (Hand[i]->getRank() == rank)
				return Hand[i];
		}
	}

	return NULL;
}

Card *Player::getCardFromPlayerHand(unsigned short cardNumber)
{
	for (unsigned int i = 0; i < Hand.size(); i++)
	{
		if (Hand[i]->getValue() == cardNumber)
			return Hand[i];
	}

	return NULL;
}


void Player::sortHand(void)
{
	bool done = false;

	while (!done)
    {
        done = true;

        for (short int i = 0; i < 19; i++) 
        {
			//special case hack for first ace of hearts
			/*if (this->hand[i] > 79)
				this->hand[i] = 0;*/

			if (Hand[i]->getRank() > Hand[i+1]->getRank())
			{
				
				Card *Temp = Hand[i];
				Hand[i] = Hand[i+1];
				Hand[i+1] = Temp;

				done = false;
			}

        }
    }
}

unsigned short Player::getCardsInHand()
{
	return Hand.size();
}

void Player::tabulateMeld()
{
	short int marriages = 0;
	short int pinochles = 0;
	short int jacks = 0;
	short int queens = 0;
	short int kings = 0;
	short int aces = 0;
	short int heartRun;
	short int clubRun;
	short int diamondRun;
	short int spadeRun;
	short int heartMarriage = 0;
	short int clubMarriage = 0;
	short int diamondMarriage = 0;
	short int spadeMarriage = 0;
	short int suitValue = 0;
	short int numberOfRuns = 0;
	//int player = this->getID();

	//check for marriages
	heartMarriage = this->getNumOfMarriages(HEARTS);
	clubMarriage = this->getNumOfMarriages(CLUBS);
	diamondMarriage = this->getNumOfMarriages(DIAMONDS);
	spadeMarriage = this->getNumOfMarriages(SPADES);
	marriages = heartMarriage + clubMarriage + diamondMarriage + spadeMarriage;

	if (this->getID() == SOUTH)
	{
		if (!marriages)
			marriages = 0;
			//agk::printc("GOT IT!");
	}

	if (heartMarriage && clubMarriage && diamondMarriage && spadeMarriage)
	{
		this->addToMeld(2);
		this->roundRobin = true;
	}
		
	//check for jacks
	jacks = this->getXAround(JACK);

	//check for pinochle
	pinochles = this->getNumOfPinochles();

	//check for queens
	queens = this->getXAround(QUEEN);

	//check for kings
	kings = this->getXAround(KING);

	//check for aces
	aces = this->getXAround(ACE);

	//check for runs
	heartRun = this->checkForRuns(HEARTS);
	clubRun = this->checkForRuns(CLUBS);
	diamondRun = this->checkForRuns(DIAMONDS);
	spadeRun = this->checkForRuns(SPADES);
	numberOfRuns = heartRun + clubRun + diamondRun + spadeRun;

	//determine strongest suit and strongest run
	if (marriages)
	{
		if (heartMarriage)
		{
			suitValue = this->getSuitValue(HEARTS);
			this->setStrongSuit(HEARTS);

			this->known[KING][HEARTS] = heartMarriage;
			this->known[QUEEN][HEARTS] = heartMarriage;
			if (heartRun)
				this->setStrongestRun(HEARTS);
		}
		if (clubMarriage)
		{
			if (suitValue < this->getSuitValue(CLUBS))
			{
				suitValue = this->getSuitValue(CLUBS);
				this->setStrongSuit(CLUBS);
				if (clubRun)
					this->setStrongestRun(CLUBS);
			}
			
			this->known[KING][CLUBS] = clubMarriage;
			this->known[QUEEN][CLUBS] = clubMarriage;
		}
		if (diamondMarriage)
		{
			if (suitValue < this->getSuitValue(DIAMONDS))
			{
				suitValue = this->getSuitValue(DIAMONDS);
				this->setStrongSuit(DIAMONDS);

				if (diamondRun)
					this->setStrongestRun(DIAMONDS);
			}

			this->known[KING][DIAMONDS] = diamondMarriage;
			this->known[QUEEN][DIAMONDS] = diamondMarriage;
		}
		if (spadeMarriage)
		{
			if (suitValue < this->getSuitValue(SPADES))
			{
				suitValue = this->getSuitValue(SPADES);
				
				this->setStrongSuit(SPADES);
				if (spadeRun)
					this->setStrongestRun(SPADES);
			}
			
			this->known[KING][SPADES] = spadeMarriage;
			this->known[QUEEN][SPADES] = spadeMarriage;

		}
	}

	this->addToMeld(1);

	this->addToMeld(marriages * 2);
	
	if (jacks == 1)
		this->addToMeld(4);
	else if (jacks == 2)
		this->addToMeld(40);

	if (jacks)
		for (short int i = 0; i < 4; i++)
		{
			this->known[JACK][i] = jacks;
		}
	
	if (queens == 1)
		this->addToMeld(6);
	else if (queens == 2)
		this->addToMeld(60);

	if (queens > heartMarriage)
		this->known[QUEEN][HEARTS] = queens;
	
	if (queens > clubMarriage)
		this->known[QUEEN][CLUBS] = queens;
	
	if (queens > diamondMarriage)
		this->known[QUEEN][DIAMONDS] = queens;
	
	if (queens > spadeMarriage)
		this->known[QUEEN][SPADES] = queens;
	
	if (queens)
	{
		this->known[KING][HEARTS] = heartMarriage;
		this->known[KING][CLUBS] = clubMarriage;
		this->known[KING][DIAMONDS] = diamondMarriage;
		this->known[KING][SPADES] = spadeMarriage;
	}

	if (kings == 1)
		this->addToMeld(8);
	else if (kings == 2)
		this->addToMeld(80);

	if (kings > heartMarriage)
		this->known[KING][HEARTS] = kings;

	if (kings > clubMarriage)
		this->known[KING][CLUBS] = kings;
	
	if (kings > diamondMarriage)
		this->known[KING][DIAMONDS] = kings;
	
	if (kings > spadeMarriage)
		this->known[KING][SPADES] = kings;
	
	if ((kings) && (queens < 2))
	{
		this->known[QUEEN][HEARTS] = heartMarriage;
		this->known[QUEEN][CLUBS] = clubMarriage;
		this->known[QUEEN][DIAMONDS] = diamondMarriage;
		this->known[QUEEN][SPADES] = spadeMarriage;
	}

	if (aces == 1)
		this->addToMeld(10);
	else if (aces == 2)
		this->addToMeld(100);

	if (aces)
	{
		for (short int i = 0; i < 4; i++)
		{
			this->known[ACE][i] = aces;
		}
	}

	if (pinochles == 1)
		this->addToMeld(4);
	else if (pinochles == 2)
		this->addToMeld(30);
	else if (pinochles == 3)
		this->addToMeld(90);
	else if (pinochles == 4)
		this->addToMeld(120);

	if (pinochles > queens)
	{
		if (pinochles > spadeMarriage)
			this->known[QUEEN][SPADES] = pinochles;
	}

	if (pinochles > jacks)
		this->known[JACK][DIAMONDS] = pinochles;
		
	if (!pinochles)
	{
		if (this->known[QUEEN][SPADES] > 0)
			this->known[JACK][DIAMONDS] = 0;
	
		if (this->known[JACK][DIAMONDS] > 0)
			this->known[QUEEN][SPADES] = 0;
	}

	if (pinochles)
	{
		if (this->known[KING][SPADES] < 0)
			this->known[KING][SPADES] = 0;
	}
}

void Player::sortCards(unsigned short theme)
{
    float offset = 0.0f;
	unsigned short handSize = Hand.size();

    if (theme == 0)
        offset = 0.5f;

	for (short int i = 0; i < handSize; i++)
	{
		if (playerID == WEST)
			getCard(i)->setPosition(WEST_LOC_X, WEST_LOC_Y + ((10 - (handSize / 2)) * CARDWIDTHH) + (((1.5f*i)-0.5f) * CARDWIDTHH));
		else if (playerID == NORTH)
			getCard(i)->setPosition(NORTH_LOC_X - ((10 - (handSize / 2)) * CARDWIDTHN) - ((i+1) * CARDWIDTHN) + offset, NORTH_LOC_Y);
		else if (playerID == EAST)
			getCard(i)->setPosition(EAST_LOC_X, EAST_LOC_Y - ((10 - (handSize / 2)) * CARDWIDTHH) - (((1.5f*i)-0.5f) * CARDWIDTHH));
		else if (playerID == SOUTH)
			getCard(i)->setPosition((SOUTH_LOC_X + ((10 - (handSize / 2)) * CARDWIDTHS)) + (i * CARDWIDTHS), SOUTH_LOC_Y);
		
		getCard(i)->setDepth(i - 3);
	}
	
}

bool Player::updateCardThrowIn(void)
{//sending four to the center
	float destinationX[8] = {45.0f, 45.0f, 45.0f, 45.0f, 45.0f, 45.0f, 45.0f, 45.0f};
	float destinationY[8] = {40.0f, 40.0f, 40.0f, 40.0f, 40.0f, 40.0f, 40.0f, 40.0f};
	//short int cardSprites[8] = {Selected->getCard(0), Selected.getCard(1), Selected.getCard(2), Selected.getCard(3), Selected.getCard(4), Selected.getCard(5), Selected.getCard(6), Selected.getCard(7)};
	float moveXperTurn[8] = {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f};
	float moveYperTurn[8] = {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f};
	float curXLocation[8] = {5.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f};
	float curYLocation[8] = {5.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f};
	bool atLocation[8] = {false, false, false, false, false, false, false, false};
	//short turn = Selected->getID();
	short totalCards = getCardsInHand();
	float offset[8];
	float median = (float) (totalCards - 1) / 2; // 3: 1, 5: 2, 7: 3----------2:0.5, 4:1.5, 6:2.5
	short adj = 1;
	float speed = 16.0f;
	const float cardwidth = 1.76f;

	if (playerID < 2)
		adj = -1;
	
	for (int i = 0; i < totalCards; i++)
	{
		if (totalCards == 1) //only happens when only one card left
		{
			offset[i] = 0.0f;
			break;
		}
		float divisor = median; // 3:1  5:2  7:3------------2:0.5, 4:1.5, 6:2.5
		float numerator = (float) (totalCards - 1); // 3:2, 5:4, 7:6--------------2:1, 4:3, 6:5
		offset[i] = 2.0f * (numerator * (i - median)) / divisor; // 3:(0:-2, 1:0, 2:2) 5:(0:-4, 1:-2, 2:0, 3:2, 4:4) 7:(0:-6, 1:-4...-----------2:(0:-1, 1:1), 4:(0:-3, 1:-1, 2:1, 3:3), 6:(0:-5, 1:...
		//above is spread between individual cards
	}

	if (playerID % 2 == BLUE)
	{
		for (int i = 0; i < totalCards; i++)
		{
			if (playerID == WEST)
				destinationX[i] = 25.0f;
			else
				destinationX[i] = 65.0f;

			destinationY[i] += offset[i] - 5.0f;
		}
	}
	else
	{
		for (int i = 0; i < totalCards; i++)
		{
			destinationX[i] += offset[i];

			if (playerID == NORTH)
				destinationY[i] = 20.0f;
			else
				destinationY[i] = 60.0f;
		}
	}

	for (short int i = 0; i < totalCards; i++)
	{
		Card *CurrentCard = getCard(i);

		curXLocation[i] = CurrentCard->getX();
		curYLocation[i] = CurrentCard->getY();
	
		if (destinationX[i] < curXLocation[i])
		{//have to go negative to reach destination
			if ((curXLocation[i] - destinationX[i]) / speed > cardwidth)
				moveXperTurn[i] = (destinationX[i] - curXLocation[i]) / speed; //normal movement rate, negative
			else if (curXLocation[i] - cardwidth >= destinationX[i])
				moveXperTurn[i] *= -2; //slower movement rate
			else
				moveXperTurn[i] = destinationX[i] - curXLocation[i]; //even out to destination, will be negative
		}
		else
		{ //have to go positive to reach destination
			if ((destinationX[i] - curXLocation[i]) / speed > cardwidth)
				moveXperTurn[i] = (destinationX[i] - curXLocation[i]) / speed; //nomal movement rate
			else if (curXLocation[i] + cardwidth <= destinationX[i])  
				moveXperTurn[i] *= 2;
			else
				moveXperTurn[i] = destinationX[i] - curXLocation[i];
		}
		
		if (destinationY[i] < curYLocation[i])
		{
			if ((curYLocation[i] - destinationY[i]) / speed > cardwidth)
				moveYperTurn[i] = (destinationY[i] - curYLocation[i]) / speed;
			else if (curYLocation[i] - cardwidth >= destinationY[i])
				moveYperTurn[i] *= -2;
			else
				moveYperTurn[i] = destinationY[i] - curYLocation[i];
		}
		else
		{
			if ((destinationY[i] - curYLocation[i]) / speed > cardwidth)
				moveYperTurn[i] = (destinationY[i] - curYLocation[i]) / speed;
			else if (curYLocation[i] + cardwidth <= destinationY[i])
				moveYperTurn[i] *= 2;
			else if (curYLocation[i] + cardwidth > destinationY[i])  //don't need to check if it's less than or equal to because it's default at 10
				moveYperTurn[i] = destinationY[i] - curYLocation[i];
		}
	
		CurrentCard->setPosition(curXLocation[i] + moveXperTurn[i], curYLocation[i] + moveYperTurn[i]);
		CurrentCard->turnFaceUp();

#if (OS != IOS)
		CurrentCard->rotate((float)(agk::Random(0, 45)+agk::Random(0, 45)));
#else
		CurrentCard->rotate((float) ((arc4random() % 46) + (arc4random() % 46)));
#endif
		if ((fabsf(moveXperTurn[i]) <= 0.001f) && (fabsf(moveYperTurn[i]) <= 0.001f))
			atLocation[i] = true;
	}

	for (int i = totalCards; i < 8; i++)
		atLocation[i] = true;

	if (atLocation[0] && atLocation[1] && atLocation[2] && atLocation[3] && atLocation[4] && atLocation[5] && atLocation[6] && atLocation[7])
		return true;
	else
		return false;
	
	/*bool rotateRight = false;
	bool rotateLeft = false;
	float destinationX[5] = {50.0f, 50.0f, 50.0f, 50.0f, 50.0f};
	float destinationY[5] = {50.0f, 50.0f, 50.0f, 50.0f, 50.0f};
	float offset[5] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
	float moveX;
	float moveY;
	float curXLocation = getX();
	float curYLocation = getY();
	float speed = 15.0f;
	float cardWidth = 1.76f;
	int turn = Selected.getID();
	int totalCards = Selected.getCardsInHand();
	
	//offset(62.5f, 87.5f);

	if (turn != SOUTH)
		turnFaceUp();
	
	switch (totalCards)
	{
	case 2:
		offset[0] = -CARDWIDTHS;
		offset[1] = CARDWIDTHS;
		break;
	case 3:
		offset[0] = -2 * CARDWIDTHS;
		offset[2] = 2 * CARDWIDTHS;
		break;
	case 4:
		offset[0] = -3 * CARDWIDTHS;
		offset[1] = -1.5f * CARDWIDTHS;
		offset[2] = 1.5f * CARDWIDTHS;
		offset[3] = 3 * CARDWIDTHS;
		break;
	case 5:
		offset[0] = -4 * CARDWIDTHS;
		offset[1] = -2 * CARDWIDTHS;
		offset[3] = 2 * CARDWIDTHS;
		offset[4] = 4 * CARDWIDTHS;
		break;
	}

	switch (turn)
	{
	case WEST:
		for (int i = 0; i < totalCards; i++)
		{
			destinationX[i] -= 20.0f;
			destinationY[i] -= 10.0f + offset[i];
		}
		rotateRight = true;
		break;
	case NORTH:
		for (int i = 0; i < totalCards; i++)
		{
			destinationX[i] -= 7.8f + offset[i];
			destinationY[i] -= 20.0f;
		}
		break;
	case EAST:
		for (int i = 0; i < totalCards; i++)
		{
			destinationX[i] += 5.0f + offset[i];
			destinationY[i] -= 10.0f;
		}
		rotateLeft = true;
		break;
	case SOUTH:
		for (int i = 0; i < totalCards; i++)
		{
			destinationX[i] -= 7.8f + offset[i];
			//destinationY[i] = ;
		}
		break;
	default:
		break;
	}

	if (destinationX[0] < curXLocation)
	{//have to go negative to reach destination
		if ((curXLocation - destinationX[0]) / speed > cardWidth)
			moveX = (destinationX[0] - curXLocation) / speed; //normal movement rate, negative
		else if (curXLocation - cardWidth >= destinationX[0])
			moveX = -cardWidth; //slower movement rate
		else
			moveX = destinationX[0] - curXLocation; //even out to destination, will be negative
	}
	else
	{ //have to go positive to reach destination
		if ((destinationX[0] - curXLocation) / speed > cardWidth)
			moveX = (destinationX[0] - curXLocation) / speed; //nomal movement rate
		else if (curXLocation + cardWidth <= destinationX[0])  
			moveX = cardWidth;
		else
			moveX = destinationX[0] - curXLocation;
	}
		
	if (destinationY[0] < curYLocation)
	{
		if ((curYLocation - destinationY[0]) / speed > cardWidth)
			moveY = (destinationY[0] - curYLocation) / speed;
		else if (curYLocation - cardWidth >= destinationY[0])
			moveY = -cardWidth;
		else
			moveY = destinationY[0] - curYLocation;
	}
	else
	{
		if ((destinationY[0] - curYLocation) / speed > cardWidth)
			moveY = (destinationY[0] - curYLocation) / speed;
		else if (curYLocation + cardWidth <= destinationY[0])
			moveY = cardWidth;
		else if (curYLocation + cardWidth > destinationY[0])  //don't need to check if it's less than or equal to because it's default at 10
			moveY = destinationY[0] - curYLocation;
	}

#if (OS != IOS)
	rotate((float)(agk::Random(0, 45)+agk::Random(0, 45)));
#else
    rotate((float) ((arc4random() % 46) + (arc4random() % 46)));
#endif

	if (curXLocation != 0.0f)
		display(curXLocation + moveX, curYLocation + moveY);
	else
	{
		display(destinationX[0], destinationY[0]);
		return true;
	}
	
	if ((fabsf(moveX) <= 0.000001f) && (fabsf(moveY) <= 0.00001f))
		return true;
	else
		return false;*/
}

/*void Player::tallyKnown(int number, int rank, int suit)
{
	int player = this->getID();

	if (suit == -1)
	{
		tallyKnown(number, rank, HEARTS);
		tallyKnown(number, rank, CLUBS);
		tallyKnown(number, rank, DIAMONDS);
		tallyKnown(number, rank, SPADES);
		return;
	}

	if (rank = -1)
	{
		switch (player)
		{
		case WEST:
			if (number > westKnown[ACE][suit])
				tallyKnown(number - westKnown[ACE][suit], ACE, suit);
			if (number > westKnown[TEN][suit])
				tallyKnown(number - westKnown[TEN][suit], TEN, suit);
			if (number > westKnown[KING][suit])
				tallyKnown(number - westKnown[KING][suit], KING, suit);
			if (number > westKnown[QUEEN][suit])
				tallyKnown(number - westKnown[QUEEN][suit], QUEEN, suit);
			if (number > westKnown[JACK][suit])
				tallyKnown(number - westKnown[JACK][suit], JACK, suit);
			break;
		case NORTH:
			if (number > northKnown[ACE][suit])
				tallyKnown(number - northKnown[ACE][suit], ACE, suit);
			if (number > northKnown[TEN][suit])
				tallyKnown(number - northKnown[TEN][suit], TEN, suit);
			if (number > northKnown[KING][suit])
				tallyKnown(number - northKnown[KING][suit], KING, suit);
			if (number > northKnown[QUEEN][suit])
				tallyKnown(number - northKnown[QUEEN][suit], QUEEN, suit);
			if (number > northKnown[JACK][suit])
				tallyKnown(number - northKnown[JACK][suit], JACK, suit);
			break;
		case EAST:
			if (number > eastKnown[ACE][suit])
				tallyKnown(number - eastKnown[ACE][suit], ACE, suit);
			if (number > eastKnown[TEN][suit])
				tallyKnown(number - eastKnown[TEN][suit], TEN, suit);
			if (number > eastKnown[KING][suit])
				tallyKnown(number - eastKnown[KING][suit], KING, suit);
			if (number > eastKnown[QUEEN][suit])
				tallyKnown(number - eastKnown[QUEEN][suit], QUEEN, suit);
			if (number > eastKnown[JACK][suit])
				tallyKnown(number - eastKnown[JACK][suit], JACK, suit);
			break;
		case SOUTH:
			if (number > southKnown[ACE][suit])
				tallyKnown(number - southKnown[ACE][suit], ACE, suit);
			if (number > southKnown[TEN][suit])
				tallyKnown(number - southKnown[TEN][suit], TEN, suit);
			if (number > southKnown[KING][suit])
				tallyKnown(number - southKnown[KING][suit], KING, suit);
			if (number > southKnown[QUEEN][suit])
				tallyKnown(number - southKnown[QUEEN][suit], QUEEN, suit);
			if (number > southKnown[JACK][suit])
				tallyKnown(number - southKnown[JACK][suit], JACK, suit);
			break;
		default:
			break;
		}
		return;
	}

	switch (player)
	{
	case WEST:
		westKnown[rank][suit] += number;
		break;
	case NORTH:
		northKnown[rank][suit] += number;
		break;
	case EAST:
		eastKnown[rank][suit] += number;
		break;
	case SOUTH:
		southKnown[rank][suit] += number;
		break;
	default:
		break;
	}
			
}*/

bool Player::getDoubleRun()
{
	return doubleRun;
}

void Player::setStrongestRun(short int suit)
{
	strongestRun = suit;
}

short int Player::getStrongestRun()
{
	return strongestRun;
}

short int Player::getNumOfRuns(void)
{
	short int count = 0;

	for (int i = 0; i < 4; i++)
	{
		if (runIn[i])
			count++;
	}
	

	return count;
}

short int Player::getDoubleRunSuit(void)
{
	short int aces;
	short int tens;
	short int kings;
	short int queens;
	short int jacks;
	short int min;

	for (short int suit = 0; suit < 4; suit++)
	{
		aces = getNumOfCardsInRange(ACE, suit);
		tens = getNumOfCardsInRange(TEN, suit);
		kings = getNumOfCardsInRange(KING, suit);
		queens = getNumOfCardsInRange(QUEEN, suit);
		jacks = getNumOfCardsInRange(JACK, suit);

		min = minNumber(aces, tens, kings, queens);
		min = minNumber(min, jacks);

		if (min > 1)
			return suit;
	}

	return -1;
}

short Player::checkForRuns(unsigned short suit)
{
	short int aces;
	short int tens;
	short int kings;
	short int queens;
	short int jacks;
	short int min;

	aces = getNumOfCardsInRange(ACE, suit);
	tens = getNumOfCardsInRange(TEN, suit);
	kings = getNumOfCardsInRange(KING, suit);
	queens = getNumOfCardsInRange(QUEEN, suit);
	jacks = getNumOfCardsInRange(JACK, suit);

	min = minNumber(aces, tens, kings, queens);
	min = minNumber(min, jacks);

	if (min > 1)
		this->doubleRun = true;

	return min;
}

bool Player::getRunInSuit(unsigned short suit)
{
	return runIn[suit];
}

short int Player::getRunSize(short int suit)
{
	short int total;

	if (suit == 4)
		return -100;

	total = this->getNumOfCardsInRange(ACE, suit) + this->getNumOfCardsInRange(TEN, suit) + this->getNumOfCardsInRange(KING, suit) + this->getNumOfCardsInRange(QUEEN, suit) + this->getNumOfCardsInRange(JACK, suit);

	return total;

}

void Player::setStrongSuit(short int suit)
{
	this->strongSuit = suit;
}

short int Player::getStrongSuit()
{
	return this->strongSuit;
}

bool Player::checkForMarriage(unsigned short suit)
{
	//bool retValue = false;
	return marriageIn[suit];

}

short int Player::getSuitValue(short int suit)
{
	short int total;

	total = (this->getNumOfCardsInRange(ACE, suit) * 5) + (this->getNumOfCardsInRange(TEN, suit) * 4) + (this->getNumOfCardsInRange(KING, suit) * 3) + (this->getNumOfCardsInRange(QUEEN, suit) * 2) + this->getNumOfCardsInRange(JACK, suit);

	return total;
}

short int Player::getXAround(short int rank)
{
	short int hearts;
	short int clubs;
	short int diamonds;
	short int spades;

	hearts = this->getNumOfCardsInRange(rank, HEARTS);
	clubs = this->getNumOfCardsInRange(rank, CLUBS);
	diamonds = this->getNumOfCardsInRange(rank, DIAMONDS);
	spades = this->getNumOfCardsInRange(rank, SPADES);

	if (rank == ACE)
		numOfAces = hearts + clubs + diamonds + spades;

	return this->minNumber(hearts, clubs, diamonds, spades);
}


short int Player::getNumOfPinochles()
{
	short int queens;
	short int jacks;

	queens = this->getNumOfCardsInRange(QUEEN, SPADES);
	jacks = this->getNumOfCardsInRange(JACK, DIAMONDS);

	return this->minNumber(queens, jacks);
}

short int Player::getNumOfMarriages(short int suit)
{
	short int kings;
	short int queens;
	//check for marriages
	kings = getNumOfCardsInRange(KING, suit);

	if (!kings)
		return 0;

	queens = getNumOfCardsInRange(QUEEN, suit);

	if (minNumber(kings, queens))
		marriageIn[suit] = true;

	return minNumber(kings, queens);
}

short int Player::minNumber(short int w, short int x)
{
	if (w < x)
		return w;
	else
		return x;
}

short int Player::minNumber(short int w, short int x, short int y, short int z)
{
	if (w < x)
		if (w < y)
			if (w < z)
				return w;
			else
				return z;
		else if (y < z)
			return y;
		else
			return z;
	else if (x < y)
		if (x < z)
			return x;
		else
			return z;
	else if (y < z)
		return y;
	else
		return z;
}

//Returns number of specified cards th player has in had, -1 is a wildcard
unsigned short Player::getNumOfCardsInRange(short rank, short suit)
{
	short count = 0; 

	for (unsigned int i = 0; i < Hand.size(); i++)
	{
		if (rank > -1)
		{
			if (Hand[i]->getRank() != rank)
				continue;
		}

		if (suit > -1)
		{
			if (Hand[i]->getSuit() != suit)
				continue;
		}

		count++;
	}

	return count;
}

short int Player::getKnownOfSuit(short int suit)
{
	short int count = -1;
	short int zeroCount = 0;

	for (short int i = ACE; i <= JACK; i++)
	{
		if (this->known[i][suit] > 0)
		{
			if (count < 0)
				count = this->known[i][suit];
			else
				count += this->known[i][suit];
		}
		else if (this->known[i][suit] == 0)
			zeroCount++;
	}

	if (zeroCount == 5)
		return 0;
	else
		return count;
}

short int Player::getID()
{
	return playerID;
}

void Player::setPlayerID(short int newID)
{
	this->playerID = newID;
}

short int Player::getNumOfAces()
{
	return this->numOfAces;
}

void Player::setBid(unsigned short amount)
{
	bid = amount;
}

void Player::incrementBid(unsigned short amount)
{
	if (!amount)
		bid++;
	else
		bid = amount;

	lastBid = bid;
}

unsigned short Player::getLastBid(void)
{
	return lastBid;
}


void Player::hideBidBubble(void)
{
	BidBubble->hide();
}

void Player::hideMeldBubble(void)
{
	MeldBubble->hide();
}
/////////From PinochleGame.cpp

short Player::determineNewMeld(unsigned short trump)
{
	unsigned short newMeld = 0;

	newMeld += getPMeld();

	newMeld += (getNumOfMarriages(trump)) * 2;

	if (getRoundRobin())
		newMeld -= 2;

	if (checkForRuns(trump))
	{
		if (getDoubleRun())
		{
			meldRun(2, trump);
			newMeld += 142;
		}
		else
		{
			newMeld += 11;
			meldRun(1, trump);
		}
	}

	addToMeld(newMeld - getPMeld());
	return getPMeld();
}

void Player::meldRun(unsigned short number, unsigned short suit)
{	
	//int player = Selected->getID();
	
	for (short int i = 0; i < 5; i++)
	{
		if (!getDoubleRun())
		{
			if (known[i][suit] <= 0)
				known[i][suit] = number;
			
			if (suit == DIAMONDS)
			{
				if ((getNumOfPinochles() == 0) && (!checkForMarriage(SPADES)) && (!getXAround(QUEEN)))
					known[QUEEN][SPADES] = 0;
			}
			else if (suit == SPADES)
			{
				if ((getNumOfPinochles() == 0) && (!checkForMarriage(DIAMONDS)) && (!getXAround(QUEEN)))
					known[JACK][DIAMONDS] = 0;
			}
		}
		else
		{
			if (!(known[i][suit] < 2))
				known[i][suit] = 2;
			
			if (suit == DIAMONDS)
			{
				if ((getNumOfPinochles() == 0) && (!checkForMarriage(SPADES)) && (!getXAround(QUEEN)))
					known[QUEEN][SPADES] = 0;
			}
			else if (suit == SPADES)
			{
				if ((getNumOfPinochles() == 0) && (!checkForMarriage(DIAMONDS)) && (!getXAround(QUEEN)))
					known[JACK][DIAMONDS] = 0;
			}
		}
	}
}

void Player::setKnown(unsigned short rank, unsigned short suit, unsigned short value)
{
	known[rank][suit] = value;
}

void Player::init(Text ThemeDir, float bidBubbleOffset, float meldBubbleOffset)
{
	MeldBubble->init(ThemeDir, playerID, false, 0.0f);
	BidBubble->init(ThemeDir, playerID, true, 0.0f);
	BidBubble->setSize(39.0f, -1.0f);
}

void Player::offsetBidNumberBy(float x, float y)
{
	BidBubble->offsetBidNumberBy(x, y);
}

void Player::offsetBidNumberBy(Point Amount)
{
	BidBubble->offsetBidNumberBy(Amount);
}

void Player::offsetMeldBubbleBy(float x, float y)
{
	MeldBubble->offsetMeldBubbleBy(x, y);
}

void Player::offsetPassBy(float x, float y)
{
	BidBubble->offsetPassBy(x, y);
}

void Player::offsetPassBy(Point Amount)
{
	BidBubble->offsetPassBy(Amount);
}

/*void Player::update(unsigned short state, Player Partner)
{
	switch (state)
	{
		//something before bidding:
		//countMeld();
	case BIDDING:
		determineMeldBid(Partner);
		break;
	case MELDING:
		break;
	case PLAYING:
		break;
	}
		
}*/

unsigned short Player::getBid(void)
{
	return bid;
}

bool Player::hasBid(void)
{
	if ((numOfBids > 0) && (pMeld >= 0))
		return true;

	return false;
}

void Player::determineMeldBid(Player Partner)
{
	unsigned short suit = 4;
	unsigned short runValue = 0;
	unsigned short topValue = 0;
	
	meld = getPMeld();
	meldBid[playerID] = meld / 10;
	numOfAces = getNumOfAces();

	if (meld % 10 == 6)
	{
		if (numOfAces >= 4)
			meldBid[playerID]++;
	}
	else if (meld % 10 == 4)
	{
		if (numOfAces >= 8)
			meldBid[playerID]++;
	}
	else if (meld % 10 == 8)
		meldBid[playerID]++;

	if (hasPassed[partnerID])
	{
		takeBid(Partner, 0);
		return;
	}

	if (!meldBid) //no meld!
	{
		if (getStrongestRun() != 4) //have a run ??
			suit = getStrongestRun();
		else if (getDoubleRun())
		{
			if (bid < 65)
				incrementBid(65);
			else
				incrementBid();

			setMeldBid(0);
			//setBidder(meldBidderID);
		}
		else // you don't have a run!
		{
			suit = getStrongSuit();

			if (!checkForMarriage(suit))
				suit = 4;
		}

		if (suit != 4)
			runValue = getSuitValue(suit);
		else
			runValue = 0;

		if (runValue >= 24)  //this is a pretty good run/marriage! 
		{
			//dbText(x, y, "*Pretty Good Suit, though!*");
			//dbSync();
			//dbWait(3*SECONDS);
			////dbWait(5 * SECONDS);
			///not first bid
			if (bid != 49)
			{
				//dbText(x, y, "*Not the first bid, has my partner gone yet?*");
				//dbSync();
				//dbWait(3*SECONDS);
				////dbWait(5 * SECONDS);
				if (Partner.getMeldBid() == -1) //partner has not given a meld bid
				{
					incrementBid();
					setMeldBid(1);
					//setBidder(meldBidderID);
					return;
				}
				else //partner has given a meld bid
				{
					//dbText(x, y, "*Yes he has, let me check how high I can go...");
					//dbSync();
					//dbWait(3*SECONDS);
					////dbWait(5 * SECONDS);
					//dbText(x, y, "...hopefully I won't have to give him a meld bid*");
					//dbSync();
					//dbWait(3*SECONDS);
					if (runValue != 4)
						topValue = findTopValue(meld + 13 + ((getNumOfMarriages(suit) - 1) * 2), getRunSize(suit));
					else
						topValue = findTopValue(meld + (2 * getNumOfMarriages(suit)), getRunSize(suit));

					if (topValue > 60)
						topValue = topValue - (topValue % 5);
					
					//dbText(x, y, "*My Top Value is........");
					//dbSync();
					//dbWait(3*SECONDS);
					//dbPrint((double)topValue);
					//dbText(x, y, "*Is it higher than the current bid?*");
					//dbSync();
					//dbWait(3*SECONDS);
					////dbWait(5 * SECONDS);

					if (topValue > bid)  //CHECK FOR PLAYER --AFTER-- THIS ONE!!!
					{
						if (bid < 60)
						{
							if (topValue >= 60) //removing any doubt of a meldbid
							{
								//dbText(x, y, "*Yes it is, and I'm removing any doubt of a meld bid by bidding...");
								if (topValue % 10 == 0)
								{
									incrementBid(60);
									incrementNumOfBids();
									incrementNumOfBids(); 
									incrementNumOfBids();//increment to 7 or 8 for run size
								//	dbPrint((double)getBid());
								}
								else
								{
									incrementBid(65);
									incrementNumOfBids();
									incrementNumOfBids();
									incrementNumOfBids();//increment to 7 or 8 for run size
								//	dbPrint((double)getBid());
								}

								//setBidder(meldBidderID);

								setMeldBid(0);

								return;
							}
							else  //bidding on a run..ouch!
							{
								incrementBid();
								setMeldBid(1);
								//setBidder(meldBidder->getID());
								return;
							}
						}
						else
						{
							return;
						}
					}
					else
					{
						if (hasPassed[partnerID])  //if Partner has NOT passed
						{
							//dbText(x, y, "***My Partner hasn't passed...");
							//dbSync();
							//dbWait(3*SECONDS);
							////dbWait(5 * SECONDS);
							//dbText(x, y, "***Does he need to be saved?");
							//dbSync();
							//dbWait(3*SECONDS);
							////dbWait(5 * SECONDS);
		
							if (hasPassed[rightID])//see if he needs to be saved
							{
								//dbText(x, y, "***Yes he does....wait, is it just between us?");
								//dbSync();
								//dbWait(3*SECONDS);
								////dbWait(5 * SECONDS);
								if (hasPassed[leftID])
								{
									//dbText(x, y, "***Yup, just between us, so do I want it?");
									//dbSync();
									//dbWait(3*SECONDS);
									takeBid(Partner, 0);
									setMeldBid(0);
									return;
								}
								
								//see if you can save your partner
								if (suit != 4) //yes I can
								{	
									//dbText(x, y, "***Yes I can, but is my marriage any good?");
									//dbSync();
									//dbWait(3*SECONDS);
									////dbWait(5 * SECONDS);
									//if so, make sure the marriage is "good"
									if (getSuitValue(suit) > 10)
									{
										toggleSaveBid();
										//meldBidder->incrementNumOfBids();
										incrementBid();
										setMeldBid(0);
										return;
									}
									else
									{
										setPass();
										setMeldBid(0);
										return;
									}
								}
								else
								{
									setPass();
									setMeldBid(0);
									return;
								}
							}
							else
							{
								setPass();
								setMeldBid(0);
								return;
							}
						}// all conditions covered
						else
						{
							setPass();
							setMeldBid(0);
							return;
						}//already an else
					}//already an else
				}//already an else
			}
			//first bid
			else if (bid == 49)
			{
				incrementBid();
				setMeldBid(0);
				incrementNumOfBids();
				incrementNumOfBids(); 
				incrementNumOfBids(); //increment to 7 or 8 for run size
				//setBidder(meldBidderID);
				return;
			}//all conditions covered
		}//all conditions covered
		else //no marriage or run worth bidding on
		{
			//dbText(x, y, "***My Partner hasn't passed...");
			//dbSync();
			//dbWait(3*SECONDS);
			////dbWait(5 * SECONDS);
			//dbText(x, y, "***Does he need to be saved??");
			//dbSync();
			//dbWait(3*SECONDS);
			////dbWait(5 * SECONDS);
		
			if (hasPassed[rightID])//see if he needs to be saved
			{
				//dbText(x, y, "***Yes he does....Can I save him?");
				//dbSync();
				//dbWait(3*SECONDS);
				////dbWait(5 * SECONDS);
				//see if you can save your partner
				if (suit != 4) //yes I can
				{	
					//dbText(x, y, "***Yes I can, but is my marriage any good?");
					//dbSync();
					//dbWait(3*SECONDS);
					////dbWait(5 * SECONDS);
					//if so, make sure the marriage is "good"
					if (getSuitValue(suit) > 10)
					{
						toggleSaveBid();
						incrementNumOfBids();
						incrementBid();
						setMeldBid(1);
						return;
					}
					else
					{
						setPass();
						setMeldBid(0);
						return;
					}
				}
				else
				{
					setPass();
					setMeldBid(0);
					return;
				}
			}
			setPass();
			setMeldBid(0);
			return;
		}
	}
	else if (bid < 59) //does have a meld bid, and can give a meld bid
	{
		if (bid == 49)
			bid = 50;
		//dbText(x, y, "I have Meld!  I'm going to give a Meld bid of....");
		//dbSync();
		//dbWait(3*SECONDS);
		////dbWait(5 * SECONDS);
		if (hasPassed[leftID] && hasPassed[rightID])
		{
			takeBid(Partner, 0);
			return;
		}
		
		if (bid + meldBid[playerID] >= 60)
		{
			//dbText(x, y, "*Wait, I can't, we're at the top already!  I'll do the best I can...");
			//dbSync();
			//dbWait(3*SECONDS);
			if (bid != 59)
			{
				setMeldBid(59 - bid);
				incrementBid(59);
				//setBidder(meldBidderID);
				return;
			}
			else
			{
				//dbText(x, y, "*Do I want to take the bid?*");
				//dbSync();
				//dbWait(3*SECONDS);
				takeBid(Partner, 0);
				setMeldBid(0);
				return;
			}
		}
		else
		{
			incrementBid(meldBid[playerID] + bid);
			setMeldBid(meldBid[playerID]);
			//setBidder(meldBidderID);
			return;
		}
	}
	else
	{
		takeBid(Partner, 0);
		setMeldBid(0);
	}
}

unsigned short int Player::findTopValue(unsigned short possibleMeld, unsigned short sizeOfSuit)
{
	return (possibleMeld + (meldBid[partnerID] * 10) + (numOfAces * 2) + (sizeOfSuit - ((20 - sizeOfSuit) / 3)) + 20);
}

void Player::setPass(unsigned short round)
{
	hasPassed[playerID] = true;
	passRound = round;
}

unsigned short Player::getPassRound(void)
{
	return passRound;
}

void Player::takeBid(Player Partner, unsigned short round)
{
	unsigned short bestR = 0;
	unsigned short bestM = 0;
	unsigned short teammateRunSize = 0;
	bool mBetterThanR = false;
	unsigned short topWRun = 0;
	unsigned short topWMarriage = 0;
	unsigned short sizeOfSuit = 0;
	//short int aces = taker->getNumOfAces();
	//short int takerID = taker->getID();

	//teammateID = teammate->getID();

	bestM = getStrongSuit();
	bestR = getStrongestRun();

	if (bestR < 4)
	{
		sizeOfSuit = getRunSize(bestR);
		
		if (getSuitValue(bestM) > getSuitValue(bestR))
			mBetterThanR = true;
	}
	else
		mBetterThanR = true;

	if (bestM == 4)
	{
		setPass(round);
		return;
	}

	if (getDoubleRun())
	{
		incrementNumOfBids();
		incrementBid();
		//setBidder(taker->getID());
		return;
	}

	//check to see if parnter has passed
	if (!hasPassed[partnerID])  //if Partner has NOT passed
	{
		if (Partner.getNumOfBids() == 0) //partner has only meld bidded (or passed)
		{
			if (hasPassed[rightID])//see if he needs to be saved
			{
				//see if you can save your partner
				if (bestM != 4) //yes I can
				{	
					//if so, make sure the marriage is "good"
					if (getSuitValue(bestM) > 10)
					{
						toggleSaveBid();
						incrementNumOfBids();
						incrementBid();
						//setBidder(taker->getID());
						return;
					}
					else //marriage sucks
					{
						setPass(round);
						return;
					}
				}
			}
			//partner does not need saving, do you even want it?
			else if (!sizeOfSuit && !mBetterThanR) //if no run or marriage, no
			{
				setPass(round);
				return;
			}
			
			if (mBetterThanR)
			{
				topWMarriage = findTopValue((getPMeld() + (2 * getNumOfMarriages(bestM))), getRunSize(bestM));
				if (topWMarriage > 60)
					topWMarriage = topWMarriage - (topWMarriage % 5);
			}

			if (bestR < 4)
			{
				if (getDoubleRun())
					topWRun = findTopValue(getPMeld() + 146 + (2 * (getNumOfMarriages(bestR) - 2)), getRunSize(bestR));
				else
					topWRun = findTopValue(getPMeld() + 13 + (2 * (getNumOfMarriages(bestR) - 1)), getRunSize(bestR));
				topWRun = topWRun - (topWRun % 5);
			}

			if (mBetterThanR)
			{
				if (topWMarriage > getBid())
				{
					if (bid < 60)
					{
						if (bid == 58)
						{
							if (topWMarriage % 10 == 0)
								incrementBid(60);
							else
								incrementBid();
						}
						else if (bid == 59)
						{
							if (topWMarriage % 10 == 0)
								incrementBid();
							else
								incrementBid(65);
						}
						else
							incrementBid();

						incrementNumOfBids();
						//setBidder(taker->getID());
						return;
					}
					else
					{
						if (topWMarriage - getBid() == 10)
							incrementBid(bid + 10);
						else
							incrementBid();

						incrementNumOfBids();
						//setBidder(taker->getID());
						return;
					}
				}
				else 
					setStrongSuit(bestR);
			}
		
			if (topWRun > getBid())
			{
				if (bid < 60)
				{
					if (bid == 58)
					{
						if (topWRun % 10 == 0)
							incrementBid(60);
						else
							incrementBid();
					}
					else if (bid == 59)
					{
						if (topWRun % 10 == 0)
							incrementBid();
						else
							incrementBid(65);
					}
					else
						incrementBid();

					incrementNumOfBids();
					//setBidder(taker->getID());
					return;
				}
				else
				{
					if (topWRun - getBid() == 10)
						incrementBid(getBid() + 10);
					else
						incrementBid();

					incrementNumOfBids();
					//setBidder(taker->getID());
					return;
				}
			}
			else //top value is not high enough
			{
				setPass(round);
				return;
			}
		}
		else  //partner indicated he had a run, determine if your run is better
		{
			teammateRunSize = ((Partner.getNumOfBids() + getNumOfBids()) * 2) + 4;

			if (bestR < 4)
			{
				topWRun = findTopValue(getPMeld() + 13 + (2 * (getNumOfMarriages(bestR) - 1)), getRunSize(bestR));
				topWRun = topWRun - (topWRun % 5);
			}
			else
			{//partner has a run, pass
				setPass(round);
				return;
			}

			if (Partner.getSaveBid() || getSaveBid())
				teammateRunSize--;

			if (teammateRunSize > sizeOfSuit)
			{
				setPass(round);
				return;
			}
			else if (topWRun > bid)
			{			
				short int modValue = 10;
					
				switch (playerID % 2)
				{
				case WEST:
					if (hasPassed[NORTH] && hasPassed[SOUTH])
						modValue = 5;
					break;
				case NORTH:
					if (hasPassed[WEST] && hasPassed[EAST])
						modValue = 5;
					break;
				}
				
				if (bid < 60)
				{
		
					if (modValue == 10)
					{
						if (bid == 58)
						{
							if (topWRun % modValue == 0)
								incrementBid(60);
							else
								incrementBid();
						}
						else if (bid == 59)
						{
							if (topWRun % modValue == 0)
								incrementBid();
							else
								incrementBid(65);
						}
						else
							incrementBid();
					}
					else
						incrementBid();

					incrementNumOfBids();
					//setBidder(taker->getID());
					return;
				}
				else
				{
					if (topWRun - bid == modValue)
						incrementBid(bid + modValue);
					else
						incrementBid();

					incrementNumOfBids();
					//setBidder(taker->getID());
					return;
				}
			}
			else //top value is not high enough
			{
				setPass(round);
				return;
			}
		}
	}
	else  //partner has passed, no need to save him
	{
		if (mBetterThanR)
		{
			topWMarriage = findTopValue(getPMeld() + (2 * getNumOfMarriages(bestM)), getRunSize(bestM));
			if (topWMarriage > 60)
				topWMarriage = topWMarriage - (topWMarriage % 5);
		}

		topWRun = findTopValue(getPMeld() + 13 + (2 * (getNumOfMarriages(bestR) - 1)), getRunSize(bestR));
		topWRun = topWRun - (topWRun % 5);

		if (mBetterThanR)
		{
			if (topWMarriage > bid)
			{
				if (bid < 60)
				{
					if (bid == 58)
					{
						if (topWMarriage % 10 == 0)
							incrementBid(60);
						else
							incrementBid();
					}
					else if (bid == 59)
					{
						if (topWMarriage % 10 == 0)
							incrementBid();
						else
							incrementBid(65);
					}
					else
						incrementBid();

					incrementNumOfBids();
					//setBidder(taker->getID());
					return;
				}
				else
				{
					if (topWMarriage - bid == 10)
						incrementBid(bid + 10);
					else
						incrementBid();

					incrementNumOfBids();
					//setBidder(taker->getID());
					return;
				}
			}
			else //best Marriage not good enough
				setStrongSuit(bestR);
		}
			
		if (topWRun > bid)
		{
			if (bid < 60)
			{
				if (bid == 58)
				{
					if (topWRun % 10 == 0)
						incrementBid(60);
					else
						incrementBid();
				}
				else if (bid == 59)
				{
					if (topWRun % 10 == 0)
						incrementBid();
					else
						incrementBid(65);
				}
				else
					incrementBid();

				incrementNumOfBids();
				//setBidder(taker->getID());
				return;
			}
			else
			{
				if (topWRun - bid == 10)
					incrementBid(bid + 10);
				else
					incrementBid();

				incrementNumOfBids();
				//setBidder(taker->getID());
				return;
			}
		}
		else //top value is not high enough
		{
			setPass(round);
			return;
		}
	}
}

void Player::displayMeld(Point FirstCardLoc, unsigned short trump)
{
	float offset = 0;
	short int count = 0;
	short int extras = 0;
	Card *SelectedCard = new Card();
	float bubbleOffset = 0.0f;
	
#if (PLATFORM == MOBILE)
    bubbleOffset = -5.0f;
#endif

	MeldBubble->show(-1);

	if (getDoubleRunSuit() && (lastBid == bid)) //if last bid equals bid, then this player took the bid and we should count the double run
	{
		for (int rank = 0; rank < 5; rank++)
		{
			if (known[rank][trump] < 2)
				known[rank][trump] = 2;
		}
	}

	for(int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++)
		{
//			int cardOffset;
			offset = (float)((100*((18 * count)/1024.0))); 

			if (known[j][i] > 0)
			{
				//int cardImage = j + (i * 5) + 1; //get general card

				if (extras == 0)
					extras = known[j][i];

				SelectedCard = getCardFromPlayerHand(j, i);

				if (playerID % 2 == 0)
					SelectedCard->unRotate();

				// code to try to get the meld to bold cards
				SelectedCard->turnFaceUp();
				SelectedCard->setPosition(FirstCardLoc.getX() + offset, FirstCardLoc.getY());
				extras--;
				count++;

				if (extras != 0)
					j--;
			}
		}
	}
}