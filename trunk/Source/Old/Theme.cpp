#include "Theme.h"
#include "agk.h"

Theme::Theme()
{
    themeReady = false;
	themeHasGrown = false;
	currentTheme = GREEN;
}

/*void Theme::reset(unsigned short newTheme, unsigned short state)
{
	themeReady = false;
	currentTheme = newTheme;

	BCBubble = new BidControl();

	for (int i = 0; i < 4; i++)
	{
		MeldBubbles[i] = new Bubbles();
		BidBubbles[i] = new Bubbles();
	}

	InGameMenuButton = new Buttons();

	AllCards = new Deck();

	Bid = new Numbers();
	BidScore = new Numbers();
	H2Get = new Numbers();
	HMeld = new Numbers();
	HScore = new Numbers();
	PastEastBid = new Numbers();
	PastNorthBid = new Numbers();
	PastSouthBid = new Numbers();
	PastWestBid = new Numbers();
	V2Get = new Numbers();
	VMeld = new Numbers();
	VScore = new Numbers();

	Background = new Sprite();
	TextBackground = new Sprite();

	TSBubble = new TrumpSelect();
}*/

Theme::~Theme(void)
{
}

unsigned short Theme::getCurrentTheme(void)
{
	return selectedTheme;
}

void Theme::init(AnimatedSprite *Symbol, unsigned short theme, unsigned short state)
{
	Point CardLocation[80];
	bool faceDown[80];
	bool outlined[80];
	bool rotatedLeft[80];
	bool rotatedRight[80];
	Image *BackgroundImage = new Image();

	if (state != MENU)
	{
		for (int i = 0; i < 80; i++)
		{
			CardLocation[i] = AllCards->FullDeck[i]->getLocation();
			faceDown[i] = AllCards->FullDeck[i]->getFaceDirection();
			outlined[i] = AllCards->FullDeck[i]->getIsOutlined();
			rotatedLeft[i] = AllCards->FullDeck[i]->isRotatedLeft();
			rotatedRight[i] = AllCards->FullDeck[i]->isRotatedRight();
		}
	}

	TSBubble->setSize(40.0f);
	
	for (int i = 0; i < 4; i++)
	{
		BidBubbles[i]->setSize(39.0f);
		MeldBubbles[i]->setSize(57.0f);
	}

	if (PLATFORM != MOBILE)
	{
		BidBubbles[WEST]->offsetBidNumberBy(new Point(0.0f, -3.0f));
		BidBubbles[NORTH]->offsetBidNumberBy(new Point(0.0f, -3.0f));
		BidBubbles[NORTH]->offsetPassBy(new Point(0.0f, -1.0f));
		BidBubbles[EAST]->offsetBidNumberBy(new Point(0.0f, -3.0f));
		BidBubbles[SOUTH]->offsetBidNumberBy(new Point(0.0f, 3.0f));
		BidBubbles[SOUTH]->offsetPassBy(new Point(0.0f, 6.0f));

	BCBubble->setSize(45.0f);
	Background->setSize(100.0, -1.0f);

	Symbol->incrementFrame();
	agk::Sync();
}

void Theme::initNumbers(void)
{
		//initialize numbers to a value, then hide--don't display!
	HScore->setDigit(0, 0);
	HScore->setDigit(1, 0);
	HScore->setDigit(2, 0);
	VScore->setDigit(0, 0);
	VScore->setDigit(1, 0);
	VScore->setDigit(2, 0);

	HScore->hideAll();
	VScore->hideAll();

	BidScore->setValue(50);
	BidScore->hideAll();
	//BidScore.display(0, 0);
	//BidScore.display(1, 5);

	H2Get->setValue(0);
	//H2Get.display(0, 0);
	V2Get->setValue(0);
	//V2Get.display(0, 0);
	H2Get->hideAll();
	V2Get->hideAll();

	PastNorthBid->setValue(50);
	PastSouthBid->setValue(50);
	PastEastBid->setValue(50);
	PastWestBid->setValue(50);
	PastNorthBid->hideAll();
	PastSouthBid->hideAll();
	PastEastBid->hideAll();
	PastWestBid->hideAll();
}

void Theme::setNumberPrio(void)
{
		//Step 3: Set Priority
	Bid->setDepth(9997);
	BidScore->setDepth(9997);
	VScore->setDepth(9997);
	HScore->setDepth(9997);
	VMeld->setDepth(9997);
	HMeld->setDepth(9997);
	//BCBubble->Bid.setPriority(7);
	V2Get->setDepth(9997);
	H2Get->setDepth(9997);
	PastNorthBid->setDepth(9965); //need to be high to get over cards
	PastSouthBid->setDepth(9965);
	PastEastBid->setDepth(9965);
	PastWestBid->setDepth(9965);
}

void Theme::setNumberLoc(void)
{
    float offset = 0.0f;
    
    if (PLATFORM == MOBILE)
        offset = 0.25f;
    
	for (short int i = 0; i < 3; i++)
	{
		if (strcmp(currentDir, "green/") == 0) //if currentDir is green
		{
			BidScore->setLocation(i, 83.5f - (3.0f * i), 70.0f, 0);
			VScore->setLocation(i, 8.25f - (2.0f * i), 10.0f, -5.75f, -0.6f);
			HScore->setLocation(i, 18.75f - (2.0f * i), 10.0f, -5.75f, -0.6f); //
			VMeld->setLocation(i, 4.9f - (1.5f * i), 71.25f, 0); //
			HMeld->setLocation(i, 9.9f - (1.5f * i), 71.25, 0); //0, 0.5
			V2Get->setLocation(i, 15.25f - (1.5f * i), 71.25f, 0); 
			H2Get->setLocation(i, 20.25f - (1.5f * i), 71.25f, 0);
		}
		else if (strcmp(currentDir, "red/") == 0) //if currentDir is red
		{
            BidScore->setLocation(i, 84.5f - ((2.5f + offset) * i), 70.0f, 0); //added 1 space
			VScore->setLocation(i, 8.25f - (2.0f * i), 10.0f, -5.75f, -0.6f);
			HScore->setLocation(i, 18.75f - (2.0f * i), 10.0f, -5.75f, -0.6f); //
			VMeld->setLocation(i, 4.75f - (1.5f * i), 71.25f, 0); //
			HMeld->setLocation(i, 9.9f - (1.5f * i), 71.25, 0); //0, 0.5
			V2Get->setLocation(i, 15.0f - (1.5f * i), 71.25f, 0); 
			H2Get->setLocation(i, 20.25f - (1.5f * i), 71.25f, 0);
		}
        else if (strcmp(currentDir, "ancient/") == 0) //if currentDir is ancient
		{

		}
		else if (strcmp(currentDir, "xmas/") == 0) //if currentDir is ancient
		{
			BidScore->setLocation(i, 83.5f - (3.0f * i), 73.0f, 0);
			VScore->setLocation(i, 9.25f - (2.0f * i), 13.0f, -5.75f, -0.6f);
			HScore->setLocation(i, 20.75f - (2.0f * i), 13.0f, -5.75f, -0.6f); //
			VMeld->setLocation(i, 4.9f - (1.5f * i), 73.75f, 0); //
			HMeld->setLocation(i, 9.9f - (1.5f * i), 73.75, 0); //0, 0.5
			V2Get->setLocation(i, 16.25f - (1.5f * i), 73.75f, 0); 
			H2Get->setLocation(i, 22.25f - (1.5f * i), 73.75f, 0);
		}
		else //current Dir is electric
		{
			BidScore->setLocation(i, 84.5f - ((2.5f + offset) * i), 70.5f - (offset * 2), 0);
			VScore->setLocation(i, 8.5f - (2.0f * i), 10.0f, -5.75f, -0.6f);
			HScore->setLocation(i, 18.75f - (2.0f * i), 10.0f, -5.75f, -0.6f); //
			VMeld->setLocation(i, 4.9f - (1.5f * i), 71.25f, 0); //
			HMeld->setLocation(i, 9.9f - (1.5f * i), 71.25, 0); //0, 0.5
			V2Get->setLocation(i, 15.25f - (1.5f * i), 71.25f, 0); 
			H2Get->setLocation(i, 20.25f - (1.5f * i), 71.25f, 0);
		}
			

		PastNorthBid->setLocation(i, 52.0f - (2.75f * i), 10.75f, 0);
		PastSouthBid->setLocation(i, 52.0f - (2.75f * i), 87.0f, 0);
		PastWestBid->setLocation(i, 13.5f - (2.75f * i), 39.25f, 0);
		PastEastBid->setLocation(i, 90.5f - (2.75f * i), 39.25f, 0);
	}
}

void Theme::setSizeNumbers(void)
{
	//Step 4: Scale
//	BCBubble->BidValue.setSize(5.25f); ///keeping value for other themes
	
	Bid->setSize(6.5f);
	VScore->setSize(1.75f);
	HScore->setSize(1.75f);
	VMeld->setSize(1.5f);
	HMeld->setSize(1.5f);
	V2Get->setSize(1.5f);
	H2Get->setSize(1.5f);
	PastNorthBid->setSize(2.5f);
	PastSouthBid->setSize(2.5f);
	PastEastBid->setSize(2.5f);
	PastWestBid->setSize(2.5f);

	for (int i = 0; i < 4; i++)
		BidBubbles[i]->Bid->setSize(6.5f);
}

void Theme::initNumbers(Text Dir)
{
	Bid->setData(Dir);
    BidScore->setData(Dir);
    VScore->setData(Dir, true);
    HScore->setData(Dir, true);
    VMeld->setData(Dir, true);
    HMeld->setData(Dir, true);
    PastNorthBid->setData(Dir);
    PastEastBid->setData(Dir);
    PastSouthBid->setData(Dir);
    PastWestBid->setData(Dir);
    V2Get->setData(Dir);
    H2Get->setData(Dir);
}

void Theme::show(short int state)
{
	InGameMenuButton->show();

	AllCards->show();
	
	//setNumberLoc();
	//setSizeNumbers();

	BidScore->showAll();
	//Bid.hideAll();
	//Bid.showAll();
	H2Get->showAll();
	HMeld->showAll();
	HScore->showAll();

	if (state != PLAYING)
	{
		PastEastBid->showAll();
		PastNorthBid->showAll();
		PastSouthBid->showAll();
		PastWestBid->showAll();
	}

	V2Get->showAll();
	VMeld->showAll();
	VScore->showAll();

	Background->setVisible(true);
	InGameMenuButton->show();
}

void Theme::hide(void)
{
	InGameMenuButton->hide();

	Background->setVisible(false);

	AllCards->hide();
	
	BCBubble->hide();
	TSBubble->hide();

	BidScore->hideAll();
	Bid->hideAll();
	H2Get->hideAll();
	HMeld->hideAll();
	HScore->hideAll();
	PastEastBid->hideAll();
	PastNorthBid->hideAll();
	PastSouthBid->hideAll();
	PastWestBid->hideAll();
	V2Get->hideAll();
	VMeld->hideAll();
	VScore->hideAll();
}

bool Theme::isSetup(void)
{
    return themeReady;
}

void Theme::showPastBid(unsigned short player)
{
	PastBids[player]->showAll();
}

void Theme::hidePastBid(unsigned short player)
{
	PastBids[player]->hideAll();
}

void Theme::growBackground(void)
{
	Background.hasShrunk())
	{
		Options.Background.updateShrinkClose(-1);
		return;
	}

	if (CurrentTheme.Background.isGrowing())
	{
		CurrentTheme.Background.updateGrowOpen(100.0f);
		return;
	}
	else if (!CurrentTheme.Background.hasGrown())
	{
		CurrentTheme.Background.updateGrowOpen(100.0f);
		CurrentTheme.Background.setPriority(1);
		return;
	}

	NewGame.toggleXState(GROWBACKGROUND);
	NewGame.toggleXState(NewGame.getPrevState());

	//CurrentTheme.Bid.setValue(bid);
	CurrentTheme.show(NewGame.getState());

	//if (NewGame.getState() == MELDING)
	//	CurrentTheme.BidMeldBubbles.show(turn);

	themeHasGrown = true;
}

