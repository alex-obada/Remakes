#include <iostream>

#include "std-remakes/random.h"
#include "std-remakes/list.h"
#include "std-remakes/string.h"
#include "std-remakes/timer.h"
#include "std-remakes/uniqptr.h"

using namespace cox;

void TestRandom();
void TestList();
void TestTimer();

int main()
{
    TestTimer();
    return 0;
}

void TestTimer()
{
    Timer t(Timer::DefaultLogFunction, false);

    t.Start();
    for (int i = 1; i <= 1e9; ++i);
    t.Stop();
    t.Start();
    for (int i = 1; i <= 1e9; ++i);
    t.Stop();
    t.Start();
    for (int i = 1; i <= 1e9; ++i);
    t.Stop();

}

void TestList()
{
    List<int> l;
    l.emplace_back(2);
}

void TestRandom()
{
    int i = 100;
    while (i--)
        std::cout << Random::Get() << '\n';
}
