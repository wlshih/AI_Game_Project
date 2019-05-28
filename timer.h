#include <ctime>

class Timer {
private:
	clock_t start;
	clock_t end;
	double limit;
	double elapsed;
public:
	Timer() {}
	Timer(int lim);
	void setTime(int lim);
	bool timeUp();
};