bool Theme::hasGrown(void)
{
	return themeHasGrown;
}

bool Theme::hasShrunk(void)
{
	return themeHasShrunk;
}

///////////////////////////////////////////////////////////////////////////////////////////
///  hScore = East-West Score
///  vScore = North-South Score
void Theme::updateBottomLeft(void)
{
	hScore = HScore->getValue();
	vScore = VScore->getValue();

	if (!HScore->getVisible())
	{
		CurrentTheme.HScore.setValue(hScore);
		CurrentTheme.HScore.showAll();
	}

	if (!CurrentTheme.VScore.getVisible())
	{
		CurrentTheme.VScore.setValue(vScore);
		CurrentTheme.VScore.showAll();
	}

	if (CurrentTheme.VScore.getValue() != vScore)
	{
		if (CurrentTheme.VScore.getValue() != vScore)
		{
			CurrentTheme.VScore.incrementTo(vScore, true);
#if (OS == ANDROID)
			if(CurrentTheme.VScore.getValue()%5==0)
#endif
                PointClick.playOnce();
		}
	}
	else if (vScore == 0)
		CurrentTheme.VScore.incrementTo(0, true);

	if (CurrentTheme.HScore.getValue() != hScore)
	{
		if (CurrentTheme.HScore.getValue() != hScore)
		{
			CurrentTheme.HScore.incrementTo(hScore, true);
#if (OS == ANDROID)
			if(CurrentTheme.HScore.getValue()%5==0)
#endif
                PointClick.playOnce();
		}
	}
	else if (hScore == 0)
		CurrentTheme.HScore.incrementTo(0, true);
}

