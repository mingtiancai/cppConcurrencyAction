#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <chrono>
#include <queue>
#include <memory>

using namespace std;

template <typename T>
class ThreadSafeQueue
{
public:
    ThreadSafeQueue()
    {
    }

    ThreadSafeQueue(ThreadSafeQueue const &other)
    {
        lock_guard<mutex> lock(other.dataMutex_);
        lock_guard<mutex> lockSelf(dataMutex_);
        dataQueue_ = other.dataQueue_;
    }

    void push(T newValue)
    {
        lock_guard<mutex> lock(dataMutex_);
        dataQueue_.push(newValue);
        cout << "push: " << newValue << endl;
        dataConditionVariable_.notify_one();
    }

    void waitAndPop(T &value)
    {
        unique_lock<mutex> lock(dataMutex_);
        dataConditionVariable_.wait(lock, [this]()
                                    { return !dataQueue_.empty(); });
        value = dataQueue_.front();
        cout << "wait pop : " << value << endl;
        dataQueue_.pop();
    }

    shared_ptr<T> waitAndPop()
    {
        unique_lock<mutex> lock(dataMutex_);
        dataConditionVariable_.wait(lock, [this]
                                    { return !dataQueue_.empty(); });
        shared_ptr<T> res(make_shared<T>(dataQueue_.front));
        dataQueue_.pop();
        return res;
    }

    bool tryPop(T &value)
    {
        lock_guard<mutex> lock(dataMutex_);
        if (dataQueue_.empty())
            return false;
        value = dataQueue_.front();
        dataQueue_.pop();
        return true;
    }

    std::shared_ptr<T> tryPop()
    {
        lock_guard<mutex> lock(dataMutex_);
        if (dataQueue_.empty())
            return nullptr;
        shared_ptr<T> res = make_shared<T>(dataQueue_.front());
        dataQueue_.pop();
        return res;
    }

    bool empty() const
    {
        lock_guard<mutex> lock(dataMutex_);
        return dataQueue_.empty();
    }

private:
    mutable mutex dataMutex_;
    queue<T> dataQueue_;
    condition_variable dataConditionVariable_;
};

int main(int argc, char **argv)
{
    ThreadSafeQueue<string> queueSample;
    queueSample.push("name1");
    queueSample.push("name2");

    string getSample1, getSample2;

    typedef void (ThreadSafeQueue<string>::*func1)(string & value);

    thread t1(&ThreadSafeQueue<string>::push, &queueSample, string("name3"));
    thread t2(func1(&ThreadSafeQueue<string>::waitAndPop), &queueSample, ref(getSample1));
    thread t3(func1(&ThreadSafeQueue<string>::waitAndPop), &queueSample, ref(getSample2));

    t1.join();
    t2.join();
    t3.join();

    cout << "getSample1: " << getSample1 << endl;
    cout << "getSample2: " << getSample2 << endl;

    return 0;
}
