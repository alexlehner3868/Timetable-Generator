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

unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash> get_classes() {
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
    class_one.semester(Semester::Fall);
    CourseOfferings class_two("Programming Fundamentals",
                              "ECE244H1",
                              course_two_lecture_sections,
                              course_two_tutorial_sections,
                              course_two_practical_sections);
    class_two.semester(Semester::Fall);
    CourseOfferings class_three("Seminar Course",
                                "ECE201H1",
                                course_three_lecture_sections,
                                course_three_tutorial_sections,
                                course_three_practical_sections);
    class_three.semester(Semester::Fall);
    CourseOfferings class_four("Circuit Analysis",
                               "ECE212H1",
                               course_four_lecture_sections,
                               course_four_tutorial_sections,
                               course_four_practical_sections);
    class_four.semester(Semester::Fall);
    CourseOfferings class_five("Advanced Engineering Mathematics",
                               "MAT290H1",
                               course_five_lecture_sections,
                               course_five_tutorial_sections,
                               course_five_practical_sections);
    class_five.semester(Semester::Fall);
    CourseOfferings class_six("Calculus III",
                              "MAT291H1",
                              course_six_lecture_sections,
                              course_six_tutorial_sections,
                              course_six_practical_sections);
    class_six.semester(Semester::Fall);

    unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash> offerings;
    //offerings.insert(class_one);
    //offerings.insert(class_two);
    ///offerings.insert(class_three);
    //offerings.insert(class_four);
    //offerings.insert(class_five);
    //offerings.insert(class_six);


    std::vector<Section> course_seven_lecture_sections = course_data.add_course("ECE216H1", 1);
    std::vector<Section> course_eight_lecture_sections = course_data.add_course("ECE221H1", 1);
    std::vector<Section> course_nine_lecture_sections = course_data.add_course("ECE231H1", 1);
    std::vector<Section> course_ten_lecture_sections = course_data.add_course("ECE243H1", 1);
    std::vector<Section> course_eleven_lecture_sections = course_data.add_course("ECE297H1", 1);

    // add tutorials
    std::vector<Section> course_seven_tutorial_sections = course_data.add_course("ECE216H1", 2);
    std::vector<Section> course_eight_tutorial_sections = course_data.add_course("ECE221H1", 2);
    std::vector<Section> course_nine_tutorial_sections = course_data.add_course("ECE231H1", 2);
    std::vector<Section> course_ten_tutorial_sections = course_data.add_course("ECE243H1", 2);
    std::vector<Section> course_eleven_tutorial_sections = course_data.add_course("ECE297H1", 2);
    // add practicals
    std::vector<Section> course_seven_practical_sections = course_data.add_course("ECE216H1", 3);
    std::vector<Section> course_eight_practical_sections = course_data.add_course("ECE221H1", 3);
    std::vector<Section> course_nine_practical_sections = course_data.add_course("ECE231H1", 3);
    std::vector<Section> course_ten_practical_sections = course_data.add_course("ECE243H1", 3);
    std::vector<Section> course_eleven_practical_sections = course_data.add_course("ECE297H1", 3);

    CourseOfferings class_seven("Signals and Systems",
                              "ECE216H1",
                              course_seven_lecture_sections,
                              course_seven_tutorial_sections,
                              course_seven_practical_sections);
    class_seven.semester(Semester::Winter);
    CourseOfferings class_eight("Electric and Magnetic Fields",
                              "ECE221H1",
                              course_eight_lecture_sections,
                              course_eight_tutorial_sections,
                              course_eight_practical_sections);
    class_eight.semester(Semester::Winter);
    CourseOfferings class_nine("Introductory Electronics",
                                "ECE231H1",
                                course_nine_lecture_sections,
                                course_nine_tutorial_sections,
                                course_nine_practical_sections);
    class_nine.semester(Semester::Winter);
    CourseOfferings class_ten("Computer Organization",
                               "ECE243H1",
                               course_ten_lecture_sections,
                               course_ten_tutorial_sections,
                               course_ten_practical_sections);
    class_ten.semester(Semester::Winter);
    CourseOfferings class_eleven("Communication and Design",
                               "ECE297H1",
                               course_eleven_lecture_sections,
                               course_eleven_tutorial_sections,
                               course_eleven_practical_sections);
    class_eleven.semester(Semester::Winter);


    //offerings.insert(class_seven);
    offerings.insert(class_eight);
    offerings.insert(class_nine);
   // offerings.insert(class_ten);
    //offerings.insert(class_eleven);

    return offerings;
}

