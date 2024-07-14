#include "FieldSize.h"

FieldSize::FieldSize()
{
	this->rowCount = 0;
	this->columnCount = 0;
}

FieldSize::FieldSize(int rowCount, int columnCount)
{
	this->rowCount = rowCount;
	this->columnCount = columnCount;
}

FieldSize::FieldSize(const FieldSize& fieldSize)
{
	this->rowCount = fieldSize.rowCount;
	this->columnCount = fieldSize.columnCount;
}

FieldSize& FieldSize::operator=(const FieldSize& fieldSize)
{
	this->rowCount = fieldSize.rowCount;
	this->columnCount = fieldSize.columnCount;
	return *this;
}
