CC=g++
CXXFLAGS= -std=c++17 -Wall -Wextra

compile: clean
	qmake src/icp.pro -o src/Makefile
	$(MAKE) CXX=$(CC) -C src/ -o src/icp

run: compile
	cd ./src; ./icp

clean:
	rm -rf src/debug src/release src/Makefile* build*/ doc src/ui_* src/*.o src/.qmake.stash src/moc_* src/icp

doxygen:
	doxygen Doxyfile

pack: clean
	zip -r 1_xtrlic02_xbedna77.zip src examples res doc README.txt README.md Makefile Doxyfile