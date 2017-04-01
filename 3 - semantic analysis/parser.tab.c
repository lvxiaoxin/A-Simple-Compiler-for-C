/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TYPE = 258,
     INT = 259,
     FLOAT = 260,
     ID = 261,
     SEMI = 262,
     COMMA = 263,
     ASSIGNOP = 264,
     RELOP = 265,
     PLUS = 266,
     MINUS = 267,
     STAR = 268,
     DIV = 269,
     AND = 270,
     OR = 271,
     DOT = 272,
     NOT = 273,
     LP = 274,
     RP = 275,
     LB = 276,
     RB = 277,
     LC = 278,
     RC = 279,
     STRUCT = 280,
     RETURN = 281,
     IF = 282,
     ELSE = 283,
     WHILE = 284,
     LOWER_THAN_ELSE = 285,
     UMINUS = 286
   };
#endif
/* Tokens.  */
#define TYPE 258
#define INT 259
#define FLOAT 260
#define ID 261
#define SEMI 262
#define COMMA 263
#define ASSIGNOP 264
#define RELOP 265
#define PLUS 266
#define MINUS 267
#define STAR 268
#define DIV 269
#define AND 270
#define OR 271
#define DOT 272
#define NOT 273
#define LP 274
#define RP 275
#define LB 276
#define RB 277
#define LC 278
#define RC 279
#define STRUCT 280
#define RETURN 281
#define IF 282
#define ELSE 283
#define WHILE 284
#define LOWER_THAN_ELSE 285
#define UMINUS 286




