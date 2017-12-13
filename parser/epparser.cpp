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
std::string currentFunction;
std::string currentModule;
bool functionCalledInMultipleActions;
bool PARSER_DEBUG = false;
bool MAP_DEBUG = false;

#line 37 "parser\\epparser.c"
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
#define YYNOCODE 140
#define YYACTIONTYPE unsigned short int
#define ParseTOKENTYPE Token*
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  int yy279;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL  ParserStruct* ps ;
#define ParseARG_PDECL , ParserStruct* ps 
#define ParseARG_FETCH  ParserStruct* ps  = yypParser->ps 
#define ParseARG_STORE yypParser->ps  = ps 
#define YYNSTATE 343
#define YYNRULE 178
#define YYERRORSYMBOL 72
#define YYERRSYMDT yy279
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
#define YY_ACTTAB_COUNT (1242)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   223,   67,   69,   68,   74,   73,   71,   72,   70,  219,
 /*    10 */    38,  224,  317,  207,  207,  341,  327,   18,   18,  337,
 /*    20 */   325,  222,    2,   75,   75,  218,  217,  216,  155,  309,
 /*    30 */   308,  307,  306,  305,  211,  210,   37,  224,   94,  255,
 /*    40 */   209,  172,    7,    3,  125,  150,  174,    8,   40,  231,
 /*    50 */    94,  230,  171,    6,   11,  223,  125,  150,  336,   22,
 /*    60 */    13,    5,   84,    4,  219,  335,   77,  317,  311,  167,
 /*    70 */   166,  270,  332,   27,   28,  325,  222,    2,  331,  215,
 /*    80 */   218,  217,  216,  155,  309,  308,  307,  306,  305,  211,
 /*    90 */   210,   76,  228,   94,   78,  255,  209,  256,  203,  125,
 /*   100 */   150,  174,    8,   40,   27,   28,   94,  171,    6,   11,
 /*   110 */   226,  223,  125,  150,   22,   13,    5,   84,    4,  206,
 /*   120 */   219,   77,   19,  317,  330,  254,  224,  267,  201,  118,
 /*   130 */    87,  325,  222,    2,  285,  202,  218,  217,  216,  155,
 /*   140 */   309,  308,  307,  306,  305,  211,  210,   35,   36,   94,
 /*   150 */    39,  206,   81,  236,  224,  125,  150,  174,    8,   40,
 /*   160 */   201,  118,  246,  171,    6,   11,  223,   33,  224,  328,
 /*   170 */    22,   13,    5,   84,    4,  219,  326,   77,  317,   27,
 /*   180 */    28,  250,  264,  224,   32,  224,  325,  222,    2,  324,
 /*   190 */    34,  218,  217,  216,  155,  309,  308,  307,  306,  305,
 /*   200 */   211,  210,  522,   10,   94,   27,   28,  209,  237,  280,
 /*   210 */   125,  150,  174,    8,   40,   27,   28,  100,  171,    6,
 /*   220 */    11,   90,  223,  273,   89,   22,   13,    5,   84,    4,
 /*   230 */   206,  219,   77,  315,  317,  271,   83,   82,  252,  293,
 /*   240 */   118,  314,  325,  222,    2,  268,  313,  218,  217,  216,
 /*   250 */   155,  309,  308,  307,  306,  305,  211,  210,  312,  214,
 /*   260 */    94,   27,   28,  206,  213,  212,  125,  150,  174,    8,
 /*   270 */    40,  310,  177,  118,  171,    6,   11,  223,  304,  303,
 /*   280 */   209,   22,   13,    5,   84,    4,  219,  215,   77,  317,
 /*   290 */   119,  265,  291,  249,   19,  298,  227,  325,  222,    2,
 /*   300 */   225,  205,  218,  217,  216,  155,  309,  308,  307,  306,
 /*   310 */   305,  211,  210,   88,  295,   94,  294,  206,  209,   39,
 /*   320 */    30,  125,  150,  174,    8,   40,  176,  118,  120,  171,
 /*   330 */     6,   11,   17,  223,   31,  196,   22,   13,    5,   84,
 /*   340 */     4,  206,  219,   77,  290,  317,  209,  195,  192,  242,
 /*   350 */   175,  118,  193,  325,  222,    2,   97,  289,  218,  217,
 /*   360 */   216,  155,  309,  308,  307,  306,  305,  211,  210,  190,
 /*   370 */   187,   94,  189,  206,  209,  288,  186,  125,  150,  174,
 /*   380 */     8,   40,  148,  118,   93,  171,    6,   11,  161,  136,
 /*   390 */   287,  209,   22,   13,    5,   84,    4,  219,  286,   77,
 /*   400 */   317,   92,   28,   15,  269,  278,  137,  282,  240,  221,
 /*   410 */     2,  277,    1,  218,  217,  216,  155,  309,  308,  307,
 /*   420 */   306,  305,  211,  210,  276,  123,   94,   25,  206,  209,
 /*   430 */    12,  257,  125,  150,  174,    8,   40,  158,  118,  131,
 /*   440 */   171,    6,   11,   24,  301,   23,  263,   22,   13,    5,
 /*   450 */    84,    4,  206,  219,   77,   14,  317,  253,  251,   16,
 /*   460 */   245,  157,  118,  162,  302,  220,    2,  319,  241,  218,
 /*   470 */   217,  216,  155,  309,  308,  307,  306,  305,  211,  210,
 /*   480 */   159,  239,   94,  209,  209,  209,  156,  333,  125,  150,
 /*   490 */   174,    8,   40,  130,   93,   93,  171,    6,   11,  284,
 /*   500 */   184,  320,  321,   22,   13,    5,   84,    4,   63,   62,
 /*   510 */    77,   71,   72,   70,   61,  300,  121,  316,  318,  207,
 /*   520 */   153,  209,   64,   18,  204,  323,   86,  322,   21,   75,
 /*   530 */   299,  143,  181,  200,  197,  194,  191,  188,   85,   42,
 /*   540 */    41,   66,   65,   67,   69,   68,   74,   73,   71,   72,
 /*   550 */    70,  272,  209,  266,  170,  165,  207,  248,  247,   20,
 /*   560 */    18,  279,  119,  329,  198,  179,   75,  297,  152,  151,
 /*   570 */    63,   62,  209,  209,  149,  244,   61,  300,  121,  316,
 /*   580 */   164,  243,  142,  119,   64,  198,  180,  323,   86,  321,
 /*   590 */    21,  146,  299,  145,  144,  200,  197,  194,  191,  188,
 /*   600 */    85,   42,   41,   66,   65,   67,   69,   68,   74,   73,
 /*   610 */    71,   72,   70,  272,  209,  266,  170,  165,  207,  248,
 /*   620 */   247,   20,   18,  296,  119,  173,  198,  185,   75,  523,
 /*   630 */   523,  523,   63,   62,  209,  209,  523,  523,   61,  300,
 /*   640 */   121,  316,  523,  209,  141,  119,   64,  198,  163,  323,
 /*   650 */    86,  523,   21,  119,  299,  198,  182,  200,  197,  194,
 /*   660 */   191,  188,   85,   42,   41,  523,  209,  523,  523,  523,
 /*   670 */   523,  523,  523,  523,  209,  272,  129,  266,  170,  165,
 /*   680 */   523,  248,  247,   20,  128,   60,   58,   57,   56,   55,
 /*   690 */    59,   66,   65,   67,   69,   68,   74,   73,   71,   72,
 /*   700 */    70,  523,  209,  209,  209,  209,  207,  523,  523,  523,
 /*   710 */    18,  296,   93,  127,  124,  126,   75,  283,   60,   58,
 /*   720 */    57,   56,   55,   59,   66,   65,   67,   69,   68,   74,
 /*   730 */    73,   71,   72,   70,  209,  209,  523,  523,  523,  207,
 /*   740 */    63,   62,  209,   18,   96,  140,   61,  300,  121,   75,
 /*   750 */   523,  209,   93,  209,   64,  523,  523,  135,   86,  523,
 /*   760 */    21,  139,  299,  138,  523,  200,  197,  194,  191,  188,
 /*   770 */    85,   42,   41,  523,   66,   65,   67,   69,   68,   74,
 /*   780 */    73,   71,   72,   70,  523,  209,  209,   26,  209,  178,
 /*   790 */   523,  523,  209,   18,  209,  117,  116,  523,   93,   54,
 /*   800 */    63,   62,  115,  134,   93,  209,   61,  300,  208,  133,
 /*   810 */   275,  274,  523,  209,   29,  114,  523,  523,  523,  523,
 /*   820 */    21,  209,  199,  113,  523,  200,  197,  194,  191,  188,
 /*   830 */   523,   93,  209,   63,   62,  209,  132,  523,  523,   61,
 /*   840 */   300,  154,  112,  523,  209,   95,  523,   64,  281,  523,
 /*   850 */   523,  523,  183,   21,  111,  299,  292,  523,  200,  197,
 /*   860 */   194,  191,  188,  523,  523,  523,   63,   62,  209,  209,
 /*   870 */   523,  209,   61,  300,  121,  209,  523,  209,  110,  109,
 /*   880 */    64,  108,  523,  523,  523,  107,   21,  106,  299,  209,
 /*   890 */   523,  200,  197,  194,  191,  188,   53,   42,   41,  105,
 /*   900 */    66,   65,   67,   69,   68,   74,   73,   71,   72,   70,
 /*   910 */    63,   62,  457,  457,  523,  207,   61,  300,  154,   18,
 /*   920 */   523,  209,  523,  523,   64,   75,  122,  523,  523,  523,
 /*   930 */    21,  104,  299,  292,  209,  200,  197,  194,  191,  188,
 /*   940 */   523,  523,  523,   19,  103,  523,   52,   51,   50,   49,
 /*   950 */    48,   47,   46,   45,   44,   43,  523,  523,  523,  523,
 /*   960 */   523,  523,  457,  457,  457,  457,  457,  457,  457,  457,
 /*   970 */   457,  457,  523,  523,  523,  523,   66,   65,   67,   69,
 /*   980 */    68,   74,   73,   71,   72,   70,  209,  523,  209,  209,
 /*   990 */   523,  207,  523,  209,  523,   18,  102,  523,  101,   99,
 /*  1000 */   262,   75,  523,   98,  523,   66,   65,   67,   69,   68,
 /*  1010 */    74,   73,   71,   72,   70,  523,  261,  260,  259,  209,
 /*  1020 */   178,  523,  523,  523,   18,   63,   62,  523,  523,   94,
 /*  1030 */    54,   61,  300,  208,  523,  125,  150,  523,  523,   64,
 /*  1040 */   523,  523,  523,  523,  523,   21,  258,  299,  523,  523,
 /*  1050 */   200,  197,  194,  191,  188,  523,  523,  523,   63,   62,
 /*  1060 */   523,  523,  523,  523,   61,  300,  121,  523,  523,  523,
 /*  1070 */   523,  523,   64,  523,  523,  523,  523,  523,   21,  523,
 /*  1080 */   299,  523,  523,  200,  197,  194,  191,  188,  342,  235,
 /*  1090 */   340,  339,  338,  234,  233,  232,  334,  523,    9,  523,
 /*  1100 */   523,  238,  147,  459,  459,  523,    2,   65,   67,   69,
 /*  1110 */    68,   74,   73,   71,   72,   70,  458,  458,  523,  523,
 /*  1120 */   523,  207,  523,  523,  523,   18,   74,   73,   71,   72,
 /*  1130 */    70,   75,  523,  523,  523,  523,  207,  523,  523,  523,
 /*  1140 */    18,  523,  523,  523,  523,  523,   75,  523,  523,  523,
 /*  1150 */   523,  523,  523,  459,  459,  459,  459,  459,  459,  459,
 /*  1160 */   459,  459,  459,  523,  523,  523,  458,  458,  458,  458,
 /*  1170 */   458,  458,  458,  458,  458,  458,   69,   68,   74,   73,
 /*  1180 */    71,   72,   70,  523,  262,  523,  523,  523,  207,  523,
 /*  1190 */   523,  523,   18,  343,  523,  523,  523,  523,   75,  523,
 /*  1200 */   261,  260,  259,  209,  523,  523,  523,  523,  523,  523,
 /*  1210 */   523,  523,  523,   94,  523,  523,  523,  523,  523,  125,
 /*  1220 */   150,  523,   91,  523,  229,  523,  523,  160,  323,   80,
 /*  1230 */   169,  168,  523,  523,  523,  523,  523,  523,  523,  523,
 /*  1240 */   523,   79,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    72,   15,   16,   17,   18,   19,   20,   21,   22,   81,
 /*    10 */     1,    2,   84,   28,   28,   27,   88,   32,   32,   27,
 /*    20 */    92,   93,   94,   38,   38,   97,   98,   99,  100,  101,
 /*    30 */   102,  103,  104,  105,  106,  107,    1,    2,  110,   99,
 /*    40 */   100,  121,  122,  123,  116,  117,  118,  119,  120,   28,
 /*    50 */   110,   30,  124,  125,  126,   72,  116,  117,   27,  131,
 /*    60 */   132,  133,  134,  135,   81,   27,  138,   84,   27,  129,
 /*    70 */   130,   88,   26,    3,    4,   92,   93,   94,   26,   38,
 /*    80 */    97,   98,   99,  100,  101,  102,  103,  104,  105,  106,
 /*    90 */   107,    1,   26,  110,   32,   99,  100,   27,    2,  116,
 /*   100 */   117,  118,  119,  120,    3,    4,  110,  124,  125,  126,
 /*   110 */    33,   72,  116,  117,  131,  132,  133,  134,  135,  100,
 /*   120 */    81,  138,   32,   84,   27,  129,    2,   88,  109,  110,
 /*   130 */   111,   92,   93,   94,   33,   39,   97,   98,   99,  100,
 /*   140 */   101,  102,  103,  104,  105,  106,  107,    1,    2,  110,
 /*   150 */     2,  100,   36,   37,    2,  116,  117,  118,  119,  120,
 /*   160 */   109,  110,  111,  124,  125,  126,   72,    1,    2,   26,
 /*   170 */   131,  132,  133,  134,  135,   81,   27,  138,   84,    3,
 /*   180 */     4,   33,   88,    2,    1,    2,   92,   93,   94,   27,
 /*   190 */    66,   97,   98,   99,  100,  101,  102,  103,  104,  105,
 /*   200 */   106,  107,   74,   75,  110,    3,    4,  100,   27,   33,
 /*   210 */   116,  117,  118,  119,  120,    3,    4,  110,  124,  125,
 /*   220 */   126,   27,   72,  116,   27,  131,  132,  133,  134,  135,
 /*   230 */   100,   81,  138,   27,   84,   33,  136,  137,   88,  109,
 /*   240 */   110,   27,   92,   93,   94,   33,   27,   97,   98,   99,
 /*   250 */   100,  101,  102,  103,  104,  105,  106,  107,   27,   38,
 /*   260 */   110,    3,    4,  100,   25,   39,  116,  117,  118,  119,
 /*   270 */   120,   39,  109,  110,  124,  125,  126,   72,   27,   27,
 /*   280 */   100,  131,  132,  133,  134,  135,   81,   38,  138,   84,
 /*   290 */   110,   33,  112,   88,   32,   26,   87,   92,   93,   94,
 /*   300 */    91,   38,   97,   98,   99,  100,  101,  102,  103,  104,
 /*   310 */   105,  106,  107,   38,   25,  110,   39,  100,  100,    2,
 /*   320 */    32,  116,  117,  118,  119,  120,  109,  110,  110,  124,
 /*   330 */   125,  126,   32,   72,    2,   32,  131,  132,  133,  134,
 /*   340 */   135,  100,   81,  138,   33,   84,  100,   41,   41,   88,
 /*   350 */   109,  110,   32,   92,   93,   94,  110,   33,   97,   98,
 /*   360 */    99,  100,  101,  102,  103,  104,  105,  106,  107,   32,
 /*   370 */    32,  110,   41,  100,  100,   33,   41,  116,  117,  118,
 /*   380 */   119,  120,  109,  110,  110,  124,  125,  126,   72,  115,
 /*   390 */    33,  100,  131,  132,  133,  134,  135,   81,   33,  138,
 /*   400 */    84,  110,    4,   32,   61,   39,  115,   33,   92,   93,
 /*   410 */    94,   33,   96,   97,   98,   99,  100,  101,  102,  103,
 /*   420 */   104,  105,  106,  107,   33,   26,  110,   32,  100,  100,
 /*   430 */     2,   27,  116,  117,  118,  119,  120,  109,  110,  110,
 /*   440 */   124,  125,  126,   32,   72,   32,   32,  131,  132,  133,
 /*   450 */   134,  135,  100,   81,  138,    2,   84,   33,   32,   32,
 /*   460 */    27,  109,  110,   33,   92,   93,   94,   95,   37,   97,
 /*   470 */    98,   99,  100,  101,  102,  103,  104,  105,  106,  107,
 /*   480 */    26,   35,  110,  100,  100,  100,   85,   26,  116,  117,
 /*   490 */   118,  119,  120,  110,  110,  110,  124,  125,  126,  115,
 /*   500 */   115,   95,   37,  131,  132,  133,  134,  135,   18,   19,
 /*   510 */   138,   20,   21,   22,   24,   25,   26,   27,   95,   28,
 /*   520 */   108,  100,   32,   32,   25,   35,   36,   37,   38,   38,
 /*   530 */    40,  110,  114,   43,   44,   45,   46,   47,   48,   49,
 /*   540 */    50,   13,   14,   15,   16,   17,   18,   19,   20,   21,
 /*   550 */    22,   61,  100,   63,   64,   65,   28,   67,   68,   69,
 /*   560 */    32,    2,  110,   26,  112,  113,   38,   39,   91,   91,
 /*   570 */    18,   19,  100,  100,   91,  136,   24,   25,   26,   27,
 /*   580 */    71,  136,  110,  110,   32,  112,  113,   35,   36,   37,
 /*   590 */    38,   91,   40,   91,   91,   43,   44,   45,   46,   47,
 /*   600 */    48,   49,   50,   13,   14,   15,   16,   17,   18,   19,
 /*   610 */    20,   21,   22,   61,  100,   63,   64,   65,   28,   67,
 /*   620 */    68,   69,   32,   33,  110,   62,  112,  113,   38,  139,
 /*   630 */   139,  139,   18,   19,  100,  100,  139,  139,   24,   25,
 /*   640 */    26,   27,  139,  100,  110,  110,   32,  112,  113,   35,
 /*   650 */    36,  139,   38,  110,   40,  112,  113,   43,   44,   45,
 /*   660 */    46,   47,   48,   49,   50,  139,  100,  139,  139,  139,
 /*   670 */   139,  139,  139,  139,  100,   61,  110,   63,   64,   65,
 /*   680 */   139,   67,   68,   69,  110,    7,    8,    9,   10,   11,
 /*   690 */    12,   13,   14,   15,   16,   17,   18,   19,   20,   21,
 /*   700 */    22,  139,  100,  100,  100,  100,   28,  139,  139,  139,
 /*   710 */    32,   33,  110,  110,  110,  110,   38,  115,    7,    8,
 /*   720 */     9,   10,   11,   12,   13,   14,   15,   16,   17,   18,
 /*   730 */    19,   20,   21,   22,  100,  100,  139,  139,  139,   28,
 /*   740 */    18,   19,  100,   32,  110,  110,   24,   25,   26,   38,
 /*   750 */   139,  100,  110,  100,   32,  139,  139,  115,   36,  139,
 /*   760 */    38,  110,   40,  110,  139,   43,   44,   45,   46,   47,
 /*   770 */    48,   49,   50,  139,   13,   14,   15,   16,   17,   18,
 /*   780 */    19,   20,   21,   22,  139,  100,  100,    5,  100,   28,
 /*   790 */   139,  139,  100,   32,  100,  110,  110,  139,  110,   38,
 /*   800 */    18,   19,  110,  115,  110,  100,   24,   25,   26,  115,
 /*   810 */    49,   50,  139,  100,   32,  110,  139,  139,  139,  139,
 /*   820 */    38,  100,   40,  110,  139,   43,   44,   45,   46,   47,
 /*   830 */   139,  110,  100,   18,   19,  100,  115,  139,  139,   24,
 /*   840 */    25,   26,  110,  139,  100,  110,  139,   32,   33,  139,
 /*   850 */   139,  139,   70,   38,  110,   40,   41,  139,   43,   44,
 /*   860 */    45,   46,   47,  139,  139,  139,   18,   19,  100,  100,
 /*   870 */   139,  100,   24,   25,   26,  100,  139,  100,  110,  110,
 /*   880 */    32,  110,  139,  139,  139,  110,   38,  110,   40,  100,
 /*   890 */   139,   43,   44,   45,   46,   47,    1,   49,   50,  110,
 /*   900 */    13,   14,   15,   16,   17,   18,   19,   20,   21,   22,
 /*   910 */    18,   19,    1,    2,  139,   28,   24,   25,   26,   32,
 /*   920 */   139,  100,  139,  139,   32,   38,   39,  139,  139,  139,
 /*   930 */    38,  110,   40,   41,  100,   43,   44,   45,   46,   47,
 /*   940 */   139,  139,  139,   32,  110,  139,   51,   52,   53,   54,
 /*   950 */    55,   56,   57,   58,   59,   60,  139,  139,  139,  139,
 /*   960 */   139,  139,   51,   52,   53,   54,   55,   56,   57,   58,
 /*   970 */    59,   60,  139,  139,  139,  139,   13,   14,   15,   16,
 /*   980 */    17,   18,   19,   20,   21,   22,  100,  139,  100,  100,
 /*   990 */   139,   28,  139,  100,  139,   32,  110,  139,  110,  110,
 /*  1000 */    81,   38,  139,  110,  139,   13,   14,   15,   16,   17,
 /*  1010 */    18,   19,   20,   21,   22,  139,   97,   98,   99,  100,
 /*  1020 */    28,  139,  139,  139,   32,   18,   19,  139,  139,  110,
 /*  1030 */    38,   24,   25,   26,  139,  116,  117,  139,  139,   32,
 /*  1040 */   139,  139,  139,  139,  139,   38,  127,   40,  139,  139,
 /*  1050 */    43,   44,   45,   46,   47,  139,  139,  139,   18,   19,
 /*  1060 */   139,  139,  139,  139,   24,   25,   26,  139,  139,  139,
 /*  1070 */   139,  139,   32,  139,  139,  139,  139,  139,   38,  139,
 /*  1080 */    40,  139,  139,   43,   44,   45,   46,   47,   76,   77,
 /*  1090 */    78,   79,   80,   81,   82,   83,   84,  139,   86,  139,
 /*  1100 */   139,   89,   90,    1,    2,  139,   94,   14,   15,   16,
 /*  1110 */    17,   18,   19,   20,   21,   22,    1,    2,  139,  139,
 /*  1120 */   139,   28,  139,  139,  139,   32,   18,   19,   20,   21,
 /*  1130 */    22,   38,  139,  139,  139,  139,   28,  139,  139,  139,
 /*  1140 */    32,  139,  139,  139,  139,  139,   38,  139,  139,  139,
 /*  1150 */   139,  139,  139,   51,   52,   53,   54,   55,   56,   57,
 /*  1160 */    58,   59,   60,  139,  139,  139,   51,   52,   53,   54,
 /*  1170 */    55,   56,   57,   58,   59,   60,   16,   17,   18,   19,
 /*  1180 */    20,   21,   22,  139,   81,  139,  139,  139,   28,  139,
 /*  1190 */   139,  139,   32,    0,  139,  139,  139,  139,   38,  139,
 /*  1200 */    97,   98,   99,  100,  139,  139,  139,  139,  139,  139,
 /*  1210 */   139,  139,  139,  110,  139,  139,  139,  139,  139,  116,
 /*  1220 */   117,  139,   29,  139,   31,  139,  139,   34,   35,   36,
 /*  1230 */   127,  128,  139,  139,  139,  139,  139,  139,  139,  139,
 /*  1240 */   139,   48,
};
#define YY_SHIFT_USE_DFLT (-16)
#define YY_SHIFT_COUNT (235)
#define YY_SHIFT_MIN   (-15)
#define YY_SHIFT_MAX   (1193)
static const short yy_shift_ofst[] = {
 /*     0 */   -16,  552,  490,  614,  614,  614,  614,  614,  614,  614,
 /*    10 */  1193,  722,  722,  848,  848,  815,  892,  892,  892,  892,
 /*    20 */  1007, 1007,  782,  782,  782,  782,  782,  782,  782,  782,
 /*    30 */   782,  892, 1007, 1007, 1007, 1007, 1040, 1007, 1007, 1007,
 /*    40 */   563, 1007, 1007, 1007, 1007, 1007, 1007, 1007, 1007, 1007,
 /*    50 */  1007, 1007, 1007, 1007, 1007, 1007, 1007, 1007, 1007, 1007,
 /*    60 */  1007, 1007, 1007, 1007, 1007, 1007, 1007, 1007, 1007, 1007,
 /*    70 */  1007, 1007, 1007, 1007, 1007, 1007, 1007,  509,  537,  537,
 /*    80 */   537,  537,  509,  509,  537,  537,  537,  559,  499,  465,
 /*    90 */   465,  461,  678,  711,  761,  887,  590,  528,  963,  963,
 /*   100 */   992,  963,  963,  963,  963,  963,  963,  963,  963,  963,
 /*   110 */   963,  963,  963,  963,  963,  963,  963,  963,  963,  963,
 /*   120 */   963,  911, 1115, 1102, 1093,  895,  -14, 1160, 1108, 1108,
 /*   130 */   491,  491,   70,  258,  212,  202,  176,  101,  -15,  -15,
 /*   140 */   -15,  -15,  -15,  -15,  183,  166,  181,  116,  148,  124,
 /*   150 */   146,   35,    9,   96,   90,   41,   21,  317,  317,  446,
 /*   160 */   454,  431,  433,  430,  427,  426,  424,  453,  404,  428,
 /*   170 */   414,  413,  411,  343,  395,  317,  317,  317,  399,  391,
 /*   180 */   378,  366,  374,  371,  398,  365,  357,  335,  338,  342,
 /*   190 */   331,  337,  324,  307,  320,  311,  306,  303,  332,  300,
 /*   200 */   288,  317,  277,  289,  226,  275,  263,  269,  262,  249,
 /*   210 */   252,  251,  232,  226,  239,  221,  231,  219,  214,  206,
 /*   220 */   197,  194,  162,  149,  143,  152,   97,   77,   62,   66,
 /*   230 */    52,   46,   38,   31,   -8,  -12,
};
#define YY_REDUCE_USE_DFLT (-81)
#define YY_REDUCE_COUNT (91)
#define YY_REDUCE_MIN   (-80)
#define YY_REDUCE_MAX   (1103)
static const short yy_reduce_ofst[] = {
 /*     0 */   128,  372,  316,  261,  205,  150,   94,   39,  -17,  -72,
 /*    10 */  1012, 1103,  919,  -60,   -4,  543,  535,  514,  473,  452,
 /*    20 */    51,   19,  721,  694,  688,  642,  602,  385,  384,  291,
 /*    30 */   274,  180,  352,  328,  273,  241,  107,  217,  163,  130,
 /*    40 */   -80,  893,  889,  888,  886,  834,  821,  789,  777,  775,
 /*    50 */   771,  769,  768,  744,  735,  732,  713,  705,  692,  686,
 /*    60 */   685,  653,  651,  635,  634,  605,  604,  603,  574,  566,
 /*    70 */   534,  472,  421,  383,  329,  246,  218,  100,  209,  503,
 /*    80 */   502,  500,  445,  439,  483,  478,  477,  418,  412,  423,
 /*    90 */   406,  401,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   344,  518,  518,  518,  518,  518,  518,  518,  518,  518,
 /*    10 */   521,  497,  521,  500,  521,  521,  414,  414,  414,  414,
 /*    20 */   403,  403,  521,  521,  521,  521,  521,  521,  521,  521,
 /*    30 */   521,  521,  521,  521,  521,  521,  521,  521,  521,  521,
 /*    40 */   485,  521,  521,  521,  521,  521,  521,  521,  521,  521,
 /*    50 */   521,  521,  521,  521,  521,  521,  521,  521,  521,  521,
 /*    60 */   521,  521,  521,  521,  521,  521,  521,  521,  521,  521,
 /*    70 */   521,  521,  521,  521,  521,  521,  521,  521,  397,  521,
 /*    80 */   521,  521,  520,  519,  521,  521,  521,  421,  521,  521,
 /*    90 */   521,  521,  441,  441,  521,  521,  521,  521,  466,  464,
 /*   100 */   521,  477,  476,  475,  474,  473,  472,  471,  470,  469,
 /*   110 */   468,  462,  448,  447,  446,  445,  444,  443,  401,  410,
 /*   120 */   412,  407,  409,  408,  436,  460,  437,  435,  434,  433,
 /*   130 */   429,  428,  521,  521,  521,  521,  521,  521,  440,  439,
 /*   140 */   438,  432,  431,  430,  521,  452,  521,  521,  521,  521,
 /*   150 */   521,  521,  452,  521,  407,  418,  357,  456,  454,  521,
 /*   160 */   521,  389,  521,  521,  521,  521,  521,  501,  521,  496,
 /*   170 */   521,  521,  521,  484,  521,  463,  455,  453,  521,  521,
 /*   180 */   521,  521,  521,  521,  450,  521,  521,  521,  521,  521,
 /*   190 */   521,  521,  521,  521,  521,  521,  521,  521,  415,  406,
 /*   200 */   521,  404,  521,  521,  393,  521,  418,  521,  407,  418,
 /*   210 */   521,  521,  521,  521,  521,  521,  521,  521,  521,  521,
 /*   220 */   521,  521,  521,  521,  521,  398,  358,  521,  521,  521,
 /*   230 */   521,  521,  521,  521,  521,  521,  364,  363,  362,  361,
 /*   240 */   390,  374,  486,  517,  516,  515,  511,  510,  509,  508,
 /*   250 */   507,  506,  505,  504,  499,  498,  503,  502,  495,  494,
 /*   260 */   493,  492,  491,  490,  489,  488,  487,  483,  482,  481,
 /*   270 */   480,  479,  478,  461,  467,  465,  416,  417,  422,  420,
 /*   280 */   423,  514,  512,  451,  449,  442,  513,  427,  426,  425,
 /*   290 */   424,  413,  411,  402,  399,  394,  419,  409,  408,  406,
 /*   300 */   405,  392,  391,  388,  387,  386,  385,  384,  383,  382,
 /*   310 */   400,  381,  380,  379,  378,  377,  376,  375,  373,  372,
 /*   320 */   371,  369,  370,  368,  367,  366,  365,  359,  396,  395,
 /*   330 */   360,  356,  355,  354,  353,  352,  351,  350,  349,  348,
 /*   340 */   347,  346,  345,
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
  "PERIOD",        "IMPORT",        "AS",            "FUNCTION",    
  "LPAREN",        "RPAREN",        "OBJECT",        "LBRACKET",    
  "VAR",           "RBRACKET",      "LSQBRACKET",    "RSQBRACKET",  
  "KILLS",         "STRING",        "FUNCCALL",      "L2V",         
  "MAPSTRING",     "UNIT",          "SWITCH",        "LOCATION",    
  "CONST",         "INC",           "DEC",           "IADD",        
  "ISUB",          "IMUL",          "IDIV",          "IMOD",        
  "ILSH",          "IRSH",          "IBND",          "IBOR",        
  "IBXR",          "IF",            "ELSE",          "WHILE",       
  "FOR",           "FOREACH",       "COLON",         "CONTINUE",    
  "BREAK",         "RETURN",        "CONDITIONNAME",  "ACTIONNAME",  
  "error",         "nt",            "program",       "chunks",      
  "chunk",         "import_chunk",  "fdef_chunk",    "fdecl_chunk", 
  "object_chunk",  "vdef_stmt",     "vdefAssign_global_stmt",  "cdef_global_stmt",
  "blockStmt",     "dottedName",    "fdef_header",   "nameList",    
  "stmt",          "object_header",  "object_body",   "nameList_nonEmpty",
  "bodyStmt",      "return_stmt",   "lbracket",      "rbracket",    
  "bodyStmtList",  "vdefAssign_stmt",  "cdef_stmt",     "assign_stmt", 
  "funcexpr",      "actionStmt",    "if_stmt",       "while_stmt",  
  "for_stmt",      "foreach_stmt",  "continue_stmt",  "break_stmt",  
  "numList_nonEmpty",  "exprList_nonEmpty",  "expr",          "exprList",    
  "fArgs_nonEmpty",  "fArgs",         "commaSkippable",  "lexpr",       
  "lvalue",        "lvalueList_nonEmpty",  "if_start",      "if_header",   
  "if_block",      "elif_start",    "elif_header",   "else_header", 
  "while_start",   "while_header",  "for_opener",    "for_init_stmt_nonEmpty",
  "for_init_stmt",  "for_action_stmt_nonEmpty",  "for_action_stmt",  "for_header1", 
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
 /*   6 */ "chunk ::= object_chunk",
 /*   7 */ "chunk ::= vdef_stmt SEMICOLON",
 /*   8 */ "chunk ::= vdefAssign_global_stmt SEMICOLON",
 /*   9 */ "chunk ::= cdef_global_stmt SEMICOLON",
 /*  10 */ "chunk ::= blockStmt",
 /*  11 */ "dottedName ::= NAME",
 /*  12 */ "dottedName ::= dottedName PERIOD NAME",
 /*  13 */ "import_chunk ::= IMPORT dottedName AS NAME",
 /*  14 */ "import_chunk ::= IMPORT dottedName",
 /*  15 */ "fdef_header ::= FUNCTION NAME LPAREN nameList RPAREN",
 /*  16 */ "fdef_chunk ::= fdef_header stmt",
 /*  17 */ "fdecl_chunk ::= FUNCTION NAME LPAREN nameList RPAREN SEMICOLON",
 /*  18 */ "object_header ::= OBJECT NAME LBRACKET",
 /*  19 */ "object_body ::= object_header",
 /*  20 */ "object_body ::= object_body VAR nameList_nonEmpty SEMICOLON",
 /*  21 */ "object_chunk ::= object_body RBRACKET",
 /*  22 */ "stmt ::= error SEMICOLON",
 /*  23 */ "stmt ::= bodyStmt",
 /*  24 */ "stmt ::= return_stmt SEMICOLON",
 /*  25 */ "lbracket ::= LBRACKET",
 /*  26 */ "rbracket ::= RBRACKET",
 /*  27 */ "blockStmt ::= lbracket RBRACKET",
 /*  28 */ "blockStmt ::= lbracket return_stmt SEMICOLON rbracket",
 /*  29 */ "blockStmt ::= lbracket bodyStmtList rbracket",
 /*  30 */ "blockStmt ::= lbracket bodyStmtList return_stmt SEMICOLON rbracket",
 /*  31 */ "blockStmt ::= lbracket error RBRACKET",
 /*  32 */ "bodyStmt ::= blockStmt",
 /*  33 */ "bodyStmt ::= SEMICOLON",
 /*  34 */ "bodyStmt ::= vdef_stmt SEMICOLON",
 /*  35 */ "bodyStmt ::= vdefAssign_stmt SEMICOLON",
 /*  36 */ "bodyStmt ::= cdef_stmt SEMICOLON",
 /*  37 */ "bodyStmt ::= assign_stmt SEMICOLON",
 /*  38 */ "bodyStmt ::= funcexpr SEMICOLON",
 /*  39 */ "bodyStmt ::= actionStmt",
 /*  40 */ "bodyStmt ::= if_stmt",
 /*  41 */ "bodyStmt ::= while_stmt",
 /*  42 */ "bodyStmt ::= for_stmt",
 /*  43 */ "bodyStmt ::= foreach_stmt",
 /*  44 */ "bodyStmt ::= continue_stmt SEMICOLON",
 /*  45 */ "bodyStmt ::= break_stmt SEMICOLON",
 /*  46 */ "bodyStmtList ::= error",
 /*  47 */ "bodyStmtList ::= bodyStmt",
 /*  48 */ "bodyStmtList ::= bodyStmtList bodyStmt",
 /*  49 */ "bodyStmtList ::= bodyStmtList error",
 /*  50 */ "numList_nonEmpty ::= NUMBER",
 /*  51 */ "numList_nonEmpty ::= numList_nonEmpty COMMA NUMBER",
 /*  52 */ "nameList_nonEmpty ::= NAME",
 /*  53 */ "nameList_nonEmpty ::= nameList_nonEmpty COMMA NAME",
 /*  54 */ "nameList ::=",
 /*  55 */ "nameList ::= nameList_nonEmpty",
 /*  56 */ "exprList_nonEmpty ::= funcexpr LSQBRACKET LSQBRACKET numList_nonEmpty RSQBRACKET RSQBRACKET",
 /*  57 */ "expr ::= funcexpr LSQBRACKET LSQBRACKET NUMBER RSQBRACKET RSQBRACKET",
 /*  58 */ "exprList_nonEmpty ::= expr",
 /*  59 */ "exprList_nonEmpty ::= exprList_nonEmpty COMMA exprList_nonEmpty",
 /*  60 */ "exprList ::=",
 /*  61 */ "exprList ::= exprList_nonEmpty",
 /*  62 */ "expr ::= NUMBER",
 /*  63 */ "expr ::= KILLS",
 /*  64 */ "expr ::= NAME",
 /*  65 */ "expr ::= expr PERIOD NAME",
 /*  66 */ "expr ::= expr LSQBRACKET expr RSQBRACKET",
 /*  67 */ "fArgs_nonEmpty ::= expr",
 /*  68 */ "fArgs_nonEmpty ::= STRING",
 /*  69 */ "fArgs_nonEmpty ::= NAME ASSIGN expr",
 /*  70 */ "fArgs_nonEmpty ::= fArgs_nonEmpty COMMA fArgs_nonEmpty",
 /*  71 */ "fArgs ::=",
 /*  72 */ "fArgs ::= fArgs_nonEmpty",
 /*  73 */ "funcexpr ::= NAME LPAREN fArgs RPAREN",
 /*  74 */ "funcexpr ::= expr LPAREN fArgs RPAREN",
 /*  75 */ "expr ::= funcexpr",
 /*  76 */ "expr ::= LPAREN expr RPAREN",
 /*  77 */ "commaSkippable ::= COMMA",
 /*  78 */ "commaSkippable ::=",
 /*  79 */ "expr ::= LSQBRACKET exprList commaSkippable RSQBRACKET",
 /*  80 */ "expr ::= L2V LPAREN lexpr RPAREN",
 /*  81 */ "expr ::= MAPSTRING LPAREN STRING RPAREN",
 /*  82 */ "expr ::= UNIT LPAREN STRING RPAREN",
 /*  83 */ "expr ::= SWITCH LPAREN STRING RPAREN",
 /*  84 */ "expr ::= LOCATION LPAREN STRING RPAREN",
 /*  85 */ "expr ::= expr PLUS expr",
 /*  86 */ "expr ::= expr MINUS expr",
 /*  87 */ "expr ::= expr MULTIPLY expr",
 /*  88 */ "expr ::= expr DIVIDE expr",
 /*  89 */ "expr ::= expr MOD expr",
 /*  90 */ "expr ::= expr LSHIFT expr",
 /*  91 */ "expr ::= expr RSHIFT expr",
 /*  92 */ "expr ::= expr BITAND expr",
 /*  93 */ "expr ::= expr BITOR expr",
 /*  94 */ "expr ::= expr BITXOR expr",
 /*  95 */ "expr ::= PLUS expr",
 /*  96 */ "expr ::= MINUS expr",
 /*  97 */ "expr ::= BITNOT expr",
 /*  98 */ "lexpr ::= expr",
 /*  99 */ "lexpr ::= LPAREN lexpr RPAREN",
 /* 100 */ "lexpr ::= expr EQ expr",
 /* 101 */ "lexpr ::= expr NE expr",
 /* 102 */ "lexpr ::= expr LE expr",
 /* 103 */ "lexpr ::= expr LT expr",
 /* 104 */ "lexpr ::= expr GE expr",
 /* 105 */ "lexpr ::= expr GT expr",
 /* 106 */ "lexpr ::= lexpr LAND lexpr",
 /* 107 */ "lexpr ::= lexpr LOR lexpr",
 /* 108 */ "lexpr ::= LNOT lexpr",
 /* 109 */ "vdef_stmt ::= VAR nameList_nonEmpty",
 /* 110 */ "vdefAssign_stmt ::= VAR nameList_nonEmpty ASSIGN exprList_nonEmpty",
 /* 111 */ "vdefAssign_global_stmt ::= VAR nameList_nonEmpty ASSIGN exprList_nonEmpty",
 /* 112 */ "cdef_stmt ::= CONST nameList_nonEmpty ASSIGN exprList_nonEmpty",
 /* 113 */ "cdef_global_stmt ::= CONST nameList_nonEmpty ASSIGN exprList_nonEmpty",
 /* 114 */ "lvalue ::= NAME",
 /* 115 */ "lvalue ::= expr LSQBRACKET expr RSQBRACKET",
 /* 116 */ "lvalue ::= expr PERIOD NAME",
 /* 117 */ "lvalueList_nonEmpty ::= lvalue",
 /* 118 */ "lvalueList_nonEmpty ::= lvalueList_nonEmpty COMMA lvalue",
 /* 119 */ "assign_stmt ::= lvalue ASSIGN expr",
 /* 120 */ "assign_stmt ::= lvalueList_nonEmpty ASSIGN exprList_nonEmpty",
 /* 121 */ "assign_stmt ::= INC expr",
 /* 122 */ "assign_stmt ::= expr INC",
 /* 123 */ "assign_stmt ::= DEC expr",
 /* 124 */ "assign_stmt ::= expr DEC",
 /* 125 */ "assign_stmt ::= lvalue IADD expr",
 /* 126 */ "assign_stmt ::= lvalue ISUB expr",
 /* 127 */ "assign_stmt ::= lvalue IMUL expr",
 /* 128 */ "assign_stmt ::= lvalue IDIV expr",
 /* 129 */ "assign_stmt ::= lvalue IMOD expr",
 /* 130 */ "assign_stmt ::= lvalue ILSH expr",
 /* 131 */ "assign_stmt ::= lvalue IRSH expr",
 /* 132 */ "assign_stmt ::= lvalue IBND expr",
 /* 133 */ "assign_stmt ::= lvalue IBOR expr",
 /* 134 */ "assign_stmt ::= lvalue IBXR expr",
 /* 135 */ "if_start ::= IF",
 /* 136 */ "if_header ::= if_start LPAREN lexpr RPAREN",
 /* 137 */ "if_block ::= if_header stmt",
 /* 138 */ "elif_start ::= ELSE IF",
 /* 139 */ "elif_header ::= elif_start LPAREN lexpr RPAREN",
 /* 140 */ "if_block ::= if_block elif_header stmt",
 /* 141 */ "else_header ::= ELSE",
 /* 142 */ "if_stmt ::= if_block",
 /* 143 */ "if_stmt ::= if_block else_header stmt",
 /* 144 */ "while_start ::= WHILE",
 /* 145 */ "while_header ::= while_start LPAREN lexpr RPAREN",
 /* 146 */ "while_stmt ::= while_header stmt",
 /* 147 */ "for_opener ::= FOR LPAREN",
 /* 148 */ "for_init_stmt_nonEmpty ::= vdef_stmt",
 /* 149 */ "for_init_stmt_nonEmpty ::= vdefAssign_stmt",
 /* 150 */ "for_init_stmt_nonEmpty ::= cdef_stmt",
 /* 151 */ "for_init_stmt_nonEmpty ::= assign_stmt",
 /* 152 */ "for_init_stmt_nonEmpty ::= for_init_stmt_nonEmpty COMMA for_init_stmt_nonEmpty",
 /* 153 */ "for_init_stmt ::= for_init_stmt_nonEmpty",
 /* 154 */ "for_init_stmt ::=",
 /* 155 */ "for_action_stmt_nonEmpty ::= assign_stmt",
 /* 156 */ "for_action_stmt_nonEmpty ::= for_action_stmt_nonEmpty COMMA for_action_stmt_nonEmpty",
 /* 157 */ "for_action_stmt ::=",
 /* 158 */ "for_action_stmt ::= for_action_stmt_nonEmpty",
 /* 159 */ "for_header1 ::= for_opener for_init_stmt SEMICOLON",
 /* 160 */ "for_header2 ::= for_header1 lexpr SEMICOLON",
 /* 161 */ "for_header ::= for_header2 for_action_stmt RPAREN",
 /* 162 */ "for_stmt ::= for_header stmt",
 /* 163 */ "foreach_opener ::= FOREACH LPAREN",
 /* 164 */ "foreach_header ::= foreach_opener nameList_nonEmpty COLON exprList_nonEmpty RPAREN",
 /* 165 */ "foreach_stmt ::= foreach_header stmt",
 /* 166 */ "continue_stmt ::= CONTINUE",
 /* 167 */ "break_stmt ::= BREAK",
 /* 168 */ "return_stmt ::= RETURN exprList",
 /* 169 */ "lexpr ::= CONDITIONNAME LPAREN fArgs RPAREN",
 /* 170 */ "lexpr ::= KILLS LPAREN fArgs RPAREN",
 /* 171 */ "lexpr ::= CONDITIONNAME LPAREN RPAREN",
 /* 172 */ "action ::= ACTIONNAME LPAREN fArgs RPAREN SEMICOLON",
 /* 173 */ "actions ::= action action",
 /* 174 */ "actions ::= actions action",
 /* 175 */ "actionStmt_start ::=",
 /* 176 */ "actionStmt ::= actionStmt_start action",
 /* 177 */ "actionStmt ::= actionStmt_start actions",
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
    case 73: /* nt */
{
#line 39 "parser\\epparser.lemon"
 delete (yypminor->yy0); 
#line 906 "parser\\epparser.c"
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
  { 74, 1 },
  { 75, 0 },
  { 75, 2 },
  { 76, 2 },
  { 76, 1 },
  { 76, 1 },
  { 76, 1 },
  { 76, 2 },
  { 76, 2 },
  { 76, 2 },
  { 76, 1 },
  { 85, 1 },
  { 85, 3 },
  { 77, 4 },
  { 77, 2 },
  { 86, 5 },
  { 78, 2 },
  { 79, 6 },
  { 89, 3 },
  { 90, 1 },
  { 90, 4 },
  { 80, 2 },
  { 88, 2 },
  { 88, 1 },
  { 88, 2 },
  { 94, 1 },
  { 95, 1 },
  { 84, 2 },
  { 84, 4 },
  { 84, 3 },
  { 84, 5 },
  { 84, 3 },
  { 92, 1 },
  { 92, 1 },
  { 92, 2 },
  { 92, 2 },
  { 92, 2 },
  { 92, 2 },
  { 92, 2 },
  { 92, 1 },
  { 92, 1 },
  { 92, 1 },
  { 92, 1 },
  { 92, 1 },
  { 92, 2 },
  { 92, 2 },
  { 96, 1 },
  { 96, 1 },
  { 96, 2 },
  { 96, 2 },
  { 108, 1 },
  { 108, 3 },
  { 91, 1 },
  { 91, 3 },
  { 87, 0 },
  { 87, 1 },
  { 109, 6 },
  { 110, 6 },
  { 109, 1 },
  { 109, 3 },
  { 111, 0 },
  { 111, 1 },
  { 110, 1 },
  { 110, 1 },
  { 110, 1 },
  { 110, 3 },
  { 110, 4 },
  { 112, 1 },
  { 112, 1 },
  { 112, 3 },
  { 112, 3 },
  { 113, 0 },
  { 113, 1 },
  { 100, 4 },
  { 100, 4 },
  { 110, 1 },
  { 110, 3 },
  { 114, 1 },
  { 114, 0 },
  { 110, 4 },
  { 110, 4 },
  { 110, 4 },
  { 110, 4 },
  { 110, 4 },
  { 110, 4 },
  { 110, 3 },
  { 110, 3 },
  { 110, 3 },
  { 110, 3 },
  { 110, 3 },
  { 110, 3 },
  { 110, 3 },
  { 110, 3 },
  { 110, 3 },
  { 110, 3 },
  { 110, 2 },
  { 110, 2 },
  { 110, 2 },
  { 115, 1 },
  { 115, 3 },
  { 115, 3 },
  { 115, 3 },
  { 115, 3 },
  { 115, 3 },
  { 115, 3 },
  { 115, 3 },
  { 115, 3 },
  { 115, 3 },
  { 115, 2 },
  { 81, 2 },
  { 97, 4 },
  { 82, 4 },
  { 98, 4 },
  { 83, 4 },
  { 116, 1 },
  { 116, 4 },
  { 116, 3 },
  { 117, 1 },
  { 117, 3 },
  { 99, 3 },
  { 99, 3 },
  { 99, 2 },
  { 99, 2 },
  { 99, 2 },
  { 99, 2 },
  { 99, 3 },
  { 99, 3 },
  { 99, 3 },
  { 99, 3 },
  { 99, 3 },
  { 99, 3 },
  { 99, 3 },
  { 99, 3 },
  { 99, 3 },
  { 99, 3 },
  { 118, 1 },
  { 119, 4 },
  { 120, 2 },
  { 121, 2 },
  { 122, 4 },
  { 120, 3 },
  { 123, 1 },
  { 102, 1 },
  { 102, 3 },
  { 124, 1 },
  { 125, 4 },
  { 103, 2 },
  { 126, 2 },
  { 127, 1 },
  { 127, 1 },
  { 127, 1 },
  { 127, 1 },
  { 127, 3 },
  { 128, 1 },
  { 128, 0 },
  { 129, 1 },
  { 129, 3 },
  { 130, 0 },
  { 130, 1 },
  { 131, 3 },
  { 132, 3 },
  { 133, 3 },
  { 104, 2 },
  { 134, 2 },
  { 135, 5 },
  { 105, 2 },
  { 106, 1 },
  { 107, 1 },
  { 93, 2 },
  { 115, 4 },
  { 115, 4 },
  { 115, 3 },
  { 136, 5 },
  { 137, 2 },
  { 137, 2 },
  { 138, 0 },
  { 101, 2 },
  { 101, 2 },
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
      case 10: /* chunk ::= blockStmt */
#line 75 "parser\\epparser.lemon"
{
    throw_error(48993, "Misplaced block statement");
}
#line 1381 "parser\\epparser.c"
        break;
      case 11: /* dottedName ::= NAME */
      case 50: /* numList_nonEmpty ::= NUMBER */ yytestcase(yyruleno==50);
      case 52: /* nameList_nonEmpty ::= NAME */ yytestcase(yyruleno==52);
      case 55: /* nameList ::= nameList_nonEmpty */ yytestcase(yyruleno==55);
      case 58: /* exprList_nonEmpty ::= expr */ yytestcase(yyruleno==58);
      case 61: /* exprList ::= exprList_nonEmpty */ yytestcase(yyruleno==61);
      case 62: /* expr ::= NUMBER */ yytestcase(yyruleno==62);
      case 67: /* fArgs_nonEmpty ::= expr */ yytestcase(yyruleno==67);
      case 68: /* fArgs_nonEmpty ::= STRING */ yytestcase(yyruleno==68);
      case 72: /* fArgs ::= fArgs_nonEmpty */ yytestcase(yyruleno==72);
      case 75: /* expr ::= funcexpr */ yytestcase(yyruleno==75);
      case 98: /* lexpr ::= expr */ yytestcase(yyruleno==98);
      case 117: /* lvalueList_nonEmpty ::= lvalue */ yytestcase(yyruleno==117);
#line 81 "parser\\epparser.lemon"
{ yygotominor.yy0 = yymsp[0].minor.yy0; }
#line 1398 "parser\\epparser.c"
        break;
      case 12: /* dottedName ::= dottedName PERIOD NAME */
#line 82 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = yymsp[-2].minor.yy0->data + "." + yymsp[0].minor.yy0->data;
    delete yymsp[-2].minor.yy0;
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1407 "parser\\epparser.c"
        break;
      case 13: /* import_chunk ::= IMPORT dottedName AS NAME */
#line 88 "parser\\epparser.lemon"
{
    std::string impPath, impModname;
    impPathProcess(yymsp[-2].minor.yy0->data, impPath, impModname);

    if(!ps->closure.defModule(yymsp[0].minor.yy0->data)) {
        throw_error(6754, "Importing already-declared module " + yymsp[0].minor.yy0->data, yymsp[0].minor.yy0->line);
    }

    if(!impPath.empty()) ps->gen << "from " << impPath << " ";
    ps->gen << "import " << impModname << " as " << yymsp[0].minor.yy0->data << std::endl;
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 1423 "parser\\epparser.c"
        break;
      case 14: /* import_chunk ::= IMPORT dottedName */
#line 101 "parser\\epparser.lemon"
{
    std::string impPath, impModname;
    impPathProcess(yymsp[0].minor.yy0->data, impPath, impModname);

    if(!ps->closure.defModule(impModname)) {
        throw_error(6754, "Importing already-declared module " + impModname, yymsp[0].minor.yy0->line);
    }

    if(!impPath.empty()) ps->gen << "from " << impPath << " ";
    ps->gen << "import " << impModname << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1439 "parser\\epparser.c"
        break;
      case 15: /* fdef_header ::= FUNCTION NAME LPAREN nameList RPAREN */
#line 115 "parser\\epparser.lemon"
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
    currentFunction = yymsp[-3].minor.yy0->data;

    if(MAP_DEBUG) {
         ps->gen << "MDBG_PUSHF(\'" << currentFunction << "\', \'" << currentModule << "\')" << std::endl;
    }

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
#line 1472 "parser\\epparser.c"
        break;
      case 16: /* fdef_chunk ::= fdef_header stmt */
#line 145 "parser\\epparser.lemon"
{
    if(MAP_DEBUG){
        ps->gen << "MDBG_POPF()" << std::endl;
    }
    ps->gen.unindent(true);
    ps->closure.popScope();
    currentFunction = "";
}
#line 1484 "parser\\epparser.c"
        break;
      case 17: /* fdecl_chunk ::= FUNCTION NAME LPAREN nameList RPAREN SEMICOLON */
#line 154 "parser\\epparser.lemon"
{
    // Preprocess yymsp[-4].minor.yy0
    funcNamePreprocess(yymsp[-4].minor.yy0->data);
    if(!ps->closure.declareFunction(yymsp[-4].minor.yy0->data)) {
        throw_error(72461, "Declaring function with non-function yymsp[-4].minor.yy0 " + yymsp[-4].minor.yy0->data, yymsp[-4].minor.yy0->line);
    }
}
#line 1495 "parser\\epparser.c"
        break;
      case 18: /* object_header ::= OBJECT NAME LBRACKET */
#line 165 "parser\\epparser.lemon"
{
    ps->gen << "class " << yymsp[-1].minor.yy0->data << "(EUDStruct):\n";
    ps->gen.indent();

    funcNamePreprocess(yymsp[-1].minor.yy0->data);
    if(!ps->closure.declareFunction(yymsp[-1].minor.yy0->data)) {
        throw_error(72461, "Declaring function with non-function yymsp[-1].minor.yy0 " + yymsp[-1].minor.yy0->data, yymsp[-1].minor.yy0->line);
    }
    ps->closure.pushScope();

    yygotominor.yy0 = yymsp[-2].minor.yy0;
    yygotominor.yy0->data = yymsp[-1].minor.yy0->data;  // Add object yymsp[-1].minor.yy0
    delete yymsp[-1].minor.yy0;
}
#line 1513 "parser\\epparser.c"
        break;
      case 19: /* object_body ::= object_header */
#line 180 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1520 "parser\\epparser.c"
        break;
      case 20: /* object_body ::= object_body VAR nameList_nonEmpty SEMICOLON */
#line 184 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-3].minor.yy0;
    yygotominor.yy0->line = yymsp[-1].minor.yy0->line;
    yygotominor.yy0->data += ", " + yymsp[-1].minor.yy0->data;
    delete yymsp[-1].minor.yy0;
}
#line 1530 "parser\\epparser.c"
        break;
      case 21: /* object_chunk ::= object_body RBRACKET */
#line 191 "parser\\epparser.lemon"
{
    ps->gen << "_fields_ = [";
    bool isFirst = true;
    commaListIter(yymsp[-1].minor.yy0->data, [&](std::string& varname) {
        if (isFirst) {
            isFirst = false;
            return;
        }
        ps->gen << "'" << varname << "', ";
    });
    ps->gen << "]\n";
    ps->gen.unindent(true);
    ps->closure.popScope();
    delete yymsp[-1].minor.yy0;
}
#line 1549 "parser\\epparser.c"
        break;
      case 22: /* stmt ::= error SEMICOLON */
#line 208 "parser\\epparser.lemon"
{ throw_error(6974, "Error while parsing statement", yymsp[0].minor.yy0->line); delete yymsp[0].minor.yy0; }
#line 1554 "parser\\epparser.c"
        break;
      case 25: /* lbracket ::= LBRACKET */
#line 214 "parser\\epparser.lemon"
{ ps->closure.pushScope(); }
#line 1559 "parser\\epparser.c"
        break;
      case 26: /* rbracket ::= RBRACKET */
#line 215 "parser\\epparser.lemon"
{ ps->closure.popScope(); }
#line 1564 "parser\\epparser.c"
        break;
      case 27: /* blockStmt ::= lbracket RBRACKET */
#line 217 "parser\\epparser.lemon"
{
    ps->closure.popScope();
}
#line 1571 "parser\\epparser.c"
        break;
      case 31: /* blockStmt ::= lbracket error RBRACKET */
#line 223 "parser\\epparser.lemon"
{
    throw_error(6298, "Block not terminated properly.", yymsp[0].minor.yy0->line);
    ps->closure.popScope();
    delete yymsp[0].minor.yy0;
}
#line 1580 "parser\\epparser.c"
        break;
      case 38: /* bodyStmt ::= funcexpr SEMICOLON */
#line 235 "parser\\epparser.lemon"
{ ps->gen << yymsp[-1].minor.yy0->data << std::endl; }
#line 1585 "parser\\epparser.c"
        break;
      case 46: /* bodyStmtList ::= error */
      case 49: /* bodyStmtList ::= bodyStmtList error */ yytestcase(yyruleno==49);
#line 245 "parser\\epparser.lemon"
{
    throw_error(8510, "Incomplete statement");
}
#line 1593 "parser\\epparser.c"
        break;
      case 51: /* numList_nonEmpty ::= numList_nonEmpty COMMA NUMBER */
      case 53: /* nameList_nonEmpty ::= nameList_nonEmpty COMMA NAME */ yytestcase(yyruleno==53);
      case 118: /* lvalueList_nonEmpty ::= lvalueList_nonEmpty COMMA lvalue */ yytestcase(yyruleno==118);
#line 258 "parser\\epparser.lemon"
{ yygotominor.yy0 = commaConcat(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1600 "parser\\epparser.c"
        break;
      case 54: /* nameList ::= */
      case 60: /* exprList ::= */ yytestcase(yyruleno==60);
      case 71: /* fArgs ::= */ yytestcase(yyruleno==71);
#line 261 "parser\\epparser.lemon"
{ yygotominor.yy0 = genEmpty(); }
#line 1607 "parser\\epparser.c"
        break;
      case 56: /* exprList_nonEmpty ::= funcexpr LSQBRACKET LSQBRACKET numList_nonEmpty RSQBRACKET RSQBRACKET */
#line 264 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "_SRET(" + yymsp[-5].minor.yy0->data + ", [" + yymsp[-2].minor.yy0->data + "])";
    delete yymsp[-5].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1616 "parser\\epparser.c"
        break;
      case 57: /* expr ::= funcexpr LSQBRACKET LSQBRACKET NUMBER RSQBRACKET RSQBRACKET */
#line 271 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-5].minor.yy0->data + "[" + yymsp[-2].minor.yy0->data + "]";
    delete yymsp[-5].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1625 "parser\\epparser.c"
        break;
      case 59: /* exprList_nonEmpty ::= exprList_nonEmpty COMMA exprList_nonEmpty */
#line 279 "parser\\epparser.lemon"
{ yygotominor.yy0 = new Token((yymsp[-2].minor.yy0->data) + ", " + (yymsp[0].minor.yy0->data), yymsp[0].minor.yy0); delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1630 "parser\\epparser.c"
        break;
      case 63: /* expr ::= KILLS */
#line 286 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = "4";
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1638 "parser\\epparser.c"
        break;
      case 64: /* expr ::= NAME */
#line 291 "parser\\epparser.lemon"
{
    checkIsRValue(yymsp[0].minor.yy0->data, yymsp[0].minor.yy0->line);
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1646 "parser\\epparser.c"
        break;
      case 65: /* expr ::= expr PERIOD NAME */
#line 296 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + "." + yymsp[0].minor.yy0->data;
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1655 "parser\\epparser.c"
        break;
      case 66: /* expr ::= expr LSQBRACKET expr RSQBRACKET */
#line 302 "parser\\epparser.lemon"
{
    yymsp[-3].minor.yy0->data = yymsp[-3].minor.yy0->data + "[" + yymsp[-1].minor.yy0->data + "]";
    delete yymsp[-1].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 1664 "parser\\epparser.c"
        break;
      case 69: /* fArgs_nonEmpty ::= NAME ASSIGN expr */
#line 311 "parser\\epparser.lemon"
{  // Keyword argument
    yymsp[0].minor.yy0->data = yymsp[-2].minor.yy0->data + "=" + yymsp[0].minor.yy0->data;
    yymsp[0].minor.yy0->type = TOKEN_TEMP;
    yygotominor.yy0 = yymsp[0].minor.yy0;
    delete yymsp[-2].minor.yy0;
}
#line 1674 "parser\\epparser.c"
        break;
      case 70: /* fArgs_nonEmpty ::= fArgs_nonEmpty COMMA fArgs_nonEmpty */
#line 318 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data;
    yymsp[0].minor.yy0->type = TOKEN_TEMP;
    yygotominor.yy0 = yymsp[0].minor.yy0;
    delete yymsp[-2].minor.yy0;
}
#line 1684 "parser\\epparser.c"
        break;
      case 73: /* funcexpr ::= NAME LPAREN fArgs RPAREN */
#line 328 "parser\\epparser.lemon"
{
    functionCalledInMultipleActions = true;

    // Preprocess yymsp[-3].minor.yy0
    funcNamePreprocess(yymsp[-3].minor.yy0->data);
    checkIsFunction(yymsp[-3].minor.yy0->data, yymsp[-3].minor.yy0->line);
    yymsp[-3].minor.yy0->data += "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 1697 "parser\\epparser.c"
        break;
      case 74: /* funcexpr ::= expr LPAREN fArgs RPAREN */
#line 338 "parser\\epparser.lemon"
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
#line 1721 "parser\\epparser.c"
        break;
      case 76: /* expr ::= LPAREN expr RPAREN */
      case 99: /* lexpr ::= LPAREN lexpr RPAREN */ yytestcase(yyruleno==99);
#line 366 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1730 "parser\\epparser.c"
        break;
      case 79: /* expr ::= LSQBRACKET exprList commaSkippable RSQBRACKET */
#line 374 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "_ARR(FlattenList([" + yymsp[-2].minor.yy0->data + "]))";
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1738 "parser\\epparser.c"
        break;
      case 80: /* expr ::= L2V LPAREN lexpr RPAREN */
#line 379 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "_L2V(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1746 "parser\\epparser.c"
        break;
      case 81: /* expr ::= MAPSTRING LPAREN STRING RPAREN */
#line 384 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetStringIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1754 "parser\\epparser.c"
        break;
      case 82: /* expr ::= UNIT LPAREN STRING RPAREN */
#line 389 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "EncodeUnit(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1762 "parser\\epparser.c"
        break;
      case 83: /* expr ::= SWITCH LPAREN STRING RPAREN */
#line 394 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "EncodeSwitch(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1770 "parser\\epparser.c"
        break;
      case 84: /* expr ::= LOCATION LPAREN STRING RPAREN */
#line 399 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetLocationIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1778 "parser\\epparser.c"
        break;
      case 85: /* expr ::= expr PLUS expr */
#line 405 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "+",  yymsp[0].minor.yy0); }
#line 1783 "parser\\epparser.c"
        break;
      case 86: /* expr ::= expr MINUS expr */
#line 406 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "-",  yymsp[0].minor.yy0); }
#line 1788 "parser\\epparser.c"
        break;
      case 87: /* expr ::= expr MULTIPLY expr */
#line 407 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "*",  yymsp[0].minor.yy0); }
#line 1793 "parser\\epparser.c"
        break;
      case 88: /* expr ::= expr DIVIDE expr */
#line 408 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "//", yymsp[0].minor.yy0); }
#line 1798 "parser\\epparser.c"
        break;
      case 89: /* expr ::= expr MOD expr */
#line 409 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "%",  yymsp[0].minor.yy0); }
#line 1803 "parser\\epparser.c"
        break;
      case 90: /* expr ::= expr LSHIFT expr */
#line 410 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = "_LSH(" + yymsp[-2].minor.yy0->data + "," + yymsp[0].minor.yy0->data + ")";
    delete yymsp[-2].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0);
}
#line 1812 "parser\\epparser.c"
        break;
      case 91: /* expr ::= expr RSHIFT expr */
#line 415 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, ">>", yymsp[0].minor.yy0); }
#line 1817 "parser\\epparser.c"
        break;
      case 92: /* expr ::= expr BITAND expr */
#line 416 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "&",  yymsp[0].minor.yy0); }
#line 1822 "parser\\epparser.c"
        break;
      case 93: /* expr ::= expr BITOR expr */
#line 417 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "|",  yymsp[0].minor.yy0); }
#line 1827 "parser\\epparser.c"
        break;
      case 94: /* expr ::= expr BITXOR expr */
#line 418 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "^",  yymsp[0].minor.yy0); }
#line 1832 "parser\\epparser.c"
        break;
      case 95: /* expr ::= PLUS expr */
#line 421 "parser\\epparser.lemon"
{ yymsp[0].minor.yy0->data = "+" + yymsp[0].minor.yy0->data; yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0); }
#line 1837 "parser\\epparser.c"
        break;
      case 96: /* expr ::= MINUS expr */
#line 422 "parser\\epparser.lemon"
{ yymsp[0].minor.yy0->data = "-" + yymsp[0].minor.yy0->data; yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0); }
#line 1842 "parser\\epparser.c"
        break;
      case 97: /* expr ::= BITNOT expr */
#line 423 "parser\\epparser.lemon"
{ yymsp[0].minor.yy0->data = "~" + yymsp[0].minor.yy0->data; yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0); }
#line 1847 "parser\\epparser.c"
        break;
      case 100: /* lexpr ::= expr EQ expr */
#line 433 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "==", yymsp[0].minor.yy0); }
#line 1852 "parser\\epparser.c"
        break;
      case 101: /* lexpr ::= expr NE expr */
#line 434 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genEmpty();
    yygotominor.yy0->line = yymsp[0].minor.yy0->line;

    yygotominor.yy0->type = TOKEN_NE;
    yygotominor.yy0->subToken[0] = yymsp[-2].minor.yy0;
    yygotominor.yy0->subToken[1] = yymsp[0].minor.yy0;
    yygotominor.yy0->data = yymsp[-2].minor.yy0->data + " != " + yymsp[0].minor.yy0->data;
}
#line 1865 "parser\\epparser.c"
        break;
      case 102: /* lexpr ::= expr LE expr */
#line 444 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "<=", yymsp[0].minor.yy0); }
#line 1870 "parser\\epparser.c"
        break;
      case 103: /* lexpr ::= expr LT expr */
#line 445 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "<",  yymsp[0].minor.yy0); }
#line 1875 "parser\\epparser.c"
        break;
      case 104: /* lexpr ::= expr GE expr */
#line 446 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, ">=", yymsp[0].minor.yy0); }
#line 1880 "parser\\epparser.c"
        break;
      case 105: /* lexpr ::= expr GT expr */
#line 447 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, ">" , yymsp[0].minor.yy0); }
#line 1885 "parser\\epparser.c"
        break;
      case 106: /* lexpr ::= lexpr LAND lexpr */
#line 450 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genEmpty();
    yygotominor.yy0->line = yymsp[0].minor.yy0->line;

    // Generate data!
    yygotominor.yy0->type = TOKEN_LAND;
    yygotominor.yy0->subToken[0] = yymsp[-2].minor.yy0;
    yygotominor.yy0->subToken[1] = yymsp[0].minor.yy0;
    yygotominor.yy0->data = "[" + flatListGetter(yygotominor.yy0, TOKEN_LAND) + "]";
}
#line 1899 "parser\\epparser.c"
        break;
      case 107: /* lexpr ::= lexpr LOR lexpr */
#line 462 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genEmpty();
    yygotominor.yy0->line = yymsp[0].minor.yy0->line;

    // Generate data!
    yygotominor.yy0->type = TOKEN_LOR;
    yygotominor.yy0->subToken[0] = yymsp[-2].minor.yy0;
    yygotominor.yy0->subToken[1] = yymsp[0].minor.yy0;
    yygotominor.yy0->data = "EUDOr(" + flatListGetter(yygotominor.yy0, TOKEN_LOR) + ")";
}
#line 1913 "parser\\epparser.c"
        break;
      case 108: /* lexpr ::= LNOT lexpr */
