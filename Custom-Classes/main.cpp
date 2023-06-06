#include <iostream>

#include "globals.h"
#include "std-remakes/random.h"
#include "std-remakes/list.h"
using namespace cox;

void TestRandom();
void TestList();

int main()
{
    TestList();
    return 0;
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
