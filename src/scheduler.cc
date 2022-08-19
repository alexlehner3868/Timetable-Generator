#include <string>
#include <iostream>
#include <stdlib.h>
#include <unordered_set>
#include <unordered_map> 

#include "period.hh"

#include "scheduler.hh"

using namespace std; 


void Scheduler::schedule_classes(unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash>& course_offerings ){
  std::unordered_map<day_time, ClassChosen, day_time_hash> timetable;
  schedule_classes_helper(course_offerings, timetable);
}


void Scheduler::schedule_classes_helper(unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash>& course_offerings, std::unordered_map<day_time, ClassChosen, day_time_hash>& timetable){
  //timetable is 5 days by 12 hours
  // TODO, add in only add if semester is the same 
  if(course_offerings.size() == 0){
    // TODO -> save this for later as a potential option 
    print_timetable(timetable);
  }

  for(auto offering : course_offerings){
    for(int sec_id = 0; sec_id < offering.lecture_sections_.size(); sec_id++){
      auto sec = offering.lecture_sections_.at(sec_id);
    //add to timetable for each section
        bool successfully_inserted;
        ClassChosen class_chosen;
        class_chosen.course_code = offering.course_id_;
        class_chosen.type = 1; // Lecture 
        class_chosen.section = sec_id;
        int lecture_in_section;
        for (lecture_in_section = 0; lecture_in_section < sec.duration_.size(); lecture_in_section++) {
            for (int i = 0; i < sec.duration_.at(lecture_in_section); i++) {
                day_time period = make_pair(sec.day_.at(lecture_in_section), sec.start_time_.at(lecture_in_section) + i);
                auto it = timetable.insert(std::make_pair(period, class_chosen));
                successfully_inserted = it.second;
                if (!successfully_inserted) {
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
                        day_time period = make_pair(sec.day_.at(lecture_in_section), sec.start_time_.at(lecture_in_section) + i);
                        timetable.erase(period);

                    }
                }
                break;
            }
        }
        unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash> remaining_classes = course_offerings;
        remaining_classes.erase(offering);
        schedule_classes_helper(remaining_classes, timetable);
        for (int remove_class = 0; remove_class <= lecture_in_section; remove_class++) {
            for (int i = 0; i < sec.duration_.at(lecture_in_section); i++) {
              day_time period = make_pair(sec.day_.at(lecture_in_section), sec.start_time_.at(lecture_in_section) + i);
              timetable.erase(period);

            }
        }
    }
    
  } 
}

void Scheduler::print_timetable(std::unordered_map<day_time, ClassChosen, day_time_hash>& timetable){
  std::cout<<"Timetable option: "<<std::endl;
  for(std::pair<day_time, ClassChosen> element : timetable){
    auto day = element.first.first;
    auto time = element.first.second;
    auto course = element.second.course_code;
    auto section_chosen = element.second.section;
    auto type = element.second.type;

    string class_type;
    if(type == 0 ){
      class_type = "lecture ";
    }else if (type == 1){
      class_type = "tutorial ";
    }else{
      class_type = "practical ";
    }

    std::cout<<"  course "<< course << " " << class_type << " section " << section_chosen << " on day " << day <<" at "<<time <<std::endl;
  }
}

Scheduler::Scheduler(){
  
}
