#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <string>
#include <iostream>
#include <unordered_set>
#include <unordered_map>

#include "course_offering.hh"
#include "constraints.hh"

using namespace std;

struct ClassChosen{
  string course_code; 
  int type; // 1 = lec, 2 = tut, 3 = pra 
  int section;
};


class Scheduler {

    private:

    public:
        Scheduler();
        void schedule_classes(unordered_set<CourseOfferings>& course_offerings);
        void schedule_classes_helper(unordered_set<CourseOfferings>& course_offerings,std::unordered_map<std::pair<int, int>, struct ClassChosen>& timetable);
        void print_timetable(std::unordered_map<std::pair<int, int>, struct ClassChosen>& timetable);

};

#endif