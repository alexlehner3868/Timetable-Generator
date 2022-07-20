#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Constraint {
  int priority_level_; // 10 = hightest, 1 = lowest, 0 = off
  
  Constraint(int priority_level){
    int priority_level_ =  priority_level;
  }
};

/**
 * A time where courses cannot be with varying priorities
*/
class TimeConstraint : private Constraint {
  private:
    int start_time_;
    int duration_;
  public:

    TimeConstraint(int start, int dur, int priority){
      start_time_ = start;
      duration_ = dur;
    };
};

/**
 * A preference to not have chunks of X (in minutes back to back)
 * no more than 5 hours back to back -> no more than 300 min back to back
*/
class ChunkConstraint : private Constraint{
  private:
    int minutes_back_to_back_;
  public:
    ChunkConstraint(int chunk_size, int priority){
      minutes_back_to_back_ = chunk_size;
    };
};


/**
 * A preference to not have classes before/after X o'clock 
*/
class CutOffTimeConstraint : private Constraint{
  private:
    int cut_off_time_;
    bool before_; // 1: not before, 0: not after 
  public:
    CutOffTimeConstraint(int cut_off_time, bool before, int priority){
      cut_off_time_ = cut_off_time;
      before_ = before;
    
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


