#pragma once
#include <SDL.h>
#include <SDL_Image.h>
#include <SDL_ttf.h>
#include "CellLogic.h"
#include "TextureLoading.h"
#include "CellView.h"
#include "FieldLogic.h"
#include "ViewSize.h"
#include "FieldPosition.h"

class FieldLogic;

class FieldView
{
public:
	FieldView(FieldLogic* gameField, SDL_Renderer* renderer, ViewSize fieldSize);
	~FieldView();

	int GetCellSize() const;
	void RenderField(FieldPosition mouseCellPosition);
	void SetRenderer(SDL_Renderer* renderer);
private:
	int CellSize();
	bool IsHiglighted(FieldPosition mouseCellPosition, FieldPosition cellPosition);

	SDL_Renderer* renderer;
	CellView* cellView;
	FieldLogic* gameFieldLogic;
	ViewSize fieldSize;
	int cellSize;
};


