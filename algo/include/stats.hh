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
    int max_timetables = 0;
    int max_number_of_top_tracked = 0;
    int actual_number_of_top_tracked = 0;
    int unqiue_timetables_found = 0;
    int scheduler_runtime = 0;

    ConstraintHandler* constraint_handler;
    vector<int> best_timetable_costs;
public:
    StatCollector(){};

    void set_scheduler_counts(int partial_prune, int full_prune, int num_explored, int max, int top_tracked, int actual_tracked, int unique_count, int dur){
        partial_timetables_pruned = partial_prune;
        full_timetables_pruned  = full_prune;
        timetables_explored = num_explored;
        max_timetables = max;
        max_number_of_top_tracked = top_tracked;
        unqiue_timetables_found = unique_count;
        actual_number_of_top_tracked = actual_tracked;
        scheduler_runtime = dur;
    };

    void track_constraints(ConstraintHandler* c, vector<int> timetable_costs){
        constraint_handler = c;
        best_timetable_costs = timetable_costs;
    }

    void print_stats(){
        std::ofstream logfile ("stats.txt");
        logfile << "--- Stats Collected --- " << endl;
        logfile<<"__________________________"<<endl;
        logfile<<"Algorithm  Runtime: " << scheduler_runtime<<" [µs]"<<endl;
        // list of courses being placed
        logfile<<"__________________________"<<endl;
        logfile<<"--- Scheduler Stats ---"<<endl;
        logfile<<"Number of best timetables tracked: " <<actual_number_of_top_tracked<< "[out of a max of "<<max_number_of_top_tracked<<"]" <<endl;
        logfile<<"Number of timetables explored: "<<timetables_explored<<endl;
        logfile<<"Number of unique timetables found: "<<unqiue_timetables_found<<endl;
        logfile<<endl;
        logfile<<"Number of partial timetables pruned: "<<partial_timetables_pruned<<endl;
        logfile<<"Number of complete timetables pruned: "<<full_timetables_pruned<<endl;
        logfile<<"__________________________"<<endl;
        logfile<<"--- Constraint Stats ---"<<endl;
        logfile<<constraint_handler->output_constraints_stats().str();
        // Number of sections preprocessed out 
        // List of active constraints and priorities 
        logfile<<"__________________________"<<endl;
        logfile<<"--- Best Timetables ---"<<endl;
        for(int i = 0; i < best_timetable_costs.size(); i++){
            logfile<<"Timeable "<<i+1<<" with cost "<< best_timetable_costs[i]<<endl;
        }
        logfile.close();
    }
   
};

#endif
