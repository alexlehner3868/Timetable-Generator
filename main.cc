#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>

#include "constraints.hh"
#include "scheduler.hh"
#include "course_offering.hh"
#include "section.hh"

using namespace std;

void test_sample_questions(){
     // Test 1: One class with one lecture section
    {
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

        unordered_set<CourseOfferings> offerings;
        offerings.insert(calculus);
        Scheduler scheduler;
        scheduler.schedule_classes(offerings);
    }

    {
        //Test 2: Mat186 Lec1 Lec2 (no conflicts)
    }

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
}