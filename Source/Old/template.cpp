// Includes, namespace and prototypes
#include "template.h"
#include <ctime>
using namespace AGK;
app App;

#if (DEMOBUILD)
const float demoTime = 3600.0f;
float timeUsedInSession;
float timeUsedPrev;
#endif

bool debug = false; 
unsigned short themeQueue[128];
unsigned short themeQueuePointer;
unsigned short menuQueue[128];
unsigned short menuQueuePointer;

//for other things
//unsigned short int Sound::volume = 100;
//Sound Buttons::ButtonClick;
//ParentImage Numbers::Parent;
//ParentImage Card::Parent;
//ParentImage Numbers::ScoreParent;
unsigned int Card::cardBackImageNumber[3];
//unsigned short Numbers::thematicNumbers[10];
//unsigned short Numbers::defaultNumbers[10];

// the main entry point for the application is this function
void app::Begin ( void )
{
    float tempWidth = (float) agk::GetDeviceWidth();
    float tempHeight = (float) agk::GetDeviceHeight();
    int currentOrientation;
    
    findValueForDebugging(tempWidth);
    findValueForDebugging(tempHeight);
    
    if (tempWidth > tempHeight)
        aspect = tempWidth / tempHeight;
    else
        aspect = tempHeight / tempWidth;
    
	agk::SetDisplayAspect(aspect);
    agk::SetOrientationAllowed(0, 0, 1, 1);
	agk::SetBorderColor(255, 0, 0);
	agk::SetSyncRate(60, 0);
    
    currentOrientation = agk::GetOrientation();
	
    agk::SetTransitionMode(1);
	agk::SetTextDefaultFontImage(agk::LoadImage("default/Arvo.png"));
    agk::SetResolutionMode(1);
    
    /*if (PLATFORM == MOBILE)
        agk::SetResolutionMode(0);
    else
        agk::SetResolutionMode(1);*/
    
    
	//Setting Error Mode
	agk::SetErrorMode(0);

#if (OS == WINDOWS)
	agk::SetWindowTitle("Double Pinochle");
#endif
	strcpy(themeDir, "green/");

	//initialize variables
	resetGame(true);
    
    loadSteeleLogo();
    initSteeleLogo();
    
	toggleXState(MENU);
	toggleXState(LOADING);

#if DEMOBUILD
	timeUsedInSession = 0;
	debug = false;
#endif
}

#if (DEMOBUILD)
void app::Loop ( bool *exit )
#else
void app::Loop(void)
#endif
{
	gameState = getState();
	trump = NewTrickGame->getTrumpSuit();
#if(OS==ANDROID)
	if((agk::GetRawKeyPressed(27)||agk::GetRawKeyPressed(87))&&menuPressed)
	{
		menuChoice=-1;
		ingamebutton=true;
		inGameMenuButton();
		menuPressed=false;
	}
#endif


	debug = false;

	if (debug)
		testScale();

#if DEMOBUILD      
	if (!debug && !demoOver)
#else
	if (!debug)
#endif
	{
		//put in controls
		switch (gameState)
		{
		case LOADING:
			handleLoading();
			return;
			break;
		case MENU:
			handleMenu();
			break;
		case OPTIONS:
			handleOptions(!CurrentTheme->isSetup());
			break;
		case START:
			handleStart();
			break;
		case INGAMEMENU:
			handleInGameMenu();
			break;
		case INGAMEOPTIONS:
			handleInGameOptions();
			break;
		case GROWBACKGROUND:
			growBackground();
			break;
		case DEALING:
			handleDealing();
			break;
		case ANIMATION:
			handleAnimation();
			break;
		case SORTING:
			handleSorting();
			break;
		case BIDDING:
			handleBidding();
			break;
		case MELDING:
			handleMelding();
			break;
		case PLAYING:
			handlePlaying();
			break;
		case SCOREBOARD:
			handleScoreboard();
			break;
		default:
			if (gameState < 0)
				toggleXState(LOADING);
			return;
			break;
		}
	}

    gameState = getState();
	//trump = NewTrickGame->getTrumpSuit();

	/*if ((gameState == ANIMATION) && !passInitialAnim)
	{
		agk::Sync();
		return;
	}*/
	/*if (agk::KeyDown(AGK_KEY_CONTROL))

		agk::Key
		dbControlKey())
		toggleDebug();
		*/

#if (DEMOBUILD)
	gameTimer = agk::Timer();
	
	if (gameState >= START)
	{
		timeUsedInSession = gameTimer;

		if (timeUsedInSession + timeUsedPrev > demoTime)
		{
			if (!DemoEndBack.hasGrown())
				DemoEndBack.updateGrowOpen(DemoEndBack.getScaleSize(), DemoEndBack.getScaleSizeY());
			else if (!mouseClick)
				DemoEndText.show();
			else
				*exit = true;

			demoOver = true;
		}

	}
#endif

/*	if (delayStep)
	{
		//agk::Print(delayStep);
		if (gameTimer - mouseDelay > 0.125f)
		{
			delayStep++;
			mouseDelay = gameTimer;
		}

		mouseClick = false;
	}*/

/*	if (agk::GetPointerReleased())
	{
		mouseClick = true;
		mouseX = agk::GetPointerX();
		mouseY = agk::GetPointerY();
		delayStep = 1;
		mouseDelay = gameTimer;
        swipe = false;
        hold = false;
	}
    
	*/
    
#if (PLATFORM != PC)
    if (!hold)
    {
        if(agk::GetPointerState())
        {
            hold = true;
            xstartpos = agk::GetPointerX();
            ystartpos = agk::GetPointerY();
        }
    }
#endif

#if (PLATFORM == PC)
	/*if (agk::GetButtonPressed(5))
		showAllCards();*/
#endif
    
	/*if (delayStep == 4)
	{
		delayStep = 0;
		mouseClick = false;
	}*/

	/*else if (delayStep)
	{
		mouseDelay = agk::Timer() - mouseDelay;

		if (mouseDelay > 1.0f)
			delayStep++;
	}*/


	//draw on screen
	//updateScore(NewGame, NewTrickGame, NewBidGame, count, passInitialAnim);
/*	if (gameState > START)
	{
		if (CurrentTheme->hasGrown())
		{
			bid = NewBidGame->getBid();
			CurrentTheme->update(gameState);
		}
	}*/
/*	else
	{
		if (Symbol->getExists())
		{
			if (Symbol->getVisible())
                Symbol->setVisible(false);

			for (short int i = 0; i < 3; i++)
			{
				CurrentTheme->hideAllHScores();
				CurrentTheme->hideAllVScores();
			}
		}
	}
	*/
#if DEBUG
	{
		displayAllKnown();

		if (!cardsRevealed)
		{
			for (short int i = 0; i < 20; i++)
			{
				CurrentTheme.Deck[i].revealCard(North);
				CurrentTheme.Deck[i].revealCard(West);
				CurrentTheme.Deck[i].revealCard(East);
			}
		}
	}
#endif

/*	if ((gameState >= BIDDING) && (gameState != SCOREBOARD))
	{
		ingamebutton=true;
		inGameMenuButton();
	}

	if (gameState <= INGAMEOPTIONS)
	{
		Symbol->setVisible(true);
		Symbol->setDepth(1);
	}
	else
		Symbol->setVisible(false);
		*/
	agk::Sync();

	if (gameState == SORTING)
		agk::Sleep(500);
/*	else if (gameState == PLAYING)
	{
		//if (foundLocation)
			//dbWaitKey();
		
		//else if (foundLocation)
			//dbWait(500); //should be at 1000
	}*/
	else if (gameState == BIDDING)
	{
		if (CurrentTheme->getTurn() != SOUTH)
			agk::Sleep(1000);
	}
}

// Called when the app ends
void app::End ( void )
{
	unsigned short int fileID = agk::OpenToWrite("SSDPS.DAT", 0);
	agk::WriteString(fileID, "_Theme_");
	agk::WriteInteger(fileID, tableTopStyle);
	agk::WriteString(fileID, "_Sound_");
	if (soundOn)
		agk::WriteInteger(fileID, 1);
	else
		agk::WriteInteger(fileID, 0);
#if(DEMOBUILD)
	{
		agk::WriteString(fileID, "_DemoTime_");
		agk::WriteFloat(fileID, timeUsedInSession + timeUsedPrev);
		agk::WriteString(fileID, "_DemoSeed_");
		agk::WriteInteger(fileID, ShuffledDeck.getDeckCounter());
	}
#endif   
	//doEndGameSwitch(fileID, NewGame.getState());

	agk::CloseFile(fileID);

	return;
}

void app::resetGame(bool startup)
{
	NewBidGame->reset();
	CurrentTheme->resetGame();
	NewTrickGame->reset();
	hand = 0;
	
#if (OS != IOS)
	dealer = agk::Random(0, 3);
#else
    dealer = arc4random() % 4;
#endif
    hideAllText();
	
	if (!startup)
	{
        GameResults->reset();
		GameResults->hide();
		HandResults->reset();
		HandResults->hide();
		CurrentTheme->hide();
		CurrentTheme->shrinkBackground();
    }
    else
    {
        //unsigned int temp = (unsigned) time(NULL);
        //std::srand(temp);
        //agk::SetRandomSeed(temp);   
    }
}

void app::setSoundData(void)
{
	PointClick->init("sounds/mouseclick1.wav");
}

void app::loadSteeleLogo(void)
{
	char temp[64];
	
	loadingImage[0] = myLoadImage(fileLoc("Loading.png", temp));

#if (PLATFORM != MOBILE)
	SteeleLogo->parentInit("default/steele_logo_1024x768_plate.png");
#else
    SteeleLogo->parentInit("default/steele_logo_480x320_plate.png");
#endif
}

void app::initSteeleLogo(void)
{
	SteeleLogo->setDepth(9999);
	SteeleLogo->setSize(100.0f);
	SteeleLogo->setVisible(true);
	SteeleLogo->setPosition(0.0f,  0.0f);
    agk::Sync();

#if (OS != IOS)
	for(unsigned short int i = 0; i < 254; i+=2)
	{
		SteeleLogo->setAlpha(i);
		agk::Sync();
	}
    
	agk::Sleep(1000);
#endif
}

void app::fadeSteeleLogo(void)
{
	for(unsigned short int i = 254; i > 0; i-=2)
	{
		SteeleLogo->setAlpha(i);
		agk::Sync();
	}
    
    agk::SetOrientationAllowed(0, 0, 1, 1);
}

void app::loadLoadScreen(void)
{
	Sprite ParentLoader = Sprite();

	ParentLoader.parentInit("default/Loading.png");
#if (OS != IOS)
	SteeleLogo->setVisible(false);
#endif
	LoadingScreen->subInit(ParentLoader.getImageNumber(), "default/load_landscape.png");
	LoadScreen1->subInit(ParentLoader.getImageNumber(), "default/loading.jpg");
#if (PLATFORM == MOBILE)
	Symbol->init(25, 25, 32, ParentLoader.getImageNumber(), "load suit rotation.png");
#else
	Symbol->init(75, 75, 32, ParentLoader.getImageNumber(), "load suit rotation.png");
#endif
    Symbol->setVisible(false);
    
    SteeleLogo->~Sprite();
}


