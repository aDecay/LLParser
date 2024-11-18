all: compiler.out

compiler.out: ./obj/main.o ./obj/lex_analyzer.o ./obj/rd_parser.o
	g++ -o compiler.out ./obj/main.o ./obj/lex_analyzer.o ./obj/rd_parser.o

./obj/main.o: ./include/lex_analyzer.h ./include/rd_parser.h ./src/main.cpp
	g++ -c -o ./obj/main.o ./src/main.cpp

./obj/lex_analyzer.o: ./include/lex_analyzer.h ./src/lex_analyzer.cpp
	g++ -c -o ./obj/lex_analyzer.o ./src/lex_analyzer.cpp

./obj/rd_parser.o: ./include/lex_analyzer.h ./include/rd_parser.h ./src/rd_parser.cpp
	g++ -c -o ./obj/rd_parser.o ./src/rd_parser.cpp

clean:
	rm -rf ./obj/*.o compiler.out