#include "MyOptions.h"
#include "MyMenu.h"
#include "agk.h"

MyOptions::MyOptions(void)
	: MyMenu()
{
	hasStarted = false;
	isBase = false;
	selectedTheme = GREEN;
}


MyOptions::~MyOptions(void)
{
}

void MyOptions::initParent(void)
{
	Text ParentFileName = Text();
    
	ParentFileName.init("default/Options.png");
    ParentImage.parentInit(ParentFileName);
}

void MyOptions::init(void)
{
    int parentImgNum = 0;
	Text ButtonBaseName = Text();

	initParent();

	MyMenu::init();

	parentImgNum = ParentImage.getImageNumber();
    
	ButtonBaseName.init("options_background.png");
	Background.subInit(parentImgNum, ButtonBaseName);
	    
	ButtonBaseName.setString("background_g.jpg");
	ThemeOption[GREEN].subInit(parentImgNum, ButtonBaseName);
    
    ButtonBaseName.setString("background_t.jpg");
	ThemeOption[RED].subInit(parentImgNum, ButtonBaseName);
    
    ButtonBaseName.setString("background_a.jpg");
	ThemeOption[ANCIENT].subInit(parentImgNum, ButtonBaseName);
	
	ButtonBaseName.setString("background_x.jpg");
	ThemeOption[NOEL].subInit(parentImgNum, ButtonBaseName);

	//imgNum = Parent.getImageNumber("background_a.jpg");
	//ThemeOption[4].setImageNumber(imgNum);

	//ThemeOption[3].setData(pImage, "background_f.jpg");
	ButtonBaseName.setString("sound_btn_on.png");
	SoundCheckOn.subInit(parentImgNum, ButtonBaseName);

	ButtonBaseName.setString("sound_btn_off.png");
	SoundCheckOff.subInit(parentImgNum, ButtonBaseName);
	
	ButtonBaseName.setString("left_arrow");
	Left.init(parentImgNum, ButtonBaseName);
	ButtonBaseName.setString("right_arrow");
	Right.init(parentImgNum, ButtonBaseName);

	///step 2: setSize
	Background.setSize(100.0f);
    
#if (PLATFORM != MOBILE)
	SoundCheckOn.setSize(37.5f);
    SoundCheckOff.setSize(37.5f);
#else
    SoundCheckOn.setSize(45.0f);
    SoundCheckOff.setSize(45.0f);
#endif

	for (short int i = 0; i < NUM_TABLE_TOP; i++)
		ThemeOption[i].setSize(45.0f);

//	NewGame->setSize(20.0f);
//	ResumeGame->setSize(20.0f);

	Left.setSize(10.0f);
	Right.setSize(10.0f);
		
	///step 3: set priority
	setDepth(9900);

#if (PLATFORM != MOBILE)
    {
		SoundCheckOn.setPosition(27.0f, 70.0f);
        SoundCheckOff.setPosition(27.0f, 70.0f);
        //ResumeGame->setPosition(65.0, 82.0);
        //NewGame->setPosition(40.0f, 82.0f);
    }
#else
    {
        SoundCheckOn.setPosition(30.0f, 72.5f);
        SoundCheckOff.setPosition(30.0f, 72.5f);
        //ResumeGame->setPosition(65.0, 83.0);
        //NewGame->setPosition(40.0f, 83.0f);
    }
#endif
	Background.setPosition(0.0f, 0.0f);
	Left.setPosition(WEST_LOC_X, 39.0f);
	Right.setPosition(EAST_LOC_X, 39.0f);

	for (short int i = 0; i < NUM_TABLE_TOP; i++)
		ThemeOption[i].setPosition(27.5f, 23.0f);

	hide();
}

void MyOptions::show(short int curStyle)
{
	Background.setVisible(true);

	ThemeOption[curStyle].setVisible(true);
	
	SoundCheckOff.setVisible(isMuted);
	SoundCheckOn.setVisible(!isMuted);
	
	AllButtons[NEWGAME]->show(UP);
	AllButtons[RESUME]->show(UP);

	Left.show();
	Right.show();
	//MainMenu.ButtonUp.show();

	selectedTheme = curStyle;
}

