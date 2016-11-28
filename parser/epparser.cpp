/* Driver template for the LEMON parser generator.
** The author disclaims copyright to this source code.
*/
/* First off, code is included that follows the "include" declaration
** in the input grammar file. */
#include <stdio.h>
#line 1 "parser\\epparser.lemon"

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
#line 21 "parser\\epparser.c"
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
#define YYNOCODE 96
#define YYACTIONTYPE unsigned short int
#define ParseTOKENTYPE Token*
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  int yy191;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL  PyGenerator* pGen ;
#define ParseARG_PDECL , PyGenerator* pGen 
#define ParseARG_FETCH  PyGenerator* pGen  = yypParser->pGen 
#define ParseARG_STORE yypParser->pGen  = pGen 
#define YYNSTATE 217
#define YYNRULE 105
#define YYERRORSYMBOL 55
#define YYERRSYMDT yy191
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
#define YY_ACTTAB_COUNT (587)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */    79,  137,  137,   30,  161,   87,  144,   98,  126,   76,
 /*    10 */   159,  158,  156,  157,  155,  154,    2,  187,  145,  109,
 /*    20 */     6,  151,    5,  105,    4,  150,    3,  149,  148,  147,
 /*    30 */    19,  136,   22,  146,   99,   49,   48,  152,  215,   87,
 /*    40 */   136,   98,  216,  136,  159,  158,  156,  157,  155,  154,
 /*    50 */   214,  143,  145,  109,    6,  151,    5,  105,    4,  150,
 /*    60 */     3,  149,  148,  147,   86,  132,   66,  146,   99,   49,
 /*    70 */    48,  152,  211,   87,  212,   98,  137,  213,  159,  158,
 /*    80 */   156,  157,  155,  154,  130,  106,  145,  109,    6,  151,
 /*    90 */     5,  105,    4,  150,    3,  149,  148,  147,   85,  132,
 /*   100 */    66,  146,   99,   49,   48,  152,  133,   87,   46,   98,
 /*   110 */   210,  129,  159,  158,  156,  157,  155,  154,  128,  174,
 /*   120 */   145,  109,    6,  151,    5,  105,    4,  150,    3,  149,
 /*   130 */   148,  147,   82,  132,   66,  146,   99,   49,   48,  152,
 /*   140 */   131,   87,  208,   98,  209,  127,  159,  158,  156,  157,
 /*   150 */   155,  154,   52,  171,  145,  109,    6,  151,    5,  105,
 /*   160 */     4,  150,    3,  149,  148,  147,   88,  132,   66,  146,
 /*   170 */    99,   49,   48,  152,  206,   87,  207,   98,  123,   31,
 /*   180 */   159,  158,  156,  157,  155,  154,  125,  169,  145,  109,
 /*   190 */     6,  151,    5,  105,    4,  150,    3,  149,  148,  147,
 /*   200 */   124,  137,   29,  146,   99,   49,   48,  152,  193,   87,
 /*   210 */   129,   98,  126,   57,  159,  158,  156,  157,  155,  154,
 /*   220 */    19,  186,  145,  109,    6,  151,    5,  105,    4,  150,
 /*   230 */     3,  149,  148,  147,  120,  136,   21,  146,  215,   49,
 /*   240 */    48,  152,   41,   42,   40,   28,   26,   25,   24,   23,
 /*   250 */    27,   36,   35,   37,   39,   38,   45,   43,   41,   42,
 /*   260 */    40,   12,   36,   35,   37,   39,   38,   45,   43,   41,
 /*   270 */    42,   40,  213,  119,   34,   33,   81,  132,   66,  204,
 /*   280 */    32,  205,  122,  136,  203,   44,  126,   58,  121,   18,
 /*   290 */   118,  115,  112,  126,   54,   73,   11,   35,   37,   39,
 /*   300 */    38,   45,   43,   41,   42,   40,  117,  107,  116,   34,
 /*   310 */    33,   13,   14,  179,  202,   32,  205,  122,  178,  114,
 /*   320 */    44,   13,   14,  121,  201,  118,  115,  112,   20,   34,
 /*   330 */    33,  126,   54,  183,  113,   32,  205,  122,  176,  111,
 /*   340 */    44,  177,  107,  121,  180,  118,  115,  112,  172,  110,
 /*   350 */    78,   36,   35,   37,   39,   38,   45,   43,   41,   42,
 /*   360 */    40,   51,  160,    1,  185,  184,   31,  200,  173,  104,
 /*   370 */    31,  103,  102,   15,   17,   14,  101,   36,   35,   37,
 /*   380 */    39,   38,   45,   43,   41,   42,   40,   10,   36,   35,
 /*   390 */    37,   39,   38,   45,   43,   41,   42,   40,   34,   33,
 /*   400 */   168,   31,  191,  190,   32,  205,  122,  188,   31,   44,
 /*   410 */   192,  175,  121,  189,  118,  115,  112,   34,   33,  126,
 /*   420 */    58,  126,   58,   32,  205,  122,    9,  167,   44,  164,
 /*   430 */   170,  121,  180,  118,  115,  112,   34,   33,   18,  126,
 /*   440 */    54,  108,   32,  205,  122,  166,   80,   44,   84,   50,
 /*   450 */   121,   78,  118,  115,  112,   16,  165,  126,   54,  182,
 /*   460 */   126,   77,   51,  160,    1,  161,  184,  100,  153,  173,
 /*   470 */   104,   96,  103,  102,   92,   17,   47,  101,  126,   54,
 /*   480 */   181,   34,   33,  126,   54,   72,   93,   32,  205,  122,
 /*   490 */   323,    8,   44,  217,   90,  121,   74,  118,  115,  112,
 /*   500 */   140,   89,  139,   37,   39,   38,   45,   43,   41,   42,
 /*   510 */    40,   83,   39,   38,   45,   43,   41,   42,   40,  136,
 /*   520 */   134,    7,  141,   45,   43,   41,   42,   40,  142,  138,
 /*   530 */    53,  163,  126,  199,  101,  126,  198,   75,  126,  197,
 /*   540 */   126,   71,  135,  126,   70,  162,   97,  126,   69,  324,
 /*   550 */   133,  126,   67,   95,  324,   94,  126,   68,  324,   91,
 /*   560 */   126,  196,  126,  195,  324,  126,  194,  324,  126,   65,
 /*   570 */   126,   56,  126,   55,  324,  126,   64,  126,   63,  126,
 /*   580 */    62,  126,   61,  126,   60,  126,   59,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    55,    1,    1,    2,   38,   60,   40,   62,   62,   63,
 /*    10 */    65,   66,   67,   68,   69,   70,   71,   72,   73,   74,
 /*    20 */    75,   76,   77,   78,   79,   80,   81,   82,   83,   84,
 /*    30 */    29,    1,    2,   88,   55,   90,   91,   92,   38,   60,
 /*    40 */     1,   62,   26,    1,   65,   66,   67,   68,   69,   70,
 /*    50 */    26,   72,   73,   74,   75,   76,   77,   78,   79,   80,
 /*    60 */    81,   82,   83,   84,   61,   62,   63,   88,   55,   90,
 /*    70 */    91,   92,   30,   60,   26,   62,    1,   38,   65,   66,
 /*    80 */    67,   68,   69,   70,    1,   72,   73,   74,   75,   76,
 /*    90 */    77,   78,   79,   80,   81,   82,   83,   84,   61,   62,
 /*   100 */    63,   88,   55,   90,   91,   92,   26,   60,   29,   62,
 /*   110 */    30,   28,   65,   66,   67,   68,   69,   70,    1,   72,
 /*   120 */    73,   74,   75,   76,   77,   78,   79,   80,   81,   82,
 /*   130 */    83,   84,   61,   62,   63,   88,   55,   90,   91,   92,
 /*   140 */    27,   60,   28,   62,   25,   28,   65,   66,   67,   68,
 /*   150 */    69,   70,   27,   72,   73,   74,   75,   76,   77,   78,
 /*   160 */    79,   80,   81,   82,   83,   84,   61,   62,   63,   88,
 /*   170 */    55,   90,   91,   92,   28,   60,   25,   62,   25,    1,
 /*   180 */    65,   66,   67,   68,   69,   70,   27,   72,   73,   74,
 /*   190 */    75,   76,   77,   78,   79,   80,   81,   82,   83,   84,
 /*   200 */    27,    1,    2,   88,   55,   90,   91,   92,   30,   60,
 /*   210 */    28,   62,   62,   63,   65,   66,   67,   68,   69,   70,
 /*   220 */    29,   72,   73,   74,   75,   76,   77,   78,   79,   80,
 /*   230 */    81,   82,   83,   84,   29,    1,    2,   88,   38,   90,
 /*   240 */    91,   92,   20,   21,   22,    7,    8,    9,   10,   11,
 /*   250 */    12,   13,   14,   15,   16,   17,   18,   19,   20,   21,
 /*   260 */    22,    5,   13,   14,   15,   16,   17,   18,   19,   20,
 /*   270 */    21,   22,   38,   33,   18,   19,   61,   62,   63,   30,
 /*   280 */    24,   25,   26,    1,   30,   29,   62,   63,   32,    1,
 /*   290 */    34,   35,   36,   62,   63,   64,    5,   14,   15,   16,
 /*   300 */    17,   18,   19,   20,   21,   22,   29,   51,   33,   18,
 /*   310 */    19,    3,    4,   89,   30,   24,   25,   26,   30,   29,
 /*   320 */    29,    3,    4,   32,   30,   34,   35,   36,   46,   18,
 /*   330 */    19,   62,   63,   64,   33,   24,   25,   26,   30,   29,
 /*   340 */    29,   30,   51,   32,   33,   34,   35,   36,   30,   33,
 /*   350 */    26,   13,   14,   15,   16,   17,   18,   19,   20,   21,
 /*   360 */    22,   37,   38,   39,   40,   41,    1,   30,   44,   45,
 /*   370 */     1,   47,   48,   29,   50,    4,   52,   13,   14,   15,
 /*   380 */    16,   17,   18,   19,   20,   21,   22,   29,   13,   14,
 /*   390 */    15,   16,   17,   18,   19,   20,   21,   22,   18,   19,
 /*   400 */    38,    1,   38,   38,   24,   25,   26,   38,    1,   29,
 /*   410 */    30,   43,   32,   38,   34,   35,   36,   18,   19,   62,
 /*   420 */    63,   62,   63,   24,   25,   26,   29,   38,   29,   38,
 /*   430 */    30,   32,   33,   34,   35,   36,   18,   19,    1,   62,
 /*   440 */    63,   64,   24,   25,   26,   38,   89,   29,   89,   29,
 /*   450 */    32,   26,   34,   35,   36,   29,   38,   62,   63,   64,
 /*   460 */    62,   63,   37,   38,   39,   38,   41,   30,   38,   44,
 /*   470 */    45,   26,   47,   48,   60,   50,   54,   52,   62,   63,
 /*   480 */    64,   18,   19,   62,   63,   64,   26,   24,   25,   26,
 /*   490 */    57,   58,   29,    0,   25,   32,   60,   34,   35,   36,
 /*   500 */    65,   59,   67,   15,   16,   17,   18,   19,   20,   21,
 /*   510 */    22,   60,   16,   17,   18,   19,   20,   21,   22,    1,
 /*   520 */    85,   86,   87,   18,   19,   20,   21,   22,   93,   94,
 /*   530 */    37,   90,   62,   63,   52,   62,   63,   26,   62,   63,
 /*   540 */    62,   63,   49,   62,   63,   90,   53,   62,   63,   95,
 /*   550 */    26,   62,   63,   26,   95,   60,   62,   63,   95,   60,
 /*   560 */    62,   63,   62,   63,   95,   62,   63,   95,   62,   63,
 /*   570 */    62,   63,   62,   63,   95,   62,   63,   62,   63,   62,
 /*   580 */    63,   62,   63,   62,   63,   62,   63,
};
#define YY_SHIFT_USE_DFLT (-35)
#define YY_SHIFT_COUNT (137)
#define YY_SHIFT_MIN   (-34)
#define YY_SHIFT_MAX   (527)
static const short yy_shift_ofst[] = {
 /*     0 */   -35,  425,  324,  425,  425,  425,  425,  425,  493,  256,
 /*    10 */   311,  291,  291,  256,  256,  256,  399,  418,  399,  380,
 /*    20 */   463,  463,  463,  463,  463,  463,  463,  463,  463,  463,
 /*    30 */   463,  463,  463,  463,  463,  463,  463,  463,  463,  463,
 /*    40 */   463,  463,  463,  463,  463,  463,   80,  527,  482,  482,
 /*    50 */   524,  511,  469,  460,  238,  375,  364,  249,  338,  338,
 /*    60 */   338,  338,  338,  338,  338,  338,  338,  283,  488,  496,
 /*    70 */   505,  505,  318,  308,  234,  200,  222,  222,    1,  -34,
 /*    80 */   437,  407,  400,  282,  288,  369,  365,   30,  178,  117,
 /*    90 */    83,   42,   39,    0,  518,   75,  422,  445,  430,  427,
 /*   100 */   391,  426,  389,  362,  420,  397,  368,  358,  371,  344,
 /*   110 */   337,  316,  310,  294,  301,  290,  284,  275,  277,  254,
 /*   120 */   240,  205,  191,  182,  153,  173,  159,  146,  151,  114,
 /*   130 */   119,  125,  113,   75,   79,   48,   24,   16,
};
#define YY_REDUCE_USE_DFLT (-56)
#define YY_REDUCE_COUNT (53)
#define YY_REDUCE_MIN   (-55)
#define YY_REDUCE_MAX   (523)
static const short yy_reduce_ofst[] = {
 /*     0 */   433,  -55,  149,  115,   81,   47,   13,  -21,  435,  421,
 /*    10 */   359,  416,  395,  377,  269,  231,  357,  215,  224,  105,
 /*    20 */    71,   37,    3,  523,  521,  519,  517,  515,  513,  510,
 /*    30 */   508,  506,  503,  500,  498,  494,  489,  485,  481,  478,
 /*    40 */   476,  473,  470,  398,  150,  -54,  499,  495,  455,  441,
 /*    50 */   451,  436,  442,  414,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   320,  322,  322,  322,  322,  322,  322,  322,  322,  322,
 /*    10 */   322,  322,  322,  322,  322,  322,  322,  322,  322,  322,
 /*    20 */   322,  322,  322,  322,  322,  322,  322,  322,  322,  322,
 /*    30 */   322,  322,  322,  322,  322,  322,  322,  322,  322,  322,
 /*    40 */   322,  322,  322,  322,  322,  322,  322,  322,  296,  295,
 /*    50 */   322,  322,  322,  322,  322,  322,  322,  322,  287,  254,
 /*    60 */   253,  252,  251,  250,  249,  225,  224,  244,  245,  243,
 /*    70 */   242,  241,  322,  322,  322,  322,  236,  237,  322,  322,
 /*    80 */   322,  322,  322,  322,  322,  322,  322,  322,  322,  322,
 /*    90 */   322,  322,  322,  322,  314,  315,  322,  322,  322,  322,
 /*   100 */   322,  322,  322,  322,  322,  322,  271,  322,  256,  322,
 /*   110 */   322,  322,  322,  322,  322,  322,  322,  322,  322,  322,
 /*   120 */   322,  322,  227,  322,  322,  322,  230,  322,  322,  322,
 /*   130 */   322,  322,  230,  322,  322,  322,  322,  322,  321,  319,
 /*   140 */   318,  317,  316,  284,  268,  313,  312,  311,  310,  309,
 /*   150 */   308,  307,  306,  305,  304,  303,  302,  301,  300,  299,
 /*   160 */   298,  297,  294,  293,  292,  285,  286,  280,  279,  278,
 /*   170 */   277,  276,  275,  274,  273,  272,  270,  291,  290,  289,
 /*   180 */   288,  258,  257,  255,  269,  267,  266,  265,  262,  260,
 /*   190 */   264,  263,  229,  228,  248,  247,  246,  240,  239,  238,
 /*   200 */   235,  234,  233,  232,  231,  226,  222,  219,  223,  218,
 /*   210 */   283,  282,  281,  261,  221,  259,  220,
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
  "ACTIONNAME",    "FROM",          "IMPORT",        "error",       
  "nt",            "program",       "chunks",        "numList",     
  "nameList",      "exprList",      "funcexpr",      "expr",        
  "lexpr",         "vdef_stmt",     "vdefAssign_stmt",  "vdefMulti_stmt",
  "vdefMultiAssign_stmt",  "assign_stmt",   "assignMulti_stmt",  "stmtList",    
  "stmt",          "block",         "if_start",      "if_header",   
  "if_stmt",       "else_header",   "while_start",   "while_header",
  "while_stmt",    "foreach_header",  "foreach_stmt",  "continue_stmt",
  "break_stmt",    "function_start",  "function_header",  "fdef_chunk",  
  "return_stmt",   "caExpr",        "action",        "actions",     
  "actionStmt",    "import_chunk",  "chunk",       
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
 /*  88 */ "stmt ::= funcexpr SEMICOLON",
 /*  89 */ "stmt ::= actionStmt",
 /*  90 */ "stmt ::= if_stmt",
 /*  91 */ "stmt ::= while_stmt",
 /*  92 */ "stmt ::= foreach_stmt",
 /*  93 */ "stmt ::= continue_stmt",
 /*  94 */ "stmt ::= break_stmt",
 /*  95 */ "stmt ::= return_stmt",
 /*  96 */ "stmt ::= block",
 /*  97 */ "import_chunk ::= FROM NAME IMPORT nameList",
 /*  98 */ "import_chunk ::= FROM NAME IMPORT NAME",
 /*  99 */ "chunk ::= import_chunk",
 /* 100 */ "chunk ::= fdef_chunk",
 /* 101 */ "chunk ::= vdef_stmt",
 /* 102 */ "chunk ::= vdefMulti_stmt",
 /* 103 */ "chunks ::=",
 /* 104 */ "chunks ::= chunks chunk",
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
    case 56: /* nt */
{
#line 27 "parser\\epparser.lemon"
 delete (yypminor->yy0); 
#line 647 "parser\\epparser.c"
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
  { 57, 1 },
  { 59, 3 },
  { 59, 3 },
  { 60, 3 },
  { 60, 3 },
  { 61, 6 },
  { 63, 6 },
  { 61, 1 },
  { 61, 3 },
  { 63, 1 },
  { 63, 1 },
  { 62, 4 },
  { 62, 3 },
  { 63, 1 },
  { 63, 3 },
  { 63, 4 },
  { 63, 4 },
  { 63, 4 },
  { 63, 4 },
  { 63, 3 },
  { 63, 3 },
  { 63, 3 },
  { 63, 3 },
  { 63, 3 },
  { 63, 3 },
  { 63, 3 },
  { 63, 3 },
  { 63, 3 },
  { 63, 3 },
  { 63, 2 },
  { 63, 2 },
  { 63, 2 },
  { 64, 3 },
  { 64, 3 },
  { 64, 3 },
  { 64, 3 },
  { 64, 3 },
  { 64, 3 },
  { 64, 3 },
  { 64, 3 },
  { 64, 2 },
  { 64, 3 },
  { 65, 3 },
  { 66, 5 },
  { 67, 3 },
  { 68, 5 },
  { 69, 4 },
  { 70, 4 },
  { 71, 1 },
  { 71, 2 },
  { 73, 3 },
  { 73, 3 },
  { 74, 1 },
  { 75, 4 },
  { 76, 2 },
  { 77, 3 },
  { 76, 2 },
  { 78, 1 },
  { 79, 4 },
  { 80, 2 },
  { 81, 6 },
  { 82, 2 },
  { 83, 2 },
  { 84, 2 },
  { 85, 2 },
  { 86, 4 },
  { 86, 3 },
  { 87, 2 },
  { 88, 2 },
  { 88, 3 },
  { 89, 1 },
  { 89, 1 },
  { 89, 3 },
  { 64, 4 },
  { 64, 3 },
  { 90, 5 },
  { 91, 2 },
  { 91, 2 },
  { 92, 1 },
  { 92, 1 },
  { 72, 2 },
  { 72, 1 },
  { 72, 1 },
  { 72, 1 },
  { 72, 1 },
  { 72, 1 },
  { 72, 1 },
  { 72, 1 },
  { 72, 2 },
  { 72, 1 },
  { 72, 1 },
  { 72, 1 },
  { 72, 1 },
  { 72, 1 },
  { 72, 1 },
  { 72, 1 },
  { 72, 1 },
  { 93, 4 },
  { 93, 4 },
  { 94, 1 },
  { 94, 1 },
  { 94, 1 },
  { 94, 1 },
  { 58, 0 },
  { 58, 2 },
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
#line 53 "parser\\epparser.lemon"
{
    yygotominor.yy0 = new Token(yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data, yymsp[0].minor.yy0);
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 1051 "parser\\epparser.c"
        break;
      case 3: /* nameList ::= NAME COMMA NAME */
      case 4: /* nameList ::= nameList COMMA NAME */ yytestcase(yyruleno==4);
      case 8: /* exprList ::= exprList COMMA expr */ yytestcase(yyruleno==8);
#line 61 "parser\\epparser.lemon"
{ yygotominor.yy0 = new Token((yymsp[-2].minor.yy0->data) + ", " + (yymsp[0].minor.yy0->data), yymsp[0].minor.yy0); delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1058 "parser\\epparser.c"
        break;
      case 5: /* exprList ::= funcexpr LSQBRACKET LSQBRACKET numList RSQBRACKET RSQBRACKET */
      case 6: /* expr ::= funcexpr LSQBRACKET LSQBRACKET NUMBER RSQBRACKET RSQBRACKET */ yytestcase(yyruleno==6);
#line 63 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[-2].minor.yy0);
    (*pGen) << yygotominor.yy0->data << " = _SRET(" << yymsp[-5].minor.yy0->data << ", [" << yymsp[-2].minor.yy0->data << "])" << std::endl;
    delete yymsp[-5].minor.yy0; delete yymsp[-2].minor.yy0;
}
#line 1068 "parser\\epparser.c"
        break;
      case 7: /* exprList ::= expr */
      case 9: /* expr ::= NUMBER */ yytestcase(yyruleno==9);
      case 13: /* expr ::= funcexpr */ yytestcase(yyruleno==13);
      case 41: /* lexpr ::= LNOT LNOT lexpr */ yytestcase(yyruleno==41);
      case 70: /* caExpr ::= expr */ yytestcase(yyruleno==70);
      case 71: /* caExpr ::= STRING */ yytestcase(yyruleno==71);
#line 74 "parser\\epparser.lemon"
{ yygotominor.yy0 = yymsp[0].minor.yy0; }
#line 1078 "parser\\epparser.c"
        break;
      case 10: /* expr ::= NAME */
#line 79 "parser\\epparser.lemon"
{
    if(pGen->undefined(yymsp[0].minor.yy0->data)) {
        throw_error(yymsp[0].minor.yy0->line, 103, ("Undeclared variable \'" + (yymsp[0].minor.yy0->data) + "\'"));
        pGen->namedef(yymsp[0].minor.yy0->data);
    }
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1089 "parser\\epparser.c"
        break;
      case 11: /* funcexpr ::= NAME LPAREN exprList RPAREN */
#line 88 "parser\\epparser.lemon"
{
    // Preprocess yymsp[-3].minor.yy0
    funcNamePreprocess(yymsp[-3].minor.yy0->data);
    if (pGen->undefined(yymsp[-3].minor.yy0->data)) {
        throw_error(yymsp[-3].minor.yy0->line, 4449, ("Undefined function " + yymsp[-3].minor.yy0->data));
        pGen->namedef(yymsp[-3].minor.yy0->data);
    }

    yymsp[-3].minor.yy0->data += "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0, *pGen);
}
#line 1104 "parser\\epparser.c"
        break;
      case 12: /* funcexpr ::= NAME LPAREN RPAREN */
#line 101 "parser\\epparser.lemon"
{
    // Preprocess yymsp[-2].minor.yy0
    funcNamePreprocess(yymsp[-2].minor.yy0->data);
    if (pGen->undefined(yymsp[-2].minor.yy0->data)) {
        throw_error(yymsp[-2].minor.yy0->line, 4449, ("Undefined function " + yymsp[-2].minor.yy0->data));
        pGen->namedef(yymsp[-2].minor.yy0->data);
    }

    yymsp[-2].minor.yy0->data += "()";
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0, *pGen);
}
#line 1119 "parser\\epparser.c"
        break;
      case 14: /* expr ::= LPAREN expr RPAREN */
#line 116 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0, *pGen);
}
#line 1127 "parser\\epparser.c"
        break;
      case 15: /* expr ::= MAPSTRING LPAREN STRING RPAREN */
#line 121 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetStringIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0, *pGen);
}
#line 1135 "parser\\epparser.c"
        break;
      case 16: /* expr ::= UNIT LPAREN STRING RPAREN */
#line 126 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetUnitIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0, *pGen);
}
#line 1143 "parser\\epparser.c"
        break;
      case 17: /* expr ::= SWITCH LPAREN STRING RPAREN */
