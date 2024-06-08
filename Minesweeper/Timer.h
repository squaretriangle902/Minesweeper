#pragma once
#include<string>
#include<iostream>
#include<ctime>

class Timer
{
public:
	Timer(const std::string& name);
	~Timer();
private:
	int startTime;
	int endTime;
	std::string name;
};