#line 473 "parser\\epparser.lemon"
{
    if(yymsp[0].minor.yy0->type == TOKEN_LNOT) {
        yygotominor.yy0 = yymsp[0].minor.yy0->subToken[0];
        yymsp[0].minor.yy0->subToken[0] = nullptr;
        delete yymsp[0].minor.yy0;
    }
    else {
        yygotominor.yy0 = genEmpty();
        yygotominor.yy0->line = yymsp[0].minor.yy0->line;
        yygotominor.yy0->type = TOKEN_LNOT;
        yygotominor.yy0->data = "EUDNot([" + yymsp[0].minor.yy0->data + "])";
        yygotominor.yy0->subToken[0] = yymsp[0].minor.yy0;
    }
}
#line 1931 "parser\\epparser.c"
        break;
      case 109: /* vdef_stmt ::= VAR nameList_nonEmpty */
#line 490 "parser\\epparser.lemon"
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
#line 1955 "parser\\epparser.c"
        break;
      case 110: /* vdefAssign_stmt ::= VAR nameList_nonEmpty ASSIGN exprList_nonEmpty */
#line 511 "parser\\epparser.lemon"
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
#line 1980 "parser\\epparser.c"
        break;
      case 111: /* vdefAssign_global_stmt ::= VAR nameList_nonEmpty ASSIGN exprList_nonEmpty */
