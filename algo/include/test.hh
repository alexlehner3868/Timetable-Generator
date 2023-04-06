#ifndef TEST_H
#define TEST_H

using namespace std;

priority_queue<CourseOfferings, vector<CourseOfferings>, greater<CourseOfferings>> get_classes();
void test_sample_questions();
void remove_course(priority_queue<CourseOfferings, vector<CourseOfferings>, greater<CourseOfferings>>& offerings, string course_id);
void get_schedule();
priority_queue<CourseOfferings, vector<CourseOfferings>, greater<CourseOfferings>> test_three_classes_conflict();


#endif