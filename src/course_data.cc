
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


int CourseData::get_sql_data(void * course_data, int argc, char** argv, char** azColName){
    std::vector<std::string> one_sections_data;

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
    cout << azColName[1] << " ---> " << argv[1] << endl;
    cout << azColName[3] << " ---> " << argv[3] << endl;
    cout << azColName[4] << " ---> " << argv[4] << endl;
    cout << azColName[5] << " ---> " << argv[5] << endl;
    cout << azColName[6] << " ---> " << argv[6] << endl;
    cout << azColName[7] << " ---> " << argv[7] << endl;

    // need error checking here so that no errors results
    // this can probably be broken :( 
        
    one_sections_data.push_back(argv[1]);
    one_sections_data.push_back(argv[3]);
    one_sections_data.push_back(argv[4]);
    one_sections_data.push_back(argv[5]);
    one_sections_data.push_back(argv[6]);
    one_sections_data.push_back(argv[7]);

    std::vector<std::vector<std::string>> * pointer_to_course_data = (std::vector<std::vector<std::string>> *) course_data;
    (*pointer_to_course_data).push_back(one_sections_data);
    
    printf("\n");
    return 0;
}

std::vector<Section> CourseData::get_course_info(string course_id) {
    vector<int> class_durations;
    vector<int> class_start_time;
    vector<int> class_day;
    vector<char> class_semester;
    vector<bool> class_async;
    int section_num;
    std::vector<std::vector<std::string>> course_data;
    std::vector<Section> available_sections;

    
    // we want to add lectures first
    std::string sql = "SELECT * FROM Courses WHERE ACAD_ACT_CD = " + quotesql(course_id) + " ;";
    int action_success = sqlite3_exec(DB_, sql.c_str(), get_sql_data, &course_data, NULL);
    if (action_success != SQLITE_OK) {
        cout << "No lectures in class" << std::endl;
    }
    
    
    // now course_data is in
    // let's loop through it and add it to a section

    for (std::vector<std::string> section : course_data) {
        // each vector contains all the info for one section of a lecture

        // 0 - section F/W
        // 1 - lec/tut/pra
        // 2 - section #
        // 3 - day
        // 4 - class start time
        // 5 - class end time

        // error checking on this - make sure it is valid
        section_num = stoi(section[2]);
        
        //if class start time doesn't exist, then class is async
        class_async.push_back(!empty(section[4]));
        class_durations.push_back(stoi(section[5]) - stoi(section[4]));
        class_start_time.push_back(stoi(section[4]));
        //take the first char of the string 'F' or 'W' or 'Y'
        class_semester.push_back(section[0][0]);

        if (section[3] == "MO") {
            class_day.push_back(1);
        } else if (section[3] == "TU") {
            class_day.push_back(2);
        } else if (section[3] == "WE") {
            class_day.push_back(3);
        } else if (section[3] == "TH") {
            class_day.push_back(4);
        } else if (section[3] == "FR") {
            class_day.push_back(5);
        } else {
            class_day.push_back(2);
        }

        //create a section containing all the information we just queried from SQL DB
        Section add_section(section_num, class_durations, class_start_time, class_semester, class_day, class_async);  
        available_sections.push_back(add_section);
    }

    //make sure this is error free
    return available_sections;
}