#line 533 "parser\\epparser.lemon"
{
    std::string& s = yymsp[-2].minor.yy0->data;
    int varCount = std::count(s.begin(), s.end(), ',') + 1;

    // Register variables.
    commaListIter(s, [&](std::string& varname) {
        if(!ps->closure.defVariable(varname)) {
            throw_error(7998, ("Redeclaration of variable \'" + varname + "\'"), yymsp[-2].minor.yy0->line);
        }
    });

    ps->gen << s << " = EUDCreateVariables(" << varCount << ")" << std::endl;
    ps->gen << "_IGVA(" << s << ", lambda: [" << yymsp[0].minor.yy0->data << "])" << std::endl;

    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 2000 "parser\\epparser.c"
        break;
      case 112: /* cdef_stmt ::= CONST nameList_nonEmpty ASSIGN exprList_nonEmpty */
#line 550 "parser\\epparser.lemon"
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
#line 2022 "parser\\epparser.c"
        break;
      case 113: /* cdef_global_stmt ::= CONST nameList_nonEmpty ASSIGN exprList_nonEmpty */
#line 569 "parser\\epparser.lemon"
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
        ps->gen << s << " = _CGFW(lambda: [" << yymsp[0].minor.yy0->data << "], 1)[0]" << std::endl;
    }
    else {
        ps->gen << s << " = List2Assignable(_CGFW(lambda: [" << yymsp[0].minor.yy0->data << "], nameCount))" << std::endl;
    }
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 2044 "parser\\epparser.c"
        break;
      case 114: /* lvalue ::= NAME */
