#include <cstdio>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <set>
#include <clip/clip.h>
#include <chrono>

#include "constraints.hh"
#include "course_data.hh"
#include "course_offering.hh"
#include "scheduler.hh"
#include "section.hh"
#include "test.hh"
#include "timetable.hh"
#include "selections.hh"


using namespace std;

/* TO BE DELETED
TimeTable combineTimeTables (TimeTable & t1, TimeTable &t2){
    TimeTable merged_timetable = t1;

    // Insert synch classes 
    for (auto c : t2.classes()){
       merged_timetable.insert(c);
    }
    for(auto async_class : t2.async_classes()){
        merged_timetable.insert_async(async_class);
    }
    return merged_timetable;
}

pair<priority_queue<CourseOfferings, vector<CourseOfferings>, greater<CourseOfferings>>, priority_queue<CourseOfferings, vector<CourseOfferings>, greater<CourseOfferings>>> split_into_semesters(priority_queue<CourseOfferings, vector<CourseOfferings>, greater<CourseOfferings>>& offerings){
   priority_queue<CourseOfferings, vector<CourseOfferings>, greater<CourseOfferings>> fall_classes;
   priority_queue<CourseOfferings, vector<CourseOfferings>, greater<CourseOfferings>> winter_classes;

    for(auto offering : offerings){
        pair<int, int> sem_count =  offering.sec_per_sem(); 
        if(sem_count.first > sem_count.second){
            offering.semester(Semester::Fall);
            fall_classes.insert(offering);
        }else if(sem_count.first < sem_count.second){
            offering.semester(Semester::Winter);
            winter_classes.insert(offering);
        }else{
            if(fall_classes.size() < winter_classes.size()){
                offering.semester(Semester::Fall);
                fall_classes.insert(offering);
            }else{
                offering.semester(Semester::Winter);
                winter_classes.insert(offering);
            }
        }
    }
    return {fall_classes, winter_classes};
}
*/
/*
priority_queue<CourseOfferings, vector<CourseOfferings>, greater<CourseOfferings>> reorder_offerings(priority_queue<CourseOfferings, vector<CourseOfferings>, greater<CourseOfferings>> &original_offerings){
    priority_queue<pair<int, int>, vector<pair<int,int>>, less<pair<int,int>>> pq; 
    priority_queue<CourseOfferings, vector<CourseOfferings>, greater<CourseOfferings>> ordered_set;
    vector<CourseOfferings> vector_of_offerings(original_offerings.begin(), original_offerings.end());
    priority_queue<CourseOfferings, vector<CourseOfferings>, greater<CourseOfferings>> pq2; 
    int num_off = vector_of_offerings.size();
    for(int i = 0 ; i < num_off; i++){
        pq.push({vector_of_offerings[i].min_sections_, i});
        pq2.push(vector_of_offerings[i]);
    }
    while(!pq.empty()){
        ordered_set.insert(vector_of_offerings[pq.top().second]);
        pq.pop();
    }
    while(!pq2.empty()){
        cout<<pq2.top().course_id_<<" "<<pq2.top().min_sections_<<endl;
        pq2.pop();
    }

    return ordered_set;
}
*/

 


