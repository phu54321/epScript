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
#define YYNOCODE 93
#define YYACTIONTYPE unsigned short int
#define ParseTOKENTYPE Token*
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  int yy185;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL  PyGenerator* pGen ;
#define ParseARG_PDECL , PyGenerator* pGen 
#define ParseARG_FETCH  PyGenerator* pGen  = yypParser->pGen 
#define ParseARG_STORE yypParser->pGen  = pGen 
#define YYNSTATE 211
#define YYNRULE 102
#define YYERRORSYMBOL 53
#define YYERRSYMDT yy185
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
#define YY_ACTTAB_COUNT (609)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */    79,  132,  132,   30,  125,   87,  210,  121,   55,  208,
 /*    10 */   152,  151,  149,  150,  148,  147,    2,  180,  139,  104,
 /*    20 */     6,  145,    5,  100,    4,  144,    3,  143,  142,  141,
 /*    30 */    19,  124,  206,  140,   94,   48,   47,  146,  209,   87,
 /*    40 */   131,  121,   55,  131,  152,  151,  149,  150,  148,  147,
 /*    50 */    46,  137,  139,  104,    6,  145,    5,  100,    4,  144,
 /*    60 */     3,  143,  142,  141,  121,   53,   73,  140,   94,   48,
 /*    70 */    47,  146,  205,   87,  132,  121,   55,  207,  152,  151,
 /*    80 */   149,  150,  148,  147,  126,  101,  139,  104,    6,  145,
 /*    90 */     5,  100,    4,  144,    3,  143,  142,  141,  121,   53,
 /*   100 */   176,  140,   94,   48,   47,  146,  154,   87,  138,  121,
 /*   110 */    55,   31,  152,  151,  149,  150,  148,  147,   51,  167,
 /*   120 */   139,  104,    6,  145,    5,  100,    4,  144,    3,  143,
 /*   130 */   142,  141,  121,   53,  103,  140,   94,   48,   47,  146,
 /*   140 */   187,   87,   31,  121,   55,   18,  152,  151,  149,  150,
 /*   150 */   148,  147,  203,  164,  139,  104,    6,  145,    5,  100,
 /*   160 */     4,  144,    3,  143,  142,  141,  121,   53,  175,  140,
 /*   170 */    94,   48,   47,  146,  171,   87,  202,  121,   55,  184,
 /*   180 */   152,  151,  149,  150,  148,  147,  123,  162,  139,  104,
 /*   190 */     6,  145,    5,  100,    4,  144,    3,  143,  142,  141,
 /*   200 */   201,  132,   29,  140,   94,   48,   47,  146,  200,   87,
 /*   210 */   120,  121,   55,  122,  152,  151,  149,  150,  148,  147,
 /*   220 */    31,  179,  139,  104,    6,  145,    5,  100,    4,  144,
 /*   230 */     3,  143,  142,  141,  121,   53,  174,  140,  209,   48,
 /*   240 */    47,  146,   34,   33,  131,   41,   42,   40,   32,  199,
 /*   250 */    78,  131,   22,   44,   13,   14,  116,  181,  113,  110,
 /*   260 */   107,   50,  153,    1,  178,  177,  121,   76,  166,   99,
 /*   270 */    31,   98,   97,   31,   17,  119,   96,   34,   33,   18,
 /*   280 */   118,  169,  128,   32,  199,   78,  204,   19,   44,   20,
 /*   290 */   124,  116,  115,  113,  110,  107,   50,  153,    1,  163,
 /*   300 */   177,  121,   57,  166,   99,  197,   98,   97,   95,   17,
 /*   310 */   159,   96,   28,   26,   25,   24,   23,   27,   36,   35,
 /*   320 */    37,   39,   38,   45,   43,   41,   42,   40,   12,   36,
 /*   330 */    35,   37,   39,   38,   45,   43,   41,   42,   40,  121,
 /*   340 */    77,   34,   33,  114,  131,   21,  198,   32,  199,  117,
 /*   350 */   121,  193,   44,  314,    8,  116,  112,  113,  110,  107,
 /*   360 */    86,  127,   66,   11,   35,   37,   39,   38,   45,   43,
 /*   370 */    41,   42,   40,  111,  102,  196,   34,   33,  135,  108,
 /*   380 */   134,  207,   32,  199,  117,  121,  192,   44,   13,   14,
 /*   390 */   116,  109,  113,  110,  107,  195,   34,   33,  129,    7,
 /*   400 */   136,  106,   32,  199,  117,  194,  133,   44,  170,  102,
 /*   410 */   116,  173,  113,  110,  107,  165,   36,   35,   37,   39,
 /*   420 */    38,   45,   43,   41,   42,   40,   36,   35,   37,   39,
 /*   430 */    38,   45,   43,   41,   42,   40,   34,   33,   85,  127,
 /*   440 */    66,  185,   32,  199,  117,  105,   15,   44,  186,   14,
 /*   450 */   116,  183,  113,  110,  107,   36,   35,   37,   39,   38,
 /*   460 */    45,   43,   41,   42,   40,  121,  191,   34,   33,   82,
 /*   470 */   127,   66,   10,   32,  199,  117,  121,   71,   44,  168,
 /*   480 */   182,  116,  173,  113,  110,  107,   34,   33,   88,  127,
 /*   490 */    66,    9,   32,  199,  117,  121,   58,   44,  121,   70,
 /*   500 */   116,   49,  113,  110,  107,  161,  158,   36,   35,   37,
 /*   510 */    39,   38,   45,   43,   41,   42,   40,  121,   69,   34,
 /*   520 */    33,  160,  172,  121,   67,   32,  199,  117,   16,  157,
 /*   530 */    44,  121,   58,  116,  154,  113,  110,  107,   81,  127,
 /*   540 */    66,   37,   39,   38,   45,   43,   41,   42,   40,  211,
 /*   550 */    39,   38,   45,   43,   41,   42,   40,   93,   80,   89,
 /*   560 */    45,   43,   41,   42,   40,  121,   58,  121,   53,   72,
 /*   570 */   121,   68,  121,  190,  121,  189,  121,  188,  121,   65,
 /*   580 */   121,   56,   92,  121,   54,   90,   52,  121,   64,   75,
 /*   590 */    74,  128,   84,  121,   63,   83,  121,   62,  130,  121,
 /*   600 */    61,  121,   60,  121,   59,  156,   96,  155,   91,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    53,    1,    1,    2,    1,   58,   26,   60,   61,   26,
 /*    10 */    63,   64,   65,   66,   67,   68,   69,   70,   71,   72,
 /*    20 */    73,   74,   75,   76,   77,   78,   79,   80,   81,   82,
 /*    30 */    29,   28,   26,   86,   53,   88,   89,   90,   38,   58,
 /*    40 */     1,   60,   61,    1,   63,   64,   65,   66,   67,   68,
 /*    50 */    29,   70,   71,   72,   73,   74,   75,   76,   77,   78,
 /*    60 */    79,   80,   81,   82,   60,   61,   62,   86,   53,   88,
 /*    70 */    89,   90,   30,   58,    1,   60,   61,   38,   63,   64,
 /*    80 */    65,   66,   67,   68,   27,   70,   71,   72,   73,   74,
 /*    90 */    75,   76,   77,   78,   79,   80,   81,   82,   60,   61,
 /*   100 */    62,   86,   53,   88,   89,   90,   38,   58,   40,   60,
 /*   110 */    61,    1,   63,   64,   65,   66,   67,   68,   27,   70,
 /*   120 */    71,   72,   73,   74,   75,   76,   77,   78,   79,   80,
 /*   130 */    81,   82,   60,   61,   62,   86,   53,   88,   89,   90,
 /*   140 */    30,   58,    1,   60,   61,    1,   63,   64,   65,   66,
 /*   150 */    67,   68,   25,   70,   71,   72,   73,   74,   75,   76,
 /*   160 */    77,   78,   79,   80,   81,   82,   60,   61,   62,   86,
 /*   170 */    53,   88,   89,   90,   30,   58,   28,   60,   61,   38,
 /*   180 */    63,   64,   65,   66,   67,   68,    1,   70,   71,   72,
 /*   190 */    73,   74,   75,   76,   77,   78,   79,   80,   81,   82,
 /*   200 */    25,    1,    2,   86,   53,   88,   89,   90,   28,   58,
 /*   210 */    27,   60,   61,   28,   63,   64,   65,   66,   67,   68,
 /*   220 */     1,   70,   71,   72,   73,   74,   75,   76,   77,   78,
 /*   230 */    79,   80,   81,   82,   60,   61,   62,   86,   38,   88,
 /*   240 */    89,   90,   18,   19,    1,   20,   21,   22,   24,   25,
 /*   250 */    26,    1,    2,   29,    3,    4,   32,   38,   34,   35,
 /*   260 */    36,   37,   38,   39,   40,   41,   60,   61,   44,   45,
 /*   270 */     1,   47,   48,    1,   50,   27,   52,   18,   19,    1,
 /*   280 */    25,   30,   26,   24,   25,   26,   30,   29,   29,   46,
 /*   290 */    28,   32,   29,   34,   35,   36,   37,   38,   39,   30,
 /*   300 */    41,   60,   61,   44,   45,   30,   47,   48,   30,   50,
 /*   310 */    38,   52,    7,    8,    9,   10,   11,   12,   13,   14,
 /*   320 */    15,   16,   17,   18,   19,   20,   21,   22,    5,   13,
 /*   330 */    14,   15,   16,   17,   18,   19,   20,   21,   22,   60,
 /*   340 */    61,   18,   19,   33,    1,    2,   30,   24,   25,   26,
 /*   350 */    60,   61,   29,   55,   56,   32,   29,   34,   35,   36,
 /*   360 */    59,   60,   61,    5,   14,   15,   16,   17,   18,   19,
 /*   370 */    20,   21,   22,   33,   51,   30,   18,   19,   63,   33,
 /*   380 */    65,   38,   24,   25,   26,   60,   61,   29,    3,    4,
 /*   390 */    32,   29,   34,   35,   36,   30,   18,   19,   83,   84,
 /*   400 */    85,   29,   24,   25,   26,   30,   91,   29,   30,   51,
 /*   410 */    32,   33,   34,   35,   36,   30,   13,   14,   15,   16,
 /*   420 */    17,   18,   19,   20,   21,   22,   13,   14,   15,   16,
 /*   430 */    17,   18,   19,   20,   21,   22,   18,   19,   59,   60,
 /*   440 */    61,   38,   24,   25,   26,   33,   29,   29,   30,    4,
 /*   450 */    32,   38,   34,   35,   36,   13,   14,   15,   16,   17,
 /*   460 */    18,   19,   20,   21,   22,   60,   61,   18,   19,   59,
 /*   470 */    60,   61,   29,   24,   25,   26,   60,   61,   29,   43,
 /*   480 */    38,   32,   33,   34,   35,   36,   18,   19,   59,   60,
 /*   490 */    61,   29,   24,   25,   26,   60,   61,   29,   60,   61,
 /*   500 */    32,   29,   34,   35,   36,   38,   38,   13,   14,   15,
 /*   510 */    16,   17,   18,   19,   20,   21,   22,   60,   61,   18,
 /*   520 */    19,   38,   87,   60,   61,   24,   25,   26,   29,   38,
 /*   530 */    29,   60,   61,   32,   38,   34,   35,   36,   59,   60,
 /*   540 */    61,   15,   16,   17,   18,   19,   20,   21,   22,    0,
 /*   550 */    16,   17,   18,   19,   20,   21,   22,   26,   87,   57,
 /*   560 */    18,   19,   20,   21,   22,   60,   61,   60,   61,   62,
 /*   570 */    60,   61,   60,   61,   60,   61,   60,   61,   60,   61,
 /*   580 */    60,   61,   58,   60,   61,   25,   37,   60,   61,   26,
 /*   590 */    58,   26,   87,   60,   61,   58,   60,   61,   49,   60,
 /*   600 */    61,   60,   61,   60,   61,   88,   52,   88,   58,
};
#define YY_SHIFT_USE_DFLT (-21)
#define YY_SHIFT_COUNT (132)
#define YY_SHIFT_MIN   (-20)
#define YY_SHIFT_MAX   (565)
static const short yy_shift_ofst[] = {
 /*     0 */   -21,  259,  224,  259,  259,  259,  259,  259,  549,  323,
 /*    10 */   378,  358,  358,  323,  323,  323,  449,  468,  449,  418,
 /*    20 */   501,  501,  501,  501,  501,  501,  501,  501,  501,  501,
 /*    30 */   501,  501,  501,  501,  501,  501,  501,  501,  501,  501,
 /*    40 */   501,  501,  501,  501,  501,  501,  256,  554,  554,  565,
 /*    50 */   563,  560,  531,  305,  442,  413,  403,  316,  494,  494,
 /*    60 */   494,  494,  494,  494,  494,  494,  494,  350,  526,  534,
 /*    70 */   542,  542,  385,  251,  343,  200,  225,  225,    1,   68,
 /*    80 */   278,  272,  269,  243,  144,  219,  141,  250,  110,  185,
 /*    90 */     3,   42,   39,    0,  496,  491,  499,  483,  467,  472,
 /*   100 */   462,  436,  443,  445,  417,  375,  412,  372,  365,  346,
 /*   110 */   362,  345,  340,  327,  275,  310,  263,  258,  262,  255,
 /*   120 */   248,  183,  180,  175,  148,  127,   91,   57,   73,   21,
 /*   130 */     6,  -17,  -20,
};
#define YY_REDUCE_USE_DFLT (-54)
#define YY_REDUCE_COUNT (52)
#define YY_REDUCE_MIN   (-53)
#define YY_REDUCE_MAX   (550)
static const short yy_reduce_ofst[] = {
 /*     0 */   298,  -53,  151,  117,   83,   49,   15,  -19,  315,  507,
 /*    10 */   505,  174,  106,   72,   38,    4,  471,  479,  435,  429,
 /*    20 */   410,  379,  301,  543,  541,  539,  536,  533,  527,  523,
 /*    30 */   520,  518,  516,  514,  512,  510,  463,  457,  438,  416,
 /*    40 */   405,  325,  290,  279,  241,  206,  550,  519,  517,  537,
 /*    50 */   532,  502,  524,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   311,  313,  313,  313,  313,  313,  313,  313,  313,  313,
 /*    10 */   313,  313,  313,  313,  313,  313,  313,  313,  313,  313,
 /*    20 */   313,  313,  313,  313,  313,  313,  313,  313,  313,  313,
 /*    30 */   313,  313,  313,  313,  313,  313,  313,  313,  313,  313,
 /*    40 */   313,  313,  313,  313,  313,  313,  313,  290,  289,  313,
 /*    50 */   313,  313,  313,  313,  313,  313,  313,  313,  281,  248,
 /*    60 */   247,  246,  245,  244,  243,  219,  218,  238,  239,  237,
 /*    70 */   236,  235,  313,  313,  313,  313,  230,  231,  221,  313,
 /*    80 */   313,  313,  313,  313,  313,  313,  313,  313,  313,  313,
 /*    90 */   313,  313,  313,  313,  313,  313,  313,  313,  313,  313,
 /*   100 */   313,  265,  313,  250,  313,  313,  313,  313,  313,  313,
 /*   110 */   313,  313,  313,  313,  313,  313,  313,  221,  313,  313,
 /*   120 */   313,  224,  313,  313,  313,  313,  313,  224,  313,  313,
 /*   130 */   313,  313,  313,  312,  310,  309,  308,  278,  262,  307,
 /*   140 */   306,  305,  304,  303,  302,  301,  300,  298,  297,  296,
 /*   150 */   295,  294,  293,  292,  291,  288,  287,  286,  279,  280,
 /*   160 */   274,  273,  272,  271,  270,  269,  268,  267,  266,  264,
 /*   170 */   285,  284,  283,  282,  252,  251,  249,  263,  261,  260,
 /*   180 */   259,  256,  254,  299,  258,  257,  223,  222,  242,  241,
 /*   190 */   240,  234,  233,  232,  229,  228,  227,  226,  225,  220,
 /*   200 */   216,  213,  217,  212,  277,  276,  275,  255,  215,  253,
 /*   210 */   214,
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
  "MAPSTRING",     "STRING",        "UNIT",          "SWITCH",      
  "LOCATION",      "VAR",           "SEMICOLON",     "LBRACKET",    
  "RBRACKET",      "IF",            "IFX",           "ELSE",        
  "WHILE",         "FOR",           "COLON",         "CONTINUE",    
  "BREAK",         "FUNCTION",      "RETURN",        "CONDITIONNAME",
  "ACTIONNAME",    "error",         "nt",            "program",     
  "chunks",        "numList",       "nameList",      "exprList",    
  "funcexpr",      "expr",          "lexpr",         "vdef_stmt",   
  "vdefAssign_stmt",  "vdefMulti_stmt",  "vdefMultiAssign_stmt",  "assign_stmt", 
  "assignMulti_stmt",  "stmtList",      "stmt",          "block",       
  "if_start",      "if_header",     "if_stmt",       "else_header", 
  "while_start",   "while_header",  "while_stmt",    "foreach_header",
  "foreach_stmt",  "continue_stmt",  "break_stmt",    "function_start",
  "function_header",  "fdef_chunk",    "return_stmt",   "caExpr",      
  "action",        "actions",       "actionStmt",    "chunk",       
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
 /*  15 */ "expr ::= MAPSTRING LPAREN STRING RPAREN",
 /*  16 */ "expr ::= UNIT LPAREN STRING RPAREN",
 /*  17 */ "expr ::= SWITCH LPAREN STRING RPAREN",
 /*  18 */ "expr ::= LOCATION LPAREN STRING RPAREN",
 /*  19 */ "expr ::= expr PLUS expr",
 /*  20 */ "expr ::= expr MINUS expr",
 /*  21 */ "expr ::= expr MULTIPLY expr",
 /*  22 */ "expr ::= expr DIVIDE expr",
 /*  23 */ "expr ::= expr MOD expr",
 /*  24 */ "expr ::= expr LSHIFT expr",
 /*  25 */ "expr ::= expr RSHIFT expr",
 /*  26 */ "expr ::= expr BITAND expr",
 /*  27 */ "expr ::= expr BITOR expr",
 /*  28 */ "expr ::= expr BITXOR expr",
 /*  29 */ "expr ::= PLUS expr",
 /*  30 */ "expr ::= MINUS expr",
 /*  31 */ "expr ::= BITNOT expr",
 /*  32 */ "lexpr ::= expr EQ expr",
 /*  33 */ "lexpr ::= expr NE expr",
 /*  34 */ "lexpr ::= expr LE expr",
 /*  35 */ "lexpr ::= expr LT expr",
 /*  36 */ "lexpr ::= expr GE expr",
 /*  37 */ "lexpr ::= expr GT expr",
 /*  38 */ "lexpr ::= lexpr LAND lexpr",
 /*  39 */ "lexpr ::= lexpr LOR lexpr",
 /*  40 */ "lexpr ::= LNOT lexpr",
 /*  41 */ "lexpr ::= LNOT LNOT lexpr",
 /*  42 */ "vdef_stmt ::= VAR NAME SEMICOLON",
 /*  43 */ "vdefAssign_stmt ::= VAR NAME ASSIGN expr SEMICOLON",
 /*  44 */ "vdefMulti_stmt ::= VAR nameList SEMICOLON",
 /*  45 */ "vdefMultiAssign_stmt ::= VAR nameList ASSIGN exprList SEMICOLON",
 /*  46 */ "assign_stmt ::= NAME ASSIGN expr SEMICOLON",
 /*  47 */ "assignMulti_stmt ::= nameList ASSIGN exprList SEMICOLON",
 /*  48 */ "stmtList ::= stmt",
 /*  49 */ "stmtList ::= stmtList stmt",
 /*  50 */ "block ::= LBRACKET stmtList RBRACKET",
 /*  51 */ "block ::= LBRACKET error RBRACKET",
 /*  52 */ "if_start ::= IF",
 /*  53 */ "if_header ::= if_start LPAREN lexpr RPAREN",
 /*  54 */ "if_stmt ::= if_header stmt",
 /*  55 */ "else_header ::= if_header stmt ELSE",
 /*  56 */ "if_stmt ::= else_header stmt",
 /*  57 */ "while_start ::= WHILE",
 /*  58 */ "while_header ::= while_start LPAREN lexpr RPAREN",
 /*  59 */ "while_stmt ::= while_header stmt",
 /*  60 */ "foreach_header ::= FOR LPAREN nameList COLON exprList RPAREN",
 /*  61 */ "foreach_stmt ::= foreach_header stmt",
 /*  62 */ "continue_stmt ::= CONTINUE SEMICOLON",
 /*  63 */ "break_stmt ::= BREAK SEMICOLON",
 /*  64 */ "function_start ::= FUNCTION NAME",
 /*  65 */ "function_header ::= function_start LPAREN nameList RPAREN",
 /*  66 */ "function_header ::= function_start LPAREN RPAREN",
 /*  67 */ "fdef_chunk ::= function_header stmt",
 /*  68 */ "return_stmt ::= RETURN SEMICOLON",
 /*  69 */ "return_stmt ::= RETURN exprList SEMICOLON",
 /*  70 */ "caExpr ::= expr",
 /*  71 */ "caExpr ::= STRING",
 /*  72 */ "caExpr ::= caExpr COMMA caExpr",
 /*  73 */ "lexpr ::= CONDITIONNAME LPAREN caExpr RPAREN",
 /*  74 */ "lexpr ::= CONDITIONNAME LPAREN RPAREN",
 /*  75 */ "action ::= ACTIONNAME LPAREN caExpr RPAREN SEMICOLON",
 /*  76 */ "actions ::= action action",
 /*  77 */ "actions ::= actions action",
 /*  78 */ "actionStmt ::= action",
 /*  79 */ "actionStmt ::= actions",
 /*  80 */ "stmt ::= error SEMICOLON",
 /*  81 */ "stmt ::= SEMICOLON",
 /*  82 */ "stmt ::= vdef_stmt",
 /*  83 */ "stmt ::= vdefAssign_stmt",
 /*  84 */ "stmt ::= vdefMultiAssign_stmt",
 /*  85 */ "stmt ::= vdefMulti_stmt",
 /*  86 */ "stmt ::= assign_stmt",
 /*  87 */ "stmt ::= assignMulti_stmt",
 /*  88 */ "stmt ::= expr SEMICOLON",
 /*  89 */ "stmt ::= actionStmt",
 /*  90 */ "stmt ::= if_stmt",
 /*  91 */ "stmt ::= while_stmt",
 /*  92 */ "stmt ::= foreach_stmt",
 /*  93 */ "stmt ::= continue_stmt",
 /*  94 */ "stmt ::= break_stmt",
 /*  95 */ "stmt ::= return_stmt",
 /*  96 */ "stmt ::= block",
 /*  97 */ "chunk ::= fdef_chunk",
 /*  98 */ "chunk ::= vdef_stmt",
 /*  99 */ "chunk ::= vdefMulti_stmt",
 /* 100 */ "chunks ::=",
 /* 101 */ "chunks ::= chunks chunk",
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
    case 54: /* nt */
{
#line 28 "parser/epparser.lemon"
 delete (yypminor->yy0); 
#line 647 "parser/epparser.c"
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
  { 55, 1 },
  { 57, 3 },
  { 57, 3 },
  { 58, 3 },
  { 58, 3 },
  { 59, 6 },
  { 61, 6 },
  { 59, 1 },
  { 59, 3 },
  { 61, 1 },
  { 61, 1 },
  { 60, 4 },
  { 60, 3 },
  { 61, 1 },
  { 61, 3 },
  { 61, 4 },
  { 61, 4 },
  { 61, 4 },
  { 61, 4 },
  { 61, 3 },
  { 61, 3 },
  { 61, 3 },
  { 61, 3 },
  { 61, 3 },
  { 61, 3 },
  { 61, 3 },
  { 61, 3 },
  { 61, 3 },
  { 61, 3 },
  { 61, 2 },
  { 61, 2 },
  { 61, 2 },
  { 62, 3 },
  { 62, 3 },
  { 62, 3 },
  { 62, 3 },
  { 62, 3 },
  { 62, 3 },
  { 62, 3 },
  { 62, 3 },
  { 62, 2 },
  { 62, 3 },
  { 63, 3 },
  { 64, 5 },
  { 65, 3 },
  { 66, 5 },
  { 67, 4 },
  { 68, 4 },
  { 69, 1 },
  { 69, 2 },
  { 71, 3 },
  { 71, 3 },
  { 72, 1 },
  { 73, 4 },
  { 74, 2 },
  { 75, 3 },
  { 74, 2 },
  { 76, 1 },
  { 77, 4 },
  { 78, 2 },
  { 79, 6 },
  { 80, 2 },
  { 81, 2 },
  { 82, 2 },
  { 83, 2 },
  { 84, 4 },
  { 84, 3 },
  { 85, 2 },
  { 86, 2 },
  { 86, 3 },
  { 87, 1 },
  { 87, 1 },
  { 87, 3 },
  { 62, 4 },
  { 62, 3 },
  { 88, 5 },
  { 89, 2 },
  { 89, 2 },
  { 90, 1 },
  { 90, 1 },
  { 70, 2 },
  { 70, 1 },
  { 70, 1 },
  { 70, 1 },
  { 70, 1 },
  { 70, 1 },
  { 70, 1 },
  { 70, 1 },
  { 70, 2 },
  { 70, 1 },
  { 70, 1 },
  { 70, 1 },
  { 70, 1 },
  { 70, 1 },
  { 70, 1 },
  { 70, 1 },
  { 70, 1 },
  { 91, 1 },
  { 91, 1 },
  { 91, 1 },
  { 56, 0 },
  { 56, 2 },
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
#line 1048 "parser/epparser.c"
        break;
      case 3: /* nameList ::= NAME COMMA NAME */
      case 4: /* nameList ::= nameList COMMA NAME */ yytestcase(yyruleno==4);
      case 8: /* exprList ::= exprList COMMA expr */ yytestcase(yyruleno==8);
#line 62 "parser/epparser.lemon"
{ yygotominor.yy0 = new Token((yymsp[-2].minor.yy0->data) + ", " + (yymsp[0].minor.yy0->data), yymsp[0].minor.yy0); delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1055 "parser/epparser.c"
        break;
      case 5: /* exprList ::= funcexpr LSQBRACKET LSQBRACKET numList RSQBRACKET RSQBRACKET */
      case 6: /* expr ::= funcexpr LSQBRACKET LSQBRACKET NUMBER RSQBRACKET RSQBRACKET */ yytestcase(yyruleno==6);
#line 64 "parser/epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[-2].minor.yy0);
    (*pGen) << yygotominor.yy0->data << " = _SRET(" << yymsp[-5].minor.yy0->data << ", [" << yymsp[-2].minor.yy0->data << "])" << std::endl;
    delete yymsp[-5].minor.yy0; delete yymsp[-2].minor.yy0;
}
#line 1065 "parser/epparser.c"
        break;
      case 7: /* exprList ::= expr */
      case 9: /* expr ::= NUMBER */ yytestcase(yyruleno==9);
      case 13: /* expr ::= funcexpr */ yytestcase(yyruleno==13);
      case 41: /* lexpr ::= LNOT LNOT lexpr */ yytestcase(yyruleno==41);
      case 70: /* caExpr ::= expr */ yytestcase(yyruleno==70);
      case 71: /* caExpr ::= STRING */ yytestcase(yyruleno==71);
#line 75 "parser/epparser.lemon"
{ yygotominor.yy0 = yymsp[0].minor.yy0; }
#line 1075 "parser/epparser.c"
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
#line 1086 "parser/epparser.c"
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
#line 1106 "parser/epparser.c"
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
#line 1127 "parser/epparser.c"
        break;
      case 14: /* expr ::= LPAREN expr RPAREN */
#line 128 "parser/epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0, *pGen);
}
#line 1135 "parser/epparser.c"
        break;
      case 15: /* expr ::= MAPSTRING LPAREN STRING RPAREN */
#line 133 "parser/epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "EncodeString(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0, *pGen);
}
#line 1143 "parser/epparser.c"
        break;
      case 16: /* expr ::= UNIT LPAREN STRING RPAREN */
