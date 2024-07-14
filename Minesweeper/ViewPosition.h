#pragma once

struct ViewPosition
{
public:
	ViewPosition();
	ViewPosition(int x, int y);
	ViewPosition(const ViewPosition& windowPosition);

	int x;
	int y;
};

