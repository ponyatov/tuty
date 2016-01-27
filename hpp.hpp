#ifndef _H_TUTY
#define _H_TUTY

#include <iostream>
#include <cstdlib>
#include <cassert>
#include <vector>
#include <map>
using namespace std;

struct Sym {							// == Abstract Symbolic Type (AST) ==
	string tag;								// class / data tag
	string val;								// data value
	Sym(string,string);						// <T:V> \ constructors
	Sym(string);							// token /
	vector<Sym*> nest;						// \ nest[]ed
	void push(Sym*);						// /
	virtual string dump(int depth=0);		// \ dump object in string
	string tagval();						// <T:V> string
	string pad(int);						// /
	virtual Sym* eval();					// compute/evaluate
	virtual Sym* str();						// str(A) \ operators
	virtual Sym* at(Sym*);
	virtual Sym* eq(Sym*);
};
extern map<string,Sym*> env;				// \ == global environment ==
extern void env_init();						// /

extern void W(Sym*);						// \ == writers ==
extern void W(string);						// /

struct Directive:Sym { Directive(string); };// .directive

											// == scalars ==
struct Str:Sym { Str(string); };			// 'string'

											// == composites ==
struct List:Sym { List(); };

											// == functionals ==
struct Op:Sym { Op(string); Sym*eval(); };	// operator
typedef Sym*(*FN)(Sym*);
struct Fn:Sym { Fn(string,FN); FN fn; Sym*at(Sym*); };	// function

											// == fileio ==
struct Dir:Sym { Dir(Sym*); };				// directory
extern Sym* dir(Sym*);

											// lexer/parser intarface
extern int yylex();
extern int yylineno;
extern char* yytext;
#define TOC(C,X) { yylval.o = new C(yytext); return X; }
extern int yyparse();
extern void yyerror(string);
#include "ypp.tab.hpp"

#ifdef __MINGW32__
#include "win32.hpp"
#endif

#endif // _H_TUTY
