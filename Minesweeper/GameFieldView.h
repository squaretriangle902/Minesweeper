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
	GameFieldView(GameField* gameField, SDL_Renderer* renderer, int width, int height);
	~GameFieldView();

	int GetCellSize() const;
	void DrawField(int mouseColumn, int mouseRow) const;
private:
	int CellSize(GameField* gameField);

	SDL_Renderer* renderer;
	CellView* cellView;
	GameField* gameField;
	int cellSize;
	int width;
	int height;
};


