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

using namespace std;

struct SelectedCourseSection{
  string course_code; 
  int type; // 1 = lec, 2 = tut, 3 = pra 
  int section;
  char semester;
};

enum class_type {
  LEC = 1,
  TUT = 2,
  PRA = 3,
  CONSTRAINT = 4
};

class Scheduler {

    private:

        std::vector<std::unordered_map<Date, SelectedCourseSection, Date_Hash>> timetables_;
        std::vector<std::vector<std::string>> timetables_str;
        int max_sections_scheduled();
        int number_of_timetables = 5;
        int max_number_of_timetables = 400;
       
    public:
        Scheduler();
        void add_time_constraint(std::unordered_map<Date, SelectedCourseSection, Date_Hash>& timetable, int day_of_week_, int time_, int duration_, char semester_);
        void schedule_classes(unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash>& courses);
        void schedule_classes_helper(unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash>& courses, std::unordered_map<Date, SelectedCourseSection, Date_Hash>& timetable, bool first_itartion = false);
        void print_timetable(std::unordered_map<Date, SelectedCourseSection, Date_Hash>& timetable);
        void attempt_to_add_section(std::unordered_map<Date, SelectedCourseSection, Date_Hash>& timetable, int class_type, CourseOfferings course, unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash>& courses);
        bool unique_check(std::unordered_map<Date, SelectedCourseSection, Date_Hash>& timetable);
        std::vector<std::string> make_timetable_str(std::unordered_map<Date, SelectedCourseSection, Date_Hash>& timetable);
        void print_timetables();
};

#endif