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
#define YYNOCODE 97
#define YYACTIONTYPE unsigned short int
#define ParseTOKENTYPE Token*
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  int yy193;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL  PyGenerator* pGen ;
#define ParseARG_PDECL , PyGenerator* pGen 
#define ParseARG_FETCH  PyGenerator* pGen  = yypParser->pGen 
#define ParseARG_STORE yypParser->pGen  = pGen 
#define YYNSTATE 217
#define YYNRULE 106
#define YYERRORSYMBOL 55
#define YYERRSYMDT yy193
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
 /*     0 */    78,   41,   42,   40,  160,   87,  143,   46,   93,   84,
 /*    10 */   110,   64,  158,  157,  155,  156,  154,  153,    2,  184,
 /*    20 */   144,  105,    6,  150,    5,  101,    4,  149,    3,  148,
 /*    30 */   147,  146,  134,   23,   94,  145,   50,   49,  151,   87,
 /*    40 */   135,   30,   93,  128,   65,  195,  158,  157,  155,  156,
 /*    50 */   154,  153,  108,  142,  144,  105,    6,  150,    5,  101,
 /*    60 */     4,  149,    3,  148,  147,  146,  130,   99,   94,  145,
 /*    70 */    50,   49,  151,   87,  134,   21,   93,  215,   19,  124,
 /*    80 */   158,  157,  155,  156,  154,  153,  107,  102,  144,  105,
 /*    90 */     6,  150,    5,  101,    4,  149,    3,  148,  147,  146,
 /*   100 */   130,  141,   94,  145,   50,   49,  151,   87,  194,  135,
 /*   110 */    93,  213,   19,  106,  158,  157,  155,  156,  154,  153,
 /*   120 */   216,  173,  144,  105,    6,  150,    5,  101,    4,  149,
 /*   130 */     3,  148,  147,  146,  130,  129,   94,  145,   50,   49,
 /*   140 */   151,   87,  177,  134,   93,  188,  110,   64,  158,  157,
 /*   150 */   155,  156,  154,  153,  214,  170,  144,  105,    6,  150,
 /*   160 */     5,  101,    4,  149,    3,  148,  147,  146,  128,   75,
 /*   170 */    94,  145,   50,   49,  151,   87,  128,   57,   93,   83,
 /*   180 */   110,   64,  158,  157,  155,  156,  154,  153,  212,  168,
 /*   190 */   144,  105,    6,  150,    5,  101,    4,  149,    3,  148,
 /*   200 */   147,  146,  128,   76,   94,  145,   50,   49,  151,   87,
 /*   210 */    13,   14,   93,   81,  110,   64,  158,  157,  155,  156,
 /*   220 */   154,  153,  211,  183,  144,  105,    6,  150,    5,  101,
 /*   230 */     4,  149,    3,  148,  147,  146,   13,   14,  175,  145,
 /*   240 */    50,   49,  151,   29,   27,   26,   25,   24,   28,   36,
 /*   250 */    35,   37,   39,   38,   45,   43,   41,   42,   40,   34,
 /*   260 */    33,  138,  135,  137,  171,   32,  208,  123,  135,   31,
 /*   270 */   196,   44,  193,   12,  122,  119,  116,  113,   80,  110,
 /*   280 */    64,  132,    7,  139,  128,  202,   34,   33,  140,  136,
 /*   290 */   127,  131,   32,  208,  123,   22,  210,   16,   44,  215,
 /*   300 */   126,  122,  119,  116,  113,  125,  134,   11,   36,   35,
 /*   310 */    37,   39,   38,   45,   43,   41,   42,   40,  124,  103,
 /*   320 */    34,   33,  128,   65,   79,  169,   32,  208,  123,  128,
 /*   330 */    65,   88,   44,  192,   22,  122,  119,  116,  113,   34,
 /*   340 */    33,  128,   54,  213,   72,   32,  208,  123,   77,   16,
 /*   350 */   196,   44,  176,  103,  122,  119,  116,  113,  209,   51,
 /*   360 */   159,    1,  182,  181,  324,    8,  172,  100,  121,   98,
 /*   370 */    97,  187,   18,  120,   96,   36,   35,   37,   39,   38,
 /*   380 */    45,   43,   41,   42,   40,   37,   39,   38,   45,   43,
 /*   390 */    41,   42,   40,  207,   36,   35,   37,   39,   38,   45,
 /*   400 */    43,   41,   42,   40,   39,   38,   45,   43,   41,   42,
 /*   410 */    40,  128,   65,   82,   34,   33,  206,   22,  117,  186,
 /*   420 */    32,  208,  123,   22,  118,  196,   44,  128,  201,  122,
 /*   430 */   119,  116,  113,   34,   33,  205,   19,  115,  114,   32,
 /*   440 */   208,  123,  128,  200,  204,   44,   77,  112,  122,  119,
 /*   450 */   116,  113,  203,  164,  185,  128,   70,   51,  159,    1,
 /*   460 */   165,  181,  128,   69,  172,  100,   95,   98,   97,  111,
 /*   470 */    18,  109,   96,   36,   35,   37,   39,   38,   45,   43,
 /*   480 */    41,   42,   40,   34,   33,  217,  128,   68,   52,   32,
 /*   490 */   208,  123,  191,  128,   54,   44,  180,  190,  122,  119,
 /*   500 */   116,  113,  189,   20,   35,   37,   39,   38,   45,   43,
 /*   510 */    41,   42,   40,  174,   45,   43,   41,   42,   40,  128,
 /*   520 */    66,   14,   53,   15,   91,  128,   54,  167,  104,  128,
 /*   530 */    54,   89,  179,   10,  133,   85,  128,   54,   92,  178,
 /*   540 */   128,   54,    9,   71,  128,   67,  128,  199,   48,  128,
 /*   550 */   198,  128,  197,  166,  128,   56,   17,  128,   55,  163,
 /*   560 */   128,   63,  128,   62,  128,   61,  160,  152,  128,   60,
 /*   570 */   128,   59,  128,   58,   47,   90,   86,   96,   74,   73,
 /*   580 */   131,  325,  325,  162,  325,  325,  161,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    55,   20,   21,   22,   38,   60,   40,   30,   63,   62,
 /*    10 */    63,   64,   67,   68,   69,   70,   71,   72,   73,   74,
 /*    20 */    75,   76,   77,   78,   79,   80,   81,   82,   83,   84,
 /*    30 */    85,   86,    1,    2,   55,   90,   91,   92,   93,   60,
 /*    40 */     1,    2,   63,   63,   64,   65,   67,   68,   69,   70,
 /*    50 */    71,   72,    1,   74,   75,   76,   77,   78,   79,   80,
 /*    60 */    81,   82,   83,   84,   85,   86,   60,   61,   55,   90,
 /*    70 */    91,   92,   93,   60,    1,    2,   63,   38,    1,   28,
 /*    80 */    67,   68,   69,   70,   71,   72,    1,   74,   75,   76,
 /*    90 */    77,   78,   79,   80,   81,   82,   83,   84,   85,   86,
 /*   100 */    60,   61,   55,   90,   91,   92,   93,   60,   31,    1,
 /*   110 */    63,   38,    1,   28,   67,   68,   69,   70,   71,   72,
 /*   120 */    26,   74,   75,   76,   77,   78,   79,   80,   81,   82,
 /*   130 */    83,   84,   85,   86,   60,   61,   55,   90,   91,   92,
 /*   140 */    93,   60,   31,    1,   63,   62,   63,   64,   67,   68,
 /*   150 */    69,   70,   71,   72,   26,   74,   75,   76,   77,   78,
 /*   160 */    79,   80,   81,   82,   83,   84,   85,   86,   63,   64,
 /*   170 */    55,   90,   91,   92,   93,   60,   63,   64,   63,   62,
 /*   180 */    63,   64,   67,   68,   69,   70,   71,   72,   26,   74,
 /*   190 */    75,   76,   77,   78,   79,   80,   81,   82,   83,   84,
 /*   200 */    85,   86,   63,   64,   55,   90,   91,   92,   93,   60,
 /*   210 */     3,    4,   63,   62,   63,   64,   67,   68,   69,   70,
 /*   220 */    71,   72,   31,   74,   75,   76,   77,   78,   79,   80,
 /*   230 */    81,   82,   83,   84,   85,   86,    3,    4,   31,   90,
 /*   240 */    91,   92,   93,    7,    8,    9,   10,   11,   12,   13,
 /*   250 */    14,   15,   16,   17,   18,   19,   20,   21,   22,   18,
 /*   260 */    19,   67,    1,   69,   31,   24,   25,   26,    1,    2,
 /*   270 */    29,   30,   31,    5,   33,   34,   35,   36,   62,   63,
 /*   280 */    64,   87,   88,   89,   63,   64,   18,   19,   94,   95,
 /*   290 */    27,   26,   24,   25,   26,    1,   31,   30,   30,   38,
 /*   300 */    27,   33,   34,   35,   36,   25,    1,    5,   13,   14,
 /*   310 */    15,   16,   17,   18,   19,   20,   21,   22,   28,   51,
 /*   320 */    18,   19,   63,   64,   65,   31,   24,   25,   26,   63,
 /*   330 */    64,   65,   30,   38,    1,   33,   34,   35,   36,   18,
 /*   340 */    19,   63,   64,   38,   66,   24,   25,   26,   26,   30,
 /*   350 */    29,   30,   31,   51,   33,   34,   35,   36,   28,   37,
 /*   360 */    38,   39,   40,   41,   57,   58,   44,   45,   30,   47,
 /*   370 */    48,   38,   50,   29,   52,   13,   14,   15,   16,   17,
 /*   380 */    18,   19,   20,   21,   22,   15,   16,   17,   18,   19,
 /*   390 */    20,   21,   22,   31,   13,   14,   15,   16,   17,   18,
 /*   400 */    19,   20,   21,   22,   16,   17,   18,   19,   20,   21,
 /*   410 */    22,   63,   64,   65,   18,   19,   31,    1,   29,   38,
 /*   420 */    24,   25,   26,    1,   30,   29,   30,   63,   64,   33,
 /*   430 */    34,   35,   36,   18,   19,   31,    1,   30,   29,   24,
 /*   440 */    25,   26,   63,   64,   31,   30,   26,   30,   33,   34,
 /*   450 */    35,   36,   31,   38,   38,   63,   64,   37,   38,   39,
 /*   460 */    38,   41,   63,   64,   44,   45,   31,   47,   48,   29,
 /*   470 */    50,   27,   52,   13,   14,   15,   16,   17,   18,   19,
 /*   480 */    20,   21,   22,   18,   19,    0,   63,   64,   27,   24,
 /*   490 */    25,   26,   25,   63,   64,   30,   66,   25,   33,   34,
 /*   500 */    35,   36,   28,   46,   14,   15,   16,   17,   18,   19,
 /*   510 */    20,   21,   22,   43,   18,   19,   20,   21,   22,   63,
 /*   520 */    64,    4,   37,   30,   26,   63,   64,   38,   66,   63,
 /*   530 */    64,   60,   66,   30,   49,   59,   63,   64,   53,   66,
 /*   540 */    63,   64,   30,   66,   63,   64,   63,   64,   30,   63,
 /*   550 */    64,   63,   64,   38,   63,   64,   30,   63,   64,   38,
 /*   560 */    63,   64,   63,   64,   63,   64,   38,   38,   63,   64,
 /*   570 */    63,   64,   63,   64,   54,   26,   25,   52,   26,   60,
 /*   580 */    26,   96,   96,   91,   96,   96,   91,
};
#define YY_SHIFT_USE_DFLT (-35)
#define YY_SHIFT_COUNT (135)
#define YY_SHIFT_MIN   (-34)
#define YY_SHIFT_MAX   (554)
static const short yy_shift_ofst[] = {
 /*     0 */   -35,  420,  322,  420,  420,  420,  420,  420,  485,  268,
 /*    10 */   321,  302,  302,  268,  268,  268,  241,  396,  415,  396,
 /*    20 */   465,  465,  465,  465,  465,  465,  465,  465,  465,  465,
 /*    30 */   465,  465,  465,  465,  465,  465,  465,  465,  465,  465,
 /*    40 */   465,  465,  465,  465,  465,  465,  265,  554,  554,  525,
 /*    50 */   525,  552,  551,  549,  236,  381,  295,  362,  460,  460,
 /*    60 */   460,  460,  460,  460,  460,  460,  490,  370,  388,  496,
 /*    70 */   496,  233,  207,   73,   39,  -19,  -19,  267,  -34,  435,
 /*    80 */   422,  294,  111,  416,  333,   85,   51,   31,   77,  305,
 /*    90 */   261,  520,  498,  529,  528,  521,  526,  515,  489,  457,
 /*   100 */   518,  512,  470,  503,  517,  493,  474,  472,  467,  461,
 /*   110 */   444,  421,  440,  417,  413,  409,  407,  404,  389,  394,
 /*   120 */   385,  344,  338,  319,  330,  290,  280,  273,  263,  191,
 /*   130 */   142,  108,  -23,  162,  128,   94,
};
#define YY_REDUCE_USE_DFLT (-56)
#define YY_REDUCE_COUNT (53)
#define YY_REDUCE_MIN   (-55)
#define YY_REDUCE_MAX   (519)
static const short yy_reduce_ofst[] = {
 /*     0 */   307,  -55,  149,  115,   81,   47,   13,  -21,  194,  477,
 /*    10 */   348,  473,  466,  462,  430,  278,  266,  259,  216,  -20,
 /*    20 */   151,  117,   83,  -53,  509,  507,  505,  501,  499,  497,
 /*    30 */   494,  491,  488,  486,  483,  481,  456,  423,  399,  392,
 /*    40 */   379,  364,  221,  139,  113,  105,   74,   40,    6,  495,
 /*    50 */   492,  519,  476,  471,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   321,  323,  323,  323,  323,  323,  323,  323,  323,  323,
 /*    10 */   323,  323,  323,  323,  323,  323,  323,  323,  323,  323,
 /*    20 */   323,  323,  323,  323,  323,  323,  323,  323,  323,  323,
 /*    30 */   323,  323,  323,  323,  323,  323,  323,  323,  323,  323,
 /*    40 */   323,  323,  323,  323,  323,  323,  323,  323,  323,  298,
 /*    50 */   297,  323,  323,  323,  323,  323,  323,  323,  259,  258,
 /*    60 */   257,  256,  255,  254,  226,  230,  249,  250,  248,  247,
 /*    70 */   246,  323,  323,  323,  323,  241,  242,  323,  323,  323,
 /*    80 */   323,  323,  323,  323,  323,  323,  323,  323,  323,  323,
 /*    90 */   323,  323,  323,  323,  323,  323,  323,  323,  323,  323,
 /*   100 */   323,  323,  276,  323,  261,  323,  323,  323,  323,  323,
 /*   110 */   235,  323,  323,  323,  323,  323,  323,  323,  323,  323,
 /*   120 */   323,  323,  323,  229,  323,  323,  323,  323,  235,  323,
 /*   130 */   223,  222,  323,  323,  323,  323,  322,  320,  319,  318,
 /*   140 */   317,  316,  289,  273,  315,  314,  313,  312,  311,  310,
 /*   150 */   309,  308,  307,  306,  305,  304,  303,  302,  301,  300,
 /*   160 */   299,  296,  295,  294,  290,  291,  285,  284,  283,  282,
 /*   170 */   281,  280,  279,  278,  277,  275,  293,  292,  263,  262,
 /*   180 */   260,  274,  272,  271,  270,  267,  265,  269,  227,  224,
 /*   190 */   219,  218,  268,  234,  233,  232,  231,  253,  252,  251,
 /*   200 */   245,  244,  243,  240,  239,  238,  237,  236,  228,  225,
 /*   210 */   288,  287,  286,  266,  221,  264,  220,
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
  "RSQBRACKET",    "STRING",        "LPAREN",        "RPAREN",      
  "FUNCCALL",      "MAPSTRING",     "UNIT",          "SWITCH",      
  "LOCATION",      "VAR",           "SEMICOLON",     "LBRACKET",    
  "RBRACKET",      "IF",            "IFX",           "ELSE",        
  "WHILE",         "FOR",           "COLON",         "CONTINUE",    
  "BREAK",         "FUNCTION",      "RETURN",        "CONDITIONNAME",
  "ACTIONNAME",    "FROM",          "IMPORT",        "error",       
  "nt",            "program",       "chunks",        "numList",     
  "nameListMulti",  "nameList",      "exprList",      "funcexpr",    
  "expr",          "fArgs",         "lexpr",         "vdef_stmt",   
  "vdefAssign_stmt",  "vdefMulti_stmt",  "vdefMultiAssign_stmt",  "assign_stmt", 
  "assignMulti_stmt",  "stmtList",      "stmt",          "block",       
  "if_start",      "if_header",     "if_stmt",       "else_header", 
  "while_start",   "while_header",  "while_stmt",    "foreach_header",
  "foreach_stmt",  "continue_stmt",  "break_stmt",    "function_start",
  "function_header",  "fdef_chunk",    "return_stmt",   "action",      
  "actions",       "actionStmt",    "import_chunk",  "chunk",       
};
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *const yyRuleName[] = {
 /*   0 */ "program ::= chunks",
 /*   1 */ "numList ::= NUMBER COMMA NUMBER",
 /*   2 */ "numList ::= numList COMMA NUMBER",
 /*   3 */ "nameListMulti ::= NAME COMMA NAME",
 /*   4 */ "nameListMulti ::= nameListMulti COMMA NAME",
 /*   5 */ "nameList ::= NAME",
 /*   6 */ "nameList ::= nameListMulti",
 /*   7 */ "exprList ::= funcexpr LSQBRACKET LSQBRACKET numList RSQBRACKET RSQBRACKET",
 /*   8 */ "expr ::= funcexpr LSQBRACKET LSQBRACKET NUMBER RSQBRACKET RSQBRACKET",
 /*   9 */ "exprList ::= expr",
 /*  10 */ "exprList ::= exprList COMMA exprList",
 /*  11 */ "expr ::= NUMBER",
 /*  12 */ "expr ::= NAME",
 /*  13 */ "fArgs ::= expr",
 /*  14 */ "fArgs ::= STRING",
 /*  15 */ "fArgs ::= fArgs COMMA fArgs",
 /*  16 */ "funcexpr ::= NAME LPAREN fArgs RPAREN",
 /*  17 */ "funcexpr ::= NAME LPAREN RPAREN",
 /*  18 */ "expr ::= funcexpr",
 /*  19 */ "expr ::= LPAREN expr RPAREN",
 /*  20 */ "expr ::= MAPSTRING LPAREN STRING RPAREN",
 /*  21 */ "expr ::= UNIT LPAREN STRING RPAREN",
 /*  22 */ "expr ::= SWITCH LPAREN STRING RPAREN",
 /*  23 */ "expr ::= LOCATION LPAREN STRING RPAREN",
 /*  24 */ "expr ::= expr PLUS expr",
 /*  25 */ "expr ::= expr MINUS expr",
 /*  26 */ "expr ::= expr MULTIPLY expr",
 /*  27 */ "expr ::= expr DIVIDE expr",
 /*  28 */ "expr ::= expr MOD expr",
 /*  29 */ "expr ::= expr LSHIFT expr",
 /*  30 */ "expr ::= expr RSHIFT expr",
 /*  31 */ "expr ::= expr BITAND expr",
 /*  32 */ "expr ::= expr BITOR expr",
 /*  33 */ "expr ::= expr BITXOR expr",
 /*  34 */ "expr ::= PLUS expr",
 /*  35 */ "expr ::= MINUS expr",
 /*  36 */ "expr ::= BITNOT expr",
 /*  37 */ "lexpr ::= expr EQ expr",
 /*  38 */ "lexpr ::= expr NE expr",
 /*  39 */ "lexpr ::= expr LE expr",
 /*  40 */ "lexpr ::= expr LT expr",
 /*  41 */ "lexpr ::= expr GE expr",
 /*  42 */ "lexpr ::= expr GT expr",
 /*  43 */ "lexpr ::= lexpr LAND lexpr",
 /*  44 */ "lexpr ::= lexpr LOR lexpr",
 /*  45 */ "lexpr ::= LNOT lexpr",
 /*  46 */ "lexpr ::= LNOT LNOT lexpr",
 /*  47 */ "vdef_stmt ::= VAR NAME SEMICOLON",
 /*  48 */ "vdefAssign_stmt ::= VAR NAME ASSIGN expr SEMICOLON",
 /*  49 */ "vdefMulti_stmt ::= VAR nameListMulti SEMICOLON",
 /*  50 */ "vdefMultiAssign_stmt ::= VAR nameListMulti ASSIGN exprList SEMICOLON",
 /*  51 */ "assign_stmt ::= NAME ASSIGN expr SEMICOLON",
 /*  52 */ "assignMulti_stmt ::= nameListMulti ASSIGN exprList SEMICOLON",
 /*  53 */ "stmtList ::= stmt",
 /*  54 */ "stmtList ::= stmtList stmt",
 /*  55 */ "block ::= LBRACKET stmtList RBRACKET",
 /*  56 */ "block ::= LBRACKET error RBRACKET",
 /*  57 */ "if_start ::= IF",
 /*  58 */ "if_header ::= if_start LPAREN lexpr RPAREN",
 /*  59 */ "if_stmt ::= if_header stmt",
 /*  60 */ "else_header ::= if_header stmt ELSE",
 /*  61 */ "if_stmt ::= else_header stmt",
 /*  62 */ "while_start ::= WHILE",
 /*  63 */ "while_header ::= while_start LPAREN lexpr RPAREN",
 /*  64 */ "while_stmt ::= while_header stmt",
 /*  65 */ "foreach_header ::= FOR LPAREN nameList COLON exprList RPAREN",
 /*  66 */ "foreach_stmt ::= foreach_header stmt",
 /*  67 */ "continue_stmt ::= CONTINUE SEMICOLON",
 /*  68 */ "break_stmt ::= BREAK SEMICOLON",
 /*  69 */ "function_start ::= FUNCTION NAME",
 /*  70 */ "function_header ::= function_start LPAREN nameList RPAREN",
 /*  71 */ "function_header ::= function_start LPAREN RPAREN",
 /*  72 */ "fdef_chunk ::= function_header stmt",
 /*  73 */ "return_stmt ::= RETURN SEMICOLON",
 /*  74 */ "return_stmt ::= RETURN exprList SEMICOLON",
 /*  75 */ "lexpr ::= CONDITIONNAME LPAREN fArgs RPAREN",
 /*  76 */ "lexpr ::= CONDITIONNAME LPAREN RPAREN",
 /*  77 */ "action ::= ACTIONNAME LPAREN fArgs RPAREN SEMICOLON",
 /*  78 */ "actions ::= action action",
 /*  79 */ "actions ::= actions action",
 /*  80 */ "actionStmt ::= action",
 /*  81 */ "actionStmt ::= actions",
 /*  82 */ "stmt ::= error SEMICOLON",
 /*  83 */ "stmt ::= SEMICOLON",
 /*  84 */ "stmt ::= vdef_stmt",
 /*  85 */ "stmt ::= vdefAssign_stmt",
 /*  86 */ "stmt ::= vdefMultiAssign_stmt",
 /*  87 */ "stmt ::= vdefMulti_stmt",
 /*  88 */ "stmt ::= assign_stmt",
 /*  89 */ "stmt ::= assignMulti_stmt",
 /*  90 */ "stmt ::= funcexpr SEMICOLON",
 /*  91 */ "stmt ::= actionStmt",
 /*  92 */ "stmt ::= if_stmt",
 /*  93 */ "stmt ::= while_stmt",
 /*  94 */ "stmt ::= foreach_stmt",
 /*  95 */ "stmt ::= continue_stmt",
 /*  96 */ "stmt ::= break_stmt",
 /*  97 */ "stmt ::= return_stmt",
 /*  98 */ "stmt ::= block",
 /*  99 */ "import_chunk ::= FROM NAME IMPORT nameList",
 /* 100 */ "chunk ::= import_chunk",
 /* 101 */ "chunk ::= fdef_chunk",
 /* 102 */ "chunk ::= vdef_stmt",
 /* 103 */ "chunk ::= vdefMulti_stmt",
 /* 104 */ "chunks ::=",
 /* 105 */ "chunks ::= chunks chunk",
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
#line 648 "parser\\epparser.c"
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
  { 61, 1 },
  { 61, 1 },
  { 62, 6 },
  { 64, 6 },
  { 62, 1 },
  { 62, 3 },
  { 64, 1 },
  { 64, 1 },
  { 65, 1 },
  { 65, 1 },
  { 65, 3 },
  { 63, 4 },
  { 63, 3 },
  { 64, 1 },
  { 64, 3 },
  { 64, 4 },
  { 64, 4 },
  { 64, 4 },
  { 64, 4 },
  { 64, 3 },
  { 64, 3 },
  { 64, 3 },
  { 64, 3 },
  { 64, 3 },
  { 64, 3 },
  { 64, 3 },
  { 64, 3 },
  { 64, 3 },
  { 64, 3 },
  { 64, 2 },
  { 64, 2 },
  { 64, 2 },
  { 66, 3 },
  { 66, 3 },
  { 66, 3 },
  { 66, 3 },
  { 66, 3 },
  { 66, 3 },
  { 66, 3 },
  { 66, 3 },
  { 66, 2 },
  { 66, 3 },
  { 67, 3 },
  { 68, 5 },
  { 69, 3 },
  { 70, 5 },
  { 71, 4 },
  { 72, 4 },
  { 73, 1 },
  { 73, 2 },
  { 75, 3 },
  { 75, 3 },
  { 76, 1 },
  { 77, 4 },
  { 78, 2 },
  { 79, 3 },
  { 78, 2 },
  { 80, 1 },
  { 81, 4 },
  { 82, 2 },
  { 83, 6 },
  { 84, 2 },
  { 85, 2 },
  { 86, 2 },
  { 87, 2 },
  { 88, 4 },
  { 88, 3 },
  { 89, 2 },
  { 90, 2 },
  { 90, 3 },
  { 66, 4 },
  { 66, 3 },
  { 91, 5 },
  { 92, 2 },
  { 92, 2 },
  { 93, 1 },
  { 93, 1 },
  { 74, 2 },
  { 74, 1 },
  { 74, 1 },
  { 74, 1 },
  { 74, 1 },
  { 74, 1 },
  { 74, 1 },
  { 74, 1 },
  { 74, 2 },
  { 74, 1 },
  { 74, 1 },
  { 74, 1 },
  { 74, 1 },
  { 74, 1 },
  { 74, 1 },
  { 74, 1 },
  { 74, 1 },
  { 94, 4 },
  { 95, 1 },
  { 95, 1 },
  { 95, 1 },
  { 95, 1 },
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
#line 1053 "parser\\epparser.c"
        break;
      case 3: /* nameListMulti ::= NAME COMMA NAME */
      case 4: /* nameListMulti ::= nameListMulti COMMA NAME */ yytestcase(yyruleno==4);
      case 10: /* exprList ::= exprList COMMA exprList */ yytestcase(yyruleno==10);
#line 61 "parser\\epparser.lemon"
{ yygotominor.yy0 = new Token((yymsp[-2].minor.yy0->data) + ", " + (yymsp[0].minor.yy0->data), yymsp[0].minor.yy0); delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1060 "parser\\epparser.c"
        break;
      case 5: /* nameList ::= NAME */
      case 6: /* nameList ::= nameListMulti */ yytestcase(yyruleno==6);
      case 9: /* exprList ::= expr */ yytestcase(yyruleno==9);
      case 11: /* expr ::= NUMBER */ yytestcase(yyruleno==11);
      case 13: /* fArgs ::= expr */ yytestcase(yyruleno==13);
      case 14: /* fArgs ::= STRING */ yytestcase(yyruleno==14);
      case 18: /* expr ::= funcexpr */ yytestcase(yyruleno==18);
      case 46: /* lexpr ::= LNOT LNOT lexpr */ yytestcase(yyruleno==46);
#line 63 "parser\\epparser.lemon"
{ yygotominor.yy0 = yymsp[0].minor.yy0; }
#line 1072 "parser\\epparser.c"
        break;
      case 7: /* exprList ::= funcexpr LSQBRACKET LSQBRACKET numList RSQBRACKET RSQBRACKET */
      case 8: /* expr ::= funcexpr LSQBRACKET LSQBRACKET NUMBER RSQBRACKET RSQBRACKET */ yytestcase(yyruleno==8);
#line 66 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[-2].minor.yy0);
    (*pGen) << yygotominor.yy0->data << " = _SRET(" << yymsp[-5].minor.yy0->data << ", [" << yymsp[-2].minor.yy0->data << "])" << std::endl;
    delete yymsp[-5].minor.yy0; delete yymsp[-2].minor.yy0;
}
#line 1082 "parser\\epparser.c"
        break;
      case 12: /* expr ::= NAME */
#line 83 "parser\\epparser.lemon"
{
    if(pGen->undefined(yymsp[0].minor.yy0->data)) {
        throw_error(yymsp[0].minor.yy0->line, 103, ("Undeclared variable \'" + (yymsp[0].minor.yy0->data) + "\'"));
        pGen->namedef(yymsp[0].minor.yy0->data);
    }
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1093 "parser\\epparser.c"
        break;
      case 15: /* fArgs ::= fArgs COMMA fArgs */
#line 94 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data;
    yymsp[-2].minor.yy0->type = TOKEN_TEMP;
    yygotominor.yy0 = yymsp[-2].minor.yy0;
}
#line 1102 "parser\\epparser.c"
        break;
      case 16: /* funcexpr ::= NAME LPAREN fArgs RPAREN */
#line 100 "parser\\epparser.lemon"
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
#line 1117 "parser\\epparser.c"
        break;
      case 17: /* funcexpr ::= NAME LPAREN RPAREN */
#line 113 "parser\\epparser.lemon"
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
#line 1132 "parser\\epparser.c"
        break;
      case 19: /* expr ::= LPAREN expr RPAREN */
#line 128 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0, *pGen);
}
#line 1140 "parser\\epparser.c"
        break;
      case 20: /* expr ::= MAPSTRING LPAREN STRING RPAREN */
