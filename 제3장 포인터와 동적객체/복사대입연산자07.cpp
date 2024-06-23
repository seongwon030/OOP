#include <iostream>
#include <vector>
#include <string>

using namespace std;

// &operator의 문제점 : 자신의 참조를 반환하여 치환연산자를 적용
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
    Foo *ptr = nullptr;
    vector<Foo *> vec;

    Bar() = default;
    Bar(Foo *p, vector<Foo *> v) : ptr(p), vec(v) {}

    Bar(const Bar &t)
    {
        ptr = new Foo(*t.ptr);
        for (auto &pt : t.vec)
            vec.push_back(new Foo(*pt));
    }

    // 자신의 참조를 반환하면 =연산자를 연속적으로 적용가능
    Bar &operator=(const Bar &t)
    {
        ptr = new Foo(*t.ptr);
        for (auto &pt : t.vec)
            vec.push_back(new Foo(*pt));
        return *this;
        // 복사 대입 연산자는 대입된 객체 자기 자신을 반환해야 한다
        // 이렇게 하면 연쇄적인 대입 (a = b = c)이 가능해짐
    }
};

int main()
{
    Bar a;
    a.ptr = new Foo(100);
    a.vec.push_back(new Foo(1));
    a.vec.push_back(new Foo(2));
    a.vec.push_back(new Foo(3));

    // 초기화가 아닌 치환문의 경우 복사 생성자가
    // 실행되지 않으며 단지 멤버별 복사가 일어난다
    Bar c;
    c = a;

    a.ptr->val = 200;
    a.vec[0]->val = 300;

    cout << a.ptr->val << " " << a.vec[0]->val << endl;
    cout << c.ptr->val << " " << c.vec[0]->val << endl;
    return 0;
}
