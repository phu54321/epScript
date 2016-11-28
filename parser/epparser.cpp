/* Driver template for the LEMON parser generator.
** The author disclaims copyright to this source code.
*/
/* First off, code is included that follows the "include" declaration
** in the input grammar file. */
#include <stdio.h>
#line 1 "parser/epparser.lemon"

#include <stdio.h>
#include <assert.h>
#include <string>
#include <iostream>
#include <sstream>
#include "epparser.h"
#include "pygen.h"
#include "tokenAdapter.h"
#include "parserUtilities.h"

int currentTokenizingLine;
#line 21 "parser/epparser.c"
/* Next is all token values, in a form suitable for use by makeheaders.
** This section will be null unless lemon is run with the -m switch.
*/
/* 
** These constants (all generated automatically by the parser generator)
** specify the various kinds of tokens (terminals) that the parser
** understands. 
**
** Each symbol here is a terminal symbol in the grammar.
*/
/* Make sure the INTERFACE macro is defined.
*/
#ifndef INTERFACE
# define INTERFACE 1
#endif
/* The next thing included is series of defines which control
** various aspects of the generated parser.
**    YYCODETYPE         is the data type used for storing terminal
**                       and nonterminal numbers.  "unsigned char" is
**                       used if there are fewer than 250 terminals
**                       and nonterminals.  "int" is used otherwise.
**    YYNOCODE           is a number of type YYCODETYPE which corresponds
**                       to no legal terminal or nonterminal number.  This
**                       number is used to fill in empty slots of the hash 
**                       table.
**    YYFALLBACK         If defined, this indicates that one or more tokens
**                       have fall-back values which should be used if the
**                       original value of the token will not parse.
**    YYACTIONTYPE       is the data type used for storing terminal
**                       and nonterminal numbers.  "unsigned char" is
**                       used if there are fewer than 250 rules and
**                       states combined.  "int" is used otherwise.
**    ParseTOKENTYPE     is the data type used for minor tokens given 
**                       directly to the parser from the tokenizer.
**    YYMINORTYPE        is the data type used for all minor tokens.
**                       This is typically a union of many types, one of
**                       which is ParseTOKENTYPE.  The entry in the union
**                       for base tokens is called "yy0".
**    YYSTACKDEPTH       is the maximum depth of the parser's stack.  If
**                       zero the stack is dynamically sized using realloc()
**    ParseARG_SDECL     A static variable declaration for the %extra_argument
**    ParseARG_PDECL     A parameter declaration for the %extra_argument
**    ParseARG_STORE     Code to store %extra_argument into yypParser
**    ParseARG_FETCH     Code to extract %extra_argument from yypParser
**    YYNSTATE           the combined number of states.
**    YYNRULE            the number of rules in the grammar
**    YYERRORSYMBOL      is the code number of the error symbol.  If not
**                       defined, then do no error processing.
*/
#define YYCODETYPE unsigned char
#define YYNOCODE 87
#define YYACTIONTYPE unsigned short int
#define ParseTOKENTYPE Token*
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  int yy173;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL  PyGenerator* pGen ;
#define ParseARG_PDECL , PyGenerator* pGen 
#define ParseARG_FETCH  PyGenerator* pGen  = yypParser->pGen 
#define ParseARG_STORE yypParser->pGen  = pGen 
#define YYNSTATE 190
#define YYNRULE 94
#define YYERRORSYMBOL 48
#define YYERRSYMDT yy173
#define YY_NO_ACTION      (YYNSTATE+YYNRULE+2)
#define YY_ACCEPT_ACTION  (YYNSTATE+YYNRULE+1)
#define YY_ERROR_ACTION   (YYNSTATE+YYNRULE)

/* The yyzerominor constant is used to initialize instances of
** YYMINORTYPE objects to zero. */
static const YYMINORTYPE yyzerominor = { 0 };

/* Define the yytestcase() macro to be a no-op if is not already defined
** otherwise.
**
** Applications can choose to define yytestcase() in the %include section
** to a macro that can assist in verifying code coverage.  For production
** code the yytestcase() macro should be turned off.  But it is useful
** for testing.
*/
#ifndef yytestcase
# define yytestcase(X)
#endif


