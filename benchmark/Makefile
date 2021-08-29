prog: src/main.o src/Set.o src/List.o
	g++ -g -w -o prog src/Set.o src/List.o src/main.o

main.o: src/main.cc
	g++ -g -w -Wall -Wextra -Wwrite-strings -c src/main.cc

Set.o: src/Set.h src/Set.cc
	g++ -g -w -Wall -Wextra -Wwrite-strings -c src/Set.cc

Set.o: src/List.h src/List.cc
	g++ -g -w -Wall -Wextra -Wwrite-strings -c src/List.cc

clean:
	rm -f prog
	rm -f src/*.o