#include <iostream>
#include <string>
using namespace std;

class Computer
{
private:
    string manufacturer;
    string processor;
    int ramSize;
    int diskSize;
    double processorSpeed;

public:
    Computer() = default;
    Computer(string man, string proc, int ram, int disk, double procSpeed) : manufacturer(man), processor(proc), ramSize(ram),
                                                                             diskSize(disk), processorSpeed(procSpeed) {}

    double computePower()
    {
        return ramSize * processorSpeed;
    }

    double getRamSize() { return ramSize; }
    double getProcessorSpeed() { return processorSpeed; }
    int getDiskSize() { return diskSize; }

    virtual string toString()
    {
        string result = "Manufacturer: " + manufacturer +
                        "\nCPU: " + processor +
                        "\nRAM: " + to_string(ramSize) + " megabytes" +
                        "\nDisk: " + to_string(diskSize) + " gigabytes" +
                        "\nProcessor speed: " + to_string(processorSpeed) +
                        " gigahertz";
        return result;
    }
};

class Notebook : public Computer
{
private:
    double screenSize;
    double weight;

public:
    Notebook() = default;
    Notebook(string man, string proc, int ram, int disk,
             double procSpeed, double screen, double weight) : Computer(man, proc, ram, disk, procSpeed),
                                                               screenSize(screen), weight(weight) {}
    // 파생클래스의 멤버들 중 베이스클래스에 속한 멤버들은 베이스클래스의 생성자를 이용해 초기화
    // 명시적으로 베이스클래스의 생성자를 호출해주지 않으면 베이스클래스의 디폴트 생성자를 자동 호출
    double getScreenSize()
    {
        return screenSize;
    }

    double getWeight()
    {
        return weight;
    }

    //    void faulty_method() {
    //        cout << manufacturer << endl;
    //    }
};

int main()
{
    Computer myComputer("Acme", "Intel", 2, 160, 2.4);
    Notebook yourComputer("DellGate", "AMD", 4, 240, 1.8, 15.0, 7.5);

    cout << yourComputer.getRamSize() << endl;
    cout << yourComputer.getDiskSize() << endl;
    cout << yourComputer.getScreenSize() << endl;
    cout << endl;

    cout << "My computer is:\n" + myComputer.toString() << endl;
    cout << endl;

    // yourComputer는 Notebook 객체이지만 toString() 메서드가
    // 상위클래스인 Computer클래스의 멤버이므로 screenSize와 weight를 출력할 수 없다
    cout << "Your computer is:\n" + yourComputer.toString() << endl;
    return 0;
}