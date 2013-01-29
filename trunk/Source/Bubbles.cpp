#include "Bubbles.h"
#include "agk.h"

#define X 0
#define Y 1

Bubbles::Bubbles(void)
{


}


Bubbles::~Bubbles(void)
{
}

void Bubbles::setup(AnimatedSprite *Symbol, const char fullname[], const char dir[])
{
	float offset = 5.0f;
    unsigned int imgNum;

    Parent.setImage(fullname);

    imgNum = Parent.getImageNumber("east_bid.png");
	EastBid.setImageNumber(imgNum);

    imgNum = Parent.getImageNumber("north_bid.png");
	NorthBid.setImageNumber(imgNum);

    imgNum = Parent.getImageNumber("south_bid.png");
	SouthBid.setImageNumber(imgNum);

    imgNum = Parent.getImageNumber("west_bid.png");
	WestBid.setImageNumber(imgNum);

    imgNum = Parent.getImageNumber("east_meld.png");
	EastMeld.setImageNumber(imgNum);

    imgNum = Parent.getImageNumber("north_meld.png");
	NorthMeld.setImageNumber(imgNum);

    imgNum = Parent.getImageNumber("south_meld.png");
	SouthMeld.setImageNumber(imgNum);

    imgNum = Parent.getImageNumber("west_meld.png");
	WestMeld.setImageNumber(imgNum);

	Bid.setData(dir);

	for (short int i = 0; i < 4; i++)
    {
        imgNum = Parent.getImageNumber("pass_bid.png");
		BidPass[i].setImageNumber(imgNum);
    }

	///display--Needs to be offset!!
	if(! (strcmp (dir, "green/") || strcmp(dir, "red/") || strcmp(dir, "xmas/")))
		offset = 5.0f;

	WestBid.display(14.5f + offset, 12.0f);
	NorthBid.display(30.0f, 13.0f); //green felt doesn't need offset, do others?
	EastBid.display(46.0f - offset, 12.0f);

    if (PLATFORM != MOBILE)
        SouthBid.display(30.0f, 35.0f); //green felt doesn't need offset, do others?
    else
        SouthBid.display(30.0f, 35.0f - offset); //green felt doesn't need offset, do others?

	Symbol->incrementSpriteFrame();
	agk::Sync();

	hide();

#if (PLATFORM != MOBILE)
	firstCardPos[GREEN][WEST][X] = 32.5f;
	firstCardPos[GREEN][WEST][Y] = 36.75f;
	firstCardPos[GREEN][NORTH][X] = 30.0f;
	firstCardPos[GREEN][NORTH][Y] = 40.5f;
	firstCardPos[GREEN][EAST][X] = 29.5f;
	firstCardPos[GREEN][EAST][Y] = 37.0f;
	firstCardPos[GREEN][SOUTH][X] = 32.4f;
	firstCardPos[GREEN][SOUTH][Y] = 39.5f;

	firstCardPos[RED][WEST][X] = 36.5f;
	firstCardPos[RED][WEST][Y] = 32.5f;
	firstCardPos[RED][NORTH][X] = 28.0f;
	firstCardPos[RED][NORTH][Y] = 40.5f;
	firstCardPos[RED][EAST][X] = 28.25f;
	firstCardPos[RED][EAST][Y] = 40.5f;
	firstCardPos[RED][SOUTH][X] = 28.25f;
	firstCardPos[RED][SOUTH][Y] = 40.25f;

	firstCardPos[ANCIENT][WEST][X] = 27.5f;
	firstCardPos[ANCIENT][WEST][Y] = 33.75f;
	firstCardPos[ANCIENT][NORTH][X] = 24.75f;
	firstCardPos[ANCIENT][NORTH][Y] = 37.5f; //
	firstCardPos[ANCIENT][EAST][X] = 25.0f;
	firstCardPos[ANCIENT][EAST][Y] = 32.0f;
	firstCardPos[ANCIENT][SOUTH][X] = 28.25f;
	firstCardPos[ANCIENT][SOUTH][Y] = 38.0f; //

	firstCardPos[WINTER][WEST][X] = 31.5f; //bubble needs moving west
	firstCardPos[WINTER][WEST][Y] = 36.75f;
	firstCardPos[WINTER][NORTH][X] = 31.0f;
	firstCardPos[WINTER][NORTH][Y] = 36.5f;
	firstCardPos[WINTER][EAST][X] = 34.0;
	firstCardPos[WINTER][EAST][Y] = 37.0f;
	firstCardPos[WINTER][SOUTH][X] = 35.4f;
	firstCardPos[WINTER][SOUTH][Y] = 44.5f;

	firstCardPos[ELECTRIC][WEST][X] = 27.5f; //bubble needs moving west
	firstCardPos[ELECTRIC][WEST][Y] = 33.5f;
	firstCardPos[ELECTRIC][NORTH][X] = 28.0f;
	firstCardPos[ELECTRIC][NORTH][Y] = 41.0f;
	firstCardPos[ELECTRIC][EAST][X] = 32.0f;
	firstCardPos[ELECTRIC][EAST][Y] = 40.5f;
	firstCardPos[ELECTRIC][SOUTH][X] = 26.0f;
	firstCardPos[ELECTRIC][SOUTH][Y] = 40.0f;
#else
    firstCardPos[GREEN][WEST][X] = 32.5f;
	firstCardPos[GREEN][WEST][Y] = 40.5f; //
	firstCardPos[GREEN][NORTH][X] = 30.0f;
	firstCardPos[GREEN][NORTH][Y] = 45.0f; //
	firstCardPos[GREEN][EAST][X] = 29.5f;
	firstCardPos[GREEN][EAST][Y] = 40.5f; //
	firstCardPos[GREEN][SOUTH][X] = 32.4f;
	firstCardPos[GREEN][SOUTH][Y] = 38.5f;

	firstCardPos[RED][WEST][X] = 35.5f; //
	firstCardPos[RED][WEST][Y] = 36.75f; //
	firstCardPos[RED][NORTH][X] = 27.0f; //
	firstCardPos[RED][NORTH][Y] = 45.0f; //
	firstCardPos[RED][EAST][X] = 28.25f;
	firstCardPos[RED][EAST][Y] = 45.75f; //
	firstCardPos[RED][SOUTH][X] = 28.25f;
	firstCardPos[RED][SOUTH][Y] = 39.0f; //

	firstCardPos[ANCIENT][WEST][X] = 27.5f;
	firstCardPos[ANCIENT][WEST][Y] = 36.25f; //
	firstCardPos[ANCIENT][NORTH][X] = 24.75f;
	firstCardPos[ANCIENT][NORTH][Y] = 41.5f; //
	firstCardPos[ANCIENT][EAST][X] = 25.0f;
	firstCardPos[ANCIENT][EAST][Y] = 36.6f; //
	firstCardPos[ANCIENT][SOUTH][X] = 28.25f;
	firstCardPos[ANCIENT][SOUTH][Y] = 37.0f; //

	firstCardPos[WINTER][WEST][X] = 32.5f;
	firstCardPos[WINTER][WEST][Y] = 40.5f; //
	firstCardPos[WINTER][NORTH][X] = 30.0f;
	firstCardPos[WINTER][NORTH][Y] = 45.0f; //
	firstCardPos[WINTER][EAST][X] = 29.5f;
	firstCardPos[WINTER][EAST][Y] = 40.5f; //
	firstCardPos[WINTER][SOUTH][X] = 32.4f;
	firstCardPos[WINTER][SOUTH][Y] = 38.5f;

	firstCardPos[ELECTRIC][WEST][X] = 27.5f; //bubble needs moving west
	firstCardPos[ELECTRIC][WEST][Y] = 41.0f;
	firstCardPos[ELECTRIC][NORTH][X] = 28.0f;
	firstCardPos[ELECTRIC][NORTH][Y] = 40.0f;
	firstCardPos[ELECTRIC][EAST][X] = 39.0f;
	firstCardPos[ELECTRIC][EAST][Y] = 47.5f;
	firstCardPos[ELECTRIC][SOUTH][X] = 32.0f;
	firstCardPos[ELECTRIC][SOUTH][Y] = 47.5f;
#endif

	firstCardPos[FUTURE][WEST][X] = 27.5f; //bid bubble needs moving south and west
	firstCardPos[FUTURE][WEST][Y] = 41.0f;
	firstCardPos[FUTURE][NORTH][X] = 28.0f;
	firstCardPos[FUTURE][NORTH][Y] = 40.0f;
	firstCardPos[FUTURE][EAST][X] = 36.0f;
	firstCardPos[FUTURE][EAST][Y] = 47.5f;
	firstCardPos[FUTURE][SOUTH][X] = 32.0f;
	firstCardPos[FUTURE][SOUTH][Y] = 47.5f;


}

