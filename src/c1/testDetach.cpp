#include <iostream>
#include <thread>

using namespace std;

void workerFunc()
{
    this_thread::sleep_for(2s);
    cout << "workerFunc" << endl;
}

int main(int argc, char **argv)
{
    thread t(workerFunc);
    t.detach();

    cout << "end" << endl;
    return 0;
}