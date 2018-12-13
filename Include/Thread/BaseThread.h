#ifndef THREAD_BASETHREAD_H
#define THREAD_BASETHREAD_H

#include <atomic>
#include <thread>

class BaseThread {
    protected:
        std::thread thread;

    public:
        BaseThread();

        void Start(int detach = 0);
        void Wait();

        virtual void Run() = 0;

        void operator()(int detach = 0);
};

#endif