#line 133 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetStringIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0, *pGen);
}
#line 1148 "parser\\epparser.c"
        break;
      case 21: /* expr ::= UNIT LPAREN STRING RPAREN */
#line 138 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetUnitIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0, *pGen);
}
#line 1156 "parser\\epparser.c"
        break;
      case 22: /* expr ::= SWITCH LPAREN STRING RPAREN */
#line 143 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetSwitchIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0, *pGen);
}
#line 1164 "parser\\epparser.c"
        break;
      case 23: /* expr ::= LOCATION LPAREN STRING RPAREN */
#line 148 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetLocationIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0, *pGen);
}
#line 1172 "parser\\epparser.c"
        break;
      case 24: /* expr ::= expr PLUS expr */
#line 153 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "+",  yymsp[0].minor.yy0, *pGen); }
#line 1177 "parser\\epparser.c"
        break;
      case 25: /* expr ::= expr MINUS expr */
#line 154 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "-",  yymsp[0].minor.yy0, *pGen); }
#line 1182 "parser\\epparser.c"
        break;
      case 26: /* expr ::= expr MULTIPLY expr */
#line 155 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "*",  yymsp[0].minor.yy0, *pGen); }
#line 1187 "parser\\epparser.c"
        break;
      case 27: /* expr ::= expr DIVIDE expr */
