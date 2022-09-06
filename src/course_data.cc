
#include <string>
#include <iostream>
#include <stdlib.h>
#include <sqlite3.h>
#include <fstream>
#include <sstream>

#include "course_data.hh"

using namespace std; 

CourseData::CourseData(){
    
    int action_succes = 0;
    //char* messaggeError;

    string db_name = "CourseData.db"; 
     //The .db file is initiazed so we shouldnt need to run this code again
   /* action_succes = sqlite3_open(db_name.c_str(), &DB_);
    if (action_succes != SQLITE_OK) {
        cout<<"Error creating account"<<std::endl;
    }

    ifstream infile("data/courses.sql");
    string sql;

    fstream datafile;
    datafile.open("data/courses.sql",ios::in); //open a file to perform read operation using file object
    if (datafile.is_open()){   //checking whether the file is open
        string sql;
        while(getline(datafile, sql)){ //read data from file object and put it into string.
           action_succes = sqlite3_exec(DB_, sql.c_str(), NULL, 0, &messaggeError);
            cout<<sql<<endl;
        if (action_succes != SQLITE_OK) {
            cout<<"Error running sql command"<<std::endl;
            sqlite3_free(messaggeError);
        }
        }
        datafile.close(); //close the file object.
    }
    
*/
   // Open the Database and store it in DB_
     action_succes = sqlite3_open(db_name.c_str(), &DB_);
    if (action_succes != SQLITE_OK) {
        cout<<"Error openning database"<<std::endl;
    }else{
        cout<<"Databse opened sucessful"<<std::endl;
    }
}

void CourseData::find_course_times(string course_id){
    int action_success = 0;
    string sql = "SELECT * FROM Courses WHERE ACAD_ACT_CD = " +quotesql(course_id) + ";";
    action_success = sqlite3_exec(DB_, sql.c_str(), callback, NULL, NULL);
    if (action_success != SQLITE_OK) {
        cout<<"Error finding class"<<std::endl;
    }
}

string CourseData::quotesql( const string& s ) {
    return string("'") + s + string("'");
}

int CourseData::callback(void* data, int argc, char** argv, char** azColName){
    int i;
    fprintf(stderr, "%s: ", (const char*)data);
  
   // for (i = 0; i < argc; i++) {
    //    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    //}

    /**
     *  azColName[i] - the header of the data
     *  0 - course id
     *  1 - section (fall or winter)
     *  2 - session (likely won't need this)
     *  3 - type of class - lecture, tutorial, or practical
     *  4 - section # 
     *  5 - day
     *  6 - class start time
     *  7 - class end time
     */
    // argv[i] - the data at that header
    for( i = 0; i < argc; i++){
        cout<<azColName[i]<<" ---> " << argv[i]<<endl;
    }
  
    printf("\n");
    return 0;
}


/** 
 * 
 * 
 * 
 * 
 * 
*/
void CourseData::add_course(string course_id) {
    //we need to keep a list of the courses we are trying to add


    //
}

void CourseData::remove_course(string course_id) {

}
/*
Section CourseData::get_course_info(string course_id) {
    vector<int> class_durations;
    vector<int> class_start_time;
    vector<int> class_day;
    vector<char> class_semester;
    vector<bool> class_async;

    string sql = "SELECT * FROM Courses WHERE ACAD_ACT_CD = " +quotesql(course_id) + ";";

    vector<int> class_durations_ = 
    // Calculus
    // -- Section 1 
    // Monday 9 - 10
    // Wednesday 10 - 12
    // Thursday 1 - 2
    //first get SQL for the durations of each class
    class_durations.insert(class_durations.end(), { 1, 2, 1 });
    //then get start times of each class
    class_start_time.insert(class_start_time.end(), { 9, 10, 13 });
    //get the days that the classes occur on
    class_day.insert(class_day.end(), { 1, 3, 4 });
    //get the semester that the class occurs in
    class_semester.insert(class_semester.end(), { 'F', 'F', 'F' });
    //is the class async?
    class_async.insert(class_async.end(), { false, false, false });

    //create a section containing all the information we just queried from SQL DB
    Section calc_section_1(1, class_durations, class_start_time, class_semester, class_day, class_async);   
}
*/