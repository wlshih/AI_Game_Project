#include "timer.h"

Timer::Timer(double lim) {
	setTime(lim);
}
void Timer::setTime(double lim) {
	start = clock();
	limit = lim;
}

bool Timer::timeUp() {
	end = clock();
	elapsed = (double)(end - start) / CLOCKS_PER_SEC;
	return (elapsed > limit);
}

double Timer::getElapsed() {
	return this->elapsed;
}
