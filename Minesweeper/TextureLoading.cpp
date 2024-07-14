#include "TextureLoading.h"

SDL_Texture* LoadTexture(SDL_Renderer* renderer, const std::string& imagePath)
{
	SDL_Surface* surface = IMG_Load(imagePath.c_str());
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	return texture;
}

SDL_Rect RectangleAtCellPosition(FieldPosition cellPosition, int cellSize)
{
	SDL_Rect rectangle = SDL_Rect();
	rectangle.w = cellSize;
	rectangle.h = cellSize;
	rectangle.x = cellPosition.column * cellSize;
	rectangle.y = cellPosition.row * cellSize;
	return rectangle;
}
