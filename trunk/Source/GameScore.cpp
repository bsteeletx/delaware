#include "GameScore.h"
#include "agk.h"

GameScore::GameScore(void)
{

}

GameScore::~GameScore(void)
{
}

void GameScore::setup(AnimatedSprite *Symbol, ParentImage *HandParent)
{
    int imgNum;

    Parent = *HandParent;

    //Parent.setImage("default/Scoreboards.png");

    ///step 1: setup or setData/////////////
    imgNum = Parent.getImageNumber("board_background.png");
	Background.setImageNumber(imgNum);

    imgNum = Parent.getImageNumber("board_header.png");
	Header.setImageNumber(imgNum);

    imgNum = Parent.getImageNumber("board_hand score.png");
    for (short int i = 0; i < 11; i++)
		MiddleSection[i].setImageNumber(imgNum);

    imgNum = Parent.getImageNumber("board_total score.png");
    Total.setImageNumber(imgNum);
	setNumberData();

	Symbol->incrementSpriteFrame();
	agk::Sync();

	///step 2: setSize
	Background.setSize(62.5f, 78.0f);
	Header.setSize(58.0f, 4.9f);
	for (short int i = 0; i < 11; i++)
		MiddleSection[i].setSize(58.0f, 4.9f);
	Total.setSize(58.0f, 4.9f);

	///step 3: set priority
	setPriority(50);

	Symbol->incrementSpriteFrame();
	agk::Sync();

	///step 4: set x, y location with display
	Background.display(20.0f, 15.0f);
	for (short int i = 0; i < 11; i++)
		MiddleSection[i].display(21.0f, 22.5f + (5.0f * i));
	Header.display(21.0f, 17.0f);
	Total.display(21.0f, 77.0f);

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
	for (int i = 0; i < 12; i++)
	{
		for (short int j = 0; j < 3; j++)
			GameScoreData[i][j].setData("default/");
	}

	for (short int i = 0; i < 3; i++)
	{
		for (short int g = 0; g < 12; g++) //rows
		{
			for (short int h = 0; h < 3; h++) //columns
			{
				GameScoreData[g][h].setLocation(i, 73.75f - ((1.75f * i) + (h * 14.25f)), 23.75f + (4.95f * g), -6.0f, -0.5f);
			}
		}
	}

	for (short int g = 0; g < 12; g++)
	{
		for (short int h = 0; h < 3; h++)
		{
			GameScoreData[g][h].setPriority(52);
			GameScoreData[g][h].setSize(1.5f);
			//GameResults.GameScoreData[g][h].hideAll();
			GameScoreData[g][h].setValue(0);
			GameScoreData[g][h].hideAll();
		}
	}
}

void GameScore::hide(void)
{
	Background.hide();

	Header.hide();

	for (short int i = 0; i < 12; i++)
	{
		if (i != 11)
			MiddleSection[i].hide();

		for (short int j = 0; j < 3; j++)
			GameScoreData[i][j].hideAll();
	}

	Total.hide();
}

void GameScore::setPriority(short unsigned int value)
{
	Background.setPriority(value);

	Header.setPriority(value + 1);

	for (short int i = 0; i < 11; i++)
	{
		MiddleSection[i].setPriority(value + 1);

		for (short int j = 0; j < 3; j++)
		{
			GameScoreData[i][j].setPriority(value + 2);
		}
	}

	Total.setPriority(value + 1);
}

void GameScore::reset(void)
{
	for (short int i = 0; i < 12; i++)
	{
		for (short int j = 0; j < 3; j++)
			GameScoreData[i][j].setValue(0);
	}
}
