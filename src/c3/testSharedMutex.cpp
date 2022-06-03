#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include <shared_mutex>
#include <map>
#include <string>

using namespace std;

struct Entry
{
    string name_;
};

class Cache
{
private:
    map<int, Entry> entries;
    mutable shared_mutex entryMutex;

public:
    Entry find(int id)
    {
        shared_lock<shared_mutex> lock(entryMutex);
        cout << "read threadId: " << this_thread::get_id() << endl;
        this_thread::sleep_for(chrono::seconds(1));

        auto it = entries.find(id);
        if (it == entries.end())
            return Entry();
        return it->second;
    }

    void update(int id, Entry &entry)
    {
        lock_guard<shared_mutex> lock(entryMutex);
        cout << "write threadId: " << this_thread::get_id() << endl;
        this_thread::sleep_for(chrono::seconds(5));
        entries[id] = entry;
    }
};

int main(int argc, char **argv)
{

    Cache cache;
    Entry entry1, entry2;
    entry1.name_ = "1";
    entry2.name_ = "2";

    thread t1(&Cache::update, &cache, 1, ref(entry1));
    thread t3(&Cache::update, &cache, 2, ref(entry2));
    thread t2(&Cache::find, &cache, 1);

    thread t4(&Cache::find, &cache, 1);
    thread t5(&Cache::find, &cache, 1);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();

    return 0;
}
