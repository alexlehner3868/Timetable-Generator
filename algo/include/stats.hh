#ifndef STATS_H
#define STATS_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "constraints.hh"


using namespace std;

class StatCollector {
private:
    int partial_timetables_pruned = 0;
    int full_timetables_pruned = 0;
    int timetables_explored = 0; 
    int total_timetables = 0;
    int number_of_top_tracked = 0;

    ConstraintHandler constraint_handler;
public:
    StatCollector(){};

    void set_scheduler_counts(int partial_prune, int full_prune, int num_explored, int total, int top_tracked){
        partial_timetables_pruned = partial_prune;
        full_timetables_pruned  = full_prune;
        timetables_explored = num_explored;
        total_timetables = total;
        number_of_top_tracked = top_tracked;
    };

    void track_constraints(ConstraintHandler& c){
        constraint_handler = c;
    }

    void print_stats(){
        
    }
};

#endif
