#include "TrickGame.h"

TrickGame::TrickGame(void)
{
	trump = -1;
	lead = -1;
	trickCounter = 0;
	trickValue = 0;
	horizontalTricks = 0;
	verticalTricks = 0;
	tricksPlayed = 0;

	for (short int i = 0; i < 4; i++)
		for (short int j = 0; j < 5; j++)
			playedCards[j][i] = 0;
}

TrickGame::~TrickGame(void)
{
}

void TrickGame::reset()
{
	trump = -1;
	lead = -1;
	trickCounter = 0;
	trickValue = 0;
	horizontalTricks = 0;
	verticalTricks = 0;
	tricksPlayed = 0;

	for (short int i = 0; i < 4; i++)
		for (short int j = 0; j < 5; j++)
			playedCards[j][i] = 0;
}

void TrickGame::setLead(short int turn)
{
	lead = turn;
	bidWinner = turn;
}

short int TrickGame::getTrumpSuit()
{
	return trump;
}

void TrickGame::setTrumpSuit(short int suit)
{
	trump = suit;
}

short int TrickGame::getLead()
{
	return lead;
}

short int TrickGame::getTrickCounter()
{
	return trickCounter;
}

void TrickGame::setLeadSuit(short int suit)
{
	leadSuit = suit;
}

short int TrickGame::getLeadSuit()
{
	return leadSuit;
}

short int TrickGame::getNumOfCardsLeft(short int rank, short int suit)
{
	if (rank != -1)
		return 4 - playedCards[rank][suit];
	else
	{
		short int count = 0;

		for (short int i = 0; i < 5; i++)
		{
			count += 4 - playedCards[i][suit];
		}

		return count;
	}
}

void TrickGame::updateTrump(short int trumpPlayed)
{
	trumpLeft -= trumpPlayed;
}

short int TrickGame::getTopRank()
{
	return topRank;
}

short int TrickGame::getTopSuit()
{
	return topSuit;
}

void TrickGame::setTopRank(short int rank)
{
	topRank = rank;
}

void TrickGame::setTopSuit(short int suit)
{
	topSuit = suit;
}

short int TrickGame::getTricksPlayed()
{
	return tricksPlayed;
}

void TrickGame::playedCard(Card *PlayedCard, Player *Selected)
{
	short int rank = PlayedCard->getRank();
	short int suit = PlayedCard->getSuit();

	if (trickCounter == 0)
	{
		leadSuit = suit;
		topSuit = suit;
		topRank = rank;
		lead = Selected->getID();
	}

	if (suit == topSuit)
	{
		if (rank < topRank)
		{//Aces are lower than Jacks  
			topRank = rank;
			lead = Selected->getID();
		}
	}
	else if (suit == trump)
	{
		if (topSuit != trump)
		{
			topSuit = suit;
			topRank = rank;
			lead = Selected->getID();
		}
		else if (rank < topRank)
		{
			lead = Selected->getID();
			topRank = rank;
		}
	}

	playedCards[rank][suit]++;
	
	if (rank <= KING)
		trickValue++;

	trickCounter++;
	
	
	if (trickCounter == 4)
		tallyTrick();
}

void TrickGame::tallyTrick()
{
	if (getLead() % 2 == 0)
		horizontalTricks += trickValue;
	else
		verticalTricks += trickValue;

	trickValue = 0;
	trickCounter = 0;
	tricksPlayed++;
}

short int TrickGame::getHTricks()
{
	return horizontalTricks;
}

short int TrickGame::getVTricks()
{
	return verticalTricks;
}

void TrickGame::lastTrick(short int player)
{
	if (player % 2 == BLUE)
		horizontalTricks += 2;
	else
		verticalTricks += 2;
}

