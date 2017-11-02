export function greeter(person: string) {
    return "Hello, " + person;
}

let user = "Jane Doe";


export function gps(initialStates: string[], goalStates: string[], operators: Operator[]) {
    var prefix = 'Executing ';
    operators.forEach(function(operator: Operator) {
        operator.add.push(prefix + operator.action);
    });

    var finalStates = achieveAll(initialStates, operators, goalStates, []);

    if (!finalStates.length) return false;

    var actions = finalStates.filter(function(elem: string) {
        return elem.startsWith(prefix);
    });

    return actions;
}


function achieveAll(states: string[], ops: Operator[], goals: string[], goalStack: string[]) {
    goals.forEach(function (goal: string) {
        states = achieve(states, ops, goal, goalStack);
        if (!states.length) return <string[]>[];
    });

    goals.forEach(function(goal: string) {
      if (states && states.indexOf(goal) < 0) return [];
    });

    return states;
}

export class Operator {
    add: string[];
    delete: string[];
    preconds: string[];
    action: string;

    constructor(add: string[],
                del: string[],
                preconds: string[],
                action: string) {
        this.add = add;
        this.delete = del;
        this.preconds = preconds;
        this.action = action;
    }
}

function achieve(states: string[], operators: Operator[], goal: string, goalStack: string[]) {
  // Let's check to see if the state already holds before we do anything.
  if (states && states.indexOf(goal) >= 0) {
      return states;
  }

  if (goalStack.indexOf(goal) >= 0) { // is this a bug? What if the index of goal is 0 AND 4?
      return <string[]>[];
  }

  var result = <string[]>[];

  for(var op of operators) {
    if (op.add.indexOf(goal) < 0) {
      continue
    }

    var result: string[] = applyOperator(op, states, operators, goal, goalStack);

    if (!!result.length) return result;
  }

  return <string[]>[];
}

export function applyOperator(operator: Operator,
                       states: string[],
                       operators: Operator[],
                       goal: string,
                       goalStack: string[]) {

    var result = achieveAll(states, operators, operator.preconds, [goal].concat(goalStack));
    if (!result.length) return [];

    let addList = operator.add;
    let delList = operator.delete;

    var newState = result.filter(function(elem: string) {
      return this.indexOf(elem) < 0;
    }, delList);

    return newState.concat(addList);
}
