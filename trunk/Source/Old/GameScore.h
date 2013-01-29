#pragma once

#include "Sprite.h"
#include "Numbers.h"
#include "AnimatedSprite.h"
#include "Defines.h"
//#include "ParentImage.h"

class GameScore
{
public:
	GameScore(void);
	~GameScore(void);

	void addToScore(short int team, short int amount);

	short int getScore(short int team);

	void hide(void);
	
	void init(void);

	void reset(void);

	void setDepth(short unsigned int value);
	void setNumberData(void);
	
private:

    Sprite *ParentImage;
	Sprite *Background;
	Sprite *Header;
	Sprite *MiddleSection[11];
	Sprite *Total;

	Numbers *GameScoreData[12][3];
    
	short int horizontalScore;
	short int verticalScore;

};

