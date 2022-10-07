#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <string>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <random>
#include <queue>


#include "course_offering.hh"
#include "constraints.hh"
#include "date.hh"
#include "period.hh"
#include "timetable.hh"

using namespace std;



class Scheduler {
    private:
        priority_queue<TimeTable, vector<TimeTable>, CompareTimeTable> timetables_;
        std::vector<std::vector<std::string>> timetables_str;
        int max_sections_scheduled();
        int max_num_of_timetables_to_show = 5;
        int number_of_explored_timetables = 0;
        int max_number_of_timetables_to_explore = 400;
       ConstraintHandler constraint_handler_;
    public:
        Scheduler();
        vector<TimeTable> schedule_classes(unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash>& courses, ConstraintHandler& constraint_handler);
        void schedule_classes_helper(unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash>& courses, TimeTable& timetable);
        void print_timetable(TimeTable& timetable);
        void attempt_to_add_section(TimeTable& timetable, int class_type, CourseOfferings course, unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash>& courses);
        bool unique_check(TimeTable& timetable);
        std::vector<std::string> make_timetable_str(TimeTable& timetable);
        void print_timetables(vector<TimeTable> timetables);
};

#endif