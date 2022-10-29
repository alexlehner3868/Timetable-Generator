#ifndef SELECTIONS_H
#define SELECTIONS_H

#include "constraints.hh"
#include "scheduler.hh"
#include <string>

using namespace std;

class Selections {
    private:
        vector<string> fall_courses;
        vector<string> winter_courses;
        ConstraintHandler official_constraints;
        Scheduler official_scheduler;
    public:
        void add_class(string course_id, int semester);
        void remove_class(string course_id);
        void add_constraint(int constraint_num);
        void run_scheduler();
};

#endif