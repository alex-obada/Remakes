#include <iostream>

#include "globals.h"
#include "std-remakes/random.h"
using namespace cox;

void TestRandom();

int main()
{
    TestRandom();
}

void TestRandom()
{
    int i = 100;
    while (i--)
        std::cout << Random::Get() << '\n';
}
