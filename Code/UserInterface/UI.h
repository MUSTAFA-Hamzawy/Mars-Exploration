//
// Created by Mustafa Hamzawy on 8/1/2022.
//
#include <fstream>
#include <string>
#include "InputInfo.h"
#include "../Events/Event.h"
#include "../Events/FormulationEvent.h"
#include "../Events/CancellationEvent.h"
#include "../Events/PromotionEvent.h"
#include <queue>
using namespace std;
#ifndef MARS_EXPLORATION_USERINTERFACE_H
#define MARS_EXPLORATION_USERINTERFACE_H


class UI{
    string fileSource;
    InputInfo input_info;
    queue<Event*> events;
public:

    /**
     * To set the source of the input file
     * @param src
     */
    void set_src_file(string src){
        fileSource = src;
    }

    /**
     * To read the input file
     */
    void readInputFile(){
        // open the file
        std::ifstream input;
        input.open(fileSource);
        if ( ! input)
        {
            cerr << "Error : Can't open the file";
            exit(1);
        }

        // get the input
        input >> input_info.num_of_emergency_rovers;
        input >> input_info.num_of_polar_rovers;
        input >> input_info.num_of_mountainous_rovers;

        input >> input_info.speed_of_emergency_rovers;
        input >> input_info.speed_of_polar_rovers;
        input >> input_info.speed_of_mountainous_rovers;

        input >> input_info.num_of_emergency_missions_before_checkup;
        input >> input_info.num_of_polar_missions_before_checkup;
        input >> input_info.num_of_mountainous_missions_before_checkup;

        input >> input_info.checkup_duration;

        input >> input_info.auto_promotion_limit;

        input >> input_info.num_of_event;

        char charIn;
        int event_day, id, target_location, num_days_to_finish, significance;
        for (int i = 0; i < input_info.num_of_event; ++i) {
            input >> charIn;
            if (charIn == 'F')
            {
                FormulationEvent *ev = new FormulationEvent();
                input >> charIn;        //  mission type
                input >> event_day >> id >> target_location >> num_days_to_finish >> significance;
                ev->set_data(event_day, id, charIn, target_location, num_days_to_finish, significance);
                events.push(ev);
                ev = nullptr;
            }else if (charIn == 'X'){
                CancellationEvent *ev = new CancellationEvent();
                input >> event_day >> id;
                ev->set_data(event_day, id);
                events.push(ev);
                ev = nullptr;
            }else if (charIn == 'P'){
                PromotionEvent *ev = new PromotionEvent();
                input >> event_day >> id;
                ev->set_data(event_day, id);
                events.push(ev);
                ev = nullptr;
            }
        }
        cout << "OK, I got the input.";
    }

    queue<Event*> fetch_events(){
        return events;
    }

    int get_auto_promotion_limit(){
        return input_info.auto_promotion_limit;
    }

    int get_num_of_events(){
        return input_info.num_of_event;
    }

    int get_total_num_of_rovers(){
        return input_info.num_of_mountainous_rovers + input_info.num_of_emergency_rovers + input_info.num_of_polar_rovers;
    }

    int get_num_emergency_rovers(){
        return input_info.num_of_emergency_rovers;
    }
    int get_num_polar_rovers(){
        return input_info.num_of_polar_rovers;
    }
    int get_num_mountainous_rovers(){
        return input_info.num_of_mountainous_rovers;
    }
    int get_speed_of_emergency_rover(){
        return input_info.speed_of_emergency_rovers;
    }
    int get_speed_of_polar_rover(){
        return input_info.speed_of_polar_rovers;
    }
    int get_speed_of_mountainous_rover(){
        return input_info.speed_of_mountainous_rovers;
    }

    int get_num_of_missions_before_mountainous_checkup(){
        return input_info.num_of_mountainous_missions_before_checkup;
    }
    int get_num_of_missions_before_polar_checkup(){
        return input_info.num_of_polar_missions_before_checkup;
    }
    int get_num_of_missions_before_emergency_checkup(){
        return input_info.num_of_emergency_missions_before_checkup;
    }
    int get_checkup_duration()
    {
        return input_info.checkup_duration;
    }
};

#endif //MARS_EXPLORATION_USERINTERFACE_H
