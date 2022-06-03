#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <string>

using namespace std;

class Sample
{
public:
    void init(string s)
    {
        for (int i = 0; i < 5; i++)
        {
            cout << "init by " << s << endl;
            this_thread::sleep_for(chrono::seconds(2));
        }

        name_ = "Sample";
    }

    void sendData()
    {
        call_once(initFlag_, &Sample::init, this, string("send"));
        cout << "send" << endl;
    }

    void recieveData()
    {
        call_once(initFlag_, &Sample::init, this, string("recieve"));
        cout << "recieve" << endl;
    }

private:
    std::once_flag initFlag_;
    string name_;
};

int main(int argc, char **argv)
{
    Sample sample;
    thread t2(&Sample::recieveData, &sample);
    thread t1(&Sample::sendData, &sample);

    t1.join();
    t2.join();

    return 0;
}