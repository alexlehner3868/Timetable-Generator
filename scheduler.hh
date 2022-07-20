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
    std::vector<std::unique_ptr<Constraint>> constraints_;
  public:
   Scheduler();

   void add_course(CourseOfferings course);
   void remove_course(CourseOfferings course);
   void add_constraint(Constraint* constraint);
   void remove_constraint(Constraint* constriant);

   void Solver::init_variables()
   bool Solver::apply_board(board const& b)
   void Solver::exactly_one_true(Minisat::vec<Minisat::Lit> const& literals)
};

