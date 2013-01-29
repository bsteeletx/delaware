#include "Numbers.h"
#include "agk.h"

Numbers::Numbers(void)
{
	visDigit1 = 0;
	visDigit2 = 0;
	visDigit3 = 0;
	colorValue[0] = 0;
	colorValue[1] = 0;
	colorValue[2] = 0;
	colorValue[3] = 255;
	isPositive = true;
	value = 0;
	useMinus = true;
}

Numbers::~Numbers(void)
{
}

void Numbers::useParentheses(void)
{
	useMinus = false;
}

void Numbers::init(unsigned short theme)
{
	Text Dir = Text();

	switch (theme)
	{
	case GREEN:
		Dir.init("green/");
		break;
	case RED:
		Dir.init("red/");
		break;
	case ANCIENT:
		Dir.init("ancient/");
		break;
	case NOEL:
		Dir.init("noel/");
		break;
	default:
		initDefaultNumbers();
		return;
		break;
	}

	initThematicNumbers(Dir);
}

void Numbers::init(Text ThemeDir)
{
	initThematicNumbers(ThemeDir);
}

void Numbers::initDefaultNumbers()
{
    Text ParentFileName = Text();
    
	ParentFileName.init("default/Numbers.png");
	DefaultParent.parentInit(ParentFileName);
    
    for (int i = 0; i < 10; i++)
    {
		Text Buffer = Text();
		Text Extension = Text();

        Buffer.init(agk::Str(i));
		Extension.init(".png");

		Buffer += Extension;
       
        DigitOne[i]->subInit(DefaultParent.getImageNumber(), Buffer);
		DigitTwo[i]->subInit(DefaultParent.getImageNumber(), Buffer);
		DigitThree[i]->subInit(DefaultParent.getImageNumber(), Buffer);
    }
}

void Numbers::initThematicNumbers(Text Directory)
{
	Text ParentFileName = Directory;
	Text TempFileName = Text();

	TempFileName.init("Numbers.png");
    
	ParentFileName += TempFileName;
	Parent.parentInit(ParentFileName);
    
    for (int i = 0; i < 10; i++)
    {
		Text Buffer = Text();
		Text Extension = Text();

		Buffer.init(agk::Str(i));
		Extension.init(".png");
        
		Buffer += Extension;

		DigitOne[i]->subInit(Parent.getImageNumber(), Buffer);
		DigitTwo[i]->subInit(Parent.getImageNumber(), Buffer);
		DigitThree[i]->subInit(Parent.getImageNumber(), Buffer);
    }
}
/*
void Numbers::setData(Text *ThemeFilePath, bool useParentheses)
{
    unsigned imgNum;
    //char tempDir[32] = {NULL};
    
    //strcpy(tempDir, d);
    
    //strcat(tempDir, "Numbers.png");

	Text *ParentImageFilePath = new Text(*ThemeFilePath += "Numbers.png");
    
	if (ParentImageFilePath->getChar(0) == 'd')
    {
        if (!ScoreParent.isParentImageSet())
            initDefaultNumbers();
    }
    else
    {
        if (!Parent.isParentImageSet() || Parent.isDifferent(ParentImageFilePath->getString()))
			initThematicNumbers(ThemeFilePath->getString());
    }
   
	for (short int i = 0; i < 10; i++)
	{
        if (*ThemeFilePath == Text("default/"))
        {
            DigitOne[i]->setImageNumber(defaultNumbers[i]);
            DigitTwo[i]->setImageNumber(defaultNumbers[i]);
            DigitThree[i]->setImageNumber(defaultNumbers[i]);
        }
        else
        {
            DigitOne[i]->setImageNumber(thematicNumbers[i]);
            DigitTwo[i]->setImageNumber(thematicNumbers[i]);
            DigitThree[i]->setImageNumber(thematicNumbers[i]);
        }
	}

	if (useParentheses)
	{
		useMinus = false;
        
        imgNum = Parent.getImageNumber("left_parenthesis.png");
        
		Parentheses[0]->setImageNumber(imgNum);
        
        imgNum = Parent.getImageNumber("right_parenthesis.png");
        
		Parentheses[1]->setImageNumber(imgNum);
		Parentheses[0]->setSize(1.5f);
		Parentheses[1]->setSize(1.5f);
		Parentheses[0]->setPriority(5);
		Parentheses[1]->setPriority(5);
	}
	else
	{
		if (MinusSign->getID() == 0)
		{
			MinusSign->createT("-");
			MinusSign->color(0, 0, 0);
		}
		useMinus = true;
	}
    
    isPositive = true;
}
*/
void Numbers::setSize(float x, float y)
{
    float factor = 1.0f;
    
    if (PLATFORM == MOBILE)
        factor = 1.5;
    
	for (short int i = 0; i < 10; i++)
	{
		DigitOne[i]->setSize(x, y);
		DigitTwo[i]->setSize(x, y);
		DigitThree[i]->setSize(x, y);
	}
	
	if (useMinus)
		MinusSign->setSize(x*2.5f*factor); //5.5f?
}

