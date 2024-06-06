#pragma once
#include <SDL.h>
#include <SDL_Image.h>
#include <SDL_ttf.h>
#include "GameField.h"
#include "CellView.h"
#include "GameFieldView.h"
#include <string>

class GameFieldView;

class GameField;

class GameWindow
{
public:
	GameWindow();
	~GameWindow();

	void Init(std::string title, int width, int height);
	void HandleEvents(GameField* gameField);
	void Render(GameField* gameField);
	void Clean();

	void HandleMouseLeftButtonDown(SDL_MouseButtonEvent& b, GameField* gameField);
	void HandleMouseBothButtonDown(SDL_MouseButtonEvent& b, GameField* gameField);
	void HandleMouseRightButtonDown(SDL_MouseButtonEvent& b, GameField* gameField);

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
};

