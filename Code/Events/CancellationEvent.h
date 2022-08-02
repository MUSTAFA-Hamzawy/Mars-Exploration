//
// Created by Mustafa Hamzawy on 8/2/2022.
//

#ifndef FILE_CANCELLATIONEVENT_H
#define FILE_CANCELLATIONEVENT_H

#include <iostream>
using namespace std;
#include "Event.h"
class CancellationEvent : public Event{

public:
    void set_data(int event_day, int mission_id){
        this->event_day = event_day;
        this->mission_id = mission_id;
    }

    void execute(){

    }

    void print_info(){
        cout << "event_day" << event_day << endl;
        cout << "mission_id" << mission_id << endl;

    }
};


#endif //FILE_CANCELLATIONEVENT_H
