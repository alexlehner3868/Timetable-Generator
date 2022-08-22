#include <string>
#include <iostream>
#include <stdlib.h>
#include <unordered_set>
#include <unordered_map> 

#include "period.hh"

#include "scheduler.hh"

using namespace std; 

/**
 * TODO: add support for tutorials and practicals 
 * TODO: add support for async classes 
 * TODO: Add in constraints that force course to be in a certain semester. 
 * TODO: If a course has a prereq also being schedule, make sure the pre req is first 
 * TODO: Add better time table printing for courses longer than one hour  
 * TODO: make SelectedCourseSection a class 
 * TODO: Do we need to add parallelism to speed it up?? 
 */


void Scheduler::schedule_classes(unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash>& courses ){
  std::unordered_map<Date, SelectedCourseSection, Date_Hash> timetable;
  schedule_classes_helper(courses, timetable);
}

void Scheduler::schedule_classes_helper(unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash>& courses, std::unordered_map<Date, SelectedCourseSection, Date_Hash>& timetable){

  // When all classes have been added to the timetable, save this valid timetable (base case)
  if(courses.size() == 0){
    timetables_.push_back(timetable);
    // Print out valid timetable (used for debuggin)
    print_timetable(timetable);
  }

  // Loop through all of the Course Offerings (ie the course and all its sections)
  for(auto course : courses){
    // Loop through all of the possible sections in the course 
    for(int section_id = 0; section_id < course.lecture_sections_.size(); section_id++){
        bool successfully_inserted; 
        Section section = course.lecture_sections_.at(section_id);
        
        // Create an object to represent the section that was chosen 
        SelectedCourseSection class_chosen{
          .course_code = course.course_id_,
          .section = section_id,
          .type = 1, // Lecture
          .semester = section.semester_.at(section_id)
        };

        // Try adding all of the lecture sections for that section and class to the timetable 
        int lecture_in_section;
        for (lecture_in_section = 0; lecture_in_section < section.duration_.size(); lecture_in_section++) {
            // Add a entry for every hour that the lecure has
            for (int i = 0; i < section.duration_.at(lecture_in_section); i++) {
                // If the class is in the winter offset the day by 5 ([1,5] = fall, [6,10] = winter)
                int semester_offset = (class_chosen.semester == 'F') ? 0 : 5;
                Date period = make_pair(section.day_.at(lecture_in_section) + semester_offset, section.start_time_.at(lecture_in_section) + i);
                
                // Insert into the timetable  
                auto it = timetable.insert(std::make_pair(period, class_chosen));
                successfully_inserted = it.second;
                
                // Check if the class was sucessfully inserted 
                if (!successfully_inserted) {
                    break;
                    //Combination is invalid
                    //Time occupied by another course offering
                }
                
            }

            // There is a conflict with the class section that was just inputted so remove it 
            if (!successfully_inserted) {
                for (int remove_class = 0; remove_class <= lecture_in_section; remove_class++) {
                    for (int i = 0; i < section.duration_.at(lecture_in_section); i++) {
                        Date period = make_pair(section.day_.at(lecture_in_section), section.start_time_.at(lecture_in_section) + i);
                        timetable.erase(period);
                    }
                }
                break;
            }

        }

        /** 
         * Call this function recusviely to place the remaining classes 
         * Remove the current class from the courses list and then recall this function to place the rest of the classes
         */
        unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash> remaining_classes = courses;
        remaining_classes.erase(course);
        schedule_classes_helper(remaining_classes, timetable);
        for (int remove_class = 0; remove_class < lecture_in_section; remove_class++) { //should this be < or <= (<= seg faults)
            for (int i = 0; i < section.duration_.at(remove_class); i++) {
              Date period = make_pair(section.day_.at(remove_class), section.start_time_.at(remove_class) + i);
              timetable.erase(period);

            }
        }
    }
    
  } 

}

void Scheduler::print_timetable(std::unordered_map<Date, SelectedCourseSection, Date_Hash>& timetable){
  std::cout<<"Timetable option: "<<std::endl;
  for(std::pair<Date, SelectedCourseSection> element : timetable){
    auto day = element.first.first;
    auto time = element.first.second;
    auto course = element.second.course_code;
    auto section_chosen = element.second.section;
    auto type = element.second.type;
    auto semester = element.second.semester;
    string class_type;
    if(type == 0 ){
      class_type = "lecture ";
    }else if (type == 1){
      class_type = "tutorial ";
    }else{
      class_type = "practical ";
    }

    std::cout<<"  "<<semester<<": course "<< course << " " << class_type << " section " << section_chosen << " on day " << day <<" at "<<time <<std::endl;
  }
}

// Default constructor
Scheduler::Scheduler(){
  
}
