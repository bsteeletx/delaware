#pragma once
#include "Sprite.h"
//#include "File.h"

class AnimatedSprite :
	public Sprite
{
public:
	~AnimatedSprite(void);
	AnimatedSprite(void);
	
	void addFrame(Image NewFrame);
	
	unsigned int getCurrentFrame(void);
	unsigned int getFrameCount(void);
	float getPlaySpeed(void);
	//bool getVisible(void);

	void incrementFrame(void);
	void init(unsigned int width, unsigned int height, unsigned int count, unsigned int parentImage, Text SubImageFilename, unsigned int assignedSpriteNumber = 0, unsigned int assignedImageNumber = 0);
	void init(unsigned int width, unsigned int height, unsigned int count, unsigned int parentImage, const char subImageFilename[], unsigned int assignedSpriteNumber = 0, unsigned int assignedImageNumber = 0);
	void init(File FileToInit);

	void play(float fps = 10.0f, bool loop = true, unsigned int start = 1, unsigned int end = 0);
	
	void resume(void);

	void setFrame(unsigned int frame);
	void setPosition(Point Location);
	void setSpeed(float fps);
	//void setVisibile(bool value);
	void stopSprite(void);

private:
	
	void set(unsigned int width, unsigned int height, unsigned int count);
	bool _Frame(unsigned int frame);
	bool _FPS(float fps);

	unsigned short frameHeight;
	unsigned short frameWidth;
	unsigned short frameCount;

	float originalY;
	float playSpeed;
};

