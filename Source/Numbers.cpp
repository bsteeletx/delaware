#include "template.h"
#include "Numbers.h"

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

void Numbers::initDefaultNumbers()
{
    char buffer[2];
    char tempFileName[8];

    ScoreParent.setImage("default/Numbers.png");

    for (int i = 0; i < 10; i++)
    {
        sprintf(buffer, "%d", i);
		strcpy(tempFileName, buffer);
		strcat(tempFileName, ".png");

        defaultNumbers[i] = ScoreParent.getImageNumber(tempFileName);
    }
}

void Numbers::initThematicNumbers(const char *dir)
{
    char buffer[2];
    char tempFileName[8];
    char tempFileLoc[32] = {NULL};

    strcpy(tempFileLoc, dir);
    strcat(tempFileLoc, "Numbers.png");

    Parent.setImage(tempFileLoc);

    for (int i = 0; i < 10; i++)
    {
        sprintf(buffer, "%d", i);
		strcpy(tempFileName, buffer);
		strcat(tempFileName, ".png");

        thematicNumbers[i] = Parent.getImageNumber(tempFileName);
    }
}

void Numbers::setData(const char dir[], bool useParentheses)
{
    unsigned imgNum;
    char tempDir[32] = {NULL};

    strcpy(tempDir, dir);

    strcat(tempDir, "Numbers.png");

    if (tempDir[0] == 'd')
    {
        if (!ScoreParent.isParentImageSet())
            initDefaultNumbers();
    }
    else
    {
        if (!Parent.isParentImageSet() || Parent.isDifferent(tempDir))
            initThematicNumbers(dir);
    }

	for (short int i = 0; i < 10; i++)
	{
        if (strcmp(dir, "default/") == 0)
        {
            digitOne[i].setImageNumber(defaultNumbers[i]);
            digitTwo[i].setImageNumber(defaultNumbers[i]);
            digitThree[i].setImageNumber(defaultNumbers[i]);
        }
        else
        {
            digitOne[i].setImageNumber(thematicNumbers[i]);
            digitTwo[i].setImageNumber(thematicNumbers[i]);
            digitThree[i].setImageNumber(thematicNumbers[i]);
        }
	}

	if (useParentheses)
	{
		useMinus = false;

        imgNum = Parent.getImageNumber("left_parenthesis.png");

		Parentheses[0].setImageNumber(imgNum);

        imgNum = Parent.getImageNumber("right_parenthesis.png");

		Parentheses[1].setImageNumber(imgNum);
		Parentheses[0].setSize(1.5f);
		Parentheses[1].setSize(1.5f);
		Parentheses[0].setPriority(5);
		Parentheses[1].setPriority(5);
	}
	else
	{
		if (MinusSign.getID() == 0)
		{
			MinusSign.createT("-");
			MinusSign.color(0, 0, 0);
		}
		useMinus = true;
	}

    isPositive = true;
}

void Numbers::setSize(float x, float y)
{
    float factor = 1.0f;

    if (PLATFORM == MOBILE)
        factor = 1.5;

	for (short int i = 0; i < 10; i++)
	{
		digitOne[i].setSize(x, y);
		digitTwo[i].setSize(x, y);
		digitThree[i].setSize(x, y);
	}

	if (useMinus)
		MinusSign.size(x*2.5f*factor); //5.5f?
}

void Numbers::setDigitData(short int digit, char desc[])
{
	switch (digit)
	{
	case 0:
		for (short int i = 0; i < 10; i++)
			digitOne[i].setData(digitOne[i].getImageNumber(), desc);
		break;
	case 1:
		for (short int i = 0; i < 10; i++)
			digitTwo[i].setData(digitTwo[i].getImageNumber(), desc);
		break;
	case 2:
		for (short int i = 0; i < 10; i++)
			digitThree[i].setData(digitThree[i].getImageNumber(), desc);
		break;
	default:
		break;
	}


	//updateValue(getSeparatedValue());
}