Card *TrickGame::followLead(Player *Selected, short int rank, short int suit, bool lTrump, bool pTrump, short int count) //unless can take lead, just follow simple rules
{
	short int currentValue = 0;
	Card *CardInHand;
	short int bestValue = -999;
	Card *BestCard;
	bool takeTrick = false;
	bool noSuit = false;
	bool noTrump = false;
	short int suitA = -1;
	short int suitB = -1;
	short int suitC = -1;
	bool flagA = false;
	bool flagB = false;
	bool flagC = false;
	bool allTrue = false;
	short int newSuitA = -1;
	short int newSuitB = -1;
	short int newSuitC = -1;
	short int numFlags = 0;
	bool lastToPlay = false;
	//bool isTrumping = false;

	if (count % 4 == 3)
		lastToPlay = true;

	if (getTricksPlayed() == 19) //one card left, just play it
		return 0;

	if (Selected->getNumOfCardsInRange(-1, leadSuit) == 0)
		noSuit = true;
	if (Selected->getNumOfCardsInRange(-1, trump) == 0)
		noTrump = true;

	if (noSuit)
	{
		if(noTrump)
		{

			for (short int i = 0; i < 4; i++)
			{
				Selected->trumpingSuit[i] = false;

				if ((i == leadSuit) || (i == trump))
				{
					if (i != 3)
						continue;
				}

				if (suitA == -1)
				{
					suitA = 0;
					if (((lead % 2) == (Selected->getID() % 2)) || allTrue)
					{
						suitA += Selected->getNumOfCardsInRange(KING, i);
						suitA += Selected->getNumOfCardsInRange(TEN, i);
						if (allTrue)
							suitA += Selected->getNumOfCardsInRange(ACE, i);
						if (suitA < 1)
							flagA = true;
					}
					if ((suitA < 1) || ((lead % 2) != (Selected->getID() % 2)))
					{
						suitA += Selected->getNumOfCardsInRange(JACK, i);
						suitA += Selected->getNumOfCardsInRange(QUEEN, i);
						if ((suitA < 1) && ((lead % 2) != (Selected->getID() % 2)))
							flagA = true;
						else if (suitA > 0)
							flagA = false;
					}
					newSuitA = i;
					if (flagA)
						numFlags++;
				}
				else if (suitB == -1)
				{
					suitB = 0;
					if ((lead % 2) == (Selected->getID() % 2) || allTrue)
					{
						suitB += Selected->getNumOfCardsInRange(KING, i);
						suitB += Selected->getNumOfCardsInRange(TEN, i);
						if (allTrue)
							suitB += Selected->getNumOfCardsInRange(ACE, i);
						if (suitB < 1)
							flagB = true;
					}
					if ((suitB < 1) || ((lead % 2) != (Selected->getID() % 2))) 
					{
						suitB += Selected->getNumOfCardsInRange(JACK, i);
						suitB += Selected->getNumOfCardsInRange(QUEEN, i);
						if ((suitB < 1) && ((lead % 2) != (Selected->getID() % 2)))
							flagB = true;
						else if (suitB > 0)
							flagB = false;
					}
					newSuitB = i;
					if (flagB)
						numFlags++;
				}
				else if (suitC == -1)
				{
					suitC = 0;
					if ((lead % 2) == (Selected->getID() % 2) || allTrue)
					{
						suitC += Selected->getNumOfCardsInRange(KING, i);
						suitC += Selected->getNumOfCardsInRange(TEN, i);
						if (allTrue)
							suitC += Selected->getNumOfCardsInRange(ACE, i);
						if (suitC < 1)
							flagC = true;
					}
					if((suitC < 1) || ((lead % 2) != (Selected->getID() % 2))) 
					{
						suitC += Selected->getNumOfCardsInRange(JACK, i);
						suitC += Selected->getNumOfCardsInRange(QUEEN, i);
						if ((suitC < 1) && ((lead % 2) != (Selected->getID() % 2)))
							flagC = true;
						else if (suitC > 0)
							flagC = false;
					}
					newSuitC = i;
					if (flagC)
						numFlags++;
				}
				if ((suitA <= 0) && (suitB <= 0) && (i == 3))
				{
					if (((numFlags == 3) && flagA && flagB && flagC) || ((numFlags == 2) && flagA && flagB))
					{
						if ((suitC <= 0) && (flagC || (leadSuit != trump)))
						{
							allTrue = true;
							flagA = false;
							flagB = false;
							flagC = false;
							suitA = -1;
							suitB = -1;
							suitC = -1;
							i = -1;
							numFlags = 0;
						}
					}
				}
			}

			if (flagA || flagB || flagC)
			{//if any of these are true
				if (!(flagA && flagB && flagC) && (leadSuit != trump))
				{//if not ALL are true
					if (flagA)
						suitA = -1;
					if (flagB)
						suitB = -1;
					if (flagC)
						suitC = -1;
				}
			}

			if (suitB >= suitA)
			{
				if (suitC > suitB)
					suit = newSuitC;
				else
					suit = newSuitB;
			}
			else
			{
				if (suitC >= suitA)
					suit = newSuitC;
				else
					suit = newSuitA;
			}
			rank = ACE;
		}
		else //has trump
		{
			if (leadSuit != trump) //trumping
			{
				suit = trump;
				if (topSuit == leadSuit)
					rank = JACK;
				else
				{
					rank = topRank - 1;
					if (rank < ACE)
						rank = JACK;
				}

				for (short int i = rank; i >= ACE; i--)
				{
					if (Selected->getNumOfCardsInRange(i, trump))
					{
						return Selected->getCardFromPlayerHand(i, trump);
					}
				}

				for (short int i = JACK; i >= ACE; i--)
				{
					if (Selected->getNumOfCardsInRange(i, trump))
					{
						return Selected->getCardFromPlayerHand(i, trump);
					}
				}

			}
		}
	}
	//not trumping
	for (short int j = 0; j < 20; j++)
	{	
		currentValue = 0;
		CardInHand = Selected->getCard(j);

		if (CardInHand == NULL)
			break;
		
		if (CardInHand->getSuit() != suit) //if it's not the correct suit
		{
			if (CardInHand->getSuit() > suit)  //if this suit is greater, we've already passed the suit, try again (later)
				break;
			else  //keep looking
				continue;
		}

		if (rank != ACE)  //if the lead is not an ACE, you HAVE to beat it
		{
			if (CardInHand->getRank() >= rank)
				break;
		}
		//at this poiont, either the lead was a card that cannot be beaten, or the current card beats the previous one
		
		currentValue = cardValues[CardInHand->getRank()][CardInHand->getSuit()];

		if (suit == trump) 
		{
			if ((CardInHand->getRank() == ACE) && ((Selected->getNumOfCardsInRange(ACE, -1) - (Selected->getNumOfCardsInRange(ACE, trump)) < 2))) //let it pass
			{ //not enough aces to jump on the ace of trump
				if (Selected->getNumOfCardsInRange(-1, trump) - Selected->getNumOfCardsInRange(ACE, trump) > 1) //unless low on trump
					currentValue -= 12;
				if (Selected->getID() % 2 == bidWinner % 2) //if partner is bidWinner, then jump on it
				{
					if (Selected->getID() != bidWinner)
						currentValue += 12;
				}
			}
		}
		
		if ((rank == ACE) || (rank == JACK + 1))  //jack + 1 means that the player cannot beat the current lead
		{
			if (CardInHand->getRank() <= KING)
			{//are you giving the leader a point? or is your partner trumping?  (And the person to your left not trumping
				if (lead % 2 == Selected->getID() % 2)
					currentValue += 4;
				else if ((count % 4 == 1) && pTrump)
					currentValue += 2;
				else
					currentValue -= 2;
				
				if (lTrump && !lastToPlay)
					currentValue -= 2;



				if ((rank == ACE) && (CardInHand->getRank() == ACE))
				{
					if ((suit != trump) && (topSuit != trump))
					{
						if ((lead % 2 == Selected->getID() % 2) && (Selected->getNumOfCardsInRange(ACE, suit) == getNumOfCardsLeft(ACE, suit)))
						{
							if (Selected->getNumOfCardsInRange(ACE, suit) > 1)
							{
								if (Selected->getNumOfCardsInRange(TEN, suit))//ACE ON AN ACE!!
								{
									if (topRank == ACE)
										currentValue += 6;
								}
								else
									currentValue -= 6;
							}
							else
								currentValue -= 6;
						}
						else
							currentValue -= 6;
					}
					else
						currentValue -= 12;
				}
			}
			else
			{
				if (lead % 2 != Selected->getID() % 2)
					currentValue += 2;
				else
					currentValue -= 2;
			}
		}
		else if (CardInHand->getRank() < rank)
		{//beating the current lead
			if (!lTrump && !pTrump)
			{
				if (CardInHand->getRank() != ACE)
				{
					if (!lastToPlay)
					{
						for (short int k = CardInHand->getRank() - 1; k >= ACE; k--)
						{//check to see if what you currently are playing cannot be beaten
							if (getNumOfCardsLeft(k, suit))
								takeTrick = false;
							else
							{
								takeTrick = true;   //there is a case where you KNOW no one left can beat you
								break;
							}
						}
					}
					else
						takeTrick = true;
				}
				else
					takeTrick = true;
			}
		}
	
		if (takeTrick)
		{
			if (lastToPlay)
			{
				if (rank == QUEEN)
					currentValue += 28;
				else if (rank == KING)
					currentValue += 12;
				else if (rank == TEN)
					currentValue += 4;
			}
			
			currentValue = currentValue + 4;
		}
		
		if (currentValue >= bestValue)
		{
			bestValue = currentValue;
			BestCard = CardInHand;
		}

	}

	if (bestValue == -999)
		return (followLead(Selected, JACK+1, topSuit, lTrump, pTrump, count));
	else
		return BestCard;

}

