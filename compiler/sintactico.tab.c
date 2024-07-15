/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "sintactico.y"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "listaSimbolos.h"
#include "listaCodigo.h"
#include "generacionCodigo.h"
#define RED 	"\033[0;31m"
#define RESET   "\033[0m"
#define PRINT_ERROR(fmt, ...) fprintf(stderr, RED fmt RESET, ##__VA_ARGS__) // ## sirve para que no ponga coma si no hay args https://gcc.gnu.org/onlinedocs/gcc/Variadic-Macros.html
#define CLEAN_ERROR yyerrok;yyclearin;
// MACROS tabla de simbolos para acciones que se repiten
#define AÑADIR_ID(nombre,tipo) if (!pertenece(nombre,l)) añadeEntrada(nombre,tipo,l,contCadenas); \
	  		    else { PRINT_ERROR("Error semántico en la linea %d, Variable %s ya declarada \n",yylineno,nombre); error=true; semErrors++;}
#define ASIG_VALIDA(nombre) if (!pertenece(nombre,l)) {PRINT_ERROR("Error semántico en la linea %d variable %s no declarada\n",yylineno,nombre); error=true; semErrors++;} \
			    else if(esConstante(nombre,l)) {PRINT_ERROR("Error semántico en la linea %d Asignación a la constante %s\n",yylineno,nombre); error=true;semErrors++;}

extern int yylex();
void yyerror();
extern int yylineno;
bool error = false;
int sinErrors = 0;
int semErrors = 0;
extern int lexErrors;
// tabla de simbolos
Tipo tipo;
Lista l;
int contCadenas=0;


