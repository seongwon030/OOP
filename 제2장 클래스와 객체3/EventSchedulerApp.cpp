#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

class Date
{
private:
    int year, month, day;

public:
    Date() = default;
    Date(int y, int m, int d) : year(y), month(m), day(d) {}
    Date(string date_string)
    {
        int start = 0, end = 0;
        while (date_string.at(end) != '/')
            end++; // end 인덱스 증가시키며 슬래시찾기
        year = stoi(date_string.substr(start, end));
        // 문자열의 처음부터 슬래시 직전까지의 부분 문자열 반환
        // stoi 는 부분 문자열을 정수로 변환해 year에 저장

        end++, start = end;
        while (date_string.at(end) != '/')
            end++;
        month = stoi(date_string.substr(start, end - start));

        start = end + 1;
        day = stoi(date_string.substr(start));
    }

    bool operator<(Date &rhs)
    {
        return year < rhs.year || (year == rhs.year && month < rhs.month) ||
               (year == rhs.year && month == rhs.month && day < rhs.day);
    }

    bool operator>(Date &rhs)
    {
        return year > rhs.year || (year == rhs.year && month > rhs.month) ||
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
        return *this < rhs || *this == rhs;
    }

    bool operator>=(Date &rhs)
    {
        return *this > rhs || *this == rhs;
    }

    void print(ostream &out)
    {
        out << year << "/" << month << "/" << day;
    }
};
// 하루 지정 이벤트
class OneDayEvent
{
private:
    Date date;
    string content;

public:
    OneDayEvent() = default;
    OneDayEvent(Date d, string str) : date(d), content(str) {}

    bool relevant_to(Date &theDay)
    {
        // 날짜가 같아야 함
        return theDay == date;
    }
    void print(ostream &out)
    {
        date.print(out);
        out << ":" << content;
    }
};

// 기간이벤트
class PeriodEvent
{
private:
    Date begin, end;
    string content;

public:
    PeriodEvent() = default;
    PeriodEvent(Date d1, Date d2, string str) : begin(d1), end(d2), content(str) {}

    bool relevant_to(Date &theDay)
    {
        // 시작날짜와 종료날짜 사이에 있어야 함
        return begin <= theDay && theDay <= end;
    }

    void print(ostream &out)
    {
        begin.print(out);
        out << "-";
        end.print(out);
        out << ":" << content;
    }
};

// 마감일 지정 이벤트
class DeadlineEvent
{
private:
    Date deadline;
    string content;

public:
    DeadlineEvent() = default;
    DeadlineEvent(Date d, string str) : deadline(d), content(str) {}

    bool relevant_to(Date &theDay)
    {
        // 마감일보다 날짜가 먼저여야 함
        return theDay <= deadline;
    }

    void print(ostream &out)
    {
        out << "~";
        deadline.print(out);
        out << ":" << content;
    }
};

class EventScheduler
{
private:
    vector<OneDayEvent> oneday_events;
    vector<PeriodEvent> period_events;
    vector<DeadlineEvent> deadline_events;

    void parse_period_string(string period_str, Date &s, Date &t)
    {
        // 시작과 종료는 - 를 기준으로 나누어져 있음
        int idx = period_str.find_first_of("-");
        Date d1(period_str.substr(0, idx));
        Date d2(period_str.substr(idx + 1));
        s = d1, t = d2;
    }

public:
    void add_oneday_event(string date_string, string content);
    void add_period_event(string date_string, string content);
    void add_deadline_event(string date_string, string content);
    void show_relevant_events(Date theDay);
    void show_all_events();
    void load_data_file(string file_name);
};

void EventScheduler::add_oneday_event(string date_string, string content)
{
    Date d(date_string);
    OneDayEvent e(d, content);
    oneday_events.push_back(e);
}

void EventScheduler::add_period_event(string date_string, string content)
{
    Date s, t;
    parse_period_string(date_string, s, t);
    PeriodEvent e(s, t, content);
    period_events.push_back(e);
}

void EventScheduler::add_deadline_event(string date_string, string content)
{
    Date d(date_string); // excluding leading ~
    DeadlineEvent e(d, content);
    deadline_events.push_back(e);
}

// 포함되는 이벤트
void EventScheduler::show_relevant_events(Date theDay)
{
    for (auto ev : oneday_events)
    {
        if (ev.relevant_to(theDay))
        {
            ev.print(cout);
            cout << endl;
        }
    }
    for (auto ev : period_events)
    {
        if (ev.relevant_to(theDay))
        {
            ev.print(cout);
            cout << endl;
        }
    }
    for (auto ev : deadline_events)
    {
        if (ev.relevant_to(theDay))
        {
            ev.print(cout);
            cout << endl;
        }
    }
}

// 모든 이벤트
void EventScheduler::show_all_events()
{
    for (auto ev : oneday_events)
    {
        ev.print(cout);
        cout << endl;
    }
    for (auto ev : period_events)
    {
        ev.print(cout);
        cout << endl;
    }
    for (auto ev : deadline_events)
    {
        ev.print(cout);
        cout << endl;
    }
}

// 이벤트 파일 로드
void EventScheduler::load_data_file(string file_name)
{
    ifstream infile(file_name);
    string line, date_string, content;
    while (getline(infile, line))
    {
        stringstream sstream(line);
        sstream >> date_string;
        getline(sstream, content);
        if (date_string.find('-') != string::npos) // -1을 가지는 상수, find로 찾을 때 없는 경우 반환
        {
            // "-" 있으면 기간날짜 벡터에 추가
            add_period_event(date_string, content);
        }
        else if (date_string.find('~') != string ::npos)
        {
            // "~"있으면 첫번째 문자 빼고 나머지 문자와 이벤트내용을 마감날짜 벡터에 추가
            add_deadline_event(date_string.substr(1), content);
        }
        else
        {
            add_oneday_event(date_string, content);
        }
    }
    infile.close();
}

void process_command(EventScheduler scheduler)
{
    string command, event_type, date_string, content;
    while (1)
    {
        cout << "$ ";
        cin >> command;
        if (command == "add")
        {
            cin >> event_type;
            cin >> date_string;
            getline(cin, content);

            if (event_type == "-O") // one day event
                scheduler.add_oneday_event(date_string, content);
            else if (event_type == "-P") // period event
                scheduler.add_period_event(date_string, content);
            else if (event_type == "-D") // deadlined event
                scheduler.add_deadline_event(date_string, content);
            else // unsupported event type
                cout << "Unsupported event type." << endl;
        }
        else if (command == "find")
        {
            cin >> date_string;
            Date d(date_string);
            scheduler.show_relevant_events(d);
        }
        else if (command == "list")
        {
            scheduler.show_all_events();
        }
        else if (command == "exit")
        {
            break;
        }
    }
}

int main()
{
    EventScheduler scheduler;
    scheduler.load_data_file("events.txt");
    process_command(scheduler);

    return 0;
}