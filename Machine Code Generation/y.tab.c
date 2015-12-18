/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

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
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "code_gen.y" /* yacc.c:339  */

	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
	#include<stdbool.h>
	#include<malloc.h>
	
	#include "astree.h"

	symbol* stable[100];
	int id_count = 0; 
	int label_count = 0;
	int var_count = 0;
	int reg_count = 0;
	int find_id(char *);
	int getreg();
	void freereg(); 
	int getlabel();
	ast* statement(ast*, ast*);
	ast* assign(ast*, ast*, ast*);
	ast *cond(ast*, ast*, ast*);
	ast* loop(ast*, ast*);
	ast* read(ast*, ast*);
	ast* write(ast*);
	ast* expression(int, ast*, ast*);
	void make_node(ast*, int, int, char*, int, bool, ast*, ast*, ast*, symbol*);
	void make_symbol(symbol*, int, char*, int);
	int evaluate_ast(ast*);
	FILE *fp;

	#define INT 1
	#define BOOL 0
	#define ASSG 10
	#define VOID -1

	

#line 104 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
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

/* Copy the second part of user declarations.  */

#line 221 "y.tab.c" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  8
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   220

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  14
/* YYNRULES -- Number of rules.  */
#define YYNRULES  43
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  110

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   288

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      34,    35,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    36,
       2,    39,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    37,     2,    38,     2,     2,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    79,    79,    86,    89,    91,    94,    99,   104,   111,
     120,   123,   124,   127,   128,   129,   130,   131,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   149,   151,   153,   154,   157,   159,   162,   164,
     167,   170,   171,   174
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "BOOLE", "NUM", "ID", "BEG", "END",
  "DECL", "ENDDECL", "IF", "THEN", "ELSE", "ENDIF", "WHILE", "DO",
  "ENDWHILE", "READ", "WRITE", "PLUS", "MINUS", "MUL", "DIV", "AND", "OR",
  "NOT", "LEQ", "GEQ", "LTHAN", "GTHAN", "INTEGER", "BOOLEAN", "EQEQ",
  "NEQ", "'('", "')'", "';'", "'['", "']'", "'='", "$accept", "program",
  "declaration", "dlist", "dstmt", "body", "stmtlist", "stmt", "expr",
  "assignment", "condition", "loop", "read", "write", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,    40,    41,    59,    91,    93,    61
};
# endif

