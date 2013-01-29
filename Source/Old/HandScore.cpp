#include "HandScore.h"
#include "agk.h"

HandScore::HandScore(void)
{

}


HandScore::~HandScore(void)
{
}

void HandScore::init(AnimatedSprite *Symbol)
{
	Text TempFileName = Text();
	unsigned int parentImage = 0;
    float hOffset;
    float vOffset;

	TempFileName.init("default/Scoreboards.png");
	///step 1: setup or setData
	ParentImage.parentInit(TempFileName);
	parentImage = ParentImage.getImageNumber();

	TempFileName.setString("board table.png");
	Background->subInit(parentImage, TempFileName);
	setNumberData();
    
	TempFileName.setString("check_box_off.png");
	HCheckOff->subInit(parentImage, TempFileName);
	VCheckOff->subInit(parentImage, TempFileName);
	
	TempFileName.setString("check_box_on.png");
	HCheckOn->subInit(parentImage, TempFileName);
    VCheckOn->subInit(parentImage, TempFileName);
	
	///step 2: setSize
	HCheckOff->setSize(5.0f);
	HCheckOn->setSize(5.0f);
	VCheckOff->setSize(5.0f);
	VCheckOn->setSize(5.0f);
	Background->setSize(80.0f);

	setDepth(9950);

	///step 4: set x, y with display
#if (PLATFORM == MOBILE)
    hOffset = 4.5f;
    vOffset = 3.5f;
#else
    hOffset = 0.0f;
    vOffset = 0.0f;
#endif
    
	Background->setPosition(10.0f, 25.0f);
	HCheckOff->setPosition(66.0f, 60.0f + hOffset);
	HCheckOn->setPosition(66.0f, 60.0f + hOffset);
	VCheckOff->setPosition(66.0f, 51.0f + vOffset);
	VCheckOn->setPosition(66.0f, 51.0f + vOffset);

	///step 5: hide
	HCheckOff->setVisible(false);
	HCheckOn->setVisible(false);
	VCheckOff->setVisible(false);
	VCheckOn->setVisible(false);

	///step 6 (optional): setimprint

	/////TEXT


	/*MinusSign[1].createT("-");
	MinusSign[1].color(0, 0, 0);
	MinusSign[1].size(5.5f);
	MinusSign[1].setDepth(55);
	MinusSign[1].hide();

	MinusSign[0].position(76.5f, 51.5f);
	MinusSign[1].position(76.5f, 60.5f);*/
}

