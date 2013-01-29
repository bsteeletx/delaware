#pragma once

class Sprite
{
public:
	Sprite();
	~Sprite(void);
	Sprite& operator= (const Sprite &newSprite);

	void changeColor(unsigned short int red, unsigned short int blue, unsigned short int green, unsigned short int alpha=255);
	void changeImage(unsigned short int imageNum);
	void changeImage(char filename[], char filepath[]);
	void display();
	void display(float x, float y);
	short unsigned getImageNumber();
	float getImprintX(void);
	float getImprintY(void);
	float getScaleSize(void);
	float getScaleSizeY(void);
	float getSizeY(void);
	short unsigned int getSpriteNumber();
	float getX();
	float getY();
	bool hasGrown();
	bool hasShrunk();
	void hide();
	bool isGrowing();
	bool isMoving(void);
	bool isShrinking();
	bool isValid();
	bool isVisible();
	void moveOffScreen(short direction);
	void moveOnScreen(short direction);
	void moveSprite(float x, float y);
	void offset(float, float);
    void flipSprite(void);
    void setImageNumber(unsigned int imageNum);
	void setSize(float x, float y, bool init = true);
	void setSize(float x, bool init = true);
	void setData(const char filename[], const char filepath[]);
	void setData(unsigned short int image, const char name[]);
    //void setData(const char name[]);
	//void setData(unsigned short int spriteID, unsigned short int spritePriority, float x, float y);
    void setData(unsigned short parentImages[], const char name[]);
	void setImprint(float x, float y);
	void setPriority(unsigned short int newPriority);
	void setTransparency(unsigned short int spriteNumber, int mode);
	void setAlpha(unsigned short int alpha);
	void show();
	void updateGrowOpen(float xamount, float yamount=-1);
	void updateShrinkClose(short int location);

#if (OS == ANDROID)
	static bool inAnimation;
#else
	bool inAnimation;
#endif


protected:

	short unsigned int imageNumber;
	short unsigned int spriteNumber;
	short unsigned int priority;
	float xScaleSize;
	float yScaleSize;
	float curScaleX;
	float curScaleY;
	bool grown;
	bool growing;
	bool shrunk;
	bool shrinking;
	float xImprint;
	float yImprint;
	bool moving;
};
