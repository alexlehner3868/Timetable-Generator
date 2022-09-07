#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>

#include "constraints.hh"
#include "scheduler.hh"
#include "course_offering.hh"
#include "section.hh"
#include "course_data.hh"

using namespace std;

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

    Section calc_section_1(1, class_durations, class_start_time, class_semester, class_day, class_async);
    calc_lecture_sections.push_back(calc_section_1);


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

    Section linalg_section_1(1, class_durations, class_start_time, class_semester, class_day, class_async);
    linalg_lecture_sections.push_back(linalg_section_1);


    CourseOfferings calculus("Calculus 1", "MAT186", calc_lecture_sections, empty_vec, empty_vec);
    CourseOfferings linear_algebra("Linear Algebra", "MAT188", linalg_lecture_sections, empty_vec, empty_vec);

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

    Section calc_section_1(1, class_durations, class_start_time, class_semester, class_day, class_async);
    calc_lecture_sections.push_back(calc_section_1);


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

    Section calc_section_2(2, class_durations, class_start_time, class_semester, class_day, class_async);
    calc_lecture_sections.push_back(calc_section_2);

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

    Section linalg_section_1(1, class_durations, class_start_time, class_semester, class_day, class_async);
    linalg_lecture_sections.push_back(linalg_section_1);

    Section linalg_section_2(2, class_durations, class_start_time, class_semester, class_day, class_async);
    linalg_lecture_sections.push_back(linalg_section_2);

    CourseOfferings calculus("Calculus 1", "MAT186", calc_lecture_sections, empty_vec, empty_vec);
    CourseOfferings linear_algebra("Linear Algebra", "MAT188", linalg_lecture_sections, empty_vec, empty_vec);

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

    Section calc_section_1(1, class_durations, class_start_time, class_semester, class_day, class_async);
    calc_lecture_sections.push_back(calc_section_1);


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

    Section calc_section_2(2, class_durations, class_start_time, class_semester, class_day, class_async);
    calc_lecture_sections.push_back(calc_section_2);

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

    Section linalg_section_1(1, class_durations, class_start_time, class_semester, class_day, class_async);
    linalg_lecture_sections.push_back(linalg_section_1);

    
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

    Section linalg_section_2(2, class_durations, class_start_time, class_semester, class_day, class_async);
    linalg_lecture_sections.push_back(linalg_section_2);

    CourseOfferings calculus("Calculus 1", "MAT186", calc_lecture_sections, empty_vec, empty_vec);
    CourseOfferings linear_algebra("Linear Algebra", "MAT188", linalg_lecture_sections, empty_vec, empty_vec);

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

    Section calc_section_1(1, class_durations, class_start_time, class_semester, class_day, class_async);
    calc_lecture_sections.push_back(calc_section_1);


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

    Section calc_section_2(2, class_durations, class_start_time, class_semester, class_day, class_async);
    calc_lecture_sections.push_back(calc_section_2);

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

    Section linalg_section_1(1, class_durations, class_start_time, class_semester, class_day, class_async);
    linalg_lecture_sections.push_back(linalg_section_1);

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

    Section linalg_section_2(2, class_durations, class_start_time, class_semester, class_day, class_async);
    linalg_lecture_sections.push_back(linalg_section_2);

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

    Section mech_section_1(1, class_durations, class_start_time, class_semester, class_day, class_async);
    mech_lecture_sections.push_back(mech_section_1);

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

    
    Section mech_section_2(2, class_durations, class_start_time, class_semester, class_day, class_async);
    mech_lecture_sections.push_back(mech_section_2);
    
    CourseOfferings calculus("Calculus 1", "MAT186", calc_lecture_sections, empty_vec, empty_vec);
    CourseOfferings linear_algebra("Linear Algebra", "MAT188", linalg_lecture_sections, empty_vec, empty_vec);
    CourseOfferings mechanics("Mechanics", "CIV100", mech_lecture_sections, empty_vec, empty_vec);

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

    Section calc_section_1(1, class_durations, class_start_time, class_semester, class_day, class_async);
    calc_lecture_sections.push_back(calc_section_1);


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

    Section calc_section_2(2, class_durations, class_start_time, class_semester, class_day, class_async);
    calc_lecture_sections.push_back(calc_section_2);

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

    Section linalg_section_1(1, class_durations, class_start_time, class_semester, class_day, class_async);
    linalg_lecture_sections.push_back(linalg_section_1);

    
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

    Section linalg_section_2(2, class_durations, class_start_time, class_semester, class_day, class_async);
    linalg_lecture_sections.push_back(linalg_section_2);

    CourseOfferings calculus("Calculus 1", "MAT186", calc_lecture_sections, empty_vec, empty_vec);
    CourseOfferings linear_algebra("Linear Algebra", "MAT188", linalg_lecture_sections, empty_vec, empty_vec);

    unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash> offerings;
    offerings.insert(calculus);
    offerings.insert(linear_algebra);
    Scheduler scheduler;
    scheduler.schedule_classes(offerings);
}
// Test 8
void test_three_classes_conflict() {
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

    Section calc_section_1(1, class_durations, class_start_time, class_semester, class_day, class_async);
    calc_lecture_sections.push_back(calc_section_1);


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

    Section calc_section_2(2, class_durations, class_start_time, class_semester, class_day, class_async);
    calc_lecture_sections.push_back(calc_section_2);

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

    Section linalg_section_1(1, class_durations, class_start_time, class_semester, class_day, class_async);
    linalg_lecture_sections.push_back(linalg_section_1);

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

    Section linalg_section_2(2, class_durations, class_start_time, class_semester, class_day, class_async);
    linalg_lecture_sections.push_back(linalg_section_2);

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

    Section mech_section_1(1, class_durations, class_start_time, class_semester, class_day, class_async);
    mech_lecture_sections.push_back(mech_section_1);

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

    
    Section mech_section_2(2, class_durations, class_start_time, class_semester, class_day, class_async);
    mech_lecture_sections.push_back(mech_section_2);
    
    CourseOfferings calculus("Calculus 1", "MAT186", calc_lecture_sections, empty_vec, empty_vec);
    CourseOfferings linear_algebra("Linear Algebra", "MAT188", linalg_lecture_sections, empty_vec, empty_vec);
    CourseOfferings mechanics("Mechanics", "CIV100", mech_lecture_sections, empty_vec, empty_vec);

    unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash> offerings;
    offerings.insert(calculus);
    offerings.insert(linear_algebra);
    offerings.insert(mechanics);
    Scheduler scheduler;
    scheduler.schedule_classes(offerings);
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

int main(int argc, char *argv[])
{
    //--- Data Procesing ---- 
    // 1. Parses csv to get classes 
    // 2. Store csv in SQL database or something and related sql funcitons 
    CourseData course_data;

    // add lectures
    std::vector<Section> course_one_lecture_sections = course_data.add_course("MAT186H1", 1);
    //std::vector<Section> course_two_lecture_sections = course_data.add_course("MAT188H1", 1);
    //std::vector<Section> course_three_lecture_sections = course_data.add_course("CIV100H1", 1);

    std::vector<Section> empty_vec;
    //add tutorials
    std::vector<Section> course_one_tutorial_sections = course_data.add_course("MAT186H1", 2);
    //std::vector<Section> course_two_tutorial_sections = course_data.add_course("MAT188H1", 2);
    //std::vector<Section> course_three_tutorial_sections = course_data.add_course("CIV100H1", 2);
    //add practicals
   // std::vector<Section> course_one_practical_sections = course_data.add_course("MAT186H1", 3);
    //std::vector<Section> course_two_practical_sections = course_data.add_course("MAT188H1", 3);
    //std::vector<Section> course_three_practical_sections = course_data.add_course("CIV100H1", 3);

    CourseOfferings class_one("Calculus 1", "MAT186", course_one_lecture_sections, course_one_tutorial_sections, empty_vec);
    //CourseOfferings class_two("Linear Algebra", "MAT188", course_two_lecture_sections, course_two_tutorial_sections, course_two_practical_sections);
    //CourseOfferings class_three("Mechanics", "CIV100", mech_lecture_sections, course_three_tutorial_sections, course_three_practical_sections);

    unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash> offerings;
    offerings.insert(class_one);
    //offerings.insert(class_two);
    //offerings.insert(class_three);
    Scheduler scheduler;
    scheduler.schedule_classes(offerings);

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
    //test_sample_questions();
    return 0;
}