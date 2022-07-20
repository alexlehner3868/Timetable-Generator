#include <string>
#include <iostream>
#include <unordered_set>

#include "course_offering.hh";
#include "constraints.hh";

using namespace std;

class Scheduler {
  private:
    unordered_set<CourseOfferings> course_offerings_;
    std::vector<std::unique_ptr<Constraint>> constraints_;
  public:
   Scheduler();

   void add_course(CourseOfferings course);
   void remove_course(CourseOfferings course);
   void add_constraint(Constraint* constraint);
   void remove_constraint(Constraint* constriant);

};

