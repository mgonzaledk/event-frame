#ifndef EVENT_H
#define EVENT_H

class Event {
    private:
        int id;
    
    public:
        Event();
        Event(int id);

        int GetId() const;

        void SetId(int id);

        virtual ~Event();
};

#endif
