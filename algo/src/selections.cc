#include "selections.hh"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "timetable.hh"

using namespace std;

void Selections::add_class(string course_id, int semester) {
    // check if course id is valid?

    // check if vectors are full (max 6 classes per term)
    if (semester == 0) {
        if (fall_courses.size() > 5) {
            cout << "You already have six courses in the fall!" << endl;
            return;
        } else {
            // try to add to fall semester
            fall_courses.push_back(course_id);
        }
    } else if (semester == 1) {
        if (winter_courses.size() > 5) {
            cout << "You already have six courses in the winter!" << endl;
            return;
        } else {
            // try to add to winter semester
            winter_courses.push_back(course_id);
        }
    } else {
        cout << "Invalid semester!" << endl;
        return;
    }


}
void Selections::remove_class(string course_id) {

    if ( std::find(fall_courses.begin(), fall_courses.end(), course_id) != fall_courses.end() ) {
        cout << "Found course in winter semester" << endl;
        auto itr = std::find(fall_courses.begin(), fall_courses.end(), course_id);
        fall_courses.erase(itr);
        return;
    } else if ( std::find(winter_courses.begin(), winter_courses.end(), course_id) != winter_courses.end() ) {
        cout << "Found course in winter semester" << endl;\
        auto itr = std::find(winter_courses.begin(), winter_courses.end(), course_id);
        winter_courses.erase(itr);
        return;
    } else {
        cout << "Couldn't find class." << endl;
        return;
    }
}

