CC=g++
CXXFLAGS= -std=c++17 -Wall -Wextra

compile: clean
	qmake src/icp.pro -o src/Makefile
	$(MAKE) CXX=$(CC) -C src/ -o src/icp

run: compile
	cd ./src; ./icp

clean:
	rm -rf 1-xtrlic02-xbedna77.zip src/debug src/release src/Makefile* build*/ doc src/ui_* src/*.o src/.qmake.stash src/moc_* src/icp

doxygen:
	doxygen Doxyfile

pack: clean
	zip -r src examples res doc README.txt README.md Makefile Doxyfile