#define YYPACT_NINF -22

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-22)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      46,     3,    69,    53,    79,    84,    64,     3,   -22,   202,
     -22,    40,    68,   -22,   -22,   -21,    -2,    -2,    65,    85,
     117,   202,   -22,   -22,   -22,   -22,   -22,   -22,   121,   -22,
     124,    -2,    -2,   -22,   -22,    93,    -2,    -2,    59,   114,
     126,    -2,   -22,   -22,   101,   106,    29,   129,    -2,   -15,
     165,   202,    -2,    -2,    -2,    -2,    -2,    -2,    -2,    -2,
      -2,    -2,    -2,    -2,   202,    37,   182,   109,   118,   120,
     -22,    74,   -22,    96,    89,    89,   -22,   -22,    44,   -15,
     -11,   -11,   -11,   -11,     6,     6,   144,   127,    -2,   128,
     -22,   -22,    -2,   -22,   202,   136,   141,   -22,    94,   -22,
     147,   168,   -22,   -22,   143,   -22,   146,   154,   -22,   -22
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     5,     1,     0,
       2,     0,     0,     3,     4,     0,     0,     0,     0,     0,
       0,    12,    13,    14,    15,    16,    17,     6,     0,     7,
       0,     0,     0,    35,    34,    32,     0,     0,     0,     0,
       0,     0,    10,    11,     0,     0,     0,     0,     0,    30,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      36,     0,    31,     0,    18,    19,    21,    20,    24,    25,
      28,    29,    26,    27,    22,    23,     0,     0,     0,     0,
       8,     9,     0,    33,     0,     0,     0,    41,     0,    43,
       0,     0,    38,    40,     0,    37,     0,     0,    39,    42
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -22,   -22,   -22,   188,   -22,   -22,    -4,   -22,   -17,   -22,
     -22,   -22,   -22,   -22
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     3,     6,     7,    10,    20,    21,    38,    22,
      23,    24,    25,    26
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      39,    33,    34,    35,    52,    53,    54,    55,    52,    53,
      54,    55,    56,    57,    46,    47,    31,    43,    32,    49,
      50,    62,    63,    36,    66,    52,    53,    54,    55,    56,
      57,    71,    37,     4,     5,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    73,    52,    53,
      54,    55,    56,    57,     1,    58,    59,    60,    61,     9,
      86,    62,    63,    52,    53,    54,    55,    69,    57,     8,
      51,    98,    87,    13,    88,   100,    27,    28,    52,    53,
      54,    55,    56,    57,    11,    58,    59,    60,    61,    12,
     101,    62,    63,    52,    53,    54,    55,    56,    57,    40,
      58,    59,    60,    61,    29,    30,    62,    63,    94,    95,
      54,    55,    93,    52,    53,    54,    55,    56,    57,    41,
      58,    59,    60,    61,    42,    44,    62,    63,    45,    64,
      48,    65,   104,    52,    53,    54,    55,    56,    57,    67,
      58,    59,    60,    61,    68,    90,    62,    63,    52,    53,
      54,    55,    56,    57,    91,    58,    59,    60,    61,    92,
      96,    62,    63,    97,    99,    70,    52,    53,    54,    55,
      56,    57,   102,    58,    59,    60,    61,   103,   107,    62,
      63,   106,   108,   105,    52,    53,    54,    55,    56,    57,
     109,    58,    59,    60,    61,    14,     0,    62,    63,     0,
      72,    52,    53,    54,    55,    56,    57,    15,    58,    59,
      60,    61,    16,     0,    62,    63,    17,    89,     0,    18,
      19
};

static const yytype_int8 yycheck[] =
{
      17,     3,     4,     5,    19,    20,    21,    22,    19,    20,
      21,    22,    23,    24,    31,    32,    37,    21,    39,    36,
      37,    32,    33,    25,    41,    19,    20,    21,    22,    23,
      24,    48,    34,    30,    31,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    51,    19,    20,
      21,    22,    23,    24,     8,    26,    27,    28,    29,     6,
      64,    32,    33,    19,    20,    21,    22,    38,    24,     0,
      11,    88,    35,     9,    37,    92,    36,    37,    19,    20,
      21,    22,    23,    24,     5,    26,    27,    28,    29,     5,
      94,    32,    33,    19,    20,    21,    22,    23,    24,    34,
      26,    27,    28,    29,    36,    37,    32,    33,    12,    13,
      21,    22,    38,    19,    20,    21,    22,    23,    24,    34,
      26,    27,    28,    29,     7,     4,    32,    33,     4,    15,
      37,     5,    38,    19,    20,    21,    22,    23,    24,    38,
      26,    27,    28,    29,    38,    36,    32,    33,    19,    20,
      21,    22,    23,    24,    36,    26,    27,    28,    29,    39,
      16,    32,    33,    36,    36,    36,    19,    20,    21,    22,
      23,    24,    36,    26,    27,    28,    29,    36,    35,    32,
      33,    13,    36,    36,    19,    20,    21,    22,    23,    24,
      36,    26,    27,    28,    29,     7,    -1,    32,    33,    -1,
      35,    19,    20,    21,    22,    23,    24,     5,    26,    27,
      28,    29,    10,    -1,    32,    33,    14,    35,    -1,    17,
      18
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     8,    41,    42,    30,    31,    43,    44,     0,     6,
      45,     5,     5,     9,    43,     5,    10,    14,    17,    18,
      46,    47,    49,    50,    51,    52,    53,    36,    37,    36,
      37,    37,    39,     3,     4,     5,    25,    34,    48,    48,
      34,    34,     7,    46,     4,     4,    48,    48,    37,    48,
      48,    11,    19,    20,    21,    22,    23,    24,    26,    27,
      28,    29,    32,    33,    15,     5,    48,    38,    38,    38,
      36,    48,    35,    46,    48,    48,    48,    48,    48,    48,
      48,    48,    48,    48,    48,    48,    46,    35,    37,    35,
      36,    36,    39,    38,    12,    13,    16,    36,    48,    36,
      48,    46,    36,    36,    38,    36,    13,    35,    36,    36
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    40,    41,    42,    43,    43,    44,    44,    44,    44,
      45,    46,    46,    47,    47,    47,    47,    47,    48,    48,
      48,    48,    48,    48,    48,    48,    48,    48,    48,    48,
      48,    48,    48,    48,    48,    48,    49,    49,    50,    50,
      51,    52,    52,    53
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     3,     2,     1,     3,     3,     6,     6,
       3,     2,     1,     1,     1,     1,     1,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     3,     1,     4,     1,     1,     4,     7,     6,     8,
       6,     5,     8,     5
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
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
  int yytoken = 0;
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

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
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
      if (yytable_value_is_error (yyn))
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
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
     '$$ = $1'.

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
#line 79 "code_gen.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]); 
						fprintf(fp,"START\n");						
						evaluate_ast((yyval));
						fprintf(fp,"HALT\n");
						printf("\nComplete\n");exit(1);}
