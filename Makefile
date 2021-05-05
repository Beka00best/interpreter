all: bin bin/const.o bin/lexem.o bin/lexical.o bin/syntax.o bin/semantic.o bin/main 

bin:
	mkdir bin -p

bin/const.o: src/const.cpp
	g++ -I./include -c src/const.cpp -o bin/const.o 

bin/lexem.o: src/lexem.cpp
	g++ -I./include -c src/lexem.cpp -o bin/lexem.o 

bin/lexical.o: src/lexical.cpp
	g++ -I./include -c src/lexical.cpp -o bin/lexical.o 

bin/syntax.o: src/syntax.cpp
	g++ -I./include -c src/syntax.cpp -o bin/syntax.o 

bin/semantic.o: src/semantic.cpp
	g++ -I./include -c src/semantic.cpp -o bin/semantic.o 

bin/main: src/main.cpp
	g++ -I./include src/main.cpp bin/const.o bin/lexem.o bin/lexical.o bin/syntax.o bin/semantic.o -o bin/main 

clean:
	rm bin/const.o bin/lexem.o bin/lexical.o bin/syntax.o bin/semantic.o bin/main
	rmdir bin

