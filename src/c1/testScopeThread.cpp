#include <iostream>
#include <thread>
#include <exception>
#include <chrono>

using namespace std;

class ScopeThread
{
public:
    explicit ScopeThread(thread t) : t_(move(t))
    {
        if (!t_.joinable())
            throw logic_error("No thread");
    }

    ~ScopeThread()
    {
        t_.join();
    }

    ScopeThread(ScopeThread const &) = delete;
    ScopeThread &operator=(ScopeThread const &) = delete;

private:
    thread t_;
};

struct ThreadFunc
{
    void operator()()
    {
        while (1)
        {
            cout << "ThreadFunc" << endl;
            this_thread::sleep_for(chrono::milliseconds(500));
        }
    }
};

void f(int inData)
{
    while (1)
    {
        cout << "f : " << inData << endl;
        this_thread::sleep_for(chrono::milliseconds(500));
    }
}

int main(int argc, char **argv)
{
    ThreadFunc func;

    // ScopeThread t1(thread(f, 1));
    ScopeThread t1(move(thread(&ThreadFunc::operator(), &func)));

    for (int i = 0; i < 10; i++)
    {
        cout << "main thread : " << i << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }

    return 0;
}