/* Next are the tables used to determine what action to take based on the
** current state and lookahead token.  These tables are used to implement
** functions that take a state number and lookahead value and return an
** action integer.  
**
** Suppose the action integer is N.  Then the action is determined as
** follows
**
**   0 <= N < YYNSTATE                  Shift N.  That is, push the lookahead
**                                      token onto the stack and goto state N.
**
**   YYNSTATE <= N < YYNSTATE+YYNRULE   Reduce by rule N-YYNSTATE.
**
**   N == YYNSTATE+YYNRULE              A syntax error has occurred.
**
**   N == YYNSTATE+YYNRULE+1            The parser accepts its input.
**
**   N == YYNSTATE+YYNRULE+2            No such action.  Denotes unused
**                                      slots in the yy_action[] table.
**
** The action table is constructed as a single large table named yy_action[].
** Given state S and lookahead X, the action is computed as
**
**      yy_action[ yy_shift_ofst[S] + X ]
**
** If the index value yy_shift_ofst[S]+X is out of range or if the value
** yy_lookahead[yy_shift_ofst[S]+X] is not equal to X or if yy_shift_ofst[S]
** is equal to YY_SHIFT_USE_DFLT, it means that the action is not in the table
** and that yy_default[S] should be used instead.  
**
** The formula above is for computing the action when the lookahead is
** a terminal symbol.  If the lookahead is a non-terminal (as occurs after
** a reduce action) then the yy_reduce_ofst[] array is used in place of
** the yy_shift_ofst[] array and YY_REDUCE_USE_DFLT is used in place of
** YY_SHIFT_USE_DFLT.
**
** The following are the tables generated in this section:
**
**  yy_action[]        A single table containing all actions.
**  yy_lookahead[]     A table containing the lookahead for each entry in
**                     yy_action.  Used to detect hash collisions.
**  yy_shift_ofst[]    For each state, the offset into yy_action for
**                     shifting terminals.
**  yy_reduce_ofst[]   For each state, the offset into yy_action for
**                     shifting non-terminals after a reduce.
**  yy_default[]       Default action for each state.
*/
#define YY_ACTTAB_COUNT (550)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */    77,  189,  118,   29,  111,   85,  187,  107,   54,  117,
 /*    10 */   138,  137,  135,  136,  134,  133,    2,  163,  125,  102,
 /*    20 */     6,  131,    5,   98,    4,  130,    3,  129,  128,  127,
 /*    30 */    16,  110,   92,  126,   47,   46,  132,   85,  184,  107,
 /*    40 */    54,   30,  138,  137,  135,  136,  134,  133,  185,  123,
 /*    50 */   125,  102,    6,  131,    5,   98,    4,  130,    3,  129,
 /*    60 */   128,  127,  118,   28,   92,  126,   47,   46,  132,   85,
 /*    70 */   170,  107,   54,   30,  138,  137,  135,  136,  134,  133,
 /*    80 */    45,   99,  125,  102,    6,  131,    5,   98,    4,  130,
 /*    90 */     3,  129,  128,  127,  118,  188,   92,  126,   47,   46,
 /*   100 */   132,   85,  159,  107,   54,   30,  138,  137,  135,  136,
 /*   110 */   134,  133,  112,  153,  125,  102,    6,  131,    5,   98,
 /*   120 */     4,  130,    3,  129,  128,  127,  117,   20,   92,  126,
 /*   130 */    47,   46,  132,   85,  149,  107,   54,   30,  138,  137,
 /*   140 */   135,  136,  134,  133,   50,  150,  125,  102,    6,  131,
 /*   150 */     5,   98,    4,  130,    3,  129,  128,  127,  118,  186,
 /*   160 */    92,  126,   47,   46,  132,   85,   93,  107,   54,  181,
 /*   170 */   138,  137,  135,  136,  134,  133,  182,  148,  125,  102,
 /*   180 */     6,  131,    5,   98,    4,  130,    3,  129,  128,  127,
 /*   190 */   180,  188,   92,  126,   47,   46,  132,   85,  179,  107,
 /*   200 */    54,  106,  138,  137,  135,  136,  134,  133,  105,  162,
 /*   210 */   125,  102,    6,  131,    5,   98,    4,  130,    3,  129,
 /*   220 */   128,  127,  104,   33,   32,  126,   47,   46,  132,   31,
 /*   230 */   178,   76,  117,   21,   43,   40,   41,   39,   49,  139,
 /*   240 */     1,  161,  160,  114,  110,  152,   97,  183,   96,   95,
 /*   250 */   117,   15,   94,   27,   25,   24,   23,   22,   26,   35,
 /*   260 */    34,   36,   38,   37,   44,   42,   40,   41,   39,   16,
 /*   270 */    33,   32,   84,  113,   64,   13,   31,  178,   76,  107,
 /*   280 */    74,   43,   83,  113,   64,   49,  139,    1,  140,  160,
 /*   290 */   124,   18,  152,   97,   14,   96,   95,   19,   15,   94,
 /*   300 */    35,   34,   36,   38,   37,   44,   42,   40,   41,   39,
 /*   310 */    38,   37,   44,   42,   40,   41,   39,  177,   35,   34,
 /*   320 */    36,   38,   37,   44,   42,   40,   41,   39,   12,   13,
 /*   330 */   121,  154,  120,   44,   42,   40,   41,   39,    9,  168,
 /*   340 */    35,   34,   36,   38,   37,   44,   42,   40,   41,   39,
 /*   350 */   115,    7,  122,   12,   13,  155,  147,  119,   82,  113,
 /*   360 */    64,  166,   35,   34,   36,   38,   37,   44,   42,   40,
 /*   370 */    41,   39,   80,  113,   64,   78,  113,   64,  107,   56,
 /*   380 */   151,  107,   75,  165,   35,   34,   36,   38,   37,   44,
 /*   390 */    42,   40,   41,   39,   86,  113,   64,   48,   34,   36,
 /*   400 */    38,   37,   44,   42,   40,   41,   39,   36,   38,   37,
 /*   410 */    44,   42,   40,   41,   39,   11,   79,  113,   64,   33,
 /*   420 */    32,  107,   52,   71,  117,   31,  178,  103,   33,   32,
 /*   430 */    43,  169,  190,  146,   31,  178,  103,   17,   30,   43,
 /*   440 */    10,  143,  101,  140,   33,   32,  107,   52,  158,   30,
 /*   450 */    31,  178,  103,   33,   32,   43,   90,  186,   87,   31,
 /*   460 */   178,  103,  109,   30,   43,   51,   91,  101,  107,   52,
 /*   470 */   100,  167,   33,   32,  107,   52,  157,  116,   31,  178,
 /*   480 */   103,   88,  164,   43,  107,   52,  156,   72,  144,  108,
 /*   490 */    73,  107,   52,   70,  107,  176,  145,   81,  107,  175,
 /*   500 */   107,  174,  107,   69,  107,   68,  107,   67,  107,   65,
 /*   510 */   107,   66,  114,  107,  173,  107,  172,  286,  107,  171,
 /*   520 */   107,   63,   94,  107,   55,  107,   53,  107,   62,  107,
 /*   530 */    61,  107,   60,  107,   59,  107,   58,   89,  107,   57,
 /*   540 */   285,    8,  286,  286,  286,  286,  286,  286,  142,  141,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    48,   26,    1,    2,    1,   53,   26,   55,   56,    1,
 /*    10 */    58,   59,   60,   61,   62,   63,   64,   65,   66,   67,
 /*    20 */    68,   69,   70,   71,   72,   73,   74,   75,   76,   77,
 /*    30 */    29,   28,   48,   81,   82,   83,   84,   53,   30,   55,
 /*    40 */    56,    1,   58,   59,   60,   61,   62,   63,   26,   65,
 /*    50 */    66,   67,   68,   69,   70,   71,   72,   73,   74,   75,
 /*    60 */    76,   77,    1,    2,   48,   81,   82,   83,   84,   53,
 /*    70 */    30,   55,   56,    1,   58,   59,   60,   61,   62,   63,
 /*    80 */    29,   65,   66,   67,   68,   69,   70,   71,   72,   73,
 /*    90 */    74,   75,   76,   77,    1,   34,   48,   81,   82,   83,
 /*   100 */    84,   53,   30,   55,   56,    1,   58,   59,   60,   61,
 /*   110 */    62,   63,   27,   65,   66,   67,   68,   69,   70,   71,
 /*   120 */    72,   73,   74,   75,   76,   77,    1,    2,   48,   81,
 /*   130 */    82,   83,   84,   53,   30,   55,   56,    1,   58,   59,
 /*   140 */    60,   61,   62,   63,   27,   65,   66,   67,   68,   69,
 /*   150 */    70,   71,   72,   73,   74,   75,   76,   77,    1,   34,
 /*   160 */    48,   81,   82,   83,   84,   53,   30,   55,   56,   28,
 /*   170 */    58,   59,   60,   61,   62,   63,   25,   65,   66,   67,
 /*   180 */    68,   69,   70,   71,   72,   73,   74,   75,   76,   77,
 /*   190 */    25,   34,   48,   81,   82,   83,   84,   53,   28,   55,
 /*   200 */    56,   27,   58,   59,   60,   61,   62,   63,   27,   65,
 /*   210 */    66,   67,   68,   69,   70,   71,   72,   73,   74,   75,
 /*   220 */    76,   77,   25,   18,   19,   81,   82,   83,   84,   24,
 /*   230 */    25,   26,    1,    2,   29,   20,   21,   22,   33,   34,
 /*   240 */    35,   36,   37,   26,   28,   40,   41,   30,   43,   44,
 /*   250 */     1,   46,   47,    7,    8,    9,   10,   11,   12,   13,
 /*   260 */    14,   15,   16,   17,   18,   19,   20,   21,   22,   29,
 /*   270 */    18,   19,   54,   55,   56,    4,   24,   25,   26,   55,
 /*   280 */    56,   29,   54,   55,   56,   33,   34,   35,   34,   37,
 /*   290 */    36,   42,   40,   41,   29,   43,   44,   29,   46,   47,
 /*   300 */    13,   14,   15,   16,   17,   18,   19,   20,   21,   22,
 /*   310 */    16,   17,   18,   19,   20,   21,   22,   30,   13,   14,
 /*   320 */    15,   16,   17,   18,   19,   20,   21,   22,    3,    4,
 /*   330 */    58,   39,   60,   18,   19,   20,   21,   22,   29,   34,
 /*   340 */    13,   14,   15,   16,   17,   18,   19,   20,   21,   22,
 /*   350 */    78,   79,   80,    3,    4,   30,   34,   85,   54,   55,
 /*   360 */    56,   34,   13,   14,   15,   16,   17,   18,   19,   20,
 /*   370 */    21,   22,   54,   55,   56,   54,   55,   56,   55,   56,
 /*   380 */    30,   55,   56,   34,   13,   14,   15,   16,   17,   18,
 /*   390 */    19,   20,   21,   22,   54,   55,   56,   29,   14,   15,
 /*   400 */    16,   17,   18,   19,   20,   21,   22,   15,   16,   17,
 /*   410 */    18,   19,   20,   21,   22,    5,   54,   55,   56,   18,
 /*   420 */    19,   55,   56,   57,    1,   24,   25,   26,   18,   19,
 /*   430 */    29,   30,    0,   34,   24,   25,   26,   29,    1,   29,
 /*   440 */     5,   34,   32,   34,   18,   19,   55,   56,   57,    1,
 /*   450 */    24,   25,   26,   18,   19,   29,   53,   34,   52,   24,
 /*   460 */    25,   26,    1,    1,   29,   33,   26,   32,   55,   56,
 /*   470 */    57,   34,   18,   19,   55,   56,   57,   45,   24,   25,
 /*   480 */    26,   25,   34,   29,   55,   56,   57,   53,   34,   28,
 /*   490 */    26,   55,   56,   57,   55,   56,   34,   53,   55,   56,
 /*   500 */    55,   56,   55,   56,   55,   56,   55,   56,   55,   56,
 /*   510 */    55,   56,   26,   55,   56,   55,   56,   86,   55,   56,
 /*   520 */    55,   56,   47,   55,   56,   55,   56,   55,   56,   55,
 /*   530 */    56,   55,   56,   55,   56,   55,   56,   53,   55,   56,
 /*   540 */    50,   51,   86,   86,   86,   86,   86,   86,   82,   82,
};
#define YY_SHIFT_USE_DFLT (-26)
#define YY_SHIFT_COUNT (118)
#define YY_SHIFT_MIN   (-25)
#define YY_SHIFT_MAX   (486)
static const short yy_shift_ofst[] = {
 /*     0 */   -26,  252,  205,  252,  252,  252,  252,  252,  432,  410,
 /*    10 */   435,  435,  410,  410,  410,  454,  401,  426,  426,  426,
 /*    20 */   426,  426,  426,  426,  426,  426,  426,  426,  426,  426,
 /*    30 */   426,  426,  426,  426,  426,  426,  426,  426,  426,  426,
 /*    40 */   426,  426,  426,  426,  426,  217,  475,  475,  486,  464,
 /*    50 */   456,  440,  246,  349,  327,  305,  287,  371,  371,  371,
 /*    60 */   371,  371,  371,  371,  371,  384,  392,  294,  315,  315,
 /*    70 */   350,  325,  125,   61,  215,  215,    1,  254,  136,  462,
 /*    80 */   104,  249,   72,  448,  437,  231,   40,  461,    3,    8,
 /*    90 */   423,  157,  409,  407,  408,  399,  322,  368,  309,  292,
 /*   100 */   271,  268,  265,  240,  216,  197,  181,  174,  170,  165,
 /*   110 */   141,  151,  117,   85,   93,   51,   22,  -20,  -25,
};
#define YY_REDUCE_USE_DFLT (-49)
#define YY_REDUCE_COUNT (51)
#define YY_REDUCE_MIN   (-48)
#define YY_REDUCE_MAX   (490)
static const short yy_reduce_ofst[] = {
 /*     0 */   490,  -48,  144,  112,   80,   48,   16,  -16,  272,  436,
 /*    10 */   429,  419,  413,  391,  366,  362,  340,  321,  318,  304,
 /*    20 */   228,  218,  483,  480,  478,  476,  474,  472,  470,  468,
 /*    30 */   465,  463,  460,  458,  455,  453,  451,  449,  447,  445,
 /*    40 */   443,  439,  326,  323,  224,  484,  467,  466,  444,  434,
 /*    50 */   406,  403,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   282,  284,  284,  284,  284,  284,  284,  284,  284,  284,
 /*    10 */   284,  284,  284,  284,  284,  284,  284,  284,  284,  284,
 /*    20 */   284,  284,  284,  284,  284,  284,  284,  284,  284,  284,
 /*    30 */   284,  284,  284,  284,  284,  284,  284,  284,  284,  284,
 /*    40 */   284,  284,  284,  284,  284,  284,  261,  260,  284,  284,
 /*    50 */   284,  284,  284,  284,  284,  284,  284,  224,  223,  222,
 /*    60 */   221,  220,  219,  198,  197,  213,  214,  212,  211,  210,
 /*    70 */   284,  284,  284,  284,  205,  206,  200,  284,  284,  284,
 /*    80 */   284,  284,  284,  284,  284,  284,  284,  284,  284,  284,
 /*    90 */   284,  284,  284,  284,  284,  284,  284,  284,  284,  241,
 /*   100 */   226,  284,  284,  200,  284,  284,  284,  203,  284,  284,
 /*   110 */   284,  284,  284,  203,  284,  284,  284,  284,  284,  283,
 /*   120 */   281,  280,  279,  254,  238,  278,  277,  276,  275,  274,
 /*   130 */   273,  272,  271,  269,  268,  267,  266,  265,  264,  263,
 /*   140 */   262,  259,  258,  257,  255,  256,  250,  249,  248,  247,
 /*   150 */   246,  245,  244,  243,  242,  240,  228,  227,  225,  218,
 /*   160 */   239,  237,  236,  235,  232,  230,  270,  234,  233,  202,
 /*   170 */   201,  217,  216,  215,  209,  208,  207,  204,  199,  195,
 /*   180 */   192,  196,  191,  253,  252,  251,  231,  194,  229,  193,
};

