#include "Random.h"

int RandomInt(int lowerBound, int upperBound)
{
	return rand() % (upperBound - lowerBound + 1) + lowerBound;
}
