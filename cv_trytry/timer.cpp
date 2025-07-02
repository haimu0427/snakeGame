#define _CRT_SECURE_NO_WARNINGS 1
#include "head.h"
#include "timer.h"
#include <time.h>
#include <thread>

Timer::Timer(int fps) {
	this->frameTime = 100 / fps;

	beginTime = 0;
	endTime = 0;
	dt = 0;
}


void Timer::init() {
	beginTime = clock();
}

void Timer::update() {
	endTime = clock();
	dt = endTime - beginTime;
	if (dt < frameTime) {
		std::this_thread::sleep_for(std::chrono::milliseconds(frameTime - dt));
	}
}