#line 156 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "//", yymsp[0].minor.yy0, *pGen); }
#line 1192 "parser\\epparser.c"
        break;
      case 28: /* expr ::= expr MOD expr */
#line 157 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "%",  yymsp[0].minor.yy0, *pGen); }
#line 1197 "parser\\epparser.c"
        break;
      case 29: /* expr ::= expr LSHIFT expr */
#line 158 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<<", yymsp[0].minor.yy0, *pGen); }
#line 1202 "parser\\epparser.c"
        break;
      case 30: /* expr ::= expr RSHIFT expr */
#line 159 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">>", yymsp[0].minor.yy0, *pGen); }
#line 1207 "parser\\epparser.c"
        break;
      case 31: /* expr ::= expr BITAND expr */
#line 160 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "&",  yymsp[0].minor.yy0, *pGen); }
#line 1212 "parser\\epparser.c"
        break;
      case 32: /* expr ::= expr BITOR expr */
#line 161 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "|",  yymsp[0].minor.yy0, *pGen); }
#line 1217 "parser\\epparser.c"
        break;
      case 33: /* expr ::= expr BITXOR expr */
#line 162 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "^",  yymsp[0].minor.yy0, *pGen); }
#line 1222 "parser\\epparser.c"
        break;
      case 34: /* expr ::= PLUS expr */
