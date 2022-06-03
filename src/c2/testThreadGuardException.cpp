#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

struct func
{
    int &_i;
    func(int &i) : _i(i) {}
    void operator()()
    {
        for (; _i < 2000; ++_i)
        {
            cout << _i << endl;
            this_thread::sleep_for(chrono::milliseconds(3));
        }
    }
};

class thread_guard
{
public:
    explicit thread_guard(thread &t) : _t(t)
    {
    }

    ~thread_guard()
    {
        if (_t.joinable())
            _t.join();
    }

    thread_guard(thread_guard const &) = delete;
    thread_guard &operator=(thread_guard const &) = delete;

private:
    thread &_t;
};

int main(int argc, char **argv)
{
    int var = 0;
    func myFunc(var);
    thread t(myFunc);
    thread_guard g(t);

    for (int j = 0; j < 1000; j++)
    {
        cout << " j: " << j << endl;
        this_thread::sleep_for(chrono::milliseconds(2));
    }
    throw;

    return 0;
}