#pragma once
#include <string>

struct ViewSize
{
public:
	ViewSize();
	ViewSize(int width, int height);
	ViewSize(const ViewSize& viewSize);

	ViewSize& operator=(const ViewSize& viewSize);

	int width;
	int height;
};

