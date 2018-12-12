#include <Event/Event.h>

Event::Event() :
    id(Type(0)) {}

Event::Event(Event::Type id) :
    id(id) {}

Event::Event(const Event &ev) :
    id(ev.id) {}

Event::Type Event::GetId() const {
    return id;
}

Event::~Event() {}
