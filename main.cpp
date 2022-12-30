#include <iostream>
#if 0
#include <fstream>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <string>
#include "string.h"
#include "fractie.h"
#include "matrix.h"
#include <list>
#endif
#include "matrix.h"
#include "list.h"
#include <vector>

using namespace cox;



#define LOG(x) std::cout << x << ' ';

int main()
{
    Matrix m(4, 3, 7);


    int cnt{ 1 };
    for (size_t i = 0; i < m.GetLines(); ++i, std::cout << '\n')
        for (size_t j = 0; j < m.GetColumns(); ++j)
        {
            m[i][j] = cnt++;
            LOG(m[i][j]);
        }
    LOG("\n\n");

    auto a = Matrix::GetTransposed(m);
    auto b = Matrix::GetUnitMatrix(4);

    LOG(b);
    LOG("\n" << Matrix::GetTrace(b));
    
    /*
    //LOG(asd);
    //LOG("\n\n");


    //for (size_t i = 0; i < m.GetLines(); ++i, std::cout << '\n')
    //    for (size_t j = 0; j < m.GetColumns(); ++j)
    //        LOG(asd[i][j]);
    
    */


}




// vector
/*
    // declarare
    vector<int> arr(5, 3);


    arr.erase(arr.begin() + 2);
    arr.insert(arr.begin() + 4, 9);



    //iterare
    for (int i = 0; i < arr.size(); ++i); // arr[i]

    // *it
    for (vector<int>::iterator it = arr.begin(); it != arr.end(); ++it);
    for (auto it = arr.begin(); it != arr.end(); ++it);

    for (auto& x : arr)
        cout << x << ' ';


    // acces
    arr.push_back(7);
    arr.pop_back();
    arr.front(); arr.back();
    arr[2];

    //LOG(arr.size());

    vector<pair<int, int>> p;

    p.push_back({ 1, 1 }); // caca
    p.emplace_back(1, 1); // good

    p.data();

    p.clear();


*/

/*
int main()
{
    List<int> a;


    for(int i = 1; i < 10; ++i)
        a.push_back(i);
    a.insertAfter(a.GetLast()->prev, 10);
    a.insertBefore(a.GetLast()->prev, 999);

    LOG(a);


   /* std::ifstream fin("D:\\info\\VS\\Test1\\numere.in");

    fin >> a;
    LOG(a);


    List<int> b = a;
    while (a)
    {
        std::cout << a.size() << '\t';
        LOG(a);

        a.pop_front();
    }

    a = std::move(b);


    while (a)
    {
        std::cout << a.size() << '\t';
        LOG(a);

        a.pop_back();
    }
    //LOG(b);

    List<int>::Node nod(nullptr, 3, nullptr);

    LOG(nod.prev);
    LOG(nod.data);
    LOG(nod.next);




    return 0;
}

*/
/*
cox::Matrix<int> a(3, 3, 2343564), x, y, z;;



a[0][0] = 1232141;

x = y = z = a;

LOG(x);
LOG(y);
LOG(z);

//-------------------------------
cox::Fractie a{ -2, 3 }, b{ 2, 3 }, c{1000000, 17};

LOG(a);

LOG(b);
LOG(c);
return 0;*/

/*
for (int i = 1; i < 20; ++i)
    a.push_back(std::move(i));

//for (int i = 20; i < 40; ++i)
//    b.push_back(i);
//
//a.swap(b);

for (auto& x : a)
{
    LOG(x);
}
a.erase(++a.begin());
std::cout << '\n';
for (auto& x : a)
{
    LOG(x);
}


//cox::List<int>* p = &a;

//(* p).Empty
//p->
*/