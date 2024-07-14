#include "FieldLogic.h"

FieldLogic::FieldLogic(FieldSize fieldSize)
{
	this->fieldSize = fieldSize;
	this->columnCount = fieldSize.columnCount;
	this->rowCount = fieldSize.rowCount;
	this->cells = InitializeCells();
	this->bombCount = 0;
	this->openedCellsCount = 0;
	this->gameState = GameState::continues;
}

FieldLogic::~FieldLogic()
{
}

void FieldLogic::FloodOpenStep(std::queue<FieldPosition>& cellQueue)
{
	FieldPosition position = cellQueue.front();
	cellQueue.pop();
	
	if (!GetCellInternal(position)->TryOpen())
	{
		return;
	}
	if (CellNearBombsCount(position) == 0)
	{
		AddToQueueNearSatisfyingCells(position, cellQueue);
	}
}

bool FieldLogic::CellSatisfiesForChord(FieldPosition fieldPosition) const
{
	int nearFlagCount = 0;
	int nearBombCount = 0;
	for (int i = 0; i < offsets.size(); i++)
	{
		FieldPosition currentPosititon = fieldPosition + offset_s[i];
		if (!InField(currentPosititon))
		{
			continue;
		}
		if (IsBomb(currentPosititon))
		{
			nearBombCount++;
		}
		if (IsFlag(currentPosititon))
		{
			nearFlagCount++;
		}
	}
	return nearBombCount == nearFlagCount;
}

void FieldLogic::Chord(FieldPosition fieldPosition)
{
	for (int i = 0; i < offsets.size(); i++)
	{
		FieldPosition currentPosititon = fieldPosition + offset_s[i];
		if (InField(currentPosititon))
		{
			FloodOpen(currentPosititon);
		}
	}
}

bool FieldLogic::IsBomb(FieldPosition fieldPosition) const
{
	return cells[fieldPosition.row][fieldPosition.column]->HasBomb();
}

bool FieldLogic::IsFlag(FieldPosition fieldPosition) const
{
	return cells[fieldPosition.row][fieldPosition.column]->HasFlag();
}

std::vector<std::vector<CellLogic*>> FieldLogic::InitializeCells()
{
	std::vector<std::vector<CellLogic*>> result = std::vector<std::vector<CellLogic*>>(
		fieldSize.rowCount, 
		std::vector<CellLogic*>(fieldSize.columnCount)
	);
	for (int row = 0; row < fieldSize.rowCount; row++)
	{
		for (int column = 0; column < fieldSize.columnCount; column++)
		{
			result[row][column] = new CellLogic();
		}
	}
	return result;
}

void FieldLogic::UpdateOpenedCellsCount()
{
	this->openedCellsCount = 0;
	for (int row = 0; row < rowCount; row++)
	{
		for (int column = 0; column < columnCount; column++)
		{
			if (GetCell(FieldPosition(row, column))->IsOpened())
			{
				this->openedCellsCount++;
			}
		}
	}
}

CellLogic* FieldLogic::GetCellInternal(FieldPosition fieldPosition)
{
	return cells[fieldPosition.row][fieldPosition.column];
}

void FieldLogic::FloodOpen(FieldPosition fieldPosition)
{
	std::queue<FieldPosition> cellQueue = std::queue<FieldPosition>();
	cellQueue.push(fieldPosition);
	while (!cellQueue.empty())
	{
		FloodOpenStep(cellQueue);
	}
	UpdateOpenedCellsCount();
}

bool FieldLogic::InField(FieldPosition fieldPosition) const
{
	return fieldPosition.row < fieldSize.rowCount && 
		fieldPosition.row >= 0 && 
		fieldPosition.column < fieldSize.columnCount &&
		fieldPosition.column >= 0;
}

