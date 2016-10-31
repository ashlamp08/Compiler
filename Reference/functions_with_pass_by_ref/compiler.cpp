
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
#include <set>
#include "syntaxTree.h"
#include "util.h"
#include <string>

	//
	//	External Variables 
	//	Declared in compiler.l
	extern FILE *yyin;								
	extern unsigned lineNumber;						
	extern unsigned colNumber;		
	
	//
	//	Function Declarations
	//
	int yylex();									
	void yyerror(const std::string &s) {			
		std::cout << "ERROR: "<<lineNumber<<","<<colNumber<<": "<<  s << "\n";
	}							

	
	SNode *program, *Scope[2] = {nullptr, nullptr};
	int Status;



/* Line 189 of yacc.c  */
#line 106 "compiler.cpp"

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
     FALSE = 283,
     FUNC = 284,
     RETURN = 285
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
#line 178 "compiler.cpp"

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
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   351

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  48
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  21
/* YYNRULES -- Number of rules.  */
#define YYNRULES  62
/* YYNRULES -- Number of states.  */
#define YYNSTATES  138

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   285

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    46,     2,
      39,    40,    35,    33,    43,    34,     2,    36,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    42,
      31,    47,    32,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    44,     2,    45,    37,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    41,     2,    38,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     6,     9,    11,    18,    26,    30,    31,
      34,    36,    40,    44,    46,    51,    56,    58,    62,    64,
      65,    68,    73,    77,    80,    82,    84,    86,    88,    89,
      92,    94,    98,   103,   109,   115,   124,   135,   144,   148,
     152,   156,   160,   164,   168,   172,   176,   180,   184,   188,
     192,   196,   199,   203,   205,   207,   209,   211,   216,   221,
     223,   227,   229
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      49,     0,    -1,    53,    50,    -1,    51,    50,    -1,    51,
      -1,    52,     7,    62,    64,     8,    38,    -1,    61,     3,
      39,    58,    40,    41,    53,    -1,    20,    54,    21,    -1,
      -1,    55,    54,    -1,    55,    -1,    61,    56,    42,    -1,
      57,    43,    56,    -1,    57,    -1,     3,    39,    58,    40,
      -1,     3,    44,     4,    45,    -1,     3,    -1,    59,    42,
      58,    -1,    59,    -1,    -1,    61,    60,    -1,    46,     3,
      43,    60,    -1,     3,    43,    60,    -1,    46,     3,    -1,
       3,    -1,    22,    -1,    23,    -1,    63,    -1,    -1,    65,
      63,    -1,    65,    -1,    30,    66,    42,    -1,    67,    47,
      66,    42,    -1,     5,    39,    67,    40,    42,    -1,     6,
      39,    66,    40,    42,    -1,     9,    39,    66,    40,    10,
      62,    12,    42,    -1,     9,    39,    66,    40,    10,    62,
      11,    62,    12,    42,    -1,    13,    39,    66,    40,    14,
      62,    15,    42,    -1,    66,    33,    66,    -1,    66,    34,
      66,    -1,    66,    35,    66,    -1,    66,    36,    66,    -1,
      66,    37,    66,    -1,    66,    31,    66,    -1,    66,    32,
      66,    -1,    66,    18,    66,    -1,    66,    19,    66,    -1,
      66,    16,    66,    -1,    66,    17,    66,    -1,    66,    24,
      66,    -1,    66,    25,    66,    -1,    26,    66,    -1,    39,
      66,    40,    -1,    27,    -1,    28,    -1,     4,    -1,    67,
      -1,     3,    39,    68,    40,    -1,     3,    44,    66,    45,
      -1,     3,    -1,    66,    43,    68,    -1,    66,    -1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    63,    63,    75,    76,    79,    98,   114,   125,   136,
     137,   141,   145,   146,   150,   151,   152,   156,   157,   158,
     162,   166,   167,   168,   169,   172,   173,   177,   178,   181,
     182,   186,   190,   191,   192,   196,   202,   208,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   244,   249,
     256,   257,   258
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
  "AND", "OR", "NOT", "TRUE", "FALSE", "FUNC", "RETURN", "'<'", "'>'",
  "'+'", "'-'", "'*'", "'/'", "'^'", "'}'", "'('", "')'", "'{'", "';'",
  "','", "'['", "']'", "'&'", "'='", "$accept", "PROG", "FUNCTIONLIST",
  "FUNCTIONDEF", "FUNCTIONHEADER", "DECLERATIONS", "DLIST", "DECLARE",
  "MULDCL", "VARDCL", "ARGLIST", "ARGGROUP", "IDLIST", "TYPE", "SLIST",
  "STATEMENTS", "RETSTMT", "STMT", "EXPR", "IDENT", "ACTARGLIST", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,    60,    62,    43,    45,    42,    47,    94,   125,    40,
      41,   123,    59,    44,    91,    93,    38,    61
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    48,    49,    50,    50,    51,    52,    53,    53,    54,
      54,    55,    56,    56,    57,    57,    57,    58,    58,    58,
      59,    60,    60,    60,    60,    61,    61,    62,    62,    63,
      63,    64,    65,    65,    65,    65,    65,    65,    66,    66,
      66,    66,    66,    66,    66,    66,    66,    66,    66,    66,
      66,    66,    66,    66,    66,    66,    66,    66,    67,    67,
      68,    68,    68
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     1,     6,     7,     3,     0,     2,
       1,     3,     3,     1,     4,     4,     1,     3,     1,     0,
       2,     4,     3,     2,     1,     1,     1,     1,     0,     2,
       1,     3,     4,     5,     5,     8,    10,     8,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     3,     1,     1,     1,     1,     4,     4,     1,
       3,     1,     0
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       8,     0,     0,     0,    25,    26,     0,    10,     0,     1,
       2,     4,     0,     0,     7,     9,    16,     0,    13,     3,
      28,     0,    19,     0,    11,     0,    59,     0,     0,     0,
       0,     0,    27,    30,     0,    19,     0,    18,     0,     0,
      12,     0,     0,     0,     0,     0,     0,     0,    29,     0,
       0,    14,    19,    24,     0,    20,    15,    59,    55,     0,
      53,    54,     0,     0,    56,     0,     0,     0,     0,     0,
       0,     0,     0,    17,     0,    23,    62,    51,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    58,     0,     0,     0,     0,    31,     5,    32,
       8,    22,     0,    61,     0,    52,    47,    48,    45,    46,
      49,    50,    43,    44,    38,    39,    40,    41,    42,    33,
      34,    28,    28,     6,    21,    62,    57,     0,     0,    60,
      28,     0,     0,     0,    35,    37,     0,    36
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,    10,    11,    12,     3,     6,     7,    17,    18,
      36,    37,    55,    38,    31,    32,    47,    33,   103,    64,
     104
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -74
static const yytype_int16 yypact[] =
{
     -17,    -5,    12,    -5,   -74,   -74,    -2,    -5,    18,   -74,
     -74,    -5,    17,    50,   -74,   -74,   -30,    30,    40,   -74,
     181,    46,    -5,    80,   -74,    18,    48,    47,    55,    56,
      60,    70,   -74,   181,    69,    -5,    77,    76,     8,    78,
     -74,    29,   118,    29,    29,    29,    29,   114,   -74,    29,
      84,   -74,    -5,    82,   135,   -74,   -74,    54,   -74,    29,
     -74,   -74,    29,    42,   -74,    99,   139,   164,   189,    95,
     102,   117,   103,   -74,     8,   100,    29,     6,   214,    29,
      29,    29,    29,    29,    29,    29,    29,    29,    29,    29,
      29,    29,   -74,   104,   105,   150,   131,   -74,   -74,   -74,
     -17,   -74,     8,    72,   121,   -74,   261,   239,   281,   300,
     137,   -74,   314,     2,    45,    45,    -9,    -9,    -9,   -74,
     -74,   181,   181,   -74,   -74,    29,   -74,    53,   151,   -74,
     181,   123,   125,   156,   -74,   -74,   127,   -74
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -74,   -74,   166,   -74,   -74,    85,   171,   -74,   167,   -74,
     -27,   -74,   -73,   208,   -59,   158,   -74,   -74,   -39,   -20,
      68
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_int16 yytable[] =
{
      34,   101,    63,     1,    66,    67,    68,    69,    50,    22,
      71,    53,     9,    34,    23,    83,    84,     4,     5,    14,
      77,    16,    65,    78,    20,    73,    83,    84,    91,   124,
      83,    84,    57,    58,    -1,    87,    88,    89,    90,    91,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,    21,    54,    59,    60,    61,    79,    80,
      81,    82,   127,   128,   130,   131,    83,    84,    62,    83,
      84,   133,    24,    85,    86,    87,    88,    89,    90,    91,
      89,    90,    91,    25,    39,    35,    42,    92,    79,    80,
      81,    82,    41,    76,    43,    44,    83,    84,    41,    45,
      46,    34,    34,    85,    86,    87,    88,    89,    90,    91,
      34,    79,    80,    81,    82,   125,    49,    51,    52,    83,
      84,    26,    70,    56,    72,    74,    85,    86,    87,    88,
      89,    90,    91,    79,    80,    81,    82,    97,    75,    93,
      98,    83,    84,   102,   100,   122,   119,   120,    85,    86,
      87,    88,    89,    90,    91,    79,    80,    81,    82,    99,
     121,   126,    84,    83,    84,   134,   132,   135,   136,   137,
      85,    86,    87,    88,    89,    90,    91,    19,    15,    94,
      79,    80,    81,    82,    26,   123,    27,    28,    83,    84,
      29,    48,    40,   129,    30,    85,    86,    87,    88,    89,
      90,    91,     0,     0,    95,    79,    80,    81,    82,     8,
       0,    13,     0,    83,    84,     8,     0,     0,     0,    13,
      85,    86,    87,    88,    89,    90,    91,     0,     0,    96,
      79,    80,    81,    82,     0,     0,     0,     0,    83,    84,
       0,     0,     0,     0,     0,    85,    86,    87,    88,    89,
      90,    91,     0,     0,   105,    79,    -1,    81,    82,     0,
       0,     0,     0,    83,    84,     0,     0,     0,     0,     0,
      85,    86,    87,    88,    89,    90,    91,    -1,     0,    81,
      82,     0,     0,     0,     0,    83,    84,     0,     0,     0,
       0,     0,    85,    86,    87,    88,    89,    90,    91,    -1,
      82,     0,     0,     0,     0,    83,    84,     0,     0,     0,
       0,     0,    85,    86,    87,    88,    89,    90,    91,    -1,
       0,     0,     0,     0,    83,    84,     0,     0,     0,     0,
       0,    85,    86,    87,    88,    89,    90,    91,    83,    84,
       0,     0,     0,     0,     0,    -1,    86,    87,    88,    89,
      90,    91
};

static const yytype_int16 yycheck[] =
{
      20,    74,    41,    20,    43,    44,    45,    46,    35,    39,
      49,     3,     0,    33,    44,    24,    25,    22,    23,    21,
      59,     3,    42,    62,     7,    52,    24,    25,    37,   102,
      24,    25,     3,     4,    32,    33,    34,    35,    36,    37,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,     3,    46,    26,    27,    28,    16,    17,
      18,    19,   121,   122,    11,    12,    24,    25,    39,    24,
      25,   130,    42,    31,    32,    33,    34,    35,    36,    37,
      35,    36,    37,    43,     4,    39,    39,    45,    16,    17,
      18,    19,    44,    39,    39,    39,    24,    25,    44,    39,
      30,   121,   122,    31,    32,    33,    34,    35,    36,    37,
     130,    16,    17,    18,    19,    43,    47,    40,    42,    24,
      25,     3,     8,    45,    40,    43,    31,    32,    33,    34,
      35,    36,    37,    16,    17,    18,    19,    42,     3,    40,
      38,    24,    25,    43,    41,    14,    42,    42,    31,    32,
      33,    34,    35,    36,    37,    16,    17,    18,    19,    42,
      10,    40,    25,    24,    25,    42,    15,    42,    12,    42,
      31,    32,    33,    34,    35,    36,    37,    11,     7,    40,
      16,    17,    18,    19,     3,   100,     5,     6,    24,    25,
       9,    33,    25,   125,    13,    31,    32,    33,    34,    35,
      36,    37,    -1,    -1,    40,    16,    17,    18,    19,     1,
      -1,     3,    -1,    24,    25,     7,    -1,    -1,    -1,    11,
      31,    32,    33,    34,    35,    36,    37,    -1,    -1,    40,
      16,    17,    18,    19,    -1,    -1,    -1,    -1,    24,    25,
      -1,    -1,    -1,    -1,    -1,    31,    32,    33,    34,    35,
      36,    37,    -1,    -1,    40,    16,    17,    18,    19,    -1,
      -1,    -1,    -1,    24,    25,    -1,    -1,    -1,    -1,    -1,
      31,    32,    33,    34,    35,    36,    37,    16,    -1,    18,
      19,    -1,    -1,    -1,    -1,    24,    25,    -1,    -1,    -1,
      -1,    -1,    31,    32,    33,    34,    35,    36,    37,    18,
      19,    -1,    -1,    -1,    -1,    24,    25,    -1,    -1,    -1,
      -1,    -1,    31,    32,    33,    34,    35,    36,    37,    19,
      -1,    -1,    -1,    -1,    24,    25,    -1,    -1,    -1,    -1,
      -1,    31,    32,    33,    34,    35,    36,    37,    24,    25,
      -1,    -1,    -1,    -1,    -1,    31,    32,    33,    34,    35,
      36,    37
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    20,    49,    53,    22,    23,    54,    55,    61,     0,
      50,    51,    52,    61,    21,    54,     3,    56,    57,    50,
       7,     3,    39,    44,    42,    43,     3,     5,     6,     9,
      13,    62,    63,    65,    67,    39,    58,    59,    61,     4,
      56,    44,    39,    39,    39,    39,    30,    64,    63,    47,
      58,    40,    42,     3,    46,    60,    45,     3,     4,    26,
      27,    28,    39,    66,    67,    67,    66,    66,    66,    66,
       8,    66,    40,    58,    43,     3,    39,    66,    66,    16,
      17,    18,    19,    24,    25,    31,    32,    33,    34,    35,
      36,    37,    45,    40,    40,    40,    40,    42,    38,    42,
      41,    60,    43,    66,    68,    40,    66,    66,    66,    66,
      66,    66,    66,    66,    66,    66,    66,    66,    66,    42,
      42,    10,    14,    53,    60,    43,    40,    62,    62,    68,
      11,    12,    15,    62,    42,    42,    12,    42
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
#line 63 "compiler.y"
    {
									program->setNext((yyvsp[(2) - (2)]));
									for (symbolNode *i = (yyvsp[(1) - (2)])->getTable();i;i=i->getNext())
										i->setAsGlobal();
									if((yyvsp[(1) - (2)])){
										program->setTable((yyvsp[(1) - (2)])->getTable());
										delete (yyvsp[(1) - (2)]);
									}
									return 0;
								;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 75 "compiler.y"
    { (yyval) = (yyvsp[(1) - (2)]); (yyvsp[(1) - (2)])->setNext((yyvsp[(2) - (2)])); ;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 76 "compiler.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 80 "compiler.y"
    {											
									(yyval) = (yyvsp[(1) - (6)]);
									(yyval)->setPTR2((yyvsp[(2) - (6)]));
									(yyvsp[(4) - (6)])->setReturnType((yyval)->getReturnType());
									(yyvsp[(4) - (6)])->setTable((yyval)->getTable());
									if((yyvsp[(3) - (6)])==nullptr){
										(yyvsp[(2) - (6)])->setNext((yyvsp[(4) - (6)]));
									}
									else{
										(yyvsp[(2) - (6)])->setNext((yyvsp[(3) - (6)]));
										SNode *i;
										for(i=(yyvsp[(3) - (6)]);i->getNext();i=i->getNext());
										i->setNext((yyvsp[(4) - (6)]));
									}
									Scope[0] = nullptr;
									delete (yyvsp[(5) - (6)]);
								;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 99 "compiler.y"
    {
									(yyval) = processFunctionHeader((yyvsp[(1) - (7)]), (yyvsp[(2) - (7)]), (yyvsp[(4) - (7)]), (yyvsp[(7) - (7)]), Scope[1]);
                                    if((yyval)==nullptr){
										Status = FAIL;
										(yyval) = new SNode(FUNC, (yyvsp[(2) - (7)])->getName(), (yyvsp[(2) - (7)])->lineNo, (yyvsp[(2) - (7)])->colNo);
										(yyval)->setReturnType((yyvsp[(1) - (7)])->getReturnType());
                                    }
                                    Scope[0] = (yyval);
                                    delete (yyvsp[(1) - (7)]);
                                    delete (yyvsp[(2) - (7)]);
                                    delete (yyvsp[(4) - (7)]);
                                    delete (yyvsp[(7) - (7)]);   
								;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 114 "compiler.y"
    {	
									symbolNode *Table = new symbolNode("&&&", -1);
                                    processDeclerations(Table, (yyvsp[(2) - (3)]));
									delete (yyvsp[(1) - (3)]);delete (yyvsp[(2) - (3)]);delete (yyvsp[(3) - (3)]);
									(yyval) = new SNode(-1, "&&&",(yyvsp[(2) - (3)])->lineNo, (yyvsp[(2) - (3)])->colNo);
									(yyval)->setTable(Table);
									if(!Scope[1]){
										Scope[1] = (yyval);
										Scope[1]->getTable()->install("main", INTEGER, -2);
									}	
								;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 125 "compiler.y"
    {
									(yyval)=nullptr;
									if(!Scope[1]){
										SNode *temp = new SNode(-1, "&&&", -1, -1);
										temp->setTable(new symbolNode("&&&", -1));
										Scope[1] = temp;
										Scope[1]->getTable()->install("main", INTEGER, -2);
									}
								;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 136 "compiler.y"
    {(yyval) = (yyvsp[(1) - (2)]); (yyvsp[(1) - (2)])->setNext((yyvsp[(2) - (2)]));;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 137 "compiler.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 141 "compiler.y"
    {(yyvsp[(1) - (3)])->setPTR3((yyvsp[(2) - (3)])); (yyval) = (yyvsp[(1) - (3)]);;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 145 "compiler.y"
    {(yyval) = (yyvsp[(1) - (3)]); (yyvsp[(1) - (3)])->setPTR3((yyvsp[(3) - (3)]));;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 146 "compiler.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 150 "compiler.y"
    {(yyval) = (yyvsp[(1) - (4)]); (yyval)->setPTR2((yyvsp[(3) - (4)]));(yyval)->setNodeType(FUNC);;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 151 "compiler.y"
    {(yyval) = (yyvsp[(1) - (4)]); (yyval)->setPTR2((yyvsp[(3) - (4)]));;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 152 "compiler.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 156 "compiler.y"
    {(yyval) = (yyvsp[(1) - (3)]); (yyvsp[(1) - (3)])->setNext((yyvsp[(3) - (3)]));;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 157 "compiler.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 158 "compiler.y"
    {(yyval) = nullptr;;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 162 "compiler.y"
    {(yyval) = (yyvsp[(1) - (2)]); (yyval)->setPTR3((yyvsp[(2) - (2)]));;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 166 "compiler.y"
    {(yyval) = (yyvsp[(2) - (4)]); (yyval)->setReturnType('&'); (yyval)->setNext((yyvsp[(4) - (4)]));;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 167 "compiler.y"
    {(yyval) = (yyvsp[(1) - (3)]); (yyval)->setNext((yyvsp[(3) - (3)]));;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 168 "compiler.y"
    {(yyval) = (yyvsp[(2) - (2)]); (yyval)->setReturnType('&');;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 169 "compiler.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 172 "compiler.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 173 "compiler.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 177 "compiler.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 178 "compiler.y"
    {(yyval) = nullptr;;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 181 "compiler.y"
    {(yyval) = (yyvsp[(1) - (2)]); (yyvsp[(1) - (2)])->setNext((yyvsp[(2) - (2)]));;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 182 "compiler.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 186 "compiler.y"
    {(yyval)=(yyvsp[(1) - (3)]); (yyvsp[(1) - (3)])->setPTR2((yyvsp[(2) - (3)]));;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 190 "compiler.y"
    {(yyval) = (yyvsp[(2) - (4)]); (yyval)->setPTR1((yyvsp[(1) - (4)])); (yyval)->setPTR2((yyvsp[(3) - (4)]));;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 191 "compiler.y"
    {(yyval) = (yyvsp[(1) - (5)]); (yyval)->setPTR2((yyvsp[(3) - (5)]));;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 192 "compiler.y"
    {
									(yyval) = (yyvsp[(1) - (5)]);
									(yyval)->setPTR2((yyvsp[(3) - (5)]));
								;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 197 "compiler.y"
    {
									(yyval) = (yyvsp[(1) - (8)]);
									(yyval)->setPTR1((yyvsp[(3) - (8)]));(yyval)->setPTR2((yyvsp[(6) - (8)]));
									delete (yyvsp[(5) - (8)]);delete (yyvsp[(7) - (8)]);
								;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 203 "compiler.y"
    {
									(yyval) = (yyvsp[(1) - (10)]);
									(yyval)->setPTR1((yyvsp[(3) - (10)]));(yyval)->setPTR2((yyvsp[(6) - (10)]));(yyval)->setPTR3((yyvsp[(8) - (10)]));
									delete (yyvsp[(5) - (10)]);delete (yyvsp[(7) - (10)]);	delete (yyvsp[(9) - (10)]);
								;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 209 "compiler.y"
    {
									(yyval) = (yyvsp[(1) - (8)]);
									(yyval)->setPTR1((yyvsp[(3) - (8)]));(yyval)->setPTR2((yyvsp[(6) - (8)]));
									delete (yyvsp[(5) - (8)]);	delete (yyvsp[(7) - (8)]);
								;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 217 "compiler.y"
    {(yyval) = (yyvsp[(2) - (3)]); (yyval)->setPTR1((yyvsp[(1) - (3)])); (yyval)->setPTR2((yyvsp[(3) - (3)])); (yyval)->setReturnType(INTEGER);;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 218 "compiler.y"
    {(yyval) = (yyvsp[(2) - (3)]); (yyval)->setPTR1((yyvsp[(1) - (3)])); (yyval)->setPTR2((yyvsp[(3) - (3)])); (yyval)->setReturnType(INTEGER);;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 219 "compiler.y"
    {(yyval) = (yyvsp[(2) - (3)]); (yyval)->setPTR1((yyvsp[(1) - (3)])); (yyval)->setPTR2((yyvsp[(3) - (3)])); (yyval)->setReturnType(INTEGER);;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 220 "compiler.y"
    {(yyval) = (yyvsp[(2) - (3)]); (yyval)->setPTR1((yyvsp[(1) - (3)])); (yyval)->setPTR2((yyvsp[(3) - (3)])); (yyval)->setReturnType(INTEGER);;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 221 "compiler.y"
    {(yyval) = (yyvsp[(2) - (3)]); (yyval)->setPTR1((yyvsp[(1) - (3)])); (yyval)->setPTR2((yyvsp[(3) - (3)])); (yyval)->setReturnType(INTEGER);;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 222 "compiler.y"
    {(yyval) = (yyvsp[(2) - (3)]); (yyval)->setPTR1((yyvsp[(1) - (3)])); (yyval)->setPTR2((yyvsp[(3) - (3)])); (yyval)->setReturnType(BOOLEAN);;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 223 "compiler.y"
    {(yyval) = (yyvsp[(2) - (3)]); (yyval)->setPTR1((yyvsp[(1) - (3)])); (yyval)->setPTR2((yyvsp[(3) - (3)])); (yyval)->setReturnType(BOOLEAN);;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 224 "compiler.y"
    {(yyval) = (yyvsp[(2) - (3)]); (yyval)->setPTR1((yyvsp[(1) - (3)])); (yyval)->setPTR2((yyvsp[(3) - (3)])); (yyval)->setReturnType(BOOLEAN);;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 225 "compiler.y"
    {(yyval) = (yyvsp[(2) - (3)]); (yyval)->setPTR1((yyvsp[(1) - (3)])); (yyval)->setPTR2((yyvsp[(3) - (3)])); (yyval)->setReturnType(BOOLEAN);;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 226 "compiler.y"
    {(yyval) = (yyvsp[(2) - (3)]); (yyval)->setPTR1((yyvsp[(1) - (3)])); (yyval)->setPTR2((yyvsp[(3) - (3)])); (yyval)->setReturnType(BOOLEAN);;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 227 "compiler.y"
    {(yyval) = (yyvsp[(2) - (3)]); (yyval)->setPTR1((yyvsp[(1) - (3)])); (yyval)->setPTR2((yyvsp[(3) - (3)])); (yyval)->setReturnType(BOOLEAN);;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 228 "compiler.y"
    {(yyval) = (yyvsp[(2) - (3)]); (yyval)->setPTR1((yyvsp[(1) - (3)])); (yyval)->setPTR2((yyvsp[(3) - (3)])); (yyval)->setReturnType(BOOLEAN);;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 229 "compiler.y"
    {(yyval) = (yyvsp[(2) - (3)]); (yyval)->setPTR1((yyvsp[(1) - (3)])); (yyval)->setPTR2((yyvsp[(3) - (3)])); (yyval)->setReturnType(BOOLEAN);;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 230 "compiler.y"
    {(yyval) = (yyvsp[(1) - (2)]); (yyval)->setPTR1((yyvsp[(2) - (2)])); (yyval)->setReturnType(BOOLEAN);;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 231 "compiler.y"
    {(yyval) = (yyvsp[(2) - (3)]);;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 232 "compiler.y"
    {(yyval) = (yyvsp[(1) - (1)]); (yyval)->setReturnType(BOOLEAN);;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 233 "compiler.y"
    {(yyval) = (yyvsp[(1) - (1)]); (yyval)->setReturnType(BOOLEAN);;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 234 "compiler.y"
    {(yyval) = (yyvsp[(1) - (1)]); (yyval)->setReturnType(INTEGER);;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 235 "compiler.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 236 "compiler.y"
    {
                                    (yyval) = variableAccess((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]), Scope, FUNCTION);
                                    if(!(yyval))
										Status = FAIL;
								;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 244 "compiler.y"
    {
                                    (yyval) = variableAccess((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]), Scope, ARRAY);
									if(!(yyval))
										Status = FAIL;
								;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 249 "compiler.y"
    {
									(yyval) = variableAccess((yyvsp[(1) - (1)]), nullptr, Scope, VARIABLE);
									if(!(yyval))
										Status = FAIL;
								;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 256 "compiler.y"
    { (yyval) = (yyvsp[(1) - (3)]); (yyval)->setNext((yyvsp[(3) - (3)])); ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 257 "compiler.y"
    { (yyval) = (yyvsp[(1) - (1)]); ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 258 "compiler.y"
    { (yyval) = nullptr; ;}
    break;



/* Line 1455 of yacc.c  */
#line 2037 "compiler.cpp"
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
#line 259 "compiler.y"


/*** Auxiliary functions section ***/

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
	if(yyparse() || std::min(Status,std::min(program->typeCheck(),checkFunctionDeclared(program)))<=WARN){
		delete program->getTable();
		delete program;
		std::cout << "SNodes Left = " << SNode::getCount() << "\n";
		std::cout << "symbolNodes Left = " << symbolNode::getCount() << "\n";
		return 1;
	}
	program->print();
	
	fprintf(output, "START\n");
	fprintf(output, "MOV BP, 2\n");
	fprintf(output, "MOV SP, 2\n");
	generateCode(program, output);
//	program->run();
	delete program->getTable();
	delete program;
	std::cout << "SNodes Left = " << SNode::getCount() << "\n";
	std::cout << "symbolNodes Left = " << symbolNode::getCount() << "\n";
	return 0;
}

