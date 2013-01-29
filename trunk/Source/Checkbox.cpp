#include "Checkbox.h"
#include "AGK.h"

Checkbox::Checkbox(void)
{
}


Checkbox::~Checkbox(void)
{
}

void Checkbox::setData(const char filename[], ParentImage OptionsParent)
{
    char tempFileCheck[32] = {NULL};
	char tempFileNotCheck[32] = {NULL};
    unsigned int imgNum;

    Parent = OptionsParent;

    if (strlen(filename) < 24)
	{
		strcpy(tempFileCheck, filename);
		strcpy(tempFileNotCheck, filename);

		strcat(tempFileCheck, "_on.png");
		strcat(tempFileNotCheck, "_off.png");
	}

    imgNum = Parent.getImageNumber(tempFileCheck);
	Checked.setImageNumber(imgNum);

    imgNum = Parent.getImageNumber(tempFileNotCheck);
	NotChecked.setImageNumber(imgNum);
}

void Checkbox::Check(void)
{
	Checked.show();
	NotChecked.hide();

	isChecked = true;
}

void Checkbox::UnCheck(void)
{
	NotChecked.show();
	Checked.hide();

	isChecked = false;
}

void Checkbox::hide(void)
{
	NotChecked.hide();
	Checked.hide();
}