void app::handleMenu()
{
	buttonDelay = 1.0f;
#if (OS == IOS)
    #if (PLATFORM == TABLET) // New Game-Options Button 
    const float yMinValue = 81.0f;
    const float yMaxValue = 89.0f;
    #elif (PLATFORM == MOBILE)
    const float yMinValue = 80.0f;
    const float yMaxValue = 95.0f;
    #endif
#else
	const float yMinValue = 81.0f;
	const float yMaxValue = 89.0f;
#endif
    
	LoadScreen1->setVisible(false);
	Legal->setVisible(false);
    Symbol->setVisible(false);
	
	CurrentTheme->shrinkBackground();
	
	MainMenu->showButton(NEWGAME);
	MainMenu->showButton(OPTS);

	//MainMenu.update();

	if (mouseClick)
	{
		if ((mouseX >= (15.0f )) && (mouseX <= (35.0f )))
		{
			if((mouseY >= (yMinValue)) && (mouseY <= (yMaxValue)))
			{
				menuChoice = 1;
			}
		}

		if ((mouseX >= (55.0f )) && (mouseX <= 84.8f ))
		{
			if ((mouseY >= (yMinValue)) && (mouseY <= (yMaxValue)))
				menuChoice = 4;
		}
	}

	MainMenu->ButtonAnimation(menuChoice);
		
	if (menuChoice == 1)
	{
		MainMenu->hide();
		Symbol->setVisible(true);
		LoadScreen1->setVisible(true);
        clearQueue(Symbol, 1);
        CurrentTheme->init(Symbol, tableTopStyle, getState());
		toggleXState(MENU);
		toggleXState(START);
        Symbol->setVisible(false);
		LoadScreen1->setVisible(false);
	}
	else if (menuChoice == 4)
	{
		toggleXState(MENU);
		
		if (!isStateActive(OPTIONS))
			toggleXState(OPTIONS);
		
		menuChoice = 0;
		MainMenu->hide();
	}
}

void app::handleInGameMenu()
{
	if (!CurrentTheme->hasShrunk())
	{
		CurrentTheme->shrinkBackground();
		return;
	}

	MainMenu->showButton(NEWGAME);
	MainMenu->showButton(OPTS);
	MainMenu->showButton(RESUME);
	MeldAmount->setVisible(false);
	TapScreen->setVisible(false);

	if (getState() == BIDDING)
		CurrentTheme->hideBidBubble();
	else if (getState() == MELDING)
		CurrentTheme->hideMeldBubble();

#if(OS==ANDROID)
	if(agk::GetRawKeyPressed(27))
	{
		menuChoice=3;
	}
#endif
	if (mouseClick)
	{
		if ((mouseX >= (16.17f )) && (mouseX <= (35.0f ))) //NewGame
		{
			if((mouseY >= (81.0f )) && (mouseY <= (88.8f )))
			{
				menuChoice = 1;
			}
		}

		if ((mouseX >= (66.2f )) && (mouseX <= (85.0f ))) //Options
		{
			if ((mouseY >= (81.0f )) && (mouseY <= (88.8f )))
				menuChoice = 4;
		}

		if ((mouseX >= (41.0f )) && (mouseX <= (59.9f ))) //ResumeGame
		{
			if ((mouseY >= (81.0f )) && (mouseY <= (88.8f )))
				menuChoice = 3;
			menuPressed=true;
		}

		if (menuChoice == 0)
			mouseClick = false;
	}

	MainMenu->ButtonAnimation(menuChoice);
	
	MainMenu->hide();

	if (menuChoice == 1)
	{
		toggleXState(INGAMEMENU);
		resetGame();
		toggleXState(START);
	}
	else if (menuChoice == 4)
	{
		toggleXState(INGAMEMENU);
		toggleXState(INGAMEOPTIONS);
	}
	else if (menuChoice == 3)
	{
		toggleXState(INGAMEMENU);
		toggleXState(GROWBACKGROUND);
	}
	
	menuChoice = 0;
	delayStep = 0;
}

void app::setThemeOptionImage(char buffer[])
{
	strcpy(buffer, "background_");

	switch(tableTopStyle)
	{
	case 0:
		strcat(buffer, "g.jpg");
		break;
	case 1:
		strcat(buffer, "r.jpg");
		break;
	case 2:
		strcat(buffer, "a.jpg");
		break;
	case 3:
		strcat(buffer, "f.jpg");
		break;
	case 4:
		strcat(buffer, "e.jpg");
		break;
	case 5:
		strcat(buffer, "w.jpg");
		break;
	default:
		strcat(buffer, "g.jpg");
	}
}

void app::handleOptions(bool init)
{
	bool change = false;
	unsigned short choice = 0;
	
	choice = Options->update();

	if (getPrevState() <= MENU)
		Options->hideButton(RESUME);

	if (choice >= 5)
	{
		change = changeTheme(tableTopStyle, init);
                
		if (change)
		{
			CurrentTheme->hide();
			setAnimatedSpriteData();
		}
                				           
		Options->shrinkBackground();
		toggleXState(OPTIONS);
                
        if (choice == 2)
			toggleXState(GROWBACKGROUND);
        else if (choice == 1)
        {
			resetGame();
			toggleXState(START);
		}
                
        //clearQueue(&Loading, 1);
		//menuChoice = 0;
		//delayStep = 0;

		if (change)
		{
			unsigned short int fileID = agk::OpenToWrite("SSDPS.DAT", 0);
			agk::WriteString(fileID, "_Theme_");
			agk::WriteInteger(fileID, tableTopStyle);
			agk::WriteString(fileID, "_Sound_");
			if (!Options->isSoundMuted())
				agk::WriteInteger(fileID, 1);
			else
				agk::WriteInteger(fileID, 0);

			agk::WriteString(fileID, "_Language_");
			agk::WriteInteger(fileID, language);

			agk::CloseFile(fileID);
		}
	}
}
/*
void app::handleInGameOptions(void)
{
	Options->growBackground();

	Options->show(tableTopStyle);
	
	//Options.update();

	if((!((strcmp(agk::GetDeviceName(), "windows") == 0) || (strcmp(agk::GetDeviceName(), "osx"))==0)) || debug)
	{
        if(agk::GetPointerState())
        {
			if ((mouseY >= (23.0f )) && (mouseY <= (68.0f )))
			{
				if (!hold)
				{
					xstartpos = agk::GetPointerX();
					hold = true;
				}
				else
				{
					if (agk::GetPointerX() <= xstartpos - (5.0f ))
					{
						menuChoice = 5;
						hold = false;
					}
					else if (agk::GetPointerX() >= xstartpos + (5.0f ))
					{
						menuChoice = 6;
						hold = false;
					}
				}
			}
		}
		else
			hold = false;
    }

	if (mouseClick && !debug)
	{

		if (mouseX >= (7.0f ))
		{
			if (mouseX <= (93.5f ))
			{
				if ((mouseY >= (12.0f )) && (mouseY <= (51.5f )))
				{//somewhere valid
					if (mouseX <= (16.5f ))
					{
						menuChoice = 5;
						delayStep = 1;
					}
					else if (mouseX >= (84.0f ))
					{
						menuChoice = 6;
						delayStep = 1;
					}
				}
				else if ((mouseY >= (70.0f )) && (mouseY <= (80.0f )))
				{
					if (soundOn == true)
					{
						soundOn = false;
						Options->mute();
					}
					else
					{
						soundOn = true;
						Options->unMute();
					}
				}
				else if ((mouseX >= (41.0f )) && (mouseX <= (60.0f )))
				{
					if ((mouseY >= (83.0f )) && (mouseY <= (94.0f )))
					{
						menuChoice = 1;
						delayStep = 1;
					}
				}
				else if ((mouseX >= (65.0f )) && (mouseX <= (85.0f )))
				{
					if ((mouseY >= (81.0f )) && (mouseY <= (91.4f )))
					{
						menuChoice = 2;
						delayStep = 1;
					}

				}
			}
		}
	}

	if (!delayStep && ((menuChoice == 5) || (menuChoice == 6)))
	{
		short newStyle;
		short offDirection;
		short onDirection;

		if(menuChoice == 5)
		{//table top
			if (tableTopStyle + 1 < NUM_TABLE_TOP)
				newStyle = tableTopStyle + 1;
			else
				newStyle = 0;

			offDirection = WEST;
			onDirection = EAST;
		}
		else
		{
			if (tableTopStyle - 1 < 0)
				newStyle = NUM_TABLE_TOP - 1;
			else
				newStyle = tableTopStyle - 1;

			offDirection = EAST;
			onDirection = WEST;
		}

		if (Options.ThemeOption[tableTopStyle].isVisible())
		{
			Options.ThemeOption[tableTopStyle].moveOffScreen(offDirection);

			Options.ThemeOption[newStyle].moveOnScreen(onDirection);
		}
		else  if (Options.ThemeOption[newStyle].isMoving())
		{
			if (Options.ThemeOption[tableTopStyle].isMoving())
				Options.ThemeOption[tableTopStyle].moveOffScreen(offDirection);

			Options.ThemeOption[newStyle].moveOnScreen(onDirection);
		}
		else
		{
			menuChoice = 0;
			tableTopStyle = newStyle;
		}

		debug = false;
		return;
	}

	if (delayStep)
	{
		if (menuChoice < 5)
		{
			if(Options.ButtonAnimation(delayStep, menuChoice))
			{
				changeTheme(tableTopStyle);
				Options.hide();
				Options.ThemeOption[tableTopStyle].hide();
				Options.Background.hide();
				Options.SoundCheck.hide();
				NewGame.toggleXState(INGAMEOPTIONS);
				if (menuChoice == 2)
					NewGame.toggleXState(GROWBACKGROUND);
				else
				{
					resetGame();
					NewGame.toggleXState(START);
				}
				menuChoice = 0;
				delayStep = 0;

				unsigned short int fileID = agk::OpenToWrite("SSDPS.DAT", 0);
				agk::WriteString(fileID, "_Theme_");
				agk::WriteInteger(fileID, tableTopStyle);
				agk::WriteString(fileID, "_Sound_");
				if (soundOn)
					agk::WriteInteger(fileID, 1);
				else
					agk::WriteInteger(fileID, 0);

				agk::WriteString(fileID, "_Language_");
				agk::WriteInteger(fileID, language);

				agk::CloseFile(fileID);
			}
		}
		else
			Options.arrowAnimation(delayStep, menuChoice);
	}
}
*/

void app::getThemeDir(short int style, char buffer[])
{
	switch(style)
	{
	case 0:
		strcpy(buffer, "green/");
		break;
	case 1:
		strcpy(buffer, "red/");
		break;
	case 2:
		strcpy(buffer, "ancient/");
		break;
	case 3:
		strcpy(buffer, "future/");
		break;
	case 4:
		strcpy(buffer, "electric/");
		break;
	case 5:
		strcpy(buffer, "winter/");
		break;
	default:
		strcpy(buffer, "default/");
		break;
	}
}

