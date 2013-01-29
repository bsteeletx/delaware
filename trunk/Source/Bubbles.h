#pragma once

#include "sprite.h"
#include "Numbers.h"
#include "AnimatedSprite.h"
#include "BidGame.h"
#include "Pinochle.h"
#include "ParentImage.h"

class Bubbles
{
public:
	Bubbles(void);
	~Bubbles(void);

	float getFirstCardPos(int theme, int player, bool getX);
	void show(short int meldBubble);
	void setBidSize(float x, float y = -1.0f);
	void hide(void);
	void setPriority(short unsigned int value);
	void setup(AnimatedSprite *Symbol, const char fullname[], const char dir[]);
	bool updateBid(short int turn, short int dealer, BidGame NewBidGame, short int theme);

	Numbers Bid;

	Sprite BidPass[4];
	Sprite EastBid;
	Sprite EastMeld;
	Sprite NorthBid;
	Sprite NorthMeld;
	Sprite SouthBid;
	Sprite SouthMeld;
	Sprite WestBid;
	Sprite WestMeld;

private:
	char currentDir[64];
	float firstCardPos[NUM_TABLE_TOP][4][2];

    ParentImage Parent;
};
