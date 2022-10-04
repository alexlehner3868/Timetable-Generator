#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <string>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <random>
#include "course_offering.hh"
#include "constraints.hh"
#include "date.hh"
#include "period.hh"
#include "timetable.hh"

using namespace std;



class Scheduler {

    private:

        std::vector<TimeTable> timetables_;
        std::vector<std::vector<std::string>> timetables_str;
        int max_sections_scheduled();
        int number_of_timetables = 5;
        int max_number_of_timetables = 400;
       
    public:
        Scheduler();
        void schedule_classes(unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash>& courses);
        void schedule_classes_helper(unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash>& courses, TimeTable& timetable);
        void print_timetable(TimeTable& timetable);
        void attempt_to_add_section(TimeTable& timetable, int class_type, CourseOfferings course, unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash>& courses);
        bool unique_check(TimeTable& timetable);
        std::vector<std::string> make_timetable_str(TimeTable& timetable);
        void print_timetables();
};

#endif