#line 131 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetSwitchIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0, *pGen);
}
#line 1151 "parser\\epparser.c"
        break;
      case 18: /* expr ::= LOCATION LPAREN STRING RPAREN */
#line 136 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetLocationIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0, *pGen);
}
#line 1159 "parser\\epparser.c"
        break;
      case 19: /* expr ::= expr PLUS expr */
#line 141 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "+",  yymsp[0].minor.yy0, *pGen); }
#line 1164 "parser\\epparser.c"
        break;
      case 20: /* expr ::= expr MINUS expr */
#line 142 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "-",  yymsp[0].minor.yy0, *pGen); }
#line 1169 "parser\\epparser.c"
        break;
      case 21: /* expr ::= expr MULTIPLY expr */
#line 143 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "*",  yymsp[0].minor.yy0, *pGen); }
#line 1174 "parser\\epparser.c"
        break;
      case 22: /* expr ::= expr DIVIDE expr */
#line 144 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "//", yymsp[0].minor.yy0, *pGen); }
#line 1179 "parser\\epparser.c"
        break;
      case 23: /* expr ::= expr MOD expr */
#line 145 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "%",  yymsp[0].minor.yy0, *pGen); }
#line 1184 "parser\\epparser.c"
        break;
      case 24: /* expr ::= expr LSHIFT expr */