/*void Numbers::setDigitData(short int digit, char desc[])
{
	switch (digit)
	{
	case 0:
		for (short int i = 0; i < 10; i++)
			DigitOne[i].setData(DigitOne[i].getImageNumber(), desc);
		break;
	case 1:
		for (short int i = 0; i < 10; i++)
			DigitTwo[i].setData(DigitTwo[i].getImageNumber(), desc);
		break;
	case 2:
		for (short int i = 0; i < 10; i++)
			DigitThree[i].setData(DigitThree[i].getImageNumber(), desc);
		break;
	default:
		break;
	}

	
	//updateValue(getSeparatedValue());
}
*/
void Numbers::setDepth(short unsigned int depthValue)
{
	for (short int j = 0; j < 10; j++)
	{
		if (DigitOne[j]->getExists())
			DigitOne[j]->setDepth(depthValue);
		if (DigitTwo[j]->getExists())
			DigitTwo[j]->setDepth(depthValue);
		if (DigitThree[j]->getExists())
			DigitThree[j]->setDepth(depthValue);
	}

	if (useMinus)
		MinusSign->setDepth(55);
}

/*void Numbers::setLocationAll(Point *Location, Point *NegOffset)
{
	for (int i = 0; i < 3; i++)
		setLocation(i, Location->getX(), Location->getY(), NegOffset->getX(), NegOffset->getY();
}*/

void Numbers::setLocation(short int digit, float x, float y, float negOffsetX, float negOffsetY)
{
	switch (digit)
	{
	case 0:
		for (short int i = 0; i < 10; i++)
		{
			DigitOne[i]->setPosition(x, y);
			DigitOne[i]->setVisible(false);
		}
		visDigit1 = 0;
		break;
	case 1:
		for (short int i = 0; i < 10; i++)
		{
			DigitTwo[i]->setPosition(x, y);
			DigitTwo[i]->setVisible(false);
		}
		visDigit2 = 0;
		break;
	case 2:
		for (short int i = 0; i < 10; i++)
		{
			DigitThree[i]->setPosition(x, y);
			DigitThree[i]->setVisible(false);
		}
		visDigit3 = 0;
		break;
	default:
		break;
	}

	if ((digit == 1) && useMinus)
		MinusSign->setPosition(x + negOffsetX, y + negOffsetY);
	else if ((digit == 0) && !useMinus)
	{
		Parentheses[0]->setPosition(x + negOffsetX, y + negOffsetY); //12.f, 92.4f
		Parentheses[1]->setPosition(x + negOffsetX + 7.25f, y + negOffsetY); //21.0f
	}
}

void Numbers::display(short int digit, short int number, float x, float y)
{
	switch (digit)
	{
	case 0:
		DigitOne[visDigit1]->setVisible(false);
		DigitOne[number]->setPosition(x, y);
		DigitOne[number]->setVisible(true);
		visDigit1 = number;
		break;
	case 1:
		DigitTwo[visDigit2]->setVisible(false);
		DigitTwo[number]->setPosition(x, y);
		DigitTwo[number]->setVisible(true);
		visDigit2 = number;
		break;
	case 2:
		if (number == 0)
			DigitThree[visDigit3]->setVisible(false);
		else
		{
			DigitThree[visDigit3]->setVisible(false);
			DigitThree[number]->setPosition(x, y);
			DigitThree[number]->setVisible(true);
			visDigit3 = number;
		}
		break;
	default:
		break;
	}
}

