#ifndef SECTION_H
#define SECTION_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Section {
private:
public:
    Section(int section_id,
            vector<int> duration,
            vector<int> start_time,
            vector<char> semester,
            vector<int> day,
            vector<bool> async) {
        section_id_ = section_id;
        duration_ = duration;
        start_time_ = start_time;
        day_ = day;
        semester_ = semester;
        async_ = async;
    }
    Section() {}
    int section_id_;
    vector<int> duration_;   // length of class in hour integer segements
    vector<int> start_time_; // military time in hours
    vector<int> day_;        // Monday = 0 .... Fri = 5
    vector<char> semester_;  //'F' or 'S'
    vector<bool> async_;

    int num_classes_in_section() {
        return duration_.size();
    }

    int num_hours_in_section(){
        int hours = 0;
        for(auto i : duration_){
            hours+=i;
        }
        return hours;
    }
};

#endif