#line 138 "parser/epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "EncodeUnit(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0, *pGen);
}
#line 1151 "parser/epparser.c"
        break;
      case 17: /* expr ::= SWITCH LPAREN STRING RPAREN */
#line 143 "parser/epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "EncodeSwitch(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0, *pGen);
}
#line 1159 "parser/epparser.c"
        break;
      case 18: /* expr ::= LOCATION LPAREN STRING RPAREN */
#line 148 "parser/epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "EncodeLocation(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0, *pGen);
}
#line 1167 "parser/epparser.c"
        break;
      case 19: /* expr ::= expr PLUS expr */
#line 153 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "+",  yymsp[0].minor.yy0, *pGen); }
#line 1172 "parser/epparser.c"
        break;
      case 20: /* expr ::= expr MINUS expr */
#line 154 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "-",  yymsp[0].minor.yy0, *pGen); }
#line 1177 "parser/epparser.c"
        break;
      case 21: /* expr ::= expr MULTIPLY expr */
#line 155 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "*",  yymsp[0].minor.yy0, *pGen); }
#line 1182 "parser/epparser.c"
        break;
      case 22: /* expr ::= expr DIVIDE expr */
#line 156 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "//", yymsp[0].minor.yy0, *pGen); }
#line 1187 "parser/epparser.c"
        break;
      case 23: /* expr ::= expr MOD expr */
