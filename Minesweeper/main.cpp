#include <iostream>
#include <SDL.h>	
#include "GameWindow.h"
#include "main.h"

using namespace std;

void AddBomb(GameField* gameField)
{
	while (!gameField->TryAddBomb(rand() % (gameField->GetColumnCount() + 1), rand() % (gameField->GetRowCount() + 1))) {};
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
	int bombCount = 3;

	GameField* gameField = new GameField(rows, columns);
	//FillWithBombs(gameField, bombCount);

	vector<pair<int, int>> vect = { {15, 15},
		{20, 15}, {19, 15}, {18, 15}, {17, 15}, {16, 15}, {14, 15}, {13, 15}, {12, 15}, {11, 15}, {10, 15}, 
		{20, 10}, {19, 10}, {18, 10}, {17, 10}, {16, 10},
	    {14, 20}, {13, 20}, {12, 20}, {11, 20}, {10, 20}, 
		{15, 20}, {15, 19}, {15, 18}, {15, 17}, {15, 16}, {15, 14}, {15, 13}, {15, 12}, {15, 11}, {15, 10},
		{20, 20}, {20, 19}, {20, 18}, {20, 17}, {20, 16}, 
		{10, 14}, {10, 13}, {10, 12}, {10, 11}, {10, 10}, };

	for (size_t i = 0; i < vect.size(); i++)
	{
		gameField->TryAddBomb(vect[i].first, vect[i].second);
	}

	const int FPS = 200;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart = SDL_GetTicks();
	int frameTime = 0;

	GameWindow* game = new GameWindow();
	game->Init("Minesweeper", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, columns * cellSize, rows * cellSize, true);
	while (game->Running())
	{
		frameStart = SDL_GetTicks();

		game->HandleEvents(gameField);
		game->Render(gameField);

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) 
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}
	game->Clean();


	return 0;
}