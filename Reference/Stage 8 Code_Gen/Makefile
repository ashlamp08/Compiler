all:	compiler.exe
compiler_lex.cpp:	compiler.l
		flex  -ocompiler_lex.cpp compiler.l
compiler.cpp:	compiler.y 
		bison -d -ocompiler.cpp compiler.y
compiler.o: compiler.cpp compiler.hpp
		g++ -Wunreachable-code -std=c++11 -Wextra -Wall -c compiler.cpp -o compiler.o
compiler_lex.o: compiler_lex.cpp compiler.hpp
		g++ -Wunreachable-code -std=c++11 -Wextra -Wall -c compiler_lex.cpp -o compiler_lex.o
symbolTable.o: symbolTable.cpp symbolTable.h compiler.hpp
		g++ -Wunreachable-code -std=c++11 -Wextra -Wall -c symbolTable.cpp -o symbolTable.o
syntaxTree.o: syntaxTree.cpp syntaxTree.h compiler.hpp symbolTable.h 
		g++ -Wunreachable-code -std=c++11 -Wextra -Wall -c syntaxTree.cpp -o syntaxTree.o
compiler.exe:	compiler.o compiler_lex.o syntaxTree.o symbolTable.o
		g++ -o compiler.exe compiler.o compiler_lex.o syntaxTree.o symbolTable.o 
clean:
		del compiler_lex.cpp
		del compiler.cpp
		del compiler.hpp
		del compiler.o
		del compiler_lex.o
		del compiler.exe
		del syntaxTree.o
		del symbolTable.o