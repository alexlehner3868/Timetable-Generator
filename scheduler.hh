#include <string>
#include <iostream>
#include <unordered_set>

#include "course_offering.hh";
#include "constraints.hh";

using namespace std;

class Scheduler {

    private:
        unordered_set<CourseOfferings> course_offerings_;
        unordered_set<TimeConstraint> time_constraints_;
        unordered_set<ChunkConstraint> chunk_constraints_;
        unordered_set<CutOffTimeConstraint> cut_off_time_constraints_;

    public:
        Scheduler();

        // Setting Data 
        void add_course(CourseOfferings course);
        void remove_course(CourseOfferings course);

        void add_time_constraint(TimeConstraint constraint);
        void remove_time_constraint(TimeConstraint constraint);

        void add_chunk_constraint(ChunkConstraint constraint);
        void remove_chunk_constraint(ChunkConstraint constraint);

        void add_cuttoff_constraint(CutOffTimeConstraint constraint);
        void remove_cutoff_constraint(CutOffTimeConstraint constraint);


};

