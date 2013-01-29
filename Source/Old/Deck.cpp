#include "Deck.h"
#include "agk.h"
#include "../template.h"

Deck::Deck(void)
{
	for (short int i = 0; i < 80; i++)
		FullDeck[i] = new Card();
		//currentDeck[i] = i;

	deckLocation = SOUTH;

	deckCounter = 0;
//	handCounter = 0;
}

Deck::~Deck(void)
{
}

void Deck::init(Text ThemeDir, unsigned int state)
{
	for (short int i = 0; i < 80; i++)
	{
        short j;
        
        if (i % 4 == 0)
        {
            FullDeck[i]->init(ThemeDir, i%20/4, i/20);
            j = i;
        }
        else
        {
            FullDeck[i]->setFrontImage(FullDeck[j]->getFrontImage());
            FullDeck[i]->setBackImage(FullDeck[j]->getBackImage());
            FullDeck[i]->setOutlineImage(FullDeck[j]->getOutlineImage());
        }
        
		if (state != LOADING)
		{
			if (FullDeck[i]->getIsOutlined())
				FullDeck[i]->outlineCard();

			if (FullDeck[i]->getFaceDirection()) //true is face down
				FullDeck[i]->turnFaceDown();

			if (FullDeck[i]->isRotatedLeft())
				FullDeck[i]->rotateLeft();
			else if (FullDeck[i]->isRotatedRight())
				FullDeck[i]->rotateRight();

			//FullDeck[i]->setPosition(Point(cardPosX[i], cardPosY[i]);
			FullDeck[i]->hide();
		}
	}
}

void Deck::show(void)
{
	for (short int i = 0; i < 80; i++)
	{
		if ((FullDeck[i]->getX() > 0.0f) && (FullDeck[i]->getX() < 100.0f))
		{
			if ((FullDeck[i]->getY() > 0.0f) && (FullDeck[i]->getY() < 100.0f))
				FullDeck[i]->show();
		}
	}
}

void Deck::hide(void)
{
	for (int i = 0; i < 80; i++)
		FullDeck[i]->hide();
}

