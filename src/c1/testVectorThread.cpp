#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

void workerFunc(int id)
{
    for (int i = 0; i < 10; i++)
    {
        cout << id << " : " << i << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }
}

int main(int argc, char **argv)
{
    vector<thread> threadVec;
    for (int i = 0; i < 20; i++)
    {
        threadVec.emplace_back(workerFunc, i);
    }

    for (auto &entry : threadVec)
    {
        entry.join();
    }

    return 0;
}