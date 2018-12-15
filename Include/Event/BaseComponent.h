#ifndef EVENT_BASECOMPONENT_H
#define EVENT_BASECOMPONENT_H

#include <atomic>
#include <mutex>
#include <queue>
#include <thread>
#include <unordered_map>
#include <vector>

#include <Event/Event.h>
#include <Event/UserEvent.h>
#include <Thread/BaseStoppable.h>

class BaseComponent : public BaseStoppable {
    private:
        typedef std::unordered_map<
            Event::Type,
            std::vector<BaseComponent *>
        > EventMap;

        std::queue<Event *> queue;
        static EventMap events;

        std::mutex queueLock;
        static std::mutex eventsLock;

        void DeleteAll();
        virtual void Run();
    
    protected:
        template<class T>
        void AddEvent(const UserEvent<T> &ev) {
            std::lock_guard<std::mutex> lock(queueLock);

            queue.push(new UserEvent<T>(ev));
        }

        void AddEvent(const Event &ev);
    
    public:
        BaseComponent();

        template<class T>
        static void Publish(const UserEvent<T> &ev) {
            std::lock_guard<std::mutex> lock(eventsLock);
            Event::Type type = ev.GetType();

            for(size_t i = 0; i < events[type].size(); ++i) {
                if(events[type][i] == nullptr) {
                    throw;
                }

                events[type][i]->AddEvent<T>(ev);
            }
        }

        static void Publish(const Event &ev);

        void Subscribe(Event::Type type);
        void Unsubscribe(Event::Type type);

        virtual void Init() = 0;
        virtual void Process() = 0;
        virtual void Handler(Event *ev) = 0;
        virtual void End() = 0;

        ~BaseComponent();
};

#endif
