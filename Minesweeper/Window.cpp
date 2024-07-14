#include "Window.h"

Window::Window(const std::string& title, ViewSize windowSize, FieldLogic* gameFieldLogic, int FPS)
{
	this->window = SDL_CreateWindow(
		title.c_str(), 
		SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED, 
		windowSize.width, 
		windowSize.height,
		SDL_WINDOW_SHOWN);
	this->renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	this->gameFieldLogic = gameFieldLogic;
	this->gameFieldView = new FieldView(gameFieldLogic, renderer, windowSize);
	this->windowSize = windowSize;
	this->isRunning = true;
	this->leftPressed = false;
	this->rightPressed = false;
	this->frameDelay = 1000 / FPS;

	this->lostMessageTextrue = LoadTexture(renderer, "images/lostMessage.png");
	this->wonMessageTextrue = LoadTexture(renderer, "images/wonMessage.png");
}

Window::~Window()
{
	delete gameFieldView;
	delete gameFieldLogic;
}

void Window::HandleEvents()
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

void Window::RenderField(FieldLogic* gameField)
{
	int cellSize = gameFieldView->GetCellSize();
	FieldPosition mouseFieldPosition = MouseFieldPosition(cellSize);
	gameFieldView->RenderField(mouseFieldPosition);
}

void Window::LostMessage()
{
	SDL_Rect rectangle = SDL_Rect();
	rectangle.w = 208;
	rectangle.h = 68;
	rectangle.x = (windowSize.width - rectangle.w) / 2;
	rectangle.y = (windowSize.height - rectangle.h) / 2;
	SDL_RenderCopy(renderer, this->lostMessageTextrue, nullptr, &rectangle);
}

void Window::WonMessage()
{
	SDL_Rect rectangle = SDL_Rect();
	rectangle.w = 170;
	rectangle.h = 68;
	rectangle.x = (windowSize.width - rectangle.w) / 2;
	rectangle.y = (windowSize.height - rectangle.h) / 2;
	SDL_RenderCopy(renderer, this->wonMessageTextrue, nullptr, &rectangle);
}

FieldPosition Window::MouseFieldPosition(int cellSize)
{
	int mousePositionX;
	int mousePositionY;
	SDL_GetMouseState(&mousePositionX, &mousePositionY);
	return FieldPosition(mousePositionY / cellSize, mousePositionX / cellSize);
}

void Window::Render()
{
	SDL_RenderClear(renderer);
	RenderField(gameFieldLogic);
	switch (gameFieldLogic->GetGameState())
	{
	case GameState::won:
		WonMessage();
		break;
	case GameState::lost:
		LostMessage();
		break;
	default:
		break;
	}
	SDL_RenderPresent(renderer);
}

void Window::Clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void Window::HandleMouseLeftButtonDown(SDL_MouseButtonEvent& b)
{
	FieldPosition fieldPosition = Convert(EventPosition(b), CellSize(gameFieldLogic));
	if (gameFieldLogic->GetGameState() != GameState::continues)
	{
		return;
	}
	gameFieldLogic->TryFloodOpen(fieldPosition);

}

void Window::HandleMouseBothButtonDown(SDL_MouseButtonEvent& b)
{
	FieldPosition fieldPosition = Convert(EventPosition(b), CellSize(gameFieldLogic));
	if (gameFieldLogic->GetGameState() != GameState::continues)
	{
		return;
	}
	gameFieldLogic->TryChord(fieldPosition);
}

void Window::HandleMouseRightButtonDown(SDL_MouseButtonEvent& b)
{
	FieldPosition fieldPosition = Convert(EventPosition(b), CellSize(gameFieldLogic));
	gameFieldLogic->TrySwitchFlag(fieldPosition);
}

void Window::SetGameFieldView(FieldView* gameFieldView)
{
	this->gameFieldView = gameFieldView;
	gameFieldView->SetRenderer(this->renderer);
}

void Window::Run()
{
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

bool Window::Running()
{
	return isRunning;
}

int Window::CellSize(FieldLogic* gameFieldLogic)
{
	return std::min(windowSize.height / gameFieldLogic->GetRowCount(), windowSize.width / gameFieldLogic->GetColumnCount());
}

ViewPosition Window::EventPosition(SDL_MouseButtonEvent& b)
{
	return ViewPosition(b.x, b.y);
}
