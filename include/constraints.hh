#ifndef CONSTRAINTS_H
#define CONSTRAINTS_H

#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include "course_offering.hh"
#include "course_data.hh"
#include "date.hh"

using namespace std;

/**
 * @brief 
 * Constraints List:
 * ☑ Block off Time
 * ☐ No large chunks of class w/ no break
 * ☐ early constraint
 * ☐ late constraint (same as above)
 * ☐ condense schedule
 * ☐ 
 * 
 */

  enum constraint_priority {
    NO_PRIORITY = 0,
    NICE_TO_HAVE = 1,
    GOOD_TO_HAVE = 2,
    MUST_HAVE = 3,
  };

/**
 * A time where courses cannot be with varying priorities
*/
class TimeConstraint {
  private:
    int start_time_;
    int day_;
    int priority_;
    char semester_;
  public:
  TimeConstraint();
    TimeConstraint(int start, int day, int priority, char semester){
      start_time_ = start;
      priority_ = priority;
      day_ = day;
      semester_ = semester;
    };
    int priority(){
      return priority_;
    }
    int start(){
      return start_time_;
    }
    int day(){
      return day_;
    }
    char semester(){
      return semester_;
    }
};

class ConstraintHandler {
  private:
  /*
    std::vector<int> day_of_week_;
    std::vector<int> time_;
    std::vector<int> duration_;
    std::vector<char> semester_;
    std::vector<int> constraint_type_;
    */

  vector<TimeConstraint> time_constraints_;
  int minimize_days_at_school_ = NO_PRIORITY;
  int breaks_between_classes_ = NO_PRIORITY;
  int free_days_ = NO_PRIORITY;
  int prefer_morning_classes_ = NO_PRIORITY;
  int prefer_evening_classes_ = NO_PRIORITY;
  pair<int, int> back_to_back_constraint_; // <max hours back to back, priority>
  pair<int, int> no_classes_after_X_; // <X, priority> 
  pair<int, int> no_classes_before_X_; // <X, prioity>

  public:
    ConstraintHandler();
    void add_time_constraint(int start_time, int duration, int day, char semester, int priority);
    void set_back_to_back_constraint(int max_back_to_back, int priority);
    void set_no_classes_after_X_constraint(int X, int prioirty);
    void set_no_classes_before_X_constraint(int X, int prioirty);
    void set_free_days_constraint(int priority);
    void set_minimize_days_at_school_constraint(int priority);
    void set_prefer_morning_classes_constraint(int priority);
    void set_prefer_evening_classes_constraint(int priority);
    void reorder_time_constraints_based_on_priority();

    bool remove_classes_conflicting_with_high_priority_time_constraints(unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash>& original_offerings);
};

#endif