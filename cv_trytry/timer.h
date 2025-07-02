#define _CRT_SECURE_NO_WARNINGS 1
#pragma once

#include <time.h>

/*
	稳定帧率用的计时器
*/
class Timer {
public:
	long frameTime;

	Timer(int fps);

	void init();

	void update();

private:
	long beginTime, endTime, dt;

};


