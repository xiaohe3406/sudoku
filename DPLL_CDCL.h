#include "common.h"
#include <stack>
#include <set>
#include <random>
#include <algorithm>

#define DECIDE 0
#define BACKTRACK 1
#define PROPAGATE 2
#define SAT 0
#define CONFLICT 1
#define OTHERS 2

// Ñ¡Ôñ
struct choice
{
	literal variable;
	int category;
	choice(literal v, int cat) :variable(v), category(cat) {
	}
};


class DPLL_CDCL {
public:
	
	DPLL_CDCL(const formula& phi) : phi(phi), cur_time(0),
		remaining_var(phi.num_variable),
		roots(phi.num_variable + 1, std::set<int>()),
		time_stamp(phi.num_variable + 1, 0),
		mp(phi.num_variable + 1, 0),
		visited(phi.num_variable + 1, 0)
	{
	}

	// Check if the formula is satisfiable.
	bool check_sat();

	// get the result
	model get_model();

	// propagate
	literal propagate();
	// Backtracking
	bool try_backjump();
	// make decision
	void make_decision(std::default_random_engine& random, std::bernoulli_distribution& d);
	// traverse the clauses and initialize some vector
	void traverse_clauses();

	void ShowResult(bool);

private:
	// cnf formula
	formula phi; 
	// the number of unassigned var
	int remaining_var;  
	// stack to store the choice
	std::stack<choice> st;  
	// stack to store the decision
	std::stack<int> decision_st;   
	// store the assignment of variables, 0 - unassigned, positive - true, negative - false
	std::vector<int> mp, visited;  
	// will be used to backtracking 
	std::vector<std::set<int>> roots;
	unsigned long long cur_time;
	std::vector<unsigned long long> time_stamp;
};