void Theme::updateTopLeft()
{
	//float x = WEST_LOC_X - 88;
	//float y = NORTH_LOC_Y + 58;
	short hSaveAmount = 20;
	short vSaveAmount = 20;

	if ((bidWinner == -1) || (NewTrickGame.getTrumpSuit() == -1))
	{
		CurrentTheme.H2Get.setValue(0);
		CurrentTheme.V2Get.setValue(0);
		CurrentTheme.HMeld.setValue(0);
		CurrentTheme.VMeld.setValue(0);
		CurrentTheme.HMeld.hideAll();
		CurrentTheme.VMeld.hideAll();
		CurrentTheme.H2Get.hideAll();
		CurrentTheme.V2Get.hideAll();
		return;
	}

	//dbSetTextFont("Rockwell");
	if (bidWinner % 2 == 0)
		hSaveAmount = bid - hMeld;
	else
		vSaveAmount = bid - vMeld;

	if (hSaveAmount < 20)
		hSaveAmount = 20;
	if (vSaveAmount < 20)
		vSaveAmount = 20;

	if (hTricks != -1)
		hSaveAmount -= hTricks;
	if (vTricks != -1)
		vSaveAmount -= vTricks;

	if (hSaveAmount < 0)
		hSaveAmount = 0;
	if (vSaveAmount < 0)
		vSaveAmount = 0;

	if (hMeld < 20)
		hMeld = 0;
	if (vMeld < 20)
		vMeld = 0;

	if (hMeld >= 20)
	{
		if (CurrentTheme.HMeld.getValue() != hMeld)
		{

			CurrentTheme.HMeld.incrementTo(hMeld);
			PointClick.playOnce();
		}
	}
	else
	{
		CurrentTheme.HMeld.setValue(0);
		CurrentTheme.HMeld.showAll(true);
	}

	if (vMeld >= 20)
	{
		if (CurrentTheme.VMeld.getValue() != vMeld)
		{
			CurrentTheme.VMeld.incrementTo(vMeld);
			PointClick.playOnce();
		}
	}
	else
	{
		CurrentTheme.VMeld.setValue(0);
		CurrentTheme.HMeld.showAll(true);
	}

	//CurrentTheme.HMeld.hideAll();
	if (CurrentTheme.H2Get.getValue() != hSaveAmount)
	{
		CurrentTheme.H2Get.incrementTo(hSaveAmount);
		PointClick.playOnce();
	}

	if (CurrentTheme.V2Get.getValue() != vSaveAmount)
	{
		CurrentTheme.V2Get.incrementTo(vSaveAmount);
		PointClick.playOnce();
	}
}

void Theme::updateTopRight(void)
{
	//CurrentTheme.BidScore.hideAll();

	/*if (bid >= 100)
	{
		CurrentTheme.BidScore.display(2, 1);
		//CurrentTheme.Bid[0].display(75.5, 10.0);
		CurrentTheme.BidScore.show(2, 1);
	}*/

	if (bid > 50)
	{

		if (CurrentTheme.BidScore.getValue() != bid)
		{
			CurrentTheme.BidScore.incrementTo(bid);
			PointClick.playOnce();
		}
		//CurrentTheme.BidScore.display(0, bid%10);

		//CurrentTheme.BidScore.show(1, bid%100/10);
		//CurrentTheme.BidScore.show(0, bid%10);
	}

	if (bid <= 50)
	{
		//CurrentTheme.BidScore.hideAll();
		//CurrentTheme.BidScore.setDigit(0, 0);
		//CurrentTheme.BidScore.setDigit(1, 5);
		//CurrentTheme.BidScore.setDigit(2, 0);
		CurrentTheme.BidScore.setValue(50);
		/*hide(0, CurrentTheme.BidScore.getDigit(0));
		CurrentTheme.BidScore.hide(1, CurrentTheme.BidScore.getDigit(1));
		CurrentTheme.BidScore.hide(2, CurrentTheme.BidScore.getDigit(2));*/
	}

	if (gameState >= MELDING)
	{
		if (gameState == PLAYING)
		{
			TrumpSymbol.pauseAnimation();
			TrumpSymbol.setAnimatedFrameTo((8 * trump) + 1);
		}

		if (!TrumpSymbol.isVisible())
		{
			TrumpSymbol.playAnimationFrames(5.0, true, (8 * trump) + 1, 8 * (trump + 1));
			TrumpSymbol.show();
		}
	}
	else if (gameState != ANIMATION)
		TrumpSymbol.hide();
}

void Theme::update(unsigned short state)
{
	switch (state)
	{
	case BIDDING:
		bool switchState = checkForBidWinner();
		updateBidding();
		updateBidBubbles();
		if (!switchState)
			doBids(turn);
	case MELDING:
		updateMeldProcess();
	case PLAYING:
		if ((count % 4 == 0) && foundLocation && (mouseDelay == 2))
		{
			for (short int i = JACK; i >= ACE; i--)
			{
				for (short int j = HEARTS; j <= SPADES; j++)
				{
					if (NewTrickGame->getNumOfCardsLeft(i, j) == 0)
					{
						for (int k = 0; k < 4; k++)
							AllPlayers[k]->setKnown(i , j, 0);
					}
				}
			}
		}
		break;
	}

	updateBottomLeft();
	updateTopLeft();
	updateTopRight();
}

unsigned short Theme::getBidWinner(void)
{
	unsigned int bidWinner = 0;
	unsigned int lastBid = 0;

	for (int i = 0; i < 4; i++)
	{
		if (AllPlayers[i]->getLastBid() > lastBid)
		{
			lastBid = AllPlayers[i]->getLastBid();
			bidWinner = i;
		}
	}

	return bidWinner;
}

void Theme::updateMeldProcess(void)
{
	for (int i = 0; i < 4; i++)
	{
		AllPlayers[i]->hideBidBubble();
		PastBids[i]->hideAll();
		BidBacks[i]->hide();
	}
	
	if (!meldCount)
	{
		HMeld->setValue(AllPlayers[EAST]->getPMeld() + AllPlayers[WEST].getPMeld());
		VMeld->setValue(AllPlayers[NORTH]->getPMeld() + AllPlayers[SOUTH].getPMeld());
	}
	    

	if (meldCount > 8)
		showFinalMeldText();
	else
		showMeld();
}

