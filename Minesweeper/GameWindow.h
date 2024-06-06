#pragma once
#include <SDL.h>
#include <SDL_Image.h>
#include <SDL_ttf.h>
#include <string>
#include "GameField.h"
#include "CellView.h"
#include "GameFieldView.h"
#include "WindowPosition.h"
#include "CellPosition.h"
#include "PositionConvert.h"

class GameFieldView;

class GameField;

class GameWindow
{
public:
	GameWindow();
	~GameWindow();

	void Init(std::string title, int width, int height, GameField* gameField);
	void HandleEvents();
	void Render();
	void Clean();

	void HandleMouseLeftButtonDown(SDL_MouseButtonEvent& b);
	void HandleMouseBothButtonDown(SDL_MouseButtonEvent& b);
	void HandleMouseRightButtonDown(SDL_MouseButtonEvent& b);

	bool Running();
private:
	void DrawField(GameField* gameField);
	void MouseFieldPosition(int& mouseColumn, int& mouseRow, int cellSize);
	int CellSize(GameField* gameField);

	bool leftPressed, rightPressed;
	int width, height;
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
	GameFieldView* gameFieldView;
	GameField* gameField;
};

