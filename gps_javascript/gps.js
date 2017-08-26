
var gps = ( initial_states, goal_states, operators ) => {
  console.log('what what!');
};

/**
* Achieve the goal state using means-ends analysis.
* Identifies an appropriate and applicable operator--one that contains the
* goal state in its add-list and has all its preconditions satisified.
* Applies the operator and returns the result.  Returns null if no such
* operator is found or infinite recursion is detected in the goal stack.
*/
var achieve = ( states, operators, goal, goalStack ) => {
  console.log(goalStack, `Achieving: ${goal}`);

  // Let's check to see if the state already holds before we do anything.
  if (states.indexOf(goal) >= 0) {
    return states;
  }

  // Prevent going in circles: look through the goal stack to see if the
  // specified goal appears there.  If so, then we are indirectly trying to
  // achieve goal while already in the process of achieving it.  For example,
  // while trying to achieve state A, we try to achieve state B--a precondition
  // for applying an appropriate operator.  However, to achieve B, we try to
  // satisfy the preconditions for another operator that contains A in its
  // preconditions.
  if (goalStack.indexOf(goal) >= 0) {
    return null;
  }

  operators.forEach(function (value) {
    // Is operator appropriate?  Look through its add-list to see if goal is there.
    if (op.add.indexOf(goal) < 0) {
      continue;
    }

    // Is op applicable?  Try to apply it--if one of its preconditions cannot
    // be satisifed, then it will return null.
    var result = applyOperator(op, states, operators, goal, goalStack);

    if (result): return result;
  });

  return null; // TODO check this
};


/**
* Applies operator and returns the resulting states.
* Achieves all of operator's preconditions and returns the states that hold
* after processing its add-list and delete-list.  If any of its preconditions
* cannot be satisfied, returns null.
*/
var applyOperator = ( operator, states, ops, goal, goalStack ) => {
  console.log(goalStack, `Considering: ${operation.action}`);

  var result = acheiveAll(states, ops, operation.preconds, [goal].concat(goalStack));

  if (!result) return null;

  console.log(goalStack, `Action: ${operator.action}`);

  // Merge the old state with the operator's add-list, filtering out the operator's delete list
  var addList = operator.add;
  var delList = operator.delete;

  var newState = result.filter(function(e) {
    return this.indexOf(e) < 0;
  }, delList);

  return newState.concat(addList);
};

export { gps };
