

#ifndef COURSE_DATA_H
#define COURSE_DATA_H

#include <string>
#include <iostream>
#include <stdlib.h>
#include <dlfcn.h>
#include "sqlite3.h"

using namespace std; 



class CourseData {

    private:
        string quotesql(const string& s);
        static int callback(void* data, int argc, char** argv, char** azColName);
        sqlite3* DB_;
    public:
        CourseData();
        void find_course_times(string course_id);

};

#endif


