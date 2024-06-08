#include "Timer.h"

Timer::Timer(const std::string& name)
{
	this->name = name;
	this->startTime = clock();
}

Timer::~Timer()
{
	this->endTime = clock();
	std::cout << name << "; time elapsed: " << (endTime - startTime) << "\n";
}