#line 1389 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 86 "code_gen.y" /* yacc.c:1646  */
    {}
#line 1395 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 89 "code_gen.y" /* yacc.c:1646  */
    {}
#line 1401 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 91 "code_gen.y" /* yacc.c:1646  */
    {}
#line 1407 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 94 "code_gen.y" /* yacc.c:1646  */
    {stable[id_count] = (symbol *)malloc(sizeof(symbol));
						make_symbol(stable[id_count],INT,(yyvsp[-1])->name,0);
						free((yyvsp[-1]));								
						id_count++;}
#line 1416 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 99 "code_gen.y" /* yacc.c:1646  */
    {stable[id_count] = (symbol *)malloc(sizeof(symbol));
						make_symbol(stable[id_count],BOOL,(yyvsp[-1])->name,0);	
						free((yyvsp[-1]));			
						id_count++;}
#line 1425 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 104 "code_gen.y" /* yacc.c:1646  */
    {if((yyvsp[-2])->datatype!=INT)
							yyerror();
						stable[id_count] = (symbol *)malloc(sizeof(symbol));
						make_symbol(stable[id_count],INT,(yyvsp[-4])->name,(yyvsp[-2])->int_value);	
						free((yyvsp[-4])); free((yyvsp[-2]));						
						id_count++;}
#line 1436 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 111 "code_gen.y" /* yacc.c:1646  */
    {if((yyvsp[-2])->datatype!=INT)
							yyerror();
						stable[id_count] = (symbol *)malloc(sizeof(symbol));
						make_symbol(stable[id_count],BOOL,(yyvsp[-4])->name,(yyvsp[-2])->int_value);	
						free((yyvsp[-4])); free((yyvsp[-2]));						
						id_count++;}
#line 1447 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 120 "code_gen.y" /* yacc.c:1646  */
    {(yyval)=(yyvsp[-1]);}
#line 1453 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 123 "code_gen.y" /* yacc.c:1646  */
    {(yyval) = statement((yyvsp[-1]),(yyvsp[0]));}
#line 1459 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 124 "code_gen.y" /* yacc.c:1646  */
    {(yyval)=(yyvsp[0]);}
#line 1465 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 127 "code_gen.y" /* yacc.c:1646  */
    {(yyval)=(yyvsp[0]);}
#line 1471 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 128 "code_gen.y" /* yacc.c:1646  */
    {(yyval)=(yyvsp[0]);}
