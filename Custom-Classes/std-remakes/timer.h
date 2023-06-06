#ifndef TIMER_
#define TIMER_

#include <iostream>
#include <chrono>
#include <functional>

#include "../globals.h"

COX_BEGIN_NAMESPACE

using chrono_time_point = std::chrono::high_resolution_clock::time_point;
using namespace std::literals::chrono_literals;

class Timer {
public:
    static std::function<void(std::chrono::duration<double>&)> DefaultLogFunction;

    Timer(Timer const&) = delete;
    Timer(Timer&&) = delete;

    Timer(std::function<void(std::chrono::duration<double>&)> loggingFunction = DefaultLogFunction, bool startImmediately = true)
        : loggingFunction{ loggingFunction }, duration { std::chrono::duration<double>() }, startImmediately { startImmediately }
    {
        if(!startImmediately)
            start = std::chrono::high_resolution_clock::now();
    }

    void Start()
    {
        if (startImmediately || started)
            return;

        started = true;
        start = std::chrono::high_resolution_clock::now();
    }

    void Stop()
    {
        if (startImmediately || !started)
            return;

        end = std::chrono::high_resolution_clock::now();
        duration = end - start;
        started = false;

        loggingFunction(duration);
    }
    
    ~Timer()
    {
        if (!startImmediately)
            return;

        end = std::chrono::high_resolution_clock::now();
        duration = end - start;
        
        loggingFunction(duration);
    }

private:
    chrono_time_point start, end;
    bool started = false;
    std::chrono::duration<double> duration;
    std::function<void(std::chrono::duration<double>&)> loggingFunction;
    bool startImmediately;
};

std::function<void(std::chrono::duration<double>&)> Timer::DefaultLogFunction = [](std::chrono::duration<double>& duration) {
    
    std::cout << duration.count() / (1ms).count() << "ms\n";
};

COX_END_NAMESPACE

 #endif