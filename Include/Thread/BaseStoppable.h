#ifndef THREAD_BASESTOPPABLE_H
#define THREAD_BASESTOPPABLE_H

#include <future>

#include <Thread/BaseThread.h>

class BaseStoppable : public BaseThread {
    private:
        std::promise<void> signal;
        std::future<void> object;
    
    public:
        BaseStoppable();

        void Stop();
        bool Stopping();

        virtual void Run() = 0;
};

#endif
