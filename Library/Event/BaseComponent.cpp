#include <algorithm>

#include <Event/BaseComponent.h>

void BaseComponent::DeleteAll() {
    std::lock_guard<std::mutex> lock(queueLock);

    while(!queue.empty()) {
        delete queue.front();
        queue.pop();
    }
}

void BaseComponent::Loop() {
    exit = false;

    Init();

    while(!exit) {
        if(queueLock.try_lock()) {
            if(queue.empty()) {
                queueLock.unlock();

                if(exit) exit = true;
            } else {
                Event *ev = queue.front();
                queue.pop();

                queueLock.unlock();

                Process(ev);
                delete ev;
            }
        }

        Run();
    }
}

void BaseComponent::AddEvent(const Event &ev) {
    std::lock_guard<std::mutex> lock(queueLock);

    queue.push(new Event(ev));
}

BaseComponent::BaseComponent() :
    exit(0) {}

void BaseComponent::Start(int detach) {
    exit.store(0, std::memory_order_relaxed);
    thread = std::thread(Loop, this);

    if(detach) {
        thread.detach();
    }
}

void BaseComponent::Stop(int force) {
    if(force) {
        DeleteAll();
    }

    exit.store(1, std::memory_order_relaxed);
}

void BaseComponent::Wait() {
    if(thread.joinable()) {
        thread.join();
    }
}

void BaseComponent::Publish(const Event &ev) {
    std::lock_guard<std::mutex> lock(eventsLock);
    Event::Type type = ev.GetType();

    for(size_t i = 0; i < events[type].size(); ++i) {
        // events[type][i] != nullptr
        events[type][i]->AddEvent(ev);
    }
}

void BaseComponent::Subscribe(Event::Type type) {
    std::lock_guard<std::mutex> lock(eventsLock);
    
    if(
        std::find(
            events[type].begin(), events[type].end(),
            this
        ) == events[type].end()
    ) {
        events[type].push_back(this);
    }
}

void BaseComponent::Unsubscribe(Event::Type type) {
    std::lock_guard<std::mutex> lock(eventsLock);

    EventMap::iterator eIt = events.find(type);
    // eIt != events.end()

    std::vector<BaseComponent *>::iterator vIt =
        std::find(eIt->second.begin(), eIt->second.end(), this);
    // vIt != eIt->second.end()

    eIt->second.erase(vIt);
}

BaseComponent::~BaseComponent() {}
