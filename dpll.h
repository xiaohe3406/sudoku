#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <vector>

#include "slist.hpp"

using namespace std;

#define NegSymbol "¬"
#define AndSymbol "∧"
#define OrSymbol "∨"
#define WideSpace "　"

typedef long long ll;
typedef unsigned long long llu;

class Literal;
class Clause;
class CNF;
class Occur;
class AvAtom;

/**
 * 结构体：文字
 * 包括命题变号及其否定（如 a 或 ¬a ）
 */
class Literal {
public:
	llu index;
	bool neg;
	CNF* cnf;
	node<Clause>* cl;
	node<Occur>* oc;

public:
	Literal(CNF* _cnf, string s, bool _neg);
	string str();
	void RemoveOccurrence();
};

/**
 * 结构体：子句（析取式）
 * 形如 a∨b∨c∨...∨z
 * 包含一个文字链表
 */
class Clause {
public:
	slist<Literal>* lt;
	CNF* cnf;

public:
	Clause(CNF* _cnf);
	string str();
};

/**
 * 结构体：文字的出现
 * 为可用变量列表中的元素
 * 指向对应的 Literal
 */
class Occur {
public:
	node<Literal>* lit;

public:
	Occur(node<Literal>* _lit) { this->lit = _lit; }
};

/**
 * 结构体：可用变量（命题变号）
 * 包含该命题变号的出现（Occurence）链表
 */
class AvAtom {
public:
	llu index;
	slist<Occur>* oc;
	CNF* cnf;

public:
	AvAtom(CNF* _cnf, llu i);
};

/**
 * 结构体：公式集（析取式的合取式）
 * 形如 (a∨b∨...∨z)∧(d∨e∨...∨f)∧...∧(g∨...∨i)
 * 包含一个子句链表
 */
class CNF {
public:
	map<string, llu> Dict;
	vector<string> Atoms;
	vector<ll> scheme;
	llu AtomN = 0;
	llu VarNum = 0;
	slist<Clause> CL;
	slist<AvAtom> AVA;
	vector<node<AvAtom>*> avAtoms;
	rmRecorder<Literal> Rec_Literal;
	rmRecorder<Clause> Rec_Clause;
	rmRecorder<Occur> Rec_Occur;
	rmRecorder<AvAtom> Rec_AvAtom;
	stack<list<ll>> Rec_assign;
	bool Solve;

public:
	CNF()
	{
		this->CL.regRec(&this->Rec_Clause);
		this->AVA.regRec(&this->Rec_AvAtom);
	}
	void read(string& filename);
	void show();
	void create(string& filename);
	string str();
	string occurStr();
	string schemeStr();
	void removeLiteral(node<Clause>* cl, node<Literal>* lit);
	void removeClause(node<Clause>* cl);
	ll AssignLiteralIn(node<Clause>* cl, node<Literal>* unit);
	bool PureLiteralAssign();
	bool UnitPropagate();
	void nextLayer();
	void backtrack();
	bool containEmptyClause = false;
	bool DPLL(bool disableSimp);
};