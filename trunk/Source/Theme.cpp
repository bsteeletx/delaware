#include "Theme.h"
#include "agk.h"

Theme::Theme()
{
    themeReady = false;
}


Theme::~Theme(void)
{
}

void Theme::setup(AnimatedSprite *Symbol, char dir[], short int state, float _aspect)
{
	char temp[64];
	float cardPosX[80];
	float cardPosY[80];
	bool faceDown[80];
	bool outlined[80];
	bool rotatedLeft[80];
	bool rotatedRight[80];

	if (!strcmp(dir, currentDir)) //if it's the same
        return;

	if (strlen(dir) <= 64)
		strcpy(currentDir, dir);

	if (state != MENU)
	{
		for (int i = 0; i < 80; i++)
		{
			cardPosX[i] = Deck[i].getX();
			cardPosY[i] = Deck[i].getY();
			faceDown[i] = Deck[i].getFaceDirection();
			outlined[i] = Deck[i].getOutline();
			rotatedLeft[i] = Deck[i].isRotatedLeft();
			rotatedRight[i] = Deck[i].isRotatedRight();
		}


	}

	///step 1: setup or setData////////////

    Background.setData("background.jpg", currentDir);
    InGameMenuButton.setData("menu", currentDir);

	strcpy(temp, currentDir);
	strcat(temp, "BCBubble.png");
    BCBubble.setup(Symbol, temp, currentDir);

	strcpy(temp, currentDir);
	strcat(temp, "BidBubble.png");
	BidMeldBubbles.setup(Symbol, temp, currentDir);

	strcpy(temp, currentDir);
	strcat(temp, "TSBubble.png");
	TSBubble.setup(Symbol, temp);

	strcpy(temp, currentDir);
	strcat(temp, "Cards.png");

	for (short int i = 0; i < 80; i++)
	{
        short j;

        if (i % 4 == 0)
        {
            Deck[i].setData(temp, i%20/4, i/20);
            j = i;
        }
        else
        {
            Deck[i].setFrontImage(Deck[j].getFrontImage());
            Deck[i].setBackImage(Deck[j].getBackImage());
            Deck[i].setOutlineImage(Deck[j].getOutlineImage());
        }

		if (state != LOADING)
		{
			if (outlined[i])
				Deck[i].outlineCard();

			if (faceDown[i])
				Deck[i].turnFaceDown();

			if (rotatedLeft[i])
				Deck[i].rotateLeft();
			else if (rotatedRight[i])
				Deck[i].rotateRight();

			Deck[i].display(cardPosX[i], cardPosY[i]);
			Deck[i].hide();
		}

        Symbol->incrementSpriteFrame();
        agk::Sync();
	}
	setNumberData();
	setNumberPrio();
	hide();

	Symbol->incrementSpriteFrame();
	agk::Sync();

	///step 2: setSize
	setSizeNumbers();
	TSBubble.setSize(40.0f);

	BidMeldBubbles.setBidSize(39.0f, -1.0f);

	BCBubble.setSize(45.0f);


	Background.setSize(100.0, -1.0f, true);
	for (short int i = 0; i < 80; i++)
		Deck[i].setSize(CARDSIZE);

	BidMeldBubbles.NorthMeld.setSize(57.0f);
	BidMeldBubbles.SouthMeld.setSize(57.0f);
	BidMeldBubbles.EastMeld.setSize(57.0f);
	BidMeldBubbles.WestMeld.setSize(57.0f);

	InGameMenuButton.setSize(100.0f);

	Symbol->incrementSpriteFrame();
	agk::Sync();

	///step 3: set priority
	Background.setPriority(2);
	InGameMenuButton.setPriority(5);
	BidMeldBubbles.setPriority(3);
	BCBubble.setPriority(4);
	TSBubble.setPriority(3);

	Symbol->incrementSpriteFrame();
	agk::Sync();

	///step 4: set x, y location with display
	setNumberLoc();
	if (state == 0)
		initNumbers();
	InGameMenuButton.display(0.f, 0.0f);

	Symbol->incrementSpriteFrame();
	agk::Sync();

	///step 5: hide
	hide();
	Bid.hideAll();
	BidScore.hideAll();
	VScore.hideAll();
	HScore.hideAll();
	VMeld.hideAll();
	HMeld.hideAll();
	BCBubble.BidValue.hideAll();
	V2Get.hideAll();
	H2Get.hideAll();
	PastNorthBid.hideAll();
	PastEastBid.hideAll();
	PastSouthBid.hideAll();
	PastWestBid.hideAll();

	Symbol->incrementSpriteFrame();
	agk::Sync();

	themeReady = true;
	///step 6 (optional): set imprint
}

