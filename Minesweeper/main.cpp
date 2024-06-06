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
	srand(time(nullptr));

	int const rowCount = 30; 
	int const columnCount = 30;
	int const bombCount = 99;
	int const cellSize = 20;

	GameField* gameField = new GameField(rowCount, columnCount);
	FillWithBombs(gameField, bombCount);

	int const FPS = 200;
	int const frameDelay = 1000 / FPS;

	GameWindow* gameWindow = new GameWindow();
	gameWindow->Init("Minesweeper", columnCount * cellSize, rowCount * cellSize, gameField);
	while (gameWindow->Running())
	{
		Uint32 frameStart = SDL_GetTicks();
		gameWindow->HandleEvents();
		gameWindow->Render();
		int frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime) 
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}
	gameWindow->Clean();
	return 0;
}