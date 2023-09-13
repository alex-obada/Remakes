#include <iostream>

#include "std-remakes/random.h"
#include "std-remakes/list.h"
#include "std-remakes/string.h"
#include "std-remakes/timer.h"
#include "std-remakes/uniqptr.h"
#include "std-remakes/vector.h"
#include <list>
#include <vector>

using namespace cox;

void TestRandom();
void TestList();
void TestTimer();
void TestVector();
void TestUniquePtr();

int main()
{
    TestUniquePtr();
    return 0;
}

void TestVector()
{
    vector<int> c;
    std::vector<int> a;


    c.push_back(5);
    c.emplace_back(2);
    c.emplace_back(3);
    c.emplace_back(9);
    c.pop_back();
    
    for (auto it = c.begin(); it != c.end(); ++it)
        std::cout << *it << ' ';
    c.clear();
    
}

void TestUniquePtr()
{
    using Type = std::pair<int, std::string>;
    unique_ptr<Type> ptr = make_unique<Type>(20, "Marcelo");
    std::cout << ptr->first << ' ' << ptr->second << '\n';
}


void TestTimer()
{
    ScopedTimer t("timer");
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
}

void TestList()
{
    auto PrintList = []<typename T>(List<T>& list) {
        /*for (auto const& x : list)
            std::cout << x << ' ';
        std::cout << std::endl;*/

        //for (auto it = list.cbegin(); it != list.cend(); ++it)
        //{
        //    //*it = 2; // error
        //    std::cout << *it << ' ';
        //}

        for (auto it = list.crbegin(); it != list.crend(); ++it)
        {
            //*it = 2; // error
            std::cout << *it << ' ';
        }
        std::cout << std::endl;

    };

    List<int> l = { 1, 2, 3, 4, 20 };

    PrintList(l);
    //auto i = l.cbegin();
    //l.erase(i);

    int asd;
    int* p = &asd;
    std::cout << p << '\n' << ++p << "\n\n";



    auto it = l.rend();
    std::cout << (--it).operator*() << "\n\n";

    Node<std::pair<int, int>> c(nullptr, { 1, 1 }, nullptr);
    std::cout << "Prev: " << &c.prev << '\n' 
              << "Data: " << &c.data << '\n' 
              << "Next: " << &c.next << "\n\n";


    Node<int> ca(nullptr, 1, nullptr);
    std::cout << "Prev: " << &ca.prev << '\n'
        << "Data: " << &ca.data << '\n'
        << "Next: " << &ca.next << "\n\n";


    std::cout << "Prev: " << offsetof(Node<int>,prev) << '\n'
              << "Data: " << offsetof(Node<int>,data) << '\n'
              << "Next: " << offsetof(Node<int>,next) << "\n\n";
    std::cout << sizeof(std::nullptr_t);







}

void TestRandom()
{
    int i = 100;
    while (i--)
        
        std::cout << Random::Get() << '\n';
}