bool app::changeTheme(short int style, bool init)
{
	bool returnValue = false;

	Symbol->setVisible(true);
	LoadScreen1->setVisible(true);
	//LoadScreen1->setPriority(3);
	agk::Sync();

	if (style != CurrentTheme->getCurrentTheme())
	{
		switch (style)
		{
		case GREEN:
			CurrentTheme = new Green();
			break;
		case RED:
			CurrentTheme = new Red();
			break;
		case ANCIENT:
			CurrentTheme = new Ancient();
			break;
		case NOEL:
			CurrentTheme = new Noel();
			break;
		}

		CurrentTheme->init(Symbol, style, getState());

		returnValue = true;
	}

	Symbol->setVisible(false);
	LoadScreen1->setVisible(false);

	return returnValue;
}

void app::handleStart(void)
{
	if (!CurrentTheme->start(dealer))
		return;
	
	foundLocation = false;
	playingAnimation = false;
	passInitialAnim = false;
	round = 0;
	count = 0;
	bid = 49;
	bidWinner = -1;
	hMeld = 0;
	vMeld = 0;
	hTricks = -1;
	vTricks = -1;
	toggleXState(START);
	toggleXState(DEALING);
}

void app::handleAnimation(void)
{
	//NewGame.toggleXState(ANIMATION);
	//NewGame.toggleXState(SORTING);
		
	/*foundLocation = CurrentTheme.Deck[cardPlayed[(count-1)%4]].updateCardLoc(turn, NewGame, NewBidGame, NewTrickGame, count, passInitialAnim);
		if (foundLocation)
		{
			if (soundOn)
			{
				

			NewGame.toggleXState(ANIMATION);
			playingAnimation = false;
			turn++;
			if (turn > 3)
				turn = 0;
		}
	}*/
}

void app::handleSorting(void)
{
	passInitialAnim = true;
	if (turn)
	{
		CurrentTheme->sortHands();
		turn = 0;
	}
	else
	{
		turn = -1;
		count = -1;
		toggleXState(SORTING);
		toggleXState(BIDDING);
		for (int i = 0; i < 4; i++)
			BidBacks[i]->setVisible(true);
	}
}

void app::handleBidding(void)
{
	pauseGame = false;
	bool playerBid = false;
	char num[4]= {NULL};

	if (CurrentTheme->getBidValue() < bid)
	{
		incrementing = true;
		return;
	}

	incrementing = false;

	if (!CurrentTheme->checkForBidWinner())
		CurrentTheme->update(BIDDING);
	else
	{
		toggleXState(BIDDING);
		toggleXState(MELDING);
	}
}

void app::handleMelding(void)
{
	if (!CurrentTheme->getMeldingComplete())
		CurrentTheme->update(MELDING);
	else
	{
		NewTrickGame->buildDecisionTree();
		toggleXState(MELDING);
		toggleXState(PLAYING);
	}
}
void app::handlePlaying(void)
{
	CurrentTheme->playGame();
}

void app::handleScoreboard(void)
{
	MeldAmount->setVisible(false);
	TapScreen->setVisible(false);
	HandResults->update();
}

void app::handleLoading(void)
{
	switch (count)
	{
	case 0:
        fadeSteeleLogo();
        break;
	case 1:
		loadLoadScreen();
		break;
	case 2:
		initLoadScreen();
		break;
	case 3:
		initVars();
		break;
	case 4:
        parseFile(); 
		break;
	case 5:
		setSoundData();
		break;
	case 6:
		setNumberData();
		break;
	case 7:
		MainMenu->init();
		break;
	case 8:
		Options->init();
		break;
	case 9:
		HandResults->init();
		break;
	case 10:
        GameResults->init();
        break;
	case 11:
		setSpriteData();
		break;
	case 12:
		setAnimatedSpriteData();
		break;
	case 13:
		finalSetup();
		break;
	case 14:
		toggleXState(LOADING);
		toggleXState(MENU);
		count = -1;
		Symbol->setVisible(false);
		break;
	}

	count++;
}

void app::testScale(void)
{

}

void app::writePlayerData(short unsigned int fileID, Player Selected)
{
	short int state = NewGame.getState();

	agk::WriteString(fileID, "Hand");
	for (short int i = 0; i < Selected.getCardsInHand(); i++)
	{
		agk::WriteString(fileID, "|");
		agk::WriteInteger(fileID, West.getCard(i));
	}

	if (state == PLAYING)
	{

		agk::WriteString(fileID, "Known");
		for (short int i = 0; i < 5; i++)
		{
			for (short int j = 0; j < 4; j++)
			{
				agk::WriteString(fileID, "|");
				agk::WriteInteger(fileID, Selected.known[i][j]);
			}
		}

		agk::WriteString(fileID, "Trumping");
		for (short int i = 0; i < 4; i++)
		{
			agk::WriteString(fileID, "|");
			if (Selected.trumpingSuit[i])
				agk::WriteInteger(fileID, 1);
			else
				agk::WriteInteger(fileID, 0);
		}
	}
	if (state == BIDDING)
	{
		agk::WriteString(fileID, "Bidding");
		agk::WriteString(fileID, "|");

		if (NewBidGame.getPass(Selected.getID()))
		{
			agk::WriteInteger(fileID, 1);
			agk::WriteString(fileID, "|");
			agk::WriteInteger(fileID, NewBidGame.getPassRound(Selected.getID()));
		}
		else
			agk::WriteInteger(fileID, 0);

	}
}
void app::formatPlayerData(short unsigned int fileID)
{
	agk::WriteString(fileID, "_WestData_");
	writePlayerData(fileID, West);
	agk::WriteString(fileID, "_NorthData_");
	writePlayerData(fileID, North);
	agk::WriteString(fileID, "_EastData_");
	writePlayerData(fileID, East);
	agk::WriteString(fileID, "_SouthData_");
	writePlayerData(fileID, South);
}

void app::formatDeckData(short unsigned int fileID)
{
	agk::WriteString(fileID, "_DeckData_");
	agk::WriteString(fileID, "Deck");
	for (short int i = 0; i < 80; i++)
	{
		agk::WriteString(fileID, "|");
		agk::WriteInteger(fileID, ShuffledDeck.getCard(i));
	}
}

void app::formatScores(short unsigned int fileID)
{
	agk::WriteString(fileID, "_Scores_");
	agk::WriteString(fileID, "Horizontal");
	agk::WriteString(fileID, "|");
	agk::WriteInteger(fileID, hScore);
	agk::WriteString(fileID, "Vertical");
	agk::WriteString(fileID, "|");
	agk::WriteInteger(fileID, vScore);
}

void app::formatBids(short unsigned int fileID)
{
	agk::WriteString(fileID, "_BidData_");
	agk::WriteString(fileID, "CurrentBid");
	agk::WriteString(fileID, "|");
	agk::WriteInteger(fileID, bid);
	agk::WriteString(fileID, "NumOfBids");
	agk::WriteString(fileID, "|");
	agk::WriteInteger(fileID, West.getNumOfBids());
	agk::WriteString(fileID, "|");
	agk::WriteInteger(fileID, North.getNumOfBids());
	agk::WriteString(fileID, "|");
	agk::WriteInteger(fileID, East.getNumOfBids());
	agk::WriteString(fileID, "|");
	agk::WriteInteger(fileID, South.getNumOfBids());
}

void app::formatMelds(short unsigned int fileID)
{
	//don't need to do anything special, just restart meldin process from count = 0;
}

void app::formatGame(short unsigned int fileID)
{
	agk::WriteString(fileID, "_GameData_");
	agk::WriteString(fileID, "Lead");
	agk::WriteString(fileID, "|");
	agk::WriteInteger(fileID, NewTrickGame.getLead());
	agk::WriteString(fileID, "CardsPlayed");
	agk::WriteInteger(fileID, count%4);
	for (short int i = 0; i < count%4; i++)
	{
		agk::WriteString(fileID, "|");
		agk::WriteInteger(fileID, cardPlayed[i]);
	}
	agk::WriteString(fileID, "Meld");
	agk::WriteString(fileID, "Vertical");
	agk::WriteString(fileID, "|");
	agk::WriteInteger(fileID, NewGame.verticalMeld);
	agk::WriteString(fileID, "Horizontal");
	agk::WriteString(fileID, "|");
	agk::WriteInteger(fileID, NewGame.horizontalMeld);
	agk::WriteString(fileID, "BidWinner");
	agk::WriteString(fileID, "|");
	agk::WriteInteger(fileID, NewBidGame.getBidWinner());
	agk::WriteString(fileID, "Bid");
	agk::WriteString(fileID, "|");
	agk::WriteInteger(fileID, bid);
}

