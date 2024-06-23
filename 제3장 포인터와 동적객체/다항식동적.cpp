#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Term
{
    friend class Polynomial;

private:
    int coef; // 숫자
    int expo; // 지수

public:
    Term() = default;
    Term(int c, int e) : coef(c), expo(e) {}
    int calc(int x)
    {
        return coef * pow(x, expo); // 제곱
    }

    void print(ostream &out)
    {
        out << coef << "x^" << expo;
    }
};

class Polynomial
{
private:
    char name;
    vector<Term *> terms; // terms를 Term *의 벡터로 변경

public:
    Polynomial() = default;
    Polynomial(char pname) : name(pname) {}

    char get_name()
    {
        return name;
    }

    void set_name(char c)
    {
        name = c;
    }

    int calc(int x)
    {
        int result = 0;
        for (auto t : terms)
            result += t->calc(x);
        return result;
    }

    void print(ostream &out)
    {
        cout << name << "=";
        for (auto t : terms)
        {
            t->print(out);
            out << " + ";
        }
    }

    void clear_terms()
    {
        for (auto t : terms)
            delete t;
    }

    void add_term(int coef, int expo)
    {
        auto it = terms.begin();
        while (it != terms.end() && (*it)->expo > expo)
            it++;

        if (it != terms.end() && (*it)->expo == expo)
        {
            (*it)->coef += coef;
            if ((*it)->coef == 0)
            {
                // 더했을 때 0이 되면 해당 객체를 terms에서 삭제
                delete *it;
                terms.erase(it);
            }
        }
        else
        {
            // 동적 생성된 Term 객체의 주소를 벡터 terms에 삽입
            terms.insert(it, new Term(coef, expo));
        }
    }
};

class PolyCalculator
{
private:
    vector<Polynomial> polys;

    vector<Polynomial>::iterator find(char name)
    {
        for (auto it = polys.begin(); it != polys.end(); it++)
        {
            if (it->get_name() == name)
                return it;
        }
        return polys.end();
    }

public:
    void create_or_update_poly(char name)
    {
        Polynomial p(name);
        auto it = find(name);
        if (it != polys.end())
        {
            // 해당 이름을 가진 다항식을 찾으면, 해당 다항식의 용어들을 비우고,
            // 새로 생성한 다항식 'p'로 덮어쓰기
            it->clear_terms();
            *it = p;
        }
        else
            // 해당 이름의 다항식이 존재하지 않으면, 새로운 다항식을 추가
            polys.push_back(p);
    }

    void add_term_to(char name, int coef, int expo)
    {
        auto it = find(name);
        if (it == polys.end())
            cout << "Undefined polynomial !" << endl;
        else
            it->add_term(coef, expo);
    }

    void calc_poly(char name, int x)
    {
        auto it = find(name);
        if (it == polys.end())
            cout << "Undefined polynomial !" << endl;
        else
            cout << it->calc(x) << endl;
    }

    void print_poly(ostream &out, char name)
    {
        auto it = find(name);
        if (it == polys.end())
            cout << "Undefined polynomial !" << endl;
        else
        {
            it->print(out);
            out << endl;
        }
    }

    void copy_poly(char name, char new_name)
    {
        auto it = find(name);
        if (it == polys.end())
        {
            // 해당 이름의 다항식이 존재하지 않는 경우
            cout << "Undefined polynomial !" << endl;
            return;
        }

        Polynomial q = *it; // shallow copy ==> deep copy
        // 해당 이름의 다항식을 찾으면 얕은 복사

        q.set_name(new_name); // 새로운 다항식의 이름을 새로운 이름으로 설정
        it = find(new_name);
        if (it == polys.end())
            // 새로운 이름이 polys에 존재하지 않으면 polys에 추가
            polys.push_back(q);
        else
        {
            // 존재하는 경우 해당 다항식을 새로운 다항식 'q'로 덮어쓰기
            *it = q;
        }
    }

    void copy_poly_wrong_version(char name, char new_name)
    {
        auto it = find(name);
        if (it == polys.end())
        {
            cout << "Undefined polynomial !" << endl;
            return;
        }

        Polynomial q = *it;
        q.set_name(new_name);
        it = find(new_name);
        if (it == polys.end())
            polys.push_back(q);
        else
            *it = q;
    }

    void delete_poly(char name)
    {
        auto it = find(name);
        if (it == polys.end())
        {
            cout << "Undefined polynomial !" << endl;
            return;
        }
        // 해당 이름의 다항식이 존재하면 해당 다항식의 용어들을 비움
        // polys에서 해당 다항식 삭제
        it->clear_terms();
        polys.erase(it);
    }

    void list_polys(ostream &out)
    {
        for (auto p : polys)
        {
            p.print(out);
            out << endl;
        }
    }
};

void process_command(PolyCalculator &calculator)
{
    char name, new_name;
    int coef, expo, x;
    string command;
    while (true)
    {
        cout << "$ ";
        cin >> command;
        if (command == "print")
        {
            cin >> name;
            calculator.print_poly(cout, name);
        }
        else if (command == "calc")
        {
            cin >> name >> x;
            calculator.calc_poly(name, x);
        }
        else if (command == "create")
        {
            cin >> name;
            calculator.create_or_update_poly(name);
        }
        else if (command == "add")
        {
            cin >> name >> coef >> expo;
            calculator.add_term_to(name, coef, expo);
        }
        else if (command == "copy")
        {
            cin >> name >> new_name;
            calculator.copy_poly(name, new_name);
        }
        else if (command == "delete")
        {
            cin >> name;
            calculator.delete_poly(name);
        }
        else if (command == "list")
        {
            calculator.list_polys(cout);
        }
        else if (command == "exit")
            break;
    }
}

int main()
{
    PolyCalculator calculator;
    process_command(calculator);
    return 0;
}
