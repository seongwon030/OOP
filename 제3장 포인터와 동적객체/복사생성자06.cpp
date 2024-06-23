#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Foo
{
public:
    int val;
    Foo() = default;
    Foo(int a) : val(a) {}
};

class Bar
{
public:
    Foo *ptr;
    vector<Foo *> vec;
    Bar() = default;

    Bar(const Bar &t) // 복사생성자 선언 : 원본 객체 수정 x
    {
        // 깊은 복사
        cout << "copy constr" << endl;
        // 포인터 멤버 ptr의 깊은복사
        // t.ptr이 가리키는 객체를 복사해 새로운 Foo 객체 생성
        // 원본 객체 t 의 ptr 과 복사된 객체의 ptr 이 서로 다른 메모리 위치를 가리킴
        ptr = new Foo(*t.ptr);
        for (auto &pt : t.vec)
            vec.push_back(new Foo(*pt));
    }
};

int main()
{
    Bar a;
    a.ptr = new Foo(100);
    a.vec.push_back(new Foo(1));
    a.vec.push_back(new Foo(2));
    a.vec.push_back(new Foo(3));

    Bar b = a; // 자동 생성된 복사 생성자가 실행된다.
    a.ptr->val = 200;
    a.vec[0]->val = 300;

    cout << a.ptr->val << " " << a.vec[0]->val << endl;
    cout << b.ptr->val << " " << b.vec[0]->val << endl;

    return 0;
}