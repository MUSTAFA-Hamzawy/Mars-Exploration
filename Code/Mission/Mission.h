//
// Created by Mustafa Hamzawy on 8/2/2022.
//

#ifndef FILE_MISSION_H
#define FILE_MISSION_H


class Mission {
private:
    int waiting_days;
    int execution_days;
    int completion_day;
    int formulation_day;
    int target_location;
    int mission_duration;
    int significance;
    int id;
public:

    Mission(int id)
    {
        this->id = id;
    }

    int get_id()
    {
        return id;
    }

    int calc_prioriy(){
        return (mission_duration + target_location) / formulation_day + significance;
    }

    int get_duration(){
        return mission_duration;
    }

    int get_target_location(){
        return target_location;
    }
    int get_signficance(){
        return significance;
    }

    void set_info(int mission_id, int target_loc, int num_of_days_to_finish, int significance, int formulation_day)
    {
        this->id = mission_id;
        this->target_location = target_loc;
        this->mission_duration = num_of_days_to_finish;
        this->significance = significance;
        this->formulation_day = formulation_day;
    }

};


#endif //FILE_MISSION_H
