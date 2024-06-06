#pragma once
#include <SDL.h>
#include <SDL_Image.h>
#include <SDL_ttf.h>
#include "Cell.h"
#include "TextureLoading.h"
#include "CellView.h"
#include "GameField.h"

class GameField;

class GameFieldView
{
public:
	GameFieldView(SDL_Renderer* renderer);
	~GameFieldView();

	void DrawField(GameField* gameField, int cellSize, int mouseColumn, int mouseRow);
private:
	SDL_Renderer* renderer;
	CellView* cellView;
};


