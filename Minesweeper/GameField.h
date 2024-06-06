#pragma once
#include <vector>
#include <queue>
#include "Cell.h"
#include "GameWindow.h"
#include <iostream>

const std::vector<std::pair<int, int>> offsets = { {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, };

class GameWindow;

class GameField
{
public:
	GameField(int rowCount, int columnCount);
	~GameField();

	bool TryAddBomb(int column, int row);
	bool TrySwitchFlag(int row, int column);
	bool FloodOpen(int row, int column);
	int CellNearBombsCount(int row, int column) const;
	int GetRowCount() const;
	int GetColumnCount() const;
	const Cell* GetCell(int row, int column) const;
	bool TryChord(int row, int column);
	bool InField(int row, int column) const;

private:
	int CellNearFlagsCount(int column, int row) const;
	int CellNearOpenedCount(int column, int row) const;

	bool CellSatisfiesForFloodOpen(int currentColumn, int currentRow);
	void AddToQueueNearSatisfyingCells(std::pair<int, int>& position, std::queue<std::pair<int, int>>& cellQueue);
	void FloodOpenStep(std::queue<std::pair<int, int>>& queue);
	bool CellSatisfiesForChord(int row, int column) const;
	void Chord(int row, int column);
	bool IsBomb(int row, int column) const;
	bool IsFlag(int row, int column) const;
	bool IsOpened(int row, int column) const;
	bool TryOpen(int row, int column);
	std::vector<std::vector<Cell*>> InitializeCellVector(int columnCount, int rowCount);

	std::vector<std::vector<Cell*>> cells;
	int columnCount;
	int rowCount;
};
