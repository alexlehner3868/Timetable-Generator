
#include "course_data.hh"

#include <sqlite3.h>
#include <stdlib.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

#include "scheduler.hh"

using namespace std;

#define SECTION_OFFSET 100

CourseData::CourseData() {
    int action_succes = 0;
    // char* messaggeError;

    string db_name = "data/courses.db";
    // The .db file is initiazed so we shouldnt need to run this code again
    /* action_succes = sqlite3_open(db_name.c_str(), &DB_);
    if (action_succes != SQLITE_OK) {
        cout<<"Error creating account"<<std::endl;
    }

    ifstream infile("data/courses.sql");
    string sql;

    fstream datafile;
    datafile.open("data/courses.sql",ios::in); //open a file to perform read operation using file
    object if (datafile.is_open()){   //checking whether the file is open string sql;
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
        cout << "Error opening database" << std::endl;
    } else {
        // cout<<"Database opened sucessful"<<std::endl;
    }
}

void CourseData::find_course_times(string course_id) {
    int action_success = 0;
    string sql = "SELECT * FROM Courses WHERE ACAD_ACT_CD = " + quotesql(course_id) + ";";
    action_success = sqlite3_exec(DB_, sql.c_str(), callback, NULL, NULL);
    if (action_success != SQLITE_OK) {
        cout << "Error finding class" << std::endl;
    }
}

string CourseData::quotesql(const string &s) {
    return string("'") + s + string("'");
}

int CourseData::callback(void *data, int argc, char **argv, char **azColName) {
    int i;
    fprintf(stderr, "%s: ", (const char *)data);

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
    for (i = 0; i < argc; i++) {
        cout << azColName[i] << " ---> " << argv[i] << endl;
    }
    printf("\n");
    return 0;
}

void CourseData::remove_course(string course_id) {}

int CourseData::get_sql_data(void *course_data, int argc, char **argv, char **azColName) {
    std::vector<std::string> one_sections_data;

    /**
     *  azColName[i] - the header of the data
     *  0 - course id
     *  1 - section (fall/winter/summer/full year)
     *  2 - session (likely won't need this)
     *  3 - type of class - lecture, tutorial, or practical
     *  4 - section #
     *  5 - day
     *  6 - class start time
     *  7 - class end time
     */

    // argv[i] - the data at that header

    /*
    cout << azColName[1] << " ---> " << argv[1] << endl;
    cout << azColName[3] << " ---> " << argv[3] << endl;
    cout << azColName[4] << " ---> " << argv[4] << endl;
    cout << azColName[5] << " ---> " << argv[5] << endl;
    cout << azColName[6] << " ---> " << argv[6] << endl;
    cout << azColName[7] << " ---> " << argv[7] << endl;
    */

    // cout << azColName[1] << " ---> " << argv[1] << endl;
    //  need error checking here so that no errors results
    //  this can probably be broken :(
    // cout << "section" << endl;
    one_sections_data.push_back(argv[2]);
    // cout << "type of class" << endl;
    one_sections_data.push_back(argv[4]);
    one_sections_data.push_back(argv[5]);
    // cout << argv[4] << endl;
    one_sections_data.push_back(argv[6]);
    one_sections_data.push_back(argv[7]);
    one_sections_data.push_back(argv[8]);
    one_sections_data.push_back(argv[3]);
    //name of the course
    one_sections_data.push_back(argv[0]);
    std::vector<std::vector<std::string>>
        *pointer_to_course_data = (std::vector<std::vector<std::string>> *)course_data;
    (*pointer_to_course_data).push_back(one_sections_data);

    return 0;
}

