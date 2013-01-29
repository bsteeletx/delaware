#include "BidLogic.h"

bool BidLogic::hasPassed[4];
unsigned short BidLogic::bid;
short BidLogic::meldBid[4];

BidLogic::BidLogic(void)
{
	pMeld = -1;

	roundRobin = false;
		
	for (short int i = 0; i < 4; i++)
	{
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
	playerID = -1;
}


BidLogic::~BidLogic(void)
{
}

void BidLogic::init(unsigned int BidLogicID)
{
	leftID = (BidLogicID + 1) % 4;
	playerID = BidLogicID;
	partnerID = (BidLogicID + 2) % 4;
	rightID = (BidLogicID + 3) % 4;
}

void BidLogic::reset(void)
{
	pMeld = -1;

	for (int i = 0; i < 4; i++)
		meldBid[i] = -1;

	roundRobin = false;
	
	for (short int i = 0; i < 4; i++)
	{
		runIn[i] = false;
		marriageIn[i] = false;
	}

	numOfBids = 0;
	saveBid = false;
	doubleRun = false;
	strongestRun = 4;
	strongSuit = 4;
}

short int BidLogic::getNumOfBids()
{
	return numOfBids;
}

bool BidLogic::getRoundRobin()
{
	return this->roundRobin;
}

bool BidLogic::getSaveBid()
{
	return this->saveBid;
}

void BidLogic::incrementNumOfBids()
{
	numOfBids++;
}

void BidLogic::setMeldBid(unsigned short int value)
{
	meldBid[playerID] = value;
}

short int BidLogic::getMeldBid()
{
	if (meldBid < 0)
		return 0;

	return this->meldBid[playerID];
}

void BidLogic::addToMeld(short int x)
{
	pMeld += x;
}

short int BidLogic::getPMeld(void)
{
	return pMeld;
}

void BidLogic::tabulateMeld()
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
