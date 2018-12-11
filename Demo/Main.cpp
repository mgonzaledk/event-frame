#include <iostream>

#include <Lock/Semaphore.h>

int main(int argc, char **argv) {
    (void)argc, (void)argv;

    Semaphore sem;

    sem.Wait();
    sem.Signal();

    return 0;
}