#line 146 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<<", yymsp[0].minor.yy0, *pGen); }
#line 1189 "parser\\epparser.c"
        break;
      case 25: /* expr ::= expr RSHIFT expr */
#line 147 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">>", yymsp[0].minor.yy0, *pGen); }
#line 1194 "parser\\epparser.c"
        break;
      case 26: /* expr ::= expr BITAND expr */
#line 148 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "&",  yymsp[0].minor.yy0, *pGen); }
#line 1199 "parser\\epparser.c"
        break;
      case 27: /* expr ::= expr BITOR expr */
#line 149 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "|",  yymsp[0].minor.yy0, *pGen); }
#line 1204 "parser\\epparser.c"
        break;
      case 28: /* expr ::= expr BITXOR expr */
#line 150 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "^",  yymsp[0].minor.yy0, *pGen); }
#line 1209 "parser\\epparser.c"
        break;
      case 29: /* expr ::= PLUS expr */
#line 153 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = +" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1214 "parser\\epparser.c"
        break;
      case 30: /* expr ::= MINUS expr */
#line 154 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = -" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1219 "parser\\epparser.c"
        break;
      case 31: /* expr ::= BITNOT expr */
#line 155 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = ~" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1224 "parser\\epparser.c"
        break;
      case 32: /* lexpr ::= expr EQ expr */
