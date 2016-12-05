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
#include <algorithm>
#include <regex>

#include "epparser.h"
#include "generator/pygen.h"
#include "generator/closure.h"
#include "parser.h"
#include "tokenAdapter.h"
#include "parserUtilities.h"

struct ParserStruct {
    PyGenerator gen;
    ClosureManager closure;
};

int currentTokenizingLine;
bool functionCalledInMultipleActions;

#line 33 "parser\\epparser.c"
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
#define YYNOCODE 132
#define YYACTIONTYPE unsigned short int
#define ParseTOKENTYPE Token*
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  int yy263;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL  ParserStruct* ps ;
#define ParseARG_PDECL , ParserStruct* ps 
#define ParseARG_FETCH  ParserStruct* ps  = yypParser->ps 
#define ParseARG_STORE yypParser->ps  = ps 
#define YYNSTATE 326
#define YYNRULE 168
#define YYERRORSYMBOL 71
#define YYERRSYMDT yy263
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
#define YY_ACTTAB_COUNT (1286)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   211,  241,  197,   28,   29,   18,   28,   29,  207,   75,
 /*    10 */   205,  303,  195,   90,  313,  311,  210,    2,  121,  144,
 /*    20 */   206,  204,  149,  295,  294,  293,  292,  291,  199,  198,
 /*    30 */   212,  240,  271,   90,  324,  265,   81,   80,  121,  144,
 /*    40 */   162,    8,   40,  297,   28,   29,  159,    6,   10,  321,
 /*    50 */   211,  203,   22,   13,    5,   82,    4,   76,  207,   77,
 /*    60 */   205,  303,   38,  212,  256,  311,  210,    2,  242,   14,
 /*    70 */   206,  204,  149,  295,  294,  293,  292,  291,  199,  198,
 /*    80 */   160,    7,    3,   90,  194,   37,  212,   19,  121,  144,
 /*    90 */   162,    8,   40,   34,  279,  114,  159,    6,   10,  239,
 /*   100 */   211,   39,   22,   13,    5,   82,    4,  320,  207,   77,
 /*   110 */   205,  303,   35,   36,  253,  311,  210,    2,  215,  197,
 /*   120 */   206,  204,  149,  295,  294,  293,  292,  291,  199,  198,
 /*   130 */    96,  235,  197,   90,  319,  259,  213,  218,  121,  144,
 /*   140 */   162,    8,   40,  115,  219,  277,  159,    6,   10,  317,
 /*   150 */   211,  191,   22,   13,    5,   82,    4,  197,  207,   77,
 /*   160 */   205,  303,   33,  212,  250,  311,  210,    2,  116,  197,
 /*   170 */   206,  204,  149,  295,  294,  293,  292,  291,  199,  198,
 /*   180 */    93,  216,  197,   90,  194,  190,  495,   11,  121,  144,
 /*   190 */   162,    8,   40,  127,  165,  114,  159,    6,   10,   78,
 /*   200 */   211,  214,   22,   13,    5,   82,    4,  197,  207,   77,
 /*   210 */   205,  303,  316,  212,  237,  311,  210,    2,  126,  197,
 /*   220 */   206,  204,  149,  295,  294,  293,  292,  291,  199,  198,
 /*   230 */   139,  314,  197,   90,  194,  202,  312,  310,  121,  144,
 /*   240 */   162,    8,   40,  138,  164,  114,  159,    6,   10,   87,
 /*   250 */   211,  197,   22,   13,    5,   82,    4,  197,  207,   77,
 /*   260 */   205,  303,  137,  201,  234,  311,  210,    2,  125,  197,
 /*   270 */   206,  204,  149,  295,  294,  293,  292,  291,  199,  198,
 /*   280 */   124,   86,  197,   90,  194,  200,  301,  300,  121,  144,
 /*   290 */   162,    8,   40,  123,  163,  114,  159,    6,   10,  299,
 /*   300 */   211,  197,   22,   13,    5,   82,    4,  298,  207,   77,
 /*   310 */   205,  303,  120,  296,  227,  311,  210,    2,  203,  197,
 /*   320 */   206,  204,  149,  295,  294,  293,  292,  291,  199,  198,
 /*   330 */   122,  290,  197,   90,  194,  289,   19,  284,  121,  144,
 /*   340 */   162,    8,   40,   92,  141,  114,  159,    6,   10,  193,
 /*   350 */   151,  197,   22,   13,    5,   82,    4,   85,  207,   77,
 /*   360 */   205,  303,  136,  281,  280,  225,  209,    2,   39,    1,
 /*   370 */   206,  204,  149,  295,  294,  293,  292,  291,  199,  198,
 /*   380 */    31,   17,  197,   90,  194,   32,  184,  183,  121,  144,
 /*   390 */   162,    8,   40,  135,  150,  114,  159,    6,   10,  276,
 /*   400 */   287,  181,   22,   13,    5,   82,    4,  180,  207,   77,
 /*   410 */   205,  303,  275,  178,  177,  288,  208,    2,  305,  197,
 /*   420 */   206,  204,  149,  295,  294,  293,  292,  291,  199,  198,
 /*   430 */    89,  274,  197,   90,  132,  175,  174,  273,  121,  144,
 /*   440 */   162,    8,   40,  134,  272,   29,  159,    6,   10,   15,
 /*   450 */   264,  119,   22,   13,    5,   82,    4,   63,   62,   77,
 /*   460 */    71,   72,   70,   61,  286,  117,  302,   28,   29,  267,
 /*   470 */    64,   18,  309,  308,   21,   75,  285,  263,  195,   25,
 /*   480 */   188,  185,  182,  179,  176,   84,   83,   42,   41,   69,
 /*   490 */    68,   74,   73,   71,   72,   70,  257,  262,  255,  258,
 /*   500 */    24,  252,  158,  155,   18,  233,  232,   20,   75,   28,
 /*   510 */    29,  195,  197,   23,  249,   12,  236,  243,   63,   62,
 /*   520 */   431,  431,  230,  113,   61,  286,  117,  302,   28,   29,
 /*   530 */    16,   64,  226,  309,  307,   21,  152,  285,  254,  306,
 /*   540 */   197,  188,  185,  182,  179,  176,   84,   83,   42,   41,
 /*   550 */    19,  115,  307,  186,  167,  304,  147,  251,  192,  146,
 /*   560 */   258,  315,  252,  158,  155,  145,  233,  232,   20,  431,
 /*   570 */   431,  431,  431,  431,  431,  431,  431,  431,  431,   63,
 /*   580 */    62,  142,  197,  241,  197,   61,  286,  117,  302,  229,
 /*   590 */   154,  161,   64,   88,  309,   90,   21,  133,  285,  228,
 /*   600 */   121,  144,  188,  185,  182,  179,  176,   84,   83,   42,
 /*   610 */    41,  140,  496,  143,  496,  197,  496,  496,  496,  496,
 /*   620 */   496,  258,  496,  252,  158,  155,   89,  233,  232,   20,
 /*   630 */   270,   60,   58,   57,   56,   55,   59,   66,   65,   67,
 /*   640 */    69,   68,   74,   73,   71,   72,   70,  197,  496,  496,
 /*   650 */   496,  496,  496,  496,  496,   18,  282,  496,  115,   75,
 /*   660 */   186,  168,  195,   60,   58,   57,   56,   55,   59,   66,
 /*   670 */    65,   67,   69,   68,   74,   73,   71,   72,   70,  496,
 /*   680 */   496,  496,   63,   62,  496,  496,  194,   18,   61,  286,
 /*   690 */   117,   75,  194,  496,  195,   64,  189,  114,  169,   21,
 /*   700 */   496,  285,  189,  114,  231,  188,  185,  182,  179,  176,
 /*   710 */    84,   83,   42,   41,   63,   62,  496,  496,  496,  197,
 /*   720 */    61,  286,  117,  496,  197,  197,  496,   64,  238,  326,
 /*   730 */    89,   21,  197,  285,  172,  112,  111,  188,  185,  182,
 /*   740 */   179,  176,  496,  110,   42,   41,  496,   66,   65,   67,
 /*   750 */    69,   68,   74,   73,   71,   72,   70,  220,  496,  217,
 /*   760 */    27,  496,  309,  496,  496,   18,  197,  197,  496,   54,
 /*   770 */   496,  496,  166,   63,   62,   79,   83,  109,  108,   61,
 /*   780 */   286,  196,  261,  260,  197,  496,   30,  496,  496,   26,
 /*   790 */    21,  496,  187,  197,  496,   91,  188,  185,  182,  179,
 /*   800 */   176,  197,   63,   62,  115,  496,  186,  173,   61,  286,
 /*   810 */   196,  496,   89,  496,  496,   30,  269,  496,  496,   21,
 /*   820 */   496,  187,  496,  197,  171,  188,  185,  182,  179,  176,
 /*   830 */   197,  197,  197,  496,  115,  496,  186,  153,   63,   62,
 /*   840 */   496,  107,  106,   89,   61,  286,  148,  268,  496,  197,
 /*   850 */   496,   64,  266,  171,  496,   21,  197,  285,  496,  278,
 /*   860 */   105,  188,  185,  182,  179,  176,  496,  104,  197,  197,
 /*   870 */    63,   62,  496,  496,  197,  197,   61,  286,  117,  115,
 /*   880 */    89,  186,  170,   64,  131,  103,   89,   21,  496,  285,
 /*   890 */   130,  197,  496,  188,  185,  182,  179,  176,  496,  496,
 /*   900 */    42,   41,  102,   66,   65,   67,   69,   68,   74,   73,
 /*   910 */    71,   72,   70,  496,   74,   73,   71,   72,   70,  197,
 /*   920 */   496,   18,  197,  496,  496,   75,  283,   18,  195,  496,
 /*   930 */   101,   75,  496,  100,  195,   66,   65,   67,   69,   68,
 /*   940 */    74,   73,   71,   72,   70,  496,  496,  197,  496,  496,
 /*   950 */   197,  496,  496,   18,  282,  197,  496,   75,   89,  496,
 /*   960 */   195,   99,  129,  496,  496,  496,   98,   66,   65,   67,
 /*   970 */    69,   68,   74,   73,   71,   72,   70,  496,  496,  496,
 /*   980 */   197,  496,  496,  496,  496,   18,  496,   63,   62,   75,
 /*   990 */   118,   97,  195,   61,  286,  148,  197,  496,  197,  496,
 /*  1000 */    64,  496,  496,  496,   21,  496,  285,   95,  278,   94,
 /*  1010 */   188,  185,  182,  179,  176,  496,  496,  496,   66,   65,
 /*  1020 */    67,   69,   68,   74,   73,   71,   72,   70,  496,  496,
 /*  1030 */   197,  496,  496,  496,  496,  496,   18,  496,  496,  496,
 /*  1040 */    75,   89,  496,  195,  496,  128,  496,  496,  496,  496,
 /*  1050 */    66,   65,   67,   69,   68,   74,   73,   71,   72,   70,
 /*  1060 */   496,  496,  496,  496,  496,  496,  496,  496,   18,  496,
 /*  1070 */    63,   62,   54,  496,  496,  166,   61,  286,  196,  496,
 /*  1080 */   496,  496,  496,   64,  496,  496,  496,   21,  496,  285,
 /*  1090 */   496,  496,  496,  188,  185,  182,  179,  176,  496,  496,
 /*  1100 */   496,  496,   63,   62,  496,  496,  496,  496,   61,  286,
 /*  1110 */   117,  433,  433,  496,  496,   64,  496,  496,  496,   21,
 /*  1120 */   496,  285,  496,  432,  432,  188,  185,  182,  179,  176,
 /*  1130 */    65,   67,   69,   68,   74,   73,   71,   72,   70,  496,
 /*  1140 */   496,  496,  496,  496,  496,  496,  496,   18,  496,  496,
 /*  1150 */   496,   75,  496,  496,  195,  496,  496,  496,  496,  496,
 /*  1160 */   433,  433,  433,  433,  433,  433,  433,  433,  433,  433,
 /*  1170 */    53,  496,  432,  432,  432,  432,  432,  432,  432,  432,
 /*  1180 */   432,  432,   67,   69,   68,   74,   73,   71,   72,   70,
 /*  1190 */   496,  496,  496,  496,  496,  496,  496,  496,   18,  496,
 /*  1200 */   496,  496,   75,  496,  496,  195,  496,  496,  496,  496,
 /*  1210 */   496,  496,  496,  496,  496,  496,  496,  496,  496,   52,
 /*  1220 */    51,   50,   49,   48,   47,   46,   45,   44,   43,  496,
 /*  1230 */   325,  224,  323,  322,  223,  222,  221,  318,    9,  496,
 /*  1240 */   248,  496,  246,    2,  248,  496,  246,  496,  496,  496,
 /*  1250 */   496,  496,  247,  245,  197,  496,  247,  245,  197,  496,
 /*  1260 */   496,  496,  496,  496,  496,   90,  496,  496,  496,   90,
 /*  1270 */   121,  144,  496,  496,  121,  144,  496,  496,  496,  496,
 /*  1280 */   496,  157,  156,  496,  496,  244,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    71,   92,   93,    3,    4,   31,    3,    4,   79,   35,
 /*    10 */    81,   82,   38,  104,   85,   86,   87,   88,  109,  110,
 /*    20 */    91,   92,   93,   94,   95,   96,   97,   98,   99,  100,
 /*    30 */     2,  122,   32,  104,   27,   32,  128,  129,  109,  110,
 /*    40 */   111,  112,  113,   27,    3,    4,  117,  118,  119,   27,
 /*    50 */    71,   35,  123,  124,  125,  126,  127,    1,   79,  130,
 /*    60 */    81,   82,    1,    2,   85,   86,   87,   88,   27,    2,
 /*    70 */    91,   92,   93,   94,   95,   96,   97,   98,   99,  100,
 /*    80 */   114,  115,  116,  104,   93,    1,    2,   31,  109,  110,
 /*    90 */   111,  112,  113,   65,  103,  104,  117,  118,  119,   32,
 /*   100 */    71,    2,  123,  124,  125,  126,  127,   27,   79,  130,
 /*   110 */    81,   82,    1,    2,   85,   86,   87,   88,   84,   93,
 /*   120 */    91,   92,   93,   94,   95,   96,   97,   98,   99,  100,
 /*   130 */   104,   32,   93,  104,   27,  109,  102,   29,  109,  110,
 /*   140 */   111,  112,  113,  104,   26,  106,  117,  118,  119,   26,
 /*   150 */    71,    2,  123,  124,  125,  126,  127,   93,   79,  130,
 /*   160 */    81,   82,    1,    2,   85,   86,   87,   88,  104,   93,
 /*   170 */    91,   92,   93,   94,   95,   96,   97,   98,   99,  100,
 /*   180 */   104,   26,   93,  104,   93,   36,   73,   74,  109,  110,
 /*   190 */   111,  112,  113,  104,  103,  104,  117,  118,  119,   31,
 /*   200 */    71,   32,  123,  124,  125,  126,  127,   93,   79,  130,
 /*   210 */    81,   82,   27,    2,   85,   86,   87,   88,  104,   93,
 /*   220 */    91,   92,   93,   94,   95,   96,   97,   98,   99,  100,
 /*   230 */   104,   26,   93,  104,   93,   35,   27,   27,  109,  110,
 /*   240 */   111,  112,  113,  104,  103,  104,  117,  118,  119,   27,
 /*   250 */    71,   93,  123,  124,  125,  126,  127,   93,   79,  130,
 /*   260 */    81,   82,  104,   25,   85,   86,   87,   88,  104,   93,
 /*   270 */    91,   92,   93,   94,   95,   96,   97,   98,   99,  100,
 /*   280 */   104,   27,   93,  104,   93,   36,   27,   27,  109,  110,
 /*   290 */   111,  112,  113,  104,  103,  104,  117,  118,  119,   27,
 /*   300 */    71,   93,  123,  124,  125,  126,  127,   27,   79,  130,
 /*   310 */    81,   82,  104,   36,   85,   86,   87,   88,   35,   93,
 /*   320 */    91,   92,   93,   94,   95,   96,   97,   98,   99,  100,
 /*   330 */   104,   27,   93,  104,   93,   27,   31,   26,  109,  110,
 /*   340 */   111,  112,  113,  104,  103,  104,  117,  118,  119,   35,
 /*   350 */    71,   93,  123,  124,  125,  126,  127,   35,   79,  130,
 /*   360 */    81,   82,  104,   25,   36,   86,   87,   88,    2,   90,
 /*   370 */    91,   92,   93,   94,   95,   96,   97,   98,   99,  100,
 /*   380 */    31,   31,   93,  104,   93,    2,   31,   39,  109,  110,
 /*   390 */   111,  112,  113,  104,  103,  104,  117,  118,  119,   32,
 /*   400 */    71,   31,  123,  124,  125,  126,  127,   39,   79,  130,
 /*   410 */    81,   82,   32,   31,   39,   86,   87,   88,   89,   93,
 /*   420 */    91,   92,   93,   94,   95,   96,   97,   98,   99,  100,
 /*   430 */   104,   32,   93,  104,  108,   31,   39,   32,  109,  110,
 /*   440 */   111,  112,  113,  104,   32,    4,  117,  118,  119,   31,
 /*   450 */    36,   26,  123,  124,  125,  126,  127,   18,   19,  130,
 /*   460 */    20,   21,   22,   24,   25,   26,   27,    3,    4,   32,
 /*   470 */    31,   31,   33,   34,   35,   35,   37,   32,   38,   31,
 /*   480 */    41,   42,   43,   44,   45,   46,   47,   48,   49,   16,
 /*   490 */    17,   18,   19,   20,   21,   22,   32,   32,   60,   60,
 /*   500 */    31,   62,   63,   64,   31,   66,   67,   68,   35,    3,
 /*   510 */     4,   38,   93,   31,   31,    2,   31,   27,   18,   19,
 /*   520 */     1,    2,   27,  104,   24,   25,   26,   27,    3,    4,
 /*   530 */    31,   31,   34,   33,   34,   35,   32,   37,   32,   89,
 /*   540 */    93,   41,   42,   43,   44,   45,   46,   47,   48,   49,
 /*   550 */    31,  104,   34,  106,  107,   89,  101,   32,   25,  102,
 /*   560 */    60,   26,   62,   63,   64,  102,   66,   67,   68,   50,
 /*   570 */    51,   52,   53,   54,   55,   56,   57,   58,   59,   18,
 /*   580 */    19,  102,   93,   92,   93,   24,   25,   26,   27,  128,
 /*   590 */    70,   61,   31,  104,   33,  104,   35,  108,   37,  128,
 /*   600 */   109,  110,   41,   42,   43,   44,   45,   46,   47,   48,
 /*   610 */    49,  102,  131,  122,  131,   93,  131,  131,  131,  131,
 /*   620 */   131,   60,  131,   62,   63,   64,  104,   66,   67,   68,
 /*   630 */   108,    7,    8,    9,   10,   11,   12,   13,   14,   15,
 /*   640 */    16,   17,   18,   19,   20,   21,   22,   93,  131,  131,
 /*   650 */   131,  131,  131,  131,  131,   31,   32,  131,  104,   35,
 /*   660 */   106,  107,   38,    7,    8,    9,   10,   11,   12,   13,
 /*   670 */    14,   15,   16,   17,   18,   19,   20,   21,   22,  131,
 /*   680 */   131,  131,   18,   19,  131,  131,   93,   31,   24,   25,
 /*   690 */    26,   35,   93,  131,   38,   31,  103,  104,  105,   35,
 /*   700 */   131,   37,  103,  104,  105,   41,   42,   43,   44,   45,
 /*   710 */    46,   47,   48,   49,   18,   19,  131,  131,  131,   93,
 /*   720 */    24,   25,   26,  131,   93,   93,  131,   31,   32,    0,
 /*   730 */   104,   35,   93,   37,  108,  104,  104,   41,   42,   43,
 /*   740 */    44,   45,  131,  104,   48,   49,  131,   13,   14,   15,
 /*   750 */    16,   17,   18,   19,   20,   21,   22,   28,  131,   30,
 /*   760 */     5,  131,   33,  131,  131,   31,   93,   93,  131,   35,
 /*   770 */   131,  131,   38,   18,   19,   46,   47,  104,  104,   24,
 /*   780 */    25,   26,   48,   49,   93,  131,   31,  131,  131,    5,
 /*   790 */    35,  131,   37,   93,  131,  104,   41,   42,   43,   44,
 /*   800 */    45,   93,   18,   19,  104,  131,  106,  107,   24,   25,
 /*   810 */    26,  131,  104,  131,  131,   31,  108,  131,  131,   35,
 /*   820 */   131,   37,  131,   93,   69,   41,   42,   43,   44,   45,
 /*   830 */    93,   93,   93,  131,  104,  131,  106,  107,   18,   19,
 /*   840 */   131,  104,  104,  104,   24,   25,   26,  108,  131,   93,
 /*   850 */   131,   31,   32,   69,  131,   35,   93,   37,  131,   39,
 /*   860 */   104,   41,   42,   43,   44,   45,  131,  104,   93,   93,
 /*   870 */    18,   19,  131,  131,   93,   93,   24,   25,   26,  104,
 /*   880 */   104,  106,  107,   31,  108,  104,  104,   35,  131,   37,
 /*   890 */   108,   93,  131,   41,   42,   43,   44,   45,  131,  131,
 /*   900 */    48,   49,  104,   13,   14,   15,   16,   17,   18,   19,
 /*   910 */    20,   21,   22,  131,   18,   19,   20,   21,   22,   93,
 /*   920 */   131,   31,   93,  131,  131,   35,   36,   31,   38,  131,
 /*   930 */   104,   35,  131,  104,   38,   13,   14,   15,   16,   17,
 /*   940 */    18,   19,   20,   21,   22,  131,  131,   93,  131,  131,
 /*   950 */    93,  131,  131,   31,   32,   93,  131,   35,  104,  131,
 /*   960 */    38,  104,  108,  131,  131,  131,  104,   13,   14,   15,
 /*   970 */    16,   17,   18,   19,   20,   21,   22,  131,  131,  131,
 /*   980 */    93,  131,  131,  131,  131,   31,  131,   18,   19,   35,
 /*   990 */    36,  104,   38,   24,   25,   26,   93,  131,   93,  131,
 /*  1000 */    31,  131,  131,  131,   35,  131,   37,  104,   39,  104,
 /*  1010 */    41,   42,   43,   44,   45,  131,  131,  131,   13,   14,
 /*  1020 */    15,   16,   17,   18,   19,   20,   21,   22,  131,  131,
 /*  1030 */    93,  131,  131,  131,  131,  131,   31,  131,  131,  131,
 /*  1040 */    35,  104,  131,   38,  131,  108,  131,  131,  131,  131,
 /*  1050 */    13,   14,   15,   16,   17,   18,   19,   20,   21,   22,
 /*  1060 */   131,  131,  131,  131,  131,  131,  131,  131,   31,  131,
 /*  1070 */    18,   19,   35,  131,  131,   38,   24,   25,   26,  131,
 /*  1080 */   131,  131,  131,   31,  131,  131,  131,   35,  131,   37,
 /*  1090 */   131,  131,  131,   41,   42,   43,   44,   45,  131,  131,
 /*  1100 */   131,  131,   18,   19,  131,  131,  131,  131,   24,   25,
 /*  1110 */    26,    1,    2,  131,  131,   31,  131,  131,  131,   35,
 /*  1120 */   131,   37,  131,    1,    2,   41,   42,   43,   44,   45,
 /*  1130 */    14,   15,   16,   17,   18,   19,   20,   21,   22,  131,
 /*  1140 */   131,  131,  131,  131,  131,  131,  131,   31,  131,  131,
 /*  1150 */   131,   35,  131,  131,   38,  131,  131,  131,  131,  131,
 /*  1160 */    50,   51,   52,   53,   54,   55,   56,   57,   58,   59,
 /*  1170 */     1,  131,   50,   51,   52,   53,   54,   55,   56,   57,
 /*  1180 */    58,   59,   15,   16,   17,   18,   19,   20,   21,   22,
 /*  1190 */   131,  131,  131,  131,  131,  131,  131,  131,   31,  131,
 /*  1200 */   131,  131,   35,  131,  131,   38,  131,  131,  131,  131,
 /*  1210 */   131,  131,  131,  131,  131,  131,  131,  131,  131,   50,
 /*  1220 */    51,   52,   53,   54,   55,   56,   57,   58,   59,  131,
 /*  1230 */    75,   76,   77,   78,   79,   80,   81,   82,   83,  131,
 /*  1240 */    79,  131,   81,   88,   79,  131,   81,  131,  131,  131,
 /*  1250 */   131,  131,   91,   92,   93,  131,   91,   92,   93,  131,
 /*  1260 */   131,  131,  131,  131,  131,  104,  131,  131,  131,  104,
 /*  1270 */   109,  110,  131,  131,  109,  110,  131,  131,  131,  131,
 /*  1280 */   131,  120,  121,  131,  131,  120,
};
#define YY_SHIFT_USE_DFLT (-27)
#define YY_SHIFT_COUNT (224)
#define YY_SHIFT_MIN   (-26)
#define YY_SHIFT_MAX   (1169)
static const short yy_shift_ofst[] = {
 /*     0 */   -27,  500,  439,  561,  561,  561,  561,  561,  561,  561,
 /*    10 */   664,  729,  664,  696,  852,  820,  969,  969,  969,  969,
 /*    20 */  1052, 1052,  755,  755,  755,  755,  784,  784,  755,  755,
 /*    30 */   755,  755,  969, 1052, 1052, 1052, 1084, 1052, 1052, 1052,
 /*    40 */   530, 1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052,
 /*    50 */  1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052,
 /*    60 */  1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052, 1052,
 /*    70 */  1052, 1052, 1052, 1052, 1052, 1052, 1052,  520,  535,  535,
 /*    80 */   520,  520,  535,  535,  535,  533,  518,  518,  624,  656,
 /*    90 */   734,  954,  922,  890, 1005, 1005, 1037, 1005, 1005, 1005,
 /*   100 */  1005, 1005, 1005, 1005, 1005, 1005, 1005, 1005, 1005, 1005,
 /*   110 */  1005, 1005, 1005, 1005, 1005, 1005, 1005,  519, 1122, 1110,
 /*   120 */  1116, 1169, 1167,  473,  896,  896,  440,  440,   41,  525,
 /*   130 */   506,  464,    3,    0,  -26,  -26,  -26,  -26,  -26,  -26,
 /*   140 */   161,   99,   28,   67,  111,   84,   61,  149,   56,   16,
 /*   150 */   366,  498,  495,  504,  499,  485,  490,  513,  483,  482,
 /*   160 */   469,  438,  448,  366,  366,  366,  425,  465,  445,  414,
 /*   170 */   437,  418,  441,  412,  405,  397,  404,  399,  375,  382,
 /*   180 */   380,  368,  370,  367,  348,  355,  383,  350,  349,  366,
 /*   190 */   328,  338,  249,  322,  314,  311,  305,  283,  308,  304,
 /*   200 */   277,  249,  238,  200,  280,  272,  260,  259,  254,  222,
 /*   210 */   210,  209,  205,  211,  185,  169,  168,  155,  123,  108,
 /*   220 */   118,  107,   80,   22,    7,
};
#define YY_REDUCE_USE_DFLT (-93)
#define YY_REDUCE_COUNT (87)
#define YY_REDUCE_MIN   (-92)
#define YY_REDUCE_MAX   (1165)
static const short yy_reduce_ofst[] = {
 /*     0 */   113,  329,  279,  229,  179,  129,   79,   29,  -21,  -71,
 /*    10 */  1161, 1155, 1165,  491,  -91,  775,  730,  700,  554,  447,
 /*    20 */   599,  593,  937,  854,  782,  776,  739,  708,  626,  522,
 /*    30 */   489,  326,   39,  291,  241,  191,   26,  141,   91,   -9,
 /*    40 */   -34,  905,  903,  887,  862,  857,  829,  826,  798,  781,
 /*    50 */   763,  756,  738,  737,  691,  674,  673,  639,  632,  631,
 /*    60 */   419,  339,  289,  258,  239,  226,  208,  189,  176,  164,
 /*    70 */   158,  139,  126,  114,   89,   76,   64,  -92,   34,  509,
 /*    80 */   471,  461,  479,  463,  457,  455,  466,  450,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   327,  491,  491,  491,  491,  491,  491,  491,  491,  491,
 /*    10 */   471,  494,  494,  494,  494,  494,  390,  390,  390,  390,
 /*    20 */   379,  379,  494,  494,  494,  494,  494,  494,  494,  494,
 /*    30 */   494,  494,  494,  494,  494,  494,  494,  494,  494,  494,
 /*    40 */   459,  494,  494,  494,  494,  494,  494,  494,  494,  494,
 /*    50 */   494,  494,  494,  494,  494,  494,  494,  494,  494,  494,
 /*    60 */   494,  494,  494,  494,  494,  494,  494,  494,  494,  494,
 /*    70 */   494,  494,  494,  494,  494,  494,  494,  494,  373,  494,
 /*    80 */   493,  492,  494,  494,  494,  494,  494,  494,  415,  415,
 /*    90 */   494,  494,  494,  494,  440,  438,  494,  451,  450,  449,
 /*   100 */   448,  447,  446,  445,  444,  443,  442,  436,  422,  421,
 /*   110 */   420,  419,  418,  417,  377,  386,  388,  383,  385,  384,
 /*   120 */   410,  434,  411,  409,  408,  407,  403,  402,  494,  494,
 /*   130 */   494,  494,  494,  494,  414,  413,  412,  406,  405,  404,
 /*   140 */   427,  494,  494,  494,  494,  494,  427,  494,  383,  394,
 /*   150 */   429,  365,  494,  494,  494,  494,  494,  470,  494,  494,
 /*   160 */   494,  458,  494,  437,  430,  428,  494,  494,  494,  494,
 /*   170 */   494,  494,  424,  494,  494,  494,  494,  494,  494,  494,
 /*   180 */   494,  494,  494,  494,  494,  494,  391,  382,  494,  380,
 /*   190 */   494,  494,  369,  494,  394,  494,  383,  394,  494,  494,
 /*   200 */   494,  494,  494,  494,  494,  494,  494,  494,  494,  494,
 /*   210 */   494,  494,  494,  374,  338,  494,  494,  494,  494,  337,
 /*   220 */   494,  494,  494,  494,  494,  366,  350,  460,  490,  489,
 /*   230 */   488,  484,  483,  482,  481,  480,  479,  478,  477,  476,
 /*   240 */   473,  472,  475,  474,  469,  468,  467,  466,  465,  464,
 /*   250 */   463,  462,  461,  457,  456,  455,  454,  453,  452,  435,
 /*   260 */   441,  439,  392,  393,  396,  397,  487,  485,  426,  425,
 /*   270 */   423,  416,  486,  401,  400,  399,  398,  389,  387,  378,
 /*   280 */   375,  370,  395,  385,  384,  382,  381,  368,  367,  364,
 /*   290 */   363,  362,  361,  360,  359,  358,  376,  357,  356,  355,
 /*   300 */   354,  353,  352,  351,  349,  348,  347,  345,  346,  344,
 /*   310 */   343,  342,  341,  339,  372,  371,  340,  336,  335,  334,
 /*   320 */   333,  332,  331,  330,  329,  328,
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
  "$",             "ASSIGN",        "COMMA",         "LOR",         
  "LAND",          "LNOT",          "DOUBLE_LNOT",   "EQ",          
  "LE",            "LT",            "GE",            "GT",          
  "NE",            "BITOR",         "BITXOR",        "BITAND",      
  "LSHIFT",        "RSHIFT",        "PLUS",          "MINUS",       
  "DIVIDE",        "MULTIPLY",      "MOD",           "UNARY",       
  "BITNOT",        "NUMBER",        "NAME",          "SEMICOLON",   
  "IMPORT",        "AS",            "FUNCTION",      "LPAREN",      
  "RPAREN",        "LBRACKET",      "RBRACKET",      "LSQBRACKET",  
  "RSQBRACKET",    "KILLS",         "PERIOD",        "STRING",      
  "FUNCCALL",      "L2V",           "MAPSTRING",     "UNIT",        
  "SWITCH",        "LOCATION",      "VAR",           "CONST",       
  "INC",           "DEC",           "IADD",          "ISUB",        
  "IMUL",          "IDIV",          "IMOD",          "ILSH",        
  "IRSH",          "IBND",          "IBOR",          "IBXR",        
  "IF",            "ELSE",          "WHILE",         "FOR",         
  "FOREACH",       "COLON",         "CONTINUE",      "BREAK",       
  "RETURN",        "CONDITIONNAME",  "ACTIONNAME",    "error",       
  "nt",            "program",       "chunks",        "chunk",       
  "import_chunk",  "fdef_chunk",    "fdecl_chunk",   "vdef_stmt",   
  "vdefAssign_global_stmt",  "cdef_stmt",     "blockStmt",     "fdef_header", 
  "nameList",      "stmt",          "bodyStmt",      "return_stmt", 
  "lbracket",      "rbracket",      "bodyStmtList",  "vdefAssign_stmt",
  "assign_stmt",   "funcexpr",      "actionStmt",    "if_stmt",     
  "while_stmt",    "for_stmt",      "foreach_stmt",  "continue_stmt",
  "break_stmt",    "numList_nonEmpty",  "nameList_nonEmpty",  "exprList_nonEmpty",
  "expr",          "exprList",      "fArgs_nonEmpty",  "fArgs",       
  "lexpr",         "lvalue",        "lvalueList_nonEmpty",  "if_start",    
  "if_header",     "if_block",      "elif_start",    "elif_header", 
  "else_header",   "while_start",   "while_header",  "for_opener",  
  "for_init_stmt_nonEmpty",  "for_init_stmt",  "for_action_stmt_nonEmpty",  "for_header1", 
  "for_header2",   "for_header",    "foreach_opener",  "foreach_header",
  "action",        "actions",       "actionStmt_start",
};
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *const yyRuleName[] = {
 /*   0 */ "program ::= chunks",
 /*   1 */ "chunks ::=",
 /*   2 */ "chunks ::= chunks chunk",
 /*   3 */ "chunk ::= import_chunk SEMICOLON",
 /*   4 */ "chunk ::= fdef_chunk",
 /*   5 */ "chunk ::= fdecl_chunk",
 /*   6 */ "chunk ::= vdef_stmt SEMICOLON",
 /*   7 */ "chunk ::= vdefAssign_global_stmt SEMICOLON",
 /*   8 */ "chunk ::= cdef_stmt SEMICOLON",
 /*   9 */ "chunk ::= blockStmt",
 /*  10 */ "import_chunk ::= IMPORT NAME AS NAME",
 /*  11 */ "import_chunk ::= IMPORT NAME",
 /*  12 */ "fdef_header ::= FUNCTION NAME LPAREN nameList RPAREN",
 /*  13 */ "fdef_chunk ::= fdef_header stmt",
 /*  14 */ "fdecl_chunk ::= FUNCTION NAME LPAREN nameList RPAREN SEMICOLON",
 /*  15 */ "stmt ::= error SEMICOLON",
 /*  16 */ "stmt ::= bodyStmt",
 /*  17 */ "stmt ::= return_stmt SEMICOLON",
 /*  18 */ "lbracket ::= LBRACKET",
 /*  19 */ "rbracket ::= RBRACKET",
 /*  20 */ "blockStmt ::= lbracket RBRACKET",
 /*  21 */ "blockStmt ::= lbracket return_stmt SEMICOLON rbracket",
 /*  22 */ "blockStmt ::= lbracket bodyStmtList rbracket",
 /*  23 */ "blockStmt ::= lbracket bodyStmtList return_stmt SEMICOLON rbracket",
 /*  24 */ "blockStmt ::= lbracket error RBRACKET",
 /*  25 */ "bodyStmt ::= blockStmt",
 /*  26 */ "bodyStmt ::= SEMICOLON",
 /*  27 */ "bodyStmt ::= vdef_stmt SEMICOLON",
 /*  28 */ "bodyStmt ::= vdefAssign_stmt SEMICOLON",
 /*  29 */ "bodyStmt ::= cdef_stmt SEMICOLON",
 /*  30 */ "bodyStmt ::= assign_stmt SEMICOLON",
 /*  31 */ "bodyStmt ::= funcexpr SEMICOLON",
 /*  32 */ "bodyStmt ::= actionStmt",
 /*  33 */ "bodyStmt ::= if_stmt",
 /*  34 */ "bodyStmt ::= while_stmt",
 /*  35 */ "bodyStmt ::= for_stmt",
 /*  36 */ "bodyStmt ::= foreach_stmt",
 /*  37 */ "bodyStmt ::= continue_stmt SEMICOLON",
 /*  38 */ "bodyStmt ::= break_stmt SEMICOLON",
 /*  39 */ "bodyStmtList ::= error",
 /*  40 */ "bodyStmtList ::= bodyStmt",
 /*  41 */ "bodyStmtList ::= bodyStmtList bodyStmt",
 /*  42 */ "bodyStmtList ::= bodyStmtList error",
 /*  43 */ "numList_nonEmpty ::= NUMBER",
 /*  44 */ "numList_nonEmpty ::= numList_nonEmpty COMMA NUMBER",
 /*  45 */ "nameList_nonEmpty ::= NAME",
 /*  46 */ "nameList_nonEmpty ::= nameList_nonEmpty COMMA NAME",
 /*  47 */ "nameList ::=",
 /*  48 */ "nameList ::= nameList_nonEmpty",
 /*  49 */ "exprList_nonEmpty ::= funcexpr LSQBRACKET LSQBRACKET numList_nonEmpty RSQBRACKET RSQBRACKET",
 /*  50 */ "expr ::= funcexpr LSQBRACKET LSQBRACKET NUMBER RSQBRACKET RSQBRACKET",
 /*  51 */ "exprList_nonEmpty ::= expr",
 /*  52 */ "exprList_nonEmpty ::= exprList_nonEmpty COMMA exprList_nonEmpty",
 /*  53 */ "exprList ::=",
 /*  54 */ "exprList ::= exprList_nonEmpty",
 /*  55 */ "expr ::= NUMBER",
 /*  56 */ "expr ::= KILLS",
 /*  57 */ "expr ::= NAME",
 /*  58 */ "expr ::= expr PERIOD NAME",
 /*  59 */ "expr ::= expr LSQBRACKET expr RSQBRACKET",
 /*  60 */ "fArgs_nonEmpty ::= expr",
 /*  61 */ "fArgs_nonEmpty ::= STRING",
 /*  62 */ "fArgs_nonEmpty ::= NAME ASSIGN expr",
 /*  63 */ "fArgs_nonEmpty ::= fArgs_nonEmpty COMMA fArgs_nonEmpty",
 /*  64 */ "fArgs ::=",
 /*  65 */ "fArgs ::= fArgs_nonEmpty",
 /*  66 */ "funcexpr ::= NAME LPAREN fArgs RPAREN",
 /*  67 */ "funcexpr ::= expr LPAREN fArgs RPAREN",
 /*  68 */ "expr ::= funcexpr",
 /*  69 */ "expr ::= LPAREN expr RPAREN",
 /*  70 */ "expr ::= LSQBRACKET exprList RSQBRACKET",
 /*  71 */ "expr ::= L2V LPAREN lexpr RPAREN",
 /*  72 */ "expr ::= MAPSTRING LPAREN STRING RPAREN",
 /*  73 */ "expr ::= UNIT LPAREN STRING RPAREN",
 /*  74 */ "expr ::= SWITCH LPAREN STRING RPAREN",
 /*  75 */ "expr ::= LOCATION LPAREN STRING RPAREN",
 /*  76 */ "expr ::= expr PLUS expr",
 /*  77 */ "expr ::= expr MINUS expr",
 /*  78 */ "expr ::= expr MULTIPLY expr",
 /*  79 */ "expr ::= expr DIVIDE expr",
 /*  80 */ "expr ::= expr MOD expr",
 /*  81 */ "expr ::= expr LSHIFT expr",
 /*  82 */ "expr ::= expr RSHIFT expr",
 /*  83 */ "expr ::= expr BITAND expr",
 /*  84 */ "expr ::= expr BITOR expr",
 /*  85 */ "expr ::= expr BITXOR expr",
 /*  86 */ "expr ::= PLUS expr",
 /*  87 */ "expr ::= MINUS expr",
 /*  88 */ "expr ::= BITNOT expr",
 /*  89 */ "lexpr ::= expr",
 /*  90 */ "lexpr ::= LPAREN lexpr RPAREN",
 /*  91 */ "lexpr ::= expr EQ expr",
 /*  92 */ "lexpr ::= expr NE expr",
 /*  93 */ "lexpr ::= expr LE expr",
 /*  94 */ "lexpr ::= expr LT expr",
 /*  95 */ "lexpr ::= expr GE expr",
 /*  96 */ "lexpr ::= expr GT expr",
 /*  97 */ "lexpr ::= lexpr LAND lexpr",
 /*  98 */ "lexpr ::= lexpr LOR lexpr",
 /*  99 */ "lexpr ::= LNOT lexpr",
 /* 100 */ "lexpr ::= LNOT LNOT lexpr",
 /* 101 */ "vdef_stmt ::= VAR nameList_nonEmpty",
 /* 102 */ "vdefAssign_stmt ::= VAR nameList_nonEmpty ASSIGN exprList_nonEmpty",
 /* 103 */ "vdefAssign_global_stmt ::= VAR nameList_nonEmpty ASSIGN exprList_nonEmpty",
 /* 104 */ "cdef_stmt ::= CONST nameList_nonEmpty ASSIGN exprList_nonEmpty",
 /* 105 */ "lvalue ::= NAME",
 /* 106 */ "lvalue ::= expr LSQBRACKET expr RSQBRACKET",
 /* 107 */ "lvalue ::= expr PERIOD NAME",
 /* 108 */ "lvalueList_nonEmpty ::= lvalue",
 /* 109 */ "lvalueList_nonEmpty ::= lvalueList_nonEmpty COMMA lvalue",
 /* 110 */ "assign_stmt ::= lvalue ASSIGN expr",
 /* 111 */ "assign_stmt ::= lvalueList_nonEmpty ASSIGN exprList_nonEmpty",
 /* 112 */ "assign_stmt ::= INC expr",
 /* 113 */ "assign_stmt ::= expr INC",
 /* 114 */ "assign_stmt ::= DEC expr",
 /* 115 */ "assign_stmt ::= expr DEC",
 /* 116 */ "assign_stmt ::= lvalue IADD expr",
 /* 117 */ "assign_stmt ::= lvalue ISUB expr",
 /* 118 */ "assign_stmt ::= lvalue IMUL expr",
 /* 119 */ "assign_stmt ::= lvalue IDIV expr",
 /* 120 */ "assign_stmt ::= lvalue IMOD expr",
 /* 121 */ "assign_stmt ::= lvalue ILSH expr",
 /* 122 */ "assign_stmt ::= lvalue IRSH expr",
 /* 123 */ "assign_stmt ::= lvalue IBND expr",
 /* 124 */ "assign_stmt ::= lvalue IBOR expr",
 /* 125 */ "assign_stmt ::= lvalue IBXR expr",
 /* 126 */ "if_start ::= IF",
 /* 127 */ "if_header ::= if_start LPAREN lexpr RPAREN",
 /* 128 */ "if_block ::= if_header stmt",
 /* 129 */ "elif_start ::= ELSE IF",
 /* 130 */ "elif_header ::= elif_start LPAREN lexpr RPAREN",
 /* 131 */ "if_block ::= if_block elif_header stmt",
 /* 132 */ "else_header ::= ELSE",
 /* 133 */ "if_stmt ::= if_block",
 /* 134 */ "if_stmt ::= if_block else_header stmt",
 /* 135 */ "while_start ::= WHILE",
 /* 136 */ "while_header ::= while_start LPAREN lexpr RPAREN",
 /* 137 */ "while_stmt ::= while_header stmt",
 /* 138 */ "for_opener ::= FOR LPAREN",
 /* 139 */ "for_init_stmt_nonEmpty ::= vdef_stmt",
 /* 140 */ "for_init_stmt_nonEmpty ::= vdefAssign_stmt",
 /* 141 */ "for_init_stmt_nonEmpty ::= cdef_stmt",
 /* 142 */ "for_init_stmt_nonEmpty ::= assign_stmt",
 /* 143 */ "for_init_stmt_nonEmpty ::= for_init_stmt_nonEmpty COMMA for_init_stmt_nonEmpty",
 /* 144 */ "for_init_stmt ::= for_init_stmt_nonEmpty",
 /* 145 */ "for_init_stmt ::=",
 /* 146 */ "for_action_stmt_nonEmpty ::= assign_stmt",
 /* 147 */ "for_action_stmt_nonEmpty ::= for_action_stmt_nonEmpty COMMA for_action_stmt_nonEmpty",
 /* 148 */ "for_header1 ::= for_opener for_init_stmt SEMICOLON",
 /* 149 */ "for_header2 ::= for_header1 lexpr SEMICOLON",
 /* 150 */ "for_header ::= for_header2 for_action_stmt_nonEmpty RPAREN",
 /* 151 */ "for_header ::= for_header2 RPAREN",
 /* 152 */ "for_stmt ::= for_header stmt",
 /* 153 */ "foreach_opener ::= FOREACH LPAREN",
 /* 154 */ "foreach_header ::= foreach_opener nameList_nonEmpty COLON exprList_nonEmpty RPAREN",
 /* 155 */ "foreach_stmt ::= foreach_header stmt",
 /* 156 */ "continue_stmt ::= CONTINUE",
 /* 157 */ "break_stmt ::= BREAK",
 /* 158 */ "return_stmt ::= RETURN exprList",
 /* 159 */ "lexpr ::= CONDITIONNAME LPAREN fArgs RPAREN",
 /* 160 */ "lexpr ::= KILLS LPAREN fArgs RPAREN",
 /* 161 */ "lexpr ::= CONDITIONNAME LPAREN RPAREN",
 /* 162 */ "action ::= ACTIONNAME LPAREN fArgs RPAREN SEMICOLON",
 /* 163 */ "actions ::= action action",
 /* 164 */ "actions ::= actions action",
 /* 165 */ "actionStmt_start ::=",
 /* 166 */ "actionStmt ::= actionStmt_start action",
 /* 167 */ "actionStmt ::= actionStmt_start actions",
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
    case 72: /* nt */
{
#line 35 "parser\\epparser.lemon"
 delete (yypminor->yy0); 
#line 894 "parser\\epparser.c"
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
  { 73, 1 },
  { 74, 0 },
  { 74, 2 },
  { 75, 2 },
  { 75, 1 },
  { 75, 1 },
  { 75, 2 },
  { 75, 2 },
  { 75, 2 },
  { 75, 1 },
  { 76, 4 },
  { 76, 2 },
  { 83, 5 },
  { 77, 2 },
  { 78, 6 },
  { 85, 2 },
  { 85, 1 },
  { 85, 2 },
  { 88, 1 },
  { 89, 1 },
  { 82, 2 },
  { 82, 4 },
  { 82, 3 },
  { 82, 5 },
  { 82, 3 },
  { 86, 1 },
  { 86, 1 },
  { 86, 2 },
  { 86, 2 },
  { 86, 2 },
  { 86, 2 },
  { 86, 2 },
  { 86, 1 },
  { 86, 1 },
  { 86, 1 },
  { 86, 1 },
  { 86, 1 },
  { 86, 2 },
  { 86, 2 },
  { 90, 1 },
  { 90, 1 },
  { 90, 2 },
  { 90, 2 },
  { 101, 1 },
  { 101, 3 },
  { 102, 1 },
  { 102, 3 },
  { 84, 0 },
  { 84, 1 },
  { 103, 6 },
  { 104, 6 },
  { 103, 1 },
  { 103, 3 },
  { 105, 0 },
  { 105, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 1 },
  { 104, 3 },
  { 104, 4 },
  { 106, 1 },
  { 106, 1 },
  { 106, 3 },
  { 106, 3 },
  { 107, 0 },
  { 107, 1 },
  { 93, 4 },
  { 93, 4 },
  { 104, 1 },
  { 104, 3 },
  { 104, 3 },
  { 104, 4 },
  { 104, 4 },
  { 104, 4 },
  { 104, 4 },
  { 104, 4 },
  { 104, 3 },
  { 104, 3 },
  { 104, 3 },
  { 104, 3 },
  { 104, 3 },
  { 104, 3 },
  { 104, 3 },
  { 104, 3 },
  { 104, 3 },
  { 104, 3 },
  { 104, 2 },
  { 104, 2 },
  { 104, 2 },
  { 108, 1 },
  { 108, 3 },
  { 108, 3 },
  { 108, 3 },
  { 108, 3 },
  { 108, 3 },
  { 108, 3 },
  { 108, 3 },
  { 108, 3 },
  { 108, 3 },
  { 108, 2 },
  { 108, 3 },
  { 79, 2 },
  { 91, 4 },
  { 80, 4 },
  { 81, 4 },
  { 109, 1 },
  { 109, 4 },
  { 109, 3 },
  { 110, 1 },
  { 110, 3 },
  { 92, 3 },
  { 92, 3 },
  { 92, 2 },
  { 92, 2 },
  { 92, 2 },
  { 92, 2 },
  { 92, 3 },
  { 92, 3 },
  { 92, 3 },
  { 92, 3 },
  { 92, 3 },
  { 92, 3 },
  { 92, 3 },
  { 92, 3 },
  { 92, 3 },
  { 92, 3 },
  { 111, 1 },
  { 112, 4 },
  { 113, 2 },
  { 114, 2 },
  { 115, 4 },
  { 113, 3 },
  { 116, 1 },
  { 95, 1 },
  { 95, 3 },
  { 117, 1 },
  { 118, 4 },
  { 96, 2 },
  { 119, 2 },
  { 120, 1 },
  { 120, 1 },
  { 120, 1 },
  { 120, 1 },
  { 120, 3 },
  { 121, 1 },
  { 121, 0 },
  { 122, 1 },
  { 122, 3 },
  { 123, 3 },
  { 124, 3 },
  { 125, 3 },
  { 125, 2 },
  { 97, 2 },
  { 126, 2 },
  { 127, 5 },
  { 98, 2 },
  { 99, 1 },
  { 100, 1 },
  { 87, 2 },
  { 108, 4 },
  { 108, 4 },
  { 108, 3 },
  { 128, 5 },
  { 129, 2 },
  { 129, 2 },
  { 130, 0 },
  { 94, 2 },
  { 94, 2 },
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
      case 9: /* chunk ::= blockStmt */
#line 70 "parser\\epparser.lemon"
{
    throw_error(48993, "Misplaced block statement");
}
#line 1359 "parser\\epparser.c"
        break;
      case 10: /* import_chunk ::= IMPORT NAME AS NAME */
#line 76 "parser\\epparser.lemon"
{
    if(!ps->closure.defModule(yymsp[0].minor.yy0->data)) {
        throw_error(6754, "Importing already-declared module " + yymsp[0].minor.yy0->data, yymsp[0].minor.yy0->line);
    }
    ps->gen << "import _" << yymsp[-2].minor.yy0->data << " as " << yymsp[0].minor.yy0->data << std::endl;
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 1370 "parser\\epparser.c"
        break;
      case 11: /* import_chunk ::= IMPORT NAME */
#line 84 "parser\\epparser.lemon"
{
    if(!ps->closure.defModule(yymsp[0].minor.yy0->data)) {
        throw_error(6754, "Importing already-declared module " + yymsp[0].minor.yy0->data, yymsp[0].minor.yy0->line);
    }
    ps->gen << "import _" << yymsp[0].minor.yy0->data << " as " << yymsp[0].minor.yy0->data << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1381 "parser\\epparser.c"
        break;
      case 12: /* fdef_header ::= FUNCTION NAME LPAREN nameList RPAREN */
#line 93 "parser\\epparser.lemon"
{
    // Preprocess yymsp[-3].minor.yy0
    funcNamePreprocess(yymsp[-3].minor.yy0->data);
    if(!ps->closure.defFunction(yymsp[-3].minor.yy0->data)) {
        throw_error(4495, "Duplicate function " + yymsp[-3].minor.yy0->data, yymsp[-3].minor.yy0->line);
    }

    ps->gen << "@EUDFunc" << std::endl;
    ps->gen << "def " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data << "):" << std::endl;
    ps->gen.indent();

    ps->closure.pushScope();

    // Register variables.
    commaListIter(yymsp[-1].minor.yy0->data, [&](std::string& varname) {
        if(!ps->closure.defVariable(varname)) {
            throw_error(196, ("Redeclaration of variable \'" + varname + "\'"), yymsp[-1].minor.yy0->line);
        }
    });

    tmpIndex = 1;
    delete yymsp[-3].minor.yy0;
    delete yymsp[-1].minor.yy0;
}
#line 1409 "parser\\epparser.c"
        break;
      case 13: /* fdef_chunk ::= fdef_header stmt */
      case 155: /* foreach_stmt ::= foreach_header stmt */ yytestcase(yyruleno==155);
#line 118 "parser\\epparser.lemon"
{
    ps->gen.unindent(true);
    ps->closure.popScope();
}
#line 1418 "parser\\epparser.c"
        break;
      case 14: /* fdecl_chunk ::= FUNCTION NAME LPAREN nameList RPAREN SEMICOLON */
#line 123 "parser\\epparser.lemon"
{
    // Preprocess yymsp[-4].minor.yy0
    funcNamePreprocess(yymsp[-4].minor.yy0->data);
    if(!ps->closure.declareFunction(yymsp[-4].minor.yy0->data)) {
        throw_error(72461, "Declaring function with non-function yymsp[-4].minor.yy0 " + yymsp[-4].minor.yy0->data, yymsp[-4].minor.yy0->line);
    }
}
#line 1429 "parser\\epparser.c"
        break;
      case 15: /* stmt ::= error SEMICOLON */
#line 132 "parser\\epparser.lemon"
{ throw_error(6974, "Error while parsing statement", yymsp[0].minor.yy0->line); delete yymsp[0].minor.yy0; }
#line 1434 "parser\\epparser.c"
        break;
      case 18: /* lbracket ::= LBRACKET */
#line 138 "parser\\epparser.lemon"
{ ps->closure.pushScope(); }
#line 1439 "parser\\epparser.c"
        break;
      case 19: /* rbracket ::= RBRACKET */
#line 139 "parser\\epparser.lemon"
{ ps->closure.popScope(); }
#line 1444 "parser\\epparser.c"
        break;
      case 20: /* blockStmt ::= lbracket RBRACKET */
#line 141 "parser\\epparser.lemon"
{
    ps->gen << "pass" << std::endl;
    ps->closure.popScope();
}
#line 1452 "parser\\epparser.c"
        break;
      case 24: /* blockStmt ::= lbracket error RBRACKET */
#line 148 "parser\\epparser.lemon"
{
    throw_error(6298, "Block not terminated properly.", yymsp[0].minor.yy0->line);
    ps->gen << "pass" << std::endl;
    ps->closure.popScope();
    delete yymsp[0].minor.yy0;
}
#line 1462 "parser\\epparser.c"
        break;
      case 31: /* bodyStmt ::= funcexpr SEMICOLON */
#line 161 "parser\\epparser.lemon"
{ ps->gen << yymsp[-1].minor.yy0->data << std::endl; }
#line 1467 "parser\\epparser.c"
        break;
      case 39: /* bodyStmtList ::= error */
#line 171 "parser\\epparser.lemon"
{
    throw_error(8510, "Incomplete statement");
    ps->gen << "pass" << std::endl;
}
#line 1475 "parser\\epparser.c"
        break;
      case 42: /* bodyStmtList ::= bodyStmtList error */
#line 178 "parser\\epparser.lemon"
{
    throw_error(8510, "Incomplete statement");
}
#line 1482 "parser\\epparser.c"
        break;
      case 43: /* numList_nonEmpty ::= NUMBER */
      case 45: /* nameList_nonEmpty ::= NAME */ yytestcase(yyruleno==45);
      case 48: /* nameList ::= nameList_nonEmpty */ yytestcase(yyruleno==48);
      case 51: /* exprList_nonEmpty ::= expr */ yytestcase(yyruleno==51);
      case 54: /* exprList ::= exprList_nonEmpty */ yytestcase(yyruleno==54);
      case 55: /* expr ::= NUMBER */ yytestcase(yyruleno==55);
      case 60: /* fArgs_nonEmpty ::= expr */ yytestcase(yyruleno==60);
      case 61: /* fArgs_nonEmpty ::= STRING */ yytestcase(yyruleno==61);
      case 65: /* fArgs ::= fArgs_nonEmpty */ yytestcase(yyruleno==65);
      case 68: /* expr ::= funcexpr */ yytestcase(yyruleno==68);
      case 89: /* lexpr ::= expr */ yytestcase(yyruleno==89);
      case 100: /* lexpr ::= LNOT LNOT lexpr */ yytestcase(yyruleno==100);
      case 108: /* lvalueList_nonEmpty ::= lvalue */ yytestcase(yyruleno==108);
#line 184 "parser\\epparser.lemon"
{ yygotominor.yy0 = yymsp[0].minor.yy0; }
#line 1499 "parser\\epparser.c"
        break;
      case 44: /* numList_nonEmpty ::= numList_nonEmpty COMMA NUMBER */
      case 46: /* nameList_nonEmpty ::= nameList_nonEmpty COMMA NAME */ yytestcase(yyruleno==46);
      case 109: /* lvalueList_nonEmpty ::= lvalueList_nonEmpty COMMA lvalue */ yytestcase(yyruleno==109);
#line 185 "parser\\epparser.lemon"
{ yygotominor.yy0 = commaConcat(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1506 "parser\\epparser.c"
        break;
      case 47: /* nameList ::= */
      case 53: /* exprList ::= */ yytestcase(yyruleno==53);
      case 64: /* fArgs ::= */ yytestcase(yyruleno==64);
#line 188 "parser\\epparser.lemon"
{ yygotominor.yy0 = genEmpty(); }
#line 1513 "parser\\epparser.c"
        break;
      case 49: /* exprList_nonEmpty ::= funcexpr LSQBRACKET LSQBRACKET numList_nonEmpty RSQBRACKET RSQBRACKET */
#line 191 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "_SRET(" + yymsp[-5].minor.yy0->data + ", [" + yymsp[-2].minor.yy0->data + "])";
    delete yymsp[-5].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1522 "parser\\epparser.c"
        break;
      case 50: /* expr ::= funcexpr LSQBRACKET LSQBRACKET NUMBER RSQBRACKET RSQBRACKET */
#line 198 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-5].minor.yy0->data + "[" + yymsp[-2].minor.yy0->data + "]";
    delete yymsp[-5].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1531 "parser\\epparser.c"
        break;
      case 52: /* exprList_nonEmpty ::= exprList_nonEmpty COMMA exprList_nonEmpty */
#line 206 "parser\\epparser.lemon"
{ yygotominor.yy0 = new Token((yymsp[-2].minor.yy0->data) + ", " + (yymsp[0].minor.yy0->data), yymsp[0].minor.yy0); delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1536 "parser\\epparser.c"
        break;
      case 56: /* expr ::= KILLS */
#line 213 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = "4";
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1544 "parser\\epparser.c"
        break;
      case 57: /* expr ::= NAME */
#line 218 "parser\\epparser.lemon"
{
    checkIsRValue(yymsp[0].minor.yy0->data, yymsp[0].minor.yy0->line);
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1552 "parser\\epparser.c"
        break;
      case 58: /* expr ::= expr PERIOD NAME */
#line 223 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + "." + yymsp[0].minor.yy0->data;
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1561 "parser\\epparser.c"
        break;
      case 59: /* expr ::= expr LSQBRACKET expr RSQBRACKET */
#line 229 "parser\\epparser.lemon"
{
    yymsp[-3].minor.yy0->data = yymsp[-3].minor.yy0->data + "[" + yymsp[-1].minor.yy0->data + "]";
    delete yymsp[-1].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 1570 "parser\\epparser.c"
        break;
      case 62: /* fArgs_nonEmpty ::= NAME ASSIGN expr */
#line 238 "parser\\epparser.lemon"
{  // Keyword argument
    yymsp[0].minor.yy0->data = yymsp[-2].minor.yy0->data + "=" + yymsp[0].minor.yy0->data;
    yymsp[0].minor.yy0->type = TOKEN_TEMP;
    yygotominor.yy0 = yymsp[0].minor.yy0;
    delete yymsp[-2].minor.yy0;
}
#line 1580 "parser\\epparser.c"
        break;
      case 63: /* fArgs_nonEmpty ::= fArgs_nonEmpty COMMA fArgs_nonEmpty */
#line 245 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data;
    yymsp[0].minor.yy0->type = TOKEN_TEMP;
    yygotominor.yy0 = yymsp[0].minor.yy0;
    delete yymsp[-2].minor.yy0;
}
#line 1590 "parser\\epparser.c"
        break;
      case 66: /* funcexpr ::= NAME LPAREN fArgs RPAREN */
#line 255 "parser\\epparser.lemon"
{
    functionCalledInMultipleActions = true;

    // Preprocess yymsp[-3].minor.yy0
    funcNamePreprocess(yymsp[-3].minor.yy0->data);
    checkIsFunction(yymsp[-3].minor.yy0->data, yymsp[-3].minor.yy0->line);
    yymsp[-3].minor.yy0->data += "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 1603 "parser\\epparser.c"
        break;
      case 67: /* funcexpr ::= expr LPAREN fArgs RPAREN */
#line 265 "parser\\epparser.lemon"
{
    functionCalledInMultipleActions = true;

    // If calling function imported from another module, add f_ prefix to function yymsp[-3].minor.yy0.
    static std::regex prefixedFuncNameRegex("^[a-z][_a-zA-Z0-9]*");
    std::string& nameStr = yymsp[-3].minor.yy0->data;
    if(std::count(nameStr.begin(), nameStr.end(), '.') == 1) {
        size_t p = nameStr.find('.');
        std::string moduleName = nameStr.substr(0, p);
        std::string funcName = nameStr.substr(p + 1);
        if (closure->isModule(moduleName) && std::regex_match(funcName, prefixedFuncNameRegex)) {
            funcNamePreprocess(funcName);
            yymsp[-3].minor.yy0->data = moduleName + '.' + funcName;
        }
    }

    // Preprocess yymsp[-3].minor.yy0
    yymsp[-3].minor.yy0->data += "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 1627 "parser\\epparser.c"
        break;
      case 69: /* expr ::= LPAREN expr RPAREN */
      case 90: /* lexpr ::= LPAREN lexpr RPAREN */ yytestcase(yyruleno==90);
#line 289 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1636 "parser\\epparser.c"
        break;
      case 70: /* expr ::= LSQBRACKET exprList RSQBRACKET */
#line 294 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "EUDArray(FlattenList([" + yymsp[-1].minor.yy0->data + "]))";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1644 "parser\\epparser.c"
        break;
      case 71: /* expr ::= L2V LPAREN lexpr RPAREN */
#line 299 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "_L2V(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1652 "parser\\epparser.c"
        break;
      case 72: /* expr ::= MAPSTRING LPAREN STRING RPAREN */
#line 304 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetStringIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1660 "parser\\epparser.c"
        break;
      case 73: /* expr ::= UNIT LPAREN STRING RPAREN */
#line 309 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "EncodeUnit(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1668 "parser\\epparser.c"
        break;
      case 74: /* expr ::= SWITCH LPAREN STRING RPAREN */
#line 314 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "EncodeSwitch(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1676 "parser\\epparser.c"
        break;
      case 75: /* expr ::= LOCATION LPAREN STRING RPAREN */
#line 319 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetLocationIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1684 "parser\\epparser.c"
        break;
      case 76: /* expr ::= expr PLUS expr */
#line 325 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "+",  yymsp[0].minor.yy0); }
#line 1689 "parser\\epparser.c"
        break;
      case 77: /* expr ::= expr MINUS expr */
#line 326 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "-",  yymsp[0].minor.yy0); }
#line 1694 "parser\\epparser.c"
        break;
      case 78: /* expr ::= expr MULTIPLY expr */
#line 327 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "*",  yymsp[0].minor.yy0); }
#line 1699 "parser\\epparser.c"
        break;
      case 79: /* expr ::= expr DIVIDE expr */
#line 328 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "//", yymsp[0].minor.yy0); }
#line 1704 "parser\\epparser.c"
        break;
      case 80: /* expr ::= expr MOD expr */
#line 329 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "%",  yymsp[0].minor.yy0); }
#line 1709 "parser\\epparser.c"
        break;
      case 81: /* expr ::= expr LSHIFT expr */
#line 330 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "<<", yymsp[0].minor.yy0); }
#line 1714 "parser\\epparser.c"
        break;
      case 82: /* expr ::= expr RSHIFT expr */
#line 331 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, ">>", yymsp[0].minor.yy0); }
#line 1719 "parser\\epparser.c"
        break;
      case 83: /* expr ::= expr BITAND expr */
#line 332 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "&",  yymsp[0].minor.yy0); }
#line 1724 "parser\\epparser.c"
        break;
      case 84: /* expr ::= expr BITOR expr */
#line 333 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "|",  yymsp[0].minor.yy0); }
#line 1729 "parser\\epparser.c"
        break;
      case 85: /* expr ::= expr BITXOR expr */
#line 334 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "^",  yymsp[0].minor.yy0); }
#line 1734 "parser\\epparser.c"
        break;
      case 86: /* expr ::= PLUS expr */
#line 337 "parser\\epparser.lemon"
{ yymsp[0].minor.yy0->data = "+" + yymsp[0].minor.yy0->data; yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0); }
#line 1739 "parser\\epparser.c"
        break;
      case 87: /* expr ::= MINUS expr */
#line 338 "parser\\epparser.lemon"
{ yymsp[0].minor.yy0->data = "-" + yymsp[0].minor.yy0->data; yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0); }
#line 1744 "parser\\epparser.c"
        break;
      case 88: /* expr ::= BITNOT expr */
#line 339 "parser\\epparser.lemon"
{ yymsp[0].minor.yy0->data = "~" + yymsp[0].minor.yy0->data; yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0); }
#line 1749 "parser\\epparser.c"
        break;
      case 91: /* lexpr ::= expr EQ expr */
#line 349 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "==", yymsp[0].minor.yy0); }
#line 1754 "parser\\epparser.c"
        break;
      case 92: /* lexpr ::= expr NE expr */
#line 350 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "!=", yymsp[0].minor.yy0); }
#line 1759 "parser\\epparser.c"
        break;
      case 93: /* lexpr ::= expr LE expr */
#line 351 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "<=", yymsp[0].minor.yy0); }
#line 1764 "parser\\epparser.c"
        break;
      case 94: /* lexpr ::= expr LT expr */
#line 352 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "<",  yymsp[0].minor.yy0); }
#line 1769 "parser\\epparser.c"
        break;
      case 95: /* lexpr ::= expr GE expr */
#line 353 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, ">=", yymsp[0].minor.yy0); }
#line 1774 "parser\\epparser.c"
        break;
      case 96: /* lexpr ::= expr GT expr */
#line 354 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, ">" , yymsp[0].minor.yy0); }
#line 1779 "parser\\epparser.c"
        break;
      case 97: /* lexpr ::= lexpr LAND lexpr */
#line 357 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "[" + yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data + "]";
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1788 "parser\\epparser.c"
        break;
      case 98: /* lexpr ::= lexpr LOR lexpr */
#line 363 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "EUDOr(" + yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data + ")";
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1797 "parser\\epparser.c"
        break;
      case 99: /* lexpr ::= LNOT lexpr */
#line 369 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = "EUDNot([" + yymsp[0].minor.yy0->data + "])";
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0);
}
#line 1805 "parser\\epparser.c"
        break;
      case 101: /* vdef_stmt ::= VAR nameList_nonEmpty */
#line 379 "parser\\epparser.lemon"
{
    std::string& s = yymsp[0].minor.yy0->data;
    int varCount = std::count(s.begin(), s.end(), ',') + 1;

    // Register variables.
    commaListIter(s, [&](std::string& varname) {
        if(!ps->closure.defVariable(varname)) {
            throw_error(196, ("Redeclaration of variable \'" + varname + "\'"), yymsp[0].minor.yy0->line);
        }
    });

    if(varCount == 1) {
        ps->gen << s << " = EUDVariable()" << std::endl;
    }
    else {
        ps->gen << s << " = EUDCreateVariables(" << varCount << ")" << std::endl;
    }

    delete yymsp[0].minor.yy0;
}
#line 1829 "parser\\epparser.c"
        break;
      case 102: /* vdefAssign_stmt ::= VAR nameList_nonEmpty ASSIGN exprList_nonEmpty */
#line 400 "parser\\epparser.lemon"
{
    std::string& s = yymsp[-2].minor.yy0->data;
    int varCount = std::count(s.begin(), s.end(), ',') + 1;

    // Register variables.
    commaListIter(s, [&](std::string& varname) {
        if(!ps->closure.defVariable(varname)) {
            throw_error(7998, ("Redeclaration of variable \'" + varname + "\'"), yymsp[-2].minor.yy0->line);
        }
    });

    if(varCount == 1) {
        ps->gen << s << " = EUDVariable()" << std::endl;
        ps->gen << s << " << (" << yymsp[0].minor.yy0->data << ")" << std::endl;
    }
    else {
        ps->gen << s << " = _MVAR([" << yymsp[0].minor.yy0->data << "])" << std::endl;
    }

    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 1854 "parser\\epparser.c"
        break;
      case 103: /* vdefAssign_global_stmt ::= VAR nameList_nonEmpty ASSIGN exprList_nonEmpty */
#line 422 "parser\\epparser.lemon"
{
    std::string& s = yymsp[-2].minor.yy0->data;
    int varCount = std::count(s.begin(), s.end(), ',') + 1;

    // Register variables.
    commaListIter(s, [&](std::string& varname) {
        if(!ps->closure.defVariable(varname)) {
            throw_error(7998, ("Redeclaration of variable \'" + varname + "\'"), yymsp[-2].minor.yy0->line);
        }
    });

    if(varCount == 1) {
        ps->gen << s << " = EUDVariable(" << yymsp[0].minor.yy0->data << ")" << std::endl;
    }
    else {
        ps->gen << s << " = [EUDVariable(v) for v in FlattenList([" << yymsp[0].minor.yy0->data << "])]" << std::endl;
    }

    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 1878 "parser\\epparser.c"
        break;
      case 104: /* cdef_stmt ::= CONST nameList_nonEmpty ASSIGN exprList_nonEmpty */
#line 443 "parser\\epparser.lemon"
{
    std::string& s = yymsp[-2].minor.yy0->data;
    int nameCount = std::count(s.begin(), s.end(), ',') + 1;

    // Register constants.
    commaListIter(s, [&](std::string& constname) {
        if(!ps->closure.defConstant(constname)) {
            throw_error(7719, ("Redeclaration of constant \'" + constname + "\'"), yymsp[-2].minor.yy0->line);
        }
    });
    if(nameCount == 1) {
        ps->gen << s << " = " << yymsp[0].minor.yy0->data << std::endl;
    }
    else {
        ps->gen << s << " = List2Assignable([" << yymsp[0].minor.yy0->data << "])" << std::endl;
    }
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 1900 "parser\\epparser.c"
        break;
      case 105: /* lvalue ::= NAME */
#line 463 "parser\\epparser.lemon"
{
    checkIsVariable(yymsp[0].minor.yy0->data, yymsp[0].minor.yy0->line);
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1908 "parser\\epparser.c"
        break;
      case 106: /* lvalue ::= expr LSQBRACKET expr RSQBRACKET */
#line 468 "parser\\epparser.lemon"
{
    checkIsConstant(yymsp[-3].minor.yy0->data, yymsp[-3].minor.yy0->line);
    yymsp[-1].minor.yy0->data = "_ARRW(" + yymsp[-3].minor.yy0->data + ", " + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
    delete yymsp[-3].minor.yy0;
}
#line 1918 "parser\\epparser.c"
        break;
      case 107: /* lvalue ::= expr PERIOD NAME */
#line 475 "parser\\epparser.lemon"
{
    checkIsConstant(yymsp[-2].minor.yy0->data, yymsp[-2].minor.yy0->line);
    yymsp[0].minor.yy0->data = "_ATTW(" + yymsp[-2].minor.yy0->data + ", '" + yymsp[0].minor.yy0->data + "')";
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0);
    delete yymsp[-2].minor.yy0;
}
#line 1928 "parser\\epparser.c"
        break;
      case 110: /* assign_stmt ::= lvalue ASSIGN expr */
#line 484 "parser\\epparser.lemon"
{
    ps->gen << yymsp[-2].minor.yy0->data << " << (" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 1936 "parser\\epparser.c"
        break;
      case 111: /* assign_stmt ::= lvalueList_nonEmpty ASSIGN exprList_nonEmpty */
#line 489 "parser\\epparser.lemon"
{
    ps->gen << "_SV([" << yymsp[-2].minor.yy0->data << "], [" << yymsp[0].minor.yy0->data << "])" << std::endl;
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 1944 "parser\\epparser.c"
        break;
      case 112: /* assign_stmt ::= INC expr */
#line 497 "parser\\epparser.lemon"
{ ps->gen << yymsp[0].minor.yy0->data << ".__iadd__(1)" << std::endl; delete yymsp[0].minor.yy0; }
#line 1949 "parser\\epparser.c"
        break;
      case 113: /* assign_stmt ::= expr INC */
#line 498 "parser\\epparser.lemon"
{ ps->gen << yymsp[-1].minor.yy0->data << ".__iadd__(1)" << std::endl; delete yymsp[-1].minor.yy0; }
#line 1954 "parser\\epparser.c"
        break;
      case 114: /* assign_stmt ::= DEC expr */
#line 499 "parser\\epparser.lemon"
{ ps->gen << yymsp[0].minor.yy0->data << ".__isub__(1)" << std::endl; delete yymsp[0].minor.yy0; }
#line 1959 "parser\\epparser.c"
        break;
      case 115: /* assign_stmt ::= expr DEC */
#line 500 "parser\\epparser.lemon"
{ ps->gen << yymsp[-1].minor.yy0->data << ".__isub__(1)" << std::endl; delete yymsp[-1].minor.yy0; }
#line 1964 "parser\\epparser.c"
        break;
      case 116: /* assign_stmt ::= lvalue IADD expr */
#line 501 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__iadd__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1969 "parser\\epparser.c"
        break;
      case 117: /* assign_stmt ::= lvalue ISUB expr */
#line 502 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__isub__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1974 "parser\\epparser.c"
        break;
      case 118: /* assign_stmt ::= lvalue IMUL expr */
#line 503 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__imul__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1979 "parser\\epparser.c"
        break;
      case 119: /* assign_stmt ::= lvalue IDIV expr */
#line 504 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ifloordiv__("  << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1984 "parser\\epparser.c"
        break;
      case 120: /* assign_stmt ::= lvalue IMOD expr */
#line 505 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__imod__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1989 "parser\\epparser.c"
        break;
      case 121: /* assign_stmt ::= lvalue ILSH expr */
#line 506 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ilshift__("    << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1994 "parser\\epparser.c"
        break;
      case 122: /* assign_stmt ::= lvalue IRSH expr */
#line 507 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__irshift__("    << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1999 "parser\\epparser.c"
        break;
      case 123: /* assign_stmt ::= lvalue IBND expr */
#line 508 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__iand__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2004 "parser\\epparser.c"
        break;
      case 124: /* assign_stmt ::= lvalue IBOR expr */
#line 509 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ior__("        << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2009 "parser\\epparser.c"
        break;
      case 125: /* assign_stmt ::= lvalue IBXR expr */
#line 510 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ixor__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2014 "parser\\epparser.c"
        break;
      case 126: /* if_start ::= IF */
#line 513 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDIf()" << std::endl;
}
#line 2022 "parser\\epparser.c"
        break;
      case 127: /* if_header ::= if_start LPAREN lexpr RPAREN */
      case 136: /* while_header ::= while_start LPAREN lexpr RPAREN */ yytestcase(yyruleno==136);
#line 518 "parser\\epparser.lemon"
{
    ps->gen << "if " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data << "):" << std::endl;
    ps->gen.indent();
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 2032 "parser\\epparser.c"
        break;
      case 129: /* elif_start ::= ELSE IF */
#line 526 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen.unindent(false);
    ps->gen << yygotominor.yy0->data << " = EUDElseIf()" << std::endl;
}
#line 2041 "parser\\epparser.c"
        break;
      case 130: /* elif_header ::= elif_start LPAREN lexpr RPAREN */
#line 532 "parser\\epparser.lemon"
{
    ps->gen << "if " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data <<"):" << std::endl;
    ps->gen.indent();
}
#line 2049 "parser\\epparser.c"
        break;
      case 132: /* else_header ::= ELSE */
#line 539 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "if EUDElse()():" << std::endl;
    ps->gen.indent();
}
#line 2058 "parser\\epparser.c"
        break;
      case 133: /* if_stmt ::= if_block */
      case 134: /* if_stmt ::= if_block else_header stmt */ yytestcase(yyruleno==134);
#line 545 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndIf()" << std::endl;
}
#line 2067 "parser\\epparser.c"
        break;
      case 135: /* while_start ::= WHILE */
#line 557 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDWhile()" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2076 "parser\\epparser.c"
        break;
      case 137: /* while_stmt ::= while_header stmt */
#line 569 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndWhile()" << std::endl;
}
#line 2084 "parser\\epparser.c"
        break;
      case 138: /* for_opener ::= FOR LPAREN */
      case 153: /* foreach_opener ::= FOREACH LPAREN */ yytestcase(yyruleno==153);
#line 575 "parser\\epparser.lemon"
{
    ps->closure.pushScope();
}
#line 2092 "parser\\epparser.c"
        break;
      case 148: /* for_header1 ::= for_opener for_init_stmt SEMICOLON */
#line 591 "parser\\epparser.lemon"
{
    // opening for lexpr
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDWhile()" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2102 "parser\\epparser.c"
        break;
      case 149: /* for_header2 ::= for_header1 lexpr SEMICOLON */
#line 598 "parser\\epparser.lemon"
{
    ps->gen << "if " << yymsp[-2].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data << "):" << std::endl;
    ps->gen.indent();
    delete yymsp[-2].minor.yy0; delete yymsp[-1].minor.yy0;

    // Opening for assign_statement
    yygotominor.yy0 = genTemp(yymsp[-1].minor.yy0);
    ps->gen << "def " << yygotominor.yy0->data <<"():" << std::endl;
    ps->gen.indent();
}
#line 2116 "parser\\epparser.c"
        break;
      case 150: /* for_header ::= for_header2 for_action_stmt_nonEmpty RPAREN */
#line 609 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-2].minor.yy0;
    ps->gen.unindent(false);
}
#line 2124 "parser\\epparser.c"
        break;
      case 151: /* for_header ::= for_header2 RPAREN */
#line 614 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
    ps->gen << "pass" << std::endl;
    ps->gen.unindent(false);
}
#line 2133 "parser\\epparser.c"
        break;
      case 152: /* for_stmt ::= for_header stmt */
#line 620 "parser\\epparser.lemon"
{
    ps->gen << "EUDSetContinuePoint()" << std::endl;
    ps->gen << yymsp[-1].minor.yy0->data << "()" << std::endl;
    ps->gen.unindent(false);
    ps->gen << "EUDEndWhile()" << std::endl;
    ps->closure.popScope();
}
#line 2144 "parser\\epparser.c"
        break;
      case 154: /* foreach_header ::= foreach_opener nameList_nonEmpty COLON exprList_nonEmpty RPAREN */
#line 635 "parser\\epparser.lemon"
{
    commaListIter(yymsp[-3].minor.yy0->data, [&](std::string& s) {
        ps->closure.defVariable(s);
    });
    ps->gen << "for " << yymsp[-3].minor.yy0->data << " in " << yymsp[-1].minor.yy0->data << ":" << std::endl;
    ps->gen.indent();
}
#line 2155 "parser\\epparser.c"
        break;
      case 156: /* continue_stmt ::= CONTINUE */
#line 651 "parser\\epparser.lemon"
{
    ps->gen << "EUDContinue()" << std::endl;
}
#line 2162 "parser\\epparser.c"
        break;
      case 157: /* break_stmt ::= BREAK */
#line 655 "parser\\epparser.lemon"
{
    ps->gen << "EUDBreak()" << std::endl;
}
#line 2169 "parser\\epparser.c"
        break;
      case 158: /* return_stmt ::= RETURN exprList */
#line 662 "parser\\epparser.lemon"
{
    ps->gen << "EUDReturn(" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2177 "parser\\epparser.c"
        break;
      case 159: /* lexpr ::= CONDITIONNAME LPAREN fArgs RPAREN */
      case 160: /* lexpr ::= KILLS LPAREN fArgs RPAREN */ yytestcase(yyruleno==160);
#line 670 "parser\\epparser.lemon"
{
    yymsp[-3].minor.yy0->data = yymsp[-3].minor.yy0->data + "(" + yymsp[-1].minor.yy0->data + ")";
    delete yymsp[-1].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 2187 "parser\\epparser.c"
        break;
      case 161: /* lexpr ::= CONDITIONNAME LPAREN RPAREN */
#line 682 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + "()";
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 2195 "parser\\epparser.c"
        break;
      case 162: /* action ::= ACTIONNAME LPAREN fArgs RPAREN SEMICOLON */
#line 687 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[-4].minor.yy0);
    yygotominor.yy0->data =  yymsp[-4].minor.yy0->data + "(" + yymsp[-2].minor.yy0->data + ")";
    delete yymsp[-4].minor.yy0; delete yymsp[-2].minor.yy0;
}
#line 2204 "parser\\epparser.c"
        break;
      case 163: /* actions ::= action action */
      case 164: /* actions ::= actions action */ yytestcase(yyruleno==164);
#line 693 "parser\\epparser.lemon"
{
    if(functionCalledInMultipleActions) {
        ps->gen << "DoActions([" << std::endl;
        ps->gen.indent();
        ps->gen << yymsp[-1].minor.yy0->data << std::endl;
        ps->gen.unindent(false);
        ps->gen << "])" << std::endl;

        delete yymsp[-1].minor.yy0;
        yygotominor.yy0 = yymsp[0].minor.yy0;
    }
    else {
        yymsp[0].minor.yy0->data = yymsp[-1].minor.yy0->data + ",\n" + yymsp[0].minor.yy0->data;
        yygotominor.yy0 = yymsp[0].minor.yy0;
        delete yymsp[-1].minor.yy0;
    }
    functionCalledInMultipleActions = false;
}
#line 2227 "parser\\epparser.c"
        break;
      case 165: /* actionStmt_start ::= */
#line 731 "parser\\epparser.lemon"
{
    functionCalledInMultipleActions = false;
}
#line 2234 "parser\\epparser.c"
        break;
      case 166: /* actionStmt ::= actionStmt_start action */
#line 735 "parser\\epparser.lemon"
{
    ps->gen << "DoActions(" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2242 "parser\\epparser.c"
        break;
      case 167: /* actionStmt ::= actionStmt_start actions */
#line 740 "parser\\epparser.lemon"
{
    ps->gen << "DoActions([" << std::endl;
    ps->gen.indent();
    ps->gen << yymsp[0].minor.yy0->data << std::endl;
    ps->gen.unindent(false);
    ps->gen << "])" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2254 "parser\\epparser.c"
        break;
      default:
      /* (0) program ::= chunks */ yytestcase(yyruleno==0);
      /* (1) chunks ::= */ yytestcase(yyruleno==1);
      /* (2) chunks ::= chunks chunk */ yytestcase(yyruleno==2);
      /* (3) chunk ::= import_chunk SEMICOLON */ yytestcase(yyruleno==3);
      /* (4) chunk ::= fdef_chunk */ yytestcase(yyruleno==4);
      /* (5) chunk ::= fdecl_chunk */ yytestcase(yyruleno==5);
      /* (6) chunk ::= vdef_stmt SEMICOLON */ yytestcase(yyruleno==6);
      /* (7) chunk ::= vdefAssign_global_stmt SEMICOLON */ yytestcase(yyruleno==7);
      /* (8) chunk ::= cdef_stmt SEMICOLON */ yytestcase(yyruleno==8);
      /* (16) stmt ::= bodyStmt */ yytestcase(yyruleno==16);
      /* (17) stmt ::= return_stmt SEMICOLON */ yytestcase(yyruleno==17);
      /* (21) blockStmt ::= lbracket return_stmt SEMICOLON rbracket */ yytestcase(yyruleno==21);
      /* (22) blockStmt ::= lbracket bodyStmtList rbracket */ yytestcase(yyruleno==22);
      /* (23) blockStmt ::= lbracket bodyStmtList return_stmt SEMICOLON rbracket */ yytestcase(yyruleno==23);
      /* (25) bodyStmt ::= blockStmt */ yytestcase(yyruleno==25);
      /* (26) bodyStmt ::= SEMICOLON */ yytestcase(yyruleno==26);
      /* (27) bodyStmt ::= vdef_stmt SEMICOLON */ yytestcase(yyruleno==27);
      /* (28) bodyStmt ::= vdefAssign_stmt SEMICOLON */ yytestcase(yyruleno==28);
      /* (29) bodyStmt ::= cdef_stmt SEMICOLON */ yytestcase(yyruleno==29);
      /* (30) bodyStmt ::= assign_stmt SEMICOLON */ yytestcase(yyruleno==30);
      /* (32) bodyStmt ::= actionStmt */ yytestcase(yyruleno==32);
      /* (33) bodyStmt ::= if_stmt */ yytestcase(yyruleno==33);
      /* (34) bodyStmt ::= while_stmt */ yytestcase(yyruleno==34);
      /* (35) bodyStmt ::= for_stmt */ yytestcase(yyruleno==35);
      /* (36) bodyStmt ::= foreach_stmt */ yytestcase(yyruleno==36);
      /* (37) bodyStmt ::= continue_stmt SEMICOLON */ yytestcase(yyruleno==37);
      /* (38) bodyStmt ::= break_stmt SEMICOLON */ yytestcase(yyruleno==38);
      /* (40) bodyStmtList ::= bodyStmt */ yytestcase(yyruleno==40);
      /* (41) bodyStmtList ::= bodyStmtList bodyStmt */ yytestcase(yyruleno==41);
      /* (128) if_block ::= if_header stmt */ yytestcase(yyruleno==128);
      /* (131) if_block ::= if_block elif_header stmt */ yytestcase(yyruleno==131);
      /* (139) for_init_stmt_nonEmpty ::= vdef_stmt */ yytestcase(yyruleno==139);
      /* (140) for_init_stmt_nonEmpty ::= vdefAssign_stmt */ yytestcase(yyruleno==140);
      /* (141) for_init_stmt_nonEmpty ::= cdef_stmt */ yytestcase(yyruleno==141);
      /* (142) for_init_stmt_nonEmpty ::= assign_stmt */ yytestcase(yyruleno==142);
      /* (143) for_init_stmt_nonEmpty ::= for_init_stmt_nonEmpty COMMA for_init_stmt_nonEmpty */ yytestcase(yyruleno==143);
      /* (144) for_init_stmt ::= for_init_stmt_nonEmpty */ yytestcase(yyruleno==144);
      /* (145) for_init_stmt ::= */ yytestcase(yyruleno==145);
      /* (146) for_action_stmt_nonEmpty ::= assign_stmt */ yytestcase(yyruleno==146);
      /* (147) for_action_stmt_nonEmpty ::= for_action_stmt_nonEmpty COMMA for_action_stmt_nonEmpty */ yytestcase(yyruleno==147);
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
#line 27 "parser\\epparser.lemon"

    throw_error(-1, "Unrecoverable error");
#line 2345 "parser\\epparser.c"
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
#line 754 "parser\\epparser.lemon"


int PARSER_DEBUG = 0;
PyGenerator* pGen;
ClosureManager* closure;

std::string ParseString(const std::string& code, bool addComment)
{
    Tokenizer tok(code);
    void* pParser = ParseAlloc (malloc);
    ParserStruct ps;
    Token* token;
    currentTokenizingLine = 0;
    pGen = &ps.gen;
    closure = &ps.closure;
    functionCalledInMultipleActions = false;

    if(PARSER_DEBUG) std::cout << "Parsing string [[[\n" << code.c_str() << "\n]]]\n";

    tmpIndex = 1;
    resetParserErrorNum();
    while ((token = tok.getToken()) != nullptr) {
        if (currentTokenizingLine != tok.getCurrentLine()) {
            if(addComment) {
                currentTokenizingLine = tok.getCurrentLine();
                ps.gen << "# (Line " << currentTokenizingLine << ") " << trim(tok.getCurrentLineString()) << std::endl;
            }
            if(PARSER_DEBUG) printf("# reading line %s\n", tok.getCurrentLineString().c_str());
        }
        if (tokenTypeConv(token)) {
            Parse (pParser, token->type, token, &ps);
#ifndef NDEBUG
            if(PARSER_DEBUG) ParseTrace(stdout, "--");
#endif
        }
        else {
            throw_error(8104, "Invalid token");
        }
    }
    Parse (pParser, 0, nullptr, &ps);
    ParseFree(pParser, free );

    std::string ret = iwCollapse(ps.gen.str());
    if(getParseErrorNum() > 0) {
        ret += "\nraise RuntimeError('Compile error')\n";
    }
    return ret;
}
#line 2599 "parser\\epparser.c"
