prog: src/main.o src/Set.o
	g++ -g -w -o prog src/Set.o src/main.o

main.o: src/main.cc
	g++ -g -w -Wall -Wextra -Wwrite-strings -c src/main.cc

Set.o: src/Set.h src/Set.cc
	g++ -g -w -Wall -Wextra -Wwrite-strings -c src/Set.cc

clean:
	rm -f prog
	rm -f src/*.o