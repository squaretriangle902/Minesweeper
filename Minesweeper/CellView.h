#pragma once
#include <SDL.h>
#include <SDL_Image.h>
#include <SDL_ttf.h>
#include "CellLogic.h"
#include "TextureLoading.h"

class CellView
{
public:
	CellView(SDL_Renderer* renderer);
	~CellView();

	void Render(SDL_Rect* rectangle, const CellLogic* cell);
	void SetNearBombCount(int nearBombCount);
	void SetIsHover(bool isHover);

private:
	void RenderOpenedCell(SDL_Rect* rectangle, const CellLogic* cell);
	void RenderCell(SDL_Rect* rectangle, const CellLogic* cell);
	void RenderClosedCell(SDL_Rect* rectangle, const CellLogic* cell);
	void RenderHover(SDL_Rect* rectangle, const CellLogic* cell);
	void RenderBombCount(SDL_Rect* rectangle);

	int nearBombCount;
	bool isHover;
	SDL_Renderer* renderer; 
	SDL_Surface* tmpSurface;
	SDL_Texture* closedCellTexture;
	SDL_Texture* openedCellTexture;
	SDL_Texture* one;
	SDL_Texture* two;
	SDL_Texture* three;
	SDL_Texture* four;
	SDL_Texture* five;
	SDL_Texture* six;
	SDL_Texture* seven;
	SDL_Texture* eight;
	SDL_Texture* flag;
	SDL_Texture* bomb;

};