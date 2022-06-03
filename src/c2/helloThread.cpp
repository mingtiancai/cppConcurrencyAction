#include <iostream>
#include <thread>

using namespace std;

void workerFunc()
{
    cout << "workerFunc" << endl;
}

int main(int argc, char **argv)
{
    thread t(workerFunc);
    t.join();
    return 0;
}