std::vector<Section> CourseData::add_course(string course_id, int section_type) {
    vector<int> class_durations;
    vector<int> class_start_time;
    vector<int> class_day;
    vector<char> class_semester;
    vector<bool> class_async;
    vector<int> old_section_num;
    old_section_num.push_back(0);
    vector<int> current_section_num;
    current_section_num.push_back(0);
    std::vector<std::vector<std::string>> course_data;
    std::vector<Section> available_sections;
    std::vector<Section> available_sections_pruned;

    if (section_type == LEC) {
        // we want to add lectures
        std::string sql = "SELECT * FROM Courses WHERE ACAD_ACT_CD = " + quotesql(course_id) +
                          " AND TEACH_METHOD = 'LEC';";
        int action_success = sqlite3_exec(DB_, sql.c_str(), get_sql_data, &course_data, NULL);
        if (action_success != SQLITE_OK) {
            cout << "No lectures in class" << std::endl;
        }
    } else if (section_type == TUT) {
        // we want to add tutorials
        std::string sql = "SELECT * FROM Courses WHERE ACAD_ACT_CD = " + quotesql(course_id) +
                          " AND TEACH_METHOD = 'TUT';";
        int action_success = sqlite3_exec(DB_, sql.c_str(), get_sql_data, &course_data, NULL);
        if (action_success != SQLITE_OK) {
            cout << "No tutorials in class" << std::endl;
        }
    } else if (section_type == PRA) {
        // we want to add practicals
        std::string sql = "SELECT * FROM Courses WHERE ACAD_ACT_CD = " + quotesql(course_id) +
                          " AND TEACH_METHOD = 'PRA';";
        int action_success = sqlite3_exec(DB_, sql.c_str(), get_sql_data, &course_data, NULL);
        if (action_success != SQLITE_OK) {
            cout << "No practicals in class" << std::endl;
        }
    } else {
        // bad
    }

    /*
    // now course_data is in
    // let's loop through it and add it to a section
    //cout << course_data[0][2] << endl;
    if (!course_data.empty()) {
        old_section_num = (stoi(course_data[0][2]) - SECTION_OFFSET);
        cout << (stoi(course_data[0][2]) - SECTION_OFFSET) << endl;
    } else {
        //there is no course_data so skip setting the old_section_num
        old_section_num = 1;
    }*/
    char old_sem = 'F';
    char sem = 'F';
    old_section_num.clear();
    old_section_num.push_back(1);
    for (std::vector<std::string> section : course_data) {
        // error checking on this - make sure it is valid
        current_section_num.clear();
        current_section_num.push_back(stoi(section[2]) - SECTION_OFFSET);
        
        //cout << "pushing back section " << current_section_num[0] << " and course id " << course_id << endl;
        // << endl;
        //  each vector contains all the info for one section of a lecture
        // 0 - section F/W
        // 1 - lec/tut/pra
        // 2 - section #
        // 3 - day
        // 4 - class start time
        // 5 - class end time
        // 6 - session id

        // if no more sections need to be added to the vectors
        if (old_section_num[0] != current_section_num[0] || old_sem != section[0][0]) {

            // create a section containing all the information we just queried from SQL DB
            //cout << "adding a class with the section number " << old_section_num[0] << " and course id " << course_id << endl << "at " << class_start_time[0] << endl;
            // the way the loop is set up, we are
            Section add_section(old_section_num,
                                class_durations,
                                class_start_time,
                                class_semester,
                                class_day,
                                class_async);
            old_section_num.clear();
            old_section_num.push_back(current_section_num[0]);
            available_sections.push_back(add_section);
            class_durations.clear();
            class_start_time.clear();
            class_day.clear();
            class_semester.clear();
            class_async.clear();
        }

        // if class start time doesn't exist, then class is async
        class_async.insert(class_async.end(), {empty(section[4])});
        if (section[5].empty() && section[4].empty()) {
            class_durations.insert(class_durations.end(), {0});
            class_start_time.insert(class_start_time.end(), {0});
        } else {
            class_durations.insert(class_durations.end(), {(stoi(section[5]) - stoi(section[4]))});
            class_start_time.insert(class_start_time.end(), {stoi(section[4])});
        }
        
        
        // take the first char of the string 'F' or 'W' or 'Y'
        old_sem = sem;
        sem = section[0][0];
        if(sem == 'Y'){
            if(section[6].back() == '9'){
                class_semester.insert(class_semester.end(), 'F');
            } else{
                class_semester.insert(class_semester.end(), 'W'); 
            }
        }else{
            class_semester.insert(class_semester.end(), {section[0][0]});
        }
       

        if (section[3] == "MO") {
            class_day.insert(class_day.end(), {1});
        } else if (section[3] == "TU") {
            class_day.insert(class_day.end(), {2});
        } else if (section[3] == "WE") {
            class_day.insert(class_day.end(), {3});
        } else if (section[3] == "TH") {
            class_day.insert(class_day.end(), {4});
        } else if (section[3] == "FR") {
            class_day.insert(class_day.end(), {5});
        } else {
            // error, fix
            class_day.insert(class_day.end(), {6});
        }
    }
    // add the last section once no more sections exist
    if (current_section_num[0] != 0) {
        Section add_section(old_section_num,
                            class_durations,
                            class_start_time,
                            class_semester,
                            class_day,
                            class_async);
        available_sections.push_back(add_section);
        class_durations.clear();
        class_start_time.clear();
        class_day.clear();
        class_semester.clear();
        class_async.clear();
    }



    // here we want to check sections that have the same info but different section number
    // note we are changing the vector as we iterate through it...
    int vector_top = 0;
    int vector_inner = 0;
    set<int> sections;

    for (auto section: available_sections) {
        // compare each section
        vector_inner = vector_top + 1;
        for (vector<Section>::iterator inner_section = available_sections.begin() + vector_inner; inner_section != available_sections.end(); inner_section++) {
            if ( ((*inner_section).duration_ == section.duration_) &&
                 ((*inner_section).start_time_ == section.start_time_) &&
                 ((*inner_section).semester_ == section.semester_) &&
                 ((*inner_section).day_ == section.day_) &&
                 ((*inner_section).async_ == section.async_) &&vector_top != vector_inner) {
                    //cout << " section " << vector_inner+1 << " with top section " <<vector_top+1<< " to be deleted" << endl;
                    sections.insert(vector_inner);
                    //cout << vector_inner << endl;
            }
            vector_inner++;
        }
        vector_top++;
    }
    // or sections with same data but different number, we delete the extras
    //set with all the section ids!
    set<int> all_sections;
    for (int i = 0; i < int(available_sections.size()); i++) {
        all_sections.insert(i);
        //cout << "Adding " << i << " to list of all sections" << endl;
    }
    

    //set with the proper section ids!
    set<int> new_sections = all_sections;
    
    for (auto section: sections) {
        //cout << "Checking if all sections contains " << section << endl;
        //cout << all_sections.contains(section) << endl;
        if ((all_sections.contains(section))) {
            new_sections.erase(section);
            //cout << "removing section " << section << endl;
        }
    }

    for (auto section_to_add: new_sections) {
        //cout << "Section " << section_to_add << "is in the final list" << endl;
        //cout << "Adding section " << available_sections[section_to_add].section_id_[0] << " in semester " << available_sections[section_to_add].semester_[0] << " on day " 
        //<< available_sections[section_to_add].day_[0] << " at time " << available_sections[section_to_add].start_time_[0] << " for " << available_sections[section_to_add].duration_[0] << " hours." << endl;
        available_sections_pruned.push_back(available_sections[section_to_add]);
    }
    //cout << endl << endl;
    // make sure this is error free

    //for (auto section: available_sections_pruned) {
        //cout << "adding sections " << section.section_id_[0] << endl;
    //}
    return available_sections_pruned;
}
