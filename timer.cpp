#include "timer.h"

Timer::Timer(int lim) {
	setTime(lim);
}
void Timer::setTime(int lim) {
	start = clock();
	limit = lim;
}

bool Timer::timeUp() {
	end = clock();
	elapsed = (double)(end - start) / CLOCKS_PER_SEC;
	return (elapsed > limit);
}