void Numbers::display(short int digit, short int number)
{
	switch (digit)
	{
	case 0:
		DigitOne[visDigit1]->setVisible(false);
		//DigitOne[number].display();
		DigitOne[number]->setVisible(true);
		visDigit1 = number;
		break;
	case 1:
		DigitTwo[visDigit2]->setVisible(false);
		
		//DigitTwo[number].display();
		DigitTwo[number]->setVisible(true);
		visDigit2 = number;
		break;
	case 2:
		DigitThree[visDigit3]->setVisible(false);

		if (number == 0)
		{
			DigitThree[visDigit3]->setVisible(false);
			visDigit3 = 0;
		}
		else
		{
			//DigitThree[number].display();
			DigitThree[number]->setVisible(true);
			visDigit3 = number;
		}
		break;
	default:
		break;
	}
}

void Numbers::hide(short int digit, short int number)
{
	if (number == -1)
		return;

	switch (digit)
	{
	case 0:
		DigitOne[number]->setVisible(false);
		visDigit1 = 0;
		break;
	case 1:
		DigitTwo[number]->setVisible(false);
		visDigit2 = 0;
		break;
	case 2:
		DigitThree[number]->setVisible(false);
		visDigit3 = 0;
		break;
	default:
		break;
	}

	if (useMinus)
		MinusSign->setVisible(false);
	else
	{
		Parentheses[0]->setVisible(false);
		Parentheses[1]->setVisible(false);
	}
}
/*
void Numbers::changeImage(short int theme)
{
	for (short int i = 0; i < 10; i++)
	{
		DigitOne[i].changeImage(100 + (theme*10) + i);
		DigitTwo[i].changeImage(100 + (theme*10) + i);
		DigitThree[i].changeImage(100 + (theme*10) + i);
	}
}
*/
void Numbers::hideAll(void)
{
	for (short int j = 0; j < 10; j++)
	{
		DigitOne[j]->setVisible(false);
		DigitTwo[j]->setVisible(false);
		DigitThree[j]->setVisible(false);
	}
	
	if (useMinus)
		MinusSign->setVisible(false);
	else
	{
		Parentheses[0]->setVisible(false);
		Parentheses[1]->setVisible(false);
	}
}

void Numbers::showAll(bool always)
{
	if (abs(value) == 0)
	{
		if (always)
		{
			for (short int i = 0; i < 10; i++)
			{
				DigitOne[i]->setVisible(false);
				DigitTwo[i]->setVisible(false);
				DigitThree[i]->setVisible(false);
			}
			DigitOne[0]->setVisible(true);
		}
	}
	else
	{
		visDigit1 = abs(value) % 10;
		
		DigitOne[visDigit1]->setVisible(true);
	}
	if (abs(value) > 9)
	{
		visDigit2 = abs(value) % 100 / 10;

		DigitTwo[visDigit2]->setVisible(true);
	}
	if (abs(value) > 99)
	{
		visDigit3 = abs(value) / 100;

		DigitThree[visDigit3]->setVisible(true);
	}

	if (!isPositive)
	{
		if (useMinus)
			MinusSign->setVisible(true);
		else
		{
			Parentheses[0]->setVisible(true);
			Parentheses[1]->setVisible(true);
		}
	}
}

void Numbers::show(short int digit, short int number)
{
	switch (digit)
	{
	case 0:
		DigitOne[number]->setVisible(true);
		visDigit1 = number;
		break;
	case 1:
		DigitTwo[number]->setVisible(true);
		visDigit2 = number;
		break;
	case 2:
		DigitThree[number]->setVisible(true);
		visDigit3 = number;
		break;
	default:
		break;
	}
}

short int Numbers::getDigit(short int digit)
{
	switch (digit)
	{
	case 0:
		return visDigit1;
	case 1:
		return visDigit2;
	case 2:
		return visDigit3;
	default:
		return -1;
	}
}

void Numbers::setDigit(short int digit, short int number)
{
	switch (digit)
	{
	case 0:
		visDigit1 = number;
		break;
	case 1:
		visDigit2 = number;
		break;
	case 2:
		visDigit3 = number;
		break;
	default:
		break;
	}

	//updateValue(getSeparatedValue());
}

