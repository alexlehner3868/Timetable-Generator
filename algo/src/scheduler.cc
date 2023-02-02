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


#include "constraints.hh"
#include "course_offering.hh"
#include "period.hh"
#include "print_functions.hh"
#include "scheduler.hh"

using namespace std;

/**
 * TODO: remove classes
 * TODO: add constraints
 * TODO: add support for async classes
 * TODO: add option to allow conflicts? -> uoft allows you to enroll even when you have 3 conflicts
 * at once
 * TODO: Add in constraints that force course to be in a certain semester.
 * TODO: If a course has a prereq also being schedule, make sure the pre req is first
 * TODO: set max courses per semester to 6
 */

vector<TimeTable> Scheduler::schedule_classes(
    unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash> &courses,
    ConstraintHandler* constraint_handler) {
    constraint_handler_ = constraint_handler;

    // create timetable
    TimeTable timetable;

    for(auto offering : courses){
        maximum_number_of_sections += offering.numCourses();
    }

    // run scheduling algorithm
    auto start = std::chrono::system_clock::now();
    schedule_classes_helper(courses, timetable);
    auto end = std::chrono::system_clock::now();

    // Convert pq to vector and return
    vector<TimeTable> best_time_tables;
    vector<int> timetable_costs;
    int num_tables = timetables_.size();
    for (int i = 0; i < num_tables; i++) {
        TimeTable t = timetables_.top();
        timetable_costs.push_back(t.cost());
        best_time_tables.push_back(t);
        timetables_.pop();
    }
    if (num_tables == 0) {
       result_string += "Could not generate any possible timetables";
    }

    if(output_stats){
        stats_collector_.set_scheduler_counts(partial_timetables_pruned_, full_timetable_pruned_, number_of_explored_timetables, max_number_of_timetables_to_explore, max_num_of_timetables_to_show, num_tables, unique_timetables_found_, std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());
        stats_collector_.track_constraints(constraint_handler, timetable_costs);
        stats_collector_.print_stats();
    }
    return best_time_tables;
}

string Scheduler::get_result_string() {
    return ""; // FIXME
}

void Scheduler::schedule_classes_helper(
    unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash> &courses,
    TimeTable &timetable) {

    if (number_of_explored_timetables > max_number_of_timetables_to_explore) {
        timetables_not_explored_++;
        return;
    }
    // All sections have been added
    if (courses.size() == 0) {
        number_of_explored_timetables++;

        int timetable_additional_cost = constraint_handler_->cost_of_timetable(timetable.classes());
        timetable.add_cost(timetable_additional_cost);
        if (timetable.size() == maximum_number_of_sections && unique_check(timetable)) { 
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
        }
    }

    // the current timetable is worse than the worst best cost. stop exploring it
    // TODO -> VERIFY that timetables_.top is showing the worst best cost
    if ((int) timetables_.size() > 0 && (int) timetables_.size() >= (int) max_num_of_timetables_to_show) {
        TimeTable t = timetables_.top();
        int cost = t.cost();
        if (timetable.cost() > cost) {
            partial_timetables_pruned_++;
            return;
        }
    }

    // Loop through all of the Course Offerings (ie the course and all its sections)
    for (auto course : courses) {
        // Attempt to add a section
        auto sem = attempt_to_add_section(timetable, LEC, course, courses);
        // Track which semester we put it in
        if (!course.semester_ && sem) {
            switch (*sem) {
                case Semester::Fall:
                    timetable.chose_fall++;
                    break;
                case Semester::Winter:
                    timetable.chose_winter++;
                    break;
            }
        }
    }
}