void Theme::initNumbers(void)
{
		//initialize numbers to a value, then hide--don't display!
	HScore.setDigit(0, 0);
	HScore.setDigit(1, 0);
	HScore.setDigit(2, 0);
	VScore.setDigit(0, 0);
	VScore.setDigit(1, 0);
	VScore.setDigit(2, 0);

	HScore.hideAll();
	VScore.hideAll();

	BidScore.setValue(50);
	BidScore.hideAll();
	//BidScore.display(0, 0);
	//BidScore.display(1, 5);

	H2Get.setValue(0);
	//H2Get.display(0, 0);
	V2Get.setValue(0);
	//V2Get.display(0, 0);
	H2Get.hideAll();
	V2Get.hideAll();

	PastNorthBid.setValue(50);
	PastSouthBid.setValue(50);
	PastEastBid.setValue(50);
	PastWestBid.setValue(50);
	PastNorthBid.hideAll();
	PastSouthBid.hideAll();
	PastEastBid.hideAll();
	PastWestBid.hideAll();
}

void Theme::setNumberPrio(void)
{
		//Step 3: Set Priority
	Bid.setPriority(3);
	BidScore.setPriority(3);
	VScore.setPriority(3);
	HScore.setPriority(3);
	VMeld.setPriority(3);
	HMeld.setPriority(3);
	BCBubble.Bid.setPriority(7);
	V2Get.setPriority(3);
	H2Get.setPriority(3);
	PastNorthBid.setPriority(35); //need to be high to get over cards
	PastSouthBid.setPriority(35);
	PastEastBid.setPriority(35);
	PastWestBid.setPriority(35);
}

void Theme::setNumberLoc(void)
{
    float offset = 0.0f;

    if (PLATFORM == MOBILE)
        offset = 0.25f;

	for (short int i = 0; i < 3; i++)
	{
		if (strcmp(currentDir, "green/") == 0) //if currentDir is green
		{
			BidScore.setLocation(i, 83.5f - (3.0f * i), 70.0f, 0);
			VScore.setLocation(i, 8.25f - (2.0f * i), 10.0f, -5.75f, -0.6f);
			HScore.setLocation(i, 18.75f - (2.0f * i), 10.0f, -5.75f, -0.6f); //
			VMeld.setLocation(i, 4.9f - (1.5f * i), 71.25f, 0); //
			HMeld.setLocation(i, 9.9f - (1.5f * i), 71.25, 0); //0, 0.5
			V2Get.setLocation(i, 15.25f - (1.5f * i), 71.25f, 0);
			H2Get.setLocation(i, 20.25f - (1.5f * i), 71.25f, 0);
		}
		else if (strcmp(currentDir, "red/") == 0) //if currentDir is red
		{
            BidScore.setLocation(i, 84.5f - ((2.5f + offset) * i), 70.0f, 0); //added 1 space
			VScore.setLocation(i, 8.25f - (2.0f * i), 10.0f, -5.75f, -0.6f);
			HScore.setLocation(i, 18.75f - (2.0f * i), 10.0f, -5.75f, -0.6f); //
			VMeld.setLocation(i, 4.75f - (1.5f * i), 71.25f, 0); //
			HMeld.setLocation(i, 9.9f - (1.5f * i), 71.25, 0); //0, 0.5
			V2Get.setLocation(i, 15.0f - (1.5f * i), 71.25f, 0);
			H2Get.setLocation(i, 20.25f - (1.5f * i), 71.25f, 0);
		}
        else if (strcmp(currentDir, "ancient/") == 0) //if currentDir is ancient
		{
            BidScore.setLocation(i, 84.5f - ((2.5f + offset) * i), 70.0f - (offset * 2), 0); //added 1 space
			VScore.setLocation(i, 8.25f - (2.0f * i), 10.0f, -5.75f, -0.6f);
			HScore.setLocation(i, 18.75f - (2.0f * i), 10.0f, -5.75f, -0.6f); //
			VMeld.setLocation(i, 4.9f - (1.5f * i), 71.25f, 0); //
			HMeld.setLocation(i, 9.9f - (1.5f * i), 71.25, 0); //0, 0.5
			V2Get.setLocation(i, 15.25f - (1.5f * i), 71.25f, 0);
			H2Get.setLocation(i, 20.25f - (1.5f * i), 71.25f, 0);
		}
		else if (strcmp(currentDir, "xmas/") == 0) //if currentDir is ancient
		{
			BidScore.setLocation(i, 83.5f - (3.0f * i), 73.0f, 0);
			VScore.setLocation(i, 9.25f - (2.0f * i), 13.0f, -5.75f, -0.6f);
			HScore.setLocation(i, 20.75f - (2.0f * i), 13.0f, -5.75f, -0.6f); //
			VMeld.setLocation(i, 4.9f - (1.5f * i), 73.75f, 0); //
			HMeld.setLocation(i, 9.9f - (1.5f * i), 73.75, 0); //0, 0.5
			V2Get.setLocation(i, 16.25f - (1.5f * i), 73.75f, 0);
			H2Get.setLocation(i, 22.25f - (1.5f * i), 73.75f, 0);
		}
		else //current Dir is electric
		{
			BidScore.setLocation(i, 84.5f - ((2.5f + offset) * i), 70.5f - (offset * 2), 0);
			VScore.setLocation(i, 8.5f - (2.0f * i), 10.0f, -5.75f, -0.6f);
			HScore.setLocation(i, 18.75f - (2.0f * i), 10.0f, -5.75f, -0.6f); //
			VMeld.setLocation(i, 4.9f - (1.5f * i), 71.25f, 0); //
			HMeld.setLocation(i, 9.9f - (1.5f * i), 71.25, 0); //0, 0.5
			V2Get.setLocation(i, 15.25f - (1.5f * i), 71.25f, 0);
			H2Get.setLocation(i, 20.25f - (1.5f * i), 71.25f, 0);
		}


		PastNorthBid.setLocation(i, 52.0f - (2.75f * i), 10.75f, 0);
		PastSouthBid.setLocation(i, 52.0f - (2.75f * i), 87.0f, 0);
		PastWestBid.setLocation(i, 13.5f - (2.75f * i), 39.25f, 0);
		PastEastBid.setLocation(i, 90.5f - (2.75f * i), 39.25f, 0);
	}
}

