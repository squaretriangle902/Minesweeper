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
	if (!InField(row, column))
	{
		return false;
	}
	return cells[column][row]->TryAddBomb();
}

bool GameField::TrySwitchFlag(int row, int column)
{
	if (!InField(row, column))
	{
		return false;
	}
	return cells[column][row]->TrySwitchFlag();
}

bool GameField::TryOpen(int row, int column)
{
	return cells[column][row]->TryOpen();
}

bool GameField::CellSatisfiesForFloodOpen(int column, int row)
{
	return InField(row, column) && !IsOpened(row, column) && !IsBomb(row, column);
}

void GameField::AddToQueueNearSatisfyingCells(std::pair<int, int>& position, std::queue<std::pair<int, int>>& cellQueue)
{
	for (int i = 0; i < offsets.size(); i++)
	{
		int currentColumn = position.first + offsets[i].first;
		int currentRow = position.second + offsets[i].second;
		if (CellSatisfiesForFloodOpen(currentColumn, currentRow))
		{
			TryOpen(currentRow, currentColumn);
			cellQueue.push({ currentColumn, currentRow });
		}
	}
}

void GameField::FloodOpenStep(std::queue<std::pair<int, int>>& cellQueue)
{
	std::pair<int, int> position = cellQueue.front();
	cellQueue.pop();
	if (TryOpen(position.second, position.first) && CellNearBombsCount(position.second, position.first) == 0)
	{
		AddToQueueNearSatisfyingCells(position, cellQueue);
	}
}

bool GameField::FloodOpen(int row, int column)
{
	std::queue<std::pair<int, int>> cellQueue = std::queue<std::pair<int, int>>();
	cellQueue.push({ column, row });
	while (!cellQueue.empty())
	{
		FloodOpenStep(cellQueue);
	}
	return false;

}

bool GameField::IsBomb(int row, int column) const
{
	return cells[column][row]->HasBomb();
}

bool GameField::IsFlag(int column, int row) const
{
	return cells[column][row]->HasFlag();
}

bool GameField::IsOpened(int row, int column) const
{
	return cells[column][row]->IsOpened();
}

std::vector<std::vector<Cell*>> GameField::InitializeCellVector(int columnCount, int rowCount)
{
	std::vector<std::vector<Cell*>> result = std::vector<std::vector<Cell*>>(columnCount, std::vector<Cell*>(rowCount));
	for (int i = 0; i < columnCount; i++)
	{
		for (int j = 0; j < rowCount; j++)
		{
			result[i][j] = new Cell();
		}
	}
	return result;
}

int GameField::CellNearBombsCount(int row, int column) const
{
	int nearBombsCount = 0;
	for (int i = 0; i < offsets.size(); i++)
	{
		int currentRow = row + offsets[i].first, currentColumn = column + offsets[i].second;
		if (InField(currentRow, currentColumn) && IsBomb(currentRow, currentColumn))
		{
			nearBombsCount++;
		}
	}
	return nearBombsCount;
}

int GameField::CellNearFlagsCount(int column, int row) const
{
	int nearFlagsCount = 0;
	for (int i = 0; i < offsets.size(); i++)
	{
		int currentRow = row + offsets[i].first, currentColumn = column + offsets[i].second;
		if (InField(currentRow, currentColumn) && IsFlag(currentRow, currentColumn))
		{
			nearFlagsCount++;
		}
	}
	return nearFlagsCount;
}

int GameField::CellNearOpenedCount(int column, int row) const
{
	int nearOpenedCount = 0;
	for (int i = 0; i < offsets.size(); i++)
	{
		int currentRow = row + offsets[i].first, currentColumn = column + offsets[i].second;
		if (InField(currentRow, currentColumn) && IsOpened(currentColumn, currentRow))
		{
			nearOpenedCount++;
		}
	}
	return nearOpenedCount;
}

bool GameField::CellSatisfiesForChord(int row, int column) const
{
	int nearFlagCount = 0, nearBombCount = 0;
	for (int i = 0; i < offsets.size(); i++)
	{
		int currentRow = row + offsets[i].first, currentColumn = column + offsets[i].second;
		if (!InField(currentRow, currentColumn))
		{
			continue;
		}
		if (IsBomb(currentRow, currentColumn)) nearBombCount++;
		if (IsFlag(currentColumn, currentRow)) nearFlagCount++;
	}
	return nearBombCount == nearFlagCount;
}


int GameField::GetRowCount() const
{
	return this->rowCount;
}

int GameField::GetColumnCount() const
{
	return this->columnCount;
}

const Cell* GameField::GetCell(int row, int column) const
{
	return cells[column][row];
}

bool GameField::TryChord(int row, int column)
{
	if (!InField(row, column) || !CellSatisfiesForChord(row, column))
	{
		return false;
	}
	Chord(row, column);
	return true;
}

void GameField::Chord(int row, int column)
{
	for (int i = 0; i < offsets.size(); i++)
	{
		int currentColumn = column + offsets[i].first; 
		int currentRow = row + offsets[i].second;
		if (InField(currentRow, currentColumn))
		{
			FloodOpen(currentRow, currentColumn);
		}
	}
}

bool GameField::InField(int row, int column) const
{
	return row < rowCount && row >= 0 && column < columnCount && column >= 0;
}

