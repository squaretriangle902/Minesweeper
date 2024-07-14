#include "ViewPosition.h"

ViewPosition::ViewPosition()
{
	x = 0;
	y = 0;
}

ViewPosition::ViewPosition(int x, int y)
{
	this->x = x;
	this->y = y;
}

ViewPosition::ViewPosition(const ViewPosition& windowPosition)
{
	this->x = windowPosition.x;
	this->y = windowPosition.y;
}
