import { gps, Operator } from './gps';
import * as example from '../examples/monkeys.json';

// let operator =  new Operator(['yes'], ['no'], ['ready']);

var operators: Operator[] = [];
for (var op of (<any>example).ops) {
  let op_ = new Operator(op.add, op.delete, op.preconds, op.action);
  operators.push(op_)
}

let result = gps((<any>example).start, (<any>example).finish, operators);

console.log('Result: ');
console.log(result);
