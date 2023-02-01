#pragma once
#include <SDL.h>
#include <SDL_Image.h>

#include "Controller.h"

class Controller;

class View
{
	View(Controller* controller);
	~View();

	void Initialize(const char* title, int xPosition, int yPosition, int width, int height);
	void SendEvents();

	void Render();
	void Update();

private:
	int width, height, cellSize;
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;

	Controller* controller;
};

