#include <iostream>
#include <thread>
#include <string>

using namespace std;

struct Data
{
    int id_;
    string name_;
};

void threadFunc(int i, Data &data)
{
    cout << i << endl;
    cout << data.id_ << endl;
    cout << data.name_ << endl;
}

class C1
{
public:
    void print(Data &data)
    {
        cout << data.id_ << endl;
        cout << data.name_ << endl;
        cout << type << endl;
    }

private:
    string type = "c1";
};

int main(int argc, char **argv)
{
    Data data;
    data.id_ = 1;
    data.name_ = "sts";

    // 单独引用独立函数，形参是非const引用的时候
    // thread t(threadFunc, 9, std::ref(data));
    // t.join();

    C1 c1;

    // 引用类成员函数，形参非const引用的时候
    thread t(&C1::print, &c1, ref(data));
    t.join();

    return 0;
}