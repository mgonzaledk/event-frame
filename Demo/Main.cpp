#include <iostream>
#include <thread>

#include <Lock/Semaphore.h>
#include <Event/Key.h>

#define N 2

void counter(Semaphore *semaphore, int *globalCounter) {
    for(int i = 0; i < 50; ++i) {
        semaphore->Wait();
        *globalCounter += 1;
        semaphore->Signal();
    }
} 

int main(int argc, char **argv) {
    (void)argc, (void)argv;

    std::cout << EventType<3>().GetId();

    Semaphore semaphore(1);
    int globalCounter = 0;
    std::thread threadCounters[N];
    
    for(size_t i = 0; i < N; ++i) {
        threadCounters[i] = std::thread(counter, &semaphore, &globalCounter);
    }
    
    for(size_t i = 0; i < N; ++i) {
        threadCounters[i].join();
    }

    std::cout << "[*] Global counter: " << globalCounter << std::endl;

    if(globalCounter != 100) {
        std::cerr << "[!] UNEXPECTED RESULT" << std::endl;
    }

    return 0;
}
