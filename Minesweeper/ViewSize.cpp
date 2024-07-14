#include "ViewSize.h"

ViewSize::ViewSize()
{
	width = 0;
	height = 0;
}

ViewSize::ViewSize(int width, int height)
{
	this->height = height;
	this->width = width;
}

ViewSize::ViewSize(const ViewSize& viewSize)
{
	this->width = viewSize.width;
	this->height = viewSize.height;
}

ViewSize& ViewSize::operator=(const ViewSize& viewSize)
{
	this->width = viewSize.width;
	this->height = viewSize.height;
	return *this;
}
