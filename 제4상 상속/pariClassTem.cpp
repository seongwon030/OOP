#include <iostream>
using namespace std;

template <typename T>
class Pair
{
public:
    Pair(T first, T second) : first(first), second(second) {}
    T getFirst() { return first; }
    T getSecond() { return second; }

private:
    T first, second;
};

int main()
{
    Pair<int> intPair(1, 2);
    Pair<double> doublePair(3.5, 4.5);

    cout << intPair.getFirst() << ", " << intPair.getSecond() << endl;
    cout << doublePair.getFirst() << ", " << doublePair.getSecond() << endl;
}
