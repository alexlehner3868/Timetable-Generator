
/* commenting out for now
#include <string>
#include <iostream>
#include <stdlib.h>
#include <sqlite3.h>
#include <fstream>
#include <sstream>

#include "course_data.hh"

using namespace std; 

CourseData::CourseData(){
    /*
    int action_succes = 0;
    char* messaggeError;

    string db_name = "course_data.db"; 
    action_succes = sqlite3_open(db_name.c_str(), &DB_);
    if (action_succes != SQLITE_OK) {
        cout<<"Error creating account"<<std::endl;
    }

    ifstream infile("data/courses.sql");
    string sql;

    while (std::getline(infile, sql)){
        stringstream iss(sql);
        if (!(iss >> sql)) { break; } // error
        action_succes = sqlite3_exec(DB_, sql.c_str(), NULL, 0, &messaggeError);

        if (action_succes != SQLITE_OK) {
            cout<<"Error running sql command"<<std::endl;
            sqlite3_free(messaggeError);
        }
    }
    
}
*/
