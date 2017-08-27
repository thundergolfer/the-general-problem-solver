
/**
* Find a sequence of operators that will achieve all of the goal states.
* Returns a list of actions that will achieve all of the goal states, or
* None if no such sequence exists.  Each operator is specified by an
* action name, a list of preconditions, an add-list, and a delete-list.
*/
var gps = ( initialStates, goalStates, operators ) => {
  // To keep track of which operators have been applied, we add additional
  // 'executing ...' states to each operator's add-list.  These will never be
  // deleted by another operator, so when the problem is solved we can find
  // them in the list of current states.
  var prefix = 'Executing ';
  operators.forEach(function (operator) {
    operator.add.push(prefix + operator.action);
  });

  var finalStates = achieveAll(initialStates, operators, goalStates, []);

  if (!finalStates.length) return false;

  var actions = finalStates.filter(function(elem) {
    return elem.startsWith(prefix);
  });

  return actions;
};

/**
* Achieve each state in goals and make sure they still hold at the end.
* The goal stack keeps track of our recursion: which preconditions are we
* trying to satisfy by achieving the specified goals?
*/
var achieveAll = ( states, ops, goals, goalStack ) => {
  // We try to achieve each goal in the order they are given.  If any one
  // goal state cannot be achieved, then the problem cannot be solved.
  goals.forEach(function (goal) {
    states = achieve(states, ops, goal, goalStack);
    debugger;
    if (!states.length) return [];
  });

  // We must ensure that we haven't removed a goal state in the process of
  // solving other states--having done so is called the "prerequisite clobbers
  // sibling goal problem".
  goals.forEach(function (goal) {
    if (states && states.indexOf(goal) < 0) return [];
  });

  return states;
};

/**
* Achieve the goal state using means-ends analysis.
* Identifies an appropriate and applicable operator--one that contains the
* goal state in its add-list and has all its preconditions satisified.
* Applies the operator and returns the result.  Returns null if no such
* operator is found or infinite recursion is detected in the goal stack.
*/
var achieve = ( states, operators, goal, goalStack ) => {
  // Let's check to see if the state already holds before we do anything.
  if (states && states.indexOf(goal) >= 0) {
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
    return [];
  }

  var result = [];

  for(var op of operators) {
    // Is operator appropriate?  Look through its add-list to see if goal is there.
    if (op.add.indexOf(goal) < 0) {
      continue
    }

    // Is op applicable?  Try to apply it--if one of its preconditions cannot
    // be satisifed, then it will return null.
    result = applyOperator(op, states, operators, goal, goalStack);

    if (!!result.length) return result;
  }

  return []; // TODO check this
};


/**
* Applies operator and returns the resulting states.
* Achieves all of operator's preconditions and returns the states that hold
* after processing its add-list and delete-list.  If any of its preconditions
* cannot be satisfied, returns null.
*/
var applyOperator = ( operator, states, ops, goal, goalStack ) => {
  // console.log('Goal stack: ', goalStack, `Considering: ${operator.action}`);

  var result = achieveAll(states, ops, operator.preconds, [goal].concat(goalStack));
  if (!result.length) return [];

  // Merge the old state with the operator's add-list, filtering out the operator's delete list
  var addList = operator.add;
  var delList = operator.delete;

  var newState = result.filter(function(e) {
    return this.indexOf(e) < 0;
  }, delList);

  return newState.concat(addList);
};

export { gps };