/* Copy the first part of user declarations.  */
#line 1 "./parser.y"

	#include<stdio.h>
	#include"tree.h"
	#include"table.h"
	char * _structName = NULL;
	char * _funcName = NULL;
	void loginVar(TreeNode * decList){
		TreeNode * dec = decList->child;
		TreeNode * id = dec->child;
		int dimension = -1;
		while (id->child !=NULL){
			id = id->child;
			dimension = dimension +1;
		}
		if (findVarTable(id->text)!=NULL || findStructTable(id->text)!=NULL){
			printf("Error type 3 at Line %d: Redefined variable \"%s\".\n",id->lineno,id->text);
		}else{
			int type = -1;
			if (decList->_struct == NULL){
				type = decList->_type;
			} else{
				type = 3;
			}
			insertVarTable(type,id->text,decList->_struct,dimension);	
		} 
		if (dec->brother !=NULL && dec->brother->brother != NULL){
			dec->brother->brother->_type = decList->_type;
			dec->brother->brother->_struct = decList->_struct;
			loginVar(dec->brother->brother);
		}
	}

	 void loginVars(TreeNode * defList){
                TreeNode * def = defList->child;
                if ( def != NULL){
                        loginVar(def->child->brother);
			loginVars(def->brother);
                }
        }
	 void loginStructVar(TreeNode * decList,char * structName){
                TreeNode * dec = decList->child;
                TreeNode * id = dec->child;
                int dimension = -1;
                while (id->child !=NULL){
                        id = id->child;
                        dimension = dimension +1;
                }
                if (findStructVar(id->text,structName)!=NULL){
                        printf("Error type 15 at Line %d: Redefined variable \"%s\" in struct \"%s\".\n",id->lineno,id->text,structName);
                }else{
			int type = -1;
                        if (decList->_struct == NULL){
                                type = decList->_type;
                        } else{
                                type = 3;
                        }
                        insertStructVar(type,id->text,decList->_struct,dimension,structName);
                }
                if (dec->brother !=NULL && dec->brother->brother != NULL){
                        dec->brother->brother->_type = decList->_type;
                        loginStructVar(dec->brother->brother,structName);
                }
        }
         void loginStructVars(TreeNode * defList,char * structName){
                TreeNode * def = defList->child;
                if ( def != NULL){
                        loginStructVar(def->child->brother,structName);
                        loginStructVars(def->brother,structName);
                }
        }
	

	 void loginParamVar(TreeNode * varDec,char * funcName){
                TreeNode * id = varDec;
                int dimension = -1;
                while (id->child !=NULL){
                        id = id->child;
                        dimension = dimension +1;
                }
                if (findVarTable(id->text)!=NULL || findStructTable(id->text)!=NULL){
                        printf("Error type 3 at Line %d: Redefined variable \"%s\".\n",id->lineno,id->text);
                }else{
                        int type = -1;
                        if (varDec->_struct == NULL){
                                type = varDec->_type;
                        } else{
                                type = 3;
                        }
                        insertFuncParam(type,id->text,varDec->_struct,dimension,funcName);
                }
        }
	void loginParamVars(TreeNode * VarList,char * funcName){
		TreeNode * paramDec = VarList->child;
		if (paramDec != NULL){
			loginParamVar(paramDec->child->brother,funcName);
			if (paramDec->brother != NULL && paramDec->brother->brother != NULL){
				loginParamVars(paramDec->brother->brother,funcName);
			}
		}
	}
	void paramMatch(TreeNode * args,FuncNode * funcNode){
		int v=1;
		TreeNode * t = args->child;
		while (t->brother!=NULL){
			v++;
			t = t->brother->brother->child;
		}
		if (funcNode->paramNum!= v){
			printf("Error type 9 at Line %d: Params in function \"%s\" can't match.\n",args->lineno,funcNode->funcName);
		} else {
			VarNode * p = funcNode->beginParam;
			TreeNode * a = args;
			 while ( 1 == 1 ){
	                        TreeNode * exp = a->child;
                	        if (exp->_type != p-> type || exp->_struct != p->structType || exp->_dim != p->dimension){
                        	        printf("Error type 9 at Line %d: Params in function \"%s\" can't match.\n",exp->lineno,funcNode->funcName);
                        	}
				if (exp->brother == NULL){
					break;
				} else {
	                                a = exp->brother->brother;
        	                	p = p->next;
				}
                	}
		}
}


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

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 128 "./parser.y"
{
	struct treenode * t;
}
/* Line 193 of yacc.c.  */
#line 290 "parser.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 303 "parser.tab.c"

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
# if defined YYENABLE_NLS && YYENABLE_NLS
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
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
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
  yytype_int16 yyss;
  YYSTYPE yyvs;
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
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  13
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   218

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  32
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  62
/* YYNRULES -- Number of states.  */
#define YYNSTATES  114

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   286

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     6,     9,    13,    16,    19,    22,
      24,    28,    30,    32,    36,    39,    43,    44,    46,    48,
      50,    55,    60,    64,    68,    70,    73,    78,    80,    81,
      84,    87,    89,    93,    99,   107,   113,   114,   117,   121,
     123,   127,   129,   133,   137,   141,   145,   149,   153,   157,
     161,   165,   169,   172,   175,   180,   184,   189,   193,   195,
     197,   199,   203
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      33,     0,    -1,    34,    -1,    -1,    35,    34,    -1,    38,
      37,     7,    -1,    38,     7,    -1,    36,    47,    -1,    38,
      44,    -1,    43,    -1,    43,     8,    37,    -1,     3,    -1,
      39,    -1,    40,    51,    24,    -1,    25,    42,    -1,    25,
      41,    23,    -1,    -1,     6,    -1,     6,    -1,     6,    -1,
      43,    21,     4,    22,    -1,     6,    19,    45,    20,    -1,
       6,    19,    20,    -1,    46,     8,    45,    -1,    46,    -1,
      38,    43,    -1,    48,    51,    49,    24,    -1,    23,    -1,
      -1,    50,    49,    -1,    55,     7,    -1,    47,    -1,    26,
      55,     7,    -1,    27,    19,    55,    20,    50,    -1,    27,
      19,    55,    20,    50,    28,    50,    -1,    29,    19,    55,
      20,    50,    -1,    -1,    52,    51,    -1,    38,    53,     7,
      -1,    54,    -1,    54,     8,    53,    -1,    43,    -1,    43,
       9,    55,    -1,    55,     9,    55,    -1,    55,    15,    55,
      -1,    55,    11,    55,    -1,    55,    16,    55,    -1,    55,
      10,    55,    -1,    55,    12,    55,    -1,    55,    13,    55,
      -1,    55,    14,    55,    -1,    19,    55,    20,    -1,    12,
      55,    -1,    18,    55,    -1,     6,    19,    56,    20,    -1,
       6,    19,    20,    -1,    55,    21,    55,    22,    -1,    55,
      17,     6,    -1,     6,    -1,     4,    -1,     5,    -1,    55,
       8,    56,    -1,    55,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   152,   152,   156,   157,   159,   160,   161,   163,   168,
     169,   171,   173,   177,   178,   187,   199,   200,   202,   204,
     205,   207,   215,   223,   224,   226,   231,   233,   236,   237,
     239,   240,   241,   251,   252,   253,   255,   256,   258,   269,
     270,   272,   273,   275,   284,   285,   294,   295,   296,   305,
     314,   323,   324,   325,   326,   337,   351,   365,   378,   389,
     393,   399,   400
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TYPE", "INT", "FLOAT", "ID", "SEMI",
  "COMMA", "ASSIGNOP", "RELOP", "PLUS", "MINUS", "STAR", "DIV", "AND",
  "OR", "DOT", "NOT", "LP", "RP", "LB", "RB", "LC", "RC", "STRUCT",
  "RETURN", "IF", "ELSE", "WHILE", "LOWER_THAN_ELSE", "UMINUS", "$accept",
  "Program", "ExtDefList", "ExtDef", "FuncBegin", "ExtDecList",
  "Specifier", "StructSpecifier", "StructSpecifierBegin", "OptTag", "Tag",
  "VarDec", "FunDec", "VarList", "ParamDec", "CompSt", "CompStBegin",
  "StmtList", "Stmt", "DefList", "Def", "DecList", "Dec", "Exp", "Args", 0
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
     285,   286
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    32,    33,    34,    34,    35,    35,    35,    36,    37,
      37,    38,    38,    39,    39,    40,    41,    41,    42,    43,
      43,    44,    44,    45,    45,    46,    47,    48,    49,    49,
      50,    50,    50,    50,    50,    50,    51,    51,    52,    53,
      53,    54,    54,    55,    55,    55,    55,    55,    55,    55,
      55,    55,    55,    55,    55,    55,    55,    55,    55,    55,
      55,    56,    56
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     3,     2,     2,     2,     1,
       3,     1,     1,     3,     2,     3,     0,     1,     1,     1,
       4,     4,     3,     3,     1,     2,     4,     1,     0,     2,
       2,     1,     3,     5,     7,     5,     0,     2,     3,     1,
       3,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     2,     4,     3,     4,     3,     1,     1,
       1,     3,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,    11,    16,     0,     2,     3,     0,     0,    12,    36,
      18,     0,    14,     1,     4,    27,     7,    36,    19,     6,
       0,     9,     8,     0,     0,    36,    15,    28,     0,     5,
       0,     0,    19,    41,     0,    39,    13,    37,    59,    60,
      58,     0,     0,     0,     0,     0,     0,    31,     0,    28,
       0,    22,     0,     0,    24,    10,     0,     0,    38,     0,
       0,    52,    53,     0,     0,     0,     0,    26,    29,    30,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      25,    21,     0,    20,    42,    40,    55,    62,     0,    51,
      32,     0,     0,    43,    47,    45,    48,    49,    50,    44,
      46,    57,     0,    23,     0,    54,     0,     0,    56,    61,
      33,    35,     0,    34
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,     5,     6,    20,    23,     8,     9,    11,
      12,    21,    22,    53,    54,    47,    17,    48,    49,    24,
      25,    34,    35,    50,    88
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -95
static const yytype_int16 yypact[] =
{
      18,   -95,     8,    23,   -95,    18,    21,    40,   -95,    18,
      34,    35,   -95,   -95,   -95,   -95,   -95,    18,    42,   -95,
      20,    -2,   -95,    66,    49,    18,   -95,    36,     4,   -95,
      66,    71,   -95,     1,    69,    70,   -95,   -95,   -95,   -95,
      60,    62,    62,    62,    62,    68,    78,   -95,    74,    36,
      79,   -95,    66,    90,   103,   -95,   102,    62,   -95,    66,
      65,    -6,    -6,   133,    92,    62,    62,   -95,   -95,   -95,
      62,    62,    62,    62,    62,    62,    62,    62,   120,    62,
      91,   -95,    18,   -95,   172,   -95,   -95,   106,   105,   -95,
     -95,   146,   159,   172,   195,   197,   197,    -6,    -6,    39,
     184,   -95,   119,   -95,    62,   -95,    36,    36,   -95,   -95,
     109,   -95,    36,   -95
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -95,   -95,   134,   -95,   -95,   108,     0,   -95,   -95,   -95,
     -95,   -14,   -95,    82,   -95,   145,   -95,   116,   -94,    -9,
     -95,    93,   -95,   -40,    73
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -18
static const yytype_int8 yytable[] =
{
       7,    61,    62,    63,    64,     7,    30,     1,    27,    33,
      57,    78,   110,   111,    10,    79,    37,    84,   113,    31,
      87,     1,    31,    13,    51,    91,    92,    29,    52,     2,
      93,    94,    95,    96,    97,    98,    99,   100,    80,   102,
      38,    39,    40,     2,    15,    33,    18,    19,    41,    71,
      72,    73,    74,    75,    42,    43,    78,   -17,    26,    15,
      79,    28,    44,    45,    87,    46,    38,    39,    40,    38,
      39,    40,    32,    36,    41,    56,    58,    41,    59,    60,
      42,    43,    52,    42,    43,    86,    69,    65,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    66,    67,    90,
      79,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      81,    82,    31,    79,   104,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    83,   105,   101,    79,    70,    71,
      72,    73,    74,    75,    76,    77,    78,   112,    55,    14,
      79,   108,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    16,    85,    89,    79,    70,    71,    72,    73,    74,
      75,    76,    77,    78,   103,    68,   106,    79,    70,    71,
      72,    73,    74,    75,    76,    77,    78,   109,     0,   107,
      79,    70,    71,    72,    73,    74,    75,    76,    77,    78,
       0,     0,     0,    79,    71,    72,    73,    74,    75,    76,
       0,    78,     0,     0,     0,    79,    72,    73,    74,    75,
      74,    75,    78,     0,    78,     0,    79,     0,    79
};

static const yytype_int8 yycheck[] =
{
       0,    41,    42,    43,    44,     5,     8,     3,    17,    23,
       9,    17,   106,   107,     6,    21,    25,    57,   112,    21,
      60,     3,    21,     0,    20,    65,    66,     7,    28,    25,
      70,    71,    72,    73,    74,    75,    76,    77,    52,    79,
       4,     5,     6,    25,    23,    59,     6,     7,    12,    10,
      11,    12,    13,    14,    18,    19,    17,    23,    23,    23,
      21,    19,    26,    27,   104,    29,     4,     5,     6,     4,
       5,     6,     6,    24,    12,     4,     7,    12,     8,    19,
      18,    19,    82,    18,    19,    20,     7,    19,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    19,    24,     7,
      21,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      20,     8,    21,    21,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    22,    20,     6,    21,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    28,    30,     5,
      21,    22,     9,    10,    11,    12,    13,    14,    15,    16,
      17,     6,    59,    20,    21,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    82,    49,    20,    21,     9,    10,
      11,    12,    13,    14,    15,    16,    17,   104,    -1,    20,
      21,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      -1,    -1,    -1,    21,    10,    11,    12,    13,    14,    15,
      -1,    17,    -1,    -1,    -1,    21,    11,    12,    13,    14,
      13,    14,    17,    -1,    17,    -1,    21,    -1,    21
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    25,    33,    34,    35,    36,    38,    39,    40,
       6,    41,    42,     0,    34,    23,    47,    48,     6,     7,
      37,    43,    44,    38,    51,    52,    23,    51,    19,     7,
       8,    21,     6,    43,    53,    54,    24,    51,     4,     5,
       6,    12,    18,    19,    26,    27,    29,    47,    49,    50,
      55,    20,    38,    45,    46,    37,     4,     9,     7,     8,
      19,    55,    55,    55,    55,    19,    19,    24,    49,     7,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    21,
      43,    20,     8,    22,    55,    53,    20,    55,    56,    20,
       7,    55,    55,    55,    55,    55,    55,    55,    55,    55,
      55,     6,    55,    45,     8,    20,    20,    20,    22,    56,
      50,    50,    28,    50
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
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
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
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
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
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
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



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

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
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
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

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
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
#line 152 "./parser.y"
    {
//printf("Program (%d)\n",yylineno);
/*printtree($1,1);*/;}
    break;

  case 3:
#line 156 "./parser.y"
    { (yyval.t)=newtreenode(NULL, yylineno, ""); ;}
    break;

  case 4:
#line 157 "./parser.y"
    {(yyval.t)=newtree2((yyvsp[(1) - (2)].t),(yyvsp[(2) - (2)].t),"ExtDefList");;}
    break;

  case 5:
#line 159 "./parser.y"
    {(yyval.t)=newtree3((yyvsp[(1) - (3)].t),(yyvsp[(2) - (3)].t),(yyvsp[(3) - (3)].t),"ExtDef");;}
    break;

  case 6:
#line 160 "./parser.y"
    {(yyval.t)=newtree2((yyvsp[(1) - (2)].t),(yyvsp[(2) - (2)].t),"ExtDef");;}
    break;

  case 7:
#line 161 "./parser.y"
    {(yyval.t)=newtree2((yyvsp[(1) - (2)].t),(yyvsp[(2) - (2)].t),"ExtDef");;}
    break;

  case 8:
#line 163 "./parser.y"
    {(yyval.t)=newtree2((yyvsp[(1) - (2)].t),(yyvsp[(2) - (2)].t),"FuncBegin");
                        insertFuncRtType((yyvsp[(2) - (2)].t)->child->text,(yyvsp[(1) - (2)].t)->_type,(yyvsp[(2) - (2)].t)->_struct);
			_funcName = (yyvsp[(2) - (2)].t)->child->text;
;}
    break;

  case 9:
#line 168 "./parser.y"
    {(yyval.t)=newtree1((yyvsp[(1) - (1)].t),"ExtDecList");;}
    break;

  case 10:
#line 169 "./parser.y"
    {(yyval.t)=newtree3((yyvsp[(1) - (3)].t),(yyvsp[(2) - (3)].t),(yyvsp[(3) - (3)].t),"ExtDecList");;}
    break;

  case 11:
#line 171 "./parser.y"
    {(yyval.t)=newtree1((yyvsp[(1) - (1)].t),"Specifier");
			 (yyval.t)->_type = (yyvsp[(1) - (1)].t)->_type;;}
    break;

  case 12:
#line 173 "./parser.y"
    {(yyval.t)=newtree1((yyvsp[(1) - (1)].t),"Specifier");
		(yyval.t)->_struct = (yyvsp[(1) - (1)].t)->_struct;
		(yyval.t)->_type = 2;;}
    break;

  case 13:
#line 177 "./parser.y"
    {(yyval.t)=newtree3((yyvsp[(1) - (3)].t),(yyvsp[(2) - (3)].t),(yyvsp[(3) - (3)].t),"StructSpecifier");;}
    break;

  case 14:
#line 178 "./parser.y"
    {(yyval.t)=newtree2((yyvsp[(1) - (2)].t),(yyvsp[(2) - (2)].t),"StructSpecifier");
	StructNode * _struct = findStructTable((yyvsp[(2) - (2)].t)->child->text);
	if (_struct==NULL){
		printf("Error type 17 at Line %d: Undefined struct \"%s\".\n",(yyvsp[(2) - (2)].t)->lineno,(yyvsp[(2) - (2)].t)->child->text);
	}else {
		(yyval.t)->_struct = _struct;
	}
;}
    break;

  case 15:
#line 187 "./parser.y"
    {(yyval.t)=newtree3((yyvsp[(1) - (3)].t),(yyvsp[(2) - (3)].t),(yyvsp[(3) - (3)].t),"StructSpecifierBegin");
	char * structName = (yyvsp[(2) - (3)].t)->child->text;	
	if (findStructTable(structName)!=NULL || findVarTable(structName)!=NULL){
		printf("Error type 16 at Line %d: Redefined struct \"%s\".\n",(yyvsp[(2) - (3)].t)->lineno,structName);
	} else {
		insertStructTable(structName);
		_structName = structName;
		//loginStructVars($4,structName);
		//printStructTable();
	}
;}
    break;

  case 16:
#line 199 "./parser.y"
    {(yyval.t)=newtreenode(NULL,yylineno,"");;}
    break;

  case 17:
#line 200 "./parser.y"
    {(yyval.t)=newtree1((yyvsp[(1) - (1)].t),"OptTag");;}
    break;

  case 18:
#line 202 "./parser.y"
    {(yyval.t)=newtree1((yyvsp[(1) - (1)].t),"Tag");;}
    break;

  case 19:
#line 204 "./parser.y"
    {(yyval.t)=newtree1((yyvsp[(1) - (1)].t),"VarDec");;}
    break;

  case 20:
#line 205 "./parser.y"
    {(yyval.t)=newtree4((yyvsp[(1) - (4)].t),(yyvsp[(2) - (4)].t),(yyvsp[(3) - (4)].t),(yyvsp[(4) - (4)].t),"VarDec");;}
    break;

  case 21:
#line 207 "./parser.y"
    {(yyval.t)=newtree4((yyvsp[(1) - (4)].t),(yyvsp[(2) - (4)].t),(yyvsp[(3) - (4)].t),(yyvsp[(4) - (4)].t),"FunDec");
	if (findFuncTable((yyvsp[(1) - (4)].t)->text)!=NULL){
		printf("Error type 4 at Line %d: Redefined function \"%s\".\n",(yyvsp[(1) - (4)].t)->lineno,(yyvsp[(1) - (4)].t)->text);
	}else{
		insertFuncTable((yyvsp[(1) - (4)].t)->text);
		loginParamVars((yyvsp[(3) - (4)].t),(yyvsp[(1) - (4)].t)->text);
	}
;}
    break;

  case 22:
#line 215 "./parser.y"
    {(yyval.t)=newtree3((yyvsp[(1) - (3)].t),(yyvsp[(2) - (3)].t),(yyvsp[(3) - (3)].t),"FunDec");
	if (findFuncTable((yyvsp[(1) - (3)].t)->text)!=NULL){
                printf("Error type 4 at Line %d: Redefined function \"%s\".\n",(yyvsp[(1) - (3)].t)->lineno,(yyvsp[(1) - (3)].t)->text);
        }else{
                insertFuncTable((yyvsp[(1) - (3)].t)->text);
        }       
;}
    break;

  case 23:
#line 223 "./parser.y"
    {(yyval.t)=newtree3((yyvsp[(1) - (3)].t),(yyvsp[(2) - (3)].t),(yyvsp[(3) - (3)].t),"VarList");;}
    break;

  case 24:
#line 224 "./parser.y"
    {(yyval.t)=newtree1((yyvsp[(1) - (1)].t),"VarList");;}
    break;

  case 25:
#line 226 "./parser.y"
    {(yyval.t)=newtree2((yyvsp[(1) - (2)].t),(yyvsp[(2) - (2)].t),"ParamDec");
		(yyvsp[(2) - (2)].t)->_type = (yyvsp[(1) - (2)].t)->_type;
		(yyvsp[(2) - (2)].t)->_struct = (yyvsp[(1) - (2)].t)->_struct;
;}
    break;

  case 26:
#line 231 "./parser.y"
    {(yyval.t)=newtree4((yyvsp[(1) - (4)].t),(yyvsp[(2) - (4)].t),(yyvsp[(3) - (4)].t),(yyvsp[(4) - (4)].t),"CompSt");;}
    break;

  case 27:
#line 233 "./parser.y"
    {(yyval.t)=newtree1((yyvsp[(1) - (1)].t),"CompStBegin");
	_structName = NULL;;}
    break;

  case 28:
#line 236 "./parser.y"
    {(yyval.t)=newtreenode(NULL,yylineno,"");;}
    break;

  case 29:
#line 237 "./parser.y"
    {(yyval.t)=newtree2((yyvsp[(1) - (2)].t),(yyvsp[(2) - (2)].t),"StmtList");;}
    break;

  case 30:
#line 239 "./parser.y"
    {(yyval.t)=newtree2((yyvsp[(1) - (2)].t),(yyvsp[(2) - (2)].t),"Stmt");;}
    break;

  case 31:
#line 240 "./parser.y"
    {(yyval.t)=newtree1((yyvsp[(1) - (1)].t),"Stmt");;}
    break;

  case 32:
#line 241 "./parser.y"
    {(yyval.t)=newtree3((yyvsp[(1) - (3)].t),(yyvsp[(2) - (3)].t),(yyvsp[(3) - (3)].t),"Stmt");
		if (_funcName== NULL){
			
		}else {
			FuncNode *f = findFuncTable(_funcName);
			if (f->rtType != (yyvsp[(2) - (3)].t)->_type || f->rtStructType != (yyvsp[(2) - (3)].t)->_struct){
				printf("Error type 8 at Line %d: Return value can't match.\n",(yyvsp[(2) - (3)].t)->lineno);
			}
		}
;}
    break;

  case 33:
#line 251 "./parser.y"
    {(yyval.t)=newtree5((yyvsp[(1) - (5)].t),(yyvsp[(2) - (5)].t),(yyvsp[(3) - (5)].t),(yyvsp[(4) - (5)].t),(yyvsp[(5) - (5)].t),"Stmt");;}
    break;

  case 34:
#line 252 "./parser.y"
    {(yyval.t)=newtree7((yyvsp[(1) - (7)].t),(yyvsp[(2) - (7)].t),(yyvsp[(3) - (7)].t),(yyvsp[(4) - (7)].t),(yyvsp[(5) - (7)].t),(yyvsp[(6) - (7)].t),(yyvsp[(7) - (7)].t),"Stmt");;}
    break;

  case 35:
#line 253 "./parser.y"
    {(yyval.t)=newtree5((yyvsp[(1) - (5)].t),(yyvsp[(2) - (5)].t),(yyvsp[(3) - (5)].t),(yyvsp[(4) - (5)].t),(yyvsp[(5) - (5)].t),"Stmt");;}
    break;

  case 36:
#line 255 "./parser.y"
    {(yyval.t)=newtreenode(NULL,yylineno,"");;}
    break;

  case 37:
#line 256 "./parser.y"
    {(yyval.t)=newtree2((yyvsp[(1) - (2)].t),(yyvsp[(2) - (2)].t),"DefList");;}
    break;

  case 38:
#line 258 "./parser.y"
    {(yyval.t)=newtree3((yyvsp[(1) - (3)].t),(yyvsp[(2) - (3)].t),(yyvsp[(3) - (3)].t),"Def");
		(yyvsp[(2) - (3)].t)->_type = (yyvsp[(1) - (3)].t)->_type;
		(yyvsp[(2) - (3)].t)->_struct = (yyvsp[(1) - (3)].t)->_struct;
		 if (_structName == NULL){
                        loginVar((yyvsp[(2) - (3)].t));
                }else {
                        loginStructVar((yyvsp[(2) - (3)].t),_structName);
                }

;}
    break;

  case 39:
#line 269 "./parser.y"
    {(yyval.t)=newtree1((yyvsp[(1) - (1)].t),"DecList");;}
    break;

  case 40:
#line 270 "./parser.y"
    {(yyval.t)=newtree3((yyvsp[(1) - (3)].t),(yyvsp[(2) - (3)].t),(yyvsp[(3) - (3)].t),"DecList");;}
    break;

  case 41:
#line 272 "./parser.y"
    {(yyval.t)=newtree1((yyvsp[(1) - (1)].t),"Dec");;}
    break;

  case 42:
#line 273 "./parser.y"
    {(yyval.t)=newtree3((yyvsp[(1) - (3)].t),(yyvsp[(2) - (3)].t),(yyvsp[(3) - (3)].t),"Dec");;}
    break;

  case 43:
#line 275 "./parser.y"
    {(yyval.t)=newtree3((yyvsp[(1) - (3)].t),(yyvsp[(2) - (3)].t),(yyvsp[(3) - (3)].t),"Exp");
	     if ((yyvsp[(1) - (3)].t)->_type == (yyvsp[(3) - (3)].t)->_type && (yyvsp[(1) - (3)].t)->_struct == (yyvsp[(3) - (3)].t)->_struct && (yyvsp[(1) - (3)].t)->_dim == (yyvsp[(3) - (3)].t)->_dim){
		(yyval.t)->_type = (yyvsp[(1) - (3)].t)->_type;
		(yyval.t)->_struct = (yyvsp[(1) - (3)].t)->_struct;
		(yyval.t)->_dim = (yyvsp[(1) - (3)].t)->_dim;
	} else {
		printf("Error type 5 at Line %d: Symbol type left side of \"%s\" can't match the right side.\n",(yyvsp[(2) - (3)].t)->lineno,(yyvsp[(2) - (3)].t)->text);
	}
;}
    break;

  case 44:
#line 284 "./parser.y"
    {(yyval.t)=newtree3((yyvsp[(1) - (3)].t),(yyvsp[(2) - (3)].t),(yyvsp[(3) - (3)].t),"Exp");;}
    break;

  case 45:
#line 285 "./parser.y"
    {(yyval.t)=newtree3((yyvsp[(1) - (3)].t),(yyvsp[(2) - (3)].t),(yyvsp[(3) - (3)].t),"Exp");
	if ((yyvsp[(1) - (3)].t)->_struct == NULL && (yyvsp[(3) - (3)].t)->_struct==NULL && (yyvsp[(1) - (3)].t)->_type == (yyvsp[(3) - (3)].t)->_type  && (yyvsp[(1) - (3)].t)->_dim == (yyvsp[(3) - (3)].t)->_dim){
		(yyval.t)->_type = (yyvsp[(1) - (3)].t)->_type;
		(yyval.t)->_dim = (yyvsp[(1) - (3)].t)->_dim;
		(yyval.t)->_struct = (yyvsp[(1) - (3)].t)->_struct;
	} else {
		printf("Error type 7 at Line %d: Type can't match.\n",(yyvsp[(2) - (3)].t)->lineno);
	}
;}
    break;

  case 46:
#line 294 "./parser.y"
    {(yyval.t)=newtree3((yyvsp[(1) - (3)].t),(yyvsp[(2) - (3)].t),(yyvsp[(3) - (3)].t),"Exp");;}
    break;

  case 47:
#line 295 "./parser.y"
    {(yyval.t)=newtree3((yyvsp[(1) - (3)].t),(yyvsp[(2) - (3)].t),(yyvsp[(3) - (3)].t),"Exp");;}
    break;

  case 48:
#line 296 "./parser.y"
    {(yyval.t)=newtree3((yyvsp[(1) - (3)].t),(yyvsp[(2) - (3)].t),(yyvsp[(3) - (3)].t),"Exp");
		if ((yyvsp[(1) - (3)].t)->_struct == NULL && (yyvsp[(3) - (3)].t)->_struct==NULL && (yyvsp[(1) - (3)].t)->_type == (yyvsp[(3) - (3)].t)->_type  && (yyvsp[(1) - (3)].t)->_dim == (yyvsp[(3) - (3)].t)->_dim){
                (yyval.t)->_type = (yyvsp[(1) - (3)].t)->_type;
                (yyval.t)->_dim = (yyvsp[(1) - (3)].t)->_dim;
                (yyval.t)->_struct = (yyvsp[(1) - (3)].t)->_struct;
        } else {
                printf("Error type 7 at Line %d: Type can't match.\n",(yyvsp[(2) - (3)].t)->lineno);
        }
;}
    break;

  case 49:
#line 305 "./parser.y"
    {(yyval.t)=newtree3((yyvsp[(1) - (3)].t),(yyvsp[(2) - (3)].t),(yyvsp[(3) - (3)].t),"Exp");
	if ((yyvsp[(1) - (3)].t)->_struct == NULL && (yyvsp[(3) - (3)].t)->_struct==NULL && (yyvsp[(1) - (3)].t)->_type == (yyvsp[(3) - (3)].t)->_type  && (yyvsp[(1) - (3)].t)->_dim == (yyvsp[(3) - (3)].t)->_dim){
                (yyval.t)->_type = (yyvsp[(1) - (3)].t)->_type;
                (yyval.t)->_dim = (yyvsp[(1) - (3)].t)->_dim;
                (yyval.t)->_struct = (yyvsp[(1) - (3)].t)->_struct;
        } else {
                printf("Error type 7 at Line %d: Type can't match.\n",(yyvsp[(2) - (3)].t)->lineno);
        }
;}
    break;

  case 50:
#line 314 "./parser.y"
    {(yyval.t)=newtree3((yyvsp[(1) - (3)].t),(yyvsp[(2) - (3)].t),(yyvsp[(3) - (3)].t),"Exp");
	if ((yyvsp[(1) - (3)].t)->_struct == NULL && (yyvsp[(3) - (3)].t)->_struct==NULL && (yyvsp[(1) - (3)].t)->_type == (yyvsp[(3) - (3)].t)->_type  && (yyvsp[(1) - (3)].t)->_dim == (yyvsp[(3) - (3)].t)->_dim){
                (yyval.t)->_type = (yyvsp[(1) - (3)].t)->_type;
                (yyval.t)->_dim = (yyvsp[(1) - (3)].t)->_dim;
                (yyval.t)->_struct = (yyvsp[(1) - (3)].t)->_struct;
        } else {
                printf("Error type 7 at Line %d: Type can't match.\n",(yyvsp[(2) - (3)].t)->lineno);
        }
;}
    break;

  case 51:
#line 323 "./parser.y"
    {(yyval.t)=newtree3((yyvsp[(1) - (3)].t),(yyvsp[(2) - (3)].t),(yyvsp[(3) - (3)].t),"Exp");;}
    break;

  case 52:
#line 324 "./parser.y"
    {(yyval.t)=newtree2((yyvsp[(1) - (2)].t),(yyvsp[(2) - (2)].t),"Exp");;}
    break;

  case 53:
#line 325 "./parser.y"
    {(yyval.t)=newtree2((yyvsp[(1) - (2)].t),(yyvsp[(2) - (2)].t),"Exp");;}
    break;

  case 54:
#line 326 "./parser.y"
    {(yyval.t)=newtree4((yyvsp[(1) - (4)].t),(yyvsp[(2) - (4)].t),(yyvsp[(3) - (4)].t),(yyvsp[(4) - (4)].t),"Exp");
	VarNode * v = findVarTable((yyvsp[(1) - (4)].t)->text);
	FuncNode * f = findFuncTable((yyvsp[(1) - (4)].t)->text);
	if (f== NULL && v!=NULL){
                printf("Error type 11 at Line %d: Can't use \"()\" at a Variable.\n",(yyvsp[(1) - (4)].t)->lineno);
        } else if (f==NULL && v==NULL){
		printf("Error type 2 at Line %d: Undefined funcition \"%s\".\n",(yyvsp[(1) - (4)].t)->lineno,(yyvsp[(1) - (4)].t)->text);
	} else {
		paramMatch((yyvsp[(3) - (4)].t),f);
	}
;}
    break;

  case 55:
#line 337 "./parser.y"
    {(yyval.t)=newtree3((yyvsp[(1) - (3)].t),(yyvsp[(2) - (3)].t),(yyvsp[(3) - (3)].t),"Exp");
	VarNode * v = findVarTable((yyvsp[(1) - (3)].t)->text);
	FuncNode * f = findFuncTable((yyvsp[(1) - (3)].t)->text);
	if (f== NULL && v!=NULL){
		printf("Error type 11 at Line %d: Can't use \"()\" at a Variable.\n",(yyvsp[(1) - (3)].t)->lineno);
	} else if (f== NULL && v== NULL){
                printf("Error type 2 at Line %d: Undefined funcition \"%s\".\n",(yyvsp[(1) - (3)].t)->lineno,(yyvsp[(1) - (3)].t)->text);
        }else{
		if (f->beginParam!=NULL){
			printf("Error type 9 at Line %d: Params in function \"%s\" can't match.\n",(yyvsp[(2) - (3)].t)->lineno,(yyvsp[(1) - (3)].t)->text);
		}
	}

;}
    break;

  case 56:
#line 351 "./parser.y"
    {(yyval.t)=newtree4((yyvsp[(1) - (4)].t),(yyvsp[(2) - (4)].t),(yyvsp[(3) - (4)].t),(yyvsp[(4) - (4)].t),"Exp");
		if ((yyvsp[(3) - (4)].t)->_type != 0 || (yyvsp[(3) - (4)].t)->_dim != 0){
			printf("Error type 12 at Line %d: number in \"[ ]\" is not an integer.\n",(yyvsp[(3) - (4)].t)->lineno);
		} else {
			int dim = (yyvsp[(1) - (4)].t)->_dim - 1;
			if (dim < 0){
				printf("Error type 10 at Line %d: Can't use \"[ ]\" at an not array symbol.\n",(yyvsp[(1) - (4)].t)->lineno);
			}else {
				(yyval.t)->_type = (yyvsp[(1) - (4)].t)->_type;
				(yyval.t)->_struct = (yyvsp[(1) - (4)].t)->_struct;
				(yyval.t)->_dim = dim;
			}		
		}
;}
    break;

  case 57:
#line 365 "./parser.y"
    {(yyval.t)=newtree3((yyvsp[(1) - (3)].t),(yyvsp[(2) - (3)].t),(yyvsp[(3) - (3)].t),"Exp");
	if ((yyvsp[(1) - (3)].t)->_struct == NULL){
		printf("Error type 13 at Line %d: Symbol before \".\" is not a struct.\n",(yyvsp[(2) - (3)].t)->lineno);
	}else {
		VarNode * v = findStructVar((yyvsp[(3) - (3)].t)->text,(yyvsp[(1) - (3)].t)->_struct->structName);		if (v == NULL){
			printf("Error type 14 at Line %d: \"%s\" is undefined in the struct.\n",(yyvsp[(3) - (3)].t)->lineno,(yyvsp[(3) - (3)].t)->text);
		} else {
			(yyval.t)->_type = v->type;
			(yyval.t)->_struct = v->structType;
			(yyval.t)->_dim = v->dimension;
		}	
	}
;}
    break;

  case 58:
#line 378 "./parser.y"
    {(yyval.t)=newtree1((yyvsp[(1) - (1)].t),"Exp");
	VarNode *t =findVarTable((yyvsp[(1) - (1)].t)->text);
	if (t==NULL){
		printf("Error type 1 at Line %d: Undefined variable \"%s\".\n",(yyvsp[(1) - (1)].t)->lineno,(yyvsp[(1) - (1)].t)->text);
	} else {
		(yyval.t)->_type = t->type;
		(yyval.t)->_struct = t->structType;
		(yyval.t)->_dim = t->dimension;
	}
	//printVarTable();
;}
    break;

  case 59:
#line 389 "./parser.y"
    {(yyval.t)=newtree1((yyvsp[(1) - (1)].t),"Exp");
	(yyval.t)->_type = (yyvsp[(1) - (1)].t)->_type;
	(yyval.t)->_dim = 0;
	(yyval.t)->_struct=NULL;;}
    break;

  case 60:
#line 393 "./parser.y"
    {(yyval.t)=newtree1((yyvsp[(1) - (1)].t),"Exp");
	(yyval.t)->_type = (yyvsp[(1) - (1)].t)->_type;
	(yyval.t)->_struct = NULL;
	(yyval.t)->_dim = 0;
;}
    break;

  case 61:
#line 399 "./parser.y"
    {(yyval.t)=newtree3((yyvsp[(1) - (3)].t),(yyvsp[(2) - (3)].t),(yyvsp[(3) - (3)].t),"Args");;}
    break;

  case 62:
#line 400 "./parser.y"
    {(yyval.t)=newtree1((yyvsp[(1) - (1)].t),"Args");;}
    break;


/* Line 1267 of yacc.c.  */
#line 2087 "parser.tab.c"
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
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
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

  if (yyn == YYFINAL)
    YYACCEPT;

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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
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


#line 402 "./parser.y"

#include "lex.yy.c"
int main(int argc, int ** argv) {
	init();
	 if (argc > 1){
                if (!(yyin = fopen((const char *)argv[1],"r"))){
                        perror((const char *)argv[1]);
                        return 1;
                }
        }
	yyparse();
	return 0;
}
yyerror(char * msg){
	fprintf(stderr,"Error type B at Line %d: %s\n",yylineno,msg);
}