void app::parseFile(void)
{
	unsigned short int fileID;
	bool getQuery = true;
	std::string query;

	if (agk::GetFileExists("SSDPS.DAT"))
		fileID = agk::OpenToRead("SSDPS.DAT");
	else
		return;

	while (!agk::FileEOF(fileID))
	{
		if (getQuery)
			query = agk::ReadString(fileID);

		if (query == "_State_")
		{
			NewGame.toggleXState(NewGame.getState());
			NewGame.toggleXState(agk::ReadInteger(fileID));
		}
		else if (query == "_Theme_")
		{
			tableTopStyle = agk::ReadInteger(fileID);
			getThemeDir(tableTopStyle, themeDir);
			//changeTheme(tableTopStyle);
		}
		else if (query == "_Language_")
			language = agk::ReadInteger(fileID);
#if DEMOBUILD
		else if (query == "_DemoTime_")
		{
			if (DEMOBUILD)
				timeUsedPrev = agk::ReadFloat(fileID);
		}
		else if (query == "_DemoSeed_")
		{
			if (DEMOBUILD)
				ShuffledDeck.setDeckCounter(agk::ReadInteger(fileID));
		}
#endif
		else if (query == "_Sound_")
		{
			if (agk::ReadInteger(fileID))
			{
				soundOn = true;
				Options.unMute();
				PointClick.setMasterVolume(100);
			}
			else
			{
				soundOn = false;
				Options.mute();
				PointClick.setMasterVolume(0);
			}
		}
		else if (query == "Turn")
			turn = agk::ReadInteger(fileID);
		else if (query == "Count")
			count = agk::ReadInteger(fileID);
		else if (query == "Dealer")
			dealer = agk::ReadInteger(fileID);
		else if (query == "_WestData_")
		{
			parsePlayerData(fileID, &West);
			parsePlayerData(fileID, &North);
			parsePlayerData(fileID, &East);
			query = parsePlayerData(fileID, &South);
			getQuery = false;
		}
		else if (query == "_Scores_")
		{
			agk::ReadString(fileID);
			agk::ReadString(fileID);
			hScore = agk::ReadInteger(fileID);
			agk::ReadString(fileID);
			agk::ReadString(fileID);
			vScore = agk::ReadInteger(fileID);
			getQuery = true;
		}
		else if (query == "_DeckData_")
		{
			char savedDeck[80];
			agk::ReadString(fileID);
			for (short int i = 0; i < 80; i++)
			{
				agk::ReadString(fileID);
				savedDeck[i] = agk::ReadInteger(fileID);
			}

			ShuffledDeck.setDeck(savedDeck);
		}
		else if (query == "_BidData_")
		{
			agk::ReadString(fileID); //currentBid
			agk::ReadString(fileID); //|
			NewBidGame.setBid(agk::ReadInteger(fileID));
			West.tabulateMeld();
			North.tabulateMeld();
			East.tabulateMeld();
			South.tabulateMeld();

			agk::ReadString(fileID);//numofbids
			agk::ReadString(fileID);//|
			short int numOfBids = agk::ReadInteger(fileID);
			for (short int i = 0; i < numOfBids; i++)
				West.incrementNumOfBids();

			agk::ReadString(fileID); //|
			numOfBids = agk::ReadInteger(fileID);
			for (short int i = 0; i < numOfBids; i++)
				North.incrementNumOfBids();

			agk::ReadString(fileID); //|
			numOfBids = agk::ReadInteger(fileID);
			for (short int i = 0; i < numOfBids; i++)
				East.incrementNumOfBids();

			agk::ReadString(fileID); //|
			numOfBids = agk::ReadInteger(fileID);
			for (short int i = 0; i < numOfBids; i++)
				South.incrementNumOfBids();
		}
		else if (query == "_GameData_")
		{
			agk::ReadString(fileID);
			agk::ReadString(fileID);
			NewTrickGame.setLead(agk::ReadInteger(fileID));
			agk::ReadString(fileID);
			short int numOfCards = agk::ReadInteger(fileID);
			for (short int i = 0; i < numOfCards; i++)
			{
				agk::ReadString(fileID);
				cardPlayed[i] = agk::ReadInteger(fileID);
			}
			agk::ReadString(fileID);
			agk::ReadString(fileID);
			agk::ReadString(fileID);
			NewGame.verticalMeld = agk::ReadInteger(fileID);
			agk::ReadString(fileID);
			agk::ReadString(fileID);
			NewGame.horizontalMeld = agk::ReadInteger(fileID);
			agk::ReadString(fileID);
			agk::ReadString(fileID);
			bidWinner = agk::ReadInteger(fileID);
			NewBidGame.setBidder(bidWinner);
			for (short int i = 0; i < 4; i++)
			{
				if (i != bidWinner)
					NewBidGame.setPass(i);
			}
			agk::ReadString(fileID);
			agk::ReadString(fileID);
			NewBidGame.setBid(agk::ReadInteger(fileID));
		}
	}

	//makeVisible(); //make everything visible
	//reDeal();
}

void app::reDeal()
{
	short int westToDeal = West.getCardsInHand();
	short int northToDeal = North.getCardsInHand();
	short int eastToDeal = East.getCardsInHand();
	short int southToDeal = South.getCardsInHand();
	short int totalToDeal = westToDeal + northToDeal + eastToDeal + southToDeal;
	short int newRound = 0;
	short int newTurn = (dealer + 1) % 4;

	while (totalToDeal > 0)
	{

		if (newTurn == WEST)
			foundLocation = CurrentTheme.Deck[0].updateCardLocs(newTurn, CurrentTheme.Deck, West.getCard(newRound * 4), West.getCard((newRound * 4) + 1), West.getCard((newRound * 4) + 2), West.getCard((newRound * 4) + 3), newRound);
		else if (newTurn == NORTH)
			foundLocation = CurrentTheme.Deck[0].updateCardLocs(newTurn, CurrentTheme.Deck, North.getCard(newRound * 4), North.getCard((newRound * 4) + 1), North.getCard((newRound * 4) + 2), North.getCard((newRound * 4) + 3), newRound);
		else if (newTurn == EAST)
			foundLocation = CurrentTheme.Deck[0].updateCardLocs(newTurn, CurrentTheme.Deck, East.getCard(newRound * 4), East.getCard((newRound * 4) + 1), East.getCard((newRound * 4) + 2), East.getCard((newRound * 4) + 3), newRound);
		else if (newTurn == SOUTH)
			foundLocation = CurrentTheme.Deck[0].updateCardLocs(newTurn, CurrentTheme.Deck, South.getCard(newRound * 4), South.getCard((newRound * 4) + 1), South.getCard((newRound * 4) + 2), South.getCard((newRound * 4) + 3), newRound);

		if (foundLocation) //at location!
		{
			foundLocation = false;
			newTurn = (newTurn + 1) % 4;
			totalToDeal -= 4;
		}
	}
}

std::string app::parsePlayerData(short unsigned int fileID, Player *Selected)
{
	//Stubbing out


	//bool lastField = false;
	std::string query = agk::ReadString(fileID);
/*
	while (!lastField)
	{
		if (query == "Hand")
		{
			query = agk::ReadString(fileID);

			while (query == "|")
			{
				Selected->dealToHand(agk::ReadInteger(fileID));
				query = agk::ReadString(fileID);
			}
		}
		else if (query == "Known")
		{
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					query = agk::ReadString(fileID);
					Selected->known[i][j] = agk::ReadInteger(fileID);
				}
			}

			query = agk::ReadString(fileID);
		}
		else if (query == "Trumping")
		{
			for (int i = 0; i < 4; i++)
			{
				agk::ReadString(fileID);

				if (agk::ReadInteger(fileID))
					Selected->trumpingSuit[i] == true;
				else
					Selected->trumpingSuit[i] == false;
			}
		}
		else if (query == "Bidding")
		{
			query = agk::ReadString(fileID);

			if (query == "|")
			{
				if (agk::ReadInteger(fileID))
				{
					agk::ReadString(fileID);
					NewBidGame.setPass(Selected->getID(), agk::ReadInteger(fileID));
				}
			}
			//lastField = true;
		}
		else if (query == "|")
			query = agk::ReadString(fileID);
		else
			lastField = true;
	}
	*/
	return query;

}

void app::doEndGameSwitch(short unsigned int fileID, short int gameState)
{
	/*char prevState = NewGame.getPrevState();

	if ((gameState != OPTIONS) && (gameState != ANIMATION) && (gameState != MENU))
	{
		agk::WriteString(fileID, "_State_");
		agk::WriteInteger(fileID, gameState);*/

		agk::WriteString(fileID, "Theme");
		agk::WriteInteger(fileID, tableTopStyle);

		/*agk::WriteString(fileID, "Turn");
		agk::WriteInteger(fileID, turn);

		agk::WriteString(fileID, "Count");
		if (gameState == MELDING)
			agk::WriteInteger(fileID, 0); //start over
		else
			agk::WriteInteger(fileID, count);

		agk::WriteString(fileID, "Dealer");
		agk::WriteInteger(fileID, dealer);

		if (gameState >= MELDING)
			agk::WriteString(fileID, "Trump");

		formatPlayerData(fileID);
		formatScores(fileID);

	}

	switch(gameState)
	{
	case MENU://save theme
	case START://save scores and theme
		break;
	case OPTIONS: //Could be from anything past this point
		doEndGameSwitch(fileID, prevState);
		break;
	case DEALING:
		formatDeckData(fileID);
		break;
	case ANIMATION: //could be part of dealing or playing
		doEndGameSwitch(fileID, prevState);
		break;
	case SORTING: //same as bidding, I think
	case BIDDING:
		formatBids(fileID);
		break;
	case MELDING:
		//formatMelds(fileID);  //don't need to do anything special
		break;
	case PLAYING:
		formatGame(fileID);
		break;
	}*/

}

void app::initLoadScreen(void)
{
    float factor = 1.0f;
    float offset = 0.0f;
    
    if (PLATFORM == MOBILE)
    {
        factor = 1.5f;
        offset = -1.0f;
    }
    
	Legal.createT("Copyright 2012 Steele Studios, All Rights Reserved");
	Legal.color(255, 255, 255);
	Legal.position(32.5f, 92.5f + offset);
	Legal.size(3.0f*factor);
	Legal.show();

	LoadingScreen.setSize(100.0f); //setSize(0.09f, 0.09f);
	LoadingScreen.setPriority(0);
	LoadingScreen.display(0.0f, 0.0f); //7.0f, (float)((50.0/768.0)*100));
	LoadingScreen.show();

	//loading test screen can be changed to a proper loading screen if needed
	LoadScreen1.setSize(55.0f);
	LoadScreen1.setPriority(1);
	LoadScreen1.display(0.0f,90.0f);
	LoadScreen1.show();

	Loading.setSize(5.0f);
	Loading.display(26.0f, 90.0f);
	Loading.setPriority(5);
	Loading.setAnimatedFrameTo(1);
	agk::Sync();
}

void app::initSprites(void)
{

}

void app::initNumbers(void)
{
}

