#include <queue>
#include <mutex>
#include <condition_variable>

using namespace std;

class BlockingQueue
{
private:
    queue<int> q;

    mutex m;

    condition_variable notEmpty;
    condition_variable notFull;

    size_t capacity;

public:
    BlockingQueue(size_t size)
        : capacity(size)
    {
    }

    void put(int value)
    {
        unique_lock<mutex> lock(m);

        notFull.wait(lock, [this] {
            return q.size() < capacity;
        });

        q.push(value);

        lock.unlock();

        notEmpty.notify_one();
    }

    int take()
    {
        unique_lock<mutex> lock(m);

        notEmpty.wait(lock, [this] {
            return !q.empty();
        });

        int value = q.front();
        q.pop();

        lock.unlock();

        notFull.notify_one();

        return value;
    }
};
