#include "timer.hpp"
#include <ctime>

void Timer::start() {
    clock_gettime(CLOCK_MONOTONIC, &startTime);
}

double Timer::elapsedMs() const {
    timespec now{};
    clock_gettime(CLOCK_MONOTONIC, &now);

    long sec = now.tv_sec - startTime.tv_sec;
    long nsec = now.tv_nsec - startTime.tv_nsec;
    double ms = sec * 1000.0 + nsec / 1e6;
    return ms;
}

double Timer::elapsedSeconds() const {
    return elapsedMs() / 1000.0;
}
