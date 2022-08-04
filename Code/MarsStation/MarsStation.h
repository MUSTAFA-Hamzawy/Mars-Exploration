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
#include "../PriorityQueue.h"

class MarsStation {
private:
    queue<Rover> available_rovers[3];                     // index 0 for emergency, index 1 for polar, index 2 for mountainous
    queue<Rover> checkup_rovers[3];                     // index 0 for emergency, index 1 for polar, index 2 for mountainous
    queue<Rover> executing_rovers[3];                     // index 0 for emergency, index 1 for polar, index 2 for mountainous
    queue<Event*> events;
    mixed_missions waiting_missions;
    PriorityQueue executing_missions;
    queue<Mission>completed_missions;
    UI user_interface;
    int current_day;
    int num_of_executed_events;
    int num_of_auto_promoted;
public:

    MarsStation(){
        current_day = 1;
        num_of_executed_events = 0;
        num_of_auto_promoted= 0 ;
    }

    void read_input(){
        user_interface.readInputFile();

        //  create rovers
        for (int j = 0; j < user_interface.get_num_emergency_rovers(); ++j) {
            available_rovers[0].push(new Rover()->set_data(user_interface.get_checkup_duration(),
                                                           user_interface.get_speed_of_emergency_rover(),
                                                           user_interface.get_num_of_missions_before_emergency_checkup()));
        }
        for (int j = 0; j < user_interface.get_num_polar_rovers(); ++j) {
            available_rovers[1].push(new Rover()->set_data(user_interface.get_checkup_duration(),
                                                           user_interface.get_speed_of_polar_rover(),
                                                           user_interface.get_num_of_missions_before_polar_checkup()));
        }
        for (int j = 0; j < user_interface.get_num_mountainous_rovers(); ++j) {
            available_rovers[2].push(new Rover()->set_data(user_interface.get_checkup_duration(),
                                                           user_interface.get_speed_of_mountainous_rover(),
                                                           user_interface.get_num_of_missions_before_mountainous_checkup()));
        }

        // assign the events from the input file
        events = user_interface.fetch_events();
    }