void app::finalSetup(void)
{
	//char temp[64] = {NULL};
	unsigned short int fontImNum;

	initNumbers();
	initSprites();

	fontImNum = myLoadImage("default/Corben.png");

	gameResult.createT("");
	gameResult.font(fontImNum);
	gameResult.hide();
	gameResult.size(4.75f);
	gameResult.color(245, 245, 245);
	gameResult.position(50.0f, 30.0f);

	Loading.incrementSpriteFrame();
	agk::Sync();

	gameResult4.createT("");
	gameResult4.font(fontImNum);
	gameResult4.size(4.75f);
	gameResult4.color(245, 245, 245);
	gameResult4.hide();
	gameResult4.position(50.0f, 35.0f);

	Loading.incrementSpriteFrame();
	agk::Sync();

	MeldFail.createT("");
	MeldFail.font(fontImNum);
	MeldFail.size(4.75f);
	MeldFail.color(245, 245, 245);
	MeldFail.hide();
	MeldFail.position(50.0f, 35.0f);
    MeldFail.setDepth(9999);
	MeldFail.centerText();

	Loading.incrementSpriteFrame();
	agk::Sync();

	MeldAmount.createT("");
	MeldAmount.size(4.75f);
	MeldAmount.font(fontImNum);
	MeldAmount.color(245, 245, 245);
	MeldAmount.position(50.0f, 35.0f);
	MeldAmount.centerText();
	MeldAmount.hide();

	Loading.incrementSpriteFrame();
	agk::Sync();

	GameOver.createT("");
	GameOver.size(4.75f);
	GameOver.font(fontImNum);
	GameOver.color(245, 245, 245);
	GameOver.position(50.0f, 35.0f);
	GameOver.centerText();
	GameOver.hide();

	Loading.incrementSpriteFrame();
	agk::Sync();

	switch (language)
	{
	case ENGLISH:
		TapScreen.createT("Tap Screen to Continue");
		break;
	case FRENCH:
		TapScreen.createT("Appuyez sur l'écran pour continuer");
		break;
	case ITALIAN:
		TapScreen.createT("Tocco dello schermo per continuare");
		break;
	case GERMAN:
		TapScreen.createT("Tippen sie auf bildschirm, um fortzufahren");
		break;
	case SPANISH:
		TapScreen.createT("Tocar la pantalla para continuar");
		break;
	}
	TapScreen.font(fontImNum);
	TapScreen.size(4.75f);
	TapScreen.color(245, 245, 245);
	TapScreen.position(50.0f, 35.0f);
	TapScreen.centerText();
	TapScreen.hide();

	Loading.incrementSpriteFrame();
	agk::Sync();

	switch (language)
	{
	case ENGLISH:
		SwipeHelp.createT("Touch card to select a card.\nSwipe up to play selected card.");
		break;
	case FRENCH:
		SwipeHelp.createT("Touchez carte pour le sélectionner.\nGlisser pour jouer la carte sélectionnée.");
		break;
	case ITALIAN:
		SwipeHelp.createT("Tocco carta per selezionarla.\nScorrere fino a giocare la carta selezionato.");
		break;
	case GERMAN:
		SwipeHelp.createT("Touch-karte, um sie auszuwählen.\nStreichen bis zur gewählten karte spielen.");
		break;
	case SPANISH:
		SwipeHelp.createT("Tarjeta de contacto para seleccionarlo.\nPasa para jugar la carta elegida.");
		break;
	}
	SwipeHelp.font(fontImNum);
	SwipeHelp.size(4.75f);
	SwipeHelp.color(245, 245, 245);
	SwipeHelp.position(50.0f, 65.0f);
	SwipeHelp.centerText();
	SwipeHelp.hide();
	
	Loading.incrementSpriteFrame();
	agk::Sync();

	switch (language)
	{
	case ENGLISH:
		ChooseTrump.createT("Choose your trump suit.\nPotential suits must have a marriage.");
		break;
	case FRENCH:
		ChooseTrump.createT("Choisissez votre couler d'atout.\nCostumes potentiel doit avoir un mariage.");
		break;
	case ITALIAN:
		ChooseTrump.createT("Scegliere il seme di briscola.\nSi adatta alle potenzialità deve avere un matrimonio.");
		break;
	case GERMAN:
		ChooseTrump.createT("Wählen sie ihre trumpffarbe.\nPotenzial anzüge müssen eine ehe.");
		break;
	case SPANISH:
		ChooseTrump.createT("Elige tu palo de triunfo.\nDemandas potenciales deben tener un matrimonio.");
		break;
	}
	ChooseTrump.font(fontImNum);
	ChooseTrump.size(4.75f);
	ChooseTrump.color(245, 245, 245);
	ChooseTrump.position(50.0f, 65.0f);
	ChooseTrump.centerText();
	ChooseTrump.hide();
	
	Loading.incrementSpriteFrame();
	agk::Sync();

	switch (language)
	{
	case ENGLISH:
		OptionsHelp.createT("To choose another Theme,\nswipe left or right.");
		break;
	case FRENCH:
		OptionsHelp.createT("De choisir un autre thème,\nfaites glisser à gauche ou à droite.");
		break;
	case ITALIAN:
		OptionsHelp.createT("Di scegliere un altro tema,\nscorrere a destra oa sinistra.");
		break;
	case GERMAN:
		OptionsHelp.createT("Zu wählen, ein weiteres thema,\nlinks oder rechts streichen.");
		break;
	case SPANISH:
		OptionsHelp.createT("A elegir otra tema,\ndeslizar a izquierda o derecha.");
		break;
	}
	OptionsHelp.font(fontImNum);
	OptionsHelp.size(4.75f);
	OptionsHelp.color(245, 245, 245);
	OptionsHelp.position(50.0f, 65.0f);
	OptionsHelp.centerText();
	OptionsHelp.hide();
	
	Loading.incrementSpriteFrame();
	agk::Sync();

	Legal.hide();
	Legal.~Text();

#if DEMOBUILD
	DemoEndText.createT("Sorry, but your one hour has been reached.\nThe full game will be released soon,\nFind us on Facebook (Steele Studios)\nand on Twitter (@SteeleStudios)\nto get more details!");
	DemoEndText.font(fontImNum);
	DemoEndText.hide();
	DemoEndText.size(4.75f);
	DemoEndText.color(245, 245, 245);
	DemoEndText.position(50.0f, 30.0f);
	DemoEndText.centerText();
	DemoEndText.setDepth(10001);
#endif

	delayStep = 0;
}

/*void app::setCardData(void)
{
	//similar setup to sprites, but need a front image
	for(int i = 0; i < 20; i++)
	{
		for (int j = i * 4; j < (i * 4) + 4; j++)
		{
			int tempImageF;
			int tempImageB;
			int tempImageO;
			char tempFileName[32];
			char tempFileNameO[64];
			char tempChar[64];

			switch (i)
			{
			case 0:
				strcpy(tempFileName, "ace_hearts.png");
				break;
			case 1:
				strcpy(tempFileName, "10_hearts.png");
				break;
			case 2:
				strcpy(tempFileName, "king_hearts.png");
				break;
			case 3:
				strcpy(tempFileName, "queen_hearts.png");
				break;
			case 4:
				strcpy(tempFileName, "jack_hearts.png");
				break;
			case 5:
				strcpy(tempFileName, "ace_clubs.png");
				break;
			case 6:
				strcpy(tempFileName, "10_clubs.png");
				break;
			case 7:
				strcpy(tempFileName, "king_clubs.png");
				break;
			case 8:
				strcpy(tempFileName, "queen_clubs.png");
				break;
			case 9:
				strcpy(tempFileName, "jack_clubs.png");
				break;
			case 10:
				strcpy(tempFileName, "ace_diamonds.png");
				break;
			case 11:
				strcpy(tempFileName, "10_diamonds.png");
				break;
			case 12:
				strcpy(tempFileName, "king_diamonds.png");
				break;
			case 13:
				strcpy(tempFileName, "queen_diamonds.png");
				break;
			case 14:
				strcpy(tempFileName, "jack_diamonds.png");
				break;
			case 15:
				strcpy(tempFileName, "ace_spades.png");
				break;
			case 16:
				strcpy(tempFileName, "10_spades.png");
				break;
			case 17:
				strcpy(tempFileName, "king_spades.png");
				break;
			case 18:
				strcpy(tempFileName, "queen_spades.png");
				break;
			case 19:
				strcpy(tempFileName, "jack_spades.png");
				break;
			}

			tempImageF = myLoadImage(fileLoc(tempFileName, tempChar));
			tempImageB = myLoadImage(fileLoc("card_back.png", tempChar));

			strncpy(tempFileNameO, tempFileName, strlen(tempFileName)-4);
			strcat(tempFileNameO, "m.png");

			tempImageO = myLoadImage(fileLoc(tempFileNameO, tempChar));

			CurrentTheme.Deck[j].setData(tempImageF, tempImageB, tempImageO, i, i/5);
			//CurrentTheme.Deck[j].setFrontImage(i+1);
			//CurrentTheme.Deck[j].setSize(-1.0f, 12.5f);
			CurrentTheme.Deck[j].setSize(0.037f);
			CurrentTheme.Deck[j].hide();

			Loading.incrementSpriteFrame();
			agk::Sync();
		}
	}
}*/

void app::setAnimatedSpriteData(void)
{
    float factor = 0.0f;
#if (PLATFORM == MOBILE)
	TrumpSymbol.setAnimatedData(25, 25, 32, "load suit rotation.png", loadingImage);
#else
    TrumpSymbol.setAnimatedData(75, 75, 32, "load suit rotation.png", loadingImage);
#endif
	TrumpSymbol.setAnimatedFrameTo(1);
	TrumpSymbol.setPriority(5);
    
#if (PLATFORM == MOBILE)
    factor = -0.5;
#endif
    
	if (tableTopStyle == 0)
	{
		TrumpSymbol.setSize(4.25f + factor);
		TrumpSymbol.display(91.25f, 70.0f);
	}
	else if (tableTopStyle == 1)
	{
		TrumpSymbol.setSize(5.0f + factor);
		TrumpSymbol.display(91.5f, 69.0f);
	}
	else
	{
		TrumpSymbol.setSize(5.0f + factor);
		TrumpSymbol.display(91.0f, 69.0f);
	}
	TrumpSymbol.hide();

	Loading.incrementSpriteFrame();
	agk::Sync();
}

void app::setSpriteData(void)
{
	/*******************************
	*		Steps to setup a sprite!
	*		1: SetData(imageNo, spriteNo, "Sprite Name")
	*		2: setSize or setSize
	*		3: setPriority
	*		4: display
	*		5: hide
	*******************************/
	//int tempPImage = HandResults.getPImage();
	//char temp[64];

	//Step1: Set Data Field-------------------------------------------------
    unsigned int imgNum;
    
    imgNum = HandResults.Parent.getImageNumber("woodoval.png");
	NBack.setImageNumber(imgNum);
	SBack.setImageNumber(imgNum);
	WBack.setImageNumber(imgNum);
	EBack.setImageNumber(imgNum);
    
#if DEMOBUILD
	DemoEndBack.setImageNumber(imgNum);
#endif

	Loading.incrementSpriteFrame();
	agk::Sync();
	//End Step 1------------------------------------------------------

	//Begin Step 2: Scale/Stretch/Size--------------------------------
	NBack.setSize(13.5f);
	EBack.setSize(13.5f);
	SBack.setSize(13.5f);
	WBack.setSize(13.5f);
	DemoEndBack.setSize(85.0f, 35.0f, true);

	Loading.incrementSpriteFrame();
	agk::Sync();
	//End Step 2-------------------------------------------------------

	//Start Step 3: Set Priority---------------------------------------
	NBack.setPriority(30);  //need to be high to get over cards
	SBack.setPriority(30);
	WBack.setPriority(30);
	EBack.setPriority(30);
	DemoEndBack.setPriority(10000);

	Loading.incrementSpriteFrame();
	agk::Sync();
	//End Step 3--------------------------------------------------------

	//Start Step 4: display--------------------------------------------

	//End Step 4------------------------------------------------------------

	//Start Step 5: hide---------------------------------------------------

	//Options.hide();

	NBack.hide();
	SBack.hide();
	WBack.hide();
	EBack.hide();
	DemoEndBack.hide();

	Loading.incrementSpriteFrame();
	agk::Sync();
	//End Step 5------------------------------------------------------------

	//Optional Step 6: Setting Imprint, only for shrink close/grow open effects
	NBack.setImprint(43.0f,8.0f);
	SBack.setImprint(43.0f,84.5f);
	WBack.setImprint(4.3f,36.5f);
	EBack.setImprint(81.75f,36.5f);

	if (DEMOBUILD)
	{
		DemoEndBack.setImprint(7.0f, 25.0f);
		DemoEndBack.setAlpha(220);


		while (!DemoEndBack.hasShrunk())
			DemoEndBack.updateShrinkClose(-1);
	}

	Loading.incrementSpriteFrame();
	agk::Sync();
	//End Step 6------------------------------------------------------------
}

void app::setNumberData(void)
{

}

char* app::fileLoc(const char fileName[], char newFilename[])
{
	strcpy(newFilename, themeDir);
	strcat(newFilename, fileName);

	if (agk::GetFileExists(newFilename))
		return newFilename;
	else
	{
		strcpy(newFilename, "default/");
		strcat(newFilename, fileName);

		return newFilename;
	}
}

