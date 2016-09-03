#include "general_problem_solver.h"

using namespace std;

#define DEBUG 0 // set to 1 for debuggig

/**
 * Find a sequence of operators that will achieve all of the goal states.
 *
 * Returns a list of actions that will achieve all of the goal states, or
 * None if no such sequence exists. Each operator is specified by an action name,
 * list of preconditions, and add-list, and a delete-list.
 */
vector<string> gps( vector<string> init_states,
                      vector<string> goal_states,
                      vector<Operator>& operators ) {

  string prefix = "Executing ";
  for ( Operator& op : operators ) { // access by ref.  to avoid copying
    op.add.push_back( prefix + op.action );
  }
  vector<string> goal_stack = vector<string>();
  vector<string> final_states = achieve_all(init_states,
                                            operators,
                                            goal_states,
                                            goal_stack);
  vector<string> prefixed_final (final_states.size());
  if ( final_states.empty() ) {
    if( DEBUG ) { cout << "Final states empty returning empty\n"; }
    return {}; // empty vector
  }
  else {
    auto it = copy_if(final_states.begin(), final_states.end(),
            prefixed_final.begin(), prefixed_state());
    prefixed_final.resize(distance(prefixed_final.begin(), it)); // shrink container to new size
  }
  if(DEBUG && prefixed_final.empty()) { cout << "prefixed_final is empty after copy().\n"; }
  return prefixed_final;
}

// ACHIEVING SUB-GOALS //

vector<string> achieve_all( vector<string> states,
                            vector<Operator>& ops,
                            vector<string> goals,
                            vector<string>& goal_stack ) {
  // Try achieve each goal in the order they are given. If any one
  // goal state cannot be achieved, then the problem cannot be solved.
  for (auto const& goal : goals ) {
    states = achieve( states, ops, goal, goal_stack );
    if ( states.empty() ) {
      if(DEBUG) { cout << "can't achieve <" + goal + ">. returning empty\n"; }
      return {};
    }
  }
  if(DEBUG) {
    for( auto const& op : ops ) {
      for( auto const& state : op.add ) {
        cout << state;
      }
      cout << '\n';
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
    cout << "Goal Stack size: " + to_string(goal_stack.size()) << '\n';
    cout << "Acheiving: " + goal << '\n';
  }

  // check if the state already holds before we do anything
  if( find(states.begin(), states.end(), goal) != states.end() ) {
    return states;
  }

  // prevent going in circles. if the current goal in is the goal stack
  // it means we are already trying to achieve it by way of achieving... itself
  if( find( goal_stack.begin(), goal_stack.end(), goal ) != goal_stack.end() ) {
    if(DEBUG) { cout << "found goal in goal_stack. we are in a circle!\n"; }
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
    if(DEBUG) { cout << "Action: " + op.action + " couldn't be applied.\n"; }
  }
  if(DEBUG) { cout << "Couldn't find appropiate operator to apply. returning empty.\n"; }
  return {};
} // end achieve()

// USING OPERATORS //

vector<string> apply_operator( Operator op,
                               vector<string> states,
                               vector<Operator> ops,
                               string goal,
                               vector<string>& goal_stack ) {
  if(DEBUG) {
    cout << goal_stack.size() << '\n';
    cout << "Consider: " + op.action << '\n';
  }

  // Satisfy all of operator's preconditions
  goal_stack.push_back(goal);
  vector<string> result = achieve_all(states, ops,
                                      op.preconds,
                                      goal_stack); // should goal be on end or at start?
  if( result.empty() ) {
    return {};
  }

  if(DEBUG) {
    cout << goal_stack.size() << '\n';
    cout << "Action: " + op.action << '\n';
  }

  // Merge the old states with operator's add-list, filtering out delete-list.
  vector<string> add_list = op.add;
  vector<string> del_list = op.remove;
  vector<string> new_result = {};
  for( auto const& state: result ) {
    if( find( del_list.begin(), del_list.end(), state ) != del_list.end() ) {
      continue;
    }
    else {
      new_result.push_back(state);
    }
  }
  for( auto const& state: add_list) {
    new_result.push_back(state);
  }
  return new_result;
} // end apply_operator()
