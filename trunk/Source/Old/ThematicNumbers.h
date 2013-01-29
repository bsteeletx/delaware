#pragma once
#include "numbers.h"
class ThematicNumbers :
	public Numbers
{
public:
	ThematicNumbers(void);
	~ThematicNumbers(void);

	void init(unsigned short theme);
	void init(Text Directory);
};

