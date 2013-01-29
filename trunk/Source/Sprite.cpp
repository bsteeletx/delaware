 #include "Sprite.h"
#include "template.h"

Sprite::Sprite()
{
	grown = true;
	growing = false;
	shrunk = false;
	shrinking = false;
	priority = -1;
	imageNumber = 0;
	spriteNumber = 0;
    xScaleSize = 0.0f;
    yScaleSize = 0.0f;
}

Sprite& Sprite::operator= (const Sprite &newSprite)
{
	imageNumber = newSprite.imageNumber;
	spriteNumber = newSprite.spriteNumber;
	grown = newSprite.grown;
	growing = newSprite.growing;
	shrunk = newSprite.shrunk;
	shrinking = newSprite.shrinking;
	//strcpy(filename, newSprite.filename);
	priority = newSprite.priority;

	return *this;
}


void Sprite::setData(const char newFilename[], const char newFilepath[])
{
	char temp[64] = {NULL};
    bool deletable = true;

	if ((strlen(newFilepath) + strlen(newFilename)) < 64)
	{
		strcpy(temp, newFilepath);
		strcat(temp, newFilename);
	}
	else
		return;

	if (!agk::GetFileExists(temp))
	{
		strcpy(temp, "default/");
		strcat(temp, newFilename);

        deletable = false;

		if (!agk::GetFileExists(temp))
			return;
		//else
		//{
			//filename = newFilename;
			//filepath = "default/";
		//}
	}
	//else
	//{
		//filename = newFilename;
		//filepath = newFilepath;
	//}

	if (!agk::GetSpriteExists(spriteNumber))
	{
		imageNumber = agk::LoadImage(temp);

        if (deletable)
            addToQueue(imageNumber, 0);
        else
            addToQueue(imageNumber, 1);

		spriteNumber = agk::CreateSprite(imageNumber);
	}
	else
	{
		imageNumber = agk::LoadImage(temp);

        //agk::SetSpriteImage(spriteNumber, 0);
        //agk::SetSpriteImage(spriteNumber, imageNumber);
        agk::DeleteSprite(spriteNumber);

        spriteNumber = agk::CreateSprite(imageNumber);

        if (deletable)
            addToQueue(imageNumber, 0);
        else
            addToQueue(imageNumber, 1);

	}
	hide();
}


void Sprite::setData(unsigned short int image, const char name[])
{
	if (agk::GetImageExists(image))
	{
		imageNumber = agk::LoadSubImage(image, name);
	}
	else
		return;

	if (agk::GetImageExists(imageNumber))
	{
		if (spriteNumber != 0)
            changeImage(imageNumber);
        else
            spriteNumber = agk::CreateSprite(imageNumber);
	}
	else
    {
        imageNumber = 0;
        return;
    }

	//filename = name;
	//strcpy(filename, name);

	hide();
}

void Sprite::setImageNumber(unsigned int imageNum)
{
    /*if (agk::GetImageExists(imageNum))
    {
        if (spriteNumber)
            agk::DeleteSprite(spriteNumber);

        spriteNumber = agk::CreateSprite(imageNum);
    }
    else
        imageNumber = 0;

    imageNumber = imageNum;*/

    changeImage(imageNum);

    hide();
}

void Sprite::setData(unsigned short parentImages[], const char name[])
{
    int length = 4;
    int imageNum = 0;

    for (int i = 0; i < length; i++)
    {

        if (agk::GetImageExists(parentImages[i]))
        {
            imageNum = agk::LoadSubImage(parentImages[i], name);
        }
        else
            return;

        if (agk::GetImageExists(imageNum))
        {
            /*if (spriteNumber)
                agk::DeleteSprite(spriteNumber);

            spriteNumber = agk::CreateSprite(imageNumber);*/
            changeImage(imageNum);
        }

	//filename = name;
	//strcpy(filename, name);

        hide();
    }
}

void Sprite::moveSprite(float x, float y)
{
	//x /= FACTOR;
	//y /= FACTOR;

	agk::SetSpritePosition(spriteNumber, x, y);
}

Sprite::~Sprite(void)
{

}

void Sprite::setPriority(unsigned short int newPriority)
{
	priority = 10000 - newPriority;
	agk::SetSpriteDepth(spriteNumber, priority);
}

