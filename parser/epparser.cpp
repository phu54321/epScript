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
#define YYNSTATE 309
#define YYNRULE 156
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
 /*     0 */   200,  182,   28,   29,  307,   28,   29,  196,  305,  194,
 /*    10 */   177,  105,  158,  296,  294,  199,    2,  304,  286,  303,
 /*    20 */   195,  193,  137,  278,  277,  276,  275,  274,  188,  187,
 /*    30 */   205,  254,   98,  182,  243,   28,   29,  111,  133,  151,
 /*    40 */     8,   39,  177,  105,  217,  148,    6,   10,   67,   68,
 /*    50 */    66,   22,   13,    5,   77,    4,   76,   75,  200,   18,
 /*    60 */    28,   29,  297,   72,  240,  196,  184,  194,  298,   28,
 /*    70 */    29,  242,  294,  199,    2,  204,  286,  302,  195,  193,
 /*    80 */   137,  278,  277,  276,  275,  274,  188,  187,  301,  237,
 /*    90 */    98,  227,  186,  228,   73,  111,  133,  151,    8,   39,
 /*   100 */   299,  179,   98,  148,    6,   10,  295,  111,  133,   22,
 /*   110 */    13,    5,   77,    4,   76,   75,  200,   18,  293,   82,
 /*   120 */   226,   72,   81,  196,  184,  194,  149,    7,    3,  239,
 /*   130 */   294,  199,    2,  284,  286,  178,  195,  193,  137,  278,
 /*   140 */   277,  276,  275,  274,  188,  187,  283,  201,   98,  227,
 /*   150 */   186,  280,   14,  111,  133,  151,    8,   39,  282,  192,
 /*   160 */    98,  148,    6,   10,  281,  111,  133,   22,   13,    5,
 /*   170 */    77,    4,   76,   75,  200,  182,  186,  300,  132,   37,
 /*   180 */   201,  196,  225,  194,  260,  105,   98,  236,  294,  199,
 /*   190 */     2,  245,  286,  191,  195,  193,  137,  278,  277,  276,
 /*   200 */   275,  274,  188,  187,   36,  201,   98,  182,  186,   34,
 /*   210 */    35,  111,  133,  151,    8,   39,  154,  105,   83,  148,
 /*   220 */     6,   10,  122,  186,  190,   22,   13,    5,   77,    4,
 /*   230 */    76,   75,  200,  106,  182,  183,  156,  201,   38,  196,
 /*   240 */   189,  194,  279,  153,  105,  223,  294,  199,    2,  273,
 /*   250 */   286,  192,  195,  193,  137,  278,  277,  276,  275,  274,
 /*   260 */   188,  187,   32,  201,   98,  182,  186,  272,  221,  111,
 /*   270 */   133,  151,    8,   39,  152,  105,   83,  148,    6,   10,
 /*   280 */   253,  186,   19,   22,   13,    5,   77,    4,   76,   75,
 /*   290 */   200,  106,  182,  183,  157,  466,   12,  196,   33,  194,
 /*   300 */   267,  130,  105,  220,  294,  199,    2,   31,  286,  262,
 /*   310 */   195,  193,  137,  278,  277,  276,  275,  274,  188,  187,
 /*   320 */   181,   80,   98,  182,  186,  261,   38,  111,  133,  151,
 /*   330 */     8,   39,  139,  105,   83,  148,    6,   10,  161,  186,
 /*   340 */   186,   22,   13,    5,   77,    4,   76,   75,  200,  106,
 /*   350 */    83,  183,  162,   30,  252,  196,   17,  194,  173,  172,
 /*   360 */   259,  213,  294,  199,    2,  170,  286,  258,  195,  193,
 /*   370 */   137,  278,  277,  276,  275,  274,  188,  187,  169,  166,
 /*   380 */    98,  186,  186,  167,  164,  111,  133,  151,    8,   39,
 /*   390 */   257,   86,   83,  148,    6,   10,  251,  186,  186,   22,
 /*   400 */    13,    5,   77,    4,   76,   75,  140,  106,   83,  183,
 /*   410 */   142,  163,  121,  196,  256,  194,  255,   29,   15,  248,
 /*   420 */   211,  198,    2,  250,  286,    1,  195,  193,  137,  278,
 /*   430 */   277,  276,  275,  274,  188,  187,  247,  246,   98,  186,
 /*   440 */   186,  109,   25,  111,  133,  151,    8,   39,  241,   85,
 /*   450 */    83,  148,    6,   10,  120,  186,  186,   22,   13,    5,
 /*   460 */    77,    4,   76,   75,  270,  106,   83,  183,  159,   24,
 /*   470 */   119,  196,   11,  194,   23,  235,  229,  222,  271,  197,
 /*   480 */     2,  288,  286,   16,  195,  193,  137,  278,  277,  276,
 /*   490 */   275,  274,  188,  187,  141,  216,   98,  309,  186,  212,
 /*   500 */   289,  111,  133,  151,    8,   39,  287,  290,   83,  148,
 /*   510 */     6,   10,  118,  180,  186,   22,   13,    5,   77,    4,
 /*   520 */    76,   75,   60,   59,  106,  206,  264,  203,   58,  269,
 /*   530 */   107,  285,  186,  136,  135,   71,  134,  292,  291,   21,
 /*   540 */   297,  268,  117,   74,   78,  176,  174,  171,  168,  165,
 /*   550 */    79,   78,   65,   64,   70,   69,   67,   68,   66,  131,
 /*   560 */   215,  143,  244,  186,  238,  147,  144,   18,  219,  218,
 /*   570 */    20,   72,  143,  116,  184,  214,  186,  129,  150,  138,
 /*   580 */   467,   60,   59,  186,  467,  186,  128,   58,  269,  107,
 /*   590 */   285,  467,  467,  127,   71,  126,  292,  290,   21,  467,
 /*   600 */   268,  186,  186,  467,  176,  174,  171,  168,  165,   79,
 /*   610 */    78,  115,  114,   70,   69,   67,   68,   66,  467,  467,
 /*   620 */   467,  244,  186,  238,  147,  144,   18,  219,  218,   20,
 /*   630 */    72,  143,  113,  184,  186,  186,  467,  467,  467,  467,
 /*   640 */    60,   59,  186,  467,  110,  112,   58,  269,  107,  285,
 /*   650 */   186,  467,  125,   71,  467,  292,  467,   21,  467,  268,
 /*   660 */   124,  467,  467,  176,  174,  171,  168,  165,   79,   78,
 /*   670 */   308,  210,  306,  209,  208,  207,  202,    9,  467,  186,
 /*   680 */   244,  467,  238,  147,  144,  467,  219,  218,   20,  123,
 /*   690 */   143,   57,   55,   54,   53,   52,   56,   62,   61,   63,
 /*   700 */    65,   64,   70,   69,   67,   68,   66,   27,  186,  467,
 /*   710 */   467,  467,  467,  467,  186,   18,  467,  467,  104,   72,
 /*   720 */    60,   59,  184,  467,  103,  186,   58,  269,  185,  467,
 /*   730 */   467,  467,  186,   71,  467,  102,  467,   21,  186,  175,
 /*   740 */   186,  467,  101,  176,  174,  171,  168,  165,  100,  186,
 /*   750 */    99,   26,  186,  467,  467,  467,  186,  186,  186,   84,
 /*   760 */   467,  467,   97,  186,   60,   59,   96,   95,   94,  160,
 /*   770 */    58,  269,  185,   93,  186,  467,  186,   71,  467,  467,
 /*   780 */   467,   21,  186,  175,   92,  186,   91,  176,  174,  171,
 /*   790 */   168,  165,   90,  467,  186,   89,  186,  467,  467,  467,
 /*   800 */   467,  467,   60,   59,   88,  467,   87,  467,   58,  269,
 /*   810 */   185,  467,  467,  160,  467,   71,  249,  467,  467,   21,
 /*   820 */   467,  268,  467,  265,  467,  176,  174,  171,  168,  165,
 /*   830 */   467,  467,   60,   59,  467,  467,  467,  467,   58,  269,
 /*   840 */   107,  467,  467,  467,  467,   71,  467,  467,  467,   21,
 /*   850 */   467,  268,  467,  467,  467,  176,  174,  171,  168,  165,
 /*   860 */    79,   78,  467,   62,   61,   63,   65,   64,   70,   69,
 /*   870 */    67,   68,   66,  467,  467,  467,  467,  467,  467,  467,
 /*   880 */   467,   18,  467,  467,  467,   72,  266,  467,  184,  467,
 /*   890 */   467,  467,  467,  467,  467,   62,   61,   63,   65,   64,
 /*   900 */    70,   69,   67,   68,   66,  467,  467,  467,  467,  467,
 /*   910 */   467,  467,  467,   18,  263,  467,  467,   72,  467,  467,
 /*   920 */   184,  467,  467,  467,  467,  467,  467,   62,   61,   63,
 /*   930 */    65,   64,   70,   69,   67,   68,   66,  467,  467,  467,
 /*   940 */   467,  467,  467,  467,  467,   18,  467,   60,   59,   72,
 /*   950 */   108,  467,  184,   58,  269,  185,  467,  467,  467,  467,
 /*   960 */    71,  467,  467,  467,   21,  467,  268,  467,  265,  467,
 /*   970 */   176,  174,  171,  168,  165,  467,  467,  467,  467,   60,
 /*   980 */    59,  467,  467,  467,  467,   58,  269,  107,  467,  467,
 /*   990 */   467,  467,   71,  224,  467,  467,   21,  467,  268,  467,
 /*  1000 */   467,  467,  176,  174,  171,  168,  165,  362,  362,  362,
 /*  1010 */   362,  362,  362,  362,  362,  362,  362,  467,  467,  467,
 /*  1020 */   467,  467,  467,  467,  467,   19,  467,  467,  467,  362,
 /*  1030 */   467,  467,  362,  467,  467,  467,  467,  467,  467,   62,
 /*  1040 */    61,   63,   65,   64,   70,   69,   67,   68,   66,  467,
 /*  1050 */   467,  467,  467,  467,  467,  467,  467,   18,  467,  467,
 /*  1060 */   467,   72,  467,  467,  184,  467,  467,  467,  467,  467,
 /*  1070 */   467,   62,   61,   63,   65,   64,   70,   69,   67,   68,
 /*  1080 */    66,  467,  467,  467,  467,  467,  467,  467,  467,   18,
 /*  1090 */   467,   60,   59,   51,  467,  467,  155,   58,  269,  185,
 /*  1100 */   467,  467,  467,  467,   71,  467,  467,  467,   21,  467,
 /*  1110 */   268,  467,  467,  467,  176,  174,  171,  168,  165,  467,
 /*  1120 */   467,  467,  467,   60,   59,  467,  467,  467,  467,   58,
 /*  1130 */   269,  107,  409,  409,  467,  467,   71,  467,  467,  467,
 /*  1140 */    21,  467,  268,  467,  408,  408,  176,  174,  171,  168,
 /*  1150 */   165,   61,   63,   65,   64,   70,   69,   67,   68,   66,
 /*  1160 */   467,  467,  467,  467,  467,  467,  467,  467,   18,  467,
 /*  1170 */   467,  467,   72,  467,  467,  184,  467,  467,  467,  409,
 /*  1180 */   409,  409,  409,  409,  409,  409,  409,  409,  409,   50,
 /*  1190 */   467,  408,  408,  408,  408,  408,  408,  408,  408,  408,
 /*  1200 */   408,   63,   65,   64,   70,   69,   67,   68,   66,  467,
 /*  1210 */   467,  467,  467,  467,  467,  467,  467,   18,  467,  467,
 /*  1220 */   467,   72,  467,  467,  184,  467,  467,  467,  467,  467,
 /*  1230 */   467,  467,  467,  234,  467,  232,   49,   48,   47,   46,
 /*  1240 */    45,   44,   43,   42,   41,   40,  233,  231,  186,  467,
 /*  1250 */   467,  467,  234,  467,  232,  467,  467,  467,   98,  467,
 /*  1260 */   467,  467,  467,  111,  133,  233,  231,  186,  467,  467,
 /*  1270 */   467,  467,  467,  467,  146,  145,  467,   98,  467,  467,
 /*  1280 */   467,  467,  111,  133,  467,  467,  467,  467,  467,  467,
 /*  1290 */   467,  467,  467,  230,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    69,   91,    3,    4,   27,    3,    4,   76,   27,   78,
 /*    10 */   100,  101,  102,   82,   83,   84,   85,   27,   87,   27,
 /*    20 */    89,   90,   91,   92,   93,   94,   95,   96,   97,   98,
 /*    30 */    26,   32,  101,   91,   32,    3,    4,  106,  107,  108,
 /*    40 */   109,  110,  100,  101,  102,  114,  115,  116,   20,   21,
 /*    50 */    22,  120,  121,  122,  123,  124,  125,  126,   69,   31,
 /*    60 */     3,    4,   26,   35,   32,   76,   38,   78,   32,    3,
 /*    70 */     4,   82,   83,   84,   85,   29,   87,   26,   89,   90,
 /*    80 */    91,   92,   93,   94,   95,   96,   97,   98,   26,   32,
 /*    90 */   101,   90,   91,   27,   31,  106,  107,  108,  109,  110,
 /*   100 */    26,    2,  101,  114,  115,  116,   27,  106,  107,  120,
 /*   110 */   121,  122,  123,  124,  125,  126,   69,   31,   27,   27,
 /*   120 */   119,   35,   27,   76,   38,   78,  111,  112,  113,   82,
 /*   130 */    83,   84,   85,   27,   87,   36,   89,   90,   91,   92,
 /*   140 */    93,   94,   95,   96,   97,   98,   27,    2,  101,   90,
 /*   150 */    91,   27,    2,  106,  107,  108,  109,  110,   27,   35,
 /*   160 */   101,  114,  115,  116,   27,  106,  107,  120,  121,  122,
 /*   170 */   123,  124,  125,  126,   69,   91,   91,   32,  119,    1,
 /*   180 */     2,   76,   32,   78,  100,  101,  101,   82,   83,   84,
 /*   190 */    85,  106,   87,   35,   89,   90,   91,   92,   93,   94,
 /*   200 */    95,   96,   97,   98,    1,    2,  101,   91,   91,    1,
 /*   210 */     2,  106,  107,  108,  109,  110,  100,  101,  101,  114,
 /*   220 */   115,  116,  105,   91,   25,  120,  121,  122,  123,  124,
 /*   230 */   125,  126,   69,  101,   91,  103,  104,    2,    2,   76,
 /*   240 */    36,   78,   36,  100,  101,   82,   83,   84,   85,   27,
 /*   250 */    87,   35,   89,   90,   91,   92,   93,   94,   95,   96,
 /*   260 */    97,   98,    1,    2,  101,   91,   91,   27,   32,  106,
 /*   270 */   107,  108,  109,  110,  100,  101,  101,  114,  115,  116,
 /*   280 */   105,   91,   31,  120,  121,  122,  123,  124,  125,  126,
 /*   290 */    69,  101,   91,  103,  104,   71,   72,   76,   63,   78,
 /*   300 */    26,  100,  101,   82,   83,   84,   85,    2,   87,   25,
 /*   310 */    89,   90,   91,   92,   93,   94,   95,   96,   97,   98,
 /*   320 */    35,   35,  101,   91,   91,   36,    2,  106,  107,  108,
 /*   330 */   109,  110,  100,  101,  101,  114,  115,  116,  105,   91,
 /*   340 */    91,  120,  121,  122,  123,  124,  125,  126,   69,  101,
 /*   350 */   101,  103,  104,   31,  105,   76,   31,   78,   31,   39,
 /*   360 */    32,   82,   83,   84,   85,   31,   87,   32,   89,   90,
 /*   370 */    91,   92,   93,   94,   95,   96,   97,   98,   39,   39,
 /*   380 */   101,   91,   91,   31,   31,  106,  107,  108,  109,  110,
 /*   390 */    32,  101,  101,  114,  115,  116,  105,   91,   91,  120,
 /*   400 */   121,  122,  123,  124,  125,  126,   69,  101,  101,  103,
 /*   410 */   104,   39,  105,   76,   32,   78,   32,    4,   31,   36,
 /*   420 */    83,   84,   85,   32,   87,   88,   89,   90,   91,   92,
 /*   430 */    93,   94,   95,   96,   97,   98,   32,   32,  101,   91,
 /*   440 */    91,   26,   31,  106,  107,  108,  109,  110,   58,  101,
 /*   450 */   101,  114,  115,  116,  105,   91,   91,  120,  121,  122,
 /*   460 */   123,  124,  125,  126,   69,  101,  101,  103,  104,   31,
 /*   470 */   105,   76,    2,   78,   31,   31,   27,   31,   83,   84,
 /*   480 */    85,   86,   87,   31,   89,   90,   91,   92,   93,   94,
 /*   490 */    95,   96,   97,   98,   32,   27,  101,    0,   91,   34,
 /*   500 */    86,  106,  107,  108,  109,  110,   86,   34,  101,  114,
 /*   510 */   115,  116,  105,   25,   91,  120,  121,  122,  123,  124,
 /*   520 */   125,  126,   18,   19,  101,   28,  103,   30,   24,   25,
 /*   530 */    26,   27,   91,   99,   81,   31,   81,   33,   34,   35,
 /*   540 */    26,   37,  101,   46,   47,   41,   42,   43,   44,   45,
 /*   550 */    46,   47,   16,   17,   18,   19,   20,   21,   22,   81,
 /*   560 */   125,   68,   58,   91,   60,   61,   62,   31,   64,   65,
 /*   570 */    66,   35,   68,  101,   38,  125,   91,   81,   59,   81,
 /*   580 */   127,   18,   19,   91,  127,   91,  101,   24,   25,   26,
 /*   590 */    27,  127,  127,  101,   31,  101,   33,   34,   35,  127,
 /*   600 */    37,   91,   91,  127,   41,   42,   43,   44,   45,   46,
 /*   610 */    47,  101,  101,   18,   19,   20,   21,   22,  127,  127,
 /*   620 */   127,   58,   91,   60,   61,   62,   31,   64,   65,   66,
 /*   630 */    35,   68,  101,   38,   91,   91,  127,  127,  127,  127,
 /*   640 */    18,   19,   91,  127,  101,  101,   24,   25,   26,   27,
 /*   650 */    91,  127,  101,   31,  127,   33,  127,   35,  127,   37,
 /*   660 */   101,  127,  127,   41,   42,   43,   44,   45,   46,   47,
 /*   670 */    73,   74,   75,   76,   77,   78,   79,   80,  127,   91,
 /*   680 */    58,  127,   60,   61,   62,  127,   64,   65,   66,  101,
 /*   690 */    68,    7,    8,    9,   10,   11,   12,   13,   14,   15,
 /*   700 */    16,   17,   18,   19,   20,   21,   22,    5,   91,  127,
 /*   710 */   127,  127,  127,  127,   91,   31,  127,  127,  101,   35,
 /*   720 */    18,   19,   38,  127,  101,   91,   24,   25,   26,  127,
 /*   730 */   127,  127,   91,   31,  127,  101,  127,   35,   91,   37,
 /*   740 */    91,  127,  101,   41,   42,   43,   44,   45,  101,   91,
 /*   750 */   101,    5,   91,  127,  127,  127,   91,   91,   91,  101,
 /*   760 */   127,  127,  101,   91,   18,   19,  101,  101,  101,   67,
 /*   770 */    24,   25,   26,  101,   91,  127,   91,   31,  127,  127,
 /*   780 */   127,   35,   91,   37,  101,   91,  101,   41,   42,   43,
 /*   790 */    44,   45,  101,  127,   91,  101,   91,  127,  127,  127,
 /*   800 */   127,  127,   18,   19,  101,  127,  101,  127,   24,   25,
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
#define YY_SHIFT_USE_DFLT (-24)
#define YY_SHIFT_COUNT (210)
#define YY_SHIFT_MIN   (-23)
#define YY_SHIFT_MAX   (1188)
static const short yy_shift_ofst[] = {
 /*     0 */   -24,  563,  504,  622,  622,  622,  622,  622,  622,  622,
 /*    10 */   814,  814,  497,  961, 1105,  784,  929,  929,  929,  929,
 /*    20 */  1073, 1073,  702,  702,  702,  702,  746,  746,  702,  702,
 /*    30 */   702,  929, 1073, 1073, 1073, 1105, 1073, 1073, 1073,  519,
 /*    40 */  1073, 1073, 1073, 1073, 1073, 1073, 1073, 1073, 1073, 1073,
 /*    50 */  1073, 1073, 1073, 1073, 1073, 1073, 1073, 1073, 1073, 1073,
 /*    60 */  1073, 1073, 1073, 1073, 1073, 1073, 1073, 1073, 1073, 1073,
 /*    70 */  1073, 1073, 1073,   36,  514,  493,  493,  514,  514,  514,
 /*    80 */   488,  473,  473,  684,  914,  882,  850, 1026, 1026, 1026,
 /*    90 */  1026, 1026, 1026, 1026, 1026, 1026, 1026, 1026, 1058, 1026,
 /*   100 */  1026, 1026, 1026, 1026, 1026, 1026, 1026,  994, 1143, 1131,
 /*   110 */  1137, 1188, 1186,  536,  595,  595,   28,   28,   66,   57,
 /*   120 */    32,    2,   -1,   86,   86,   86,   86,   86,   86,  261,
 /*   130 */   236,  235,  150,  208,  203,  178,   99,  124,  145,  324,
 /*   140 */   465,  468,  462,  452,  446,  449,  470,  444,  443,  438,
 /*   150 */   390,  411,  324,  324,  324,  415,  405,  404,  383,  391,
 /*   160 */   387,  413,  384,  382,  372,  353,  358,  340,  352,  335,
 /*   170 */   339,  334,  328,  320,  327,  325,  322,  324,  289,  284,
 /*   180 */   204,  286,  285,  305,  274,  251,  216,  240,  222,  206,
 /*   190 */   204,  199,  158,  137,  131,  119,  106,   95,   92,   91,
 /*   200 */    79,   74,   63,   62,   51,   46,    4,   -8,  -10,  -19,
 /*   210 */   -23,
};
#define YY_REDUCE_USE_DFLT (-91)
#define YY_REDUCE_COUNT (82)
#define YY_REDUCE_MIN   (-90)
#define YY_REDUCE_MAX   (1176)
static const short yy_reduce_ofst[] = {
 /*     0 */   224,  395,  337,  279,  221,  163,  105,   47,  -11,  -69,
 /*    10 */  1157, 1176,  597,   59,    1,  364,  306,  248,  190,  132,
 /*    20 */   -58,  -90,  407,  365,  349,  307,  291,  249,  233,  175,
 /*    30 */   117,  423,  232,  201,  174,   85,  143,  116,   84,   15,
 /*    40 */   705,  703,  694,  691,  685,  683,  672,  667,  666,  665,
 /*    50 */   661,  658,  649,  647,  641,  634,  623,  617,  588,  559,
 /*    60 */   551,  544,  543,  531,  511,  510,  494,  492,  485,  472,
 /*    70 */   441,  348,  290,  498,  496,  450,  435,  478,  455,  453,
 /*    80 */   434,  420,  414,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   310,  465,  465,  465,  465,  465,  465,  465,  465,  465,
 /*    10 */   443,  465,  465,  465,  465,  465,  368,  368,  368,  368,
 /*    20 */   358,  358,  465,  465,  465,  465,  465,  465,  465,  465,
 /*    30 */   465,  465,  465,  465,  465,  465,  465,  465,  465,  431,
 /*    40 */   465,  465,  465,  465,  465,  465,  465,  465,  465,  465,
 /*    50 */   465,  465,  465,  465,  465,  465,  465,  465,  465,  465,
 /*    60 */   465,  465,  465,  465,  465,  465,  465,  465,  465,  465,
 /*    70 */   465,  465,  465,  465,  465,  464,  463,  465,  465,  465,
 /*    80 */   465,  465,  465,  465,  465,  465,  465,  423,  422,  421,
 /*    90 */   420,  419,  418,  417,  416,  415,  414,  412,  465,  398,
 /*   100 */   397,  396,  395,  394,  393,  356,  365,  407,  364,  363,
 /*   110 */   388,  410,  389,  387,  386,  385,  381,  380,  465,  465,
 /*   120 */   465,  465,  465,  392,  391,  390,  384,  383,  382,  403,
 /*   130 */   465,  465,  465,  465,  465,  403,  465,  372,  465,  405,
 /*   140 */   465,  465,  465,  465,  465,  465,  442,  465,  465,  465,
 /*   150 */   430,  465,  413,  406,  404,  465,  465,  465,  465,  465,
 /*   160 */   465,  400,  465,  465,  465,  465,  465,  465,  465,  465,
 /*   170 */   465,  465,  465,  465,  465,  361,  465,  359,  465,  465,
 /*   180 */   350,  465,  372,  369,  465,  362,  372,  465,  465,  465,
 /*   190 */   465,  465,  465,  465,  465,  465,  465,  465,  465,  465,
 /*   200 */   465,  465,  465,  465,  465,  318,  465,  465,  465,  465,
 /*   210 */   465,  347,  332,  432,  462,  461,  460,  456,  455,  454,
 /*   220 */   453,  452,  451,  450,  449,  448,  445,  444,  447,  446,
 /*   230 */   441,  440,  439,  438,  437,  436,  435,  434,  433,  429,
 /*   240 */   428,  427,  426,  425,  424,  411,  370,  371,  374,  459,
 /*   250 */   457,  402,  401,  399,  375,  458,  379,  378,  377,  376,
 /*   260 */   357,  354,  351,  373,  367,  366,  364,  363,  361,  360,
 /*   270 */   349,  348,  346,  345,  344,  343,  342,  341,  340,  355,
 /*   280 */   339,  338,  337,  336,  335,  334,  333,  331,  330,  329,
 /*   290 */   327,  328,  326,  325,  324,  323,  322,  352,  321,  353,
 /*   300 */   320,  319,  317,  316,  315,  314,  313,  312,  311,
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
  "vdef_stmt",     "vdefAssign_global_stmt",  "cdef_stmt",     "function_start",
  "function_header",  "nameList_nonEmpty",  "stmt",          "bodyStmt",    
  "return_stmt",   "lbracket",      "rbracket",      "blockStmt",   
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
 /*   8 */ "import_chunk ::= IMPORT NAME AS NAME",
 /*   9 */ "import_chunk ::= IMPORT NAME",
 /*  10 */ "function_start ::= FUNCTION NAME",
 /*  11 */ "function_header ::= function_start LPAREN nameList_nonEmpty RPAREN",
 /*  12 */ "function_header ::= function_start LPAREN RPAREN",
 /*  13 */ "fdef_chunk ::= function_header stmt",
 /*  14 */ "stmt ::= error SEMICOLON",
 /*  15 */ "stmt ::= bodyStmt",
 /*  16 */ "stmt ::= return_stmt SEMICOLON",
 /*  17 */ "lbracket ::= LBRACKET",
 /*  18 */ "rbracket ::= RBRACKET",
 /*  19 */ "blockStmt ::= lbracket RBRACKET",
 /*  20 */ "blockStmt ::= lbracket return_stmt SEMICOLON rbracket",
 /*  21 */ "blockStmt ::= lbracket bodyStmtList rbracket",
 /*  22 */ "blockStmt ::= lbracket bodyStmtList return_stmt SEMICOLON rbracket",
 /*  23 */ "blockStmt ::= lbracket error RBRACKET",
 /*  24 */ "bodyStmt ::= blockStmt",
 /*  25 */ "bodyStmt ::= SEMICOLON",
 /*  26 */ "bodyStmt ::= vdef_stmt SEMICOLON",
 /*  27 */ "bodyStmt ::= vdefAssign_stmt SEMICOLON",
 /*  28 */ "bodyStmt ::= cdef_stmt SEMICOLON",
 /*  29 */ "bodyStmt ::= assign_stmt SEMICOLON",
 /*  30 */ "bodyStmt ::= funcexpr SEMICOLON",
 /*  31 */ "bodyStmt ::= actionStmt",
 /*  32 */ "bodyStmt ::= if_stmt",
 /*  33 */ "bodyStmt ::= while_stmt",
 /*  34 */ "bodyStmt ::= for_stmt",
 /*  35 */ "bodyStmt ::= foreach_stmt",
 /*  36 */ "bodyStmt ::= continue_stmt SEMICOLON",
 /*  37 */ "bodyStmt ::= break_stmt SEMICOLON",
 /*  38 */ "bodyStmtList ::= bodyStmt",
 /*  39 */ "bodyStmtList ::= bodyStmtList bodyStmt",
 /*  40 */ "bodyStmtList ::= bodyStmtList error",
 /*  41 */ "numList_nonEmpty ::= NUMBER",
 /*  42 */ "numList_nonEmpty ::= numList_nonEmpty COMMA NUMBER",
 /*  43 */ "nameList_nonEmpty ::= NAME",
 /*  44 */ "nameList_nonEmpty ::= nameList_nonEmpty COMMA NAME",
 /*  45 */ "exprList_nonEmpty ::= funcexpr LSQBRACKET LSQBRACKET numList_nonEmpty RSQBRACKET RSQBRACKET",
 /*  46 */ "expr ::= funcexpr LSQBRACKET LSQBRACKET NUMBER RSQBRACKET RSQBRACKET",
 /*  47 */ "exprList_nonEmpty ::= expr",
 /*  48 */ "exprList_nonEmpty ::= exprList_nonEmpty COMMA exprList_nonEmpty",
 /*  49 */ "exprList ::=",
 /*  50 */ "exprList ::= exprList_nonEmpty",
 /*  51 */ "expr ::= NUMBER",
 /*  52 */ "expr ::= KILLS",
 /*  53 */ "expr ::= NAME",
 /*  54 */ "expr ::= expr PERIOD NAME",
 /*  55 */ "expr ::= expr LSQBRACKET expr RSQBRACKET",
 /*  56 */ "fArgs_nonEmpty ::= expr",
 /*  57 */ "fArgs_nonEmpty ::= STRING",
 /*  58 */ "fArgs_nonEmpty ::= fArgs_nonEmpty COMMA fArgs_nonEmpty",
 /*  59 */ "fArgs ::=",
 /*  60 */ "fArgs ::= fArgs_nonEmpty",
 /*  61 */ "funcexpr ::= NAME LPAREN fArgs RPAREN",
 /*  62 */ "funcexpr ::= expr LPAREN fArgs RPAREN",
 /*  63 */ "expr ::= funcexpr",
 /*  64 */ "expr ::= LPAREN expr RPAREN",
 /*  65 */ "expr ::= LSQBRACKET exprList RSQBRACKET",
 /*  66 */ "expr ::= L2V LPAREN lexpr RPAREN",
 /*  67 */ "expr ::= MAPSTRING LPAREN STRING RPAREN",
 /*  68 */ "expr ::= UNIT LPAREN STRING RPAREN",
 /*  69 */ "expr ::= SWITCH LPAREN STRING RPAREN",
 /*  70 */ "expr ::= LOCATION LPAREN STRING RPAREN",
 /*  71 */ "expr ::= expr PLUS expr",
 /*  72 */ "expr ::= expr MINUS expr",
 /*  73 */ "expr ::= expr MULTIPLY expr",
 /*  74 */ "expr ::= expr DIVIDE expr",
 /*  75 */ "expr ::= expr MOD expr",
 /*  76 */ "expr ::= expr LSHIFT expr",
 /*  77 */ "expr ::= expr RSHIFT expr",
 /*  78 */ "expr ::= expr BITAND expr",
 /*  79 */ "expr ::= expr BITOR expr",
 /*  80 */ "expr ::= expr BITXOR expr",
 /*  81 */ "expr ::= PLUS expr",
 /*  82 */ "expr ::= MINUS expr",
 /*  83 */ "expr ::= BITNOT expr",
 /*  84 */ "lexpr ::= expr EQ expr",
 /*  85 */ "lexpr ::= expr NE expr",
 /*  86 */ "lexpr ::= expr LE expr",
 /*  87 */ "lexpr ::= expr LT expr",
 /*  88 */ "lexpr ::= expr GE expr",
 /*  89 */ "lexpr ::= expr GT expr",
 /*  90 */ "lexpr ::= lexpr LAND lexpr",
 /*  91 */ "lexpr ::= lexpr LOR lexpr",
 /*  92 */ "lexpr ::= LNOT lexpr",
 /*  93 */ "lexpr ::= LNOT LNOT lexpr",
 /*  94 */ "vdef_stmt ::= VAR nameList_nonEmpty",
 /*  95 */ "vdefAssign_stmt ::= VAR nameList_nonEmpty ASSIGN exprList_nonEmpty",
 /*  96 */ "vdefAssign_global_stmt ::= VAR nameList_nonEmpty ASSIGN exprList_nonEmpty",
 /*  97 */ "cdef_stmt ::= CONST nameList_nonEmpty ASSIGN exprList_nonEmpty",
 /*  98 */ "lvalue ::= NAME",
 /*  99 */ "lvalue ::= expr LSQBRACKET expr RSQBRACKET",
 /* 100 */ "lvalue ::= expr PERIOD NAME",
 /* 101 */ "lvalueList_nonEmpty ::= lvalue",
 /* 102 */ "lvalueList_nonEmpty ::= lvalueList_nonEmpty COMMA lvalue",
 /* 103 */ "assign_stmt ::= lvalue ASSIGN expr",
 /* 104 */ "assign_stmt ::= lvalueList_nonEmpty ASSIGN exprList_nonEmpty",
 /* 105 */ "assign_stmt ::= lvalue IADD expr",
 /* 106 */ "assign_stmt ::= lvalue ISUB expr",
 /* 107 */ "assign_stmt ::= lvalue IMUL expr",
 /* 108 */ "assign_stmt ::= lvalue IDIV expr",
 /* 109 */ "assign_stmt ::= lvalue IMOD expr",
 /* 110 */ "assign_stmt ::= lvalue ILSH expr",
 /* 111 */ "assign_stmt ::= lvalue IRSH expr",
 /* 112 */ "assign_stmt ::= lvalue IBND expr",
 /* 113 */ "assign_stmt ::= lvalue IBOR expr",
 /* 114 */ "assign_stmt ::= lvalue IBXR expr",
 /* 115 */ "if_start ::= IF",
 /* 116 */ "if_header ::= if_start LPAREN lexpr RPAREN",
 /* 117 */ "if_block ::= if_header stmt",
 /* 118 */ "elif_start ::= ELSE IF",
 /* 119 */ "elif_header ::= elif_start LPAREN lexpr RPAREN",
 /* 120 */ "if_block ::= if_block elif_header stmt",
 /* 121 */ "else_header ::= ELSE",
 /* 122 */ "if_stmt ::= if_block",
 /* 123 */ "if_stmt ::= if_block else_header stmt",
 /* 124 */ "while_start ::= WHILE",
 /* 125 */ "while_header ::= while_start LPAREN lexpr RPAREN",
 /* 126 */ "while_stmt ::= while_header stmt",
 /* 127 */ "for_opener ::= FOR LPAREN",
 /* 128 */ "for_init_stmt_nonEmpty ::= vdef_stmt",
 /* 129 */ "for_init_stmt_nonEmpty ::= vdefAssign_stmt",
 /* 130 */ "for_init_stmt_nonEmpty ::= cdef_stmt",
 /* 131 */ "for_init_stmt_nonEmpty ::= assign_stmt",
 /* 132 */ "for_init_stmt_nonEmpty ::= for_init_stmt_nonEmpty COMMA for_init_stmt_nonEmpty",
 /* 133 */ "for_init_stmt ::= for_init_stmt_nonEmpty",
 /* 134 */ "for_init_stmt ::=",
 /* 135 */ "for_action_stmt_nonEmpty ::= assign_stmt",
 /* 136 */ "for_action_stmt_nonEmpty ::= for_action_stmt_nonEmpty COMMA for_action_stmt_nonEmpty",
 /* 137 */ "for_header1 ::= for_opener for_init_stmt SEMICOLON",
 /* 138 */ "for_header2 ::= for_header1 lexpr SEMICOLON",
 /* 139 */ "for_header ::= for_header2 for_action_stmt_nonEmpty RPAREN",
 /* 140 */ "for_header ::= for_header2 RPAREN",
 /* 141 */ "for_stmt ::= for_header stmt",
 /* 142 */ "foreach_opener ::= FOREACH LPAREN",
 /* 143 */ "foreach_header ::= foreach_opener nameList_nonEmpty COLON exprList_nonEmpty RPAREN",
 /* 144 */ "foreach_stmt ::= foreach_header stmt",
 /* 145 */ "continue_stmt ::= CONTINUE",
 /* 146 */ "break_stmt ::= BREAK",
 /* 147 */ "return_stmt ::= RETURN exprList",
 /* 148 */ "lexpr ::= CONDITIONNAME LPAREN fArgs RPAREN",
 /* 149 */ "lexpr ::= KILLS LPAREN fArgs RPAREN",
 /* 150 */ "lexpr ::= CONDITIONNAME LPAREN RPAREN",
 /* 151 */ "action ::= ACTIONNAME LPAREN fArgs RPAREN SEMICOLON",
 /* 152 */ "actions ::= action action",
 /* 153 */ "actions ::= actions action",
 /* 154 */ "actionStmt ::= action",
 /* 155 */ "actionStmt ::= actions",
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
#line 878 "parser\\epparser.c"
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
  { 74, 4 },
  { 74, 2 },
  { 79, 2 },
  { 80, 4 },
  { 80, 3 },
  { 75, 2 },
  { 82, 2 },
  { 82, 1 },
  { 82, 2 },
  { 85, 1 },
  { 86, 1 },
  { 87, 2 },
  { 87, 4 },
  { 87, 3 },
  { 87, 5 },
  { 87, 3 },
  { 83, 1 },
  { 83, 1 },
  { 83, 2 },
  { 83, 2 },
  { 83, 2 },
  { 83, 2 },
  { 83, 2 },
  { 83, 1 },
  { 83, 1 },
  { 83, 1 },
  { 83, 1 },
  { 83, 1 },
  { 83, 2 },
  { 83, 2 },
  { 88, 1 },
  { 88, 2 },
  { 88, 2 },
  { 99, 1 },
  { 99, 3 },
  { 81, 1 },
  { 81, 3 },
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
  { 84, 2 },
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
      case 8: /* import_chunk ::= IMPORT NAME AS NAME */
#line 70 "parser\\epparser.lemon"
{
    if(!ps->closure.defModule(yymsp[0].minor.yy0->data)) {
        throw_error(6754, "Importing already-declared module " + yymsp[0].minor.yy0->data);
    }
    ps->gen << "import " << yymsp[-2].minor.yy0->data << " as " << yymsp[0].minor.yy0->data << std::endl;
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 1335 "parser\\epparser.c"
        break;
      case 9: /* import_chunk ::= IMPORT NAME */
#line 78 "parser\\epparser.lemon"
{
    if(!ps->closure.defModule(yymsp[0].minor.yy0->data)) {
        throw_error(6754, "Importing already-declared module " + yymsp[0].minor.yy0->data);
    }
    ps->gen << "import " << yymsp[0].minor.yy0->data << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1346 "parser\\epparser.c"
        break;
      case 10: /* function_start ::= FUNCTION NAME */
#line 87 "parser\\epparser.lemon"
{
    // Preprocess yymsp[0].minor.yy0
    funcNamePreprocess(yymsp[0].minor.yy0->data);
    if(!ps->closure.defFunction(yymsp[0].minor.yy0->data)) {
        throw_error(4495, "Duplicate function " + yymsp[0].minor.yy0->data);
    }
    ps->closure.pushScope();
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1359 "parser\\epparser.c"
        break;
      case 11: /* function_header ::= function_start LPAREN nameList_nonEmpty RPAREN */
#line 97 "parser\\epparser.lemon"
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
#line 1378 "parser\\epparser.c"
        break;
      case 12: /* function_header ::= function_start LPAREN RPAREN */
#line 113 "parser\\epparser.lemon"
{
    ps->gen << "@EUDFunc" << std::endl;
    ps->gen << "def " << yymsp[-2].minor.yy0->data << "():" << std::endl;
    ps->gen.indent();
    tmpIndex = 1;
    delete yymsp[-2].minor.yy0;
}
#line 1389 "parser\\epparser.c"
        break;
      case 13: /* fdef_chunk ::= function_header stmt */
      case 144: /* foreach_stmt ::= foreach_header stmt */ yytestcase(yyruleno==144);
#line 121 "parser\\epparser.lemon"
{
    ps->gen.unindent(true);
    ps->closure.popScope();
}
#line 1398 "parser\\epparser.c"
        break;
      case 14: /* stmt ::= error SEMICOLON */
#line 128 "parser\\epparser.lemon"
{ throw_error(6974, "Error while parsing statement"); }
#line 1403 "parser\\epparser.c"
        break;
      case 17: /* lbracket ::= LBRACKET */
#line 134 "parser\\epparser.lemon"
{ ps->closure.pushScope(); }
#line 1408 "parser\\epparser.c"
        break;
      case 18: /* rbracket ::= RBRACKET */
#line 135 "parser\\epparser.lemon"
{ ps->closure.popScope(); }
#line 1413 "parser\\epparser.c"
        break;
      case 19: /* blockStmt ::= lbracket RBRACKET */
#line 137 "parser\\epparser.lemon"
{
    ps->gen << "pass" << std::endl;
    ps->closure.popScope();
}
#line 1421 "parser\\epparser.c"
        break;
      case 23: /* blockStmt ::= lbracket error RBRACKET */
#line 144 "parser\\epparser.lemon"
{
    throw_error(6298, "Block not terminated properly.");
    ps->closure.popScope();
}
#line 1429 "parser\\epparser.c"
        break;
      case 30: /* bodyStmt ::= funcexpr SEMICOLON */
#line 155 "parser\\epparser.lemon"
{ ps->gen << yymsp[-1].minor.yy0->data << std::endl; }
#line 1434 "parser\\epparser.c"
        break;
      case 40: /* bodyStmtList ::= bodyStmtList error */
#line 167 "parser\\epparser.lemon"
{
    throw_error(8510, "Incomplete statement");
}
#line 1441 "parser\\epparser.c"
        break;
      case 41: /* numList_nonEmpty ::= NUMBER */
      case 43: /* nameList_nonEmpty ::= NAME */ yytestcase(yyruleno==43);
      case 47: /* exprList_nonEmpty ::= expr */ yytestcase(yyruleno==47);
      case 50: /* exprList ::= exprList_nonEmpty */ yytestcase(yyruleno==50);
      case 51: /* expr ::= NUMBER */ yytestcase(yyruleno==51);
      case 56: /* fArgs_nonEmpty ::= expr */ yytestcase(yyruleno==56);
      case 57: /* fArgs_nonEmpty ::= STRING */ yytestcase(yyruleno==57);
      case 60: /* fArgs ::= fArgs_nonEmpty */ yytestcase(yyruleno==60);
      case 63: /* expr ::= funcexpr */ yytestcase(yyruleno==63);
      case 93: /* lexpr ::= LNOT LNOT lexpr */ yytestcase(yyruleno==93);
      case 101: /* lvalueList_nonEmpty ::= lvalue */ yytestcase(yyruleno==101);
#line 173 "parser\\epparser.lemon"
{ yygotominor.yy0 = yymsp[0].minor.yy0; }
#line 1456 "parser\\epparser.c"
        break;
      case 42: /* numList_nonEmpty ::= numList_nonEmpty COMMA NUMBER */
      case 44: /* nameList_nonEmpty ::= nameList_nonEmpty COMMA NAME */ yytestcase(yyruleno==44);
      case 102: /* lvalueList_nonEmpty ::= lvalueList_nonEmpty COMMA lvalue */ yytestcase(yyruleno==102);
#line 174 "parser\\epparser.lemon"
{ yygotominor.yy0 = commaConcat(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1463 "parser\\epparser.c"
        break;
      case 45: /* exprList_nonEmpty ::= funcexpr LSQBRACKET LSQBRACKET numList_nonEmpty RSQBRACKET RSQBRACKET */
#line 178 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "_SRET(" + yymsp[-5].minor.yy0->data + ", [" + yymsp[-2].minor.yy0->data + "])";
    delete yymsp[-5].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1472 "parser\\epparser.c"
        break;
      case 46: /* expr ::= funcexpr LSQBRACKET LSQBRACKET NUMBER RSQBRACKET RSQBRACKET */
#line 185 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-5].minor.yy0->data + "[" + yymsp[-2].minor.yy0->data + "]";
    delete yymsp[-5].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1481 "parser\\epparser.c"
        break;
      case 48: /* exprList_nonEmpty ::= exprList_nonEmpty COMMA exprList_nonEmpty */
#line 193 "parser\\epparser.lemon"
{ yygotominor.yy0 = new Token((yymsp[-2].minor.yy0->data) + ", " + (yymsp[0].minor.yy0->data), yymsp[0].minor.yy0); delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1486 "parser\\epparser.c"
        break;
      case 49: /* exprList ::= */
      case 59: /* fArgs ::= */ yytestcase(yyruleno==59);
#line 195 "parser\\epparser.lemon"
{ yygotominor.yy0 = genEmpty(); }
#line 1492 "parser\\epparser.c"
        break;
      case 52: /* expr ::= KILLS */
#line 200 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = "4";
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1500 "parser\\epparser.c"
        break;
      case 53: /* expr ::= NAME */
#line 205 "parser\\epparser.lemon"
{
    checkIsRValue(yymsp[0].minor.yy0->data);
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1508 "parser\\epparser.c"
        break;
      case 54: /* expr ::= expr PERIOD NAME */
#line 210 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + "." + yymsp[0].minor.yy0->data;
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1517 "parser\\epparser.c"
        break;
      case 55: /* expr ::= expr LSQBRACKET expr RSQBRACKET */
#line 216 "parser\\epparser.lemon"
{
    yymsp[-3].minor.yy0->data = yymsp[-3].minor.yy0->data + "[" + yymsp[-1].minor.yy0->data + "]";
    delete yymsp[-1].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 1526 "parser\\epparser.c"
        break;
      case 58: /* fArgs_nonEmpty ::= fArgs_nonEmpty COMMA fArgs_nonEmpty */
#line 225 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data;
    yymsp[-2].minor.yy0->type = TOKEN_TEMP;
    yygotominor.yy0 = yymsp[-2].minor.yy0;
    delete yymsp[0].minor.yy0;
}
#line 1536 "parser\\epparser.c"
        break;
      case 61: /* funcexpr ::= NAME LPAREN fArgs RPAREN */
#line 235 "parser\\epparser.lemon"
{
    // Preprocess yymsp[-3].minor.yy0
    funcNamePreprocess(yymsp[-3].minor.yy0->data);
    checkIsFunction(yymsp[-3].minor.yy0->data);
    yymsp[-3].minor.yy0->data += "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 1547 "parser\\epparser.c"
        break;
      case 62: /* funcexpr ::= expr LPAREN fArgs RPAREN */
#line 243 "parser\\epparser.lemon"
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
#line 1569 "parser\\epparser.c"
        break;
      case 64: /* expr ::= LPAREN expr RPAREN */
#line 265 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1577 "parser\\epparser.c"
        break;
      case 65: /* expr ::= LSQBRACKET exprList RSQBRACKET */
#line 270 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "EUDArray(FlattenList([" + yymsp[-1].minor.yy0->data + "]))";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1585 "parser\\epparser.c"
        break;
      case 66: /* expr ::= L2V LPAREN lexpr RPAREN */
#line 275 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "_L2V(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = genTemp(yymsp[-1].minor.yy0);
}
#line 1593 "parser\\epparser.c"
        break;
      case 67: /* expr ::= MAPSTRING LPAREN STRING RPAREN */
#line 280 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetStringIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1601 "parser\\epparser.c"
        break;
      case 68: /* expr ::= UNIT LPAREN STRING RPAREN */
#line 285 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "EncodeUnit(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1609 "parser\\epparser.c"
        break;
      case 69: /* expr ::= SWITCH LPAREN STRING RPAREN */
#line 290 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "EncodeSwitch(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1617 "parser\\epparser.c"
        break;
      case 70: /* expr ::= LOCATION LPAREN STRING RPAREN */
#line 295 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetLocationIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1625 "parser\\epparser.c"
        break;
      case 71: /* expr ::= expr PLUS expr */
#line 301 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "+",  yymsp[0].minor.yy0); }
#line 1630 "parser\\epparser.c"
        break;
      case 72: /* expr ::= expr MINUS expr */
#line 302 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "-",  yymsp[0].minor.yy0); }
#line 1635 "parser\\epparser.c"
        break;
      case 73: /* expr ::= expr MULTIPLY expr */
#line 303 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "*",  yymsp[0].minor.yy0); }
#line 1640 "parser\\epparser.c"
        break;
      case 74: /* expr ::= expr DIVIDE expr */
#line 304 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "//", yymsp[0].minor.yy0); }
#line 1645 "parser\\epparser.c"
        break;
      case 75: /* expr ::= expr MOD expr */
#line 305 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "%",  yymsp[0].minor.yy0); }
#line 1650 "parser\\epparser.c"
        break;
      case 76: /* expr ::= expr LSHIFT expr */
#line 306 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<<", yymsp[0].minor.yy0); }
#line 1655 "parser\\epparser.c"
        break;
      case 77: /* expr ::= expr RSHIFT expr */
#line 307 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">>", yymsp[0].minor.yy0); }
#line 1660 "parser\\epparser.c"
        break;
      case 78: /* expr ::= expr BITAND expr */
#line 308 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "&",  yymsp[0].minor.yy0); }
#line 1665 "parser\\epparser.c"
        break;
      case 79: /* expr ::= expr BITOR expr */
#line 309 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "|",  yymsp[0].minor.yy0); }
#line 1670 "parser\\epparser.c"
        break;
      case 80: /* expr ::= expr BITXOR expr */
#line 310 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "^",  yymsp[0].minor.yy0); }
#line 1675 "parser\\epparser.c"
        break;
      case 81: /* expr ::= PLUS expr */
#line 313 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = +" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1680 "parser\\epparser.c"
        break;
      case 82: /* expr ::= MINUS expr */
#line 314 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = -" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1685 "parser\\epparser.c"
        break;
      case 83: /* expr ::= BITNOT expr */
#line 315 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = ~" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1690 "parser\\epparser.c"
        break;
      case 84: /* lexpr ::= expr EQ expr */
#line 319 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "==", yymsp[0].minor.yy0); }
#line 1695 "parser\\epparser.c"
        break;
      case 85: /* lexpr ::= expr NE expr */
#line 320 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "!=", yymsp[0].minor.yy0); }
#line 1700 "parser\\epparser.c"
        break;
      case 86: /* lexpr ::= expr LE expr */
#line 321 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<=", yymsp[0].minor.yy0); }
#line 1705 "parser\\epparser.c"
        break;
      case 87: /* lexpr ::= expr LT expr */
#line 322 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<",  yymsp[0].minor.yy0); }
#line 1710 "parser\\epparser.c"
        break;
      case 88: /* lexpr ::= expr GE expr */
#line 323 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">=", yymsp[0].minor.yy0); }
#line 1715 "parser\\epparser.c"
        break;
      case 89: /* lexpr ::= expr GT expr */
#line 324 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">" , yymsp[0].minor.yy0); }
#line 1720 "parser\\epparser.c"
        break;
      case 90: /* lexpr ::= lexpr LAND lexpr */
#line 326 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "[" + yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data + "]";
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1729 "parser\\epparser.c"
        break;
      case 91: /* lexpr ::= lexpr LOR lexpr */
#line 332 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "EUDOr([" + yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data + "])";
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1738 "parser\\epparser.c"
        break;
      case 92: /* lexpr ::= LNOT lexpr */
#line 338 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = "EUDNot([" + yymsp[0].minor.yy0->data + "])";
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0);
}
#line 1746 "parser\\epparser.c"
        break;
      case 94: /* vdef_stmt ::= VAR nameList_nonEmpty */
#line 348 "parser\\epparser.lemon"
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
#line 1770 "parser\\epparser.c"
        break;
      case 95: /* vdefAssign_stmt ::= VAR nameList_nonEmpty ASSIGN exprList_nonEmpty */
#line 369 "parser\\epparser.lemon"
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
#line 1795 "parser\\epparser.c"
        break;
      case 96: /* vdefAssign_global_stmt ::= VAR nameList_nonEmpty ASSIGN exprList_nonEmpty */
#line 391 "parser\\epparser.lemon"
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
#line 1819 "parser\\epparser.c"
        break;
      case 97: /* cdef_stmt ::= CONST nameList_nonEmpty ASSIGN exprList_nonEmpty */
#line 412 "parser\\epparser.lemon"
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
#line 1841 "parser\\epparser.c"
        break;
      case 98: /* lvalue ::= NAME */
#line 432 "parser\\epparser.lemon"
{
    checkIsVariable(yymsp[0].minor.yy0->data);
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1849 "parser\\epparser.c"
        break;
      case 99: /* lvalue ::= expr LSQBRACKET expr RSQBRACKET */
#line 437 "parser\\epparser.lemon"
{
    checkIsConstant(yymsp[-3].minor.yy0->data);
    yymsp[-1].minor.yy0->data = "_ARRW(" + yymsp[-3].minor.yy0->data + ", " + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
    delete yymsp[-3].minor.yy0;
}
#line 1859 "parser\\epparser.c"
        break;
      case 100: /* lvalue ::= expr PERIOD NAME */
#line 444 "parser\\epparser.lemon"
{
    checkIsConstant(yymsp[-2].minor.yy0->data);
    yymsp[0].minor.yy0->data = "_ATTW(" + yymsp[-2].minor.yy0->data + ", '" + yymsp[0].minor.yy0->data + "')";
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0);
    delete yymsp[-2].minor.yy0;
}
#line 1869 "parser\\epparser.c"
        break;
      case 103: /* assign_stmt ::= lvalue ASSIGN expr */
#line 453 "parser\\epparser.lemon"
{
    ps->gen << yymsp[-2].minor.yy0->data << " << (" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 1877 "parser\\epparser.c"
        break;
      case 104: /* assign_stmt ::= lvalueList_nonEmpty ASSIGN exprList_nonEmpty */
#line 458 "parser\\epparser.lemon"
{
    ps->gen << "_SV([" << yymsp[-2].minor.yy0->data << "], [" << yymsp[0].minor.yy0->data << "])" << std::endl;
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 1885 "parser\\epparser.c"
        break;
      case 105: /* assign_stmt ::= lvalue IADD expr */
#line 466 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__iadd__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1890 "parser\\epparser.c"
        break;
      case 106: /* assign_stmt ::= lvalue ISUB expr */
#line 467 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__isub__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1895 "parser\\epparser.c"
        break;
      case 107: /* assign_stmt ::= lvalue IMUL expr */
#line 468 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__imul__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1900 "parser\\epparser.c"
        break;
      case 108: /* assign_stmt ::= lvalue IDIV expr */
#line 469 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ifloordiv__("  << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1905 "parser\\epparser.c"
        break;
      case 109: /* assign_stmt ::= lvalue IMOD expr */
#line 470 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__imod__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1910 "parser\\epparser.c"
        break;
      case 110: /* assign_stmt ::= lvalue ILSH expr */
#line 471 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ilshift__("    << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1915 "parser\\epparser.c"
        break;
      case 111: /* assign_stmt ::= lvalue IRSH expr */
#line 472 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__irshift__("    << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1920 "parser\\epparser.c"
        break;
      case 112: /* assign_stmt ::= lvalue IBND expr */
#line 473 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__iand__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1925 "parser\\epparser.c"
        break;
      case 113: /* assign_stmt ::= lvalue IBOR expr */
#line 474 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ior__("        << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1930 "parser\\epparser.c"
        break;
      case 114: /* assign_stmt ::= lvalue IBXR expr */
#line 475 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ixor__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1935 "parser\\epparser.c"
        break;
      case 115: /* if_start ::= IF */
#line 478 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDIf()" << std::endl;
}
#line 1943 "parser\\epparser.c"
        break;
      case 116: /* if_header ::= if_start LPAREN lexpr RPAREN */
      case 125: /* while_header ::= while_start LPAREN lexpr RPAREN */ yytestcase(yyruleno==125);
#line 482 "parser\\epparser.lemon"
{
    ps->gen << "if " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data << "):" << std::endl;
    ps->gen.indent();
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1953 "parser\\epparser.c"
        break;
      case 118: /* elif_start ::= ELSE IF */
#line 490 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen.unindent(false);
    ps->gen << yygotominor.yy0->data << " = EUDElseIf()" << std::endl;
}
#line 1962 "parser\\epparser.c"
        break;
      case 119: /* elif_header ::= elif_start LPAREN lexpr RPAREN */
#line 496 "parser\\epparser.lemon"
{
    ps->gen << "if " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data <<"):" << std::endl;
    ps->gen.indent();
}
#line 1970 "parser\\epparser.c"
        break;
      case 121: /* else_header ::= ELSE */
#line 503 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "if EUDElse()():" << std::endl;
    ps->gen.indent();
}
#line 1979 "parser\\epparser.c"
        break;
      case 122: /* if_stmt ::= if_block */
      case 123: /* if_stmt ::= if_block else_header stmt */ yytestcase(yyruleno==123);
#line 509 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndIf()" << std::endl;
}
#line 1988 "parser\\epparser.c"
        break;
      case 124: /* while_start ::= WHILE */
#line 521 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDWhile()" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1997 "parser\\epparser.c"
        break;
      case 126: /* while_stmt ::= while_header stmt */
#line 533 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndWhile()" << std::endl;
}
#line 2005 "parser\\epparser.c"
        break;
      case 127: /* for_opener ::= FOR LPAREN */
      case 142: /* foreach_opener ::= FOREACH LPAREN */ yytestcase(yyruleno==142);
#line 539 "parser\\epparser.lemon"
{
    ps->closure.pushScope();
}
#line 2013 "parser\\epparser.c"
        break;
      case 137: /* for_header1 ::= for_opener for_init_stmt SEMICOLON */
#line 555 "parser\\epparser.lemon"
{
    // opening for lexpr
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDWhile()" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2023 "parser\\epparser.c"
        break;
      case 138: /* for_header2 ::= for_header1 lexpr SEMICOLON */
#line 562 "parser\\epparser.lemon"
{
    ps->gen << "if " << yymsp[-2].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data << "):" << std::endl;
    ps->gen.indent();
    delete yymsp[-2].minor.yy0; delete yymsp[-1].minor.yy0;

    // Opening for assign_statement
    yygotominor.yy0 = genTemp(yymsp[-1].minor.yy0);
    ps->gen << "def " << yygotominor.yy0->data <<"():" << std::endl;
    ps->gen.indent();
}
#line 2037 "parser\\epparser.c"
        break;
      case 139: /* for_header ::= for_header2 for_action_stmt_nonEmpty RPAREN */
#line 573 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-2].minor.yy0;
    ps->gen.unindent(false);
}
#line 2045 "parser\\epparser.c"
        break;
      case 140: /* for_header ::= for_header2 RPAREN */
#line 578 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
    ps->gen << "pass" << std::endl;
    ps->gen.unindent(false);
}
#line 2054 "parser\\epparser.c"
        break;
      case 141: /* for_stmt ::= for_header stmt */
#line 584 "parser\\epparser.lemon"
{
    ps->gen << yymsp[-1].minor.yy0->data << "()" << std::endl;
    ps->gen.unindent(false);
    ps->gen << "EUDEndWhile()" << std::endl;
    ps->closure.popScope();
}
#line 2064 "parser\\epparser.c"
        break;
      case 143: /* foreach_header ::= foreach_opener nameList_nonEmpty COLON exprList_nonEmpty RPAREN */
#line 598 "parser\\epparser.lemon"
{
    commaListIter(yymsp[-3].minor.yy0->data, [&](std::string& s) {
        ps->closure.defVariable(s);
    });
    ps->gen << "for " << yymsp[-3].minor.yy0->data << " in " << yymsp[-1].minor.yy0->data << ":" << std::endl;
    ps->gen.indent();
}
#line 2075 "parser\\epparser.c"
        break;
      case 145: /* continue_stmt ::= CONTINUE */
#line 614 "parser\\epparser.lemon"
{
    ps->gen << "EUDContinue()" << std::endl;
}
#line 2082 "parser\\epparser.c"
        break;
      case 146: /* break_stmt ::= BREAK */
#line 618 "parser\\epparser.lemon"
{
    ps->gen << "EUDBreak()" << std::endl;
}
#line 2089 "parser\\epparser.c"
        break;
      case 147: /* return_stmt ::= RETURN exprList */
#line 625 "parser\\epparser.lemon"
{
    ps->gen << "EUDReturn(" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2097 "parser\\epparser.c"
        break;
      case 148: /* lexpr ::= CONDITIONNAME LPAREN fArgs RPAREN */
      case 149: /* lexpr ::= KILLS LPAREN fArgs RPAREN */ yytestcase(yyruleno==149);
#line 633 "parser\\epparser.lemon"
{
    yymsp[-3].minor.yy0->data = yymsp[-3].minor.yy0->data + "(" + yymsp[-1].minor.yy0->data + ")";
    delete yymsp[-1].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 2107 "parser\\epparser.c"
        break;
      case 150: /* lexpr ::= CONDITIONNAME LPAREN RPAREN */
#line 645 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + "()";
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 2115 "parser\\epparser.c"
        break;
      case 151: /* action ::= ACTIONNAME LPAREN fArgs RPAREN SEMICOLON */
#line 650 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[-4].minor.yy0);
    yygotominor.yy0->data =  yymsp[-4].minor.yy0->data + "(" + yymsp[-2].minor.yy0->data + ")";
    delete yymsp[-4].minor.yy0; delete yymsp[-2].minor.yy0;
}
#line 2124 "parser\\epparser.c"
        break;
      case 152: /* actions ::= action action */
      case 153: /* actions ::= actions action */ yytestcase(yyruleno==153);
#line 656 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
    yymsp[-1].minor.yy0->data += ",\n" + yymsp[0].minor.yy0->data;
    delete yymsp[0].minor.yy0;
}
#line 2134 "parser\\epparser.c"
        break;
      case 154: /* actionStmt ::= action */
#line 668 "parser\\epparser.lemon"
{
    ps->gen << "DoActions(" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2142 "parser\\epparser.c"
        break;
      case 155: /* actionStmt ::= actions */
#line 673 "parser\\epparser.lemon"
{
    ps->gen << "DoActions([" << std::endl;
    ps->gen.indent();
    ps->gen << yymsp[0].minor.yy0->data << std::endl;
    ps->gen.unindent(false);
    ps->gen << "])" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2154 "parser\\epparser.c"
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
      /* (15) stmt ::= bodyStmt */ yytestcase(yyruleno==15);
      /* (16) stmt ::= return_stmt SEMICOLON */ yytestcase(yyruleno==16);
      /* (20) blockStmt ::= lbracket return_stmt SEMICOLON rbracket */ yytestcase(yyruleno==20);
      /* (21) blockStmt ::= lbracket bodyStmtList rbracket */ yytestcase(yyruleno==21);
      /* (22) blockStmt ::= lbracket bodyStmtList return_stmt SEMICOLON rbracket */ yytestcase(yyruleno==22);
      /* (24) bodyStmt ::= blockStmt */ yytestcase(yyruleno==24);
      /* (25) bodyStmt ::= SEMICOLON */ yytestcase(yyruleno==25);
      /* (26) bodyStmt ::= vdef_stmt SEMICOLON */ yytestcase(yyruleno==26);
      /* (27) bodyStmt ::= vdefAssign_stmt SEMICOLON */ yytestcase(yyruleno==27);
      /* (28) bodyStmt ::= cdef_stmt SEMICOLON */ yytestcase(yyruleno==28);
      /* (29) bodyStmt ::= assign_stmt SEMICOLON */ yytestcase(yyruleno==29);
      /* (31) bodyStmt ::= actionStmt */ yytestcase(yyruleno==31);
      /* (32) bodyStmt ::= if_stmt */ yytestcase(yyruleno==32);
      /* (33) bodyStmt ::= while_stmt */ yytestcase(yyruleno==33);
      /* (34) bodyStmt ::= for_stmt */ yytestcase(yyruleno==34);
      /* (35) bodyStmt ::= foreach_stmt */ yytestcase(yyruleno==35);
      /* (36) bodyStmt ::= continue_stmt SEMICOLON */ yytestcase(yyruleno==36);
      /* (37) bodyStmt ::= break_stmt SEMICOLON */ yytestcase(yyruleno==37);
      /* (38) bodyStmtList ::= bodyStmt */ yytestcase(yyruleno==38);
      /* (39) bodyStmtList ::= bodyStmtList bodyStmt */ yytestcase(yyruleno==39);
      /* (117) if_block ::= if_header stmt */ yytestcase(yyruleno==117);
      /* (120) if_block ::= if_block elif_header stmt */ yytestcase(yyruleno==120);
      /* (128) for_init_stmt_nonEmpty ::= vdef_stmt */ yytestcase(yyruleno==128);
      /* (129) for_init_stmt_nonEmpty ::= vdefAssign_stmt */ yytestcase(yyruleno==129);
      /* (130) for_init_stmt_nonEmpty ::= cdef_stmt */ yytestcase(yyruleno==130);
      /* (131) for_init_stmt_nonEmpty ::= assign_stmt */ yytestcase(yyruleno==131);
      /* (132) for_init_stmt_nonEmpty ::= for_init_stmt_nonEmpty COMMA for_init_stmt_nonEmpty */ yytestcase(yyruleno==132);
      /* (133) for_init_stmt ::= for_init_stmt_nonEmpty */ yytestcase(yyruleno==133);
      /* (134) for_init_stmt ::= */ yytestcase(yyruleno==134);
      /* (135) for_action_stmt_nonEmpty ::= assign_stmt */ yytestcase(yyruleno==135);
      /* (136) for_action_stmt_nonEmpty ::= for_action_stmt_nonEmpty COMMA for_action_stmt_nonEmpty */ yytestcase(yyruleno==136);
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
#line 2244 "parser\\epparser.c"
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
#line 687 "parser\\epparser.lemon"


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
#line 2497 "parser\\epparser.c"
