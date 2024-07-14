#pragma once
#include <SDL.h>
#include <SDL_Image.h>
#include <SDL_ttf.h>
#include <string>
#include "FieldLogic.h"
#include "CellView.h"
#include "FieldView.h"
#include "ViewPosition.h"
#include "FieldPosition.h"
#include "PositionConvert.h"
#include "ViewSize.h"

class FieldView;
class FieldLogic;

class Window
{
public:
	Window(const std::string& title, ViewSize size, FieldLogic* gameField, int fps);
	~Window();

	void HandleMouseLeftButtonDown(SDL_MouseButtonEvent& b);
	void HandleMouseBothButtonDown(SDL_MouseButtonEvent& b);
	void HandleMouseRightButtonDown(SDL_MouseButtonEvent& b);
	void SetGameFieldView(FieldView* gameFieldView);
	void Run();

private:
	bool Running();
	void HandleEvents();
	void Render();
	void Clean();
	void RenderField(FieldLogic* gameField);
	void LostMessage();
	void WonMessage();
	FieldPosition MouseFieldPosition(int cellSize);
	ViewPosition EventPosition(SDL_MouseButtonEvent& b);
	int CellSize(FieldLogic* gameField);

	bool leftPressed;
	bool rightPressed;
	bool isRunning;
	int frameDelay;
	SDL_Window* window;
	SDL_Renderer* renderer;
	ViewSize windowSize;
	FieldView* gameFieldView;
	FieldLogic* gameFieldLogic;

	SDL_Texture* lostMessageTextrue;
	SDL_Texture* wonMessageTextrue;
};