#line 157 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "%",  yymsp[0].minor.yy0, *pGen); }
#line 1192 "parser/epparser.c"
        break;
      case 24: /* expr ::= expr LSHIFT expr */
#line 158 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<<", yymsp[0].minor.yy0, *pGen); }
#line 1197 "parser/epparser.c"
        break;
      case 25: /* expr ::= expr RSHIFT expr */
#line 159 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">>", yymsp[0].minor.yy0, *pGen); }
#line 1202 "parser/epparser.c"
        break;
      case 26: /* expr ::= expr BITAND expr */
#line 160 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "&",  yymsp[0].minor.yy0, *pGen); }
#line 1207 "parser/epparser.c"
        break;
      case 27: /* expr ::= expr BITOR expr */
#line 161 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "|",  yymsp[0].minor.yy0, *pGen); }
#line 1212 "parser/epparser.c"
        break;
      case 28: /* expr ::= expr BITXOR expr */
#line 162 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "^",  yymsp[0].minor.yy0, *pGen); }
#line 1217 "parser/epparser.c"
        break;
      case 29: /* expr ::= PLUS expr */
#line 165 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = +" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1222 "parser/epparser.c"
        break;
      case 30: /* expr ::= MINUS expr */
#line 166 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = -" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1227 "parser/epparser.c"
        break;
      case 31: /* expr ::= BITNOT expr */
