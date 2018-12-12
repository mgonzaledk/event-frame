#ifndef EVENT_KEY_H
#define EVENT_KEY_H

#include <Event/Event.h>

template<Event::Type id>
class EventType {
    public:
        static constexpr Event::Type GetId() {
            return id;
        }
};

#endif
