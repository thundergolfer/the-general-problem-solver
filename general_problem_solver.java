
import java.util.*;

/**
 * Find a sequence of operators from the set that will achieve all of the goal states.
 * Returns a list of actions that will achieve all of the goal states, or None if no such sequence exists.
 * Each operator is specified by an action name, a list of preconditions, an add-list, and a delete-list.
 */
public List<String> gps( List<String> initial_states, List<String> goal_states, Operator[] operators ) {

	String prefix = "Executing ";
	List<String> final_states = new ArrayList<String>();
	List<String> prefixed_final_states = new ArrayList<String>();

	for( Operator op : operators ) {
		op.add_to_add_list(prefix + op.action);
	}

	final_states = achieve_all( initial_states, operators, goal_states )

	if(final_states.isEmpty()) {
		return null;
	}
	else {
		for( String state: final_states) {
			if( state.startsWith(prefix)) {
				prefixed_final_states.add(state);
			}
		}
		return prefixed_final_states;
	}

} // end of gps()

/**
 * Acheiving Sub-goals
 * 
 */

/**
 *  Achieve each state in goals and make sure they still hold at the end.
 *  The goal stack keeps track of our recursion: which preconditions are we
 *  trying to satisfy by achieving the specified goals?
 */ 
public List<String> achieve_all( List<String> states,  Operator[] ops,
							 	 List<String> goals, List<String> goal_stack ) {

	states = new ArrayList<String>();
	// We try to acheive each goal in the order they are given. If any one goal state cannot
	// be acheived,  then the problem cannot be solved.
	for( String goal : goals ) {
		states = achieve(states, ops, goal, goal_stack);
		if(states.isEmpty()) {
			return null;
		}
	}

	// We must ensure that we haven't removed a goal state in the process of solving
	// other states-- have done so is called the "prerequisite clobbers sibling goal problem"
	for( String goal: goals ) {
		if(!states.contains(goal)) {
			return null;
		}
	}

	return states;
} // end of achieve_all()

/**
 *  Achieve the goal state using means-ends analysis.
 *  Identifies an appropriate and applicable operator--one that contains the
 *  goal state in its add-list and has all its preconditions satisified.
 *  Applies the operator and returns the result.  Returns None if no such
 *  operator is found or infinite recursion is detected in the goal stack.
 */
public List<String> achieve( List<String> states, Operator[] operators, String goal, List<String> goal_stack ) {

	List<String> result = new ArrayList<String>();

	// Check to see if the state already holds before we do anything
	if(states.containsAll(goal)) {
		return states;
	}

	// Prevent going in circles: look through the goal stack to see if the
    // specified goal appears there.  If so, then we are indirectly trying to
    // achieve goal while already in the process of achieving it.  For example,
    // while trying to achieve state A, we try to achieve state B--a precondition
    // for applying an appropriate operator.  However, to achieve B, we try to
    // satisfy the preconditions for another operator that contains A in its preconditions
    if(goal_stack.containsAll(goal)) {
    	return null;
    }

    for( Operator op: operators ) {
    	// Is op appropriate?  Look through its add-list to see if goal is there.
        if(!op.get_add_list().containsAll(goal)) {
            continue;
        }
        // Is op applicable?  Try to apply it--if one of its preconditions cannot
        // be satisifed, then it will return None.
        result = apply_operator(op, states, operators, goal, goal_stack);
        if(!result.isEmpty()) {
        	return result;
        }
    }
} // end of achieve()

/**
 * USING OPERATORS
 */

/**
 *   Applies operator and returns the resulting states.
 *   Achieves all of operator's preconditions and returns the states that hold
 *   after processing its add-list and delete-list.  If any of its preconditions
 *   cannot be satisfied, returns None.
 */
public List<String> apply_operator( Operator operator, List<String> states, Operator[] ops,
									List<String> goals, List<String> goal_stack ) {

	List<String> result = new ArrayList<String>();
	List<String> new_states = new ArrayList<String>();
	// add all of goal's states into goal stack
	for( String goal : goals ) {
		goal_stack.add(goal);
	}
	// Satisfy all of operator's preconditions
	result = achieve_all(states, ops, operator.get_preconds, goal_stack);
	if(result.isEmpty()) {
		return null;
	}

	// Merge the old states with operator's add-list, filerting out delete-list.
	ArrayList<String> add_list    = operator.get_add_list();
	ArrayList<String> delete_list = operator.get_del_list();

	// Remove states from result which are in the delete list
	for( String state: result ) {
		if(!delete_list.contains(state)) {
			new_states.add(state);
		}
	}
	// Add states from add list to result
	for( String state: add_list ) {
		new_states.add(state);
	}

	return new_states;

} // end of apply_operator()

/**
 * A class to hold the data required of an operator in the GPS algorithm.
 */
class Operator {
	public String action;
	private ArrayList<String> preconditions;
	private ArrayList<String> add_list;
	private ArrayList<String> del_list;

	public Operator( String action_name, ArrayList<String> preconditions,
					 ArrayList<String> add_list, ArrayList<String> del_list ) {
		this.action = action_name;
		this.preconditions = preconditions;
		this.add_list = add_list;
		this.del_list = del_list;
	}

	public List<String> get_preconds() {
		return preconditions;
	}

	public List<String> get_add_list() {
		return add_list;
	}

	public boolean add_to_add_list( String state ) {
		return add_list.add(state);
	}

	public boolean remove_from_add_list( String state ) {
		boolean removed;
		removed = add_list.remove(state); 
		if(removed) { return removed; }
		else 		{ return false;   }
		// this could be awkward code
	}

	public List<String> get_del_list() {
		return del_list;
	}
}