#include <iostream>
#include <mutex>
#include <condition_variable>

using namespace std;

class Foo
{
private:
    mutex m;
    condition_variable cv;
    int step = 0;

public:

    void first()
    {
        unique_lock<mutex> lock(m);

        cout << "first ";

        step = 1;

        lock.unlock();
        cv.notify_all();
    }

    void second()
    {
        unique_lock<mutex> lock(m);

        cv.wait(lock, [this] {
            return step == 1;
        });

        cout << "second ";

        step = 2;

        lock.unlock();
        cv.notify_all();
    }

    void third()
    {
        unique_lock<mutex> lock(m);

        cv.wait(lock, [this] {
            return step == 2;
        });

        cout << "third ";
    }
};
