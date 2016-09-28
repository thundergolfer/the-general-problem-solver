package main

import "fmt" // 'format' package
import "encoding/json" // might not be needed

type Operators []struct{
  Action    string
  Preconds  []string
  Add       []string
  Delete    []string
}

func main() {
    fmt.Printf("hello, world\n")
}

// Find a sequence of operators that will achieve all of the goal states.
// Each operator is specified by an action name, a list of preconditions,
// and add-list, and a delete-list.
// Returns a list of actions that will achieve all of the goal states, or
// None if no such sequence exists.
func gps( initial_states []string, goal_states []string, operators []Operator ) {

  // To keep track of which operators have been applied, we add additional
  // 'executing ...' states to each operator's add-list.  These will never be
  // deleted by another operator, so when the problem is solved we can find
  // them in the list of current states.
  var string prefix = "Executing "
  for _, operator := range operators {
    operator.Add = append( operator.Add, prefix + operator.Action )
  }

  var []string final_states = achieve_all(initial_states, operators, goal_states, []string{} )
  if( !final_states ) {
    return nil
  }
  // filter the final_states list to find the "Executing X" states, which are actually actions
  // TODO 
}

/* ACHIEVING SUBGOALS */

// Achieve each state in goals and make sure they still hold at the end.
// The goal stack keeps track of our recursion: which preconditions are we
// trying to satisfy by achieving the specified goals?
func achieve_all( states []string, ops []Operator, goals []string, goal_stack []string ) {

}

// Achieve the goal state using means-ends analysis.
// Identifies an appropiate and applicable operator -- one that contains the
// goal state in its add-list and has all its preconoditions satisfied.
// Applies the operator and returns the result.
// Returns None if no such operator is found or infinite recursion is detected in goal stack
func achieve( states []string, ops []Operator, goal string /* Goal Stack !!! */) {

}

// Applies operator and returns the resulting states.
// Achieves all of operator's preconditions and returns the states that hold
// after processing its add-list and delete-list. If an of its preconditions
// cannot be satisfied, returns None.
func apply_operator( operator Operator, states []string, ops []Operator, string goal /* GOALSTACK !! */) {

}
