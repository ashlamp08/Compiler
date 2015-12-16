/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    BOOLE = 258,
    NUM = 259,
    ID = 260,
    BEG = 261,
    END = 262,
    DECL = 263,
    ENDDECL = 264,
    IF = 265,
    THEN = 266,
    ELSE = 267,
    ENDIF = 268,
    WHILE = 269,
    DO = 270,
    ENDWHILE = 271,
    READ = 272,
    WRITE = 273,
    PLUS = 274,
    MINUS = 275,
    MUL = 276,
    DIV = 277,
    AND = 278,
    OR = 279,
    NOT = 280,
    LEQ = 281,
    GEQ = 282,
    LTHAN = 283,
    GTHAN = 284,
    INTEGER = 285,
    BOOLEAN = 286,
    EQEQ = 287,
    NEQ = 288
  };
#endif
/* Tokens.  */
#define BOOLE 258
#define NUM 259
#define ID 260
#define BEG 261
#define END 262
#define DECL 263
#define ENDDECL 264
#define IF 265
#define THEN 266
#define ELSE 267
#define ENDIF 268
#define WHILE 269
#define DO 270
#define ENDWHILE 271
#define READ 272
#define WRITE 273
#define PLUS 274
#define MINUS 275
#define MUL 276
#define DIV 277
#define AND 278
#define OR 279
#define NOT 280
#define LEQ 281
#define GEQ 282
#define LTHAN 283
#define GTHAN 284
#define INTEGER 285
#define BOOLEAN 286
#define EQEQ 287
#define NEQ 288

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
