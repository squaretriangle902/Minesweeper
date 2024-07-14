#pragma once
#include <vector>
#include <queue>
#include <map>
#include <iostream>
#include "CellLogic.h"
#include "Window.h"
#include "Timer.h"
#include "Random.h"
#include "FieldPosition.h"
#include "FieldSize.h"

const std::vector<std::pair<int, int>> offsets = { {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, };

const std::vector<FieldPosition> offset_s = 
{ 
	FieldPosition(-1, -1), 
	FieldPosition(-1, 0), 
	FieldPosition(-1, 1), 
	FieldPosition(0, -1), 
	FieldPosition(0, 1), 
	FieldPosition(1, 1), 
	FieldPosition(1, 0), 
	FieldPosition(1, -1),
};

enum class GameState
{
	continues = 0,
	won = 1,
	lost = 2,
};

class Window;

class FieldLogic
{
public: 
	FieldLogic(FieldSize fieldSize);
	~FieldLogic();

	bool TryAddBomb(FieldPosition fieldPosition);
	bool TrySwitchFlag(FieldPosition fieldPosition);
	bool TryFloodOpen(FieldPosition fieldPosition);
	bool TryChord(FieldPosition fieldPosition);
	int CellNearBombsCount(FieldPosition fieldPosition) const;
	int GetRowCount() const;
	int GetColumnCount() const;
	const CellLogic* GetCell(FieldPosition fieldPosition) const;
	void AddBomb();
	void FillWithBombs(int bombCount);
	GameState GetGameState() const;

private:
	CellLogic* GetCellInternal(FieldPosition fieldPosition);
	void FloodOpen(FieldPosition fieldPosition);
	bool InField(FieldPosition fieldPosition) const;
	int CellNearFlagsCount(FieldPosition fieldPosition) const;
	int CellNearOpenedCount(FieldPosition fieldPosition) const;
	bool CellSatisfiesForFloodOpen(FieldPosition fieldPosition) const;
	void AddToQueueNearSatisfyingCells(FieldPosition fieldPosition, std::queue<FieldPosition>& cellQueue);
	void FloodOpenStep(std::queue<FieldPosition>& queue);
	bool CellSatisfiesForChord(FieldPosition fieldPosition) const;
	void Chord(FieldPosition fieldPosition);
	bool IsBomb(FieldPosition fieldPosition) const;
	bool IsFlag(FieldPosition fieldPosition) const;
	std::vector<std::vector<CellLogic*>> InitializeCells();
	void UpdateOpenedCellsCount();

	std::vector<std::vector<CellLogic*>> cells;
	GameState gameState;
	FieldSize fieldSize;
	int bombCount;
	int openedCellsCount;
	int columnCount;
	int rowCount;
};
