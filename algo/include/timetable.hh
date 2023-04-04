#ifndef TIMETABLE_H
#define TIMETABLE_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <vector>

#include "course_data.hh"
#include "course_offering.hh"
#include "date.hh"

using namespace std;


class TimeTable {
public:
    std::unordered_map<Date, SelectedCourseSection, Date_Hash> scheduled_classes;
    std::unordered_set<string> scheduled_async_classes;
    int num_async_classes = 0;
    int current_time_table_cost = 0;
    int chose_fall = 0;
    int chose_winter = 0;
    TimeTable() {}
    TimeTable(std::unordered_map<Date, SelectedCourseSection, Date_Hash> &classes, int cost) {
        scheduled_classes = classes;
        current_time_table_cost = cost;
    }

    // Overload the < operator.
    bool operator<(const TimeTable &other) {
        return this->current_time_table_cost < other.current_time_table_cost;
    }
    // Overload the > operator.
    bool operator>(const TimeTable &other) {
        return this->current_time_table_cost > other.current_time_table_cost;
    }

    bool insert(pair<Date, SelectedCourseSection> possible_section) {
        auto it = scheduled_classes.insert(possible_section);
        return it.second;
    }

    bool exists(Date period) {
        return (scheduled_classes.find(period) != scheduled_classes.end());
    }

    void erase(Date period) {
        scheduled_classes.erase(period);
    }

    int size(){
        return scheduled_classes.size();
    }

    SelectedCourseSection atTime(Date period){
        return scheduled_classes[period];
    }

    bool insert(SelectedCourseSection possible_section){
        scheduled_async_classes.insert(async_course_string(possible_section));
        return true;
    }

    void erase (SelectedCourseSection section){
        scheduled_async_classes.erase(async_course_string(section));
    }
    
    string async_course_string(SelectedCourseSection possible_section){
        return possible_section.course_code +  " " + to_string(possible_section.section) + " " + possible_section.semester + " "+ to_string(possible_section.type);
    }

    std::unordered_map<Date, SelectedCourseSection, Date_Hash> classes() {
        return scheduled_classes;
    }

    SelectedCourseSection create_class_section(string course_info){
        stringstream ss(course_info);

        string course_code;
        string class_type;
        string section;
        string semester;

        ss >> course_code;
        ss >> section;
        ss >> semester;
        ss >> class_type;

        SelectedCourseSection course{
            .course_code = course_code,
            .type = stoi(class_type), // Lecture
            .section = stoi(section),
            .semester = semester[0],
            .async = true
        };
        return course;
    }

    vector<pair<Date, SelectedCourseSection>> all_classes(){
        vector<pair<Date, SelectedCourseSection>> courses;
        for(auto c : scheduled_classes){
            courses.push_back({c.first, c.second});
        }
        for(string c : scheduled_async_classes){
            courses.push_back({{-1, -1}, create_class_section(c)});
        }
        return courses;
    } 

    int cost() {
        return current_time_table_cost;
    }

    void add_cost(int c) {
        current_time_table_cost += c;
    }

    bool balanced() {
      return std::abs(this->chose_fall - this->chose_winter) <= 3;
    }
};

struct CompareTimeTable {
    bool operator()(TimeTable const &t1, TimeTable const &t2) {
        return t1.current_time_table_cost < t2.current_time_table_cost;
    }
};



#endif
