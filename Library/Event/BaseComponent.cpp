#include <algorithm>
#include <iostream>

#include <Event/BaseComponent.h>

BaseComponent::EventMap BaseComponent::events =
    BaseComponent::EventMap();

std::mutex BaseComponent::eventsLock;

void BaseComponent::DeleteAll() {
    std::lock_guard<std::mutex> lock(queueLock);

    while(!queue.empty()) {
        delete queue.front();
        queue.pop();
    }
}

void BaseComponent::Run() {
    Init();

    while(!Stopping()) {
        if(queueLock.try_lock()) {
            if(queue.empty()) {
                queueLock.unlock();
            } else {
                Event *ev = queue.front();
                queue.pop();

                queueLock.unlock();

                Handler(ev);
                delete ev;
            }
        }

        Process();
    }

    End();
}

void BaseComponent::AddEvent(const Event &ev) {
    std::lock_guard<std::mutex> lock(queueLock);

    queue.push(new Event(ev));
}

BaseComponent::BaseComponent() :
    BaseStoppable() {}

void BaseComponent::Publish(const Event &ev) {
    std::lock_guard<std::mutex> lock(eventsLock);
    Event::Type type = ev.GetType();

    for(size_t i = 0; i < events[type].size(); ++i) {
        if(events[type][i] == nullptr) {
            throw;
        }

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
    
    if(eIt == events.end()) {
        throw;
    }

    std::vector<BaseComponent *>::iterator vIt =
        std::find(eIt->second.begin(), eIt->second.end(), this);
    
    if(vIt == eIt->second.end()) {
        throw;
    }

    eIt->second.erase(vIt);
}

BaseComponent::~BaseComponent() {}