#line 103 "sintactico.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "sintactico.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_PRINT = 3,                      /* PRINT  */
  YYSYMBOL_VAR = 4,                        /* VAR  */
  YYSYMBOL_READ = 5,                       /* READ  */
  YYSYMBOL_SEMICOLON = 6,                  /* SEMICOLON  */
  YYSYMBOL_COMMA = 7,                      /* COMMA  */
  YYSYMBOL_WHILE = 8,                      /* WHILE  */
  YYSYMBOL_CONST = 9,                      /* CONST  */
  YYSYMBOL_LCORCHETE = 10,                 /* LCORCHETE  */
  YYSYMBOL_RCORCHETE = 11,                 /* RCORCHETE  */
  YYSYMBOL_LPAREN = 12,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 13,                    /* RPAREN  */
  YYSYMBOL_IF = 14,                        /* IF  */
  YYSYMBOL_DO = 15,                        /* DO  */
  YYSYMBOL_NUM = 16,                       /* NUM  */
  YYSYMBOL_ID = 17,                        /* ID  */
  YYSYMBOL_STRING = 18,                    /* STRING  */
  YYSYMBOL_ASSIGNOP = 19,                  /* ASSIGNOP  */
  YYSYMBOL_OR = 20,                        /* OR  */
  YYSYMBOL_AND = 21,                       /* AND  */
  YYSYMBOL_UNOT = 22,                      /* UNOT  */
  YYSYMBOL_GTOP = 23,                      /* GTOP  */
  YYSYMBOL_LTOP = 24,                      /* LTOP  */
  YYSYMBOL_GTEOP = 25,                     /* GTEOP  */
  YYSYMBOL_LTEOP = 26,                     /* LTEOP  */
  YYSYMBOL_EQOP = 27,                      /* EQOP  */
  YYSYMBOL_NOTEQOP = 28,                   /* NOTEQOP  */
  YYSYMBOL_PLUSOP = 29,                    /* PLUSOP  */
  YYSYMBOL_MINUSOP = 30,                   /* MINUSOP  */
  YYSYMBOL_MULTOP = 31,                    /* MULTOP  */
  YYSYMBOL_DIVOP = 32,                     /* DIVOP  */
  YYSYMBOL_UMINUS = 33,                    /* UMINUS  */
  YYSYMBOL_NOT_ELSE = 34,                  /* NOT_ELSE  */
  YYSYMBOL_ELSE = 35,                      /* ELSE  */
  YYSYMBOL_YYACCEPT = 36,                  /* $accept  */
  YYSYMBOL_program = 37,                   /* program  */
  YYSYMBOL_38_1 = 38,                      /* $@1  */
  YYSYMBOL_declarations = 39,              /* declarations  */
  YYSYMBOL_40_2 = 40,                      /* $@2  */
  YYSYMBOL_41_3 = 41,                      /* $@3  */
  YYSYMBOL_identifier_list = 42,           /* identifier_list  */
  YYSYMBOL_identifier = 43,                /* identifier  */
  YYSYMBOL_statement_list = 44,            /* statement_list  */
  YYSYMBOL_statement = 45,                 /* statement  */
  YYSYMBOL_print_list = 46,                /* print_list  */
  YYSYMBOL_print_item = 47,                /* print_item  */
  YYSYMBOL_read_list = 48,                 /* read_list  */
  YYSYMBOL_expression = 49                 /* expression  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   291

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  36
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  14
/* YYNRULES -- Number of rules.  */
#define YYNRULES  60
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  131

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   290


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    59,    59,    59,    61,    61,    62,    63,    64,    64,
      65,    67,    68,    71,    72,    81,    82,    85,    92,    93,
      94,    95,    96,    97,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   113,   115,   116,
     119,   122,   130,   134,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   159,   160,
     166
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "PRINT", "VAR", "READ",
  "SEMICOLON", "COMMA", "WHILE", "CONST", "LCORCHETE", "RCORCHETE",
  "LPAREN", "RPAREN", "IF", "DO", "NUM", "ID", "STRING", "ASSIGNOP", "OR",
  "AND", "UNOT", "GTOP", "LTOP", "GTEOP", "LTEOP", "EQOP", "NOTEQOP",
  "PLUSOP", "MINUSOP", "MULTOP", "DIVOP", "UMINUS", "NOT_ELSE", "ELSE",
  "$accept", "program", "$@1", "declarations", "$@2", "$@3",
  "identifier_list", "identifier", "statement_list", "statement",
  "print_list", "print_item", "read_list", "expression", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-38)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-9)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -15,    24,    38,    60,   -38,    51,   -38,   -38,     6,     8,
      10,   199,    75,    73,    82,    73,    88,     2,    29,    30,
     -38,   -38,    31,   229,    86,   -38,   -38,   102,    52,   -38,
     -38,    92,   -38,   100,     4,   116,    11,   117,     7,   214,
     118,    55,   121,    67,    70,   -38,    73,   -38,   -38,   112,
      70,   -38,   -38,   -38,    70,    70,    26,   -38,   227,   -38,
     113,   -38,    62,   -38,   128,   107,   -38,   -38,   129,   127,
     131,   -38,    87,   227,   -38,   138,   147,   249,   -38,    48,
      34,    70,    70,    70,    70,    70,    70,    70,    70,    70,
      70,    70,    70,   139,   132,    56,   -38,   229,   -38,   229,
      79,   -38,   -38,   -38,   -38,   -38,   -38,   239,   249,   259,
     259,   259,   259,   259,   259,    71,    71,   -38,   -38,   -38,
     -38,   -38,   -38,   -38,   111,   148,   167,   229,   -38,   -38,
     -38
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     1,     0,     2,    10,    16,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      16,     3,     0,     0,     0,    15,     7,    13,     0,    11,
       6,     0,    36,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     5,     0,     9,    25,     0,
       0,    60,    59,    41,     0,     0,     0,    38,    40,    28,
       0,    42,     0,    32,     0,     0,    18,    35,     0,     0,
       0,    24,     0,    14,    12,     0,     0,    56,    57,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    31,     0,    34,     0,
       0,    17,    27,    58,    39,    26,    23,    55,    54,    49,
      48,    50,    51,    52,    53,    44,    45,    46,    47,    30,
      43,    29,    37,    21,    19,     0,     0,     0,    33,    22,
      20
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -38,   -38,   -38,   -38,   -38,   -38,   149,   119,   142,   -23,
     -38,    84,   -38,   -37
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,     7,     8,    13,    15,    28,    29,    11,    25,
      56,    57,    62,    58
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      42,    65,     1,    33,    69,    49,    72,    73,    64,    12,
       9,    14,    60,    76,    34,    10,    50,    77,    78,    50,
      51,    52,    53,    51,    52,    -4,    54,    -8,    61,    54,
      35,    37,    40,    79,    55,   105,     3,    55,     4,    80,
     106,    36,    38,    41,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,    68,   121,    45,    46,
      50,     6,   122,   126,    51,    52,    53,    50,    71,    94,
      54,    51,    52,     5,   123,    95,   124,    54,    55,    50,
     125,    26,    50,    51,    52,    55,    51,    52,    30,    54,
      27,    50,    54,   101,    32,    51,    52,    55,    47,    46,
      55,    54,    91,    92,   130,    43,    48,    81,    82,    55,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      97,    44,    59,    63,    67,    75,    93,    81,    82,    70,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      99,    96,    98,   100,   102,   119,   127,    81,    82,   120,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
     103,   128,    39,   104,    31,    74,     0,    81,    82,     0,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
     129,     0,     0,     0,     0,     0,     0,    81,    82,     0,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      16,     0,    17,     0,    18,     0,     0,    19,     0,    20,
      21,     0,     0,    22,    23,    16,    24,    17,     0,    18,
       0,     0,    19,     0,    20,    66,     0,     0,    22,    23,
      16,    24,    17,     0,    18,     0,     0,    19,     0,    20,
       0,     0,     0,    22,    23,     0,    24,    81,    82,     0,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      82,     0,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    -9,    -9,    -9,    -9,    -9,    -9,    89,    90,
      91,    92
};