short unsigned int app::myLoadImage(const char fileLoc[], short unsigned int imageNum)
{
	unsigned short int newImageNum = 0;
    short queue = 0;
    
    if (fileLoc[0] == 'd')
        queue = 1;

	if (imageNum != 0)
	{
		if (agk::GetFileExists(fileLoc))
		{
			agk::LoadImage(imageNum, fileLoc);
            
            if (fileLoc[0] != 'd')
                addToQueue(imageNum, queue);
		}

		return imageNum;
	}

    newImageNum = agk::LoadImage(fileLoc);

    if (fileLoc[0] != 'd')
        addToQueue(newImageNum, queue);
    
	return newImageNum;
}

//no checks! make sure the file exists before calling!
/*void app::loadDefaultSprites(char dir[])
{
	char temp[64];

	myLoadImage(fileLoc("sound_btn_off.png", temp));
	myLoadImage(fileLoc("sound_btn_on.png", temp));

	Loading.incrementSpriteFrame();
	agk::Sync();

	myLoadImage(fileLoc("board table.png", temp));
	myLoadImage(fileLoc("board_background.png", temp));
	myLoadImage(fileLoc("board_header.png", temp));
	myLoadImage(fileLoc("board_hand score.png", temp));
	myLoadImage(fileLoc("board_total score.png", temp));

	myLoadImage(fileLoc("Suit Rotation.png", temp));

	Loading.incrementSpriteFrame();
	agk::Sync();

	myLoadImage(fileLoc("Options_Off.png", temp));
	myLoadImage(fileLoc("Options_On.png", temp));
	myLoadImage(fileLoc("Options_Down.png", temp));

	Loading.incrementSpriteFrame();
	agk::Sync();

	myLoadImage(fileLoc("Check box.png", temp));
	myLoadImage(fileLoc("Check box with check.png", temp));

	Loading.incrementSpriteFrame();
	agk::Sync();

	myLoadImage(fileLoc("Resume_Off.png", temp));
	myLoadImage(fileLoc("Resume_On.png", temp));
	myLoadImage(fileLoc("Resume_Down.png", temp));
	myLoadImage(fileLoc("Main_Menu_Off.png", temp));
	myLoadImage(fileLoc("Main_Menu_On.png", temp));
	myLoadImage(fileLoc("Main_Menu_Down.png", temp));
	myLoadImage(fileLoc("New_Game_Off.png", temp));
	myLoadImage(fileLoc("New_Game_On.png", temp));
	myLoadImage(fileLoc("New_Game_Down.png", temp));

	Loading.incrementSpriteFrame();
	agk::Sync();

	//Text Font


	Loading.incrementSpriteFrame();
	agk::Sync();

	myLoadImage(fileLoc("background_g.jpg", temp));    //themes
	myLoadImage(fileLoc("background_r.jpg", temp));    //themes
	myLoadImage(fileLoc("background_a.jpg", temp));    //themes
	myLoadImage(fileLoc("background_f.jpg", temp));    //themes
	myLoadImage(fileLoc("background_e.jpg", temp));    //themes
	myLoadImage(fileLoc("background_w.jpg", temp));    //themes

	Loading.incrementSpriteFrame();
	agk::Sync();
}*/

void app::initDisplay(void)
{
	

}

void app::initVars()
{
	menuPressed=true;
	ingamebutton=true;

#if DEMOBUILD
	demoOver = false;
#endif
	copyOnce = false;
	visScreen = 0;
	calcOnce = false;
	soundOn = true;
	wipingCards = false;
	//count = 0;
	// = 100;
#if DEMOBUILD
	dealer = 0;
#else
		//dealer = agk::Random(0, 3);
    dealer = arc4random() % 4;
#endif

    initQueue();
	language = ENGLISH;
	turn = (dealer+1)%4;
	//int state = 0;
	round = 0;
	foundLocation = false;
	playingAnimation = false;
	passInitialAnim = false;
	quit = false;
	menuChoice = 0;
	mouseX = 0;
	mouseY = 0;
	mouseClick = false;
	cardsRevealed = false;
	hand = 0;
	pauseGame = false;
	tableTopStyle = 0; //default
	contFlag = true;  //for animating the cards moving to whoever took the trick
	hScore = 0;
	vScore = 0;
	mouseDelay = 0;
	delayStep = 0;
	bidWinner = -1;

	Loading.incrementSpriteFrame();
	agk::Sync();

	West.setPlayerID(WEST);
	North.setPlayerID(NORTH);
	East.setPlayerID(EAST);
	South.setPlayerID(SOUTH);

	Loading.incrementSpriteFrame();
	agk::Sync();
}


void toggleLayout(Sprite *View)
{
	View->updateShrinkClose(-1);

	switch(View->getImageNumber())
	{
	case 30:
		View->changeImage(31);
		break;
	case 31:
		View->changeImage(30);
		break;
	case 32:
		View->changeImage(33);
		break;
	case 33:
		View->changeImage(32);
		break;
	}

	View->updateGrowOpen(100);
}

void toggleDebug()
{
	debug = !debug;
}

const float findTargetX(short int player)
{
	if (player == WEST)
		return 100*(WEST_LOC_X/1024);
	else if (player == NORTH)
		return 100*(NORTH_LOC_X);
	else if (player == EAST)
		return 100*(EAST_LOC_X/1024);
	else if (player == SOUTH)
		return 100*(SOUTH_LOC_X/1024);
	else
		return -1;
}

const float findTargetY(short int player)
{
	if (player == WEST)
		return (float)(100*(WEST_LOC_Y/768.0));
	else if (player == NORTH)
		return (float)(100*(NORTH_LOC_Y/768.0));
	else if (player == EAST)
		return (float)(100*(EAST_LOC_Y/768.0));
	else if (player == SOUTH)
		return (float)(100*(SOUTH_LOC_Y/768.0));
	else
		return -1.0f;
}

void app::displayAllKnown(void)
{
	//char suit[9];
	//char rank[6];

/*	dbSetTextSize(20);
	dbText(x[WEST], y[NORTH], "WEST");
	dbText(x[NORTH], y[NORTH], "NORTH");
	dbText(x[EAST], y[NORTH], "EAST");
	dbText(x[SOUTH], y[NORTH], "SOUTH");
	dbLine(x[WEST], y[NORTH]+20, x[SOUTH]+90, y[NORTH]+20);
	y[WEST] += 20;
	y[NORTH] += 20;
	y[EAST] += 20;
	y[SOUTH] += 20;

	for(int i = 0; i <= SPADES; i++)
	{
		switch (i)
		{
		case HEARTS:
			strcpy(suit, "HEARTS");
			break;
		case DIAMONDS:
			strcpy(suit, "DIAMONDS");
			break;
		case SPADES:
			strcpy(suit, "SPADES");
			break;
		case CLUBS:
			strcpy(suit, "CLUBS");
		}

		for (int j = 0; j <= JACK; j++)
		{
			switch (j)
			{
			case ACE:
				strcpy(rank, "ACE");
				break;
			case TEN:
				strcpy(rank, "TEN");
				break;
			case KING:
				strcpy(rank, "KING");
				break;
			case QUEEN:
				strcpy(rank, "QUEEN");
				break;
			case JACK:
				strcpy(rank, "JACK");
				break;
			}

			if (West.known[j][i] > -1)
			{
				if (West.newKnown[j][i] != -1)
					dbInk(dbRGB(255, 0, 0), dbRGB(0, 0, 0));
				else
					dbInk(dbRGB(0, 0, 0), dbRGB(0, 0, 0));

				dbSetCursor(x[WEST], y[WEST]);
				dbPrint((double) West.known[j][i]);
				dbText(x[WEST]+10, y[WEST], rank);
				dbText(x[WEST]+70, y[WEST], "of");
				dbText(x[WEST]+90, y[WEST], suit);
				y[WEST] += 20;
			}

			if (North.known[j][i] > -1)
			{
				if (North.newKnown[j][i] > -1)
					dbInk(dbRGB(255, 0, 0), dbRGB(0, 0, 0));
				else
					dbInk(dbRGB(0, 0, 0), dbRGB(0, 0, 0));
				dbSetCursor(x[NORTH], y[NORTH]);
				dbPrint((double) North.known[j][i]);
				dbText(x[NORTH]+10, y[NORTH], rank);
				dbText(x[NORTH]+70, y[NORTH], "of");
				dbText(x[NORTH]+90, y[NORTH], suit);
				y[NORTH] += 20;
			}

			if (East.known[j][i] > -1)
			{
				if (East.newKnown[j][i] > -1)
					dbInk(dbRGB(255, 0, 0), dbRGB(0, 0, 0));
				else
					dbInk(dbRGB(0, 0, 0), dbRGB(0, 0, 0));
				dbSetCursor(x[EAST], y[EAST]);
				dbPrint((double) East.known[j][i]);
				dbText(x[EAST]+10, y[EAST], rank);
				dbText(x[EAST]+70, y[EAST], "of");
				dbText(x[EAST]+90, y[EAST], suit);
				y[EAST] += 20;
			}

			if (South.known[j][i] > -1)
			{
				if (South.newKnown[j][i] > -1)
					dbInk(dbRGB(255, 0, 0), dbRGB(0, 0, 0));
				else
					dbInk(dbRGB(0, 0, 0), dbRGB(0, 0, 0));
				dbSetCursor(x[SOUTH], y[SOUTH]);
				dbPrint((double) South.known[j][i]);
				dbText(x[SOUTH]+10, y[SOUTH], rank);
				dbText(x[SOUTH]+70, y[SOUTH], "of");
				dbText(x[SOUTH]+90, y[SOUTH], suit);
				y[SOUTH] += 20;
			}

			if ((j == JACK) && (i == SPADES))
			{
				dbInk(dbRGB(255, 0, 0), dbRGB(255, 0, 0));
				dbLine(x[WEST], y[WEST], x[WEST]+110, y[WEST]);
				dbLine(x[NORTH], y[NORTH], x[NORTH]+110, y[NORTH]);
				dbLine(x[EAST], y[EAST], x[EAST]+110, y[EAST]);
				dbLine(x[SOUTH], y[SOUTH], x[SOUTH]+110, y[SOUTH]);
				for (int k = HEARTS; k <= SPADES; k++)
				{
					if (West.trumpingSuit[k])
					{
						if (k == HEARTS)
							dbText(x[WEST], y[WEST], "HEARTS");
						else if (k == CLUBS)
							dbText(x[WEST], y[WEST], "CLUBS");
						else if (k == DIAMONDS)
							dbText(x[WEST], y[WEST], "DIAMONDS");
						else if (k == SPADES)
							dbText(x[WEST], y[WEST], "SPADES");

						y[WEST] += 20;
					}

					if (South.trumpingSuit[k])
					{
						if (k == HEARTS)
							dbText(x[SOUTH], y[SOUTH], "HEARTS");
						else if (k == CLUBS)
							dbText(x[SOUTH], y[SOUTH], "CLUBS");
						else if (k == DIAMONDS)
							dbText(x[SOUTH], y[SOUTH], "DIAMONDS");
						else if (k == SPADES)
							dbText(x[SOUTH], y[SOUTH], "SPADES");

						y[SOUTH] += 20;
					}

					if (East.trumpingSuit[k])
					{
						if (k == HEARTS)
							dbText(x[EAST], y[EAST], "HEARTS");
						else if (k == CLUBS)
							dbText(x[EAST], y[EAST], "CLUBS");
						else if (k == DIAMONDS)
							dbText(x[EAST], y[EAST], "DIAMONDS");
						else if (k == SPADES)
							dbText(x[EAST], y[EAST], "SPADES");

						y[EAST] += 20;
					}

					if (North.trumpingSuit[k])
					{
						if (k == HEARTS)
							dbText(x[NORTH], y[NORTH], "HEARTS");
						else if (k == CLUBS)
							dbText(x[NORTH], y[NORTH], "CLUBS");
						else if (k == DIAMONDS)
							dbText(x[NORTH], y[NORTH], "DIAMONDS");
						else if (k == SPADES)
							dbText(x[NORTH], y[NORTH], "SPADES");

						y[NORTH] += 20;
					}
				}
			}
		}
	}*/
}

