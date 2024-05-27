noflags =
errflags = -Wall -Wextra
linkedLibraries = -lmingw32
dependencies = Makefile superList.h test.cpp 

main: $(dependencies)
	g++ $(errflags) test.cpp -o test $(linkedLibraries)

test: main
	./test.exe