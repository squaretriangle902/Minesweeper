#include <iostream>
#include <SDL.h>	
#include <memory>
#include "Window.h"
#include "ViewSize.h"

int main(int argc, char* argv[])
{
	const int seed = time(nullptr);
	const int rowCount = 20 * 2;
	const int columnCount = 30 * 2;
	const int bombCount = 99 * 2;
	const int cellSize = 20;
	const int fps = 200;
	const int width = columnCount * cellSize;
	const int height = rowCount * cellSize;
	const ViewSize windowSize = ViewSize(width, height);
	const FieldSize fieldSize = FieldSize(rowCount, columnCount);
	const std::string title = "Minesweeper";

	srand(seed);
	FieldLogic* gameFieldLogic = new FieldLogic(fieldSize);
	gameFieldLogic->FillWithBombs(bombCount);
	std::unique_ptr<Window> gameWindow(new Window(title, windowSize, gameFieldLogic, fps));
	gameWindow->Run();
	return 0;
}