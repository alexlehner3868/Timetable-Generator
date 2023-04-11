#include <algorithm>
#include <iostream>
#include <optional>
#include <random>
#include <sstream>
#include <string>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <chrono>
#include <iostream>
#include <random>
#include <execution>
#include <stdlib.h>

#include "math.h"
#include "constraints.hh"
#include "course_offering.hh"
#include "period.hh"
#include "print_functions.hh"
#include "scheduler.hh"

using namespace std;

#define MAX_SEARCH_TIME 0.75
#define QUICK_SEED 1859965549

/*
struct set_cmp {
	bool operator()(const CourseOfferings &x, const CourseOfferings &y) const { return x.numCourses() < y.numCourses(); }
};
*/
int non_test_count = 0;
vector<TimeTable> Scheduler::schedule_classes(
    priority_queue<CourseOfferings, vector<CourseOfferings>, greater<CourseOfferings>> &courses,
    ConstraintHandler* constraint_handler) {
    if(constraint_handler_ == nullptr && constraint_handler->any_constraints_exists()){
        constraint_handler_ = constraint_handler;
        check_for_constraint_ = true;
    }

    if(courses.size() == 0) return vector<TimeTable>();
    // Clear saved before scheduling 
    maximum_number_of_sections_ = 0; 
    int max_sections_total = 0;
    number_of_explored_timetables = 0; 
    timetables_ = priority_queue<TimeTable, vector<TimeTable>, CompareTimeTable>();
    timetables_str.clear();

    // create timetable
    TimeTable timetable;
    // Calculate num section in full timetable
    priority_queue<CourseOfferings, vector<CourseOfferings>, greater<CourseOfferings>> pq_copy = courses;
    while(!pq_copy.empty()) {
        auto offering = pq_copy.top();

        maximum_number_of_sections_ += offering.numCourses();
        max_sections_total += offering.numSections();
        pq_copy.pop();
    }

    // run scheduling algorithm
    start_schedule_time_ = std::chrono::system_clock::now();
    schedule_classes_helper(courses, timetable);   
    auto current_time = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(current_time - start_schedule_time_).count();
    //cout << "It took " << duration << " seconds." << endl;
    // Convert pq to vector and return
    int num_tables = timetables_.size();
    vector<TimeTable> best_time_tables(num_tables);
    vector<int> timetable_costs(num_tables);
    for (int i = num_tables-1; i >= 0; i--) {
        TimeTable t = timetables_.top();
        timetable_costs[i] = t.cost();
        best_time_tables[i] = t;
        timetables_.pop();
    }
    //cout << "We found " << num_tables << " unique timetables." << endl;
    //Reverse order so best are first 

    if (num_tables == 0) {
       result_string += "Could not generate any possible timetables";
    }
    if(output_stats){
        stats_collector_.set_scheduler_counts(partial_timetables_pruned_, full_timetable_pruned_, number_of_explored_timetables, max_number_of_timetables_to_explore, max_num_of_timetables_to_show, num_tables, unique_timetables_found_, std::chrono::duration_cast<std::chrono::microseconds>(current_time - start_schedule_time_).count());
        stats_collector_.track_constraints(constraint_handler, timetable_costs);
        stats_collector_.print_stats();
    }
    //cerr<<"Non unique "<<non_test_count<<endl;
    return best_time_tables;
}

string Scheduler::get_result_string() {
    return result_string; 
}
int print = 1;

