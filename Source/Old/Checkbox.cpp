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