#include "CellView.h"

void CellView::Render(SDL_Rect* rectangle, const CellLogic* cell)
{
	RenderCell(rectangle, cell);
	RenderHover(rectangle, cell);
}

void CellView::RenderOpenedCell(SDL_Rect* rectangle, const CellLogic* cell)
{
	SDL_RenderCopy(renderer, openedCellTexture, nullptr, rectangle);
	if (cell->HasBomb())
	{
		SDL_RenderCopy(renderer, bomb, nullptr, rectangle);
		return;
	}
	if (this->nearBombCount > 0)
	{
		RenderBombCount(rectangle);
	}
}

void CellView::RenderCell(SDL_Rect* rectangle, const CellLogic* cell)
{
	if (!cell->IsOpened())
	{
		RenderClosedCell(rectangle, cell);
		return;
	}
	RenderOpenedCell(rectangle, cell);
}

void CellView::RenderClosedCell(SDL_Rect* rectangle, const CellLogic* cell)
{
	SDL_RenderCopy(renderer, closedCellTexture, nullptr, rectangle);
	if (cell->HasFlag())
	{
		SDL_RenderCopy(renderer, flag, nullptr, rectangle);
	}
}

void CellView::RenderHover(SDL_Rect* rectangle, const CellLogic* cell)
{
	if (isHover)
	{
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 128);
		SDL_RenderFillRect(renderer, rectangle);
	}
}

void CellView::RenderBombCount(SDL_Rect* rectangle)
{
	switch (this->nearBombCount)
	{
	case 1:
		SDL_RenderCopy(renderer, one, nullptr, rectangle);
		return;
	case 2:
		SDL_RenderCopy(renderer, two, nullptr, rectangle);
		return;
	case 3:
		SDL_RenderCopy(renderer, three, nullptr, rectangle);
		return;
	case 4:
		SDL_RenderCopy(renderer, four, nullptr, rectangle);
		return;
	case 5:
		SDL_RenderCopy(renderer, five, nullptr, rectangle);
		return;
	case 6:
		SDL_RenderCopy(renderer, six, nullptr, rectangle);
		return;
	case 7:
		SDL_RenderCopy(renderer, seven, nullptr, rectangle);
		return;
	case 8:
		SDL_RenderCopy(renderer, eight, nullptr, rectangle);
		return;
	default:
		return;
	}
}

void CellView::SetNearBombCount(int nearBombCount)
{
	this->nearBombCount = nearBombCount;
}

void CellView::SetIsHover(bool isHover)
{
	this->isHover = isHover;
}

CellView::CellView(SDL_Renderer* renderer)
{
	this->renderer = renderer;
	this->tmpSurface = new SDL_Surface();
	this->isHover = false;
	this->nearBombCount = 0;
	this->closedCellTexture = LoadTexture(renderer, "images/closedCell.png");
	this->openedCellTexture = LoadTexture(renderer, "images/openedCell.png");
	this->one = LoadTexture(renderer, "images/one.png");
	this->two = LoadTexture(renderer, "images/two.png");
	this->three = LoadTexture(renderer, "images/three.png");
	this->four = LoadTexture(renderer, "images/four.png");
	this->five = LoadTexture(renderer, "images/five.png");
	this->six = LoadTexture(renderer, "images/six.png");
	this->seven = LoadTexture(renderer, "images/seven.png");
	this->eight = LoadTexture(renderer, "images/eight.png");
	this->flag = LoadTexture(renderer, "images/flag.png");
	this->bomb = LoadTexture(renderer, "images/bomb.png");
}

CellView::~CellView()
{
}