int exec(vector<string> courses, vector<string> constraints, int num_timetables) {
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
    priority_queue<CourseOfferings, vector<CourseOfferings>, greater<CourseOfferings>> offerings;
    if (courses.empty()){
        offerings = get_classes();
        //cout<<"ALEX IN MAIN "<<offerings.top().lecture_sections_.size()<<endl;
   } else {
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
            offerings.push(course);
        }
    }

    ConstraintHandler constraint_handler;
    
    int constraint_type;
    int priority;
    int hours;
    vector<char> block_semesters;
    vector<int> block_start_time;
    vector<int> block_day;

    int index = 0;

    

    for (auto constraint: constraints) {
        //cout << "constraint is " << constraint << endl;
        //cout << "day is " << int(constraint[2])-48 << endl;
        constraint_type = 10*int(constraint[0])-480 + int(constraint[1])-48;
        priority = int(constraint[2])-48;
        hours = 10*int(constraint[3])-480 + int(constraint[4])-48;
        //cout << "constraint type is " << constraint_type << endl;
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
            constraint_handler.set_no_morning_classes_constraint(priority);
        } else if (constraint_type == 1 && (priority > 0)) {
            constraint_handler.set_no_afternoon_classes_constraint(priority);
        } else if (constraint_type == 2 && priority > 0) {
            constraint_handler.set_no_evening_classes_constraint(priority);
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
        } else if (constraint_type == 12 && priority > 0 && hours > 0) {
            constraint_handler.set_no_more_than_X_hours_per_day_constraint(hours, priority);
        } else if (constraint_type == 13 && hours > 0) {
            //since the constraint type is 13, days is always one char and time is two chars, use "hours" for time 
            //when blocked off and "priority" for the day
            //hardcode priority to must have
            //cout << "Adding constraint on day " << int(constraint[2])-48 << endl;
            if (int(constraint[2])-48 < 5) {
                //add_time_constraint(int start_time, int duration, int day, char semester, int priority);
                //cout << "adding time constraints" << endl;
                //cout << int(constraint[2])-48 << endl;
                constraint_handler.add_time_constraint(hours, 1, int(constraint[2])-48+1/*this is really the day*/, 'F', 10);
                block_semesters.insert(block_semesters.end(), 'F');
                block_day.insert(block_day.end(), int(constraint[2])-48);
                block_start_time.insert(block_start_time.end(), hours);
            } else {
                constraint_handler.add_time_constraint(hours, 1, int(constraint[2])-48+1-5, 'S', 10);
                block_semesters.insert(block_semesters.end(), 'S');
                block_day.insert(block_day.end(), int(constraint[2])-48);
                block_start_time.insert(block_start_time.end(), hours);
            }
        } else {
            //pass, bad
        }
    }
    //constraint_handler.add_time_constraint(10, 2, 2, 'F', MUST_HAVE); // tuesday at 10 am for 2 hours in the fall with
    //constraint_handler.set_no_classes_before_X_constraint(13, GOOD_TO_HAVE);
    Scheduler scheduler_handler;
    scheduler_handler.set_num_timetables(num_timetables);
    switch(courses.size()) {
        case 1: scheduler_handler.set_max_explore(1000); break;
        case 2: scheduler_handler.set_max_explore(800); break;
        case 3: scheduler_handler.set_max_explore(500); break;
        case 4: scheduler_handler.set_max_explore(500); break;
        case 5: scheduler_handler.set_max_explore(500); break;
        case 6: scheduler_handler.set_max_explore(500); break;
        case 7: scheduler_handler.set_max_explore(500); break;
        case 8: scheduler_handler.set_max_explore(100); break;
        case 9: scheduler_handler.set_max_explore(100); break;
        case 10: scheduler_handler.set_max_explore(100); break;
        case 11: scheduler_handler.set_max_explore(350); break;
        case 12: scheduler_handler.set_max_explore(400); break;
        case 13: scheduler_handler.set_max_explore(400); break;
        case 14: scheduler_handler.set_max_explore(400); break;
        default: scheduler_handler.set_max_explore(100); break;
    }
    
    if(constraint_handler.blocked_off_time_exists()){
        constraint_handler.preprocess_high_priority_classes_out(offerings, result_string);
    }

    // Reorder the offerings based on number of things that need to be scheduled 
    //offerings = reorder_offerings(offerings);
    
        /*cout<<"ALEX IN MAIN "<<offerings.top().lecture_sections_.size()<<endl;
        for (auto section:offerings.top().lecture_sections_ ) {
            cout << section.semester_[1] << endl;
            cout << section.day_[1] << endl;
            cout << section.start_time_[1] << endl;
            cout << section.duration_[1] << endl;
            cout << section.section_id_[1] << endl;
            cout << endl;
        }*/
    vector<TimeTable> best_timetables  = scheduler_handler.schedule_classes(offerings, &constraint_handler);
    result_string += scheduler_handler.get_result_string(); 

    if(result_string.empty()){
        result_string = "Timetables generated successfully";
    }   
    

    vector<TimeTable> best_timetables_post_constraints;
    index = 0;
    for (auto in_timetable: best_timetables) {
        
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
        best_timetables_post_constraints.push_back(in_timetable);

    }
    scheduler_handler.print_timetables(best_timetables_post_constraints, result_string);

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
    parser.add(
        clip::Opt<string>("numtimetables")
            .shortname('n')
            .help("How many timetables to display.")
        );
    // Parse args
    parser.parse();

    // Retrieve string of courses from input
    const auto &course_str = parser.getOpt<string>("courses").value();
    const auto &constraint_str = parser.getOpt<string>("constraints").value();
    const auto &num_timetables_str = parser.getOpt<string>("numtimetables").value();
    // Split courses into a vector
    size_t start;
    const char delim = ',';
    vector<string> courses, constraints;
    int num_timetables;
    if (!num_timetables_str.empty()) {
        num_timetables = stoi(num_timetables_str);
    } else {
        num_timetables = 20;
    }
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
    std::sort(courses.begin(),courses.end());
    return exec(courses, constraints, num_timetables);
}
