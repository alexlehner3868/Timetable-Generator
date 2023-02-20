#include <cstdio>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>

#include <clip/clip.h>

#include "constraints.hh"
#include "course_data.hh"
#include "course_offering.hh"
#include "scheduler.hh"
#include "section.hh"
#include "test.hh"
#include "timetable.hh"
#include "selections.hh"


using namespace std;

int exec(vector<string> courses, vector<string> constraints) {
    string result_string = "";
    //--- Data Procesing ----
    // 1. Parses csv to get classes
    // 2. Store csv in SQL database or something and related sql funcitons

    // to remove a class it should already be in offerings
    // remove_course(offerings, "ECE212H1");

    // STAGES
    // Stage 1: Get user input
    // TODO: when user presses schedule button, get their input
    // Stage 2: Parse input
    // TODO: function (url of option) -> unordered_ offerings
    // TODO: function (url of options) -> set of constraints
    //(will need to ensure times are given to constraint in military times and that times are valid)
    // eg: cannot have "constraint no_class after 1am"
    // eg: cannot have "constraint max back to back classes: 0 hours"
    // Stage 3: Preprocess courses
    // function: sorts all constraints in order of priority
    // Function (offerings, hard-stop time constraints) -> set of offerings not in forbidden times
    // -> TODO: add some behaviour if all of one course's offerings are deleted. (maybe output
    // something)
    // Stage 4: create schedulers
    // Schedule classes and evaluate timetables
    // TODO: add evaluator and cost tracking
    // Stage 5: parse timetables to give to front end
    // TODO: function (best timetables) -> url
    unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash> offerings;
    if (courses.empty())
        offerings = get_classes();
    else {
        CourseData data;
        for (auto &&code : courses) {
            optional<Semester> sem;
            switch (code.size()) {
                case 8: break;
                case 9: {
                    char c = *--code.end();
                    code.pop_back();
                    sem = char2sem(c);
                    if (!sem)
                        cout << "[warn]: ignoring semester: " << c << endl;
                    break;
                }
                default:
                    cout << "[error]: malformed course code: " << code << endl;
                    std::exit(1);
            }
            vector<Section> lec = data.add_course(code, 1);
            vector<Section> tut = data.add_course(code, 2);
            vector<Section> pra = data.add_course(code, 3);
            CourseOfferings course(code, code, lec, tut, pra);
            if (sem)
                course.semester(*std::move(sem));
            offerings.insert(course);
        }
    }
    ConstraintHandler constraint_handler;
    
    int constraint_type;
    int priority;
    int hours;
    vector<char> block_semesters;
    vector<int> block_start_time;
    vector<int> block_day;
    while (constraints.size() > 0) {
        
        constraint_type = 10*int(constraints[0][0]-48) + int(constraints[0][1]-48);
        priority = int(constraints[0][2]-48);
        hours = 10*int(constraints[0][3]-48) + int(constraints[0][4]-48);
        //cout << "hours: " << hours << "constraint type: " << constraint_type << "priority" << priority << endl;
        if (priority == 1) {
            priority = 3;
        } else if (priority == 2) {
            priority = 6;
        } else if (priority == 3) {
            priority = 10;
        }
        if (constraint_type == 0 && priority > 0) {
            //all info passed is valid
            constraint_handler.set_prefer_morning_classes_constraint(priority);
        } else if (constraint_type == 1 && (priority > 0)) {
            constraint_handler.set_prefer_afternoon_classes_constraint(priority);
        } else if (constraint_type == 2 && priority > 0) {
            constraint_handler.set_prefer_evening_classes_constraint(priority);
        } else if (constraint_type == 3 && priority > 0) {
            constraint_handler.set_minimize_days_at_school_constraint(priority);
        } else if (constraint_type == 4 && priority > 0) {
            constraint_handler.set_prefer_async_classes_constraint(priority);
        } else if (constraint_type == 5 && priority > 0) {
            constraint_handler.set_prefer_sync_classes_constraint(priority);
        } else if (constraint_type == 6 && priority > 0) {
            constraint_handler.set_prefer_async_classes_constraint(priority);
        } else if (constraint_type == 7 && priority > 0) {
            constraint_handler.set_prefer_async_classes_constraint(priority);
        } else if (constraint_type == 8 && priority > 0) {
            constraint_handler.set_no_classes_before_X_constraint(hours, priority);
        } else if (constraint_type == 9 && priority > 0 && hours > 0) {
            constraint_handler.set_no_classes_after_X_constraint(hours, priority);
        } else if (constraint_type == 10 && priority > 0 && hours > 0) {
            constraint_handler.set_back_to_back_constraint(hours, priority);
        } else if (constraint_type == 11 && priority > 0 && hours > 0) {
            constraint_handler.set_no_breaks_larger_than_X_constraint(hours, priority);
        } else if (constraint_type == 12 && int(constraints[0][2]-48) > 0 && hours > 0) {
            //hardcode into fall semester for now
            //hardcode priority to must have
            if (int(constraints[0][2]-48) < 6) {
                //add_time_constraint(int start_time, int duration, int day, char semester, int priority);
                constraint_handler.add_time_constraint(hours, 1, int(constraints[0][2]-48), 'F', 10);
                block_semesters.insert(block_semesters.end(), 'F');
                block_day.insert(block_day.end(), int(constraints[0][2]-48));
                block_start_time.insert(block_start_time.end(), hours);
            } else {
                constraint_handler.add_time_constraint(hours, 1, int(constraints[0][2]-48), 'S', 10);
                block_semesters.insert(block_semesters.end(), 'S');
                block_day.insert(block_day.end(), int(constraints[0][2]-48));
                block_start_time.insert(block_start_time.end(), hours);
            }
        } else {
            //pass, bad
            
        }
        constraints.erase(constraints.begin());
    }
    //constraint_handler.add_time_constraint(10, 2, 2, 'F', MUST_HAVE); // tuesday at 10 am for 2 hours in the fall with
    //constraint_handler.set_no_classes_before_X_constraint(13, GOOD_TO_HAVE);
    Scheduler scheduler_handler;
    if (!constraint_handler.prune_semesters(offerings) /*&& !scheduler_handler.allow_incomplete*/) {
        result_string += "Timetable not created due to course specified in semester, but not offered. ";
        //return 1; // TODO: change me
    }
    if (!constraint_handler.preprocess_high_priority_classes_out(offerings, result_string)) {
        //return 1; // TODO: change me
    }
    vector<TimeTable> best_timetables = scheduler_handler.schedule_classes(offerings, &constraint_handler);

    result_string += scheduler_handler.get_result_string(); // need to return this to the front end too

    // for each timetable, add the time constraints
    vector<TimeTable> best_timetables_post_constraints;
    int index = 0;
    for (auto in_timetable:best_timetables) {
        
        for (auto sem:block_semesters) {
            char semester = sem;
            int day = block_day[index];
            int start_time = block_start_time[index];
            index++;
            SelectedCourseSection class_chosen{
                .course_code = "BLOCKED",
                .type = 4, // UNKNOWN
                .section = 0,
                .semester = semester, // Each section should only be in either F or W
                                                    // (need support for full year courses)
                                                    // semester can be a char instead of a vector
                                                    // F - FALL W - WINTER Y - BOTH [WONT SAY Y ANYM]
                .async = false
            };
            Date period = make_pair(day+1, start_time);
            in_timetable.insert(std::make_pair(period, class_chosen));
        }
        index = 0;
        best_timetables_post_constraints.insert(best_timetables_post_constraints.end(),in_timetable);
    }

    scheduler_handler.print_timetables(best_timetables_post_constraints);

    // -- User input (later)
    // 1. Search and add classes to timetable
    // 2. Remove classes
    // 3. Add constraints
    /*
        string input;
        while(1){
            cout<<"command: ";
            cin>>input;
            if(input == "add"){
                string courseid;
                cin >> courseid;
                course_data.find_course_times(courseid);
            }else if(input == "quit"){
                return;
            }else if(input == "schedule"){

            }else if(input == "remove"){

            }
        }
        */
    // -- Scheduling Algo
    // 1. Loop through all options and see what works
    // 2. Evaluate all possible options based on constraints
    // 3. What happens if no solution

    // -- GUI
    // -- Web stuff

    // -- Testing Code
    // test_sample_questions();
    return 0;
}

