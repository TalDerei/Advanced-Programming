prog: src/main.o src/Set.o src/List.o src/SortedVector.o src/UnsortedVector.o
	g++ -g -w -o prog src/Set.o src/List.o src/SortedVector.o src/UnsortedVector.o src/main.o

main.o: src/main.cc
	g++ -g -w -Wall -Wextra -Wwrite-strings -c src/main.cc

Set.o: src/Set.h src/Set.cc
	g++ -g -w -Wall -Wextra -Wwrite-strings -c src/Set.cc

List.o: src/List.h src/List.cc
	g++ -g -w -Wall -Wextra -Wwrite-strings -c src/List.cc

SortedVector.o: src/SortedVector.h src/SortedVector.cc
	g++ -g -w -Wall -Wextra -Wwrite-strings -c src/SortedVector.cc

UnsortedVector.o: src/UnsortedVector.h src/UnsortedVector.cc
	g++ -g -w -Wall -Wextra -Wwrite-strings -c src/UnsortedVector.cc

clean:
	rm -f prog
	rm -f src/*.o