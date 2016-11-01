%{
 
/*
1.Request input of an even and an odd number
2.indicate input characteristic : Even/Odd
3.check for input's correctness and print result
*/
 
#include <iostream>
int wordCount; 
int charCount; 
int lineCount; 
%}
 
%%

[a-zA-Z]+	{
//				std::cout<<"Word Found = "<<yytext<<"\n";
				wordCount++;
				charCount+=yyleng;
			}
"\n"		{
//				std::cout<<"NewLine\n";
				lineCount++;
				charCount++;
			}
.			{
//				std::cout<<"Other = "<<yytext<<"\n";
				charCount++;
			}
%%
 
int yywrap()
{
  return 1;
}
 
int main()
{
	wordCount = 0;
	lineCount = 1;
	charCount = 0;
	
  yylex();
  std::cout<<"wordCount = "<<wordCount<<"\n";
  std::cout<<"lineCount = "<<lineCount<<"\n";
  std::cout<<"charCount = "<<charCount<<"\n";
  return 0;
}