void Theme::showFinalMeldText(void)
{
	unsigned short bidWinner = getBidWinner();
	unsigned short trumpSuit = AllPlayers[bidWinner]->getStrongSuit();
	unsigned short cardsDisplayed = 0;
	
	Text BidTeamColor = Text();
	Text OppTeamColor = Text();
	unsigned short backAmount = 0;
	unsigned short oppMeldAmount = 0;
		
	if (((trumpSuit == 4) || (HMeld->getValue() < 20)) && (bidWinner % 2 == BLUE))
	{
		BidTeamColor.init("Blue");
		OppTeamColor.init("Red");
		backAmount = AllPlayers[bidWinner]->getLastBid();
		oppMeldAmount = VMeld->GetValue();
	}
	else if (((trumpSuit == 4) || (VMeld->getValue() < 20)) && (bidWinner % 2 == RED))
	{
		BidTeamColor.init("Blue");
		OppTeamColor.init("Red");
		backAmount = AllPlayers[bidWinner]->getLastBid();
		oppMeldAmount = VMeld->GetValue();
	}

	if (!agk::getPointerPressed() && !backAmount)
	{
		char buffer[256];
		char buffer2[64];

		//DemoEndBack.show();
                
        //hideAllText();

		switch(language)
		{
		case ENGLISH:
			sprintf(buffer, "%s Team took the bid\nand did not have\nthe minimum 20 meld points.\n%s Team goes back %d points\n", BidTeamColor.getString(), BidTeamColor.getString(), backAmount);

			if (oppMeldAmount > 20)
			{
				sprintf(buffer2, "\n%s Team has more than 20 points\n%s team scores %d points", OppTeamColor.getString(), OppTeamColor.getString(), oppMeldAmount);
				strcat(buffer, buffer2);
			}
			break;
/*
			case FRENCH:
				sprintf(buffer, "L'Équipe bleue a pris l'offre\net n'ont pas\nle minimum de %d points de fusioner", bid);

				if (vMeld >= 20)
				{
					sprintf(buffer2, "\nÉquipe rouge a plus de 20 points\nÉquipe marque %d points rouges", vMeld);
					strcat(buffer, buffer2);
				}
				break;
			case ITALIAN:
				sprintf(buffer, "Squadra blu ha preso l'offerta\ne non hanno\nil minimo di 20 punti si fondono");//need re-translation

				if (vMeld >= 20)
				{
					sprintf(buffer2, "\nSquadra rossa ha più di 20 puti\nPunteggi squadra rosso %d punti", vMeld);
					strcat(buffer, buffer2);
				}
				break;
			case GERMAN:
				sprintf(buffer, "Blaue team nahm das angebot\nund nicht die\nmindestens %d punkte verschmelzen", bid);

				if (vMeld >= 20)
				{
					sprintf(buffer2, "\nRote team hat mehr als 20 punkte\nRote team %d punkte", hMeld);
					strcat(buffer, buffer2);
				}
				break;
			case SPANISH:
				sprintf(buffer, "Equipo azul tomó la oferta\ny no tenia\nel minimo de %d puntos se fusionana", bid);

				if (vMeld >= 20)
				{
					sprintf(buffer2, "\nEquipo rojo tiene más de 20 puntos\nResultados del equipo rojo de %d puntos", vMeld);
					strcat(buffer, buffer2);
				}
				break;*/
		}

		MeldFail->init(buffer);
        MeldFail->show();
                
        TapScreen.position(MeldFail.getX(), MeldFail.getY() + 18.0f);
		TapScreen.show();
	}
	else
	{
		DemoEndBack.hide();
		MeldFail->hide();
		getMeldingComplete = true;
				
		for (int i = 0; i < 4; i++)
			AllPlayers[i]->hideMeldBubble();
	}
}

void Theme::showMeld(void)
{
	unsigned short bidWinner = getBidWinner();
	//unsigned short skipTo = 0;
	
	for (int i = 0; i < 4; i++)
		AllPlayers[i]->hideMeldBubble();
	
	switch (meldCount)
	{
	case 0:
		if (agk::getPointerPressed())
		{
			if (bidWinner % 2 == 0)
				meldCount = 3;
			else
				meldCount = 1;
			GameResult.hide();
			GameResult4.hide();
		}

		break; //else start with west
	case 1:
		if (HMeld->getValue() >= 20)
		{
			AllPlayers[WEST]->displayMeld();
			switch (language)
			{
			case ENGLISH:
				sprintf(cMeldAmount, "West has %d Meld Points", West.getPMeld());
				break;
			case FRENCH:
				sprintf(cMeldAmount, "Ouest a %d points de fusionner", West.getPMeld());
				break;
			case ITALIAN:
				sprintf(cMeldAmount, "Ovest ha %d punti si fondono", West.getPMeld());
				break;
			case GERMAN:
				sprintf(cMeldAmount, "Westen hat %d punkte verschmelzen", West.getPMeld());
				break;
			case SPANISH:
				sprintf(cMeldAmount, "Al oeste con %d puntos se funden", West.getPMeld());
				break;
			}
			if (bidWinner == WEST)
				skipTo = 9; //All Done, exit
			else if (bidWinner == EAST)
				skipTo = 2;
			else
				skipTo = 2;
		}
		else if ((NewGame.verticalMeld >= 20) && (bidWinner % 2 != 0))
		{//Red team has meld, and took bid
			if (bidWinner == SOUTH)
				skipTo = 3; //Send to North
			else if (bidWinner == NORTH)
				skipTo = 4; //Send to South
		}
		else
			skipTo = 9;
		break;
	case 2:
		if (NewGame.horizontalMeld >= 20)
		{
			cardsDisplayed = displayKnown(EAST);
			switch (language)
			{
			case ENGLISH:
				sprintf(cMeldAmount, "East has %d Meld Points", East.getPMeld());
				break;
			case FRENCH:
				sprintf(cMeldAmount, "Est a %d points de fusionner", East.getPMeld());
				break;
			case ITALIAN:
				sprintf(cMeldAmount, "Est ha %d punti si fondono", East.getPMeld());
				break;
			case GERMAN:
				sprintf(cMeldAmount, "Osten hat %d punkte verschmelzen", East.getPMeld());
				break;
			case SPANISH:
				sprintf(cMeldAmount, "Esta cuenta con %d puntos se funden", East.getPMeld());
				break;
			}
			if (bidWinner == EAST)
				skipTo = 9; //All Done, exit
			else if (bidWinner == WEST)
				skipTo = 1;
			else if ((NewGame.verticalMeld >= 20) && (bidWinner % 2 != 0))
			{//Red team has meld, and took bid
				if (bidWinner == SOUTH)
					skipTo = 3; //Send to North
				else if (bidWinner == NORTH)
					skipTo = 4; //Send to South
			}
			else //Red team took bit, and has less than 20 meld
				skipTo = 9;
		}
		else if ((NewGame.verticalMeld >= 20) && (bidWinner % 2 != 0))
		{//Red team has meld, and took bid
			if (bidWinner == SOUTH)
				skipTo = 3; //Send to North
			else if (bidWinner == NORTH)
				skipTo = 4; //Send to South
		}
		else
			skipTo = 9;
		break;
	case 3:
		if (NewGame.verticalMeld >= 20)
		{
			cardsDisplayed = displayKnown(NORTH);
			switch (language)
			{
			case ENGLISH:
				sprintf(cMeldAmount, "North has %d Meld Points", North.getPMeld());
				break;
			case FRENCH:
				sprintf(cMeldAmount, "Nord a %d points de fusionner", North.getPMeld());
				break;
			case ITALIAN:
				sprintf(cMeldAmount, "Nord ha %d punti si fondono", North.getPMeld());
				break;
			case GERMAN:
				sprintf(cMeldAmount, "Norden hat %d punkte verschmelzen", North.getPMeld());
				break;
			case SPANISH:
				sprintf(cMeldAmount, "Norte cuenta con %d puntos se funden", North.getPMeld());
				break;
			}
			if (bidWinner == NORTH)
				skipTo = 9; //All Done, exit
			else if (bidWinner == SOUTH)
				skipTo = 4;
			else
				skipTo = 4;
		}
		else if ((NewGame.horizontalMeld >= 20) && (bidWinner % 2 != 1))
		{//Red team has meld, and took bid
			if (bidWinner == WEST)
				skipTo = 2; //Send to East
			else if (bidWinner == EAST)
				skipTo = 1; //Send to West
		}
		else
			skipTo = 9;
		break;
	case 4:
		if (NewGame.verticalMeld >= 20)
		{
			cardsDisplayed = displayKnown(SOUTH);
			switch (language)
			{
			case ENGLISH:
				sprintf(cMeldAmount, "You have %d Meld Points", South.getPMeld());
				break;
			case FRENCH:
				sprintf(cMeldAmount, "Vous avez %d points de fusionner", South.getPMeld());
				break;
			case ITALIAN:
				sprintf(cMeldAmount, "Avete %d punti si fondono", South.getPMeld());
				break;
			case GERMAN:
				sprintf(cMeldAmount, "Sie haben %d punkte verschmelzen", South.getPMeld());
				break;
			case SPANISH:
				sprintf(cMeldAmount, "Usted tiene %d puntos se funden", South.getPMeld());
				break;
			}
			if (bidWinner == SOUTH)
				skipTo = 9; //All Done, exit
			else if (bidWinner == NORTH)
				skipTo = 3;
			else if ((NewGame.horizontalMeld >= 20) && (bidWinner % 2 != 1))
			{//Red team has meld, and took bid
				if (bidWinner == WEST)
					skipTo = 2; //Send to East
				else if (bidWinner == EAST)
					skipTo = 1; //Send to West
			}
			else
				skipTo = 9;
		}
		else if ((NewGame.horizontalMeld >= 20) && (bidWinner % 2 != 1))
		{//Red team has meld, and took bid
			if (bidWinner == WEST)
				skipTo = 2; //Send to East
			else if (bidWinner == EAST)
				skipTo = 1; //Send to West
		}
		else
			skipTo = 9;
		break;
	default:
		break;
	}

	if (count && (count <= 4))
	{
		MeldAmount.position(50.0f, 66.0f);
		MeldAmount.changeText(cMeldAmount);
		MeldAmount.show();

		TapScreen.position(MeldAmount.getX(), MeldAmount.getY() + 5.0f);
		TapScreen.show();
	}

	if (mouseClick || !cardsDisplayed)
	{
		if ((mouseX >= (74.4f )) && (mouseX <= (98.0f )))
		{
				if ((mouseY >= 0.0f) && (mouseY <= (15.59f )))
					return;
		}

		CurrentTheme.Deck[0].sortVisualCards(West, North, East, South, CurrentTheme.Deck, -1, tableTopStyle);
		count = skipTo;
	}
}

