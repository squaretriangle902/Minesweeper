#include "GameFieldView.h"

GameFieldView::GameFieldView(GameField* gameField, SDL_Renderer* renderer, int width, int height)
{
	this->renderer = renderer;
	this->cellView = new CellView(renderer);
	this->width = width;
	this->height = height;
	this->cellSize = CellSize(gameField);
	this->gameField = gameField;
}

int GameFieldView::GetCellSize() const
{
	return this->cellSize;
}

void GameFieldView::DrawField(int mouseColumn, int mouseRow) const
{
	for (int column = 0; column < gameField->GetColumnCount(); column++)
	{
		for (int row = 0; row < gameField->GetRowCount(); row++)
		{
			cellView->SetIsHighlighted(mouseColumn == column && mouseRow == row);
			cellView->SetNearBombCount(gameField->CellNearBombsCount(row, column));
			SDL_Rect rectangle = RectangleAtPosition(row, column, cellSize);
			cellView->DrawCell(&rectangle, gameField->GetCell(row, column));
		}
	}
}

int GameFieldView::CellSize(GameField* gameField)
{
	return std::min(width / gameField->GetColumnCount(), height / gameField->GetRowCount());
}