#line 589 "parser\\epparser.lemon"
{
    checkIsVariable(yymsp[0].minor.yy0->data, yymsp[0].minor.yy0->line);
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 2052 "parser\\epparser.c"
        break;
      case 115: /* lvalue ::= expr LSQBRACKET expr RSQBRACKET */
#line 594 "parser\\epparser.lemon"
{
    checkIsConstant(yymsp[-3].minor.yy0->data, yymsp[-3].minor.yy0->line);
    yymsp[-1].minor.yy0->data = "_ARRW(" + yymsp[-3].minor.yy0->data + ", " + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
    delete yymsp[-3].minor.yy0;
}
#line 2062 "parser\\epparser.c"
        break;
      case 116: /* lvalue ::= expr PERIOD NAME */
#line 601 "parser\\epparser.lemon"
{
    checkIsConstant(yymsp[-2].minor.yy0->data, yymsp[-2].minor.yy0->line);
    yymsp[0].minor.yy0->data = "_ATTW(" + yymsp[-2].minor.yy0->data + ", '" + yymsp[0].minor.yy0->data + "')";
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0);
    delete yymsp[-2].minor.yy0;
}
#line 2072 "parser\\epparser.c"
        break;
      case 119: /* assign_stmt ::= lvalue ASSIGN expr */
