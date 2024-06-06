#include "GameWindow.h"

GameWindow::GameWindow()
{
}

GameWindow::~GameWindow()
{
}

void GameWindow::Init(std::string title, int width, int height)
{
	this->window   = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 
		SDL_WINDOW_SHOWN);
	this->renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	this->gameFieldView = new GameFieldView(renderer);
	this->isRunning = true;
	this->width = width;
	this->height = height;
	this->leftPressed = false;
	this->rightPressed = false;
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

void GameWindow::MouseFieldPosition(int& mouseColumn, int& mouseRow, int cellSize)
{
	int mousePositionX, mousePositionY;
	SDL_GetMouseState(&mousePositionX, &mousePositionY);
	mouseColumn = mousePositionX / cellSize;
	mouseRow = mousePositionY / cellSize;
}

void GameWindow::DrawField(GameField* gameField)
{
	int cellSize = CellSize(gameField);
	int mouseColumn, mouseRow;
	MouseFieldPosition(mouseColumn, mouseRow, cellSize);
	gameFieldView->DrawField(gameField, cellSize, mouseColumn, mouseRow);
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

int GameWindow::CellSize(GameField* gameField)
{
	int columnCount = gameField->GetColumnCount(); 
	int rowCount = gameField->GetRowCount();
	return std::min(width / columnCount, height / rowCount);
}