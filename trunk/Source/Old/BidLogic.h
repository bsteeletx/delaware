#pragma once

#include "Player.h"
#include "Card.h"

class BidLogic
{
public:
	BidLogic(void);
	~BidLogic(void);

	void addToMeld(short x);

	bool checkForMarriage(std::vector<Card*> Hand, unsigned short suit);
	short checkForRuns(std::vector<Card*> Hand, unsigned short suit);
	void clearMeld(void);
	void countMeld(std::vector<Card*> Hand);

	void determineMeldBid(std::vector<Card*> Hand, Player Partner);
	short determineNewMeld(std::vector<Card*> Hand, unsigned short trump);
	void displayMeld(std::vector<Card*> Hand, Point FirstCardLoc, unsigned short trump);

	unsigned short int findTopValue(std::vector<Card*> Hand, unsigned short possibleMeld, unsigned short sizeOfSuit);

	short int getBestSuit(std::vector<Card*> Hand, short int w, short int x);
	short int getBestSuit(std::vector<Card*> Hand, short int w, short int x, short int y, short int z);
	unsigned short getBid(void);
	bool getDoubleRun();
	short int getDoubleRunSuit(void);
	unsigned short getLastBid();
	short int getMeldBid();
	short int getNumOfBids();
	short int getNumOfMarriages(short int suit);
	short int getNumOfPinochles();
	short int getNumOfRuns();
	bool getPass(unsigned short int player);
	unsigned short getPassRound(void);
	short int getPMeld(void);
	bool getRoundRobin();
	bool getRunInSuit(unsigned short suit);
	short int getRunSize(short int suit);
	bool getSaveBid();
	short int getStrongestRun();
	short int getStrongSuit();
	short int getSuitValue(short int suit);
	short int getXAround(short int rank);

	bool hasBid(void);
	void hideBidBubble(void);
	void hideMeldBubble(void);

	void incrementBid(unsigned short amount = 0);
	void incrementNumOfBids();
	void init(unsigned int playerID);

	void meldRun(unsigned short number, unsigned short suit);
	short int minNumber(short int w, short int x);
	short int minNumber(short int w, short int x, short int y, short int z);

	void reset();

	void setBid(unsigned short amount);
	void setMeldBid(unsigned short int value);
	void setPass(unsigned short round = 0);
	void setKnown(unsigned short rank, unsigned short suit, unsigned short value);
	void setStrongestRun(short int suit);
	void setStrongSuit(short int suit);
		
	void tabulateMeld();	
	void takeBid(Player Partner, unsigned short round);

private:
	static unsigned short bid;

	static unsigned short dealer;
	bool didBid;
	bool doubleRun;
	
	static bool hasPassed[4];
	
	unsigned short lastBid;
	unsigned short leftID;

	bool marriageIn[4];
	unsigned short meld;
	static short meldBid[4];
	
	short int numOfAces;
	unsigned short numOfBids;  //non-meld
	unsigned short numOfRuns;
	
	unsigned short partnerID;
	short passRound;
	unsigned short playerID;
	short int pMeld;
	
	bool roundRobin;
		
	unsigned short rightID;
	bool runIn[4];
	
	bool saveBid;
	unsigned short strongSuit;
	unsigned short strongestRun;

};