#line 610 "parser\\epparser.lemon"
{
    ps->gen << yymsp[-2].minor.yy0->data << " << (" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 2080 "parser\\epparser.c"
        break;
      case 120: /* assign_stmt ::= lvalueList_nonEmpty ASSIGN exprList_nonEmpty */
#line 615 "parser\\epparser.lemon"
{
    ps->gen << "_SV([" << yymsp[-2].minor.yy0->data << "], [" << yymsp[0].minor.yy0->data << "])" << std::endl;
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 2088 "parser\\epparser.c"
        break;
      case 121: /* assign_stmt ::= INC expr */
#line 623 "parser\\epparser.lemon"
{ ps->gen << yymsp[0].minor.yy0->data << ".__iadd__(1)" << std::endl; delete yymsp[0].minor.yy0; }
#line 2093 "parser\\epparser.c"
        break;
      case 122: /* assign_stmt ::= expr INC */
#line 624 "parser\\epparser.lemon"
{ ps->gen << yymsp[-1].minor.yy0->data << ".__iadd__(1)" << std::endl; delete yymsp[-1].minor.yy0; }
#line 2098 "parser\\epparser.c"
        break;
      case 123: /* assign_stmt ::= DEC expr */
#line 625 "parser\\epparser.lemon"
{ ps->gen << yymsp[0].minor.yy0->data << ".__isub__(1)" << std::endl; delete yymsp[0].minor.yy0; }
#line 2103 "parser\\epparser.c"
        break;
      case 124: /* assign_stmt ::= expr DEC */
#line 626 "parser\\epparser.lemon"
{ ps->gen << yymsp[-1].minor.yy0->data << ".__isub__(1)" << std::endl; delete yymsp[-1].minor.yy0; }
#line 2108 "parser\\epparser.c"
        break;
      case 125: /* assign_stmt ::= lvalue IADD expr */
#line 627 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__iadd__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2113 "parser\\epparser.c"
        break;
      case 126: /* assign_stmt ::= lvalue ISUB expr */
#line 628 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__isub__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2118 "parser\\epparser.c"
        break;
      case 127: /* assign_stmt ::= lvalue IMUL expr */
#line 629 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__imul__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2123 "parser\\epparser.c"
        break;
      case 128: /* assign_stmt ::= lvalue IDIV expr */
#line 630 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ifloordiv__("  << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2128 "parser\\epparser.c"
        break;
      case 129: /* assign_stmt ::= lvalue IMOD expr */
#line 631 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__imod__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2133 "parser\\epparser.c"
        break;
      case 130: /* assign_stmt ::= lvalue ILSH expr */
#line 632 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ilshift__("    << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2138 "parser\\epparser.c"
        break;
      case 131: /* assign_stmt ::= lvalue IRSH expr */
#line 633 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__irshift__("    << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2143 "parser\\epparser.c"
        break;
      case 132: /* assign_stmt ::= lvalue IBND expr */
#line 634 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__iand__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2148 "parser\\epparser.c"
        break;
      case 133: /* assign_stmt ::= lvalue IBOR expr */
#line 635 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ior__("        << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2153 "parser\\epparser.c"
        break;
      case 134: /* assign_stmt ::= lvalue IBXR expr */
#line 636 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ixor__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2158 "parser\\epparser.c"
        break;
      case 135: /* if_start ::= IF */
#line 639 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDIf()" << std::endl;
}
#line 2166 "parser\\epparser.c"
        break;
      case 136: /* if_header ::= if_start LPAREN lexpr RPAREN */
      case 139: /* elif_header ::= elif_start LPAREN lexpr RPAREN */ yytestcase(yyruleno==139);
      case 145: /* while_header ::= while_start LPAREN lexpr RPAREN */ yytestcase(yyruleno==145);
#line 644 "parser\\epparser.lemon"
{
    writeNegatableCondition(yymsp[-3].minor.yy0, yymsp[-1].minor.yy0);
    ps->gen.indent();
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 2177 "parser\\epparser.c"
        break;
      case 138: /* elif_start ::= ELSE IF */
#line 652 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen.unindent(false);
    ps->gen << yygotominor.yy0->data << " = EUDElseIf()" << std::endl;
}
#line 2186 "parser\\epparser.c"
        break;
      case 141: /* else_header ::= ELSE */
#line 666 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "if EUDElse()():" << std::endl;
    ps->gen.indent();
}
#line 2195 "parser\\epparser.c"
        break;
      case 142: /* if_stmt ::= if_block */
      case 143: /* if_stmt ::= if_block else_header stmt */ yytestcase(yyruleno==143);
