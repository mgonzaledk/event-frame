#include <Event/Event.h>

Event::Event() :
    id(0) {}

Event::Event(int id) :
    id(id) {}

int Event::GetId() const {
    return id;
}

void Event::SetId(int id) {
    this->id = id;
}
