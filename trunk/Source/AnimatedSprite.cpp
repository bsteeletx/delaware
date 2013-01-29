#include "template.h"
#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(void)
{
	spriteNumber = -1;
	spriteFrame = -1;
	//spriteFrameMax = -1;
}

AnimatedSprite::AnimatedSprite(unsigned short int imageNo, unsigned short int across, unsigned short int down, unsigned short int total)
{
	spriteNumber = agk::CreateSprite(imageNo);
	imageNumber = imageNo;
	agk::SetSpriteAnimation(spriteNumber, across, down, total);

	spriteFrame = 0;
	//spriteFrameMax = across * down;
}

AnimatedSprite::~AnimatedSprite(void)
{
}

void AnimatedSprite::setAnimatedData(unsigned short int across, unsigned short int down, unsigned short int total, const char filename[], unsigned short imageNum[])
{
	setData(imageNum, filename);
	agk::SetSpriteVisible(spriteNumber, 1);
	agk::SetSpriteAnimation(spriteNumber, across, down, total);

	spriteFrame = 1;
	totalFrames = total;
}

void AnimatedSprite::setAnimatedData(unsigned short int across, unsigned short int down, unsigned short int total, const char filename[])
{
    setData(filename, "green/");
	agk::SetSpriteVisible(spriteNumber, 1);
	agk::SetSpriteAnimation(spriteNumber, across, down, total);

	spriteFrame = 1;
	totalFrames = total;
}

unsigned short int AnimatedSprite::getSpriteFrame(void)
{
	return spriteFrame;
}

void AnimatedSprite::incrementSpriteFrame(void)
{

	spriteFrame = (spriteFrame + 1) % totalFrames; //spriteFrameMax;
	agk::SetSpriteFrame(spriteNumber, spriteFrame);
}

void AnimatedSprite::playAnimation(float speed)
{
	agk::PlaySprite(spriteNumber, speed);
}

void AnimatedSprite::playAnimationLooped(float speed, bool loop)
{
	short int iLoop;
	if (loop)
		iLoop = 1;
	else
		iLoop = 0;

	agk::PlaySprite(spriteNumber, speed, iLoop);
}

void AnimatedSprite::playAnimationOnce(float speed)
{
	agk::PlaySprite(spriteNumber, speed, 0);
}

void AnimatedSprite::playAnimationFrames(float speed, bool loop, unsigned short int start, unsigned short int stop)
{
	short int iLoop;
	if (loop)
		iLoop = 1;
	else
		iLoop = 0;

	agk::PlaySprite(spriteNumber, speed, iLoop, start, stop);

	inAnimation = true;
}

void AnimatedSprite::setAnimatedFrameTo(unsigned short int frame)
{
	if (frame == 0)
		spriteFrame = 10;
	else if (frame > totalFrames)
		spriteFrame = frame % totalFrames;
	else
		spriteFrame = frame;

	agk::SetSpriteFrame(spriteNumber, spriteFrame);
}

void AnimatedSprite::pauseAnimation(void)
{
	agk::StopSprite(spriteNumber);
	inAnimation = false;
}

