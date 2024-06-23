#include <iostream>
using namespace std;

class P
{
public:
    void print()
    {
        cout << "Inside P";
    }
};

class Q : public P
{
public:
    void print()
    {
        cout << "Insize Q";
    }
};

class R : public Q
{
    // public:
    //     void print()
    //     {
    //         cout << "Insize R";
    //     }
};

int main()
{
    R r;
    r.print();
    return 0;
}