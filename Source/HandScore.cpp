#include "HandScore.h"
#include "agk.h"

HandScore::HandScore(void)
{

}


HandScore::~HandScore(void)
{
}

void HandScore::setup(AnimatedSprite *Symbol)
{
    int imgNum;
    float hOffset;
    float vOffset;
	///step 1: setup or setData
	Parent.setImage("default/Scoreboards.png");

    imgNum = Parent.getImageNumber("board table.png");
	Background.setImageNumber(imgNum);
	setNumberData();

    imgNum = Parent.getImageNumber("check_box_off.png");
	HCheck.setImageNumber(imgNum);
    VCheck.setImageNumber(imgNum);

    imgNum = Parent.getImageNumber("check_box_on.png");
	HCheckOn.setImageNumber(imgNum);
    VCheckOn.setImageNumber(imgNum);

	Symbol->incrementSpriteFrame();
	agk::Sync();

	///step 2: setSize
	HCheck.setSize(5.0f);
	HCheckOn.setSize(5.0f);
	VCheck.setSize(5.0f);
	VCheckOn.setSize(5.0f);
	Background.setSize(80.0f);

	Symbol->incrementSpriteFrame();
	agk::Sync();

	///step 3: setPriority
	setPriority(50);

	Symbol->incrementSpriteFrame();
	agk::Sync();

	///step 4: set x, y with display
#if (PLATFORM == MOBILE)
    hOffset = 4.5f;
    vOffset = 3.5f;
#else
    hOffset = 0.0f;
    vOffset = 0.0f;
#endif

	Background.display(10.0f, 25.0f);
	HCheck.display(66.0f, 60.0f + hOffset);
	HCheckOn.display(66.0f, 60.0f + hOffset);
	VCheck.display(66.0f, 51.0f + vOffset);
	VCheckOn.display(66.0f, 51.0f + vOffset);

	Symbol->incrementSpriteFrame();
	agk::Sync();

	///step 5: hide
	HCheck.hide();
	HCheckOn.hide();
	VCheck.hide();
	VCheckOn.hide();

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

void HandScore::setNumberData(void)
{
    float hOffset = 0.0f;
    float vOffset = 0.0f;
    float mOffset = 0.0f;

	for (short int i = 0; i < 2; i++)
	{
		for (short int j = 0; j < 4; j++)
			HandScoreData[i][j].setData("default/");
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
				HandScoreData[0][k-1].setLocation(i, 83.0f - ((2.5f * i) + (k * 12.6f)), 52.0f + vOffset, -4.5f, -0.5f + mOffset);
				HandScoreData[1][k-1].setLocation(i, 83.0f - ((2.5f * i) + (k * 12.6f)), 61.0f + hOffset, -4.5f, -0.5f + mOffset);
			}
			else
			{
				HandScoreData[0][k].setLocation(i, 83.0f - ((2.5f * i) + (k * 12.6f)), 52.0f + vOffset, -4.5f, -0.5f + mOffset);
				HandScoreData[1][k].setLocation(i, 83.0f - ((2.5f * i) + (k * 12.6f)), 61.0f + hOffset, -4.5f, -0.5f + mOffset);
			}
		}
	}

	for (short int k = 0; k < 4; k++)
	{
		HandScoreData[0][k].setPriority(52);
		HandScoreData[1][k].setPriority(52);
		HandScoreData[0][k].setSize(2.5f);
		HandScoreData[1][k].setSize(2.5f);
		HandScoreData[0][k].setValue(0);
		HandScoreData[1][k].setValue(0);
		HandScoreData[0][k].hideAll();
		HandScoreData[1][k].hideAll();
	}
}

void HandScore::hide(void)
{
	Background.hide();
	for (short int i = 0; i < 2; i++)
	{
		for (short int j = 0; j < 4; j++)
			HandScoreData[i][j].hideAll();
	}

	HCheck.hide();
	HCheckOn.hide();
	VCheck.hide();
	VCheckOn.hide();
}

void HandScore::setPriority(short unsigned int value)
{
	Background.setPriority(value);

	HCheck.setPriority(value+1);
	HCheckOn.setPriority(value+1);
	VCheck.setPriority(value+1);
	VCheckOn.setPriority(value+1);

	for (short int i = 0; i < 2; i++)
	{
		for (short int j = 0; j < 4; j++)
			HandScoreData[i][j].setPriority(value+1);
	}
}

void HandScore::reset(void)
{
	for (short int i = 0; i < 2; i++)
	{
		for (short int j = 0; j < 4; j++)
			HandScoreData[i][j].setValue(0);
	}
}
