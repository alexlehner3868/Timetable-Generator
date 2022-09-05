
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

    string db_name = "course_data.db"; 
    /* The .db file is initiazed so we shouldnt need to run this code again
    action_succes = sqlite3_open(db_name.c_str(), &DB_);
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
    int action_succes = 0;
    string sql = "SELECT * FROM Courses WHERE ACAD_ACT_CD = " +quotesql(course_id) + ";";
    action_succes = sqlite3_exec(DB_, sql.c_str(), callback, NULL, NULL);
    if (action_succes != SQLITE_OK) {
        cout<<"Error finding class"<<std::endl;
    }
}

string CourseData::quotesql( const string& s ) {
    return string("'") + s + string("'");
}

int CourseData::callback(void* data, int argc, char** argv, char** azColName){
    int i;
    fprintf(stderr, "%s: ", (const char*)data);
  
    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
  
    printf("\n");
    return 0;
}

