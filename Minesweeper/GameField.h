#pragma once
#include <vector>
#include <queue>
#include "Cell.h"
#include "GameWindow.h"
#include <iostream>

using namespace std;

const vector<pair<int, int>> offsetVector = { {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, };

class GameWindow;

class GameField
{
public:
	GameField(int rowCount, int columnCount);
	~GameField();

	bool TryAddBomb(int column, int row);
	bool TrySwitchFlag(int column, int row);

	bool FloodOpen(int column, int row);
	

	int CellNearBombsCount(int column, int row);


	int GetRowCount();
	int GetColumnCount();

	Cell* GetCell(int column, int row);

	const Cell* GetCell(int column, int row) const;

	bool TryChord(int column, int row);
	bool InField(int column, int row);

private:
	int CellNearFlagsCount(int column, int row);
	int CellNearOpenedCount(int column, int row);

	bool CellSatisfiesForFloodOpen(int currentColumn, int currentRow);
	void AddToQueueNearSatisfyingCells(pair<int, int>& position, queue<pair<int, int>>& cellQueue);
	void FloodOpenStep(queue<pair<int, int>>& queue);
	bool NearBombsCountEqualsNearFlagsCount(int column, int row);
	void Chord(int column, int row);
	bool IsBomb(int column, int row);
	bool IsFlag(int row, int column);
	bool IsOpened(int column, int row);
	bool TryOpen(int column, int row);

	vector<vector<Cell*>> InitializeCellVector(int columnCount, int rowCount);

	vector<vector<Cell*>> cells;
	int columnCount;
	int rowCount;
};
