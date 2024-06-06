#include "TextureLoading.h"

SDL_Texture* LoadTexture(SDL_Surface* surface, SDL_Renderer* renderer, std::string imagePath)
{
	surface = IMG_Load(imagePath.c_str());
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	return texture;
}

SDL_Rect* RectangleAtPosition(int column, int row, int cellSize)
{
	SDL_Rect* rectangle = new SDL_Rect();
	rectangle->w = cellSize;
	rectangle->h = cellSize;
	rectangle->x = column * cellSize;
	rectangle->y = row * cellSize;
	return rectangle;
}
