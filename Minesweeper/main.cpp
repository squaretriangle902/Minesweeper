#include <iostream>
#include <SDL.h>	
#include "GameWindow.h"
#include "main.h"


void AddBomb(GameFieldLogic* gameField)
{
	int randomColumnUpperBound = gameField->GetColumnCount() + 1;
	int randomRowUpperBound = gameField->GetRowCount() + 1;
	while (true)
	{
		int randomColumn = rand() % randomColumnUpperBound;
		int randomRow = rand() % randomRowUpperBound;
		if (gameField->TryAddBomb(randomRow, randomColumn))
		{
			return;
		}
	}
}

void FillWithBombs(GameFieldLogic* gameField, int bombCount)
{
	for (int i = 0; i < bombCount; i++)
	{
		AddBomb(gameField);
	}
}


int main(int argc, char* argv[])
{
	srand(time(nullptr));

	const int rowCount = 30;
	const int columnCount = 30;
	const int bombCount = 99;
	const int cellSize = 20;
	const int FPS = 200;

	GameFieldLogic* gameField = new GameFieldLogic(rowCount, columnCount);
	FillWithBombs(gameField, bombCount);
	GameWindow* gameWindow = new GameWindow("Minesweeper", columnCount * cellSize, rowCount * cellSize, gameField, FPS);
	gameWindow->Run();
	delete gameWindow;
	return 0;
}