void Scheduler::schedule_classes_helper(
    priority_queue<CourseOfferings, vector<CourseOfferings>, greater<CourseOfferings>> &courses,
    TimeTable &timetable) {

/*
    auto current_time = std::chrono::system_clock::now();
    auto durantion = std::chrono::duration_cast<std::chrono::seconds>(current_time - start_schedule_time_).count();
    if(durantion > MAX_SEARCH_TIME && timetables_.size() == 0){
        return;
    }
*/  
    if (timetables_.size() > 0 && number_of_explored_timetables > max_number_of_timetables_to_explore) {
        timetables_not_explored_++;
        return;
    }
    // All sections have been added
    if (courses.size() == 0) {
        number_of_explored_timetables++;
        int timetable_additional_cost = 0;
        if(check_for_constraint_){
            timetable_additional_cost = constraint_handler_->cost_of_timetable(timetable.classes());
            timetable.add_cost(timetable_additional_cost);
        }
           
        if (/*timetable.size() ==  maximum_number_of_sections_  &&*/ unique_check(timetable)) { 
            unique_timetables_found_++;
            // Priority queue has less than the max num of timetables
            if ((int)timetables_.size() < (int)max_num_of_timetables_to_show) {
                timetables_.push(timetable);
            } else {
                TimeTable t = timetables_.top();
                int cost = t.cost();
                if (timetable.cost() <= cost) {
                    timetables_.pop();
                    timetables_.push(timetable);
                }else{
                    full_timetable_pruned_++;
                }
            }
        }else{
            non_test_count++;
        }
        timetable.remove_cost(timetable_additional_cost);
        return;
    }

    // the current timetable is worse than the worst best cost. stop exploring it
    // TODO -> VERIFY that timetables_.top is showing the worst best cost
    if ((int) timetables_.size() > 0 && (int) timetables_.size() >= (int) max_num_of_timetables_to_show) {
        TimeTable t = timetables_.top();
        //NOT SURE IF THIS ONE LINE SHOULD BE HERE...
        //number_of_explored_timetables++;
        int cost = t.cost();
        if (timetable.cost() > cost) {
            partial_timetables_pruned_++;
            return;
        }
    }
    // Schedule the next course in the courses list 
    attempt_to_add_section(timetable, LEC, courses.top(), courses, char());   
}