#line 158 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "==", yymsp[0].minor.yy0, *pGen); }
#line 1229 "parser\\epparser.c"
        break;
      case 33: /* lexpr ::= expr NE expr */
#line 159 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "!=", yymsp[0].minor.yy0, *pGen); }
#line 1234 "parser\\epparser.c"
        break;
      case 34: /* lexpr ::= expr LE expr */
#line 160 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<=", yymsp[0].minor.yy0, *pGen); }
#line 1239 "parser\\epparser.c"
        break;
      case 35: /* lexpr ::= expr LT expr */
#line 161 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<",  yymsp[0].minor.yy0, *pGen); }
#line 1244 "parser\\epparser.c"
        break;
      case 36: /* lexpr ::= expr GE expr */
#line 162 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">=", yymsp[0].minor.yy0, *pGen); }
#line 1249 "parser\\epparser.c"
        break;
      case 37: /* lexpr ::= expr GT expr */
#line 163 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">" , yymsp[0].minor.yy0, *pGen); }
#line 1254 "parser\\epparser.c"
        break;
      case 38: /* lexpr ::= lexpr LAND lexpr */
#line 165 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "[" + yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data + "]";
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0, *pGen);
}
#line 1263 "parser\\epparser.c"
        break;
      case 39: /* lexpr ::= lexpr LOR lexpr */
