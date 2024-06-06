#include "CellView.h"

void CellView::DrawCell(SDL_Rect* rectangle, const Cell* cell/*, bool highlighted, int nearBombCount*/)
{
	if (!cell->IsOpened())
	{
		SDL_RenderCopy(renderer, closedCellTexture, nullptr, rectangle);
	}
	if (cell->HasFlag())
	{
		SDL_RenderCopy(renderer, flaggedCellTexture, nullptr, rectangle);
	}
	if (cell->IsOpened() && !cell->HasBomb())
	{
		DrawBombCount(rectangle, nearBombCount);
	}
	if (cell->IsOpened() && cell->HasBomb())
	{
		SDL_RenderCopy(renderer, explodedCellTexture, nullptr, rectangle);
	}
	if (isHighlighted)
	{
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 128);
		SDL_RenderFillRect(renderer, rectangle);
	}
}

void CellView::DrawBombCount(SDL_Rect* rectangle, int bombCount)
{
	switch (bombCount)
	{
	case 0:
		SDL_RenderCopy(renderer, openedCellTexture_0, nullptr, rectangle);
		break;
	case 1:
		SDL_RenderCopy(renderer, openedCellTexture_1, nullptr, rectangle);
		break;
	case 2:
		SDL_RenderCopy(renderer, openedCellTexture_2, nullptr, rectangle);
		break;
	case 3:
		SDL_RenderCopy(renderer, openedCellTexture_3, nullptr, rectangle);
		break;
	case 4:
		SDL_RenderCopy(renderer, openedCellTexture_4, nullptr, rectangle);
		break;
	case 5:
		SDL_RenderCopy(renderer, openedCellTexture_5, nullptr, rectangle);
		break;
	case 6:
		SDL_RenderCopy(renderer, openedCellTexture_6, nullptr, rectangle);
		break;
	case 7:
		SDL_RenderCopy(renderer, openedCellTexture_7, nullptr, rectangle);
		break;
	case 8:
		SDL_RenderCopy(renderer, openedCellTexture_8, nullptr, rectangle);
		break;
	default:
		break;
	}
}

void CellView::SetNearBombCount(int nearBombCount)
{
	this->nearBombCount = nearBombCount;
}

void CellView::SetIsHighlighted(bool isHighlighted)
{
	this->isHighlighted = isHighlighted;
}

CellView::CellView(SDL_Renderer* renderer)
{
	this->renderer            = renderer;
	this->tmpSurface          = tmpSurface;
	this->tmpSurface          = new SDL_Surface();
}

CellView::~CellView()
{
}
