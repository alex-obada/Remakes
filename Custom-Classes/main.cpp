#include <iostream>

#include "std-remakes/random.h"
#include "std-remakes/list.h"
#include "std-remakes/string.h"
#include "std-remakes/timer.h"
#include "std-remakes/uniqptr.h"
#include "std-remakes/vector.h"
#include <list>

using namespace cox;

void TestRandom();
void TestList();
void TestTimer();
void TestVector();

int main()
{
    TestTimer();
    return 0;
}

void TestVector()
{
    vector<int> a;
}

void TestTimer()
{
    ScopedTimer t("pula");
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
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

    List<int> l = { 1, 2, 3, 4, 31245 };
    l.push_back(2);
    l.push_back(3);
    l.push_back(5);
    l.push_back(7);

    //auto i = --l.end();
    //l.erase(i);

    std::list<int> a = { 2, 3, 5, 8 };
    auto it = a.end();
    std::cout << (--it).operator*();;


    //PrintList(l);












}

void TestRandom()
{
    int i = 100;
    while (i--)
        
        std::cout << Random::Get() << '\n';
}
