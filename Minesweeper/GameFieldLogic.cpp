#include "GameFieldLogic.h"

GameFieldLogic::GameFieldLogic(int rowCount, int columnCount)
{
	this->columnCount = columnCount;
	this->rowCount = rowCount;
	this->cells = InitializeCells(rowCount, columnCount);
}

GameFieldLogic::~GameFieldLogic()
{
}

bool GameFieldLogic::TryAddBomb(int row, int column)
{
	if (!InField(row, column))
	{
		return false;
	}
	return cells[row][column]->TryAddBomb();
}

bool GameFieldLogic::TrySwitchFlag(int row, int column)
{
	if (!InField(row, column))
	{
		return false;
	}
	return cells[row][column]->TrySwitchFlag();
}

bool GameFieldLogic::TryOpen(int row, int column)
{
	return cells[row][column]->TryOpen();
}

bool GameFieldLogic::CellSatisfiesForFloodOpen(int row, int column) const
{
	return InField(row, column) && !IsOpened(row, column) && !IsBomb(row, column);
}

void GameFieldLogic::AddToQueueNearSatisfyingCells(std::pair<int, int>& position, std::queue<std::pair<int, int>>& cellQueue)
{
	for (int i = 0; i < offsets.size(); i++)
	{
		int currentRow = position.first + offsets[i].first;
		int currentColumn = position.second + offsets[i].second;
		if (CellSatisfiesForFloodOpen(currentRow, currentColumn))
		{
			TryOpen(currentRow, currentColumn);
			cellQueue.push({ currentRow, currentColumn });
		}
	}
}

void GameFieldLogic::FloodOpenStep(std::queue<std::pair<int, int>>& cellQueue)
{
	std::pair<int, int> position = cellQueue.front();
	cellQueue.pop();
	if (TryOpen(position.first, position.second) && CellNearBombsCount(position.first, position.second) == 0)
	{
		AddToQueueNearSatisfyingCells(position, cellQueue);
	}
}

void GameFieldLogic::FloodOpen(int row, int column)
{
	std::queue<std::pair<int, int>> cellQueue = std::queue<std::pair<int, int>>();
	cellQueue.push({ row, column });
	while (!cellQueue.empty())
	{
		FloodOpenStep(cellQueue);
	}
}

bool GameFieldLogic::TryFloodOpen(int row, int column)
{
	if (IsOpened(row, column))
	{
		return false;
	}
	FloodOpen(row, column);
	return true;
}

bool GameFieldLogic::IsBomb(int row, int column) const
{
	return cells[row][column]->HasBomb();
}

bool GameFieldLogic::IsFlag(int column, int row) const
{
	return cells[row][column]->HasFlag();
}

bool GameFieldLogic::IsOpened(int row, int column) const
{
	return cells[row][column]->IsOpened();
}

std::vector<std::vector<Cell*>> GameFieldLogic::InitializeCells(int rowCount, int columnCount)
{
	std::vector<std::vector<Cell*>> result = std::vector<std::vector<Cell*>>(rowCount, std::vector<Cell*>(columnCount));
	for (int row = 0; row < rowCount; row++)
	{
		for (int column = 0; column < columnCount; column++)
		{
			result[row][column] = new Cell();
		}
	}
	return result;
}

int GameFieldLogic::CellNearBombsCount(int row, int column) const
{
	int nearBombsCount = 0;
	for (int i = 0; i < offsets.size(); i++)
	{
		int currentRow = row + offsets[i].first; 
		int currentColumn = column + offsets[i].second;
		if (InField(currentRow, currentColumn) && IsBomb(currentRow, currentColumn))
		{
			nearBombsCount++;
		}
	}
	return nearBombsCount;
}

int GameFieldLogic::CellNearFlagsCount(int row, int column) const
{
	int nearFlagsCount = 0;
	for (int i = 0; i < offsets.size(); i++)
	{
		int currentRow = row + offsets[i].first; 
		int currentColumn = column + offsets[i].second;
		if (InField(currentRow, currentColumn) && IsFlag(currentRow, currentColumn))
		{
			nearFlagsCount++;
		}
	}
	return nearFlagsCount;
}

int GameFieldLogic::CellNearOpenedCount(int row, int column) const
{
	int nearOpenedCount = 0;
	for (int i = 0; i < offsets.size(); i++)
	{
		int currentRow = row + offsets[i].first; 
		int currentColumn = column + offsets[i].second;
		if (InField(currentRow, currentColumn) && IsOpened(currentColumn, currentRow))
		{
			nearOpenedCount++;
		}
	}
	return nearOpenedCount;
}

bool GameFieldLogic::CellSatisfiesForChord(int row, int column) const
{
	int nearFlagCount = 0; 
	int nearBombCount = 0;
	for (int i = 0; i < offsets.size(); i++)
	{
		int currentRow = row + offsets[i].first; 
		int currentColumn = column + offsets[i].second;
		if (!InField(currentRow, currentColumn))
		{
			continue;
		}
		if (IsBomb(currentRow, currentColumn)) 
		{
			nearBombCount++;
		}
		if (IsFlag(currentColumn, currentRow)) 
		{
			nearFlagCount++;
		}
	}
	return nearBombCount == nearFlagCount;
}


int GameFieldLogic::GetRowCount() const
{
	return this->rowCount;
}

int GameFieldLogic::GetColumnCount() const
{
	return this->columnCount;
}

const Cell* GameFieldLogic::GetCell(int row, int column) const
{
	return cells[row][column];
}

bool GameFieldLogic::TryChord(int row, int column)
{
	if (!InField(row, column) || !CellSatisfiesForChord(row, column))
	{
		return false;
	}
	Chord(row, column);
	return true;
}

void GameFieldLogic::Chord(int row, int column)
{
	for (int i = 0; i < offsets.size(); i++)
	{
		int currentRow = row + offsets[i].first;
		int currentColumn = column + offsets[i].second; 
		if (InField(currentRow, currentColumn))
		{
			FloodOpen(currentRow, currentColumn);
		}
	}
}

bool GameFieldLogic::InField(int row, int column) const
{
	return row < rowCount && row >= 0 && column < columnCount && column >= 0;
}

