#include "hpp.hpp"
#define YYERR "\n\n"<<yylineno<<":"<<msg<<"["<<yytext<<"]\n\n"
void yyerror(string msg) { cout<<YYERR; cerr<<YYERR; exit(-1); }
int main() { env_init(); return yyparse(); }

Sym::Sym(string T, string V) 	{ tag=T; val=V; }
Sym::Sym(string V):Sym("sym",V) { }

void Sym::push(Sym*o)			{ nest.push_back(o); }

void W(Sym*o) { cout << o->dump(); }
void W(string s) { cout << s; }

string Sym::tagval()	{ return "<"+tag+":"+val+">"; }
string Sym::pad(int n)	{ string S; for (int i=0;i<n;i++) S+="\t"; return S; }
string Sym::dump(int depth) {
	string S = "\n"+pad(depth)+tagval();
	return S; }

Sym* Sym::eval() { Sym*E = env[val]; if (E) return E; else return this; }

														// == directive ==
Directive::Directive(string V):Sym("",V) {
	while (val.size() && (val[0]!=' ' && val[0]!='\t')) {
		tag += val[0]; val.erase(0,1); }
	while (val.size() && (val[0]==' ' || val[0]=='\t')) {
		               val.erase(0,1); }
}

														// == functionals ==
Op::Op(string V):Sym("op",V) {}							// operator


map<string,Sym*> env;
void env_init() {
	// ---- metainformation ----
	env["MODULE"]	=new Sym(MODULE);
	env["OS"]		=new Sym(OS);
}

