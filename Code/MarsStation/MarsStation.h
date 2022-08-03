//
// Created by Mustafa Hamzawy on 8/2/2022.
//

#ifndef FILE_MARSSTATION_H
#define FILE_MARSSTATION_H

#include <queue>
#include "../Rover/Rover.h"
#include "../Mission/Mission.h"
#include "../UserInterface/UI.h"
#include "../Mission/mixed_missions_struct.h"

class MarsStation {
private:
    queue<Rover> available_rovers[3];                     // index 0 for emergency, index 1 for polar, index 2 for mountainous
    queue<Rover> checkup_rovers[3];                     // index 0 for emergency, index 1 for polar, index 2 for mountainous
    queue<Event*> events;
    mixed_missions waiting_missions;
    priority_queue<Mission>executing_missions;
    UI user_interface;
    int current_day;
public:

    MarsStation(){
        current_day = 1;
    }

    void read_input(){
        user_interface.readInputFile();

        // TODO : create rovers

        events = user_interface.fetch_events();
    }

    void check_events(){
        bool stop = false;
        do {
            Event* current_event = events.front();
            if (current_event->get_event_day() == current_day){
                events.pop();
                current_event->execute(waiting_missions);
            }
            else
                stop = true;
        }while(! stop)
    }

    bool check_and_assign_emergency_missions(){

        if (waiting_missions.emergency_mission.empty())
            return true;

        if (! available_rovers[0].empty())      // check for available emergency rover
        {
            // pop the rover from the available list
            Rover rover_1 = available_rovers[0].front();
            available_rovers[0].pop();

            // assign the mission to it
            rover_1.assign_mission(waiting_missions.emergency_mission.front());
            executing_missions.push(waiting_missions.emergency_mission.front()); // TODO : set the priority here be the mission_duration
            waiting_missions.emergency_mission.pop();
            return true;

        }else if(! available_rovers[2].empty())// check for available mountainous rover
        {
            // pop the rover from the available list
            Rover rover_2 = available_rovers[2].front();
            available_rovers[2].pop();

            // assign the mission to it
            rover_2.assign_mission(waiting_missions.emergency_mission.front());
            executing_missions.push(waiting_missions.emergency_mission.front()); // TODO : set the priority here be the mission_duration
            waiting_missions.emergency_mission.pop();
            return true;
        }else if(! available_rovers[1].empty())// check for available polar rover
        {
            // pop the rover from the available list
            Rover rover_3 = available_rovers[1].front();
            available_rovers[1].pop();

            // assign the mission to it
            rover_3.assign_mission(waiting_missions.emergency_mission.front());
            executing_missions.push(waiting_missions.emergency_mission.front()); // TODO : set the priority here be the mission_duration
            waiting_missions.emergency_mission.pop();
            return true;
        }
        else return false;
    }

    void check_and_assign_mountainous_missions(){
        if (! available_rovers[2].empty())      // check for available mountainous rover
        {
            // pop the rover from the available list
            Rover rover_1 = available_rovers[2].front();
            available_rovers[2].pop();

            // assign the mission to it
            rover_1.assign_mission(waiting_missions.mountainous_mission.front());
            executing_missions.push(waiting_missions.mountainous_mission.front()); // TODO : set the priority here be the mission_duration
            waiting_missions.mountainous_mission.pop();

        }else if(! available_rovers[0].empty())// check for available mountainous rover
        {
            // pop the rover from the available list
            Rover rover_2 = available_rovers[0].front();
            available_rovers[0].pop();

            // assign the mission to it
            rover_2.assign_mission(waiting_missions.mountainous_mission.front());
            executing_missions.push(waiting_missions.mountainous_mission.front()); // TODO : set the priority here be the mission_duration
            waiting_missions.mountainous_mission.pop();
        }
    }

    void check_and_assign_polar_missions(){
        if (! available_rovers[1].empty())      // check for available mountainous rover
        {
            // pop the rover from the available list
            Rover rover_1 = available_rovers[1].front();
            available_rovers[1].pop();

            // assign the mission to it
            rover_1.assign_mission(waiting_missions.polar_mission.front());
            executing_missions.push(waiting_missions.polar_mission.front()); // TODO : set the priority here be the mission_duration
            waiting_missions.polar_mission.pop();

        }
    }

    void check_waiting_missions(){

        // check emergency missions     ( can be assigned to any type of rovers in this order : emergency, mountainous, polar )
        if (! check_and_assign_emergency_missions())
            return;     // there is no available rovers, so return

        // check mountainous missions    ( can be assigned to mountainous or emergency rover )
        check_and_assign_mountainous_missions();

        // check polar missions         ( assigned to polar rovers only )
        check_and_assign_polar_missions();

    }

    void simulate(){

        // read input file
        read_input();

        bool finished = false;

        while (! finished)
        {
            // 1- check events and execute them
            check_events();

            // 2- check waiting missions to assign them to available rovers
            check_waiting_missions();

            // 3- collect statistics that needed to create the output file

            currentDay++;
        }


        // 6- call the output function
    }

};


#endif //FILE_MARSSTATION_H