void Theme::upateBidding(void)
{
	for (int i = 0; i < 4; i++)
	{
		BidBacks[i]->setVisible(true);

		if (playerBid(i))
			showPastBid(i);
		else
			hidePastBid(i);
	}
}

unsigned short Theme::getTurn(void)
{
	return turn;
}

bool Theme::updateBid(Theme *CurrentTheme)  //returns true if bid, false if not
{
	float x = 0.0f;
	float y = 0.0f;
	//bool passed = false;
	//short int round = (bidder - dealer - 1) / 4;
	//signed short int bid = NewBidGame.getBid();
	float offset = 0.0f;
	bool passed = false;
	
	if (turn == -1)
	{
		showBidBubble((dealer + 1)%4, -1);
		agk::Sync();

		return true;
	}

	if (!AllPlayers[turn]->getPass())
		showBidBubble(turn, -1);
	else
	{
		if (AllPlayers[turn]->getPassedThisRound())
		{
			showBidBubble(turn, -1);
			passed = true;
		}
		else
		{
			hideBidBubble(turn);
			return false;
		}
	}
	
	showBidBubble(turn%4, AllPlayers[turn]->getBid());
	
	return !passed;
}

bool Theme::checkForBidWinner(void)
{
	bool passed[4] = {false, false, false, false};
	unsigned short count = 0;

	for (int i = 0; i < 4; i++)
	{
		if (AllPlayers[i]->getPass())
		{
			passed[i] = true;
			count++;
		}
	}

	if (count == 3)
		return true;
	
	return false;
}

