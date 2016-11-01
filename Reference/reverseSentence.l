%{

#include <iostream> 
#define YYSTYPE std::string 
#include "reverseSentence.hpp"
#define verbose(x) ;//std::cout<<"LEX found "<<x<<"\n"

%}

%%

[A-Za-z]+		{verbose(yytext);yylval.assign(yytext);return WORD;}
" "				{verbose(yytext);yylval.assign(" ");return *yytext;}
"\n"			{verbose(yytext);return *yytext;}

%%

yywrap(){
	return 1;
}