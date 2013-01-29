#pragma once

#include "BidGame.h"
#include "TrickGame.h"
#include "Player.h"
#include "Defines.h"
//#include "ParentImage.h"
#include "Text.h"
#include "Deck.h"
#include "Sound.h"

class Card
{
public:
	Card(short unsigned int frontImageNumber, short unsigned int backImageNumber);
	Card();
	~Card(void);

    bool compareBackImageTo(unsigned int image);

	unsigned int getBackImage(void);
	bool getFaceDirection(void);
	unsigned int getFrontImage(void);
	bool getIsOutlined(void);
	bool getIsRotated();
	Point getLocation();
	unsigned int getOutlineImage(void);
	short int getRank(void);
	Text getRank(short int rankNum);
	float getRotationAmount(void);
	short int getStyle(void);
	short int getSuit(void);
	Text getSuit(short int suitNum);
	unsigned short getValue(void);
	float getX(void);
	float getY(void);

	void hide(void);

	void init(Text FilePath, short int rankNum, short int suitNum);
	bool isRotatedLeft(void);
	bool isRotatedRight(void);
	
	void offset(float x, float y);
	void outlineCard(void);

	void playSound(unsigned int sound);
	
	void raiseHeight(void);
	void resetHeight(void);
	void revealAllCardsFrom(Player *Selected);
	void rotate(float amount, bool additive = true);
	void rotateLeft();
	void rotateRight();
	
    void setBackImage(unsigned int backImage, short place);
    void setBackImage(unsigned int backImage);
	void setData(char filename[], short int rankNum, short int suitNum);
	void setDepth(unsigned short int value);
    void setFrontImage(unsigned int frontImage);
    void setOutlineImage(unsigned int outlineImage);
	void setPosition(Point Location);
	void setPosition(float x, float y);
	void setSize(float value);
	void setStyle(int newStyle);
	void show(void);
	
	void turnFaceDown();
	void turnFaceUp();
	
	void unOutlineCard(void);
	void unRotate();
	bool updateCardLoc(short int turn);
	Card *updateCardPos(Player *South, short int topSuit, short int topRank, short int leadSuit, short int trump, short int firstPlay);
	
private:
	Sound *Cards[10];
	Sound *Trump[5];
	Sprite *Front;
	Sprite *Back;
	Sprite *Outlined;
    static Sprite *ParentImage;

	bool isRotated;
	bool rotatedLeft;
	bool rotatedRight;
	bool isTrump;
	bool isFaceDown;
	bool multipleBack;
	float rotateAmount;
	short int suit;
	short int rank;
	unsigned short cardValue;
    static unsigned int cardBackImageNumber[3];
};

