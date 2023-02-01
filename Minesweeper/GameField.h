#pragma once
#include <vector>
#include <queue>
#include "Cell.h"

using namespace std;

const vector<pair<int, int>> offsetVector = { {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}, };

class GameField
{
public:
	GameField(int rowCount, int columnCount);
	~GameField();

	bool TryAddBomb(int column, int row);
	bool TrySwitchFlag(int row, int column);

	void OpenRecursive(int row, int column);

	bool TryOpen(int column, int row);
	bool FloodOpen(int column, int row);

	int CellNearBombsCount(int column, int row);
	int CellNearFlagsCount(int column, int row);

	int GetRowCount();
	int GetColumnCount();

	const Cell* GetCell(int column, int row) const;

	bool TryMultiGuess(int column, int row);

	bool InField(int column, int row);
private:

	bool NearBombsCountEqualsNearFlagsCount(int column, int row);

	void MultiGuess(int column, int row);


	bool IsBomb(int column, int row);
	bool IsFlag(int row, int column);
	bool isOpened(int column, int row);

	vector<vector<Cell*>> gameField;
	int columnCount;
	int rowCount;
};
