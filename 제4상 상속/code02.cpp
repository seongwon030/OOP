#include <iostream>
#include <string>
using namespace std;

class Computer
{
private: //  데이터 멤버들을 private으로 바꿈
    string manufacturer;
    string processor;
    int ramSize;
    int diskSize;
    double processorSpeed;

public:
    double computePower()
    {
        return ramSize * processorSpeed;
    }

    double getRamSize() { return ramSize; }
    double getProcessorSpeed() { return processorSpeed; }
    int getDiskSize() { return diskSize; }

    string toString()
    {
        string result = "manufacturer: " + manufacturer +
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
    double getScreenSize()
    {
        return screenSize;
    }

    double getWeight()
    {
        return weight;
    }

    // 파생 클래스 내부에서 베이스 클래스에 속한 private 멤버는 액세스 할 수 없다 -> 오류
    void faulty_method()
    {
        dummy_method();
        cout << manufacturer << endl;
    }
};

int main()
{
    Notebook yourNotebook;
    //    yourNotebook.manufacturer = "Dell";
    //    yourNotebook.processor = "AMD";
    //    yourNotebook.ramSize = 16;
    //    yourNotebook.diskSize = 512;
    //    yourNotebook.processorSpeed = 2.6;
    //    yourNotebook.screenSize = 15.0;
    //    yourNotebook.weight = 1.8;
    cout << yourNotebook.computePower() << endl;
    cout << yourNotebook.getScreenSize() << endl;
    return 0;
}