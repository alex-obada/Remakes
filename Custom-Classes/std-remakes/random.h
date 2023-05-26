#ifndef RANDOM_H
#define RANDOM_H

#include <random>

#include "../globals.h"

COX_BEGIN_NAMESPACE

class Random {
public:
    Random(Random const& r) = delete;
    Random& operator = (Random const& r) = delete;

    static int Get(int max = (int)1e9)
    {
        if (instance == nullptr)
            instance = new Random();

        return instance->engine() % max;
    }

private:
    Random()
    {
        std::random_device rd;
        engine = std::mt19937(rd());
    };

    std::mt19937 engine;
    static Random* instance;
};

Random* Random::instance = nullptr;

COX_END_NAMESPACE

#endif // RANDOM_H
