#pragma once
#include <vector>
#include <queue>
#include <iostream>
#include "Cell.h"
#include "GameWindow.h"
#include "Timer.h"

const std::vector<std::pair<int, int>> offsets = { {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, };

class GameWindow;

class GameFieldLogic
{
public:
	GameFieldLogic(int rowCount, int columnCount);
	~GameFieldLogic();

	bool TryAddBomb(int row, int column);
	bool TrySwitchFlag(int row, int column);
	bool TryFloodOpen(int row, int column);
	bool TryChord(int row, int column);
	int CellNearBombsCount(int row, int column) const;
	int GetRowCount() const;
	int GetColumnCount() const;
	const Cell* GetCell(int row, int column) const;

private:
	void FloodOpen(int row, int column);
	bool InField(int row, int column) const;
	int CellNearFlagsCount(int row, int column) const;
	int CellNearOpenedCount(int row, int column) const;
	bool CellSatisfiesForFloodOpen(int currentRow, int currentColumn) const;
	void AddToQueueNearSatisfyingCells(std::pair<int, int>& position, std::queue<std::pair<int, int>>& cellQueue);
	void FloodOpenStep(std::queue<std::pair<int, int>>& queue);
	bool CellSatisfiesForChord(int row, int column) const;
	void Chord(int row, int column);
	bool IsBomb(int row, int column) const;
	bool IsFlag(int row, int column) const;
	bool IsOpened(int row, int column) const;
	bool TryOpen(int row, int column);
	std::vector<std::vector<Cell*>> InitializeCells(int rowCount, int columnCount);

	std::vector<std::vector<Cell*>> cells;
	int columnCount;
	int rowCount;
};
