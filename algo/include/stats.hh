#ifndef STATS_H
#define STATS_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "course_data.hh"
#include "course_offering.hh"
#include "date.hh"


using namespace std;

class StatCollectors {
private:
    int partial_timetables_pruned = 0;
    int full_timetables_pruned = 0;
    int timetables_explored = 0; 
public:
    StatCollectors();

};

#endif
