#include "PositionConvert.h"

CellPosition Convert(WindowPosition windowPosition, int cellSize)
{
    return CellPosition(windowPosition.y / cellSize, windowPosition.x / cellSize);
}
