//
// Created by Mustafa Hamzawy on 8/2/2022.
//

#ifndef FILE_MIXED_MISSIONS_STRUCT_H
#define FILE_MIXED_MISSIONS_STRUCT_H
#include "Mission.h"
#include "../PriorityQueue.h"
#include <queue>
struct mixed_missions_struct{
    std::queue<Mission> polar_missions;
    std::queue<Mission> mountainous_missions;
    PriorityQueue emergency_mission;
};
#endif //FILE_MIXED_MISSIONS_STRUCT_H
