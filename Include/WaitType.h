#ifndef WAITTYPE_H
#define WAITTYPE_H

enum class WaitType : int {
    SUCCESS = 0,
    ERROR,
    TIMED_OUT,
    CANCELED
};

#endif
