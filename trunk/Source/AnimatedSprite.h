#pragma once
#include "sprite.h"
#include "Pinochle.h"

class AnimatedSprite :
	public Sprite
{
public:
	AnimatedSprite(unsigned short int imageNumber, unsigned short int across, unsigned short int down, unsigned short int total);
	AnimatedSprite();
	~AnimatedSprite(void);

	void displayBidNumbers(Sprite *Values, unsigned short int bidValue, bool pass);
	void displayTrump();
	bool isPlaying(void);
	unsigned short int getSpriteFrame(void);
	void hide(void);
	void incrementSpriteFrame(void);
	bool isVisible(void);
	//void makeAnimated(int across, int down, int total);
	void pauseAnimation(void);
	void playAnimation(float speed);
	void playAnimationFrames(float speed, bool loop, unsigned short int start, unsigned short int stop);
	void playAnimationOnce(float speed);
	void playAnimationLooped(float speed, bool loop);
	void setAnimatedData(unsigned short int across, unsigned short int down, unsigned short int total, const char filename[]);
    void setAnimatedData(unsigned short int across, unsigned short int down, unsigned short int total, const char filename[], unsigned short imageNum[]);
	void setAnimatedFrameTo(unsigned short int frame);
	//void setupTrumpAnimation(int, int trumpSymb);
	//void setupTrumpAnimation(AnimatedSprite *Symbol);
	void show(void);
private:
	unsigned short int spriteFrame;
	unsigned short int totalFrames;
	float spriteX;
	float spriteY;

	bool inAnimation;
};