void Theme::setSizeNumbers(void)
{
	//Step 4: Scale
	if (strcmp(currentDir, "future/"))
		BCBubble.BidValue.setSize(6.25f);
	else
		BCBubble.BidValue.setSize(5.25f);
	//Bid.setSize(6.5f);
	if (strcmp(currentDir, "green/"))
		BidScore.setSize(2.5f);
	else
		BidScore.setSize(3.0f);
	VScore.setSize(1.75f);
	HScore.setSize(1.75f);
	VMeld.setSize(1.5f);
	HMeld.setSize(1.5f);
	V2Get.setSize(1.5f);
	H2Get.setSize(1.5f);
	PastNorthBid.setSize(2.5f);
	PastSouthBid.setSize(2.5f);
	PastEastBid.setSize(2.5f);
	PastWestBid.setSize(2.5f);
	BidMeldBubbles.Bid.setSize(6.5f);
}

void Theme::setNumberData(void)
{
    Bid.setData(currentDir);
    BidScore.setData(currentDir);
    VScore.setData(currentDir, true);
    HScore.setData(currentDir, true);
    VMeld.setData(currentDir, true);
    HMeld.setData(currentDir, true);
    PastNorthBid.setData(currentDir);
    PastEastBid.setData(currentDir);
    PastSouthBid.setData(currentDir);
    PastWestBid.setData(currentDir);
    V2Get.setData(currentDir);
    H2Get.setData(currentDir);
}

void Theme::show(short int state)
{
	InGameMenuButton.ButtonUp.show();

	for (short int i = 0; i < 80; i++)
	{
		if ((Deck[i].getX() > 0.0f) && (Deck[i].getX() < 100.0f))
		{
			if ((Deck[i].getY() > 0.0f) && (Deck[i].getY() < 100.0f))
				Deck[i].show();
		}
	}

	//setNumberLoc();
	//setSizeNumbers();

	BidScore.showAll();
	//Bid.hideAll();
	//Bid.showAll();
	H2Get.showAll();
	HMeld.showAll();
	HScore.showAll();

	if (state != PLAYING)
	{
		PastEastBid.showAll();
		PastNorthBid.showAll();
		PastSouthBid.showAll();
		PastWestBid.showAll();
	}

	V2Get.showAll();
	VMeld.showAll();
	VScore.showAll();

	Background.show();
	InGameMenuButton.show();
}

void Theme::hide(void)
{
	InGameMenuButton.ButtonUp.hide();

	Background.hide();
	for (short int i = 0; i < 80; i++)
		Deck[i].hide();

	BCBubble.hide();
	TSBubble.hide();

	BidScore.hideAll();
	Bid.hideAll();
	H2Get.hideAll();
	HMeld.hideAll();
	HScore.hideAll();
	PastEastBid.hideAll();
	PastNorthBid.hideAll();
	PastSouthBid.hideAll();
	PastWestBid.hideAll();
	V2Get.hideAll();
	VMeld.hideAll();
	VScore.hideAll();
}

bool Theme::isSetup()
{
    return themeReady;
}
