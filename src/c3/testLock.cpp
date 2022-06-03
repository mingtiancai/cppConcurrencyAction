#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

using namespace std;

void swap(int &lId, int &rId)
{
    int tmpId = lId;
    lId = rId;
    rId = tmpId;
}

class X
{
private:
    int id_;
    mutex m_;

public:
    X(int id) : id_(id) {}
    friend void swap(X &lhs, X &rhs)
    {
        if (&lhs.m_ == &rhs.m_)
            return;
        // lock(lhs.m_, rhs.m_);
        // lock_guard<mutex> lockL(lhs.m_, std::adopt_lock);
        // lock_guard<mutex> lockR(rhs.m_, std::adopt_lock);
        scoped_lock guard(lhs.m_, rhs.m_); // 等效上面三行
        cout << "swap" << endl;
        swap(lhs.id_, rhs.id_);
    }

    void print()
    {
        lock_guard<mutex> lock(m_);
        cout << id_ << endl;
        this_thread::sleep_for(chrono::seconds(5));
    }
};

int main(int argc, char **argv)
{
    X x1(1);
    X x2(2);

    x1.print();
    x2.print();

    swap(x1, x2);

    x1.print();
    x2.print();

    return 0;
}
