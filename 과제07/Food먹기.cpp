#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;

class GameObject
{ // 추상 클래스
protected:
    int distance; // 한 번 이동 거리
    int x, y;     // 현재 위치
public:
    GameObject(int startX, int startY, int distance)
    { // 초기 위치와 이동거리 설정
        this->x = startX;
        this->y = startY;
        this->distance = distance;
    }
    virtual ~GameObject(){};     // 가상 소멸자
    virtual void move() = 0;     // 이동한 후 새로운 위치로 x, y 변경
    virtual char getShape() = 0; // 객체의 모양을 나타내는 문자 리턴
    int getX() { return x; }
    int getY() { return y; }
    bool collide(GameObject *p)
    { // 이 객체가 객체 p와 충돌했으면 true 리턴
        if (this->x == p->getX() && this->y == p->getY())
            return true;
        else
            return false;
    }
};

class Human : public GameObject
{
public:
    Human(int x, int y, int dis) : GameObject(x, y, dis) {}
    void move();
    char getShape() { return 'H'; }
};
void Human::move()
{
    string key;
    for (;;)
    {
        cout << "왼쪽(a), 아래(s), 위(d), 오른쪽(f) >> ";
        cin >> key;
        if (key == "a")
        {
            if (y != 0)
            {
                y -= distance;
                break;
            }
            else
            {
                cout << "이동불가" << endl;
            }
        }
        else if (key == "s")
        {
            if (x != 9)
            {
                x += distance;
                break;
            }
            else
            {
                cout << "이동불가" << endl;
            }
        }
        else if (key == "d")
        {
            if (x != 0)
            {
                x -= distance;
                break;
            }
            else
            {
                cout << "이동불가" << endl;
            }
        }
        else if (key == "f")
        { // 오른쪽으로 이동
            if (y != 19)
            {
                y += distance;
                break;
            }
            else
                cout << "이동불가" << endl;
        }
        else
            cout << "입력 에러" << endl;
    }
}
class Monster : public GameObject
{
public:
    Monster(int x, int y, int dis) : GameObject(x, y, dis) { srand((unsigned)time(0)); } // 랜덤하게 이동하기때문에
    void move();
    char getShape() { return 'M'; }
};
void Monster::move()
{
    for (;;)
    {
        int n = rand() % 4;
        if (n == 0)
        {
            if (y > 1)
            {
                y -= distance;
                break;
            }
        }
        else if (n == 1)
        {
            if (x < 8)
            {
                x += distance;
                break;
            }
        }
        else if (n == 2)
        {
            if (x > 1)
            {
                x -= distance;
                break;
            }
        }
        else
        {
            if (y < 18)
            {
                y += distance;
                break;
            }
        }
    }
}
class Food : public GameObject
{
public:
    Food(int x, int y, int dis) : GameObject(x, y, dis) {}
    void move();
    char getShape() { return '@'; }
};
void Food::move()
{
    for (;;)
    {
        int n = rand() % 4;
        if (n == 0)
        {
            if (y != 0)
            {
                y -= distance;
                break;
            }
        }
        else if (n == 1)
        {
            if (x != 9)
            {
                x += distance;
                break;
            }
        }
        else if (n == 2)
        { // 위로 이동
            if (x != 0)
            {
                x -= distance;
                break;
            }
        }
        else
        {
            if (y != 19)
            { // 오른쪽으로 이동
                y += distance;
                break;
            }
        }
    }
}
class Game
{
    string board[10][20];
    Human *h = new Human(0, 0, 1);
    Monster *m = new Monster(5, 7, 2);
    Food *f = new Food(8, 10, 1);

public:
    Game()
    {
        srand((unsigned)time(0));
        cout << "** Human의 Food 먹기 게임을 시작합니다. **" << endl
             << endl;
        for (int i = 0; i < 10; ++i)
        {
            for (int j = 0; j < 20; ++j)
            {
                board[i][j] = "-";
            }
        }
    }
    ~Game() { delete h, delete m, delete f; }
    void game();
    void clr1()
    {
        board[h->getX()][h->getY()] = "-";
        board[m->getX()][m->getY()] = "-";
    }
    void clr2()
    {
        board[f->getX()][f->getY()] = "-";
    }
    void setXY()
    {
        board[h->getX()][h->getY()] = h->getShape();
        board[m->getX()][m->getY()] = m->getShape();
        board[f->getX()][f->getY()] = f->getShape();
    }
    void show()
    {
        for (int i = 0; i < 10; ++i)
        {
            for (int j = 0; j < 20; ++j)
                cout << board[i][j];
            cout << endl;
        }
    }
};
void Game::game()
{
    int count = 0, gamecount = 0;
    for (;;)
    {
        setXY();
        show();
        clr1();
        h->move(), m->move();
        int n = rand();
        cout << endl;
        // 5번 중 처음 3번은 랜덤하게 Food 이동
        if (n % 2 == 0 && count < 2 && gamecount <= 3)
        {
            clr2();
            f->move();
            ++count;
        }
        // 3번 돌고 나머지 2번 못
        if (gamecount > 3 && count < 2)
        {
            clr2();
            f->move();
            ++count;
        }
        if (f->collide(h))
        {
            setXY();
            board[f->getX()][f->getY()] = "H";
            show();
            cout << "Human is Winner!!" << endl;
            break;
        }
        else if (h->collide(m))
        { // 몬스터가 사람을 먹으면
            setXY();
            board[f->getX()][f->getY()] = "M";
            show();
            cout << "Monster is Winner!!" << endl;
            break;
        }
        else if (f->collide(m))
        { // 몬스터가 food 를 먹으면
            setXY();
            board[f->getX()][f->getY()] = "M";
            show();
            cout << "Monster is Winner!!" << endl;
            break;
        }
        ++gamecount;
        if ((gamecount % 5) == 0)
        {
            // food가 5번중 2번움직이게끔 하는것을 만들기위해
            count = 0;
            gamecount = 0;
        }
    }
}
int main()
{
    Game *g = new Game;
    g->game();
    delete g;
}