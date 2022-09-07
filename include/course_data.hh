

#ifndef COURSE_DATA_H
#define COURSE_DATA_H

#include <string>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <dlfcn.h>
#include "sqlite3.h"
#include "section.hh"

using namespace std; 


class CourseData {

    private:
        string quotesql(const string& s);
        static int callback(void* data, int argc, char** argv, char** azColName);
        static int get_sql_data(void* course_data, int argc, char** argv, char** azColName);
        sqlite3* DB_;
        std::vector<int> fall_course_ids;
        std::vector<int> winter_course_ids;
    public:
        CourseData();
        void find_course_times(string course_id);
        void remove_course(string course_id);
        std::vector<Section> add_course(string course_id, int section_type);

};

#endif


