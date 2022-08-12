#include <iostream>

#include "constraints.hh";
using namespace std;
 
int main(int argc, char *argv[])
{
    // TODO 


    //--- Data Procesing ---- 
    // 1. Parses csv to get classes 
    // 2. Store csv in SQL database or something and related sql funcitons 

    // -- User input (later) 
    // 1. Search and add classes to timetable 
    // 2. Remove classes 
    // 3. Add constraints 

        unordered_set<CourseOfferings> course_offerings_;
        unordered_set<TimeConstraint> time_constraints_;
        unordered_set<ChunkConstraint> chunk_constraints_;
        unordered_set<CutOffTimeConstraint> cut_off_time_constraints_;


    // -- Scheduling Algo 
    // 1. Loop through all options and see what works 
    // 2. Evaluate all possible options based on constraints 
    // 3. What happens if no solution 


    // GUI  
    // Web stuff 
}