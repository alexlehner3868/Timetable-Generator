#ifndef CONSTRAINTS_H
#define CONSTRAINTS_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "course_data.hh"
#include "course_offering.hh"
#include "date.hh"

using namespace std;

/**
 * @brief
 * Constraints List:
 * ☑ Block off Time
 * ☐ No large chunks of class w/ no break
 * ☐ early constraint
 * ☐ late constraint (same as above)
 * ☐ condense schedule
 * ☐
 *
 */

enum constraint_priority {
    NO_PRIORITY = 0,
    NICE_TO_HAVE = 1,
    GOOD_TO_HAVE = 2,
    MUST_HAVE = 3,
};

const int cost_multiplier = 10;
const int meet_preference = -15;

class ConstraintHandler {
private:
    // Constraints handled per section
    bool prefer_morning_classes_ = false;
    bool prefer_evening_classes_ = false;
    bool prefer_afternoon_classes_ = false;
    pair<int, int> no_classes_after_X_;                    // <X, priority>
    pair<int, int> no_classes_before_X_;                   // <X, prioity>
    unordered_map<Date, int, Date_Hash> time_constraints_; // key: (day, time), value: priority

    // Constraints handled per timetable
    int breaks_between_classes_ = NO_PRIORITY; // do we need?
    bool minimize_days_at_school_ = false;
    pair<int, int> back_to_back_constraint_; // <max hours back to back, priority>

public:
    ConstraintHandler();
    void add_time_constraint(int start_time, int duration, int day, char semester, int priority);
    void set_back_to_back_constraint(int max_back_to_back, int priority);
    void set_no_classes_after_X_constraint(int X, int priority);
    void set_no_classes_before_X_constraint(int X, int priority);
    void set_minimize_days_at_school_constraint(bool ans);
    void set_prefer_morning_classes_constraint(bool ans);
    void set_prefer_afternoon_classes_constraint(bool ans);
    void set_prefer_evening_classes_constraint(bool ans);
    void reorder_time_constraints_based_on_priority();

    bool preprocess_high_priority_classes_out(
        unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash> &original_offerings);

    int cost_of_class(Date d);
};

#endif