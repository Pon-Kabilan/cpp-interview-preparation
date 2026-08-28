//Thread-Safe Counter: Mutex vs Atomic
//Using Mutex
int counter = 0;
mutex m;

void increment()
{
    lock_guard<mutex> lock(m);
    counter++;
}
//Using Atomic

//For a simple counter:

#include <atomic>

atomic<int> counter{0};

void increment()
{
    counter++;
}




//Additional info

/*When to use Atomic?

Good for simple operations:

counter++
counter--
flag = true
flag = false

When Mutex is needed?

Suppose you need:

Check balance
↓
Check if enough money exists
↓
Deduct money

These operations must happen together.

if (balance >= amount)
{
    balance -= amount;
}

A simple atomic operation is not enough for this complete logic.

Use a mutex to protect the critical section.

Remember

Atomic protects a simple operation. Mutex protects a critical section involving multiple operations./*
