#pragma once

#include "Defines.h"
#include "Card.h"
#include "Text.h"
#include "Player.h"

class Card;
class Player;

class Deck
{
public:
	Deck(void);
	~Deck(void);

	void deal(Player *AllPlayers[4], unsigned short dealer);

	Card *getCard(unsigned short value);
	short int getDeckLocation();
	short int getDeckCounter();
	short int getRank(short int card);
	short int getSuit(short int card);
	void getTopFourCardsFromDeck(char[]);

	void hide(void);

	void incrementDeckLocation();
	void init(Text ThemeDir, unsigned int state);

	void reset(void);

	//void setDeck(char deck[]);
	void setDeckCounter(short int counter);
	void show(void);
	void shuffleDeck(void);
	void sortAllCards(Player *AllPlayers[4], unsigned short round, unsigned short theme);

	//void translateCard(short int card, char decodedCard[]);

	bool updateCardLocs(short int turn, Card *Cards[4], short int round, bool flag=false);

	
private:
	void shuffleDeck(bool randType);
	//short int currentDeck[80];
	unsigned short deckLocation;
	short int deckCounter;
	//short int handCounter;

	Card *FullDeck[80];
};
