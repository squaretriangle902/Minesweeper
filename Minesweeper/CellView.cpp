#include "CellView.h"

void CellView::DrawCell(SDL_Rect* rectangle, Cell* cell, bool highlighted, int bombCount)
{
	if (!cell->IsOpened())
	{
		SDL_RenderCopy(renderer, closedCellTexture, NULL, rectangle);
	}
	if (cell->HasFlag())
	{
		SDL_RenderCopy(renderer, flaggedCellTexture, NULL, rectangle);
	}
	if (cell->IsOpened() && !cell->HasBomb())
	{
		DrawBombCount(rectangle, cell, bombCount);
	}
	if (cell->IsOpened() && cell->HasBomb())
	{
		SDL_RenderCopy(renderer, explodedCellTexture, NULL, rectangle);
	}
	if (highlighted)
	{
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 128);
		SDL_RenderFillRect(renderer, rectangle);
	}
}

void CellView::DrawBombCount(SDL_Rect* rectangle, Cell* cell, int bombCount)
{
	switch (bombCount)
	{
	case 0:
		SDL_RenderCopy(renderer, openedCellTexture_0, NULL, rectangle);
		break;
	case 1:
		SDL_RenderCopy(renderer, openedCellTexture_1, NULL, rectangle);
		break;
	case 2:
		SDL_RenderCopy(renderer, openedCellTexture_2, NULL, rectangle);
		break;
	case 3:
		SDL_RenderCopy(renderer, openedCellTexture_3, NULL, rectangle);
		break;
	case 4:
		SDL_RenderCopy(renderer, openedCellTexture_4, NULL, rectangle);
		break;
	case 5:
		SDL_RenderCopy(renderer, openedCellTexture_5, NULL, rectangle);
		break;
	case 6:
		SDL_RenderCopy(renderer, openedCellTexture_6, NULL, rectangle);
		break;
	case 7:
		SDL_RenderCopy(renderer, openedCellTexture_7, NULL, rectangle);
		break;
	case 8:
		SDL_RenderCopy(renderer, openedCellTexture_8, NULL, rectangle);
		break;
	default:
		break;
	}
}

CellView::CellView(SDL_Renderer* renderer)
{
	this->renderer            = renderer;
	this->tmpSurface          = tmpSurface;
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