#line 167 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = ~" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1232 "parser/epparser.c"
        break;
      case 32: /* lexpr ::= expr EQ expr */
#line 170 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "==", yymsp[0].minor.yy0, *pGen); }
#line 1237 "parser/epparser.c"
        break;
      case 33: /* lexpr ::= expr NE expr */
#line 171 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "!=", yymsp[0].minor.yy0, *pGen); }
#line 1242 "parser/epparser.c"
        break;
      case 34: /* lexpr ::= expr LE expr */
#line 172 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<=", yymsp[0].minor.yy0, *pGen); }
#line 1247 "parser/epparser.c"
        break;
      case 35: /* lexpr ::= expr LT expr */
#line 173 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<",  yymsp[0].minor.yy0, *pGen); }
#line 1252 "parser/epparser.c"
        break;
      case 36: /* lexpr ::= expr GE expr */
#line 174 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">=", yymsp[0].minor.yy0, *pGen); }
#line 1257 "parser/epparser.c"
        break;
      case 37: /* lexpr ::= expr GT expr */
#line 175 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">" , yymsp[0].minor.yy0, *pGen); }
#line 1262 "parser/epparser.c"
        break;
      case 38: /* lexpr ::= lexpr LAND lexpr */
#line 177 "parser/epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "[" + yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data + "]";
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0, *pGen);
}
#line 1271 "parser/epparser.c"
        break;
      case 39: /* lexpr ::= lexpr LOR lexpr */
