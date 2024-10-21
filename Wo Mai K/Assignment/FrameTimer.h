#pragma once
#include <Windows.h>
#include <profileapi.h>

class FrameTimer
{
public:
	void init(int);
	int framesToUpdate();


private:
	LARGE_INTEGER timerFreq;
	LARGE_INTEGER timeNow;
	LARGE_INTEGER timePrevious;

	int requestedFPS;
	float intervalsPerFrame;
	float intervalsSinceLastUpdate;

};
