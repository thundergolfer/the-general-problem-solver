#include "json.hpp"
#include "general_problem_solver.h"

// for convenience
using json = nlohmann::json;
using namespace std;

json problem = {
    {"start", {"at door", "on floor", "has ball", "hungry", "chair at door"}},
    {"finish", {"not hungry"}},
    {"ops", { // begin list
	{
	    {"action", "climb on chair"},
	    {"preconds", {"chair at middle room", "at middle room", "on floor"}},
	    {"add", {"at bananas", "on chair"}},
	    {"delete", {"at middle room", "on floor"}}
	},
	{
	    {"action", "push chair from door to middle room"},
	    {"preconds", {"chair at door", "at door"}},
	    {"add", {"chair at middle room", "at middle room"}},
	    {"delete", {"chair at door", "at door"}}
	},
	{
	    {"action", "walk from door to middle room"},
	    {"preconds", {"at door", "on floor"}},
	    {"add", {"at middle room"}},
	    {"delete", {"at door"}}
	},
	{
	    {"action", "grasp bananas"},
	    {"preconds", {"at bananas", "empty handed"}},
	    {"add", {"has bananas"}},
	    {"delete", {"empty handed"}}
	},
	{
	    {"action", "drop ball"},
	    {"preconds", {"has ball"}},
	    {"add", {"empty handed"}},
	    {"delete", {"has ball"}}
	},
	{
	    {"action", "eat bananas"},
	    {"preconds", {"has bananas"}},
	    {"add", {"empty handed", "not hungry"}},
	    {"delete", {"has bananas", "hungry"}}
	}
    } // end list
  } // end ops object
};

/**
 * Implicit conversion of json array to vector gives a
 * "ambiguous overloaded operator" error on my machine.
 */
vector<string> jsonArrayToVec( json j ) {
  vector<string> v = vector<string>();
  // iterate the array
  for (json::iterator it = j.begin(); it != j.end(); ++it) {
     v.push_back(*it);
  }

  return v;
}

int main() {
  vector<string> start = problem["start"];
  vector<string> finish = problem["finish"];
  vector<json>   ops_json = problem["ops"];
  vector<Operator> ops = vector<Operator>(); // init new vector
  for( json obj : ops_json ) {
    Operator op = {};
    op.action = obj["action"];
    op.preconds = jsonArrayToVec(obj["preconds"]);
    //op.add = obj.at("add");
    //op.remove = obj.at("delete");
    ops.push_back(op);
  }
  //for action in gps(start, finish, ops):
      //print action

  return 0;
}