void Numbers::setPriority(short unsigned int prioValue)
{
	for (short int j = 0; j < 10; j++)
	{
		if (digitOne[j].getImageNumber() != 0)
			digitOne[j].setPriority(prioValue);
		if (digitTwo[j].getImageNumber() != 0)
			digitTwo[j].setPriority(prioValue);
		if (digitThree[j].getImageNumber() != 0)
			digitThree[j].setPriority(prioValue);
	}

	if (useMinus)
		MinusSign.setDepth(55);
}

void Numbers::setLocation(short int digit, float x, float y, float negOffsetX, float negOffsetY)
{
	switch (digit)
	{
	case 0:
		for (short int i = 0; i < 10; i++)
		{
			digitOne[i].display(x, y);
			digitOne[i].hide();
		}
		visDigit1 = 0;
		break;
	case 1:
		for (short int i = 0; i < 10; i++)
		{
			digitTwo[i].display(x, y);
			digitTwo[i].hide();
		}
		visDigit2 = 0;
		break;
	case 2:
		for (short int i = 0; i < 10; i++)
		{
			digitThree[i].display(x, y);
			digitThree[i].hide();
		}
		visDigit3 = 0;
		break;
	default:
		break;
	}

	if ((digit == 1) && useMinus)
		MinusSign.position(x + negOffsetX, y + negOffsetY);
	else if ((digit == 0) && !useMinus)
	{
		Parentheses[0].display(x + negOffsetX, y + negOffsetY); //12.f, 92.4f
		Parentheses[1].display(x + negOffsetX + 7.25f, y + negOffsetY); //21.0f
	}
}

void Numbers::display(short int digit, short int number, float x, float y)
{
	switch (digit)
	{
	case 0:
		digitOne[visDigit1].hide();
		digitOne[number].display(x, y);
		digitOne[number].show();
		visDigit1 = number;
		break;
	case 1:
		digitTwo[visDigit2].hide();
		digitTwo[number].display(x, y);
		digitTwo[number].show();
		visDigit2 = number;
		break;
	case 2:
		if (number == 0)
			digitThree[visDigit3].hide();
		else
		{
			digitThree[visDigit3].hide();
			digitThree[number].display(x, y);
			digitThree[number].show();
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
        digitOne[visDigit1].hide();
		digitOne[number].display();
		digitOne[number].show();
		visDigit1 = number;
		break;
	case 1:
		digitTwo[visDigit2].hide();

		digitTwo[number].display();
		digitTwo[number].show();
		visDigit2 = number;
		break;
	case 2:
		digitThree[visDigit3].hide();

		if (number == 0)
		{
			digitThree[visDigit3].hide();
			visDigit3 = 0;
		}
		else
		{
			digitThree[number].display();
			digitThree[number].show();
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
		digitOne[number].hide();
		visDigit1 = 0;
		break;
	case 1:
		digitTwo[number].hide();
		visDigit2 = 0;
		break;
	case 2:
		digitThree[number].hide();
		visDigit3 = 0;
		break;
	default:
		break;
	}

	if (useMinus)
		MinusSign.hide();
	else
	{
		Parentheses[0].hide();
		Parentheses[1].hide();
	}
}

void Numbers::changeImage(short int theme)
{
	for (short int i = 0; i < 10; i++)
	{
		digitOne[i].changeImage(100 + (theme*10) + i);
		digitTwo[i].changeImage(100 + (theme*10) + i);
		digitThree[i].changeImage(100 + (theme*10) + i);
	}
}

void Numbers::hideAll(void)
{
	for (short int j = 0; j < 10; j++)
	{
		digitOne[j].hide();
		digitTwo[j].hide();
		digitThree[j].hide();
	}

	if (useMinus)
		MinusSign.hide();
	else
	{
		Parentheses[0].hide();
		Parentheses[1].hide();
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
				digitOne[i].hide();
				digitTwo[i].hide();
				digitThree[i].hide();
			}
			digitOne[0].show();
		}
	}
	else
	{
		visDigit1 = abs(value) % 10;

		digitOne[visDigit1].show();
	}
	if (abs(value) > 9)
	{
		visDigit2 = abs(value) % 100 / 10;

		digitTwo[visDigit2].show();
	}
	if (abs(value) > 99)
	{
		visDigit3 = abs(value) / 100;

		digitThree[visDigit3].show();
	}

	if (!isPositive)
	{
		if (useMinus)
			MinusSign.show();
		else
		{
			Parentheses[0].show();
			Parentheses[1].show();
		}
	}
}

