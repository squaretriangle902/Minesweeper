#include <SDL.h>
#include <SDL_Image.h>
#include <SDL_ttf.h>
#include <string>
#include "FieldPosition.h"

SDL_Texture* LoadTexture(SDL_Renderer* renderer, const std::string& imagePath);
SDL_Rect RectangleAtCellPosition(FieldPosition cellPosition, int cellSize);