Card *TrickGame::playCard(Player *All[4], unsigned short count, unsigned short turn, Card *LeadCard)
{	
	//short int cardPlayed;
	short int suit;
	short int rank;
	Card *PlayedCard;
	bool notOut = false;
	bool aceOnAce = false;

	if (LeadCard == NULL)
	{

		if (getTrickCounter() == 0)
		{
			PlayedCard = startTrick(All, turn);

			//PlayedCard = Selected->getCard(cardInHand);
			All[turn]->removeCardFromHand(PlayedCard);
			rank = PlayedCard->getRank();
			suit = PlayedCard->getSuit();
		}
		else
		{
			suit = leadSuit;
		
			if (suit != topSuit)
				rank = ACE;
			else
				rank = topRank;
		
			PlayedCard = followLead(All[turn], rank, suit, All[All[turn]->getLeftID()]->trumpingSuit[suit], All[All[turn]->getPartnerID()]->trumpingSuit[suit], count);  
			//cardNumber = Selected->getCard(cardPlayed);
			All[turn]->removeCardFromHand(PlayedCard);
			rank = PlayedCard->getRank();
			suit = PlayedCard->getSuit();
		}
	}
	else
	{
		rank = LeadCard->getRank();
		suit = LeadCard->getSuit();
		//cardInHand = Selected->getCardFromPlayerHand(cardNumber);
		All[turn]->removeCardFromHand(LeadCard);
		PlayedCard = LeadCard;
	}
	
	if ((All[turn]->getID() != lead) && (topRank == ACE) && (suit == topSuit)) //Lead was an ACE
	{
		if ((lead % 2) == (All[turn]->getID() % 2)) //partner
		{
			if (rank == TEN)
				All[turn]->known[KING][suit] = 0;
			else if (rank == QUEEN)
			{
				All[turn]->known[JACK][suit] = 0;
				All[turn]->known[TEN][suit] = 0;
				All[turn]->known[KING][suit] = 0;
			}
			else if (rank == JACK)
			{
				All[turn]->known[TEN][suit] = 0;
				All[turn]->known[KING][suit] = 0;
			}
			
		}
		else //opponent
		{
			if (rank == QUEEN)
				All[turn]->known[JACK][suit] = 0;
			else if (rank == KING)
			{
				All[turn]->known[JACK][suit] = 0;
				All[turn]->known[QUEEN][suit] = 0;
			}
			else if (rank == TEN)
			{
				All[turn]->known[KING][suit] = 0;
				All[turn]->known[QUEEN][suit] = 0;
				All[turn]->known[JACK][suit] = 0;
			}
		}
	
		if ((rank == ACE) && (topRank == ACE))
		{
			aceOnAce = true;

			for (short int i = JACK; i >= TEN; i--)
			{
				if (All[turn]->known[i][suit] > 0)
				{
					notOut = true;
					break;
				}
			}

			if (!notOut)
			{
				All[turn]->known[TEN][suit] = 0;
				All[turn]->known[KING][suit] = 0;
				All[turn]->known[QUEEN][suit] = 0;
				All[turn]->known[JACK][suit] = 0;
			}
			
			if(leadSuit != trump)
				All[turn]->trumpingSuit[leadSuit] = true;  //even if he's not out, have to convince partner to send him a K
		}
	}
	else if ((All[turn]->getID() != lead) && (topRank != ACE) && (suit == topSuit)) //lead was not an ace, and player couldn't play an Ace
	{
		if (rank < topRank)
		{//beat top rank
			for (short int i = rank+1; i < topRank; i++)
			{
				All[turn]->known[i][suit] = 0;
			}
			if ((leadSuit != trump) && (suit == trump))
				All[turn]->trumpingSuit[leadSuit] = true;
		}
		else if (rank >= topRank) //couldn't beat it
		{
			for (short int i = topRank-1; i >= ACE; i--)
			{
				All[turn]->known[i][suit] = 0;
			}
		}

		if ((leadSuit != trump) && (suit == trump))
			All[turn]->trumpingSuit[leadSuit] = true;

	}
	else if ((getTrickCounter() != 0) && (suit != leadSuit))  //trumped
	{
		for (short int i = ACE; i <= JACK; i++)
		{
			All[turn]->known[i][leadSuit] = 0;
		}
		if (leadSuit != trump)
		{
			if (All[turn]->getNumOfCardsInRange(-1, trump) > 0)
				All[turn]->trumpingSuit[leadSuit] = true;
			else if (suit == trump) //JUST played last trump, so no one knows that he's out
				All[turn]->trumpingSuit[leadSuit] = true;

		}

	}

	playedCard(PlayedCard, All[turn]);

	if (getNumOfCardsLeft(rank, suit) == 0)
		All[turn]->known[rank][suit] = 0;
	else if (All[turn]->known[rank][suit] > 1)
		All[turn]->known[rank][suit]--;
	else
		All[turn]->known[rank][suit] = -1;

	if (All[turn]->trumpingSuit[suit] && !aceOnAce)
		All[turn]->trumpingSuit[suit] = false;

	return PlayedCard;
}

