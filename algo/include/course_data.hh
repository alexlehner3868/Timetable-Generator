

#ifndef COURSE_DATA_H
#define COURSE_DATA_H

#include <dlfcn.h>
#include <stdlib.h>

#include <iostream>
#include <string>
#include <vector>

#include "section.hh"
#include "sqlite3.h"

using namespace std;

struct SelectedCourseSection {
    string course_code;
    int type; // 1 = lec, 2 = tut, 3 = pra
    int section;
    char semester;
};

enum class_type { LEC = 1, TUT = 2, PRA = 3, CONSTRAINT = 4 };

class CourseData {
private:
    string quotesql(const string &s);
    static int callback(void *data, int argc, char **argv, char **azColName);
    static int get_sql_data(void *course_data, int argc, char **argv, char **azColName);
    sqlite3 *DB_;
    std::vector<int> fall_course_ids;
    std::vector<int> winter_course_ids;

public:
    CourseData();
    void find_course_times(string course_id);
    void remove_course(string course_id);
    std::vector<Section> add_course(string course_id, int section_type);
};

#endif