void Sprite::display(float x, float y)
{
	//x /= FACTOR;
	//y /= FACTOR;
	//if (!spriteNumber || !imageNumber)
		//agk::Print("Uh-Oh!");
	agk::SetSpritePosition(spriteNumber, x, y);
	agk::SetSpriteDepth(spriteNumber, priority);
	//agk::SetSpriteX(spriteNumber, x);
	//agk::SetSpriteY(spriteNumber, y);
}

void Sprite::setImprint(float x, float y)
{
	xImprint = x;
	yImprint = y;
}

float Sprite::getImprintX(void)
{
	return xImprint;
}

float Sprite::getImprintY(void)
{
	return yImprint;
}

void Sprite::display()
{
	float x = agk::GetSpriteX(spriteNumber);
	float y = agk::GetSpriteY(spriteNumber);

	agk::SetSpritePosition(spriteNumber, x, y);
}

bool Sprite::hasShrunk()
{
	return shrunk;
}

bool Sprite::isShrinking()
{
	return shrinking;
}

bool Sprite::isMoving(void)
{
	return moving;
}

void Sprite::moveOnScreen(short direction)
{
	float x = getX();
	float y = getY();
	float newX;
	float newY;
	//float amount;
	float speed = 2.0f;

	if (!moving)
	{
		switch (direction)
		{
		case WEST:
			x = WEST_LOC_X - (50.0f ) - xScaleSize;
			break;
		case NORTH:
			y = NORTH_LOC_Y - (50.0f ) - yScaleSize;
			break;
		case EAST:
			x = EAST_LOC_X + (50.0f );
			break;
		case SOUTH:
			y = SOUTH_LOC_Y + (50.f );
			break;
		}

		moving = true;
	}

	newX = 27.5f ;
	newY = 23.0f ;

	if (direction > 1)
	{
		if (fabsf(newX - x) < speed)
			x = newX;
		else if (x < newX)
			x += (x - newX) / speed;
		else
			x += (newX - x) / speed;

		if (fabsf(newY - y) < speed)
			y = newY;
		else if (y < newX)
			y += (y - newY) / speed;
		else
			y += (newY - y) / speed;
	}
	else
	{
		if (fabsf(newX - x) < speed)
			x = newX;
		else if (x > newX)
			x += (x - newX) / speed;
		else
			x += (newX - x) / speed;

		if (fabsf(newY - y) < speed)
			y = newY;
		else if (y > newX)
			y += (y - newY) / speed;
		else
			y += (newY - y) / speed;
	}

	display(x, y);
	show();

	if ((newX == x) && (newY == y))
	{
		moving = false;
		//hide();
	}
}

void Sprite::moveOffScreen(short direction)
{
	float x = getX();
	float y = getY();
	float newX;
	float newY;
	//float amount;
	float speed = 2.0f;

	moving = true;

	switch (direction)
	{
	case WEST:
		newX = WEST_LOC_X - ((50.0f ) + xScaleSize);
		newY = y;
		break;
	case NORTH:
		newX = x;
		newY = NORTH_LOC_Y - ((50.0f ) + yScaleSize);;
		break;
	case EAST:
		newX = EAST_LOC_X + (50.0f );
		newY = y;
		break;
	case SOUTH:
		newX = x;
		newY = SOUTH_LOC_Y + (50.0f );
		break;
	}

	if (direction > 1)
	{
		if (fabsf(newX - x) < speed)
			x = newX;
		else if (x > newX)
			x += (x - newX) / speed;
		else
			x += (newX - x) / speed;

		if (fabsf(newY - y) < speed)
			y = newY;
		else if (y > newY)
			y += (y - newY) / speed;
		else
			y += (newY - y) / speed;
	}
	else
	{
		if (fabsf(newX - x) < speed)
			x = newX;
		else if (x < newX)
			x += (x - newX) / speed;
		else
			x += (newX - x) / speed;

		if (fabsf(newY - y) < speed)
			y = newY;
		else if (y < newY)
			y += (y - newY) / speed;
		else
			y += (newY - y) / speed;
	}

	display(x, y);


	if ((newX == x) && (newY == y))
	{
		moving = false;
		hide();
	}
}