short int TrickGame::findRank(short int value, bool trumped)
//Jacks = 0, Queens, 1, Kings 2, Tens 3, Aces 4
{
	switch (value)     
	{
	case 0:
		return JACK;
		break;
	case 1:
		return QUEEN;
		break;
	case 2:
		return KING;
		break;
	case 3:
		return TEN;
		break;
	case 4:
		return ACE;
		break;
	default:
		return -1;
		break;
	}

}


short int TrickGame::potentialTrickValue(Player *All[4], short int rank, short int suit, unsigned short turn)
{
	short int playValue = 0;
	short int totalValue = 0;
	short int topCardPlay = 8 - cardValues[rank][suit];
	bool lostTrick = false;
	bool trumped = false;
	bool newTrump = false;
	short int trumpRank = JACK+1;
	short int tempTrumpRank = JACK+1;
	short int points = 0;

	playValue = 8 - potPlays(All, turn, All[turn]->getLeftID(), rank, suit, &trumped, &trumpRank, lostTrick, 0);
	totalValue = playValue;

	if (trumped)  //trumped to take trick
	{
		lostTrick = true;
		topCardPlay = playValue;
		trumpRank = findRank(playValue, trumped);
		rank = JACK+1;
		tempTrumpRank = trumpRank; //for use later
		newTrump = true;
	}
	else if (playValue > topCardPlay) //played better card than lead
	{
		lostTrick = true;
		topCardPlay = playValue;
		rank = findRank(playValue, trumped);
	}

	if (findRank(playValue, trumped) <= KING)
		points += 2;
	
	playValue = 8 - potPlays(All, turn, All[turn]->getPartnerID(), rank, suit, &trumped, &trumpRank, lostTrick, 0);
	totalValue += playValue;
	
	if ((trumped) && (trumpRank > tempTrumpRank))  //overtrumped or trumped to take lead
	{
		lostTrick = false;
		topCardPlay = playValue;
		trumpRank = findRank(playValue, trumped);
		tempTrumpRank = trumpRank; //for later use
		rank = JACK+1;
		newTrump = true;
	}
	else if ((!trumped) && (playValue > topCardPlay)) //played a better card than previous or lead
	{
		if (lostTrick)
			lostTrick = false;

		topCardPlay = playValue;
		rank = findRank(playValue, newTrump);
	}

	if (findRank(playValue, newTrump) <= KING)
		points += 2;

	newTrump = false;
	playValue = 8 - potPlays(All, turn, All[turn]->getRightID(), rank, suit, &trumped, &trumpRank, lostTrick, 0);
	totalValue += playValue;

	if ((trumped) && (trumpRank > tempTrumpRank)) //overtrumped or trumped to take lead
	{
		lostTrick = true;
		newTrump = true;
	}
	else if ((!trumped) && (playValue > topCardPlay)) //played a better card than previous or lead
		lostTrick = true;

	if (findRank(playValue, newTrump) <= KING)
		points += 2;

	if (lostTrick)
		return -(totalValue + points);
	else
		return totalValue + points;
}

/////////////Starter = lead, turn is whose turn is it in the virtual plan

