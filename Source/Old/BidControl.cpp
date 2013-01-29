#include "BidControl.h"
#include "agk.h"


BidControl::BidControl()
{
	
}

BidControl::~BidControl(void)
{
}

void BidControl::init(Text ThemeDir, float bidValueSize)
{	
    int parentImage;
	Text ParentImageName = ThemeDir;
	Text ParentFileName;
	Text FrameFileName;
	Text BidFileName;
	Text MinusFileName;
	Text PassFileName;
	Text PlusFileName;

	ParentFileName.init("BCBubble.png");
	FrameFileName.init("control_bid_bubble.png");
	BidFileName.init("bid");
	MinusFileName.init("minus");
	PassFileName.init("pass");
	PlusFileName.init("plus");

	ParentImageName += ParentFileName;
    
    Parent->parentInit(ParentImageName);
	parentImage = Parent->getImageNumber();

    //frameImageNum = Parent.getImageNumber("control_bid_bubble.png");
    
	Frame->subInit(parentImage, FrameFileName);

	Bid->init(parentImage, BidFileName);
	Minus->init(parentImage, MinusFileName);
	Pass->init(parentImage, PassFileName);
	Plus->init(parentImage, PlusFileName);

	BidValue->init(ThemeDir);
	BidValue->setSize(bidValueSize);
}

void BidControl::show(void)
{
	Frame->setVisible(true);

	Bid->show();
	Minus->show();
	Pass->show();
	Plus->show();

	BidValue->showAll();
}

void BidControl::hide(void)
{
	Frame->setVisible(false);

	Bid->hide();
	Minus->hide();
	Pass->hide();
	Plus->hide();

	BidValue->hideAll();
}

void BidControl::setSize(float x, float y)
{
	Frame->setSize(x, y);
	Bid->setSize(x, y);
	Minus->setSize(x, y);
	Pass->setSize(x, y);
	Plus->setSize(x, y);
}

void BidControl::setDepth(unsigned short value)
{
	Frame->setDepth(value);

	Bid->setDepth(value - 1);
	Minus->setDepth(value - 1);
	Pass->setDepth(value - 1);
	Plus->setDepth(value - 1);
}

void BidControl::display(float x, float y)
{
	Frame->setPosition(x, y);

	Bid->display(x, y);
	Minus->display(x, y);
	Pass->display(x, y);
	Plus->display(x, y);
}

bool BidControl::isVisible(void)
{
	if (Frame->getVisible())
		return true;
	
	return false;
}

bool BidControl::animation(short int menuChoice, short int stage)
{
	switch (menuChoice)
	{
	case 1:
		return Bid->animation(stage);
		break;
	case 2:
		return Minus->animation(stage);
		break;
	case 3:
		return Pass->animation(stage);
		break;
	case 4:
		return Plus->animation(stage);
		break;
	default:
		return false;
		break;
	}
}