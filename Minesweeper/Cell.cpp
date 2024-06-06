#include "Cell.h"


Cell::Cell(bool bomb, bool flag, bool  opened)
{
	this->hasBomb = bomb;
	this->hasFlag = flag;
	this->isOpened = opened;
}

Cell::~Cell()
{
}

bool Cell::HasBomb() const
{
	return this->hasBomb;
}

bool Cell::HasFlag() const
{
	return this->hasFlag;
}

bool Cell::IsOpened() const
{
	return this->isOpened;
}

bool Cell::TryAddBomb()
{
	if (this->hasBomb)
	{
		return false;
	}
	this->hasBomb = true;
	return true;
}

bool Cell::TrySwitchFlag()
{
	if (this->isOpened)
	{
		return false;
	}
	this->hasFlag = !hasFlag;
	return true;
}

bool Cell::TryOpen()
{
	if (this->hasFlag)
	{
		return false;
	}
	this->isOpened = true;
	return true;
}
