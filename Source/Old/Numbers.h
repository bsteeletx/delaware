#pragma once
#include "Sprite.h"
#include "Text.h"
#include "../Defines.h"
//#include "../ArtHandlers/ParentImage.h"

class Numbers
{
public:
	//Sound(char filename[]);
	Numbers();
	~Numbers(void);

	//void changeImage(short int theme);

    void decrementValue(void);
	void display(short int digit, short int number);
	void display(short int digit, short int number, float x, float y);

	short int getDigit(short int digit);
	bool getPositive(void);
	//int getSeparatedValue(void);
	short int getValue(void);
	bool getVisible(void);
	float getX(short int digit);
	float getY(short int digit);

	void hide(short int digit, short int number);
	void hideAll(void);

	void incrementTo(short int targetValue, bool alwaysDisplay = false);
    void incrementValue(void);
	void init(unsigned short theme);
	void init(Text ThemeDir);
    void initDefaultNumbers(void);
    void initThematicNumbers(Text Directory);
	bool isVisible(void);

    void makeNegative(void);
    void makePositive(void);

	//bool scroll(char value, char digit);
	void setColor(unsigned short int red, unsigned short int green, unsigned short int blue, unsigned short int alpha);
	//void setData(Text ThemeFilePath, bool useParentheses=false);
	//void setDigit(short int digit, float x, float y);
	void setDigit(short int digit, short int number);
	//void setDigitData(short int digit, char desc[]);
	void setLocation(short int digit, float x, float y, float negOffsetX=0, float negOffsetY=0);
	void setLocationAll(Point *Location, Point *NegOffset = NULL);
	void setDepth(short unsigned int depthValue);
	void setSize(float x, float y = -1.0f);
	void setValue(short int newValue);
	void show(short int digit, short int number);
	void showAll(bool always=false);

	void useParentheses(void);
   
	
private:

	void updateValue(int newValue);
    
	Sprite *DigitOne[10]; //ones
	Sprite *DigitTwo[10]; //tens
	Sprite *DigitThree[10]; //hundreds
	Sprite *Parentheses[2];

	Text *MinusSign;

	static Sprite Parent;
    static Sprite DefaultParent;

	short int visDigit1;
	short int visDigit2;
	short int visDigit3;
	short int value;
	unsigned short int colorValue[4];
	bool isPositive;
	bool useMinus;
};