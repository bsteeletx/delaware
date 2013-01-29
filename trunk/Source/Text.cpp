#include "template.h"

Text::Text(void)
{
	textid=0;
	strcpy(textname, "");
	textColor[0] = -1;
	textColor[1] = -1;
	textColor[2] = -1;
	colorDelay = 0;
}

Text::~Text(void)
{
}

void Text::setId(unsigned short int id)
{
	textid=id;
	agk::DeleteText(textid);
}

void Text::deleteT()
{
	agk::DeleteText(textid);
}

void Text::createT(const char newtextname[])
{
	if (strlen(newtextname) < 256)
		strcpy (textname, newtextname);
	else
		return;

	if (textid == 0)
		textid = agk::CreateText(textname);
	else
		agk::CreateText(textid,textname);
}

void Text::size(float tsize)
{
	//tsize /= FACTOR;

	agk::SetTextSize(textid,tsize);
}

void Text::font(unsigned short int fontImage)
{
	agk::SetTextFontImage(textid,fontImage);
}

void Text::position(float xpos,float ypos)
{
	//xpos /= FACTOR;
	//ypos /= FACTOR;

	agk::SetTextPosition(textid,xpos,ypos);
}

void Text::color(unsigned short int rcolor,unsigned short int gcolor, unsigned short int bcolor)
{
	textColor[0] = rcolor;
	textColor[1] = gcolor;
	textColor[2] = bcolor;
	agk::SetTextColor(textid,rcolor,gcolor,bcolor);
}

void Text::show()
{
	agk::SetTextVisible(textid,1);
}
void Text::hide()
{
	agk::SetTextVisible(textid,0);
}

void Text::changeText(const char text[])
{
	agk::SetTextString(textid,text);
}

void Text::changeText(int x)
{
	char temp[4];

	sprintf(temp,"%d",x);
	agk::SetTextString(textid,temp);
}

void Text::setDepth(unsigned short int depth)
{
	agk::SetTextDepth(textid,10000-depth);
}

unsigned short int Text::getID(void)
{
	return textid;
}

void Text::centerText(void)
{
	agk::SetTextAlignment(textid, 1);
}

void Text::leftText(void)
{
	agk::SetTextAlignment(textid, 0);
}

void Text::rightText(void)
{
	agk::SetTextAlignment(textid, 2);
}

float Text::getX(void)
{
	return agk::GetTextX(textid);
}

float Text::getY(void)
{
	return agk::GetTextY(textid);
}

bool Text::isVisible(void)
{
	if (agk::GetTextVisible(textid))
		return true;
	else
		return false;
}

void Text::incrementColor(void)
{
	colorDelay++;

	if (colorDelay % 15 == 0)
	{
#if (OS != IOS)
		textColor[0] = (textColor[0] + agk::Random(0, 255)) % 255;
		textColor[1] = (textColor[1] + agk::Random(0, 255)) % 255;
		textColor[2] = (textColor[2] + agk::Random(0, 255)) % 255;
#else
        textColor[0] = (textColor[0] + (arc4random() % 256) % 256);
        textColor[1] = (textColor[1] + (arc4random() % 256) % 256);
        textColor[2] = (textColor[2] + (arc4random() % 256) % 256);
#endif
		color(textColor[0], textColor[1], textColor[2]);

		colorDelay = 0;
	}
}
