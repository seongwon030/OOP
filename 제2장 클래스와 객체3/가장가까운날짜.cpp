#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

class Date
{
private:
    int year, month, day;
    vector<int> short_months{4, 6, 9, 11}; // 30일인 달
    bool is_short_month()
    {
        // 날이 30일인 달인지 확인
        return find(short_months.begin(), short_months.end(), month) != short_months.end();
    }

    bool last_day_of_month()
    {
        // 2월은 28일이면 마지막날
        // 30일인 달이면 day가 30일이면 마지막날
        // 31이면 마지막날
        return month == 2 && day == 28 || is_short_month() && day == 30 || day == 31;
    }

    bool last_day_of_year()
    {
        return month == 12 && day == 31;
    }

public:
    Date() = default;
    Date(int y, int m, int d) : year(y), month(m), day(d) {}

    bool operator<(Date &rhs)
    {
        // rhs : 클래스 멤버함수로 2진 연산자를 오버로딩할 때 왼쪽 피연산자는 자기 자신이며
        // 오른쪽 피연산자는 매개변수로 받음.
        return year < rhs.year ||
               (year == rhs.year && month < rhs.month) ||
               (year == rhs.year && month == rhs.month && day < rhs.day);
    }
    bool operator>(Date &rhs)
    {
        return year > rhs.year ||
               (year == rhs.year && month > rhs.month) ||
               (year == rhs.year && month == rhs.month && day > rhs.day);
    }
    bool operator==(Date &rhs)
    {
        return year == rhs.year && month == rhs.month && day == rhs.day;
    }
    bool operator!=(Date &rhs)
    {
        return !(*this == rhs);
    }
    bool operator<=(Date &rhs)
    {
        // 이미 구현했음
        // 객체 자신을 액세스 할 경우엔 포인터 this를 사용
        return *this < rhs || *this == rhs;
    }
    bool operator>=(Date &rhs)
    {
        return *this > rhs || *this == rhs;
    }

    Date &operator++()
    {
        // 증감연산자는 자신의 참조를 반환해야 한다.
        // 전위 증감 연산자가 참조를 반환하는 이유는 객체를 복사할 필요가 없거나 복사되어선 안되기 때문
        if (last_day_of_year())
        {
            year++, month = 1, day = 1;
        }
        else if (last_day_of_month())
        {
            month++;
            day = 1;
        }
        else
        {
            day++;
        }
        return *this;
    }
    // int 는 단지 전위 연산자와 구분하기 위함
    Date operator++(int)
    {
        // 후위연산자는 연산 수행 전의 값을 반환해야 하므로 먼저 현재의 객체를 복사해 둠.
        Date ret = *this;

        if (last_day_of_year())
        {
            year++, month = 1, day = 1;
        }
        else if (last_day_of_month())
        {
            month++;
            day = 1;
        }
        else
        {
            day++;
        }
        return ret;
        // 복사해둔 객체는 이 함수가 종료되면 소멸되므로 "복사에 의한 return"
        // 후위 증감 연산자는 연산 적용 이전의 상태를 반환해야 하므로 참조에 의한 반환을 하면 안된다
    }

    // 두 날짜간의 차이를 계산
    int operator-(Date &rhs)
    {

        if (*this == rhs)
            return 0;
        else if (*this < rhs)
        {
            Date temp = *this; // 객체의 내용이 변경되어선 안되므로 복사본을 만들어 작업
            int diff = 0;
            while (temp < rhs)
            {
                temp++;
                diff++;
            }
            return -diff;
        }
        else
        {
            Date rhs_temp = rhs;
            int diff = 0;
            while (*this > rhs_temp)
            {
                rhs_temp++;
                diff++;
            }
            return diff;
        }
    }

    // 해당 날짜에 k일 더한 날짜
    Date operator+(int k)
    {
        Date temp = *this;
        for (int i = 0; i < k; i++)
        {
            ++temp;
        }
        return temp;
    }
    void print(ostream &out)
    {
        out << year << "/" << month << "/" << day;
    }
};

void sort_dates(vector<Date> &dates)
{
    for (int i = dates.size() - 1; i > 0; i--)
    {
        for (int j = 0; j < i; j++)
        {
            if (dates.at(j) > dates.at(j + 1))
                swap(dates.at(j), dates.at(j + 1));
        }
    }
}

int main()
{
    vector<Date> dates;
    ifstream infile("dates.txt");
    int y, m, d;
    while (infile >> y >> m >> d)
    {
        dates.push_back(Date(y, m, d));
    }
    infile.close();

    // 날짜 정렬
    sort_dates(dates);

    for (Date &d : dates)
    {
        d.print(cout);
        cout << endl;
    }

    // 새로운 날짜 입력
    cin >> y >> m >> d;
    Date theDay(y, m, d);

    int min_diff = abs(dates[0] - theDay);
    Date closest_day = dates[0];
    for (Date &dt : dates)
    {
        int diff = abs(dt - theDay);
        if (diff < min_diff)
        {
            min_diff = diff;
            closest_day = dt;
        }
    }
    closest_day.print(cout);
    cout << " with difference " << min_diff << " days." << endl;

    return 0;
}