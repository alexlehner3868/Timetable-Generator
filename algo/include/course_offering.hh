#ifndef OFFERING_H
#define OFFERING_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "section.hh"

using namespace std;

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
    }

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

    string name_;
    string course_id_;
    vector<Section> lecture_sections_;
    vector<Section> tutorial_sections_;
    vector<Section> practical_sections_;
};

#endif