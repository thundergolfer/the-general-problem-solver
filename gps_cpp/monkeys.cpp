#include "json.hpp"
#include "general_problem_solver.h"

#define DEBUG 0 // set to 1 for debugging

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
    op.add = jsonArrayToVec(obj["add"]);
    op.remove = jsonArrayToVec(obj["delete"]);
    ops.push_back(op);
  }
  if(DEBUG) {
    cout << "Op Actions : ";
    for( auto const& op: ops ) {
      cout << op.action + ", ";
    }
    cout << '\n';
  }
  vector<string> result_actions = gps(start, finish, ops);
  for( auto const& action : result_actions ) {
    cout << action << '\n';
  }

  return 0;
}
