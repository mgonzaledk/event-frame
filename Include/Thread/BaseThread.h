#ifndef BASETHREAD_H
#define BASETHREAD_H

#include <atomic>
#include <thread>

class BaseThread {
    protected:
        std::atomic<int> exit;
        std::thread thread;

    public:
        BaseThread();

        void Start(int detach = 0);
        void Wait();

        virtual void Run() = 0;

        void operator()(int detach = 0);

        ~BaseThread();
};

#endif