float Bubbles::getFirstCardPos(int theme, int player, bool getX)
{
	if (getX)
		return firstCardPos[theme][player][X];
	else
		return firstCardPos[theme][player][Y];
}

void Bubbles::setBidSize(float x, float y)
{
	EastBid.setSize(x, y);
	NorthBid.setSize(x, y);
	SouthBid.setSize(x, y);
	WestBid.setSize(x, y);

	for (short int i = 0; i < 4; i++)
		BidPass[i].setSize(x/2.0f, y/2.0f);
}

void Bubbles::hide(void)
{
	EastBid.hide();
	EastMeld.hide();
	NorthBid.hide();
	NorthMeld.hide();
	SouthBid.hide();
	SouthMeld.hide();
	WestBid.hide();
	WestMeld.hide();

	Bid.hideAll();

	for (short int i = 0; i < 4; i++)
		BidPass[i].hide();
}

void Bubbles::setPriority(short unsigned int value)
{
	EastBid.setPriority(value);
	EastMeld.setPriority(value);
	NorthBid.setPriority(value);
	NorthMeld.setPriority(value);
	SouthBid.setPriority(value);
	SouthMeld.setPriority(value);
	WestBid.setPriority(value);
	WestMeld.setPriority(value);

	Bid.setPriority(value + 1);

	for (short int i = 0; i < 4; i++)
		BidPass[i].setPriority(value + 1);
}