#line 672 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndIf()" << std::endl;
}
#line 2204 "parser\\epparser.c"
        break;
      case 144: /* while_start ::= WHILE */
#line 684 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDWhile()" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2213 "parser\\epparser.c"
        break;
      case 146: /* while_stmt ::= while_header stmt */
#line 696 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndWhile()" << std::endl;
}
#line 2221 "parser\\epparser.c"
        break;
      case 147: /* for_opener ::= FOR LPAREN */
      case 163: /* foreach_opener ::= FOREACH LPAREN */ yytestcase(yyruleno==163);
#line 702 "parser\\epparser.lemon"
{
    ps->closure.pushScope();
}
#line 2229 "parser\\epparser.c"
        break;
      case 159: /* for_header1 ::= for_opener for_init_stmt SEMICOLON */
#line 720 "parser\\epparser.lemon"
{
    // opening for lexpr
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDWhile()" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2239 "parser\\epparser.c"
        break;
      case 160: /* for_header2 ::= for_header1 lexpr SEMICOLON */
#line 727 "parser\\epparser.lemon"
{
    writeNegatableCondition(yymsp[-2].minor.yy0, yymsp[-1].minor.yy0);
    ps->gen.indent();
    delete yymsp[-2].minor.yy0; delete yymsp[-1].minor.yy0;

    // Opening for assign_statement
    yygotominor.yy0 = genTemp(yymsp[-1].minor.yy0);
    ps->gen << "def " << yygotominor.yy0->data <<"():" << std::endl;
    ps->gen.indent();
}
#line 2253 "parser\\epparser.c"
        break;
      case 161: /* for_header ::= for_header2 for_action_stmt RPAREN */
#line 738 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-2].minor.yy0;
    ps->gen.unindent(false);
}
#line 2261 "parser\\epparser.c"
        break;
      case 162: /* for_stmt ::= for_header stmt */
