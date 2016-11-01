%{

#include <iostream>

int count;

%}

%%
[a-zB-Z0-9][a-zA-Z]*/[^a-zA-Z0-9]	{}
"A"[a-zA-Z][a-zA-Z]/[^a-zA-Z0-9]	{
										std::cout << yytext << "\n";
										count++;
									}
"\n"								{}
.									{}
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