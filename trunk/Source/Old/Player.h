#pragma once

#include "Sprite.h"
#include "Defines.h"
#include "Card.h"
#include <vector>
#include "Bubbles.h"

class Card;
class Bubbles;

class Player
{
public:
	Player(void);
	~Player(void);

	void addToMeld(short x);

	void buildDecisionTree();

	short checkForRuns(unsigned short suit);
	bool checkForMarriage(unsigned short suit);
	void clearHand(void);
	void clearMeld(void);
	void countMeld();

	void dealToHand(Card *FourCardDeal[4]);
	void determineMeldBid(Player Partner);
	short determineNewMeld(unsigned short trump);
	void displayMeld(Point FirstCardLoc, unsigned short trump);

	bool findCard(Card CardToFind);
	unsigned short int findTopValue(unsigned short possibleMeld, unsigned short sizeOfSuit);
	
	short int getBestSuit(short int w, short int x);
	short int getBestSuit(short int w, short int x, short int y, short int z);
	unsigned short getBid(void);
	bool getDoubleRun();
	short int getDoubleRunSuit(void);
	short int getKnownOfSuit(short int suit);
	Card *getCard(short int value);
	Card *getCardFromPlayerHand(unsigned short rank, unsigned short suit);
	Card *getCardFromPlayerHand(unsigned short cardNumber);
	unsigned short getCardsInHand();
	short int getID();
	unsigned short getLastBid();
	unsigned short getLeftID();
	short int getMeldBid();
	short int getNumOfAces();
	short int getNumOfBids();
	unsigned short getNumOfCardsInRange(short rank, short suit);
	short int getNumOfMarriages(short int suit);
	short int getNumOfPinochles();
	short int getNumOfRuns();
	unsigned short getPartnerID();
	bool getPass(unsigned short int player);
	unsigned short getPassRound(void);
	short int getPMeld(void);
	unsigned short getRightID();
	bool getRoundRobin();
	bool getRunInSuit(unsigned short suit);
	short int getRunSize(short int suit);
	bool getSaveBid();
	short int getStrongestRun();
	short int getStrongSuit();
	bool getSuitState(short int suit);
	short int getSuitValue(short int suit);
	short int getXAround(short int rank);

	bool hasBid(void);
	void hideBidBubble(void);
	void hideMeldBubble(void);

	void incrementBid(unsigned short amount = 0);
	void incrementNumOfBids();
	void init(Text ThemeDir, float bidBubbleOffset, float meldBubbleOffset);

	
	void meldRun(unsigned short number, unsigned short suit);
	short int minNumber(short int w, short int x);
	short int minNumber(short int w, short int x, short int y, short int z);

	void offsetBidNumberBy(float x, float y);
	void offsetBidNumberBy(Point Amount);
	void offsetMeldBubbleBy(float x, float y);
	void offsetPassBy(float x, float y);
	void offsetPassBy(Point Amount);
	
	void reset();
	void resetKnown();
	void removeCardFromHand(Card *CardPlayed);

	void setBid(unsigned short amount);
	void setMeldBid(unsigned short int value);
	void setPass(unsigned short round = 0);
	void setPlayerID(short int newID);
	void sortCards(unsigned short theme);
	void sortHand();
	void setKnown(unsigned short rank, unsigned short suit, unsigned short value);
	void setStrongestRun(short int suit);
	void setStrongSuit(short int suit);
		
	void tabulateMeld();	
	void takeBid(Player Partner, unsigned short round);
	void togglePass(short int passer);
	void toggleSaveBid();

	//void update(unsigned short state, Player Partner = NULL);
	//bool updateBid(Theme *CurrentTheme);  //returns true if bid, false if not
	bool updateCardThrowIn(void);
	
private:
	static unsigned short bid;

	static unsigned short dealer;
	bool didBid;
	bool doubleRun;
	
	static bool hasPassed[4];

	unsigned short known[5][4];
	
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
	short int playerID;
	short int pMeld;
	
	bool roundRobin;
		
	unsigned short rightID;
	bool runIn[4];
	
	bool saveBid;
	unsigned short strongSuit;
	unsigned short strongestRun;
	
	bool trumpingSuit[4];
	
	std::vector<Card*> Hand;

	Bubbles *MeldBubble;
	Bubbles *BidBubble;
};