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





class ConstraintGeneral {
  private:
    std::vector<int> day_of_week_;
    std::vector<int> time_;
    std::vector<int> duration_;
    std::vector<char> semester_;
    std::vector<int> constraint_type_;
  public:
    ConstraintGeneral();
    /*ConstraintGeneral(int day_of_week, int time, int duration, char semester, int constraint_type) {
      day_of_week_ = day_of_week;
      time_ = time;
      duration_ = duration;
      semester_ = semester;
      constraint_type_ = constraint_type;
    }*/
    void add_time_constraint(std::unordered_map<Date, SelectedCourseSection, Date_Hash>& timetable, int day_of_week, int time, int duration, char semester, int constraint_type);
    void remove_conflicts(std::unordered_map<Date, SelectedCourseSection, Date_Hash> timetable, unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash>& courses);
    
};



/**
 * A time where courses cannot be with varying priorities
*/
class TimeConstraint {
  private:
    int start_time_;
    int duration_;
    int priority_;
  public:
  TimeConstraint();
    TimeConstraint(int start, int dur, int priority){
      start_time_ = start;
      duration_ = dur;
      priority_ = priority;
    };
};

/**
 * A preference to not have chunks of X (in minutes back to back)
 * no more than 5 hours back to back -> no more than 300 min back to back
*/
class ChunkConstraint {
  private:
    int minutes_back_to_back_;
    int priority_;
  public:
    ChunkConstraint(int chunk_size, int priority){
      minutes_back_to_back_ = chunk_size;
      priority_ = priority;
    };
};


/**
 * A preference to not have classes before/after X o'clock 
*/
class CutOffTimeConstraint {
  private:
    int cut_off_time_;
    bool before_; // 1: not before, 0: not after 
    int priority_;
  public:
    CutOffTimeConstraint(int cut_off_time, bool before, int priority){
      cut_off_time_ = cut_off_time;
      before_ = before;
      priority_ = priority;
    };
};

/**
 * A preference to condense your classes to minimize days at school 
*/
class MinimizeDaysSchoolConstraint {
  private:
    int priority_level_;
  public:
    MinimizeDaysSchoolConstraint(int priority){
      priority_level_ = priority;
    };
};

#endif