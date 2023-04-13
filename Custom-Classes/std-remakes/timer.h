#ifndef _TIMER
#define _TIMER

#include <iostream>
#include <chrono>
// using namespace std::literals::chrono_literals;

typedef std::chrono::high_resolution_clock::time_point chrono_time_point;
typedef std::chrono::duration<double> double_durr;
typedef void(*funcptr)(double_durr&);

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

 #endif