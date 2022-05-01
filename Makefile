CC=g++
CXXFLAGS= -std=c++17 -Wall -Wextra

run: compile clean
	src/icp

compile: 
	qmake src/icp.pro -o src/Makefile
	$(MAKE) CXX=$(CC) -C src/ -o src/icp

clean:
	rm -rf src/debug src/release src/Makefile* build*/ doc

doxygen:
	doxygen Doxyfile
