#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <string>
#include <iostream>
#include <unordered_set>
#include <unordered_map>

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
  PRA = 3
};

struct TimetablesHash{
    size_t operator()(const std::unordered_map<Date, SelectedCourseSection, Date_Hash>& mp) const
    {
      return hash<string>()();
    }
};

class Scheduler {

    private:

    std::unordered_set<std::unordered_map<Date, SelectedCourseSection, Date_Hash>> timetables_;
    
    public:
        Scheduler();
        void schedule_classes(unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash>& courses);
        void schedule_classes_helper(unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash>& courses, std::unordered_map<Date, SelectedCourseSection, Date_Hash>& timetable);
        void print_timetable(std::unordered_map<Date, SelectedCourseSection, Date_Hash>& timetable);
        void attempt_to_add_section(std::unordered_map<Date, SelectedCourseSection, Date_Hash>& timetable, int class_type, CourseOfferings course, unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash>& courses);


};

#endif