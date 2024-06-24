#include <iostream>
using namespace std;

class Point
{
private:
    int x, y;

public:
    Point() : x(0), y(0) {}
    // 함수호출 연산자 operator() 를 오버로딩해 Point 객체를 함수처럼 사용
    // 현재 객체에 대한 참조를 반환
    Point &operator()(int dx, int dy);
    void show()
    {
        cout << "x = " << x << ", y = " << y << endl;
    }
};

// 전달된 dx와 dy로 x와 y를 설정
// 마지막엔 현재 객체에 대한 참조를 반환
Point &Point::operator()(int dx, int dy)
{
    x = dx;
    y = dy;
    return *this;
}

int main()
{
    Point pt;
    pt(3, 2);
    pt.show();
    return 0;
}