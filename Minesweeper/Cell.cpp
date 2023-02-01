#include "Cell.h"

Cell::Cell(bool bomb, bool flag, bool  opened)
{
	this->bomb = bomb;
	this->flag = flag;
	this->opened = opened;
	this->nearBombsCount = 0;
}

Cell::~Cell()
{
}

int Cell::GetNearBombsCount()
{
	return this->nearBombsCount;
}

bool Cell::IsBomb()
{
	return this->bomb;
}

bool Cell::IsFlag()
{
	return this->flag;
}

bool Cell::IsOpened()
{
	return this->opened;
}

void Cell::IncrementNearBombsCount()
{
	this->nearBombsCount++;
}

void Cell::AddBomb()
{
	this->bomb = true;
}

void Cell::SwitchFlag()
{
	this->flag = !flag;
}

void Cell::Open()
{
	this->opened = true;
}

bool Cell::IsBomb() const
{
	return bomb;
}

bool Cell::IsFlag() const
{
	return flag;
}

bool Cell::IsOpened() const
{
	return opened;
}

bool Cell::TryAddBomb()
{
	if (this->bomb)
	{
		return false;
	}
	this->bomb = true;
	return true;
}

bool Cell::TrySwitchFlag()
{
	if (this->opened)
	{
		return false;
	}
	this->flag = !flag;
	return true;
}

bool Cell::TryOpen()
{
	if (this->flag)
	{
		return false;
	}
	this->opened = true;
	return true;
}
