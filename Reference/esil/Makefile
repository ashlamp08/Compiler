all:	compiler.exe
compiler_lex.cpp:	compiler.l
		flex  -ocompiler_lex.cpp compiler.l
compiler.cpp compiler.hpp:	compiler.y
		bison -d -ocompiler.cpp compiler.y
compiler.o: compiler.cpp syntaxTree.h symbolTable.h util.h typeTable.h
		g++ -g  -Wunreachable-code -std=c++11 -Wextra -Wall -c compiler.cpp -o compiler.o
compiler_lex.o: compiler_lex.cpp syntaxTree.h symbolTable.h compiler.hpp typeTable.h
		g++ -g  -Wunreachable-code -std=c++11 -Wextra -Wall -c compiler_lex.cpp -o compiler_lex.o
util.o: util.cpp util.h syntaxTree.h symbolTable.h compiler.hpp typeTable.h
		g++ -g  -Wunreachable-code -std=c++11 -Wextra -Wall -c util.cpp -o util.o
symbolTable.o: symbolTable.cpp symbolTable.h compiler.hpp typeTable.h
		g++ -g  -Wunreachable-code -std=c++11 -Wextra -Wall -c symbolTable.cpp -o symbolTable.o
syntaxTree.o: syntaxTree.cpp syntaxTree.h symbolTable.h compiler.hpp util.h typeTable.h
		g++ -g  -Wunreachable-code -std=c++11 -Wextra -Wall -c syntaxTree.cpp -o syntaxTree.o
typeTable.o: typeTable.cpp typeTable.h
		g++ -g  -Wunreachable-code -std=c++11 -Wextra -Wall -c typeTable.cpp -o typeTable.o
compiler.exe:	compiler.o compiler_lex.o syntaxTree.o symbolTable.o util.o typeTable.o
		g++ -g  -o compiler.exe compiler.o compiler_lex.o syntaxTree.o symbolTable.o util.o typeTable.o
clean:
		rm -f compiler_lex.cpp
		rm -f compiler.cpp
		rm -f compiler.hpp
		rm -f compiler.o
		rm -f util.o
		rm -f compiler_lex.o
		rm -f compiler.exe
		rm -f syntaxTree.o
		rm -f symbolTable.o
		rm -f typeTable.o

format:
		astyle --mode=c --options="/home/suraj/cpp_style.txt" compiler.l
		astyle --mode=c --options="/home/suraj/cpp_style.txt" compiler.y
		astyle --mode=c --options="/home/suraj/cpp_style.txt" compiler.y
		astyle --mode=c --options="/home/suraj/cpp_style.txt" symbolTable.cpp
		astyle --mode=c --options="/home/suraj/cpp_style.txt" symbolTable.h
		astyle --mode=c --options="/home/suraj/cpp_style.txt" syntaxTree.cpp
		astyle --mode=c --options="/home/suraj/cpp_style.txt" syntaxTree.h