/* The next table maps tokens into fallback tokens.  If a construct
** like the following:
** 
**      %fallback ID X Y Z.
**
** appears in the grammar, then ID becomes a fallback token for X, Y,
** and Z.  Whenever one of the tokens X, Y, or Z is input to the parser
** but it does not parse, the type of the token is changed to ID and
** the parse is retried before an error is thrown.
*/
#ifdef YYFALLBACK
static const YYCODETYPE yyFallback[] = {
};
#endif /* YYFALLBACK */

/* The following structure represents a single element of the
** parser's stack.  Information stored includes:
**
**   +  The state number for the parser at this level of the stack.
**
**   +  The value of the token stored at this level of the stack.
**      (In other words, the "major" token.)
**
**   +  The semantic value stored at this level of the stack.  This is
**      the information used by the action routines in the grammar.
**      It is sometimes called the "minor" token.
*/
struct yyStackEntry {
  YYACTIONTYPE stateno;  /* The state-number */
  YYCODETYPE major;      /* The major token value.  This is the code
                         ** number for the token at this stack level */
  YYMINORTYPE minor;     /* The user-supplied minor token value.  This
                         ** is the value of the token  */
};
typedef struct yyStackEntry yyStackEntry;

/* The state of the parser is completely contained in an instance of
** the following structure */
struct yyParser {
  int yyidx;                    /* Index of top element in stack */
#ifdef YYTRACKMAXSTACKDEPTH
  int yyidxMax;                 /* Maximum value of yyidx */
#endif
  int yyerrcnt;                 /* Shifts left before out of the error */
  ParseARG_SDECL                /* A place to hold %extra_argument */
#if YYSTACKDEPTH<=0
  int yystksz;                  /* Current side of the stack */
  yyStackEntry *yystack;        /* The parser's stack */
#else
  yyStackEntry yystack[YYSTACKDEPTH];  /* The parser's stack */
#endif
};
typedef struct yyParser yyParser;

#ifndef NDEBUG
#include <stdio.h>
static FILE *yyTraceFILE = 0;
static char *yyTracePrompt = 0;
#endif /* NDEBUG */

#ifndef NDEBUG
/* 
** Turn parser tracing on by giving a stream to which to write the trace
** and a prompt to preface each trace message.  Tracing is turned off
** by making either argument NULL 
**
** Inputs:
** <ul>
** <li> A FILE* to which trace output should be written.
**      If NULL, then tracing is turned off.
** <li> A prefix string written at the beginning of every
**      line of trace output.  If NULL, then tracing is
**      turned off.
** </ul>
**
** Outputs:
** None.
*/
void ParseTrace(FILE *TraceFILE, char *zTracePrompt){
  yyTraceFILE = TraceFILE;
  yyTracePrompt = zTracePrompt;
  if( yyTraceFILE==0 ) yyTracePrompt = 0;
  else if( yyTracePrompt==0 ) yyTraceFILE = 0;
}
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing shifts, the names of all terminals and nonterminals
** are required.  The following table supplies these names */
static const char *const yyTokenName[] = { 
  "$",             "COMMA",         "ASSIGN",        "LOR",         
  "LAND",          "LNOT",          "DOUBLE_LNOT",   "EQ",          
  "LE",            "LT",            "GE",            "GT",          
  "NE",            "BITOR",         "BITXOR",        "BITAND",      
  "LSHIFT",        "RSHIFT",        "PLUS",          "MINUS",       
  "DIVIDE",        "MULTIPLY",      "MOD",           "UNARY",       
  "BITNOT",        "NUMBER",        "NAME",          "LSQBRACKET",  
  "RSQBRACKET",    "LPAREN",        "RPAREN",        "FUNCCALL",    
  "CONDITIONNAME",  "VAR",           "SEMICOLON",     "LBRACKET",    
  "RBRACKET",      "IF",            "IFX",           "ELSE",        
  "WHILE",         "FOR",           "COLON",         "CONTINUE",    
  "BREAK",         "FUNCTION",      "RETURN",        "ACTIONNAME",  
  "error",         "nt",            "program",       "chunks",      
  "numList",       "nameList",      "exprList",      "funcexpr",    
  "expr",          "lexpr",         "vdef_stmt",     "vdefAssign_stmt",
  "vdefMulti_stmt",  "vdefMultiAssign_stmt",  "assign_stmt",   "assignMulti_stmt",
  "stmtList",      "stmt",          "block",         "if_start",    
  "if_header",     "if_stmt",       "else_header",   "while_start", 
  "while_header",  "while_stmt",    "foreach_header",  "foreach_stmt",
  "continue_stmt",  "break_stmt",    "function_start",  "function_header",
  "fdef_chunk",    "return_stmt",   "action",        "actions",     
  "actionStmt",    "chunk",       
};
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *const yyRuleName[] = {
 /*   0 */ "program ::= chunks",
 /*   1 */ "numList ::= NUMBER COMMA NUMBER",
 /*   2 */ "numList ::= numList COMMA NUMBER",
 /*   3 */ "nameList ::= NAME COMMA NAME",
 /*   4 */ "nameList ::= nameList COMMA NAME",
 /*   5 */ "exprList ::= funcexpr LSQBRACKET LSQBRACKET numList RSQBRACKET RSQBRACKET",
 /*   6 */ "expr ::= funcexpr LSQBRACKET LSQBRACKET NUMBER RSQBRACKET RSQBRACKET",
 /*   7 */ "exprList ::= expr",
 /*   8 */ "exprList ::= exprList COMMA expr",
 /*   9 */ "expr ::= NUMBER",
 /*  10 */ "expr ::= NAME",
 /*  11 */ "funcexpr ::= NAME LPAREN exprList RPAREN",
 /*  12 */ "funcexpr ::= NAME LPAREN RPAREN",
 /*  13 */ "expr ::= funcexpr",
 /*  14 */ "expr ::= LPAREN expr RPAREN",
 /*  15 */ "expr ::= expr PLUS expr",
 /*  16 */ "expr ::= expr MINUS expr",
 /*  17 */ "expr ::= expr MULTIPLY expr",
 /*  18 */ "expr ::= expr DIVIDE expr",
 /*  19 */ "expr ::= expr MOD expr",
 /*  20 */ "expr ::= expr LSHIFT expr",
 /*  21 */ "expr ::= expr RSHIFT expr",
 /*  22 */ "expr ::= expr BITAND expr",
 /*  23 */ "expr ::= expr BITOR expr",
 /*  24 */ "expr ::= expr BITXOR expr",
 /*  25 */ "expr ::= PLUS expr",
 /*  26 */ "expr ::= MINUS expr",
 /*  27 */ "expr ::= BITNOT expr",
 /*  28 */ "lexpr ::= CONDITIONNAME LPAREN exprList RPAREN",
 /*  29 */ "lexpr ::= expr EQ expr",
 /*  30 */ "lexpr ::= expr NE expr",
 /*  31 */ "lexpr ::= expr LE expr",
 /*  32 */ "lexpr ::= expr LT expr",
 /*  33 */ "lexpr ::= expr GE expr",
 /*  34 */ "lexpr ::= expr GT expr",
 /*  35 */ "lexpr ::= lexpr LAND lexpr",
 /*  36 */ "lexpr ::= lexpr LOR lexpr",
 /*  37 */ "lexpr ::= LNOT lexpr",
 /*  38 */ "lexpr ::= LNOT LNOT lexpr",
 /*  39 */ "vdef_stmt ::= VAR NAME SEMICOLON",
 /*  40 */ "vdefAssign_stmt ::= VAR NAME ASSIGN expr SEMICOLON",
 /*  41 */ "vdefMulti_stmt ::= VAR nameList SEMICOLON",
 /*  42 */ "vdefMultiAssign_stmt ::= VAR nameList ASSIGN exprList SEMICOLON",
 /*  43 */ "assign_stmt ::= NAME ASSIGN expr SEMICOLON",
 /*  44 */ "assignMulti_stmt ::= nameList ASSIGN exprList SEMICOLON",
 /*  45 */ "stmtList ::= stmt",
 /*  46 */ "stmtList ::= stmtList stmt",
 /*  47 */ "block ::= LBRACKET stmtList RBRACKET",
 /*  48 */ "block ::= LBRACKET error RBRACKET",
 /*  49 */ "if_start ::= IF",
 /*  50 */ "if_header ::= if_start LPAREN lexpr RPAREN",
 /*  51 */ "if_stmt ::= if_header stmt",
 /*  52 */ "else_header ::= if_header stmt ELSE",
 /*  53 */ "if_stmt ::= else_header stmt",
 /*  54 */ "while_start ::= WHILE",
 /*  55 */ "while_header ::= while_start LPAREN lexpr RPAREN",
 /*  56 */ "while_stmt ::= while_header stmt",
 /*  57 */ "foreach_header ::= FOR LPAREN nameList COLON exprList RPAREN",
 /*  58 */ "foreach_stmt ::= foreach_header stmt",
 /*  59 */ "continue_stmt ::= CONTINUE SEMICOLON",
 /*  60 */ "break_stmt ::= BREAK SEMICOLON",
 /*  61 */ "function_start ::= FUNCTION NAME",
 /*  62 */ "function_header ::= function_start LPAREN nameList RPAREN",
 /*  63 */ "function_header ::= function_start LPAREN RPAREN",
 /*  64 */ "fdef_chunk ::= function_header stmt",
 /*  65 */ "return_stmt ::= RETURN SEMICOLON",
 /*  66 */ "return_stmt ::= RETURN exprList SEMICOLON",
 /*  67 */ "action ::= ACTIONNAME LPAREN exprList RPAREN SEMICOLON",
 /*  68 */ "actions ::= action action",
 /*  69 */ "actions ::= actions action",
 /*  70 */ "actionStmt ::= action",
 /*  71 */ "actionStmt ::= actions",
 /*  72 */ "stmt ::= error SEMICOLON",
 /*  73 */ "stmt ::= SEMICOLON",
 /*  74 */ "stmt ::= vdef_stmt",
 /*  75 */ "stmt ::= vdefAssign_stmt",
 /*  76 */ "stmt ::= vdefMultiAssign_stmt",
 /*  77 */ "stmt ::= vdefMulti_stmt",
 /*  78 */ "stmt ::= assign_stmt",
 /*  79 */ "stmt ::= assignMulti_stmt",
 /*  80 */ "stmt ::= expr SEMICOLON",
 /*  81 */ "stmt ::= actionStmt",
 /*  82 */ "stmt ::= if_stmt",
 /*  83 */ "stmt ::= while_stmt",
 /*  84 */ "stmt ::= foreach_stmt",
 /*  85 */ "stmt ::= continue_stmt",
 /*  86 */ "stmt ::= break_stmt",
 /*  87 */ "stmt ::= return_stmt",
 /*  88 */ "stmt ::= block",
 /*  89 */ "chunk ::= fdef_chunk",
 /*  90 */ "chunk ::= vdef_stmt",
 /*  91 */ "chunk ::= vdefMulti_stmt",
 /*  92 */ "chunks ::=",
 /*  93 */ "chunks ::= chunks chunk",
};
#endif /* NDEBUG */