/*
void test_one_class_one_section(){
    vector<Section> calc_lecture_sections;
    vector<Section> empty_vec;
    vector<int> calc_durations;
    vector<int> calc_start_time;
    vector<int> calc_day;
    vector<char> calc_semester;
    vector<bool> calc_async;

    calc_durations.push_back(1);
    calc_start_time.push_back(9);
    calc_day.push_back(1);
    calc_semester.push_back('F');
    calc_async.push_back(false);

    Section calc_section_1(1, calc_durations, calc_start_time, calc_semester, calc_day, calc_async);
    calc_lecture_sections.push_back(calc_section_1);

    CourseOfferings calculus("Calculus 1", "MAT186", calc_lecture_sections, empty_vec, empty_vec);

    unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash> offerings;
    offerings.insert(calculus);
    Scheduler scheduler;
    scheduler.schedule_classes(offerings);
}

void test_one_class_multiple_sections(){
    vector<Section> calc_lecture_sections;
    vector<Section> empty_vec;
    vector<int> calc_durations;
    vector<int> calc_start_time;
    vector<int> calc_day;
    vector<char> calc_semester;
    vector<bool> calc_async;

    // -- Section 1
    // Monday 9 - 10
    // Wednesday 10 - 12
    // Thursday 1 - 2
    calc_durations.insert(calc_durations.end(), {1, 2, 1});
    calc_start_time.insert(calc_start_time.end(), {9, 10, 13});
    calc_day.insert(calc_day.end(), {1, 3, 4});
    calc_semester.insert(calc_semester.end(), {'F', 'F', 'F'});
    calc_async.insert(calc_async.end(), {false, false, false});

    Section calc_section_1(1, calc_durations, calc_start_time, calc_semester, calc_day, calc_async);
    calc_lecture_sections.push_back(calc_section_1);



    // -- Section 2
    // Tuesday 9 - 10
    // Wednesday 1 - 2
    // Friday 11 - 12
    calc_durations.clear();
    calc_start_time.clear();
    calc_day.clear();
    calc_semester.clear();
    calc_async.clear();
    calc_durations.insert(calc_durations.end(), {1, 1, 1});
    calc_start_time.insert(calc_start_time.end(), {9, 13, 11});
    calc_day.insert(calc_day.end(), {2, 3, 5});
    calc_semester.insert(calc_semester.end(), {'F', 'F', 'F'});
    calc_async.insert(calc_async.end(), {false, false, false});

    Section calc_section_2(2, calc_durations, calc_start_time, calc_semester, calc_day, calc_async);
    calc_lecture_sections.push_back(calc_section_2);


    // -- Section 3
    // Monday 3 - 5
    // Tuesday 9 - 10
    // Wednesday 11 - 12
    calc_durations.clear();
    calc_start_time.clear();
    calc_day.clear();
    calc_semester.clear();
    calc_async.clear();
    calc_durations.insert(calc_durations.end(), {2, 1, 1});
    calc_start_time.insert(calc_start_time.end(), {15, 9, 11});
    calc_day.insert(calc_day.end(), {1, 2, 3});
    calc_semester.insert(calc_semester.end(), {'F', 'F', 'F'});
    calc_async.insert(calc_async.end(), {false, false, false});

    Section calc_section_3(3, calc_durations, calc_start_time, calc_semester, calc_day, calc_async);
    calc_lecture_sections.push_back(calc_section_3);

    CourseOfferings calculus("Calculus 1", "MAT186", calc_lecture_sections, empty_vec, empty_vec);

    unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash> offerings;
    offerings.insert(calculus);
    Scheduler scheduler;
    scheduler.schedule_classes(offerings);
}

void test_two_classes_one_section() {
    vector<Section> calc_lecture_sections;
    vector<Section> linalg_lecture_sections;
    vector<Section> empty_vec;
    vector<int> class_durations;
    vector<int> class_start_time;
    vector<int> class_day;
    vector<char> class_semester;
    vector<bool> class_async;


    // Calculus
    // -- Section 1
    // Monday 9 - 10
    // Wednesday 10 - 12
    // Thursday 1 - 2
    class_durations.insert(class_durations.end(), { 1, 2, 1 });
    class_start_time.insert(class_start_time.end(), { 9, 10, 13 });
    class_day.insert(class_day.end(), { 1, 3, 4 });
    class_semester.insert(class_semester.end(), { 'F', 'F', 'F' });
    class_async.insert(class_async.end(), { false, false, false });

    Section calc_section_1(1, class_durations, class_start_time, class_semester, class_day,
class_async); calc_lecture_sections.push_back(calc_section_1);


    // Linear Algebra
    // -- Section 1
    // Tuesday 9 - 10
    // Wednesday 1 - 2
    // Friday 11 - 12
    class_durations.clear();
    class_start_time.clear();
    class_day.clear();
    class_semester.clear();
    class_async.clear();
    class_durations.insert(class_durations.end(), { 1, 1, 1 });
    class_start_time.insert(class_start_time.end(), { 9, 13, 11 });
    class_day.insert(class_day.end(), { 2, 3, 5 });
    class_semester.insert(class_semester.end(), { 'F', 'F', 'F' });
    class_async.insert(class_async.end(), { false, false, false });

    Section linalg_section_1(1, class_durations, class_start_time, class_semester, class_day,
class_async); linalg_lecture_sections.push_back(linalg_section_1);


    CourseOfferings calculus("Calculus 1", "MAT186", calc_lecture_sections, empty_vec, empty_vec);
    CourseOfferings linear_algebra("Linear Algebra", "MAT188", linalg_lecture_sections, empty_vec,
empty_vec);

    unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash> offerings;
    offerings.insert(calculus);
    offerings.insert(linear_algebra);
    Scheduler scheduler;
    scheduler.schedule_classes(offerings);
}

void test_two_classes_two_sections() {
    vector<Section> calc_lecture_sections;
    vector<Section> linalg_lecture_sections;
    vector<Section> empty_vec;
    vector<int> class_durations;
    vector<int> class_start_time;
    vector<int> class_day;
    vector<char> class_semester;
    vector<bool> class_async;


    // Calculus
    // -- Section 1
    // Monday 9 - 10
    // Wednesday 10 - 12
    // Thursday 1 - 2
    class_durations.insert(class_durations.end(), { 1, 2, 1 });
    class_start_time.insert(class_start_time.end(), { 9, 10, 13 });
    class_day.insert(class_day.end(), { 1, 3, 4 });
    class_semester.insert(class_semester.end(), { 'F', 'F', 'F' });
    class_async.insert(class_async.end(), { false, false, false });

    Section calc_section_1(1, class_durations, class_start_time, class_semester, class_day,
class_async); calc_lecture_sections.push_back(calc_section_1);


    // -- Section 2
    // Monday 10 - 11
    // Tuesday 10 - 11
    // Thursday 10 - 11
    class_durations.clear();
    class_start_time.clear();
    class_day.clear();
    class_semester.clear();
    class_async.clear();
    class_durations.insert(class_durations.end(), { 1, 1, 1 });
    class_start_time.insert(class_start_time.end(), { 10, 10, 10 });
    class_day.insert(class_day.end(), { 1, 2, 4 });
    class_semester.insert(class_semester.end(), { 'F', 'F', 'F' });
    class_async.insert(class_async.end(), { false, false, false });

    Section calc_section_2(2, class_durations, class_start_time, class_semester, class_day,
class_async); calc_lecture_sections.push_back(calc_section_2);

    // Linear Algebra
    // -- Section 1
    // Tuesday 9 - 10
    // Wednesday 1 - 2
    // Friday 11 - 12
    class_durations.clear();
    class_start_time.clear();
    class_day.clear();
    class_semester.clear();
    class_async.clear();
    class_durations.insert(class_durations.end(), { 1, 1, 1 });
    class_start_time.insert(class_start_time.end(), { 9, 13, 11 });
    class_day.insert(class_day.end(), { 2, 3, 5 });
    class_semester.insert(class_semester.end(), { 'F', 'F', 'F' });
    class_async.insert(class_async.end(), { false, false, false });

    Section linalg_section_1(1, class_durations, class_start_time, class_semester, class_day,
class_async); linalg_lecture_sections.push_back(linalg_section_1);

    Section linalg_section_2(2, class_durations, class_start_time, class_semester, class_day,
class_async); linalg_lecture_sections.push_back(linalg_section_2);

    CourseOfferings calculus("Calculus 1", "MAT186", calc_lecture_sections, empty_vec, empty_vec);
    CourseOfferings linear_algebra("Linear Algebra", "MAT188", linalg_lecture_sections, empty_vec,
empty_vec);

    unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash> offerings;
    offerings.insert(calculus);
    offerings.insert(linear_algebra);
    Scheduler scheduler;
    scheduler.schedule_classes(offerings);
}
// Test 5
void test_two_classes_multiple_sections() {
    vector<Section> calc_lecture_sections;
    vector<Section> linalg_lecture_sections;
    vector<Section> empty_vec;
    vector<int> class_durations;
    vector<int> class_start_time;
    vector<int> class_day;
    vector<char> class_semester;
    vector<bool> class_async;


    // Calculus
    // -- Section 1
    // Monday 9 - 10
    // Wednesday 10 - 12
    // Thursday 1 - 2
    class_durations.insert(class_durations.end(), { 1, 2, 1 });
    class_start_time.insert(class_start_time.end(), { 9, 10, 13 });
    class_day.insert(class_day.end(), { 1, 3, 4 });
    class_semester.insert(class_semester.end(), { 'F', 'F', 'F' });
    class_async.insert(class_async.end(), { false, false, false });

    Section calc_section_1(1, class_durations, class_start_time, class_semester, class_day,
class_async); calc_lecture_sections.push_back(calc_section_1);


    // -- Section 2
    // Monday 10 - 11
    // Tuesday 10 - 11
    // Thursday 10 - 11
    class_durations.clear();
    class_start_time.clear();
    class_day.clear();
    class_semester.clear();
    class_async.clear();
    class_durations.insert(class_durations.end(), { 1, 1, 1 });
    class_start_time.insert(class_start_time.end(), { 10, 10, 10 });
    class_day.insert(class_day.end(), { 1, 2, 4 });
    class_semester.insert(class_semester.end(), { 'F', 'F', 'F' });
    class_async.insert(class_async.end(), { false, false, false });

    Section calc_section_2(2, class_durations, class_start_time, class_semester, class_day,
class_async); calc_lecture_sections.push_back(calc_section_2);

    // Linear Algebra
    // -- Section 1
    // Tuesday 9 - 10
    // Wednesday 1 - 2
    // Friday 11 - 12
    class_durations.clear();
    class_start_time.clear();
    class_day.clear();
    class_semester.clear();
    class_async.clear();
    class_durations.insert(class_durations.end(), { 1, 1, 1 });
    class_start_time.insert(class_start_time.end(), { 9, 13, 11 });
    class_day.insert(class_day.end(), { 2, 3, 5 });
    class_semester.insert(class_semester.end(), { 'F', 'F', 'F' });
    class_async.insert(class_async.end(), { false, false, false });

    Section linalg_section_1(1, class_durations, class_start_time, class_semester, class_day,
class_async); linalg_lecture_sections.push_back(linalg_section_1);


    // -- Section 2
    // Tuesday 4 - 5
    // Wednesday 4 - 5
    // Friday 4 - 5
    class_durations.clear();
    class_start_time.clear();
    class_day.clear();
    class_semester.clear();
    class_async.clear();
    class_durations.insert(class_durations.end(), { 1, 1, 1 });
    class_start_time.insert(class_start_time.end(), { 16, 16, 16 });
    class_day.insert(class_day.end(), { 2, 3, 5 });
    class_semester.insert(class_semester.end(), { 'F', 'F', 'F' });
    class_async.insert(class_async.end(), { false, false, false });

    Section linalg_section_2(2, class_durations, class_start_time, class_semester, class_day,
class_async); linalg_lecture_sections.push_back(linalg_section_2);

    CourseOfferings calculus("Calculus 1", "MAT186", calc_lecture_sections, empty_vec, empty_vec);
    CourseOfferings linear_algebra("Linear Algebra", "MAT188", linalg_lecture_sections, empty_vec,
empty_vec);

    unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash> offerings;
    offerings.insert(calculus);
    offerings.insert(linear_algebra);
    Scheduler scheduler;
    scheduler.schedule_classes(offerings);
}
// Test 6
void test_three_classes_multiple_sections() {
    vector<Section> calc_lecture_sections;
    vector<Section> linalg_lecture_sections;
    vector<Section> mech_lecture_sections;
    vector<Section> empty_vec;
    vector<int> class_durations;
    vector<int> class_start_time;
    vector<int> class_day;
    vector<char> class_semester;
    vector<bool> class_async;


    // Calculus
    // -- Section 1
    // Monday 9 - 10
    // Wednesday 10 - 12
    // Thursday 1 - 2
    class_durations.insert(class_durations.end(), { 1, 2, 1 });
    class_start_time.insert(class_start_time.end(), { 9, 10, 13 });
    class_day.insert(class_day.end(), { 1, 3, 4 });
    class_semester.insert(class_semester.end(), { 'F', 'F', 'F' });
    class_async.insert(class_async.end(), { false, false, false });

    Section calc_section_1(1, class_durations, class_start_time, class_semester, class_day,
class_async); calc_lecture_sections.push_back(calc_section_1);


    // -- Section 2
    // Monday 10 - 11
    // Tuesday 10 - 11
    // Thursday 10 - 11
    class_durations.clear();
    class_start_time.clear();
    class_day.clear();
    class_semester.clear();
    class_async.clear();
    class_durations.insert(class_durations.end(), { 1, 1, 1 });
    class_start_time.insert(class_start_time.end(), { 10, 10, 10 });
    class_day.insert(class_day.end(), { 1, 2, 4 });
    class_semester.insert(class_semester.end(), { 'F', 'F', 'F' });
    class_async.insert(class_async.end(), { false, false, false });

    Section calc_section_2(2, class_durations, class_start_time, class_semester, class_day,
class_async); calc_lecture_sections.push_back(calc_section_2);

    // Linear Algebra
    // -- Section 1
    // Tuesday 9 - 10
    // Wednesday 1 - 2
    // Friday 11 - 12
    class_durations.clear();
    class_start_time.clear();
    class_day.clear();
    class_semester.clear();
    class_async.clear();
    class_durations.insert(class_durations.end(), { 1, 1, 1 });
    class_start_time.insert(class_start_time.end(), { 9, 13, 11 });
    class_day.insert(class_day.end(), { 2, 3, 5 });
    class_semester.insert(class_semester.end(), { 'F', 'F', 'F' });
    class_async.insert(class_async.end(), { false, false, false });

    Section linalg_section_1(1, class_durations, class_start_time, class_semester, class_day,
class_async); linalg_lecture_sections.push_back(linalg_section_1);

    // -- Section 2
    // Tuesday 4 - 5
    // Wednesday 4 - 5
    // Friday 4 - 5
    class_durations.clear();
    class_start_time.clear();
    class_day.clear();
    class_semester.clear();
    class_async.clear();
    class_durations.insert(class_durations.end(), { 1, 1, 1 });
    class_start_time.insert(class_start_time.end(), { 16, 16, 16 });
    class_day.insert(class_day.end(), { 2, 3, 5 });
    class_semester.insert(class_semester.end(), { 'F', 'F', 'F' });
    class_async.insert(class_async.end(), { false, false, false });

    Section linalg_section_2(2, class_durations, class_start_time, class_semester, class_day,
class_async); linalg_lecture_sections.push_back(linalg_section_2);

    // Mechanics
    // -- Section 1
    // Monday 3 - 6
    class_durations.clear();
    class_start_time.clear();
    class_day.clear();
    class_semester.clear();
    class_async.clear();
    class_durations.insert(class_durations.end(), { 3 });
    class_start_time.insert(class_start_time.end(), { 15 });
    class_day.insert(class_day.end(), { 1 });
    class_semester.insert(class_semester.end(), { 'F' });
    class_async.insert(class_async.end(), { false });

    Section mech_section_1(1, class_durations, class_start_time, class_semester, class_day,
class_async); mech_lecture_sections.push_back(mech_section_1);

    // -- Section 2
    // Friday 3 - 6
    class_durations.clear();
    class_start_time.clear();
    class_day.clear();
    class_semester.clear();
    class_async.clear();
    class_durations.insert(class_durations.end(), { 3 });
    class_start_time.insert(class_start_time.end(), { 13 });
    class_day.insert(class_day.end(), { 5 });
    class_semester.push_back({ 'F' });
    class_async.insert(class_async.end(), { false });


    Section mech_section_2(2, class_durations, class_start_time, class_semester, class_day,
class_async); mech_lecture_sections.push_back(mech_section_2);

    CourseOfferings calculus("Calculus 1", "MAT186", calc_lecture_sections, empty_vec, empty_vec);
    CourseOfferings linear_algebra("Linear Algebra", "MAT188", linalg_lecture_sections, empty_vec,
empty_vec); CourseOfferings mechanics("Mechanics", "CIV100", mech_lecture_sections, empty_vec,
empty_vec);

    unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash> offerings;
    offerings.insert(calculus);
    offerings.insert(linear_algebra);
    offerings.insert(mechanics);
    Scheduler scheduler;
    scheduler.schedule_classes(offerings);
}

// Test 7
void test_two_classes_conflict() {
    vector<Section> calc_lecture_sections;
    vector<Section> linalg_lecture_sections;
    vector<Section> empty_vec;
    vector<int> class_durations;
    vector<int> class_start_time;
    vector<int> class_day;
    vector<char> class_semester;
    vector<bool> class_async;


    // Calculus
    // -- Section 1
    // Tuesday 9 - 10
    // Wednesday 10 - 12
    // Thursday 1 - 2
    class_durations.insert(class_durations.end(), { 1, 2, 1 });
    class_start_time.insert(class_start_time.end(), { 9, 10, 13 });
    class_day.insert(class_day.end(), { 2, 3, 4 });
    class_semester.insert(class_semester.end(), { 'F', 'F', 'F' });
    class_async.insert(class_async.end(), { false, false, false });

    Section calc_section_1(1, class_durations, class_start_time, class_semester, class_day,
class_async); calc_lecture_sections.push_back(calc_section_1);


    // -- Section 2
    // Monday 10 - 11
    // Tuesday 10 - 11
    // Thursday 10 - 11
    class_durations.clear();
    class_start_time.clear();
    class_day.clear();
    class_semester.clear();
    class_async.clear();
    class_durations.insert(class_durations.end(), { 1, 1, 1 });
    class_start_time.insert(class_start_time.end(), { 10, 10, 10 });
    class_day.insert(class_day.end(), { 1, 2, 4 });
    class_semester.insert(class_semester.end(), { 'F', 'F', 'F' });
    class_async.insert(class_async.end(), { false, false, false });

    Section calc_section_2(2, class_durations, class_start_time, class_semester, class_day,
class_async); calc_lecture_sections.push_back(calc_section_2);

    // Linear Algebra
    // -- Section 1
    // Tuesday 9 - 10
    // Wednesday 1 - 2
    // Friday 11 - 12
    class_durations.clear();
    class_start_time.clear();
    class_day.clear();
    class_semester.clear();
    class_async.clear();
    class_durations.insert(class_durations.end(), { 1, 1, 1 });
    class_start_time.insert(class_start_time.end(), { 9, 13, 11 });
    class_day.insert(class_day.end(), { 2, 3, 5 });
    class_semester.insert(class_semester.end(), { 'F', 'F', 'F' });
    class_async.insert(class_async.end(), { false, false, false });

    Section linalg_section_1(1, class_durations, class_start_time, class_semester, class_day,
class_async); linalg_lecture_sections.push_back(linalg_section_1);


    // -- Section 2
    // Tuesday 4 - 5
    // Wednesday 4 - 5
    // Friday 4 - 5
    class_durations.clear();
    class_start_time.clear();
    class_day.clear();
    class_semester.clear();
    class_async.clear();
    class_durations.insert(class_durations.end(), { 1, 1, 1 });
    class_start_time.insert(class_start_time.end(), { 16, 16, 16 });
    class_day.insert(class_day.end(), { 2, 3, 5 });
    class_semester.insert(class_semester.end(), { 'F', 'F', 'F' });
    class_async.insert(class_async.end(), { false, false, false });

    Section linalg_section_2(2, class_durations, class_start_time, class_semester, class_day,
class_async); linalg_lecture_sections.push_back(linalg_section_2);

    CourseOfferings calculus("Calculus 1", "MAT186", calc_lecture_sections, empty_vec, empty_vec);
    CourseOfferings linear_algebra("Linear Algebra", "MAT188", linalg_lecture_sections, empty_vec,
empty_vec);

    unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash> offerings;
    offerings.insert(calculus);
    offerings.insert(linear_algebra);
    Scheduler scheduler;
    scheduler.schedule_classes(offerings);
}
*/
// Test 8
unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash> test_three_classes_conflict() {
    vector<Section> calc_lecture_sections;
    vector<Section> linalg_lecture_sections;
    vector<Section> mech_lecture_sections;
    vector<Section> empty_vec;
    vector<int> class_durations;
    vector<int> class_start_time;
    vector<int> class_day;
    vector<char> class_semester;
    vector<bool> class_async;


    // Calculus
    // -- Section 1
    // Monday 9 - 10
    // Wednesday 10 - 12
    // Thursday 1 - 2
    class_durations.insert(class_durations.end(), { 1, 2, 1 });
    class_start_time.insert(class_start_time.end(), { 9, 10, 13 });
    class_day.insert(class_day.end(), { 1, 3, 4 });
    class_semester.insert(class_semester.end(), { 'F', 'F', 'F' });
    class_async.insert(class_async.end(), { false, false, false });

    Section calc_section_1(1, class_durations, class_start_time, class_semester, class_day,
class_async); calc_lecture_sections.push_back(calc_section_1);


    // -- Section 2
    // Monday 10 - 11
    // Tuesday 10 - 11
    // Thursday 10 - 11
    class_durations.clear();
    class_start_time.clear();
    class_day.clear();
    class_semester.clear();
    class_async.clear();
    class_durations.insert(class_durations.end(), { 1, 1, 1 });
    class_start_time.insert(class_start_time.end(), { 10, 10, 10 });
    class_day.insert(class_day.end(), { 1, 2, 4 });
    class_semester.insert(class_semester.end(), { 'F', 'F', 'F' });
    class_async.insert(class_async.end(), { false, false, false });

    Section calc_section_2(2, class_durations, class_start_time, class_semester, class_day,
class_async); calc_lecture_sections.push_back(calc_section_2);

    // Linear Algebra
    // -- Section 1
    // Tuesday 9 - 10
    // Wednesday 1 - 2
    // Friday 11 - 12
    class_durations.clear();
    class_start_time.clear();
    class_day.clear();
    class_semester.clear();
    class_async.clear();
    class_durations.insert(class_durations.end(), { 1, 1, 1 });
    class_start_time.insert(class_start_time.end(), { 9, 13, 11 });
    class_day.insert(class_day.end(), { 2, 3, 5 });
    class_semester.insert(class_semester.end(), { 'F', 'F', 'F' });
    class_async.insert(class_async.end(), { false, false, false });

    Section linalg_section_1(1, class_durations, class_start_time, class_semester, class_day,
class_async); linalg_lecture_sections.push_back(linalg_section_1);

    // -- Section 2
    // Tuesday 4 - 5
    // Wednesday 4 - 5
    // Friday 4 - 5
    class_durations.clear();
    class_start_time.clear();
    class_day.clear();
    class_semester.clear();
    class_async.clear();
    class_durations.insert(class_durations.end(), { 1, 1, 1 });
    class_start_time.insert(class_start_time.end(), { 16, 16, 16 });
    class_day.insert(class_day.end(), { 2, 3, 5 });
    class_semester.insert(class_semester.end(), { 'F', 'F', 'F' });
    class_async.insert(class_async.end(), { false, false, false });

    Section linalg_section_2(2, class_durations, class_start_time, class_semester, class_day,
class_async); linalg_lecture_sections.push_back(linalg_section_2);

    // Mechanics
    // -- Section 1
    // Monday 3 - 6
    class_durations.clear();
    class_start_time.clear();
    class_day.clear();
    class_semester.clear();
    class_async.clear();
    class_durations.insert(class_durations.end(), { 3 });
    class_start_time.insert(class_start_time.end(), { 15 });
    class_day.insert(class_day.end(), { 1 });
    class_semester.insert(class_semester.end(), { 'F' });
    class_async.insert(class_async.end(), { false });

    Section mech_section_1(1, class_durations, class_start_time, class_semester, class_day,
class_async); mech_lecture_sections.push_back(mech_section_1);

    // -- Section 2
    // Friday 3 - 6
    class_durations.clear();
    class_start_time.clear();
    class_day.clear();
    class_semester.clear();
    class_async.clear();
    class_durations.insert(class_durations.end(), { 3 });
    class_start_time.insert(class_start_time.end(), { 15 });
    class_day.insert(class_day.end(), { 5 });
    class_semester.push_back({ 'F' });
    class_async.insert(class_async.end(), { false });


    Section mech_section_2(2, class_durations, class_start_time, class_semester, class_day,
class_async); mech_lecture_sections.push_back(mech_section_2);

    CourseOfferings calculus("Calculus 1", "MAT186", calc_lecture_sections, empty_vec, empty_vec);
    CourseOfferings linear_algebra("Linear Algebra", "MAT188", linalg_lecture_sections, empty_vec,
empty_vec); CourseOfferings mechanics("Mechanics", "CIV100", mech_lecture_sections, empty_vec,
empty_vec);

    unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash> offerings;
    offerings.insert(calculus);
    offerings.insert(linear_algebra);
    offerings.insert(mechanics);
    return offerings;
}


