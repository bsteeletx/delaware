#pragma once

#include "Buttons.h"
#include "AnimatedSprite.h"
#include "Defines.h"
//#include "ArtHandlers/ParentImage.h"

class MyMenu
{
public:
	MyMenu(void);
	~MyMenu(void);

	void ButtonAnimation(unsigned short button);
	
	virtual void hide(void);
	void hideButton(unsigned short);
	
	virtual void init();
	virtual void initParent(void);

	virtual void setDepth(unsigned short value);
	void showButton(unsigned short button);

	virtual unsigned short update(void);
	
//    ParentImage MenuParent;

protected:
	bool isBase;
	//Sprite Background;
	Sprite ParentImage;
	
	Buttons *AllButtons[4];
};