#line 1477 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 129 "code_gen.y" /* yacc.c:1646  */
    {(yyval)=(yyvsp[0]);}
#line 1483 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 130 "code_gen.y" /* yacc.c:1646  */
    {(yyval)=(yyvsp[0]);}
#line 1489 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 131 "code_gen.y" /* yacc.c:1646  */
    {(yyval)=(yyvsp[0]);}
#line 1495 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 134 "code_gen.y" /* yacc.c:1646  */
    {(yyval) = expression(PLUS,(yyvsp[-2]),(yyvsp[0]));}
#line 1501 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 135 "code_gen.y" /* yacc.c:1646  */
    {(yyval) = expression(MINUS,(yyvsp[-2]),(yyvsp[0]));}
#line 1507 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 136 "code_gen.y" /* yacc.c:1646  */
    {(yyval) = expression(DIV,(yyvsp[-2]),(yyvsp[0]));}
#line 1513 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 137 "code_gen.y" /* yacc.c:1646  */
    {(yyval) = expression(MUL,(yyvsp[-2]),(yyvsp[0]));}
#line 1519 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 138 "code_gen.y" /* yacc.c:1646  */
    {(yyval) = expression(EQEQ,(yyvsp[-2]),(yyvsp[0]));}
#line 1525 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 139 "code_gen.y" /* yacc.c:1646  */
    {(yyval) = expression(NEQ,(yyvsp[-2]),(yyvsp[0]));}
#line 1531 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 140 "code_gen.y" /* yacc.c:1646  */
    {(yyval) = expression(AND,(yyvsp[-2]),(yyvsp[0]));}
#line 1537 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 141 "code_gen.y" /* yacc.c:1646  */
    {(yyval) = expression(OR,(yyvsp[-2]),(yyvsp[0]));}
#line 1543 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 142 "code_gen.y" /* yacc.c:1646  */
    {(yyval) = expression(LTHAN,(yyvsp[-2]),(yyvsp[0]));}
#line 1549 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 143 "code_gen.y" /* yacc.c:1646  */
    {(yyval) = expression(GTHAN,(yyvsp[-2]),(yyvsp[0]));}
#line 1555 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 144 "code_gen.y" /* yacc.c:1646  */
    {(yyval) = expression(LEQ,(yyvsp[-2]),(yyvsp[0]));}
#line 1561 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 145 "code_gen.y" /* yacc.c:1646  */
    {(yyval) = expression(GEQ,(yyvsp[-2]),(yyvsp[0]));}
#line 1567 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 146 "code_gen.y" /* yacc.c:1646  */
    {(yyval) = expression(NOT,(yyvsp[-1]),NULL);}
#line 1573 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 147 "code_gen.y" /* yacc.c:1646  */
    {(yyval)=(yyvsp[-1]);}
#line 1579 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 149 "code_gen.y" /* yacc.c:1646  */
    {(yyval) = expression(ID,(yyvsp[0]),NULL);}
#line 1585 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 151 "code_gen.y" /* yacc.c:1646  */
    {(yyval) = expression(ID,(yyvsp[-3]),(yyvsp[-1]));}
#line 1591 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 153 "code_gen.y" /* yacc.c:1646  */
    {(yyval)=(yyvsp[0]);}
#line 1597 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 154 "code_gen.y" /* yacc.c:1646  */
    {(yyval)=(yyvsp[0]);}
#line 1603 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 157 "code_gen.y" /* yacc.c:1646  */
    {(yyval) = assign((yyvsp[-3]),(yyvsp[-1]),NULL);}
#line 1609 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 159 "code_gen.y" /* yacc.c:1646  */
    {(yyval) = assign((yyvsp[-6]),(yyvsp[-4]),(yyvsp[-1]));}
#line 1615 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 162 "code_gen.y" /* yacc.c:1646  */
    {(yyval) = cond((yyvsp[-4]),(yyvsp[-2]),NULL);}