#line 165 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = +" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1227 "parser\\epparser.c"
        break;
      case 35: /* expr ::= MINUS expr */
#line 166 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = -" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1232 "parser\\epparser.c"
        break;
      case 36: /* expr ::= BITNOT expr */
#line 167 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = ~" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1237 "parser\\epparser.c"
        break;
      case 37: /* lexpr ::= expr EQ expr */
#line 170 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "==", yymsp[0].minor.yy0, *pGen); }
#line 1242 "parser\\epparser.c"
        break;
      case 38: /* lexpr ::= expr NE expr */
#line 171 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "!=", yymsp[0].minor.yy0, *pGen); }
#line 1247 "parser\\epparser.c"
        break;
      case 39: /* lexpr ::= expr LE expr */
#line 172 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<=", yymsp[0].minor.yy0, *pGen); }
#line 1252 "parser\\epparser.c"
        break;
      case 40: /* lexpr ::= expr LT expr */
#line 173 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<",  yymsp[0].minor.yy0, *pGen); }
#line 1257 "parser\\epparser.c"
        break;
      case 41: /* lexpr ::= expr GE expr */
#line 174 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">=", yymsp[0].minor.yy0, *pGen); }
#line 1262 "parser\\epparser.c"
        break;
      case 42: /* lexpr ::= expr GT expr */
