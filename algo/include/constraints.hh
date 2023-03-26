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
    NICE_TO_HAVE = 3,
    GOOD_TO_HAVE = 6,
    MUST_HAVE = 10,
};

class ConstraintHandler {
private:
    // Constraints handled per section
    int no_morning_classes_;                           // int = priority
    int no_evening_classes_;                           // int = priority
    int no_afternoon_classes_;                         // int = priority
    pair<int, int> no_classes_after_X_;                    // <X, priority>
    pair<int, int> no_classes_before_X_;                   // <X, priority>
    int prefer_async_classes_;                             // int = priority 
    int prefer_sync_classes_;                               // int = priority


    unordered_map<Date, int, Date_Hash> time_constraints_; // key: (day, time), value: priority

    // Constraints handled per timetable
    int minimize_days_at_school_;                          // int = priority
    pair<int, int> back_to_back_constraint_; // <max hours back to back, priority>
    pair<int, int> no_more_than_X_hours_per_day_;          // <X, priority>
    pair<int, int> no_breaks_larger_than_X_;                // <X, prioirty>
    int prefer_lunch_break_;                                   // int = priority
    int prefer_dinner_break_;                                  //int = prioirty 

    // For Stats
    int number_of_classes_preprossed_out = 0;

public:
    ConstraintHandler();

    // Add/configure constraints
    void add_time_constraint(int start_time, int duration, int day, char semester, int priority);
    void set_back_to_back_constraint(int max_back_to_back, int priority);
    void set_no_classes_after_X_constraint(int X, int priority);
    void set_no_classes_before_X_constraint(int X, int priority);
    void set_minimize_days_at_school_constraint(int priority);
    void set_no_morning_classes_constraint(int priority);
    void set_no_afternoon_classes_constraint(int priority);
    void set_no_evening_classes_constraint(int priority);
    void set_prefer_async_classes_constraint(int priority);
    void set_prefer_sync_classes_constraint(int priority);
    void set_no_more_than_X_hours_per_day_constraint(int X, int priority);
    void set_no_breaks_larger_than_X_constraint(int X, int priority);
    void set_prefer_lunch_break_constraint(int priority);
    void set_prefer_dinner_break_constraint(int priority);

    void reorder_time_constraints_based_on_priority();

    // Remove sections for initial pruning 
    bool preprocess_high_priority_classes_out(
        unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash> &original_offerings, string& result);
    bool prune_semesters(
        unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash> &offerings);

    // Calculate costs for pruning/ranking 
    int cost_of_class(Date d);
    int cost_of_timetable(std::unordered_map<Date, SelectedCourseSection, Date_Hash> timetable);
    int sync_vs_async_cost(bool is_class_sync);
    // For stats
    stringstream output_constraints_stats();
};

#endif