#line 1621 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 164 "code_gen.y" /* yacc.c:1646  */
    {(yyval) = cond((yyvsp[-6]),(yyvsp[-4]),(yyvsp[-2]));}
#line 1627 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 167 "code_gen.y" /* yacc.c:1646  */
    {(yyval) = loop((yyvsp[-4]),(yyvsp[-2]));}
#line 1633 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 170 "code_gen.y" /* yacc.c:1646  */
    {(yyval) = read((yyvsp[-2]),NULL);}
#line 1639 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 171 "code_gen.y" /* yacc.c:1646  */
    {(yyval) = read((yyvsp[-5]),(yyvsp[-3]));}
#line 1645 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 174 "code_gen.y" /* yacc.c:1646  */
    {(yyval) = write((yyvsp[-2]));}
#line 1651 "y.tab.c" /* yacc.c:1646  */
    break;


#line 1655 "y.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
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

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
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
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
#line 176 "code_gen.y" /* yacc.c:1906  */


int getreg() {return reg_count++;}
void freereg() {reg_count--;}
int getlabel() {return label_count++;}

int evaluate_ast(ast* node)
{
	int i,r1,r2,r3,r4,l1,l2,l3,l4,temp,add;

	switch(node->nodetype)
	{
		case VOID: 	evaluate_ast(node->ptr1); evaluate_ast(node->ptr2);
				break;
		case ASSG:	if(node->ptr3==NULL)
				{
					i = find_id(node->ptr1->name);
					
					add = stable[i]->store;
					r1 = evaluate_ast(node->ptr2);

					fprintf(fp, "MOV [%d], R%d\n",add,r1);

					freereg();
					return 1;
				}
				else
				{
					i = find_id(node->ptr1->name);
					
					add = stable[i]->store;
					r1 = evaluate_ast(node->ptr2);
					r2 = evaluate_ast(node->ptr3);
					r3 = getreg();

					fprintf(fp, "MOV R%d, %d\n",r3,add);
					fprintf(fp, "ADD R%d, R%d\n",r1,r3);
					fprintf(fp, "MOV [R%d], R%d\n",r1,r2);
					
					freereg();
					freereg();
					freereg();

					return 1;					
				}
				break;
		case IF:	if(node->ptr3==NULL)
				{
					l1 = getlabel();
					r1 = evaluate_ast(node->ptr1);
					fprintf(fp, "JZ R%d, L%d\n",r1,l1);
					freereg();
					evaluate_ast(node->ptr2);
					fprintf(fp, "L%d:\n", l1);
					return 1;
				}
				else
				{
					l1 = getlabel();
					l2 = getlabel();
					r1 = evaluate_ast(node->ptr1);
					fprintf(fp, "JZ R%d, L%d\n",r1,l1);
					freereg();
					evaluate_ast(node->ptr2);
					fprintf(fp, "JMP L%d\n", l2);
					fprintf(fp, "L%d:\n", l1);
					evaluate_ast(node->ptr3);
					fprintf(fp, "L%d:\n", l2);
					return 1;
				}
				break;


		case WHILE:	l1 = getlabel();
				l2 = getlabel();
				fprintf(fp,"L%d:\n",l1);
				r1 = evaluate_ast(node->ptr1);
				fprintf(fp, "JZ R%d, L%d\n",r1,l2);
				freereg();
				evaluate_ast(node->ptr2);
				fprintf(fp, "JMP L%d\n", l1);
				fprintf(fp, "L%d:\n", l2);
				return 1;
				break;

		case READ:	if(node->ptr2==NULL)
				{
					i = find_id(node->ptr1->name);
					
					add = stable[i]->store;
					r1 = getreg();

					fprintf(fp, "IN R%d\n",r1);
					fprintf(fp, "MOV [%d], R%d\n",add,r1);

					freereg();
					return 1;
				}
				else
				{
					i = find_id(node->ptr1->name);
					
					add = stable[i]->store;
					r1 = evaluate_ast(node->ptr2);
					r2 = getreg();

					fprintf(fp, "MOV R%d, %d\n",r2,add);
					fprintf(fp, "ADD R%d, R%d\n",r1,r2);
					fprintf(fp, "IN R%d\n",r2);
					fprintf(fp, "MOV [R%d], R%d\n",r1,r2);
					
					freereg();
					freereg();

					return 1;					
				}
				break;

		case WRITE:	r1 = evaluate_ast(node->ptr1);
				fprintf(fp,"OUT R%d\n",r1);
				freereg();
				break;

		case PLUS:	r1 = evaluate_ast(node->ptr1); r2 = evaluate_ast(node->ptr2);
				fprintf(fp,"ADD R%d, R%d\n",r1,r2);
				freereg();
				return r1;
				break;
		case MINUS:	r1 = evaluate_ast(node->ptr1); r2 = evaluate_ast(node->ptr2);
				fprintf(fp,"SUB R%d, R%d\n",r1,r2);
				freereg();
				return r1;
				break;
		case MUL:	r1 = evaluate_ast(node->ptr1); r2 = evaluate_ast(node->ptr2);
				fprintf(fp,"MUL R%d, R%d\n",r1,r2);
				freereg();
				return r1;
				break;
		case DIV:	r1 = evaluate_ast(node->ptr1); r2 = evaluate_ast(node->ptr2);
				fprintf(fp,"DIV R%d, R%d\n",r1,r2);
				freereg();
				return r1;
				break;
		case LTHAN:	r1 = evaluate_ast(node->ptr1); r2 = evaluate_ast(node->ptr2);
				fprintf(fp,"LT R%d, R%d\n",r1,r2);
				freereg();
				return r1;
				break;
		case GTHAN:	r1 = evaluate_ast(node->ptr1); r2 = evaluate_ast(node->ptr2);
				fprintf(fp,"GT R%d, R%d\n",r1,r2);
				freereg();
				return r1;
				break;
		case LEQ:	r1 = evaluate_ast(node->ptr1); r2 = evaluate_ast(node->ptr2);
				fprintf(fp,"LE R%d, R%d\n",r1,r2);
				freereg();
				return r1;
				break;		
		case GEQ:	r1 = evaluate_ast(node->ptr1); r2 = evaluate_ast(node->ptr2);
				fprintf(fp,"GE R%d, R%d\n",r1,r2);
				freereg();
				return r1;
				break;
		case EQEQ:	r1 = evaluate_ast(node->ptr1); r2 = evaluate_ast(node->ptr2);
				fprintf(fp,"EQ R%d, R%d\n",r1,r2);
				freereg();
				return r1;
				break;
		case NEQ:	r1 = evaluate_ast(node->ptr1); r2 = evaluate_ast(node->ptr2);
				fprintf(fp,"NE R%d, R%d\n",r1,r2);
				freereg();
				return r1;
				break;
		case ID:	if(node->ptr1==NULL)
				{
					i = find_id(node->name);					
					temp = stable[i]->store;
					
					r1 = getreg();
					fprintf(fp,"MOV R%d, [%d]\n",r1,temp);

					return r1;	
				}
				else
				{
					i = find_id(node->name);		
					
					r1 = getreg();
					r2 = getreg();
					r3 = evaluate_ast(node->ptr1);		
				
					fprintf(fp,"MOV R%d, %d\n",r2,stable[i]->store); 
					fprintf(fp,"ADD R%d, R%d\n",r2,r3);
					fprintf(fp,"MOV R%d,[R%d]\n",r1,r2);

					freereg();			
					freereg();		
					return r1;
				}
				break;
		case NUM:	r1 = getreg();
				fprintf(fp,"MOV R%d, %d\n",r1,node->int_value);
				return r1;
		case BOOLE:	r1 = getreg();
				fprintf(fp,"MOV R%d, %d\n",r1,node->bool_value);
				return r1;		
				
		default:	break;
	}
	return 1;
}


