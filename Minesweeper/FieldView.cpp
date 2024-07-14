#include "FieldView.h"

FieldView::FieldView(FieldLogic* gameFieldLogic, SDL_Renderer* renderer, ViewSize fieldSize)
{
	this->renderer = renderer;
	this->cellView = new CellView(renderer);
	this->gameFieldLogic = gameFieldLogic;
	this->fieldSize = fieldSize;
	this->cellSize = CellSize();
}

FieldView::~FieldView()
{
	delete cellView;
}

int FieldView::GetCellSize() const
{
	return this->cellSize;
}

void FieldView::RenderField(FieldPosition mouseFieldPosition)
{
	for (int column = 0; column < gameFieldLogic->GetColumnCount(); column++)
	{
		for (int row = 0; row < gameFieldLogic->GetRowCount(); row++)
		{
			FieldPosition cellFieldPosition = FieldPosition(row, column);
			cellView->SetIsHover(IsHiglighted(cellFieldPosition, mouseFieldPosition));
			cellView->SetNearBombCount(gameFieldLogic->CellNearBombsCount(cellFieldPosition));
			SDL_Rect rectangle = RectangleAtCellPosition(cellFieldPosition, cellSize);
			cellView->Render(&rectangle, gameFieldLogic->GetCell(cellFieldPosition));
		}
	}
}

void FieldView::SetRenderer(SDL_Renderer* renderer)
{
	this->renderer = renderer;
}

int FieldView::CellSize()
{
	return std::min(fieldSize.width / gameFieldLogic->GetColumnCount(), fieldSize.height / gameFieldLogic->GetRowCount());
}

bool FieldView::IsHiglighted(FieldPosition mouseCellPosition, FieldPosition cellPosition)
{
	return 
		mouseCellPosition.column == cellPosition.column && 
		mouseCellPosition.row == cellPosition.row;
}
