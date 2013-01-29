#include "Buttons.h"
#include "agk.h"

//Sound Buttons::ButtonClick;
//int Sound::volume = 100;

Buttons::Buttons(void)
{
	soundPlaying = false;
}


Buttons::~Buttons(void)
{
}

void Buttons::setSound(bool playSound)
{
	if (playSound)
		ButtonClick->setSystemVolume(100);
	else
		ButtonClick->setSystemVolume(0);
}

bool Buttons::animation(short int stage)
{
	switch (stage)
	{
	case 1:
		AllButtons[DOWN]->setVisible(true);
		AllButtons[UP]->setVisible(false);
		AllButtons[OVER]->setVisible(false);
		if (!soundPlaying)
		{
			ButtonClick->play();
			soundPlaying = true;
		}
		return false;
		break;
	case 2: 
		AllButtons[DOWN]->setVisible(false);
		AllButtons[UP]->setVisible(true);
		soundPlaying = false;
		return false;
		break;
	}
	
	return true;
}

void Buttons::display(float x, float y)
{
	for (int i = 0; i < 4; i++)
	{
		if (AllButtons[i]->getExists())
			AllButtons[i]->setPosition(x, y);
	}
}

void Buttons::hide(unsigned short button)
{
	if (button == 4)
	{
		for (int i = 0; i < 4; i++)
		{
			if (AllButtons[i]->getExists())
				AllButtons[i]->setVisible(false);
		}
	}
	else
		AllButtons[button]->setVisible(false);

}

void Buttons::show(unsigned short button)
{
	if (AllButtons[button]->getExists())
		AllButtons[button]->setVisible(true);
	/*if (agk::GetSpriteExists(ButtonDown.getSpriteNumber()))
		ButtonDown.show();
	if (agk::GetSpriteExists(ButtonOver.getSpriteNumber()))
		ButtonOver.show();
	if (agk::GetSpriteExists(ButtonGray.getSpriteNumber()))
		ButtonGray.show();*/
}

void Buttons::setPosition(float x, float y)
{
	for (int i = 0; i < 4; i++)
	{
		if (AllButtons[i]->getExists())
			AllButtons[i]->setPosition(x, y);
	}
}

void Buttons::setSize(float x, float y)
{
	for (int i = 0; i < 4; i++)
	{
		if (AllButtons[i]->getExists())
			AllButtons[i]->setSize(x, y);
	}
}


Text Buttons::getFileExtension(short int buttonType)
{
	Text ReturnText = Text();

	switch(buttonType)
	{
	case 1:
		ReturnText.init("_off.png");
		break;
	case 2:
		ReturnText.init("_down.png");
		break;
	case 3:
		ReturnText.init("_on.png");
		break;
	case 4:
		ReturnText.init("_negative.png");
		break;
	}

	return ReturnText;
}

void Buttons::init(File FileToInit)
{
	//STUB
}

void Buttons::init(unsigned int parentImageNumber, Text ButtonBaseName)
{
	Text Temp;
	Text SoundFileName;

	SoundFileName.init("sounds/woodclick1.wav");
	ButtonClick->init(SoundFileName);

	for (int i = 0; i < 4; i++)
	{
		if (AllButtons[i]->getExists())
		{
			Temp = ButtonBaseName;
			Temp += getFileExtension(i);

			if (parentImageNumber != 0)
				AllButtons[i]->subInit(parentImageNumber, Temp);
			else
				AllButtons[i]->parentInit(Temp);

			AllButtons[i]->setDepth(5);
		}
	}
}

bool Buttons::isVisible(void)
{
	for (int i = 0; i < 4; i++)
	{
		if (AllButtons[i]->getVisible())
			return true;
	}

	return false;
}

void Buttons::setDepth(unsigned int depthValue)
{
	for (int i = 0; i < 4; i++)
		AllButtons[i]->setDepth(depthValue);
}