    void check_events(){
        bool stop = false;
        do {
            Event* current_event = events.front();
            if (current_event->get_event_day() == current_day){
                events.pop();
                current_event->execute(waiting_missions);
                num_of_executed_events++;
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
            executing_missions.push(waiting_missions.emergency_mission.front(), waiting_missions.emergency_mission.front().get_duration());
            waiting_missions.emergency_mission.pop();
            return true;

        }else if(! available_rovers[2].empty())// check for available mountainous rover
        {
            // pop the rover from the available list
            Rover rover_2 = available_rovers[2].front();
            available_rovers[2].pop();

            // assign the mission to it
            rover_2.assign_mission(waiting_missions.emergency_mission.front());
            executing_missions.push(waiting_missions.emergency_mission.front(), waiting_missions.emergency_mission.front().get_duration());
            waiting_missions.emergency_mission.pop();
            return true;
        }else if(! available_rovers[1].empty())// check for available polar rover
        {
            // pop the rover from the available list
            Rover rover_3 = available_rovers[1].front();
            available_rovers[1].pop();

            // assign the mission to it
            rover_3.assign_mission(waiting_missions.emergency_mission.front());
            executing_missions.push(waiting_missions.emergency_mission.front(), waiting_missions.emergency_mission.front().get_duration());
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
            executing_missions.push(waiting_missions.mountainous_mission.front(), waiting_missions.mountainous_mission.front().get_duration());
            waiting_missions.mountainous_mission.pop();

        }else if(! available_rovers[0].empty())// check for available mountainous rover
        {
            // pop the rover from the available list
            Rover rover_2 = available_rovers[0].front();
            available_rovers[0].pop();

            // assign the mission to it
            rover_2.assign_mission(waiting_missions.mountainous_mission.front());
            executing_missions.push(waiting_missions.mountainous_mission.front(), waiting_missions.mountainous_mission.front().get_duration());
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
            executing_missions.push(waiting_missions.polar_mission.front(), waiting_missions.polar_mission.front().get_duration());
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


    void increment_waiting_days(){

        // polar mission
        queue<Mission> temp;
        Mission temp_mission;
        while (! waiting_missions.polar_missions.empty())
        {
            temp_mission = waiting_missions.polar_missions.front();
            temp_mission.increment_waiting_days();
            temp.push(temp_mission);
            waiting_missions.polar_missions.pop();
        }

        waiting_missions.polar_missions = temp;

        // mountainous missions
        queue<Mission> temp_2;
        while (! waiting_missions.mountainous_missions.empty())
        {
            temp_mission = waiting_missions.mountainous_missions.front();
            temp_mission.increment_waiting_days();
            temp_2.push(temp_mission);
            waiting_missions.mountainous_missions.pop();
        }

        waiting_missions.mountainous_missions = temp_2;
        // emergency missions
        PriorityQueue temp_3;
        while(! waiting_missions.emergency_missions.empty())
        {
            temp_mission = waiting_missions.emergency_missions.front();
            temp_mission.increment_waiting_days();
            temp_3.push(temp_mission);
            waiting_missions.emergency_missions.pop();
        }
        waiting_missions.emergency_missions = temp_3;
    }

    void increment_execution_days(){
        // emergency missions
        PriorityQueue temp;
        Mission temp_mission;
        while(! executing_missions.empty())
        {
            temp_mission = executing_missions.front();
            temp_mission.increment_waiting_days();
            temp.push(temp_mission);
            executing_missions.pop();
        }
        executing_missions = temp;
    }

    void check_finished_rovers(){
        queue<Rover>temp;
        Rover temp_rover;
        for (int i = 0; i < 3; ++i) {
            while(!executing_rovers[i].empty())
            {
                temp_rover = executing_rovers[i].front();
                executing_rovers[i].pop();
                if (temp_rover.get_mission().is_finished())
                {
                    temp_rover.increment_finished_missions();
                    completed_missions.push(temp_rover.get_mission());
                    if (temp_rover.need_checkup())
                    {
                        checkup_rovers[i].push(temp_rover);
                    }else{
                        available_rovers[i].push(temp_rover);
                    }
                }
                else{
                    temp.push(temp_rover);
                }
            }
            executing_rovers[i] = temp;

            // clear the queue
            while(! temp.empty())
                temp.pop();
        }
    }

    void check_rovers_in_checkup_station(){
        queue<Rover>temp;
        Rover temp_rover;
        for (int i = 0; i < 3; ++i) {
            while(!checkup_rovers[i].empty())
            {
                temp_rover = checkup_rovers[i].front();
                checkup_rovers[i].pop();
                temp_rover.increment_checkup_days();
                if (temp_rover.finished_checkup_duration())
                {
                    available_rovers[i].push(temp_rover);
                }
                else{
                    temp.push(temp_rover);
                }
            }
            checkup_rovers[i] = temp;

            // clear the queue
            while(! temp.empty())
                temp.pop();
        }
    }
    void check_for_auto_promotion(){
        // check for the waiting days of the only mountainous missions
        queue<Mission>temp;
        Mission temp_mission;
        while (! waiting_missions.mountainous_missions.empty())
        {
            temp_mission = waiting_missions.mountainous_missions.front();
            waiting_missions.mountainous_missions.pop()
            if (temp_mission.get_waiting_days() == user_interface.get_auto_promotion_limit())
            {
                num_of_auto_promoted++;
                // promote this mission to be an emergency one
                waiting_missions.emergency_missions.push(temp_mission, temp_mission.calc_prioriy());
            }else
                temp.push(temp_mission);
        }
        waiting_missions.mountainous_missions = temp;

    }
    bool is_everything_done(){
        bool condition = waiting_missions.polar_missions.empty() &&
                         waiting_missions.emergency_missions.empty() &&
                         waiting_missions.mountainous_missions.empty() &&
                         executing_missions.empty() &&
                         num_of_executed_events == user_interface.get_num_of_events();

        return condition;
    }

    bool next_day(){
        currentDay++;

        // increment the waiting days of the missions in waiting list
        increment_waiting_days();

        // increment the execution days of the missions in executing list
        increment_execution_days();

        // check if any rover finished its mission
        check_finished_rovers();

        // check the rovers which in the checkup station
        check_rovers_in_checkup_station();

        // check for the auto promotion events
        check_for_auto_promotion();

        // check if we finished all missions or not
        return is_everything_done();
    }

    void make_total_output(){
        /**
         * CD : Completion Day
         * ID : mission id
         * FD : Formulation Day
         * WD : Waiting Days
         * ED : Execution Days
         */
        cout << "CD\t" << "ID\t" << "FD\t" << "WD\t" << "ED\n";
        Mission temp;
        int count = completed_missions.size();
        double sum_waiting = 0,
            sum_executing = 0;
        while (! completed_missions.empty())
        {
            temp = completed_missions.front();
            sum_waiting += temp.get_waiting_days();
            sum_executing += temp.get_execution_days();

            cout << temp.get_completion_day() << '\t' << temp.get_id() << '\t';
            cout << temp.get_formulated_day() << '\t' << temp.get_waiting_days() << '\t';
            cout << temp.get_execution_days() << '\n';

            completed_missions.pop();
        }
        cout << "=========================================================================================\n";
        cout << "Missions : " << count << endl;
        cout << "Rovers : " << user_interface.get_total_num_of_rovers() << endl;
        cout << "Avg waiting : " << sum_waiting / count << endl;
        cout << "Avg executing : " << sum_executing / count << endl;
        cout << "Auto Promoted : " << ( num_of_auto_promoted / count ) * 100 << "%\n";
    }

    void daily_output(){

        cout << "Current Day : " << current_day << endl;
        cout << "Waiting Missions : " << waiting_missions.polar_missions.size() + waiting_missions.mountainous_missions.size() + waiting_missions.emergency_missions.size() << "\n\n";
        cout << "In-Execution Missions / Rovers : " << executing_missions->size() << " / " <<
        executing_rovers[0].size() + executing_rovers[1].size() + executing_rovers[2].size() << "\n\n";
        cout << "Available rovers : " << available_rovers[0].size()+available_rovers[1].size()+available_rovers[2].size() << "\n\n";
        cout << "In-Checkup Rovers : " << checkup_rovers[0].size()+checkup_rovers[1].size()+checkup_rovers[2].size() << "\n\n";
        cout << "Completed Missions : " << completed_missions.size() << "\n\n";
        cout << "======================================================================================================================";
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

            // 3- print the daily info
            daily_output();

            // 4- collect statistics that needed to create the output file
            finished = next_day();
        }


        // call the output function
        make_total_output();
    }

};


#endif //FILE_MARSSTATION_H
