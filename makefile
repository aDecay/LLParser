all: compiler.out

compiler.out: ./obj/main.o ./obj/lex_analyzer.o
	g++ -o compiler.out ./obj/main.o ./obj/lex_analyzer.o

./obj/main.o: ./include/lex_analyzer.h ./src/main.cpp
	g++ -c -o ./obj/main.o ./src/main.cpp

./obj/lex_analyzer.o: ./include/lex_analyzer.h ./src/lex_analyzer.cpp
	g++ -c -o ./obj/lex_analyzer.o ./src/lex_analyzer.cpp

clean:
	rm -rf ./obj/*.o compiler.out