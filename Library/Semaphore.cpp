#include <Lock/Semaphore.h>

#ifdef WIN_C
    #include <Windows.h>
#elif defined(LIN_C)
    #include <errno.h>
    #include <semaphore.h>
    #include <time.h>
#endif

void Semaphore::Init(unsigned int count) {
    #ifdef WIN_C
        handle = CreateSemaphore(nullptr, count, LONG_MAX, nullptr);
    #elif defined(LIN_C)
        sem_init(&handle, 0, count);
    #endif
}

void Semaphore::Deinit() {
    #ifdef WIN_C
        CloseHandle(handle);
    #elif defined(LIN_C)
        sem_destroy(&handle);
    #endif
}

#ifdef WIN_C
WaitType Semaphore::WaitWindows(unsigned int milliseconds) {
    DWORD wait = WaitForSingleObject(handle, milliseconds);

    switch(wait) {
        case WAIT_OBJECT_0: return WaitType::SUCCESS;
        case WAIT_TIMEOUT: return WaitType::TIMED_OUT;
    }

    return WaitType::ERROR;
}

void Semaphore::SignalWindows() {
    ReleaseSemaphore(handle, 1, nullptr);
}
#elif defined(LIN_C)
WaitType Semaphore::WaitLinux(unsigned int milliseconds) {
    int wait;
    struct timespec timespec;
    
    clock_gettime(CLOCK_REALTIME, &timespec);

    timespec.tv_nsec += milliseconds * 1E6;
    timespec.tv_sec += timespec.tv_nsec / 1E9;
    timespec.tv_nsec %= (__syscall_slong_t)1E9;

    do {
        wait = sem_timedwait(&handle, &timespec);
    } while(wait == -1 && errno == EINTR);

    if(!wait) {
        return WaitType::SUCCESS;
    }

    return errno == ETIMEDOUT ?
        WaitType::TIMED_OUT :
        WaitType::ERROR;
}

void Semaphore::SignalLinux() {
    sem_post(&handle);
}
#endif

Semaphore::Semaphore() {
    Init(1);
}

Semaphore::Semaphore(unsigned int count) {
    Init(count);
}

void Semaphore::Signal() {
    #ifdef WIN_C
        SignalWindows();
    #elif defined(LIN_C)
        SignalLinux();
    #endif
}

WaitType Semaphore::Wait(unsigned int milliseconds) {
    #ifdef WIN_C
        return WaitWindows(milliseconds);
    #elif defined(LIN_C)
        return WaitLinux(milliseconds);
    #endif
}

Semaphore::~Semaphore() {
    Deinit();
}