#line 183 "parser/epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "EUDOr([" + yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data + "])";
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0, *pGen);
}
#line 1280 "parser/epparser.c"
        break;
      case 40: /* lexpr ::= LNOT lexpr */
#line 189 "parser/epparser.lemon"
{
    yymsp[0].minor.yy0->data = "EUDNot([" + yymsp[0].minor.yy0->data + "])";
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0, *pGen);
}
#line 1288 "parser/epparser.c"
        break;
      case 42: /* vdef_stmt ::= VAR NAME SEMICOLON */
#line 199 "parser/epparser.lemon"
{
    (*pGen) << yymsp[-1].minor.yy0->data << " = EUDVariable()" << std::endl;
    pGen->namedef(yymsp[-1].minor.yy0->data);
    delete yymsp[-1].minor.yy0;
}
#line 1297 "parser/epparser.c"
        break;
      case 43: /* vdefAssign_stmt ::= VAR NAME ASSIGN expr SEMICOLON */
#line 205 "parser/epparser.lemon"
{
    (*pGen) << yymsp[-3].minor.yy0->data << " = _MVAR([" << yymsp[-1].minor.yy0->data << "])" << std::endl;
    if(!pGen->namedef(yymsp[-3].minor.yy0->data)) {
        throw_error(yymsp[-3].minor.yy0->line, 196, ("Redeclaration of variable \'" + (yymsp[-3].minor.yy0->data) + "\'"));
    }
    delete yymsp[-3].minor.yy0;
}
#line 1308 "parser/epparser.c"
        break;
      case 44: /* vdefMulti_stmt ::= VAR nameList SEMICOLON */
