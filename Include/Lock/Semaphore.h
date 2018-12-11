#ifndef LOCK_SEMAPHORE
#define LOCK_SEMAPHORE

#include <OSCheck.h>
#include <WaitType.h>

#ifdef WIN_C
    #include <Windows.h>
#elif defined(LIN_C)
    #include <semaphore.h>
#endif

class Semaphore {
    private:
        #ifdef WIN_C
            void *handle;
        #elif defined(LIN_C)
            sem_t handle;
        #endif

        Semaphore(const Semaphore &) = delete;
        Semaphore &operator=(const Semaphore &) = delete;
    
        void Init(unsigned int count);
        void Deinit();

        #ifdef WIN_C
            WaitType WaitWindows(unsigned int milliseconds);
            void SignalWindows();
        #elif defined(LIN_C)
            WaitType WaitLinux(unsigned int milliseconds);
            void SignalLinux();
        #endif

    public:
        Semaphore();
        Semaphore(unsigned int count);

        void Signal();
        WaitType Wait(unsigned int milliseconds = 10000);

        ~Semaphore();
};

#endif
