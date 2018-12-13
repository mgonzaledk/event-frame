#include <chrono>

#include <Thread/BaseStoppable.h>

BaseStoppable::BaseStoppable() :
    BaseThread(), object(signal.get_future()) {}

void BaseStoppable::Stop() {
    signal.set_value();
}

bool BaseStoppable::Stopping() {
    if(object.wait_for(std::chrono::milliseconds(0)) ==
        std::future_status::timeout
    ) {
        return false;
    }

    return true;
}