#line 213 "parser/epparser.lemon"
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
#line 1325 "parser/epparser.c"
        break;
      case 45: /* vdefMultiAssign_stmt ::= VAR nameList ASSIGN exprList SEMICOLON */
#line 227 "parser/epparser.lemon"
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
#line 1342 "parser/epparser.c"
        break;
      case 46: /* assign_stmt ::= NAME ASSIGN expr SEMICOLON */
#line 241 "parser/epparser.lemon"
{
    (*pGen) << yymsp[-3].minor.yy0->data << " << " << yymsp[-1].minor.yy0->data << std::endl;
    if(pGen->undefined(yymsp[-3].minor.yy0->data)) {
        throw_error(yymsp[-3].minor.yy0->line, 103, ("Undeclared variable \'" + (yymsp[-3].minor.yy0->data) + "\'"));
        pGen->namedef(yymsp[-3].minor.yy0->data);
    }
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1354 "parser/epparser.c"
        break;
      case 47: /* assignMulti_stmt ::= nameList ASSIGN exprList SEMICOLON */
#line 250 "parser/epparser.lemon"
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
#line 1370 "parser/epparser.c"
        break;
      case 51: /* block ::= LBRACKET error RBRACKET */
#line 267 "parser/epparser.lemon"
{
    throw_error(yymsp[0].minor.yy0->line, 6298, "Block not terminated properly.");
}
#line 1377 "parser/epparser.c"
        break;
      case 52: /* if_start ::= IF */
#line 273 "parser/epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    (*pGen) << yygotominor.yy0->data << " = EUDIf()" << std::endl;
}
#line 1385 "parser/epparser.c"
        break;
      case 53: /* if_header ::= if_start LPAREN lexpr RPAREN */
      case 58: /* while_header ::= while_start LPAREN lexpr RPAREN */ yytestcase(yyruleno==58);