int main(int argc, char *argv[]) {
    // Create parser
    clip::Parser parser(
        argc,
        argv,
        clip::App("algo")
            .about("ECE496 scheduler algorithm.")
            .version("0.1.0")
    );
    // Add parser options
    parser.add(
        clip::Opt<string>("courses")
            .shortname('c')
            .help("Comma separated list of courses.")
        );
    parser.add(
        clip::Opt<string>("constraints")
            .shortname('x')
            .help("Comma separated list of constraints.")
        );
    // Parse args
    parser.parse();

    // Retrieve string of courses from input
    const auto &course_str = parser.getOpt<string>("courses").value();
    const auto &constraint_str = parser.getOpt<string>("constraints").value();
    // Split courses into a vector
    size_t start;
    const char delim = ',';
    vector<string> courses, constraints;
    size_t end = 0;
    while ((start = course_str.find_first_not_of(delim, end)) != std::string::npos) {
        end = course_str.find(delim, start);
        courses.push_back(course_str.substr(start, end - start));
    }
    end = 0;
    while ((start = constraint_str.find_first_not_of(delim, end)) != std::string::npos) {
        end = constraint_str.find(delim, start);
        constraints.push_back(constraint_str.substr(start, end - start));
    }

    // Execute the algorithm
    return exec(courses, constraints);
}
