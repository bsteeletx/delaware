#pragma once

#include "Sprite.h"
#include "Buttons.h"
#include "Numbers.h"
#include "AnimatedSprite.h"
#include "../Defines.h"
//#include "ParentImage.h"

class BidControl
{
public:
	BidControl();
	~BidControl(void);

	bool animation(short int menuChoice, short int stage);
	
	void display(float x, float y);	
	
	void hide(void);
	
	void init(Text FilePath, float bidValueSize);
	bool isVisible(void);

	void setDepth(unsigned short value);
	void setSize(float x, float y = -1.0f);	
	void show(void);	
	
private:
    Sprite *Frame;

	Buttons *Bid; //1
	Buttons *Minus; //2
	Buttons *Pass; //3
	Buttons *Plus; //4

	Numbers *BidValue;
    
	Sprite *Parent;
    
};