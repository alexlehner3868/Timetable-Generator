#include "selections.hh"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void Selections::add_class(string course_id, int semester){
    // check if vectors are full (max 6 classes per term)
    if (semester == 0) {
        if (fall_courses.size() > 5) {
            cout << "You already have six courses in the fall!" << endl;
            return;
        } else {
            // try to add to fall semester
            //fall_courses.push_back();
        }
    } else if (semester == 1) {
        if (winter_courses.size() > 5) {
            cout << "You already have six courses in the winter!" << endl;
            return;
        } else {

        }
    } else {
        cout << "Invalid semester!" << endl;
        return;
    }
    // check if course id is valid
    

}
void Selections::remove_class(string course_id){

}
void Selections::add_constraint(int constraint_num){

}
void Selections::run_scheduler(){
    
}