#include <iostream>
#include <thread>
#include <mutex>
#include <future>
#include <chrono>
#include <string>

using namespace std;

int doSomething(string str)
{
    for (int i = 0; i < 10; i++)
    {
        cout << str << " --- "
             << "do something: " << i << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }

    return 1;
}

int main(int agrc, char **argv)
{
    string name = "test";
    future<int> res = async(doSomething, ref(name));

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