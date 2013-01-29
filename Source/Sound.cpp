#include "template.h"

Sound::Sound()
{
	volume = 100;
}

Sound::~Sound(void)
{
	agk::DeleteSound(soundID);
}

void Sound::setFileName(const char filename[])
{
	soundID = agk::LoadSound(filename);
}

void Sound::playOnce(void)
{
	if (agk::GetSoundsPlaying(soundID))
		return;

	agk::PlaySound(soundID, volume);
}

void Sound::playLoop(void)
{
	agk::PlaySound(soundID, volume, 1);
}

void Sound::stop(void)
{
	agk::StopSound(soundID);
}

bool Sound::exists(void)
{
	if (agk::GetSoundExists(soundID))
		return true;
	else
		return false;
}

void Sound::setMasterVolume(unsigned short int newVolume)
{
	volume = newVolume;
	agk::SetSoundSystemVolume(volume);
}

bool Sound::isPlaying(void)
{
	if (agk::GetSoundsPlaying(soundID))
		return true;
	else
		return false;
}
