#pragma once

#include "AnimatedSprite.h"
#include "BidControl.h"
#include "Bubbles.h"
#include "Buttons.h"
#include "Numbers.h"
#include "Sprite.h"
#include "TrumpSelect.h"
#include "Defines.h"
//#include "ParentImage.h"
#include "Deck.h"
#include "Image.h"
//#include "Background.h"

class Bubbles;
class Deck;

class Theme
{
public:
	Theme(void);
	~Theme(void);

	bool arePastBidsEqual(unsigned int player);

	bool checkForBidWinner(void);

	void doBids(short turn);

	virtual Point getFirstCardPos(unsigned short player);
	unsigned short getBidValue(void);
	unsigned short getBidWinner(void);
	unsigned short getCurrentTheme(void);
	bool getMeldingComplete(void);
	unsigned short getPastBid(unsigned int player);
	unsigned short getTurn(void);
	void growBackground(void);

	bool hasGrown(void);
	bool hasPlayerBid(unsigned int player);
	bool hasShrunk(void);
	void hide(void);
	void hideAllHScores(void);
	void hideAllVScores(void);
	void hideBidBubble(void);
	void hideMeldBubble(void);
	void hidePastBid(unsigned short player);
	
	virtual void init(AnimatedSprite *Symbol, unsigned short state);
	void init(AnimatedSprite *Symbol, unsigned short theme, unsigned short state);
	virtual void initNumbers(void);
	void initNumbers(Text Dir);
	bool isSetup(void);

	void playGame(void);
	void playerMeldBid(unsigned short newBid);
	void playerTakeBid(Player *South, Player *North, short int round, unsigned short int newBid);

	void resetGame(void);
	void resetHand(void);

	virtual void setNumberData(void);
	virtual void setNumberLoc(void);
	virtual void setNumberPrio(void);
	virtual void setSizeNumbers(void);
	void show(short state);
	void showFinalMeldText(void);
	void showMeld(void);
	void showPastBid(unsigned short player);
	void showBidBubble(unsigned short player, short bid);
	void shrinkBackground(void);
	void sortHands(void);
	bool start(unsigned short dealer);

	void update(unsigned short state);
	void updateBottomLeft(void);
	void updateMeldProcess(void);
	void updateScore(void);
    void updateTopLeft(void);
    void updateTopRight(void);

protected:
	unsigned short bidRound;

	unsigned short currentTheme;
	
	unsigned short dealer;

	unsigned short language;

	unsigned short meldCount;
	bool meldingComplete;

    //bool themeReady;
	//bool themeHasGrown;
	//bool themeHasShrunk;

	unsigned short turn;

	BidControl *BCBubble;
	Buttons *InGameMenuButton;

	Deck *AllCards;

	Numbers *Bid;
	Numbers *BidScore;
	Numbers *H2Get;
	Numbers *HMeld;
	Numbers *HScore;
	Numbers *PastBids[4];
	Numbers *V2Get;
	Numbers *VMeld;
	Numbers *VScore;

	Player *AllPlayers[4];

	Sprite *Background;
	Sprite *TextBackground;

	Text *MeldFail;
	TrumpSelect *TSBubble;
};