void HandScore::update(unsigned short bidValue, bool meldFail, unsigned short bidWinner)
{
	bool meldFail = false;
	//turn = NewTrickGame.getLead();
	//ingamebutton=false;

	unsigned short bid = bidValue;

	if (bid == 49)
		bid = 50;

	//if (turn == -1)
	//	meldFail = true;

	if (!calcOnce && !meldFail)
	{
		/*if (bidWinner % 2 == 0)
			NewTrickGame.lastTrick(BLUE);
		else
			NewTrickGame.lastTrick(RED);*/

		hTricks = NewTrickGame.getHTricks();
		vTricks = NewTrickGame.getVTricks();
        
		HandResults->checkForSaves(NewTrickGame->getHTricks(), NewTrickGame->getVTricks(), bidWinner, bid);

		calcOnce = true;
	}
	else if (meldFail && !calcOnce)
	{
		if (bidWinner % 2 == BLUE)
		{
			if (vMeld >= 20)
				NewGame.addToScore(RED, vMeld);
		}
		else
		{
			if (hMeld >= 20)
				NewGame.addToScore(BLUE, hMeld);
		}
        
        NewGame.addToScore(bidWinner % 2, -bid);
		calcOnce = true;
	}

	//CurrentTheme.HScore.incrementTo(abs(NewGame.getScore(0)));
	//CurrentTheme.VScore.incrementTo(abs(NewGame.getScore(1)));

	if (!mouseClick && (visScreen == 0))
	{
		if (vMeld < 20)
			vMeld = 0;
		if (hMeld < 20)
			hMeld = 0;

		short int vTrickScore;
		short int hTrickScore;

		if (vTricks < 20)
			vTrickScore = 0;
		else
			vTrickScore = vTricks;

		if (hTricks < 20)
			hTrickScore = 0;
		else
			hTrickScore = hTricks;

		HandResults.HandScoreData[0][0].showAll();

		if (bidWinner % 2 == RED)
		{
			if (HandResults.HandScoreData[0][3].getValue() != bid)
            {
				HandResults.HandScoreData[0][3].incrementTo(bid); //TODO: change to 4 when new scoreboard in
                PointClick.playOnce();
            }

			HandResults.HandScoreData[1][3].hideAll();

			if (CurrentTheme.V2Get.getValue() == 0)
			{
				if (HandResults.HandScoreData[0][0].getValue() != (vMeld + vTrickScore))
                {
					HandResults.HandScoreData[0][0].incrementTo(vMeld + vTrickScore);
                    PointClick.playOnce();
                }

				HandResults.VCheckOn.show();
			}
			else
			{
				if (HandResults.HandScoreData[0][0].getValue() != -bid)
                {
					HandResults.HandScoreData[0][0].incrementTo(-bid);
                    PointClick.playOnce();
                }

				HandResults.VCheck.show();
			}
			if ((CurrentTheme.H2Get.getValue() == 0) || meldFail)
			{
				if (HandResults.HandScoreData[1][0].getValue() != (hMeld + hTrickScore))
                {
					HandResults.HandScoreData[1][0].incrementTo(hMeld + hTrickScore);
                    PointClick.playOnce();
                }

				HandResults.HCheckOn.show();
			}
			else
			{
				HandResults.HandScoreData[1][0].incrementTo(0, true);

				HandResults.HCheck.show();
			}
		}
		else
		{
			if (HandResults.HandScoreData[1][3].getValue() != bid)
            {
				HandResults.HandScoreData[1][3].incrementTo(bid); //TODO: change to 4 when new scoreboard in
                PointClick.playOnce();
            }

			HandResults.HandScoreData[0][3].hideAll();

			if (CurrentTheme.H2Get.getValue() == 0)
			{
				if (HandResults.HandScoreData[1][0].getValue() != (hMeld + hTrickScore))
                {
					HandResults.HandScoreData[1][0].incrementTo(hMeld + hTrickScore);
                    PointClick.playOnce();
                }

				HandResults.HCheckOn.show();
			}
			else
			{
				if (HandResults.HandScoreData[1][0].getValue() != -bid)
                {
					HandResults.HandScoreData[1][0].incrementTo(-bid);
                    PointClick.playOnce();
                }

				HandResults.HCheck.show();
			}

			if ((CurrentTheme.V2Get.getValue() == 0) || meldFail)
			{
				if (HandResults.HandScoreData[0][0].getValue() != (vMeld + vTrickScore))
                {
					HandResults.HandScoreData[0][0].incrementTo(vMeld + vTrickScore);
                    PointClick.playOnce();
                }

				HandResults.VCheckOn.show();
			}
			else
			{
				HandResults.HandScoreData[0][0].incrementTo(0, true);

				HandResults.VCheck.show();
			}
		}

		if (HandResults.HandScoreData[0][2].getValue() != vMeld)
        {
            HandResults.HandScoreData[0][2].incrementTo(vMeld, true);
            PointClick.playOnce();
        }
		if (HandResults.HandScoreData[1][2].getValue() != hMeld)
        {
            HandResults.HandScoreData[1][2].incrementTo(hMeld, true);
            PointClick.playOnce();
        }
		if (HandResults.HandScoreData[0][1].getValue() != NewTrickGame.getVTricks())
        {
            HandResults.HandScoreData[0][1].incrementTo(NewTrickGame.getVTricks(), true);
            PointClick.playOnce();
        }
		if (HandResults.HandScoreData[1][1].getValue() != NewTrickGame.getHTricks())
        {
            HandResults.HandScoreData[1][1].incrementTo(NewTrickGame.getHTricks(), true);
            PointClick.playOnce();
        }

		for (int i = 0; i < 80; i++)
			CurrentTheme.Deck[i].hide();

		HandResults.Background.show();
		//HandResults.Background.setPriority(50);
#if (PLATFORM == MOBILE)
		TapScreen.position(TapScreen.getX() + 5.0f, 70.0f);
#else
        TapScreen.position(TapScreen.getX(), 70.0f);
#endif
		TapScreen.show();
	}
	else if ((visScreen == 1) && !mouseClick)
	{
		TapScreen.position(50.0f, 10.0f);
		TapScreen.show();

		HandResults.hide();

		GameResults.Background.show();
		GameResults.Background.setAlpha(255);
		GameResults.Header.show();

		if (hand > 0)
		{
			if (!copyOnce)
			{
				if (hand > 10)
				{
					for (short int i = 0; i < 10; i++)
					{
						GameResults.GameScoreData[i][0].hideAll();
						GameResults.GameScoreData[i][1].hideAll();
						GameResults.GameScoreData[i][2].hideAll();
						GameResults.GameScoreData[i][0].setValue(GameResults.GameScoreData[i+1][0].getValue());
						GameResults.GameScoreData[i][1].setValue(GameResults.GameScoreData[i+1][1].getValue());
						GameResults.GameScoreData[i][2].setValue(GameResults.GameScoreData[i+1][2].getValue());
						copyOnce = true;
					}

					GameResults.GameScoreData[10][0].setValue(0);
					GameResults.GameScoreData[10][1].setValue(0);
				}
				/*else
				{
					GameResults.MiddleSection[hand].display(GameResults.MiddleSection[hand-1].getX(), GameResults.MiddleSection[hand-1].getY() + (5.0f * (hand)));
					copyOnce = true;
				}*/
			}
		}

		for (short int i = 0; i < hand + 1; i++)
		{
			if (i > 10)
				break;

			GameResults.MiddleSection[i].show();
		}

		GameResults.Total.show();

		short int temphand = hand;

		if (temphand > 10)
			temphand = 10;

		hTricks = NewTrickGame.getHTricks();
		if (hTricks < 20)
			hTricks = 0;

		vTricks = NewTrickGame.getVTricks();
		if (vTricks < 20)
			vTricks = 0;

		//hMeld = NewGame.horizontalMeld;
		//vMeld = NewGame.verticalMeld;

		if (hMeld < 20)
			hMeld = 0;
		if (vMeld < 20)
			vMeld = 0;

		if (bidWinner % 2 == BLUE)
		{
			if (CurrentTheme.H2Get.getValue() == 0)
			{
				if (GameResults.GameScoreData[temphand][0].getValue() != (hMeld + hTricks))
                {
					GameResults.GameScoreData[temphand][0].incrementTo(hMeld + hTricks);
                    PointClick.playOnce();
                }
			}
			else
			{
				if (GameResults.GameScoreData[temphand][0].getValue() != -bid)
                {
					GameResults.GameScoreData[temphand][0].incrementTo(-bid); //need to make this negative somehow!
                    PointClick.playOnce();
                }
			}

			if ((CurrentTheme.V2Get.getValue() == 0) || (meldFail && vMeld))
			{
				if (GameResults.GameScoreData[temphand][1].getValue() != (vMeld + vTricks))
                {
					GameResults.GameScoreData[temphand][1].incrementTo(vMeld + vTricks);
                    PointClick.playOnce();
                }
			}
			else
			{
				GameResults.GameScoreData[temphand][1].incrementTo(0, true);
			}
		}
		else
		{
			if ((CurrentTheme.H2Get.getValue() == 0) || (meldFail && hMeld))
			{
				if (GameResults.GameScoreData[temphand][0].getValue() != (hMeld + hTricks))
                {
					GameResults.GameScoreData[temphand][0].incrementTo(hMeld + hTricks);
                    PointClick.playOnce();
                }
			}
			else
			{
				GameResults.GameScoreData[temphand][0].incrementTo(0, true);
			}

			if (CurrentTheme.V2Get.getValue() == 0)
			{
				if (GameResults.GameScoreData[temphand][1].getValue() != (vMeld + vTricks))
                {
					GameResults.GameScoreData[temphand][1].incrementTo(vMeld + vTricks);
                    PointClick.playOnce();
                }
			}
			else
			{
				if (GameResults.GameScoreData[temphand][1].getValue() != -bid)
                {
					GameResults.GameScoreData[temphand][1].incrementTo(-bid); //need to make this negative
                    PointClick.playOnce();
                }
			}
		}

		GameResults.GameScoreData[temphand][2].hideAll();
		GameResults.GameScoreData[temphand][2].setValue(hand+1);

		for (short int g = 0; g < hand; g++)
		{
			for (short int h = 0; h < 3; h++)
				GameResults.GameScoreData[g][h].showAll(true);
		}

        if (GameResults.GameScoreData[11][0].getValue() != hScore)
        {
            GameResults.GameScoreData[11][0].incrementTo(NewGame.getScore(BLUE), true);
            PointClick.playOnce();
        }
        
        if (GameResults.GameScoreData[11][1].getValue() != vScore)
        {
            GameResults.GameScoreData[11][1].incrementTo(NewGame.getScore(RED), true);
            PointClick.playOnce();
        }

		GameResults.GameScoreData[11][0].showAll(true);
		GameResults.GameScoreData[11][1].showAll(true);
		GameResults.GameScoreData[11][2].hideAll();

		if ((NewGame.getScore(0) >= 500) || (NewGame.getScore(1) >= 500))
		{
			GameOver.position(50.0f, 89.0f);
			if ((NewGame.getScore(0) >= 500) && (NewGame.getScore(1) < 500))
				GameOver.changeText("Blue Team Wins!");
			else if ((NewGame.getScore(1) >= 500) && (NewGame.getScore(0) < 500))
				GameOver.changeText("Red Team Wins!");
			else
			{
				if (bidWinner % 2)
					GameOver.changeText("Red Team Wins!");
				else
					GameOver.changeText("Blue Team Wins!");
			}
			GameOver.incrementColor();
			GameOver.show();
		}
	}
	else if (visScreen == 3)
	{
		GameResults.hide();
		TapScreen.hide();

		if ((NewGame.getScore(0) < 500) && (NewGame.getScore(1) < 500))
		{
			resetHand();
			NewGame.toggleXState(SCOREBOARD);
			NewGame.toggleXState(START);
			calcOnce = false;
			visScreen = 0;
			copyOnce = false;
		}
		else
			visScreen++;
	}
	else if (visScreen == 4)
	{
		//So and so Wins!
		resetGame();
		CurrentTheme.hide();

		hScore = 0;
		vScore = 0;
		visScreen = 0;
		hand = 0;
		delayStep = 0;
		calcOnce = false;
		copyOnce = false;

		GameResults.hide();

		CurrentTheme.Background.updateShrinkClose(-2);
        
        NewGame.toggleXState(SCOREBOARD);
		NewGame.toggleXState(MENU);
	}
	else
		visScreen++;
}