#line 175 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">" , yymsp[0].minor.yy0, *pGen); }
#line 1267 "parser\\epparser.c"
        break;
      case 43: /* lexpr ::= lexpr LAND lexpr */
#line 177 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "[" + yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data + "]";
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0, *pGen);
}
#line 1276 "parser\\epparser.c"
        break;
      case 44: /* lexpr ::= lexpr LOR lexpr */
#line 183 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "EUDOr([" + yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data + "])";
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0, *pGen);
}
#line 1285 "parser\\epparser.c"
        break;
      case 45: /* lexpr ::= LNOT lexpr */
#line 189 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = "EUDNot([" + yymsp[0].minor.yy0->data + "])";
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0, *pGen);
}
#line 1293 "parser\\epparser.c"
        break;
      case 47: /* vdef_stmt ::= VAR NAME SEMICOLON */
#line 199 "parser\\epparser.lemon"
{
    (*pGen) << yymsp[-1].minor.yy0->data << " = EUDVariable()" << std::endl;
    pGen->namedef(yymsp[-1].minor.yy0->data);
    delete yymsp[-1].minor.yy0;
}
#line 1302 "parser\\epparser.c"
        break;
      case 48: /* vdefAssign_stmt ::= VAR NAME ASSIGN expr SEMICOLON */
