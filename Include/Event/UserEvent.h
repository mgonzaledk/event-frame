#ifndef EVENT_USEREVENT_H
#define EVENT_USEREVENT_H

#include <Event/Event.h>

template<class T>
class UserEvent : public Event {
    private:
        T object;

    public:
        UserEvent() :
            Event() {}
        
        UserEvent(Event::Type type, const T &object) :
            Event(type), object(object) {}
        
        UserEvent(const UserEvent<T> &ev) :
            Event(ev.type), object(ev.object) {}
        
        T &GetObject() {
            return object;
        }

        virtual ~UserEvent() {}
};

#endif
