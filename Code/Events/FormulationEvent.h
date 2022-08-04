//
// Created by Mustafa Hamzawy on 8/2/2022.
//
#include "Event.h"
#ifndef FILE_FORMULATIONEVENT_H
#define FILE_FORMULATIONEVENT_H
#include "../Mission/mixed_missions_struct.h"
#include <iostream>
#include "../Mission/Mission.h"
using namespace std;
class FormulationEvent : public Event{
private:
    Mission mission;
    char mission_type;

public:
    void execute(mixed_missions_struct &waiting_missions){

        if (mission_type == 'M')
            waiting_missions.mountainous_missions.push(mission);
        else if (mission_type = 'E')
            waiting_missions.emergency_missions.push(mission, mission.calc_prioriy());
        else
            waiting_missions.polar_missions.push(mission);

    }

    void set_data(int event_day, int mission_id, char mission_typ, int target_loc, int num_of_days_to_finish, int significance){
        this->event_day = event_day;
        this->mission_type = mission_typ;

        mission.set_info(mission_id, target_loc, num_of_days_to_finish, significance, event_day);
    }

};


#endif //FILE_FORMULATIONEVENT_H
