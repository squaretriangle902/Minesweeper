#include "PositionConvert.h"

FieldPosition Convert(ViewPosition windowPosition, int cellSize)
{
    return FieldPosition(windowPosition.y / cellSize, windowPosition.x / cellSize);
}
