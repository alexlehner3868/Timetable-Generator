#ifndef STATS_H
#define STATS_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <fstream> 
#include <chrono>
#include <ctime>

#include "constraints.hh"


using namespace std;

class StatCollector {
private:
    int partial_timetables_pruned = 0;
    int full_timetables_pruned = 0;
    int timetables_explored = 0; 
    int total_timetables = 0;
    int number_of_top_tracked = 0;
    int scheduler_runtime = 0;; 
    ConstraintHandler constraint_handler;
public:
    StatCollector(){};

    void set_scheduler_counts(int partial_prune, int full_prune, int num_explored, int total, int top_tracked, int dur){
        partial_timetables_pruned = partial_prune;
        full_timetables_pruned  = full_prune;
        timetables_explored = num_explored;
        total_timetables = total;
        number_of_top_tracked = top_tracked;
        scheduler_runtime = dur;
    };

    void track_constraints(ConstraintHandler& c){
        constraint_handler = c;
    }

    void print_stats(){
        std::ofstream logfile ("stats.txt");
        logfile << "--- Stats Collected --- " << endl;
        logfile<<"Algorithm  Runtime: " << scheduler_runtime<<" sec"<<endl;
        logfile<<"__________________________"<<endl;
        
        logfile.close();
    }
   
};

#endif
