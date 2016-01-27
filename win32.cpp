#include "hpp.hpp"

														// == fileio ==
Dir::Dir(Sym*o):Sym("dir",o->str()->val) { mkdir(val.c_str()); }