#if YYSTACKDEPTH<=0
/*
** Try to increase the size of the parser stack.
*/
static void yyGrowStack(yyParser *p){
  int newSize;
  yyStackEntry *pNew;

  newSize = p->yystksz*2 + 100;
  pNew = realloc(p->yystack, newSize*sizeof(pNew[0]));
  if( pNew ){
    p->yystack = pNew;
    p->yystksz = newSize;
#ifndef NDEBUG
    if( yyTraceFILE ){
      fprintf(yyTraceFILE,"%sStack grows to %d entries!\n",
              yyTracePrompt, p->yystksz);
    }
#endif
  }
}
#endif

/* 
** This function allocates a new parser.
** The only argument is a pointer to a function which works like
** malloc.
**
** Inputs:
** A pointer to the function used to allocate memory.
**
** Outputs:
** A pointer to a parser.  This pointer is used in subsequent calls
** to Parse and ParseFree.
*/
void *ParseAlloc(void *(*mallocProc)(size_t)){
  yyParser *pParser;
  pParser = (yyParser*)(*mallocProc)( (size_t)sizeof(yyParser) );
  if( pParser ){
    pParser->yyidx = -1;
#ifdef YYTRACKMAXSTACKDEPTH
    pParser->yyidxMax = 0;
#endif
#if YYSTACKDEPTH<=0
    pParser->yystack = NULL;
    pParser->yystksz = 0;
    yyGrowStack(pParser);
#endif
  }
  return pParser;
}

/* The following function deletes the value associated with a
** symbol.  The symbol can be either a terminal or nonterminal.
** "yymajor" is the symbol code, and "yypminor" is a pointer to
** the value.
*/
static void yy_destructor(
  yyParser *yypParser,    /* The parser */
  YYCODETYPE yymajor,     /* Type code for object to destroy */
  YYMINORTYPE *yypminor   /* The object to be destroyed */
){
  ParseARG_FETCH;
  switch( yymajor ){
    /* Here is inserted the actions which take place when a
    ** terminal or non-terminal is destroyed.  This can happen
    ** when the symbol is popped from the stack during a
    ** reduce or during error processing or when a parser is 
    ** being destroyed before it is finished parsing.
    **
    ** Note: during a reduce, the only symbols destroyed are those
    ** which appear on the RHS of the rule, but which are not used
    ** inside the C code.
    */
    case 49: /* nt */
{
#line 28 "parser/epparser.lemon"
 delete (yypminor->yy0); 
#line 621 "parser/epparser.c"
}
      break;
    default:  break;   /* If no destructor action specified: do nothing */
  }
}

/*
** Pop the parser's stack once.
**
** If there is a destructor routine associated with the token which
** is popped from the stack, then call it.
**
** Return the major token number for the symbol popped.
*/
static int yy_pop_parser_stack(yyParser *pParser){
  YYCODETYPE yymajor;
  yyStackEntry *yytos = &pParser->yystack[pParser->yyidx];

  if( pParser->yyidx<0 ) return 0;
#ifndef NDEBUG
  if( yyTraceFILE && pParser->yyidx>=0 ){
    fprintf(yyTraceFILE,"%sPopping %s\n",
      yyTracePrompt,
      yyTokenName[yytos->major]);
  }
#endif
  yymajor = yytos->major;
  yy_destructor(pParser, yymajor, &yytos->minor);
  pParser->yyidx--;
  return yymajor;
}

/* 
** Deallocate and destroy a parser.  Destructors are all called for
** all stack elements before shutting the parser down.
**
** Inputs:
** <ul>
** <li>  A pointer to the parser.  This should be a pointer
**       obtained from ParseAlloc.
** <li>  A pointer to a function used to reclaim memory obtained
**       from malloc.
** </ul>
*/
void ParseFree(
  void *p,                    /* The parser to be deleted */
  void (*freeProc)(void*)     /* Function used to reclaim memory */
){
  yyParser *pParser = (yyParser*)p;
  if( pParser==0 ) return;
  while( pParser->yyidx>=0 ) yy_pop_parser_stack(pParser);
#if YYSTACKDEPTH<=0
  free(pParser->yystack);
#endif
  (*freeProc)((void*)pParser);
}

/*
** Return the peak depth of the stack for a parser.
*/
#ifdef YYTRACKMAXSTACKDEPTH
int ParseStackPeak(void *p){
  yyParser *pParser = (yyParser*)p;
  return pParser->yyidxMax;
}
#endif

/*
** Find the appropriate action for a parser given the terminal
** look-ahead token iLookAhead.
**
** If the look-ahead token is YYNOCODE, then check to see if the action is
** independent of the look-ahead.  If it is, return the action, otherwise
** return YY_NO_ACTION.
*/
static int yy_find_shift_action(
  yyParser *pParser,        /* The parser */
  YYCODETYPE iLookAhead     /* The look-ahead token */
){
  int i;
  int stateno = pParser->yystack[pParser->yyidx].stateno;
 
  if( stateno>YY_SHIFT_COUNT
   || (i = yy_shift_ofst[stateno])==YY_SHIFT_USE_DFLT ){
    return yy_default[stateno];
  }
  assert( iLookAhead!=YYNOCODE );
  i += iLookAhead;
  if( i<0 || i>=YY_ACTTAB_COUNT || yy_lookahead[i]!=iLookAhead ){
    if( iLookAhead>0 ){
#ifdef YYFALLBACK
      YYCODETYPE iFallback;            /* Fallback token */
      if( iLookAhead<sizeof(yyFallback)/sizeof(yyFallback[0])
             && (iFallback = yyFallback[iLookAhead])!=0 ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE, "%sFALLBACK %s => %s\n",
             yyTracePrompt, yyTokenName[iLookAhead], yyTokenName[iFallback]);
        }
#endif
        return yy_find_shift_action(pParser, iFallback);
      }
#endif
#ifdef YYWILDCARD
      {
        int j = i - iLookAhead + YYWILDCARD;
        if( 
#if YY_SHIFT_MIN+YYWILDCARD<0
          j>=0 &&
#endif
#if YY_SHIFT_MAX+YYWILDCARD>=YY_ACTTAB_COUNT
          j<YY_ACTTAB_COUNT &&
#endif
          yy_lookahead[j]==YYWILDCARD
        ){
#ifndef NDEBUG
          if( yyTraceFILE ){
            fprintf(yyTraceFILE, "%sWILDCARD %s => %s\n",
               yyTracePrompt, yyTokenName[iLookAhead], yyTokenName[YYWILDCARD]);
          }
#endif /* NDEBUG */
          return yy_action[j];
        }
      }
#endif /* YYWILDCARD */
    }
    return yy_default[stateno];
  }else{
    return yy_action[i];
  }
}

/*
** Find the appropriate action for a parser given the non-terminal
** look-ahead token iLookAhead.
**
** If the look-ahead token is YYNOCODE, then check to see if the action is
** independent of the look-ahead.  If it is, return the action, otherwise
** return YY_NO_ACTION.
*/
static int yy_find_reduce_action(
  int stateno,              /* Current state number */
  YYCODETYPE iLookAhead     /* The look-ahead token */
){
  int i;
#ifdef YYERRORSYMBOL
  if( stateno>YY_REDUCE_COUNT ){
    return yy_default[stateno];
  }
#else
  assert( stateno<=YY_REDUCE_COUNT );
#endif
  i = yy_reduce_ofst[stateno];
  assert( i!=YY_REDUCE_USE_DFLT );
  assert( iLookAhead!=YYNOCODE );
  i += iLookAhead;
#ifdef YYERRORSYMBOL
  if( i<0 || i>=YY_ACTTAB_COUNT || yy_lookahead[i]!=iLookAhead ){
    return yy_default[stateno];
  }
#else
  assert( i>=0 && i<YY_ACTTAB_COUNT );
  assert( yy_lookahead[i]==iLookAhead );
#endif
  return yy_action[i];
}

