#pragma once
struct FieldPosition
{
public:
	FieldPosition(int row, int column);

	FieldPosition operator+(const FieldPosition& fieldPosition);

	int row;
	int column;
};