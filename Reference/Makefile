all:	expression.exe
expression_lex.cpp:	expression.l
		flex  -oexpression_lex.cpp expression.l
expression.cpp:	expression.y 
		bison -d -oexpression.cpp expression.y
expression.o: expression.cpp expression.hpp
		g++ -Wunreachable-code -std=c++11 -Wextra -Wall -c expression.cpp -o expression.o
expression_lex.o: expression_lex.cpp expression.hpp
		g++ -Wunreachable-code -std=c++11 -Wextra -Wall -c expression_lex.cpp -o expression_lex.o
exptree.o: exptree.cpp exptree.h expression.hpp
		g++ -Wunreachable-code -std=c++11 -Wextra -Wall -c exptree.cpp -o exptree.o
expression.exe:	expression.o expression_lex.o exptree.o	
		g++ -o expression.exe expression.o expression_lex.o exptree.o 
clean:
		del expression_lex.cpp
		del expression.cpp
		del expression.hpp
		del expression.o
		del expression_lex.o
		del expression.exe
		del exptree.o