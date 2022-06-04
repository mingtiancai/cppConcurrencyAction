#include <iostream>
#include <thread>
#include <mutex>
#include <future>
#include <chrono>

using namespace std;

int doSomething()
{
    for (int i = 0; i < 10; i++)
    {
        cout << "do something: " << i << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }

    return 1;
}

int main(int agrc, char **argv)
{
    future<int> res = async(doSomething);

    for (int i = 0; i < 10; i++)
    {
        cout << "main: " << i << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }

    auto result = res.get();

    cout << "res: " << result << endl;
    cout << "res: " << result << endl;
    cout << "res: " << result << endl;

    return 0;
}