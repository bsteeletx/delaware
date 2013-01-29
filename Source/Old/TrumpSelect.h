#pragma once

#include "Buttons.h"
#include "Sprite.h"
#include "AnimatedSprite.h"
#include "../Defines.h"
//#include "ParentImage.h"

class TrumpSelect
{
public:
	TrumpSelect(void);
	~TrumpSelect(void);

	bool animation(short int button, short int stage);

	void display(float x, float y);

	void hide(void);
	
	void init(Text FilePath);
	
	void setPriority(unsigned short int value);
	void setSize(float x, float y = -1.0f);
	void show(void);

private:
	char currentDir[32];
    
    Sprite *ParentImage;

	Buttons *Hearts; //1
	Buttons *Clubs; //2
	Buttons *Diamonds; //3
	Buttons *Spades; //4

	Sprite *Frame;
};

