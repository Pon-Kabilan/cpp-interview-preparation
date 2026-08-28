#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

mutex m;
condition_variable cv;

int current = 1;
const int MAX = 10;

void printOdd()
{
    while (true)
    {
        unique_lock<mutex> lock(m);

        cv.wait(lock, [] {
            return current > MAX || current % 2 == 1;
        });

        if (current > MAX)
        {
            break;
        }

        cout << current << " ";

        current++;

        lock.unlock();
        cv.notify_all();
    }
}

void printEven()
{
    while (true)
    {
        unique_lock<mutex> lock(m);

        cv.wait(lock, [] {
            return current > MAX || current % 2 == 0;
        });

        if (current > MAX)
        {
            break;
        }

        cout << current << " ";

        current++;

        lock.unlock();
        cv.notify_all();
    }
}

int main()
{
    thread t1(printOdd);
    thread t2(printEven);

    t1.join();
    t2.join();
}
