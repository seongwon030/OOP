#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Term
{
    // Polynomial 에서 Term의 private 멤버를 액세스
    friend class Polynomial;

private:
    int coef;
    int expo;
    Term() = default;
    Term(int c, int e) : coef(c), expo(e) {}

public:
    int calc(int x)
    {
        return coef * pow(x, expo);
    }

    void print(ostream &out)
    {
        out << coef << "x^" << expo;
    }
};

class Polynomial
{
    friend void print_poly(Polynomial p, ostream &out);
    // class Polynomial 의 멤버로도 둘 수 있지만 여기선 별개의 함수로 정의
    // class Polynomial 의 friend 함수로 선언하면 이 함수 내부에서 class Polynomial의 private멤버를 액세스가능

private:
    char name;
    vector<Term> terms;

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
        // 다항식 계산
        int result = 0;
        for (auto t : terms)
            result += t.calc(x);
        return result;
    }

    void add_term(int coef, int expo)
    {
        // 항 추가
        auto it = terms.begin();
        while (it != terms.end() && it->expo > expo)
            // 벡터를 순회하면서 추가할 다항식의 차수보다 요소의 차수가 크면 다음 요소로 넘어감
            it++;

        if (it != terms.end() && it->expo == expo)
        {
            // 차수가 같으면 계수를 더함
            it->coef += coef;
            if (it->coef == 0)
                // 계수가 0이되면 해당 다항식 삭제
                terms.erase(it);
        }
        else
        {
            // 차수가 같은 게 존재하지 않으면 새로운 다항식으로 벡터에 추가
            terms.insert(it, Term(coef, expo));
        }
    }
};

void print_poly(Polynomial p, ostream &out)
{
    cout << p.name << "=";
    for (auto t : p.terms)
    {
        t.print(out);
        out << " + ";
    }
}

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
            // 추가할 다항식의 이름과 같은게 있다면 새로운 다항식 이름으로 덮어쓰기
            *it = p;
        else
            polys.push_back(p);
    }

    void add_term_to(char name, int coef, int expo)
    {
        auto it = find(name);
        if (it == polys.end())
            // 이름이 없으면
            cout << "Undefined polynomial !" << endl;
        else
            // 이름이 있으면 다항식 추가
            it->add_term(coef, expo);
    }

    void calc_poly(char name, int x)
    {
        auto it = find(name);
        if (it == polys.end())
            // 이름없음
            cout << "Undefined polynomial !" << endl;
        else
            // 이름있으면 모든 다항식 더하기
            cout << it->calc(x) << endl;
    }

    void print_pol(ostream &out, char name)
    {
        auto it = find(name);
        if (it == polys.end())
            cout << "Undefined polynomial !" << endl;
        else
        {
            // 해당이름의 다항식 출력
            print_poly(*it, out);
            out << endl;
        }
    }

    void copy_poly(char name, char new_name)
    {
        auto it = find(name);
        if (it == polys.end())
        {
            cout << "Undefined polynomial !" << endl;
            return;
        }

        // 이름 해당하는 다항식 없으면 카피
        Polynomial q = *it;
        q.set_name(new_name);
        it = find(new_name);
        if (it == polys.end())
            // 이름 없으면 새로 push
            polys.push_back(q);
        else
            // 있으면 덮어쓰기
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
        polys.erase(it);
    }

    void list_polys(ostream &out)
    {
        for (auto p : polys)
        {
            print_poly(p, out);
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
            calculator.print_pol(cout, name);
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
