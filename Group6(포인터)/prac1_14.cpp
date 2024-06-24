#include <iostream>
#include <vector>
using namespace std;

class Foo
{
public:
    int x;
    Foo() = default;
    Foo(int a) : x(a) {}
};

int main()
{
    vector<Foo *> vec{new Foo(1), new Foo(2), new Foo(5), new Foo(4)};
    auto it = vec.begin() + 2; // 인덱스
    cout << (*it)->x << endl;  // 인덱스에 해당하는 x값

    // 동적으로 할당된 메모리 해제
    for (auto foo_ptr : vec)
    {
        delete foo_ptr;
    }

    return 0;
}