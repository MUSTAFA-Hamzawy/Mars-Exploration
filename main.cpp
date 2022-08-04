#include <iostream>
#include "Code/UserInterface/UI.h"
#include <typeinfo>
#include "Code/Events/Event.h"
#include "Code/Events/FormulationEvent.h"
#include "Code/PriorityQueue.h"
#include "Code/MarsStation/MarsStation.h"
using namespace std;

int main() {

    // Reading the input file
    UI user_interface;
    string path = "D:\\second_term_project\\Mars-Exploration\\input.txt";
    user_interface.set_src_file(path);
    user_interface.readInputFile();

    // Simulate the mars station
    MarsStation station;
    station.simulate();

    return 0;
}