#line 171 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "EUDOr([" + yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data + "])";
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0, *pGen);
}
#line 1272 "parser\\epparser.c"
        break;
      case 40: /* lexpr ::= LNOT lexpr */
#line 177 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = "EUDNot([" + yymsp[0].minor.yy0->data + "])";
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0, *pGen);
}
#line 1280 "parser\\epparser.c"
        break;
      case 42: /* vdef_stmt ::= VAR NAME SEMICOLON */
#line 187 "parser\\epparser.lemon"
{
    (*pGen) << yymsp[-1].minor.yy0->data << " = EUDVariable()" << std::endl;
    pGen->namedef(yymsp[-1].minor.yy0->data);
    delete yymsp[-1].minor.yy0;
}
#line 1289 "parser\\epparser.c"
        break;
      case 43: /* vdefAssign_stmt ::= VAR NAME ASSIGN expr SEMICOLON */
#line 193 "parser\\epparser.lemon"
{
    (*pGen) << yymsp[-3].minor.yy0->data << " = _MVAR([" << yymsp[-1].minor.yy0->data << "])" << std::endl;
    if(!pGen->namedef(yymsp[-3].minor.yy0->data)) {
        throw_error(yymsp[-3].minor.yy0->line, 196, ("Redeclaration of variable \'" + (yymsp[-3].minor.yy0->data) + "\'"));
    }
    delete yymsp[-3].minor.yy0;
}
#line 1300 "parser\\epparser.c"
        break;
      case 44: /* vdefMulti_stmt ::= VAR nameList SEMICOLON */