#line 205 "parser\\epparser.lemon"
{
    (*pGen) << yymsp[-3].minor.yy0->data << " = _MVAR([" << yymsp[-1].minor.yy0->data << "])" << std::endl;
    if(!pGen->namedef(yymsp[-3].minor.yy0->data)) {
        throw_error(yymsp[-3].minor.yy0->line, 196, ("Redeclaration of variable \'" + (yymsp[-3].minor.yy0->data) + "\'"));
    }
    delete yymsp[-3].minor.yy0;
}
#line 1313 "parser\\epparser.c"
        break;
      case 49: /* vdefMulti_stmt ::= VAR nameListMulti SEMICOLON */
#line 213 "parser\\epparser.lemon"
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
#line 1330 "parser\\epparser.c"
        break;
      case 50: /* vdefMultiAssign_stmt ::= VAR nameListMulti ASSIGN exprList SEMICOLON */
#line 227 "parser\\epparser.lemon"
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
#line 1347 "parser\\epparser.c"
        break;
      case 51: /* assign_stmt ::= NAME ASSIGN expr SEMICOLON */
#line 241 "parser\\epparser.lemon"
{
    (*pGen) << yymsp[-3].minor.yy0->data << " << " << yymsp[-1].minor.yy0->data << std::endl;
    if(pGen->undefined(yymsp[-3].minor.yy0->data)) {
        throw_error(yymsp[-3].minor.yy0->line, 103, ("Undeclared variable \'" + (yymsp[-3].minor.yy0->data) + "\'"));
        pGen->namedef(yymsp[-3].minor.yy0->data);
    }
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1359 "parser\\epparser.c"
        break;
      case 52: /* assignMulti_stmt ::= nameListMulti ASSIGN exprList SEMICOLON */
#line 250 "parser\\epparser.lemon"
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
#line 1375 "parser\\epparser.c"
        break;
      case 56: /* block ::= LBRACKET error RBRACKET */
#line 267 "parser\\epparser.lemon"
{
    throw_error(yymsp[0].minor.yy0->line, 6298, "Block not terminated properly.");
}
#line 1382 "parser\\epparser.c"
        break;
      case 57: /* if_start ::= IF */
#line 273 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    (*pGen) << yygotominor.yy0->data << " = EUDIf()" << std::endl;
}
#line 1390 "parser\\epparser.c"
        break;
      case 58: /* if_header ::= if_start LPAREN lexpr RPAREN */
      case 63: /* while_header ::= while_start LPAREN lexpr RPAREN */ yytestcase(yyruleno==63);
