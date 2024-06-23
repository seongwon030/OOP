int *g()
{
    int *px;
    *px = 10;  // 초기화되지 않은 포인터를 역참고하고 값을 할당하려고 함
    return px; // 초기화되지 않은 포인터를 반환
}

// 1. 동적 메모리를 사용
int *g()
{
    int *px = new int; // 동적 메모리 할당
    *px = 10;          // 할당된 메모리에 값 저장
    return px;         // 포인터 반환
}

int main()
{
    int *p = g();
    cout << *p << endl; // 출력: 10
    delete p;           // 동적 메모리 해제
    return 0;
}

// 2. 정적 또는 전역 변수를 사용해 포인터 반환
int *g()
{
    static int x; // 정적 변수 선언
    x = 10;
    return &x; // 정적 변수의 주소 반환
}

int main()
{
    int *p = g();
    cout << *p << endl; // 출력: 10
    return 0;
}
