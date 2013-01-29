#pragma once

#include "sprite.h"
#include "Numbers.h"
#include "AnimatedSprite.h"
#include "BidGame.h"
#include "Defines.h"
//#include "../ArtHandlers/ParentImage.h"
#include "Sprite.h"

class Bubbles
	: Sprite
{
public:
	Bubbles(void);
	~Bubbles(void);

	float getFirstCardPos(int theme, int player, bool getX);

	void hide(void);

	void init(Text ThemeDir, unsigned short playerID, bool setIsBidBubble, float offsetGraphics);

	void offsetBidNumberBy(float x, float y);
	void offsetBidNumberBy(Point Location);
	void offsetMeldBubbleBy(float x, float y);
	void offsetPassBy(Point Location);
	void offsetPassBy(float x, float y);

	void setDepth(short unsigned int value);
	void setSize(float x, float y = -1.0f);
	void show(short bidValue);
	
	//bool updateBid(short int turn, short int dealer, BidGame NewBidGame, short int theme);

private:
	bool isBidBubble;

	float firstCardPos[NUM_TABLE_TOP][4][2];
    
	Numbers *Bid;
	Sprite *BidPass;
	Sprite *Bubble;
	Sprite *ParentImage;
};