void app::displayPlayerControlBubble(void)
{
    short int tempBid = bid + 1;
    float offset = 0.0f;
    
    if (PLATFORM == MOBILE)
        offset = -2.0f;

	if (tableTopStyle != 3)
		CurrentTheme.BCBubble.display(27.5f, 32.0f + offset);
	else
		CurrentTheme.BCBubble.display(27.5f, 23.5f + offset);

	if ((tableTopStyle == 0) || (tableTopStyle == 5))
	{
		for (short int i = 0; i < 10; i++)
			CurrentTheme.BCBubble.BidValue.setLocation(i, 54.0f - (6.5f * i), 44.5f, 0); //2, 0

		CurrentTheme.BCBubble.BidValue.setValue(bid+1);
	}
    else if (tableTopStyle == 1)
    {
        for (short i = 0; i < 10; i++)
            CurrentTheme.BCBubble.BidValue.setLocation(i, 54.0f - (6.5f * i), 49.5, 0);
        
        CurrentTheme.BCBubble.BidValue.setValue(bid+1);
    }
	else if (tableTopStyle == 2)
	{
		for (short int i = 0; i < 10; i++)
			CurrentTheme.BCBubble.BidValue.setLocation(i, 54.0f - (6.5f * i), 49.5f, 0); //2, 0

		CurrentTheme.BCBubble.BidValue.setValue(bid+1);
	}
	else if (tableTopStyle == 3)
	{
		for (short int i = 0; i < 10; i++)
			CurrentTheme.BCBubble.BidValue.setLocation(i, 53.0f - (5.5f * i), 46.0f, 0); //2, 0

		CurrentTheme.BCBubble.BidValue.setValue(bid+1);
	}

	if (CurrentTheme.BCBubble.BidValue.getValue() > 99)
		CurrentTheme.BCBubble.BidValue.display(2, 1);
	else
		CurrentTheme.BCBubble.BidValue.display(2, 0);

	CurrentTheme.BCBubble.BidValue.display(1, tempBid%100/10);
	CurrentTheme.BCBubble.BidValue.display(0, tempBid%10);

	CurrentTheme.BCBubble.show();
}

bool app::southBid()
{
//////////////////////////////////////////////////////////////////////////////////////////
//Start of MeldBid controls!
//////////////////////////////////////////////////////////////////////////////////////////
	buttonDelay = 0.5f;
#if (IOS == OS)
    #if (PLATFORM == TABLET) // +/- for Red/Ancient , +/- for Green,  , Bid for Red/Ancient , Bid for Green, Pass for Red/Ancient , Pass for Green
    const float yMinValue[6] = { 48.25f, 39.3f, 38.25f, 33.0f, 62.0f, 57.25f };
    const float yMaxValue[6] = { 62.0f, 59.5f, 48.25f, 42.25f, 71.5f, 69.25f };
    #elif (PLATFORM == MOBILE)
    const float yMinValue[6] = { 50.0f, 40.0f, 35.0f, 30.0f, 65.0f, 60.0f };
    const float yMaxValue[6] = { 65.0f, 60.0f, 50.0f, 45.0f, 80.0f, 80.0f };
    #endif
#endif

	if (NewBidGame.getPass(SOUTH))
		return true;

	if (!CurrentTheme.BCBubble.isVisible())
		displayPlayerControlBubble();

	if (VisualBid == 255)
	{
		if (bid == 49)
            VisualBid = 51;
		else if (bid <60)
			VisualBid = bid + 1;
		else
			VisualBid = bid + 5;
	}

	if (CurrentTheme.BCBubble.BidValue.getValue() != VisualBid)
	{
		PointClick.playOnce();
		CurrentTheme.BCBubble.BidValue.incrementTo(VisualBid);
	}

	if (mouseClick)
	{
		//BidPlus
		if ((mouseX >= (60.9f )) && (mouseX <= (71.8f )))
		{
			if ((tableTopStyle != 0) && (tableTopStyle != 5))
			{
				if ((mouseY >= (yMinValue[0] )) && (mouseY <= (yMaxValue[0] )))
					menuChoice = 4;
			}
			else
			{
				if ((mouseY >= (yMinValue[1])) && (mouseY <= (yMaxValue[1])))
					menuChoice = 4;
			}
		}

		//BidMinus
		if ((mouseX >= (28.1f )) && (mouseX <= (40.0f )))
		{
			if ((tableTopStyle != 0) && (tableTopStyle != 5))
			{
				if ((mouseY >= (yMinValue[0])) && (mouseY <= (yMaxValue[0])))
					menuChoice = 2;
			}
			else
			{
				if ((mouseY >= (yMinValue[1])) && (mouseY <= (yMaxValue[1])))
					menuChoice = 2;
			}
		}

		//Bid
		if ((mouseX >= (39.25f )) && (mouseX <= (60.75f )))
		{
			if ((tableTopStyle != 0) && (tableTopStyle != 5))
			{
				if (tableTopStyle != 3)
				{
					if ((mouseY >= (yMinValue[2])) && (mouseY <= (yMaxValue[2])))
						menuChoice = 1;
				}
				else
				{
					if ((mouseY >= (27.0f )) && (mouseY <= (38.5f )))
						menuChoice = 1;
				}
			}
			else
			{
				if ((mouseY >= (yMinValue[3])) && (mouseY <= (yMaxValue[3])))
					menuChoice = 1;
			}
		}

		//BidPass
		if ((mouseX >= (39.25f )) && (mouseX <= (60.75f )))
		{
			if ((tableTopStyle != 0) && (tableTopStyle != 5))
			{
				if ((mouseY >= (yMinValue[4])) && (mouseY <= (yMaxValue[4])))
					menuChoice = 3;
			}
			else
			{
				if ((mouseY >= (yMinValue[5])) && (mouseY <= (yMaxValue[5])))
					menuChoice = 3;
			}
		}

		buttonDelay = 1.0f;
	}

	if (menuChoice)
	{
		mouseClick = false;

		if ((menuChoice == 4) && (VisualBid == 195))
		{
			delayStep = 0;
			menuChoice = 0;
			return false;
		}

		if ((menuChoice == 2) && (VisualBid == bid + 1))
		{
			delayStep = 0;
			menuChoice = 0;
			return false;
		}

		if(CurrentTheme.BCBubble.animation(menuChoice, delayStep))
		{
			if(menuChoice == 4) //BidPlus
			{
				//Increase bid by 1 if < 60, and by 5 if >= 60
				if (VisualBid < 60)
					VisualBid++;

				else if (VisualBid >= 60)
					VisualBid+=5;

				delayStep = 0;
				menuChoice = 0;
				return false;
			}
			else if (menuChoice == 2) //BidMinus
			{
				//Decrease bid by 1 if < 60, and by 5 if >= 60
				//buttonAnimation(&BidMinusDown);

				if ((VisualBid <= 60) && (VisualBid > bid + 1))
					VisualBid--;
				else if ((VisualBid > 60) && (VisualBid > bid + 5))
					VisualBid-=5;

				delayStep = 0;
				menuChoice = 0;
				return false;
			}
			else if (menuChoice == 1) //Bid
			{
				//Pass the final bid
				if (count < 4)
					NewBidGame.playerMeldBid(&South, &North, VisualBid);
				else
					NewBidGame.playerTakeBid(&South, &North, count/4, VisualBid);

				CurrentTheme.BCBubble.BidValue.hideAll();

				VisualBid = 255;
				delayStep = 0;
				menuChoice = 0;

				return true;
			}
			else if (menuChoice == 3) //BidPass
			{
				//Pass on your turn

				if (count < 4)
					NewBidGame.playerMeldBid(&South, &North, 0);
				else
					NewBidGame.playerTakeBid(&South, &North, count/4, 0);

				for (short int i = 0; i < 3; i++)
					CurrentTheme.BCBubble.BidValue.hide(i, CurrentTheme.BCBubble.BidValue.getDigit(i));

				VisualBid = 255;
				delayStep = 0;
				menuChoice = 0;

				return true;
			}
		}
	}
	return false;
}

void app::southTrumpSelection()
{
//////////////////////////////////////////////////////////////////////////////////////////
//Start of TrumpSelection
//////////////////////////////////////////////////////////////////////////////////////////
	CurrentTheme.TSBubble.show();

	short int checkClubs = South.getNumOfMarriages(CLUBS);
	short int checkDiamonds = South.getNumOfMarriages(DIAMONDS);
	short int checkHearts = South.getNumOfMarriages(HEARTS);
	short int checkSpades = South.getNumOfMarriages(SPADES);
    
#if (OS == IOS)
    #if (PLATFORM == TABLET) // Hearts/Spades , Clubs/Diamonds
    const float yMinValue[2] = { 33.5f, 49.5f };
    const float yMaxValue[2] = { 49.5f, 66.0f };
    #elif (PLATFORM == MOBILE)
    const float yMinValue[2] = { 35.0f, 55.0f};
    const float yMaxValue[2] = { 55.0f, 80.0f};
    #endif
#endif

	if (checkClubs == 0)
	{
		CurrentTheme.TSBubble.Clubs.ButtonUp.hide();
		CurrentTheme.TSBubble.Clubs.ButtonGray.show();
	}

	if (checkDiamonds == 0)
	{
		CurrentTheme.TSBubble.Diamonds.ButtonUp.hide();
		CurrentTheme.TSBubble.Diamonds.ButtonGray.show();
	}

	if (checkHearts == 0)
	{
		CurrentTheme.TSBubble.Hearts.ButtonGray.show();
		CurrentTheme.TSBubble.Hearts.ButtonUp.hide();
	}

	if (checkSpades == 0)
	{
		CurrentTheme.TSBubble.Spades.ButtonGray.show();
		CurrentTheme.TSBubble.Spades.ButtonUp.hide();
	}

	if (mouseClick)
	{
		//Club location
		if ((mouseX >= (28.61f )) && (mouseX <= (47.5f )))
		{
				if ((mouseY >= (yMinValue[1])) && (mouseY <= (yMaxValue[1])))
					menuChoice = 2;
		}

		//Diamond location
		if ((mouseX > (47.5f )) && (mouseX <= (67.5f )))
		{
				if ((mouseY >= (yMinValue[1])) && (mouseY <= (yMaxValue[1])))
					menuChoice = 3;
		}

		//Heart location
		if ((mouseX >= (28.61f )) && (mouseX <= (47.5f )))
		{
				if ((mouseY >= (yMinValue[0])) && (mouseY < (yMaxValue[0])))
					menuChoice = 1;
		}

		//Spade location
		if ((mouseX > (47.5f )) && (mouseX <= (67.5f )))
		{
				if ((mouseY >= (yMinValue[0])) && (mouseY < (yMaxValue[0])))
					menuChoice = 4;
		}

	}

	if (CurrentTheme.TSBubble.animation(menuChoice, delayStep))
	{
		if(menuChoice == 2) //Club selection
		{
			if(checkClubs != 0)
			{
				NewTrickGame.setTrumpSuit(CLUBS);
				menuChoice = 0;
			}
		}
		else if (menuChoice == 3) //Diamond selection
		{
			if (checkDiamonds != 0)
			{
				NewTrickGame.setTrumpSuit(DIAMONDS);
				menuChoice = 0;
			}
		}
		else if (menuChoice == 1) //Heart location
		{
			if (checkHearts != 0)
			{
				NewTrickGame.setTrumpSuit(HEARTS);
				menuChoice = 0;
			}
		}
		else if (menuChoice == 4) //Spade location
		{
			if (checkSpades != 0)
			{
				NewTrickGame.setTrumpSuit(SPADES);
				menuChoice = 0;
			}
		}
	}
}

