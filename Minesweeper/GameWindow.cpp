#include "GameWindow.h"

GameWindow::GameWindow(const std::string& title, int width, int height, GameFieldLogic* gameField, int FPS)
{
	this->window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height,
		SDL_WINDOW_SHOWN);
	this->renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	this->gameFieldLogic = gameField;
	this->gameFieldView = new GameFieldView(gameField, renderer, width, height);
	this->width = width;
	this->height = height;
	this->isRunning = true;
	this->leftPressed = false;
	this->rightPressed = false;
	this->FPS = FPS;
}

GameWindow::~GameWindow()
{
	delete gameFieldView;
	delete gameFieldLogic;
}

void GameWindow::HandleEvents()
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
				HandleMouseBothButtonDown(event.button);
			}
			else
			{
				HandleMouseLeftButtonDown(event.button);
			}
			break;
		case SDL_BUTTON_RIGHT:
			this->rightPressed = true;
			if (this->leftPressed)
			{
				HandleMouseBothButtonDown(event.button);
			}
			else
			{
				HandleMouseRightButtonDown(event.button);
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

void GameWindow::DrawField(GameFieldLogic* gameField)
{
	int cellSize = gameFieldView->GetCellSize();
	int mouseColumn, mouseRow;
	MouseFieldPosition(mouseColumn, mouseRow, cellSize);
	gameFieldView->DrawField(mouseRow, mouseColumn);
}

void GameWindow::Render()
{
	SDL_RenderClear(renderer);
	DrawField(gameFieldLogic);
	SDL_RenderPresent(renderer);
}

void GameWindow::Clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void GameWindow::HandleMouseLeftButtonDown(SDL_MouseButtonEvent& b)
{
	int cellSize = CellSize(gameFieldLogic);
	gameFieldLogic->TryFloodOpen(b.y / cellSize, b.x / cellSize);
}

void GameWindow::HandleMouseBothButtonDown(SDL_MouseButtonEvent& b)
{
	int cellSize = CellSize(gameFieldLogic);
	gameFieldLogic->TryChord(b.y / cellSize, b.x / cellSize);
}

void GameWindow::HandleMouseRightButtonDown(SDL_MouseButtonEvent& b)
{
	int cellSize = CellSize(gameFieldLogic);
	gameFieldLogic->TrySwitchFlag(b.y / cellSize, b.x / cellSize);
}

void GameWindow::Run()
{
	const int frameDelay = 1000 / FPS;
	while (Running())
	{
		long long frameStart = SDL_GetTicks64();
		HandleEvents();
		Render();
		long long frameTime = SDL_GetTicks64() - frameStart;
		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}
}

bool GameWindow::Running()
{
	return isRunning;
}

int GameWindow::CellSize(GameFieldLogic* gameField)
{
	return std::min(height / gameField->GetRowCount(), width / gameField->GetColumnCount());
}