void make_node(ast* node, int dtype, int ntype, char* na, int int_val, bool bool_val, ast* p1, ast* p2, ast* p3, symbol *s)
{
	node->datatype = dtype;
	node->nodetype = ntype;
	if(na!=NULL)
		strcpy(node->name,na);
	node->int_value = int_val;
	node->bool_value = bool_val;

	node->ptr1 = p1; node->ptr2 = p2; node->ptr3 = p3;
	node->Gentry = s;
}

void make_symbol(symbol* sym, int dtype, char *n, int sz)
{
	sym->datatype = dtype;
	if(n!=NULL)
		strcpy(sym->name,n);
	sym->size = sz;
	sym->store = var_count;
	var_count = var_count + sym->size;
}

int find_id(char* str)
{
	int j;	
	for(j=0;j<id_count;j++)
	{
		if(strcmp(str,stable[j]->name)==0)
			return j;
	}
	return id_count;
}



ast* statement(ast* a, ast* b)
{
	ast* ptr;
	ptr =(ast *)malloc(sizeof(ast));
	make_node(ptr,VOID,VOID,NULL,0,false,a,b,NULL,NULL);

	return ptr;
}

ast* assign(ast* a, ast* b, ast* c)
{
	int i = find_id(a->name);

	if(i!=id_count)
		a->Gentry = stable[i];
	else
		yyerror();

	a->datatype = stable[i]->datatype;
	
	ast* ptr;

	if(c == NULL)
	{
		if(a->datatype != b->datatype)
			yyerror();

		ptr =(ast *)malloc(sizeof(ast));
		make_node(ptr, VOID,ASSG,NULL,0,false,a,b,NULL,NULL);
	}
	else
	{
		if(a->datatype != c->datatype)
			yyerror();

		if(b->datatype!=INT)
			yyerror();
		ptr =(ast *)malloc(sizeof(ast));
		make_node(ptr, VOID,ASSG,NULL,0,false,a,b,c,NULL);
	}
	
	return ptr;
}	

