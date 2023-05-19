#include "timer.h"
Timer::Timer() :
	c_start(std::clock()),
	t_start(std::chrono::high_resolution_clock::now())
{}

// cpu seconds to execute
double Timer::cpu_seconds_used()
{
	clock_t c_end = clock();
	return  ((double)(c_end - c_start)) / CLOCKS_PER_SEC;
}
// wall clock milliseconds to execute
double Timer::wall_clock_milliseconds_used()
{
	std::chrono::time_point<std::chrono::high_resolution_clock> t_end =
		std::chrono::high_resolution_clock::now();
	return std::chrono::duration<double, std::milli>(t_end - t_start).count();
}
