SRC = tuty.bI

MODULE = $(notdir $(CURDIR))
.PHONY: exec
exec: ./exe.exe $(SRC)
	./exe.exe < $(MODULE).bI > $(MODULE).blog && tail $(TAIL) $(MODULE).blog
C = ../dos/cpp.cpp ../dos/$(OS).cpp ypp.tab.cpp lex.yy.c
H = ../dos/hpp.hpp ../dos/$(OS).hpp ypp.tab.hpp
CXXFLAGS += -I../dos -std=gnu++11 -DMODULE=\"$(MODULE)\" -DOS=\"$(OS)\"
./exe.exe: $(C) $(H) $(RES) Makefile
	$(CXX) $(CXXFLAGS) -o $@ $(C) $(RES)
ypp.tab.cpp: ../dos/ypp.ypp
	bison $<
lex.yy.c: ../dos/lpp.lpp
	flex $<
res.res: rc.rc
	windres $< -O coff -o $@

.PHONY: clean
clean:
	rm -rf ./exe.exe *.*log ypp.tab.?pp lex.yy.c res.res

.PHONY: update
update:
	cp tuty/README.md README.md
	cp tuty/.gitignore .gitignore
	cp tuty/rc.rc rc.rc
	
