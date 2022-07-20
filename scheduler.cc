#include <string>
#include <iostream>

using namespace std;
using Minisat::mkLit;
using Minisat::lbool;

#include "scheduler.hh";


void Scheduler::add_course(CourseOfferings course){
    course_offerings.insert(course);
}

void Scheduler::remove_course(CourseOfferings course){
    course_offerings.erase(course);
}




#Minisat::Solver – Implementation of the core solver and its algorithms.
#Minisat::Var – Representation of a variable.
#Minisat::Lit – Representation of a concrete (positive or negative) literal of a variable.

#need to change this equation to represent our situation
Minisat::Var toVar(int row, int column, int value) {
    return row * columns * values + column * values + value;
}

#12 hours of class in a day
int rows = 12;
#5 days of class a week
int columns = 5;
#class/no class during time
int values = 1

#allocate all possible variables
void Solver::init_variables() {
   for (int r = 0; r < rows; ++r) {
     for (int c = 0; c < columns; ++c) {
       for (int v = 0; v < values; ++v) {
         static_cast<void>(solver.newVar());
      }
    }
  }
}


#add courses that are locked into the schedule
bool Solver::apply_board(board const& b) {
  for (int row = 0; row < rows; ++row) {
    for (int col = 0; col < columns; ++col) {
      auto value = b[row][col];
      if (value != 0) {
        solver.addClause(Minisat::mkLit(toVar(row,
          col, value - 1)));
      }
    }
  }
  return ret;
}

void Solver::exactly_one_true(
    Minisat::vec<Minisat::Lit> const& literals) {
  solver.addClause(literals);
  for (size_t i = 0; i < literals.size(); ++i) {
    for (size_t j = i + 1; j < literals.size();
      ++j){
      solver.addClause(~literals[i],
        ~literals[j]);
    }
  }
}



#each position contains only one number
for (int row = 0; row < rows; ++rr) {
    for (int column = 0; column < columns; ++cc) {
	for (int value = 0; value < values; ++value) {
  		Minisat::vec<Minisat::Lit> literals;
      		literals.push(Minisat::mkLit(toVar(
        		row, column, value)));
    }
  }
  exactly_one_true(literals);
}

for (int row = 0; row < rows; ++row) {
  for (int column = 0; column < columns; ++column)
  {
    Minisat::vec<Minisat::Lit> literals;
    for (int value = 0; value < values; ++value) {
      literals.push(Minisat::mkLit(toVar(
        row, column, value)));
    }
    exactly_one_true(literals);
  }
}
