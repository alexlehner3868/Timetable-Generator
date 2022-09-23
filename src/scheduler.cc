#include <string>
#include <iostream>
#include <stdlib.h>
#include <unordered_set>
#include <unordered_map> 
#include <thread>
#include <algorithm>
#include <random>
//#include <tbb/parallel_for.h>
//#include <tbb/atomic.h>

#include "period.hh"
#include "print_functions.hh"

#include "scheduler.hh"

using namespace std; 

/**
 * TODO: add support for tutorials and practicals (verify it works)
 * TODO: add/remove classes 
 * TODO: add constraints 
 * TODO: add support for async classes 
 * TODO: add option to allow conflicts? -> uoft allows you to enroll even when you have 3 conflicts at once
 * TODO: Add in constraints that force course to be in a certain semester. 
 * TODO: If a course has a prereq also being schedule, make sure the pre req is first 
 * TODO: Add better time table printing for courses longer than one hour  
 * TODO: Do we need to add parallelism to speed it up?? 
 * TODO: set max courses per semester to 6
 * TODO: currently only prints timetable if all classes are inserted. add a config to output half complete ones too
 */


void Scheduler::schedule_classes(unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash>& courses ){
  std::unordered_map<Date, SelectedCourseSection, Date_Hash> timetable;
  schedule_classes_helper(courses, timetable, true);
}