short int TrickGame::potPlays(Player *All[4], unsigned short starter, unsigned short turn, short int rank, short int suit, bool *trumped, short int *trumpRank, bool lostTrick, short int loopType)
{
	short int startRank = JACK;
	short int endRank = ACE;
	short int numOfCardsLeft = 0;

	if ((All[turn]->getSuitState(suit)) && (loopType != 2)) //if Selected is trumping suit, loopType == 2 means new trump
	{
		rank = *trumpRank;
		suit = trump;
		*trumped = true;
	}
	else if ((rank > ACE) && !loopType && !(*trumped)) //not trumping, Ace not led, first time through, not currently trumped
	{ 
		if ((!All[All[starter]->getPartnerID()]->trumpingSuit[suit]) && (!All[All[starter]->getLeftID()]->trumpingSuit[suit]) && (!All[All[starter]->getRightID()]->trumpingSuit[suit]))
		{ // no one is trumping that you know of
			if (All[All[turn]->getPartnerID()]->known[ACE][suit] > 0)  //if he has it, he'll take it
				return cardValues[ACE][suit];

			if (All[turn]->getID() == All[starter]->getLeftID()) //Selected is to the Left of Starter
			{
				short int temp = 0;
				temp += All[starter]->getNumOfCardsInRange(ACE, suit);  //counting how many known Ace's are out there
				if (All[All[starter]->getPartnerID()]->known[ACE][suit] > 0)  
					temp += All[All[starter]->getPartnerID()]->known[ACE][suit];  //continuing the count
				if (All[All[turn]->getPartnerID()]->known[ACE][suit] > 0)
					temp += All[All[turn]->getPartnerID()]->known[ACE][suit]; //finalizing the count

				if (getNumOfCardsLeft(ACE, suit) - temp > 0) //checking to see if they're not all accounted for
					return cardValues[ACE][suit];  //one must assume that it'll get played
				else if (getNumOfCardsLeft(ACE, suit) == All[All[turn]->getPartnerID()]->known[ACE][suit]) //Selected's Partner will take trick
				{
					if (rank > KING)
						startRank = KING;
					else
						startRank = rank;
				}
			}
			else //selected's P has already played, just play lowest card possible
				startRank = rank;
		}
		else //someone is trumping it, find out who
		{
			if (All[All[turn]->getPartnerID()]->trumpingSuit[suit])
				startRank = KING;
			else
				startRank = JACK;
		}
		endRank = ACE;
	}
	else if ((rank == ACE) && (loopType != 2) && !(*trumped))
	{//Ace was played, not a new trump, not currently trumped
		if (All[turn]->getID() % 2 == lead % 2)
		{//if partner of the current leader
			if (loopType != 1 && !lostTrick)
			{//if he hasn't already gone through this section, and they haven't already lost the trick
				startRank = KING;
				endRank = TEN;
			}
			else
			{//either don't have any Kings or Tens, OR already lost the trick
				startRank = JACK;
				endRank = rank;
			}
		}
		else if (!lostTrick)
		{//not partner of current leader, and leader hasn't lost the trick
			startRank = JACK;
			endRank = rank;
		}
		else
		{//not partner of current leader, and leader HAS lost the trick
			startRank = KING;
			endRank = rank;
		}
	}

	for(short int i = startRank; i >= endRank; i--) //play lowest card in range
	{
		if (All[turn]->known[i][suit] == 0)//already know Selected does not have this card
			continue;

		short int temp = 0;

		if (All[turn]->known[i][suit] > 0) //already know Selected DOES have this card
			return cardValues[i][suit];

		if (All[All[turn]->getPartnerID()]->known[i][suit] > 0)  //counting how many cards are out there
			temp += All[All[turn]->getPartnerID()]->known[i][suit];

		if (All[starter]->known[i][suit] > 0)
			temp += All[All[starter]->getPartnerID()]->known[i][suit];

		temp += All[starter]->getNumOfCardsInRange(i, suit);

		numOfCardsLeft = getNumOfCardsLeft(i, suit) - temp;

		if (numOfCardsLeft > 0)
			return cardValues[i][suit];
	}
	
	if (loopType == 2)
		return 0;
	else if (startRank == KING)
		return potPlays(All, starter, turn, rank, suit, trumped, trumpRank, lostTrick, 1); //try from the J
	else if (startRank == JACK)
		return potPlays(All, starter, turn, *trumpRank, trump, trumped, trumpRank, lostTrick, 2); //has to trump
	else
		return 0;
}

