#ifndef TEST_H
#define TEST_H

using namespace std;

unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash> get_classes();
void test_sample_questions();
void remove_course(unordered_set<CourseOfferings, CourseOfferings::CourseOfferingHash>& offerings, string course_id);
void get_schedule();


#endif