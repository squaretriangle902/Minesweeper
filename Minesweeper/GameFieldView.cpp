#include "GameFieldView.h"

GameFieldView::GameFieldView(SDL_Renderer* renderer)
{
	this->renderer = renderer;
	this->cellView = new CellView(renderer);
}

void GameFieldView::DrawField(GameField* gameField, int cellSize, int mouseColumn, int mouseRow)
{
	for (int column = 0; column < gameField->GetColumnCount(); column++)
	{
		for (int row = 0; row < gameField->GetRowCount(); row++)
		{
			SDL_Rect* rectangle = RectangleAtPosition(column, row, cellSize);
			bool isHighlited = mouseColumn == column && mouseRow == row;
			cellView->DrawCell(rectangle, gameField->GetCell(column, row), isHighlited, gameField->CellNearBombsCount(column, row));
			delete rectangle;
		}
	}
}
