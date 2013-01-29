#include "MyMenu.h"
#include "AGK.h"

MyMenu::MyMenu(void)
{
	isBase = true;
}


MyMenu::~MyMenu(void)
{
}

void MyMenu::initParent(void)
{
	Text ParentFileName = Text();

	ParentFileName.init("default/MainMenu.png");
    ParentImage.parentInit(ParentFileName);
}

void MyMenu::init(void)
{
	Text ButtonBaseName = Text();
	unsigned int parentImgNum = 0;

	if (isBase)
		initParent();

	parentImgNum = ParentImage.getImageNumber();

	///step 1: setup or setData/////////////
	ButtonBaseName.init("new_game");
	AllButtons[NEWGAME]->init(parentImgNum, ButtonBaseName);
	ButtonBaseName.setString("options");
	AllButtons[OPTS]->init(parentImgNum, ButtonBaseName);
	ButtonBaseName.setString("resume");
	AllButtons[RESUME]->init(parentImgNum, ButtonBaseName);

	///step 2: setSize
	AllButtons[NEWGAME]->setSize(20.0f);
	AllButtons[OPTS]->setSize(20.0f);
	AllButtons[RESUME]->setSize(20.0f);

	///step 3: set priority
	setDepth(9998);

	///step 4: set x, y with display
	AllButtons[OPTS]->display(65.0, 80.0);
	AllButtons[RESUME]->display(40.0, 80.0);
	AllButtons[NEWGAME]->display(15.0, 80.0);
}

unsigned short MyMenu::update()
{
	short int choice = 0;
		
	float mouseX = agk::GetPointerX();
	float mouseY = agk::GetPointerY();

	if ((mouseX >= 15) && (mouseX <= 35))
	{
		if((mouseY >= 81) && (mouseY <= 89))
			choice = 1;
	}

	if (AllButtons[RESUME]->isVisible())
	{
		if ((mouseX >= 40) && (mouseX <= 60))
		{
			if ((mouseY >= 81) && (mouseY <= 89))
				choice = 3;
		}
	}

	if ((mouseX >= 65) && (mouseX <= 85))
	{
		if ((mouseY >= 81) && (mouseY <= 89))
			choice = 4;
	} 

#if (PLATFORM == PC)
	if (choice == 0)
	{
		AllButtons[NEWGAME]->hide(OVER);
		AllButtons[OPTS]->hide(OVER);
		AllButtons[RESUME]->hide(OVER);
		AllButtons[MAINMENU]->hide(OVER);
	}

	if (choice == 1)
		AllButtons[NEWGAME]->show(OVER);
	/*else
	{
		Options.ButtonOver.hide();
		ResumeGame.ButtonOver.hide();
	}*/
	
	if (choice == 4)
		AllButtons[OPTS]->show(OVER);
	/*else
	{
		ResumeGame.ButtonOver.hide();
		NewGame.ButtonOver.hide();
	}*/

	if (choice == 3)
		AllButtons[RESUME]->show(OVER);
	/*else
	{
		NewGame.ButtonOver.hide();
		Options.ButtonOver.hide();
	}*/
#endif

	return choice;
}	 

void MyMenu::showButton(unsigned short button)
{
	AllButtons[button]->show();
}

void MyMenu::ButtonAnimation(unsigned short button)
{
	AllButtons[button]->animation(1);
	agk::Sleep(250);
	AllButtons[button]->animation(2);
}

void MyMenu::hide(void)
{
	for (int i = 0; i < 4; i++)
		AllButtons[i]->hide();
}

void MyMenu::setDepth(unsigned short value)
{
	//Background.setPriority(value);
	for (int i = 0; i < 4; i++)
		AllButtons[i]->setDepth(value - 1);
}

void MyMenu::hideButton(unsigned short button)
{
	AllButtons[button]->hide();
}