bool Deck::updateCardLocs(short int turn, Card *Cards[4], short int round, bool flag)
{//sending 4 at a time to hand
	float destinationX[4] = {-1.0f, -1.0f, -1.0f, -1.0f};
	float destinationY[4] = {-1.0f, -1.0f, -1.0f, -1.0f};
	//short int cardSprites[4] = {card1, card2, card3, card4};
	float moveXperTurn[4] = {10.0f, 10.0f, 10.0f, 10.0f};
	float moveYperTurn[4] = {10.0f, 10.0f, 10.0f, 10.0f};
	float curXLocation[4] = {10.0f, 10.0f, 10.0f, 10.0f};
	float curYLocation[4];
	float offsetN = (round * 4.0f * CARDWIDTHN) + CARDWIDTHN;
	float offsetH = (round * 4.0f * CARDWIDTHH) + CARDWIDTHH;
	float offsetS = (round * 4.0f * CARDWIDTHS) + CARDWIDTHS;
	bool atLocation[4] = {false, false, false, false};

#if (OS != IOS)
	unsigned short randomSound = agk::Random(4, 8);
#else
    unsigned short randomSound = (arc4random() % 5) + 4;
#endif

	Cards[0]->playSound(randomSound);

	if (turn % 2 == 0)
		offsetH = (round * 6.0f * CARDWIDTHH) - (1.5f * CARDWIDTHH);

	switch (turn)
	{
	case WEST:
		destinationX[0] = destinationX[1] = destinationX[2] = destinationX[3] = WEST_LOC_X;
		destinationY[0] = WEST_LOC_Y + offsetH + CARDWIDTHH;
		destinationY[1] = destinationY[0] + (CARDWIDTHH * 1.5f);
		destinationY[2] = destinationY[1] + (CARDWIDTHH * 1.5f);
		destinationY[3] = destinationY[2] + (CARDWIDTHH * 1.5f);
		for(short int i = 0; i < 4; i++)
		{
			Cards[i]->rotateRight();
			Cards[i]->turnFaceDown();
		}
		break;
	case NORTH:
        if (flag)
            offsetN -= 0.5f;
		destinationX[0] = NORTH_LOC_X - offsetN;
		destinationX[1] = destinationX[0] - CARDWIDTHN;
		destinationX[2] = destinationX[1] - CARDWIDTHN;
		destinationX[3] = destinationX[2] - CARDWIDTHN;
		destinationY[0] = destinationY[1] = destinationY[2] = destinationY[3] = NORTH_LOC_Y;
		//y[1] = CENTER_Y -200; //debug
		for (short int i = 0; i < 4; i++)
			Cards[i]->turnFaceDown();
		break;
	case EAST:
		destinationX[0] = destinationX[1] = destinationX[2] = destinationX[3] = EAST_LOC_X;
		destinationY[0] = EAST_LOC_Y - offsetH - CARDWIDTHH;
		destinationY[1] = destinationY[0] - (CARDWIDTHH * 1.5f);
		destinationY[2] = destinationY[1] - (CARDWIDTHH * 1.5f);
		destinationY[3] = destinationY[2] - (CARDWIDTHH * 1.5f);
		for(short int i = 0; i < 4; i++)
		{
			Cards[i]->rotateLeft();
			Cards[i]->turnFaceDown();
		}
		break;
	case SOUTH:
		destinationX[0] = SOUTH_LOC_X - CARDWIDTHS + offsetS; 
		destinationX[1] = destinationX[0] + CARDWIDTHS;
		destinationX[2] = destinationX[1] + CARDWIDTHS;
		destinationX[3] = destinationX[2] + CARDWIDTHS;
		destinationY[0] = destinationY[1] = destinationY[2] = destinationY[3] = SOUTH_LOC_Y;
		for(short int i = 0; i < 4; i++)
			Cards[i]->turnFaceUp();
		//y[1] = CENTER_Y +200;
		break;
	default:
		break;
	}

	for (short int i = 0; i < 4; i++)
	{
		curXLocation[i] = Cards[i]->getX();
		curYLocation[i] = Cards[i]->getY();
	
		if (destinationX[i] < curXLocation[i])
		{//have to go negative to reach destination
			if ((curXLocation[i] - destinationX[i]) / 8.0 > 20.0)
				moveXperTurn[i] = (destinationX[i] - curXLocation[i]) / 8; //normal movement rate, negative
			else if (curXLocation[i] - 20.0 >= destinationX[i])
				moveXperTurn[i] *= -2; //slower movement rate
			else
				moveXperTurn[i] = destinationX[i] - curXLocation[i]; //even out to destination, will be negative
		}
		else
		{ //have to go positive to reach destination
			if ((destinationX[i] - curXLocation[i]) / 8 > 20)
				moveXperTurn[i] = (destinationX[i] - curXLocation[i]) / 8; //nomal movement rate
			else if (curXLocation[i] + 20 <= destinationX[i])  
				moveXperTurn[i] *= 2;
			else
				moveXperTurn[i] = destinationX[i] - curXLocation[i];
		}
		
		if (destinationY[i] < curYLocation[i])
		{
			if ((curYLocation[i] - destinationY[i]) / 8 > 20)
				moveYperTurn[i] = (destinationY[i] - curYLocation[i]) / 8;
			else if (curYLocation[i] - 20 >= destinationY[i])
				moveYperTurn[i] *= -2;
			else
				moveYperTurn[i] = destinationY[i] - curYLocation[i];
		}
		else
		{
			if ((destinationY[i] - curYLocation[i]) / 8 > 20)
				moveYperTurn[i] = (destinationY[i] - curYLocation[i]) / 8;
			else if (curYLocation[i] + 20 <= destinationY[i])
				moveYperTurn[i] *= 2;
			else if (curYLocation[i] + 20 > destinationY[i])  //don't need to check if it's less than or equal to because it's default at 10
				moveYperTurn[i] = destinationY[i] - curYLocation[i];
		}
	
		Point MoveTo;
		MoveTo.init(curXLocation[i] + moveXperTurn[i], curYLocation[i] + moveYperTurn[i]);
		Cards[i]->setPosition(MoveTo);
		//if (turn == EAST)
			//vDec[cardSprites[i]].setPriority((round * 4) - i + 4);
		//else
		Cards[i]->setDepth((round * 4) - i - 2);
		if ((abs(moveXperTurn[i]) <= 0.01f) && (abs(moveYperTurn[i]) <= 0.01f))
			atLocation[i] = true;
		Cards[i]->show();
	}
	
	if (atLocation[0] && atLocation[1] && atLocation[2] & atLocation[3])
		return true;
	else
		return false;
}

void Deck::reset(void)
{
	shuffleDeck();

	deckCounter = 0;
}

/*void Deck::setDeck(char deck[])
{
	for (short int i = 0; i < 80; i++)
		currentDeck[i] = deck[i];
}*/

short int Deck::getDeckCounter(void)
{
	return deckCounter;
}

/*void Deck::setDeckCounter(short int counter)
{
	handCounter = counter;
}*/

void Deck::shuffleDeck(void)
{
	Card *TempCard;
    short rand;

	#if (OS == IOS)
	unsigned int random = (arc4random() % 3) + 1;
#else
	unsigned int random = agk::Random(1, 3);
#endif

	FullDeck[0]->playSound(random);

	for (short int j  = 0; j < 14; j++)
	{
		for(short int i = 79;i > 0; i--)
		{
#if (OS != IOS)
			rand = agk::Random(0, i);
#else
            rand = arc4random() % (i+1);
#endif
				
			//swap
			TempCard = FullDeck[i];
			FullDeck[i] = FullDeck[rand];
			FullDeck[rand] = TempCard;
		}
	}
}