void HandScore::setNumberData(void)
{
    float hOffset = 0.0f;
    float vOffset = 0.0f;
    float mOffset = 0.0f;
    
	for (short int i = 0; i < 2; i++)
	{
		for (short int j = 0; j < 4; j++)
			HandScoreData[i][j]->initDefaultNumbers();
	}
    
#if (PLATFORM == MOBILE)
    hOffset = 4.5f;
    vOffset = 3.5f;
    mOffset = -1.0f;
#endif

	for (short int i = 0; i < 3; i++)
	{
		for (short int k = 0; k < 5; k++)
		{
			if (k == 1)
				continue;
			if (k > 1)
			{
				HandScoreData[0][k-1]->setLocation(i, 83.0f - ((2.5f * i) + (k * 12.6f)), 52.0f + vOffset, -4.5f, -0.5f + mOffset);
				HandScoreData[1][k-1]->setLocation(i, 83.0f - ((2.5f * i) + (k * 12.6f)), 61.0f + hOffset, -4.5f, -0.5f + mOffset);
			}
			else
			{
				HandScoreData[0][k]->setLocation(i, 83.0f - ((2.5f * i) + (k * 12.6f)), 52.0f + vOffset, -4.5f, -0.5f + mOffset);
				HandScoreData[1][k]->setLocation(i, 83.0f - ((2.5f * i) + (k * 12.6f)), 61.0f + hOffset, -4.5f, -0.5f + mOffset);
			}
		}
	}

	for (short int k = 0; k < 4; k++)
	{
		HandScoreData[0][k]->setDepth(9948);
		HandScoreData[1][k]->setDepth(9948);
		HandScoreData[0][k]->setSize(2.5f);
		HandScoreData[1][k]->setSize(2.5f);
		HandScoreData[0][k]->setValue(0);
		HandScoreData[1][k]->setValue(0);
		HandScoreData[0][k]->hideAll();
		HandScoreData[1][k]->hideAll();
	}
}

