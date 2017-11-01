export function greeter(person: string) {
    return "Hello, " + person;
}

let user = "Jane Doe";


function achieveAll(states: string[], ops: Object[], goals: string[], goalStack: string[]) {
    return [];
}

export class Operator {
    add: string[];
    delete: string[];
    preconds: string[];

    constructor(add: string[],
                del: string[],
                preconds: string[]) {
        this.add = add;
        this.delete = del;
        this.preconds = preconds;
    }
}

export function applyOperator(operator: Operator,
                       states: string[],
                       operators: Operator[],
                       goal: string,
                       goalStack: string[]) {

    var result = achieveAll(states, operators, operator.preconds, [goal].concat(goalStack));
    if (!result.length) return [];
}
