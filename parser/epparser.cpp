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
#define YYNOCODE 131
#define YYACTIONTYPE unsigned short int
#define ParseTOKENTYPE Token*
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  int yy261;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL  ParserStruct* ps ;
#define ParseARG_PDECL , ParserStruct* ps 
#define ParseARG_FETCH  ParserStruct* ps  = yypParser->ps 
#define ParseARG_STORE yypParser->ps  = ps 
#define YYNSTATE 325
#define YYNRULE 167
#define YYERRORSYMBOL 71
#define YYERRSYMDT yy261
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
#define YY_ACTTAB_COUNT (1351)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   210,  240,  196,   28,   29,   18,   28,   29,  206,   75,
 /*    10 */   204,  302,  194,   89,  312,  310,  209,    2,  120,  143,
 /*    20 */   205,  203,  148,  294,  293,  292,  291,  290,  198,  197,
 /*    30 */   190,  239,  270,   89,  193,  264,   28,   29,  120,  143,
 /*    40 */   161,    8,   40,  323,  278,  113,  158,    6,   10,   38,
 /*    50 */   211,  210,   22,   13,    5,   81,    4,   80,   79,  206,
 /*    60 */   241,  204,  302,  320,  189,  255,  310,  209,    2,  319,
 /*    70 */    76,  205,  203,  148,  294,  293,  292,  291,  290,  198,
 /*    80 */   197,  159,    7,    3,   89,  193,  296,   37,  211,  120,
 /*    90 */   143,  161,    8,   40,  202,  164,  113,  158,    6,   10,
 /*   100 */    19,  214,  196,   22,   13,    5,   81,    4,   80,   79,
 /*   110 */   210,  240,  196,  114,   14,  185,  166,  211,  206,  212,
 /*   120 */   204,  302,  318,   89,  252,  310,  209,    2,  120,  143,
 /*   130 */   205,  203,  148,  294,  293,  292,  291,  290,  198,  197,
 /*   140 */    39,  142,  196,   89,  238,   28,   29,  218,  120,  143,
 /*   150 */   161,    8,   40,  114,  217,  276,  158,    6,   10,   35,
 /*   160 */    36,  210,   22,   13,    5,   81,    4,   80,   79,  206,
 /*   170 */   234,  204,  302,  316,  256,  249,  310,  209,    2,  215,
 /*   180 */    34,  205,  203,  148,  294,  293,  292,  291,  290,  198,
 /*   190 */   197,   77,   28,   29,   89,  196,   28,   29,  213,  120,
 /*   200 */   143,  161,    8,   40,   33,  211,  115,  158,    6,   10,
 /*   210 */   493,   11,  193,   22,   13,    5,   81,    4,   80,   79,
 /*   220 */   210,  253,  188,  113,  168,  250,  315,  196,  206,  211,
 /*   230 */   204,  302,  313,  201,  236,  310,  209,    2,   92,  196,
 /*   240 */   205,  203,  148,  294,  293,  292,  291,  290,  198,  197,
 /*   250 */    95,  311,  196,   89,  196,  258,  200,  309,  120,  143,
 /*   260 */   161,    8,   40,  126,   86,  125,  158,    6,   10,  196,
 /*   270 */    85,  210,   22,   13,    5,   81,    4,   80,   79,  206,
 /*   280 */    88,  204,  302,  199,  131,  233,  310,  209,    2,  300,
 /*   290 */   196,  205,  203,  148,  294,  293,  292,  291,  290,  198,
 /*   300 */   197,   87,  299,  196,   89,  132,  298,  297,  295,  120,
 /*   310 */   143,  161,    8,   40,  138,  289,  288,  158,    6,   10,
 /*   320 */   202,   19,  193,   22,   13,    5,   81,    4,   80,   79,
 /*   330 */   210,  196,  188,  113,  230,  283,  192,  196,  206,   84,
 /*   340 */   204,  302,  137,  280,  226,  310,  209,    2,  136,  196,
 /*   350 */   205,  203,  148,  294,  293,  292,  291,  290,  198,  197,
 /*   360 */    88,  279,  196,   89,  269,   39,   31,   17,  120,  143,
 /*   370 */   161,    8,   40,  124,   32,  183,  158,    6,   10,  196,
 /*   380 */   182,  150,   22,   13,    5,   81,    4,   80,   79,  206,
 /*   390 */    88,  204,  302,  275,  171,  180,  224,  208,    2,  179,
 /*   400 */     1,  205,  203,  148,  294,  293,  292,  291,  290,  198,
 /*   410 */   197,   29,  274,  196,   89,  177,  176,  273,  174,  120,
 /*   420 */   143,  161,    8,   40,  123,  173,  272,  158,    6,   10,
 /*   430 */   271,  196,  196,   22,   13,    5,   81,    4,   80,   79,
 /*   440 */   286,  196,  122,  114,   15,  185,  167,  266,  206,  118,
 /*   450 */   204,  302,  119,  263,  262,  287,  207,    2,  304,  261,
 /*   460 */   205,  203,  148,  294,  293,  292,  291,  290,  198,  197,
 /*   470 */    25,  254,  196,   89,   24,   23,  248,   12,  120,  143,
 /*   480 */   161,    8,   40,  121,  242,  235,  158,    6,   10,   16,
 /*   490 */   196,  229,   22,   13,    5,   81,    4,   80,   79,   63,
 /*   500 */    62,   91,   71,   72,   70,   61,  285,  116,  301,  151,
 /*   510 */   225,  146,   64,   18,  308,  307,   21,   75,  284,  305,
 /*   520 */   194,  306,  187,  184,  181,  178,  175,   83,   82,   42,
 /*   530 */    41,   69,   68,   74,   73,   71,   72,   70,  303,  191,
 /*   540 */   145,  257,  314,  251,  157,  154,   18,  232,  231,   20,
 /*   550 */    75,  153,  193,  194,  193,  144,  228,  141,  153,  196,
 /*   560 */    63,   62,  163,  113,  162,  113,   61,  285,  116,  301,
 /*   570 */    88,  139,  160,   64,  268,  308,  306,   21,  227,  284,
 /*   580 */   494,  494,  193,  187,  184,  181,  178,  175,   83,   82,
 /*   590 */    42,   41,  140,  113,   74,   73,   71,   72,   70,  494,
 /*   600 */   494,  494,  257,  494,  251,  157,  154,   18,  232,  231,
 /*   610 */    20,   75,  153,  494,  194,  494,  494,  494,  494,  494,
 /*   620 */   196,   63,   62,  494,  494,  494,  196,   61,  285,  116,
 /*   630 */   301,   88,  494,  494,   64,  267,  308,   88,   21,  494,
 /*   640 */   284,  130,  196,  196,  187,  184,  181,  178,  175,   83,
 /*   650 */    82,   42,   41,  114,   88,  185,  172,  196,  129,  494,
 /*   660 */   494,  494,  494,  257,  494,  251,  157,  154,   88,  232,
 /*   670 */   231,   20,  128,  153,   60,   58,   57,   56,   55,   59,
 /*   680 */    66,   65,   67,   69,   68,   74,   73,   71,   72,   70,
 /*   690 */   196,  494,  494,  494,  494,  494,  494,  494,   18,  281,
 /*   700 */   494,  114,   75,  185,  152,  194,   60,   58,   57,   56,
 /*   710 */    55,   59,   66,   65,   67,   69,   68,   74,   73,   71,
 /*   720 */    72,   70,  494,  494,  196,   63,   62,  494,  494,  196,
 /*   730 */    18,   61,  285,  116,   75,   88,  193,  194,   64,  127,
 /*   740 */   135,  494,   21,  494,  284,  494,  149,  113,  187,  184,
 /*   750 */   181,  178,  175,   83,   82,   42,   41,   63,   62,  494,
 /*   760 */   494,  494,  196,   61,  285,  116,  196,  196,  196,  494,
 /*   770 */    64,  237,  325,  134,   21,  196,  284,  133,  112,  111,
 /*   780 */   187,  184,  181,  178,  175,  494,  110,   42,   41,  494,
 /*   790 */    66,   65,   67,   69,   68,   74,   73,   71,   72,   70,
 /*   800 */   219,  494,  216,   27,  494,  308,  494,  494,   18,  196,
 /*   810 */   196,  494,   54,  494,  494,  165,   63,   62,   78,   82,
 /*   820 */   109,  108,   61,  285,  195,  260,  259,  196,  494,   30,
 /*   830 */   494,  494,   26,   21,  494,  186,  196,  494,  107,  187,
 /*   840 */   184,  181,  178,  175,  196,   63,   62,  114,  196,  185,
 /*   850 */   169,   61,  285,  195,  494,   90,  494,  494,   30,  106,
 /*   860 */   494,  494,   21,  494,  186,  494,  196,  170,  187,  184,
 /*   870 */   181,  178,  175,  196,  196,  196,  494,  105,  494,  494,
 /*   880 */   196,   63,   62,  494,  104,  103,  102,   61,  285,  147,
 /*   890 */   196,  101,  196,  494,   64,  265,  170,  494,   21,  196,
 /*   900 */   284,  100,  277,   99,  187,  184,  181,  178,  175,  494,
 /*   910 */    98,  196,  196,   63,   62,  494,  196,  196,  494,   61,
 /*   920 */   285,  116,   97,   96,  494,  494,   64,   94,   93,  494,
 /*   930 */    21,  494,  284,  494,  494,  494,  187,  184,  181,  178,
 /*   940 */   175,  494,  494,   42,   41,  494,   66,   65,   67,   69,
 /*   950 */    68,   74,   73,   71,   72,   70,  494,  494,  494,  494,
 /*   960 */   494,  494,  494,  494,   18,  494,  494,  494,   75,  282,
 /*   970 */   494,  194,  494,  494,  494,  494,  494,  494,   66,   65,
 /*   980 */    67,   69,   68,   74,   73,   71,   72,   70,  494,  494,
 /*   990 */   494,  494,  494,  494,  494,  494,   18,  281,  494,  494,
 /*  1000 */    75,  494,  494,  194,  494,  494,  494,  494,  494,  494,
 /*  1010 */    66,   65,   67,   69,   68,   74,   73,   71,   72,   70,
 /*  1020 */   430,  430,  494,  494,  494,  494,  494,  494,   18,  494,
 /*  1030 */    63,   62,   75,  117,  494,  194,   61,  285,  147,  494,
 /*  1040 */   494,  494,  494,   64,  494,  494,  494,   21,  494,  284,
 /*  1050 */    19,  277,  494,  187,  184,  181,  178,  175,  494,  494,
 /*  1060 */   494,  494,  494,  494,  494,  494,  494,  494,  494,  430,
 /*  1070 */   430,  430,  430,  430,  430,  430,  430,  430,  430,  494,
 /*  1080 */   494,  494,  494,   66,   65,   67,   69,   68,   74,   73,
 /*  1090 */    71,   72,   70,  494,  494,  494,  494,  494,  494,  494,
 /*  1100 */   494,   18,  494,  494,  494,   75,  494,  494,  194,  494,
 /*  1110 */   494,  494,  494,  494,  494,   66,   65,   67,   69,   68,
 /*  1120 */    74,   73,   71,   72,   70,  494,  494,  494,  494,  494,
 /*  1130 */   494,  494,  494,   18,  494,   63,   62,   54,  494,  494,
 /*  1140 */   165,   61,  285,  195,  494,  494,  494,  494,   64,  494,
 /*  1150 */   494,  494,   21,  494,  284,  494,  494,  494,  187,  184,
 /*  1160 */   181,  178,  175,  494,  494,  494,  494,   63,   62,  494,
 /*  1170 */   494,  494,  494,   61,  285,  116,  432,  432,  494,  494,
 /*  1180 */    64,  494,  494,  494,   21,  494,  284,  494,  431,  431,
 /*  1190 */   187,  184,  181,  178,  175,   65,   67,   69,   68,   74,
 /*  1200 */    73,   71,   72,   70,  494,  494,  494,  494,  494,  494,
 /*  1210 */   494,  494,   18,  494,  494,  494,   75,  494,  494,  194,
 /*  1220 */   494,  494,  494,  494,  494,  432,  432,  432,  432,  432,
 /*  1230 */   432,  432,  432,  432,  432,   53,  494,  431,  431,  431,
 /*  1240 */   431,  431,  431,  431,  431,  431,  431,   67,   69,   68,
 /*  1250 */    74,   73,   71,   72,   70,  494,  494,  494,  494,  494,
 /*  1260 */   494,  494,  494,   18,  494,  494,  494,   75,  494,  494,
 /*  1270 */   194,  494,  494,  494,  494,  494,  494,  494,  494,  494,
 /*  1280 */   494,  494,  494,  494,   52,   51,   50,   49,   48,   47,
 /*  1290 */    46,   45,   44,   43,  494,  324,  223,  322,  321,  222,
 /*  1300 */   221,  220,  317,    9,  494,  247,  494,  245,    2,  247,
 /*  1310 */   494,  245,  494,  494,  494,  494,  494,  246,  244,  196,
 /*  1320 */   494,  246,  244,  196,  494,  494,  494,  494,  494,  494,
 /*  1330 */    89,  494,  494,  494,   89,  120,  143,  494,  494,  120,
 /*  1340 */   143,  494,  494,  494,  494,  494,  156,  155,  494,  494,
 /*  1350 */   243,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    71,   92,   93,    3,    4,   31,    3,    4,   79,   35,
 /*    10 */    81,   82,   38,  104,   85,   86,   87,   88,  109,  110,
 /*    20 */    91,   92,   93,   94,   95,   96,   97,   98,   99,  100,
 /*    30 */     2,  122,   32,  104,   93,   32,    3,    4,  109,  110,
 /*    40 */   111,  112,  113,   27,  103,  104,  117,  118,  119,    1,
 /*    50 */     2,   71,  123,  124,  125,  126,  127,  128,  129,   79,
 /*    60 */    27,   81,   82,   27,   36,   85,   86,   87,   88,   27,
 /*    70 */     1,   91,   92,   93,   94,   95,   96,   97,   98,   99,
 /*    80 */   100,  114,  115,  116,  104,   93,   27,    1,    2,  109,
 /*    90 */   110,  111,  112,  113,   35,  103,  104,  117,  118,  119,
 /*   100 */    31,   84,   93,  123,  124,  125,  126,  127,  128,  129,
 /*   110 */    71,   92,   93,  104,    2,  106,  107,    2,   79,  102,
 /*   120 */    81,   82,   27,  104,   85,   86,   87,   88,  109,  110,
 /*   130 */    91,   92,   93,   94,   95,   96,   97,   98,   99,  100,
 /*   140 */     2,  122,   93,  104,   32,    3,    4,   26,  109,  110,
 /*   150 */   111,  112,  113,  104,   29,  106,  117,  118,  119,    1,
 /*   160 */     2,   71,  123,  124,  125,  126,  127,  128,  129,   79,
 /*   170 */    32,   81,   82,   26,   32,   85,   86,   87,   88,   26,
 /*   180 */    65,   91,   92,   93,   94,   95,   96,   97,   98,   99,
 /*   190 */   100,   31,    3,    4,  104,   93,    3,    4,   32,  109,
 /*   200 */   110,  111,  112,  113,    1,    2,  104,  117,  118,  119,
 /*   210 */    73,   74,   93,  123,  124,  125,  126,  127,  128,  129,
 /*   220 */    71,   32,  103,  104,  105,   32,   27,   93,   79,    2,
 /*   230 */    81,   82,   26,   35,   85,   86,   87,   88,  104,   93,
 /*   240 */    91,   92,   93,   94,   95,   96,   97,   98,   99,  100,
 /*   250 */   104,   27,   93,  104,   93,  109,   25,   27,  109,  110,
 /*   260 */   111,  112,  113,  104,   27,  104,  117,  118,  119,   93,
 /*   270 */    27,   71,  123,  124,  125,  126,  127,  128,  129,   79,
 /*   280 */   104,   81,   82,   36,  108,   85,   86,   87,   88,   27,
 /*   290 */    93,   91,   92,   93,   94,   95,   96,   97,   98,   99,
 /*   300 */   100,  104,   27,   93,  104,  108,   27,   27,   36,  109,
 /*   310 */   110,  111,  112,  113,  104,   27,   27,  117,  118,  119,
 /*   320 */    35,   31,   93,  123,  124,  125,  126,  127,  128,  129,
 /*   330 */    71,   93,  103,  104,  105,   26,   35,   93,   79,   35,
 /*   340 */    81,   82,  104,   25,   85,   86,   87,   88,  104,   93,
 /*   350 */    91,   92,   93,   94,   95,   96,   97,   98,   99,  100,
 /*   360 */   104,   36,   93,  104,  108,    2,   31,   31,  109,  110,
 /*   370 */   111,  112,  113,  104,    2,   31,  117,  118,  119,   93,
 /*   380 */    39,   71,  123,  124,  125,  126,  127,  128,  129,   79,
 /*   390 */   104,   81,   82,   32,  108,   31,   86,   87,   88,   39,
 /*   400 */    90,   91,   92,   93,   94,   95,   96,   97,   98,   99,
 /*   410 */   100,    4,   32,   93,  104,   31,   39,   32,   31,  109,
 /*   420 */   110,  111,  112,  113,  104,   39,   32,  117,  118,  119,
 /*   430 */    32,   93,   93,  123,  124,  125,  126,  127,  128,  129,
 /*   440 */    71,   93,  104,  104,   31,  106,  107,   32,   79,   26,
 /*   450 */    81,   82,  104,   36,   32,   86,   87,   88,   89,   32,
 /*   460 */    91,   92,   93,   94,   95,   96,   97,   98,   99,  100,
 /*   470 */    31,   60,   93,  104,   31,   31,   31,    2,  109,  110,
 /*   480 */   111,  112,  113,  104,   27,   31,  117,  118,  119,   31,
 /*   490 */    93,   27,  123,  124,  125,  126,  127,  128,  129,   18,
 /*   500 */    19,  104,   20,   21,   22,   24,   25,   26,   27,   32,
 /*   510 */    34,  101,   31,   31,   33,   34,   35,   35,   37,   89,
 /*   520 */    38,   34,   41,   42,   43,   44,   45,   46,   47,   48,
 /*   530 */    49,   16,   17,   18,   19,   20,   21,   22,   89,   25,
 /*   540 */   102,   60,   26,   62,   63,   64,   31,   66,   67,   68,
 /*   550 */    35,   70,   93,   38,   93,  102,  128,  102,   70,   93,
 /*   560 */    18,   19,  103,  104,  103,  104,   24,   25,   26,   27,
 /*   570 */   104,  102,   61,   31,  108,   33,   34,   35,  128,   37,
 /*   580 */   130,  130,   93,   41,   42,   43,   44,   45,   46,   47,
 /*   590 */    48,   49,  103,  104,   18,   19,   20,   21,   22,  130,
 /*   600 */   130,  130,   60,  130,   62,   63,   64,   31,   66,   67,
 /*   610 */    68,   35,   70,  130,   38,  130,  130,  130,  130,  130,
 /*   620 */    93,   18,   19,  130,  130,  130,   93,   24,   25,   26,
 /*   630 */    27,  104,  130,  130,   31,  108,   33,  104,   35,  130,
 /*   640 */    37,  108,   93,   93,   41,   42,   43,   44,   45,   46,
 /*   650 */    47,   48,   49,  104,  104,  106,  107,   93,  108,  130,
 /*   660 */   130,  130,  130,   60,  130,   62,   63,   64,  104,   66,
 /*   670 */    67,   68,  108,   70,    7,    8,    9,   10,   11,   12,
 /*   680 */    13,   14,   15,   16,   17,   18,   19,   20,   21,   22,
 /*   690 */    93,  130,  130,  130,  130,  130,  130,  130,   31,   32,
 /*   700 */   130,  104,   35,  106,  107,   38,    7,    8,    9,   10,
 /*   710 */    11,   12,   13,   14,   15,   16,   17,   18,   19,   20,
 /*   720 */    21,   22,  130,  130,   93,   18,   19,  130,  130,   93,
 /*   730 */    31,   24,   25,   26,   35,  104,   93,   38,   31,  108,
 /*   740 */   104,  130,   35,  130,   37,  130,  103,  104,   41,   42,
 /*   750 */    43,   44,   45,   46,   47,   48,   49,   18,   19,  130,
 /*   760 */   130,  130,   93,   24,   25,   26,   93,   93,   93,  130,
 /*   770 */    31,   32,    0,  104,   35,   93,   37,  104,  104,  104,
 /*   780 */    41,   42,   43,   44,   45,  130,  104,   48,   49,  130,
 /*   790 */    13,   14,   15,   16,   17,   18,   19,   20,   21,   22,
 /*   800 */    28,  130,   30,    5,  130,   33,  130,  130,   31,   93,
 /*   810 */    93,  130,   35,  130,  130,   38,   18,   19,   46,   47,
 /*   820 */   104,  104,   24,   25,   26,   48,   49,   93,  130,   31,
 /*   830 */   130,  130,    5,   35,  130,   37,   93,  130,  104,   41,
 /*   840 */    42,   43,   44,   45,   93,   18,   19,  104,   93,  106,
 /*   850 */   107,   24,   25,   26,  130,  104,  130,  130,   31,  104,
 /*   860 */   130,  130,   35,  130,   37,  130,   93,   69,   41,   42,
 /*   870 */    43,   44,   45,   93,   93,   93,  130,  104,  130,  130,
 /*   880 */    93,   18,   19,  130,  104,  104,  104,   24,   25,   26,
 /*   890 */    93,  104,   93,  130,   31,   32,   69,  130,   35,   93,
 /*   900 */    37,  104,   39,  104,   41,   42,   43,   44,   45,  130,
 /*   910 */   104,   93,   93,   18,   19,  130,   93,   93,  130,   24,
 /*   920 */    25,   26,  104,  104,  130,  130,   31,  104,  104,  130,
 /*   930 */    35,  130,   37,  130,  130,  130,   41,   42,   43,   44,
 /*   940 */    45,  130,  130,   48,   49,  130,   13,   14,   15,   16,
 /*   950 */    17,   18,   19,   20,   21,   22,  130,  130,  130,  130,
 /*   960 */   130,  130,  130,  130,   31,  130,  130,  130,   35,   36,
 /*   970 */   130,   38,  130,  130,  130,  130,  130,  130,   13,   14,
 /*   980 */    15,   16,   17,   18,   19,   20,   21,   22,  130,  130,
 /*   990 */   130,  130,  130,  130,  130,  130,   31,   32,  130,  130,
 /*  1000 */    35,  130,  130,   38,  130,  130,  130,  130,  130,  130,
 /*  1010 */    13,   14,   15,   16,   17,   18,   19,   20,   21,   22,
 /*  1020 */     1,    2,  130,  130,  130,  130,  130,  130,   31,  130,
 /*  1030 */    18,   19,   35,   36,  130,   38,   24,   25,   26,  130,
 /*  1040 */   130,  130,  130,   31,  130,  130,  130,   35,  130,   37,
 /*  1050 */    31,   39,  130,   41,   42,   43,   44,   45,  130,  130,
 /*  1060 */   130,  130,  130,  130,  130,  130,  130,  130,  130,   50,
 /*  1070 */    51,   52,   53,   54,   55,   56,   57,   58,   59,  130,
 /*  1080 */   130,  130,  130,   13,   14,   15,   16,   17,   18,   19,
 /*  1090 */    20,   21,   22,  130,  130,  130,  130,  130,  130,  130,
 /*  1100 */   130,   31,  130,  130,  130,   35,  130,  130,   38,  130,
 /*  1110 */   130,  130,  130,  130,  130,   13,   14,   15,   16,   17,
 /*  1120 */    18,   19,   20,   21,   22,  130,  130,  130,  130,  130,
 /*  1130 */   130,  130,  130,   31,  130,   18,   19,   35,  130,  130,
 /*  1140 */    38,   24,   25,   26,  130,  130,  130,  130,   31,  130,
 /*  1150 */   130,  130,   35,  130,   37,  130,  130,  130,   41,   42,
 /*  1160 */    43,   44,   45,  130,  130,  130,  130,   18,   19,  130,
 /*  1170 */   130,  130,  130,   24,   25,   26,    1,    2,  130,  130,
 /*  1180 */    31,  130,  130,  130,   35,  130,   37,  130,    1,    2,
 /*  1190 */    41,   42,   43,   44,   45,   14,   15,   16,   17,   18,
 /*  1200 */    19,   20,   21,   22,  130,  130,  130,  130,  130,  130,
 /*  1210 */   130,  130,   31,  130,  130,  130,   35,  130,  130,   38,
 /*  1220 */   130,  130,  130,  130,  130,   50,   51,   52,   53,   54,
 /*  1230 */    55,   56,   57,   58,   59,    1,  130,   50,   51,   52,
 /*  1240 */    53,   54,   55,   56,   57,   58,   59,   15,   16,   17,
 /*  1250 */    18,   19,   20,   21,   22,  130,  130,  130,  130,  130,
 /*  1260 */   130,  130,  130,   31,  130,  130,  130,   35,  130,  130,
 /*  1270 */    38,  130,  130,  130,  130,  130,  130,  130,  130,  130,
 /*  1280 */   130,  130,  130,  130,   50,   51,   52,   53,   54,   55,
 /*  1290 */    56,   57,   58,   59,  130,   75,   76,   77,   78,   79,
 /*  1300 */    80,   81,   82,   83,  130,   79,  130,   81,   88,   79,
 /*  1310 */   130,   81,  130,  130,  130,  130,  130,   91,   92,   93,
 /*  1320 */   130,   91,   92,   93,  130,  130,  130,  130,  130,  130,
 /*  1330 */   104,  130,  130,  130,  104,  109,  110,  130,  130,  109,
 /*  1340 */   110,  130,  130,  130,  130,  130,  120,  121,  130,  130,
 /*  1350 */   120,
};
#define YY_SHIFT_USE_DFLT (-27)
#define YY_SHIFT_COUNT (223)
#define YY_SHIFT_MIN   (-26)
#define YY_SHIFT_MAX   (1234)
static const short yy_shift_ofst[] = {
 /*     0 */   -27,  542,  481,  603,  603,  603,  603,  603,  603,  603,
 /*    10 */   707,  772,  707,  739,  895,  863, 1012, 1012, 1012, 1012,
 /*    20 */  1117, 1117,  798,  798,  798,  798,  827,  827,  798,  798,
 /*    30 */   798,  798, 1012, 1117, 1117, 1117, 1149, 1117, 1117, 1117,
 /*    40 */   511, 1117, 1117, 1117, 1117, 1117, 1117, 1117, 1117, 1117,
 /*    50 */  1117, 1117, 1117, 1117, 1117, 1117, 1117, 1117, 1117, 1117,
 /*    60 */  1117, 1117, 1117, 1117, 1117, 1117, 1117, 1117, 1117, 1117,
 /*    70 */  1117, 1117, 1117, 1117, 1117, 1117, 1117,  516,  516,  488,
 /*    80 */   488,  516,  516,  516,  514,  487,  487,  667,  699,  777,
 /*    90 */   997,  965,  933, 1070, 1070, 1102, 1070, 1070, 1070, 1070,
 /*   100 */  1070, 1070, 1070, 1070, 1070, 1070, 1070, 1070, 1070, 1070,
 /*   110 */  1070, 1070, 1070, 1070, 1070, 1070, 1019, 1187, 1175, 1181,
 /*   120 */  1234, 1232,  515,  576,  576,  482,  482,   33,  193,  189,
 /*   130 */   142,    3,    0,  -26,  -26,  -26,  -26,  -26,  -26,  203,
 /*   140 */   138,  115,  112,  158,   86,   48,   28,   69,   59,  363,
 /*   150 */   476,  464,  477,  458,  454,  457,  475,  445,  444,  443,
 /*   160 */   411,  439,  363,  363,  363,  423,  427,  422,  417,  415,
 /*   170 */   413,  407,  398,  394,  386,  387,  385,  377,  384,  380,
 /*   180 */   360,  364,  361,  341,  344,  372,  336,  335,  363,  325,
 /*   190 */   318,  247,  304,  301,  309,  290,  285,  289,  288,  272,
 /*   200 */   247,  231,  198,  280,  279,  275,  262,  243,  237,  230,
 /*   210 */   224,  206,  227,  199,  166,  160,  153,  147,  125,  121,
 /*   220 */    95,   42,   36,   16,
};
#define YY_REDUCE_USE_DFLT (-92)
#define YY_REDUCE_COUNT (86)
#define YY_REDUCE_MIN   (-91)
#define YY_REDUCE_MAX   (1230)
static const short yy_reduce_ofst[] = {
 /*     0 */   137,  369,  310,  259,  200,  149,   90,   39,  -20,  -71,
 /*    10 */  1226, 1220, 1230,   19,  -91,  743,  597,  549,  339,    9,
 /*    20 */   229,  119,  631,  564,  550,  533,  527,  466,  286,  256,
 /*    30 */   197,  176,   49,  643,  489,  461,  146,  459,   -8,  -59,
 /*    40 */   -33,  824,  823,  819,  818,  806,  799,  797,  787,  782,
 /*    50 */   781,  780,  773,  755,  751,  734,  717,  716,  682,  675,
 /*    60 */   674,  673,  669,  636,  397,  379,  348,  338,  320,  269,
 /*    70 */   244,  238,  210,  161,  159,  134,  102,   17,  469,  450,
 /*    80 */   428,  455,  453,  438,  410,  449,  430,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   326,  492,  492,  492,  492,  492,  492,  492,  492,  492,
 /*    10 */   470,  492,  492,  492,  492,  492,  389,  389,  389,  389,
 /*    20 */   378,  378,  492,  492,  492,  492,  492,  492,  492,  492,
 /*    30 */   492,  492,  492,  492,  492,  492,  492,  492,  492,  492,
 /*    40 */   458,  492,  492,  492,  492,  492,  492,  492,  492,  492,
 /*    50 */   492,  492,  492,  492,  492,  492,  492,  492,  492,  492,
 /*    60 */   492,  492,  492,  492,  492,  492,  492,  492,  492,  492,
 /*    70 */   492,  492,  492,  492,  492,  492,  492,  372,  492,  491,
 /*    80 */   490,  492,  492,  492,  492,  492,  492,  414,  414,  492,
 /*    90 */   492,  492,  492,  439,  437,  492,  450,  449,  448,  447,
 /*   100 */   446,  445,  444,  443,  442,  441,  435,  421,  420,  419,
 /*   110 */   418,  417,  416,  376,  385,  387,  382,  384,  383,  409,
 /*   120 */   433,  410,  408,  407,  406,  402,  401,  492,  492,  492,
 /*   130 */   492,  492,  492,  413,  412,  411,  405,  404,  403,  426,
 /*   140 */   492,  492,  492,  492,  492,  426,  492,  382,  393,  428,
 /*   150 */   364,  492,  492,  492,  492,  492,  469,  492,  492,  492,
 /*   160 */   457,  492,  436,  429,  427,  492,  492,  492,  492,  492,
 /*   170 */   492,  423,  492,  492,  492,  492,  492,  492,  492,  492,
 /*   180 */   492,  492,  492,  492,  492,  390,  381,  492,  379,  492,
 /*   190 */   492,  368,  492,  393,  492,  382,  393,  492,  492,  492,
 /*   200 */   492,  492,  492,  492,  492,  492,  492,  492,  492,  492,
 /*   210 */   492,  492,  373,  337,  492,  492,  492,  492,  336,  492,
 /*   220 */   492,  492,  492,  492,  365,  349,  459,  489,  488,  487,
 /*   230 */   483,  482,  481,  480,  479,  478,  477,  476,  475,  472,
 /*   240 */   471,  474,  473,  468,  467,  466,  465,  464,  463,  462,
 /*   250 */   461,  460,  456,  455,  454,  453,  452,  451,  434,  440,
 /*   260 */   438,  391,  392,  395,  396,  486,  484,  425,  424,  422,
 /*   270 */   415,  485,  400,  399,  398,  397,  388,  386,  377,  374,
 /*   280 */   369,  394,  384,  383,  381,  380,  367,  366,  363,  362,
 /*   290 */   361,  360,  359,  358,  357,  375,  356,  355,  354,  353,
 /*   300 */   352,  351,  350,  348,  347,  346,  344,  345,  343,  342,
 /*   310 */   341,  340,  338,  371,  370,  339,  335,  334,  333,  332,
 /*   320 */   331,  330,  329,  328,  327,
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
  "action",        "actions",     
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
 /* 165 */ "actionStmt ::= action",
 /* 166 */ "actionStmt ::= actions",
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
#line 907 "parser\\epparser.c"
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
  { 94, 1 },
  { 94, 1 },
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
#line 1371 "parser\\epparser.c"
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
#line 1382 "parser\\epparser.c"
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
#line 1393 "parser\\epparser.c"
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
#line 1421 "parser\\epparser.c"
        break;
      case 13: /* fdef_chunk ::= fdef_header stmt */
      case 155: /* foreach_stmt ::= foreach_header stmt */ yytestcase(yyruleno==155);
#line 118 "parser\\epparser.lemon"
{
    ps->gen.unindent(true);
    ps->closure.popScope();
}
#line 1430 "parser\\epparser.c"
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
#line 1441 "parser\\epparser.c"
        break;
      case 15: /* stmt ::= error SEMICOLON */
#line 132 "parser\\epparser.lemon"
{ throw_error(6974, "Error while parsing statement", yymsp[0].minor.yy0->line); delete yymsp[0].minor.yy0; }
#line 1446 "parser\\epparser.c"
        break;
      case 18: /* lbracket ::= LBRACKET */
#line 138 "parser\\epparser.lemon"
{ ps->closure.pushScope(); }
#line 1451 "parser\\epparser.c"
        break;
      case 19: /* rbracket ::= RBRACKET */
#line 139 "parser\\epparser.lemon"
{ ps->closure.popScope(); }
#line 1456 "parser\\epparser.c"
        break;
      case 20: /* blockStmt ::= lbracket RBRACKET */
#line 141 "parser\\epparser.lemon"
{
    ps->gen << "pass" << std::endl;
    ps->closure.popScope();
}
#line 1464 "parser\\epparser.c"
        break;
      case 24: /* blockStmt ::= lbracket error RBRACKET */
#line 148 "parser\\epparser.lemon"
{
    throw_error(6298, "Block not terminated properly.", yymsp[0].minor.yy0->line);
    ps->gen << "pass" << std::endl;
    ps->closure.popScope();
    delete yymsp[0].minor.yy0;
}
#line 1474 "parser\\epparser.c"
        break;
      case 31: /* bodyStmt ::= funcexpr SEMICOLON */
#line 161 "parser\\epparser.lemon"
{ ps->gen << yymsp[-1].minor.yy0->data << std::endl; }
#line 1479 "parser\\epparser.c"
        break;
      case 39: /* bodyStmtList ::= error */
#line 171 "parser\\epparser.lemon"
{
    throw_error(8510, "Incomplete statement");
    ps->gen << "pass" << std::endl;
}
#line 1487 "parser\\epparser.c"
        break;
      case 42: /* bodyStmtList ::= bodyStmtList error */
#line 178 "parser\\epparser.lemon"
{
    throw_error(8510, "Incomplete statement");
}
#line 1494 "parser\\epparser.c"
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
#line 1511 "parser\\epparser.c"
        break;
      case 44: /* numList_nonEmpty ::= numList_nonEmpty COMMA NUMBER */
      case 46: /* nameList_nonEmpty ::= nameList_nonEmpty COMMA NAME */ yytestcase(yyruleno==46);
      case 109: /* lvalueList_nonEmpty ::= lvalueList_nonEmpty COMMA lvalue */ yytestcase(yyruleno==109);
#line 185 "parser\\epparser.lemon"
{ yygotominor.yy0 = commaConcat(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1518 "parser\\epparser.c"
        break;
      case 47: /* nameList ::= */
      case 53: /* exprList ::= */ yytestcase(yyruleno==53);
      case 64: /* fArgs ::= */ yytestcase(yyruleno==64);
#line 188 "parser\\epparser.lemon"
{ yygotominor.yy0 = genEmpty(); }
#line 1525 "parser\\epparser.c"
        break;
      case 49: /* exprList_nonEmpty ::= funcexpr LSQBRACKET LSQBRACKET numList_nonEmpty RSQBRACKET RSQBRACKET */
#line 191 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "_SRET(" + yymsp[-5].minor.yy0->data + ", [" + yymsp[-2].minor.yy0->data + "])";
    delete yymsp[-5].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1534 "parser\\epparser.c"
        break;
      case 50: /* expr ::= funcexpr LSQBRACKET LSQBRACKET NUMBER RSQBRACKET RSQBRACKET */
#line 198 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-5].minor.yy0->data + "[" + yymsp[-2].minor.yy0->data + "]";
    delete yymsp[-5].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1543 "parser\\epparser.c"
        break;
      case 52: /* exprList_nonEmpty ::= exprList_nonEmpty COMMA exprList_nonEmpty */
#line 206 "parser\\epparser.lemon"
{ yygotominor.yy0 = new Token((yymsp[-2].minor.yy0->data) + ", " + (yymsp[0].minor.yy0->data), yymsp[0].minor.yy0); delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1548 "parser\\epparser.c"
        break;
      case 56: /* expr ::= KILLS */
#line 213 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = "4";
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1556 "parser\\epparser.c"
        break;
      case 57: /* expr ::= NAME */
#line 218 "parser\\epparser.lemon"
{
    checkIsRValue(yymsp[0].minor.yy0->data, yymsp[0].minor.yy0->line);
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1564 "parser\\epparser.c"
        break;
      case 58: /* expr ::= expr PERIOD NAME */
#line 223 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + "." + yymsp[0].minor.yy0->data;
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1573 "parser\\epparser.c"
        break;
      case 59: /* expr ::= expr LSQBRACKET expr RSQBRACKET */
#line 229 "parser\\epparser.lemon"
{
    yymsp[-3].minor.yy0->data = yymsp[-3].minor.yy0->data + "[" + yymsp[-1].minor.yy0->data + "]";
    delete yymsp[-1].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 1582 "parser\\epparser.c"
        break;
      case 62: /* fArgs_nonEmpty ::= NAME ASSIGN expr */
#line 238 "parser\\epparser.lemon"
{  // Keyword argument
    yymsp[0].minor.yy0->data = yymsp[-2].minor.yy0->data + "=" + yymsp[0].minor.yy0->data;
    yymsp[0].minor.yy0->type = TOKEN_TEMP;
    yygotominor.yy0 = yymsp[0].minor.yy0;
    delete yymsp[-2].minor.yy0;
}
#line 1592 "parser\\epparser.c"
        break;
      case 63: /* fArgs_nonEmpty ::= fArgs_nonEmpty COMMA fArgs_nonEmpty */
#line 245 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data;
    yymsp[0].minor.yy0->type = TOKEN_TEMP;
    yygotominor.yy0 = yymsp[0].minor.yy0;
    delete yymsp[-2].minor.yy0;
}
#line 1602 "parser\\epparser.c"
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
#line 1615 "parser\\epparser.c"
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
#line 1639 "parser\\epparser.c"
        break;
      case 69: /* expr ::= LPAREN expr RPAREN */
      case 90: /* lexpr ::= LPAREN lexpr RPAREN */ yytestcase(yyruleno==90);
#line 289 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1648 "parser\\epparser.c"
        break;
      case 70: /* expr ::= LSQBRACKET exprList RSQBRACKET */
#line 294 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "EUDArray(FlattenList([" + yymsp[-1].minor.yy0->data + "]))";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1656 "parser\\epparser.c"
        break;
      case 71: /* expr ::= L2V LPAREN lexpr RPAREN */
#line 299 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "_L2V(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = genTemp(yymsp[-1].minor.yy0);
}
#line 1664 "parser\\epparser.c"
        break;
      case 72: /* expr ::= MAPSTRING LPAREN STRING RPAREN */
#line 304 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetStringIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1672 "parser\\epparser.c"
        break;
      case 73: /* expr ::= UNIT LPAREN STRING RPAREN */
#line 309 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "EncodeUnit(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1680 "parser\\epparser.c"
        break;
      case 74: /* expr ::= SWITCH LPAREN STRING RPAREN */
#line 314 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "EncodeSwitch(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1688 "parser\\epparser.c"
        break;
      case 75: /* expr ::= LOCATION LPAREN STRING RPAREN */
#line 319 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetLocationIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1696 "parser\\epparser.c"
        break;
      case 76: /* expr ::= expr PLUS expr */
#line 325 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "+",  yymsp[0].minor.yy0); }
#line 1701 "parser\\epparser.c"
        break;
      case 77: /* expr ::= expr MINUS expr */
#line 326 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "-",  yymsp[0].minor.yy0); }
#line 1706 "parser\\epparser.c"
        break;
      case 78: /* expr ::= expr MULTIPLY expr */
#line 327 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "*",  yymsp[0].minor.yy0); }
#line 1711 "parser\\epparser.c"
        break;
      case 79: /* expr ::= expr DIVIDE expr */
#line 328 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "//", yymsp[0].minor.yy0); }
#line 1716 "parser\\epparser.c"
        break;
      case 80: /* expr ::= expr MOD expr */
#line 329 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "%",  yymsp[0].minor.yy0); }
#line 1721 "parser\\epparser.c"
        break;
      case 81: /* expr ::= expr LSHIFT expr */
#line 330 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "<<", yymsp[0].minor.yy0); }
#line 1726 "parser\\epparser.c"
        break;
      case 82: /* expr ::= expr RSHIFT expr */
#line 331 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, ">>", yymsp[0].minor.yy0); }
#line 1731 "parser\\epparser.c"
        break;
      case 83: /* expr ::= expr BITAND expr */
#line 332 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "&",  yymsp[0].minor.yy0); }
#line 1736 "parser\\epparser.c"
        break;
      case 84: /* expr ::= expr BITOR expr */
#line 333 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "|",  yymsp[0].minor.yy0); }
#line 1741 "parser\\epparser.c"
        break;
      case 85: /* expr ::= expr BITXOR expr */
#line 334 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "^",  yymsp[0].minor.yy0); }
#line 1746 "parser\\epparser.c"
        break;
      case 86: /* expr ::= PLUS expr */
#line 337 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = +" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1751 "parser\\epparser.c"
        break;
      case 87: /* expr ::= MINUS expr */
#line 338 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = -" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1756 "parser\\epparser.c"
        break;
      case 88: /* expr ::= BITNOT expr */
#line 339 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = ~" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1761 "parser\\epparser.c"
        break;
      case 91: /* lexpr ::= expr EQ expr */
#line 349 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "==", yymsp[0].minor.yy0); }
#line 1766 "parser\\epparser.c"
        break;
      case 92: /* lexpr ::= expr NE expr */
#line 350 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "!=", yymsp[0].minor.yy0); }
#line 1771 "parser\\epparser.c"
        break;
      case 93: /* lexpr ::= expr LE expr */
#line 351 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "<=", yymsp[0].minor.yy0); }
#line 1776 "parser\\epparser.c"
        break;
      case 94: /* lexpr ::= expr LT expr */
#line 352 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "<",  yymsp[0].minor.yy0); }
#line 1781 "parser\\epparser.c"
        break;
      case 95: /* lexpr ::= expr GE expr */
#line 353 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, ">=", yymsp[0].minor.yy0); }
#line 1786 "parser\\epparser.c"
        break;
      case 96: /* lexpr ::= expr GT expr */
#line 354 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, ">" , yymsp[0].minor.yy0); }
#line 1791 "parser\\epparser.c"
        break;
      case 97: /* lexpr ::= lexpr LAND lexpr */
#line 357 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "[" + yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data + "]";
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1800 "parser\\epparser.c"
        break;
      case 98: /* lexpr ::= lexpr LOR lexpr */
#line 363 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "EUDOr([" + yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data + "])";
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1809 "parser\\epparser.c"
        break;
      case 99: /* lexpr ::= LNOT lexpr */
#line 369 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = "EUDNot([" + yymsp[0].minor.yy0->data + "])";
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0);
}
#line 1817 "parser\\epparser.c"
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
#line 1841 "parser\\epparser.c"
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
#line 1866 "parser\\epparser.c"
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
#line 1890 "parser\\epparser.c"
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
#line 1912 "parser\\epparser.c"
        break;
      case 105: /* lvalue ::= NAME */
#line 463 "parser\\epparser.lemon"
{
    checkIsVariable(yymsp[0].minor.yy0->data, yymsp[0].minor.yy0->line);
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1920 "parser\\epparser.c"
        break;
      case 106: /* lvalue ::= expr LSQBRACKET expr RSQBRACKET */
#line 468 "parser\\epparser.lemon"
{
    checkIsConstant(yymsp[-3].minor.yy0->data, yymsp[-3].minor.yy0->line);
    yymsp[-1].minor.yy0->data = "_ARRW(" + yymsp[-3].minor.yy0->data + ", " + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
    delete yymsp[-3].minor.yy0;
}
#line 1930 "parser\\epparser.c"
        break;
      case 107: /* lvalue ::= expr PERIOD NAME */
#line 475 "parser\\epparser.lemon"
{
    checkIsConstant(yymsp[-2].minor.yy0->data, yymsp[-2].minor.yy0->line);
    yymsp[0].minor.yy0->data = "_ATTW(" + yymsp[-2].minor.yy0->data + ", '" + yymsp[0].minor.yy0->data + "')";
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0);
    delete yymsp[-2].minor.yy0;
}
#line 1940 "parser\\epparser.c"
        break;
      case 110: /* assign_stmt ::= lvalue ASSIGN expr */
#line 484 "parser\\epparser.lemon"
{
    ps->gen << yymsp[-2].minor.yy0->data << " << (" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 1948 "parser\\epparser.c"
        break;
      case 111: /* assign_stmt ::= lvalueList_nonEmpty ASSIGN exprList_nonEmpty */
#line 489 "parser\\epparser.lemon"
{
    ps->gen << "_SV([" << yymsp[-2].minor.yy0->data << "], [" << yymsp[0].minor.yy0->data << "])" << std::endl;
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 1956 "parser\\epparser.c"
        break;
      case 112: /* assign_stmt ::= INC expr */
#line 497 "parser\\epparser.lemon"
{ ps->gen << yymsp[0].minor.yy0->data << ".__iadd__(1)" << std::endl; delete yymsp[0].minor.yy0; }
#line 1961 "parser\\epparser.c"
        break;
      case 113: /* assign_stmt ::= expr INC */
#line 498 "parser\\epparser.lemon"
{ ps->gen << yymsp[-1].minor.yy0->data << ".__iadd__(1)" << std::endl; delete yymsp[-1].minor.yy0; }
#line 1966 "parser\\epparser.c"
        break;
      case 114: /* assign_stmt ::= DEC expr */
#line 499 "parser\\epparser.lemon"
{ ps->gen << yymsp[0].minor.yy0->data << ".__isub__(1)" << std::endl; delete yymsp[0].minor.yy0; }
#line 1971 "parser\\epparser.c"
        break;
      case 115: /* assign_stmt ::= expr DEC */
#line 500 "parser\\epparser.lemon"
{ ps->gen << yymsp[-1].minor.yy0->data << ".__isub__(1)" << std::endl; delete yymsp[-1].minor.yy0; }
#line 1976 "parser\\epparser.c"
        break;
      case 116: /* assign_stmt ::= lvalue IADD expr */
#line 501 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__iadd__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1981 "parser\\epparser.c"
        break;
      case 117: /* assign_stmt ::= lvalue ISUB expr */
#line 502 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__isub__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1986 "parser\\epparser.c"
        break;
      case 118: /* assign_stmt ::= lvalue IMUL expr */
#line 503 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__imul__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1991 "parser\\epparser.c"
        break;
      case 119: /* assign_stmt ::= lvalue IDIV expr */
#line 504 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ifloordiv__("  << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1996 "parser\\epparser.c"
        break;
      case 120: /* assign_stmt ::= lvalue IMOD expr */
#line 505 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__imod__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2001 "parser\\epparser.c"
        break;
      case 121: /* assign_stmt ::= lvalue ILSH expr */
#line 506 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ilshift__("    << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2006 "parser\\epparser.c"
        break;
      case 122: /* assign_stmt ::= lvalue IRSH expr */
#line 507 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__irshift__("    << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2011 "parser\\epparser.c"
        break;
      case 123: /* assign_stmt ::= lvalue IBND expr */
#line 508 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__iand__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2016 "parser\\epparser.c"
        break;
      case 124: /* assign_stmt ::= lvalue IBOR expr */
#line 509 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ior__("        << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2021 "parser\\epparser.c"
        break;
      case 125: /* assign_stmt ::= lvalue IBXR expr */
#line 510 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ixor__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2026 "parser\\epparser.c"
        break;
      case 126: /* if_start ::= IF */
#line 513 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDIf()" << std::endl;
}
#line 2034 "parser\\epparser.c"
        break;
      case 127: /* if_header ::= if_start LPAREN lexpr RPAREN */
      case 136: /* while_header ::= while_start LPAREN lexpr RPAREN */ yytestcase(yyruleno==136);
#line 518 "parser\\epparser.lemon"
{
    ps->gen << "if " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data << "):" << std::endl;
    ps->gen.indent();
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 2044 "parser\\epparser.c"
        break;
      case 129: /* elif_start ::= ELSE IF */
#line 526 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen.unindent(false);
    ps->gen << yygotominor.yy0->data << " = EUDElseIf()" << std::endl;
}
#line 2053 "parser\\epparser.c"
        break;
      case 130: /* elif_header ::= elif_start LPAREN lexpr RPAREN */
#line 532 "parser\\epparser.lemon"
{
    ps->gen << "if " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data <<"):" << std::endl;
    ps->gen.indent();
}
#line 2061 "parser\\epparser.c"
        break;
      case 132: /* else_header ::= ELSE */
#line 539 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "if EUDElse()():" << std::endl;
    ps->gen.indent();
}
#line 2070 "parser\\epparser.c"
        break;
      case 133: /* if_stmt ::= if_block */
      case 134: /* if_stmt ::= if_block else_header stmt */ yytestcase(yyruleno==134);
#line 545 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndIf()" << std::endl;
}
#line 2079 "parser\\epparser.c"
        break;
      case 135: /* while_start ::= WHILE */
#line 557 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDWhile()" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2088 "parser\\epparser.c"
        break;
      case 137: /* while_stmt ::= while_header stmt */
#line 569 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndWhile()" << std::endl;
}
#line 2096 "parser\\epparser.c"
        break;
      case 138: /* for_opener ::= FOR LPAREN */
      case 153: /* foreach_opener ::= FOREACH LPAREN */ yytestcase(yyruleno==153);
