#include <cstdio>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

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

int exec(vector<string> courses) {
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
    constraint_handler.add_time_constraint(10, 2, 2, 'F', MUST_HAVE); // tuesday at 10 am for 2 hours in the fall with
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
    scheduler_handler.print_timetables(best_timetables);

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
    // Parse args
    parser.parse();

    // Retrieve string of courses from input
    const auto &str = parser.getOpt<string>("courses").value();
    // Split courses into a vector
    size_t start;
    size_t end = 0;
    const char delim = ',';
    vector<string> courses;
    while ((start = str.find_first_not_of(delim, end)) != std::string::npos) {
        end = str.find(delim, start);
        courses.push_back(str.substr(start, end - start));
    }

    // Execute the algorithm
    return exec(courses);
}
