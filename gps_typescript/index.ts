import { greeter, applyOperator, Operator } from './gps';
import * as example from './examples/monkeys.json';


let user = "Jane Doe";

console.log(greeter(user));

let operator =  new Operator(['yes'], ['no'], ['ready']);

console.log(
  applyOperator(operator, ['ready', 'banana'], [operator], 'yes', [])
);
