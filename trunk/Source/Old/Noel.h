#pragma once
#include "theme.h"
class Noel :
	public Theme
{
public:
	Noel(void);
	~Noel(void);

	Point getFirstCardPos(unsigned short player) override;

	void init(AnimatedSprite *Symbol, unsigned short state) override;
	void initNumbers(void) override;

	void setNumberData(void) override;
	void setNumberLoc(void) override;
	void setNumberPrio(void) override;
	void setSizeNumbers(void) override;

private:
	Point FirstCardPos[4];
	Text DirLocation;
};

