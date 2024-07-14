#include "CellLogic.h"


CellLogic::CellLogic(bool bomb, bool flag, bool  opened)
{
	this->isBomb = bomb;
	this->isFlag = flag;
	this->isOpened = opened;
}

CellLogic::~CellLogic()
{
}

bool CellLogic::HasBomb() const
{
	return this->isBomb;
}

bool CellLogic::HasFlag() const
{
	return this->isFlag;
}

bool CellLogic::IsOpened() const
{
	return this->isOpened;
}

bool CellLogic::TryAddBomb()
{
	if (this->isBomb)
	{
		return false;
	}
	this->isBomb = true;
	return true;
}

bool CellLogic::TrySwitchFlag()
{
	if (this->isOpened)
	{
		return false;
	}
	this->isFlag = !isFlag;
	return true;
}

bool CellLogic::TryOpen()
{
	if (this->isFlag)
	{
		return false;
	}
	this->isOpened = true;
	return true;
}
