#pragma once
#include "sprite.h"
#include "Sound.h"
#include "AnimatedSprite.h"
#include "../Defines.h"
//#include "../ArtHandlers/ParentImage.h"

#define UP 0
#define DOWN 1
#define OVER 2
#define GRAY 3

class Buttons
{
public:
	Buttons(void);
	//Buttons(Text *FileLocation);
	~Buttons(void);

	bool animation(short int stage);
	
	void display(float x, float y);
	
	Text getFileExtension(short int buttonType);
	
	void hide(unsigned short button = 0);
	
	void init(File FileToInit);
	void init(unsigned int parentImageNumber, Text ButtonBaseName);
	bool isVisible();
	
	void setData(const char newFilename[], const char newDir[]);
	void setDepth(unsigned int depth);
	void setPosition(float x, float y);
	void setSize(float x, float y = -1.0f);	
	void setSound(bool playSound);	
	void show(unsigned short button = 4);

private:
    
	static Sound *ButtonClick;
    bool soundPlaying;
    
	Sprite *AllButtons[4];

};