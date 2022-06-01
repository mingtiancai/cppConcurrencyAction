#include <iostream>
#include <thread>

using namespace std;

void workerFunc1()
{
    while (1)
    {
        this_thread::sleep_for(2s);
        cout << "workerFunc1" << endl;
    }
}

void workerFunc2()
{
    while (1)
    {
        this_thread::sleep_for(2s);
        cout << "workerFunc2" << endl;
    }
}

int main(int argc, char **argv)
{
    thread t1(workerFunc1);
    thread t2(workerFunc2);
    t1.join();
    t2.join();

    cout << "end" << endl;
}