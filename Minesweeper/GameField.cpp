#include "GameField.h"

GameField::GameField(int rowCount, int columnCount)
{
	this->columnCount = columnCount;
	this->rowCount = rowCount;
	this->cells = InitializeCellVector(columnCount, rowCount);
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
	return cells[column][row]->TryAddBomb();
}

bool GameField::TrySwitchFlag(int column, int row)
{
	if (!InField(column, row))
	{
		return false;
	}
	return cells[column][row]->TrySwitchFlag();
}

bool GameField::TryOpen(int column, int row)
{
	return cells[column][row]->TryOpen();
}

bool GameField::CellSatisfiesForFloodOpen(int column, int row)
{
	return InField(column, row) && !IsOpened(column, row) && !IsBomb(column, row);
}

void GameField::AddToQueueNearSatisfyingCells(pair<int, int>& position, queue<pair<int, int>>& cellQueue)
{
	for (size_t i = 0; i < offsetVector.size(); i++)
	{
		int currentColumn = offsetVector[i].first + position.first, currentRow = offsetVector[i].second + position.second;
		if (CellSatisfiesForFloodOpen(currentColumn, currentRow))
		{
			TryOpen(currentColumn, currentRow);
			cellQueue.push({ currentColumn, currentRow });
		}
	}
}

void GameField::FloodOpenStep(queue<pair<int, int>>& cellQueue)
{
	pair<int, int> position = cellQueue.front();
	cellQueue.pop();
	if (TryOpen(position.first, position.second) && CellNearBombsCount(position.first, position.second) == 0)
	{
		AddToQueueNearSatisfyingCells(position, cellQueue);
	}
}

bool GameField::FloodOpen(int column, int row)
{
	queue<pair<int, int>> cellQueue = queue<pair<int, int>>();
	cellQueue.push({ column, row });
	while (!cellQueue.empty())
	{
		FloodOpenStep(cellQueue);
	}
	return false;

}

bool GameField::IsBomb(int column, int row)
{
	return cells[column][row]->IsBomb();
}

bool GameField::IsFlag(int column, int row)
{
	return cells[column][row]->IsFlag();
}

bool GameField::IsOpened(int column, int row)
{
	return cells[column][row]->IsOpened();
}

vector<vector<Cell*>> GameField::InitializeCellVector(int columnCount, int rowCount)
{
	vector<vector<Cell*>> result = vector<vector<Cell*>>(columnCount, vector<Cell*>(rowCount));
	for (int i = 0; i < columnCount; i++)
	{
		for (int j = 0; j < rowCount; j++)
		{
			result[i][j] = new Cell();
		}
	}
	return result;
}

int GameField::CellNearBombsCount(int column, int row)
{
	int nearBombsCount = 0;
	for (int i = 0; i < offsetVector.size(); i++)
	{
		int currentRow = row + offsetVector[i].first, currentColumn = column + offsetVector[i].second;
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
	for (int i = 0; i < offsetVector.size(); i++)
	{
		int currentRow = row + offsetVector[i].first, currentColumn = column + offsetVector[i].second;
		if (InField(currentColumn, currentRow) && IsFlag(currentRow, currentColumn))
		{
			nearFlagsCount++;
		}
	}
	return nearFlagsCount;
}

bool GameField::NearBombsCountEqualsNearFlagsCount(int column, int row)
{
	int nearFlagCount = 0, nearBombCount = 0;
	for (int i = 0; i < offsetVector.size(); i++)
	{
		int currentRow = row + offsetVector[i].first, currentColumn = column + offsetVector[i].second;
		if (!InField(currentColumn, currentRow))
		{
			continue;
		}
		if (IsBomb(currentColumn, currentRow)) nearBombCount++;
		if (IsFlag(currentColumn, currentRow)) nearFlagCount++;
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
	return cells[column][row];
}

bool GameField::TryChord(int column, int row)
{
	if (!InField(column, row) || !NearBombsCountEqualsNearFlagsCount(column, row))
	{
		return false;
	}
	Chord(column, row);
	return true;
}

void GameField::Chord(int column, int row)
{
	for (int i = 0; i < offsetVector.size(); i++)
	{
		int currentColumn = column + offsetVector[i].first, currentRow = row + offsetVector[i].second;
		if (InField(currentColumn, currentRow))
		{
			FloodOpen(currentColumn, currentRow);
		}
	}
}

bool GameField::InField(int column, int row)
{
	return row < rowCount && row >= 0 && column < columnCount && column >= 0;
}