void HandScore::hide(void)
{
	Background->setVisible(false);
	for (short int i = 0; i < 2; i++)
	{
		for (short int j = 0; j < 4; j++)
			HandScoreData[i][j]->hideAll();
	}

	HCheckOff->setVisible(false);
	HCheckOn->setVisible(false);
	VCheckOff->setVisible(false);
	VCheckOn->setVisible(false);
}

void HandScore::setDepth(short unsigned int value)
{
	Background->setDepth(value);

	HCheckOff->setDepth(value - 1);
	HCheckOn->setDepth(value - 1);
	VCheckOff->setDepth(value - 1);
	VCheckOn->setDepth(value - 1);

	for (short i = 0; i < 2; i++)
	{
		for (short j = 0; j < 4; j++)
			HandScoreData[i][j]->setDepth(value - 1);
	}
}

void HandScore::reset(void)
{
	for (short int i = 0; i < 2; i++)
	{
		for (short int j = 0; j < 4; j++)
			HandScoreData[i][j]->setValue(0);
	}
}

//////////From PinochleGame.cpp
unsigned short int HandScore::getAmountToSave(short int team)
{
	if (team == 0)
		return hAmountToGet;
	else
		return vAmountToGet;
}

void HandScore::determineAmountToGet(Player *AllPlayers[4], short int trump, short int bidWinner, unsigned short int bid)
{
	horizontalMeld = AllPlayers[WEST]->determineNewMeld(trump);
	horizontalMeld += AllPlayers[EAST]->determineNewMeld(trump);
	verticalMeld = AllPlayers[NORTH]->determineNewMeld(trump);
	verticalMeld += AllPlayers[SOUTH]->determineNewMeld(trump);

	if (horizontalMeld < 20)
	{
		horizontalMeld = 0;
		AllPlayers[WEST]->resetKnown();
		AllPlayers[EAST]->resetKnown();
	}
	if (verticalMeld < 20)
	{
		AllPlayers[NORTH]->resetKnown();
		AllPlayers[SOUTH]->resetKnown();
		verticalMeld = 0;
	}

	if((bidWinner == WEST) || (bidWinner == EAST))
	{
		if (bid - horizontalMeld < 20)
			hAmountToGet = 20;
		/*else if (horizontalMeld < 20) don't need to do this at all
		{
			//addToScore(BLUE, -bid); //ALREADY DOING THIS
			if (verticalMeld >= 20)
				addToScore(RED, verticalMeld);
		}*/
		else
			hAmountToGet = bid - horizontalMeld;

		vAmountToGet = 20;
	}
	else if((bidWinner == NORTH) || (bidWinner == SOUTH))
	{
		if (bid - verticalMeld < 20)
			vAmountToGet = 20;
		/*else if (verticalMeld < 20)
		{
			//addToScore(RED, -bid); //ALREADY DOING THIS
			if (horizontalMeld >= 20)
				addToScore(BLUE, horizontalMeld);
		}*/
		else
			vAmountToGet = bid - verticalMeld;

		hAmountToGet = 20;
	}

}

void HandScore::checkForSaves(unsigned short hTricks, unsigned short vTricks, short int bidWinnerID, unsigned short int finalBid)
{
	short int saveH = getAmountToSave(RED);
	short int saveV = getAmountToSave(BLUE);

	if (saveH >= 0)
		addToHandScore(BLUE, hTricks + horizontalMeld);
	else
	{
		if (bidWinnerID % 2 == BLUE)
			addToHandScore(BLUE, -finalBid); 
	}

	if (saveV >= 0)
		addToHandScore(RED, vTricks + verticalMeld);
	else
	{
		if (bidWinnerID % 2 == RED)
			addToHandScore(RED, -finalBid); 
	}
}

void HandScore::addToHandScore(unsigned short team, short amount)
{
	if (team == RED)
		vHandScore = amount;
	else
		hHandScore = amount;
}

short HandScore::getHandScore(unsigned short team, short amount)
{
	if (team == RED)
		return vHandScore;
	else
		return hHandScore;
}