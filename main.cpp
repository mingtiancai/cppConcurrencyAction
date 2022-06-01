#include <iostream>
#include <thread>

using namespace std;

int main(int argc, char **argv)
{

    cout << "1" << endl;
    cout << "2" << endl;
    this_thread::sleep_for(2s);

    cout << "3" << endl;
    cout << "4" << endl;

    return 0;
}