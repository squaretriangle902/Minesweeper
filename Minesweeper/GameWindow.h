#pragma once
#include <SDL.h>
#include <SDL_Image.h>
#include "GameField.h"

class GameWindow
{
public:
	GameWindow();
	~GameWindow();

	void Init(const char* title, int xPosition, int yPosition, int width, int height, bool fullscreen);
	void HandleEvents(GameField* gameField);
	void DrawField(GameField* gameField);
	void Render(GameField* gameField);
	void Clean();

	void HandleMouseLeftButtonDown(SDL_MouseButtonEvent& b, GameField* gameField);
	void HandleMouseBothButtonDown(SDL_MouseButtonEvent& b, GameField* gameField);
	void HandleMouseRightButtonDown(SDL_MouseButtonEvent& b, GameField* gameField);

	bool Running();
private:
	void DrawCell(SDL_Rect* rectangle, const Cell* cell, bool highlighted, int bombCount) const;
	int CellSize(GameField* gameField);
	void ChangeRenderRectangle(SDL_Rect* rectangle, int cellSize, int x, int y);

	void LoadTexture();

	int Min(int a, int b);

	bool leftPressed, rightPressed;



	int width, height;
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
	GameField* gameField;
};