#line 277 "parser\\epparser.lemon"
{
    (*pGen) << "if " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data << "):" << std::endl;
    pGen->indent();
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1400 "parser\\epparser.c"
        break;
      case 59: /* if_stmt ::= if_header stmt */
      case 61: /* if_stmt ::= else_header stmt */ yytestcase(yyruleno==61);
#line 283 "parser\\epparser.lemon"
{
    pGen->unindent(false);
    (*pGen) << "EUDEndIf()" << std::endl;
}
#line 1409 "parser\\epparser.c"
        break;
      case 60: /* else_header ::= if_header stmt ELSE */
#line 288 "parser\\epparser.lemon"
{
    pGen->unindent(false);
    (*pGen) << "if EUDElse()():" << std::endl;
    pGen->indent();
}
#line 1418 "parser\\epparser.c"
        break;
      case 62: /* while_start ::= WHILE */
#line 301 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    (*pGen) << yygotominor.yy0->data << " = EUDWhile()" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1427 "parser\\epparser.c"
        break;
      case 64: /* while_stmt ::= while_header stmt */
#line 313 "parser\\epparser.lemon"
{
    pGen->unindent(false);
    (*pGen) << "EUDEndWhile()" << std::endl;
}
#line 1435 "parser\\epparser.c"
        break;
      case 65: /* foreach_header ::= FOR LPAREN nameList COLON exprList RPAREN */
#line 319 "parser\\epparser.lemon"
{
    (*pGen) << "for " << yymsp[-3].minor.yy0->data << " in " << yymsp[-1].minor.yy0->data << ":" << std::endl;
    pGen->indent();
    commaListIter(yymsp[-3].minor.yy0->data, [&](const std::string& s) {
        pGen->namedef(s);
    });
}
#line 1446 "parser\\epparser.c"
        break;
      case 66: /* foreach_stmt ::= foreach_header stmt */
      case 72: /* fdef_chunk ::= function_header stmt */ yytestcase(yyruleno==72);
#line 327 "parser\\epparser.lemon"
{
    pGen->unindent(true);
}
#line 1454 "parser\\epparser.c"
        break;
      case 67: /* continue_stmt ::= CONTINUE SEMICOLON */
#line 333 "parser\\epparser.lemon"
{
    (*pGen) << "EUDContinue()" << std::endl;
}
#line 1461 "parser\\epparser.c"
        break;
      case 68: /* break_stmt ::= BREAK SEMICOLON */
#line 337 "parser\\epparser.lemon"
{
    (*pGen) << "EUDBreak()" << std::endl;
}
#line 1468 "parser\\epparser.c"
        break;
      case 69: /* function_start ::= FUNCTION NAME */
#line 342 "parser\\epparser.lemon"
{
    // Preprocess yymsp[0].minor.yy0
    funcNamePreprocess(yymsp[0].minor.yy0->data);
    yygotominor.yy0 = yymsp[0].minor.yy0;
    if(!pGen->namedef(yymsp[0].minor.yy0->data)) {
        throw_error(yymsp[0].minor.yy0->line, 4495, "Duplicate function yymsp[0].minor.yy0 " + yymsp[0].minor.yy0->data);
    }
}
#line 1480 "parser\\epparser.c"
        break;
      case 70: /* function_header ::= function_start LPAREN nameList RPAREN */
#line 351 "parser\\epparser.lemon"
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
#line 1500 "parser\\epparser.c"
        break;
      case 71: /* function_header ::= function_start LPAREN RPAREN */
#line 368 "parser\\epparser.lemon"
{
    (*pGen) << "@EUDFunc" << std::endl;
    (*pGen) << "def " << yymsp[-2].minor.yy0->data << "():" << std::endl;
    pGen->indent();
    tmpIndex = 1;
    delete yymsp[-2].minor.yy0;
}
#line 1511 "parser\\epparser.c"
        break;
      case 73: /* return_stmt ::= RETURN SEMICOLON */
#line 382 "parser\\epparser.lemon"
{
    (*pGen) << "EUDReturn()" << std::endl;
}
#line 1518 "parser\\epparser.c"
        break;
      case 74: /* return_stmt ::= RETURN exprList SEMICOLON */
#line 386 "parser\\epparser.lemon"
{
    (*pGen) << "EUDReturn(" << yymsp[-1].minor.yy0->data << ")" << std::endl;
    delete yymsp[-1].minor.yy0;
}
#line 1526 "parser\\epparser.c"
        break;
      case 75: /* lexpr ::= CONDITIONNAME LPAREN fArgs RPAREN */
#line 394 "parser\\epparser.lemon"
{
    yymsp[-3].minor.yy0->data = yymsp[-3].minor.yy0->data + "(" + yymsp[-1].minor.yy0->data + ")";
    delete yymsp[-1].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0, *pGen);
}
#line 1535 "parser\\epparser.c"
        break;
      case 76: /* lexpr ::= CONDITIONNAME LPAREN RPAREN */
