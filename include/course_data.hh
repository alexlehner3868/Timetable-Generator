

#ifndef COURSE_DATA_H
#define COURSE_DATA_H

#include <string>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <dlfcn.h>
#include "sqlite3.h"

using namespace std; 



class CourseData {

    private:
        string quotesql(const string& s);
        static int callback(void* data, int argc, char** argv, char** azColName);
        sqlite3* DB_;
        std::vector<int> fall_course_ids;
        std::vector<int> winter_course_ids;
    public:
        CourseData();
        void find_course_times(string course_id);
        void add_course(string course_id);
        void remove_course(string course_id);
        // get_course_info(string course_id);

};

#endif


