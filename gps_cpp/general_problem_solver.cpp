#include "general_problem_solver.h"

using namespace std;

int main() {

  cout << "Hello World" << endl;
  return 0;
}

/**
 * Find a sequence of operators that will achieve all of the goal states.
 *
 * Returns a list of actions that will achieve all of the goal states, or
 * None if no such sequence exists. Each operator is specified by an action name,
 * list of preconditions, and add-list, and a delete-list.
 */
vector<string> solve( vector<string> init_states,
                      vector<string> goal_states,
                      vector<Operator> operators ) {

  string prefix = "Executing ";
  for ( Operator op : operators ) { // access by ref.  to avoid copying
    op.add.push_back( prefix + op.action );
  }

  vector<string> v {"hello"};
  return v;
}

// ACHIEVING SUB-GOALS //

vector<string> achieve_all( vector<string> states,
                            vector<Operator> ops,
                            vector<string> goals,
                            stack<string> goal_stack ) {
  vector<string> v {"hello"}; // need " ". '' (single-quotes) are multi-character literals
  return v;
} // end achieve_all()

vector<string> achieve( vector<string> states,
                        vector<Operator> operators,
                        string goal,
                        stack<string> goal_stack ) {

  vector<string> v {"hello"};
  return v;
} // end achieve()

// USING OPERATORS //

vector<string> apply_operator( Operator op,
                               vector<string> states,
                               vector<Operator> ops,
                               string goal,
                               stack<string> goal_stack ) {

  vector<string> v {"hello"};
  return v;
} // end apply_operator()
