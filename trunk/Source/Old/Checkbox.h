#pragma once
#include "Sprite.h"
#include "Defines.h"
//#include "ndlers/ParentImage.h"

class Checkbox
{
public:
	Checkbox(void);
	~Checkbox(void);

	void check(void);
	
	void hide(void);
	
	//void init(const char filename[], ParentImage OptionsParent);
	
	void show(void);

	void unCheck(void);

private:
	bool isChecked;
    
	Sprite *Checked;
	Sprite *NotChecked;
};

