#pragma once

#include "Text.h"

class Sound
{
public:
	Sound();
	~Sound(void);

	void init(Text Filename, unsigned int assignedID = 0);
	void init(const char filename[], unsigned int assignedID = 0);

	bool getExists(void);
	unsigned int getInstances(void);

	void play(unsigned short volume = 100, bool loop = false);
	
	void setSystemVolume(unsigned short volume);
	void stop(void);
	
	
private:
	unsigned int soundID;

	bool _Filename(Text Filename);
};
