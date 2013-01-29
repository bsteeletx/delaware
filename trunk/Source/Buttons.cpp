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
		ButtonClick.setMasterVolume(100);
	else
		ButtonClick.setMasterVolume(0);
}

bool Buttons::animation(short int stage)
{
	switch (stage)
	{
	case 1:
		ButtonDown.show();
		ButtonUp.hide();
		ButtonOver.hide();
		if (!soundPlaying)
		{
			ButtonClick.playOnce();
			soundPlaying = true;
		}
		return false;
		break;
	case 2:
		ButtonDown.hide();
		ButtonUp.show();
		soundPlaying = false;
		return false;
		break;
	}

	return true;
}

void Buttons::display(float x, float y)
{
	if (agk::GetSpriteExists(ButtonUp.getSpriteNumber()))
		ButtonUp.display(x, y);
	if (agk::GetSpriteExists(ButtonDown.getSpriteNumber()))
		ButtonDown.display(x, y);
	if (agk::GetSpriteExists(ButtonOver.getSpriteNumber()))
		ButtonOver.display(x, y);
	if (agk::GetSpriteExists(ButtonGray.getSpriteNumber()))
		ButtonGray.display(x, y);
}

void Buttons::hide(void)
{
	if (agk::GetSpriteExists(ButtonUp.getSpriteNumber()))
		ButtonUp.hide();
	if (agk::GetSpriteExists(ButtonDown.getSpriteNumber()))
		ButtonDown.hide();
	if (agk::GetSpriteExists(ButtonOver.getSpriteNumber()))
		ButtonOver.hide();
	if (agk::GetSpriteExists(ButtonGray.getSpriteNumber()))
		ButtonGray.hide();
}

void Buttons::show(void)
{
	if (agk::GetSpriteExists(ButtonUp.getSpriteNumber()))
		ButtonUp.show();
	/*if (agk::GetSpriteExists(ButtonDown.getSpriteNumber()))
		ButtonDown.show();
	if (agk::GetSpriteExists(ButtonOver.getSpriteNumber()))
		ButtonOver.show();
	if (agk::GetSpriteExists(ButtonGray.getSpriteNumber()))
		ButtonGray.show();*/
}

void Buttons::setSize(float x, float y)
{
	if (agk::GetSpriteExists(ButtonUp.getSpriteNumber()))
		ButtonUp.setSize(x, y);
	if (agk::GetSpriteExists(ButtonDown.getSpriteNumber()))
		ButtonDown.setSize(x, y);
	if (agk::GetSpriteExists(ButtonOver.getSpriteNumber()))
		ButtonOver.setSize(x, y);
	if (agk::GetSpriteExists(ButtonGray.getSpriteNumber()))
		ButtonGray.setSize(x, y);
}

void Buttons::setPriority(short unsigned int value)
{
	if (agk::GetSpriteExists(ButtonUp.getSpriteNumber()))
		ButtonUp.setPriority(value);
	if (agk::GetSpriteExists(ButtonDown.getSpriteNumber()))
		ButtonDown.setPriority(value);
	if (agk::GetSpriteExists(ButtonOver.getSpriteNumber()))
		ButtonOver.setPriority(value);
	if (agk::GetSpriteExists(ButtonGray.getSpriteNumber()))
		ButtonGray.setPriority(value);
}

void Buttons::addFileExtension(char filebase[], short int buttonType)
{
	switch(buttonType)
	{
	case 1:
		strcat(filebase, "_off.png");
		break;
	case 2:
		strcat(filebase, "_down.png");
		break;
	case 3:
		strcat(filebase, "_on.png");
		break;
	case 4:
		strcat(filebase, "_negative.png");
		break;
	}
}

void Buttons::setData(const char newFilename[], const char newDir[])
{
	char temp[64];

	if (strlen(newFilename) >= 60)
		return;

	for (short int i = 0; i < 4; i++)
	{
		strcpy(temp, newFilename);

		addFileExtension(temp, i+1);

		switch (i)
		{
		case 0:
			ButtonUp.setData(temp, newDir);
			break;
		case 1:
			ButtonDown.setData(temp, newDir);
			break;
		case 2:
			ButtonOver.setData(temp, newDir);
			break;
		case 3:
			ButtonGray.setData(temp, newDir);
		}
	}
}

void Buttons::setup(AnimatedSprite *Symbol, const char filename[])
{
	char temp[32];
    unsigned tempImageNum;

	ButtonClick.setFileName("sounds/woodclick1.wav");

	strcpy(temp, filename);
	addFileExtension(temp, 1);
    tempImageNum = Parent.getImageNumber(temp);
	ButtonUp.setImageNumber(tempImageNum);

	Symbol->incrementSpriteFrame();
	agk::Sync();

	strcpy(temp, filename);
	addFileExtension(temp, 2);
    tempImageNum = Parent.getImageNumber(temp);
	ButtonDown.setImageNumber(tempImageNum);

	Symbol->incrementSpriteFrame();
	agk::Sync();

	strcpy(temp, filename);
	addFileExtension(temp, 3);
    tempImageNum = Parent.getImageNumber(temp);
	ButtonOver.setImageNumber(tempImageNum);

	Symbol->incrementSpriteFrame();
	agk::Sync();

	strcpy(temp, filename);
	addFileExtension(temp, 4);
    tempImageNum = Parent.getImageNumber(temp);
	ButtonGray.setImageNumber(tempImageNum);

	Symbol->incrementSpriteFrame();
	agk::Sync();
}

void Buttons::setup(AnimatedSprite *Symbol, const char filename[], ParentImage ParentTemp)
{
    Parent = ParentTemp;

    setup(Symbol, filename);
}
