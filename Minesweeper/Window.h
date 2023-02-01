#pragma once
#include <SDL.h>
#include <SDL_Image.h>
#include "Field.h"

class Window
{
public:
	Window();
	~Window();

	void Init(const char* title, int xPosition, int yPosition, int width, int height);

	SDL_Texture* LoadTexture(const char* imageSource);

private:
	void DrawCell(Cell* cell, SDL_Rect* rectangle, int bombCount);

	int width, height;
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
};