#line 743 "parser\\epparser.lemon"
{
    ps->gen << "EUDSetContinuePoint()" << std::endl;
    ps->gen << yymsp[-1].minor.yy0->data << "()" << std::endl;
    ps->gen.unindent(false);
    ps->gen << "EUDEndWhile()" << std::endl;
    ps->closure.popScope();
}
#line 2272 "parser\\epparser.c"
        break;
      case 164: /* foreach_header ::= foreach_opener nameList_nonEmpty COLON exprList_nonEmpty RPAREN */
#line 758 "parser\\epparser.lemon"
{
    commaListIter(yymsp[-3].minor.yy0->data, [&](std::string& s) {
        ps->closure.defVariable(s);
    });
    ps->gen << "for " << yymsp[-3].minor.yy0->data << " in " << yymsp[-1].minor.yy0->data << ":" << std::endl;
    ps->gen.indent();
}
#line 2283 "parser\\epparser.c"
        break;
      case 165: /* foreach_stmt ::= foreach_header stmt */
#line 766 "parser\\epparser.lemon"
{
    ps->gen.unindent(true);
    ps->closure.popScope();
}
#line 2291 "parser\\epparser.c"
        break;
      case 166: /* continue_stmt ::= CONTINUE */
#line 774 "parser\\epparser.lemon"
{
    ps->gen << "EUDContinue()" << std::endl;
}
#line 2298 "parser\\epparser.c"
        break;
      case 167: /* break_stmt ::= BREAK */
