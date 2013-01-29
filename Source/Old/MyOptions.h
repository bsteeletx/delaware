#pragma once

#include "MyMenu.h"
#include "Sprite.h"
#include "AnimatedSprite.h"
//#include "Checkbox.h"
#include "Defines.h"
#include "Buttons.h"

const short int MAX_THEMES = 8;

class MyOptions :
	public MyMenu
{
public:
	MyOptions(void);
	~MyOptions(void);

	void arrowAnimation(unsigned short button);

	float getBackgroundHeight(void);
	float getBackgroundWidth(void);
	unsigned short getTheme(void);
	void growBackground(void);

	void hide(void) override;

	void init(void) override;
	void initParent(void) override;
	bool isBackgroundGrowing(void);
	bool isBackgroundShrinking(void);
	bool isSoundMuted(void);
	bool isThemeMoving(void);
	
	void moveTheme(bool moveToRight);
	void mute(void);

	void setDepth(short unsigned int value) override;
	void show(short int curStyle);
	void shrinkBackground(void);
	void start(void);
	
	void unMute(void);
	unsigned short update(void) override;

private:
	bool hasStarted;
	bool isMuted;
	float mouseX;
	float mouseY;
	bool potSwipe;
	unsigned short selectedTheme;
	bool swipeLeft;
	bool swipeRight;

	Sprite ParentImage;
	Sprite Background;
	Sprite ThemeOption[MAX_THEMES];
	Sprite SoundCheckOn;
	Sprite SoundCheckOff;
	Buttons Left;
	Buttons Right;
};