#line 575 "parser\\epparser.lemon"
{
    ps->closure.pushScope();
}
#line 2104 "parser\\epparser.c"
        break;
      case 148: /* for_header1 ::= for_opener for_init_stmt SEMICOLON */
#line 591 "parser\\epparser.lemon"
{
    // opening for lexpr
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDWhile()" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2114 "parser\\epparser.c"
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
#line 2128 "parser\\epparser.c"
        break;
      case 150: /* for_header ::= for_header2 for_action_stmt_nonEmpty RPAREN */
#line 609 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-2].minor.yy0;
    ps->gen.unindent(false);
}
#line 2136 "parser\\epparser.c"
        break;
      case 151: /* for_header ::= for_header2 RPAREN */
#line 614 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
    ps->gen << "pass" << std::endl;
    ps->gen.unindent(false);
}
#line 2145 "parser\\epparser.c"
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
#line 2156 "parser\\epparser.c"
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
#line 2167 "parser\\epparser.c"
        break;
      case 156: /* continue_stmt ::= CONTINUE */
#line 651 "parser\\epparser.lemon"
{
    ps->gen << "EUDContinue()" << std::endl;
}
#line 2174 "parser\\epparser.c"
        break;
      case 157: /* break_stmt ::= BREAK */
#line 655 "parser\\epparser.lemon"
{
    ps->gen << "EUDBreak()" << std::endl;
}
#line 2181 "parser\\epparser.c"
        break;
      case 158: /* return_stmt ::= RETURN exprList */