bool Numbers::getVisible(void)
{
	if (visDigit1 + visDigit2 + visDigit3 <= -3)
		return false;
	else
		return true;
}

/*bool Numbers::scroll(char value, char digit)
{
	char testValue = value; 
	char testDigit;

	switch (digit)
	{
	case 0:
		testDigit = visDigit1;
		//testValue = value % 10;
		break;
	case 1:
		testDigit = visDigit2;
		//testValue = value % 100 / 10;
		break;
	case 2:
		testDigit = visDigit3;
		//testValue = value % 100;
		break;
	}

	if (testDigit != testValue)
	{
		int alpha = 255 - (abs(testDigit - i) * 255);

		if (alpha < 0)
			alpha = 0;
        
		float size = (alpha / 255) * 10;
		float posY = (testValue - i) * 10;
		char direction;

		if (testDigit < testValue)
			direction = 1;
		else
			direction = -1;

		if (!DigitOne[testDigit+direction].isVisible())
			DigitOne[testDigit+direction].show();

		float posY;

		if (digit == 0)
		{
			DigitOne[testDigit].setSize(50.0, DigitOne[testDigit].getSizeY() + direction);

			if (DigitOne[testDigit+direction].getSizeY() != 0.0)
				DigitOne[testDigit+direction].setSize(50.0, 0.0);
			else if (DigitOne[testDigit+direction].getSizeY() != 66.0)
				DigitOne[testDigit+direction].setSize(50.0, DigitOne[testDigit+direction].getSizeY() + direction);
			
			DigitOne[testDigit].display(DigitOne[testDigit].getX(), DigitOne[testDigit].getY() + direction);
			DigitOne[testDigit+direction].display(DigitOne[testDigit+direction].getX(), DigitOne[testDigit+direction].getY() + direction);

			posY = DigitOne[testDigit].getY();

			if (posY > 67.0)
			{
				posY = 67.0;
				DigitOne[testDigit].hide();
				visDigit1 = value;
			}
        
			if (posY < 53.0)
			{
				posY = 53.0;
				DigitOne[testDigit].hide();
				visDigit1 = value;
			}
		}
		else if (digit == 1)
		{
			DigitTwo[i].setAlpha(alpha);
			DigitTwo[i].setSize(50.0, size);
			posY += DigitTwo[i].getY();
			if (posY > 67.0)
				posY = 67.0;
        
			if (posY < 53.0)
				posY = 53.0;
			DigitTwo[i].display(DigitTwo[i].getX(), posY);
			//visDigit2 = value;
		}
		else if (digit == 2)
		{
			DigitThree[i].setAlpha(alpha);
			DigitThree[i].setSize(50.0, size);
			posY += DigitThree[i].getY();
			if (posY > 67.0)
				posY = 67.0;
        
			if (posY < 53.0)
				posY = 53.0;
			DigitThree[i].display(DigitThree[i].getX(), posY);
			//visDigit3 = value;
		}
	}
	return false;
}*/

void Numbers::decrementValue(void)
{
   /* short tempDigit1 = visDigit1;
    short tempDigit2 = visDigit2;
    short tempDigit3 = visDigit3;
    
    tempDigit1--;
    
    if (tempDigit1 == -1)
    {
        tempDigit1 = 9;
        tempDigit2--;
        
        if (tempDigit2 == -1)
        {
            tempDigit2 = 9;
            tempDigit3--;
        }
    }
    
    setValue(
    tempValue = abs(tempValue) - 1;
    if (tempValue <= 0)
        makePositive();
    else
        tempValue = -tempValue;*/
    
    setValue(value-1);
}

void Numbers::incrementValue()
{
    setValue(value+1);
}