void MyOptions::arrowAnimation(unsigned short button)
{
	switch(button)
	{
	case 5:
		Right.animation(1);
		agk::Sleep(250);
		Right.animation(2);
		break;
	case 6:
		Left.animation(1);
		agk::Sleep(250);
		Left.animation(2);
		break;
	}
}

void MyOptions::mute(void)
{
	if (isMuted)
		return;

	isMuted = true;

	SoundCheckOff.setVisible(true);
	SoundCheckOn.setVisible(false);
}

void MyOptions::unMute(void)
{
	if (!isMuted)
		return;

	isMuted = false;
	SoundCheckOn.setVisible(true);
	SoundCheckOff.setVisible(false);
}

void MyOptions::setDepth(unsigned short value)
{
	for (short int i = 0; i < 6; i++)
		ThemeOption[i].setDepth(value - 1);

	Background.setDepth(9999);

	SoundCheckOn.setDepth(value - 1);
	SoundCheckOff.setDepth(value - 1);

	//NewGame->setDepth(value - 2);
	//ResumeGame->setDepth(value - 2);

	Left.setDepth(value - 1);
	Right.setDepth(value - 1);

	MyMenu::setDepth(value);
}

void MyOptions::start(void)
{
	growBackground();

	show(selectedTheme);

	hasStarted = true;
}

unsigned short MyOptions::update()
{
	short int choice = 0;
	bool mouseClick = false;

	if (!hasStarted)
	{
		start();
		return 0;
	}

	if (agk::GetPointerPressed())
	{
		mouseClick = true;
		mouseX = agk::GetPointerX();
		mouseY = agk::GetPointerY();

		if ((mouseX >= 40.0f) && (mouseX <= 60.0f))
			potSwipe = true;
	}

	if (agk::GetPointerReleased())
	{
		mouseClick = false;
		potSwipe = false;
		if (abs(mouseX - agk::GetPointerX()) > 5.0f)
		{
			if (mouseX > agk::GetPointerX())
			{
				if (agk::GetPointerX() < 40.0f)
					swipeLeft = true;
			}
			else
			{
				if (agk::GetPointerX() > 60.0f)
					swipeRight = true;
			}
		}
	}

	SoundCheckOn.setVisible(!isMuted);
	SoundCheckOff.setVisible(isMuted);

	if ((mouseX >= 40.0f) && (mouseX <= 60.0f))
	{
		if((mouseY >= 83.0f) && (mouseY <= 94.0f))
			choice = 1;
	}

	if (AllButtons[RESUME]->isVisible())
	{
		if ((mouseX >= 65.0f) && (mouseX <= 85.0f))
		{
			if ((mouseY >= 80.0f) && (mouseY <= 92.0f))
				choice = 2;
		} 
	}

#if (PLATFORM == PC)
	if (choice == 0)
	{
		AllButtons[NEWGAME]->hide(OVER);
		AllButtons[RESUME]->hide(OVER);
	}
	else if (choice == 1)
	{
		AllButtons[NEWGAME]->show(OVER);
		AllButtons[RESUME]->hide(OVER);
	}
	else if (choice == 2)
	{
		AllButtons[RESUME]->show(OVER);
		AllButtons[NEWGAME]->hide(OVER);
	}
#endif

#if (PLATFORM != MOBILE) //    left-right arrows / sound button / new game-resume buttons
    const float yMinValues[3] = {35.0f, 70.0f, 81.0f};
    const float yMaxValues[3] = {51.5f, 80.0f, 94.0f};
#else
    const float yMinValues[3] = {40.0f, 75.0f, 85.0f};
    const float yMaxValues[3] = {55.0f, 85.0f, 100.0f};
#endif
	
	if (!mouseClick && swipeLeft)
        choice = 5;
    else
		choice = 6;
        
    if (mouseClick)
    {
		if (mouseX >= (7.0f ))
        {
	        if (mouseX <= (93.5f ))
            {
				if ((mouseY >= (yMinValues[0])) && (mouseY <= (yMaxValues[0])))
                {//somewhere valid
                    if (mouseX <= (16.5f ))
                    {
                        choice = 6;
                        //delayStep = 1;
                    }
                    else if (mouseX >= (84.0f ))
                    {
                        choice = 5;
                        //delayStep = 1;
                    }
                }
                else if ((mouseY >= yMinValues[1]) && (mouseY <= yMaxValues[1]))
                {
                    if (!isMuted)
						mute();
                    else
                        unMute();
                }
                else if ((mouseX >= (41.0f )) && (mouseX <= (60.0f )))
                {
                    if ((mouseY >= (yMinValues[2])) && (mouseY <= (yMaxValues[2])))
                    {
                        choice = 1;
                        //delayStep = 1;
                    }
                }
                /*else if ((mouseX >= (65.0f )) && (mouseX <= (85.0f )))
                {
                    if ((mouseY >= (yMinValues[2])) && (mouseY <= (yMaxValues[2])))
                    {
                        if (getPrevState() != MENU)
                            {
                                menuChoice = 2;
                                delayStep = 1;
                            }
                        }
                    }
                }*/
            }
        }
    }

	if ((swipeLeft || swipeRight) && (choice >= 5))
	{
		short newStyle;

		if(choice == 5)
		{//table top
			if (selectedTheme + 1 < NUM_TABLE_TOP)
				newStyle = selectedTheme + 1;
			else
				newStyle = 0;

			moveTheme(false);
            //mouseDelay = agk::Timer();
		}
		else
		{
			if (selectedTheme - 1 < 0)
				newStyle = NUM_TABLE_TOP - 1;
			else
				newStyle = selectedTheme - 1;

			moveTheme(true);
		}

		return choice;
	}

	if (choice < 5)
	{
		ButtonAnimation(choice);
		hide();
	}	
	else
		arrowAnimation(choice);
	
	return choice;
}	 

