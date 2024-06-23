#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<int> vec;
    vec.push_back(10);
    int *ptr = &vec[0];
    // cout << *ptr << endl;
    vec.push_back(20);
    vec[0] = 30;
    cout << *ptr << endl;
    return 0;
}

// 메모리 재할당 문제
// 벡터에 새로운 요소를 추가할 때 벡터의 크기가 증가하여 현재 할당된 메모리보다 더 많은 메모리가 필요하면
// 벡터는 더 큰 메모리 블록을 할당하고 기존 요소들을 새로운 메모리 블록으로 복사. 원래 요소들의 주소는 무효화.