/*
** The following routine is called if the stack overflows.
*/
static void yyStackOverflow(yyParser *yypParser, YYMINORTYPE *yypMinor){
   ParseARG_FETCH;
   yypParser->yyidx--;
#ifndef NDEBUG
   if( yyTraceFILE ){
     fprintf(yyTraceFILE,"%sStack Overflow!\n",yyTracePrompt);
   }
#endif
   while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
   /* Here code is inserted which will execute if the parser
   ** stack every overflows */
   ParseARG_STORE; /* Suppress warning about unused %extra_argument var */
}

/*
** Perform a shift action.
*/
static void yy_shift(
  yyParser *yypParser,          /* The parser to be shifted */
  int yyNewState,               /* The new state to shift in */
  int yyMajor,                  /* The major token to shift in */
  YYMINORTYPE *yypMinor         /* Pointer to the minor token to shift in */
){
  yyStackEntry *yytos;
  yypParser->yyidx++;
#ifdef YYTRACKMAXSTACKDEPTH
  if( yypParser->yyidx>yypParser->yyidxMax ){
    yypParser->yyidxMax = yypParser->yyidx;
  }
#endif
#if YYSTACKDEPTH>0 
  if( yypParser->yyidx>=YYSTACKDEPTH ){
    yyStackOverflow(yypParser, yypMinor);
    return;
  }
#else
  if( yypParser->yyidx>=yypParser->yystksz ){
    yyGrowStack(yypParser);
    if( yypParser->yyidx>=yypParser->yystksz ){
      yyStackOverflow(yypParser, yypMinor);
      return;
    }
  }
#endif
  yytos = &yypParser->yystack[yypParser->yyidx];
  yytos->stateno = (YYACTIONTYPE)yyNewState;
  yytos->major = (YYCODETYPE)yyMajor;
  yytos->minor = *yypMinor;
#ifndef NDEBUG
  if( yyTraceFILE && yypParser->yyidx>0 ){
    int i;
    fprintf(yyTraceFILE,"%sShift %d\n",yyTracePrompt,yyNewState);
    fprintf(yyTraceFILE,"%sStack:",yyTracePrompt);
    for(i=1; i<=yypParser->yyidx; i++)
      fprintf(yyTraceFILE," %s",yyTokenName[yypParser->yystack[i].major]);
    fprintf(yyTraceFILE,"\n");
  }
#endif
}

/* The following table contains information about every rule that
** is used during the reduce.
*/
static const struct {
  YYCODETYPE lhs;         /* Symbol on the left-hand side of the rule */
  unsigned char nrhs;     /* Number of right-hand side symbols in the rule */
} yyRuleInfo[] = {
  { 50, 1 },
  { 52, 3 },
  { 52, 3 },
  { 53, 3 },
  { 53, 3 },
  { 54, 6 },
  { 56, 6 },
  { 54, 1 },
  { 54, 3 },
  { 56, 1 },
  { 56, 1 },
  { 55, 4 },
  { 55, 3 },
  { 56, 1 },
  { 56, 3 },
  { 56, 3 },
  { 56, 3 },
  { 56, 3 },
  { 56, 3 },
  { 56, 3 },
  { 56, 3 },
  { 56, 3 },
  { 56, 3 },
  { 56, 3 },
  { 56, 3 },
  { 56, 2 },
  { 56, 2 },
  { 56, 2 },
  { 57, 4 },
  { 57, 3 },
  { 57, 3 },
  { 57, 3 },
  { 57, 3 },
  { 57, 3 },
  { 57, 3 },
  { 57, 3 },
  { 57, 3 },
  { 57, 2 },
  { 57, 3 },
  { 58, 3 },
  { 59, 5 },
  { 60, 3 },
  { 61, 5 },
  { 62, 4 },
  { 63, 4 },
  { 64, 1 },
  { 64, 2 },
  { 66, 3 },
  { 66, 3 },
  { 67, 1 },
  { 68, 4 },
  { 69, 2 },
  { 70, 3 },
  { 69, 2 },
  { 71, 1 },
  { 72, 4 },
  { 73, 2 },
  { 74, 6 },
  { 75, 2 },
  { 76, 2 },
  { 77, 2 },
  { 78, 2 },
  { 79, 4 },
  { 79, 3 },
  { 80, 2 },
  { 81, 2 },
  { 81, 3 },
  { 82, 5 },
  { 83, 2 },
  { 83, 2 },
  { 84, 1 },
  { 84, 1 },
  { 65, 2 },
  { 65, 1 },
  { 65, 1 },
  { 65, 1 },
  { 65, 1 },
  { 65, 1 },
  { 65, 1 },
  { 65, 1 },
  { 65, 2 },
  { 65, 1 },
  { 65, 1 },
  { 65, 1 },
  { 65, 1 },
  { 65, 1 },
  { 65, 1 },
  { 65, 1 },
  { 65, 1 },
  { 85, 1 },
  { 85, 1 },
  { 85, 1 },
  { 51, 0 },
  { 51, 2 },
};

static void yy_accept(yyParser*);  /* Forward Declaration */