/*void MyOptions::hide()
{
	NewGame.hide();
	ResumeGame.hide();
	//Background.hide();
}*/

float MyOptions::getBackgroundHeight(void)
{
	return Background.getHeight();
}

float MyOptions::getBackgroundWidth(void)
{
	return Background.getWidth();
}

void MyOptions::growBackground(void)
{
	while(Background.getWidth() != 100.0f)
	{
		Background.setSize(Background.getWidth() + 1);
		agk::Sync();
	}
}

void MyOptions::shrinkBackground(void)
{
	while(Background.getWidth() != 0.0f)
	{
		Background.setSize(Background.getWidth() - 1);
		agk::Sync();
	}
}

void MyOptions::moveTheme(bool moveToRight)
{
	short direction = 0;

	if (!moveToRight)
		direction = 1;
	else
		direction = -1;

	ThemeOption[selectedTheme + direction].setVisible(true);

	if (moveToRight)
		ThemeOption[selectedTheme + direction].setX(-45.0f);
	else
		ThemeOption[selectedTheme + direction].setX(100.0f);

	ThemeOption[selectedTheme + direction].setVisible(true);

	Point SelThemeLoc = ThemeOption[selectedTheme].getPosition();
	Point NewThemeLoc = ThemeOption[selectedTheme + direction].getPosition();
	
	while ((SelThemeLoc.getX() > 100.0f) || (SelThemeLoc.getX() < -45.0f))
	{
		SelThemeLoc.addToX(direction);
		NewThemeLoc.addToX(direction);
		ThemeOption[selectedTheme].setPosition(SelThemeLoc);
		ThemeOption[selectedTheme + direction].setPosition(NewThemeLoc);
		agk::Sync();
	}
	
	ThemeOption[selectedTheme].setVisible(false);
	selectedTheme = (selectedTheme + direction) % MAX_THEMES;
}

unsigned short MyOptions::getTheme(void)
{
	return selectedTheme;
}

void MyOptions::hide(void)
{
	Background.setVisible(false);

	ThemeOption[selectedTheme].setVisible(false);
	SoundCheckOn.setVisible(false);
	SoundCheckOff.setVisible(false);
	Left.hide();
	Right.hide();

	MyMenu::hide();
}

bool MyOptions::isSoundMuted(void)
{
	return isMuted;
}