bool Scheduler::attempt_to_add_section(
    TimeTable &timetable,
    int class_type,
    CourseOfferings course,
    priority_queue<CourseOfferings, vector<CourseOfferings>, greater<CourseOfferings>> &courses, char sem) {
    int num_sections = 0;

    bool found_at_least_one_option = false; 


    if (class_type == LEC) {
        num_sections = (int)course.numLecSections();
    } else if (class_type == TUT) {
        num_sections = (int)course.numTutSections();
    } else {
        num_sections = (int)course.numPraSections();
    }
    int srand_val = abs(time(nullptr)*cos(time(nullptr)) + time(nullptr)*sin(time(nullptr)));
    //value for second semester
    if (courses.size() && courses.size() < 3) { srand(srand_val);} //20874366//1418983059//55662427(long, not worth it)//1859965549(quick)//302889345
    //55662427(kinda)
    //1680587506);//1680628838//1680628943
    /*if (print) {
        cout << "the srand value is " << srand_val << endl;
        cout << course.course_id_ <<endl;
        print = 0;
    }*/
    //  Loop through all of the possible lecture sections in the course
    vector<int> shuffled_sections;
    for (int i = 0; i < num_sections; i++) {
        shuffled_sections.push_back(i);
    }
    
    int size = shuffled_sections.size();
    for (int i = 0; i < size - 1; i++) {
      int j = i + rand() % (size - i);
      swap(shuffled_sections[i], shuffled_sections[j]);
    }

    //cout<<"Scheduling "<<class_type<<" and there are #sections: "<<num_sections<<endl;
    for (int section_indx = 0; section_indx < num_sections; section_indx++) { //num_sections
       //cout<<" Adding "<<class_type<<" sec id "<< section_indx<<" cost before "<<timetable.cost()<<endl;
        Section section;
        if (class_type == LEC) {
            section = course.lecture_sections_.at(shuffled_sections[section_indx]);
        } else if (class_type == TUT) {
            section = course.tutorial_sections_.at(shuffled_sections[section_indx]);
        } else {
            section = course.practical_sections_.at(shuffled_sections[section_indx]);
        }

        int class_in_section;
        // Create an object to represent the section that was chosen
      
        SelectedCourseSection class_chosen{
            .course_code = course.course_id_,
            .type = class_type, // Lecture
            .section = section.section_id_[0],
            .semester = section.semester_.at(0), // Each section should only be in either F or W
                                                // (need support for full year courses)
                                                // semester can be a char instead of a vector
                                                // F - FALL W - WINTER Y - BOTH [WONT SAY Y ANYM]
            .async = section.async_.at(0)

        };
        int semester_offset = (class_chosen.semester == 'F') ? 0 : 5;
        if(class_type != LEC){
            if(sem != class_chosen.semester && course.numLecSections() != 0){
                continue;
            }
        }
        bool successfully_inserted = true;
        // Is this class an async class
        Date period;
        int section_cost = 0;
        // Try adding all of the lecture sections for that section and class to the timetable
        for (class_in_section = 0; class_in_section < (int)section.duration_.size();
             class_in_section++) {
            class_chosen.async = section.async_.at(class_in_section);
            if(class_chosen.async){
                successfully_inserted = timetable.insert(class_chosen);
                found_at_least_one_option = true;
            }
            
            // Add a entry for every hour that the lecure has
            for (int i = 0; i < section.duration_.at(class_in_section); i++) {
       
                // If the class is in the winter offset the day by 5 ([1,5] = fall, [6,10] = winter)
                period = make_pair(section.day_.at(class_in_section) + semester_offset,
                                   section.start_time_.at(class_in_section) + i);
                // Insert a non-async class into timetable
                successfully_inserted = timetable.insert(std::make_pair(period, class_chosen));
                
                // Check if the class was sucessfully inserted
                if (!successfully_inserted) {
                    break;
                    // Combination is invalid
                    // Time occupied by another course offering or constraint
                } else {
                    // Keep track of which semester we chose
                    if(check_for_constraint_){
                        int per_class_cost = 0;
                        int async_vs_sync_cost= 0;
                        if(!class_chosen.async){
                            per_class_cost += constraint_handler_->cost_of_class(period);
                        }
                        async_vs_sync_cost  += constraint_handler_ ->sync_vs_async_cost(class_chosen.async);
                        //cout<<"     two costs are: "<<per_class_cost<<" "<<async_vs_sync_cost<<endl;
                        section_cost += per_class_cost + async_vs_sync_cost;
                    }
                }
            }

            // There is a conflict with the class section that was just inputted so remove it
            // Don't remove the class that it conflicted with - simply remove the others
            if (!successfully_inserted ) {
                //cout<<" Unsucessful"<<endl;
                // loop through each class in the section
                for (int remove_class = 0; remove_class <= class_in_section; remove_class++) {
                    // loop through each hour of the class (ex. if one is a two hour class this will
                    // run twice)
                    if(section.async_.at(remove_class)){
                        timetable.erase(class_chosen);
                    }else{
                        for (int i = 0; i < section.duration_.at(remove_class); i++) {
                            Date remove_period = make_pair(section.day_.at(remove_class) + semester_offset,
                                                        section.start_time_.at(remove_class) + i);
                            
                            if (remove_period != period) {
                                timetable.erase(remove_period);
                            }
                        }
                    }
                   
                }
                break;
            } else {
                found_at_least_one_option = true;
            }
        }

        /**
         * Call this function recursively to place the remaining classes
         * Remove the current class from the courses list and then recall this function to place the
         * rest of the classes
         */
        if(successfully_inserted){
            // Add the cost of this section to the timetable since the whole section has been added 
             timetable.add_cost(section_cost);
            if (class_type == LEC) {
                // add TUT now
                attempt_to_add_section(timetable, TUT, course, courses, class_chosen.semester);
                // remove class from timetable
                for (int remove_class = 0; remove_class < class_in_section;
                    remove_class++) { // should this be < or <= (<= seg faults)
                    if(section.async_.at(remove_class)){
                        timetable.erase(class_chosen);
                    }else{
                        for (int i = 0; i < section.duration_.at(remove_class); i++) {
                            Date period = make_pair(section.day_.at(remove_class) + semester_offset,
                                                    section.start_time_.at(remove_class) + i);
                            timetable.erase(period);
                        }
                    }
                    
                }
            } else if (class_type == TUT) {
                attempt_to_add_section(timetable, PRA, course, courses, sem);

                for (int remove_class = 0; remove_class < class_in_section;
                    remove_class++) { // should this be < or <= (<= seg faults)
                    if(section.async_.at(remove_class)){
                         timetable.erase(class_chosen);
                    }else{
                        for (int i = 0; i < section.duration_.at(remove_class); i++) {
                            Date period = make_pair(section.day_.at(remove_class)+semester_offset,
                                                    section.start_time_.at(remove_class) + i);
                            timetable.erase(period);
                        }
                    }
                }
            } else {
                priority_queue<CourseOfferings, vector<CourseOfferings>, greater<CourseOfferings>>
                    remaining_classes = courses;
                remaining_classes.pop();

                schedule_classes_helper(remaining_classes, timetable);
   
                // remove class from timetable
                for (int remove_class = 0; remove_class < class_in_section;
                    remove_class++) { // should this be < or <= (<= seg faults)
                    if(section.async_.at(remove_class)){
                       timetable.erase(class_chosen);
                    }else{
                        for (int i = 0; i < section.duration_.at(remove_class); i++) {
                            Date period = make_pair(section.day_.at(remove_class)+semester_offset,
                                                    section.start_time_.at(remove_class) + i);
                            timetable.erase(period);
                        }
                    }
                }
            }
            timetable.remove_cost(section_cost);
        }
    }
    
    if (num_sections < 1) {
        if (class_type == LEC) {
            // add TUT now
             found_at_least_one_option = attempt_to_add_section(timetable, TUT, course, courses, sem);
            // remove class from timetable
        } else if (class_type == TUT) {
            found_at_least_one_option =  attempt_to_add_section(timetable, PRA, course, courses, sem);
        } else {

            priority_queue<CourseOfferings, vector<CourseOfferings>, greater<CourseOfferings>>
                remaining_classes = courses;
            remaining_classes.pop();

            schedule_classes_helper(remaining_classes, timetable);
        }
    }

    return  found_at_least_one_option;
}

