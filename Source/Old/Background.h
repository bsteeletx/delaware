#pragma once
#include "sprite.h"
//#include "../Info-Control/Buttons.h"
class Background :
	public Sprite
{
public:
	Background(void);
	~Background(void);

	void init(Text *FilePath);
private:
	Text *FileName;
	Sprite *MenuButtons[2];
};

