#include <iostream>
#include <SDL.h>	
#include "GameWindow.h"
#include "main.h"

using namespace std;

void AddBomb(GameField* gameField)
{
	int randomColumnUpperBound = gameField->GetColumnCount() + 1;
	int randomRowUpperBound = gameField->GetRowCount() + 1;
	while (true)
	{
		int randomColumn = rand() % randomColumnUpperBound;
		int randomRow = rand() % randomRowUpperBound;
		if (gameField->TryAddBomb(randomColumn, randomRow))
		{
			return;
		}
	}
}

void FillWithBombs(GameField* gameField, int bombCount)
{
	for (int i = 0; i < bombCount; i++)
	{
		AddBomb(gameField);
	}
}

int main(int argc, char* argv[])
{
	srand(time(NULL));

	int rows = 30, columns = 30;
	int cellSize = 20;
	int bombCount = 99;

	GameField* gameField = new GameField(rows, columns);
	FillWithBombs(gameField, bombCount);

	const int FPS = 200;
	const int frameDelay = 1000 / FPS;

	GameWindow* gameWindow = new GameWindow();
	gameWindow->Init("Minesweeper", columns * cellSize, rows * cellSize);
	while (gameWindow->Running())
	{
		Uint32 frameStart = SDL_GetTicks();
		gameWindow->HandleEvents(gameField);
		gameWindow->Render(gameField);
		int frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime) 
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}
	gameWindow->Clean();
	return 0;
}