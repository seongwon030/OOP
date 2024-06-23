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

    string toString() override // 메소드 오버라이딩
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
    Computer myComputer("Acme", "Intel", 2, 160, 2.4);
    Notebook yourComputer("DellGate", "AMD", 4, 240,
                          1.8, 15.0, 7.5);
    cout << "My computer is:\n" +
                myComputer.toString()
         << endl;

    cout << endl;
    // Notebook 클래스의 toString 메서드가 실행됨
    cout << "Your computer is:\n" +
                yourComputer.toString()
         << endl;
}