ast *cond(ast* a, ast* b, ast* c)
{
	if(a->datatype!=BOOL || b->datatype!=VOID)
		yyerror();

	ast* ptr;

	if(c==NULL)
	{
		ptr =(ast *)malloc(sizeof(ast));
		make_node(ptr, VOID,IF,NULL,0,false,a,b,NULL,NULL);
	}
	else
	{
		if(c->datatype!=VOID)
			yyerror();
		ptr =(ast *)malloc(sizeof(ast));
		make_node(ptr, VOID,IF,NULL,0,false,a,b,c,NULL);
	}
		
	return ptr;
}

ast* loop(ast *a, ast* b)
{
	if(a->datatype!=BOOL || b->datatype!=VOID)
		yyerror();

	ast* ptr;

	ptr =(ast *)malloc(sizeof(ast));
	make_node(ptr, VOID,WHILE,NULL,0,false,a,b,NULL,NULL);

	return ptr;
}

ast* read(ast* a, ast* b)
{
	int i = find_id(a->name);

	if(i!=id_count || (b->datatype!=INT))
		a->Gentry = stable[i];
	else
		yyerror();

	a->datatype = stable[i]->datatype;

	ast* ptr;

	ptr =(ast *)malloc(sizeof(ast));
	if(b!=NULL)
		make_node(ptr, VOID,READ,NULL,0,false,a,b,NULL,NULL);
	else
		make_node(ptr, VOID,READ,NULL,0,false,a,NULL,NULL,NULL);

	return ptr;
}

ast* write(ast* a)
{
	ast* ptr;

	ptr =(ast *)malloc(sizeof(ast));
	make_node(ptr, VOID,WRITE,NULL,0,false,a,NULL,NULL,NULL);

	return ptr;
}

