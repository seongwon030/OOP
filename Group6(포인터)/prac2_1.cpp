#include <iostream>

int *g
{
    int x = 10;
    return &x;
};

// 문제점
// 1. 지역변수의 생명주기 : 함수 g의 x 변수는 함수가 종료될 때 파괴됨
// 2. 유효하지 않는 메모리 참조 : 함수 g가 종료되고 x의 주소를 반환하면,
// 해당 주소는 더 이상 유효하지 않음

// 해결
// 1. 동적메모리 할당
int *g
{
    int *p = new int(10);
    return p;
};

// 2. 정적 변수 사용
int *g()
{
    static int x = 10; // 정적 변수로 선언합니다.
    return &x;
};
