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
#line 29 "parser\\epparser.c"
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
#define YYNOCODE 127
#define YYACTIONTYPE unsigned short int
#define ParseTOKENTYPE Token*
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  int yy253;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL  ParserStruct* ps ;
#define ParseARG_PDECL , ParserStruct* ps 
#define ParseARG_FETCH  ParserStruct* ps  = yypParser->ps 
#define ParseARG_STORE yypParser->ps  = ps 
#define YYNSTATE 305
#define YYNRULE 154
#define YYERRORSYMBOL 69
#define YYERRSYMDT yy253
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
#define YY_ACTTAB_COUNT (1288)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   198,  180,   18,  147,    7,    3,   71,  194,  192,  182,
 /*    10 */   257,  104,  293,  291,  197,    2,  303,  283,  301,  193,
 /*    20 */   191,  135,  275,  274,  273,  272,  271,  186,  185,   28,
 /*    30 */    29,   97,  224,  184,   28,   29,  110,  131,  149,    8,
 /*    40 */    38,  177,  300,   97,  146,    6,   10,  203,  110,  131,
 /*    50 */    22,   13,    5,   76,    4,   75,   74,  198,  251,  277,
 /*    60 */   294,  223,  199,  240,  194,  192,  295,  190,  199,  239,
 /*    70 */   291,  197,    2,  202,  283,  176,  193,  191,  135,  275,
 /*    80 */   274,  273,  272,  271,  186,  185,   28,   29,   97,  224,
 /*    90 */   184,   28,   29,  110,  131,  149,    8,   38,  297,   72,
 /*   100 */    97,  146,    6,   10,  299,  110,  131,   22,   13,    5,
 /*   110 */    76,    4,   75,   74,  198,  237,   36,  199,  130,   14,
 /*   120 */   234,  194,  192,   32,   28,   29,  236,  291,  197,    2,
 /*   130 */   298,  283,  296,  193,  191,  135,  275,  274,  273,  272,
 /*   140 */   271,  186,  185,   35,  199,   97,  180,  292,  225,  222,
 /*   150 */   110,  131,  149,    8,   38,  175,  104,  156,  146,    6,
 /*   160 */    10,   33,   34,  180,   22,   13,    5,   76,    4,   75,
 /*   170 */    74,  198,  175,  104,  214,   37,  290,  184,  194,  192,
 /*   180 */   460,   12,   81,  233,  291,  197,    2,  105,  283,  261,
 /*   190 */   193,  191,  135,  275,  274,  273,  272,  271,  186,  185,
 /*   200 */   189,   80,   97,  180,  184,  218,  281,  110,  131,  149,
 /*   210 */     8,   38,  152,  104,   82,  146,    6,   10,  121,  184,
 /*   220 */   184,   22,   13,    5,   76,    4,   75,   74,  198,  105,
 /*   230 */    82,  181,  154,  280,  250,  194,  192,  279,  278,  188,
 /*   240 */   220,  291,  197,    2,  187,  283,  270,  193,  191,  135,
 /*   250 */   275,  274,  273,  272,  271,  186,  185,  276,  269,   97,
 /*   260 */   180,  184,  264,   19,  110,  131,  149,    8,   38,  151,
 /*   270 */   104,   82,  146,    6,   10,  159,  184,  184,   22,   13,
 /*   280 */     5,   76,    4,   75,   74,  198,  105,   82,  181,  155,
 /*   290 */   190,  249,  194,  192,   31,  179,   79,  217,  291,  197,
 /*   300 */     2,  259,  283,  258,  193,  191,  135,  275,  274,  273,
 /*   310 */   272,  271,  186,  185,   37,  256,   97,  184,  184,   30,
 /*   320 */    17,  110,  131,  149,    8,   38,  171,   97,   85,  146,
 /*   330 */     6,   10,  242,  184,  184,   22,   13,    5,   76,    4,
 /*   340 */    75,   74,  198,  105,   82,  181,  160,  170,  248,  194,
 /*   350 */   192,  168,  167,  255,  210,  291,  197,    2,  165,  283,
 /*   360 */   254,  193,  191,  135,  275,  274,  273,  272,  271,  186,
 /*   370 */   185,  164,  161,   97,  180,  184,  162,   29,  110,  131,
 /*   380 */   149,    8,   38,  150,  104,   82,  146,    6,   10,  120,
 /*   390 */   184,  253,   22,   13,    5,   76,    4,   75,   74,  138,
 /*   400 */   105,  180,  181,  140,  252,   15,  194,  192,  247,  244,
 /*   410 */   128,  104,  208,  196,    2,  245,  283,    1,  193,  191,
 /*   420 */   135,  275,  274,  273,  272,  271,  186,  185,  243,  108,
 /*   430 */    97,  184,  184,   25,   11,  110,  131,  149,    8,   38,
 /*   440 */   238,   84,   82,  146,    6,   10,  119,  184,  184,   22,
 /*   450 */    13,    5,   76,    4,   75,   74,  267,  105,   82,  181,
 /*   460 */   157,   24,  118,  194,  192,   23,  226,  232,  219,  268,
 /*   470 */   195,    2,  285,  283,   16,  193,  191,  135,  275,  274,
 /*   480 */   273,  272,  271,  186,  185,  139,  213,   97,  184,  184,
 /*   490 */   209,  199,  110,  131,  149,    8,   38,  286,  116,   82,
 /*   500 */   146,    6,   10,  117,  287,  184,   22,   13,    5,   76,
 /*   510 */     4,   75,   74,   59,   58,  115,   66,   67,   65,   57,
 /*   520 */   266,  106,  282,  184,  134,  284,   70,   18,  289,  288,
 /*   530 */    21,   71,  265,  127,  182,  178,  174,  172,  169,  166,
 /*   540 */   163,   78,   77,   64,   63,   69,   68,   66,   67,   65,
 /*   550 */   294,  133,  132,  241,  129,  235,  145,  142,   18,  216,
 /*   560 */   215,   20,   71,  141,  305,  182,  184,  184,  212,  141,
 /*   570 */   211,  137,   59,   58,  184,  148,  126,  125,   57,  266,
 /*   580 */   106,  282,  136,  184,  114,   70,  461,  289,  287,   21,
 /*   590 */   461,  265,  204,  113,  201,  174,  172,  169,  166,  163,
 /*   600 */    78,   77,  461,  184,   69,   68,   66,   67,   65,  461,
 /*   610 */    73,   77,  241,  112,  235,  145,  142,   18,  216,  215,
 /*   620 */    20,   71,  141,  184,  182,  184,  461,  461,  461,  461,
 /*   630 */   461,   59,   58,  109,  461,  111,  461,   57,  266,  106,
 /*   640 */   282,  461,  461,  461,   70,  461,  289,  461,   21,  461,
 /*   650 */   265,  461,  461,  461,  174,  172,  169,  166,  163,   78,
 /*   660 */    77,  304,  207,  302,  206,  205,  200,    9,  461,  461,
 /*   670 */   184,  241,  461,  235,  145,  142,  461,  216,  215,   20,
 /*   680 */   124,  141,   56,   54,   53,   52,   51,   55,   61,   60,
 /*   690 */    62,   64,   63,   69,   68,   66,   67,   65,   27,  184,
 /*   700 */   461,  461,  461,  461,  184,  184,   18,  461,  461,  123,
 /*   710 */    71,   59,   58,  182,  122,  103,  184,   57,  266,  183,
 /*   720 */   461,  461,  184,  184,   70,  461,  102,  461,   21,  184,
 /*   730 */   173,  184,  101,  100,  174,  172,  169,  166,  163,   99,
 /*   740 */   461,   98,   26,  461,  461,  461,  461,  184,  184,  184,
 /*   750 */   461,  461,  461,  461,  184,   59,   58,   83,   96,   95,
 /*   760 */   158,   57,  266,  183,   94,  461,  184,  461,   70,  461,
 /*   770 */   461,  461,   21,  184,  173,  184,   93,  184,  174,  172,
 /*   780 */   169,  166,  163,   92,  461,   91,  184,   90,  184,  461,
 /*   790 */   461,  461,  461,   59,   58,  184,   89,  461,   88,   57,
 /*   800 */   266,  183,  461,  184,  158,   87,   70,  246,  461,  461,
 /*   810 */    21,  461,  265,   86,  262,  461,  174,  172,  169,  166,
 /*   820 */   163,  461,  461,   59,   58,  461,  461,  461,  461,   57,
 /*   830 */   266,  106,  461,  461,  461,  461,   70,  461,  461,  461,
 /*   840 */    21,  461,  265,  461,  461,  461,  174,  172,  169,  166,
 /*   850 */   163,   78,   77,  461,   61,   60,   62,   64,   63,   69,
 /*   860 */    68,   66,   67,   65,  461,  461,  461,  461,  461,  461,
 /*   870 */   461,  461,   18,  461,  461,  461,   71,  263,  461,  182,
 /*   880 */   461,  461,  461,  461,  461,  461,   61,   60,   62,   64,
 /*   890 */    63,   69,   68,   66,   67,   65,  461,  461,  461,  461,
 /*   900 */   461,  461,  461,  461,   18,  260,  461,  461,   71,  461,
 /*   910 */   461,  182,  461,  461,  461,  461,  461,  461,   61,   60,
 /*   920 */    62,   64,   63,   69,   68,   66,   67,   65,  461,  461,
 /*   930 */   461,  461,  461,  461,  461,  461,   18,  461,   59,   58,
 /*   940 */    71,  107,  461,  182,   57,  266,  183,  461,  461,  461,
 /*   950 */   461,   70,  461,  461,  461,   21,  461,  265,  461,  262,
 /*   960 */   461,  174,  172,  169,  166,  163,  461,  461,  461,  461,
 /*   970 */    59,   58,  461,  461,  461,  461,   57,  266,  106,  461,
 /*   980 */   461,  461,  461,   70,  221,  461,  461,   21,  461,  265,
 /*   990 */   461,  461,  461,  174,  172,  169,  166,  163,  357,  357,
 /*  1000 */   357,  357,  357,  357,  357,  357,  357,  357,  461,  461,
 /*  1010 */   461,  461,  461,  461,  461,  461,   19,  461,  461,  461,
 /*  1020 */   357,  461,  461,  357,  461,  461,  461,  461,  461,  461,
 /*  1030 */    61,   60,   62,   64,   63,   69,   68,   66,   67,   65,
 /*  1040 */   461,  461,  461,  461,  461,  461,  461,  461,   18,  461,
 /*  1050 */   461,  461,   71,  461,  461,  182,  461,  461,  461,  461,
 /*  1060 */   461,  461,   61,   60,   62,   64,   63,   69,   68,   66,
 /*  1070 */    67,   65,  461,  461,  461,  461,  461,  461,  461,  461,
 /*  1080 */    18,  461,   59,   58,   50,  461,  461,  153,   57,  266,
 /*  1090 */   183,  461,  461,  461,  461,   70,  461,  461,  461,   21,
 /*  1100 */   461,  265,  461,  461,  461,  174,  172,  169,  166,  163,
 /*  1110 */   461,  461,  461,  461,   59,   58,  461,  461,  461,  461,
 /*  1120 */    57,  266,  106,  403,  403,  461,  461,   70,  461,  461,
 /*  1130 */   461,   21,  461,  265,  461,  402,  402,  174,  172,  169,
 /*  1140 */   166,  163,   60,   62,   64,   63,   69,   68,   66,   67,
 /*  1150 */    65,  461,  461,  461,  461,  461,  461,  461,  461,   18,
 /*  1160 */   461,  461,  461,   71,  461,  461,  182,  461,  461,  461,
 /*  1170 */   403,  403,  403,  403,  403,  403,  403,  403,  403,  403,
 /*  1180 */    49,  461,  402,  402,  402,  402,  402,  402,  402,  402,
 /*  1190 */   402,  402,   62,   64,   63,   69,   68,   66,   67,   65,
 /*  1200 */   461,  461,  461,  461,  461,  461,  461,  461,   18,  461,
 /*  1210 */   461,  461,   71,  461,  461,  182,  461,  461,  461,  461,
 /*  1220 */   461,  461,  461,  461,  461,  231,  229,   48,   47,   46,
 /*  1230 */    45,   44,   43,   42,   41,   40,   39,  230,  228,  184,
 /*  1240 */   461,  461,  461,  461,  461,  461,  461,  231,  229,   97,
 /*  1250 */   461,  461,  461,  461,  110,  131,  461,  461,  461,  230,
 /*  1260 */   228,  184,  461,  461,  461,  144,  143,  461,  461,  461,
 /*  1270 */   461,   97,  461,  461,  461,  461,  110,  131,  461,  461,
 /*  1280 */   461,  461,  461,  461,  461,  461,  461,  227,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    69,   90,   31,  110,  111,  112,   35,   76,   77,   38,
 /*    10 */    99,  100,   81,   82,   83,   84,   27,   86,   27,   88,
 /*    20 */    89,   90,   91,   92,   93,   94,   95,   96,   97,    3,
 /*    30 */     4,  100,   89,   90,    3,    4,  105,  106,  107,  108,
 /*    40 */   109,    2,   27,  100,  113,  114,  115,   26,  105,  106,
 /*    50 */   119,  120,  121,  122,  123,  124,  125,   69,   32,   27,
 /*    60 */    26,  118,    2,   32,   76,   77,   32,   35,    2,   81,
 /*    70 */    82,   83,   84,   29,   86,   36,   88,   89,   90,   91,
 /*    80 */    92,   93,   94,   95,   96,   97,    3,    4,  100,   89,
 /*    90 */    90,    3,    4,  105,  106,  107,  108,  109,   32,   31,
 /*   100 */   100,  113,  114,  115,   26,  105,  106,  119,  120,  121,
 /*   110 */   122,  123,  124,  125,   69,   32,    1,    2,  118,    2,
 /*   120 */    32,   76,   77,   63,    3,    4,   81,   82,   83,   84,
 /*   130 */    26,   86,   26,   88,   89,   90,   91,   92,   93,   94,
 /*   140 */    95,   96,   97,    1,    2,  100,   90,   27,   27,   32,
 /*   150 */   105,  106,  107,  108,  109,   99,  100,  101,  113,  114,
 /*   160 */   115,    1,    2,   90,  119,  120,  121,  122,  123,  124,
 /*   170 */   125,   69,   99,  100,  101,    2,   27,   90,   76,   77,
 /*   180 */    71,   72,   27,   81,   82,   83,   84,  100,   86,  102,
 /*   190 */    88,   89,   90,   91,   92,   93,   94,   95,   96,   97,
 /*   200 */    35,   27,  100,   90,   90,   32,   27,  105,  106,  107,
 /*   210 */   108,  109,   99,  100,  100,  113,  114,  115,  104,   90,
 /*   220 */    90,  119,  120,  121,  122,  123,  124,  125,   69,  100,
 /*   230 */   100,  102,  103,   27,  104,   76,   77,   27,   27,   25,
 /*   240 */    81,   82,   83,   84,   36,   86,   27,   88,   89,   90,
 /*   250 */    91,   92,   93,   94,   95,   96,   97,   36,   27,  100,
 /*   260 */    90,   90,   26,   31,  105,  106,  107,  108,  109,   99,
 /*   270 */   100,  100,  113,  114,  115,  104,   90,   90,  119,  120,
 /*   280 */   121,  122,  123,  124,  125,   69,  100,  100,  102,  103,
 /*   290 */    35,  104,   76,   77,    2,   35,   35,   81,   82,   83,
 /*   300 */    84,   25,   86,   36,   88,   89,   90,   91,   92,   93,
 /*   310 */    94,   95,   96,   97,    2,   32,  100,   90,   90,   31,
 /*   320 */    31,  105,  106,  107,  108,  109,   31,  100,  100,  113,
 /*   330 */   114,  115,  105,   90,   90,  119,  120,  121,  122,  123,
 /*   340 */   124,  125,   69,  100,  100,  102,  103,   39,  104,   76,
 /*   350 */    77,   31,   39,   32,   81,   82,   83,   84,   31,   86,
 /*   360 */    32,   88,   89,   90,   91,   92,   93,   94,   95,   96,
 /*   370 */    97,   39,   39,  100,   90,   90,   31,    4,  105,  106,
 /*   380 */   107,  108,  109,   99,  100,  100,  113,  114,  115,  104,
 /*   390 */    90,   32,  119,  120,  121,  122,  123,  124,  125,   69,
 /*   400 */   100,   90,  102,  103,   32,   31,   76,   77,   32,   32,
 /*   410 */    99,  100,   82,   83,   84,   36,   86,   87,   88,   89,
 /*   420 */    90,   91,   92,   93,   94,   95,   96,   97,   32,   26,
 /*   430 */   100,   90,   90,   31,    2,  105,  106,  107,  108,  109,
 /*   440 */    58,  100,  100,  113,  114,  115,  104,   90,   90,  119,
 /*   450 */   120,  121,  122,  123,  124,  125,   69,  100,  100,  102,
 /*   460 */   103,   31,  104,   76,   77,   31,   27,   31,   31,   82,
 /*   470 */    83,   84,   85,   86,   31,   88,   89,   90,   91,   92,
 /*   480 */    93,   94,   95,   96,   97,   32,   27,  100,   90,   90,
 /*   490 */    34,    2,  105,  106,  107,  108,  109,   85,  100,  100,
 /*   500 */   113,  114,  115,  104,   34,   90,  119,  120,  121,  122,
 /*   510 */   123,  124,  125,   18,   19,  100,   20,   21,   22,   24,
 /*   520 */    25,   26,   27,   90,   98,   85,   31,   31,   33,   34,
 /*   530 */    35,   35,   37,  100,   38,   25,   41,   42,   43,   44,
 /*   540 */    45,   46,   47,   16,   17,   18,   19,   20,   21,   22,
 /*   550 */    26,   80,   80,   58,   80,   60,   61,   62,   31,   64,
 /*   560 */    65,   66,   35,   68,    0,   38,   90,   90,  124,   68,
 /*   570 */   124,   80,   18,   19,   90,   59,  100,  100,   24,   25,
 /*   580 */    26,   27,   80,   90,  100,   31,  126,   33,   34,   35,
 /*   590 */   126,   37,   28,  100,   30,   41,   42,   43,   44,   45,
 /*   600 */    46,   47,  126,   90,   18,   19,   20,   21,   22,  126,
 /*   610 */    46,   47,   58,  100,   60,   61,   62,   31,   64,   65,
 /*   620 */    66,   35,   68,   90,   38,   90,  126,  126,  126,  126,
 /*   630 */   126,   18,   19,  100,  126,  100,  126,   24,   25,   26,
 /*   640 */    27,  126,  126,  126,   31,  126,   33,  126,   35,  126,
 /*   650 */    37,  126,  126,  126,   41,   42,   43,   44,   45,   46,
 /*   660 */    47,   73,   74,   75,   76,   77,   78,   79,  126,  126,
 /*   670 */    90,   58,  126,   60,   61,   62,  126,   64,   65,   66,
 /*   680 */   100,   68,    7,    8,    9,   10,   11,   12,   13,   14,
 /*   690 */    15,   16,   17,   18,   19,   20,   21,   22,    5,   90,
 /*   700 */   126,  126,  126,  126,   90,   90,   31,  126,  126,  100,
 /*   710 */    35,   18,   19,   38,  100,  100,   90,   24,   25,   26,
 /*   720 */   126,  126,   90,   90,   31,  126,  100,  126,   35,   90,
 /*   730 */    37,   90,  100,  100,   41,   42,   43,   44,   45,  100,
 /*   740 */   126,  100,    5,  126,  126,  126,  126,   90,   90,   90,
 /*   750 */   126,  126,  126,  126,   90,   18,   19,  100,  100,  100,
 /*   760 */    67,   24,   25,   26,  100,  126,   90,  126,   31,  126,
 /*   770 */   126,  126,   35,   90,   37,   90,  100,   90,   41,   42,
 /*   780 */    43,   44,   45,  100,  126,  100,   90,  100,   90,  126,
 /*   790 */   126,  126,  126,   18,   19,   90,  100,  126,  100,   24,
 /*   800 */    25,   26,  126,   90,   67,  100,   31,   32,  126,  126,
 /*   810 */    35,  126,   37,  100,   39,  126,   41,   42,   43,   44,
 /*   820 */    45,  126,  126,   18,   19,  126,  126,  126,  126,   24,
 /*   830 */    25,   26,  126,  126,  126,  126,   31,  126,  126,  126,
 /*   840 */    35,  126,   37,  126,  126,  126,   41,   42,   43,   44,
 /*   850 */    45,   46,   47,  126,   13,   14,   15,   16,   17,   18,
 /*   860 */    19,   20,   21,   22,  126,  126,  126,  126,  126,  126,
 /*   870 */   126,  126,   31,  126,  126,  126,   35,   36,  126,   38,
 /*   880 */   126,  126,  126,  126,  126,  126,   13,   14,   15,   16,
 /*   890 */    17,   18,   19,   20,   21,   22,  126,  126,  126,  126,
 /*   900 */   126,  126,  126,  126,   31,   32,  126,  126,   35,  126,
 /*   910 */   126,   38,  126,  126,  126,  126,  126,  126,   13,   14,
 /*   920 */    15,   16,   17,   18,   19,   20,   21,   22,  126,  126,
 /*   930 */   126,  126,  126,  126,  126,  126,   31,  126,   18,   19,
 /*   940 */    35,   36,  126,   38,   24,   25,   26,  126,  126,  126,
 /*   950 */   126,   31,  126,  126,  126,   35,  126,   37,  126,   39,
 /*   960 */   126,   41,   42,   43,   44,   45,  126,  126,  126,  126,
 /*   970 */    18,   19,  126,  126,  126,  126,   24,   25,   26,  126,
 /*   980 */   126,  126,  126,   31,   32,  126,  126,   35,  126,   37,
 /*   990 */   126,  126,  126,   41,   42,   43,   44,   45,   13,   14,
 /*  1000 */    15,   16,   17,   18,   19,   20,   21,   22,  126,  126,
 /*  1010 */   126,  126,  126,  126,  126,  126,   31,  126,  126,  126,
 /*  1020 */    35,  126,  126,   38,  126,  126,  126,  126,  126,  126,
 /*  1030 */    13,   14,   15,   16,   17,   18,   19,   20,   21,   22,
 /*  1040 */   126,  126,  126,  126,  126,  126,  126,  126,   31,  126,
 /*  1050 */   126,  126,   35,  126,  126,   38,  126,  126,  126,  126,
 /*  1060 */   126,  126,   13,   14,   15,   16,   17,   18,   19,   20,
 /*  1070 */    21,   22,  126,  126,  126,  126,  126,  126,  126,  126,
 /*  1080 */    31,  126,   18,   19,   35,  126,  126,   38,   24,   25,
 /*  1090 */    26,  126,  126,  126,  126,   31,  126,  126,  126,   35,
 /*  1100 */   126,   37,  126,  126,  126,   41,   42,   43,   44,   45,
 /*  1110 */   126,  126,  126,  126,   18,   19,  126,  126,  126,  126,
 /*  1120 */    24,   25,   26,    1,    2,  126,  126,   31,  126,  126,
 /*  1130 */   126,   35,  126,   37,  126,    1,    2,   41,   42,   43,
 /*  1140 */    44,   45,   14,   15,   16,   17,   18,   19,   20,   21,
 /*  1150 */    22,  126,  126,  126,  126,  126,  126,  126,  126,   31,
 /*  1160 */   126,  126,  126,   35,  126,  126,   38,  126,  126,  126,
 /*  1170 */    48,   49,   50,   51,   52,   53,   54,   55,   56,   57,
 /*  1180 */     1,  126,   48,   49,   50,   51,   52,   53,   54,   55,
 /*  1190 */    56,   57,   15,   16,   17,   18,   19,   20,   21,   22,
 /*  1200 */   126,  126,  126,  126,  126,  126,  126,  126,   31,  126,
 /*  1210 */   126,  126,   35,  126,  126,   38,  126,  126,  126,  126,
 /*  1220 */   126,  126,  126,  126,  126,   76,   77,   48,   49,   50,
 /*  1230 */    51,   52,   53,   54,   55,   56,   57,   88,   89,   90,
 /*  1240 */   126,  126,  126,  126,  126,  126,  126,   76,   77,  100,
 /*  1250 */   126,  126,  126,  126,  105,  106,  126,  126,  126,   88,
 /*  1260 */    89,   90,  126,  126,  126,  116,  117,  126,  126,  126,
 /*  1270 */   126,  100,  126,  126,  126,  126,  105,  106,  126,  126,
 /*  1280 */   126,  126,  126,  126,  126,  126,  126,  116,
};
#define YY_SHIFT_USE_DFLT (-30)
#define YY_SHIFT_COUNT (207)
#define YY_SHIFT_MIN   (-29)
#define YY_SHIFT_MAX   (1179)
static const short yy_shift_ofst[] = {
 /*     0 */   -30,  554,  495,  613,  613,  613,  613,  613,  613,  613,
 /*    10 */   805,  805,  564,  952, 1096,  775,  920,  920,  920,  920,
 /*    20 */  1064, 1064,  693,  693,  693,  693,  737,  737,  693,  693,
 /*    30 */   693,  920, 1064, 1064, 1096, 1064, 1064, 1064,  516, 1064,
 /*    40 */  1064, 1064, 1064, 1064, 1064, 1064, 1064, 1064, 1064, 1064,
 /*    50 */  1064, 1064, 1064, 1064, 1064, 1064, 1064, 1064, 1064, 1064,
 /*    60 */  1064, 1064, 1064, 1064, 1064, 1064, 1064, 1064, 1064, 1064,
 /*    70 */  1064, 1064,   34,  524,  501,  501,  524,  524,  524,  510,
 /*    80 */   470,  470,  675,  905,  873,  841, 1017, 1017, 1017, 1017,
 /*    90 */  1017, 1017, 1017, 1017, 1017, 1017, 1017, 1049, 1017, 1017,
 /*   100 */  1017, 1017, 1017, 1017, 1017, 1017,  985, 1134, 1122, 1128,
 /*   110 */  1179, 1177,  527,  586,  586,  496,  496,  121,   88,   83,
 /*   120 */    31,   26,  -29,  -29,  -29,  -29,  -29,  -29,  173,   60,
 /*   130 */   117,  160,  142,  115,   39,   32,   66,  489,  456,  459,
 /*   140 */   453,  443,  437,  439,  432,  436,  434,  430,  382,  402,
 /*   150 */   312,  312,  312,  403,  396,  377,  379,  376,  374,  373,
 /*   160 */   372,  359,  333,  345,  328,  332,  327,  321,  313,  320,
 /*   170 */   283,  308,  295,  289,  288,  312,  267,  276,  208,  261,
 /*   180 */   260,  292,  236,  232,  255,  231,  219,  221,  208,  214,
 /*   190 */   165,  211,  210,  206,  179,  174,  155,  149,  120,  106,
 /*   200 */    68,  104,   78,   44,   21,   15,   -9,  -11,
};
#define YY_REDUCE_USE_DFLT (-108)
#define YY_REDUCE_COUNT (81)
#define YY_REDUCE_MIN   (-107)
#define YY_REDUCE_MAX   (1171)
static const short yy_reduce_ofst[] = {
 /*     0 */   109,  387,  330,  273,  216,  159,  102,   45,  -12,  -69,
 /*    10 */  1149, 1171,  588,    0,  -57,  357,  300,  243,  186,  129,
 /*    20 */    73,   56,  399,  358,  342,  285,  244,  187,  171,  130,
 /*    30 */   114,   87,  311,  284,  227,  170,  113,  -89, -107,  713,
 /*    40 */   705,  698,  696,  687,  685,  683,  676,  664,  659,  658,
 /*    50 */   657,  641,  639,  633,  632,  626,  615,  614,  609,  580,
 /*    60 */   535,  533,  513,  493,  484,  477,  476,  433,  415,  398,
 /*    70 */   341,  228,  502,  491,  446,  444,  474,  472,  471,  426,
 /*    80 */   440,  412,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   306,  459,  459,  459,  459,  459,  459,  459,  459,  459,
 /*    10 */   437,  459,  459,  459,  459,  459,  363,  363,  363,  363,
 /*    20 */   353,  353,  459,  459,  459,  459,  459,  459,  459,  459,
 /*    30 */   459,  459,  459,  459,  459,  459,  459,  459,  425,  459,
 /*    40 */   459,  459,  459,  459,  459,  459,  459,  459,  459,  459,
 /*    50 */   459,  459,  459,  459,  459,  459,  459,  459,  459,  459,
 /*    60 */   459,  459,  459,  459,  459,  459,  459,  459,  459,  459,
 /*    70 */   459,  459,  459,  459,  458,  457,  459,  459,  459,  459,
 /*    80 */   459,  459,  459,  459,  459,  459,  417,  416,  415,  414,
 /*    90 */   413,  412,  411,  410,  409,  408,  406,  459,  393,  392,
 /*   100 */   391,  390,  389,  388,  351,  360,  401,  359,  358,  383,
 /*   110 */   404,  384,  382,  381,  380,  376,  375,  459,  459,  459,
 /*   120 */   459,  459,  387,  386,  385,  379,  378,  377,  459,  459,
 /*   130 */   459,  459,  459,  398,  459,  367,  459,  398,  459,  459,
 /*   140 */   459,  459,  459,  459,  436,  459,  459,  459,  424,  459,
 /*   150 */   407,  400,  399,  459,  459,  459,  459,  459,  459,  395,
 /*   160 */   459,  459,  459,  459,  459,  459,  459,  459,  459,  459,
 /*   170 */   459,  459,  459,  356,  459,  354,  459,  459,  345,  459,
 /*   180 */   367,  364,  459,  357,  367,  459,  459,  459,  459,  459,
 /*   190 */   459,  459,  459,  459,  459,  459,  459,  459,  459,  459,
 /*   200 */   459,  459,  459,  313,  459,  459,  459,  459,  342,  327,
 /*   210 */   426,  456,  455,  454,  450,  449,  448,  447,  446,  445,
 /*   220 */   444,  443,  442,  439,  438,  441,  440,  435,  434,  433,
 /*   230 */   432,  431,  430,  429,  428,  427,  423,  422,  421,  420,
 /*   240 */   419,  418,  405,  365,  366,  369,  453,  451,  397,  396,
 /*   250 */   394,  370,  452,  374,  373,  372,  371,  352,  349,  346,
 /*   260 */   368,  362,  361,  359,  358,  356,  355,  344,  343,  341,
 /*   270 */   340,  339,  338,  337,  336,  335,  350,  334,  333,  332,
 /*   280 */   331,  330,  329,  328,  326,  325,  324,  322,  323,  321,
 /*   290 */   320,  319,  318,  317,  347,  316,  348,  315,  314,  312,
 /*   300 */   311,  310,  309,  308,  307,
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
  "vdef_stmt",     "cdef_stmt",     "function_start",  "function_header",
  "nameList_nonEmpty",  "stmt",          "bodyStmt",      "return_stmt", 
  "lbracket",      "rbracket",      "blockStmt",     "bodyStmtList",
  "vdefAssign_stmt",  "assign_stmt",   "funcexpr",      "actionStmt",  
  "if_stmt",       "while_stmt",    "for_stmt",      "foreach_stmt",
  "continue_stmt",  "break_stmt",    "numList_nonEmpty",  "exprList_nonEmpty",
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
 /*   5 */ "chunk ::= vdef_stmt SEMICOLON",
 /*   6 */ "chunk ::= cdef_stmt SEMICOLON",
 /*   7 */ "import_chunk ::= IMPORT NAME AS NAME",
 /*   8 */ "import_chunk ::= IMPORT NAME",
 /*   9 */ "function_start ::= FUNCTION NAME",
 /*  10 */ "function_header ::= function_start LPAREN nameList_nonEmpty RPAREN",
 /*  11 */ "function_header ::= function_start LPAREN RPAREN",
 /*  12 */ "fdef_chunk ::= function_header stmt",
 /*  13 */ "stmt ::= error SEMICOLON",
 /*  14 */ "stmt ::= bodyStmt",
 /*  15 */ "stmt ::= return_stmt SEMICOLON",
 /*  16 */ "lbracket ::= LBRACKET",
 /*  17 */ "rbracket ::= RBRACKET",
 /*  18 */ "blockStmt ::= lbracket RBRACKET",
 /*  19 */ "blockStmt ::= lbracket return_stmt SEMICOLON rbracket",
 /*  20 */ "blockStmt ::= lbracket bodyStmtList rbracket",
 /*  21 */ "blockStmt ::= lbracket bodyStmtList return_stmt SEMICOLON rbracket",
 /*  22 */ "blockStmt ::= lbracket error RBRACKET",
 /*  23 */ "bodyStmt ::= blockStmt",
 /*  24 */ "bodyStmt ::= SEMICOLON",
 /*  25 */ "bodyStmt ::= vdef_stmt SEMICOLON",
 /*  26 */ "bodyStmt ::= vdefAssign_stmt SEMICOLON",
 /*  27 */ "bodyStmt ::= cdef_stmt SEMICOLON",
 /*  28 */ "bodyStmt ::= assign_stmt SEMICOLON",
 /*  29 */ "bodyStmt ::= funcexpr SEMICOLON",
 /*  30 */ "bodyStmt ::= actionStmt",
 /*  31 */ "bodyStmt ::= if_stmt",
 /*  32 */ "bodyStmt ::= while_stmt",
 /*  33 */ "bodyStmt ::= for_stmt",
 /*  34 */ "bodyStmt ::= foreach_stmt",
 /*  35 */ "bodyStmt ::= continue_stmt SEMICOLON",
 /*  36 */ "bodyStmt ::= break_stmt SEMICOLON",
 /*  37 */ "bodyStmtList ::= bodyStmt",
 /*  38 */ "bodyStmtList ::= bodyStmtList bodyStmt",
 /*  39 */ "bodyStmtList ::= bodyStmtList error",
 /*  40 */ "numList_nonEmpty ::= NUMBER",
 /*  41 */ "numList_nonEmpty ::= numList_nonEmpty COMMA NUMBER",
 /*  42 */ "nameList_nonEmpty ::= NAME",
 /*  43 */ "nameList_nonEmpty ::= nameList_nonEmpty COMMA NAME",
 /*  44 */ "exprList_nonEmpty ::= funcexpr LSQBRACKET LSQBRACKET numList_nonEmpty RSQBRACKET RSQBRACKET",
 /*  45 */ "expr ::= funcexpr LSQBRACKET LSQBRACKET NUMBER RSQBRACKET RSQBRACKET",
 /*  46 */ "exprList_nonEmpty ::= expr",
 /*  47 */ "exprList_nonEmpty ::= exprList_nonEmpty COMMA exprList_nonEmpty",
 /*  48 */ "exprList ::=",
 /*  49 */ "exprList ::= exprList_nonEmpty",
 /*  50 */ "expr ::= NUMBER",
 /*  51 */ "expr ::= KILLS",
 /*  52 */ "expr ::= NAME",
 /*  53 */ "expr ::= expr PERIOD NAME",
 /*  54 */ "expr ::= expr LSQBRACKET expr RSQBRACKET",
 /*  55 */ "fArgs_nonEmpty ::= expr",
 /*  56 */ "fArgs_nonEmpty ::= STRING",
 /*  57 */ "fArgs_nonEmpty ::= fArgs_nonEmpty COMMA fArgs_nonEmpty",
 /*  58 */ "fArgs ::=",
 /*  59 */ "fArgs ::= fArgs_nonEmpty",
 /*  60 */ "funcexpr ::= NAME LPAREN fArgs RPAREN",
 /*  61 */ "funcexpr ::= expr LPAREN fArgs RPAREN",
 /*  62 */ "expr ::= funcexpr",
 /*  63 */ "expr ::= LPAREN expr RPAREN",
 /*  64 */ "expr ::= LSQBRACKET exprList RSQBRACKET",
 /*  65 */ "expr ::= L2V LPAREN lexpr RPAREN",
 /*  66 */ "expr ::= MAPSTRING LPAREN STRING RPAREN",
 /*  67 */ "expr ::= UNIT LPAREN STRING RPAREN",
 /*  68 */ "expr ::= SWITCH LPAREN STRING RPAREN",
 /*  69 */ "expr ::= LOCATION LPAREN STRING RPAREN",
 /*  70 */ "expr ::= expr PLUS expr",
 /*  71 */ "expr ::= expr MINUS expr",
 /*  72 */ "expr ::= expr MULTIPLY expr",
 /*  73 */ "expr ::= expr DIVIDE expr",
 /*  74 */ "expr ::= expr MOD expr",
 /*  75 */ "expr ::= expr LSHIFT expr",
 /*  76 */ "expr ::= expr RSHIFT expr",
 /*  77 */ "expr ::= expr BITAND expr",
 /*  78 */ "expr ::= expr BITOR expr",
 /*  79 */ "expr ::= expr BITXOR expr",
 /*  80 */ "expr ::= PLUS expr",
 /*  81 */ "expr ::= MINUS expr",
 /*  82 */ "expr ::= BITNOT expr",
 /*  83 */ "lexpr ::= expr EQ expr",
 /*  84 */ "lexpr ::= expr NE expr",
 /*  85 */ "lexpr ::= expr LE expr",
 /*  86 */ "lexpr ::= expr LT expr",
 /*  87 */ "lexpr ::= expr GE expr",
 /*  88 */ "lexpr ::= expr GT expr",
 /*  89 */ "lexpr ::= lexpr LAND lexpr",
 /*  90 */ "lexpr ::= lexpr LOR lexpr",
 /*  91 */ "lexpr ::= LNOT lexpr",
 /*  92 */ "lexpr ::= LNOT LNOT lexpr",
 /*  93 */ "vdef_stmt ::= VAR nameList_nonEmpty",
 /*  94 */ "vdefAssign_stmt ::= VAR nameList_nonEmpty ASSIGN exprList_nonEmpty",
 /*  95 */ "cdef_stmt ::= CONST nameList_nonEmpty ASSIGN exprList_nonEmpty",
 /*  96 */ "lvalue ::= NAME",
 /*  97 */ "lvalue ::= expr LSQBRACKET expr RSQBRACKET",
 /*  98 */ "lvalue ::= expr PERIOD NAME",
 /*  99 */ "lvalueList_nonEmpty ::= lvalue",
 /* 100 */ "lvalueList_nonEmpty ::= lvalueList_nonEmpty COMMA lvalue",
 /* 101 */ "assign_stmt ::= lvalue ASSIGN expr",
 /* 102 */ "assign_stmt ::= lvalueList_nonEmpty ASSIGN exprList_nonEmpty",
 /* 103 */ "assign_stmt ::= lvalue IADD expr",
 /* 104 */ "assign_stmt ::= lvalue ISUB expr",
 /* 105 */ "assign_stmt ::= lvalue IMUL expr",
 /* 106 */ "assign_stmt ::= lvalue IDIV expr",
 /* 107 */ "assign_stmt ::= lvalue IMOD expr",
 /* 108 */ "assign_stmt ::= lvalue ILSH expr",
 /* 109 */ "assign_stmt ::= lvalue IRSH expr",
 /* 110 */ "assign_stmt ::= lvalue IBND expr",
 /* 111 */ "assign_stmt ::= lvalue IBOR expr",
 /* 112 */ "assign_stmt ::= lvalue IBXR expr",
 /* 113 */ "if_start ::= IF",
 /* 114 */ "if_header ::= if_start LPAREN lexpr RPAREN",
 /* 115 */ "if_block ::= if_header stmt",
 /* 116 */ "elif_start ::= ELSE IF",
 /* 117 */ "elif_header ::= elif_start LPAREN lexpr RPAREN",
 /* 118 */ "if_block ::= if_block elif_header stmt",
 /* 119 */ "else_header ::= ELSE",
 /* 120 */ "if_stmt ::= if_block",
 /* 121 */ "if_stmt ::= if_block else_header stmt",
 /* 122 */ "while_start ::= WHILE",
 /* 123 */ "while_header ::= while_start LPAREN lexpr RPAREN",
 /* 124 */ "while_stmt ::= while_header stmt",
 /* 125 */ "for_opener ::= FOR LPAREN",
 /* 126 */ "for_init_stmt_nonEmpty ::= vdef_stmt",
 /* 127 */ "for_init_stmt_nonEmpty ::= vdefAssign_stmt",
 /* 128 */ "for_init_stmt_nonEmpty ::= cdef_stmt",
 /* 129 */ "for_init_stmt_nonEmpty ::= assign_stmt",
 /* 130 */ "for_init_stmt_nonEmpty ::= for_init_stmt_nonEmpty COMMA for_init_stmt_nonEmpty",
 /* 131 */ "for_init_stmt ::= for_init_stmt_nonEmpty",
 /* 132 */ "for_init_stmt ::=",
 /* 133 */ "for_action_stmt_nonEmpty ::= assign_stmt",
 /* 134 */ "for_action_stmt_nonEmpty ::= for_action_stmt_nonEmpty COMMA for_action_stmt_nonEmpty",
 /* 135 */ "for_header1 ::= for_opener for_init_stmt SEMICOLON",
 /* 136 */ "for_header2 ::= for_header1 lexpr SEMICOLON",
 /* 137 */ "for_header ::= for_header2 for_action_stmt_nonEmpty RPAREN",
 /* 138 */ "for_header ::= for_header2 RPAREN",
 /* 139 */ "for_stmt ::= for_header stmt",
 /* 140 */ "foreach_opener ::= FOREACH LPAREN",
 /* 141 */ "foreach_header ::= foreach_opener nameList_nonEmpty COLON exprList_nonEmpty RPAREN",
 /* 142 */ "foreach_stmt ::= foreach_header stmt",
 /* 143 */ "continue_stmt ::= CONTINUE",
 /* 144 */ "break_stmt ::= BREAK",
 /* 145 */ "return_stmt ::= RETURN exprList",
 /* 146 */ "lexpr ::= CONDITIONNAME LPAREN fArgs RPAREN",
 /* 147 */ "lexpr ::= KILLS LPAREN fArgs RPAREN",
 /* 148 */ "lexpr ::= CONDITIONNAME LPAREN RPAREN",
 /* 149 */ "action ::= ACTIONNAME LPAREN fArgs RPAREN SEMICOLON",
 /* 150 */ "actions ::= action action",
 /* 151 */ "actions ::= actions action",
 /* 152 */ "actionStmt ::= action",
 /* 153 */ "actionStmt ::= actions",
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
#line 31 "parser\\epparser.lemon"
 delete (yypminor->yy0); 
#line 871 "parser\\epparser.c"
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
  { 74, 4 },
  { 74, 2 },
  { 78, 2 },
  { 79, 4 },
  { 79, 3 },
  { 75, 2 },
  { 81, 2 },
  { 81, 1 },
  { 81, 2 },
  { 84, 1 },
  { 85, 1 },
  { 86, 2 },
  { 86, 4 },
  { 86, 3 },
  { 86, 5 },
  { 86, 3 },
  { 82, 1 },
  { 82, 1 },
  { 82, 2 },
  { 82, 2 },
  { 82, 2 },
  { 82, 2 },
  { 82, 2 },
  { 82, 1 },
  { 82, 1 },
  { 82, 1 },
  { 82, 1 },
  { 82, 1 },
  { 82, 2 },
  { 82, 2 },
  { 87, 1 },
  { 87, 2 },
  { 87, 2 },
  { 98, 1 },
  { 98, 3 },
  { 80, 1 },
  { 80, 3 },
  { 99, 6 },
  { 100, 6 },
  { 99, 1 },
  { 99, 3 },
  { 101, 0 },
  { 101, 1 },
  { 100, 1 },
  { 100, 1 },
  { 100, 1 },
  { 100, 3 },
  { 100, 4 },
  { 102, 1 },
  { 102, 1 },
  { 102, 3 },
  { 103, 0 },
  { 103, 1 },
  { 90, 4 },
  { 90, 4 },
  { 100, 1 },
  { 100, 3 },
  { 100, 3 },
  { 100, 4 },
  { 100, 4 },
  { 100, 4 },
  { 100, 4 },
  { 100, 4 },
  { 100, 3 },
  { 100, 3 },
  { 100, 3 },
  { 100, 3 },
  { 100, 3 },
  { 100, 3 },
  { 100, 3 },
  { 100, 3 },
  { 100, 3 },
  { 100, 3 },
  { 100, 2 },
  { 100, 2 },
  { 100, 2 },
  { 104, 3 },
  { 104, 3 },
  { 104, 3 },
  { 104, 3 },
  { 104, 3 },
  { 104, 3 },
  { 104, 3 },
  { 104, 3 },
  { 104, 2 },
  { 104, 3 },
  { 76, 2 },
  { 88, 4 },
  { 77, 4 },
  { 105, 1 },
  { 105, 4 },
  { 105, 3 },
  { 106, 1 },
  { 106, 3 },
  { 89, 3 },
  { 89, 3 },
  { 89, 3 },
  { 89, 3 },
  { 89, 3 },
  { 89, 3 },
  { 89, 3 },
  { 89, 3 },
  { 89, 3 },
  { 89, 3 },
  { 89, 3 },
  { 89, 3 },
  { 107, 1 },
  { 108, 4 },
  { 109, 2 },
  { 110, 2 },
  { 111, 4 },
  { 109, 3 },
  { 112, 1 },
  { 92, 1 },
  { 92, 3 },
  { 113, 1 },
  { 114, 4 },
  { 93, 2 },
  { 115, 2 },
  { 116, 1 },
  { 116, 1 },
  { 116, 1 },
  { 116, 1 },
  { 116, 3 },
  { 117, 1 },
  { 117, 0 },
  { 118, 1 },
  { 118, 3 },
  { 119, 3 },
  { 120, 3 },
  { 121, 3 },
  { 121, 2 },
  { 94, 2 },
  { 122, 2 },
  { 123, 5 },
  { 95, 2 },
  { 96, 1 },
  { 97, 1 },
  { 83, 2 },
  { 104, 4 },
  { 104, 4 },
  { 104, 3 },
  { 124, 5 },
  { 125, 2 },
  { 125, 2 },
  { 91, 1 },
  { 91, 1 },
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
      case 7: /* import_chunk ::= IMPORT NAME AS NAME */
#line 67 "parser\\epparser.lemon"
{
    if(!ps->closure.defModule(yymsp[0].minor.yy0->data)) {
        throw_error(6754, "Importing already-declared module " + yymsp[0].minor.yy0->data);
    }
    ps->gen << "import " << yymsp[-2].minor.yy0->data << " as " << yymsp[0].minor.yy0->data << std::endl;
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 1326 "parser\\epparser.c"
        break;
      case 8: /* import_chunk ::= IMPORT NAME */
#line 75 "parser\\epparser.lemon"
{
    if(!ps->closure.defModule(yymsp[0].minor.yy0->data)) {
        throw_error(6754, "Importing already-declared module " + yymsp[0].minor.yy0->data);
    }
    ps->gen << "import " << yymsp[0].minor.yy0->data << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1337 "parser\\epparser.c"
        break;
      case 9: /* function_start ::= FUNCTION NAME */
#line 84 "parser\\epparser.lemon"
{
    // Preprocess yymsp[0].minor.yy0
    funcNamePreprocess(yymsp[0].minor.yy0->data);
    if(!ps->closure.defFunction(yymsp[0].minor.yy0->data)) {
        throw_error(4495, "Duplicate function " + yymsp[0].minor.yy0->data);
    }
    ps->closure.pushScope();
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1350 "parser\\epparser.c"
        break;
      case 10: /* function_header ::= function_start LPAREN nameList_nonEmpty RPAREN */
#line 94 "parser\\epparser.lemon"
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
#line 1369 "parser\\epparser.c"
        break;
      case 11: /* function_header ::= function_start LPAREN RPAREN */
#line 110 "parser\\epparser.lemon"
{
    ps->gen << "@EUDFunc" << std::endl;
    ps->gen << "def " << yymsp[-2].minor.yy0->data << "():" << std::endl;
    ps->gen.indent();
    tmpIndex = 1;
    delete yymsp[-2].minor.yy0;
}
#line 1380 "parser\\epparser.c"
        break;
      case 12: /* fdef_chunk ::= function_header stmt */
      case 142: /* foreach_stmt ::= foreach_header stmt */ yytestcase(yyruleno==142);
#line 118 "parser\\epparser.lemon"
{
    ps->gen.unindent(true);
    ps->closure.popScope();
}
#line 1389 "parser\\epparser.c"
        break;
      case 13: /* stmt ::= error SEMICOLON */
#line 125 "parser\\epparser.lemon"
{ throw_error(6974, "Error while parsing statement"); }
#line 1394 "parser\\epparser.c"
        break;
      case 16: /* lbracket ::= LBRACKET */
#line 131 "parser\\epparser.lemon"
{ ps->closure.pushScope(); }
#line 1399 "parser\\epparser.c"
        break;
      case 17: /* rbracket ::= RBRACKET */
#line 132 "parser\\epparser.lemon"
{ ps->closure.popScope(); }
#line 1404 "parser\\epparser.c"
        break;
      case 18: /* blockStmt ::= lbracket RBRACKET */
#line 134 "parser\\epparser.lemon"
{
    ps->gen << "pass" << std::endl;
    ps->closure.popScope();
}
#line 1412 "parser\\epparser.c"
        break;
      case 22: /* blockStmt ::= lbracket error RBRACKET */
#line 141 "parser\\epparser.lemon"
{
    throw_error(6298, "Block not terminated properly.");
    ps->closure.popScope();
}
#line 1420 "parser\\epparser.c"
        break;
      case 29: /* bodyStmt ::= funcexpr SEMICOLON */
#line 152 "parser\\epparser.lemon"
{ ps->gen << yymsp[-1].minor.yy0->data << std::endl; }
#line 1425 "parser\\epparser.c"
        break;
      case 39: /* bodyStmtList ::= bodyStmtList error */
#line 164 "parser\\epparser.lemon"
{
    throw_error(8510, "Incomplete statement");
}
#line 1432 "parser\\epparser.c"
        break;
      case 40: /* numList_nonEmpty ::= NUMBER */
      case 42: /* nameList_nonEmpty ::= NAME */ yytestcase(yyruleno==42);
      case 46: /* exprList_nonEmpty ::= expr */ yytestcase(yyruleno==46);
      case 49: /* exprList ::= exprList_nonEmpty */ yytestcase(yyruleno==49);
      case 50: /* expr ::= NUMBER */ yytestcase(yyruleno==50);
      case 55: /* fArgs_nonEmpty ::= expr */ yytestcase(yyruleno==55);
      case 56: /* fArgs_nonEmpty ::= STRING */ yytestcase(yyruleno==56);
      case 59: /* fArgs ::= fArgs_nonEmpty */ yytestcase(yyruleno==59);
      case 62: /* expr ::= funcexpr */ yytestcase(yyruleno==62);
      case 92: /* lexpr ::= LNOT LNOT lexpr */ yytestcase(yyruleno==92);
      case 99: /* lvalueList_nonEmpty ::= lvalue */ yytestcase(yyruleno==99);
#line 170 "parser\\epparser.lemon"
{ yygotominor.yy0 = yymsp[0].minor.yy0; }
#line 1447 "parser\\epparser.c"
        break;
      case 41: /* numList_nonEmpty ::= numList_nonEmpty COMMA NUMBER */
      case 43: /* nameList_nonEmpty ::= nameList_nonEmpty COMMA NAME */ yytestcase(yyruleno==43);
      case 100: /* lvalueList_nonEmpty ::= lvalueList_nonEmpty COMMA lvalue */ yytestcase(yyruleno==100);
#line 171 "parser\\epparser.lemon"
{ yygotominor.yy0 = commaConcat(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1454 "parser\\epparser.c"
        break;
      case 44: /* exprList_nonEmpty ::= funcexpr LSQBRACKET LSQBRACKET numList_nonEmpty RSQBRACKET RSQBRACKET */
#line 175 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "_SRET(" + yymsp[-5].minor.yy0->data + ", [" + yymsp[-2].minor.yy0->data + "])";
    delete yymsp[-5].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1463 "parser\\epparser.c"
        break;
      case 45: /* expr ::= funcexpr LSQBRACKET LSQBRACKET NUMBER RSQBRACKET RSQBRACKET */
#line 182 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-5].minor.yy0->data + "[" + yymsp[-2].minor.yy0->data + "]";
    delete yymsp[-5].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1472 "parser\\epparser.c"
        break;
      case 47: /* exprList_nonEmpty ::= exprList_nonEmpty COMMA exprList_nonEmpty */
#line 190 "parser\\epparser.lemon"
{ yygotominor.yy0 = new Token((yymsp[-2].minor.yy0->data) + ", " + (yymsp[0].minor.yy0->data), yymsp[0].minor.yy0); delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1477 "parser\\epparser.c"
        break;
      case 48: /* exprList ::= */
      case 58: /* fArgs ::= */ yytestcase(yyruleno==58);
#line 192 "parser\\epparser.lemon"
{ yygotominor.yy0 = genEmpty(); }
#line 1483 "parser\\epparser.c"
        break;
      case 51: /* expr ::= KILLS */
#line 197 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = "4";
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1491 "parser\\epparser.c"
        break;
      case 52: /* expr ::= NAME */
#line 202 "parser\\epparser.lemon"
{
    checkIsRValue(yymsp[0].minor.yy0->data);
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1499 "parser\\epparser.c"
        break;
      case 53: /* expr ::= expr PERIOD NAME */
#line 207 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + "." + yymsp[0].minor.yy0->data;
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1508 "parser\\epparser.c"
        break;
      case 54: /* expr ::= expr LSQBRACKET expr RSQBRACKET */
#line 213 "parser\\epparser.lemon"
{
    yymsp[-3].minor.yy0->data = yymsp[-3].minor.yy0->data + "[" + yymsp[-1].minor.yy0->data + "]";
    delete yymsp[-1].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 1517 "parser\\epparser.c"
        break;
      case 57: /* fArgs_nonEmpty ::= fArgs_nonEmpty COMMA fArgs_nonEmpty */
#line 222 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data;
    yymsp[-2].minor.yy0->type = TOKEN_TEMP;
    yygotominor.yy0 = yymsp[-2].minor.yy0;
    delete yymsp[0].minor.yy0;
}
#line 1527 "parser\\epparser.c"
        break;
      case 60: /* funcexpr ::= NAME LPAREN fArgs RPAREN */
#line 232 "parser\\epparser.lemon"
{
    // Preprocess yymsp[-3].minor.yy0
    funcNamePreprocess(yymsp[-3].minor.yy0->data);
    checkIsFunction(yymsp[-3].minor.yy0->data);
    yymsp[-3].minor.yy0->data += "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 1538 "parser\\epparser.c"
        break;
      case 61: /* funcexpr ::= expr LPAREN fArgs RPAREN */
#line 240 "parser\\epparser.lemon"
{
    // If calling function imported from another module, add f_ prefix to function yymsp[-3].minor.yy0.
    std::string& nameStr = yymsp[-3].minor.yy0->data;
    if(std::count(nameStr.begin(), nameStr.end(), '.') == 1) {
        size_t p = nameStr.find('.');
        std::string moduleName = nameStr.substr(0, p);
        if (closure->isModule(moduleName)) {
            std::string funcName = nameStr.substr(p + 1);
            funcNamePreprocess(funcName);
            yymsp[-3].minor.yy0->data = moduleName + '.' + funcName;
        }
    }

    // Preprocess yymsp[-3].minor.yy0
    yymsp[-3].minor.yy0->data += "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 1559 "parser\\epparser.c"
        break;
      case 63: /* expr ::= LPAREN expr RPAREN */
#line 261 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1567 "parser\\epparser.c"
        break;
      case 64: /* expr ::= LSQBRACKET exprList RSQBRACKET */
#line 266 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "EUDArray(FlattenList([" + yymsp[-1].minor.yy0->data + "]))";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1575 "parser\\epparser.c"
        break;
      case 65: /* expr ::= L2V LPAREN lexpr RPAREN */
#line 271 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "_L2V(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = genTemp(yymsp[-1].minor.yy0);
}
#line 1583 "parser\\epparser.c"
        break;
      case 66: /* expr ::= MAPSTRING LPAREN STRING RPAREN */
#line 276 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetStringIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1591 "parser\\epparser.c"
        break;
      case 67: /* expr ::= UNIT LPAREN STRING RPAREN */
#line 281 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "EncodeUnit(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1599 "parser\\epparser.c"
        break;
      case 68: /* expr ::= SWITCH LPAREN STRING RPAREN */
#line 286 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "EncodeSwitch(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1607 "parser\\epparser.c"
        break;
      case 69: /* expr ::= LOCATION LPAREN STRING RPAREN */
#line 291 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetLocationIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1615 "parser\\epparser.c"
        break;
      case 70: /* expr ::= expr PLUS expr */
#line 297 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "+",  yymsp[0].minor.yy0); }
#line 1620 "parser\\epparser.c"
        break;
      case 71: /* expr ::= expr MINUS expr */
#line 298 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "-",  yymsp[0].minor.yy0); }
#line 1625 "parser\\epparser.c"
        break;
      case 72: /* expr ::= expr MULTIPLY expr */
#line 299 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "*",  yymsp[0].minor.yy0); }
#line 1630 "parser\\epparser.c"
        break;
      case 73: /* expr ::= expr DIVIDE expr */
#line 300 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "//", yymsp[0].minor.yy0); }
#line 1635 "parser\\epparser.c"
        break;
      case 74: /* expr ::= expr MOD expr */
#line 301 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "%",  yymsp[0].minor.yy0); }
#line 1640 "parser\\epparser.c"
        break;
      case 75: /* expr ::= expr LSHIFT expr */
#line 302 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<<", yymsp[0].minor.yy0); }
#line 1645 "parser\\epparser.c"
        break;
      case 76: /* expr ::= expr RSHIFT expr */
#line 303 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">>", yymsp[0].minor.yy0); }
#line 1650 "parser\\epparser.c"
        break;
      case 77: /* expr ::= expr BITAND expr */
#line 304 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "&",  yymsp[0].minor.yy0); }
#line 1655 "parser\\epparser.c"
        break;
      case 78: /* expr ::= expr BITOR expr */
#line 305 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "|",  yymsp[0].minor.yy0); }
#line 1660 "parser\\epparser.c"
        break;
      case 79: /* expr ::= expr BITXOR expr */
#line 306 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "^",  yymsp[0].minor.yy0); }
#line 1665 "parser\\epparser.c"
        break;
      case 80: /* expr ::= PLUS expr */
#line 309 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = +" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1670 "parser\\epparser.c"
        break;
      case 81: /* expr ::= MINUS expr */
#line 310 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = -" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1675 "parser\\epparser.c"
        break;
      case 82: /* expr ::= BITNOT expr */
#line 311 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = ~" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1680 "parser\\epparser.c"
        break;
      case 83: /* lexpr ::= expr EQ expr */
#line 315 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "==", yymsp[0].minor.yy0); }
#line 1685 "parser\\epparser.c"
        break;
      case 84: /* lexpr ::= expr NE expr */
#line 316 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "!=", yymsp[0].minor.yy0); }
#line 1690 "parser\\epparser.c"
        break;
      case 85: /* lexpr ::= expr LE expr */
#line 317 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<=", yymsp[0].minor.yy0); }
#line 1695 "parser\\epparser.c"
        break;
      case 86: /* lexpr ::= expr LT expr */
#line 318 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<",  yymsp[0].minor.yy0); }
#line 1700 "parser\\epparser.c"
        break;
      case 87: /* lexpr ::= expr GE expr */
#line 319 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">=", yymsp[0].minor.yy0); }
#line 1705 "parser\\epparser.c"
        break;
      case 88: /* lexpr ::= expr GT expr */
#line 320 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">" , yymsp[0].minor.yy0); }
#line 1710 "parser\\epparser.c"
        break;
      case 89: /* lexpr ::= lexpr LAND lexpr */
#line 322 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "[" + yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data + "]";
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1719 "parser\\epparser.c"
        break;
      case 90: /* lexpr ::= lexpr LOR lexpr */
#line 328 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "EUDOr([" + yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data + "])";
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1728 "parser\\epparser.c"
        break;
      case 91: /* lexpr ::= LNOT lexpr */
#line 334 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = "EUDNot([" + yymsp[0].minor.yy0->data + "])";
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0);
}
#line 1736 "parser\\epparser.c"
        break;
      case 93: /* vdef_stmt ::= VAR nameList_nonEmpty */
#line 344 "parser\\epparser.lemon"
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
#line 1760 "parser\\epparser.c"
        break;
      case 94: /* vdefAssign_stmt ::= VAR nameList_nonEmpty ASSIGN exprList_nonEmpty */
#line 365 "parser\\epparser.lemon"
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
#line 1785 "parser\\epparser.c"
        break;
      case 95: /* cdef_stmt ::= CONST nameList_nonEmpty ASSIGN exprList_nonEmpty */
#line 387 "parser\\epparser.lemon"
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
#line 1807 "parser\\epparser.c"
        break;
      case 96: /* lvalue ::= NAME */
#line 407 "parser\\epparser.lemon"
{
    checkIsVariable(yymsp[0].minor.yy0->data);
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1815 "parser\\epparser.c"
        break;
      case 97: /* lvalue ::= expr LSQBRACKET expr RSQBRACKET */
#line 412 "parser\\epparser.lemon"
{
    checkIsConstant(yymsp[-3].minor.yy0->data);
    yymsp[-1].minor.yy0->data = "_ARRW(" + yymsp[-3].minor.yy0->data + ", " + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
    delete yymsp[-3].minor.yy0;
}
#line 1825 "parser\\epparser.c"
        break;
      case 98: /* lvalue ::= expr PERIOD NAME */
#line 419 "parser\\epparser.lemon"
{
    checkIsConstant(yymsp[-2].minor.yy0->data);
    yymsp[0].minor.yy0->data = "_ATTW(" + yymsp[-2].minor.yy0->data + ", '" + yymsp[0].minor.yy0->data + "')";
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0);
    delete yymsp[-2].minor.yy0;
}
#line 1835 "parser\\epparser.c"
        break;
      case 101: /* assign_stmt ::= lvalue ASSIGN expr */
#line 428 "parser\\epparser.lemon"
{
    ps->gen << yymsp[-2].minor.yy0->data << " << (" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 1843 "parser\\epparser.c"
        break;
      case 102: /* assign_stmt ::= lvalueList_nonEmpty ASSIGN exprList_nonEmpty */
#line 433 "parser\\epparser.lemon"
{
    ps->gen << "_SV([" << yymsp[-2].minor.yy0->data << "], [" << yymsp[0].minor.yy0->data << "])" << std::endl;
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 1851 "parser\\epparser.c"
        break;
      case 103: /* assign_stmt ::= lvalue IADD expr */
#line 441 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__iadd__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1856 "parser\\epparser.c"
        break;
      case 104: /* assign_stmt ::= lvalue ISUB expr */
#line 442 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__isub__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1861 "parser\\epparser.c"
        break;
      case 105: /* assign_stmt ::= lvalue IMUL expr */
#line 443 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__imul__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1866 "parser\\epparser.c"
        break;
      case 106: /* assign_stmt ::= lvalue IDIV expr */
#line 444 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ifloordiv__("  << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1871 "parser\\epparser.c"
        break;
      case 107: /* assign_stmt ::= lvalue IMOD expr */
#line 445 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__imod__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1876 "parser\\epparser.c"
        break;
      case 108: /* assign_stmt ::= lvalue ILSH expr */
#line 446 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ilshift__("    << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1881 "parser\\epparser.c"
        break;
      case 109: /* assign_stmt ::= lvalue IRSH expr */
#line 447 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__irshift__("    << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1886 "parser\\epparser.c"
        break;
      case 110: /* assign_stmt ::= lvalue IBND expr */
#line 448 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__iand__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1891 "parser\\epparser.c"
        break;
      case 111: /* assign_stmt ::= lvalue IBOR expr */
#line 449 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ior__("        << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1896 "parser\\epparser.c"
        break;
      case 112: /* assign_stmt ::= lvalue IBXR expr */
#line 450 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ixor__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1901 "parser\\epparser.c"
        break;
      case 113: /* if_start ::= IF */
#line 453 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDIf()" << std::endl;
}
#line 1909 "parser\\epparser.c"
        break;
      case 114: /* if_header ::= if_start LPAREN lexpr RPAREN */
      case 123: /* while_header ::= while_start LPAREN lexpr RPAREN */ yytestcase(yyruleno==123);
#line 457 "parser\\epparser.lemon"
{
    ps->gen << "if " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data << "):" << std::endl;
    ps->gen.indent();
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1919 "parser\\epparser.c"
        break;
      case 116: /* elif_start ::= ELSE IF */
#line 465 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen.unindent(false);
    ps->gen << yygotominor.yy0->data << " = EUDElseIf()" << std::endl;
}
#line 1928 "parser\\epparser.c"
        break;
      case 117: /* elif_header ::= elif_start LPAREN lexpr RPAREN */
#line 471 "parser\\epparser.lemon"
{
    ps->gen << "if " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data <<"):" << std::endl;
    ps->gen.indent();
}
#line 1936 "parser\\epparser.c"
        break;
      case 119: /* else_header ::= ELSE */
#line 478 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "if EUDElse()():" << std::endl;
    ps->gen.indent();
}
#line 1945 "parser\\epparser.c"
        break;
      case 120: /* if_stmt ::= if_block */
      case 121: /* if_stmt ::= if_block else_header stmt */ yytestcase(yyruleno==121);
#line 484 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndIf()" << std::endl;
}
#line 1954 "parser\\epparser.c"
        break;
      case 122: /* while_start ::= WHILE */
#line 496 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDWhile()" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1963 "parser\\epparser.c"
        break;
      case 124: /* while_stmt ::= while_header stmt */
#line 508 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndWhile()" << std::endl;
}
#line 1971 "parser\\epparser.c"
        break;
      case 125: /* for_opener ::= FOR LPAREN */
      case 140: /* foreach_opener ::= FOREACH LPAREN */ yytestcase(yyruleno==140);
#line 514 "parser\\epparser.lemon"
{
    ps->closure.pushScope();
}
#line 1979 "parser\\epparser.c"
        break;
      case 135: /* for_header1 ::= for_opener for_init_stmt SEMICOLON */
#line 530 "parser\\epparser.lemon"
{
    // opening for lexpr
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDWhile()" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1989 "parser\\epparser.c"
        break;
      case 136: /* for_header2 ::= for_header1 lexpr SEMICOLON */
#line 537 "parser\\epparser.lemon"
{
    ps->gen << "if " << yymsp[-2].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data << "):" << std::endl;
    ps->gen.indent();
    delete yymsp[-2].minor.yy0; delete yymsp[-1].minor.yy0;

    // Opening for assign_statement
    yygotominor.yy0 = genTemp(yymsp[-1].minor.yy0);
    ps->gen << "def " << yygotominor.yy0->data <<"():" << std::endl;
    ps->gen.indent();
}
#line 2003 "parser\\epparser.c"
        break;
      case 137: /* for_header ::= for_header2 for_action_stmt_nonEmpty RPAREN */
#line 548 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-2].minor.yy0;
    ps->gen.unindent(false);
}
#line 2011 "parser\\epparser.c"
        break;
      case 138: /* for_header ::= for_header2 RPAREN */
#line 553 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
    ps->gen << "pass" << std::endl;
    ps->gen.unindent(false);
}
#line 2020 "parser\\epparser.c"
        break;
      case 139: /* for_stmt ::= for_header stmt */
#line 559 "parser\\epparser.lemon"
{
    ps->gen << yymsp[-1].minor.yy0->data << "()" << std::endl;
    ps->gen.unindent(false);
    ps->gen << "EUDEndWhile()" << std::endl;
    ps->closure.popScope();
}
#line 2030 "parser\\epparser.c"
        break;
      case 141: /* foreach_header ::= foreach_opener nameList_nonEmpty COLON exprList_nonEmpty RPAREN */
#line 573 "parser\\epparser.lemon"
{
    commaListIter(yymsp[-3].minor.yy0->data, [&](std::string& s) {
        ps->closure.defVariable(s);
    });
    ps->gen << "for " << yymsp[-3].minor.yy0->data << " in " << yymsp[-1].minor.yy0->data << ":" << std::endl;
    ps->gen.indent();
}
#line 2041 "parser\\epparser.c"
        break;
      case 143: /* continue_stmt ::= CONTINUE */
#line 589 "parser\\epparser.lemon"
{
    ps->gen << "EUDContinue()" << std::endl;
}
#line 2048 "parser\\epparser.c"
        break;
      case 144: /* break_stmt ::= BREAK */
#line 593 "parser\\epparser.lemon"
{
    ps->gen << "EUDBreak()" << std::endl;
}
#line 2055 "parser\\epparser.c"
        break;
      case 145: /* return_stmt ::= RETURN exprList */
#line 600 "parser\\epparser.lemon"
{
    ps->gen << "EUDReturn(" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2063 "parser\\epparser.c"
        break;
      case 146: /* lexpr ::= CONDITIONNAME LPAREN fArgs RPAREN */
      case 147: /* lexpr ::= KILLS LPAREN fArgs RPAREN */ yytestcase(yyruleno==147);
#line 608 "parser\\epparser.lemon"
{
    yymsp[-3].minor.yy0->data = yymsp[-3].minor.yy0->data + "(" + yymsp[-1].minor.yy0->data + ")";
    delete yymsp[-1].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 2073 "parser\\epparser.c"
        break;
      case 148: /* lexpr ::= CONDITIONNAME LPAREN RPAREN */
#line 620 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + "()";
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 2081 "parser\\epparser.c"
        break;
      case 149: /* action ::= ACTIONNAME LPAREN fArgs RPAREN SEMICOLON */
#line 625 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[-4].minor.yy0);
    yygotominor.yy0->data =  yymsp[-4].minor.yy0->data + "(" + yymsp[-2].minor.yy0->data + ")";
    delete yymsp[-4].minor.yy0; delete yymsp[-2].minor.yy0;
}
#line 2090 "parser\\epparser.c"
        break;
      case 150: /* actions ::= action action */
      case 151: /* actions ::= actions action */ yytestcase(yyruleno==151);
#line 631 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
    yymsp[-1].minor.yy0->data += ",\n" + yymsp[0].minor.yy0->data;
    delete yymsp[0].minor.yy0;
}
#line 2100 "parser\\epparser.c"
        break;
      case 152: /* actionStmt ::= action */
#line 643 "parser\\epparser.lemon"
{
    ps->gen << "DoActions(" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2108 "parser\\epparser.c"
        break;
      case 153: /* actionStmt ::= actions */
#line 648 "parser\\epparser.lemon"
{
    ps->gen << "DoActions([" << std::endl;
    ps->gen.indent();
    ps->gen << yymsp[0].minor.yy0->data << std::endl;
    ps->gen.unindent(false);
    ps->gen << "])" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2120 "parser\\epparser.c"
        break;
      default:
      /* (0) program ::= chunks */ yytestcase(yyruleno==0);
      /* (1) chunks ::= */ yytestcase(yyruleno==1);
      /* (2) chunks ::= chunks chunk */ yytestcase(yyruleno==2);
      /* (3) chunk ::= import_chunk SEMICOLON */ yytestcase(yyruleno==3);
      /* (4) chunk ::= fdef_chunk */ yytestcase(yyruleno==4);
      /* (5) chunk ::= vdef_stmt SEMICOLON */ yytestcase(yyruleno==5);
      /* (6) chunk ::= cdef_stmt SEMICOLON */ yytestcase(yyruleno==6);
      /* (14) stmt ::= bodyStmt */ yytestcase(yyruleno==14);
      /* (15) stmt ::= return_stmt SEMICOLON */ yytestcase(yyruleno==15);
      /* (19) blockStmt ::= lbracket return_stmt SEMICOLON rbracket */ yytestcase(yyruleno==19);
      /* (20) blockStmt ::= lbracket bodyStmtList rbracket */ yytestcase(yyruleno==20);
      /* (21) blockStmt ::= lbracket bodyStmtList return_stmt SEMICOLON rbracket */ yytestcase(yyruleno==21);
      /* (23) bodyStmt ::= blockStmt */ yytestcase(yyruleno==23);
      /* (24) bodyStmt ::= SEMICOLON */ yytestcase(yyruleno==24);
      /* (25) bodyStmt ::= vdef_stmt SEMICOLON */ yytestcase(yyruleno==25);
      /* (26) bodyStmt ::= vdefAssign_stmt SEMICOLON */ yytestcase(yyruleno==26);
      /* (27) bodyStmt ::= cdef_stmt SEMICOLON */ yytestcase(yyruleno==27);
      /* (28) bodyStmt ::= assign_stmt SEMICOLON */ yytestcase(yyruleno==28);
      /* (30) bodyStmt ::= actionStmt */ yytestcase(yyruleno==30);
      /* (31) bodyStmt ::= if_stmt */ yytestcase(yyruleno==31);
      /* (32) bodyStmt ::= while_stmt */ yytestcase(yyruleno==32);
      /* (33) bodyStmt ::= for_stmt */ yytestcase(yyruleno==33);
      /* (34) bodyStmt ::= foreach_stmt */ yytestcase(yyruleno==34);
      /* (35) bodyStmt ::= continue_stmt SEMICOLON */ yytestcase(yyruleno==35);
      /* (36) bodyStmt ::= break_stmt SEMICOLON */ yytestcase(yyruleno==36);
      /* (37) bodyStmtList ::= bodyStmt */ yytestcase(yyruleno==37);
      /* (38) bodyStmtList ::= bodyStmtList bodyStmt */ yytestcase(yyruleno==38);
      /* (115) if_block ::= if_header stmt */ yytestcase(yyruleno==115);
      /* (118) if_block ::= if_block elif_header stmt */ yytestcase(yyruleno==118);
      /* (126) for_init_stmt_nonEmpty ::= vdef_stmt */ yytestcase(yyruleno==126);
      /* (127) for_init_stmt_nonEmpty ::= vdefAssign_stmt */ yytestcase(yyruleno==127);
      /* (128) for_init_stmt_nonEmpty ::= cdef_stmt */ yytestcase(yyruleno==128);
      /* (129) for_init_stmt_nonEmpty ::= assign_stmt */ yytestcase(yyruleno==129);
      /* (130) for_init_stmt_nonEmpty ::= for_init_stmt_nonEmpty COMMA for_init_stmt_nonEmpty */ yytestcase(yyruleno==130);
      /* (131) for_init_stmt ::= for_init_stmt_nonEmpty */ yytestcase(yyruleno==131);
      /* (132) for_init_stmt ::= */ yytestcase(yyruleno==132);
      /* (133) for_action_stmt_nonEmpty ::= assign_stmt */ yytestcase(yyruleno==133);
      /* (134) for_action_stmt_nonEmpty ::= for_action_stmt_nonEmpty COMMA for_action_stmt_nonEmpty */ yytestcase(yyruleno==134);
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
#line 23 "parser\\epparser.lemon"

    throw_error(-1, "Unrecoverable error");
#line 2209 "parser\\epparser.c"
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
#line 662 "parser\\epparser.lemon"


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
#line 2462 "parser\\epparser.c"
