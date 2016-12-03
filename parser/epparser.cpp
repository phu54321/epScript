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
#line 31 "parser\\epparser.c"
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
#define YYNOCODE 128
#define YYACTIONTYPE unsigned short int
#define ParseTOKENTYPE Token*
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  int yy255;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL  ParserStruct* ps ;
#define ParseARG_PDECL , ParserStruct* ps 
#define ParseARG_FETCH  ParserStruct* ps  = yypParser->ps 
#define ParseARG_STORE yypParser->ps  = ps 
#define YYNSTATE 310
#define YYNRULE 157
#define YYERRORSYMBOL 69
#define YYERRSYMDT yy255
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
#define YY_ACTTAB_COUNT (1294)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   200,  308,  227,  186,   18,   37,  201,  196,   72,  194,
 /*    10 */   286,  184,  306,   98,  296,  294,  199,    2,  111,  133,
 /*    20 */   195,  193,  137,  278,  277,  276,  275,  274,  188,  187,
 /*    30 */   305,  226,   98,  182,  304,   28,   29,  111,  133,  151,
 /*    40 */     8,   39,  177,  105,  158,  148,    6,   10,   67,   68,
 /*    50 */    66,   22,   13,    5,   77,    4,   76,   75,  200,   18,
 /*    60 */   227,  186,  201,   72,  254,  196,  184,  194,  286,   36,
 /*    70 */   201,   98,  242,  294,  199,    2,  111,  133,  195,  193,
 /*    80 */   137,  278,  277,  276,  275,  274,  188,  187,   14,  132,
 /*    90 */    98,  182,  300,   28,   29,  111,  133,  151,    8,   39,
 /*   100 */   177,  105,  217,  148,    6,   10,  205,  186,  204,   22,
 /*   110 */    13,    5,   77,    4,   76,   75,  200,  106,  225,  183,
 /*   120 */   156,  280,  243,  196,  302,  194,  286,   28,   29,  192,
 /*   130 */   239,  294,  199,    2,   34,   35,  195,  193,  137,  278,
 /*   140 */   277,  276,  275,  274,  188,  187,   32,  201,   98,  301,
 /*   150 */   186,  228,   73,  111,  133,  151,    8,   39,   28,   29,
 /*   160 */    83,  148,    6,   10,  122,  186,  299,   22,   13,    5,
 /*   170 */    77,    4,   76,   75,  200,  106,  182,  183,  157,   28,
 /*   180 */    29,  196,  186,  194,  286,  260,  105,  240,  236,  294,
 /*   190 */   199,    2,   86,  295,  195,  193,  137,  278,  277,  276,
 /*   200 */   275,  274,  188,  187,  179,  293,   98,  182,  237,   82,
 /*   210 */    38,  111,  133,  151,    8,   39,  154,  105,  297,  148,
 /*   220 */     6,   10,   81,  186,  298,   22,   13,    5,   77,    4,
 /*   230 */    76,   75,  200,  106,  182,  183,  162,  201,  178,  196,
 /*   240 */   221,  194,  286,  153,  105,  284,  223,  294,  199,    2,
 /*   250 */   468,   11,  195,  193,  137,  278,  277,  276,  275,  274,
 /*   260 */   188,  187,  191,  283,   98,  149,    7,    3,  282,  111,
 /*   270 */   133,  151,    8,   39,  281,  190,  189,  148,    6,   10,
 /*   280 */   279,  186,  273,   22,   13,    5,   77,    4,   76,   75,
 /*   290 */   200,  106,  182,  183,  142,  272,  192,  196,   33,  194,
 /*   300 */   286,  152,  105,   19,  220,  294,  199,    2,  267,  181,
 /*   310 */   195,  193,  137,  278,  277,  276,  275,  274,  188,  187,
 /*   320 */    31,   80,   98,  186,  186,  262,   38,  111,  133,  151,
 /*   330 */     8,   39,  261,   98,   85,  148,    6,   10,  245,  186,
 /*   340 */    30,   22,   13,    5,   77,    4,   76,   75,  200,  106,
 /*   350 */   182,  183,  159,   17,  173,  196,  186,  194,  286,  130,
 /*   360 */   105,  259,  213,  294,  199,    2,  117,  172,  195,  193,
 /*   370 */   137,  278,  277,  276,  275,  274,  188,  187,  170,  169,
 /*   380 */    98,  182,  186,  258,  167,  111,  133,  151,    8,   39,
 /*   390 */   139,  105,   83,  148,    6,   10,  253,  186,  186,   22,
 /*   400 */    13,    5,   77,    4,   76,   75,  140,  106,   83,  264,
 /*   410 */   186,  166,  161,  196,  257,  194,  286,  164,  163,  256,
 /*   420 */    83,  211,  198,    2,  252,    1,  195,  193,  137,  278,
 /*   430 */   277,  276,  275,  274,  188,  187,  255,   29,   98,  186,
 /*   440 */   186,   15,   25,  111,  133,  151,    8,   39,  250,  116,
 /*   450 */    83,  148,    6,   10,  251,  186,  186,   22,   13,    5,
 /*   460 */    77,    4,   76,   75,  270,   83,   83,  186,  186,  121,
 /*   470 */   120,  196,  248,  194,  286,  109,  247,  128,  127,  271,
 /*   480 */   197,    2,  288,  246,  195,  193,  137,  278,  277,  276,
 /*   490 */   275,  274,  188,  187,   24,  241,   98,  186,  186,   23,
 /*   500 */   235,  111,  133,  151,    8,   39,  229,  126,   83,  148,
 /*   510 */     6,   10,  119,  222,  186,   22,   13,    5,   77,    4,
 /*   520 */    76,   75,   60,   59,  115,   12,  186,   16,   58,  269,
 /*   530 */   107,  285,  186,  141,  216,   71,   83,  292,  291,   21,
 /*   540 */   118,  268,  114,  212,  289,  176,  174,  171,  168,  165,
 /*   550 */    79,   78,   65,   64,   70,   69,   67,   68,   66,  290,
 /*   560 */   287,  136,  244,  186,  238,  147,  144,   18,  219,  218,
 /*   570 */    20,   72,  143,  113,  184,  180,  186,  135,  297,  134,
 /*   580 */   131,   60,   59,  186,  215,  186,  110,   58,  269,  107,
 /*   590 */   285,  214,  143,  112,   71,  125,  292,  290,   21,  129,
 /*   600 */   268,  186,  186,  138,  176,  174,  171,  168,  165,   79,
 /*   610 */    78,  124,  123,   70,   69,   67,   68,   66,  469,  150,
 /*   620 */   469,  244,  186,  238,  147,  144,   18,  219,  218,   20,
 /*   630 */    72,  143,  104,  184,  186,  469,  469,  469,  469,  469,
 /*   640 */    60,   59,  186,  469,  103,  469,   58,  269,  107,  285,
 /*   650 */   186,  469,  102,   71,  469,  292,  469,   21,  469,  268,
 /*   660 */   101,  186,  186,  176,  174,  171,  168,  165,   79,   78,
 /*   670 */   469,  100,   99,  469,  469,  186,  469,  469,  469,  186,
 /*   680 */   244,  469,  238,  147,  144,   84,  219,  218,   20,   97,
 /*   690 */   143,   57,   55,   54,   53,   52,   56,   62,   61,   63,
 /*   700 */    65,   64,   70,   69,   67,   68,   66,   27,  186,  469,
 /*   710 */   469,  469,  469,  469,  186,   18,  469,  469,   96,   72,
 /*   720 */    60,   59,  184,  469,   95,  186,   58,  269,  185,  469,
 /*   730 */   469,  469,  186,   71,  469,   94,  469,   21,  186,  175,
 /*   740 */   186,  469,   93,  176,  174,  171,  168,  165,   92,  469,
 /*   750 */    91,   26,  310,  186,  309,  210,  307,  209,  208,  207,
 /*   760 */   303,  202,    9,   90,   60,   59,  469,    2,  469,  160,
 /*   770 */    58,  269,  185,  469,  186,  469,  186,   71,  469,  469,
 /*   780 */   206,   21,  203,  175,   89,  292,   88,  176,  174,  171,
 /*   790 */   168,  165,  469,  469,  186,  469,  469,  469,   74,   78,
 /*   800 */   469,  469,   60,   59,   87,  469,  469,  469,   58,  269,
 /*   810 */   185,  469,  469,  160,  469,   71,  249,  469,  469,   21,
 /*   820 */   469,  268,  469,  265,  469,  176,  174,  171,  168,  165,
 /*   830 */   469,  469,   60,   59,  469,  469,  469,  469,   58,  269,
 /*   840 */   107,  469,  469,  469,  469,   71,  469,  469,  469,   21,
 /*   850 */   469,  268,  469,  469,  469,  176,  174,  171,  168,  165,
 /*   860 */    79,   78,  469,   62,   61,   63,   65,   64,   70,   69,
 /*   870 */    67,   68,   66,  469,  469,  469,  469,  469,  469,  469,
 /*   880 */   469,   18,  469,  469,  469,   72,  266,  469,  184,  469,
 /*   890 */   469,  469,  469,  469,  469,   62,   61,   63,   65,   64,
 /*   900 */    70,   69,   67,   68,   66,  469,  469,  469,  469,  469,
 /*   910 */   469,  469,  469,   18,  263,  469,  469,   72,  469,  469,
 /*   920 */   184,  469,  469,  469,  469,  469,  469,   62,   61,   63,
 /*   930 */    65,   64,   70,   69,   67,   68,   66,  469,  469,  469,
 /*   940 */   469,  469,  469,  469,  469,   18,  469,   60,   59,   72,
 /*   950 */   108,  469,  184,   58,  269,  185,  469,  469,  469,  469,
 /*   960 */    71,  469,  469,  469,   21,  469,  268,  469,  265,  469,
 /*   970 */   176,  174,  171,  168,  165,  469,  469,  469,  469,   60,
 /*   980 */    59,  469,  469,  469,  469,   58,  269,  107,  469,  469,
 /*   990 */   469,  469,   71,  224,  469,  469,   21,  469,  268,  469,
 /*  1000 */   469,  469,  176,  174,  171,  168,  165,  364,  364,  364,
 /*  1010 */   364,  364,  364,  364,  364,  364,  364,  469,  469,  469,
 /*  1020 */   469,  469,  469,  469,  469,   19,  469,  469,  469,  364,
 /*  1030 */   469,  469,  364,  469,  469,  469,  469,  469,  469,   62,
 /*  1040 */    61,   63,   65,   64,   70,   69,   67,   68,   66,  469,
 /*  1050 */   469,  469,  469,  469,  469,  469,  469,   18,  469,  469,
 /*  1060 */   469,   72,  469,  469,  184,  469,  469,  469,  469,  469,
 /*  1070 */   469,   62,   61,   63,   65,   64,   70,   69,   67,   68,
 /*  1080 */    66,  469,  469,  469,  469,  469,  469,  469,  469,   18,
 /*  1090 */   469,   60,   59,   51,  469,  469,  155,   58,  269,  185,
 /*  1100 */   469,  469,  469,  469,   71,  469,  469,  469,   21,  469,
 /*  1110 */   268,  469,  469,  469,  176,  174,  171,  168,  165,  469,
 /*  1120 */   469,  469,  469,   60,   59,  469,  469,  469,  469,   58,
 /*  1130 */   269,  107,  411,  411,  469,  469,   71,  469,  469,  469,
 /*  1140 */    21,  469,  268,  469,  410,  410,  176,  174,  171,  168,
 /*  1150 */   165,   61,   63,   65,   64,   70,   69,   67,   68,   66,
 /*  1160 */   469,  469,  469,  469,  469,  469,  469,  469,   18,  469,
 /*  1170 */   469,  469,   72,  469,  469,  184,  469,  469,  469,  411,
 /*  1180 */   411,  411,  411,  411,  411,  411,  411,  411,  411,   50,
 /*  1190 */   469,  410,  410,  410,  410,  410,  410,  410,  410,  410,
 /*  1200 */   410,   63,   65,   64,   70,   69,   67,   68,   66,  469,
 /*  1210 */   469,  469,  469,  469,  469,  469,  469,   18,  469,  469,
 /*  1220 */   469,   72,  469,  469,  184,  469,  469,  469,  469,  469,
 /*  1230 */   469,  469,  469,  234,  469,  232,   49,   48,   47,   46,
 /*  1240 */    45,   44,   43,   42,   41,   40,  233,  231,  186,  469,
 /*  1250 */   469,  469,  234,  469,  232,  469,  469,  469,   98,  469,
 /*  1260 */   469,  469,  469,  111,  133,  233,  231,  186,  469,  469,
 /*  1270 */   469,  469,  469,  469,  146,  145,  469,   98,  469,  469,
 /*  1280 */   469,  469,  111,  133,  469,  469,  469,  469,  469,  469,
 /*  1290 */   469,  469,  469,  230,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    69,   27,   90,   91,   31,    1,    2,   76,   35,   78,
 /*    10 */    79,   38,   27,  101,   83,   84,   85,   86,  106,  107,
 /*    20 */    89,   90,   91,   92,   93,   94,   95,   96,   97,   98,
 /*    30 */    27,  119,  101,   91,   27,    3,    4,  106,  107,  108,
 /*    40 */   109,  110,  100,  101,  102,  114,  115,  116,   20,   21,
 /*    50 */    22,  120,  121,  122,  123,  124,  125,  126,   69,   31,
 /*    60 */    90,   91,    2,   35,   32,   76,   38,   78,   79,    1,
 /*    70 */     2,  101,   83,   84,   85,   86,  106,  107,   89,   90,
 /*    80 */    91,   92,   93,   94,   95,   96,   97,   98,    2,  119,
 /*    90 */   101,   91,   32,    3,    4,  106,  107,  108,  109,  110,
 /*   100 */   100,  101,  102,  114,  115,  116,   26,   91,   29,  120,
 /*   110 */   121,  122,  123,  124,  125,  126,   69,  101,   32,  103,
 /*   120 */   104,   27,   32,   76,   26,   78,   79,    3,    4,   35,
 /*   130 */    83,   84,   85,   86,    1,    2,   89,   90,   91,   92,
 /*   140 */    93,   94,   95,   96,   97,   98,    1,    2,  101,   26,
 /*   150 */    91,   27,   31,  106,  107,  108,  109,  110,    3,    4,
 /*   160 */   101,  114,  115,  116,  105,   91,   26,  120,  121,  122,
 /*   170 */   123,  124,  125,  126,   69,  101,   91,  103,  104,    3,
 /*   180 */     4,   76,   91,   78,   79,  100,  101,   32,   83,   84,
 /*   190 */    85,   86,  101,   27,   89,   90,   91,   92,   93,   94,
 /*   200 */    95,   96,   97,   98,    2,   27,  101,   91,   32,   27,
 /*   210 */     2,  106,  107,  108,  109,  110,  100,  101,   26,  114,
 /*   220 */   115,  116,   27,   91,   32,  120,  121,  122,  123,  124,
 /*   230 */   125,  126,   69,  101,   91,  103,  104,    2,   36,   76,
 /*   240 */    32,   78,   79,  100,  101,   27,   83,   84,   85,   86,
 /*   250 */    71,   72,   89,   90,   91,   92,   93,   94,   95,   96,
 /*   260 */    97,   98,   35,   27,  101,  111,  112,  113,   27,  106,
 /*   270 */   107,  108,  109,  110,   27,   25,   36,  114,  115,  116,
 /*   280 */    36,   91,   27,  120,  121,  122,  123,  124,  125,  126,
 /*   290 */    69,  101,   91,  103,  104,   27,   35,   76,   63,   78,
 /*   300 */    79,  100,  101,   31,   83,   84,   85,   86,   26,   35,
 /*   310 */    89,   90,   91,   92,   93,   94,   95,   96,   97,   98,
 /*   320 */     2,   35,  101,   91,   91,   25,    2,  106,  107,  108,
 /*   330 */   109,  110,   36,  101,  101,  114,  115,  116,  106,   91,
 /*   340 */    31,  120,  121,  122,  123,  124,  125,  126,   69,  101,
 /*   350 */    91,  103,  104,   31,   31,   76,   91,   78,   79,  100,
 /*   360 */   101,   32,   83,   84,   85,   86,  101,   39,   89,   90,
 /*   370 */    91,   92,   93,   94,   95,   96,   97,   98,   31,   39,
 /*   380 */   101,   91,   91,   32,   31,  106,  107,  108,  109,  110,
 /*   390 */   100,  101,  101,  114,  115,  116,  105,   91,   91,  120,
 /*   400 */   121,  122,  123,  124,  125,  126,   69,  101,  101,  103,
 /*   410 */    91,   39,  105,   76,   32,   78,   79,   31,   39,   32,
 /*   420 */   101,   84,   85,   86,  105,   88,   89,   90,   91,   92,
 /*   430 */    93,   94,   95,   96,   97,   98,   32,    4,  101,   91,
 /*   440 */    91,   31,   31,  106,  107,  108,  109,  110,   32,  101,
 /*   450 */   101,  114,  115,  116,  105,   91,   91,  120,  121,  122,
 /*   460 */   123,  124,  125,  126,   69,  101,  101,   91,   91,  105,
 /*   470 */   105,   76,   36,   78,   79,   26,   32,  101,  101,   84,
 /*   480 */    85,   86,   87,   32,   89,   90,   91,   92,   93,   94,
 /*   490 */    95,   96,   97,   98,   31,   58,  101,   91,   91,   31,
 /*   500 */    31,  106,  107,  108,  109,  110,   27,  101,  101,  114,
 /*   510 */   115,  116,  105,   31,   91,  120,  121,  122,  123,  124,
 /*   520 */   125,  126,   18,   19,  101,    2,   91,   31,   24,   25,
 /*   530 */    26,   27,   91,   32,   27,   31,  101,   33,   34,   35,
 /*   540 */   105,   37,  101,   34,   87,   41,   42,   43,   44,   45,
 /*   550 */    46,   47,   16,   17,   18,   19,   20,   21,   22,   34,
 /*   560 */    87,   99,   58,   91,   60,   61,   62,   31,   64,   65,
 /*   570 */    66,   35,   68,  101,   38,   25,   91,   82,   26,   82,
 /*   580 */    82,   18,   19,   91,  125,   91,  101,   24,   25,   26,
 /*   590 */    27,  125,   68,  101,   31,  101,   33,   34,   35,   82,
 /*   600 */    37,   91,   91,   82,   41,   42,   43,   44,   45,   46,
 /*   610 */    47,  101,  101,   18,   19,   20,   21,   22,  127,   59,
 /*   620 */   127,   58,   91,   60,   61,   62,   31,   64,   65,   66,
 /*   630 */    35,   68,  101,   38,   91,  127,  127,  127,  127,  127,
 /*   640 */    18,   19,   91,  127,  101,  127,   24,   25,   26,   27,
 /*   650 */    91,  127,  101,   31,  127,   33,  127,   35,  127,   37,
 /*   660 */   101,   91,   91,   41,   42,   43,   44,   45,   46,   47,
 /*   670 */   127,  101,  101,  127,  127,   91,  127,  127,  127,   91,
 /*   680 */    58,  127,   60,   61,   62,  101,   64,   65,   66,  101,
 /*   690 */    68,    7,    8,    9,   10,   11,   12,   13,   14,   15,
 /*   700 */    16,   17,   18,   19,   20,   21,   22,    5,   91,  127,
 /*   710 */   127,  127,  127,  127,   91,   31,  127,  127,  101,   35,
 /*   720 */    18,   19,   38,  127,  101,   91,   24,   25,   26,  127,
 /*   730 */   127,  127,   91,   31,  127,  101,  127,   35,   91,   37,
 /*   740 */    91,  127,  101,   41,   42,   43,   44,   45,  101,  127,
 /*   750 */   101,    5,    0,   91,   73,   74,   75,   76,   77,   78,
 /*   760 */    79,   80,   81,  101,   18,   19,  127,   86,  127,   67,
 /*   770 */    24,   25,   26,  127,   91,  127,   91,   31,  127,  127,
 /*   780 */    28,   35,   30,   37,  101,   33,  101,   41,   42,   43,
 /*   790 */    44,   45,  127,  127,   91,  127,  127,  127,   46,   47,
 /*   800 */   127,  127,   18,   19,  101,  127,  127,  127,   24,   25,
 /*   810 */    26,  127,  127,   67,  127,   31,   32,  127,  127,   35,
 /*   820 */   127,   37,  127,   39,  127,   41,   42,   43,   44,   45,
 /*   830 */   127,  127,   18,   19,  127,  127,  127,  127,   24,   25,
 /*   840 */    26,  127,  127,  127,  127,   31,  127,  127,  127,   35,
 /*   850 */   127,   37,  127,  127,  127,   41,   42,   43,   44,   45,
 /*   860 */    46,   47,  127,   13,   14,   15,   16,   17,   18,   19,
 /*   870 */    20,   21,   22,  127,  127,  127,  127,  127,  127,  127,
 /*   880 */   127,   31,  127,  127,  127,   35,   36,  127,   38,  127,
 /*   890 */   127,  127,  127,  127,  127,   13,   14,   15,   16,   17,
 /*   900 */    18,   19,   20,   21,   22,  127,  127,  127,  127,  127,
 /*   910 */   127,  127,  127,   31,   32,  127,  127,   35,  127,  127,
 /*   920 */    38,  127,  127,  127,  127,  127,  127,   13,   14,   15,
 /*   930 */    16,   17,   18,   19,   20,   21,   22,  127,  127,  127,
 /*   940 */   127,  127,  127,  127,  127,   31,  127,   18,   19,   35,
 /*   950 */    36,  127,   38,   24,   25,   26,  127,  127,  127,  127,
 /*   960 */    31,  127,  127,  127,   35,  127,   37,  127,   39,  127,
 /*   970 */    41,   42,   43,   44,   45,  127,  127,  127,  127,   18,
 /*   980 */    19,  127,  127,  127,  127,   24,   25,   26,  127,  127,
 /*   990 */   127,  127,   31,   32,  127,  127,   35,  127,   37,  127,
 /*  1000 */   127,  127,   41,   42,   43,   44,   45,   13,   14,   15,
 /*  1010 */    16,   17,   18,   19,   20,   21,   22,  127,  127,  127,
 /*  1020 */   127,  127,  127,  127,  127,   31,  127,  127,  127,   35,
 /*  1030 */   127,  127,   38,  127,  127,  127,  127,  127,  127,   13,
 /*  1040 */    14,   15,   16,   17,   18,   19,   20,   21,   22,  127,
 /*  1050 */   127,  127,  127,  127,  127,  127,  127,   31,  127,  127,
 /*  1060 */   127,   35,  127,  127,   38,  127,  127,  127,  127,  127,
 /*  1070 */   127,   13,   14,   15,   16,   17,   18,   19,   20,   21,
 /*  1080 */    22,  127,  127,  127,  127,  127,  127,  127,  127,   31,
 /*  1090 */   127,   18,   19,   35,  127,  127,   38,   24,   25,   26,
 /*  1100 */   127,  127,  127,  127,   31,  127,  127,  127,   35,  127,
 /*  1110 */    37,  127,  127,  127,   41,   42,   43,   44,   45,  127,
 /*  1120 */   127,  127,  127,   18,   19,  127,  127,  127,  127,   24,
 /*  1130 */    25,   26,    1,    2,  127,  127,   31,  127,  127,  127,
 /*  1140 */    35,  127,   37,  127,    1,    2,   41,   42,   43,   44,
 /*  1150 */    45,   14,   15,   16,   17,   18,   19,   20,   21,   22,
 /*  1160 */   127,  127,  127,  127,  127,  127,  127,  127,   31,  127,
 /*  1170 */   127,  127,   35,  127,  127,   38,  127,  127,  127,   48,
 /*  1180 */    49,   50,   51,   52,   53,   54,   55,   56,   57,    1,
 /*  1190 */   127,   48,   49,   50,   51,   52,   53,   54,   55,   56,
 /*  1200 */    57,   15,   16,   17,   18,   19,   20,   21,   22,  127,
 /*  1210 */   127,  127,  127,  127,  127,  127,  127,   31,  127,  127,
 /*  1220 */   127,   35,  127,  127,   38,  127,  127,  127,  127,  127,
 /*  1230 */   127,  127,  127,   76,  127,   78,   48,   49,   50,   51,
 /*  1240 */    52,   53,   54,   55,   56,   57,   89,   90,   91,  127,
 /*  1250 */   127,  127,   76,  127,   78,  127,  127,  127,  101,  127,
 /*  1260 */   127,  127,  127,  106,  107,   89,   90,   91,  127,  127,
 /*  1270 */   127,  127,  127,  127,  117,  118,  127,  101,  127,  127,
 /*  1280 */   127,  127,  106,  107,  127,  127,  127,  127,  127,  127,
 /*  1290 */   127,  127,  127,  117,
};
#define YY_SHIFT_USE_DFLT (-28)
#define YY_SHIFT_COUNT (210)
#define YY_SHIFT_MIN   (-27)
#define YY_SHIFT_MAX   (1188)
static const short yy_shift_ofst[] = {
 /*     0 */   -28,  563,  504,  622,  622,  622,  622,  622,  622,  622,
 /*    10 */   814,  752,  814,  961, 1105,  784,  929,  929,  929,  929,
 /*    20 */  1073, 1073,  702,  702,  702,  702,  746,  746,  702,  702,
 /*    30 */   702,  929, 1073, 1073, 1073, 1105, 1073, 1073, 1073,  560,
 /*    40 */  1073, 1073, 1073, 1073, 1073, 1073, 1073, 1073, 1073, 1073,
 /*    50 */  1073, 1073, 1073, 1073, 1073, 1073, 1073, 1073, 1073, 1073,
 /*    60 */  1073, 1073, 1073, 1073, 1073, 1073, 1073, 1073, 1073, 1073,
 /*    70 */  1073, 1073, 1073,  192,  552,  524,  524,  552,  552,  552,
 /*    80 */   550,  525,  525,  684,  914,  882,  850, 1026, 1026, 1026,
 /*    90 */  1026, 1026, 1026, 1026, 1026, 1026, 1026, 1026, 1058, 1026,
 /*   100 */  1026, 1026, 1026, 1026, 1026, 1026, 1026,  994, 1143, 1131,
 /*   110 */  1137, 1188, 1186,  536,  595,  595,   28,   28,  124,  176,
 /*   120 */   155,   90,   32,  -27,  -27,  -27,  -27,  -27,  -27,  145,
 /*   130 */   208,  235,   86,  133,   68,    4,  202,   94,   60,  324,
 /*   140 */   509,  507,  501,  496,  482,  479,  523,  469,  468,  463,
 /*   150 */   437,  411,  324,  324,  324,  449,  451,  444,  436,  416,
 /*   160 */   410,  433,  404,  387,  379,  386,  382,  372,  353,  351,
 /*   170 */   340,  347,  329,  328,  323,  322,  309,  324,  296,  300,
 /*   180 */   240,  286,  274,  318,  282,  272,  261,  268,  255,  244,
 /*   190 */   240,  250,  227,  247,  241,  236,  218,  195,  182,  178,
 /*   200 */   166,  140,  121,  123,   98,   79,   80,    7,    3,  -15,
 /*   210 */   -26,
};
#define YY_REDUCE_USE_DFLT (-89)
#define YY_REDUCE_COUNT (82)
#define YY_REDUCE_MIN   (-88)
#define YY_REDUCE_MAX   (1176)
static const short yy_reduce_ofst[] = {
 /*     0 */   179,  395,  337,  279,  221,  163,  105,   47,  -11,  -69,
 /*    10 */  1157,  681, 1176,  -30,  -88,  248,  190,  132,   74,   16,
 /*    20 */     0,  -58,  435,  407,  365,  364,  349,  319,  307,  291,
 /*    30 */    59,  306,  290,  259,  201,  232,  143,  116,   85,  154,
 /*    40 */   703,  685,  683,  662,  649,  647,  641,  634,  623,  617,
 /*    50 */   588,  584,  571,  570,  559,  551,  543,  531,  511,  510,
 /*    60 */   494,  492,  485,  472,  441,  423,  406,  377,  376,  348,
 /*    70 */   265,  233,   91,  521,  517,  466,  459,  498,  497,  495,
 /*    80 */   462,  473,  457,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   311,  467,  467,  467,  467,  467,  467,  467,  467,  467,
 /*    10 */   445,  467,  467,  467,  467,  467,  370,  370,  370,  370,
 /*    20 */   360,  360,  467,  467,  467,  467,  467,  467,  467,  467,
 /*    30 */   467,  467,  467,  467,  467,  467,  467,  467,  467,  433,
 /*    40 */   467,  467,  467,  467,  467,  467,  467,  467,  467,  467,
 /*    50 */   467,  467,  467,  467,  467,  467,  467,  467,  467,  467,
 /*    60 */   467,  467,  467,  467,  467,  467,  467,  467,  467,  467,
 /*    70 */   467,  467,  467,  467,  467,  466,  465,  467,  467,  467,
 /*    80 */   467,  467,  467,  467,  467,  467,  467,  425,  424,  423,
 /*    90 */   422,  421,  420,  419,  418,  417,  416,  414,  467,  400,
 /*   100 */   399,  398,  397,  396,  395,  358,  367,  409,  366,  365,
 /*   110 */   390,  412,  391,  389,  388,  387,  383,  382,  467,  467,
 /*   120 */   467,  467,  467,  394,  393,  392,  386,  385,  384,  405,
 /*   130 */   467,  467,  467,  467,  467,  405,  467,  374,  467,  407,
 /*   140 */   467,  467,  467,  467,  467,  467,  444,  467,  467,  467,
 /*   150 */   432,  467,  415,  408,  406,  467,  467,  467,  467,  467,
 /*   160 */   467,  402,  467,  467,  467,  467,  467,  467,  467,  467,
 /*   170 */   467,  467,  467,  467,  467,  363,  467,  361,  467,  467,
 /*   180 */   352,  467,  374,  371,  467,  364,  374,  467,  467,  467,
 /*   190 */   467,  467,  467,  467,  467,  467,  467,  467,  467,  467,
 /*   200 */   467,  467,  467,  467,  467,  320,  467,  467,  467,  467,
 /*   210 */   467,  349,  334,  434,  464,  463,  462,  458,  457,  456,
 /*   220 */   455,  454,  453,  452,  451,  450,  447,  446,  449,  448,
 /*   230 */   443,  442,  441,  440,  439,  438,  437,  436,  435,  431,
 /*   240 */   430,  429,  428,  427,  426,  413,  372,  373,  376,  461,
 /*   250 */   459,  404,  403,  401,  377,  460,  381,  380,  379,  378,
 /*   260 */   359,  356,  353,  375,  369,  368,  366,  365,  363,  362,
 /*   270 */   351,  350,  348,  347,  346,  345,  344,  343,  342,  357,
 /*   280 */   341,  340,  339,  338,  337,  336,  335,  333,  332,  331,
 /*   290 */   329,  330,  328,  327,  326,  325,  324,  354,  323,  355,
 /*   300 */   322,  321,  319,  318,  317,  316,  315,  314,  313,  312,
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
  "IADD",          "ISUB",          "IMUL",          "IDIV",        
  "IMOD",          "ILSH",          "IRSH",          "IBND",        
  "IBOR",          "IBXR",          "IF",            "ELSE",        
  "WHILE",         "FOR",           "FOREACH",       "COLON",       
  "CONTINUE",      "BREAK",         "RETURN",        "CONDITIONNAME",
  "ACTIONNAME",    "error",         "nt",            "program",     
  "chunks",        "chunk",         "import_chunk",  "fdef_chunk",  
  "vdef_stmt",     "vdefAssign_global_stmt",  "cdef_stmt",     "blockStmt",   
  "function_start",  "function_header",  "nameList_nonEmpty",  "stmt",        
  "bodyStmt",      "return_stmt",   "lbracket",      "rbracket",    
  "bodyStmtList",  "vdefAssign_stmt",  "assign_stmt",   "funcexpr",    
  "actionStmt",    "if_stmt",       "while_stmt",    "for_stmt",    
  "foreach_stmt",  "continue_stmt",  "break_stmt",    "numList_nonEmpty",
  "exprList_nonEmpty",  "expr",          "exprList",      "fArgs_nonEmpty",
  "fArgs",         "lexpr",         "lvalue",        "lvalueList_nonEmpty",
  "if_start",      "if_header",     "if_block",      "elif_start",  
  "elif_header",   "else_header",   "while_start",   "while_header",
  "for_opener",    "for_init_stmt_nonEmpty",  "for_init_stmt",  "for_action_stmt_nonEmpty",
  "for_header1",   "for_header2",   "for_header",    "foreach_opener",
  "foreach_header",  "action",        "actions",     
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
 /*   5 */ "chunk ::= vdef_stmt SEMICOLON",
 /*   6 */ "chunk ::= vdefAssign_global_stmt SEMICOLON",
 /*   7 */ "chunk ::= cdef_stmt SEMICOLON",
 /*   8 */ "chunk ::= blockStmt",
 /*   9 */ "import_chunk ::= IMPORT NAME AS NAME",
 /*  10 */ "import_chunk ::= IMPORT NAME",
 /*  11 */ "function_start ::= FUNCTION NAME",
 /*  12 */ "function_header ::= function_start LPAREN nameList_nonEmpty RPAREN",
 /*  13 */ "function_header ::= function_start LPAREN RPAREN",
 /*  14 */ "fdef_chunk ::= function_header stmt",
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
 /*  39 */ "bodyStmtList ::= bodyStmt",
 /*  40 */ "bodyStmtList ::= bodyStmtList bodyStmt",
 /*  41 */ "bodyStmtList ::= bodyStmtList error",
 /*  42 */ "numList_nonEmpty ::= NUMBER",
 /*  43 */ "numList_nonEmpty ::= numList_nonEmpty COMMA NUMBER",
 /*  44 */ "nameList_nonEmpty ::= NAME",
 /*  45 */ "nameList_nonEmpty ::= nameList_nonEmpty COMMA NAME",
 /*  46 */ "exprList_nonEmpty ::= funcexpr LSQBRACKET LSQBRACKET numList_nonEmpty RSQBRACKET RSQBRACKET",
 /*  47 */ "expr ::= funcexpr LSQBRACKET LSQBRACKET NUMBER RSQBRACKET RSQBRACKET",
 /*  48 */ "exprList_nonEmpty ::= expr",
 /*  49 */ "exprList_nonEmpty ::= exprList_nonEmpty COMMA exprList_nonEmpty",
 /*  50 */ "exprList ::=",
 /*  51 */ "exprList ::= exprList_nonEmpty",
 /*  52 */ "expr ::= NUMBER",
 /*  53 */ "expr ::= KILLS",
 /*  54 */ "expr ::= NAME",
 /*  55 */ "expr ::= expr PERIOD NAME",
 /*  56 */ "expr ::= expr LSQBRACKET expr RSQBRACKET",
 /*  57 */ "fArgs_nonEmpty ::= expr",
 /*  58 */ "fArgs_nonEmpty ::= STRING",
 /*  59 */ "fArgs_nonEmpty ::= fArgs_nonEmpty COMMA fArgs_nonEmpty",
 /*  60 */ "fArgs ::=",
 /*  61 */ "fArgs ::= fArgs_nonEmpty",
 /*  62 */ "funcexpr ::= NAME LPAREN fArgs RPAREN",
 /*  63 */ "funcexpr ::= expr LPAREN fArgs RPAREN",
 /*  64 */ "expr ::= funcexpr",
 /*  65 */ "expr ::= LPAREN expr RPAREN",
 /*  66 */ "expr ::= LSQBRACKET exprList RSQBRACKET",
 /*  67 */ "expr ::= L2V LPAREN lexpr RPAREN",
 /*  68 */ "expr ::= MAPSTRING LPAREN STRING RPAREN",
 /*  69 */ "expr ::= UNIT LPAREN STRING RPAREN",
 /*  70 */ "expr ::= SWITCH LPAREN STRING RPAREN",
 /*  71 */ "expr ::= LOCATION LPAREN STRING RPAREN",
 /*  72 */ "expr ::= expr PLUS expr",
 /*  73 */ "expr ::= expr MINUS expr",
 /*  74 */ "expr ::= expr MULTIPLY expr",
 /*  75 */ "expr ::= expr DIVIDE expr",
 /*  76 */ "expr ::= expr MOD expr",
 /*  77 */ "expr ::= expr LSHIFT expr",
 /*  78 */ "expr ::= expr RSHIFT expr",
 /*  79 */ "expr ::= expr BITAND expr",
 /*  80 */ "expr ::= expr BITOR expr",
 /*  81 */ "expr ::= expr BITXOR expr",
 /*  82 */ "expr ::= PLUS expr",
 /*  83 */ "expr ::= MINUS expr",
 /*  84 */ "expr ::= BITNOT expr",
 /*  85 */ "lexpr ::= expr EQ expr",
 /*  86 */ "lexpr ::= expr NE expr",
 /*  87 */ "lexpr ::= expr LE expr",
 /*  88 */ "lexpr ::= expr LT expr",
 /*  89 */ "lexpr ::= expr GE expr",
 /*  90 */ "lexpr ::= expr GT expr",
 /*  91 */ "lexpr ::= lexpr LAND lexpr",
 /*  92 */ "lexpr ::= lexpr LOR lexpr",
 /*  93 */ "lexpr ::= LNOT lexpr",
 /*  94 */ "lexpr ::= LNOT LNOT lexpr",
 /*  95 */ "vdef_stmt ::= VAR nameList_nonEmpty",
 /*  96 */ "vdefAssign_stmt ::= VAR nameList_nonEmpty ASSIGN exprList_nonEmpty",
 /*  97 */ "vdefAssign_global_stmt ::= VAR nameList_nonEmpty ASSIGN exprList_nonEmpty",
 /*  98 */ "cdef_stmt ::= CONST nameList_nonEmpty ASSIGN exprList_nonEmpty",
 /*  99 */ "lvalue ::= NAME",
 /* 100 */ "lvalue ::= expr LSQBRACKET expr RSQBRACKET",
 /* 101 */ "lvalue ::= expr PERIOD NAME",
 /* 102 */ "lvalueList_nonEmpty ::= lvalue",
 /* 103 */ "lvalueList_nonEmpty ::= lvalueList_nonEmpty COMMA lvalue",
 /* 104 */ "assign_stmt ::= lvalue ASSIGN expr",
 /* 105 */ "assign_stmt ::= lvalueList_nonEmpty ASSIGN exprList_nonEmpty",
 /* 106 */ "assign_stmt ::= lvalue IADD expr",
 /* 107 */ "assign_stmt ::= lvalue ISUB expr",
 /* 108 */ "assign_stmt ::= lvalue IMUL expr",
 /* 109 */ "assign_stmt ::= lvalue IDIV expr",
 /* 110 */ "assign_stmt ::= lvalue IMOD expr",
 /* 111 */ "assign_stmt ::= lvalue ILSH expr",
 /* 112 */ "assign_stmt ::= lvalue IRSH expr",
 /* 113 */ "assign_stmt ::= lvalue IBND expr",
 /* 114 */ "assign_stmt ::= lvalue IBOR expr",
 /* 115 */ "assign_stmt ::= lvalue IBXR expr",
 /* 116 */ "if_start ::= IF",
 /* 117 */ "if_header ::= if_start LPAREN lexpr RPAREN",
 /* 118 */ "if_block ::= if_header stmt",
 /* 119 */ "elif_start ::= ELSE IF",
 /* 120 */ "elif_header ::= elif_start LPAREN lexpr RPAREN",
 /* 121 */ "if_block ::= if_block elif_header stmt",
 /* 122 */ "else_header ::= ELSE",
 /* 123 */ "if_stmt ::= if_block",
 /* 124 */ "if_stmt ::= if_block else_header stmt",
 /* 125 */ "while_start ::= WHILE",
 /* 126 */ "while_header ::= while_start LPAREN lexpr RPAREN",
 /* 127 */ "while_stmt ::= while_header stmt",
 /* 128 */ "for_opener ::= FOR LPAREN",
 /* 129 */ "for_init_stmt_nonEmpty ::= vdef_stmt",
 /* 130 */ "for_init_stmt_nonEmpty ::= vdefAssign_stmt",
 /* 131 */ "for_init_stmt_nonEmpty ::= cdef_stmt",
 /* 132 */ "for_init_stmt_nonEmpty ::= assign_stmt",
 /* 133 */ "for_init_stmt_nonEmpty ::= for_init_stmt_nonEmpty COMMA for_init_stmt_nonEmpty",
 /* 134 */ "for_init_stmt ::= for_init_stmt_nonEmpty",
 /* 135 */ "for_init_stmt ::=",
 /* 136 */ "for_action_stmt_nonEmpty ::= assign_stmt",
 /* 137 */ "for_action_stmt_nonEmpty ::= for_action_stmt_nonEmpty COMMA for_action_stmt_nonEmpty",
 /* 138 */ "for_header1 ::= for_opener for_init_stmt SEMICOLON",
 /* 139 */ "for_header2 ::= for_header1 lexpr SEMICOLON",
 /* 140 */ "for_header ::= for_header2 for_action_stmt_nonEmpty RPAREN",
 /* 141 */ "for_header ::= for_header2 RPAREN",
 /* 142 */ "for_stmt ::= for_header stmt",
 /* 143 */ "foreach_opener ::= FOREACH LPAREN",
 /* 144 */ "foreach_header ::= foreach_opener nameList_nonEmpty COLON exprList_nonEmpty RPAREN",
 /* 145 */ "foreach_stmt ::= foreach_header stmt",
 /* 146 */ "continue_stmt ::= CONTINUE",
 /* 147 */ "break_stmt ::= BREAK",
 /* 148 */ "return_stmt ::= RETURN exprList",
 /* 149 */ "lexpr ::= CONDITIONNAME LPAREN fArgs RPAREN",
 /* 150 */ "lexpr ::= KILLS LPAREN fArgs RPAREN",
 /* 151 */ "lexpr ::= CONDITIONNAME LPAREN RPAREN",
 /* 152 */ "action ::= ACTIONNAME LPAREN fArgs RPAREN SEMICOLON",
 /* 153 */ "actions ::= action action",
 /* 154 */ "actions ::= actions action",
 /* 155 */ "actionStmt ::= action",
 /* 156 */ "actionStmt ::= actions",
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
    case 70: /* nt */
{
#line 33 "parser\\epparser.lemon"
 delete (yypminor->yy0); 
#line 879 "parser\\epparser.c"
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
  { 71, 1 },
  { 72, 0 },
  { 72, 2 },
  { 73, 2 },
  { 73, 1 },
  { 73, 2 },
  { 73, 2 },
  { 73, 2 },
  { 73, 1 },
  { 74, 4 },
  { 74, 2 },
  { 80, 2 },
  { 81, 4 },
  { 81, 3 },
  { 75, 2 },
  { 83, 2 },
  { 83, 1 },
  { 83, 2 },
  { 86, 1 },
  { 87, 1 },
  { 79, 2 },
  { 79, 4 },
  { 79, 3 },
  { 79, 5 },
  { 79, 3 },
  { 84, 1 },
  { 84, 1 },
  { 84, 2 },
  { 84, 2 },
  { 84, 2 },
  { 84, 2 },
  { 84, 2 },
  { 84, 1 },
  { 84, 1 },
  { 84, 1 },
  { 84, 1 },
  { 84, 1 },
  { 84, 2 },
  { 84, 2 },
  { 88, 1 },
  { 88, 2 },
  { 88, 2 },
  { 99, 1 },
  { 99, 3 },
  { 82, 1 },
  { 82, 3 },
  { 100, 6 },
  { 101, 6 },
  { 100, 1 },
  { 100, 3 },
  { 102, 0 },
  { 102, 1 },
  { 101, 1 },
  { 101, 1 },
  { 101, 1 },
  { 101, 3 },
  { 101, 4 },
  { 103, 1 },
  { 103, 1 },
  { 103, 3 },
  { 104, 0 },
  { 104, 1 },
  { 91, 4 },
  { 91, 4 },
  { 101, 1 },
  { 101, 3 },
  { 101, 3 },
  { 101, 4 },
  { 101, 4 },
  { 101, 4 },
  { 101, 4 },
  { 101, 4 },
  { 101, 3 },
  { 101, 3 },
  { 101, 3 },
  { 101, 3 },
  { 101, 3 },
  { 101, 3 },
  { 101, 3 },
  { 101, 3 },
  { 101, 3 },
  { 101, 3 },
  { 101, 2 },
  { 101, 2 },
  { 101, 2 },
  { 105, 3 },
  { 105, 3 },
  { 105, 3 },
  { 105, 3 },
  { 105, 3 },
  { 105, 3 },
  { 105, 3 },
  { 105, 3 },
  { 105, 2 },
  { 105, 3 },
  { 76, 2 },
  { 89, 4 },
  { 77, 4 },
  { 78, 4 },
  { 106, 1 },
  { 106, 4 },
  { 106, 3 },
  { 107, 1 },
  { 107, 3 },
  { 90, 3 },
  { 90, 3 },
  { 90, 3 },
  { 90, 3 },
  { 90, 3 },
  { 90, 3 },
  { 90, 3 },
  { 90, 3 },
  { 90, 3 },
  { 90, 3 },
  { 90, 3 },
  { 90, 3 },
  { 108, 1 },
  { 109, 4 },
  { 110, 2 },
  { 111, 2 },
  { 112, 4 },
  { 110, 3 },
  { 113, 1 },
  { 93, 1 },
  { 93, 3 },
  { 114, 1 },
  { 115, 4 },
  { 94, 2 },
  { 116, 2 },
  { 117, 1 },
  { 117, 1 },
  { 117, 1 },
  { 117, 1 },
  { 117, 3 },
  { 118, 1 },
  { 118, 0 },
  { 119, 1 },
  { 119, 3 },
  { 120, 3 },
  { 121, 3 },
  { 122, 3 },
  { 122, 2 },
  { 95, 2 },
  { 123, 2 },
  { 124, 5 },
  { 96, 2 },
  { 97, 1 },
  { 98, 1 },
  { 85, 2 },
  { 105, 4 },
  { 105, 4 },
  { 105, 3 },
  { 125, 5 },
  { 126, 2 },
  { 126, 2 },
  { 92, 1 },
  { 92, 1 },
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
      case 8: /* chunk ::= blockStmt */
#line 67 "parser\\epparser.lemon"
{
    throw_error(48993, "Misplaced block statement");
}
#line 1333 "parser\\epparser.c"
        break;
      case 9: /* import_chunk ::= IMPORT NAME AS NAME */
#line 73 "parser\\epparser.lemon"
{
    if(!ps->closure.defModule(yymsp[0].minor.yy0->data)) {
        throw_error(6754, "Importing already-declared module " + yymsp[0].minor.yy0->data);
    }
    ps->gen << "import " << yymsp[-2].minor.yy0->data << " as " << yymsp[0].minor.yy0->data << std::endl;
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 1344 "parser\\epparser.c"
        break;
      case 10: /* import_chunk ::= IMPORT NAME */
#line 81 "parser\\epparser.lemon"
{
    if(!ps->closure.defModule(yymsp[0].minor.yy0->data)) {
        throw_error(6754, "Importing already-declared module " + yymsp[0].minor.yy0->data);
    }
    ps->gen << "import " << yymsp[0].minor.yy0->data << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1355 "parser\\epparser.c"
        break;
      case 11: /* function_start ::= FUNCTION NAME */
#line 90 "parser\\epparser.lemon"
{
    // Preprocess yymsp[0].minor.yy0
    funcNamePreprocess(yymsp[0].minor.yy0->data);
    if(!ps->closure.defFunction(yymsp[0].minor.yy0->data)) {
        throw_error(4495, "Duplicate function " + yymsp[0].minor.yy0->data);
    }
    ps->closure.pushScope();
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1368 "parser\\epparser.c"
        break;
      case 12: /* function_header ::= function_start LPAREN nameList_nonEmpty RPAREN */
#line 100 "parser\\epparser.lemon"
{
    ps->gen << "@EUDFunc" << std::endl;
    ps->gen << "def " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data << "):" << std::endl;
    ps->gen.indent();

    // Register variables.
    commaListIter(yymsp[-1].minor.yy0->data, [&](std::string& varname) {
        if(!ps->closure.defVariable(varname)) {
            throw_error(196, ("Redeclaration of variable \'" + varname + "\'"));
        }
    });

    tmpIndex = 1;
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1387 "parser\\epparser.c"
        break;
      case 13: /* function_header ::= function_start LPAREN RPAREN */
#line 116 "parser\\epparser.lemon"
{
    ps->gen << "@EUDFunc" << std::endl;
    ps->gen << "def " << yymsp[-2].minor.yy0->data << "():" << std::endl;
    ps->gen.indent();
    tmpIndex = 1;
    delete yymsp[-2].minor.yy0;
}
#line 1398 "parser\\epparser.c"
        break;
      case 14: /* fdef_chunk ::= function_header stmt */
      case 145: /* foreach_stmt ::= foreach_header stmt */ yytestcase(yyruleno==145);
#line 124 "parser\\epparser.lemon"
{
    ps->gen.unindent(true);
    ps->closure.popScope();
}
#line 1407 "parser\\epparser.c"
        break;
      case 15: /* stmt ::= error SEMICOLON */
#line 131 "parser\\epparser.lemon"
{ throw_error(6974, "Error while parsing statement"); }
#line 1412 "parser\\epparser.c"
        break;
      case 18: /* lbracket ::= LBRACKET */
#line 137 "parser\\epparser.lemon"
{ ps->closure.pushScope(); }
#line 1417 "parser\\epparser.c"
        break;
      case 19: /* rbracket ::= RBRACKET */
#line 138 "parser\\epparser.lemon"
{ ps->closure.popScope(); }
#line 1422 "parser\\epparser.c"
        break;
      case 20: /* blockStmt ::= lbracket RBRACKET */
#line 140 "parser\\epparser.lemon"
{
    ps->gen << "pass" << std::endl;
    ps->closure.popScope();
}
#line 1430 "parser\\epparser.c"
        break;
      case 24: /* blockStmt ::= lbracket error RBRACKET */
#line 147 "parser\\epparser.lemon"
{
    throw_error(6298, "Block not terminated properly.");
    ps->closure.popScope();
}
#line 1438 "parser\\epparser.c"
        break;
      case 31: /* bodyStmt ::= funcexpr SEMICOLON */
#line 158 "parser\\epparser.lemon"
{ ps->gen << yymsp[-1].minor.yy0->data << std::endl; }
#line 1443 "parser\\epparser.c"
        break;
      case 41: /* bodyStmtList ::= bodyStmtList error */
#line 170 "parser\\epparser.lemon"
{
    throw_error(8510, "Incomplete statement");
}
#line 1450 "parser\\epparser.c"
        break;
      case 42: /* numList_nonEmpty ::= NUMBER */
      case 44: /* nameList_nonEmpty ::= NAME */ yytestcase(yyruleno==44);
      case 48: /* exprList_nonEmpty ::= expr */ yytestcase(yyruleno==48);
      case 51: /* exprList ::= exprList_nonEmpty */ yytestcase(yyruleno==51);
      case 52: /* expr ::= NUMBER */ yytestcase(yyruleno==52);
      case 57: /* fArgs_nonEmpty ::= expr */ yytestcase(yyruleno==57);
      case 58: /* fArgs_nonEmpty ::= STRING */ yytestcase(yyruleno==58);
      case 61: /* fArgs ::= fArgs_nonEmpty */ yytestcase(yyruleno==61);
      case 64: /* expr ::= funcexpr */ yytestcase(yyruleno==64);
      case 94: /* lexpr ::= LNOT LNOT lexpr */ yytestcase(yyruleno==94);
      case 102: /* lvalueList_nonEmpty ::= lvalue */ yytestcase(yyruleno==102);
#line 176 "parser\\epparser.lemon"
{ yygotominor.yy0 = yymsp[0].minor.yy0; }
#line 1465 "parser\\epparser.c"
        break;
      case 43: /* numList_nonEmpty ::= numList_nonEmpty COMMA NUMBER */
      case 45: /* nameList_nonEmpty ::= nameList_nonEmpty COMMA NAME */ yytestcase(yyruleno==45);
      case 103: /* lvalueList_nonEmpty ::= lvalueList_nonEmpty COMMA lvalue */ yytestcase(yyruleno==103);
#line 177 "parser\\epparser.lemon"
{ yygotominor.yy0 = commaConcat(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1472 "parser\\epparser.c"
        break;
      case 46: /* exprList_nonEmpty ::= funcexpr LSQBRACKET LSQBRACKET numList_nonEmpty RSQBRACKET RSQBRACKET */
#line 181 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "_SRET(" + yymsp[-5].minor.yy0->data + ", [" + yymsp[-2].minor.yy0->data + "])";
    delete yymsp[-5].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1481 "parser\\epparser.c"
        break;
      case 47: /* expr ::= funcexpr LSQBRACKET LSQBRACKET NUMBER RSQBRACKET RSQBRACKET */
#line 188 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-5].minor.yy0->data + "[" + yymsp[-2].minor.yy0->data + "]";
    delete yymsp[-5].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1490 "parser\\epparser.c"
        break;
      case 49: /* exprList_nonEmpty ::= exprList_nonEmpty COMMA exprList_nonEmpty */
#line 196 "parser\\epparser.lemon"
{ yygotominor.yy0 = new Token((yymsp[-2].minor.yy0->data) + ", " + (yymsp[0].minor.yy0->data), yymsp[0].minor.yy0); delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1495 "parser\\epparser.c"
        break;
      case 50: /* exprList ::= */
      case 60: /* fArgs ::= */ yytestcase(yyruleno==60);
#line 198 "parser\\epparser.lemon"
{ yygotominor.yy0 = genEmpty(); }
#line 1501 "parser\\epparser.c"
        break;
      case 53: /* expr ::= KILLS */
#line 203 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = "4";
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1509 "parser\\epparser.c"
        break;
      case 54: /* expr ::= NAME */
#line 208 "parser\\epparser.lemon"
{
    checkIsRValue(yymsp[0].minor.yy0->data);
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1517 "parser\\epparser.c"
        break;
      case 55: /* expr ::= expr PERIOD NAME */
#line 213 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + "." + yymsp[0].minor.yy0->data;
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1526 "parser\\epparser.c"
        break;
      case 56: /* expr ::= expr LSQBRACKET expr RSQBRACKET */
#line 219 "parser\\epparser.lemon"
{
    yymsp[-3].minor.yy0->data = yymsp[-3].minor.yy0->data + "[" + yymsp[-1].minor.yy0->data + "]";
    delete yymsp[-1].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 1535 "parser\\epparser.c"
        break;
      case 59: /* fArgs_nonEmpty ::= fArgs_nonEmpty COMMA fArgs_nonEmpty */
#line 228 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data;
    yymsp[-2].minor.yy0->type = TOKEN_TEMP;
    yygotominor.yy0 = yymsp[-2].minor.yy0;
    delete yymsp[0].minor.yy0;
}
#line 1545 "parser\\epparser.c"
        break;
      case 62: /* funcexpr ::= NAME LPAREN fArgs RPAREN */
#line 238 "parser\\epparser.lemon"
{
    // Preprocess yymsp[-3].minor.yy0
    funcNamePreprocess(yymsp[-3].minor.yy0->data);
    checkIsFunction(yymsp[-3].minor.yy0->data);
    yymsp[-3].minor.yy0->data += "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 1556 "parser\\epparser.c"
        break;
      case 63: /* funcexpr ::= expr LPAREN fArgs RPAREN */
#line 246 "parser\\epparser.lemon"
{
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
#line 1578 "parser\\epparser.c"
        break;
      case 65: /* expr ::= LPAREN expr RPAREN */
#line 268 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1586 "parser\\epparser.c"
        break;
      case 66: /* expr ::= LSQBRACKET exprList RSQBRACKET */
#line 273 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "EUDArray(FlattenList([" + yymsp[-1].minor.yy0->data + "]))";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1594 "parser\\epparser.c"
        break;
      case 67: /* expr ::= L2V LPAREN lexpr RPAREN */
#line 278 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "_L2V(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = genTemp(yymsp[-1].minor.yy0);
}
#line 1602 "parser\\epparser.c"
        break;
      case 68: /* expr ::= MAPSTRING LPAREN STRING RPAREN */
#line 283 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetStringIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1610 "parser\\epparser.c"
        break;
      case 69: /* expr ::= UNIT LPAREN STRING RPAREN */
#line 288 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "EncodeUnit(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1618 "parser\\epparser.c"
        break;
      case 70: /* expr ::= SWITCH LPAREN STRING RPAREN */
#line 293 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "EncodeSwitch(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1626 "parser\\epparser.c"
        break;
      case 71: /* expr ::= LOCATION LPAREN STRING RPAREN */
#line 298 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetLocationIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1634 "parser\\epparser.c"
        break;
      case 72: /* expr ::= expr PLUS expr */
#line 304 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "+",  yymsp[0].minor.yy0); }
#line 1639 "parser\\epparser.c"
        break;
      case 73: /* expr ::= expr MINUS expr */
#line 305 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "-",  yymsp[0].minor.yy0); }
#line 1644 "parser\\epparser.c"
        break;
      case 74: /* expr ::= expr MULTIPLY expr */
#line 306 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "*",  yymsp[0].minor.yy0); }
#line 1649 "parser\\epparser.c"
        break;
      case 75: /* expr ::= expr DIVIDE expr */
#line 307 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "//", yymsp[0].minor.yy0); }
#line 1654 "parser\\epparser.c"
        break;
      case 76: /* expr ::= expr MOD expr */
#line 308 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "%",  yymsp[0].minor.yy0); }
#line 1659 "parser\\epparser.c"
        break;
      case 77: /* expr ::= expr LSHIFT expr */
#line 309 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<<", yymsp[0].minor.yy0); }
#line 1664 "parser\\epparser.c"
        break;
      case 78: /* expr ::= expr RSHIFT expr */
#line 310 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">>", yymsp[0].minor.yy0); }
#line 1669 "parser\\epparser.c"
        break;
      case 79: /* expr ::= expr BITAND expr */
#line 311 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "&",  yymsp[0].minor.yy0); }
#line 1674 "parser\\epparser.c"
        break;
      case 80: /* expr ::= expr BITOR expr */
#line 312 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "|",  yymsp[0].minor.yy0); }
#line 1679 "parser\\epparser.c"
        break;
      case 81: /* expr ::= expr BITXOR expr */
#line 313 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "^",  yymsp[0].minor.yy0); }
#line 1684 "parser\\epparser.c"
        break;
      case 82: /* expr ::= PLUS expr */
#line 316 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = +" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1689 "parser\\epparser.c"
        break;
      case 83: /* expr ::= MINUS expr */
#line 317 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = -" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1694 "parser\\epparser.c"
        break;
      case 84: /* expr ::= BITNOT expr */
#line 318 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = ~" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1699 "parser\\epparser.c"
        break;
      case 85: /* lexpr ::= expr EQ expr */
#line 322 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "==", yymsp[0].minor.yy0); }
#line 1704 "parser\\epparser.c"
        break;
      case 86: /* lexpr ::= expr NE expr */
#line 323 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "!=", yymsp[0].minor.yy0); }
#line 1709 "parser\\epparser.c"
        break;
      case 87: /* lexpr ::= expr LE expr */
#line 324 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<=", yymsp[0].minor.yy0); }
#line 1714 "parser\\epparser.c"
        break;
      case 88: /* lexpr ::= expr LT expr */
#line 325 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<",  yymsp[0].minor.yy0); }
#line 1719 "parser\\epparser.c"
        break;
      case 89: /* lexpr ::= expr GE expr */
#line 326 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">=", yymsp[0].minor.yy0); }
#line 1724 "parser\\epparser.c"
        break;
      case 90: /* lexpr ::= expr GT expr */
#line 327 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">" , yymsp[0].minor.yy0); }
#line 1729 "parser\\epparser.c"
        break;
      case 91: /* lexpr ::= lexpr LAND lexpr */
#line 329 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "[" + yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data + "]";
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1738 "parser\\epparser.c"
        break;
      case 92: /* lexpr ::= lexpr LOR lexpr */
#line 335 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "EUDOr([" + yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data + "])";
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1747 "parser\\epparser.c"
        break;
      case 93: /* lexpr ::= LNOT lexpr */
#line 341 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = "EUDNot([" + yymsp[0].minor.yy0->data + "])";
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0);
}
#line 1755 "parser\\epparser.c"
        break;
      case 95: /* vdef_stmt ::= VAR nameList_nonEmpty */
#line 351 "parser\\epparser.lemon"
{
    std::string& s = yymsp[0].minor.yy0->data;
    int varCount = std::count(s.begin(), s.end(), ',') + 1;

    // Register variables.
    commaListIter(s, [&](std::string& varname) {
        if(!ps->closure.defVariable(varname)) {
            throw_error(196, ("Redeclaration of variable \'" + varname + "\'"));
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
#line 1779 "parser\\epparser.c"
        break;
      case 96: /* vdefAssign_stmt ::= VAR nameList_nonEmpty ASSIGN exprList_nonEmpty */
#line 372 "parser\\epparser.lemon"
{
    std::string& s = yymsp[-2].minor.yy0->data;
    int varCount = std::count(s.begin(), s.end(), ',') + 1;

    // Register variables.
    commaListIter(s, [&](std::string& varname) {
        if(!ps->closure.defVariable(varname)) {
            throw_error(7998, ("Redeclaration of variable \'" + varname + "\'"));
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
#line 1804 "parser\\epparser.c"
        break;
      case 97: /* vdefAssign_global_stmt ::= VAR nameList_nonEmpty ASSIGN exprList_nonEmpty */
#line 394 "parser\\epparser.lemon"
{
    std::string& s = yymsp[-2].minor.yy0->data;
    int varCount = std::count(s.begin(), s.end(), ',') + 1;

    // Register variables.
    commaListIter(s, [&](std::string& varname) {
        if(!ps->closure.defVariable(varname)) {
            throw_error(7998, ("Redeclaration of variable \'" + varname + "\'"));
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
#line 1828 "parser\\epparser.c"
        break;
      case 98: /* cdef_stmt ::= CONST nameList_nonEmpty ASSIGN exprList_nonEmpty */
#line 415 "parser\\epparser.lemon"
{
    std::string& s = yymsp[-2].minor.yy0->data;
    int nameCount = std::count(s.begin(), s.end(), ',') + 1;

    // Register constants.
    commaListIter(s, [&](std::string& constname) {
        if(!ps->closure.defConstant(constname)) {
            throw_error(7719, ("Redeclaration of constant \'" + constname + "\'"));
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
#line 1850 "parser\\epparser.c"
        break;
      case 99: /* lvalue ::= NAME */
#line 435 "parser\\epparser.lemon"
{
    checkIsVariable(yymsp[0].minor.yy0->data);
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1858 "parser\\epparser.c"
        break;
      case 100: /* lvalue ::= expr LSQBRACKET expr RSQBRACKET */
#line 440 "parser\\epparser.lemon"
{
    checkIsConstant(yymsp[-3].minor.yy0->data);
    yymsp[-1].minor.yy0->data = "_ARRW(" + yymsp[-3].minor.yy0->data + ", " + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
    delete yymsp[-3].minor.yy0;
}
#line 1868 "parser\\epparser.c"
        break;
      case 101: /* lvalue ::= expr PERIOD NAME */
#line 447 "parser\\epparser.lemon"
{
    checkIsConstant(yymsp[-2].minor.yy0->data);
    yymsp[0].minor.yy0->data = "_ATTW(" + yymsp[-2].minor.yy0->data + ", '" + yymsp[0].minor.yy0->data + "')";
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0);
    delete yymsp[-2].minor.yy0;
}
#line 1878 "parser\\epparser.c"
        break;
      case 104: /* assign_stmt ::= lvalue ASSIGN expr */
#line 456 "parser\\epparser.lemon"
{
    ps->gen << yymsp[-2].minor.yy0->data << " << (" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 1886 "parser\\epparser.c"
        break;
      case 105: /* assign_stmt ::= lvalueList_nonEmpty ASSIGN exprList_nonEmpty */
#line 461 "parser\\epparser.lemon"
{
    ps->gen << "_SV([" << yymsp[-2].minor.yy0->data << "], [" << yymsp[0].minor.yy0->data << "])" << std::endl;
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 1894 "parser\\epparser.c"
        break;
      case 106: /* assign_stmt ::= lvalue IADD expr */
#line 469 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__iadd__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1899 "parser\\epparser.c"
        break;
      case 107: /* assign_stmt ::= lvalue ISUB expr */
#line 470 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__isub__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1904 "parser\\epparser.c"
        break;
      case 108: /* assign_stmt ::= lvalue IMUL expr */
#line 471 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__imul__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1909 "parser\\epparser.c"
        break;
      case 109: /* assign_stmt ::= lvalue IDIV expr */
#line 472 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ifloordiv__("  << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1914 "parser\\epparser.c"
        break;
      case 110: /* assign_stmt ::= lvalue IMOD expr */
#line 473 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__imod__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1919 "parser\\epparser.c"
        break;
      case 111: /* assign_stmt ::= lvalue ILSH expr */
#line 474 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ilshift__("    << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1924 "parser\\epparser.c"
        break;
      case 112: /* assign_stmt ::= lvalue IRSH expr */
#line 475 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__irshift__("    << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1929 "parser\\epparser.c"
        break;
      case 113: /* assign_stmt ::= lvalue IBND expr */
#line 476 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__iand__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1934 "parser\\epparser.c"
        break;
      case 114: /* assign_stmt ::= lvalue IBOR expr */
#line 477 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ior__("        << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1939 "parser\\epparser.c"
        break;
      case 115: /* assign_stmt ::= lvalue IBXR expr */
#line 478 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ixor__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1944 "parser\\epparser.c"
        break;
      case 116: /* if_start ::= IF */
#line 481 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDIf()" << std::endl;
}
#line 1952 "parser\\epparser.c"
        break;
      case 117: /* if_header ::= if_start LPAREN lexpr RPAREN */
      case 126: /* while_header ::= while_start LPAREN lexpr RPAREN */ yytestcase(yyruleno==126);
#line 485 "parser\\epparser.lemon"
{
    ps->gen << "if " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data << "):" << std::endl;
    ps->gen.indent();
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1962 "parser\\epparser.c"
        break;
      case 119: /* elif_start ::= ELSE IF */
#line 493 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen.unindent(false);
    ps->gen << yygotominor.yy0->data << " = EUDElseIf()" << std::endl;
}
#line 1971 "parser\\epparser.c"
        break;
      case 120: /* elif_header ::= elif_start LPAREN lexpr RPAREN */
#line 499 "parser\\epparser.lemon"
{
    ps->gen << "if " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data <<"):" << std::endl;
    ps->gen.indent();
}
#line 1979 "parser\\epparser.c"
        break;
      case 122: /* else_header ::= ELSE */
#line 506 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "if EUDElse()():" << std::endl;
    ps->gen.indent();
}
#line 1988 "parser\\epparser.c"
        break;
      case 123: /* if_stmt ::= if_block */
      case 124: /* if_stmt ::= if_block else_header stmt */ yytestcase(yyruleno==124);
#line 512 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndIf()" << std::endl;
}
#line 1997 "parser\\epparser.c"
        break;
      case 125: /* while_start ::= WHILE */
#line 524 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDWhile()" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2006 "parser\\epparser.c"
        break;
      case 127: /* while_stmt ::= while_header stmt */
#line 536 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndWhile()" << std::endl;
}
#line 2014 "parser\\epparser.c"
        break;
      case 128: /* for_opener ::= FOR LPAREN */
      case 143: /* foreach_opener ::= FOREACH LPAREN */ yytestcase(yyruleno==143);
#line 542 "parser\\epparser.lemon"
{
    ps->closure.pushScope();
}
#line 2022 "parser\\epparser.c"
        break;
      case 138: /* for_header1 ::= for_opener for_init_stmt SEMICOLON */
#line 558 "parser\\epparser.lemon"
{
    // opening for lexpr
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDWhile()" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2032 "parser\\epparser.c"
        break;
      case 139: /* for_header2 ::= for_header1 lexpr SEMICOLON */
#line 565 "parser\\epparser.lemon"
{
    ps->gen << "if " << yymsp[-2].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data << "):" << std::endl;
    ps->gen.indent();
    delete yymsp[-2].minor.yy0; delete yymsp[-1].minor.yy0;

    // Opening for assign_statement
    yygotominor.yy0 = genTemp(yymsp[-1].minor.yy0);
    ps->gen << "def " << yygotominor.yy0->data <<"():" << std::endl;
    ps->gen.indent();
}
#line 2046 "parser\\epparser.c"
        break;
      case 140: /* for_header ::= for_header2 for_action_stmt_nonEmpty RPAREN */
#line 576 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-2].minor.yy0;
    ps->gen.unindent(false);
}
#line 2054 "parser\\epparser.c"
        break;
      case 141: /* for_header ::= for_header2 RPAREN */
#line 581 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
    ps->gen << "pass" << std::endl;
    ps->gen.unindent(false);
}
#line 2063 "parser\\epparser.c"
        break;
      case 142: /* for_stmt ::= for_header stmt */
#line 587 "parser\\epparser.lemon"
{
    ps->gen << yymsp[-1].minor.yy0->data << "()" << std::endl;
    ps->gen.unindent(false);
    ps->gen << "EUDEndWhile()" << std::endl;
    ps->closure.popScope();
}
#line 2073 "parser\\epparser.c"
        break;
      case 144: /* foreach_header ::= foreach_opener nameList_nonEmpty COLON exprList_nonEmpty RPAREN */
#line 601 "parser\\epparser.lemon"
{
    commaListIter(yymsp[-3].minor.yy0->data, [&](std::string& s) {
        ps->closure.defVariable(s);
    });
    ps->gen << "for " << yymsp[-3].minor.yy0->data << " in " << yymsp[-1].minor.yy0->data << ":" << std::endl;
    ps->gen.indent();
}
#line 2084 "parser\\epparser.c"
        break;
      case 146: /* continue_stmt ::= CONTINUE */
#line 617 "parser\\epparser.lemon"
{
    ps->gen << "EUDContinue()" << std::endl;
}
#line 2091 "parser\\epparser.c"
        break;
      case 147: /* break_stmt ::= BREAK */
#line 621 "parser\\epparser.lemon"
{
    ps->gen << "EUDBreak()" << std::endl;
}
#line 2098 "parser\\epparser.c"
        break;
      case 148: /* return_stmt ::= RETURN exprList */
#line 628 "parser\\epparser.lemon"
{
    ps->gen << "EUDReturn(" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2106 "parser\\epparser.c"
        break;
      case 149: /* lexpr ::= CONDITIONNAME LPAREN fArgs RPAREN */
      case 150: /* lexpr ::= KILLS LPAREN fArgs RPAREN */ yytestcase(yyruleno==150);
#line 636 "parser\\epparser.lemon"
{
    yymsp[-3].minor.yy0->data = yymsp[-3].minor.yy0->data + "(" + yymsp[-1].minor.yy0->data + ")";
    delete yymsp[-1].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 2116 "parser\\epparser.c"
        break;
      case 151: /* lexpr ::= CONDITIONNAME LPAREN RPAREN */
#line 648 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + "()";
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 2124 "parser\\epparser.c"
        break;
      case 152: /* action ::= ACTIONNAME LPAREN fArgs RPAREN SEMICOLON */
#line 653 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[-4].minor.yy0);
    yygotominor.yy0->data =  yymsp[-4].minor.yy0->data + "(" + yymsp[-2].minor.yy0->data + ")";
    delete yymsp[-4].minor.yy0; delete yymsp[-2].minor.yy0;
}
#line 2133 "parser\\epparser.c"
        break;
      case 153: /* actions ::= action action */
      case 154: /* actions ::= actions action */ yytestcase(yyruleno==154);
#line 659 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
    yymsp[-1].minor.yy0->data += ",\n" + yymsp[0].minor.yy0->data;
    delete yymsp[0].minor.yy0;
}
#line 2143 "parser\\epparser.c"
        break;
      case 155: /* actionStmt ::= action */
#line 671 "parser\\epparser.lemon"
{
    ps->gen << "DoActions(" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2151 "parser\\epparser.c"
        break;
      case 156: /* actionStmt ::= actions */
#line 676 "parser\\epparser.lemon"
{
    ps->gen << "DoActions([" << std::endl;
    ps->gen.indent();
    ps->gen << yymsp[0].minor.yy0->data << std::endl;
    ps->gen.unindent(false);
    ps->gen << "])" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2163 "parser\\epparser.c"
        break;
      default:
      /* (0) program ::= chunks */ yytestcase(yyruleno==0);
      /* (1) chunks ::= */ yytestcase(yyruleno==1);
      /* (2) chunks ::= chunks chunk */ yytestcase(yyruleno==2);
      /* (3) chunk ::= import_chunk SEMICOLON */ yytestcase(yyruleno==3);
      /* (4) chunk ::= fdef_chunk */ yytestcase(yyruleno==4);
      /* (5) chunk ::= vdef_stmt SEMICOLON */ yytestcase(yyruleno==5);
      /* (6) chunk ::= vdefAssign_global_stmt SEMICOLON */ yytestcase(yyruleno==6);
      /* (7) chunk ::= cdef_stmt SEMICOLON */ yytestcase(yyruleno==7);
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
      /* (39) bodyStmtList ::= bodyStmt */ yytestcase(yyruleno==39);
      /* (40) bodyStmtList ::= bodyStmtList bodyStmt */ yytestcase(yyruleno==40);
      /* (118) if_block ::= if_header stmt */ yytestcase(yyruleno==118);
      /* (121) if_block ::= if_block elif_header stmt */ yytestcase(yyruleno==121);
      /* (129) for_init_stmt_nonEmpty ::= vdef_stmt */ yytestcase(yyruleno==129);
      /* (130) for_init_stmt_nonEmpty ::= vdefAssign_stmt */ yytestcase(yyruleno==130);
      /* (131) for_init_stmt_nonEmpty ::= cdef_stmt */ yytestcase(yyruleno==131);
      /* (132) for_init_stmt_nonEmpty ::= assign_stmt */ yytestcase(yyruleno==132);
      /* (133) for_init_stmt_nonEmpty ::= for_init_stmt_nonEmpty COMMA for_init_stmt_nonEmpty */ yytestcase(yyruleno==133);
      /* (134) for_init_stmt ::= for_init_stmt_nonEmpty */ yytestcase(yyruleno==134);
      /* (135) for_init_stmt ::= */ yytestcase(yyruleno==135);
      /* (136) for_action_stmt_nonEmpty ::= assign_stmt */ yytestcase(yyruleno==136);
      /* (137) for_action_stmt_nonEmpty ::= for_action_stmt_nonEmpty COMMA for_action_stmt_nonEmpty */ yytestcase(yyruleno==137);
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
#line 25 "parser\\epparser.lemon"

    throw_error(-1, "Unrecoverable error");
#line 2253 "parser\\epparser.c"
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
#line 690 "parser\\epparser.lemon"


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
#line 2506 "parser\\epparser.c"
