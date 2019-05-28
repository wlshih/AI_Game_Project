#include <ctime>

class Timer {
private:
	clock_t start;
	clock_t end;
	double limit;
	double elapsed;
public:
	Timer() {}
	Timer(double lim);
	void setTime(double lim);
	bool timeUp();
	double getElapsed();
};