void Sprite::updateShrinkClose(short int location)
{
	float x = getX();
	float y = getY();
	float newX;
	float newY;
	float amount;
	float speed = 2.0f;


	shrinking = true;

	if (curScaleX - speed < 0.0f)
		amount = 0.0f;
	else
		amount = curScaleX - speed;

	switch (location)
	{
	case -2:
		newX = getImprintX();
		newY = getImprintY();
		break;
	case WEST:
		newX = WEST_LOC_X;
		newY = WEST_LOC_Y;
		break;
	case NORTH:
		newX = NORTH_LOC_X;
		newY = NORTH_LOC_Y;
		break;
	case EAST:
		newX = EAST_LOC_X;
		newY = EAST_LOC_Y;
		break;
	case SOUTH:
		newX = SOUTH_LOC_X;
		newY = SOUTH_LOC_Y;
		break;
	default:
		newX = CENTER_X;
		newY = CENTER_Y;
		break;
	}

	grown = false;

	if (x > newX)
		x += (x - newX) / speed;
	else
		x += (newX - x) / speed;

	if (y > newX)
		y += (y - newY) / speed;
	else
		y += (newY - y) / speed;

	setSize(amount, -1.0f, false);
	if (priority == -1)
		setPriority(5);
	display(x, y);
	//show();
	//dbSync();
	//dbWait(50);

	if (amount == 0)
	{
		shrunk = true;
		shrinking = false;
		display(newX, newY);
		hide();
		inAnimation = false;
	}

	inAnimation = true;
}

void Sprite::updateGrowOpen(float xamount, float yamount)
{
	float x;
	float y;
	short int speed = 15;  //move up for slower, down for faster
	float xStretchValue = xamount;
	float yStretchValue = yamount;
	const int ASPECT_Y = agk::GetDeviceWidth();
	const int ASPECT_X = agk::GetDeviceHeight();
    //curScaleX = agk::GetSpriteWidth(spriteNumber);
    //curScaleY = agk::GetSpriteHeight(spriteNumber);

	x = getX();
	y = getY();

	//amount = amount/1000;

	growing = true;
	shrunk = false;

	if (xamount > curScaleX)
	{
		if ((curScaleX + (xamount / speed)) <= xamount)
			xStretchValue = curScaleX + (xamount / speed);
		else
			xStretchValue = xamount;
	}

	if (yamount != -1)
	{
		if (yamount > curScaleY)
		{
			if ((curScaleY + (yamount / speed)) <= yamount)
				yStretchValue = curScaleY + (yamount / speed);
			else
				yStretchValue = yamount;

			setSize(xStretchValue, yStretchValue, false);
		}
		else
			setSize(xStretchValue, yamount, false);

	}
	else
		setSize(xStretchValue, -1.0f, false);

	if (x != xImprint)
	{
		if (xImprint >= 1.0)
		{
			if (x - (xImprint / ASPECT_X) < xImprint)
				x = xImprint;
			else if (x > xImprint)
				x -= (xImprint / ASPECT_X);
		}
		else
		{
			if ((x / ASPECT_X) < ASPECT_X)
				x = xImprint;
			else
				x -= x / ASPECT_X;
		}
	}

	if (y != yImprint)
	{
		if (yImprint >= 1.0)
		{
			if (y - (yImprint / ASPECT_Y) < yImprint)
				y = yImprint;
			else if (y > yImprint)
				y -= (yImprint / ASPECT_Y);
		}
		else
		{
			if ((y / ASPECT_Y) < ASPECT_Y)
				y = yImprint;
			else
				y -= y / ASPECT_Y;
		}
	}

	display(x, y);
	show();
	//agk::Sync();
	//agk::Sleep(500);

	if ((curScaleX == xScaleSize) && (x == xImprint) && (y == yImprint))
	{
		if (yamount != -1)
		{
			 if (curScaleY == yamount)
			 {
				grown = true;
				growing = false;
				inAnimation = false;
			 }
			 else
				 inAnimation = true;
		}
		else if (yamount == -1)
		{
			grown = true;
			growing = false;
			inAnimation = false;
		}
		else
		{
			growing = true;
			grown = false;
			inAnimation = true;
		}
	}
	else
		inAnimation = true;
}

