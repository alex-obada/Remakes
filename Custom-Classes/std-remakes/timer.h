#ifndef TIMER_
#define TIMER_

#include <iostream>
#include <chrono>
#include <string>

#include "../globals.h"

_COX_BEGIN

class Timer {
public:
    Timer()
    {
        Reset();
    }

    void Reset()
    {
        start = std::chrono::high_resolution_clock::now();
    }

    double Elapsed()
    {
        return std::chrono::duration_cast<std::chrono::nanoseconds>
            (std::chrono::high_resolution_clock::now() - start)
            .count() * 0.001 * 0.001 * 0.001;
    }

    double ElapsedMs()
    {
        return Elapsed() * 1000.0;
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
};


class ScopedTimer {
public:
    ScopedTimer(std::string const& name, std::ostream* stream = &std::cout)
        : name{ name }, stream{ stream } {}

    ~ScopedTimer()
    {
        double time = timer.ElapsedMs();
        *stream << "[TIMER] " << name << " - " << time << " ms\n";
    }

private:
    std::string name;
    std::ostream* stream;
    Timer timer;
};

_COX_END

 #endif