#line 662 "parser\\epparser.lemon"
{
    ps->gen << "EUDReturn(" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2189 "parser\\epparser.c"
        break;
      case 159: /* lexpr ::= CONDITIONNAME LPAREN fArgs RPAREN */
      case 160: /* lexpr ::= KILLS LPAREN fArgs RPAREN */ yytestcase(yyruleno==160);
#line 670 "parser\\epparser.lemon"
{
    yymsp[-3].minor.yy0->data = yymsp[-3].minor.yy0->data + "(" + yymsp[-1].minor.yy0->data + ")";
    delete yymsp[-1].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 2199 "parser\\epparser.c"
        break;
      case 161: /* lexpr ::= CONDITIONNAME LPAREN RPAREN */
#line 682 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + "()";
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 2207 "parser\\epparser.c"
        break;
      case 162: /* action ::= ACTIONNAME LPAREN fArgs RPAREN SEMICOLON */
#line 687 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[-4].minor.yy0);
    yygotominor.yy0->data =  yymsp[-4].minor.yy0->data + "(" + yymsp[-2].minor.yy0->data + ")";
    delete yymsp[-4].minor.yy0; delete yymsp[-2].minor.yy0;
}
#line 2216 "parser\\epparser.c"
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
#line 2239 "parser\\epparser.c"
        break;
      case 165: /* actionStmt ::= action */
#line 731 "parser\\epparser.lemon"
{
    ps->gen << "DoActions(" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2247 "parser\\epparser.c"
        break;
      case 166: /* actionStmt ::= actions */
#line 736 "parser\\epparser.lemon"
{
    ps->gen << "DoActions([" << std::endl;
    ps->gen.indent();
    ps->gen << yymsp[0].minor.yy0->data << std::endl;
    ps->gen.unindent(false);
    ps->gen << "])" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2259 "parser\\epparser.c"
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
#line 2350 "parser\\epparser.c"
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
#line 750 "parser\\epparser.lemon"


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
#line 2604 "parser\\epparser.c"
