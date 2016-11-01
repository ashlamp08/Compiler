%{

#include <iostream>

int count;

%}

%%
"//".*"\n"						{
									std::cout << yytext << "\n";
								}
"/*"[]*"*/"						{
									std::cout << yytext << "\n___________\n";
								}
"\n"							{}
.								{}
%%

int yywrap() {
	return 1;
}

int main() {
	count = 0;
	yylex();
	std::cout<<count<<"\n";
	return 0;
}