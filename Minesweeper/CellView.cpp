#include "CellView.h"

void CellView::DrawCell(SDL_Rect* rectangle, const Cell* cell)
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
	this->tmpSurface          = new SDL_Surface();
	this->flaggedCellTexture  = LoadTexture(tmpSurface, renderer, "images/flaggedCell.png");
	this->explodedCellTexture = LoadTexture(tmpSurface, renderer, "images/explodedCell.png");
	this->closedCellTexture   = LoadTexture(tmpSurface, renderer, "images/closedCell.png");
	this->openedCellTexture_0 = LoadTexture(tmpSurface, renderer, "images/openedCell_0.png");
	this->openedCellTexture_1 = LoadTexture(tmpSurface, renderer, "images/openedCell_1.png");
	this->openedCellTexture_2 = LoadTexture(tmpSurface, renderer, "images/openedCell_2.png");
	this->openedCellTexture_3 = LoadTexture(tmpSurface, renderer, "images/openedCell_3.png");
	this->openedCellTexture_4 = LoadTexture(tmpSurface, renderer, "images/openedCell_4.png");
	this->openedCellTexture_5 = LoadTexture(tmpSurface, renderer, "images/openedCell_5.png");
	this->openedCellTexture_6 = LoadTexture(tmpSurface, renderer, "images/openedCell_6.png");
	this->openedCellTexture_7 = LoadTexture(tmpSurface, renderer, "images/openedCell_7.png");
	this->openedCellTexture_8 = LoadTexture(tmpSurface, renderer, "images/openedCell_8.png");
}

CellView::~CellView()
{
}
