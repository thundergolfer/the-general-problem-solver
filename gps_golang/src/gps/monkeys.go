// Demonstrate the GPS Algorithm
package main

import (
        "fmt"
        "encoding/json"
        "strings"
        "log"
)

const jsonStream = `
  {
    "start": ["at door", "on floor", "has ball", "hungry", "chair at door"],
    "finish": ["not hungry"],
    "ops": [
	{
	    "action": "climb on chair",
	    "preconds": ["chair at middle room", "at middle room", "on floor"],
	    "add": ["at bananas", "on chair"],
	    "delete": ["at middle room", "on floor"]
	},
	{
	    "action": "push chair from door to middle room",
	    "preconds": ["chair at door", "at door"],
	    "add": ["chair at middle room", "at middle room"],
	    "delete": ["chair at door", "at door"]
	},
	{
	    "action": "walk from door to middle room",
	    "preconds": ["at door", "on floor"],
	    "add": ["at middle room"],
	    "delete": ["at door"]
	},
	{
	    "action": "grasp bananas",
	    "preconds": ["at bananas", "empty handed"],
	    "add": ["has bananas"],
	    "delete": ["empty handed"]
	},
	{
	    "action": "drop ball",
	    "preconds": ["has ball"],
	    "add": ["empty handed"],
	    "delete": ["has ball"]
	},
	{
	    "action": "eat bananas",
	    "preconds": ["has bananas"],
	    "add": ["empty handed", "not hungry"],
	    "delete": ["has bananas", "hungry"]
	}
    ]
}`

func main() {

    type Operators []struct{
      Action    string
      Preconds  []string
      Add       []string
      Delete    []string
    }

    type Problem_Domain struct{
      Start     []string
      Finish    []string
      Ops       Operators
    }

    var problem Problem_Domain // declare target struct for out json

    decoded := json.NewDecoder(strings.NewReader(jsonStream))
    if err := decoded.Decode(&problem); err != nil {
      log.Fatal(err)
    }

    var []string start  = problem.Start
    var []string finish = problem.Finish
    var Operators ops   = problem.Ops
    // Attempt to solve the problem
    var []string actions = gps(start, finish, ops):
    // Print out the actions
    for _, val := range actions {
      fmt.Println(val)
    }


}