Card *TrickGame::startTrick(Player *All[4], unsigned short turn)
{
	short int currentLook;
	short int currentLookValue;
	//int points = 0;
	short int bestValue = -999;
	Card *BestCard;
	//int suitState = -1;
	short int suit;
	short int rank;
	short int largeSuit = -1;
	short int smallSuit = -1;
	short int lgSuit = -1;
	short int smSuit = 99;
	short int total = 0;
	bool LOutOfTrump = false;
	bool POutOfTrump = false;
	bool ROutOfTrump = false;
	bool endOfSequence = false;
	bool zeroFlag = false;
	short int unknowns = 0;
	
	if (!tricksPlayed)
		setLead(All[turn]->getID());

	for (short int i = HEARTS; i <= SPADES; i++)
	{
		short int temp;

		if (i == trump)
			continue;

		temp = All[turn]->getNumOfCardsInRange(-1, i);
		if (temp > lgSuit)
		{
			largeSuit = i;
			lgSuit = temp;
		}
		else if (temp < smSuit)
		{
			smallSuit = i;
			smSuit = temp;
		}
	}

	for(short int i = 0; i < 20; i++)
	{
		currentLook = All[turn]->getCardFromPlayerHand(i)->getValue();
	
		if (currentLook > 80)
			break;

		rank = (currentLook % 20) / 4;
		suit = currentLook / 20;

		total = 0;
		unknowns = 0;
		zeroFlag = false;

		if (All[All[turn]->getLeftID()]->getKnownOfSuit(trump) == 0)
			LOutOfTrump = true;
		else
			LOutOfTrump = false;

		if (All[All[turn]->getPartnerID()]->getKnownOfSuit(trump) == 0)
			POutOfTrump = true;
		else
			POutOfTrump = false;

		if (All[All[turn]->getRightID()]->getKnownOfSuit(trump) == 0)
			ROutOfTrump = true;
		else
			ROutOfTrump = false;		

		for (short int j = 0; j <= JACK; j++)
			total += playedCards[j][suit];

	/*	if (suit != trump)
		{
			int left = 0;
			int partner = 0;
			int right = 0;

			left = Left.getKnownOfSuit(suit);
			partner = Partner.getKnownOfSuit(suit);
			right = Right.getKnownOfSuit(suit);

			if (left == 0 && !LOutOfTrump)
				zeroFlag = true;
			else if (left > 0)
				total += left;
			else
				unknowns++;

			if (partner > 0)
				total += partner;
			else if (partner < 0)
				unknowns++;
			
			if (right == 0 && !ROutOfTrump)
				zeroFlag = true;
			else if (right > 0)
				total += right;
			else
				unknowns++;

			for (int k = 0; k < 5; k++)
			{
				total += playedCards[k][suit];
			}
		}*/
			
		if (LOutOfTrump) //if out of trump, frees up a possibility
			total--;

		if (POutOfTrump)
			total--;

		if (ROutOfTrump)
			total--;

		currentLookValue = 0;

		if (All[All[turn]->getPartnerID()]->trumpingSuit[suit] && !((All[All[turn]->getLeftID()]->trumpingSuit[suit]) || (All[All[turn]->getRightID()]->trumpingSuit[suit])))
		{
			if (rank == KING)
				currentLookValue += 512;
			else if (rank == TEN)
				currentLookValue += 256;
			else if (rank == ACE)
				currentLookValue -= 8;
			else if (rank == QUEEN)
				currentLookValue += 128;
			else
				currentLookValue += 64;
		}
		else if (All[All[turn]->getLeftID()]->trumpingSuit[suit] || All[All[turn]->getRightID()]->trumpingSuit[suit])
		{
			if (All[All[turn]->getLeftID()]->trumpingSuit[suit] != All[All[turn]->getRightID()]->trumpingSuit[suit])
			{
				if (rank == KING)
					currentLookValue -= 64;
				else if (rank == TEN)
					currentLookValue -= 128;
				else if (rank == ACE)
					currentLookValue -= 256;
				else
					currentLookValue -= 32;
			}
		}

		if (zeroFlag || (((20 - total) / 3) < 1))
		{
			if (rank == KING)
				currentLookValue -= 64;
			else if (rank == TEN)
				currentLookValue -= 128;
			else if (rank == ACE)
				currentLookValue -= 256;
			else if (rank == QUEEN)
				currentLookValue -= 32;
			else
				currentLookValue -= 16;
		}

		currentLookValue -= cardValues[rank][suit];

		currentLookValue += potentialTrickValue(All, rank, suit, turn);

		if (suit == largeSuit)
		{
			if (rank <= TEN)
				currentLookValue -= 8;
			else if (rank >= QUEEN)
				currentLookValue += 8;
		}
		else if (suit == smallSuit)
		{
			if (rank <= TEN)
				currentLookValue += 8;
			else if (rank >= QUEEN)
				currentLookValue -= 8;
		}

		if ((rank == KING) && ((getNumOfCardsLeft(TEN, suit) || (getNumOfCardsLeft(ACE, suit)))))
			currentLookValue -= 2;
		else if ((rank == TEN) && (getNumOfCardsLeft(ACE, suit)))
			currentLookValue -= 4;

		if ((suit != trump) && ((!All[All[turn]->getLeftID()]->trumpingSuit[suit]) || (!All[All[turn]->getPartnerID()]->trumpingSuit[suit]) || (!All[All[turn]->getRightID()]->trumpingSuit[suit])))
		{
			if (rank == ACE)
				currentLookValue += 1;
			else if ((rank == TEN) && (getNumOfCardsLeft(ACE, suit) == All[turn]->getNumOfCardsInRange(ACE, suit)))
				currentLookValue += 2;
			else if ((rank == KING) && (getNumOfCardsLeft(ACE, suit) + getNumOfCardsLeft(TEN, suit) == All[turn]->getNumOfCardsInRange(ACE, suit) + All[turn]->getNumOfCardsInRange(TEN, suit)))
				currentLookValue += 4;
			else if ((rank == QUEEN) && (getNumOfCardsLeft(ACE, suit) + getNumOfCardsLeft(TEN, suit) + getNumOfCardsLeft(KING, suit) == All[turn]->getNumOfCardsInRange(ACE, suit) + All[turn]->getNumOfCardsInRange(TEN, suit) + All[turn]->getNumOfCardsInRange(KING, suit)))
				currentLookValue += 8;
			else if ((rank == JACK) && (getNumOfCardsLeft(ACE, suit) + getNumOfCardsLeft(TEN, suit) + getNumOfCardsLeft(KING, suit) + getNumOfCardsLeft(QUEEN, suit) == All[turn]->getNumOfCardsInRange(ACE, suit) + All[turn]->getNumOfCardsInRange(TEN, suit) + All[turn]->getNumOfCardsInRange(KING, suit) + All[turn]->getNumOfCardsInRange(QUEEN, suit)))
				currentLookValue += 16;
		}

		if ((20 - tricksPlayed) - All[turn]->getNumOfCardsInRange(-1, trump) <= 1)
		{
			endOfSequence = true;

			if (tricksPlayed == 18)
			{
				if (suit != trump)
					currentLookValue += 256;
			}
			else
			{
				if (suit == trump)
				{
					if (rank == ACE)
						currentLookValue += 128;
					else if (rank == TEN)
						currentLookValue += 64;
					else if (rank == KING)
						currentLookValue += 32;
					else if (rank == QUEEN)
						currentLookValue += 16;
					else
						currentLookValue += 8;
				}
				else
					currentLookValue -= 256;
			}
		}

		//bid winner logic
		if (All[turn]->getID() == bidWinner)
		{
			if (All[turn]->getNumOfCardsInRange(ACE, -1) == All[turn]->getNumOfCardsInRange(ACE, trump))
			{
				//Played all Non-Trump Aces
				if ((All[turn]->getNumOfCardsInRange(-1, trump) - All[turn]->getNumOfCardsInRange(ACE, trump)) > 1)
				{//have enough trump to continue
					if ((getNumOfCardsLeft(ACE, trump) - All[turn]->getNumOfCardsInRange(ACE, trump)) > 0)
					{//still Non-Trump Aces out there
						if (suit == trump)
						{
							if (All[All[turn]->getPartnerID()]->known[ACE][trump] == (getNumOfCardsLeft(ACE, trump) - All[turn]->getNumOfCardsInRange(ACE, trump)))
							{
								if ((rank == KING) || (rank == TEN))
									currentLookValue += 16;
							}
							else if ((All[All[turn]->getLeftID()]->known[ACE][trump] > 0) && ((rank == JACK) || ((rank == QUEEN) && (All[turn]->getNumOfCardsInRange(JACK, trump) == 0))))
								currentLookValue += 16; 
							else if ((All[All[turn]->getLeftID()]->known[ACE][trump] < 0) && (rank == QUEEN))
								currentLookValue += 16; 
							else if ((All[All[turn]->getLeftID()]->known[ACE][trump] < 0) && (rank == JACK))
								currentLookValue += 8;
							else if (rank < QUEEN)
								currentLookValue -= 256;  //out of Jacks and Queens, give up looking for the Aces
						}
					}
					else //all Aces are accounted for, play your losers
					{
						if (suit != trump)
						{
							if ((rank == QUEEN) || (rank == JACK))
								currentLookValue += 8;
						}
						else if ((suit == trump) && !endOfSequence)
								currentLookValue -= 128;

						if ((rank == ACE) && (suit == trump))
							currentLookValue -= 128;
					}
				}
				else //play your ACE of trump!
				{
					if ((rank == ACE) && (suit == trump))
						currentLookValue += 32;
				}
			}
			else //make sure you don't play trump
			{
				if ((suit == trump) && !endOfSequence)
					currentLookValue -= 32;
				else if ((suit != trump) && (rank == ACE))
					currentLookValue++;
			}
		}
		
		if (All[turn]->getPartnerID() == bidWinner) //bidwinner partner's logic
		{
			if (suit == trump)
			{
				if (rank == ACE)
					currentLookValue += 64;
				else if (!endOfSequence)
					currentLookValue -= 256;
			}

			if (All[turn]->getNumOfCardsInRange(ACE, -1) == 0)
			{
				if (All[All[turn]->getLeftID()]->known[ACE][suit] > 0) 
				{
					if (rank == JACK) //Know there's an Ace to the left
						currentLookValue += 64;
					else if ((All[turn]->getNumOfCardsInRange(JACK, suit) == 0) && (rank == QUEEN))
						currentLookValue += 32;
				}
				else if (All[All[turn]->getLeftID()]->known[ACE][suit] < 0)
				{
					if (rank == QUEEN) //Don't know
						currentLookValue += 64;
					else if ((All[turn]->getNumOfCardsInRange(QUEEN, suit) == 0) && (rank == JACK))
						currentLookValue += 32;
				}

			}
			else if ((suit != trump) && (rank == ACE))
				currentLookValue += 8;
		}

		//opposition logic
		if ((All[turn]->getPartnerID() != bidWinner) && (All[turn]->getID() != bidWinner))
		{
			if (suit == trump)
			{
				if (All[turn]->getNumOfCardsInRange(-1, trump) <= (All[turn]->getNumOfCardsInRange(ACE, trump) + 1))
				{
					if (rank == ACE)
						currentLookValue += 32; //running low, play your ACE
				}
				else if (rank == ACE)
					currentLookValue -= 128; //not running low on trump, keep your ACE and all other trump
				else if (!endOfSequence)
					currentLookValue -= 64;
			}
			else if (All[turn]->getNumOfCardsInRange(ACE, -1) == All[turn]->getNumOfCardsInRange(ACE, trump))
			{
				//run out of aces to play
				if (All[All[turn]->getLeftID()]->known[ACE][suit] > 0) 
				{
					if (rank == JACK) //Know there's an Ace to the left
						currentLookValue += 32;
					else if ((All[turn]->getNumOfCardsInRange(JACK, suit) == 0) && (rank == QUEEN))
						currentLookValue += 16;
				}
				else if (All[All[turn]->getLeftID()]->known[ACE][suit] < 0)
				{
					if (rank == QUEEN) //Don't know
						currentLookValue += 32;
					else if ((All[turn]->getNumOfCardsInRange(QUEEN, suit) == 0) && (rank == JACK))
						currentLookValue += 16;
				}
				else if (rank == KING)
					currentLookValue += 16;
				else if (rank == TEN)
					currentLookValue += 8;
			}
			else if (rank == ACE)
				currentLookValue += 16;
		}
		if (currentLookValue >= bestValue)
		{
			bestValue = currentLookValue;
			BestCard = All[turn]->getCardFromPlayerHand(i);
		}
	}

	return BestCard;
}

