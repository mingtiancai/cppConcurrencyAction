#include <iostream>
#include <thread>
#include <future>
#include <mutex>
#include <utility>
#include <queue>
#include <string>

using namespace std;

struct FuncAndParam
{
    packaged_task<void(string)> task_;
    string param_;
};

class Demo
{
private:
    mutex taskQueueMutex_;
    queue<FuncAndParam> tasks_;
    bool isShutdown_;

public:
    Demo()
    {
        isShutdown_ = false;
    }

    bool getShutdownMsg()
    {
        lock_guard<mutex> lock(taskQueueMutex_);
        return isShutdown_;
    }

    void setShutDown()
    {
        lock_guard<mutex> lock(taskQueueMutex_);
        isShutdown_ = true;
    }

    void worker()
    {
        while (!getShutdownMsg())
        {
            cout << "worker" << endl;
            this_thread::sleep_for(chrono::seconds(1));
            packaged_task<void(string)> task;
            string param;
            {
                lock_guard<mutex> lock(taskQueueMutex_);
                if (tasks_.empty())
                    continue;
                task = move(tasks_.front().task_);
                param = move(tasks_.front().param_);
                tasks_.pop();
            }
            task(param);
        }
    }

    template <typename Func>
    future<void> postTask(Func func, string str)
    {
        packaged_task<void(string)> task(func);
        future<void> res = task.get_future();
        lock_guard<mutex> lock(taskQueueMutex_);
        FuncAndParam fap;
        fap.task_ = move(task);
        fap.param_ = str;
        tasks_.push(move(fap));
        return res;
    }
};

void func1(string str)
{
    for (int i = 0; i < 5; i++)
    {
        this_thread::sleep_for(chrono::seconds(1));
        cout << "func1: " << str << endl;
    }
}

int main(int argc, char **argv)
{
    Demo demo;

    string str = "111";
    demo.postTask<void(string)>(func1, ref(str));
    thread t1(&Demo::worker, &demo);

    str = "222";
    demo.postTask<void(string)>(func1, ref(str));

    this_thread::sleep_for(chrono::seconds(15));
    demo.setShutDown();

    t1.join();

    return 0;
}