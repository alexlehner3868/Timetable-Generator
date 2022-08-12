#include <string>
#include <iostream>
#include <unordered_set>

#include "course_offering.hh";
#include "constraints.hh";

using namespace std;

class Scheduler {

    private:

    public:
        Scheduler();
        void schedule_classes(unordered_set<CourseOfferings>& course_offerings);
};