/*void AnimatedSprite::setupTrumpAnimation()
{
	//agk::CreateSprite(500, trumpSymb);

	//if ((agk::GetSpriteExists(trumpSprite) == 1) && (trumpSymb == 47))
	//	{
			//agk::SetSpriteAnimation(trumpSprite, 150.1, 150, 8);
			agk::SetSpriteSize(Symbol->spriteNumber, 6, 6);
			Symbol->display(89.0, 9.8);
			//agk::PlaySprite(trumpSprite, 5, 20, 1, 9);
			//agk::Sync();
	//	}
	else if ((agk::GetSpriteExists(trumpSprite) == 0) && (trumpSymb == 47))
		{
			agk::CreateSprite(trumpSprite, trumpSymb);
			agk::SetSpriteAnimation(trumpSprite, 150.1, 150, 8);
			agk::SetSpriteSize(trumpSprite, 6, 6);
			agk::SetSpritePosition(trumpSprite, 89.0, 9.8);
			agk::PlaySprite(trumpSprite, 5, 20, 1, 9);
			//agk::Sync();
		}
	if ((agk::GetSpriteExists(trumpSprite) == 1) && (trumpSymb == 48))
		{
			agk::SetSpriteAnimation(trumpSprite, 150.1, 150, 8);
			agk::SetSpriteSize(trumpSprite, 6, 6);
			agk::SetSpritePosition(trumpSprite, 89.0, 9.8);
			agk::PlaySprite(trumpSprite, 5, 20, 1, 9);
			//agk::Sync();
		}
	else if ((agk::GetSpriteExists(trumpSprite) == 0) && (trumpSymb == 48))
		{
			agk::CreateSprite(trumpSprite, trumpSymb);
			agk::SetSpriteAnimation(trumpSprite, 150.1, 150, 8);
			agk::SetSpriteSize(trumpSprite, 6, 6);
			agk::SetSpritePosition(trumpSprite, 89.0, 9.8);
			agk::PlaySprite(trumpSprite, 5, 20, 1, 9);
			//agk::Sync();
		}
	if ((agk::GetSpriteExists(trumpSprite) == 1) && (trumpSymb == 49))
		{
			agk::SetSpriteAnimation(trumpSprite, 150.1, 150, 8);
			agk::SetSpriteSize(trumpSprite, 6, 6);
			agk::SetSpritePosition(trumpSprite, 89.0, 9.8);
			agk::PlaySprite(trumpSprite, 5, 20, 1, 9);
			//agk::Sync();
		}
	else if ((agk::GetSpriteExists(trumpSprite) == 0) && (trumpSymb == 49))
		{
			agk::CreateSprite(trumpSprite, trumpSymb);
			agk::SetSpriteAnimation(trumpSprite, 150.1, 150, 8);
			agk::SetSpriteSize(trumpSprite, 6, 6);
			agk::SetSpritePosition(trumpSprite, 89.0, 9.8);
			agk::PlaySprite(trumpSprite, 5, 20, 1, 9);
			//agk::Sync();
		}
	if ((agk::GetSpriteExists(trumpSprite) == 1) && (trumpSymb == 50))
		{
			agk::SetSpriteAnimation(trumpSprite, 150.1, 150, 8);
			agk::SetSpriteSize(trumpSprite, 6, 6);
			agk::SetSpritePosition(trumpSprite, 89.0, 9.8);
			agk::PlaySprite(trumpSprite, 5, 20, 1, 9);
			//agk::Sync();
		}
	else if ((agk::GetSpriteExists(trumpSprite) == 0) && (trumpSymb == 50))
		{
			agk::CreateSprite(trumpSprite, trumpSymb);
			agk::SetSpriteAnimation(trumpSprite, 150.1, 150, 8);
			agk::SetSpriteSize(trumpSprite, 6, 6);
			agk::SetSpritePosition(trumpSprite, 89.0, 9.8);
			agk::PlaySprite(trumpSprite, 5, 20, 1, 9);
			//agk::Sync();
		}
	//agk::SetSpriteSize(500, 6, 6);
	//agk::SetSpritePosition(500, 88.5, 10.2);
}*/

void AnimatedSprite::displayTrump()
{
	//for(int i = 0; i < 100; i++)
	//{
	agk::PlaySprite(500, 5, 20, 1, 9);
	//agk::Sync();
	//agk::Sleep(200);
	//}
}

void AnimatedSprite::hide()
{
	float newSpriteX = getX();
	float newSpriteY = getY();

	if (newSpriteX != 200.0)
	{
		spriteX = newSpriteX;
		spriteY = newSpriteY;
		display(200.0, getY());
	}
}

void AnimatedSprite::show()
{
	float newSpriteX = getX();
	float newSpriteY = getY();

	if (newSpriteX >= 100.0)
		display(spriteX, getY());

	if (newSpriteY >= 100.0)
		display(getX(), spriteY);
}

bool AnimatedSprite::isPlaying()
{
	if (agk::GetSpritePlaying(spriteNumber))
		return true;
	else
		return false;
}

bool AnimatedSprite::isVisible(void)
{
	float currentX = getX();
	float currentY = getY();
    float temp = agk::GetSpriteWidth(spriteNumber);
    float tempY = agk::GetSpriteHeight(spriteNumber);

	if (currentX > (100.0f))
        return false;
    if ((currentX + temp) <= 0.0f)
        return false;
    if (currentY > (100.0f ))
        return false;
    if ((currentY + tempY) <= 0.0f)
        return false;

    return true;
}