#line 778 "parser\\epparser.lemon"
{
    ps->gen << "EUDBreak()" << std::endl;
}
#line 2305 "parser\\epparser.c"
        break;
      case 168: /* return_stmt ::= RETURN exprList */
#line 785 "parser\\epparser.lemon"
{
    if(MAP_DEBUG){
        ps->gen << "MDBG_POPF()" << std::endl;
    }
    ps->gen << "EUDReturn(" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2316 "parser\\epparser.c"
        break;
      case 169: /* lexpr ::= CONDITIONNAME LPAREN fArgs RPAREN */
      case 170: /* lexpr ::= KILLS LPAREN fArgs RPAREN */ yytestcase(yyruleno==170);
#line 796 "parser\\epparser.lemon"
{
    yymsp[-3].minor.yy0->data = yymsp[-3].minor.yy0->data + "(" + yymsp[-1].minor.yy0->data + ")";
    delete yymsp[-1].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 2326 "parser\\epparser.c"
        break;
      case 171: /* lexpr ::= CONDITIONNAME LPAREN RPAREN */
#line 808 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + "()";
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 2334 "parser\\epparser.c"
        break;
      case 172: /* action ::= ACTIONNAME LPAREN fArgs RPAREN SEMICOLON */
#line 813 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[-4].minor.yy0);
    yygotominor.yy0->data =  yymsp[-4].minor.yy0->data + "(" + yymsp[-2].minor.yy0->data + ")";
    delete yymsp[-4].minor.yy0; delete yymsp[-2].minor.yy0;
}
#line 2343 "parser\\epparser.c"
        break;
      case 173: /* actions ::= action action */
      case 174: /* actions ::= actions action */ yytestcase(yyruleno==174);
#line 819 "parser\\epparser.lemon"
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
#line 2366 "parser\\epparser.c"
        break;
      case 175: /* actionStmt_start ::= */
#line 857 "parser\\epparser.lemon"
{
    functionCalledInMultipleActions = false;
}
#line 2373 "parser\\epparser.c"
        break;
      case 176: /* actionStmt ::= actionStmt_start action */
#line 861 "parser\\epparser.lemon"
{
    ps->gen << "DoActions(" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2381 "parser\\epparser.c"
        break;
      case 177: /* actionStmt ::= actionStmt_start actions */
#line 866 "parser\\epparser.lemon"
{
    ps->gen << "DoActions([" << std::endl;
    ps->gen.indent();
    ps->gen << yymsp[0].minor.yy0->data << std::endl;
    ps->gen.unindent(false);
    ps->gen << "])" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2393 "parser\\epparser.c"
        break;
      default:
      /* (0) program ::= chunks */ yytestcase(yyruleno==0);
      /* (1) chunks ::= */ yytestcase(yyruleno==1);
      /* (2) chunks ::= chunks chunk */ yytestcase(yyruleno==2);
      /* (3) chunk ::= import_chunk SEMICOLON */ yytestcase(yyruleno==3);
      /* (4) chunk ::= fdef_chunk */ yytestcase(yyruleno==4);
      /* (5) chunk ::= fdecl_chunk */ yytestcase(yyruleno==5);
      /* (6) chunk ::= object_chunk */ yytestcase(yyruleno==6);
      /* (7) chunk ::= vdef_stmt SEMICOLON */ yytestcase(yyruleno==7);
      /* (8) chunk ::= vdefAssign_global_stmt SEMICOLON */ yytestcase(yyruleno==8);
      /* (9) chunk ::= cdef_global_stmt SEMICOLON */ yytestcase(yyruleno==9);
      /* (23) stmt ::= bodyStmt */ yytestcase(yyruleno==23);
      /* (24) stmt ::= return_stmt SEMICOLON */ yytestcase(yyruleno==24);
      /* (28) blockStmt ::= lbracket return_stmt SEMICOLON rbracket */ yytestcase(yyruleno==28);
      /* (29) blockStmt ::= lbracket bodyStmtList rbracket */ yytestcase(yyruleno==29);
      /* (30) blockStmt ::= lbracket bodyStmtList return_stmt SEMICOLON rbracket */ yytestcase(yyruleno==30);
      /* (32) bodyStmt ::= blockStmt */ yytestcase(yyruleno==32);
      /* (33) bodyStmt ::= SEMICOLON */ yytestcase(yyruleno==33);
      /* (34) bodyStmt ::= vdef_stmt SEMICOLON */ yytestcase(yyruleno==34);
      /* (35) bodyStmt ::= vdefAssign_stmt SEMICOLON */ yytestcase(yyruleno==35);
      /* (36) bodyStmt ::= cdef_stmt SEMICOLON */ yytestcase(yyruleno==36);
      /* (37) bodyStmt ::= assign_stmt SEMICOLON */ yytestcase(yyruleno==37);
      /* (39) bodyStmt ::= actionStmt */ yytestcase(yyruleno==39);
      /* (40) bodyStmt ::= if_stmt */ yytestcase(yyruleno==40);
      /* (41) bodyStmt ::= while_stmt */ yytestcase(yyruleno==41);
      /* (42) bodyStmt ::= for_stmt */ yytestcase(yyruleno==42);
      /* (43) bodyStmt ::= foreach_stmt */ yytestcase(yyruleno==43);
      /* (44) bodyStmt ::= continue_stmt SEMICOLON */ yytestcase(yyruleno==44);
      /* (45) bodyStmt ::= break_stmt SEMICOLON */ yytestcase(yyruleno==45);
      /* (47) bodyStmtList ::= bodyStmt */ yytestcase(yyruleno==47);
      /* (48) bodyStmtList ::= bodyStmtList bodyStmt */ yytestcase(yyruleno==48);
      /* (77) commaSkippable ::= COMMA */ yytestcase(yyruleno==77);
      /* (78) commaSkippable ::= */ yytestcase(yyruleno==78);
      /* (137) if_block ::= if_header stmt */ yytestcase(yyruleno==137);
      /* (140) if_block ::= if_block elif_header stmt */ yytestcase(yyruleno==140);
      /* (148) for_init_stmt_nonEmpty ::= vdef_stmt */ yytestcase(yyruleno==148);
      /* (149) for_init_stmt_nonEmpty ::= vdefAssign_stmt */ yytestcase(yyruleno==149);
      /* (150) for_init_stmt_nonEmpty ::= cdef_stmt */ yytestcase(yyruleno==150);
      /* (151) for_init_stmt_nonEmpty ::= assign_stmt */ yytestcase(yyruleno==151);
      /* (152) for_init_stmt_nonEmpty ::= for_init_stmt_nonEmpty COMMA for_init_stmt_nonEmpty */ yytestcase(yyruleno==152);
      /* (153) for_init_stmt ::= for_init_stmt_nonEmpty */ yytestcase(yyruleno==153);
      /* (154) for_init_stmt ::= */ yytestcase(yyruleno==154);
      /* (155) for_action_stmt_nonEmpty ::= assign_stmt */ yytestcase(yyruleno==155);
      /* (156) for_action_stmt_nonEmpty ::= for_action_stmt_nonEmpty COMMA for_action_stmt_nonEmpty */ yytestcase(yyruleno==156);
      /* (157) for_action_stmt ::= */ yytestcase(yyruleno==157);
      /* (158) for_action_stmt ::= for_action_stmt_nonEmpty */ yytestcase(yyruleno==158);
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
#line 31 "parser\\epparser.lemon"

    throw_error(-1, "Unrecoverable error");
#line 2489 "parser\\epparser.c"
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
#line 880 "parser\\epparser.lemon"


PyGenerator* pGen;
ClosureManager* closure;

std::string ParseString(const std::string& fname, const std::string& code, bool addComment)
{
    // Module name from fname
    // last \/ ~ first .
    auto lpos = fname.find_last_of("\\/");
    if(lpos == std::string::npos) lpos = 0;
    else lpos++;
    auto rpos = fname.find_first_of(".", lpos);
    if(rpos == std::string::npos) rpos = fname.size();
    currentModule = fname.substr(lpos, rpos - lpos);

    // Main code
    Tokenizer tok(code);
    void* pParser = ParseAlloc (malloc);
    ParserStruct ps;
    Token* token;
    currentTokenizingLine = 0;
    pGen = &ps.gen;
    closure = &ps.closure;
    functionCalledInMultipleActions = false;

    if(PARSER_DEBUG) std::cout << "Parsing string [[[\n" << code.c_str() << "\n]]]\n";
    if(MAP_DEBUG) {
        ps.gen <<
            "try:\n"
            "   MDBG_LOG = GetEUDNamespace()['MDBG_LOG']\n"
            "   MDBG_PUSHF = GetEUDNamespace()['MDBG_PUSHF']\n"
            "   MDBG_POPF = GetEUDNamespace()['MDBG_POPF']\n"
            "except KeyError:\n"
            "    mdbg_dbepd = EPD(Db(b'0123456789ABCDEFFEDCBA9876543210' + bytes(32 * 2048)))\n"
            "    mdbg_dbc = EUDVariable()\n"
            "    \n"
            "    @EUDRegistered\n"
            "    def MDBG_LOG(line):\n"
            "        lIdf = b2i4(u2b('%4d' % line))\n"
            "        DoActions(SetMemoryEPD(mdbg_dbepd + 3 + mdbg_dbc, SetTo, lIdf))\n"
            "    \n"
            "    \n"
            "    @EUDRegistered\n"
            "    def MDBG_PUSHF(f_name, m_name):\n"
            "        global mdbg_dbc\n"
            "        data = ((u2b(m_name) + bytes(12))[:12] + b'   0' + (u2b(f_name) + bytes(16))[:16])\n"
            "        mdbg_dbc += 8\n"
            "        DoActions([SetMemoryEPD(mdbg_dbepd + i + mdbg_dbc, SetTo, b2i4(data, i * 4)) for i in range(8)])\n"
            "    \n"
            "    @EUDRegistered\n"
            "    def MDBG_POPF():\n"
            "        global mdbg_dbc\n"
            "        DoActions([SetMemoryEPD(mdbg_dbepd + i + mdbg_dbc, SetTo, 0) for i in range(8)])\n"
            "        mdbg_dbc -= 8\n"
            "\n";
    }

    tmpIndex = 1;
    resetParserErrorNum();
    while ((token = tok.getToken()) != nullptr) {
        if (currentTokenizingLine != tok.getCurrentLine()) {
            if(addComment) {
                currentTokenizingLine = tok.getCurrentLine();
                ps.gen << "# (Line " << currentTokenizingLine << ") " << trim(tok.getCurrentLineString()) << std::endl;
                if(MAP_DEBUG && !currentFunction.empty()) {
                    ps.gen << "MDBG_LOG(" << currentTokenizingLine << ")" << std::endl;
                }
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
#line 2785 "parser\\epparser.c"
