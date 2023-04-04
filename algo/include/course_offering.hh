#ifndef OFFERING_H
#define OFFERING_H

#include <iostream>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "section.hh"

using namespace std;

enum class Semester {
    Fall,
    Winter,
};

inline optional<Semester> char2sem(char c) {
    switch (c) {
        case 'F':
            return make_optional(Semester::Fall);
        case 'S':
            return make_optional(Semester::Winter);
        default:
            return std::nullopt;
    }
}

class CourseOfferings {
private:
public:
    CourseOfferings(string name,
                    string course_id,
                    vector<Section> &lec,
                    vector<Section> &tut,
                    vector<Section> &pra) {
        name_ = name;
        course_id_ = course_id;
        lecture_sections_ = lec;
        tutorial_sections_ = tut;
        practical_sections_ = pra;
        semester_ = nullopt;
    }

    void semester(Semester &&semester) {
        this->semester_ = make_optional(semester);
    }

    bool prune_semester();

    bool operator==(const CourseOfferings &otherCourse) const {
        return course_id_ == (otherCourse.course_id_);
    }

    string courseID() {
        return course_id_;
    }

    int numLecSections() {
        return lecture_sections_.size();
    }

    int numTutSections() {
        return tutorial_sections_.size();
    }

    int numPraSections() {
        return practical_sections_.size();
    }

    struct CourseOfferingHash {
        size_t operator()(const CourseOfferings &c) const {
            return hash<string>()(c.course_id_);
        }
    };

   int numCourses(){
         int num_lec = (lecture_sections_.size() > 0 ) ? lecture_sections_[0].num_hours_in_section() : 0;
         int num_pra = (practical_sections_.size() > 0 ) ? practical_sections_[0].num_hours_in_section() : 0;
         int num_tut = (tutorial_sections_.size() > 0 ) ? tutorial_sections_[0].num_hours_in_section() : 0;
         return num_lec+num_pra+num_tut;
     }
    
    pair<int, int> sec_per_sem(){
        int f_count = 0;
        int w_count = 0;
        if(numLecSections() > 0){
            for(auto sec : lecture_sections_){
                for(auto sem : sec.semester_){
                    if (sem == 'F'){
                        f_count++;
                    }else{
                        w_count++;
                    }
                }
            }
        }else if(numTutSections() > 0){
            for(auto sec : tutorial_sections_){
                for(auto sem : sec.semester_){
                    if (sem == 'F'){
                        f_count++;
                    }else{
                        w_count++;
                    }
                }
            }
        }else if(numPraSections() > 0){
            for(auto sec : practical_sections_){
                for(auto sem : sec.semester_){
                    if (sem == 'F'){
                        f_count++;
                    }else{
                        w_count++;
                    }
                }
            }
        }
        return pair<int, int>(f_count, w_count);
    }

    string name_;
    string course_id_;
    vector<Section> lecture_sections_;
    vector<Section> tutorial_sections_;
    vector<Section> practical_sections_;
    optional<Semester> semester_;
};

#endif
