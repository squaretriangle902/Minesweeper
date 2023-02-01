#pragma once
#include "Controller.h"

class View;

class Model
{
public:
	Model(View* view);
	~Model();

private:
	View* view;
};