void Numbers::show(short int digit, short int number)
{
	switch (digit)
	{
	case 0:
		digitOne[number].show();
		visDigit1 = number;
		break;
	case 1:
		digitTwo[number].show();
		visDigit2 = number;
		break;
	case 2:
		digitThree[number].show();
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

		if (!digitOne[testDigit+direction].isVisible())
			digitOne[testDigit+direction].show();

		float posY;

		if (digit == 0)
		{
			digitOne[testDigit].setSize(50.0, digitOne[testDigit].getSizeY() + direction);

			if (digitOne[testDigit+direction].getSizeY() != 0.0)
				digitOne[testDigit+direction].setSize(50.0, 0.0);
			else if (digitOne[testDigit+direction].getSizeY() != 66.0)
				digitOne[testDigit+direction].setSize(50.0, digitOne[testDigit+direction].getSizeY() + direction);

			digitOne[testDigit].display(digitOne[testDigit].getX(), digitOne[testDigit].getY() + direction);
			digitOne[testDigit+direction].display(digitOne[testDigit+direction].getX(), digitOne[testDigit+direction].getY() + direction);

			posY = digitOne[testDigit].getY();

			if (posY > 67.0)
			{
				posY = 67.0;
				digitOne[testDigit].hide();
				visDigit1 = value;
			}

			if (posY < 53.0)
			{
				posY = 53.0;
				digitOne[testDigit].hide();
				visDigit1 = value;
			}
		}
		else if (digit == 1)
		{
			digitTwo[i].setAlpha(alpha);
			digitTwo[i].setSize(50.0, size);
			posY += digitTwo[i].getY();
			if (posY > 67.0)
				posY = 67.0;

			if (posY < 53.0)
				posY = 53.0;
			digitTwo[i].display(digitTwo[i].getX(), posY);
			//visDigit2 = value;
		}
		else if (digit == 2)
		{
			digitThree[i].setAlpha(alpha);
			digitThree[i].setSize(50.0, size);
			posY += digitThree[i].getY();
			if (posY > 67.0)
				posY = 67.0;

			if (posY < 53.0)
				posY = 53.0;
			digitThree[i].display(digitThree[i].getX(), posY);
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
        MinusSign.show();
    else
    {
        Parentheses[0].show();
        Parentheses[1].show();
    }
}

void Numbers::makePositive(void)
{
    isPositive = true;

    if (useMinus)
        MinusSign.hide();
    else
    {
        Parentheses[0].hide();
        Parentheses[1].hide();
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

	for (short int i = 0; i < 10; i++)
	{
		digitOne[i].changeColor(red, green, blue, alpha);
		digitTwo[i].changeColor(red, green, blue, alpha);
		digitThree[i].changeColor(red, green, blue, alpha);
	}
}

bool Numbers::isVisible(void)
{
	for (short int i = 0; i < 10; i++)
	{
		if(digitOne[i].isVisible())
			return true;
	}

	return false;
}

float Numbers::getX(short int digit)
{
	switch (digit)
	{
	case 1:
		return digitOne[visDigit1].getX();
		break;
	case 2:
		return digitTwo[visDigit2].getX();
		break;
	case 3:
		return digitThree[visDigit3].getX();
		break;
	}

	return -1.0f;
}

float Numbers::getY(short int digit)
{
	switch (digit)
	{
	case 1:
		return digitOne[visDigit1].getY();
		break;
	case 2:
		return digitTwo[visDigit2].getY();
		break;
	case 3:
		return digitThree[visDigit3].getY();
		break;
	}

	return -1.0f;
}