#line 277 "parser/epparser.lemon"
{
    (*pGen) << "if " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data << "):" << std::endl;
    pGen->indent();
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1395 "parser/epparser.c"
        break;
      case 54: /* if_stmt ::= if_header stmt */
      case 56: /* if_stmt ::= else_header stmt */ yytestcase(yyruleno==56);
      case 59: /* while_stmt ::= while_header stmt */ yytestcase(yyruleno==59);
#line 283 "parser/epparser.lemon"
{
    pGen->unindent();
    (*pGen) << "EUDEndIf()" << std::endl;
}
#line 1405 "parser/epparser.c"
        break;
      case 55: /* else_header ::= if_header stmt ELSE */
#line 288 "parser/epparser.lemon"
{
    pGen->unindent();
    (*pGen) << "if EUDElse():" << std::endl;
    pGen->indent();
}
#line 1414 "parser/epparser.c"
        break;
      case 57: /* while_start ::= WHILE */
#line 301 "parser/epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    (*pGen) << yygotominor.yy0->data << " = EUDWhile()" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1423 "parser/epparser.c"
        break;
      case 60: /* foreach_header ::= FOR LPAREN nameList COLON exprList RPAREN */
#line 319 "parser/epparser.lemon"
{
    (*pGen) << "for " << yymsp[-3].minor.yy0->data << " in " << yymsp[-1].minor.yy0->data << ":" << std::endl;
    pGen->indent();
}
#line 1431 "parser/epparser.c"
        break;
      case 61: /* foreach_stmt ::= foreach_header stmt */
      case 67: /* fdef_chunk ::= function_header stmt */ yytestcase(yyruleno==67);
#line 324 "parser/epparser.lemon"
{
    pGen->unindent();
}
#line 1439 "parser/epparser.c"
        break;
      case 62: /* continue_stmt ::= CONTINUE SEMICOLON */
#line 330 "parser/epparser.lemon"
{
    (*pGen) << "EUDContinue()" << std::endl;
}
#line 1446 "parser/epparser.c"
        break;
      case 63: /* break_stmt ::= BREAK SEMICOLON */
#line 334 "parser/epparser.lemon"
{
    (*pGen) << "EUDBreak()" << std::endl;
}
#line 1453 "parser/epparser.c"
        break;
      case 64: /* function_start ::= FUNCTION NAME */
#line 339 "parser/epparser.lemon"
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
#line 1469 "parser/epparser.c"
        break;
      case 65: /* function_header ::= function_start LPAREN nameList RPAREN */
#line 352 "parser/epparser.lemon"
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
#line 1489 "parser/epparser.c"
        break;
      case 66: /* function_header ::= function_start LPAREN RPAREN */
#line 369 "parser/epparser.lemon"
{
    (*pGen) << "@EUDFunc" << std::endl;
    (*pGen) << "def " << yymsp[-2].minor.yy0->data << "():" << std::endl;
    pGen->indent();
    tmpIndex = 1;
    delete yymsp[-2].minor.yy0;
}
#line 1500 "parser/epparser.c"
        break;
      case 68: /* return_stmt ::= RETURN SEMICOLON */
#line 383 "parser/epparser.lemon"
{
    (*pGen) << "EUDReturn()" << std::endl;
}
#line 1507 "parser/epparser.c"
        break;
      case 69: /* return_stmt ::= RETURN exprList SEMICOLON */
#line 386 "parser/epparser.lemon"
{
    (*pGen) << "EUDReturn(" << yymsp[-1].minor.yy0->data << ")" << std::endl;
    delete yymsp[-1].minor.yy0;
}
#line 1515 "parser/epparser.c"
        break;
      case 72: /* caExpr ::= caExpr COMMA caExpr */
#line 396 "parser/epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data;
    yymsp[-2].minor.yy0->type = TOKEN_TEMP;
    yygotominor.yy0 = yymsp[-2].minor.yy0;
}
#line 1524 "parser/epparser.c"
        break;
      case 73: /* lexpr ::= CONDITIONNAME LPAREN caExpr RPAREN */
