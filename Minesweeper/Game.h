#pragma once
#include "FieldLogic.h"

class Game
{
public:
	Game(FieldLogic* fieldLogic);
	~Game();
private:
	FieldLogic* fieldLogic;
};