void Theme::doBids(short turn)
{
	for (int i = 0; i < 4; i++)
	{
		if (!arePastBidsEqual(i)) && (hasPlayerBid(i)))
		{
			PastBids[i]->incrementTo(AllPlayers[i]->getLastBid());
			return;
		}
	}

	for (int i = 0; i < 4; i++)
	{
		if (!hasPlayerBid(i))
		{
			PastBids[i]->setValue(Bid->getValue());
			PastBids[i]->hideAll();
		}
	}
	
	if (turn == -1)
	{
		turn = dealer;
		//pauseGame = true;
		turn++;
		//NewBidGame->setBidder(dealer + 1);
		//count++;
	}

	if (!NewBidGame->getBidDecided())  //winning bidder hasn't been determined
	{
		if (count < 4)
		{
			if (turn % 4 == WEST)
				NewBidGame.meldBid(&West, &East);
			else if (turn % 4 == NORTH)
				NewBidGame.meldBid(&North, &South);
			else if (turn % 4 == EAST)
				NewBidGame.meldBid(&East, &West);
			else	
				playerBid = southBid();
		}
		else
		{
			if ((turn % 4 == West.getID()) && (!NewBidGame.getPass(West.getID())))
				NewBidGame.takeBid(&West, &East, count/4);
			else if ((turn % 4 == North.getID()) && (!NewBidGame.getPass(North.getID())))
				NewBidGame.takeBid(&North, &South, count/4);
			else if ((turn % 4 == East.getID()) && (!NewBidGame.getPass(East.getID())))
				NewBidGame.takeBid(&East, &West, count/4);
			else if ((turn % 4 == South.getID()) && (!NewBidGame.getPass(South.getID())))
				playerBid = southBid();
		}

		CurrentTheme.BidMeldBubbles.hide();

		if ((turn % 4 != SOUTH) || (playerBid && !menuChoice) || ((NewBidGame.getPass(SOUTH) && (turn % 4 == SOUTH))))
		{
			pauseGame = CurrentTheme.BidMeldBubbles.updateBid(turn, dealer, NewBidGame, tableTopStyle);
			bid = NewBidGame.getBid();
			if (CurrentTheme.BidScore.getValue() < bid)
				incrementing = true;
			else if (pauseGame)
			{
				switch (turn%4)
				{
				case WEST:
					if (CurrentTheme.PastWestBid.getValue() < bid)
						incrementing = true;
					break;
				case NORTH:
					if (CurrentTheme.PastNorthBid.getValue() < bid)
						incrementing = true;
					break;
				case EAST:
					if (CurrentTheme.PastEastBid.getValue() < bid)
						incrementing = true;
					break;
				case SOUTH:
					if (CurrentTheme.PastSouthBid.getValue() < bid)
						incrementing = true;
					break;
				}
			}
			menuChoice = 0;

			switch (turn % 4)
			{
			case WEST:
				if (!NewBidGame.getPass(West.getID()))
				{
					West.setlastbid(bid);
					NewBidGame.setPlayerBid(WEST);
				}
				else if(NewBidGame.getPass(West.getID()))
				{//TODO: Put shrunk PASS image for each theme in
					/*CurrentTheme.PastWestBid.changeText("Pass");
					CurrentTheme.PastWestBid.size(1.7f);
					CurrentTheme.PastWestBid.position(7.0f,42.9f);
					CurrentTheme.PastWestBid.show();*/
				}
				break;
			case NORTH:
				if(!NewBidGame.getPass(North.getID()))
				{
					North.setlastbid(bid);
					NewBidGame.setPlayerBid(NORTH);
				}
				else if (NewBidGame.getPass(North.getID()))
				{//TODO: Put shrunk PASS image for each theme in
					//CurrentTheme.PastNorthBid.changeText("Pass");
					//CurrentTheme.PastNorthBid.size(1.7f);
					//CurrentTheme.PastNorthBid.position(43,10.5);
					//CurrentTheme.PastNorthBid.show();
				}
				break;
			case EAST:
				if(!NewBidGame.getPass(East.getID()))
				{
					East.setlastbid(bid);
					NewBidGame.setPlayerBid(EAST);
				}
				else if (NewBidGame.getPass(East.getID()))
				{//TODO: Put shrunk PASS image for each theme in
					/*CurrentTheme.PastEastBid.changeText("Pass");
					CurrentTheme.PastEastBid.position(82.8f,42.7f);
					CurrentTheme.PastEastBid.size(1.7f);
					CurrentTheme.PastEastBid.show();*/
				}
				break;
			case SOUTH:
				if (!NewBidGame.getPass(South.getID()))
				{
					South.setlastbid(bid);
					NewBidGame.setPlayerBid(SOUTH);
				}
				else
				{//TODO: Put shrunk PASS image for each theme in
				/*	CurrentTheme.PastSouthBid.changeText("Pass");
					CurrentTheme.PastSouthBid.size(1.7f);
					CurrentTheme.PastSouthBid.position(43.2f,61.5f);
					CurrentTheme.PastSouthBid.show();*/
				}

				CurrentTheme.BCBubble.hide();
				break;
			}

			turn++;
			count++;

		}

	}
	else
	{
		char temp[64];

		CurrentTheme.BidMeldBubbles.hide();

		switch (language)
		{
		case ENGLISH:
			switch(NewBidGame.getBidWinner())
			{
			case 0:
				strcpy(temp, "West");
				break;
			case 1:
				strcpy(temp, "North");
				break;
			case 2:
				strcpy(temp, "East");
				break;
			case 3:
				strcpy(temp, "You");
				break;
			}

			strcat(temp, " took the Bid at ");
			break;
		case FRENCH:
			switch(NewBidGame.getBidWinner())
			{
			case 0:
				strcpy(temp, "L'Ouest a");
				break;
			case 1:
				strcpy(temp, "Nord ont");
				break;
			case 2:
				strcpy(temp, "Est");
				break;
			case 3:
				strcpy(temp, "Vous avez");
				break;
			}
			
			strcat(temp, " pris l'enchère à ");
			break;
		case ITALIAN:
			switch(NewBidGame.getBidWinner())
			{
			case 0:
				strcpy(temp, "Ovest ha");
				break;
			case 1:
				strcpy(temp, "Nord ha");
				break;
			case 2:
				strcpy(temp, "Est ha");
				break;
			case 3:
				strcpy(temp, "Hai");
				break;
			}
			
			strcat(temp, " preso l'offert a ");
			break;
		case GERMAN:
			switch(NewBidGame.getBidWinner())
			{
			case 0:
				strcpy(temp, "Westen");
				break;
			case 1:
				strcpy(temp, "Norden");
				break;
			case 2:
				strcpy(temp, "Ost");
				break;
			case 3:
				strcpy(temp, "Sie");
				break;
			}
			
			strcat(temp, " nahm das Gebot bei ");
			break;
		case SPANISH:
			switch(NewBidGame.getBidWinner())
			{
			case 0:
				strcpy(temp, "Occidente");
				break;
			case 1:
				strcpy(temp, "Norte");
				break;
			case 2:
				strcpy(temp, "Este");
				break;
			case 3:
				strcpy(temp, "Que");
				break;
			}
			
			strcat(temp, " tomó la oferta a ");
			break;
		}

		if (NewBidGame.getBid() == 49)
		{
			NewBidGame.setBid(50);
			bid = 50;
		}
		else
			bid = NewBidGame.getBid();

		sprintf(num,"%d",bid);

		strcat(temp, num);

		gameResult.changeText(temp);
		gameResult.centerText();

		bidWinner = NewBidGame.getBidWinner();
		turn = bidWinner;

		if (turn == WEST)
			NewTrickGame.setTrumpSuit(West.getStrongSuit());
		else if (turn == NORTH)
			NewTrickGame.setTrumpSuit(North.getStrongSuit());
		else if (turn == EAST)
			NewTrickGame.setTrumpSuit(East.getStrongSuit());
		else
		{
			CurrentTheme.BidMeldBubbles.hide();

			if (South.getNumOfMarriages(HEARTS) + South.getNumOfMarriages(CLUBS) + South.getNumOfMarriages(DIAMONDS) + South.getNumOfMarriages(SPADES) != 0)
				southTrumpSelection();
			else
				NewTrickGame.setTrumpSuit(4);
		}

		count = 0;

		short int trumpSuit = NewTrickGame.getTrumpSuit();

		if (trumpSuit != -1)
		{
			NewGame.toggleXState(BIDDING);
			NewGame.toggleXState(MELDING);

			if (trumpSuit != 4)
			{
				for (short int i = 0; i < 20; i++)
					CurrentTheme.Deck[i+(trumpSuit*20)].outlineCard();

				NewGame.determineAmountToGet(&West, &North, &East, &South, NewTrickGame.getTrumpSuit(), NewBidGame.getBidder(), NewBidGame.getBid());

				CurrentTheme.TSBubble.hide();
			}

			switch (language)
			{
			case ENGLISH:
				switch (trumpSuit)
				{
				case 0: gameResult4.changeText("and Named Hearts as Trump"); break;
				case 1: gameResult4.changeText("and Named Clubs as Trump"); break;
				case 2: gameResult4.changeText("and Named Diamonds as Trump"); break;
				case 3: gameResult4.changeText("and Named Spades as Trump"); break;
				case 4:
					char buffer[64] = {NULL};
					sprintf(buffer, "and could not name trump.\nTeam loses %d points", bid);
					gameResult4.changeText(buffer);
					break;
				}
				break;
			case FRENCH:
				switch (trumpSuit)
				{
				case 0: gameResult4.changeText("coeurs et nommé commete atout"); break;
				case 1: gameResult4.changeText("clubs et nommé commete atout"); break;
				case 2: gameResult4.changeText("et a nommé les diamants commete atout"); break;
				case 3: gameResult4.changeText("et a nommé pique commete atout"); break;
				case 4:
					char buffer[64] = {NULL};
					sprintf(buffer, "et ne pouvais pas le nom trump.\nÉquipe perd %d points.", bid);
					gameResult4.changeText(buffer);
					break;
				}
				break;
			case ITALIAN:
				switch (trumpSuit)
				{
				case 0: gameResult4.changeText("e nominator cuori come vincente"); break;
				case 1: gameResult4.changeText("e nominator club come vincente"); break;
				case 2: gameResult4.changeText("e nominato diamanti come vincente"); break;
				case 3: gameResult4.changeText("e nominato come picche vincente"); break;
				case 4:
					char buffer[64] = {NULL};
					sprintf(buffer, "e non il nome trump.\nSquadra perde %d punti.", bid);
					gameResult4.changeText(buffer);
					break;
				}
				break;
			case GERMAN:
				switch (trumpSuit)
				{
				case 0: gameResult4.changeText("und herzen als trumpf namens"); break;
				case 1: gameResult4.changeText("und clubs als trumpf namens"); break;
				case 2: gameResult4.changeText("und nannte diamanten als trumpf"); break;
				case 3: gameResult4.changeText("und pik als trumpf namens"); break;
				case 4:
					char buffer[64] = {NULL};
					sprintf(buffer, "und nicht namen trumpf.\nTeam verliert %d punkte.", bid);
					gameResult4.changeText(buffer);
					break;
				}
				break;
			case SPANISH:
				switch (trumpSuit)
				{
				case 0: gameResult4.changeText("y el nombre corazones como triunfo"); break;
				case 1: gameResult4.changeText("y el nombre de los clubes de triunfo"); break;
				case 2: gameResult4.changeText("y el nombre de los diamantes de triunfo"); break;
				case 3: gameResult4.changeText("y el nombre espadas como triunfo"); break;
				case 4:
					char buffer[64] = {NULL};
					sprintf(buffer, "y noel nombre de triunfo.\nEquipo pierde %d puntos.", bid);
					gameResult4.changeText(buffer);
					break;
				}
				break;
			}
			gameResult.centerText();
			gameResult.show();
			gameResult4.centerText();
			gameResult4.show();
			TapScreen.position(gameResult4.getX(), gameResult4.getY() + 9.0f);
			TapScreen.show();
			//gameResult4.show();
		}
	}
}

