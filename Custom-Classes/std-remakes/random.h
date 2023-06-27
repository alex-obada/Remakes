#ifndef RANDOM_H
#define RANDOM_H

#include <random>

#include "../globals.h"

_COX_BEGIN

class Random {
public:
    Random(Random const& r) = delete;
    Random& operator = (Random const& r) = delete;

    static uint32_t Get(uint32_t max = 2e9)
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

_COX_END

#endif // RANDOM_H
