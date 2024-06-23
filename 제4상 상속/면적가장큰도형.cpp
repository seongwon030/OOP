#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

// 면적이 가장 큰 도형 찾기

class Point
{
public:
    double x, y;
    Point() = default;
    Point(double a, double b) : x(a), y(b) {}
    double dist(Point p)
    {
        return sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
    }
};

class Shape
// pure virtual fucntion을 하나라도 가지는 클래스는 abstract클래스가 된다.
// 추상 클래스의 객체는 생성할 수 없다.
{
private:
    string shape_type;

public:
    Shape() = default;
    Shape(string type) : shape_type(type) {}
    string get_type()
    {
        return shape_type;
    }

    // 추상적인 개념에 불과한 area를 계산할 방법이 없다
    // 이때 pure virtual function으로 선언
    // class Shape는 이 메서드 구현안하고 서브클래스에서 구현

    virtual double maxy() = 0;

    virtual void print(ostream &out)
    {
        out << shape_type;
    }
};

class Rect : public Shape
{
    // 상속일 때만 접근가능
protected:
    Point lu, rl;

public:
    Rect() = default;
    Rect(Point a, Point b) : Shape("rectangle"), lu(a), rl(b) {}
    Rect(double x1, double y1, double x2, double y2) : Shape("rectangle"), lu(Point(x1, y1)), rl(Point(x2, y2)) {}
    Rect(istream &in) : Shape("rectangle")
    {
        in >> lu.x >> lu.y >> rl.x >> rl.y;
    }

    double area()
    {
        // 사각형 넓이
        return (rl.x - lu.x) * (rl.y - lu.y);
    }

    double minx()
    {
        return lu.x;
    }

    double maxx()
    {
        return rl.x;
    }

    double miny()
    {
        return lu.y;
    }

    double maxy()
    {
        return rl.y;
    }

    void print(ostream &out) override
    {
        Shape::print(out);
        out << ": " << lu.x << " " << lu.y << " " << rl.x << " " << rl.y;
    }
};

class Circle : public Shape
{
private:
    Point center;
    double radius;

public:
    Circle() = default;
    Circle(Point a, double r) : Shape("circle"), center(a), radius(r) {}
    Circle(double x, double y, double r) : Shape("circle"), center(Point(x, y)), radius(r) {}
    Circle(istream &in) : Shape("circle")
    {
        in >> center.x >> center.y >> radius;
    }

    double area()
    {
        // 원 넓이
        return M_PI * radius * radius;
    }

    double minx()
    {
        // 중심 - r
        return center.x - radius;
    }

    double maxx()
    {
        // 중심 + r
        return center.x + radius;
    }

    double miny()
    {
        return center.y - radius;
    }

    double maxy()
    {
        return center.y + radius;
    }

    void print(ostream &out) override
    {
        Shape::print(out);
        out << ": " << center.x << " " << center.y << " " << radius;
    }
};

int main()
{
    // 서브클래스인 Rect와 Circle 타입의 객체의 주소를 수퍼클래스인 Shape 타입의 배열에 모두 저장
    vector<Shape *> vec;
    string stype;

    while (true)
    {
        cin >> stype;
        if (stype == "R")
        {
            Rect *r = new Rect(cin);
            vec.push_back(r);
        }
        else if (stype == "C")
        {
            Circle *c = new Circle(cin);
            vec.push_back(c);
        }
        else if (stype == "exit")
            break;
    }

    for (Shape *s : vec)
    {
        // 동적 바인딩에 의해서 Rect 객체는 Rect::print()가 호출되고
        // Circle 객체는 Circle::print()가 호출됨
        s->print(cout);
        cout << endl;
    }

    double max_area = 0;
    for (auto &s : vec)
    {
        if (s->area() > max_area)
        {
            // s가 실제로 가리키는 객체는 Rect이거나 Circle이며 두 클래스 모두 area()메서드를 가진다
            // 하지만 Shape 클래스엔 area()메서드가 없다. 그래서 컴파일 오류가 발생한다
            max_area = s->area();
        }
    }
    cout << max_area << endl;

    double min_x = INT_MAX, max_x = INT_MAX, min_y = INT_MAX, max_y = INT_MIN;
    for (auto &c : vec)
    {
        if (c->minx() < min_x)
            min_x = c->minx();
        if (c->maxx() > max_x)
            max_x = c->maxx();
        if (c->miny() < min_y)
            min_y = c->miny();
        if (c->maxy() > max_y)
            max_y = c->maxy();
    }

    cout << min_x << " " << max_x << " " << min_y << " " << max_y << endl;

    return 0;
}

// Pure Virtual Funtion과 Abstract Class

// pure virtural function 를 하나라도 가지는 클래스는 추상 클래스 됨
// 추상 클래싀 인스턴스(객체)는 생성할 수 없음

// 추상적인 개념에 불과한 Shape의 area를 계산할 방법은 업음
// 이럴 경우 pure virtual function으로 선언
// class Shape은 이 메서드를 구현하지 않고 서브클래스에서 구현