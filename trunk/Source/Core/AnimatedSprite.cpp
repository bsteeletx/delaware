#include "agk.h"
#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite()
	: Sprite()
{
}

AnimatedSprite::~AnimatedSprite()
{
}

void AnimatedSprite::init(unsigned int width, unsigned int height, unsigned int count, unsigned int parentImage, Text SubImageFilename, unsigned int assignedSpriteNumber, unsigned int assignedImageNumber)
{
	Sprite::subInit(parentImage, SubImageFilename, assignedSpriteNumber, assignedImageNumber);
	set(width, height, count);
}

void AnimatedSprite::init(unsigned int width, unsigned int height, unsigned int count, unsigned int parentImage, const char subImageFilename[], unsigned int assignedSpriteNumber, unsigned int assignedImageNumber)
{
	Text SubImageFilename = Text();

	SubImageFilename.init(subImageFilename);
	Sprite::subInit(parentImage, SubImageFilename, assignedSpriteNumber, assignedImageNumber);
	set(width, height, count);
}

void AnimatedSprite::init(File FileToInit)
{
	
	FileToInit.reOpen();

	while(!FileToInit.FileEOF())
	{
		Text Line;
		Text Start;
		Text End;

		Line = FileToInit.getLine();

		Line.splitAtDelimeter(&Start, &End, ':');

		if (strcmp(Start.getString(), "Height") == 0) //they are the same
			frameHeight = agk::Val(End.getString());
		else if (strcmp(Start.getString(), "Width") == 0)
			frameWidth = agk::Val(End.getString());
		else if (strcmp(Start.getString(), "Count") == 0)
			frameCount = agk::Val(End.getString());
		else if (strcmp(Start.getString(), "PlaySpeed") == 0)
		{
			if (strcmp(End.getString(), "") == 0)
				continue;
			else
				playSpeed = (float) agk::Val(End.getString());
		}
	}

	set(frameWidth, frameHeight, frameCount);

	FileToInit.close();
}

void AnimatedSprite::addFrame(Image NewFrame)
{
	agk::AddSpriteAnimationFrame(spriteNumber, NewFrame.getImageNumber());
}

unsigned int AnimatedSprite::getCurrentFrame(void)
{
	return agk::GetSpriteCurrentFrame(spriteNumber);
}

unsigned int AnimatedSprite::getFrameCount(void)
{
	return agk::GetSpriteFrameCount(spriteNumber);
}

/*bool AnimatedSprite::getVisible(void)
{
	if (getY() <= 100.0f)
		return true;

	return false;
}*/

float AnimatedSprite::getPlaySpeed(void)
{
	return playSpeed;
}

void AnimatedSprite::incrementFrame(void)
{
	if (getFrameCount() == getCurrentFrame())
		setFrame(1);
	else
		setFrame(getFrameCount() + 1);
}

void AnimatedSprite::play(float fps, bool loop, unsigned int start, unsigned int end)
{
	if (_Frame(start))
	{
		if (_Frame(end))
		{
			if (_FPS(fps))
				agk::PlaySprite(spriteNumber, fps, loop, start, end);
		}
	}
}

void AnimatedSprite::resume(void)
{
	agk::ResumeSprite(spriteNumber);
}

void AnimatedSprite::setFrame(unsigned int frame)
{
	if (_Frame(frame))
		agk::SetSpriteFrame(spriteNumber, frame);
}

void AnimatedSprite::setPosition(Point Location)
{
	originalY = Location.getY();
	Sprite::setPosition(Location);
}

void AnimatedSprite::setSpeed(float fps)
{
	if (_FPS(fps))
		agk::SetSpriteSpeed(spriteNumber, fps);
}

/*void AnimatedSprite::setVisibile(bool value)
{
	if (value)
		setY(200.0f);
	else
		setY(originalY);
}*/

void AnimatedSprite::stopSprite(void)
{
	agk::StopSprite(spriteNumber);
}

void AnimatedSprite::set(unsigned int width, unsigned int height, unsigned int count)
{
	if (width > 0)
	{
		if (height > 0)
		{
			if (count > 0)
			{
				agk::SetSpriteAnimation(spriteNumber, width, height, count);
				frameHeight = height;
				frameWidth = width;
				frameCount = count;
			}
		}
	}
}

bool AnimatedSprite::_Frame(unsigned int frame)
{
	if (frame != 0)
	{
		if (frame <= getFrameCount())
			return true;
	}

	return false;
}

bool AnimatedSprite::_FPS(float fps)
{
	if (fps > 0.0f)
		return true;

	return false;
}