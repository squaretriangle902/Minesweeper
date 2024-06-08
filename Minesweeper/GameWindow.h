#pragma once
#include <SDL.h>
#include <SDL_Image.h>
#include <SDL_ttf.h>
#include <string>
#include "GameFieldLogic.h"
#include "CellView.h"
#include "GameFieldView.h"
#include "WindowPosition.h"
#include "CellPosition.h"
#include "PositionConvert.h"

class GameFieldView;

class GameFieldLogic;

class GameWindow
{
public:
	GameWindow(const std::string& title, int width, int height, GameFieldLogic* gameField, int FPS);
	~GameWindow();

	void HandleEvents();
	void Render();
	void Clean();

	void HandleMouseLeftButtonDown(SDL_MouseButtonEvent& b);
	void HandleMouseBothButtonDown(SDL_MouseButtonEvent& b);
	void HandleMouseRightButtonDown(SDL_MouseButtonEvent& b);

	void Run();

	bool Running();
private:
	void DrawField(GameFieldLogic* gameField);
	void MouseFieldPosition(int& mouseColumn, int& mouseRow, int cellSize);
	int CellSize(GameFieldLogic* gameField);

	bool leftPressed;
	bool rightPressed;
	int width; 
	int height;
	bool isRunning;
	int FPS;
	SDL_Window* window;
	SDL_Renderer* renderer;
	GameFieldView* gameFieldView;
	GameFieldLogic* gameFieldLogic;
};

