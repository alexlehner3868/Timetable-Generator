#include "constraints.hh"

#include <string>
#include <iostream>
#include "course_data.hh"

using namespace std;


void ConstraintHandler::add_time_constraint(int start_time, int duration, int day, char semester,  int priority){
  for(int i = 0; i < duration; i++){
    if(semester == 'W'){
      day +=5;
    }
    time_constraints_.insert({make_pair(day, start_time + i), priority});
  }
}

void ConstraintHandler::set_back_to_back_constraint(int max_back_to_back, int priority){
  back_to_back_constraint_ = make_pair(max_back_to_back, priority);
}

void ConstraintHandler::set_no_classes_after_X_constraint(int X, int priority){
  no_classes_after_X_ = make_pair(X, priority);
}

void ConstraintHandler::set_no_classes_before_X_constraint(int X, int priority){
  no_classes_before_X_ = make_pair(X, priority);
}


void ConstraintHandler::set_minimize_days_at_school_constraint(bool ans){
  minimize_days_at_school_ = ans; 
}

void ConstraintHandler::set_prefer_morning_classes_constraint(bool ans){
  prefer_morning_classes_ = ans;
}

void ConstraintHandler::set_prefer_evening_classes_constraint(bool ans){
  prefer_evening_classes_ = ans;
}


bool ConstraintHandler::preprocess_high_priority_classes_out(unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash>& original_offerings){
  // Maybe? Add before_X and after_X times if it is a high priority (ie add all times above X for all days )
  // TimeConstraint(int start, int day, int priority, char semester)

  for(CourseOfferings offering: original_offerings){
    for(Section lect_section : offering.lecture_sections_){
      bool remove_section = false;
      for(int i = 0; i < lect_section.num_classes_in_section(); i++){
        for(int j = 0; j < lect_section.duration_[i]; j++){
          auto it = time_constraints_.find({lect_section.day_[i], lect_section.start_time_[i]+j});
          if(it != time_constraints_.end() && it->second == MUST_HAVE){
            //NEED TO EITHER WORK OUT HERE HOW TO REMOVE THE SECTION WE ARE LOOKING AT OR INSTEAD ONLY INSERT GOOD SECTIONS INTO NEW VECTOR (i like this better)
          }
        }
      }

    }
    for(auto tut_section : offering.tutorial_sections_){
      // add loops like above here 
    }
    for(auto pra_section : offering.practical_sections_){
      // same 
    }

    //CHCEK IF ANY OF THE LEC, PRA or TUT vectors in offering are of size 0, return false 
  }
  return true;
}

ConstraintHandler::ConstraintHandler() {
  time_constraints_.clear();
  back_to_back_constraint_ = make_pair(24, NO_PRIORITY); 
  no_classes_after_X_ = make_pair(24, NO_PRIORITY);
  no_classes_before_X_ = make_pair(0, NO_PRIORITY);
}