void Theme::playGame(void)
{
	trump = NewTrickGame->getTrumpSuit();

	MeldAmount->setVisible(false);
	TapScreen->setVisible(false);

	if (count != 80)
	{

		if ((count % 4 == 0) && count && contFlag)
		{//trick is finished
			if (mouseClick)
			{
				TapScreen->setVisible(false);
				turn = NewTrickGame.getLead();
				foundLocation = CurrentTheme.Deck[cardPlayed[0]].updateShrinkCloseTrick(turn, &CurrentTheme.Deck[cardPlayed[1]], &CurrentTheme.Deck[cardPlayed[2]], &CurrentTheme.Deck[cardPlayed[3]]);
				wipingCards = true;
			}
			else if (wipingCards)
            {
				foundLocation = CurrentTheme.Deck[cardPlayed[0]].updateShrinkCloseTrick(turn, &CurrentTheme.Deck[cardPlayed[1]], &CurrentTheme.Deck[cardPlayed[2]], &CurrentTheme.Deck[cardPlayed[3]]);
                
                if (foundLocation)
                {
                    for (int i = 0; i < 4; i++)
                        cardPlayed[i] = -1;
                }
            }
			else
			{
				TapScreen.show();
				foundLocation = false;
			}
		}

		if (count)
		{
			if	(foundLocation)
				wipingCards = false;
			else
				return;
		}

		if ((foundLocation || !count) && !wipingCards)
		{
			hTricks = NewTrickGame.getHTricks();
			vTricks = NewTrickGame.getVTricks();
			if (turn == WEST)
			{
				//sortVisualCards(South, CurrentTheme.Deck, count/4);
				cardPlayed[count%4] = NewTrickGame.playCard(&West, North, East, South, count);
				West.sortHand();
				CurrentTheme.Deck[0].sortVisualCards(West, CurrentTheme.Deck, tableTopStyle);


			}
			else if (turn == NORTH)
			{
				//sortVisualCards(South, CurrentTheme.Deck, count/4);
				cardPlayed[count%4] = NewTrickGame.playCard(&North, East, South, West, count);
				North.sortHand();
				CurrentTheme.Deck[0].sortVisualCards(North, CurrentTheme.Deck, tableTopStyle);

			}
			else if (turn == EAST)
			{
				//sortVisualCards(South, CurrentTheme.Deck, count/4);
				cardPlayed[count%4] = NewTrickGame.playCard(&East, South, West, North, count);
				East.sortHand();
				CurrentTheme.Deck[0].sortVisualCards(East, CurrentTheme.Deck, tableTopStyle);
			}
			else if (turn == SOUTH)
			{
				SwipeHelp.show();
				contFlag = false;
				//sortVisualCards(South, CurrentTheme.Deck);
				playOneTime = true;
				if((strcmp(agk::GetDeviceName(), "windows") == 0) || (strcmp(agk::GetDeviceName(), "osx"))==0)
				{
					cardPlayed[count%4] = CurrentTheme.Deck[0].updateCardPos(CurrentTheme.Deck, South, NewTrickGame.getTopSuit(), NewTrickGame.getTopRank(), NewTrickGame.getLeadSuit(), NewTrickGame.getTrumpSuit(), count);
					//mClick=mouseClick;
				}
				else
				{
                    if(agk::GetPointerState())
                    {
                        if (!hold)
						{
							ystartpos=agk::GetPointerY();
                            hold = true;
                        }
                        else
                        {
                            if (agk::GetPointerY() <= ystartpos - 5.0f)
                            {
                                swipe = true;
                                hold = false;
                            }
                        }
                            
                        if (!swipe)
								cardPlayed[count%4] = CurrentTheme.Deck[0].updateCardPos(CurrentTheme.Deck, South, NewTrickGame.getTopSuit(), NewTrickGame.getTopRank(), NewTrickGame.getLeadSuit(), NewTrickGame.getTrumpSuit(), count);
                            
					}
                }
#if (OS == WINDOWS)
				if (mouseClick && (cardPlayed[count%4] != -1))
#else
				if (swipe && (cardPlayed[count%4] != -1))
#endif
				{
					if ((!NewTrickGame.getTricksPlayed()) && (bidWinner == SOUTH))
						NewTrickGame.setLead(SOUTH);

					if (turn == SOUTH)
						SwipeHelp.hide();

					NewTrickGame.playCard(&South, West, North, East, count, cardPlayed[count%4]);
					count++;
					South.sortHand();
					CurrentTheme.Deck[0].sortVisualCards(South, CurrentTheme.Deck, tableTopStyle);

					NewGame.toggleXState(ANIMATION);
					playingAnimation = true;
					contFlag = true;
					playOneTime = false;
                    swipe = false;
				}
			}

			if (turn != SOUTH)
			{
				NewGame.toggleXState(ANIMATION);
				playingAnimation = true;
				count++;
				playOneTime = false;
			}

			if (ShuffledDeck.getSuit(cardPlayed[(count-1)%4]) == NewTrickGame.getTrumpSuit())
			{
				if (NewTrickGame.getLead() == turn)
				{
					if (NewTrickGame.getLeadSuit() != trump)
					{
						if (!playOneTime)
						{
							if (soundOn)
							{
								switch (ShuffledDeck.getRank(cardPlayed[(count-1)%4]))
								{
								case ACE:
									Trump[ACE].playOnce();
									break;
								case TEN:
									Trump[TEN].playOnce();
									break;
								case KING:
									Trump[KING].playOnce();
									break;
								case QUEEN:
									Trump[QUEEN].playOnce();
									break;
								case JACK:
									Trump[JACK].playOnce();
									break;
								}
							}

							playOneTime = true;
						}
					}
				}
			}
		}
	}
	else
	{
		if (mouseClick)
		{
			NewGame.toggleXState(PLAYING);
			NewGame.toggleXState(SCOREBOARD);
		}
		else
			TapScreen.show();
	}

}

