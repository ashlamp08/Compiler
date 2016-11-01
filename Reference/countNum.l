%{
 
/*
1.Request input of an even and an odd number
2.indicate input characteristic : Even/Odd
3.check for input's correctness and print result
*/
 
#include <iostream>
int intCount; 
int floatCount; 
%}
 
%%

[-+]?[0-9]+"."[0-9]+	{
					std::cout<<"float Found = "<<yytext<<"\n";
					floatCount++;
				}
[-+]?[0-9]+	{
					std::cout<<"int Found = "<<yytext<<"\n";
					intCount++;
				}

"\n"			{}
.			{}
%%
 
int yywrap()
{
  return 1;
}
 
int main()
{
	intCount = 0;
	floatCount = 0;
	
  yylex();
  std::cout<<"intCount = "<<intCount<<"\n";
  std::cout<<"floatCount = "<<floatCount<<"\n";
  return 0;
}