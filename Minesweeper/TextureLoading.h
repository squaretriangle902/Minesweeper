#include <SDL.h>
#include <SDL_Image.h>
#include <SDL_ttf.h>
#include <string>

SDL_Texture* LoadTexture(SDL_Surface* surface, SDL_Renderer* renderer, std::string imagePath);

SDL_Rect RectangleAtPosition(int row, int column, int cellSize);