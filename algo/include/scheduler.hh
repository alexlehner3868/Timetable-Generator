#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <algorithm>
#include <iostream>
#include <optional>
#include <queue>
#include <random>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "constraints.hh"
#include "course_offering.hh"
#include "date.hh"
#include "period.hh"
#include "timetable.hh"
#include "stats.hh"

using namespace std;

class Scheduler {
private:
    priority_queue<TimeTable, vector<TimeTable>, CompareTimeTable> timetables_;
    std::vector<std::vector<std::string>> timetables_str;
    int max_sections_scheduled();
    int max_num_of_timetables_to_show = 20;
    int number_of_explored_timetables = 0;
    int max_number_of_timetables_to_explore;
    ConstraintHandler* constraint_handler_ = nullptr;
    StatCollector stats_collector_;
    int maximum_number_of_sections_ = 0;
    std::chrono::time_point<std::chrono::system_clock> start_schedule_time_;

    std::default_random_engine rng_ = std::default_random_engine{};
    // Stats
    int partial_timetables_pruned_ = 0;
    int full_timetable_pruned_ = 0;
    int timetables_not_explored_ = 0;
    bool output_stats = true;
    int unique_timetables_found_ = 0;
    bool check_for_constraint_ = false;
    // For output
    string result_string; 

public:
    bool allow_incomplete = false;

    Scheduler();
    vector<TimeTable> schedule_classes(
        priority_queue<CourseOfferings, vector<CourseOfferings>, greater<CourseOfferings>> &courses,
        ConstraintHandler *constraint_handler);
    void schedule_classes_helper(
        priority_queue<CourseOfferings, vector<CourseOfferings>, greater<CourseOfferings>> &courses,
        TimeTable &timetable);
    void print_timetable(TimeTable &timetable, int preset);
    string jsonify(TimeTable &timetable);
    bool attempt_to_add_section(
        TimeTable &timetable,
        int class_type,
        CourseOfferings course,
        priority_queue<CourseOfferings, vector<CourseOfferings>, greater<CourseOfferings>> &courses, char sem);
    bool unique_check(TimeTable &timetable);
    std::vector<std::string> make_timetable_str(TimeTable &timetable);
    void print_timetables(vector<TimeTable> timetables, string result_string);
    string get_result_string();
    int set_num_timetables(int num_timetables);
    int set_max_explore(int explore_timetables);
};

#endif
