#ifndef _H_TUTY
#define _H_TUTY

#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
using namespace std;

struct Sym {							// == Abstract Symbolic Type (AST) ==
	string tag;							// class / data tag
	string val;							// data value
	Sym(string,string);					// <T:V> \ constructors
	Sym(string);						// token /
	vector<Sym*> nest;					// \ nest[]ed
	void push(Sym*);					// /
	virtual string dump(int depth=0);	// \ dump object in string
	string tagval();					// <T:V> string
	string pad(int);					// /
	virtual Sym* eval();				// compute/evaluate
};
extern map<string,Sym*> env;			// \ == global environment ==
extern void env_init();					// /

extern void W(Sym*);					// \ == writers ==
extern void W(string);					// /

struct Directive:Sym { Directive(string); };// .directive

										// == scalars ==
struct Str:Sym { Str(string); };		// 'string'

										// == functionals ==
struct Op:Sym { Op(string); };			// operator

										// lexer/parser intarface
extern int yylex();
extern int yylineno;
extern char* yytext;
#define TOC(C,X) { yylval.o = new C(yytext); return X; }
extern int yyparse();
extern void yyerror(string);
#include "ypp.tab.hpp"

#endif // _H_TUTY
