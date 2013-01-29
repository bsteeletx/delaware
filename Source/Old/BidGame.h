#pragma once

#include "Player.h"
#include "Defines.h"
#include "Theme.h"

class Player;
class Theme;

class BidGame
{
public:
	BidGame();
	~BidGame(void);
	
	unsigned short int findTopValue(unsigned short int meld, unsigned short int partnerMeld, short int aces, short int size);
	
	short int getBestSuit(short int w, short int x);
	short int getBestSuit(short int w, short int x, short int y, short int z);
	unsigned short int getBid();
	short int getBidder();
	bool getBidDecided();
	short int getBidWinner();
	bool getBidStatus();
	short int getDealer();
	unsigned short int getFinalBid();
	bool getPass(unsigned short int player);
	short int getPassRound(short int player);
	
	void incrementBid();
	void incrementBid(unsigned short int newBid);
	
	void meldBid(Player *, Player *);
	
	
	void playerMeldBid(Player *South, Player *North, unsigned short int newBid);
	void playerTakeBid(Player *South, Player *North, short int round, unsigned short int newBid);
	
	void reset();
	
	void setBid(unsigned short int newBid);
	void setBidder(unsigned short int player);
	void setDealer(unsigned short int value);
	void setPass(short int player, short int round = 0);
	void setPlayerBid(unsigned short int playerID);
	
	void takeBid(Player *taker, Player *teammate, short int round);
	void toggleBidDecided();
	void togglePass(short int passer);
	
	bool updateBid(Theme *CurrentTheme);  //returns true if bid, false if not
	
	short int wPassRound;
	short int nPassRound;
	short int ePassRound;
	short int sPassRound;

private:
	unsigned short int bid;
	short int bidder;
	bool bidDecided;
	bool wPass;
	bool nPass;
	bool ePass;
	bool sPass;
	bool wBid;
	bool nBid;
	bool eBid;
	bool sBid;
	bool meldBidding;
	short int dealer;
	short int winner;
	
};
