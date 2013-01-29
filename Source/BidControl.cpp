#include "BidControl.h"
#include "agk.h"


BidControl::BidControl()
{

}

BidControl::~BidControl(void)
{
}

void BidControl::setup(AnimatedSprite *Symbol, const char image[], const char dir[])
{
    int frameImageNum;

    Parent.setImage(image);
    frameImageNum = Parent.getImageNumber("control_bid_bubble.png");

	Bid.setup(Symbol, "bid", Parent);
	Minus.setup(Symbol, "minus", Parent);
	Pass.setup(Symbol, "pass", Parent);
	Plus.setup(Symbol, "plus", Parent);

	Symbol->incrementSpriteFrame();
	agk::Sync();

    Frame.setImageNumber(frameImageNum);

	Symbol->incrementSpriteFrame();
	agk::Sync();

	BidValue.setData(dir);

	Symbol->incrementSpriteFrame();
	agk::Sync();
}

void BidControl::show(void)
{
	Frame.show();

	Bid.ButtonUp.show();
	Minus.ButtonUp.show();
	Pass.ButtonUp.show();
	Plus.ButtonUp.show();

	BidValue.showAll();
}

void BidControl::hide(void)
{
	Frame.hide();

	Bid.ButtonUp.hide();
	Minus.ButtonUp.hide();
	Pass.ButtonUp.hide();
	Plus.ButtonUp.hide();

	BidValue.hideAll();
}

void BidControl::setSize(float x, float y)
{
	Frame.setSize(x, y);
	Bid.setSize(x, y);
	Minus.setSize(x, y);
	Pass.setSize(x, y);
	Plus.setSize(x, y);
}

void BidControl::setPriority(short unsigned int value)
{
	Frame.setPriority(value);

	Bid.setPriority(value + 1);
	Minus.setPriority(value + 1);
	Pass.setPriority(value + 1);
	Plus.setPriority(value + 1);
}

void BidControl::display(float x, float y)
{
	Frame.display(x, y);

	Bid.display(x, y);
	Minus.display(x, y);
	Pass.display(x, y);
	Plus.display(x, y);
}

bool BidControl::isVisible(void)
{
	if (Frame.isVisible())
		return true;

	return false;
}

bool BidControl::animation(short int menuChoice, short int stage)
{
	switch (menuChoice)
	{
	case 1:
		return Bid.animation(stage);
		break;
	case 2:
		return Minus.animation(stage);
		break;
	case 3:
		return Pass.animation(stage);
		break;
	case 4:
		return Plus.animation(stage);
		break;
	default:
		return false;
		break;
	}
}
