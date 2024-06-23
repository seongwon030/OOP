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
    Notebook(string man, string proc, int ram, int disk,
             double procSpeed, double screen, double weight) : Computer(man, proc, ram, disk, procSpeed),
                                                               screenSize(screen), weight(weight) {}

    string toString() override
    {
        string result = Computer::toString() +
                        "\nScreen size: " + to_string(screenSize) + " inches" +
                        "\nWeight: " + to_string(weight) + " pounds";
        return result;
    }

    double getScreenSize()
    {
        return screenSize;
    }

    double getWeight()
    {
        return weight;
    }
};

void someFunc(Computer &comp)
{
    cout << comp.toString() << endl
         << endl;
}

int main()
{

    Notebook theBook("Apple", "M2", 16, 16000, 2.5, 13.1, 1.2);

    Computer pc = theBook;      // 객체 슬라이싱 발생, Computer 부분만 복사됨
    Computer &ref_pc = theBook; // 참조이므로 슬라이싱 문제 없음
    Computer *ptr_pc = new Notebook("Dell", "Intel", 16, 2000, 1.8, 15.0, 1.5);
    // 동적할당과 가상함수 테이블로 다형성 유지

    //        cout << pc.getScreenSize() << endl;     // Error
    //        cout << ref_pc.getScreenSize() << endl;     // Error
    //        cout << ptr_pc->getScreenSize() << endl;     // Error

    cout << pc.toString() << endl
         << endl; // Computer::toString -> 슬라이싱 발생, pc는 Notebook부분에 접근 불가

    cout << ref_pc.toString() << endl
         << endl; // Notebook::toString -> 참조로 올바르게 호출

    someFunc(theBook);

    cout << ptr_pc->toString() << endl
         << endl; // Notebook::toString -> 포인터로 올바르게 호출

    delete ptr_pc;

    return 0;
}