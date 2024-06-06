#pragma once
#include <SDL.h>
#include <SDL_Image.h>
#include <SDL_ttf.h>
#include "Cell.h"
#include "TextureLoading.h"

class CellView
{
public:
	CellView(SDL_Renderer* renderer);
	~CellView();

	void DrawCell(SDL_Rect* rectangle, Cell* cell, bool highlighted, int bombCount);
	void DrawBombCount(SDL_Rect* rectangle, Cell* cell, int bombCount);

private:
	SDL_Renderer* renderer; 
	SDL_Surface* tmpSurface;
	SDL_Texture* flaggedCellTexture;
	SDL_Texture* explodedCellTexture;
	SDL_Texture* closedCellTexture;
	SDL_Texture * openedCellTexture_0;
	SDL_Texture * openedCellTexture_1;
	SDL_Texture * openedCellTexture_2;
	SDL_Texture * openedCellTexture_3;
	SDL_Texture * openedCellTexture_4;
	SDL_Texture * openedCellTexture_5;
	SDL_Texture * openedCellTexture_6;
	SDL_Texture * openedCellTexture_7;
	SDL_Texture * openedCellTexture_8;
};