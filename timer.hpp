#ifndef TIMER_HPP
#define TIMER_HPP

#include <ctime>

class Timer {
public:
    void start();
    double elapsedMs() const;   // milliseconds
    double elapsedSeconds() const;

private:
    timespec startTime{};
};

#endif // TIMER_HPP