/*
** Perform a reduce action and the shift that must immediately
** follow the reduce.
*/
static void yy_reduce(
  yyParser *yypParser,         /* The parser */
  int yyruleno                 /* Number of the rule by which to reduce */
){
  int yygoto;                     /* The next state */
  int yyact;                      /* The next action */
  YYMINORTYPE yygotominor;        /* The LHS of the rule reduced */
  yyStackEntry *yymsp;            /* The top of the parser's stack */
  int yysize;                     /* Amount to pop the stack */
  ParseARG_FETCH;
  yymsp = &yypParser->yystack[yypParser->yyidx];
#ifndef NDEBUG
  if( yyTraceFILE && yyruleno>=0 
        && yyruleno<(int)(sizeof(yyRuleName)/sizeof(yyRuleName[0])) ){
    fprintf(yyTraceFILE, "%sReduce [%s].\n", yyTracePrompt,
      yyRuleName[yyruleno]);
  }
#endif /* NDEBUG */

  /* Silence complaints from purify about yygotominor being uninitialized
  ** in some cases when it is copied into the stack after the following
  ** switch.  yygotominor is uninitialized when a rule reduces that does
  ** not set the value of its left-hand side nonterminal.  Leaving the
  ** value of the nonterminal uninitialized is utterly harmless as long
  ** as the value is never used.  So really the only thing this code
  ** accomplishes is to quieten purify.  
  **
  ** 2007-01-16:  The wireshark project (www.wireshark.org) reports that
  ** without this code, their parser segfaults.  I'm not sure what there
  ** parser is doing to make this happen.  This is the second bug report
  ** from wireshark this week.  Clearly they are stressing Lemon in ways
  ** that it has not been previously stressed...  (SQLite ticket #2172)
  */
  /*memset(&yygotominor, 0, sizeof(yygotominor));*/
  yygotominor = yyzerominor;


  switch( yyruleno ){
  /* Beginning here are the reduction cases.  A typical example
  ** follows:
  **   case 0:
  **  #line <lineno> <grammarfile>
  **     { ... }           // User supplied code
  **  #line <lineno> <thisfile>
  **     break;
  */
      case 1: /* numList ::= NUMBER COMMA NUMBER */
      case 2: /* numList ::= numList COMMA NUMBER */ yytestcase(yyruleno==2);
#line 54 "parser/epparser.lemon"
{
    yygotominor.yy0 = new Token(yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data, yymsp[0].minor.yy0);
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 1014 "parser/epparser.c"
        break;
      case 3: /* nameList ::= NAME COMMA NAME */
      case 4: /* nameList ::= nameList COMMA NAME */ yytestcase(yyruleno==4);
      case 8: /* exprList ::= exprList COMMA expr */ yytestcase(yyruleno==8);
#line 62 "parser/epparser.lemon"
{ yygotominor.yy0 = new Token((yymsp[-2].minor.yy0->data) + ", " + (yymsp[0].minor.yy0->data), yymsp[0].minor.yy0); delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1021 "parser/epparser.c"
        break;
      case 5: /* exprList ::= funcexpr LSQBRACKET LSQBRACKET numList RSQBRACKET RSQBRACKET */
      case 6: /* expr ::= funcexpr LSQBRACKET LSQBRACKET NUMBER RSQBRACKET RSQBRACKET */ yytestcase(yyruleno==6);
#line 64 "parser/epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[-2].minor.yy0);
    (*pGen) << yygotominor.yy0->data << " = _SRET(" << yymsp[-5].minor.yy0->data << ", [" << yymsp[-2].minor.yy0->data << "])" << std::endl;
    delete yymsp[-5].minor.yy0; delete yymsp[-2].minor.yy0;
}
#line 1031 "parser/epparser.c"
        break;
      case 7: /* exprList ::= expr */
      case 9: /* expr ::= NUMBER */ yytestcase(yyruleno==9);
      case 13: /* expr ::= funcexpr */ yytestcase(yyruleno==13);
      case 38: /* lexpr ::= LNOT LNOT lexpr */ yytestcase(yyruleno==38);
#line 75 "parser/epparser.lemon"
{ yygotominor.yy0 = yymsp[0].minor.yy0; }
#line 1039 "parser/epparser.c"
        break;
      case 10: /* expr ::= NAME */
#line 80 "parser/epparser.lemon"
{
    if(pGen->undefined(yymsp[0].minor.yy0->data)) {
        throw_error(yymsp[0].minor.yy0->line, 103, ("Undeclared variable \'" + (yymsp[0].minor.yy0->data) + "\'"));
        pGen->namedef(yymsp[0].minor.yy0->data);
    }
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1050 "parser/epparser.c"
        break;
      case 11: /* funcexpr ::= NAME LPAREN exprList RPAREN */
#line 89 "parser/epparser.lemon"
{
    // Preprocess yymsp[-3].minor.yy0
    if(yymsp[-3].minor.yy0->data[0] == '_' || ('A' <= yymsp[-3].minor.yy0->data[0] && yymsp[-3].minor.yy0->data[0] <= 'Z'));  // Name starts with uppercase -> Don't modify
    else {
        yymsp[-3].minor.yy0->data = "f_" + yymsp[-3].minor.yy0->data;
    }
    /*
    if (pGen->undefined(yymsp[-3].minor.yy0->data)) {
        throw_error(yymsp[-3].minor.yy0->line, 4449, ("Undefined function " + yymsp[-3].minor.yy0->data));
        pGen->namedef(yymsp[-3].minor.yy0->data);
    }
    */

    yymsp[-3].minor.yy0->data += "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0, *pGen);
}
#line 1070 "parser/epparser.c"
        break;
      case 12: /* funcexpr ::= NAME LPAREN RPAREN */
#line 107 "parser/epparser.lemon"
{
    // Preprocess yymsp[-2].minor.yy0
    if(yymsp[-2].minor.yy0->data[0] == '_' || ('A' <= yymsp[-2].minor.yy0->data[0] && yymsp[-2].minor.yy0->data[0] <= 'Z'));  // Name starts with uppercase -> Don't modify
    else {
        yymsp[-2].minor.yy0->data = "f_" + yymsp[-2].minor.yy0->data;
    }

    /*
    if (pGen->undefined(yymsp[-2].minor.yy0->data)) {
        throw_error(yymsp[-2].minor.yy0->line, 4449, ("Undefined function " + yymsp[-2].minor.yy0->data));
        pGen->namedef(yymsp[-2].minor.yy0->data);
    }
    */

    yymsp[-2].minor.yy0->data += "()";
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0, *pGen);
}
#line 1091 "parser/epparser.c"
        break;
      case 14: /* expr ::= LPAREN expr RPAREN */
#line 128 "parser/epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0, *pGen);
}
#line 1099 "parser/epparser.c"
        break;
      case 15: /* expr ::= expr PLUS expr */
#line 133 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "+",  yymsp[0].minor.yy0, *pGen); }
#line 1104 "parser/epparser.c"
        break;
      case 16: /* expr ::= expr MINUS expr */
#line 134 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "-",  yymsp[0].minor.yy0, *pGen); }
#line 1109 "parser/epparser.c"
        break;
      case 17: /* expr ::= expr MULTIPLY expr */
#line 135 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "*",  yymsp[0].minor.yy0, *pGen); }
#line 1114 "parser/epparser.c"
        break;
      case 18: /* expr ::= expr DIVIDE expr */
#line 136 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "//", yymsp[0].minor.yy0, *pGen); }
#line 1119 "parser/epparser.c"
        break;
      case 19: /* expr ::= expr MOD expr */
#line 137 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "%",  yymsp[0].minor.yy0, *pGen); }
#line 1124 "parser/epparser.c"
        break;
      case 20: /* expr ::= expr LSHIFT expr */
#line 138 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<<", yymsp[0].minor.yy0, *pGen); }
#line 1129 "parser/epparser.c"
        break;
      case 21: /* expr ::= expr RSHIFT expr */
#line 139 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">>", yymsp[0].minor.yy0, *pGen); }
#line 1134 "parser/epparser.c"
        break;
      case 22: /* expr ::= expr BITAND expr */
#line 140 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "&",  yymsp[0].minor.yy0, *pGen); }
#line 1139 "parser/epparser.c"
        break;
      case 23: /* expr ::= expr BITOR expr */
#line 141 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "|",  yymsp[0].minor.yy0, *pGen); }
#line 1144 "parser/epparser.c"
        break;
      case 24: /* expr ::= expr BITXOR expr */
#line 142 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "^",  yymsp[0].minor.yy0, *pGen); }
#line 1149 "parser/epparser.c"
        break;
      case 25: /* expr ::= PLUS expr */
#line 145 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = +" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1154 "parser/epparser.c"
        break;
      case 26: /* expr ::= MINUS expr */
#line 146 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = -" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1159 "parser/epparser.c"
        break;
      case 27: /* expr ::= BITNOT expr */
#line 147 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = ~" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1164 "parser/epparser.c"
        break;
      case 28: /* lexpr ::= CONDITIONNAME LPAREN exprList RPAREN */
#line 150 "parser/epparser.lemon"
{
    yymsp[-3].minor.yy0->data = yymsp[-3].minor.yy0->data + "(" + yymsp[-1].minor.yy0->data + ")";
    delete yymsp[-1].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0, *pGen);
}
#line 1173 "parser/epparser.c"
        break;
      case 29: /* lexpr ::= expr EQ expr */
#line 156 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "==", yymsp[0].minor.yy0, *pGen); }
#line 1178 "parser/epparser.c"
        break;
      case 30: /* lexpr ::= expr NE expr */
#line 157 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "!=", yymsp[0].minor.yy0, *pGen); }
#line 1183 "parser/epparser.c"
        break;
      case 31: /* lexpr ::= expr LE expr */
#line 158 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<=", yymsp[0].minor.yy0, *pGen); }
#line 1188 "parser/epparser.c"
        break;
      case 32: /* lexpr ::= expr LT expr */
#line 159 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<",  yymsp[0].minor.yy0, *pGen); }
#line 1193 "parser/epparser.c"
        break;
      case 33: /* lexpr ::= expr GE expr */
#line 160 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">=", yymsp[0].minor.yy0, *pGen); }
#line 1198 "parser/epparser.c"
        break;
      case 34: /* lexpr ::= expr GT expr */
#line 161 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">" , yymsp[0].minor.yy0, *pGen); }
#line 1203 "parser/epparser.c"
        break;
      case 35: /* lexpr ::= lexpr LAND lexpr */
#line 163 "parser/epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "[" + yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data + "]";
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0, *pGen);
}
#line 1212 "parser/epparser.c"
        break;
      case 36: /* lexpr ::= lexpr LOR lexpr */
#line 169 "parser/epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "EUDOr([" + yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data + "])";
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0, *pGen);
}
#line 1221 "parser/epparser.c"
        break;
      case 37: /* lexpr ::= LNOT lexpr */
#line 175 "parser/epparser.lemon"
{
    yymsp[0].minor.yy0->data = "EUDNot([" + yymsp[0].minor.yy0->data + "])";
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0, *pGen);
}
#line 1229 "parser/epparser.c"
        break;
      case 39: /* vdef_stmt ::= VAR NAME SEMICOLON */
#line 185 "parser/epparser.lemon"
{
    (*pGen) << yymsp[-1].minor.yy0->data << " = EUDVariable()" << std::endl;
    pGen->namedef(yymsp[-1].minor.yy0->data);
    delete yymsp[-1].minor.yy0;
}
#line 1238 "parser/epparser.c"
        break;
      case 40: /* vdefAssign_stmt ::= VAR NAME ASSIGN expr SEMICOLON */
#line 191 "parser/epparser.lemon"
{
    (*pGen) << yymsp[-3].minor.yy0->data << " = _MVAR([" << yymsp[-1].minor.yy0->data << "])" << std::endl;
    if(!pGen->namedef(yymsp[-3].minor.yy0->data)) {
        throw_error(yymsp[-3].minor.yy0->line, 196, ("Redeclaration of variable \'" + (yymsp[-3].minor.yy0->data) + "\'"));
    }
    delete yymsp[-3].minor.yy0;
}
#line 1249 "parser/epparser.c"
        break;
      case 41: /* vdefMulti_stmt ::= VAR nameList SEMICOLON */
#line 199 "parser/epparser.lemon"
{
    std::string& s = yymsp[-1].minor.yy0->data;
    int varCount = std::count(s.begin(), s.end(), ',') + 1;
    (*pGen) << s << " = EUDCreateVariables(" << varCount << ")" << std::endl;

    // Register variables.
    commaListIter(s, [&](const std::string& varname) {
        if(!pGen->namedef(varname)) {
            throw_error(yymsp[-1].minor.yy0->line, 196, ("Redeclaration of variable \'" + varname + "\'"));
        }
    });
    delete yymsp[-1].minor.yy0;
}
#line 1266 "parser/epparser.c"
        break;
      case 42: /* vdefMultiAssign_stmt ::= VAR nameList ASSIGN exprList SEMICOLON */
