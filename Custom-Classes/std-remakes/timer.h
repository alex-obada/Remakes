#ifndef TIMER_
#define TIMER_

#include <iostream>
#include <chrono>

#include "../globals.h"

COX_BEGIN_NAMESPACE

// using namespace std::literals::chrono_literals;

using chrono_time_point = std::chrono::high_resolution_clock::time_point;
using double_durr       = std::chrono::duration<double>;
using funcptr           = void(*)(double_durr&);

void LogTime(double_durr& duration) 
{ 
    std::cout << duration.count() << "s\n";
}

struct Timer {
    chrono_time_point start, end;
    double_durr duration;
    funcptr function;
 
    Timer(funcptr func = LogTime) : function{func}
    { 
        start = std::chrono::high_resolution_clock::now(); 
    }

    ~Timer()
    {
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;
        
        function(duration);
    }

};

COX_END_NAMESPACE

 #endif