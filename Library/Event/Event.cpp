#include <Event/Event.h>

Event::Event() :
    type(Type(0)) {}

Event::Event(Event::Type type) :
    type(type) {}

Event::Event(const Event &ev) :
    type(ev.type) {}

Event::Type Event::GetType() const {
    return type;
}

Event::~Event() {}
