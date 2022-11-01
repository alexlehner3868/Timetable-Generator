#include "course_offering.hh"

#include <iostream>
#include <string>

using namespace std;

bool CourseOfferings::prune_semester() {
    bool had_lec = this->lecture_sections_.size() > 0;

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

    return had_lec && (this->lecture_sections_.size() > 0);
}
