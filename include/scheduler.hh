#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <string>
#include <iostream>
#include <unordered_set>
#include <unordered_map>

#include "course_offering.hh"
#include "constraints.hh"
#include "period.hh"

using namespace std;

struct ClassChosen{
  string course_code; 
  int type; // 1 = lec, 2 = tut, 3 = pra 
  int section;
  char semester;
};

typedef std::pair<int, int> day_time;

struct day_time_hash
{
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2> &pair) const {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};

class Scheduler {

    private:

    vector<std::unordered_map<day_time, ClassChosen, day_time_hash>> timetables_;
    
    public:
        Scheduler();
        void schedule_classes(unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash>& courses);
        void schedule_classes_helper(unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash>& courses, std::unordered_map<day_time, ClassChosen, day_time_hash>& timetable);
        void print_timetable(std::unordered_map<day_time, ClassChosen, day_time_hash>& timetable);

};

#endif