float Sprite::getScaleSize(void)
{
	return xScaleSize;
}

float Sprite::getScaleSizeY(void)
{
	return yScaleSize;
}

bool Sprite::hasGrown()
{
	return grown;
}

bool Sprite::isGrowing()
{
	return growing;
}

void Sprite::changeImage(unsigned short int imageNum)
{
	if (agk::GetImageExists(imageNum))
	{
		if (agk::GetSpriteExists(spriteNumber))
        {
            agk::DeleteSprite(spriteNumber);
            spriteNumber = agk::CreateSprite(imageNum);

            //agk::SetSpriteImage(spriteNumber, 0);

            //agk::SetSpriteImage(spriteNumber, imageNum);
        }
		else
			spriteNumber = agk::CreateSprite(imageNum);

        imageNumber = imageNum;
	}

}

void Sprite::changeImage(char newFilename[], char newFilepath[])
{
	setData(newFilename, newFilepath);
}

void Sprite::offset(float x, float y)
{
	//x /= FACTOR;
	//y /= FACTOR;
	agk::SetSpriteOffset(spriteNumber, (x*xScaleSize), (y*xScaleSize));
}

void Sprite::show()
{
	if (spriteNumber == 0)
		return;

    if (imageNumber == 0)
        return;

    if (agk::GetSpriteExists(spriteNumber) == 0)
        return;

    if (agk::GetImageExists(imageNumber) == 0)
        return;

	if (agk::GetSpriteVisible(spriteNumber))
		return;

	agk::SetSpriteVisible(spriteNumber, 1);
	display();
}

bool Sprite::isValid()
{
	if (agk::GetSpriteExists(spriteNumber))
		return true;
	else
		return false;
}

bool Sprite::isVisible()
{
	if (agk::GetSpriteVisible(spriteNumber))
	{
		if (getX() > (100.0f ))
			return false;
		if ((getX() + xScaleSize) < 0.0f)
			return false;
		if (getY() > (100.0f ))
			return false;
		if ((getY() + yScaleSize) < 0.0f)
			return false;

		return true;
	}
	else
		return false;
}

void Sprite::hide()
{
	if (spriteNumber == 0)
		return;

	if (!agk::GetSpriteExists(spriteNumber))
		return;

	if (!agk::GetSpriteVisible(spriteNumber))
		return;

	agk::SetSpriteVisible(spriteNumber, 0);
}

unsigned short int Sprite::getImageNumber()
{
	return imageNumber;
}

unsigned short int Sprite::getSpriteNumber()
{
	return spriteNumber;
}

float Sprite::getX()
{
	return agk::GetSpriteX(spriteNumber);
}

float Sprite::getY()
{
	return agk::GetSpriteY(spriteNumber);
}

void Sprite::setSize(float x, bool init)
{
	//x /= FACTOR;

	agk::SetSpriteSize(spriteNumber, x, -1.0f);

	if (init)
	{
		xScaleSize = x;
		yScaleSize = -1.0f;
	}

	curScaleX = x;
	curScaleY = -1.0f;
}

void Sprite::setSize(float x, float y, bool init)
{
	//x /= FACTOR;
	//y /= FACTOR;

	agk::SetSpriteSize(spriteNumber, x, y);

	if (init)
	{
		xScaleSize = x;
		yScaleSize = y;
	}

	curScaleX = x;
	curScaleY = y;
}

void Sprite::setTransparency(unsigned short int spriteNumber, int mode)
{
	agk::SetSpriteTransparency(spriteNumber, mode);
}

void Sprite::setAlpha(unsigned short int alpha)
{
	agk::SetSpriteColorAlpha(spriteNumber, alpha);
}

float Sprite::getSizeY(void)
{
	return agk::GetSpriteHeight(spriteNumber);
}

void Sprite::changeColor(unsigned short int red, unsigned short int blue, unsigned short int green, unsigned short int alpha)
{
	agk::SetSpriteColor(spriteNumber, red, blue, green, alpha);
}

void Sprite::flipSprite()
{
    agk::SetSpriteAngle(spriteNumber, 180.0f);
}
