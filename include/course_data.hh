#ifndef COURSE_DATA_H
#define COURSE_DATA_H

#include <string>
#include <iostream>
#include <stdlib.h>
#include <sqlite3.h>

using namespace std; 

class CourseData {

    private:
        static int callback(void* data, int argc, char** argv, char** azColName);
        string quotesql(const string& s);
        sqlite3* DB_;
    public:
        CourseData();

};

#endif