ast* expression(int type, ast* a, ast* b)
{
	ast *ptr;
	int i;
	switch(type)
	{
		case PLUS: 	if((a->datatype!=INT) || (b->datatype!=INT))
					yyerror();
				ptr =(ast *)malloc(sizeof(ast));
				make_node(ptr, INT,PLUS,NULL,0,false,a,b,NULL,NULL);
				break;				
		case MINUS: 	if((a->datatype!=INT) || (b->datatype!=INT))
					yyerror();
				ptr =(ast *)malloc(sizeof(ast));
				make_node(ptr, INT,MINUS,NULL,0,false,a,b,NULL,NULL);
				break;			
		case MUL: 	if((a->datatype!=INT) || (b->datatype!=INT))
					yyerror();
				ptr =(ast *)malloc(sizeof(ast));
				make_node(ptr, INT,MUL,NULL,0,false,a,b,NULL,NULL);
				break;			
		case DIV: 	if((a->datatype!=INT) || (b->datatype!=INT))
					yyerror();
				ptr =(ast *)malloc(sizeof(ast));
				make_node(ptr, INT,DIV,NULL,0,false,a,b,NULL,NULL);
				break;	
		case LTHAN: 	if((a->datatype!=INT) || (b->datatype!=INT))
					yyerror();
				ptr =(ast *)malloc(sizeof(ast));
				make_node(ptr, BOOL,LTHAN,NULL,0,false,a,b,NULL,NULL);
				break;			
		case GTHAN: 	if((a->datatype!=INT) || (b->datatype!=INT))
					yyerror();
				ptr =(ast *)malloc(sizeof(ast));
				make_node(ptr, BOOL,GTHAN,NULL,0,false,a,b,NULL,NULL);
				break;
		case LEQ: 	if((a->datatype!=INT) || (b->datatype!=INT))
					yyerror();
				ptr =(ast *)malloc(sizeof(ast));
				make_node(ptr, BOOL,LEQ,NULL,0,false,a,b,NULL,NULL);
				break;			
		case GEQ: 	if((a->datatype!=INT) || (b->datatype!=INT))
					yyerror();
				ptr =(ast *)malloc(sizeof(ast));
				make_node(ptr, BOOL,GEQ,NULL,0,false,a,b,NULL,NULL);
				break;		
		case EQEQ: 	if((a->datatype!=INT) || (b->datatype!=INT))
					yyerror();
				ptr =(ast *)malloc(sizeof(ast));
				make_node(ptr, BOOL,EQEQ,NULL,0,false,a,b,NULL,NULL);
				break;								
		case NEQ: 	if((a->datatype!=INT) || (b->datatype!=INT))
					yyerror();
				ptr =(ast *)malloc(sizeof(ast));
				make_node(ptr, BOOL,NEQ,NULL,0,false,a,b,NULL,NULL);
				break;	
		case AND: 	if((a->datatype!=BOOL) || (b->datatype!=BOOL))
					yyerror();
				ptr =(ast *)malloc(sizeof(ast));
				make_node(ptr, BOOL,AND,NULL,0,false,a,b,NULL,NULL);
				break;			
		case OR: 	if((a->datatype!=BOOL) || (b->datatype!=BOOL))
					yyerror();
				ptr =(ast *)malloc(sizeof(ast));
				make_node(ptr, BOOL,OR,NULL,0,false,a,b,NULL,NULL);
				break;			
		case NOT: 	if(a->datatype!=BOOL)
					yyerror();
				ptr =(ast *)malloc(sizeof(ast));
				make_node(ptr, BOOL,NOT,NULL,0,false,a,NULL,NULL,NULL);
				break;
		case ID:	i = find_id(a->name);
				if(i!=id_count)
					a->Gentry = stable[i];
				else
					yyerror();

				a->datatype = stable[i]->datatype;

				if(b!=NULL)
				{
					if(b->datatype != INT)
						yyerror();
					a->ptr1 = b;
				}
	
				ptr = a;
				break;

		default: 	break;
	}
	return ptr;
} 	
		
    
yyerror()
{
	printf("\nError here\n");
}

main()
{
	fp = fopen("target.sil","w+");
	yyparse();
	fclose(fp);
	return 1;
}
