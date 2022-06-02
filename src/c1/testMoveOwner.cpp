#include <iostream>
#include <thread>
#include <memory>
#include <string>
#include <chrono>

using namespace std;

void threadFunc1()
{
    while (1)
    {
        cout << "threadFunc1" << endl;
        cout << this_thread::get_id() << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }
}

void threadFunc2()
{
    while (1)
    {
        cout << "threadFunc2" << endl;
        cout << this_thread::get_id() << endl;
        this_thread::sleep_for(chrono::seconds(2));
    }
}

int main(int argc, char **argv)
{
    thread t1(threadFunc1);

    this_thread::sleep_for(chrono::seconds(2));

    thread t2 = move(t1);

    t1 = thread(threadFunc2);

    if (t1.joinable())
        t1.join();
    t2.join();

    return 0;
}