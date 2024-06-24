#include <iostream>
using namespace std;

const int init_capacity = 1;
int *arr = nullptr;
int capacity = 0;
int n = 0;

void add_to_array(int k)
{
    // 새로운 배열 크기 결정
    int new_capcity;
    if (n == 0)
    {
        new_capcity = init_capacity;
    }
    else
    {
        new_capcity = 2 * capacity;
    }

    // 새로운 배열 동적 할당
    int *new_arr = new int[new_capcity];

    // 기존 데이터 복사
    for (int i = 0; i < n; i++)
    {
        new_arr[i] = arr[i];
    }

    // 새로운 요소 추가
    new_arr[n] = k;
    n++;

    // 기존 배열 해제
    delete[] arr;

    // 포인터 갱신
    arr = new_arr;
    capacity = new_capcity;

    // 배열의 모든 요소 출력
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main()
{
    int k;
    while (1)
    {
        cin >> k;
        if (k == -1)
        {
            break;
        }
        add_to_array(k);
    }
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    delete[] arr;
    return 0;
}
