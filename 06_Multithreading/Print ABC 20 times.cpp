#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

mutex m;
condition_variable cv;

int turn = 0;
const int COUNT = 20;

void printA()
{
    for (int i = 0; i < COUNT; i++)
    {
        unique_lock<mutex> lock(m);
        cv.wait(lock, [] {
            return turn == 0;
        });

        cout << "A";

        turn = 1;

        lock.unlock();
        cv.notify_all();
    }
}

void printB()
{
    for (int i = 0; i < COUNT; i++)
    {
        unique_lock<mutex> lock(m);

        cv.wait(lock, [] {
            return turn == 1;
        });

        cout << "B";

        turn = 2;

        lock.unlock();
        cv.notify_all();
    }
}

void printC()
{
    for (int i = 0; i < COUNT; i++)
    {
        unique_lock<mutex> lock(m);

        cv.wait(lock, [] {
            return turn == 2;
        });

        cout << "C";

        turn = 0;

        lock.unlock();
        cv.notify_all();
    }
}

int main()
{
    thread t1(printA);
    thread t2(printB);
    thread t3(printC);

    t1.join();
    t2.join();
    t3.join();
}
