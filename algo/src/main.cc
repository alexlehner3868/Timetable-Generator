#include <cstdio>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "constraints.hh"
#include "course_data.hh"
#include "course_offering.hh"
#include "scheduler.hh"
#include "section.hh"
#include "test.hh"
#include "timetable.hh"

using namespace std;

int test() {
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
    unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash> offerings = get_classes();
    ConstraintHandler constraint_handler;
    constraint_handler.add_time_constraint(10, 2, 2, 'F', MUST_HAVE); // tuesday at 10 am for 2 hours in the fall with 
    //constraint_handler.set_no_classes_before_X_constraint(13, GOOD_TO_HAVE);
    constraint_handler.preprocess_high_priority_classes_out(offerings);
    Scheduler scheduler_handler;
    vector<TimeTable> best_timetables = scheduler_handler.schedule_classes(offerings, constraint_handler);
    //scheduler_handler.print_timetables(best_timetables);

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

int query(int argc, char *argv[]) {
    // NOTE: This is the query function used by the backend.

    //--- Data Procesing ----
    // 1. Parses csv to get classes
    // 2. Store csv in SQL database or something and related sql funcitons
    CourseData course_data;

    std::vector<Section> empty_vec;
    // add lectures
    std::vector<Section> course_one_lecture_sections = course_data.add_course("ECE241H1", 1);
    std::vector<Section> course_two_lecture_sections = course_data.add_course("ECE244H1", 1);
    std::vector<Section> course_three_lecture_sections = course_data.add_course("ECE201H1", 1);
    std::vector<Section> course_four_lecture_sections = course_data.add_course("ECE212H1", 1);
    std::vector<Section> course_five_lecture_sections = course_data.add_course("MAT290H1", 1);
    std::vector<Section> course_six_lecture_sections = course_data.add_course("MAT291H1", 1);

    // add tutorials
    std::vector<Section> course_one_tutorial_sections = course_data.add_course("ECE241H1", 2);
    std::vector<Section> course_two_tutorial_sections = course_data.add_course("ECE244H1", 2);
    std::vector<Section> course_three_tutorial_sections = course_data.add_course("ECE201H1", 2);
    std::vector<Section> course_four_tutorial_sections = course_data.add_course("ECE212H1", 2);
    std::vector<Section> course_five_tutorial_sections = course_data.add_course("MAT290H1", 2);
    std::vector<Section> course_six_tutorial_sections = course_data.add_course("MAT291H1", 2);
    // add practicals
    std::vector<Section> course_one_practical_sections = course_data.add_course("ECE241H1", 3);
    std::vector<Section> course_two_practical_sections = course_data.add_course("ECE244H1", 3);
    std::vector<Section> course_three_practical_sections = course_data.add_course("ECE201H1", 3);
    std::vector<Section> course_four_practical_sections = course_data.add_course("ECE212H1", 3);
    std::vector<Section> course_five_practical_sections = course_data.add_course("MAT290H1", 3);
    std::vector<Section> course_six_practical_sections = course_data.add_course("MAT291H1", 3);

    CourseOfferings class_one("Digital Systems",
                              "ECE241H1",
                              course_one_lecture_sections,
                              course_one_tutorial_sections,
                              course_one_practical_sections);
    CourseOfferings class_two("Programming Fundamentals",
                              "ECE244H1",
                              course_two_lecture_sections,
                              course_two_tutorial_sections,
                              course_two_practical_sections);
    CourseOfferings class_three("Seminar Course",
                                "ECE201H1",
                                course_three_lecture_sections,
                                course_three_tutorial_sections,
                                course_three_practical_sections);
    CourseOfferings class_four("Circuit Analysis",
                               "ECE212H1",
                               course_four_lecture_sections,
                               course_four_tutorial_sections,
                               course_four_practical_sections);
    CourseOfferings class_five("Advanced Engineering Mathematics",
                               "MAT290H1",
                               course_five_lecture_sections,
                               course_five_tutorial_sections,
                               course_five_practical_sections);
    CourseOfferings class_six("Calculus III",
                              "MAT291H1",
                              course_six_lecture_sections,
                              course_six_tutorial_sections,
                              course_six_practical_sections);

    unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash> offerings;
    offerings.insert(class_one);
    offerings.insert(class_two);
    offerings.insert(class_three);
    offerings.insert(class_four);
    offerings.insert(class_five);
    offerings.insert(class_six);

    ConstraintHandler constraint_handler;
    Scheduler scheduler_handler;
    vector<TimeTable> best_timetables = scheduler_handler.schedule_classes(offerings,
                                                                           constraint_handler);
    stringstream json;
    bool first = true;
    json << "[";
    for (auto timetable : best_timetables) {
        if (!first)
            json << ",";
        else
            first = false;
        json << scheduler_handler.jsonify(timetable);
    }
    json << "]";
    std::cout << json.str() << std::endl;

    return 0;
}

int main(int argc, char *argv[]) {
    // Parse args
    test();
    /*
    switch (argc) {
        case 1:
            return test();
            break;
        case 2:
            if (!std::string(argv[1]).compare("test"))
                return test();
            else if (!std::string(argv[1]).compare("query"))
                return query(argc - 2, argv + 2);
        default:
            printf("Usage: %s [query|test]\n", argv[0]);
    }
    */
}
