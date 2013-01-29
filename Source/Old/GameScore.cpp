#include "GameScore.h"
#include "agk.h"

GameScore::GameScore(void)
{
	horizontalScore = 0;
	verticalScore = 0;
}

GameScore::~GameScore(void)
{
}

void GameScore::init()
{
	Text TempText = Text();
	unsigned int parentImageNumber = 0;

	TempText.init("default/Scoreboards.png");
	ParentImage->parentInit(TempText);
	parentImageNumber = ParentImage->getImageNumber();
    
	TempText.setString("board_background.png");
	Background->subInit(parentImageNumber, TempText);

	TempText.setString("board_header.png");
	Header->subInit(parentImageNumber, TempText);

    TempText.setString("board_hand score.png");
	for (short int i = 0; i < 11; i++)
		MiddleSection[i]->subInit(parentImageNumber, TempText);
	
	TempText.setString("board_total score.png");
	Total->subInit(parentImageNumber, TempText);

	setNumberData();
	
	Background->setSize(62.5f, 78.0f);
	Header->setSize(58.0f, 4.9f);
	for (short int i = 0; i < 11; i++)
		MiddleSection[i]->setSize(58.0f, 4.9f);
	Total->setSize(58.0f, 4.9f);
		
	setDepth(9050);

	Background->setPosition(20.0f, 15.0f);
	
	for (short int i = 0; i < 11; i++)
		MiddleSection[i]->setPosition(21.0f, 22.5f + (5.0f * i));
	Header->setPosition(21.0f, 17.0f);
	Total->setPosition(21.0f, 77.0f);	
	
	///step 5: hide
	hide();

	///step 6 (optional): set imprint

	///////////////Text
	/*for (char i = 0; i < 12; i++)
	{
		for (char j = 0; j < 2; j++)
		{
			MinusSign[i][j].createT("-");
			MinusSign[i][j].color(0, 0, 0);
			MinusSign[i][j].position(66.0f - (14.25f * j), 23.5f + (4.95f * i));
			MinusSign[i][j].hide();
			showMinus[i][j] = false;
		}
	}*/
}

void GameScore::setNumberData()
{
	Text Dir = Text();

	Dir.init("default/");

	for (int i = 0; i < 12; i++)
	{
		for (short int j = 0; j < 3; j++)
			GameScoreData[i][j]->init(Dir);
	}

	for (short int i = 0; i < 3; i++)
	{
		for (short int g = 0; g < 12; g++) //rows
		{
			for (short int h = 0; h < 3; h++) //columns
			{
				GameScoreData[g][h]->setLocation(i, 73.75f - ((1.75f * i) + (h * 14.25f)), 23.75f + (4.95f * g), -6.0f, -0.5f);
			}
		}
	}

	for (short int g = 0; g < 12; g++)
	{
		for (short int h = 0; h < 3; h++)
		{
			GameScoreData[g][h]->setDepth(9048);
			GameScoreData[g][h]->setSize(1.5f);
			GameScoreData[g][h]->setValue(0);
			GameScoreData[g][h]->hideAll();
		}
	}
}

void GameScore::hide(void)
{
	Background->setVisible(false);

	Header->setVisible(false);

	for (short int i = 0; i < 12; i++)
	{
		if (i != 11)
			MiddleSection[i]->setVisible(false);

		for (short int j = 0; j < 3; j++)
			GameScoreData[i][j]->hideAll();
	}

	Total->setVisible(false);
}

void GameScore::setDepth(short unsigned int value)
{
	Background->setDepth(value);

	Header->setDepth(value - 1);

	for (short int i = 0; i < 11; i++)
	{
		MiddleSection[i]->setDepth(value - 1);

		for (short int j = 0; j < 3; j++)
		{
			GameScoreData[i][j]->setDepth(value - 2);
		}
	}

	Total->setDepth(value - 1);
}

void GameScore::reset(void)
{
	for (short int i = 0; i < 12; i++)
	{
		for (short int j = 0; j < 3; j++)
			GameScoreData[i][j]->setValue(0);
	}
}

////////From PinochleGame.cpp
void GameScore::addToScore(short int team, short int amount)
{
	if (team == BLUE)
		horizontalScore += amount;
	else if (team == RED)
		verticalScore += amount;		
}

short int GameScore::getScore(short int team)
{
	if (team == BLUE)
		return horizontalScore;
	if (team == RED)
		return verticalScore;

	return -1;
}