void Selections::run_scheduler() {
    for (int i = 0; i < (int) fall_courses.size(); i++) {
        //add_class();
    }
    if (fall_courses.size() != 6 || winter_courses.size() != 5) {
        return;
    }

    CourseData course_data;
    unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash> offerings;
    std::vector<Section> empty_vec;
    // add lectures
    std::vector<Section> course_one_lecture_sections = course_data.add_course(fall_courses[0], 1);
    std::vector<Section> course_two_lecture_sections = course_data.add_course(fall_courses[1], 1);
    std::vector<Section> course_three_lecture_sections = course_data.add_course(fall_courses[2], 1);
    std::vector<Section> course_four_lecture_sections = course_data.add_course(fall_courses[3], 1);
    std::vector<Section> course_five_lecture_sections = course_data.add_course(fall_courses[4], 1);
    std::vector<Section> course_six_lecture_sections = course_data.add_course(fall_courses[5], 1);

    // add tutorials
    std::vector<Section> course_one_tutorial_sections = course_data.add_course(fall_courses[0], 2);
    std::vector<Section> course_two_tutorial_sections = course_data.add_course(fall_courses[1], 2);
    std::vector<Section> course_three_tutorial_sections = course_data.add_course(fall_courses[2], 2);
    std::vector<Section> course_four_tutorial_sections = course_data.add_course(fall_courses[3], 2);
    std::vector<Section> course_five_tutorial_sections = course_data.add_course(fall_courses[4], 2);
    std::vector<Section> course_six_tutorial_sections = course_data.add_course(fall_courses[5], 2);
    // add practicals
    std::vector<Section> course_one_practical_sections = course_data.add_course(fall_courses[0], 3);
    std::vector<Section> course_two_practical_sections = course_data.add_course(fall_courses[1], 3);
    std::vector<Section> course_three_practical_sections = course_data.add_course(fall_courses[2], 3);
    std::vector<Section> course_four_practical_sections = course_data.add_course(fall_courses[3], 3);
    std::vector<Section> course_five_practical_sections = course_data.add_course(fall_courses[4], 3);
    std::vector<Section> course_six_practical_sections = course_data.add_course(fall_courses[5], 3);

    CourseOfferings class_one("Course 1",
                              fall_courses[0],
                              course_one_lecture_sections,
                              course_one_tutorial_sections,
                              course_one_practical_sections);
    CourseOfferings class_two("Course 2",
                              fall_courses[1],
                              course_two_lecture_sections,
                              course_two_tutorial_sections,
                              course_two_practical_sections);
    CourseOfferings class_three("Course 3",
                                fall_courses[2],
                                course_three_lecture_sections,
                                course_three_tutorial_sections,
                                course_three_practical_sections);
    CourseOfferings class_four("Course 4",
                               fall_courses[3],
                               course_four_lecture_sections,
                               course_four_tutorial_sections,
                               course_four_practical_sections);
    CourseOfferings class_five("Course 4",
                               fall_courses[4],
                               course_five_lecture_sections,
                               course_five_tutorial_sections,
                               course_five_practical_sections);
    CourseOfferings class_six("Course 5",
                              fall_courses[5],
                              course_six_lecture_sections,
                              course_six_tutorial_sections,
                              course_six_practical_sections);

    offerings.insert(class_one);
    offerings.insert(class_two);
    offerings.insert(class_three);
    offerings.insert(class_four);
    offerings.insert(class_five);
    offerings.insert(class_six);


    std::vector<Section> course_seven_lecture_sections = course_data.add_course(winter_courses[0], 1);
    std::vector<Section> course_eight_lecture_sections = course_data.add_course(winter_courses[1], 1);
    std::vector<Section> course_nine_lecture_sections = course_data.add_course(winter_courses[2], 1);
    std::vector<Section> course_ten_lecture_sections = course_data.add_course(winter_courses[3], 1);
    std::vector<Section> course_eleven_lecture_sections = course_data.add_course(winter_courses[4], 1);

    // add tutorials
    std::vector<Section> course_seven_tutorial_sections = course_data.add_course(winter_courses[0], 2);
    std::vector<Section> course_eight_tutorial_sections = course_data.add_course(winter_courses[1], 2);
    std::vector<Section> course_nine_tutorial_sections = course_data.add_course(winter_courses[2], 2);
    std::vector<Section> course_ten_tutorial_sections = course_data.add_course(winter_courses[3], 2);
    std::vector<Section> course_eleven_tutorial_sections = course_data.add_course(winter_courses[4], 2);
    // add practicals
    std::vector<Section> course_seven_practical_sections = course_data.add_course(winter_courses[0], 3);
    std::vector<Section> course_eight_practical_sections = course_data.add_course(winter_courses[1], 3);
    std::vector<Section> course_nine_practical_sections = course_data.add_course(winter_courses[2], 3);
    std::vector<Section> course_ten_practical_sections = course_data.add_course(winter_courses[3], 3);
    std::vector<Section> course_eleven_practical_sections = course_data.add_course(winter_courses[4], 3);

    CourseOfferings class_seven("Course 7",
                              winter_courses[0],
                              course_seven_lecture_sections,
                              course_seven_tutorial_sections,
                              course_seven_practical_sections);
    CourseOfferings class_eight("Course 8",
                              winter_courses[1],
                              course_eight_lecture_sections,
                              course_eight_tutorial_sections,
                              course_eight_practical_sections);
    CourseOfferings class_nine("Course 9",
                                winter_courses[2],
                                course_nine_lecture_sections,
                                course_nine_tutorial_sections,
                                course_nine_practical_sections);
    CourseOfferings class_ten("Course 10",
                               winter_courses[3],
                               course_ten_lecture_sections,
                               course_ten_tutorial_sections,
                               course_ten_practical_sections);
    CourseOfferings class_eleven("Course 11",
                               winter_courses[4],
                               course_eleven_lecture_sections,
                               course_eleven_tutorial_sections,
                               course_eleven_practical_sections);


    offerings.insert(class_seven);
    offerings.insert(class_eight);
    offerings.insert(class_nine);
    offerings.insert(class_ten);
    offerings.insert(class_eleven);

    // official_constraints.preprocess_high_priority_classes_out(offerings);
    vector<TimeTable> best_timetables = official_scheduler.schedule_classes(offerings, &official_constraints);
    official_scheduler.print_timetables(best_timetables, "Timetables generated successfully");
    return;
}
