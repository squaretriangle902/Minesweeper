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

	void DrawCell(SDL_Rect* rectangle, const Cell* cell/*, bool isHighlighted, int nearBombCount*/ );
	void DrawBombCount(SDL_Rect* rectangle, int bombCount);

	void SetNearBombCount(int nearBombCount);
	void SetIsHighlighted(bool isHighlighted);

private:
	int nearBombCount;
	bool isHighlighted;
	SDL_Renderer* renderer; 
	SDL_Surface* tmpSurface;
	SDL_Texture* const flaggedCellTexture;
	SDL_Texture* const explodedCellTexture;
	SDL_Texture* const closedCellTexture;
	SDL_Texture* const openedCellTexture_0;
	SDL_Texture* const openedCellTexture_1;
	SDL_Texture* const openedCellTexture_2;
	SDL_Texture* const openedCellTexture_3;
	SDL_Texture* const openedCellTexture_4;
	SDL_Texture* const openedCellTexture_5;
	SDL_Texture* const openedCellTexture_6;
	SDL_Texture* const openedCellTexture_7;
	SDL_Texture* const openedCellTexture_8;
};