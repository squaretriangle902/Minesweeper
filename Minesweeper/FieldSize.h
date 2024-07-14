#pragma once
struct FieldSize
{
public:
	FieldSize();
	FieldSize(int rowCount, int columnCount);
	FieldSize(const FieldSize& fieldSize);

	FieldSize& operator=(const FieldSize& fieldSize);

	int rowCount;
	int columnCount;
};