#line 201 "parser\\epparser.lemon"
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
#line 1317 "parser\\epparser.c"
        break;
      case 45: /* vdefMultiAssign_stmt ::= VAR nameList ASSIGN exprList SEMICOLON */
#line 215 "parser\\epparser.lemon"
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
#line 1334 "parser\\epparser.c"
        break;
      case 46: /* assign_stmt ::= NAME ASSIGN expr SEMICOLON */
#line 229 "parser\\epparser.lemon"
{
    (*pGen) << yymsp[-3].minor.yy0->data << " << " << yymsp[-1].minor.yy0->data << std::endl;
    if(pGen->undefined(yymsp[-3].minor.yy0->data)) {
        throw_error(yymsp[-3].minor.yy0->line, 103, ("Undeclared variable \'" + (yymsp[-3].minor.yy0->data) + "\'"));
        pGen->namedef(yymsp[-3].minor.yy0->data);
    }
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1346 "parser\\epparser.c"
        break;
      case 47: /* assignMulti_stmt ::= nameList ASSIGN exprList SEMICOLON */
#line 238 "parser\\epparser.lemon"
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
#line 1362 "parser\\epparser.c"
        break;
      case 51: /* block ::= LBRACKET error RBRACKET */
#line 255 "parser\\epparser.lemon"
{
    throw_error(yymsp[0].minor.yy0->line, 6298, "Block not terminated properly.");
}
#line 1369 "parser\\epparser.c"
        break;
      case 52: /* if_start ::= IF */
#line 261 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    (*pGen) << yygotominor.yy0->data << " = EUDIf()" << std::endl;
}
#line 1377 "parser\\epparser.c"
        break;
      case 53: /* if_header ::= if_start LPAREN lexpr RPAREN */
      case 58: /* while_header ::= while_start LPAREN lexpr RPAREN */ yytestcase(yyruleno==58);
