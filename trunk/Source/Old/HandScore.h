#pragma once

#include "Sprite.h"
#include "Numbers.h"
#include "AnimatedSprite.h"
#include "Defines.h"
#include "Player.h"
//#include "ArtHandlers/ParentImage.h"

class HandScore
{
public:
	HandScore(void);
	~HandScore(void);

	void addToHandScore(unsigned short team, short amount);
	short getHandScore(unsigned short team, short amount);

	void checkBox(bool horizontal, bool vertical);
	void checkForSaves(unsigned short hTricks, unsigned short vTricks, short int bidWinnerID, unsigned short int finalBid);

	void determineAmountToGet(Player *AllPlayers[4], short int trump, short int bidWinner, unsigned short int bid);
	unsigned short int getAmountToSave(short int team);

	void hide(void);

	void init(AnimatedSprite *Symbol);	

	void reset(void);

	void setDepth(short unsigned int value);
	void setNumberData(void);

	void update(unsigned short bidValue, bool meldFail, unsigned short bidWinner);

private:

	Sprite ParentImage;
	Sprite *Background;
	Sprite *HCheckOff;
	Sprite *HCheckOn;
	Sprite *VCheckOff;
	Sprite *VCheckOn;
	Numbers *HandScoreData[2][4];    

    unsigned short horizontalMeld;
	unsigned short verticalMeld;
	short vAmountToGet;
	short hAmountToGet;
	short hHandScore;
	short vHandScore;

	bool calcOnce;
};

