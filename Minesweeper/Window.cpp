#include "Window.h"

Window::Window()
{
	window = nullptr;
	renderer = nullptr;
	isRunning = false;
}

Window::~Window()
{
}

void Window::Init(const char* title, int xPosition, int yPosition, int width, int height)
{
	this->window = SDL_CreateWindow(title, xPosition, yPosition, width, height, SDL_WINDOW_SHOWN);
	this->renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	this->isRunning = true;
	this->width = width;
	this->height = height;
}

SDL_Texture* Window::LoadTexture(const char* imageSource)
{
	SDL_Surface* tmpSurface = IMG_Load(imageSource);
	SDL_Texture* image = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	return image;
}

//void Window::DrawCell(Cell* cell, SDL_Rect* rectangle, int bombCount)
//{
//	if (cell->IsOpened())
//	{
//		SDL_RenderCopy(renderer, LoadTexture("images/openedCell.png"), NULL, rectangle);
//		if (cell->IsBomb())
//		{
//			SDL_RenderCopy(renderer, LoadTexture("images/bombedCell.png"), NULL, rectangle);
//		}
//		switch (bombCount)
//		{
//		default:
//			break;
//		}
//		return;
//	}
//	SDL_RenderCopy(renderer, closedCellTexture, NULL, rectangle);
//}

//void Window::DrawCell(Cell* cell, SDL_Rect* rectangle, SDL_Texture* closedCellTexture, SDL_Texture* openedCellTexture)
//{
//	if (cell->IsOpened())
//	{
//		SDL_RenderCopy(renderer, openedCellTexture, NULL, rectangle);
//		if (cell->IsBomb())
//		{
//			//SDL_RenderCopy(renderer, bombTexture, NULL, rectangle);
//		}
//		switch (bombCount)
//		{
//		default:
//			break;
//		}
//		return;
//	}
//	SDL_RenderCopy(renderer, closedCellTexture, NULL, rectangle);
//
//}
//
//void Window::DrawCell(Cell* cell, SDL_Rect* rectangle, int bombCount)
//{
//}
//
//void Window::DrawBomb(Cell* cell, SDL_Rect* rectangle, SDL_Texture* bombTexture)
//{
//	SDL_RenderCopy(renderer, bombTexture, NULL, rectangle);
//}
//
//void Window::DrawCell(int size, int x, int y, bool opened, bool flagged, bool bomb, bool highlighted, int bombCount)
//{
//	SDL_Rect rectangle;
//	rectangle.w = size;
//	rectangle.h = size;
//	rectangle.x = x;
//	rectangle.y = y;
//	if (!opened)
//	{
//		SDL_RenderCopy(renderer, closedCellTexture, NULL, &rectangle);
//	}
//	if (opened && !bomb)
//	{
//		switch (bombCount)
//		{
//		case 0:
//			SDL_RenderCopy(renderer, openedCellTexture_0, NULL, &rectangle);
//			break;
//		case 1:
//			SDL_RenderCopy(renderer, openedCellTexture_1, NULL, &rectangle);
//			break;
//		case 2:
//			SDL_RenderCopy(renderer, openedCellTexture_2, NULL, &rectangle);
//			break;
//		case 3:
//			SDL_RenderCopy(renderer, openedCellTexture_3, NULL, &rectangle);
//			break;
//		case 4:
//			SDL_RenderCopy(renderer, openedCellTexture_4, NULL, &rectangle);
//			break;
//		case 5:
//			SDL_RenderCopy(renderer, openedCellTexture_5, NULL, &rectangle);
//			break;
//		case 6:
//			SDL_RenderCopy(renderer, openedCellTexture_6, NULL, &rectangle);
//			break;
//		case 7:
//			SDL_RenderCopy(renderer, openedCellTexture_7, NULL, &rectangle);
//			break;
//		case 8:
//			SDL_RenderCopy(renderer, openedCellTexture_8, NULL, &rectangle);
//			break;
//		default:
//			break;
//		}
//	}
//	if (flagged)
//	{
//		SDL_RenderCopy(renderer, flaggedCellTexture, NULL, &rectangle);
//	}
//	if (opened && bomb)
//	{
//		SDL_RenderCopy(renderer, explodedCellTexture, NULL, &rectangle);
//	}
//	if (highlighted)
//	{
//		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
//		SDL_RenderDrawRect(renderer, &rectangle);
//		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//	}
//}
