all:	Interpreter.exe
Interpreter_lex.cpp:	Interpreter.l
		flex  -oInterpreter_lex.cpp Interpreter.l
Interpreter.cpp:	Interpreter.y 
		bison -d -oInterpreter.cpp Interpreter.y
Interpreter.o: Interpreter.cpp Interpreter.hpp
		g++ -Wunreachable-code -pedantic-errors -std=c++11 -Wextra -Wall -c Interpreter.cpp -o Interpreter.o
Interpreter_lex.o: Interpreter_lex.cpp Interpreter.hpp
		g++ -Wunreachable-code -pedantic-errors -std=c++11 -Wextra -Wall -c Interpreter_lex.cpp -o Interpreter_lex.o
syntaxTree.o: syntaxTree.cpp syntaxTree.h Interpreter.hpp
		g++ -Wunreachable-code -pedantic-errors -std=c++11 -Wextra -Wall -c syntaxTree.cpp -o syntaxTree.o
Interpreter.exe:	Interpreter.o Interpreter_lex.o syntaxTree.o
		g++ -o Interpreter.exe Interpreter.o Interpreter_lex.o syntaxTree.o
clean:
		del Interpreter_lex.cpp
		del Interpreter.cpp
		del Interpreter.hpp
		del Interpreter.o
		del Interpreter_lex.o
		del Interpreter.exe
		del syntaxTree.o