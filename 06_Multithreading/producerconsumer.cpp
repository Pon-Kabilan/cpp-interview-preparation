#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

using namespace std;

queue<int> q;

mutex m;

condition_variable notFull;
condition_variable notEmpty;

const int MAX_SIZE = 5;

void producer()
{
    for (int i = 1; i <= 10; i++)
    {
        unique_lock<mutex> lock(m);

        notFull.wait(lock, [] {
            return q.size() < MAX_SIZE;
        });

        q.push(i);

        cout << "Produced: " << i << endl;

        lock.unlock();
        notEmpty.notify_one();
    }
}

void consumer()
{
    for (int i = 1; i <= 10; i++)
    {
        unique_lock<mutex> lock(m);

        notEmpty.wait(lock, [] {
            return !q.empty();
        });

        int value = q.front();
        q.pop();

        cout << "Consumed: " << value << endl;

        lock.unlock();
        notFull.notify_one();
    }
}

int main()
{
    thread p(producer);
    thread c(consumer);

    p.join();
    c.join();
}