#line 400 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + "()";
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0, *pGen);
}
#line 1543 "parser\\epparser.c"
        break;
      case 77: /* action ::= ACTIONNAME LPAREN fArgs RPAREN SEMICOLON */
#line 405 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[-4].minor.yy0);
    yygotominor.yy0->data =  yymsp[-4].minor.yy0->data + "(" + yymsp[-2].minor.yy0->data + ")";
    delete yymsp[-4].minor.yy0; delete yymsp[-2].minor.yy0;
}
#line 1552 "parser\\epparser.c"
        break;
      case 78: /* actions ::= action action */
      case 79: /* actions ::= actions action */ yytestcase(yyruleno==79);
#line 411 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
    yymsp[-1].minor.yy0->data += ",\n" + yymsp[0].minor.yy0->data;
    delete yymsp[0].minor.yy0;
}
#line 1562 "parser\\epparser.c"
        break;
      case 80: /* actionStmt ::= action */
#line 423 "parser\\epparser.lemon"
{
    (*pGen) << "DoEvents(" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1570 "parser\\epparser.c"
        break;
      case 81: /* actionStmt ::= actions */
#line 428 "parser\\epparser.lemon"
{
    (*pGen) << "DoEvents([" << std::endl;
    pGen->indent();
    (*pGen) << yymsp[0].minor.yy0->data << std::endl;
    pGen->unindent(false);
    (*pGen) << "])" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1582 "parser\\epparser.c"
        break;
      case 82: /* stmt ::= error SEMICOLON */
#line 439 "parser\\epparser.lemon"
{ throw_error(yymsp[0].minor.yy0->line, 6974, "Error while parsing statement"); }
#line 1587 "parser\\epparser.c"
        break;
      case 90: /* stmt ::= funcexpr SEMICOLON */
#line 449 "parser\\epparser.lemon"
{ (*pGen) << yymsp[-1].minor.yy0->data << std::endl; }
#line 1592 "parser\\epparser.c"
        break;
      case 99: /* import_chunk ::= FROM NAME IMPORT nameList */
#line 462 "parser\\epparser.lemon"
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
#line 1607 "parser\\epparser.c"
        break;
      default:
      /* (0) program ::= chunks */ yytestcase(yyruleno==0);
      /* (53) stmtList ::= stmt */ yytestcase(yyruleno==53);
      /* (54) stmtList ::= stmtList stmt */ yytestcase(yyruleno==54);
      /* (55) block ::= LBRACKET stmtList RBRACKET */ yytestcase(yyruleno==55);
      /* (83) stmt ::= SEMICOLON */ yytestcase(yyruleno==83);
      /* (84) stmt ::= vdef_stmt */ yytestcase(yyruleno==84);
      /* (85) stmt ::= vdefAssign_stmt */ yytestcase(yyruleno==85);
      /* (86) stmt ::= vdefMultiAssign_stmt */ yytestcase(yyruleno==86);
      /* (87) stmt ::= vdefMulti_stmt */ yytestcase(yyruleno==87);
      /* (88) stmt ::= assign_stmt */ yytestcase(yyruleno==88);
      /* (89) stmt ::= assignMulti_stmt */ yytestcase(yyruleno==89);
      /* (91) stmt ::= actionStmt */ yytestcase(yyruleno==91);
      /* (92) stmt ::= if_stmt */ yytestcase(yyruleno==92);
      /* (93) stmt ::= while_stmt */ yytestcase(yyruleno==93);
      /* (94) stmt ::= foreach_stmt */ yytestcase(yyruleno==94);
      /* (95) stmt ::= continue_stmt */ yytestcase(yyruleno==95);
      /* (96) stmt ::= break_stmt */ yytestcase(yyruleno==96);
      /* (97) stmt ::= return_stmt */ yytestcase(yyruleno==97);
      /* (98) stmt ::= block */ yytestcase(yyruleno==98);
      /* (100) chunk ::= import_chunk */ yytestcase(yyruleno==100);
      /* (101) chunk ::= fdef_chunk */ yytestcase(yyruleno==101);
      /* (102) chunk ::= vdef_stmt */ yytestcase(yyruleno==102);
      /* (103) chunk ::= vdefMulti_stmt */ yytestcase(yyruleno==103);
      /* (104) chunks ::= */ yytestcase(yyruleno==104);
      /* (105) chunks ::= chunks chunk */ yytestcase(yyruleno==105);
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
#line 1683 "parser\\epparser.c"
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
#line 1701 "parser\\epparser.c"
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
#line 481 "parser\\epparser.lemon"


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
#ifndef NDEBUG
            if(PARSER_DEBUG) ParseTrace(stdout, "--");
#endif
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
#line 1931 "parser\\epparser.c"
