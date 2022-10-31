#include "course_offering.hh"

#include <iostream>
#include <string>

using namespace std;

void CourseOfferings::prune_semester() {
    if (this->semester_) {
        for (auto it = this->lecture_sections_.begin();
                it != this->lecture_sections_.end();) {
            if (char2sem(it->semester_[0]) != this->semester_)
                it = this->lecture_sections_.erase(it);
            else
                it++;
        }
        for (auto it = this->tutorial_sections_.begin();
                it != this->tutorial_sections_.end();) {
            if (char2sem(it->semester_[0]) != this->semester_)
                it = this->tutorial_sections_.erase(it);
            else
                it++;
        }
        for (auto it = this->practical_sections_.begin();
                it != this->practical_sections_.end();) {
            if (char2sem(it->semester_[0]) != this->semester_)
                it = this->practical_sections_.erase(it);
            else
                it++;
        }
    }
}

