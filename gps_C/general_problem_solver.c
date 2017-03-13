#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_STR_LENGTH 20

struct BaseLink {
	BaseLink* next;
	BaseLink* prev;
	int typeId;
};


typedef struct{
	// TODO: implement 	
}Operator

// NOTE: The following is an implementation outline. All function descriptions
// are in effect placeholder. They are not syntactically valid nor programmatically valid

/* 
Find a sequence of operators that will achieve all of the goal states.
Returns a list of actions that will achieve all of the goal states, or
None if no such sequence exists.  Each operator is specified by an
action name, a list of preconditions, an add-list, and a delete-list.
*/
void gps( initial_states, goal_states, operators ) {

   	// To keep track of which operators have been applied, we add additional
   	// 'executing ...' states to each operator's add-list.  These will never be
   	// deleted by another operator, so when the problem is solved we can find
   	// them in the list of current states.
	char* prefix = "Executing ";

	// TODO: rest of function
}

/*
Achieve each state in goals and make sure they still hold at the end.
The goal stack keeps track of our recursion: which preconditions are we
trying to satisfy by achieving the specified goals?
*/
char** achieve_all( states, ops, goals, goal_stack ) {

	// We try to acheive each goal in the order they are given. 
	// If any one goal state cannot be acheived, then the problem cannot be solved

    // We must ensure that we haven't removed a goal state in the process of
    // solving other states--having done so is called the "prerequisite clobbers
    // sibling goal problem".


	return states;
}

/*
Achieve the goal state using means-ends analysis.
Identifies an appropriate and applicable operator--one that contains the
goal state in its add-list and has all its preconditions satisified.
Applies the operator and returns the result.  Returns None if no such
operator is found or infinite recursion is detected in the goal stack.
*/
char** achieve( states, operators, goal, goal_stack ) {

	// Let's check to see if the state already holds before we do anything

	// Prevent going in circles: look through the goal stack to see if the
    // specified goal appears there.  If so, then we are indirectly trying to
    // achieve goal while already in the process of achieving it.  For example,
    // while trying to achieve state A, we try to achieve state B--a precondition
    // for applying an appropriate operator.  However, to achieve B, we try to
    // satisfy the preconditions for another operator that contains A in its
    // preconditions.
}

/*
Applies operator and returns the resulting states.
Achieves all of operator's preconditions and returns the states that hold
after processing its add-list and delete-list.  If any of its preconditions
cannot be satisfied, returns None.
*/
char** apply_operator( operator, states, ops, goal, goal_stack ) {

	// Satisfy all of operator's preconditions

	// Merge the old states with operator's add-list, filering out the delete-list states
}