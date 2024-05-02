#pragma once

#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>


// A literal is a atomic formula (that contains a variable). 
typedef int literal;
#define POSITIVE(x) ((x) > 0)
#define NEGATIVE(x) ((x) < 0)
#define VAR(x) (((x) > 0) ? (x) : (-(x)))

// A clause is a list of literals .
typedef std::vector<literal> clause;

// A formula is a list of clauses.
// We also specify the total number of variables, as some of them may not occur in any clause
struct formula {
    int num_variable;
    std::vector<clause> clauses;

    formula(int n, const std::vector<clause>& clauses) : num_variable(n), clauses(clauses) {}
};

// A satisfying model (interpretation).
// e.g. `model[i] = false` means variable `i` is assigned to false.
typedef std::unordered_map<int, bool> model;
