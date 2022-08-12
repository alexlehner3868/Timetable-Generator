#include <string>
#include <iostream>
#include <stdlib.h>

#include "scheduler.hh"

using namespace std; 

void Scheduler::Scheduler(){
  course_offerings.clear();
  time_constraints_.clear();
  chunk_constraints_.clear();
}


void Scheduler::add_course(CourseOfferings course){
    course_offerings.insert(course);
}

void Scheduler::remove_course(CourseOfferings course){
    course_offerings.erase(course);
}

void Scheduler::add_time_constraint(TimeConstraint constraint){
  time_constraints_.insert(constraint);
}

void Scheduler::remove_time_constraint(TimeConstraint constraint){
  time_constraints_.erase(constraint);
}

void Scheduler::add_chunk_constraint(ChunkConstraint constraint){
  chunk_constraints_.insert(constraint);
}

void Scheduler::remove_chunk_constraint(ChunkConstraint constraint){
  chunk_constraints_.erase(constraint);
}

void Scheduler::add_cutoff_constraint(CutOffTimeConstraint constraint){
  cut_off_time_constraints_.insert(constraint);
}

void Scheduler::remove_cutoff_constraint(CutOffTimeConstraint constraint){
  cut_off_time_constraints_.erase(constraint);
}
