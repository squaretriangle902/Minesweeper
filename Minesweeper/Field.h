#pragma once
#include "Cell.h"
#include <vector>

using namespace std;

class Field
{
public:
	Field(int columnCount, int rowCount);
	~Field();

	int GetRowCount();
	int GetColumnCount();

	bool TryAddBomb(int column, int row);
	bool TrySwitchFlag(int column, int row);
	bool TryOpen(int column, int row);

	int GetNearBombsCount(int column, int row);
	int GetNearFlagsCount(int column, int row);

	const Cell* GetCell(int column, int row) const;

	bool InField(int column, int row);
	bool IsFlag(int column, int row);
	bool IsBomb(int column, int row);
	bool IsOpened(int column, int row);

private:
	vector<vector<Cell*>> gameField;
	void InitializeGameField(int columnCount, int rowCount, vector<vector<Cell*>>& gameField);

	int columnCount;
	int rowCount;
};

