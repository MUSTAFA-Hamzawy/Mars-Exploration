//
// Created by Mustafa Hamzawy on 8/1/2022.
//

#ifndef MARS_EXPLORATION_EVENT_H
#define MARS_EXPLORATION_EVENT_H
#include "../Mission/mixed_missions_struct.h"
class Event{
protected:
    int event_day;
    int mission_id;
public:
    virtual void execute(mixed_missions_struct waiting_missions) = 0;
    virtual void print_info() = 0;
    int get_event_day(mixed_missions_struct waiting_missions){
        return event_day;
    }
};

#endif //MARS_EXPLORATION_EVENT_H
