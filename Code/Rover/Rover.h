//
// Created by Mustafa Hamzawy on 8/1/2022.
//

#ifndef MARS_EXPLORATION_ROVER_H
#define MARS_EXPLORATION_ROVER_H
#include "../Mission/Mission.h"
Class Rover{
private:
    int checkup_duration;
    int days_count_in_checkup_station;
    int speed;
    int num_of_missions_before_checkup;
    int num_of_finished_missions;
    Mission mission;
public:

    Rover{
    num_of_finished_missions = 0;
    days_count_in_checkup_station = 0;
    }
    void assign_mission(Mission m){
        this->mission = m;
    }
    void set_data(checkup_duration, int speed, int num_of_missions_before_checkup){
        this.checkup_duration = checkup_duration;
        this.speed = speed;
        this.num_of_missions_before_checkup = num_of_missions_before_checkup;

    }
    bool need_checkup(){
        return num_of_missions_before_checkup == num_of_finished_missions;
    }
    void increment_finished_missions(){
    num_of_finished_missions++;
    }
    void increment_checkup_days(){
    days_count_in_checkup_station++;
    }
    bool finished_checkup_duration()
    {
        if(days_count_in_checkup_station == checkup_duration)
        {
            days_count_in_checkup_station= 0;
            return true;
        }
        return false;

    }
    Mission get_mission(){
        return mission;
    }


};


#endif //MARS_EXPLORATION_ROVER_H
