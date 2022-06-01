#include <iostream>
#include <exception>
#include <thread>

using namespace std;

void threadFunc()
{
    for (int i = 0; i < 5; i++)
    {
        this_thread::sleep_for(1s);
        cout << "threadFunc " << i << endl;
    }
}

void func()
{
    throw "test error exception";
}

int main(int argc, char **argv)
{
    thread t(threadFunc);
    try
    {
        func();
    }
    catch (const char *error)
    {
        cout << error << endl;
        t.join();
        throw;
    }
    t.join();

    return 0;
}