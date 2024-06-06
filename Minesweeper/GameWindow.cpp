#include "GameWindow.h"

SDL_Texture* openedCellTexture_0;
SDL_Texture* openedCellTexture_1;
SDL_Texture* openedCellTexture_2;
SDL_Texture* openedCellTexture_3;
SDL_Texture* openedCellTexture_4;
SDL_Texture* openedCellTexture_5;
SDL_Texture* openedCellTexture_6;
SDL_Texture* openedCellTexture_7;
SDL_Texture* openedCellTexture_8;
SDL_Texture* flaggedCellTexture;
SDL_Texture* explodedCellTexture;
SDL_Texture* closedCellTexture;

GameWindow::GameWindow()
{
}

GameWindow::~GameWindow()
{
}

void GameWindow::Init(const char* title, int xPosition, int yPosition, int width, int height, bool fullscreen)
{
	this->window = SDL_CreateWindow(title, xPosition, yPosition, width, height, SDL_WINDOW_SHOWN);
	this->renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	this->isRunning = true;

	this->width = width;
	this->height = height;

	this->leftPressed = false;
	this->rightPressed = false;

	SDL_Surface* tmpSurface = new SDL_Surface();

	flaggedCellTexture  = LoadTexture(tmpSurface, "images/flaggedCell.png");
	explodedCellTexture	= LoadTexture(tmpSurface, "images/explodedCell.png");
	closedCellTexture 	= LoadTexture(tmpSurface, "images/closedCell.png");
	openedCellTexture_0	= LoadTexture(tmpSurface, "images/openedCell_0.png");
	openedCellTexture_1	= LoadTexture(tmpSurface, "images/openedCell_1.png");
	openedCellTexture_2	= LoadTexture(tmpSurface, "images/openedCell_2.png");
	openedCellTexture_3	= LoadTexture(tmpSurface, "images/openedCell_3.png");
	openedCellTexture_4	= LoadTexture(tmpSurface, "images/openedCell_4.png");
	openedCellTexture_5	= LoadTexture(tmpSurface, "images/openedCell_5.png");
	openedCellTexture_6	= LoadTexture(tmpSurface, "images/openedCell_6.png");
	openedCellTexture_7	= LoadTexture(tmpSurface, "images/openedCell_7.png");
	openedCellTexture_8	= LoadTexture(tmpSurface, "images/openedCell_8.png");

	delete tmpSurface;
}

void GameWindow::HandleEvents(GameField* gameField)
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_MOUSEBUTTONDOWN:
		switch (event.button.button)
		{
		case SDL_BUTTON_LEFT:
			this->leftPressed = true;
			if (this->rightPressed)
			{
				HandleMouseBothButtonDown(event.button, gameField);
			}
			else
			{
				HandleMouseLeftButtonDown(event.button, gameField);
			}
			break;
		case SDL_BUTTON_RIGHT:
			this->rightPressed = true;
			if (this->leftPressed)
			{
				HandleMouseBothButtonDown(event.button, gameField);
			}
			else
			{
				HandleMouseRightButtonDown(event.button, gameField);
			}
			break;
		default:
			break;
		}
		break;
	case SDL_MOUSEBUTTONUP:
		switch (event.button.button)
		{
		case SDL_BUTTON_LEFT:
			this->leftPressed = false;
			break;
		case SDL_BUTTON_RIGHT:
			this->rightPressed = false;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void GameWindow::ChangeRenderRectangle(SDL_Rect* rectangle, int cellSize, int cellColumn, int cellRow)
{
	rectangle->w = cellSize;
	rectangle->h = cellSize;
	rectangle->x = cellColumn * cellSize;
	rectangle->y = cellRow * cellSize;
}

SDL_Texture* GameWindow::LoadTexture(SDL_Surface* surface, const char* imagePath)
{
	surface = IMG_Load(imagePath);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	return texture;
}

void GameWindow::DrawField(GameField* gameField)
{
	int cellSize = CellSize(gameField);
	int mousePositionX, mousePositioY;
	SDL_GetMouseState(&mousePositionX, &mousePositioY);

	bool isHighlited = false;
	SDL_Rect* rectangle = new SDL_Rect;

	for (int column = 0; column < gameField->GetColumnCount(); column++)
	{
		for (int row = 0; row < gameField->GetRowCount(); row++)
		{
			ChangeRenderRectangle(rectangle, cellSize, column, row);
			isHighlited = mousePositionX / cellSize == column && mousePositioY / cellSize == row;
			DrawCell(rectangle, gameField->GetCell(column, row), isHighlited, gameField->CellNearBombsCount(column, row));
		}
	}

	delete rectangle;
}

void GameWindow::Render(GameField* gameField)
{
	SDL_RenderClear(renderer);
	DrawField(gameField);
	SDL_RenderPresent(renderer);
}

void GameWindow::Clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void GameWindow::HandleMouseLeftButtonDown(SDL_MouseButtonEvent& b, GameField* gameField)
{
	int cellSize = CellSize(gameField);
	gameField->FloodOpen(b.x / cellSize, b.y / cellSize);
}

void GameWindow::HandleMouseBothButtonDown(SDL_MouseButtonEvent& b, GameField* gameField)
{
	int cellSize = CellSize(gameField);
	gameField->TryChord(b.x / cellSize, b.y / cellSize);
}

void GameWindow::HandleMouseRightButtonDown(SDL_MouseButtonEvent& b, GameField* gameField)
{
	int cellSize = CellSize(gameField);
	gameField->TrySwitchFlag(b.x / cellSize, b.y / cellSize);
}


bool GameWindow::Running()
{
	return isRunning;
}

void GameWindow::DrawCell(SDL_Rect* rectangle, const Cell* cell, bool highlighted, int bombCount) const
{
	if (!cell->IsOpened())
	{
		SDL_RenderCopy(renderer, closedCellTexture, NULL, rectangle);
	}
	if (cell->IsFlag())
	{
		SDL_RenderCopy(renderer, flaggedCellTexture, NULL, rectangle);
	}
	if (cell->IsOpened() && !cell->IsBomb())
	{
		DrawBombCount(rectangle, cell, bombCount);
	}
	if (cell->IsOpened() && cell->IsBomb())
	{
		SDL_RenderCopy(renderer, explodedCellTexture, NULL, rectangle);
	}
	if (highlighted)
	{
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 64);
		SDL_RenderFillRect(renderer, rectangle);
	}
}

void GameWindow::DrawBombCount(SDL_Rect* rectangle, const Cell* cell, int bombCount) const
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

int GameWindow::CellSize(GameField* gameField)
{
	int columnCount = gameField->GetColumnCount(), rowCount = gameField->GetRowCount();
	return Min(width / columnCount, height / rowCount);
}

int GameWindow::Min(int a, int b)
{
	return a < b ? a : b;
}
