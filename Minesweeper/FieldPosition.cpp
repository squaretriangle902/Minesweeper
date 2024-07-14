#include "FieldPosition.h"

FieldPosition::FieldPosition(int row, int column)
{
	this->row = row;
	this->column = column;
}

FieldPosition FieldPosition::operator+(const FieldPosition& fieldPosition)
{
	return FieldPosition(row + fieldPosition.row, column + fieldPosition.column);
}
