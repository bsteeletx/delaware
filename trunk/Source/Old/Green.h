#pragma once
#include "Theme.h"
class Green :
	public Theme
{
public:
	Green(void);
	~Green(void);

	void init(AnimatedSprite *Symbol, unsigned short state) override;
	void initNumbers(void) override;

	void setNumberData(void) override;
	void setSizeNumbers(void) override;
	void setNumberLoc(void) override;
	void setNumberPrio(void) override;

private:
	Text DirLocation;
	Point FirstCardPos[4];
};