static const yytype_int8 yycheck[] =
{
      23,    38,    17,     1,    41,     1,    43,    44,     1,     1,
       4,     1,     1,    50,    12,     9,    12,    54,    55,    12,
      16,    17,    18,    16,    17,    17,    22,    17,    17,    22,
       1,     1,     1,     7,    30,     1,    12,    30,     0,    13,
       6,    12,    12,    12,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,     1,     1,     6,     7,
      12,    10,     6,   100,    16,    17,    18,    12,     1,     7,
      22,    16,    17,    13,    97,    13,    99,    22,    30,    12,
       1,     6,    12,    16,    17,    30,    16,    17,     6,    22,
      17,    12,    22,     6,     6,    16,    17,    30,     6,     7,
      30,    22,    31,    32,   127,    19,     6,    20,    21,    30,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      13,    19,     6,     6,     6,    13,    13,    20,    21,     8,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      13,    13,    13,    12,     6,     6,    35,    20,    21,    17,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      13,    13,    20,    79,    15,    46,    -1,    20,    21,    -1,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      13,    -1,    -1,    -1,    -1,    -1,    -1,    20,    21,    -1,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
       1,    -1,     3,    -1,     5,    -1,    -1,     8,    -1,    10,
      11,    -1,    -1,    14,    15,     1,    17,     3,    -1,     5,
      -1,    -1,     8,    -1,    10,    11,    -1,    -1,    14,    15,
       1,    17,     3,    -1,     5,    -1,    -1,     8,    -1,    10,
      -1,    -1,    -1,    14,    15,    -1,    17,    20,    21,    -1,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      21,    -1,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    17,    37,    12,     0,    13,    10,    38,    39,     4,
       9,    44,     1,    40,     1,    41,     1,     3,     5,     8,
      10,    11,    14,    15,    17,    45,     6,    17,    42,    43,
       6,    42,     6,     1,    12,     1,    12,     1,    12,    44,
       1,    12,    45,    19,    19,     6,     7,     6,     6,     1,
      12,    16,    17,    18,    22,    30,    46,    47,    49,     6,
       1,    17,    48,     6,     1,    49,    11,     6,     1,    49,
       8,     1,    49,    49,    43,    13,    49,    49,    49,     7,
      13,    20,    21,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    13,     7,    13,    13,    13,    13,    13,
      12,     6,     6,    13,    47,     1,     6,    49,    49,    49,
      49,    49,    49,    49,    49,    49,    49,    49,    49,     6,
      17,     1,     6,    45,    45,     1,    49,    35,    13,    13,
      45
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    36,    38,    37,    40,    39,    39,    39,    41,    39,
      39,    42,    42,    43,    43,    44,    44,    45,    45,    45,
      45,    45,    45,    45,    45,    45,    45,    45,    45,    45,
      45,    45,    45,    45,    45,    45,    45,    45,    46,    46,
      47,    47,    48,    48,    49,    49,    49,    49,    49,    49,
      49,    49,    49,    49,    49,    49,    49,    49,    49,    49,
      49
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     8,     0,     5,     4,     4,     0,     5,
       0,     1,     3,     1,     3,     2,     0,     4,     3,     5,
       7,     5,     6,     5,     3,     3,     5,     5,     3,     5,
       5,     4,     3,     6,     4,     3,     2,     5,     1,     3,
       1,     1,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     2,     3,     1,
       1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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
  case 2: /* $@1: %empty  */
#line 59 "sintactico.y"
                                    {l=creaLS();}
#line 1252 "sintactico.tab.c"
    break;

  case 3: /* program: ID LPAREN RPAREN LCORCHETE $@1 declarations statement_list RCORCHETE  */
#line 59 "sintactico.y"
                                                                                        { if(!error){(yyval.codigo) = creaCodigo(2,(yyvsp[-2].codigo),(yyvsp[-1].codigo)) ;imprimeSegDatos(l); imprimeCodigo((yyval.codigo));}}
#line 1258 "sintactico.tab.c"
    break;

  case 4: /* $@2: %empty  */
#line 61 "sintactico.y"
                               {tipo=VARIABLE;}
#line 1264 "sintactico.tab.c"
    break;

  case 5: /* declarations: declarations VAR $@2 identifier_list SEMICOLON  */
#line 61 "sintactico.y"
                                                                          { if(!error){(yyval.codigo) = creaCodigo(2,(yyval.codigo),(yyvsp[-1].codigo));}}
#line 1270 "sintactico.tab.c"
    break;

  case 6: /* declarations: declarations CONST error SEMICOLON  */
#line 62 "sintactico.y"
                                                 {CLEAN_ERROR;PRINT_ERROR("se esperaban identificadores tras el token const\n");}
#line 1276 "sintactico.tab.c"
    break;

  case 7: /* declarations: declarations VAR error SEMICOLON  */
#line 63 "sintactico.y"
                                               {CLEAN_ERROR;PRINT_ERROR("se esperaban identificadores tras el token var\n");}
#line 1282 "sintactico.tab.c"
    break;

  case 8: /* $@3: %empty  */
#line 64 "sintactico.y"
                                 {tipo=CONSTANTE;}
#line 1288 "sintactico.tab.c"
    break;

  case 9: /* declarations: declarations CONST $@3 identifier_list SEMICOLON  */
#line 64 "sintactico.y"
                                                                             { if(!error){(yyval.codigo) = creaCodigo(2,(yyval.codigo),(yyvsp[-1].codigo)); }}
#line 1294 "sintactico.tab.c"
    break;

  case 10: /* declarations: %empty  */
#line 65 "sintactico.y"
                           { if(!error){(yyval.codigo) = creaLC();}}
#line 1300 "sintactico.tab.c"
    break;

  case 11: /* identifier_list: identifier  */
#line 67 "sintactico.y"
                            { (yyval.codigo) = (yyvsp[0].codigo);}
#line 1306 "sintactico.tab.c"
    break;

  case 12: /* identifier_list: identifier_list COMMA identifier  */
#line 68 "sintactico.y"
                                                 {(yyval.codigo) = creaCodigo(2,(yyvsp[-2].codigo),(yyvsp[0].codigo));}
#line 1312 "sintactico.tab.c"
    break;

  case 13: /* identifier: ID  */
#line 71 "sintactico.y"
               {AÑADIR_ID((yyvsp[0].string),tipo); if(!error){(yyval.codigo) = creaLC();}}
#line 1318 "sintactico.tab.c"
    break;

  case 14: /* identifier: ID ASSIGNOP expression  */
#line 72 "sintactico.y"
                                   {
	  				AÑADIR_ID((yyvsp[-2].string),tipo);
					if(!error){
						ListaC aux1 = allocStoreId(recuperaResLC((yyvsp[0].codigo)),obtenerId((yyvsp[-2].string)));
						(yyval.codigo) = creaCodigo(2,(yyvsp[0].codigo),aux1);
					}
	  			   }
#line 1330 "sintactico.tab.c"
    break;

  case 15: /* statement_list: statement_list statement  */
#line 81 "sintactico.y"
                                         { if(!error){(yyval.codigo) = creaCodigo(2,(yyvsp[-1].codigo),(yyvsp[0].codigo));}}
#line 1336 "sintactico.tab.c"
    break;

  case 16: /* statement_list: %empty  */
#line 82 "sintactico.y"
                             {if(!error){(yyval.codigo) = creaLC();} }
#line 1342 "sintactico.tab.c"
    break;

  case 17: /* statement: ID ASSIGNOP expression SEMICOLON  */
#line 85 "sintactico.y"
                                            {
	 					ASIG_VALIDA((yyvsp[-3].string));
						if(!error){
							char *regRes = recuperaResLC((yyvsp[-1].codigo));
							(yyval.codigo) = creaCodigo(2,(yyvsp[-1].codigo),creaLineaCodigo("store4",regRes,obtenerId((yyvsp[-3].string)),NULL));
						}
					    }
#line 1354 "sintactico.tab.c"
    break;

  case 18: /* statement: LCORCHETE statement_list RCORCHETE  */
#line 92 "sintactico.y"
                                              { if(!error){(yyval.codigo) = (yyvsp[-1].codigo); }}
#line 1360 "sintactico.tab.c"
    break;

  case 19: /* statement: IF LPAREN expression RPAREN statement  */
#line 93 "sintactico.y"
                                                                {if(!error){(yyval.codigo) = imprimirIf((yyvsp[-2].codigo),(yyvsp[0].codigo));}}
#line 1366 "sintactico.tab.c"
    break;

  case 20: /* statement: IF LPAREN expression RPAREN statement ELSE statement  */
#line 94 "sintactico.y"
                                                                {if(!error){(yyval.codigo) = imprimirIfElse((yyvsp[-4].codigo),(yyvsp[-2].codigo),(yyvsp[0].codigo));}}
#line 1372 "sintactico.tab.c"
    break;

  case 21: /* statement: WHILE LPAREN expression RPAREN statement  */
#line 95 "sintactico.y"
                                                    { if(!error){(yyval.codigo) = imprimirWhile((yyvsp[-2].codigo),(yyvsp[0].codigo));}}
#line 1378 "sintactico.tab.c"
    break;

  case 22: /* statement: DO statement WHILE LPAREN expression RPAREN  */
#line 96 "sintactico.y"
                                                       {if(!error){(yyval.codigo) = imprimirDoWhile((yyvsp[-4].codigo),(yyvsp[-1].codigo));}}
#line 1384 "sintactico.tab.c"
    break;

  case 23: /* statement: PRINT LPAREN print_list RPAREN SEMICOLON  */
#line 97 "sintactico.y"
                                                    { if(!error){(yyval.codigo) = (yyvsp[-2].codigo); }}
#line 1390 "sintactico.tab.c"
    break;

  case 24: /* statement: ID ASSIGNOP error  */
#line 99 "sintactico.y"
                             {CLEAN_ERROR;PRINT_ERROR("se esperaba ;\n");}
#line 1396 "sintactico.tab.c"
    break;

  case 25: /* statement: PRINT error SEMICOLON  */
#line 100 "sintactico.y"
                                 {CLEAN_ERROR;PRINT_ERROR("sentencia print mal formada\n");}
#line 1402 "sintactico.tab.c"
    break;

  case 26: /* statement: PRINT LPAREN print_list RPAREN error  */
#line 101 "sintactico.y"
                                                {CLEAN_ERROR;PRINT_ERROR("se esperaba ;\n");}
#line 1408 "sintactico.tab.c"
    break;

  case 27: /* statement: PRINT LPAREN error RPAREN SEMICOLON  */
#line 102 "sintactico.y"
                                               {CLEAN_ERROR;PRINT_ERROR("argumentos de print inválidos\n");}
#line 1414 "sintactico.tab.c"
    break;

  case 28: /* statement: READ error SEMICOLON  */
#line 103 "sintactico.y"
                                {CLEAN_ERROR;PRINT_ERROR("sentencia read mal formada\n");}
#line 1420 "sintactico.tab.c"
    break;

  case 29: /* statement: READ LPAREN read_list RPAREN error  */
#line 104 "sintactico.y"
                                              {CLEAN_ERROR;PRINT_ERROR("se esperaba ;\n");}
#line 1426 "sintactico.tab.c"
    break;

  case 30: /* statement: READ LPAREN error RPAREN SEMICOLON  */
#line 105 "sintactico.y"
                                              {CLEAN_ERROR;PRINT_ERROR("argumentos de read inválidos\n");}
#line 1432 "sintactico.tab.c"
    break;

  case 31: /* statement: WHILE LPAREN error RPAREN  */
#line 106 "sintactico.y"
                                     {CLEAN_ERROR;PRINT_ERROR("expresión inválida en bucle while\n");}
#line 1438 "sintactico.tab.c"
    break;

  case 32: /* statement: WHILE error SEMICOLON  */
#line 107 "sintactico.y"
                                 {CLEAN_ERROR;PRINT_ERROR("sentencia while mal formada\n");}
#line 1444 "sintactico.tab.c"
    break;

  case 33: /* statement: DO statement WHILE LPAREN error RPAREN  */
#line 108 "sintactico.y"
                                                  {CLEAN_ERROR;PRINT_ERROR("expresión inválida en bucle do-while\n");}
#line 1450 "sintactico.tab.c"
    break;

  case 34: /* statement: IF LPAREN error RPAREN  */
#line 109 "sintactico.y"
                                  {CLEAN_ERROR;PRINT_ERROR("expresión inválida en sentencia if\n");}
#line 1456 "sintactico.tab.c"
    break;

  case 35: /* statement: IF error SEMICOLON  */
#line 110 "sintactico.y"
                               {CLEAN_ERROR;PRINT_ERROR("sentencia if mal formada\n");}
#line 1462 "sintactico.tab.c"
    break;

  case 36: /* statement: error SEMICOLON  */
#line 111 "sintactico.y"
                           {CLEAN_ERROR;PRINT_ERROR("se esperaba ;\n");}
#line 1468 "sintactico.tab.c"
    break;

  case 37: /* statement: READ LPAREN read_list RPAREN SEMICOLON  */
#line 113 "sintactico.y"
                                                  { if(!error){(yyval.codigo) = (yyvsp[-2].codigo); }}
#line 1474 "sintactico.tab.c"
    break;

  case 38: /* print_list: print_item  */
#line 115 "sintactico.y"
                       { if(!error){(yyval.codigo) = (yyvsp[0].codigo); }}
#line 1480 "sintactico.tab.c"
    break;

  case 39: /* print_list: print_list COMMA print_item  */
#line 116 "sintactico.y"
                                        { if(!error){(yyval.codigo) = creaCodigo(2,(yyvsp[-2].codigo),(yyvsp[0].codigo));} }
#line 1486 "sintactico.tab.c"
    break;

  case 40: /* print_item: expression  */
#line 119 "sintactico.y"
                       {
	  		 if(!error){(yyval.codigo) = imprimirExpresion((yyvsp[0].codigo));}
		       }
#line 1494 "sintactico.tab.c"
    break;

  case 41: /* print_item: STRING  */
#line 122 "sintactico.y"
                   {
	  		añadeEntrada((yyvsp[0].string),CADENA,l,contCadenas);
			if(!error){
				contCadenas++;
				(yyval.codigo) = imprimirCadena((yyvsp[0].string),l);
			}
		   }
#line 1506 "sintactico.tab.c"
    break;

  case 42: /* read_list: ID  */
#line 130 "sintactico.y"
              {
	 	ASIG_VALIDA((yyvsp[0].string));
		if(!error){(yyval.codigo) = leerId((yyvsp[0].string));}
	      }
#line 1515 "sintactico.tab.c"
    break;

  case 43: /* read_list: read_list COMMA ID  */
#line 134 "sintactico.y"
                              {
				ASIG_VALIDA((yyvsp[0].string));
	 			if(!error){(yyval.codigo) = creaCodigo(2,(yyvsp[-2].codigo),leerId((yyvsp[0].string)));}
			      }
#line 1524 "sintactico.tab.c"
    break;

  case 44: /* expression: expression PLUSOP expression  */
#line 140 "sintactico.y"
                                         { if(!error){(yyval.codigo) = aritExpr("add",(yyvsp[-2].codigo),(yyvsp[0].codigo));}}
#line 1530 "sintactico.tab.c"
    break;

  case 45: /* expression: expression MINUSOP expression  */
#line 141 "sintactico.y"
                                          { if(!error){(yyval.codigo) = aritExpr("sub",(yyvsp[-2].codigo),(yyvsp[0].codigo));}}
#line 1536 "sintactico.tab.c"
    break;

  case 46: /* expression: expression MULTOP expression  */
#line 142 "sintactico.y"
                                         { if(!error){(yyval.codigo) = aritExpr("mul",(yyvsp[-2].codigo),(yyvsp[0].codigo));}}
#line 1542 "sintactico.tab.c"
    break;

  case 47: /* expression: expression DIVOP expression  */
#line 143 "sintactico.y"
                                        { if(!error){(yyval.codigo) = aritExpr("udiv",(yyvsp[-2].codigo),(yyvsp[0].codigo));}}
#line 1548 "sintactico.tab.c"
    break;

  case 48: /* expression: expression LTOP expression  */
#line 144 "sintactico.y"
                                       { if(!error){(yyval.codigo) = compare("slt",(yyvsp[-2].codigo),(yyvsp[0].codigo));}}
#line 1554 "sintactico.tab.c"
    break;

  case 49: /* expression: expression GTOP expression  */
#line 145 "sintactico.y"
                                       { if(!error){(yyval.codigo) = compare("sgt",(yyvsp[0].codigo),(yyvsp[-2].codigo));}}
#line 1560 "sintactico.tab.c"
    break;

  case 50: /* expression: expression GTEOP expression  */
#line 146 "sintactico.y"
                                        { if(!error){(yyval.codigo) = compare("sge",(yyvsp[-2].codigo),(yyvsp[0].codigo));}}
#line 1566 "sintactico.tab.c"
    break;

  case 51: /* expression: expression LTEOP expression  */
#line 147 "sintactico.y"
                                        { if(!error){(yyval.codigo) = compare("sle",(yyvsp[-2].codigo),(yyvsp[0].codigo));}}
#line 1572 "sintactico.tab.c"
    break;

  case 52: /* expression: expression EQOP expression  */
#line 148 "sintactico.y"
                                       { if(!error){(yyval.codigo) = compare("eq",(yyvsp[-2].codigo),(yyvsp[0].codigo));}}
#line 1578 "sintactico.tab.c"
    break;

  case 53: /* expression: expression NOTEQOP expression  */
#line 149 "sintactico.y"
                                          { if(!error){(yyval.codigo) = compare("ne",(yyvsp[-2].codigo),(yyvsp[0].codigo));}}
#line 1584 "sintactico.tab.c"
    break;

  case 54: /* expression: expression AND expression  */
#line 150 "sintactico.y"
                                      { if(!error){(yyval.codigo) = aritExpr("and",(yyvsp[-2].codigo),(yyvsp[0].codigo));}}
#line 1590 "sintactico.tab.c"
    break;

  case 55: /* expression: expression OR expression  */
#line 151 "sintactico.y"
                                     { if(!error){(yyval.codigo) = aritExpr("or",(yyvsp[-2].codigo),(yyvsp[0].codigo));}}
#line 1596 "sintactico.tab.c"
    break;

  case 56: /* expression: UNOT expression  */
#line 152 "sintactico.y"
                            { if(!error){(yyval.codigo) = not((yyvsp[0].codigo));}}
#line 1602 "sintactico.tab.c"
    break;

  case 57: /* expression: MINUSOP expression  */
#line 153 "sintactico.y"
                                            {
						if(!error){
							char *regRes = recuperaResLC((yyvsp[0].codigo));
							(yyval.codigo) = creaCodigo(2,(yyvsp[0].codigo),creaLineaCodigo("neg",getRegister(),regRes,NULL));
						}
					    }
#line 1613 "sintactico.tab.c"
    break;

  case 58: /* expression: LPAREN expression RPAREN  */
#line 159 "sintactico.y"
                                     { (yyval.codigo) = (yyvsp[-1].codigo); }
#line 1619 "sintactico.tab.c"
    break;

  case 59: /* expression: ID  */
#line 160 "sintactico.y"
               {
			if(!error){
				if(!pertenece((yyvsp[0].string),l)){PRINT_ERROR("Error semántico en la linea %d variable %s no declarada\n",yylineno,(yyvsp[0].string)); error = true ;semErrors++;}
				(yyval.codigo) = allocStore(obtenerId((yyvsp[0].string)));
			}
		}
#line 1630 "sintactico.tab.c"
    break;

  case 60: /* expression: NUM  */
#line 166 "sintactico.y"
                 {  if(!error){ (yyval.codigo) = allocStore((yyvsp[0].string));} }
#line 1636 "sintactico.tab.c"
    break;


#line 1640 "sintactico.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 169 "sintactico.y"



void yyerror(){
	PRINT_ERROR("Error sintáctico en la linea %d ",yylineno);
	error = true;
	sinErrors++;

}