#line 265 "parser\\epparser.lemon"
{
    (*pGen) << "if " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data << "):" << std::endl;
    pGen->indent();
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1387 "parser\\epparser.c"
        break;
      case 54: /* if_stmt ::= if_header stmt */
      case 56: /* if_stmt ::= else_header stmt */ yytestcase(yyruleno==56);
#line 271 "parser\\epparser.lemon"
{
    pGen->unindent(false);
    (*pGen) << "EUDEndIf()" << std::endl;
}
#line 1396 "parser\\epparser.c"
        break;
      case 55: /* else_header ::= if_header stmt ELSE */
#line 276 "parser\\epparser.lemon"
{
    pGen->unindent(false);
    (*pGen) << "if EUDElse()():" << std::endl;
    pGen->indent();
}
#line 1405 "parser\\epparser.c"
        break;
      case 57: /* while_start ::= WHILE */
#line 289 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    (*pGen) << yygotominor.yy0->data << " = EUDWhile()" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1414 "parser\\epparser.c"
        break;
      case 59: /* while_stmt ::= while_header stmt */
#line 301 "parser\\epparser.lemon"
{
    pGen->unindent(false);
    (*pGen) << "EUDEndWhile()" << std::endl;
}
#line 1422 "parser\\epparser.c"
        break;
      case 60: /* foreach_header ::= FOR LPAREN nameList COLON exprList RPAREN */
#line 307 "parser\\epparser.lemon"
{
    (*pGen) << "for " << yymsp[-3].minor.yy0->data << " in " << yymsp[-1].minor.yy0->data << ":" << std::endl;
    pGen->indent();
    commaListIter(yymsp[-3].minor.yy0->data, [&](const std::string& s) {
        pGen->namedef(s);
    });
}
#line 1433 "parser\\epparser.c"
        break;
      case 61: /* foreach_stmt ::= foreach_header stmt */
      case 67: /* fdef_chunk ::= function_header stmt */ yytestcase(yyruleno==67);
#line 315 "parser\\epparser.lemon"
{
    pGen->unindent(true);
}
#line 1441 "parser\\epparser.c"
        break;
      case 62: /* continue_stmt ::= CONTINUE SEMICOLON */
#line 321 "parser\\epparser.lemon"
{
    (*pGen) << "EUDContinue()" << std::endl;
}
#line 1448 "parser\\epparser.c"
        break;
      case 63: /* break_stmt ::= BREAK SEMICOLON */
#line 325 "parser\\epparser.lemon"
{
    (*pGen) << "EUDBreak()" << std::endl;
}
#line 1455 "parser\\epparser.c"
        break;
      case 64: /* function_start ::= FUNCTION NAME */
#line 330 "parser\\epparser.lemon"
{
    // Preprocess yymsp[0].minor.yy0
    funcNamePreprocess(yymsp[0].minor.yy0->data);
    yygotominor.yy0 = yymsp[0].minor.yy0;
    if(!pGen->namedef(yymsp[0].minor.yy0->data)) {
        throw_error(yymsp[0].minor.yy0->line, 4495, "Duplicate function yymsp[0].minor.yy0 " + yymsp[0].minor.yy0->data);
    }
}
#line 1467 "parser\\epparser.c"
        break;
      case 65: /* function_header ::= function_start LPAREN nameList RPAREN */
#line 339 "parser\\epparser.lemon"
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
#line 1487 "parser\\epparser.c"
        break;
      case 66: /* function_header ::= function_start LPAREN RPAREN */
#line 356 "parser\\epparser.lemon"
{
    (*pGen) << "@EUDFunc" << std::endl;
    (*pGen) << "def " << yymsp[-2].minor.yy0->data << "():" << std::endl;
    pGen->indent();
    tmpIndex = 1;
    delete yymsp[-2].minor.yy0;
}
#line 1498 "parser\\epparser.c"
        break;
      case 68: /* return_stmt ::= RETURN SEMICOLON */
#line 370 "parser\\epparser.lemon"
{
    (*pGen) << "EUDReturn()" << std::endl;
}
#line 1505 "parser\\epparser.c"
        break;
      case 69: /* return_stmt ::= RETURN exprList SEMICOLON */
#line 374 "parser\\epparser.lemon"
{
    (*pGen) << "EUDReturn(" << yymsp[-1].minor.yy0->data << ")" << std::endl;
    delete yymsp[-1].minor.yy0;
}
#line 1513 "parser\\epparser.c"
        break;
      case 72: /* caExpr ::= caExpr COMMA caExpr */
#line 384 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data;
    yymsp[-2].minor.yy0->type = TOKEN_TEMP;
    yygotominor.yy0 = yymsp[-2].minor.yy0;
}
#line 1522 "parser\\epparser.c"
        break;
      case 73: /* lexpr ::= CONDITIONNAME LPAREN caExpr RPAREN */
#line 391 "parser\\epparser.lemon"
{
    yymsp[-3].minor.yy0->data = yymsp[-3].minor.yy0->data + "(" + yymsp[-1].minor.yy0->data + ")";
    delete yymsp[-1].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0, *pGen);
}
#line 1531 "parser\\epparser.c"
        break;
      case 74: /* lexpr ::= CONDITIONNAME LPAREN RPAREN */
