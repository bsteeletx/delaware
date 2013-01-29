#pragma once
class Sound
{
public:
	//Sound(char filename[]);
	Sound();
	~Sound(void);

	bool exists(void);
	bool isPlaying(void);
	void playLoop(void);
	void playOnce(void);
	void setFileName(const char filename[]);
	void setMasterVolume(unsigned short int newVolume);
	void stop(void);


private:
	short unsigned int soundID;
	static unsigned short int volume;
};
