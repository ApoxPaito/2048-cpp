#include "box.h"

Box::Box()
{
	this->value = 0;
	this->newlyCombined = 0;
}

Box::~Box()
{
	
}

int Box::GetValue() const
{
	return value;
}

void Box::SetValue(int value)
{
	this->value = value;
}

int Box::IsNewlyCombined()
{
	return newlyCombined;
}

void Box::ChangeCombinedState()
{
	if (this->newlyCombined == 0)
		this->newlyCombined = 1;
	else
		this->newlyCombined = 0;
}