void Deck::sortAllCards(Player *AllPlayers[4], unsigned short round, unsigned short theme)
{
	short int i = 0;
    float offset;
	Card Test;

    if (theme == GREEN)
        offset = 0.5f;
    else
        offset = 0.0f;
	
	while (i != 20-(round+1))
	{
		if (!AllPlayers[WEST]->getCard(i)->getIsRotated())
		{
			AllPlayers[WEST]->getCard(i)->rotateRight();
			AllPlayers[WEST]->getCard(i)->turnFaceDown();
		}

		if (!AllPlayers[EAST]->getCard(i)->getIsRotated())
		{
			AllPlayers[WEST]->getCard(i)->rotateLeft();
			AllPlayers[WEST]->getCard(i)->turnFaceDown();
		}

		if (AllPlayers[SOUTH]->getCard(i)->getIsRotated())
		{
			AllPlayers[SOUTH]->getCard(i)->unRotate();
			AllPlayers[SOUTH]->getCard(i)->turnFaceUp();
		}

		AllPlayers[NORTH]->getCard(i)->turnFaceDown();

		if (i == 0)
		{
			AllPlayers[WEST]->getCard(i)->setPosition(WEST_LOC_X, WEST_LOC_Y + (-0.5f * CARDWIDTHH));
			AllPlayers[NORTH]->getCard(i)->setPosition(NORTH_LOC_X - CARDWIDTHN, NORTH_LOC_Y);
			AllPlayers[EAST]->getCard(i)->setPosition(EAST_LOC_X, EAST_LOC_Y - (-0.5f * CARDWIDTHH));
			AllPlayers[SOUTH]->getCard(i)->setPosition(SOUTH_LOC_X, SOUTH_LOC_Y);
		}
		else
		{
			AllPlayers[WEST]->getCard(i)->setPosition(WEST_LOC_X, WEST_LOC_Y + (((1.5f*i)-0.5f) * CARDWIDTHH));
			AllPlayers[NORTH]->getCard(i)->setPosition(NORTH_LOC_X - ((i+1) * CARDWIDTHN), NORTH_LOC_Y);
			AllPlayers[EAST]->getCard(i)->setPosition(EAST_LOC_X, EAST_LOC_Y - (((1.5f*i)-0.5f) * CARDWIDTHH));
			AllPlayers[SOUTH]->getCard(i)->setPosition(SOUTH_LOC_X + (i * CARDWIDTHS), SOUTH_LOC_Y);
		}
		
		AllPlayers[WEST]->getCard(i)->setDepth(i - 3);
		AllPlayers[NORTH]->getCard(i)->setDepth(i - 3);
		AllPlayers[EAST]->getCard(i)->setDepth(i - 3);
		AllPlayers[SOUTH]->getCard(i)->setDepth(i - 3);

		i++;
	}
	
    if (theme == GREEN)
    {
        for (short j = 0; j < 20; j++)
        {
            float newX = AllPlayers[NORTH]->getCard(j)->getX();
            float curY = AllPlayers[NORTH]->getCard(j)->getY();
            
			AllPlayers[NORTH]->getCard(i)->setPosition(newX + offset, curY);
        }
    }

	FullDeck[0]->playSound(10);
}

//Unshuffled Deck Order goes A, A, A, A, 10, 10, 10, 10, K, K, etc.
/*void Deck::translateCard(short int card, char decodedCard[])
{
	short int test;
	short int suit;
	char tempString[20];
		
	test = (card - 1) / 4 % 5; // 0 = Ace, 1 = 10, 2 = K, 3 = Q, 4 = J
	suit = card / 20;  // 0 = Hearts, 1 = Clubs, 2 = Diamonds, 3 = Spades

	if (card == 99)
	{
		decodedCard = "No Card";
		return;
	}
	else if (test == ACE)
		strcpy(tempString, "Ace of ");
	else if (test == TEN)
		strcpy(tempString, "10 of ");
	else if (test == KING)
		strcpy(tempString, "King of ");
	else if (test == QUEEN)
		strcpy(tempString, "Queen of ");
	else 
		strcpy(tempString, "Jack of ");

	if (suit == HEARTS)
		strcat(tempString, "Hearts");
	else if (suit == CLUBS)
		strcat(tempString, "Clubs");
	else if (suit == DIAMONDS)
		strcat(tempString, "Diamonds");
	else 
		strcat(tempString, "Spades");

	strcpy(decodedCard, tempString);
}*/

Card *Deck::getCard(unsigned short value)
{
	return FullDeck[value];
}

void Deck::deal(Player *AllPlayers[4], unsigned short dealer)
{
	unsigned short turn = (dealer + 1)%4;
	
	for (short int i = 0; i < 80;)
	{
		Card *Dealt[4];

		for (int j = 0; j < 4; j++)
			Dealt[j] = getCard(deckCounter++);

		AllPlayers[turn]->dealToHand(Dealt);
		updateCardLocs(turn, Dealt, i%16);

		turn = (turn + 1)%4;
	}
}

short int Deck::getDeckLocation()
{
	return deckLocation;
}

void Deck::incrementDeckLocation()
{
	deckLocation = (deckLocation + 1) % 4;
}

short int Deck::getSuit(short int card)
{
	return card/20;
}

short int Deck::getRank(short int card)
{
	return card%20/4;
}