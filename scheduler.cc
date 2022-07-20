#include "scheduler.hh";

void Scheduler::add_course(CourseOfferings course){
    course_offerings.insert(course);
}

void Scheduler::remove_course(CourseOfferings course){
    course_offerings.erase(course);
}








/*

set up each course as one part of Boolean equation
 (x1 | -x5 | x4) & #all lecture sections
  (-x1 | x5 | x3 | x4) & # all practical sections
  (-x3 | x4). #all tutorial sections
       #pick one lecture section     #one pra section   # one tut section
 (   (lec101 | lec102 | lec103) & (pra101 | pra102) & (tut101 | tut102 | tut103)  )
*/