SRC = tuty.bI
SRC += symcore/symcore.bI symcore/Sym.bI

MODULE = $(notdir $(CURDIR))
.PHONY: exec
exec: ./exe.exe $(SRC)
	./exe.exe < $(MODULE).bI > $(MODULE).blog && tail $(TAIL) $(MODULE).blog
C = cpp.cpp ypp.tab.cpp lex.yy.c
H = hpp.hpp ypp.tab.hpp
CXXFLAGS += -I. -std=gnu++11 -DMODULE=\"$(MODULE)\" -DOS=\"$(OS)\"
./exe.exe: $(C) $(H) $(RES) Makefile
	$(CXX) $(CXXFLAGS) -o $@ $(C) $(RES)
ypp.tab.cpp: ypp.ypp
	bison $<
lex.yy.c: lpp.lpp
	flex $<
res.res: rc.rc
	windres $< -O coff -o $@

