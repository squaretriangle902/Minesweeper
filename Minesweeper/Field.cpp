#include "Field.h"

const vector<pair<int, int>> offsetVector = { {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}, };

Field::Field(int columnCount, int rowCount)
{
	this->columnCount = columnCount;
	this->rowCount = rowCount;
	this->gameField = vector<vector<CellLogic*>>(columnCount, vector<CellLogic*>(rowCount));
	InitializeGameField(columnCount, rowCount, gameField);
}

void Field::InitializeGameField(int columnCount, int rowCount, vector<vector<CellLogic*>>& gameField)
{
	for (int i = 0; i < columnCount; i++)
	{
		for (int j = 0; j < rowCount; j++)
		{
			gameField[i][j] = new CellLogic(false, false, false);
		}
	}
}

Field::~Field()
{
}

bool Field::TryAddBomb(int column, int row)
{
	if (!InField(row, column))
	{
		return false;
	}
	return gameField[column][row]->TryAddBomb();
}

bool Field::TrySwitchFlag(int column, int row)
{
	if (!InField(column, row))
	{
		return false;
	}
	return gameField[column][row]->TrySwitchFlag();
}

bool Field::TryOpen(int column, int row)
{
	if (!InField(column, row))
	{
		return false;
	}
	return gameField[column][row]->TryOpen();
}

int Field::GetNearBombsCount(int column, int row)
{
	int nearBombsCount = 0, m = 0, n = 0;
	for (int i = 0; i < offsetVector.size(); i++)
	{
		m = column + offsetVector[i].first, n = row + offsetVector[i].second;
		if (IsBomb(m, n))
		{
			nearBombsCount++;
		}
	}
	return nearBombsCount;
}

int Field::GetNearFlagsCount(int column, int row)
{
	int nearFlagsCount = 0, m = 0, n = 0;
	for (int i = 0; i < offsetVector.size(); i++)
	{
		m = column + offsetVector[i].first, n = row + offsetVector[i].second;
		if (IsFlag(m, n))
		{
			nearFlagsCount++;
		}
	}
	return nearFlagsCount;
}

const CellLogic* Field::GetCell(int column, int row) const
{
	return gameField[column][row];
}

int Field::GetRowCount()
{
	return this->rowCount;
}

int Field::GetColumnCount()
{
	return this->columnCount;
}

//const Cell* Field::GetCell(int columnCount, int rowCount)
//{
//	return gameField[columnCount][rowCount];
//}

bool Field::IsFlag(int column, int row)
{
	return InField(column, row) && gameField[column][row]->IsFlag();
}

bool Field::IsBomb(int column, int row)
{
	return InField(column, row) && gameField[column][row]->IsBomb();
}

bool Field::InField(int column, int row)
{
	return row < rowCount&& row >= 0 && column < columnCount&& column >= 0;
}

bool Field::IsOpened(int column, int row)
{
	return InField(column, row) && gameField[column][row]->IsOpened();
}


