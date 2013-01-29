#pragma once
#include <sstream>
#include <string>
class Text
{
public:
	Text();
	~Text();

	void setId(unsigned short int id);
	void deleteT();
	void createT(const char name[]);
	void size(float);
	void font(unsigned short int fontImage=999);
	void position(float,float);
	void color(unsigned short int rcolor,unsigned short int gcolor, unsigned short int bcolor);
	void show();
	void hide();
	void incrementColor(void);
	void changeText(const char name[]);
	void changeText(int);
	void setDepth(unsigned short int depth);
	unsigned short int getID(void);
	void centerText(void);
	void leftText(void);
	void rightText(void);
	float getX(void);
	float getY(void);
	bool isVisible(void);

	char textname[256];

protected:
	unsigned short int textid;
	short textColor[3];
	short colorDelay;

};
