#ifndef EVENT_H
#define EVENT_H

class Event {
    public:
        typedef int Type;

    protected:
        Type id;
    
    public:
        Event();
        Event(Type id);
        Event(const Event &ev);

        Type GetId() const;

        virtual ~Event();
};

#endif
