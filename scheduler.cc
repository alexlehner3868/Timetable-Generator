#include <string>
#include <iostream>
#include <stdlib.h>

#include "scheduler.hh"

using namespace std; 

void Scheduler::Scheduler(){

}

void Scheduler::schedule_classes(unordered_set<CourseOfferings>& course_offerings){
  std::unordered_map<int, int> timetable; // 5 days by 12 hours 


  for(auto offering : course_offerings){
    if(offering.lecture_sections_.size() > 1 ){
      for(auto sec : offering.lecture_sections_){
        for(int i = 0; i < sec.duration_; i++){
          timetable[sec.day_][]
        }
        unordered_set<CourseOfferings> remaining_classes = course_offerings;
        remaining_classes.remove(offering);
        schedule_classes(remaining_classes);
      }
    }
  }
  
}