void Numbers::incrementTo(short int targetValue, bool alwaysDisplay)
{
    bool adding = true;
	short int tempValue = 0;
	short int tempDigit1 = visDigit1;
	short int tempDigit2 = visDigit2;
	short int tempDigit3 = visDigit3;

	/*if ((tempDigit3 < 0) || (tempDigit3 > 9))
		tempDigit3 = 0;
	if ((tempDigit2 < 0) || (tempDigit2 > 9))
		tempDigit2 = 0;
	if ((tempDigit1 < 0) || (tempDigit1 > 9))
		tempDigit1 = 0;*/

	tempValue = tempDigit3 * 100;

	tempValue += tempDigit2 * 10;

	tempValue += tempDigit1;

	if (!isPositive)
		tempValue = -tempValue;
	
	if ((targetValue == tempValue) && !alwaysDisplay)
		return;
    
    if (alwaysDisplay && !targetValue)
    {
        if (targetValue == tempValue)
        {
            display(0, 0);
            return;
        }
    }

    if (targetValue < tempValue)
        adding = false;
    
	//if (((targetValue > tempValue) && (tempValue >= 0)) || ((targetValue < tempValue) && (tempValue < 0)))
    if (adding)
	{
		/*tempDigit1++;
		if (tempDigit1 == 10)
		{
			tempDigit1 = 0;
			tempDigit2++;

			if (tempDigit2 == 10)
			{
				tempDigit2 = 0;
				tempDigit3++;
			}
		}
		tempValue = abs(tempValue) + 1;
		if (!isPositive)
			tempValue = -tempValue;
        if ((tempValue == 1) && (targetValue < 0))
            makeNegative();*/
        incrementValue();
	}
	else if (targetValue != tempValue)
	{
        decrementValue();
		
	}
/*
	display(0, tempDigit1);
	if (abs(tempValue) > 9)
		display(1, tempDigit2);
	else
		hide(1, visDigit2);
	
	if (abs(tempValue) > 99)
		display(2, tempDigit3);
	else
		hide(2, visDigit3);

	value = abs(tempValue);*/
}

void Numbers::makeNegative(void)
{
    isPositive = false;
    
    if (useMinus)
        MinusSign->setVisible(true);
    else
    {
        Parentheses[0]->setVisible(true);
        Parentheses[1]->setVisible(true);
    }
}

void Numbers::makePositive(void)
{
    isPositive = true;
    
    if (useMinus)
        MinusSign->setVisible(false);
    else
    {
        Parentheses[0]->setVisible(false);
        Parentheses[1]->setVisible(false);
    }
}

bool Numbers::getPositive(void)
{
	return isPositive;
}

void Numbers::setValue(short int newValue)
{
	short tempValue = abs(newValue);

	visDigit1 = tempValue % 10;
	visDigit2 = tempValue % 100 / 10;
	visDigit3 = tempValue / 100;
    
    hideAll();
	display(0, visDigit1);
	if (tempValue > 9)
		display(1, visDigit2);
	if (tempValue > 99)
		display(2, visDigit3);

	value = newValue;

	if (value < 0)
		makeNegative();
	else
		makePositive();
	//updateValue(getSeparatedValue());
}

short int Numbers::getValue(void)
{
    return value;
}

void Numbers::setColor(unsigned short int red, unsigned short int green, unsigned short int blue, unsigned short int alpha)
{
	colorValue[0] = red;
	colorValue[1] = green;
	colorValue[2] = blue;
	colorValue[3] = alpha;

	RGBA Colors = RGBA();

	Colors.init(red, green, blue, alpha);

	for (short int i = 0; i < 10; i++)
	{
		DigitOne[i]->setColor(Colors);
		DigitTwo[i]->setColor(Colors);
		DigitThree[i]->setColor(Colors);
	}
}

bool Numbers::isVisible(void)
{
	for (short int i = 0; i < 10; i++)
	{
		if(DigitOne[i]->getVisible())
			return true;
	}

	return false;
}

float Numbers::getX(short int digit)
{
	switch (digit)
	{
	case 1:
		return DigitOne[visDigit1]->getX();
		break;
	case 2:
		return DigitTwo[visDigit2]->getX();
		break;
	case 3:
		return DigitThree[visDigit3]->getX();
		break;
	}

	return -1.0f;
}

float Numbers::getY(short int digit)
{
	switch (digit)
	{
	case 1:
		return DigitOne[visDigit1]->getY();
		break;
	case 2:
		return DigitTwo[visDigit2]->getY();
		break;
	case 3:
		return DigitThree[visDigit3]->getY();
		break;
	}

	return -1.0f;
}