#ifndef EVENT_EVENT_H
#define EVENT_EVENT_H

class Event {
    public:
        typedef int Type;

    protected:
        Type type;
    
    public:
        Event();
        Event(Type type);
        Event(const Event &ev);

        Type GetType() const;

        virtual ~Event();
};

#endif
