#include "GameField.h"

GameField::GameField(int rowCount, int columnCount)
{
	this->columnCount = columnCount;
	this->rowCount = rowCount;

	this->gameField = vector<vector<Cell*>>(rowCount, vector<Cell*>(columnCount));
	for (int i = 0; i < rowCount; i++)
	{
		for (int j = 0; j < columnCount; j++)
		{
			gameField[i][j] = new Cell(false, false, false);
		}
	}
}

GameField::~GameField()
{
}

bool GameField::TryAddBomb(int column, int row)
{
	if (!InField(column, row))
	{
		return false;
	}
	Cell* cell = gameField[row][column];
	if (cell->IsBomb()){
		return false;
	}
	cell->AddBomb();
	return true;
}

bool GameField::TrySwitchFlag(int row, int column)
{
	if (!InField(column, row))
	{
		return false;
	}
	return gameField[row][column]->TrySwitchFlag();
}

void GameField::OpenRecursive(int column, int row)
{
	if (InField(column, row) && !IsFlag(column, row))
	{
		gameField[row][column]->Open();
	}
	if (CellNearBombsCount(column, row) != 0)
	{
		return;
	}

	for (size_t i = 0; i < offsetVector.size(); i++)
	{
		int currentColumn = column + offsetVector[i].first, currentRow = row + offsetVector[i].second;
		if (InField(currentColumn, currentRow) && !isOpened(currentColumn, currentRow) && !IsBomb(currentColumn, currentRow))
		{
			OpenRecursive(currentColumn, currentRow);
		}
	}
}

bool GameField::TryOpen(int column, int row)
{
	return gameField[row][column]->TryOpen();
}

bool GameField::FloodOpen(int column, int row)
{
	queue<pair<int, int>> cellPositionQueue = queue<pair<int, int>>();
	cellPositionQueue.push({ column, row });
	pair<int, int> position;
	while (!cellPositionQueue.empty())
	{
		position = cellPositionQueue.front();
		TryOpen(position.first, position.second);
		cellPositionQueue.pop();
		if (CellNearBombsCount(position.first, position.second) != 0)
		{
			continue;
		}
		for (size_t i = 0; i < offsetVector.size(); i++)
		{
			int currentColumn = offsetVector[i].first + position.first, currentRow = offsetVector[i].second + position.second;
			if (InField(currentColumn, currentRow) && !isOpened(currentColumn, currentRow) && !IsBomb(currentColumn, currentRow) && !IsFlag(currentColumn, currentRow))
			{
				cellPositionQueue.push({ currentColumn, currentRow });
			}
		}
	}
	return false;

}

bool GameField::IsBomb(int column, int row)
{
	return gameField[row][column]->IsBomb();
}

bool GameField::IsFlag(int column, int row)
{
	return gameField[row][column]->IsFlag();
}

bool GameField::isOpened(int column, int row)
{
	return gameField[row][column]->IsOpened();
}

int GameField::CellNearBombsCount(int column, int row)
{
	int nearBombsCount = 0;
	int currentRow = 0, currentColumn = 0;
	for (int i = 0; i < offsetVector.size(); i++)
	{
		currentRow = row + offsetVector[i].first, currentColumn = column + offsetVector[i].second;
		if (InField(currentColumn, currentRow) && IsBomb(currentColumn, currentRow))
		{
			nearBombsCount++;
		}
	}
	return nearBombsCount;
}

int GameField::CellNearFlagsCount(int column, int row)
{
	int nearFlagsCount = 0;
	int currentRow = 0, currentColumn = 0;
	for (int i = 0; i < offsetVector.size(); i++)
	{
		currentRow = row + offsetVector[i].first, currentColumn = column + offsetVector[i].second;
		if (InField(currentColumn, currentRow) && IsFlag(currentRow, currentColumn))
		{
			nearFlagsCount++;
		}
	}
	return nearFlagsCount;
}

bool GameField::NearBombsCountEqualsNearFlagsCount(int column, int row)
{
	if (!InField(column, row))
	{
		return false;
	}
	int nearFlagCount = 0, nearBombCount = 0;
	int currentRow = 0, currentColumn = 0;
	for (int i = 0; i < offsetVector.size(); i++)
	{
		currentRow = row + offsetVector[i].first, currentColumn = column + offsetVector[i].second;
		if (!InField(currentColumn, currentRow))
		{
			continue;
		}
		if (IsBomb(currentColumn, currentRow)) nearBombCount++;
		if (IsFlag(currentRow, currentColumn)) nearFlagCount++;
	}
	return nearBombCount == nearFlagCount;
}


int GameField::GetRowCount()
{
	return this->rowCount;
}

int GameField::GetColumnCount()
{
	return this->columnCount;
}

const Cell* GameField::GetCell(int column, int row) const
{
	return gameField[row][column];
}

bool GameField::TryMultiGuess(int column, int row)
{
	int nearFlagCount = 0, nearBombCount = 0;
	if (!InField(column, row) || !NearBombsCountEqualsNearFlagsCount(column, row))
	{
		return false;
	}
	MultiGuess(column, row);
	return true;
}

void GameField::MultiGuess(int column, int row)
{
	int currentRow = 0, currentColumn = 0;
	for (int i = 0; i < offsetVector.size(); i++)
	{
		currentColumn = column + offsetVector[i].second, currentRow = row + offsetVector[i].first;
		if (InField(currentColumn, currentRow))
		{
			OpenRecursive(currentRow, currentColumn);
		}
	}
}


//void GameField::TryToIncrementCellBombCount(int row, int column)
//{
//	if (InField(row, column))
//	{
//		gameField[row][column]->IncrementNearBombsCount();
//	}
//}
//
//void GameField::IncrementNearCellsBombCount(int row, int column)
//{
//	for (int i = 0; i < offsetVector.size(); i++)
//	{
//		TryToIncrementCellBombCount(row + offsetVector[i].first, column + offsetVector[i].second);
//	}
//
//}

bool GameField::InField(int column, int row)
{
	return row < rowCount && row >= 0 && column < columnCount && column >= 0;
}
