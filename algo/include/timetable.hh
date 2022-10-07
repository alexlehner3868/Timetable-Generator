#ifndef TIMETABLE_H
#define TIMETABLE_H

#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include "course_offering.hh"
#include "course_data.hh"
#include "date.hh"
#include "scheduler.hh"

using namespace std;

class TimeTable {
    public:
    std::unordered_map<Date, SelectedCourseSection, Date_Hash> scheduled_classes;
    int current_time_table_cost = 0;
    TimeTable(){

    }
    TimeTable(std::unordered_map<Date, SelectedCourseSection, Date_Hash>& classes, int cost){
        scheduled_classes = classes;
        current_time_table_cost = cost;
    }

    //Overload the < operator.
    bool operator< (const TimeTable& other)
    {
        return this->current_time_table_cost < other.current_time_table_cost;
    }
    //Overload the > operator.
    bool operator> (const TimeTable& other)
    {
        return this->current_time_table_cost > other.current_time_table_cost;
    }
    
    bool insert(pair<Date, SelectedCourseSection> possible_section){
      auto it = scheduled_classes.insert(possible_section);
      return it.second;
    }

    bool exists(Date period){
        return (scheduled_classes.find(period) != scheduled_classes.end());
    }

    void erase(Date period){
        scheduled_classes.erase(period);
    }

    std::unordered_map<Date, SelectedCourseSection, Date_Hash> classes(){
        return scheduled_classes;
    }

    int cost(){
        return current_time_table_cost;
    }

    void add_cost(int c){
        current_time_table_cost += c;
    }
};

struct CompareTimeTable {
    bool operator()(TimeTable const& t1, TimeTable const& t2)
    {
        return t1.current_time_table_cost < t2.current_time_table_cost;
    }
};

#endif