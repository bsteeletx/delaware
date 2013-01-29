#include "Image.h"
#include "agk.h"
#include "Text.h"

std::vector<Text> Image::ParentFileNames;
std::vector<unsigned int> Image::parentImageNumbers;
std::vector<Text> Image::NonParentFileNames;
std::vector<unsigned int> Image::nonParentImageNumbers;

Image::~Image(void)
{
	//if (getExists())
		//agk::DeleteImage(imageNumber);
}

Image::Image()
{
	imageNumber = 0;
}

Image& Image::operator= (const Image& newImage)
{
	imageNumber = newImage.imageNumber;

	return *this;
}

void Image::init(File FileToInit)
{
	unsigned int parentImage = 0;
	Text Filename;
	bool alreadyLoaded = false;
	bool blackIsAlpha = false;
	unsigned int assignedNumber = 0;
	unsigned short iterator = 0;

	//Need to copy this from Pennsylvania, not sure what goes on here
	//check for a Parent File Name
	//check for the actual file name
	//check to see if black is alpha
	//check for an assigned number

	//no parent image, bad doggy! no treat for you!
	if (parentImage == 0)
		loadImage(Filename, blackIsAlpha, assignedNumber);
	else
		loadSubImage(parentImage, Filename, assignedNumber);

	FileToInit.close();
}

void Image::init(unsigned int parentImage, Text Filename, bool blackIsAlpha, unsigned int assignedImageNumber)
{
	if (parentImage)
		loadSubImage(parentImage, Filename, assignedImageNumber);
	else
		loadImage(Filename, blackIsAlpha, assignedImageNumber);
}

Text Image::decodeQRCode(void)
{
	Text RetText;

	RetText.init(agk::DecodeQRCode(imageNumber));

	return RetText;
}

bool Image::getExists(void)
{
	if (agk::GetImageExists(imageNumber))
		return true;
	else
		return false;
}

Text Image::getFilename(void)
{
	Text RetText;

	RetText.init(agk::GetImageFilename(imageNumber));

	return RetText;
}

float Image::getHeight(void)
{
	return agk::GetImageHeight(imageNumber);
}

unsigned int Image::getImageNumber(void)
{
	return imageNumber;
}

float Image::getWidth(void)
{
	return agk::GetImageWidth(imageNumber);
}

void Image::printImage(float percentSize)
{
	agk::PrintImage(imageNumber, percentSize);
}

void Image::saveImage(Text savedFilename)
{
	if (_Filename(savedFilename))
		agk::SaveImage(imageNumber, savedFilename.getString());
}

void Image::setImageMagFilter(bool linear)
{
	if (linear)
		agk::SetImageMagFilter(imageNumber, 1);
	else
		agk::SetImageMagFilter(imageNumber, 0);
}

void Image::setAsImageMask(unsigned int imageToMask, short colorDest, short colorSrc, int offsetXDest, int offsetYDest)
{
	if (_ImageNumber(imageToMask))
	{
		if (_ColorChannel(colorDest))
		{
			if (_ColorChannel(colorSrc))
				agk::SetImageMask(imageToMask, imageNumber, colorDest, colorSrc, offsetXDest, offsetYDest);
		}
	}
}

void Image::setImageMinFilter(bool linear)
{
	if (linear)
		agk::SetImageMinFilter(imageNumber, 1);
	else
		agk::SetImageMinFilter(imageNumber, 0);
}

void Image::setImageWrapU(bool repeat)
{
	if (repeat)
		agk::SetImageWrapU(imageNumber, 1);
	else
		agk::SetImageWrapU(imageNumber, 0);
}

void Image::setImageWrapV(bool repeat)
{
	if (repeat)
		agk::SetImageWrapV(imageNumber, 1);
	else
		agk::SetImageWrapV(imageNumber, 0);
}

void Image::loadImage(Text Filename, bool blackIsAlpha, unsigned int assignedImageNumber)
{
	//check through images without parents to see if we have it loaded already
	for (unsigned int i = 0; i < NonParentFileNames.size(); i++)
	{
		if (NonParentFileNames[i] == Filename)
		{
			imageNumber = nonParentImageNumbers[i];
			return;
		}
	}
	
	//not loaded already
	if (!assignedImageNumber)
		imageNumber = agk::LoadImage(Filename.getString(), blackIsAlpha);
	else
	{
		agk::LoadImage(assignedImageNumber, Filename.getString(), blackIsAlpha);
		imageNumber = assignedImageNumber;
	}

	parentImageNumbers.push_back(imageNumber);
	ParentFileNames.push_back(Filename);
}

/*void Image::loadImage(unsigned int assignedImageNumber, Text filename, bool blackIsAlpha)
{
	agk::LoadImage(assignedImageNumber, filename.getString(), blackIsAlpha);
	imageNumber = assignedImageNumber;
}

void Image::loadSubImage(unsigned int parentImage, Text subImageFilename)
{
	imageNumber = agk::LoadSubImage(parentImage, subImageFilename.getString());
}*/

void Image::loadSubImage(unsigned int parentImage, Text Filename, unsigned int assignedImageNumber)
{
	if (assignedImageNumber != 0)
	{
		agk::LoadSubImage(assignedImageNumber, parentImage, Filename.getString());
		imageNumber = assignedImageNumber;
	}
	else
		agk::LoadSubImage(parentImage, Filename.getString());

	nonParentImageNumbers.push_back(imageNumber);
	NonParentFileNames.push_back(Filename);
}

bool Image::_ColorChannel(short value)
{
	if (value > 0)
	{
		if (value < 5)
			return true;
	}

	return false;
}

bool Image::_Filename(Text filename)
{
	char tempFilename[8] = {NULL};
	short lengthOfString = filename.getLength() - 1;

	for (int i = 3; i > -1; i--)
		tempFilename[3-i] = filename.getChar(lengthOfString - i);

	if (strcmp(tempFilename, ".jpg") == 0) //equal
		return true;
	if (strcmp(tempFilename, ".png") == 0) //equal
		return true;

	return false;
}

bool Image::_ImageNumber(unsigned int number)
{
	if (number > 0)
	{
		if (agk::GetImageExists(number))
			return true;
	}

	return false;
}