void TrickGame::buildDecisionTree()
{
	for(short int i = 0; i < 5; i++)
		for (short int j = 0; j < 4; j++)
			cardValues[i][j] = i;  
								//Jacks = 4, Queens = 3, Kings = 2, Tens = 1, Aces 0

//	for(int i = ACE; i <= JACK; i++)
//		cardValues[i][getTrumpSuit()] = cardValues[i][getTrumpSuit()] - pow(2.0, JACK-i+1);  
	//of Trump:  Jacks = 33, Queens = 27, Kings = 21, Tens = 7, Aces = -13
}

void TrickGame::addBulkPoints(short team, short points)
{
	if (team == RED)
		verticalTricks += points;
	else
		horizontalTricks += points;
}

bool TrickGame::updateShrinkCloseTrick(short int location, Card *Trick[4])
{
	float x[4];// = {getX(), Card2->getX(), Card3->getX(), Card4->getX()};
	float y[4];// = {getY(), Card2->getY(), Card3->getY(), Card4->getY()};
	float newX;
	float newY;
	float moveXperTurn[4];
	float moveYperTurn[4];
	bool offScreen[4] = {false, false, false, false};
	short int speed = 4;

	for (int i = 0; i < 4; i++)
	{
		x[i] = Trick[i]->getX();
		y[i] = Trick[i]->getY();
	}

	switch (location)
	{
	case WEST:
		newX = -110.0f;
		newY = 50.0f;
		break;
	case NORTH:
		newX = 50.0f;
		newY = -110.0f;
		break;
	case EAST:
		newX = 110.0f;
		newY = 50.0f;
		break;
	case SOUTH:
		newX = 50.0f;
		newY = 110.0f;
		break;
	default:
		newX = 50.0f;
		newY = 50.0f;
		break;
	}
	
	for (short int i = 0; i < 4; i++)
	{
		if (newX < x[i])
		{//have to go negative to reach destination
			if ((x[i] - newX) / 4 > speed)
				moveXperTurn[i] = (newX - x[i]) / 4; //normal movement rate, negative
			else if (x[i] - speed >= newX)
				moveXperTurn[i] = (float)(-speed); //slower movement rate
			else
				moveXperTurn[i] = newX - x[i]; //even out to destination, will be negative
		}
		else
		{ //have to go positive to reach destination
			if ((newX - x[i]) / 4 > speed)
				moveXperTurn[i] = (newX - x[i]) / 4; //nomal movement rate
			else if (x[i] + speed <= newX)  
				moveXperTurn[i] = (float)(speed);
			else
				moveXperTurn[i] = newX - x[i];
		}
		
		if (newY < y[i])
		{
			if ((y[i] - newY) / 4 > speed)
				moveYperTurn[i] = (newY - y[i]) / 4;
			else if (y[i] - speed >= newY)
				moveYperTurn[i] = (float)(-speed);
			else
				moveYperTurn[i] = newY - y[i];
		}
		else
		{
			if ((newY - y[i]) / 4 > speed)
				moveYperTurn[i] = (newY - y[i]) / 4;
			else if (y[i] + speed <= newY)
				moveYperTurn[i] = (float)(speed);
			else if (y[i] + speed > newY)  //don't need to check if it's less than or equal to because it's default at 10
				moveYperTurn[i] = newY - y[i];
		}
	}
	
	for (int i = 0; i < 4; i++)
	{
		if ((x[i] > 100) || (x[i] < 0) || (y[i] > 100) || (y[i] < 0))
		{
			offScreen[i] = true;
			Trick[i]->hide();
		}
		else
			Trick[i]->setPosition(Point(x[i] + moveXperTurn[i], y[i] + moveYperTurn[i]));
	
/*	if ((x[1] > 100) || (x[1] < 0) || (y[1] > 100) || (y[1] < 0))
	{
		offScreen[1] = true;
		Card2->hide();
	}
	else
		Card2->setPosition(Point(x[1] + moveXperTurn[1], y[1] + moveYperTurn[1]));

	if ((x[2] > 100) || (x[2] < 0) || (y[2] > 100) || (y[2] < 0))
	{
		offScreen[2] = true;
		Card3->hide();
	}
	else
		Card3->setPosition(new Point(x[2] + moveXperTurn[2], y[2] + moveYperTurn[2]));

	if ((x[3] > 100) || (x[3] < 0) || (y[3] > 100) || (y[3] < 0))
	{
		offScreen[3] = true;
		Card4->hide();
	}
	else
		Card4->setPosition(new Point(x[3] + moveXperTurn[3], y[3] + moveYperTurn[3]));
*/
	}
	
	if (offScreen[0] && offScreen[1] && offScreen[2] && offScreen[3])
			return true;
	else
		return false;
}