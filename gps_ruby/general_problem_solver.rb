## General Problem Solver
# CREDIT TO -> Daniel Connelly @ https://github.com/dhconnelly
require 'logger'

# Runs a subprocess and applies handlers for stdout and stderr
# Params:
# +command+:: command line string to be executed by the system
# +outhandler+:: +Proc+ object that takes a pipe object as first and only param (may be nil)
# +errhandler+:: +Proc+ object that takes a pipe object as first and only param (may be nil)
def gps(initial_states, goal_states, operators)

  # To keep track of which operators have been applied, we add additional
  # 'executing ...' states to each operator's add-list.  These will never be
  # deleted by another operator, so when the problem is solved we can find
  # them in the list of current states.
  prefix = 'Executing '

  operators.each do |operator|
    operator['add'].append(prefix + operator['action'])
  end

  final_states = achieve_all(initial_states, operatos, goal_states, [])

  if !final_states
    nil
  else
    final_states.select do |state|
      state.start_with?(prefix)
    end
  end
end

### ACHIEVING SUBGOALS ###

# Achieve each state in goals and make sure they still hold at the end.
# The goal stack keeps track of our recursion: which preconditions are we
# trying to satisfy by achieving the specified goals?
def achieve_all(states, ops, goals, goal_stack)

  # We try to achieve each goal in the order they are given.  If any one
  # goal state cannot be achieved, then the problem cannot be solved.
  goals.each do |goal|
    states = achieve(states, ops, goal, goal_stack)
    if !states
      return nil
    end
  end

  # We must ensure that we haven't removed a goal state in the process of
  # solving other states--having done so is called the "prerequisite clobbers
  # sibling goal problem".
  goals.each do |goal|
    if !states.include? goal
      return nil
    end
  end
  states
end

# Achieve the goal state using means-ends analysis.
# Identifies an appropriate and applicable operator--one that contains the
# goal state in its add-list and has all its preconditions satisified.
# Applies the operator and returns the result.  Returns None if no such
# operator is found or infinite recursion is detected in the goal stack.
def achieve(states, operators, goal, goal_stack)

  # Let's check to see if the state already holds before we do anything.
  if states.include? goal
    return states
  end

  # Prevent going in circles: look through the goal stack to see if the
  # specified goal appears there.  If so, then we are indirectly trying to
  # achieve goal while already in the process of achieving it.  For example,
  # while trying to achieve state A, we try to achieve state B--a precondition
  # for applying an appropriate operator.  However, to achieve B, we try to
  # satisfy the preconditions for another operator that contains A in its
  # preconditions.
  if goal_stack.include? goal
    return nil
  end

  operators.each do |op|
    # Is op appropriate?  Look through its add-list to see if goal is there.
    if !op['add'].include?(goal)
      next
    end

    # Is op applicable?  Try to apply it--if one of its preconditions cannot
    # be satisifed, then it will return None.
    result = apply_operator(op, states, operators, goal, goal_stack)
    if result
      return result
    else
      next
    end
  end
end

## Using operators

#  Applies operator and returns the resulting states.
#  Achieves all of operator's preconditions and returns the states that hold
#  after processing its add-list and delete-list.  If any of its preconditions
# cannot be satisfied, returns None.
def apply_operator(operator, states, ops, goal, goal_stack)

  # Satify all of operator's preconditions
  result = achieve_all(states, ops, operator['preconds'], [goal] + goal_stack)
  if !result
    return nil
  end

  # Merge the old states with operator's add-list, filtering out delete-list
  add_list, delete_list = operator['add'], operator['delete']
  result = result.select do |state|
    !delete_list.include?(state)
  end
  return result.concat add_list
end

### HELPER FUNCTION ###
def debug(level, msg)
  logger.debug(" %s %s" % [" " * level, msg])
end