void Scheduler::print_timetables(vector<TimeTable> timetables, string result_string) {
    int counter = timetables.size();
    if (!counter) {
        cout << "["; 
        cout << "[]";
        cout << "," << "[{";
        cout << "\"Message\":\"" << result_string <<  "\"" << "}";
        cout << "]";
        cout << "]";
    } else {
        cout << "["; 
        for (auto timetable : timetables) {
            // Output the current timetable
            cout << jsonify(timetable);
            // Reduce how many more we must output
            counter--;
            // If there are more remaining, separate by a comma
            if (counter)
            cout << ",";
        } 
        cout << "," << "[{";
        cout << "\"Message\":\"" << result_string <<  "\"" << "}]";
        cout << "]";
    }
    
}

void Scheduler::print_timetable(TimeTable &timetable, int preset) {
    //PRESET DETERMINES WHAT IS PRINTED:
    // EITHER timetable is printed for frontend use OR timetable is printed for debugging use
    // 0 = debug
    // 1 = frontend use
    if (preset == 0) {

        std::cout << "Timetable option: " << std::endl;

        for (std::pair<Date, SelectedCourseSection> element : timetable.all_classes()) {
            auto day = element.first.first;
            auto time = element.first.second;
            auto course = element.second.course_code;
            auto section_chosen = element.second.section;
            auto type = element.second.type;
            auto semester = element.second.semester;
            auto async = element.second.async;
            if(!async){
                std::cout << "  " << semester << ": " << course << " " << toClassType(type) << " section "
                        << (section_chosen + 1) << " on " << toDay(day) << " at " << toTime(time)
                        << std::endl;
            }else{
                std::cout << "  " << semester << ": " << course << " " << toClassType(type) << " section "
                        << (section_chosen + 1) << std::endl;
            }

        }
    }

    else if (preset == 1) {
        // format is course code, section number, type of offering

        std::string class_str;
        //int num_lines = 0;
        // timetable_str is the vector of strings containing one whole timetable option
        std::vector<std::string> timetable_str;
        for (std::pair<Date, SelectedCourseSection> element : timetable.all_classes()) {
            auto course = element.second.course_code;
            auto section_chosen = element.second.section;
            auto type = element.second.type;
            auto semester = element.second.semester;
            auto day = element.first.first;
            auto time = element.first.second;
            auto async = element.second.async;

            class_str.push_back(semester);
            class_str.append("_");
            if(!async){
                if (time == 9) {
                    class_str.append("09");
                } else {
                    class_str.append(std::to_string(time));
                }
                class_str.append("_");
                if (day > 5) {
                    day -= 5;
                }
                class_str.append(std::to_string(day));
            }else{
                class_str.append("no_associated_time");
            }
            class_str.append("_");
            class_str.append(course);
            class_str.append("_");
            class_str.append((toClassType(type)));
            class_str.append("_");
            class_str.append(std::to_string(section_chosen + 1));
            timetable_str.push_back(class_str);
            class_str = "";
            //num_lines++;
        }

        // sort timetables_str
        std::sort(timetable_str.begin(), timetable_str.end());
        //cout << "NEW TIMETABLE" << endl;
        for (auto line: timetable_str) {
            cout << line << endl;
        }
        //cout << num_lines;
    }

}

