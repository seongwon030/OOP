#define _USE_MATH_DEFINES // M_PI 정의하기 위해 필요
#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

class Circle
{
private:
    int x, y, r;

public:
    Circle(int _x, int _y, int _r) : x(_x), y(_y), r(_r) {}

    double getArea() const
    {
        return M_PI * r * r;
    }
    int getX() const
    {
        return x;
    }

    int getY() const
    {
        return y;
    }

    int getR() const
    {
        return r;
    }

    // 원과 원이 교차
    bool intersects(const Circle &other) const
    {
        // 두 원의 중심 간 거리 <= 두 원의 반지름 합 = 두 원이 교차하거나 접합
        int dx = x - other.x;
        int dy = y - other.y;
        int distanceSquared = dx * dx + dy * dy;
        int sumOfRadiiSquared = (r + other.r) * (r + other.r);
        return distanceSquared <= sumOfRadiiSquared;
    }

    // 원과 직사각형이 교차
    bool intersects(int xmin, int xmax, int ymin, int ymax) const
    {
        int nearestX = max(xmin, min(x, xmax)); // 직사각형 내에서 중심 x좌표에 가장 가까운 x좌표
        int nearestY = max(ymin, min(y, ymax)); // 직사각형 내에서 중심 y좌표에 가장 가까운 y좌표
        int dx = x - nearestX;
        int dy = y - nearestY;
        // 직사각형 내에서 원의 중심에 가장 가까운 점과 원의 중심 간 거리 <= 반지름 제곱
        return (dx * dx + dy * dy) <= (r * r);
    }
};

class Rect
{
private:
    int xmin, xmax, ymin, ymax;

public:
    Rect(int _xmin, int _xmax, int _ymin, int _ymax) : xmin(_xmin), xmax(_xmax), ymin(_ymin), ymax(_ymax) {}

    double getArea() const
    {
        return (xmax - xmin) * (ymax - ymin);
    }
    int getXmin() const
    {
        return xmin;
    }

    int getXmax() const
    {
        return xmax;
    }
    int getYmin() const
    {
        return ymin;
    }

    int getYmax() const
    {
        return ymax;
    }

    bool intersects(const Circle &circle) const
    {
        return circle.intersects(xmin, xmax, ymin, ymax);
    }

    bool intersects(const Rect &other) const
    {
        return !(xmax < other.xmin || xmin > other.xmax || ymax < other.ymin || ymin > other.ymax);
    }
};

// 사각형, 원의 입력정보와 면적을 저장하는 구조체
struct AreaInfo
{
    double area;      // 면적
    string shapeInfo; // 도형 정보
};

// AreaInfo 비교 함수
bool compareArea(const AreaInfo &a, const AreaInfo &b)
{
    return a.area < b.area;
}

int main()
{
    ifstream inputFile("input1.txt");
    if (!inputFile.is_open())
    {
        cerr << "Error opening file" << endl;
        return 1;
    }

    int n;
    inputFile >> n;

    vector<Rect> rectangles;
    vector<Circle> circles;

    char shapeType;
    for (int i = 0; i < n; ++i)
    {
        inputFile >> shapeType;
        if (shapeType == 'R')
        {
            int xmin, xmax, ymin, ymax;
            inputFile >> xmin >> xmax >> ymin >> ymax;
            rectangles.emplace_back(xmin, xmax, ymin, ymax);
        }
        else if (shapeType == 'C')
        {
            int x, y, r;
            inputFile >> x >> y >> r;
            circles.emplace_back(x, y, r);
        }
    }

    int targetX, targetY, targetR;
    inputFile >> targetX >> targetY >> targetR;
    Circle targetCircle(targetX, targetY, targetR);

    vector<AreaInfo> areas;

    for (const auto &rect : rectangles)
    {
        if (rect.intersects(targetCircle))
        {
            areas.push_back({rect.getArea(), "R " + to_string(rect.getXmin()) + " " + to_string(rect.getXmax()) + " " + to_string(rect.getYmin()) + " " + to_string(rect.getYmax())});
        }
    }

    for (const auto &circle : circles)
    {
        if (circle.intersects(targetCircle))
        {
            areas.push_back({circle.getArea(), "C " + to_string(circle.getX()) + " " + to_string(circle.getY()) + " " + to_string(circle.getR())});
        }
    }

    // 면적순으로 정렬
    sort(areas.begin(), areas.end(), compareArea);

    // areas 출력
    for (const auto &area : areas)
    {
        cout << area.shapeInfo << endl;
    }

    inputFile.close();
    return 0;
}
