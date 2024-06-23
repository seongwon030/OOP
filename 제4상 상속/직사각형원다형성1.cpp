#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

// class Point, Shape, Rect, Circle은 바운딩박스와 동일
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
    // print() 메서드는 overring할 계획이므로 virtual로 선언
    // 모든 shape에 공통인 부분인 shape_type만 출력
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
            Rect *r = new Rect(cin); // Rect타입 객체 주소
            vec.push_back(r);
        }
        else if (stype == "C")
        {
            Circle *c = new Circle(cin); // Circle 타입 객체 주소
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

    return 0;
}