optional<Semester> Scheduler::attempt_to_add_section(
    TimeTable &timetable,
    int class_type,
    CourseOfferings course,
    unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash> &courses) {
    int num_sections = 0;
    optional<Semester> semester = nullopt;

    if (class_type == LEC) {
        num_sections = (int)course.numLecSections();
    } else if (class_type == TUT) {
        num_sections = (int)course.numTutSections();
    } else {
        num_sections = (int)course.numPraSections();
    }
    // cout << "there are " << num_sections << " sections of course" << course.course_id_ << endl;
    //  Loop through all of the possible lecture sections in the course
    vector<int> shuffled_sections;
    for (int i = 0; i < num_sections; i++) {
        shuffled_sections.push_back(i);
    }
    auto rng = std::default_random_engine{};
    shuffle(begin(shuffled_sections), end(shuffled_sections), rng);
    for (int section_indx : shuffled_sections) {
        // cout<<"Looking at section id "<<section_indx<<endl;
        Section section;
        if (class_type == LEC) {
            section = course.lecture_sections_.at(section_indx);
        } else if (class_type == TUT) {
            section = course.tutorial_sections_.at(section_indx);
        } else {
            section = course.practical_sections_.at(section_indx);
        }
        int class_in_section;
        // Create an object to represent the section that was chosen
        SelectedCourseSection class_chosen{
            .course_code = course.course_id_,
            .type = class_type, // Lecture
            .section = section.section_id_,
            .semester = section.semester_.at(0) // Each section should only be in either F or W
                                                // (need support for full year courses)
                                                // semester can be a char instead of a vector
                                                // F - FALL W - WINTER Y - BOTH [WONT SAY Y ANYM]

        };
        int semester_offset = (class_chosen.semester == 'F') ? 0 : 5;
        bool successfully_inserted;
        // Is this class an async class
        Date period;
        // Try adding all of the lecture sections for that section and class to the timetable
        for (class_in_section = 0; class_in_section < (int)section.duration_.size();
             class_in_section++) {
            class_chosen.async = section.async_.at(class_in_section);
            int section_cost = 0;
            // Add a entry for every hour that the lecure has
            for (int i = 0; i < section.duration_.at(class_in_section); i++) {
                // If the class is in the winter offset the day by 5 ([1,5] = fall, [6,10] = winter)
                
                period = make_pair(section.day_.at(class_in_section) + semester_offset,
                                   section.start_time_.at(class_in_section) + i);

                // Insert into the timetable
                if(class_chosen.async){
                    // Insert an async class into timetable
                    successfully_inserted = timetable.insert_async(class_chosen);
                }else{
                    // Insert a non-async class into timetable
                    successfully_inserted = timetable.insert(std::make_pair(period, class_chosen));
                }


                // Check if the class was sucessfully inserted
                if (!successfully_inserted) {
                    break;
                    // Combination is invalid
                    // Time occupied by another course offering or constraint
                } else {
                    // Keep track of which semester we chose
                    semester = make_optional((class_chosen.semester == 'F') ? Semester::Fall : Semester::Winter);
                    if(!class_chosen.async){
                        section_cost += constraint_handler_->cost_of_class(period);
                    }
                    section_cost  += constraint_handler_ ->sync_vs_async_cost(class_chosen.async);

                }
            }

            // There is a conflict with the class section that was just inputted so remove it
            // Don't remove the class that it conflicted with - simply remove the others
            if (!successfully_inserted ) {
                // loop through each class in the section
                for (int remove_class = 0; remove_class <= class_in_section; remove_class++) {
                    // loop through each hour of the class (ex. if one is a two hour class this will
                    // run twice)
                    for (int i = 0; i < section.duration_.at(remove_class); i++) {
                        Date remove_period = make_pair(section.day_.at(remove_class) + semester_offset,
                                                       section.start_time_.at(remove_class) + i);

                        if (remove_period != period) {
                            timetable.erase(remove_period);
                        }
                    }
                }

                break;
            } else {
                timetable.add_cost(section_cost);
            }
        }

        // cout << "start" << endl;
        /**
         * Call this function recursively to place the remaining classes
         * Remove the current class from the courses list and then recall this function to place the
         * rest of the classes
         */
        if (class_type == LEC) {
            // add TUT now
            attempt_to_add_section(timetable, TUT, course, courses);
            // remove class from timetable
            for (int remove_class = 0; remove_class < class_in_section;
                 remove_class++) { // should this be < or <= (<= seg faults)
                for (int i = 0; i < section.duration_.at(remove_class); i++) {
                    Date period = make_pair(section.day_.at(remove_class) + semester_offset,
                                            section.start_time_.at(remove_class) + i);
                    timetable.erase(period);
                }
            }
        } else if (class_type == TUT) {
            // cout << "type tut and about to call PRA" << endl;
            attempt_to_add_section(timetable, PRA, course, courses);
            for (int remove_class = 0; remove_class < class_in_section;
                 remove_class++) { // should this be < or <= (<= seg faults)
                for (int i = 0; i < section.duration_.at(remove_class); i++) {
                    Date period = make_pair(section.day_.at(remove_class)+semester_offset,
                                            section.start_time_.at(remove_class) + i);
                    timetable.erase(period);
                }
            }
        } else {
            // cout << "type PRA and removing course" << endl;
            // print_timetable(timetable);
            unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash>
                remaining_classes = courses;
            remaining_classes.erase(course);
            // cout << " (section exists) is courses empty?: " << remaining_classes.empty() << endl;
            schedule_classes_helper(remaining_classes, timetable);

            // remove class from timetable
            for (int remove_class = 0; remove_class < class_in_section;
                 remove_class++) { // should this be < or <= (<= seg faults)
                for (int i = 0; i < section.duration_.at(remove_class); i++) {
                    Date period = make_pair(section.day_.at(remove_class)+semester_offset,
                                            section.start_time_.at(remove_class) + i);
                    timetable.erase(period);
                }
            }
        }
    }

    if (num_sections < 1) {
        // if section is empty DO SOMETHING
        // cout << "there are no sections for class "<< course.course_id_ << " and of type " <<
        // class_type << endl;
        if (class_type == LEC) {
            // add TUT now
            attempt_to_add_section(timetable, TUT, course, courses);
            // remove class from timetable
        } else if (class_type == TUT) {
            attempt_to_add_section(timetable, PRA, course, courses);
        } else {
            // cout << "type PRA and removing course" << endl;
            // print_timetable(timetable);
            unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash>
                remaining_classes = courses;
            remaining_classes.erase(course);

            // cout << "(section doesn't exist) is courses empty?: " << remaining_classes.empty() <<
            // endl; cout << "erasing course: " << course.course_id_ << endl;
            schedule_classes_helper(remaining_classes, timetable);
        }
    }

    return semester;
}

void Scheduler::print_timetables(vector<TimeTable> timetables) {
    int counter = timetables.size();
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
    cout << "]";
}

void Scheduler::print_timetable(TimeTable &timetable, int preset) {
    //PRESET DETERMINES WHAT IS PRINTED:
    // EITHER timetable is printed for frontend use OR timetable is printed for debugging use
    // 0 = debug
    // 1 = frontend use
    if (preset == 0) {

        std::cout << "Timetable option: " << std::endl;

        for (std::pair<Date, SelectedCourseSection> element : timetable.classes()) {
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
        for (std::pair<Date, SelectedCourseSection> element : timetable.classes()) {
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
    for (std::pair<Date, SelectedCourseSection> element : timetable.classes()) {
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
                type = "UNK";
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
    for (std::pair<Date, SelectedCourseSection> element : timetable.classes()) {
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

// Default constructor
Scheduler::Scheduler() {}