#line 403 "parser/epparser.lemon"
{
    yymsp[-3].minor.yy0->data = yymsp[-3].minor.yy0->data + "(" + yymsp[-1].minor.yy0->data + ")";
    delete yymsp[-1].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0, *pGen);
}
#line 1533 "parser/epparser.c"
        break;
      case 74: /* lexpr ::= CONDITIONNAME LPAREN RPAREN */
#line 409 "parser/epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + "()";
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0, *pGen);
}
#line 1541 "parser/epparser.c"
        break;
      case 75: /* action ::= ACTIONNAME LPAREN caExpr RPAREN SEMICOLON */
#line 414 "parser/epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[-4].minor.yy0);
    yygotominor.yy0->data =  yymsp[-4].minor.yy0->data + "(" + yymsp[-2].minor.yy0->data + ")";
    delete yymsp[-4].minor.yy0; delete yymsp[-2].minor.yy0;
}
#line 1550 "parser/epparser.c"
        break;
      case 76: /* actions ::= action action */
      case 77: /* actions ::= actions action */ yytestcase(yyruleno==77);
#line 420 "parser/epparser.lemon"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
    yymsp[-1].minor.yy0->data += ",\n" + yymsp[0].minor.yy0->data;
    delete yymsp[0].minor.yy0;
}
#line 1560 "parser/epparser.c"
        break;
      case 78: /* actionStmt ::= action */
#line 432 "parser/epparser.lemon"
{
    (*pGen) << "DoEvents(" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1568 "parser/epparser.c"
        break;
      case 79: /* actionStmt ::= actions */
#line 437 "parser/epparser.lemon"
{
    (*pGen) << "DoEvents([" << std::endl;
    pGen->indent();
    (*pGen) << yymsp[0].minor.yy0->data << std::endl;
    pGen->unindent(false);
    (*pGen) << "])" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1580 "parser/epparser.c"
        break;
      case 80: /* stmt ::= error SEMICOLON */
#line 448 "parser/epparser.lemon"
{ throw_error(yymsp[0].minor.yy0->line, 6974, "Error while parsing statement"); }
#line 1585 "parser/epparser.c"
        break;
      case 88: /* stmt ::= expr SEMICOLON */
#line 458 "parser/epparser.lemon"
{ (*pGen) << yymsp[-1].minor.yy0->data << std::endl; }
#line 1590 "parser/epparser.c"
        break;
      default:
      /* (0) program ::= chunks */ yytestcase(yyruleno==0);
      /* (48) stmtList ::= stmt */ yytestcase(yyruleno==48);
      /* (49) stmtList ::= stmtList stmt */ yytestcase(yyruleno==49);
      /* (50) block ::= LBRACKET stmtList RBRACKET */ yytestcase(yyruleno==50);
      /* (81) stmt ::= SEMICOLON */ yytestcase(yyruleno==81);
      /* (82) stmt ::= vdef_stmt */ yytestcase(yyruleno==82);
      /* (83) stmt ::= vdefAssign_stmt */ yytestcase(yyruleno==83);
      /* (84) stmt ::= vdefMultiAssign_stmt */ yytestcase(yyruleno==84);
      /* (85) stmt ::= vdefMulti_stmt */ yytestcase(yyruleno==85);
      /* (86) stmt ::= assign_stmt */ yytestcase(yyruleno==86);
      /* (87) stmt ::= assignMulti_stmt */ yytestcase(yyruleno==87);
      /* (89) stmt ::= actionStmt */ yytestcase(yyruleno==89);
      /* (90) stmt ::= if_stmt */ yytestcase(yyruleno==90);
      /* (91) stmt ::= while_stmt */ yytestcase(yyruleno==91);
      /* (92) stmt ::= foreach_stmt */ yytestcase(yyruleno==92);
      /* (93) stmt ::= continue_stmt */ yytestcase(yyruleno==93);
      /* (94) stmt ::= break_stmt */ yytestcase(yyruleno==94);
      /* (95) stmt ::= return_stmt */ yytestcase(yyruleno==95);
      /* (96) stmt ::= block */ yytestcase(yyruleno==96);
      /* (97) chunk ::= fdef_chunk */ yytestcase(yyruleno==97);
      /* (98) chunk ::= vdef_stmt */ yytestcase(yyruleno==98);
      /* (99) chunk ::= vdefMulti_stmt */ yytestcase(yyruleno==99);
      /* (100) chunks ::= */ yytestcase(yyruleno==100);
      /* (101) chunks ::= chunks chunk */ yytestcase(yyruleno==101);
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
#line 1665 "parser/epparser.c"
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
#line 1684 "parser/epparser.c"
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
#line 476 "parser/epparser.lemon"


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
#line 1920 "parser/epparser.c"
