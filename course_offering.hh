#ifndef OFFERING_H
#define OFFERING_H

#include <string>
#include <iostream>
#include <vector>

#include "section.hh"

using namespace std;

class CourseOfferings {
  private:

  public:
    CourseOfferings(string name, string course_id, vector<Section>& lec, vector<Section>& tut, vector<Section>& pra){
      name_ = name;
      course_id_ = course_id;
      lecture_sections_ = lec;
      tutorial_sections_ = tut;
      practical_sections_ = pra;
    }

    string name_;
    string course_id_;
    vector<Section> lecture_sections_; 
    vector<Section> tutorial_sections_;
    vector<Section> practical_sections_;
};


#endif