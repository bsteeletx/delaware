#pragma once

#include "Player.h"
#include "Defines.h"
#include "Card.h"

class Player;
class Card;

class TrickGame
{
public:
	TrickGame();
	~TrickGame(void);

	void addBulkPoints(short team, short points);

	void buildDecisionTree();

	short int findRank(short int value, bool trumped);
	Card *followLead(Player *Selected, short int rank, short int suit, bool lTrump, bool pTrump, short int count);

	short int getHTricks();
	short int getLead();
	short int getLeadSuit();
	short int getNumOfCardsLeft(short int rank, short int suit);
	short int getTopRank();
	short int getTopSuit();
	short int getTrickCounter();
	short int getTricksPlayed();
	short int getTrumpSuit();
	short int getVTricks();

	void lastTrick(short int player);
	
	Card *playCard(Player *All[4], unsigned short count, unsigned short turn, Card *PlayerCard);
	void playedCard(Card *PlayedCard, Player *Selected);
	short int potentialTrickValue(Player *All[4], short int rank, short int suit, unsigned short turn);
	short int potPlays(Player *All[4], unsigned short starter, unsigned short turn, short int rank, short int suit, bool *trumped, short int *trumpRank, bool lostTrick, short int loopType);
	
	void reset();
	
	void setLead(short int turn);
	void setLeadSuit(short int suit);
	void setTopRank(short int rank);
	void setTopSuit(short int suit);
	void setTrumpSuit(short int suit);
	Card *startTrick(Player *All[4], unsigned short turn);

	void tallyTrick();
	
	bool updateShrinkCloseTrick(short int location, Card *Trick[4]);
	void updateTrump(short int trumpPlayed);

private:
	short int trump;
	short int lead;
	short int playedCards[5][4];
	short int trumpLeft;
	short int topRank;
	short int topSuit;
	short int leadSuit;
	short int verticalTricks;
	short int horizontalTricks;
	short int trickValue;
	short int trickCounter;
	short int cardValues[5][4];
	short int tricksPlayed;
	short int bidWinner;
};
