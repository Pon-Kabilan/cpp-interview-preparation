mutex m1;
mutex m2;

void thread1()
{
    lock_guard<mutex> lock1(m1);

    // Waiting for m2
    lock_guard<mutex> lock2(m2);
}

void thread2()
{
    lock_guard<mutex> lock2(m2);

    // Waiting for m1
    lock_guard<mutex> lock1(m1);
}
