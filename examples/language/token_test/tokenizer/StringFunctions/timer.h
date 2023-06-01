#pragma once
#include <chrono>
#include <ctime>

// https://en.cppreference.com/w/cpp/chrono/c/clock
// https://en.cppreference.com/w/c/chrono/clock_t
// https://en.cppreference.com/w/cpp/chrono/high_resolution_clock
// https://en.cppreference.com/w/cpp/chrono/duration
// https://en.cppreference.com/w/cpp/chrono/time_point

enum {
  MSECS,
  SECS
}

class Timer {
private:
	std::clock_t c_start{};
	std::chrono::time_point<std::chrono::high_resolution_clock> t_start{};
public:
	Timer();
	// cpu seconds to execute
	double cpu_seconds_used();
	// wall clock milliseconds to execute
	double wall_clock_milliseconds_used();
};
