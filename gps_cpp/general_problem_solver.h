#ifndef GPS_H
#define GPS_H

#include <iostream>
#include <vector>
#include <stack>
#include <string>

struct Operator {
  std::string action;
  std::vector<std::string> preconds;
  std::vector<std::string> add;
  std::vector<std::string> remove;
};

/**
 * Find a sequence of operators that will achieve all of the goal states.
 *
 * Returns a list of actions that will achieve all of the goal states, or
 * None if no such sequence exists. Each operator is specified by an action name,
 * list of preconditions, and add-list, and a delete-list.
 */
std::vector<std::string> solve( std::vector<std::string> init_states,
                      std::vector<std::string> goal_states,
                      std::vector<Operator> operators );

/**
 * Achieve each state in goals and make sure they still hold at then end.
 *
 * The goal stack keeps track of our recursion: which preconditions are we
 * trying to satisfy by achieving the specified goals?
 */
std::vector<std::string> achieve_all( std::vector<std::string> states,
                            std::vector<Operator> ops,
                            std::vector<std::string> goals,
                            std::stack<std::string> goal_stack );
/**
 * Achieve the goal state using means-ends analysis.
 *
 * Identifies an appropiate and applicable operator --one that contains the goal
 * state in its add-list and has all its preconditions satisfied.
 * Applies the operator and returns the result. Returns None if no such
 * operator is found or infinite recursion is detected in the goal stack.
 */
std::vector<std::string> achieve( std::vector<std::string> states,
                        std::vector<Operator> operators,
                        std::string goal,
                        std::stack<std::string> goal_stack );

// USING OPERATORS //

/**
 * Applies operator and returns the resulting states.
 *
 * Achieves all of the operator's preconditions and returns the states that hold
 * after processing its add-list and delete-list. If any of its preconditions
 * cannot be satisfied, returns None.
 *
 */
std::vector<std::string> apply_operator( Operator op,
                               std::vector<std::string> states,
                               std::vector<Operator> ops,
                               std::string goal,
                               std::stack<std::string> goal_stack );

#endif
