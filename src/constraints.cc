#include "constraints.hh"

#include <string>
#include <iostream>
#include "course_data.hh"

using namespace std;


/** 
 * Function to add a time constraint into the timetable 
 * similar to adding a class
 * just add a block of time where a class would be
 * 
 * 
*/
void ConstraintGeneral::add_time_constraint(std::unordered_map<Date, SelectedCourseSection, Date_Hash>& timetable, int day_of_week_, int time_, int duration_, char semester_, int constraint_type_) {
  // we have the timetable (empty) and now we fill it with the time block
  
  // since data is coming from our front-end, it shouldn't need to be parsed for correctness 
  // (click on schedule to place block off time)

  // now we make up a SelectedCourseSection object for our blocked off time
  // each blocked off section should have some extra info
  // because the user won't be adding the reason for blocking off time
  // we don't need extra info here since these are just for our terminal output
  SelectedCourseSection class_chosen{
  .course_code = "Blocked Off Time",
  .type = CONSTRAINT, // Blocked Off Section
  .section = 887,
  .semester = semester_ 
  };

  for (int i = 0; i < duration_; i++) {

  
    // each Date pair is: (day of week, time of day)
    // then we insert pair: (Date, class)
    Date period = make_pair(day_of_week_, time_ + i);

    auto it = timetable.insert(std::make_pair(period, class_chosen));
    bool successfully_inserted = it.second;

    // Check if the class was sucessfully inserted 
    if (!successfully_inserted) {
      // something went wrong - timetable should be empty
      cout << "Error in adding constraint." << endl;
    }
  }
}

void ConstraintGeneral::remove_conflicts(std::unordered_map<Date, SelectedCourseSection, Date_Hash> timetable, unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash>& courses) {
    // in this function we want to delete the courses from course offerings that overlap with the constraint
    // no point in trying to schedule something at the same time

    


}


ConstraintGeneral::ConstraintGeneral() {

}