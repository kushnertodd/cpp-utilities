#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <exception>

using namespace std;
using namespace std::chrono;

class TimerException : public exception {
    virtual const char *what() const throw() {
        return "Timer not started";
    }
};

class Timer {
private:
    static const int nTimers = 30;
    high_resolution_clock::time_point start_time[nTimers];
    high_resolution_clock::time_point end_time[nTimers];
    bool started[nTimers];

public:
    Timer();

    void start(int timer = 0);

    void end(int timer = 0);

    double nanos(int timer = 0);

    double millis(int timer = 0);
};

#endif // TIMER_H
