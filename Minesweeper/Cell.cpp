#include "Cell.h"


Cell::Cell(bool bomb, bool flag, bool  opened)
{
	this->isBomb = bomb;
	this->isFlag = flag;
	this->isOpened = opened;
}

Cell::~Cell()
{
}

bool Cell::HasBomb() const
{
	return this->isBomb;
}

bool Cell::HasFlag() const
{
	return this->isFlag;
}

bool Cell::IsOpened() const
{
	return this->isOpened;
}

bool Cell::TryAddBomb()
{
	if (this->isBomb)
	{
		return false;
	}
	this->isBomb = true;
	return true;
}

bool Cell::TrySwitchFlag()
{
	if (this->isOpened)
	{
		return false;
	}
	this->isFlag = !isFlag;
	return true;
}

bool Cell::TryOpen()
{
	if (this->isFlag)
	{
		return false;
	}
	this->isOpened = true;
	return true;
}