void app::resetHand(void)
{
	//TrumpSymbol.~AnimatedSprite();
	NewBidGame.reset();
	NewTrickGame.reset();
	ShuffledDeck.reset(DEMOBUILD);
	NewGame.resetHand();
	West.reset();
	North.reset();
	East.reset();
	South.reset();
	HandResults.reset();
	HandResults.hide();

	CurrentTheme.BidScore.hide(2, CurrentTheme.BidScore.getDigit(2));
	CurrentTheme.BidScore.hide(1, CurrentTheme.BidScore.getDigit(1));
	CurrentTheme.BidScore.hide(0, CurrentTheme.BidScore.getDigit(0));

	hScore = NewGame.getScore(0);
	vScore = NewGame.getScore(1);
	dealer = (dealer + 1) % 4;
	hand++;

	//SBack.setImprint(44.0f,84.5f);
	SBack.hide();

	//WBack.setImprint(4.5f,40.0f);
	WBack.hide();

	//EBack.setImprint(81.7f,40.0f);
	EBack.hide();

	NBack.hide();
}

void app::inGameMenuButton(void)
{
	if(ingamebutton)
	{
		if (mouseClick)
		{
			if ((mouseX >= (74.4f )) && (mouseX <= (98.0f )))
			{
					if ((mouseY >= 0.0f) && (mouseY <= (15.59f )))
						menuChoice = -1;
			}
		}

		if(menuChoice == -1)
		{
			if (CurrentTheme.InGameMenuButton.animation(delayStep))
			{
				CurrentTheme.hide();

				if (NewGame.getState() == MELDING)
					CurrentTheme.BidMeldBubbles.hide();

				NBack.hide();
				EBack.hide();
				WBack.hide();
				SBack.hide();

				gameResult.hide();
				gameResult4.hide();

				hideAllText();

				delayStep = 0;
				menuChoice = 0;
				
				if (CurrentTheme.BidScore.isVisible())
					CurrentTheme.BidScore.hideAll();
                
                //Options.setup(&Loading);

				NewGame.toggleXState(OPTIONS);
				Options.Background.updateGrowOpen(100.0f, 100.0f);
			}
		}
	}
}

void app::hideAllText(void)
{
	ChooseTrump.hide();
	DemoEndText.hide();
    gameResult.hide();
    gameResult4.hide();
    MeldFail.hide();
    MeldAmount.hide();
	OptionsHelp.hide();
    Legal.hide();
	SwipeHelp.hide();
    TapScreen.hide();
    GameOver.hide();
}

void app::showAllCards(void)
{
	for (int i = 0; i < 80; i++)
		CurrentTheme.Deck[i].turnFaceUp();
}

void app::findValueForDebugging(float value)
{
    int tempValue;
    
    tempValue = value;
}

void addToQueue(unsigned int imageNumber, short queue)
{
    if (queue == 0)
        themeQueue[themeQueuePointer++] = imageNumber;
    /*else
        menuQueue[menuQueuePointer++] = imageNumber;*/
}

void app::clearQueue(AnimatedSprite *Symbol, short queue)
{
    if (queue == 0)
    {
        for (int i = themeQueuePointer - 1; i > 0; i--)
        {
            agk::DeleteImage(themeQueue[i]);
        
            if (i % 5 == 0)
            {
				Symbol->setFrame(Symbol->getCurrentFrame() + 1);
                agk::Sync();
            }
        }
        
        themeQueuePointer = 0;
    }
    /*else
    {
        for (int i = menuQueuePointer - 1; i > 0; i--)
        {
            agk::DeleteImage(menuQueue[i]);
            
            if (i % 5 == 0)
            {
                Symbol->incrementSpriteFrame();
                agk::Sync();
            }
        }
        
        menuQueuePointer = 0;
    }*/
}

void initQueue(void)
{
    themeQueuePointer = 0;
    menuQueuePointer = 0;
}

////////////From PinochleGame.cpp//////////////
void app::reset(void)
{
	stateStart = false;
	stateWaitingForAnimation = false;
	stateBidding = false;
	stateSortingHands = false;
	stateDealing = false;
	statePlaying = false;
	stateMelding = false;
	stateMenuScreen = true;		
	stateInGameMenu = false;
	stateInGameOptions = false;
	stateGrowBackground = false;
	stateIncrementing = false;
	stateScoreboard = false;
	horizontalMeld = -1;
	verticalMeld = -1;
	horizontalScore = 0;
	verticalScore = 0;
	hAmountToGet = -1;
	vAmountToGet = -1;
}

void app::resetState(void)
{
	stateStart = false;
	stateLoading = false;
	stateWaitingForAnimation = false;
	stateBidding = false;
	stateSortingHands = false;
	stateDealing = false;
	statePlaying = false;
	stateMelding = false;
	stateMenuScreen = true;		
	stateInGameMenu = false;
	stateInGameOptions = false;
	stateGrowBackground = false;
	stateIncrementing = false;
	stateScoreboard = false;
}

void app::resetGame(void)
{
	stateStart = false;
	stateWaitingForAnimation = false;
	stateBidding = false;
	stateSortingHands = false;
	stateDealing = false;
	statePlaying = false;
	stateMelding = false;
	stateMenuScreen = false;		
	stateInGameMenu = false;
	stateInGameOptions = false;
	stateGrowBackground = false;
	stateLoading = false;
	stateScoreboard = false;
	horizontalMeld = -1;
	verticalMeld = -1;
	horizontalScore = 0;
	verticalScore = 0;
	hAmountToGet = -1;
	vAmountToGet = -1;
}

void app::resetHand(void)
{
	AllPlayers[WEST]->reset();
	horizontalMeld = -1;
	verticalMeld = -1;
	hAmountToGet = -1;
	vAmountToGet = -1;
}

unsigned short app::getState()
{
	if (stateLoading)
		return LOADING;
	if (stateMenuScreen)
		return MENU;
	if (stateOptions)
		return OPTIONS;
	if (stateInGameMenu)
		return INGAMEMENU;
	if (stateInGameOptions)
		return INGAMEOPTIONS;
	if (stateGrowBackground)
		return GROWBACKGROUND;
	if (stateWaitingForAnimation)
		return ANIMATION;	
	if (stateStart)
		return START;
	if (stateDealing)
		return DEALING;
	if (stateSortingHands)
		return SORTING;
	if (stateBidding)
		return BIDDING;
	if (stateMelding)
		return MELDING;
	if (statePlaying)
		return PLAYING;
	if (stateScoreboard)
		return SCOREBOARD;
    
    if (prevState != -1) //fix an issue where no states are active
        return prevState;
    
	return -1;
}

bool app::isStateActive(short int state)
{
	switch (state)
	{
	case LOADING:
		if (stateLoading)
			return true;
		break;
	case MENU:
		if(stateMenuScreen)
			return true;         
        break;
	case OPTIONS:
		if (stateOptions)
			return true;
		break;
	case START:
		if(stateStart)
			return true;
		break;
	case INGAMEMENU:
		if (stateInGameMenu)
			return true;
		break;
	case INGAMEOPTIONS:
		if (stateInGameOptions)
			return true;
		break;
	case GROWBACKGROUND:
		if (stateGrowBackground)
			return true;
		break;
	case DEALING:
		if(stateDealing)
			return true;
		break;
	case ANIMATION:
		if(stateWaitingForAnimation)
			return true;
		break;
	case SORTING:
		if (stateSortingHands)
			return true;
		break;
	case BIDDING:
		if (stateBidding)
			return true;
		break;
	case MELDING:
		if (stateMelding)
			return true;
		break;
	case PLAYING:
		if (statePlaying)
			return true;
		break;
	case SCOREBOARD:
		if (stateScoreboard)
			return true;
		break;
	default:
		break;
	}

	return false;

}
bool app::getSpecificAnimState(void)
{
	if (statePlaying)
		return true;
	else
		return false;
}

	
void app::toggleXState(short int state)
{
	short temp = getState();
	
    if (state == temp)
        prevState = temp;

	if (state == LOADING)
		stateLoading = !stateLoading;
	else if (state == START)
		stateStart = !stateStart;
	else if (state == OPTIONS)
		stateOptions = !stateOptions;
	else if (state == BIDDING)
		stateBidding = !stateBidding;
	else if (state == PLAYING)
		statePlaying = !statePlaying;
	else if (state == ANIMATION)
		stateWaitingForAnimation = !stateWaitingForAnimation;
	else if (state == SORTING)
		stateSortingHands = !stateSortingHands;
	else if (state == DEALING)
		stateDealing = !stateDealing;
	else if (state == MELDING)
		stateMelding = !stateMelding;
	else if (state == MENU)
		stateMenuScreen = !stateMenuScreen;   
	else if (state == INGAMEMENU)
		stateInGameMenu = !stateInGameMenu;
	else if (state == INGAMEOPTIONS)
		stateInGameOptions = !stateInGameOptions;
	else if (state == GROWBACKGROUND)
		stateGrowBackground = !stateGrowBackground;
	else if (state == SCOREBOARD)
		stateScoreboard = !stateScoreboard;
}

unsigned short app::getPrevState(void)
{
	short int curState = getState();

	if ((curState != ANIMATION) && (curState != OPTIONS))
		return -1;
	else
		return prevState;
}
