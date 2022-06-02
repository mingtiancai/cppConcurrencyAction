#include <iostream>
#include <thread>
#include <memory>
#include <string>

using namespace std;

struct Data
{
    void setData(int id, string name)
    {
        id_ = id;
        name_ = name;
    }
    int id_;
    string name_;
};

void processFunc(unique_ptr<Data> dataPtr)
{
    cout << dataPtr->id_ << endl;
    cout << dataPtr->name_ << endl;
}

int main(int argc, char **argv)
{
    unique_ptr<Data> dataPtr(new Data);
    dataPtr->setData(1, "gao");

    thread t(processFunc, move(dataPtr));
    t.join();

    return 0;
}