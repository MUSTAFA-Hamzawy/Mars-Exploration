//
// Created by Mustafa Hamzawy on 8/2/2022.
//

#ifndef FILE_CANCELLATIONEVENT_H
#define FILE_CANCELLATIONEVENT_H
#include "../Mission/mixed_missions_struct.h"
#include <iostream>
using namespace std;
#include "Event.h"
class CancellationEvent : public Event{

public:
    void set_data(int event_day, int mission_id){
        this->event_day = event_day;
        this->mission_id = mission_id;
    }

    void execute(mixed_missions_struct &waiting_missions){
        // find the mission in the mountainous queue
        queue<Mission>temp;
        Mission target(-1);
        while (! waiting_missions.mountainous_missions.empty()){
            bool condition = waiting_missions.mountainous_missions.front().get_id() == mission_id;
            if (condition){
                target = waiting_missions.mountainous_missions.front();
            }else{
                temp.push(waiting_missions.mountainous_missions.front());
            }
            waiting_missions.mountainous_missions.pop();
        }
        waiting_missions.mountainous_missions = temp;
        if (target.get_id() == -1)
        {
            cerr << "Can't cancel this event, This mission is not in the waiting list\n";
            return;
        }
    }

    void print_info(){
        cout << "event_day" << event_day << endl;
        cout << "mission_id" << mission_id << endl;

    }
};


#endif //FILE_CANCELLATIONEVENT_H
