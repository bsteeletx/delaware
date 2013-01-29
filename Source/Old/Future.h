#pragma once
#include "Theme.h"
class Future :
	public Theme
{
public:
	Future(void);
	~Future(void);

	void init(AnimatedSprite *Symbol, unsigned short state) override;
	void setNumberData(void) override;
	void setSizeNumbers(void) override;
	void setNumberLoc(void) override;
	void setNumberPrio(void) override;
	void initNumbers(void) override;

private:
	Text DirLocation;
	Point FirstCardPos[4];
};

