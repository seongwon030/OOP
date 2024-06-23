#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

// vector<int> 클래스처럼 제한이 없는 개수의 정수를 저장한다
// 인덱싱, 삽입, 삭제 등의 연산을 제공하는 클래스 OrderVecInt
// vector<int>와는 달리 정수들은 항상 오름차순으로 정렬된 순서로 저장된다
// 클래스 내부에서 vector를 사용하면 안된다

class OrderVecInt
{
private:
    int capacity = 0, size = 0;
    int *arr = nullptr;

    void resize(int new_capacity);

public:
    OrderVecInt();                   // 생성자
    ~OrderVecInt();                  // 소멸자
    void insert(int value);          // 정수삽입
    bool remove_by_val(int value);   // 정수삭제
    bool remove_by_index(int index); // 인덱스의 정수 삭제
    int &operator[](int index);
    int getSize() const; // 정수의 개수
};

OrderVecInt::OrderVecInt()
{
    capacity = 1;
    arr = new int[capacity];
}

OrderVecInt::~OrderVecInt()
{
    delete[] arr;
}

void OrderVecInt::insert(int value)
{
    if (size == capacity)
    {
        resize(2 * capacity); // 용량이 꽉 찼을 때 두 배로
    }

    // 오름차순으로 정수 삽입
    int index = size;
    while (index > 0 && arr[index - 1] > value)
    {
        arr[index] = arr[index - 1];
        index--;
    }
    arr[index] = value; // 올바른 위치에 값 삽입
    size++;             // size 증가
}

bool OrderVecInt::remove_by_val(int value)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == value)
        {
            for (int j = i; j < size - 1; j++)
            {
                arr[j] = arr[j + 1];
            }
            size--;
            return true;
        }
    }
    return false;
}

bool OrderVecInt::remove_by_index(int index)
{
    if (index < 0 || index >= size)
    {
        return false;
    }
    for (int i = index; i < size - 1; i++)
    {
        arr[i] = arr[i + 1];
    }
    size--;
    return true;
}

int &OrderVecInt::operator[](int index)
{
    if (index < 0 || index >= size)
    {
        cerr << "Index out of range" << endl;
        exit(1);
    }
    return arr[index];
}

// new_capacity 크기의 새로운 배열을 동적으로 할당합니다.
// 기존 배열의 요소들을 새로운 배열로 복사합니다.
// 기존 배열을 삭제하고 새로운 배열을 arr 포인터가 가리키도록 합니다.
// capacity 멤버 변수를 new_capacity로 업데이트합니다.
void OrderVecInt::resize(int new_capacity)
{
    int *new_arr = new int[new_capacity];
    for (int i = 0; i < size; i++)
    {
        new_arr[i] = arr[i];
    }
    delete[] arr;
    arr = new_arr;
    capacity = new_capacity;
}

int OrderVecInt::getSize() const
{
    return size;
}

int main()
{
    srand((unsigned int)time(NULL));
    int n, k;
    OrderVecInt vec;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int k = rand() % 1000;
        vec.insert(k);
    }

    for (int i = 0; i < vec.getSize(); i++)
    {
        cout << vec[i] << " ";
    }
    cout << endl;

    if (vec.remove_by_val(vec[2]))
    {
        cout << "Remove done" << endl;
    }
    else
    {
        cout << "Remove failed" << endl;
    }

    if (vec.remove_by_index(4))
    {
        cout << "RemoveIndex done" << endl;
    }
    else
    {
        cout << "RemoveIndex failed" << endl;
    }

    for (int i = 0; i < vec.getSize(); i++)
    {
        vec[i] -= 10;
    }

    for (int i = 0; i < vec.getSize(); i++)
    {
        cout << vec[i] << " ";
    }
    cout << endl;

    return 0;
}
