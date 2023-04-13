#ifndef RANDOM_H
#define RANDOM_H

#include <cstdlib>
#include <time.h>
#include <cmath>

class Random {
public:
    Random(Random const& r) = delete;
    Random& operator = (Random const& r) = delete;

    static int Get(int max = (int)1e9)
    {
        if (instance == nullptr)
            instance = new Random();
        return abs(rand() % max);
    }

private:
    Random()
    {
        srand(time(NULL));
    };

    static Random* instance;
};

Random* Random::instance = nullptr;

#endif // RANDOM_H
