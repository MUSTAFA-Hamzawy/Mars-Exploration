//
// Created by Mustafa Hamzawy on 8/1/2022.
//

#ifndef MARS_EXPLORATION_EVENT_H
#define MARS_EXPLORATION_EVENT_H

class Event{
protected:
    int event_day;
    int mission_id;
public:
    virtual void execute() = 0;
    virtual void print_info() = 0;
};

#endif //MARS_EXPLORATION_EVENT_H
