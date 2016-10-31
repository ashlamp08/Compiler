
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "compiler.y"

	/*** Auxiliary declarations section ***/

#include <iostream>
#include <cmath>
#include <algorithm>
#include "syntaxTree.h"
#include <string>

	extern FILE *yyin;
	int yylex();					//	Declarations of Functions
	void yyerror (const std::string & s);	//

	extern unsigned lineNumber;
	extern unsigned colNumber;

	extern void error (const std::string &s, int l, int c);
		
	SNode * program, *globalDecl, *Main, *currentScope;

	int currentType, Status;
	
	bool checkArguments(SNode * oper, SNode * X, SNode * Y);
	bool assignExpression(SNode *&dest, SNode * X, SNode * oper, SNode * Y);



/* Line 189 of yacc.c  */
#line 101 "compiler.cpp"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ID = 258,
     NUM = 259,
     READ = 260,
     WRITE = 261,
     START = 262,
     END = 263,
     IF = 264,
     THEN = 265,
     ELSE = 266,
     ENDIF = 267,
     WHILE = 268,
     DO = 269,
     ENDWHILE = 270,
     ISEQ = 271,
     NOTEQ = 272,
     LEQ = 273,
     GEQ = 274,
     STARTDECL = 275,
     ENDDECL = 276,
     INTEGER = 277,
     BOOLEAN = 278,
     AND = 279,
     OR = 280,
     NOT = 281,
     TRUE = 282,
     FALSE = 283
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 171 "compiler.cpp"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  18
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   296

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  43
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  12
/* YYNRULES -- Number of rules.  */
#define YYNRULES  42
/* YYNRULES -- Number of states.  */
#define YYNSTATES  102

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   283

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      41,    42,    33,    31,    37,    32,     2,    34,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    36,
      29,    40,    30,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    38,     2,    39,    35,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     8,    12,    16,    19,    21,    25,    29,
      31,    36,    38,    40,    42,    45,    47,    52,    58,    64,
      73,    84,    93,    97,   101,   105,   109,   113,   117,   121,
     125,   129,   133,   137,   141,   145,   148,   152,   154,   156,
     158,   160,   165
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      44,     0,    -1,    45,     7,    51,     8,    -1,     7,    51,
       8,    -1,    20,    46,    21,    -1,    47,    46,    -1,    47,
      -1,    50,    48,    36,    -1,    49,    37,    48,    -1,    49,
      -1,     3,    38,     4,    39,    -1,     3,    -1,    22,    -1,
      23,    -1,    52,    51,    -1,    52,    -1,    54,    40,    53,
      36,    -1,     5,    41,    54,    42,    36,    -1,     6,    41,
      53,    42,    36,    -1,     9,    41,    53,    42,    10,    51,
      12,    36,    -1,     9,    41,    53,    42,    10,    51,    11,
      51,    12,    36,    -1,    13,    41,    53,    42,    14,    51,
      15,    36,    -1,    53,    31,    53,    -1,    53,    32,    53,
      -1,    53,    33,    53,    -1,    53,    34,    53,    -1,    53,
      35,    53,    -1,    53,    29,    53,    -1,    53,    30,    53,
      -1,    53,    18,    53,    -1,    53,    19,    53,    -1,    53,
      16,    53,    -1,    53,    17,    53,    -1,    53,    24,    53,
      -1,    53,    25,    53,    -1,    26,    53,    -1,    41,    53,
      42,    -1,    27,    -1,    28,    -1,     4,    -1,    54,    -1,
       3,    38,    53,    39,    -1,     3,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    71,    71,    79,    88,   112,   113,   117,   121,   122,
     125,   126,   130,   131,   135,   136,   139,   140,   141,   146,
     154,   164,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   197,   215
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "NUM", "READ", "WRITE", "START",
  "END", "IF", "THEN", "ELSE", "ENDIF", "WHILE", "DO", "ENDWHILE", "ISEQ",
  "NOTEQ", "LEQ", "GEQ", "STARTDECL", "ENDDECL", "INTEGER", "BOOLEAN",
  "AND", "OR", "NOT", "TRUE", "FALSE", "'<'", "'>'", "'+'", "'-'", "'*'",
  "'/'", "'^'", "';'", "','", "'['", "']'", "'='", "'('", "')'", "$accept",
  "PROG", "DECLERATIONS", "DLIST", "DECLARE", "MULDCL", "VARDCL", "TYPE",
  "SLIST", "STMT", "EXPR", "IDENT", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,    60,
      62,    43,    45,    42,    47,    94,    59,    44,    91,    93,
      61,    40,    41
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    43,    44,    44,    45,    46,    46,    47,    48,    48,
      49,    49,    50,    50,    51,    51,    52,    52,    52,    52,
      52,    52,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    54,    54
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     4,     3,     3,     2,     1,     3,     3,     1,
       4,     1,     1,     1,     2,     1,     4,     5,     5,     8,
      10,     8,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     3,     1,     1,     1,
       1,     4,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,    42,     0,     0,     0,     0,
       0,    15,     0,    12,    13,     0,     6,     0,     1,     0,
       0,     0,     0,     0,     0,     3,    14,     0,     4,     5,
      11,     0,     9,     0,    39,     0,    37,    38,     0,     0,
      40,     0,     0,     0,     0,     0,     0,     7,     0,     2,
      35,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    41,     0,     0,     0,     0,
      16,     0,     8,    36,    31,    32,    29,    30,    33,    34,
      27,    28,    22,    23,    24,    25,    26,    17,    18,     0,
       0,    10,     0,     0,     0,     0,     0,     0,    19,    21,
       0,    20
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,    15,    16,    31,    32,    17,    10,    11,
      39,    40
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -20
static const yytype_int16 yypact[] =
{
      -5,   283,   -11,    25,    49,    17,    18,    19,    28,    30,
      62,   283,    34,   -20,   -20,    55,   -11,    74,   -20,   283,
      20,    75,    20,    20,    20,   -20,   -20,    20,   -20,   -20,
      47,    50,    53,    79,   -20,    20,   -20,   -20,    20,   138,
     -20,    56,    33,    78,    98,   162,    87,   -20,    74,   -20,
      29,   118,    20,    20,    20,    20,    20,    20,    20,    20,
      20,    20,    20,    20,    20,   -20,    63,    64,    82,    90,
     -20,    66,   -20,   -20,   203,   183,   221,   238,    76,   -20,
      -3,   250,    48,    48,   -18,   -18,   -18,   -20,   -20,   283,
     283,   -20,     2,    91,   283,    83,    85,   106,   -20,   -20,
      88,   -20
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -20,   -20,   -20,   109,   -20,    93,   -20,   -20,   -10,   -20,
     -19,    -1
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_int8 yytable[] =
{
      12,    26,     1,    42,    43,    44,    56,    57,    45,    33,
      12,    13,    14,    94,    95,     2,    50,    64,    12,    51,
      41,    56,    57,     5,    34,    18,    -1,    59,    60,    61,
      62,    63,    64,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    35,    36,    37,    52,
      53,    54,    55,    56,    57,    20,    19,    56,    57,    21,
      22,    38,    58,    59,    60,    61,    62,    63,    64,    23,
      25,    24,    56,    57,    27,    67,    28,    30,     5,    92,
      93,    62,    63,    64,    97,    46,    47,    49,    12,    12,
      48,    71,    89,    12,    52,    53,    54,    55,    66,    87,
      88,    57,    56,    57,    90,    91,    96,    58,    59,    60,
      61,    62,    63,    64,    52,    53,    54,    55,   100,    98,
      68,    99,    56,    57,   101,    29,     0,    58,    59,    60,
      61,    62,    63,    64,    52,    53,    54,    55,     0,     0,
      69,    72,    56,    57,     0,     0,     0,    58,    59,    60,
      61,    62,    63,    64,    52,    53,    54,    55,     0,     0,
      73,     0,    56,    57,     0,     0,     0,    58,    59,    60,
      61,    62,    63,    64,     0,     0,     0,    65,    52,    53,
      54,    55,     0,     0,     0,     0,    56,    57,     0,     0,
       0,    58,    59,    60,    61,    62,    63,    64,    70,    52,
      -1,    54,    55,     0,     0,     0,     0,    56,    57,     0,
       0,     0,    58,    59,    60,    61,    62,    63,    64,    -1,
       0,    54,    55,     0,     0,     0,     0,    56,    57,     0,
       0,     0,    58,    59,    60,    61,    62,    63,    64,    -1,
      55,     0,     0,     0,     0,    56,    57,     0,     0,     0,
      58,    59,    60,    61,    62,    63,    64,    -1,     0,     0,
       0,     0,    56,    57,     0,     0,     0,    58,    59,    60,
      61,    62,    63,    64,    56,    57,     0,     0,     0,     0,
      -1,    60,    61,    62,    63,    64,     5,     0,     6,     7,
       0,     0,     8,     0,     0,     0,     9
};

static const yytype_int8 yycheck[] =
{
       1,    11,     7,    22,    23,    24,    24,    25,    27,    19,
      11,    22,    23,    11,    12,    20,    35,    35,    19,    38,
      21,    24,    25,     3,     4,     0,    29,    30,    31,    32,
      33,    34,    35,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    26,    27,    28,    16,
      17,    18,    19,    24,    25,    38,     7,    24,    25,    41,
      41,    41,    29,    30,    31,    32,    33,    34,    35,    41,
       8,    41,    24,    25,    40,    42,    21,     3,     3,    89,
      90,    33,    34,    35,    94,    38,    36,     8,    89,    90,
      37,     4,    10,    94,    16,    17,    18,    19,    42,    36,
      36,    25,    24,    25,    14,    39,    15,    29,    30,    31,
      32,    33,    34,    35,    16,    17,    18,    19,    12,    36,
      42,    36,    24,    25,    36,    16,    -1,    29,    30,    31,
      32,    33,    34,    35,    16,    17,    18,    19,    -1,    -1,
      42,    48,    24,    25,    -1,    -1,    -1,    29,    30,    31,
      32,    33,    34,    35,    16,    17,    18,    19,    -1,    -1,
      42,    -1,    24,    25,    -1,    -1,    -1,    29,    30,    31,
      32,    33,    34,    35,    -1,    -1,    -1,    39,    16,    17,
      18,    19,    -1,    -1,    -1,    -1,    24,    25,    -1,    -1,
      -1,    29,    30,    31,    32,    33,    34,    35,    36,    16,
      17,    18,    19,    -1,    -1,    -1,    -1,    24,    25,    -1,
      -1,    -1,    29,    30,    31,    32,    33,    34,    35,    16,
      -1,    18,    19,    -1,    -1,    -1,    -1,    24,    25,    -1,
      -1,    -1,    29,    30,    31,    32,    33,    34,    35,    18,
      19,    -1,    -1,    -1,    -1,    24,    25,    -1,    -1,    -1,
      29,    30,    31,    32,    33,    34,    35,    19,    -1,    -1,
      -1,    -1,    24,    25,    -1,    -1,    -1,    29,    30,    31,
      32,    33,    34,    35,    24,    25,    -1,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,     3,    -1,     5,     6,
      -1,    -1,     9,    -1,    -1,    -1,    13
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     7,    20,    44,    45,     3,     5,     6,     9,    13,
      51,    52,    54,    22,    23,    46,    47,    50,     0,     7,
      38,    41,    41,    41,    41,     8,    51,    40,    21,    46,
       3,    48,    49,    51,     4,    26,    27,    28,    41,    53,
      54,    54,    53,    53,    53,    53,    38,    36,    37,     8,
      53,    53,    16,    17,    18,    19,    24,    25,    29,    30,
      31,    32,    33,    34,    35,    39,    42,    42,    42,    42,
      36,     4,    48,    42,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    36,    36,    10,
      14,    39,    51,    51,    11,    12,    15,    51,    36,    36,
      12,    36
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 71 "compiler.y"
    {
										program->setNext((yyvsp[(3) - (4)]));
										program->setTable((yyvsp[(1) - (4)])->getTable());
										delete (yyvsp[(1) - (4)]);
										delete (yyvsp[(2) - (4)]);
										delete (yyvsp[(4) - (4)]);
										return 0;
									;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 79 "compiler.y"
    {
										program->setNext((yyvsp[(2) - (3)]));
										delete (yyvsp[(1) - (3)]);
										delete (yyvsp[(3) - (3)]);
										return 0;
									;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 88 "compiler.y"
    {
										symbolNode *Table = new symbolNode("&&&", -1);
										for (SNode *head = (yyvsp[(2) - (3)]); head != nullptr; head = head->getNext() ) {
											for (SNode *i = head->getPTR3(); i != nullptr; i = i->getPTR3() ) {
												symbolNode *position;
												if (i->getPTR2())
													position = Table->install(i->getName(), head->getNodeType(), i->getPTR2()->getValue());
												else
													position = Table->install(i->getName(), head->getNodeType());
												if (position == nullptr) {
													error("'" + i->getName() + "' is already declared",i->lineNo,i->colNo);
													Status = FAIL;
												}
											}
										}
										delete (yyvsp[(1) - (3)]);
										delete (yyvsp[(2) - (3)]);
										delete (yyvsp[(3) - (3)]);
										SNode *temp = new SNode(-1, "&&&", -1, -1);
										temp->setTable(Table);
										currentScope = (yyval) = temp;
									;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 112 "compiler.y"
    {(yyval) = (yyvsp[(1) - (2)]); (yyvsp[(1) - (2)])->setNext((yyvsp[(2) - (2)]));;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 113 "compiler.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 117 "compiler.y"
    {(yyvsp[(1) - (3)])->setPTR3((yyvsp[(2) - (3)])); (yyval) = (yyvsp[(1) - (3)]);;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 121 "compiler.y"
    {(yyval) = (yyvsp[(1) - (3)]); (yyvsp[(1) - (3)])->setPTR3((yyvsp[(3) - (3)])); deb;;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 122 "compiler.y"
    {(yyval) = (yyvsp[(1) - (1)]); deb;;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 125 "compiler.y"
    {(yyval) = (yyvsp[(1) - (4)]); (yyval)->setPTR2((yyvsp[(3) - (4)]));;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 126 "compiler.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 130 "compiler.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 131 "compiler.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 135 "compiler.y"
    {(yyval) = (yyvsp[(1) - (2)]); (yyvsp[(1) - (2)])->setNext((yyvsp[(2) - (2)])); deb;;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 136 "compiler.y"
    {(yyval) = (yyvsp[(1) - (1)]); deb;;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 139 "compiler.y"
    {(yyval) = (yyvsp[(2) - (4)]); (yyval)->setPTR1((yyvsp[(1) - (4)])); (yyval)->setPTR2((yyvsp[(3) - (4)]));;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 140 "compiler.y"
    {(yyval) = (yyvsp[(1) - (5)]); (yyval)->setPTR2((yyvsp[(3) - (5)]));;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 141 "compiler.y"
    {	
										(yyval) = (yyvsp[(1) - (5)]);
										(yyval)->setPTR2((yyvsp[(3) - (5)]));
										deb;
									;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 147 "compiler.y"
    {
										(yyval) = (yyvsp[(1) - (8)]);
										(yyval)->setPTR1((yyvsp[(3) - (8)]));
										(yyval)->setPTR2((yyvsp[(6) - (8)]));
										delete (yyvsp[(5) - (8)]);
										delete (yyvsp[(7) - (8)]);
									;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 155 "compiler.y"
    {
										(yyval) = (yyvsp[(1) - (10)]);
										(yyval)->setPTR1((yyvsp[(3) - (10)]));
										(yyval)->setPTR2((yyvsp[(6) - (10)]));
										(yyval)->setPTR3((yyvsp[(8) - (10)]));
										delete (yyvsp[(5) - (10)]);
										delete (yyvsp[(7) - (10)]);
										delete (yyvsp[(9) - (10)]);
									;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 165 "compiler.y"
    {
										(yyval) = (yyvsp[(1) - (8)]);
										(yyval)->setPTR1((yyvsp[(3) - (8)]));
										(yyval)->setPTR2((yyvsp[(6) - (8)]));
										delete (yyvsp[(5) - (8)]);
										delete (yyvsp[(7) - (8)]);
									;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 175 "compiler.y"
    {(yyval) = (yyvsp[(2) - (3)]); (yyval)->setPTR1((yyvsp[(1) - (3)])); (yyval)->setPTR2((yyvsp[(3) - (3)])); (yyval)->setType(INTEGER);;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 176 "compiler.y"
    {(yyval) = (yyvsp[(2) - (3)]); (yyval)->setPTR1((yyvsp[(1) - (3)])); (yyval)->setPTR2((yyvsp[(3) - (3)])); (yyval)->setType(INTEGER);;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 177 "compiler.y"
    {(yyval) = (yyvsp[(2) - (3)]); (yyval)->setPTR1((yyvsp[(1) - (3)])); (yyval)->setPTR2((yyvsp[(3) - (3)])); (yyval)->setType(INTEGER);;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 178 "compiler.y"
    {(yyval) = (yyvsp[(2) - (3)]); (yyval)->setPTR1((yyvsp[(1) - (3)])); (yyval)->setPTR2((yyvsp[(3) - (3)])); (yyval)->setType(INTEGER);;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 179 "compiler.y"
    {(yyval) = (yyvsp[(2) - (3)]); (yyval)->setPTR1((yyvsp[(1) - (3)])); (yyval)->setPTR2((yyvsp[(3) - (3)])); (yyval)->setType(INTEGER);;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 180 "compiler.y"
    {(yyval) = (yyvsp[(2) - (3)]); (yyval)->setPTR1((yyvsp[(1) - (3)])); (yyval)->setPTR2((yyvsp[(3) - (3)])); (yyval)->setType(BOOLEAN);;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 181 "compiler.y"
    {(yyval) = (yyvsp[(2) - (3)]); (yyval)->setPTR1((yyvsp[(1) - (3)])); (yyval)->setPTR2((yyvsp[(3) - (3)])); (yyval)->setType(BOOLEAN);;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 182 "compiler.y"
    {(yyval) = (yyvsp[(2) - (3)]); (yyval)->setPTR1((yyvsp[(1) - (3)])); (yyval)->setPTR2((yyvsp[(3) - (3)])); (yyval)->setType(BOOLEAN);;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 183 "compiler.y"
    {(yyval) = (yyvsp[(2) - (3)]); (yyval)->setPTR1((yyvsp[(1) - (3)])); (yyval)->setPTR2((yyvsp[(3) - (3)])); (yyval)->setType(BOOLEAN);;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 184 "compiler.y"
    {(yyval) = (yyvsp[(2) - (3)]); (yyval)->setPTR1((yyvsp[(1) - (3)])); (yyval)->setPTR2((yyvsp[(3) - (3)])); (yyval)->setType(BOOLEAN);;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 185 "compiler.y"
    {(yyval) = (yyvsp[(2) - (3)]); (yyval)->setPTR1((yyvsp[(1) - (3)])); (yyval)->setPTR2((yyvsp[(3) - (3)])); (yyval)->setType(BOOLEAN);;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 186 "compiler.y"
    {(yyval) = (yyvsp[(2) - (3)]); (yyval)->setPTR1((yyvsp[(1) - (3)])); (yyval)->setPTR2((yyvsp[(3) - (3)])); (yyval)->setType(BOOLEAN);;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 187 "compiler.y"
    {(yyval) = (yyvsp[(2) - (3)]); (yyval)->setPTR1((yyvsp[(1) - (3)])); (yyval)->setPTR2((yyvsp[(3) - (3)])); (yyval)->setType(BOOLEAN);;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 188 "compiler.y"
    {(yyval) = (yyvsp[(1) - (2)]); (yyval)->setPTR1((yyvsp[(2) - (2)])); (yyval)->setType(BOOLEAN);;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 189 "compiler.y"
    {(yyval) = (yyvsp[(2) - (3)]);;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 190 "compiler.y"
    {(yyval) = (yyvsp[(1) - (1)]); (yyval)->setType(BOOLEAN);;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 191 "compiler.y"
    {(yyval) = (yyvsp[(1) - (1)]); (yyval)->setType(BOOLEAN);;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 192 "compiler.y"
    {(yyval) = (yyvsp[(1) - (1)]); (yyval)->setType(INTEGER);;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 193 "compiler.y"
    {(yyval) = (yyvsp[(1) - (1)]); deb;;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 197 "compiler.y"
    {
									symbolNode *Table = currentScope->getTable(), *temp;
									temp = Table->lookUp((yyvsp[(1) - (4)])->getName());
									if (temp == nullptr) {
										error("'" + (yyvsp[(1) - (4)])->getName() + "' not Declared", (yyvsp[(1) - (4)])->lineNo, (yyvsp[(1) - (4)])->colNo);
										Status = FAIL;
									}
									else if (temp->getSize() == -1) {
										error("'" + (yyvsp[(1) - (4)])->getName() + " used as Array but declared as Variable",(yyvsp[(1) - (4)])->lineNo, (yyvsp[(1) - (4)])->colNo);
										Status = FAIL;
									}
									else{
										(yyvsp[(1) - (4)])->setEntry(temp);
										(yyval) = (yyvsp[(1) - (4)]);
										(yyval)->setPTR1((yyvsp[(3) - (4)]));
										(yyval)->setType(temp->getType());
									}
								;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 215 "compiler.y"
    {
									symbolNode *Table = currentScope->getTable(), *temp;
									temp = Table->lookUp((yyvsp[(1) - (1)])->getName());
									if (temp == nullptr) {
										error("'" + (yyvsp[(1) - (1)])->getName() + "' not Declared",(yyvsp[(1) - (1)])->lineNo, (yyvsp[(1) - (1)])->colNo);
										Status = FAIL;
									}
									else if (temp->getSize() != -1) {
										error("'" + (yyvsp[(1) - (1)])->getName() + "' used as Variable but declared as Array",(yyvsp[(1) - (1)])->lineNo, (yyvsp[(1) - (1)])->colNo);
										Status = FAIL;
									}
									else{
										(yyvsp[(1) - (1)])->setEntry(temp);
										(yyval) = (yyvsp[(1) - (1)]);
										(yyval)->setType(temp->getType());
									}
									deb;
								;}
    break;



/* Line 1455 of yacc.c  */
#line 1860 "compiler.cpp"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 234 "compiler.y"


/*** Auxiliary functions section ***/

void yyerror(const std::string &s) {
	std::cout << "ERROR: "<<lineNumber<<","<<colNumber<<": "<<  s << "\n";
}

bool checkArguments(SNode *oper, SNode *X, SNode *Y) {
	switch (oper->getNodeType()) {
		case '+':
		case '-':
		case '*':
		case '/':
		case '^':
		case '<':
		case '>':
		case LEQ:
		case GEQ:
			if (X->getType() == BOOLEAN) {
				yyerror("'" + X->getName() + "' is of type Boolean, needed Integer");
				return false;
			}
			if (Y->getType() == BOOLEAN) {
				yyerror("'" + Y->getName() + "' is of type Boolean, needed Integer");
				return false;
			}
			return true;
		case ISEQ:
		case NOTEQ:
			if (X->getType() == INTEGER && Y->getType() == BOOLEAN) {
				yyerror("'" + Y->getName() + "' is of type Boolean, needed Integer");
				return false;
			}
			if (X->getType() == BOOLEAN && Y->getType() == INTEGER) {
				yyerror("'" + Y->getName() + "' is of type Integer, needed Boolean");
				return false;
			}
			return true;
		case AND:
		case OR:
			if (X->getType() == INTEGER) {
				yyerror("'" + X->getName() + "' is of type Integer, needed Boolean");
				return false;
			}
			if (Y->getType() == INTEGER) {
				yyerror("'" + Y->getName() + "' is of type Integer, needed Boolean");
				return false;
			}
			return true;
		case NOT:
			if (X->getType() == INTEGER && Y == nullptr) {
				yyerror("'" + X->getName() + "' is of type Integer, needed Boolean");
				return false;
			}
			return true;
	}
	return false;
}
bool assignExpression(SNode *&dest, SNode *X, SNode *oper, SNode *Y) {
	if (checkArguments(oper, X, Y)) {
		dest = oper;
		dest->setPTR1(X);
		dest->setPTR2(Y);
		return true;
	}
	return false;
}
int main(int argc, char *argv[]) {
	Status = PASS;
	if (argc != 2 && argc != 3) {
		std::cout << "Error: no input files\n";
		std::cout << "Usage: \tcompiler.exe <input_file> \n\tcompiler.exe <input_file> <output_file>\n";
		return 1;
	}
	else {
		yyin = fopen(argv[1], "r");
		if (!yyin) {
			std::cout << "'" << argv[1] << "' does not exists.\n";
			return 1;
		}
	}
	FILE *output;
	if(argc == 3)
		output = fopen(argv[2], "wb");
	else
		output = fopen("a.sil", "wb");
	if(!output){
		std::cout << "Cant write to file 'test.sil'\n";
		return 1;
	}
	program = new SNode(START,-1,-1);
	currentScope = program;
	if(yyparse() || std::min(Status,program->typeCheck())<=WARN){
		delete program->getTable();
		delete program;
		std::cout << "SNodes Left = " << SNode::getCount() << "\n";
		std::cout << "symbolNodes Left = " << symbolNode::getCount() << "\n";
		return 1;
	}
	program->print();
	program->codeGen(output);
	fprintf(output,"HALT\n");
//	program->run();
	delete program->getTable();
	delete program;
	std::cout << "SNodes Left = " << SNode::getCount() << "\n";
	std::cout << "symbolNodes Left = " << symbolNode::getCount() << "\n";
	return 0;
}

