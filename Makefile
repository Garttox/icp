CC=g++
CXXFLAGS= -std=c++17 -Wall -Wextra

run: compile clean
	src/icp

compile: 
	qmake src/icp.pro -o src/Makefile
	$(MAKE) CXX=$(CC) -C src/ -o src/icp

clean:
	rm -rf src/debug src/release src/Makefile* build*/ doc src/ui_* src/*.o src/.qmake.stash

doxygen:
	doxygen Doxyfile

pack:
	zip -r 1_xtrlic02_xbedna77.zip src examples res doc README.txt Makefile Doxyfile