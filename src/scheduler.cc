#include <string>
#include <iostream>
#include <stdlib.h>
#include <unordered_set>
#include <unordered_map> 

#include "period.hh"
#include "print_functions.hh"

#include "scheduler.hh"

using namespace std; 

/**
 * TODO: add support for tutorials and practicals (verify it works)
 * TODO: add/remove classes 
 * TODO: add constraints 
 * TODO: add support for async classes 
 * TODO: Add in constraints that force course to be in a certain semester. 
 * TODO: If a course has a prereq also being schedule, make sure the pre req is first 
 * TODO: Add better time table printing for courses longer than one hour  
 * TODO: Do we need to add parallelism to speed it up?? 
 * TODO: remove duplicate timetables 
 * TODO: set max courses per semester to 6
 */


void Scheduler::schedule_classes(unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash>& courses ){
  std::unordered_map<Date, SelectedCourseSection, Date_Hash> timetable;
  schedule_classes_helper(courses, timetable);
  //cout << endl << timetables_str[0][0] << endl;
  
  for (std::vector<std::string> timetable_str: timetables_str) {
    
    std::sort(timetable_str.begin(), timetable_str.end());
    /*cout << "New Option: " << endl;
    for (std::string class_str: timetable_str) {
       cout << class_str << endl;
    } */
  }
}

void Scheduler::schedule_classes_helper(unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash>& courses, std::unordered_map<Date, SelectedCourseSection, Date_Hash>& timetable){

  // When all classes have been added to the timetable, save this valid timetable (base case)
  if(courses.size() == 0){
    // TODO: check for uniqueness here
    //if (unique_check(timetable)) {
      timetables_.push_back(timetable);
      // Print out valid timetable (used for debuggin)
      print_timetable(timetable);
    //}
    
  }

  // Loop through all of the Course Offerings (ie the course and all its sections)
  for(auto course : courses){
    std::cout<<"TRYING TO ADD LEC "<< course.courseID()<<endl;
    attempt_to_add_section(timetable, LEC, course, courses);
    std::cout<<"TRYING TO ADD TUT "<< course.courseID()<<endl;
    attempt_to_add_section(timetable, TUT, course, courses);
    std::cout<<"TRYING TO ADD PARA "<< course.courseID()<<endl;
    attempt_to_add_section(timetable, PRA, course, courses);
  } 
}




void Scheduler::attempt_to_add_section(std::unordered_map<Date, SelectedCourseSection, Date_Hash>& timetable, int class_type, CourseOfferings course, unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash>& courses){
    int num_sections = 0;
    if(class_type == LEC){
          num_sections = (int) course.numLecSections();
    }else if(class_type == TUT){
          num_sections = (int) course.numTutSections();
        }else{
          num_sections = (int) course.numPraSections();
        }
    
    // Loop through all of the possible lecture sections in the course 
    for(int section_id = 0; section_id < num_sections; section_id++){
      cout<<"Looking at section id "<<section_id<<endl;
        Section section;
        if(class_type == LEC){
          section = course.lecture_sections_.at(section_id);
        }else if(class_type == TUT){
          section = course.tutorial_sections_.at(section_id);
        }else{
          section = course.practical_sections_.at(section_id);
        }
        int class_in_section;
        // Create an object to represent the section that was chosen 
        SelectedCourseSection class_chosen{
          .course_code = course.course_id_,
          .type = class_type, // Lecture
          .section = section_id,
          .semester = section.semester_.at(0) // Each section should only be in either F or W (need support for full year courses)
          // semester can be a char instead of a vector
          // F - FALL W - WINTER B - BOTH
        };
      bool successfully_inserted;
      // Try adding all of the lecture sections for that section and class to the timetable 
      for (class_in_section = 0; class_in_section < (int)section.duration_.size(); class_in_section++) {
          // Add a entry for every hour that the lecure has
          for (int i = 0; i < section.duration_.at(class_in_section); i++) {
              // If the class is in the winter offset the day by 5 ([1,5] = fall, [6,10] = winter)
              int semester_offset = (class_chosen.semester == 'F') ? 0 : 5;
              Date period = make_pair(section.day_.at(class_in_section) + semester_offset, section.start_time_.at(class_in_section) + i);
                
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
              for (int remove_class = 0; remove_class <= class_in_section; remove_class++) {
                for (int i = 0; i < section.duration_.at(remove_class); i++) {
                      Date period = make_pair(section.day_.at(remove_class), section.start_time_.at(remove_class) + i);
                      timetable.erase(period);
                  }
              }
              break;
          }
                  
    }
          /** 
         * Call this function recursively to place the remaining classes 
         * Remove the current class from the courses list and then recall this function to place the rest of the classes
         */
        unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash> remaining_classes = courses;
        remaining_classes.erase(course);
        schedule_classes_helper(remaining_classes, timetable);
        for (int remove_class = 0; remove_class < class_in_section; remove_class++) { //should this be < or <= (<= seg faults)
            for (int i = 0; i < section.duration_.at(remove_class); i++) {
              Date period = make_pair(section.day_.at(remove_class), section.start_time_.at(remove_class) + i);
              timetable.erase(period);

            }
    }
  }
}

void Scheduler::print_timetable(std::unordered_map<Date, SelectedCourseSection, Date_Hash>& timetable){
  std::cout<<"Timetable option: "<<std::endl;
  
  std::string class_str;
  std::vector<std::string> timetable_str;
  for(std::pair<Date, SelectedCourseSection> element : timetable){
    auto day = element.first.first;
    auto time = element.first.second;
    auto course = element.second.course_code;
    auto section_chosen = element.second.section;
    auto type = element.second.type;
    auto semester = element.second.semester;

    std::cout<<"  "<<semester<<": "<< course << " " << toClassType(type) << " section " << (section_chosen+1) << " on " << toDay(day) <<" at "<<toTime(time) <<std::endl;
    
    class_str.push_back(semester);
    class_str.append(course);
    class_str.append(toClassType(type));
    class_str.append(std::to_string(section_chosen+1));
    timetable_str.push_back(class_str);
    class_str = "";
  }
  timetables_str.push_back(timetable_str);
}

// Default constructor
Scheduler::Scheduler(){
  
}
