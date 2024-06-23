#include "code11.h"

class Foo;
// forword declaration

class Bar
{
public:
    Bar();
    Bar(Foo f);           // 매개변수의 타입으로 Foo 등장
    Foo *bar_func(int x); // 어떤 함수의 리턴타입으로 Foo타입의 포인터
};

// 선언 (내용이 있다면 정의)
int some_func();       // Foo타입의 참조
int some_func2(Foo f); // Foo 타입의 매개변수

int main()
{
    Bar b;
    Foo *p_foo = b.bar_func(10);
    int result = some_func();
    return 0;
}
// Foo 타입의 객체를 생성하거나 멤버들을 액세스하는 부분은 없다
// 무사히 컴파일하기 위해 클래스 Foo가 존재한다는 것만 선언하면 컴파일된다
// 다른 파일에 구현된 내용을 연결하는 건 링커의 몫이다