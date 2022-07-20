#include <string>
#include <iostream>
#include <unordered_set>
#include <minisat/core/Solver.h>


#include "course_offering.hh";
#include "constraints.hh";


using namespace std;
using Minisat::mkLit;
using Minisat::lbool;


class Scheduler {

  private:
    unordered_set<CourseOfferings> course_offerings_;
    unordered_set<TimeConstraint> time_constraints_;
    unordered_set<ChunkConstraint> chunk_constraints_;
    unordered_set<CutOffTimeConstraint> cut_off_time_constraints_;

  public:
   Scheduler();

   void add_course(CourseOfferings course);
   void remove_course(CourseOfferings course);


   void Solver::init_variables()
   bool Solver::apply_board(board const& b)
   void Solver::exactly_one_true(Minisat::vec<Minisat::Lit> const& literals)
};

