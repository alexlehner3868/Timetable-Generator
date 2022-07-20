#include <string>
#include <iostream>
#include <unordered_set>

#include "course_offering.hh";

using namespace std;

class Scheduler {
  private:
    unordered_set<CourseOfferings> course_offerings;
  public:
   Scheduler();

   void add_course(CourseOfferings course);
   void remove_course(CourseOfferings course);
};