#line 397 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + "()";
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0, *pGen);
}
#line 1539 "parser\\epparser.c"
        break;
      case 75: /* action ::= ACTIONNAME LPAREN caExpr RPAREN SEMICOLON */
#line 402 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[-4].minor.yy0);
    yygotominor.yy0->data =  yymsp[-4].minor.yy0->data + "(" + yymsp[-2].minor.yy0->data + ")";
    delete yymsp[-4].minor.yy0; delete yymsp[-2].minor.yy0;
}
#line 1548 "parser\\epparser.c"
        break;
      case 76: /* actions ::= action action */
      case 77: /* actions ::= actions action */ yytestcase(yyruleno==77);
#line 408 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
    yymsp[-1].minor.yy0->data += ",\n" + yymsp[0].minor.yy0->data;
    delete yymsp[0].minor.yy0;
}
#line 1558 "parser\\epparser.c"
        break;
      case 78: /* actionStmt ::= action */
#line 420 "parser\\epparser.lemon"
{
    (*pGen) << "DoEvents(" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1566 "parser\\epparser.c"
        break;
      case 79: /* actionStmt ::= actions */
#line 425 "parser\\epparser.lemon"
{
    (*pGen) << "DoEvents([" << std::endl;
    pGen->indent();
    (*pGen) << yymsp[0].minor.yy0->data << std::endl;
    pGen->unindent(false);
    (*pGen) << "])" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1578 "parser\\epparser.c"
        break;
      case 80: /* stmt ::= error SEMICOLON */
#line 436 "parser\\epparser.lemon"
{ throw_error(yymsp[0].minor.yy0->line, 6974, "Error while parsing statement"); }
#line 1583 "parser\\epparser.c"
        break;
      case 88: /* stmt ::= funcexpr SEMICOLON */
#line 446 "parser\\epparser.lemon"
{ (*pGen) << yymsp[-1].minor.yy0->data << std::endl; }
#line 1588 "parser\\epparser.c"
        break;
      case 97: /* import_chunk ::= FROM NAME IMPORT nameList */
#line 459 "parser\\epparser.lemon"
{
    (*pGen) << "from " << yymsp[-2].minor.yy0->data << " import " << yymsp[0].minor.yy0->data << std::endl;
    commaListIter(yymsp[0].minor.yy0->data, [&](std::string varname) {
        funcNamePreprocess(varname);
        if(!pGen->namedef(varname)) {
            throw_error(yymsp[0].minor.yy0->line, 8118, ("Importing already-declared function " + varname));
        }
        else (*pGen) << "from " << yymsp[-2].minor.yy0->data << " import " << varname << std::endl;
    });
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 1603 "parser\\epparser.c"
        break;
      case 98: /* import_chunk ::= FROM NAME IMPORT NAME */
#line 471 "parser\\epparser.lemon"
{
    funcNamePreprocess(yymsp[0].minor.yy0->data);
    if(!pGen->namedef(yymsp[0].minor.yy0->data)) {
        throw_error(yymsp[0].minor.yy0->line, 8118, ("Importing already-declared function " + yymsp[0].minor.yy0->data));
    }
    else (*pGen) << "from " << yymsp[-2].minor.yy0->data << " import " << yymsp[0].minor.yy0->data << std::endl;
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 1615 "parser\\epparser.c"
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
      /* (99) chunk ::= import_chunk */ yytestcase(yyruleno==99);
      /* (100) chunk ::= fdef_chunk */ yytestcase(yyruleno==100);
      /* (101) chunk ::= vdef_stmt */ yytestcase(yyruleno==101);
      /* (102) chunk ::= vdefMulti_stmt */ yytestcase(yyruleno==102);
      /* (103) chunks ::= */ yytestcase(yyruleno==103);
      /* (104) chunks ::= chunks chunk */ yytestcase(yyruleno==104);
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
#line 19 "parser\\epparser.lemon"

    throw_error(currentTokenizingLine, 629, "Unrecoverable error");
#line 1691 "parser\\epparser.c"
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
#line 15 "parser\\epparser.lemon"

    errorOccured = true;
#line 1709 "parser\\epparser.c"
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
#line 487 "parser\\epparser.lemon"


int PARSER_DEBUG = 0;

std::string ParseString(const std::string& code)
{
    Tokenizer tok(code);
    void* pParser = ParseAlloc (malloc);
    PyGenerator pGen;
    Token* token;
    currentTokenizingLine = 0;

    if(PARSER_DEBUG) std::cout << "Parsing string [[[\n" << code.c_str() << "\n]]]\n";

    tmpIndex = 1;
    errorOccured = false;
    while ((token = tok.getToken()) != nullptr) {
        if (currentTokenizingLine != tok.getCurrentLine()) {
            currentTokenizingLine = tok.getCurrentLine();
            pGen << "# (Line " << currentTokenizingLine << ") " << trim(tok.getCurrentLineString()) << std::endl;
            if(PARSER_DEBUG) printf("# reading line %s\n", tok.getCurrentLineString().c_str());
        }
        if (tokenTypeConv(token)) {
            Parse (pParser, token->type, token, &pGen);
        }
        else {
            throw_error(token->line, 8104, "Invalid token");
        }
    }
    Parse (pParser, 0, nullptr, &pGen);
    ParseFree(pParser, free );

    if(!errorOccured) return postProcessCode(pGen.str());
    else throw std::runtime_error("Invalid syntax");
}
#line 1936 "parser\\epparser.c"