int FieldLogic::CellNearFlagsCount(FieldPosition fieldPosition) const
{
	int nearFlagsCount = 0;
	for (int i = 0; i < offsets.size(); i++)
	{
		FieldPosition currentPosititon = fieldPosition + offset_s[i];
		if (InField(currentPosititon) && IsFlag(currentPosititon))
		{
			nearFlagsCount++;
		}
	}
	return nearFlagsCount;
}

int FieldLogic::CellNearOpenedCount(FieldPosition fieldPosition) const
{
	int nearOpenedCount = 0;
	for (int i = 0; i < offsets.size(); i++)
	{
		FieldPosition currentPosititon = fieldPosition + offset_s[i];
		if (InField(currentPosititon) && GetCell(currentPosititon)->IsOpened())
		{
			nearOpenedCount++;
		}
	}
	return nearOpenedCount;
}

bool FieldLogic::CellSatisfiesForFloodOpen(FieldPosition fieldPosition) const
{
	if (!InField(fieldPosition))
	{
		return false;
	}
	const CellLogic* cellLogic = GetCell(fieldPosition);
	return !cellLogic->IsOpened() && !cellLogic->HasBomb();
}

void FieldLogic::AddToQueueNearSatisfyingCells(FieldPosition fieldPosition, std::queue<FieldPosition>& cellQueue)
{
	for (int i = 0; i < offsets.size(); i++)
	{
		FieldPosition currentPosititon = fieldPosition + offset_s[i];
		if (CellSatisfiesForFloodOpen(currentPosititon))
		{
			GetCellInternal(currentPosititon)->TryOpen();
			cellQueue.push(currentPosititon);
		}
	}
}

bool FieldLogic::TryAddBomb(FieldPosition fieldPosition)
{
	if (!InField(fieldPosition))
	{
		return false;
	}
	return cells[fieldPosition.row][fieldPosition.column]->TryAddBomb();
}

bool FieldLogic::TrySwitchFlag(FieldPosition fieldPosition)
{
	if (gameState != GameState::continues && !InField(fieldPosition))
	{
		return false;
	}
	return cells[fieldPosition.row][fieldPosition.column]->TrySwitchFlag();
}

bool FieldLogic::TryFloodOpen(FieldPosition fieldPosition)
{
	if (gameState != GameState::continues && GetCell(fieldPosition)->IsOpened())
	{
		return false;
	}
	FloodOpen(fieldPosition);
	return true;
}

bool FieldLogic::TryChord(FieldPosition fieldPosition)
{
	if (gameState != GameState::continues && !InField(fieldPosition) || !CellSatisfiesForChord(fieldPosition))
	{
		return false;
	}
	Chord(fieldPosition);
	return true;
}

int FieldLogic::CellNearBombsCount(FieldPosition fieldPosition) const
{
	int nearBombsCount = 0;
	for (int i = 0; i < offsets.size(); i++)
	{
		FieldPosition currentPosititon = fieldPosition + offset_s[i];
		if (InField(currentPosititon) && IsBomb(currentPosititon))
		{
			nearBombsCount++;
		}
	}
	return nearBombsCount;
}

int FieldLogic::GetRowCount() const
{
	return this->rowCount;
}

int FieldLogic::GetColumnCount() const
{
	return this->columnCount;
}

const CellLogic* FieldLogic::GetCell(FieldPosition fieldPosition) const
{
	return cells[fieldPosition.row][fieldPosition.column];
}

void FieldLogic::AddBomb()
{
	while (true)
	{
		int randomRow = RandomInt(0, fieldSize.rowCount);
		int randomColumn = RandomInt(0, fieldSize.columnCount);
		FieldPosition randomPosition = FieldPosition(randomRow, randomColumn);
		if (TryAddBomb(randomPosition))
		{
			bombCount++;
			return;
		}
	}
}

void FieldLogic::FillWithBombs(int bombCount)
{
	for (int i = 0; i < bombCount; i++)
	{
		AddBomb();
	}
}

GameState FieldLogic::GetGameState() const
{
	return gameState;
}

