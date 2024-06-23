#include <iostream>
using namespace std;

template <typename T>
void bubblesort(T a[], int n)
{
    for (int i = n - 1; i > 0; i--)
    {
        for (int j = 0; j < i; j++)
        {
            if (a[j] > a[j + 1])
            {
                swap(a[j], a[j + 1]);
            }
        }
    }
}

int main()
{
    string s[5] = {"how", "fun", "is", "c++", "programming"};
    int a[5] = {10, 50, 30, 40, 20};
    int n = sizeof(a) / sizeof(a[0]);

    bubblesort<int>(a, n);
    bubblesort<string>(s, n);

    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;

    for (int i = 0; i < n; i++)
    {
        cout << s[i] << " ";
    }
    cout << endl;

    return 0;
}