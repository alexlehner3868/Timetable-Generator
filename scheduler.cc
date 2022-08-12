#include <string>
#include <iostream>
#include <stdlib.h>

#include "scheduler.hh"

using namespace std; 

struct {
    int lec;
    int pra;
    int tut;
} sections_chosen;

void Scheduler::Scheduler(){

}
void Scheduler::schedule_classes(unordered_set<CourseOfferings>& course_offerings ){
  std::unordered_set<std::pair<int, int>> timetable;
  schedule_classes_helper(course_offerings, timetable);
}


void Scheduler::schedule_classes_helper(unordered_set<CourseOfferings>& course_offerings, std::unordered_set<std::pair<int, int>>& timetable){

  //std::unordered_set<std::pair<int,int>> timetable; // 5 days by 12 hours 


  for(auto offering : course_offerings){
    for(auto sec : offering.lecture_sections_){
    //add to timetable for each section
        bool successfully_inserted;
        for (int lecture_in_section = 0; lecture_in_section < sec.duration_.size(); lecture_in_section++) {
            for (int i = 0; i < sec.duration_.at(lecture_in_section); i++) {
                successfully_inserted = timetable.insert(std::make_pair<int, int>(sec.day_, sec.start_time_ + i)).second();
                //try to add to sections_chosen
                if (!succesfully_inserted) {
                    break;
                    //combination is invalid
                    //time occupied by another course offering
                }
                
            }
            //remove all occurences of lecture section if conflict
            //also remove from sections_chosen
            if (!successfully_inserted) {
                for (int remove_class = 0; remove_class <= lecture_in_section; remove_class++) {
                    for (int i = 0; i < sec.duration_.at(lecture_in_section); i++) {
                        timetable.erase(std::make_pair<int, int>(sec.day_, sec.start_time_ + i));

                    }
                }
                break;
            }
        }
        unordered_set<CourseOfferings> remaining_classes = course_offerings;
        remaining_classes.remove(offering);
        schedule_classes(remaining_classes, timetable);
        for (int remove_class = 0; remove_class <= lecture_in_section; remove_class++) {
            for (int i = 0; i < sec.duration_.at(lecture_in_section); i++) {
                timetable.erase(std::make_pair<int, int>(sec.day_, sec.start_time_ + i));

            }
        }
    }
    
  }
  
}