void Scheduler::schedule_classes_helper(unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash>& courses, std::unordered_map<Date, SelectedCourseSection, Date_Hash>& timetable, bool first_iteration){

  // When all classes have been added to the timetable, save this valid timetable (base case)
  if(courses.size() == 0){
    //cout << "no more courses left" << endl;
    if (timetables_.size() < max_number_of_timetables && unique_check(timetable)) {
      //cout << "Appending unique timetable" << endl;
      timetables_.push_back(timetable);
      // Print out valid timetable (used for debugging)
      //print_timetable(timetable);
    }
  }

  if(timetables_.size() >= max_number_of_timetables){
    return;
  }

  auto rng = std::default_random_engine {};
  vector<CourseOfferings> randomly_sorted_courses(courses.begin(), courses.end());
  shuffle(begin(randomly_sorted_courses), end(randomly_sorted_courses), rng);

  // Loop through all of the Course Offerings (ie the course and all its sections)
  for(auto course : randomly_sorted_courses){
    attempt_to_add_section(timetable, LEC, course, courses);
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
  //cout << "there are " << num_sections << " sections of course" << course.course_id_ << endl;
  // Loop through all of the possible lecture sections in the course 
  for(int section_id = 0; section_id < num_sections; section_id++){
    //cout<<"Looking at section id "<<section_id<<endl;
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
      //cout << class_type << " is class type and " << section_id << " is the section id" << endl; 
    bool successfully_inserted;
    Date period;
      // Try adding all of the lecture sections for that section and class to the timetable 
      for (class_in_section = 0; class_in_section < (int)section.duration_.size(); class_in_section++) {
          // Add a entry for every hour that the lecure has
          //cout << "On section " << class_in_section << " of class" << endl; 
          for (int i = 0; i < section.duration_.at(class_in_section); i++) {
              // If the class is in the winter offset the day by 5 ([1,5] = fall, [6,10] = winter)
              int semester_offset = (class_chosen.semester == 'F') ? 0 : 5;
              period = make_pair(section.day_.at(class_in_section) + semester_offset, section.start_time_.at(class_in_section) + i);
              //cout << "Inserting class " << class_chosen.course_code << endl;
              //cout << "Inserting section " << class_in_section << endl;
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
          // Don't remove the class that it conflicted with - simply remove the others
          if (!successfully_inserted) {
              for (int remove_class = 0; remove_class <= class_in_section; remove_class++) {
                for (int i = 0; i < section.duration_.at(remove_class); i++) {
                      Date remove_period = make_pair(section.day_.at(remove_class), section.start_time_.at(remove_class) + i);
                      //if you want to see conflicts uncomment this
                      //cout << "Conflict detected, not able to add class " << course.course_id_ << " to schedule." << endl;
                      if (remove_period != period) {
                        timetable.erase(remove_period);
                      }
                  }
              }

              break;
          }


    }

    /** 
     * Call this function recursively to place the remaining classes 
     * Remove the current class from the courses list and then recall this function to place the rest of the classes
     */
    if (class_type == LEC) {
      //add TUT now
      attempt_to_add_section(timetable, TUT, course, courses);
      //remove class from timetable
      for (int remove_class = 0; remove_class < class_in_section; remove_class++) { //should this be < or <= (<= seg faults)
            for (int i = 0; i < section.duration_.at(remove_class); i++) {
              Date period = make_pair(section.day_.at(remove_class), section.start_time_.at(remove_class) + i);
              timetable.erase(period);
            }
      } 
    } else if (class_type == TUT) {
      //cout << "type tut and about to call PRA" << endl;
      attempt_to_add_section(timetable, PRA, course, courses);
      for (int remove_class = 0; remove_class < class_in_section; remove_class++) { //should this be < or <= (<= seg faults)
            for (int i = 0; i < section.duration_.at(remove_class); i++) {
              Date period = make_pair(section.day_.at(remove_class), section.start_time_.at(remove_class) + i);
              timetable.erase(period);
            }
      } 
    } else {
      //cout << "type PRA and removing course" << endl;
      //print_timetable(timetable);
      unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash> remaining_classes = courses;
      remaining_classes.erase(course);
      //cout << " (section exists) is courses empty?: " << remaining_classes.empty() << endl;
      schedule_classes_helper(remaining_classes, timetable);
      
      //remove class from timetable
      for (int remove_class = 0; remove_class < class_in_section; remove_class++) { //should this be < or <= (<= seg faults)
            for (int i = 0; i < section.duration_.at(remove_class); i++) {
              Date period = make_pair(section.day_.at(remove_class), section.start_time_.at(remove_class) + i);
              timetable.erase(period);
            }
      } 
    }

    
    
    
  }
  if (num_sections < 1) {
    //if section is empty DO SOMETHING
    //cout << "there are no sections for class "<< course.course_id_ << " and of type " << class_type << endl;
    if (class_type == LEC) {
        //add TUT now
        attempt_to_add_section(timetable, TUT, course, courses);
        //remove class from timetable
    } else if (class_type == TUT) {
        attempt_to_add_section(timetable, PRA, course, courses);
    } else {
       // cout << "type PRA and removing course" << endl;
        //print_timetable(timetable);
        unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash> remaining_classes = courses;
        remaining_classes.erase(course);
        //cout << "(section doesn't exist) is courses empty?: " << remaining_classes.empty() << endl;
        //cout << "erasing course: " << course.course_id_ << endl;
        schedule_classes_helper(remaining_classes, timetable);
    }
  }
}

int Scheduler::max_sections_scheduled(){
  int max_placed = 0;
    for(auto timetable : timetables_){
      max_placed = max((int)timetable.size(), max_placed);
    }
    return max_placed;
}

void Scheduler::print_timetables(){
  // TODO: can probably get this as a constant and then add a check here if no full timetable is created
  //int max_scheduled = max_sections_scheduled(); //too slow
  int offset = max_number_of_timetables / number_of_timetables;
  // TODO: add error checking here becuase we could run into an issue where we arent finding full timetables 
  // ie here are sizes [10, 10, 10, 2, 2] where the only full timetbales are the first options but we skip them
  for(int i = 0; i < max_number_of_timetables; i++){
    int index = i *offset;
  // TODO: if a full timetable exists print it here
    if(index < timetables_.size()){
      print_timetable(timetables_[index]);
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

    std::cout<<"  "<<semester<<": "<< course << " " << toClassType(type) << " section " << (section_chosen+1) << " on " << toDay(day) <<" at "<<toTime(time) <<std::endl;
    
  }
}

std::vector<std::string> Scheduler::make_timetable_str(std::unordered_map<Date, SelectedCourseSection, Date_Hash>& timetable) {
  std::string class_str;
  
  //timetable_str is the vector of strings containing one whole timetable option
  std::vector<std::string> timetable_str;
  for(std::pair<Date, SelectedCourseSection> element : timetable){
    auto course = element.second.course_code;
    auto section_chosen = element.second.section;
    auto type = element.second.type;
    auto semester = element.second.semester;

    class_str.push_back(semester);
    class_str.append(course);
    class_str.append(toClassType(type));
    class_str.append(std::to_string(section_chosen+1));
    timetable_str.push_back(class_str);
    class_str = "";
  }
  
  //sort timetables_str 
  std::sort(timetable_str.begin(), timetable_str.end());
  return timetable_str;
}

/*
* Function to check if a timetable already exists before adding it to
* timetables_
*/
bool Scheduler::unique_check(std::unordered_map<Date, SelectedCourseSection, Date_Hash>& timetable) {
  
  //first get the timetable that was just generated
  std::vector<std::string> new_timetable_str = make_timetable_str(timetable);

  // timetables_str contains all timetables as vectors of strings
  if (timetables_str.size() == 0) {
    //no timetables exist, so the first added must be valid
    //add timetable
    timetables_str.push_back(new_timetable_str);
    return true;
  } 

  //other time tables exist so let's check them for uniqueness
  //iterate through timetables_str to see if the one we are trying to add already exists
  for (auto timetable: timetables_str) {
    //check if timetable in our generated timetables is equivalent to the one we are trying to add
    if (timetable == new_timetable_str) {
      //if it does exist, nothing needs to be done - don't add
      return false;
    }
  }
  //couldn't find matching timetable - so add it to timetables
  timetables_str.push_back(new_timetable_str);
  return true;
}
// Default constructor
Scheduler::Scheduler(){
  
}
