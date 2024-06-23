#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Term
{
    friend class Polynomial;

private:
    int coef;
    int expo;

public:
    Term() = default;
    Term(int c, int e) : coef(c), expo(e) {}
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
private:
    char name;
    vector<Term *> terms;

    void clearMembers()
    {
        for (auto p : terms)
            delete p;
        terms.clear();
    }

public:
    Polynomial() = default;
    Polynomial(char pname) : name(pname) {}

    Polynomial(const Polynomial &p) : name(p.name) // copy constructor
    {
        for (auto &pt : p.terms)            // copy한 이름을 그대로 복사
            terms.push_back(new Term(*pt)); // clear할 필요없이 copy만 하면 됨

        cout << "Polynomial class copy-constructor executed." << endl;
    }

    Polynomial &operator=(const Polynomial &p)
    {
        clearMembers(); // clear하고 자기 자신을 리턴
        name = p.name;
        for (auto &pt : p.terms)
        {
            terms.push_back(new Term(*pt));
        }
        cout << "Polynomial class copy-assignment operator executed." << endl;

        return *this;
    }

    ~Polynomial() // destructor
    {
        clearMembers();
        cout << "Polynomial class destructor executed." << endl;
    }

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
                // delete 다음엔 삭제할 객체의 주소
                // iterator가 가리키는 주소
                delete *it;
                terms.erase(it);
            }
        }
        else
        {
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
            *it = p;
        // copy assignment operator
        // 덮어씌워질 객체의 terms를 clear하므로 no garbage
        else
            polys.push_back(p); // copy constructor called
        // Destructor destruct p
        cout << "polys's capacity: " << polys.capacity() << endl;
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
        // 새로운 객체를 만들어 복사됨
        // copy constructor로 하나의 객체를 복사할 때 객체가 가리키는 객체또한 따로 복제
        // shallow -> deep
        auto it = find(name);
        if (it == polys.end())
        {
            cout << "Undefined polynomial !" << endl;
            return;
        }

        Polynomial q = *it; // copy-constructor
        q.set_name(new_name);
        it = find(new_name);
        if (it == polys.end())
            polys.push_back(q); // copy-constructor called two times(one for call-by-value, and another for appending into vector, and destructor destruct a copy of q
        else
        {
            *it = q; // copy assignment operator
        }
        // Destructor destruct q
    }

    void delete_poly(char name)
    {
        auto it = find(name);
        if (it == polys.end())
        {
            cout << "Undefined polynomial !" << endl;
            return;
        }
        polys.erase(it); // Destructor
        // add_Term할 때는 먼저 delete *it 하고 erase함
        // 이유는 vector<Term *> terms - Term타입 포인터 벡터이므로
        // erase하면 실행되는건 포인터 타입의 디스트럭터이므로
        // 칸만 삭제되고 객체는 삭제되지 않는다 -> garbage
        // garbage를 삭제하기 위해서는 delete *it을 해야한다.

        // 반면에 polys는 포인터타입의 벡터가 아니라 polynomial 타입의 벡터
        // 벡터에서 한 칸은 erase하면 원소자체가 polynomial 타입의 객체이고
        // polynomial class의 디스트럭터는 자기자신을 삭제하기 전에
        // 자기가 거느리던 모든 객체를 삭제해주기 때문에 (clearMembers)
        // 벡터의 erase메서드 자체가 벡터의 원소의 디스트럭터를 호출해주기 때문에 충분
    }

    void list_polys(ostream &out)
    {
        for (auto &p : polys)
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
