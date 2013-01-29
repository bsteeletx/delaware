#include "Background.h"


Background::Background(void)
	: Sprite()
{
	//FileName = new Text("background.png");
}


Background::~Background(void)
{
}

void Background::init(Text *FilePath)
{
	FileName->init("background.png");
	
	Text *MenuOff = new Text();
	Text *MenuOn = new Text();
	Text *Temp = FilePath;
	
	MenuOff->init("menu_off.png");
	MenuOn->init("menu_on.png");

	//setting up background
	*Temp += *FileName;
	Sprite::parentInit(Temp);
	setDepth(9999);

	//setting up menu buttons
	*Temp = *FilePath;
	*Temp += *MenuOff;
	MenuButtons[0]->parentInit(Temp); 
	*Temp = *FilePath;
	*Temp += *MenuOn;
	MenuButtons[1]->parentInit(MenuOn);

	delete MenuOff;
	delete MenuOn;
}
