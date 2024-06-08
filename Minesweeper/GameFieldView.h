#pragma once
#include <SDL.h>
#include <SDL_Image.h>
#include <SDL_ttf.h>
#include "Cell.h"
#include "TextureLoading.h"
#include "CellView.h"
#include "GameFieldLogic.h"

class GameFieldLogic;

class GameFieldView
{
public:
	GameFieldView(GameFieldLogic* gameField, SDL_Renderer* renderer, int width, int height);
	~GameFieldView();

	int GetCellSize() const;
	void DrawField(int mouseRow, int mouseColumn);
private:
	int CellSize(GameFieldLogic* gameField);

	SDL_Renderer* renderer;
	CellView* cellView;
	GameFieldLogic* gameField;
	int cellSize;
	int width;
	int height;
};


