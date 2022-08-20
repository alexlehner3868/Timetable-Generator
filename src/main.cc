#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>

#include "constraints.hh"
#include "scheduler.hh"
#include "course_offering.hh"
#include "section.hh"

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


void test_sample_questions(){
    // One class, with one section 
    test_one_class_one_section();
    // One class with multiple sections 
    test_one_class_multiple_sections();

    {
        //Test 3: Mat186 Lec1  (no conflicts )
        //        LinAlg Lec1  
    }

    {
        //Test 4: Mat186 Lec1 Lec2 (no conflicts )
        //        LinAlg Lec1  
    }

    {
        //Test 5: Mat186 Lec1 Lec2 (no conflicts )
        //        LinAlg Lec1 Lec2
    }

    {
        //Test 6: Mat186 Lec1 Lec2 (no conflicts )
        //        LinAlg Lec1  Lec 2
        //        Spanish Lec1 Lec2 
    }

    {
        //Test 7: Mat186 Lec1 Lec2 (insert conflict wiht Mat lec1 and Lin1)
        //        LinAlg Lec1  
    }

    {
        //Test 8: Mat186 Lec1 Lec2 (Put in some conflicts)
        //        LinAlg Lec1  Lec2
        //        Spanish Lec1 Lec2
    }
} 

int main(int argc, char *argv[])
{
    //--- Data Procesing ---- 
    // 1. Parses csv to get classes 
    // 2. Store csv in SQL database or something and related sql funcitons 

    // -- User input (later) 
    // 1. Search and add classes to timetable 
    // 2. Remove classes 
    // 3. Add constraints 

    // -- Scheduling Algo 
    // 1. Loop through all options and see what works 
    // 2. Evaluate all possible options based on constraints 
    // 3. What happens if no solution 

    

    // -- GUI  
    // -- Web stuff 

    // -- Testing Code
    test_sample_questions();
    return 0;
}