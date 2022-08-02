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
    Event** events;
    int output_mode;
public:
    /**
     * The constructor
     * @param out_mode : to select the output mode because the program supports 3 modes of output.
     */
    UI(int out_mode){
        this->output_mode = out_mode;
    }
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

        this->events = new Event*[input_info.num_of_event];

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
                events[i] = ev;
                ev = nullptr;
            }else if (charIn == 'X'){
                CancellationEvent *ev = new CancellationEvent();
                input >> event_day >> id;
                ev->set_data(event_day, id);
                events[i] = ev;
                ev = nullptr;
            }else if (charIn == 'P'){
                PromotionEvent *ev = new PromotionEvent();
                input >> event_day >> id;
                ev->set_data(event_day, id);
                events[i] = ev;
                ev = nullptr;
            }
        }
        cout << "OK, I got the input.";
    }
};

#endif //MARS_EXPLORATION_USERINTERFACE_H
