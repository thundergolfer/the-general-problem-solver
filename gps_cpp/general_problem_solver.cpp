#include "general_problem_solver.h"

using namespace std;

#define DEBUG 1

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
  vector<string> goal_stack = vector<string>();
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
                            vector<string>& goal_stack ) {
  // Try achieve each goal in the order they are given. If any one
  // goal state cannot be achieved, then the problem cannot be solved.
  for (auto const& goal : goals ) {
    states = achieve( states, ops, goal, goal_stack );
    if ( states.empty() ) {
      return {};
    }
  }
  // Ensure we haven't removed a goal state in the process of solving
  // other states.
  for (auto const& goal : goals ) {
    if ( find( states.begin(), states.end(), goal) == states.end() ) { // if goal not in states
      cout << goal << '\n';
      return {}; // None
    }
  }
  return states;
} // end achieve_all()

vector<string> achieve( vector<string> states,
                        vector<Operator> operators,
                        string goal,
                        vector<string>& goal_stack ) {
  vector<string> result;
  if(DEBUG) {
    cout << goal_stack.size() << '\n';
    cout << "Acheiving: " + goal << '\n';
  }

  // prevent going in circles. if the current goal in is the goal stack
  // it means we are already trying to achieve it by way of achieving... itself
  if( find( goal_stack.begin(), goal_stack.end(), goal ) != goal_stack.end() ) {
    return {};
  }

  for (auto const& op : operators ) {
    // is the operator appropiate?
    if( find( op.add.begin(), op.add.end(), goal ) == op.add.end() ) {
      continue;
    }
    // Is operator applicable? Try to apply it.
    result = apply_operator(op, states, operators, goal, goal_stack );
    if ( !result.empty() ) {
      return result;
    }
  }
  return {};
} // end achieve()

// USING OPERATORS //

vector<string> apply_operator( Operator op,
                               vector<string> states,
                               vector<Operator> ops,
                               string goal,
                               vector<string>& goal_stack ) {

  vector<string> v {"hello"};
  return v;
} // end apply_operator()
