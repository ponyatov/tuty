#include "hpp.hpp"
#define YYERR "\n\n"<<yylineno<<":"<<msg<<"["<<yytext<<"]\n\n"
void yyerror(string msg) { cout<<YYERR; cerr<<YYERR; exit(-1); }
int main() { env_init(); return yyparse(); }

Sym::Sym(string T, string V) 	{ tag=T; val=V; }
Sym::Sym(string V):Sym("sym",V) { }

void Sym::push(Sym*o)			{ nest.push_back(o); }

void W(Sym*o) { cout << o->dump(); }
void W(string s) { cout << s; }

string Sym::tagval() { return "<"+tag+":"+val+">"; }	// <T:V> header string
string Sym::dump(int depth) {							// dump as text
	string S = "\n" + pad(depth) + tagval();
//	for (auto pr=par.begin(),e=par.end();pr!=e;pr++)	// par{}ameters
//		S += ","+pr->first+":"+pr->second->tagval();
	for (auto it=nest.begin(),e=nest.end();it!=e;it++)	// nest[]ed
		S += (*it)->dump(depth+1);
	return S; }
string Sym::pad(int n) {								// pad as tree
	string S;
	for(int i=0;i<n-1;i++) S+="|   ";
	if (n) S+="\\___";
	return S; }

Sym* Sym::eval() {
	Sym*E = env[val]; if (E) return E;					// env[] lookup
	for (auto it=nest.begin(),e=nest.end();it!=e;it++)	// nest[]ed
		(*it) = (*it)->eval();
	return this; }

Sym* Sym::str() 	{ return new Str(val); }
Sym* Sym::eq(Sym*o)	{ env[val]=o; return o; }
Sym* Sym::at(Sym*o)	{ push(o); return this; }

														// == directive ==
Directive::Directive(string V):Sym("",V) {
	while (val.size() && (val[0]!=' ' && val[0]!='\t')) {
		tag += val[0]; val.erase(0,1); }
	while (val.size() && (val[0]==' ' || val[0]=='\t')) {
		               val.erase(0,1); }
}

														// == scalars ==
Str::Str(string V):Sym("str",V) {}

														// == composites ==
List::List():Sym("[","]") {}

														// == functionals ==
Op::Op(string V):Sym("op",V) {}							// operator
Sym* Op::eval() {
	if (val=="=") { assert(nest.size()==2); return nest[0]->eq(nest[1]); }
	Sym::eval();
	if (nest.size()==2) {
		if (val=="@") return nest[0]->at(nest[1]);
	}
	return this;
}

Fn::Fn(string V,FN F):Sym("fn",V)	{ fn=F; }
Sym* Fn::at(Sym*o)					{ return fn(o); }

														// == fileio ==
Sym* dir(Sym*o) { return new Dir(o); }

map<string,Sym*> env;
void env_init() {
	// ---- metainformation ----
	env["MODULE"]	=new Sym(MODULE);
	env["OS"]		=new Sym(OS);
	// -- fileio --
	env["dir"]		=new Fn("dir",dir);
}

