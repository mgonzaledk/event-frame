#ifndef EVENT_BASECOMPONENT_H
#define EVENT_BASECOMPONENT_H

#include <atomic>
#include <mutex>
#include <queue>
#include <thread>
#include <unordered_map>
#include <vector>

#include <Event/Event.h>
#include <Event/TypeEvent.h>

class BaseComponent {
    private:
        typedef std::unordered_map<
            Event::Type,
            std::vector<BaseComponent *>
        > EventMap;

        std::queue<Event *> queue;
        static EventMap events;

        std::mutex queueLock;
        std::mutex eventsLock;

        void DeleteAll();
        void Loop();

    protected:
        std::atomic<int> exit;
        std::thread thread;

        template<class T>
        void AddEvent(const TypeEvent<T> &ev) {
            std::lock_guard<std::mutex> lock(queueLock);

            queue.push(new TypeEvent<T>(ev));
        }

        void AddEvent(const Event &ev);

    public:
        BaseComponent();

        void Start(int detached = 0);
        void Stop(int force = 0);
        void Wait();

        template<class T>
        void Publish(const TypeEvent<T> &ev) {
            std::lock_guard<std::mutex> lock(eventsLock);
            Event::Type type = ev.GetType();

            for(size_t i = 0; i < events[type].size(); ++i) {
                // events[type][i] != nullptr
                events[type][i]->AddEvent<T>(ev);
            }
        }

        void Publish(const Event &ev);

        void Subscribe(Event::Type type);
        void Unsubscribe(Event::Type type);

        virtual void Init() = 0;
        virtual void Run() = 0;
        virtual void Process(Event *ev) = 0;

        ~BaseComponent();
};

#endif
