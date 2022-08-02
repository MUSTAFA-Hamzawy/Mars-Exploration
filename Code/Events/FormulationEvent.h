//
// Created by Mustafa Hamzawy on 8/2/2022.
//
#include "Event.h"
#ifndef FILE_FORMULATIONEVENT_H
#define FILE_FORMULATIONEVENT_H

#include <iostream>
using namespace std;
class FormulationEvent : public Event{
private:
    char mission_type;
    int target_location;
    int num_of_days_to_finish;
    int significance;
public:
    void execute(){

    }

    void set_data(int event_day, int mission_id, char mission_typ, int target_loc, int num_of_days_to_finish, int significance){
        this->event_day = event_day;
        this->mission_id = mission_id;
        this->mission_type = mission_typ;
        this->target_location = target_loc;
        this->num_of_days_to_finish = num_of_days_to_finish;
        this->significance = significance;
    }

    void print_info(){
        cout << "event_day" << event_day << endl;
        cout << "mission_id" << mission_id << endl;
        cout << "mission_type" << mission_type << endl;
        cout << "target_location" << target_location << endl;
        cout << "num_of_days_to_finish" << num_of_days_to_finish << endl;
        cout << "significance" << significance << endl;

    }
};


#endif //FILE_FORMULATIONEVENT_H
