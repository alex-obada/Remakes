#include <iostream>

#include "std-remakes/random.h"
#include "std-remakes/list.h"
#include "std-remakes/string.h"
#include "std-remakes/timer.h"
#include "std-remakes/uniqptr.h"
#include "std-remakes/vector.h"

using namespace cox;

void TestRandom();
void TestList();
void TestTimer();
void TestVector();

int main()
{
    TestList();
    return 0;
}

void TestVector()
{
    vector<int> a;
}

void TestTimer()
{
    Timer t(Timer::DefaultLogFunction, false);
    /*
    t.Start();
    for (int i = 1; i <= 1e9; ++i);
    t.Stop();
    t.Start();
    for (int i = 1; i <= 1e9; ++i);
    t.Stop();
    t.Start();
    for (int i = 1; i <= 1e9; ++i);
    t.Stop();

    */
}

void TestList()
{
    auto PrintList = []<typename T>(List<T>& list) {
        /*for (auto const& x : list)
            std::cout << x << ' ';
        std::cout << std::endl;*/

        for (auto it = list.cbegin(); it != list.cend(); ++it)
        {
            std::cout << *it << ' ';
        }
        std::cout << std::endl;

    };

    List<int> l;
    l.push_back(2);
    l.push_back(3);
    l.push_back(5);
    l.push_back(7);



    std::vector<int> a;
    auto b = a.begin();



    PrintList(l);












}

void TestRandom()
{
    int i = 100;
    while (i--)
        
        std::cout << Random::Get() << '\n';
}
