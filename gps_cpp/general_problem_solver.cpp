#include "general_problem_solver.h"

using namespace std;

/**
 * Find a sequence of operators that will achieve all of the goal states.
 *
 * Returns a list of actions that will achieve all of the goal states, or
 * None if no such sequence exists. Each operator is specified by an action name,
 * list of preconditions, and add-list, and a delete-list.
 */
vector<string> gps( vector<string> init_states,
                      vector<string> goal_states,
                      vector<Operator> operators ) {

  string prefix = "Executing ";
  for ( Operator op : operators ) { // access by ref.  to avoid copying
    op.add.push_back( prefix + op.action );
  }
  stack<string> goal_stack = stack<string>();
  vector<string> final_states = achieve_all(init_states,
                                            operators,
                                            goal_states,
                                            goal_stack);

  vector<string> prefixed_final;
  if ( final_states.empty() ) {
    return {}; // empty vector
  }
  else {
    copy_if(final_states.begin(), final_states.end(),
            prefixed_final.begin(), prefixed_state());
  }
  return prefixed_final;
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