#line 213 "parser/epparser.lemon"
{
    std::string& s = yymsp[-3].minor.yy0->data;
    (*pGen) << s << " = _MVAR([" << yymsp[-1].minor.yy0->data << "])" << std::endl;

    // Register variables.
    commaListIter(s, [&](const std::string& varname) {
        if(!pGen->namedef(varname)) {
            throw_error(yymsp[-3].minor.yy0->line, 196, ("Redeclaration of variable \'" + varname + "\'"));
        }
    });

    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1283 "parser/epparser.c"
        break;
      case 43: /* assign_stmt ::= NAME ASSIGN expr SEMICOLON */
#line 227 "parser/epparser.lemon"
{
    (*pGen) << yymsp[-3].minor.yy0->data << " << " << yymsp[-1].minor.yy0->data << std::endl;
    if(pGen->undefined(yymsp[-3].minor.yy0->data)) {
        throw_error(yymsp[-3].minor.yy0->line, 103, ("Undeclared variable \'" + (yymsp[-3].minor.yy0->data) + "\'"));
        pGen->namedef(yymsp[-3].minor.yy0->data);
    }
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1295 "parser/epparser.c"
        break;
      case 44: /* assignMulti_stmt ::= nameList ASSIGN exprList SEMICOLON */
#line 236 "parser/epparser.lemon"
{
    (*pGen) << "SetVariables([" << yymsp[-3].minor.yy0->data << "], [" << yymsp[-1].minor.yy0->data << "])" << std::endl;

    commaListIter(yymsp[-3].minor.yy0->data, [&](const std::string& varname) {
        if(pGen->undefined(varname)) {
            throw_error(yymsp[-3].minor.yy0->line, 103, ("Undeclared variable \'" + varname + "\'"));
            pGen->namedef(varname);
        }
    });

    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1311 "parser/epparser.c"
        break;
      case 48: /* block ::= LBRACKET error RBRACKET */
#line 253 "parser/epparser.lemon"
{
    throw_error(yymsp[0].minor.yy0->line, 6298, "Block not terminated properly.");
}
#line 1318 "parser/epparser.c"
        break;
      case 49: /* if_start ::= IF */
#line 259 "parser/epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    (*pGen) << yygotominor.yy0->data << " = EUDIf()" << std::endl;
}
#line 1326 "parser/epparser.c"
        break;
      case 50: /* if_header ::= if_start LPAREN lexpr RPAREN */
      case 55: /* while_header ::= while_start LPAREN lexpr RPAREN */ yytestcase(yyruleno==55);
#line 263 "parser/epparser.lemon"
{
    (*pGen) << "if " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data << "):" << std::endl;
    pGen->indent();
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1336 "parser/epparser.c"
        break;
      case 51: /* if_stmt ::= if_header stmt */
      case 53: /* if_stmt ::= else_header stmt */ yytestcase(yyruleno==53);
      case 56: /* while_stmt ::= while_header stmt */ yytestcase(yyruleno==56);
#line 269 "parser/epparser.lemon"
{
    pGen->unindent();
    (*pGen) << "EUDEndIf()" << std::endl;
}
#line 1346 "parser/epparser.c"
        break;
      case 52: /* else_header ::= if_header stmt ELSE */
#line 274 "parser/epparser.lemon"
{
    pGen->unindent();
    (*pGen) << "if EUDElse():" << std::endl;
    pGen->indent();
}
#line 1355 "parser/epparser.c"
        break;
      case 54: /* while_start ::= WHILE */
#line 287 "parser/epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    (*pGen) << yygotominor.yy0->data << " = EUDWhile()" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1364 "parser/epparser.c"
        break;
      case 57: /* foreach_header ::= FOR LPAREN nameList COLON exprList RPAREN */
#line 305 "parser/epparser.lemon"
{
    (*pGen) << "for " << yymsp[-3].minor.yy0->data << " in " << yymsp[-1].minor.yy0->data << ":" << std::endl;
    pGen->indent();
}
#line 1372 "parser/epparser.c"
        break;
      case 58: /* foreach_stmt ::= foreach_header stmt */
      case 64: /* fdef_chunk ::= function_header stmt */ yytestcase(yyruleno==64);
#line 310 "parser/epparser.lemon"
{
    pGen->unindent();
}
#line 1380 "parser/epparser.c"
        break;
      case 59: /* continue_stmt ::= CONTINUE SEMICOLON */
#line 316 "parser/epparser.lemon"
{
    (*pGen) << "EUDContinue()" << std::endl;
}
#line 1387 "parser/epparser.c"
        break;
      case 60: /* break_stmt ::= BREAK SEMICOLON */
#line 320 "parser/epparser.lemon"
{
    (*pGen) << "EUDBreak()" << std::endl;
}
#line 1394 "parser/epparser.c"
        break;
      case 61: /* function_start ::= FUNCTION NAME */
#line 325 "parser/epparser.lemon"
{
    // Preprocess yymsp[0].minor.yy0
    if(yymsp[0].minor.yy0->data[0] == '_' || ('A' <= yymsp[0].minor.yy0->data[0] && yymsp[0].minor.yy0->data[0] <= 'Z'));  // Name starts with uppercase -> Don't modify
    else {
        yymsp[0].minor.yy0->data = "f_" + yymsp[0].minor.yy0->data;
    }

    yygotominor.yy0 = yymsp[0].minor.yy0;
    if(!pGen->namedef(yymsp[0].minor.yy0->data)) {
        throw_error(yymsp[0].minor.yy0->line, 4495, "Duplicate function yymsp[0].minor.yy0 " + yymsp[0].minor.yy0->data);
    }
}
#line 1410 "parser/epparser.c"
        break;
      case 62: /* function_header ::= function_start LPAREN nameList RPAREN */
#line 338 "parser/epparser.lemon"
{
    (*pGen) << "@EUDFunc" << std::endl;
    (*pGen) << "def " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data << "):" << std::endl;
    pGen->indent();

    // Register variables.
    const std::string& s = yymsp[-1].minor.yy0->data;
    commaListIter(yymsp[-1].minor.yy0->data, [&](const std::string& varname) {
        if(!pGen->namedef(varname)) {
            throw_error(yymsp[-1].minor.yy0->line, 196, ("Redeclaration of variable \'" + varname + "\'"));
        }
    });

    tmpIndex = 1;
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1430 "parser/epparser.c"
        break;
      case 63: /* function_header ::= function_start LPAREN RPAREN */
#line 355 "parser/epparser.lemon"
{
    (*pGen) << "@EUDFunc" << std::endl;
    (*pGen) << "def " << yymsp[-2].minor.yy0->data << "():" << std::endl;
    pGen->indent();
    tmpIndex = 1;
    delete yymsp[-2].minor.yy0;
}
#line 1441 "parser/epparser.c"
        break;
      case 65: /* return_stmt ::= RETURN SEMICOLON */
#line 369 "parser/epparser.lemon"
{
    (*pGen) << "EUDReturn()" << std::endl;
}
#line 1448 "parser/epparser.c"
        break;
      case 66: /* return_stmt ::= RETURN exprList SEMICOLON */
#line 372 "parser/epparser.lemon"
{
    (*pGen) << "EUDReturn(" << yymsp[-1].minor.yy0->data << ")" << std::endl;
    delete yymsp[-1].minor.yy0;
}
#line 1456 "parser/epparser.c"
        break;
      case 67: /* action ::= ACTIONNAME LPAREN exprList RPAREN SEMICOLON */
#line 380 "parser/epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[-4].minor.yy0);
    yygotominor.yy0->data =  yymsp[-4].minor.yy0->data + "(" + yymsp[-2].minor.yy0->data + ")";
    delete yymsp[-4].minor.yy0; delete yymsp[-2].minor.yy0;
}
#line 1465 "parser/epparser.c"
        break;
      case 68: /* actions ::= action action */
      case 69: /* actions ::= actions action */ yytestcase(yyruleno==69);
#line 386 "parser/epparser.lemon"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
    yymsp[-1].minor.yy0->data += ",\n" + yymsp[0].minor.yy0->data;
    delete yymsp[0].minor.yy0;
}
#line 1475 "parser/epparser.c"
        break;
      case 70: /* actionStmt ::= action */
#line 398 "parser/epparser.lemon"
{
    (*pGen) << "DoEvents(" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1483 "parser/epparser.c"
        break;
      case 71: /* actionStmt ::= actions */
#line 403 "parser/epparser.lemon"
{
    (*pGen) << "DoEvents([" << std::endl;
    pGen->indent();
    (*pGen) << yymsp[0].minor.yy0->data << std::endl;
    pGen->unindent(false);
    (*pGen) << "])" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1495 "parser/epparser.c"
        break;
      case 72: /* stmt ::= error SEMICOLON */
#line 414 "parser/epparser.lemon"
{ throw_error(yymsp[0].minor.yy0->line, 6974, "Error while parsing statement"); }
#line 1500 "parser/epparser.c"
        break;
      case 80: /* stmt ::= expr SEMICOLON */
#line 424 "parser/epparser.lemon"
{ (*pGen) << yymsp[-1].minor.yy0->data << std::endl; }
#line 1505 "parser/epparser.c"
        break;
      default:
      /* (0) program ::= chunks */ yytestcase(yyruleno==0);
      /* (45) stmtList ::= stmt */ yytestcase(yyruleno==45);
      /* (46) stmtList ::= stmtList stmt */ yytestcase(yyruleno==46);
      /* (47) block ::= LBRACKET stmtList RBRACKET */ yytestcase(yyruleno==47);
      /* (73) stmt ::= SEMICOLON */ yytestcase(yyruleno==73);
      /* (74) stmt ::= vdef_stmt */ yytestcase(yyruleno==74);
      /* (75) stmt ::= vdefAssign_stmt */ yytestcase(yyruleno==75);
      /* (76) stmt ::= vdefMultiAssign_stmt */ yytestcase(yyruleno==76);
      /* (77) stmt ::= vdefMulti_stmt */ yytestcase(yyruleno==77);
      /* (78) stmt ::= assign_stmt */ yytestcase(yyruleno==78);
      /* (79) stmt ::= assignMulti_stmt */ yytestcase(yyruleno==79);
      /* (81) stmt ::= actionStmt */ yytestcase(yyruleno==81);
      /* (82) stmt ::= if_stmt */ yytestcase(yyruleno==82);
      /* (83) stmt ::= while_stmt */ yytestcase(yyruleno==83);
      /* (84) stmt ::= foreach_stmt */ yytestcase(yyruleno==84);
      /* (85) stmt ::= continue_stmt */ yytestcase(yyruleno==85);
      /* (86) stmt ::= break_stmt */ yytestcase(yyruleno==86);
      /* (87) stmt ::= return_stmt */ yytestcase(yyruleno==87);
      /* (88) stmt ::= block */ yytestcase(yyruleno==88);
      /* (89) chunk ::= fdef_chunk */ yytestcase(yyruleno==89);
      /* (90) chunk ::= vdef_stmt */ yytestcase(yyruleno==90);
      /* (91) chunk ::= vdefMulti_stmt */ yytestcase(yyruleno==91);
      /* (92) chunks ::= */ yytestcase(yyruleno==92);
      /* (93) chunks ::= chunks chunk */ yytestcase(yyruleno==93);
        break;
  };
  yygoto = yyRuleInfo[yyruleno].lhs;
  yysize = yyRuleInfo[yyruleno].nrhs;
  yypParser->yyidx -= yysize;
  yyact = yy_find_reduce_action(yymsp[-yysize].stateno,(YYCODETYPE)yygoto);
  if( yyact < YYNSTATE ){
#ifdef NDEBUG
    /* If we are not debugging and the reduce action popped at least
    ** one element off the stack, then we can push the new element back
    ** onto the stack here, and skip the stack overflow test in yy_shift().
    ** That gives a significant speed improvement. */
    if( yysize ){
      yypParser->yyidx++;
      yymsp -= yysize-1;
      yymsp->stateno = (YYACTIONTYPE)yyact;
      yymsp->major = (YYCODETYPE)yygoto;
      yymsp->minor = yygotominor;
    }else
#endif
    {
      yy_shift(yypParser,yyact,yygoto,&yygotominor);
    }
  }else{
    assert( yyact == YYNSTATE + YYNRULE + 1 );
    yy_accept(yypParser);
  }
}

/*
** The following code executes when the parse fails
*/
#ifndef YYNOERRORRECOVERY
static void yy_parse_failed(
  yyParser *yypParser           /* The parser */
){
  ParseARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sFail!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser fails */
#line 20 "parser/epparser.lemon"

    throw_error(-1, 629, "Unrecoverable error");
#line 1580 "parser/epparser.c"
  ParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}
#endif /* YYNOERRORRECOVERY */

/*
** The following code executes when a syntax error first occurs.
*/
static void yy_syntax_error(
  yyParser *yypParser,           /* The parser */
  int yymajor,                   /* The major type of the error token */
  YYMINORTYPE yyminor            /* The minor type of the error token */
){
  ParseARG_FETCH;
#define TOKEN (yyminor.yy0)
#line 15 "parser/epparser.lemon"

    errorOccured = true;
    throw_error(currentTokenizingLine, 629, "General syntax error");
#line 1599 "parser/epparser.c"
  ParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/*
** The following is executed when the parser accepts
*/
static void yy_accept(
  yyParser *yypParser           /* The parser */
){
  ParseARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sAccept!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser accepts */
  ParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/* The main parser program.
** The first argument is a pointer to a structure obtained from
** "ParseAlloc" which describes the current state of the parser.
** The second argument is the major token number.  The third is
** the minor token.  The fourth optional argument is whatever the
** user wants (and specified in the grammar) and is available for
** use by the action routines.
**
** Inputs:
** <ul>
** <li> A pointer to the parser (an opaque structure.)
** <li> The major token number.
** <li> The minor token number.
** <li> An option argument of a grammar-specified type.
** </ul>
**
** Outputs:
** None.
*/
void Parse(
  void *yyp,                   /* The parser */
  int yymajor,                 /* The major token code number */
  ParseTOKENTYPE yyminor       /* The value for the token */
  ParseARG_PDECL               /* Optional %extra_argument parameter */
){
  YYMINORTYPE yyminorunion;
  int yyact;            /* The parser action. */
  int yyendofinput;     /* True if we are at the end of input */
#ifdef YYERRORSYMBOL
  int yyerrorhit = 0;   /* True if yymajor has invoked an error */
#endif
  yyParser *yypParser;  /* The parser */

  /* (re)initialize the parser, if necessary */
  yypParser = (yyParser*)yyp;
  if( yypParser->yyidx<0 ){
#if YYSTACKDEPTH<=0
    if( yypParser->yystksz <=0 ){
      /*memset(&yyminorunion, 0, sizeof(yyminorunion));*/
      yyminorunion = yyzerominor;
      yyStackOverflow(yypParser, &yyminorunion);
      return;
    }
#endif
    yypParser->yyidx = 0;
    yypParser->yyerrcnt = -1;
    yypParser->yystack[0].stateno = 0;
    yypParser->yystack[0].major = 0;
  }
  yyminorunion.yy0 = yyminor;
  yyendofinput = (yymajor==0);
  ParseARG_STORE;

#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sInput %s\n",yyTracePrompt,yyTokenName[yymajor]);
  }
#endif

  do{
    yyact = yy_find_shift_action(yypParser,(YYCODETYPE)yymajor);
    if( yyact<YYNSTATE ){
      assert( !yyendofinput );  /* Impossible to shift the $ token */
      yy_shift(yypParser,yyact,yymajor,&yyminorunion);
      yypParser->yyerrcnt--;
      yymajor = YYNOCODE;
    }else if( yyact < YYNSTATE + YYNRULE ){
      yy_reduce(yypParser,yyact-YYNSTATE);
    }else{
      assert( yyact == YY_ERROR_ACTION );
#ifdef YYERRORSYMBOL
      int yymx;
#endif
#ifndef NDEBUG
      if( yyTraceFILE ){
        fprintf(yyTraceFILE,"%sSyntax Error!\n",yyTracePrompt);
      }
#endif
#ifdef YYERRORSYMBOL
      /* A syntax error has occurred.
      ** The response to an error depends upon whether or not the
      ** grammar defines an error token "ERROR".  
      **
      ** This is what we do if the grammar does define ERROR:
      **
      **  * Call the %syntax_error function.
      **
      **  * Begin popping the stack until we enter a state where
      **    it is legal to shift the error symbol, then shift
      **    the error symbol.
      **
      **  * Set the error count to three.
      **
      **  * Begin accepting and shifting new tokens.  No new error
      **    processing will occur until three tokens have been
      **    shifted successfully.
      **
      */
      if( yypParser->yyerrcnt<0 ){
        yy_syntax_error(yypParser,yymajor,yyminorunion);
      }
      yymx = yypParser->yystack[yypParser->yyidx].major;
      if( yymx==YYERRORSYMBOL || yyerrorhit ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE,"%sDiscard input token %s\n",
             yyTracePrompt,yyTokenName[yymajor]);
        }
#endif
        yy_destructor(yypParser, (YYCODETYPE)yymajor,&yyminorunion);
        yymajor = YYNOCODE;
      }else{
         while(
          yypParser->yyidx >= 0 &&
          yymx != YYERRORSYMBOL &&
          (yyact = yy_find_reduce_action(
                        yypParser->yystack[yypParser->yyidx].stateno,
                        YYERRORSYMBOL)) >= YYNSTATE
        ){
          yy_pop_parser_stack(yypParser);
        }
        if( yypParser->yyidx < 0 || yymajor==0 ){
          yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
          yy_parse_failed(yypParser);
          yymajor = YYNOCODE;
        }else if( yymx!=YYERRORSYMBOL ){
          YYMINORTYPE u2;
          u2.YYERRSYMDT = 0;
          yy_shift(yypParser,yyact,YYERRORSYMBOL,&u2);
        }
      }
      yypParser->yyerrcnt = 3;
      yyerrorhit = 1;
#elif defined(YYNOERRORRECOVERY)
      /* If the YYNOERRORRECOVERY macro is defined, then do not attempt to
      ** do any kind of error recovery.  Instead, simply invoke the syntax
      ** error routine and continue going as if nothing had happened.
      **
      ** Applications can set this macro (for example inside %include) if
      ** they intend to abandon the parse upon the first syntax error seen.
      */
      yy_syntax_error(yypParser,yymajor,yyminorunion);
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      yymajor = YYNOCODE;
      
#else  /* YYERRORSYMBOL is not defined */
      /* This is what we do if the grammar does not define ERROR:
      **
      **  * Report an error message, and throw away the input token.
      **
      **  * If the input token is $, then fail the parse.
      **
      ** As before, subsequent error messages are suppressed until
      ** three input tokens have been successfully shifted.
      */
      if( yypParser->yyerrcnt<=0 ){
        yy_syntax_error(yypParser,yymajor,yyminorunion);
      }
      yypParser->yyerrcnt = 3;
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      if( yyendofinput ){
        yy_parse_failed(yypParser);
      }
      yymajor = YYNOCODE;
#endif
    }
  }while( yymajor!=YYNOCODE && yypParser->yyidx>=0 );
  return;
}
#line 442 "parser/epparser.lemon"


// #define PARSER_DEBUG

std::string ParseString(const std::string& code)
{
    std::istringstream is(code);
    Tokenizer tok(is);
    void* pParser = ParseAlloc (malloc);
    PyGenerator pGen;
    Token* token;
    currentTokenizingLine = 0;

#ifdef PARSER_DEBUG
    std::cout << "Parsing string [[[\n" << code << "\n]]]\n";
#endif

    tmpIndex = 1;
    errorOccured = false;
    while ((token = tok.getToken()) != nullptr) {
        if (currentTokenizingLine != tok.getCurrentLine()) {
            currentTokenizingLine = tok.getCurrentLine();
            pGen << "# (Line " << currentTokenizingLine << ") " << trim(tok.getCurrentLineString()) << std::endl;
#ifdef PARSER_DEBUG
            printf("reading line %s\n", tok.getCurrentLineString().c_str());
#endif
        }
        if (tokenTypeConv(token)) {
            Parse (pParser, token->type, token, &pGen);
#ifdef PARSER_DEBUG
            ParseTrace(stdout, "-- ");
#endif
        }
        else {
            throw_error(token->line, 8104, "Invalid token");
        }
    }
    Parse (pParser, 0, nullptr, &pGen);
    ParseFree(pParser, free );

    if(!errorOccured) return pGen.str();
    // else throw std::runtime_error("Invalid syntax");
    return pGen.str();
}
#line 1835 "parser/epparser.c"
