#pragma once

#include "PinochleGame.h"
#include "BidGame.h"
#include "TrickGame.h"
#include "Player.h"
#include "Pinochle.h"
#include "ParentImage.h"

class Card
{
public:
	Card(short unsigned int frontImageNumber, short unsigned int backImageNumber);
	Card();
	~Card(void);

    bool compareBackImageTo(unsigned int image);
    unsigned int getBackImage(void);
	bool getIsRotated();
	void getRank(char buffer[], short int rankNum);
	void getSuit(char buffer[], short int suitNum);
	short int getRank(void);
	short int getSuit(void);
	short int getStyle(void);
	bool getOutline(void);
    unsigned int getOutlineImage(void);
	bool getFaceDirection(void);
    unsigned int getFrontImage(void);
	bool isRotatedLeft(void);
	bool isRotatedRight(void);
	void outlineCard(void);
	void raiseHeight(void);
	void resetHeight(void);
	void revealCard(Player);
	void rotate(float amount);
	void rotateLeft();
	void rotateRight();
	float getRotationAmount(void);
    void setBackImage(unsigned int backImage, short place);
    void setBackImage(unsigned int backImage);
    void setFrontImage(unsigned int frontImage);
    void setOutlineImage(unsigned int outlineImage);
	void setSize(float value);
	void setData(char filename[], short int rankNum, short int suitNum);
	void setStyle(int newStyle);
	void sortVisualCards(Player West, Player North, Player East, Player South, Card *vDeck, short int round, short theme);
	void sortVisualCards(Player, Card *, short theme);
	void turnFaceDown();
	void turnFaceUp();
	void unOutlineCard(void);
	void unRotate();
	bool updateCardLocs(short int turn, Card *vDec, short int card1, short int card2, short int card3, short int card4, short int round, bool flag=false);
	bool updateCardLoc(short int turn, PinochleGame PGame, BidGame BGame, TrickGame TGame, short int count, bool flag);
	bool updateCardThrowIn(Player Selected, Card *Deck);
	short int updateCardPos(Card *vdeck, Player South, short int topSuit, short int topRank, short int leadSuit, short int trump, short int firstPlay);
	bool updateShrinkCloseTrick(short int location, Card *Card2, Card *Card3, Card *Card4);
	void display(float x, float y);
	void show(void);
	void hide(void);
	void offset(float x, float y);
	float getX(void);
	float getY(void);
	void setPriority(unsigned short int value);


private:
	Sprite Front;
	Sprite Back;
	Sprite Outlined;
    static ParentImage Parent;

	bool isRotated;
	bool rotatedLeft;
	bool rotatedRight;
	bool isTrump;
	bool isFaceDown;
	bool multipleBack;
	float rotateAmount;
	short int suit;
	short int rank;
    static unsigned int cardBackImageNumber[3];
};