string Scheduler::jsonify(TimeTable &timetable) {
    stringstream json;
    json << "[";
    bool first = true;
    for (std::pair<Date, SelectedCourseSection> element : timetable.all_classes()) {
        if (!first)
            json << ",";
        else
            first = false;
        json << "{";
        auto semester = element.second.semester;
        json << "\"semester\":\"" << semester << "\",";
        auto course = element.second.course_code;
        json << "\"course\":\"" << course << "\",";
        string type;
        switch(element.second.type) {
            case 1:
                type = "LEC";
                break;
            case 2:
                type = "TUT";
                break;
            case 3:
                type = "PRA";
                break;
            default:
                type = "_";
                break;
        }
        json << "\"type\":\"" << type << "\",";
        auto section = element.second.section;
        json << "\"section\":" << section + 1 << ",";
        if(element.second.async){
            int day = -1;
            json << "\"day\":" << day << ",";
            int time = -1;
            json << "\"time\":" << time << "";
        }else{
            auto day = element.first.first;
            json << "\"day\":" << day << ",";
            auto time = element.first.second;
            json << "\"time\":" << time << "";
        }

        json << "}";
    }
    json << "]";

    return json.str();
}


std::vector<std::string> Scheduler::make_timetable_str(TimeTable &timetable) {
    std::string class_str;

    // timetable_str is the vector of strings containing one whole timetable option
    std::vector<std::string> timetable_str;
    for (std::pair<Date, SelectedCourseSection> element : timetable.all_classes()) {
        auto course = element.second.course_code;
        auto section_chosen = element.second.section;
        auto type = element.second.type;
        auto semester = element.second.semester;

        class_str.push_back(semester);
        class_str.append(course);
        class_str.append(toClassType(type));
        class_str.append(std::to_string(section_chosen + 1));
        timetable_str.push_back(class_str);
        class_str = "";
    }

    // sort timetables_str
    std::sort(timetable_str.begin(), timetable_str.end());
    return timetable_str;
}

/*
 * Function to check if a timetable already exists before adding it to
 * timetables_
 */
bool Scheduler::unique_check(TimeTable &timetable) {
    // first get the timetable that was just generated
    std::vector<std::string> new_timetable_str = make_timetable_str(timetable);

    // timetables_str contains all timetables as vectors of strings
    if (timetables_str.size() == 0) {
        // no timetables exist, so the first added must be valid
        // add timetable
        timetables_str.push_back(new_timetable_str);
        return true;
    }

    // other time tables exist so let's check them for uniqueness
    // iterate through timetables_str to see if the one we are trying to add already exists
    for (auto timetable : timetables_str) {
        // check if timetable in our generated timetables is equivalent to the one we are trying to
        // add
        if (timetable == new_timetable_str) {
            // if it does exist, nothing needs to be done - don't add
            return false;
        }
    }
    // couldn't find matching timetable - so add it to timetables
    timetables_str.push_back(new_timetable_str);
    return true;
}
int  Scheduler::set_num_timetables(int num_timetables) {
    Scheduler::max_num_of_timetables_to_show = num_timetables;
    return Scheduler::max_num_of_timetables_to_show;
}
int  Scheduler::set_max_explore(int explore_timetables) {
    Scheduler::max_number_of_timetables_to_explore = explore_timetables;
    return Scheduler::max_number_of_timetables_to_explore;
}
// Default constructor
Scheduler::Scheduler() {}
