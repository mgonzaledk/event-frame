#include <BaseThread.h>

BaseThread::BaseThread() {}

void BaseThread::Start(int detach) {
    thread = std::thread(&BaseThread::Run, this);

    if(detach) {
        thread.detach();
    }
}

void BaseThread::Wait() {
    if(thread.joinable()) {
        thread.join();
    }
}
