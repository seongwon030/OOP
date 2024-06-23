#include <iostream>
using namespace std;

void fun(int **a)
{
    // a가 새로운 정수형 메모리 주소를 가리키도록 함
    // 메모리는 동적으로 할당되며 값은 4로 초기화됨
    *a = new int(4);
}

int main()
{
    int *p;
    fun(&p);
    *p = 6;
    cout << *p;
    delete p;
    return 0;
}

// 문제점 : fun은 a가 새로운 메모리 주소를 가리키도록 하지만, 이는 함수 내에서만 유효
// 함수 호출 끝나면 a의 변경 사항이 호출자에게 반영되지 않음. main 함수 내에서 p는 여전히 초기화되지 않은 상태

// => 포인터를 함수 내에서 변경하려면 이중 포인터를 사용해야 함