#ifndef EVENT_KEY_H
#define EVENT_KEY_H

#include <Event/Event.h>

template<class T>
class TypeEvent : public Event {
    private:
        T object;

    public:
        TypeEvent() :
            Event() {}
        
        TypeEvent(Event::Type type, T &object) :
            Event(type), object(object) {}
        
        TypeEvent(const TypeEvent<T> &ev) :
            Event(ev.id), object(ev.object) {}
        
        T &GetObject() {
            return object;
        }

        virtual ~TypeEvent() {}
};

#endif