void Theme::hideAllHScores(void)
{
	HScore->hideAll();
}

void Theme::hideAllVScores(void)
{
	VScore->hideAll();
}

void Theme::hideBidBubbles(void)
{
	AllPlayers[turn]->hideBidBubble();
}
		
void Theme::hideMeldBubbles(void)
{
	AllPlayers[turn]->hideMeldBubble();
}

void Theme::resetGame(void)
{
	HScore->setValue(0);
	VScore->setValue(0);

	for (int i = 0; i < 4; i++)
		AllPlayers[i]->reset();

	resetHand();
}

void Theme::resetHand(void)
{
	AllCards->shuffle();

	Bid->setValue(49);
	BidScore->setValue(49);
	H2Get->setValue(0);
	HMeld->setValue(0);
	HScore->setValue(0);
	
	for (int i = 0; i < 4; i++)
		PastBids[i]->setValue(0);

	V2Get->setValue(0);
	VMeld->setValue(0);
}

void Theme::shrinkBackground(void)
{
	Background->setSize(Background->getSize() - 1.0f);
}

bool Theme::start(unsigned int dealer)
{
	Point DealerLocation = Point();

	if (!hasGrown())
	{
		growBackground();
		return;
	}

	BCBubble->setValue(51);
	//BCBubble->hideAll();
	
	BidScore->setValue(50);
	BidScore->showAll();
	
	/*
	CurrentTheme.PastEastBid.hideAll();
	CurrentTheme.PastNorthBid.hideAll();
	CurrentTheme.PastWestBid.hideAll();
	CurrentTheme.PastSouthBid.hideAll();
	*/

	//VisualBid = 255;

	NewBidGame.setDealer(dealer);

	dealerOffset[0] = 0;
	dealerOffset[1] = 0;

	if (dealer == SOUTH)
		dealerOffset[1] = 200;
	else if (dealer == WEST)
		dealerOffset[0] = -200;
	else if (dealer == NORTH)
		dealerOffset[1] = -200;
	else
		dealerOffset[0] = 200;

	for(short int i = 0; i < 80; i++)
	{
		//if (CurrentTheme.Deck[i].hasShrunk())
		//CurrentTheme.Deck[i].setSize(15.0f);
		//CurrentTheme.Deck[i].offset(3.125f, 3.25f);
		CurrentTheme.Deck[i].unRotate();
		CurrentTheme.Deck[i].display(50 + dealerOffset[0], 50 + dealerOffset[1]);
		CurrentTheme.Deck[i].turnFaceDown();
		CurrentTheme.Deck[i].show();
		CurrentTheme.Deck[i].unOutlineCard();
	}
}

void Theme::sortHands(void)
{
	AllCards->sortAllCards();
	
	for (int i = 0; i < 4; i++)
		AllPlayers[i]->tabulateMeld();
}

unsigned short Theme::getBidValue(void)
{
	return Bid->getValue();
}

unsigned short Theme::getPastBid(unsigned int player)
{
	return PastBids[player]->getValue();
}

bool Theme::arePastBidsEqual(unsigned int player)
{
	return (PastBids[player]->getValue() == AllPlayers[player]->getlastbid());
}

bool Theme::hasPlayerBid(unsigned int player)
{
	return AllPlayers[players]->hasBid();
}

//in theme due to bid control bubble being in theme
void Theme::playerMeldBid(unsigned short newBid)
{
	//if (Bid->getValue() == 49)
	//	bid++;

	if ((AllPlayers[WEST]->getPass() && AllPlayers[EAST]->getPass()) && (newBid != Bid->getValue()))
	{
		AllPlayers[SOUTH]->toggleSaveBid();
		AllPlayers[SOUTH]->setMeldBid(0);
		
		Bid->incrementTo(newBid);
		//setBidder(South->getID());
	}
	else if ((newBid > 49) && (newBid < 60))
	{
		AllPlayers[SOUTH]->setMeldBid(newBid - Bid->getValue());
		Bid->incrementTo(newBid);
		//setBidder(South->getID());
		
		if (newBid == 50)
		{
			AllPlayers[SOUTH]->incrementNumOfBids();
			AllPlayers[SOUTH]->incrementNumOfBids();
			AllPlayers[SOUTH]->incrementNumOfBids(); //increment to 7 or 8 for run size
		}
	}
	else if (newBid >= 60)
	{
		if (Bid->getValue() < 59)
		{
			AllPlayers[SOUTH]->incrementNumOfBids();
			AllPlayers[SOUTH]->incrementNumOfBids();
			AllPlayers[SOUTH]->incrementNumOfBids(); //increment to 7 or 8 for run size
		}
		else
			AllPlayers[SOUTH]->incrementNumOfBids();

		Bid->incrementTo(newBid());
		AllPlayers[SOUTH]->setMeldBid(0);
		//setBidder(South->getID());
	}
	else
	{
		AllPlayers[SOUTH]->togglePass();
		AllPlayers[SOUTH]->setMeldBid(0);
	}
}

void Theme::playerTakeBid(short int round, unsigned short int newBid)
{
	if (newBid > 49)
	{
		if (AllPlayers[NORTH]->getPass())  //if Partner has NOT passed
		{
			if (AllPlayers[NORTH]->getNumOfBids() == 0) //partner has only meld bidded (or passed)
			{
				if (AllPlayers[EAST]->getPass())//see if he needs to be saved
				{
					AllPlayers[SOUTH]->toggleSaveBid();
				}
			}
		}
		AllPlayers[SOUTH]->incrementNumOfBids();
		Bid->incrementTo(newBid);
		//setBidder(SOUTH);
		return;
	}
	else
		AllPlayers[SOUTH]->setPass(round);
}