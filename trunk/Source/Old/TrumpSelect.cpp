#include "TrumpSelect.h"
#include "agk.h"

TrumpSelect::TrumpSelect(void)
{

}

TrumpSelect::~TrumpSelect(void)
{
}

void TrumpSelect::init(Text FileName)
{
    int imgNum;
	Text *Temp = FileName;

	*Temp += Text("TSBubble.png");

    ParentImage->init(0, Temp);
	imgNum = ParentImage->getImageNumber();
    
	Hearts->init(imgNum, "hearts_selection");
	Clubs->init(imgNum, "clubs_selection");
	Diamonds->init(imgNum, "diamonds_selection");
	Spades->init(imgNum, "spades_selection");
    
    Frame->init(imgNum, new Text("trump_selection_bubble.png"));
    
	display(28.0f, 30.0f);
	hide();
}

void TrumpSelect::show(void)
{
	Hearts->show();
	Clubs->show();
	Diamonds->show();
	Spades->show();
	Frame->setVisible(true);
}

void TrumpSelect::hide(void)
{
	Hearts.hide();
	Clubs.hide();
	Diamonds.hide();
	Spades.hide();
	Frame.hide();
}

void TrumpSelect::setSize(float x, float y)
{
	Frame.setSize(x, y);

	Hearts.setSize(x, y);
	Clubs.setSize(x, y);
	Diamonds.setSize(x, y);
	Spades.setSize(x, y);
}

void TrumpSelect::setPriority(unsigned short int value)
{
	Hearts.setPriority(value + 1);
	Clubs.setPriority(value + 1);
	Diamonds.setPriority(value + 1);
	Spades.setPriority(value + 1);

	Frame.setPriority(value);
}

void TrumpSelect::display(float x, float y)
{
	Hearts.display(x, y);
	Clubs.display(x, y);
	Diamonds.display(x, y);
	Spades.display(x, y);

	Frame.display(x, y);
}

bool TrumpSelect::animation(short int button, short int stage)
{
	switch (button)
	{
	case 1:
		return Hearts.animation(stage);
		break;
	case 2:
		return Clubs.animation(stage);
		break;
	case 3:
		return Diamonds.animation(stage);
		break;
	case 4:
		return Spades.animation(stage);
		break;
	default:
		return false;
		break;
	}
}