void test_sample_questions() {
    // One class, with one section
    cout<<"Test 1: One Class, One Section " << endl;
    //test_one_class_one_section();
    // One class with multiple sections
    cout<<"Test 2: One Class, Multiple Sections " << endl;
    //test_one_class_multiple_sections();
    // Two classes with one section each
    cout << "Test 3: Two Classes, One Section " << endl;
    //test_two_classes_one_section();
    // Two classes with two sections
    cout << "Test 4: Two Classes, Two Sections " << endl;
    //test_two_classes_two_sections();
    // Two classes with two sections each
    cout << "Test 5: Two Classes, Multiple Sections " << endl;
    //test_two_classes_multiple_sections();
    // Three classes with two sections each
    cout << "Test 6: Three Classes, Multiple Sections " << endl;
    //test_three_classes_multiple_sections();
    // Two classes with multiple sections and a conflict
    cout << "Test 7: Two Classes, Multiple Sections, Conflict " << endl;
    //test_two_classes_conflict();
    // Three classes with multiple sections and conflicts
    cout << "Test 8: Three Classes, Multiple Sections, Conflicts " << endl;
    //test_three_classes_conflict();
}

void remove_course(unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash>& offerings, string course_id) {
    // We need to find the element with the matching course code then remove it
    CourseData course_data;

    std::vector<Section> lec_sections = course_data.add_course(course_id, 1);
    std::vector<Section> tut_sections = course_data.add_course(course_id, 2);
    std::vector<Section> pra_sections = course_data.add_course(course_id, 3);


    CourseOfferings class_offering("Circuit Analysis", course_id, lec_sections, tut_sections,
pra_sections);

    auto search = offerings.find(class_offering);
    if (search == offerings.end()) {
        // course wasn't found, no need to remove it
        // could be an issue with course ids (H1 at the end)
        cout << "Is " << course_id << " the course id of the course you want to delete?" << endl;
    } else {
        // it was found in the unordered set
        offerings.erase(class_offering);
    }

}

void get_schedule() {
    cout << "aoooooo" << endl;
}