void Bubbles::show(short int meldBubble)
{
	switch (meldBubble)
	{
	case 0:
		WestMeld.show();
		break;
	case 1:
		NorthMeld.show();
		break;
	case 2:
		EastMeld.show();
		break;
	case 3:
		SouthMeld.show();
		break;
	}
}

bool Bubbles::updateBid(short int turn, short int dealer, BidGame NewBidGame, short int theme)  //returns true if bid, false if not
{
	float x = 0.0f;
	float y = 0.0f;
	//bool passed = false;
	short int round = (turn - dealer - 1) / 4;
	unsigned short int bid = NewBidGame.getBid();
	float offset = 0.0f;

	if (theme != 4)
		offset = 5.0f;

	if (NewBidGame.getBidder() == -1)
	{
		if (turn % 4 == WEST)
			WestBid.show();
		else if (turn %4 == NORTH)
			NorthBid.show();
		else if (turn % 4 == EAST)
			EastBid.show();
		else
			SouthBid.show();

		agk::Sync();

		return true;
	}

	switch (turn % 4)
	{
	case WEST:
		if ((!NewBidGame.getPass(WEST)) && (!NewBidGame.getBidDecided()))
			WestBid.show();

		if (NewBidGame.getPass(WEST))
		{
			if (NewBidGame.wPassRound == round)
			{
				bid = 0;
				WestBid.show();
			}
			else
			{
				WestBid.hide();
				//passed = true;
				return false;
			}
		}

		if (bid)
		{//bid
#if (PLATFORM != MOBILE)
			x = 38.0f + offset;
			y = 32.0f;
#else
            x = 38.0f + offset;
            y = 35.0f;
#endif
			if (theme == ELECTRIC)
				x += 5.0f;
			else if (theme == WINTER)
			{
				x -= 1.0f;
				y += 1.0f;
			}
		}
		else
		{//pass
			x = 26.0f + offset;
			y = 25.0f;

			if (theme == ELECTRIC)
				x += 5.0f;
			else if (theme == WINTER)
				x -= 1.0f;
		}
		break;
	case NORTH:
		if (!NewBidGame.getPass(NORTH) && (!NewBidGame.getBidDecided()))
			NorthBid.show();

		if (NewBidGame.getPass(NORTH))
		{
			if (NewBidGame.nPassRound == round)
			{
				bid = 0;
				NorthBid.show();
			}
			else
			{
				NorthBid.hide();
				//passed = true;
				return false;
			}
		}
		if (bid)
		{//did not pass
#if (PLATFORM != MOBILE)
			x = 52.5f;
			y = 31.5f + offset;
#else
            x = 52.5f;
            y = 34.5f + offset;
#endif
			if (theme == WINTER)
				y -= 2.5f;
		}
		else
		{
#if (PLATFORM != MOBILE)
			x = 35.25f + offset;
			y = 29.0f;
#else
            x = 35.25f + offset;
            y = 30.0f;
#endif
			if (theme == WINTER)
			{
				x += 0.0f;
				y -= 3.0f;
			}
		}
		break;
	case EAST:
		if (!NewBidGame.getPass(EAST) && (!NewBidGame.getBidDecided()))
			EastBid.show();

		if (NewBidGame.getPass(EAST))
		{
			if (NewBidGame.ePassRound == round)
			{
				bid = 0;
				EastBid.show();
			}
			else
			{
				EastBid.hide();
				//passed = true;
				return false;
			}
		}

		if (bid)
		{
#if (PLATFORM != MOBILE)
			x = 66.5f - offset;
			y = 32.0f;
#else
            x = 67.0f - offset;
            y = 35.0f;
#endif
			if (theme == WINTER)
			{
				y += 0.75f;
				x += 2.0f;
			}
		}
		else
		{
			x = 54.0f - offset;
			y = 25.0f;

			if (theme == WINTER)
				x += 2.5f;
		}

		break;
	case SOUTH:
		if (!NewBidGame.getPass(SOUTH) && (!NewBidGame.getBidDecided()))
		{
			SouthBid.show();
		}

		if (NewBidGame.getPass(SOUTH))
		{
			if (NewBidGame.sPassRound == round)
			{
				bid = 0;
				SouthBid.show();
			}
			else
			{
				SouthBid.hide();
				//passed = true;
				return false;
			}
		}

		if (bid)
		{
#if (PLATFORM != MOBILE)
			x = 52.5f;
			y = 58.0f - offset;
#else
            x = 52.5f;
            y = 55.0f - offset;
#endif
      		if (theme == ELECTRIC)
				x += 1.0f;
			else if (theme == WINTER)
				y += 3.0f;
		}
		else
		{
#if (PLATFORM != MOBILE)
			x = 40.0f;
			y = 51.0f - offset;
#else
            x = 40.0f;
            y = 45.0f - offset;
#endif
			if (theme == WINTER)
			{
				x += 1.0f;
				y += 2.5f;
			}
		}
		break;
	}

	if (bid)
	{//CurrentTheme.Bid.setSize(0.30f);

		if (bid >= 100)
			Bid.display(2, 1, x-12.0f, y);

        if (theme != 1)// && (theme != 3))
        {
            Bid.display(1, bid%100/10, x-6.0f, y);
            Bid.display(0, bid%10, x, y);
        }
        else// if (theme == 1)
        {
            Bid.display(1, bid%100/10, x-6.5f, y);
            Bid.display(0, bid%10, x, y);
        }

		return true;
	}
	else
	{
		BidPass[turn%4].display(x, y);
		BidPass[turn%4].show();

		return true;
	}
}
