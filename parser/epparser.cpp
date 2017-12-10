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
#define YYNOCODE 136
#define YYACTIONTYPE unsigned short int
#define ParseTOKENTYPE Token*
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  int yy271;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL  ParserStruct* ps ;
#define ParseARG_PDECL , ParserStruct* ps 
#define ParseARG_FETCH  ParserStruct* ps  = yypParser->ps 
#define ParseARG_STORE yypParser->ps  = ps 
#define YYNSTATE 333
#define YYNRULE 173
#define YYERRORSYMBOL 71
#define YYERRSYMDT yy271
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
#define YY_ACTTAB_COUNT (1191)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   218,  246,  204,  302,   27,   28,  202,  226,  214,  225,
 /*    10 */    18,  308,  210,   93,   75,  318,  316,  217,    2,  124,
 /*    20 */   147,  213,  212,  211,  152,  300,  299,  298,  297,  296,
 /*    30 */   206,  205,  162,  161,  276,   93,  246,  204,   27,   28,
 /*    40 */   331,  124,  147,  169,    8,   40,   38,  219,   93,  166,
 /*    50 */     6,   10,  328,  218,  124,  147,   22,   13,    5,   83,
 /*    60 */     4,  214,  247,   77,  308,   37,  219,  245,  261,  316,
 /*    70 */   217,    2,  323,  198,  213,  212,  211,  152,  300,  299,
 /*    80 */   298,  297,  296,  206,  205,  167,    7,    3,   93,  201,
 /*    90 */   219,   35,   36,  327,  124,  147,  169,    8,   40,  196,
 /*   100 */   117,   86,  166,    6,   10,  326,  204,  218,  197,   22,
 /*   110 */    13,    5,   83,    4,   76,  214,   77,  118,  308,  282,
 /*   120 */    33,  219,  258,  316,  217,    2,   32,  219,  213,  212,
 /*   130 */   211,  152,  300,  299,  298,  297,  296,  206,  205,   27,
 /*   140 */    28,   39,   93,   27,   28,   19,   82,   81,  124,  147,
 /*   150 */   169,    8,   40,   34,  322,  222,  166,    6,   10,  223,
 /*   160 */   218,   78,  321,   22,   13,    5,   83,    4,  214,  271,
 /*   170 */    77,  308,  241,  262,  220,  255,  316,  217,    2,  221,
 /*   180 */   219,  213,  212,  211,  152,  300,  299,  298,  297,  296,
 /*   190 */   206,  205,  319,  209,  317,   93,  201,  507,   11,  315,
 /*   200 */   208,  124,  147,  169,    8,   40,  196,  117,  237,  166,
 /*   210 */     6,   10,   89,  204,  218,  204,   22,   13,    5,   83,
 /*   220 */     4,  207,  214,   77,  119,  308,   96,   88,  301,  243,
 /*   230 */   316,  217,    2,  306,  305,  213,  212,  211,  152,  300,
 /*   240 */   299,  298,  297,  296,  206,  205,   27,   28,  304,   93,
 /*   250 */    27,   28,  303,  295,  210,  124,  147,  169,    8,   40,
 /*   260 */   294,   19,  289,  166,    6,   10,  200,  218,  204,  286,
 /*   270 */    22,   13,    5,   83,    4,  214,  259,   77,  308,  130,
 /*   280 */   256,   87,  240,  316,  217,    2,  285,   39,  213,  212,
 /*   290 */   211,  152,  300,  299,  298,  297,  296,  206,  205,   30,
 /*   300 */    17,   31,   93,  201,  204,  191,  269,  281,  124,  147,
 /*   310 */   169,    8,   40,  284,  117,   92,  166,    6,   10,  190,
 /*   320 */   135,  218,  204,   22,   13,    5,   83,    4,  188,  214,
 /*   330 */    77,  187,  308,  129,  280,   28,  233,  316,  217,    2,
 /*   340 */   185,  184,  213,  212,  211,  152,  300,  299,  298,  297,
 /*   350 */   296,  206,  205,  279,  182,   15,   93,  181,  278,  277,
 /*   360 */   273,  268,  124,  147,  169,    8,   40,  122,  267,   25,
 /*   370 */   166,    6,   10,  260,  156,   24,  201,   22,   13,    5,
 /*   380 */    83,    4,  214,   23,   77,  308,  172,  117,  254,   12,
 /*   390 */   231,  216,    2,  248,    1,  213,  212,  211,  152,  300,
 /*   400 */   299,  298,  297,  296,  206,  205,  244,   14,  242,   93,
 /*   410 */   201,  204,   16,  236,  157,  124,  147,  169,    8,   40,
 /*   420 */   171,  117,   91,  166,    6,   10,  232,  136,  292,  204,
 /*   430 */    22,   13,    5,   83,    4,  153,  214,   77,  324,  308,
 /*   440 */   142,  312,  150,  311,  293,  215,    2,  310,  309,  213,
 /*   450 */   212,  211,  152,  300,  299,  298,  297,  296,  206,  205,
 /*   460 */   199,  270,  320,   93,  176,  149,  148,  146,  235,  124,
 /*   470 */   147,  169,    8,   40,  234,  144,  143,  166,    6,   10,
 /*   480 */   159,  168,  508,  508,   22,   13,    5,   83,    4,   63,
 /*   490 */    62,   77,   71,   72,   70,   61,  291,  120,  307,  204,
 /*   500 */   202,  508,  508,   64,   18,  314,  313,   21,   75,  290,
 /*   510 */   141,  508,  195,  192,  189,  186,  183,   85,   84,   42,
 /*   520 */    41,  204,   63,   62,  508,  508,  508,  508,   61,  291,
 /*   530 */   120,  263,  140,  257,  165,  160,   64,  239,  238,   20,
 /*   540 */    21,  508,  290,  204,  508,  195,  192,  189,  186,  183,
 /*   550 */    63,   62,   42,   41,   99,  508,   61,  291,  120,  307,
 /*   560 */   264,  508,  508,  508,   64,  508,  314,  312,   21,  508,
 /*   570 */   290,  508,  508,  195,  192,  189,  186,  183,   85,   84,
 /*   580 */    42,   41,   66,   65,   67,   69,   68,   74,   73,   71,
 /*   590 */    72,   70,  263,  201,  257,  165,  160,  202,  239,  238,
 /*   600 */    20,   18,  204,  170,  117,   75,  288,  508,  508,  508,
 /*   610 */   204,   63,   62,  118,  508,  193,  174,   61,  291,  120,
 /*   620 */   307,  118,  508,  193,  175,   64,  508,  314,  508,   21,
 /*   630 */   508,  290,  204,  508,  195,  192,  189,  186,  183,   85,
 /*   640 */    84,   42,   41,  128,   74,   73,   71,   72,   70,  508,
 /*   650 */   508,  508,  508,  263,  202,  257,  165,  160,   18,  239,
 /*   660 */   238,   20,   75,   60,   58,   57,   56,   55,   59,   66,
 /*   670 */    65,   67,   69,   68,   74,   73,   71,   72,   70,  204,
 /*   680 */   204,  508,  508,  508,  202,  333,  508,  508,   18,  287,
 /*   690 */    92,  118,   75,  193,  180,  275,   60,   58,   57,   56,
 /*   700 */    55,   59,   66,   65,   67,   69,   68,   74,   73,   71,
 /*   710 */    72,   70,  508,  204,   90,  508,  224,  202,  508,  314,
 /*   720 */   508,   18,   63,   62,  118,   75,  193,  158,   61,  291,
 /*   730 */   120,   80,   79,  201,  508,  508,   64,  508,  508,  508,
 /*   740 */    21,  508,  290,  145,  117,  195,  192,  189,  186,  183,
 /*   750 */    85,   84,   42,   41,   66,   65,   67,   69,   68,   74,
 /*   760 */    73,   71,   72,   70,  201,   26,  508,  508,  508,  173,
 /*   770 */   201,  204,  204,   18,  155,  117,  508,   54,   63,   62,
 /*   780 */   154,  117,   92,   92,   61,  291,  203,  179,  274,  266,
 /*   790 */   265,  508,   29,  508,  508,  508,   21,  508,  194,  508,
 /*   800 */   508,  195,  192,  189,  186,  183,  332,  230,  330,  329,
 /*   810 */   229,  228,  227,  325,  508,    9,  508,   63,   62,  204,
 /*   820 */     2,  508,  204,   61,  291,  151,  508,  508,  204,  178,
 /*   830 */   127,   64,  272,  126,  508,   21,  508,  290,  283,  123,
 /*   840 */   195,  192,  189,  186,  183,   66,   65,   67,   69,   68,
 /*   850 */    74,   73,   71,   72,   70,  508,  204,  508,  508,  508,
 /*   860 */   202,  204,  508,  508,   18,  287,  508,  118,   75,  193,
 /*   870 */   177,  508,  125,  204,   66,   65,   67,   69,   68,   74,
 /*   880 */    73,   71,   72,   70,   95,  442,  442,  508,  204,  202,
 /*   890 */   508,  508,  204,   18,   63,   62,  508,   75,  121,   92,
 /*   900 */    61,  291,  151,  139,  134,  508,  508,  508,   64,  508,
 /*   910 */   508,  204,   21,  204,  290,  283,   19,  195,  192,  189,
 /*   920 */   186,  183,   92,  508,   92,  508,  508,  133,  508,  132,
 /*   930 */   508,  253,  508,  508,  442,  442,  442,  442,  442,  442,
 /*   940 */   442,  442,  442,  442,  252,  251,  250,  204,   66,   65,
 /*   950 */    67,   69,   68,   74,   73,   71,   72,   70,   93,  508,
 /*   960 */   508,  204,  508,  202,  124,  147,  508,   18,  508,  508,
 /*   970 */   508,   75,  138,  508,  253,  164,  163,   66,   65,   67,
 /*   980 */    69,   68,   74,   73,   71,   72,   70,  252,  251,  250,
 /*   990 */   204,  204,  173,  508,  508,  204,   18,   63,   62,  204,
 /*  1000 */    54,   93,  137,   61,  291,  203,  116,  124,  147,  508,
 /*  1010 */   115,   64,  508,  508,  204,   21,  204,  290,  249,  508,
 /*  1020 */   195,  192,  189,  186,  183,  114,  508,   92,  508,  508,
 /*  1030 */    63,   62,  131,  444,  444,  204,   61,  291,  120,  508,
 /*  1040 */   204,  204,  508,  508,   64,  508,  113,  204,   21,  508,
 /*  1050 */   290,  112,  111,  195,  192,  189,  186,  183,   94,   65,
 /*  1060 */    67,   69,   68,   74,   73,   71,   72,   70,  443,  443,
 /*  1070 */   508,  508,  508,  202,  508,  508,  508,   18,  508,  508,
 /*  1080 */   508,   75,  444,  444,  444,  444,  444,  444,  444,  444,
 /*  1090 */   444,  444,   53,   67,   69,   68,   74,   73,   71,   72,
 /*  1100 */    70,  204,  204,  508,  204,  508,  202,  508,  508,  508,
 /*  1110 */    18,  508,  110,  109,   75,  108,  204,  443,  443,  443,
 /*  1120 */   443,  443,  443,  443,  443,  443,  443,  107,  204,  204,
 /*  1130 */   508,  508,  508,  508,  508,  508,  508,  508,  508,  106,
 /*  1140 */   105,   52,   51,   50,   49,   48,   47,   46,   45,   44,
 /*  1150 */    43,  508,  508,  508,  204,  204,  204,  204,   69,   68,
 /*  1160 */    74,   73,   71,   72,   70,  104,  103,  102,  101,  204,
 /*  1170 */   202,  508,  508,  508,   18,  508,  508,  204,   75,  204,
 /*  1180 */   100,  508,  508,  508,  508,  508,  508,  508,   98,  508,
 /*  1190 */    97,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    71,   94,   95,   27,    3,    4,   28,   28,   79,   30,
 /*    10 */    32,   82,   36,  106,   36,   86,   87,   88,   89,  112,
 /*    20 */   113,   92,   93,   94,   95,   96,   97,   98,   99,  100,
 /*    30 */   101,  102,  125,  126,   33,  106,   94,   95,    3,    4,
 /*    40 */    27,  112,  113,  114,  115,  116,    1,    2,  106,  120,
 /*    50 */   121,  122,   27,   71,  112,  113,  127,  128,  129,  130,
 /*    60 */   131,   79,   27,  134,   82,    1,    2,  125,   86,   87,
 /*    70 */    88,   89,   26,    2,   92,   93,   94,   95,   96,   97,
 /*    80 */    98,   99,  100,  101,  102,  117,  118,  119,  106,   95,
 /*    90 */     2,    1,    2,   27,  112,  113,  114,  115,  116,  105,
 /*   100 */   106,  107,  120,  121,  122,   27,   95,   71,   37,  127,
 /*   110 */   128,  129,  130,  131,    1,   79,  134,  106,   82,  108,
 /*   120 */     1,    2,   86,   87,   88,   89,    1,    2,   92,   93,
 /*   130 */    94,   95,   96,   97,   98,   99,  100,  101,  102,    3,
 /*   140 */     4,    2,  106,    3,    4,   32,  132,  133,  112,  113,
 /*   150 */   114,  115,  116,   65,   26,   85,  120,  121,  122,   26,
 /*   160 */    71,   32,   27,  127,  128,  129,  130,  131,   79,   33,
 /*   170 */   134,   82,   33,   33,  104,   86,   87,   88,   89,   33,
 /*   180 */     2,   92,   93,   94,   95,   96,   97,   98,   99,  100,
 /*   190 */   101,  102,   26,   36,   27,  106,   95,   73,   74,   27,
 /*   200 */    25,  112,  113,  114,  115,  116,  105,  106,  107,  120,
 /*   210 */   121,  122,   27,   95,   71,   95,  127,  128,  129,  130,
 /*   220 */   131,   37,   79,  134,  106,   82,  106,   27,   37,   86,
 /*   230 */    87,   88,   89,   27,   27,   92,   93,   94,   95,   96,
 /*   240 */    97,   98,   99,  100,  101,  102,    3,    4,   27,  106,
 /*   250 */     3,    4,   27,   27,   36,  112,  113,  114,  115,  116,
 /*   260 */    27,   32,   26,  120,  121,  122,   36,   71,   95,   25,
 /*   270 */   127,  128,  129,  130,  131,   79,   33,  134,   82,  106,
 /*   280 */    33,   36,   86,   87,   88,   89,   37,    2,   92,   93,
 /*   290 */    94,   95,   96,   97,   98,   99,  100,  101,  102,   32,
 /*   300 */    32,    2,  106,   95,   95,   32,   37,   33,  112,  113,
 /*   310 */   114,  115,  116,  105,  106,  106,  120,  121,  122,   39,
 /*   320 */   111,   71,   95,  127,  128,  129,  130,  131,   32,   79,
 /*   330 */   134,   39,   82,  106,   33,    4,   86,   87,   88,   89,
 /*   340 */    32,   39,   92,   93,   94,   95,   96,   97,   98,   99,
 /*   350 */   100,  101,  102,   33,   32,   32,  106,   39,   33,   33,
 /*   360 */    33,   33,  112,  113,  114,  115,  116,   26,   33,   32,
 /*   370 */   120,  121,  122,   60,   71,   32,   95,  127,  128,  129,
 /*   380 */   130,  131,   79,   32,  134,   82,  105,  106,   32,    2,
 /*   390 */    87,   88,   89,   27,   91,   92,   93,   94,   95,   96,
 /*   400 */    97,   98,   99,  100,  101,  102,   33,    2,   32,  106,
 /*   410 */    95,   95,   32,   27,   33,  112,  113,  114,  115,  116,
 /*   420 */   105,  106,  106,  120,  121,  122,   35,  111,   71,   95,
 /*   430 */   127,  128,  129,  130,  131,   83,   79,  134,   26,   82,
 /*   440 */   106,   35,  103,   90,   87,   88,   89,   90,   90,   92,
 /*   450 */    93,   94,   95,   96,   97,   98,   99,  100,  101,  102,
 /*   460 */    25,    2,   26,  106,  110,  104,  104,  104,  132,  112,
 /*   470 */   113,  114,  115,  116,  132,  104,  104,  120,  121,  122,
 /*   480 */    70,   61,  135,  135,  127,  128,  129,  130,  131,   18,
 /*   490 */    19,  134,   20,   21,   22,   24,   25,   26,   27,   95,
 /*   500 */    28,  135,  135,   32,   32,   34,   35,   36,   36,   38,
 /*   510 */   106,  135,   41,   42,   43,   44,   45,   46,   47,   48,
 /*   520 */    49,   95,   18,   19,  135,  135,  135,  135,   24,   25,
 /*   530 */    26,   60,  106,   62,   63,   64,   32,   66,   67,   68,
 /*   540 */    36,  135,   38,   95,  135,   41,   42,   43,   44,   45,
 /*   550 */    18,   19,   48,   49,  106,  135,   24,   25,   26,   27,
 /*   560 */   112,  135,  135,  135,   32,  135,   34,   35,   36,  135,
 /*   570 */    38,  135,  135,   41,   42,   43,   44,   45,   46,   47,
 /*   580 */    48,   49,   13,   14,   15,   16,   17,   18,   19,   20,
 /*   590 */    21,   22,   60,   95,   62,   63,   64,   28,   66,   67,
 /*   600 */    68,   32,   95,  105,  106,   36,   37,  135,  135,  135,
 /*   610 */    95,   18,   19,  106,  135,  108,  109,   24,   25,   26,
 /*   620 */    27,  106,  135,  108,  109,   32,  135,   34,  135,   36,
 /*   630 */   135,   38,   95,  135,   41,   42,   43,   44,   45,   46,
 /*   640 */    47,   48,   49,  106,   18,   19,   20,   21,   22,  135,
 /*   650 */   135,  135,  135,   60,   28,   62,   63,   64,   32,   66,
 /*   660 */    67,   68,   36,    7,    8,    9,   10,   11,   12,   13,
 /*   670 */    14,   15,   16,   17,   18,   19,   20,   21,   22,   95,
 /*   680 */    95,  135,  135,  135,   28,    0,  135,  135,   32,   33,
 /*   690 */   106,  106,   36,  108,  109,  111,    7,    8,    9,   10,
 /*   700 */    11,   12,   13,   14,   15,   16,   17,   18,   19,   20,
 /*   710 */    21,   22,  135,   95,   29,  135,   31,   28,  135,   34,
 /*   720 */   135,   32,   18,   19,  106,   36,  108,  109,   24,   25,
 /*   730 */    26,   46,   47,   95,  135,  135,   32,  135,  135,  135,
 /*   740 */    36,  135,   38,  105,  106,   41,   42,   43,   44,   45,
 /*   750 */    46,   47,   48,   49,   13,   14,   15,   16,   17,   18,
 /*   760 */    19,   20,   21,   22,   95,    5,  135,  135,  135,   28,
 /*   770 */    95,   95,   95,   32,  105,  106,  135,   36,   18,   19,
 /*   780 */   105,  106,  106,  106,   24,   25,   26,  111,  111,   48,
 /*   790 */    49,  135,   32,  135,  135,  135,   36,  135,   38,  135,
 /*   800 */   135,   41,   42,   43,   44,   45,   75,   76,   77,   78,
 /*   810 */    79,   80,   81,   82,  135,   84,  135,   18,   19,   95,
 /*   820 */    89,  135,   95,   24,   25,   26,  135,  135,   95,   69,
 /*   830 */   106,   32,   33,  106,  135,   36,  135,   38,   39,  106,
 /*   840 */    41,   42,   43,   44,   45,   13,   14,   15,   16,   17,
 /*   850 */    18,   19,   20,   21,   22,  135,   95,  135,  135,  135,
 /*   860 */    28,   95,  135,  135,   32,   33,  135,  106,   36,  108,
 /*   870 */   109,  135,  106,   95,   13,   14,   15,   16,   17,   18,
 /*   880 */    19,   20,   21,   22,  106,    1,    2,  135,   95,   28,
 /*   890 */   135,  135,   95,   32,   18,   19,  135,   36,   37,  106,
 /*   900 */    24,   25,   26,  106,  111,  135,  135,  135,   32,  135,
 /*   910 */   135,   95,   36,   95,   38,   39,   32,   41,   42,   43,
 /*   920 */    44,   45,  106,  135,  106,  135,  135,  111,  135,  111,
 /*   930 */   135,   79,  135,  135,   50,   51,   52,   53,   54,   55,
 /*   940 */    56,   57,   58,   59,   92,   93,   94,   95,   13,   14,
 /*   950 */    15,   16,   17,   18,   19,   20,   21,   22,  106,  135,
 /*   960 */   135,   95,  135,   28,  112,  113,  135,   32,  135,  135,
 /*   970 */   135,   36,  106,  135,   79,  123,  124,   13,   14,   15,
 /*   980 */    16,   17,   18,   19,   20,   21,   22,   92,   93,   94,
 /*   990 */    95,   95,   28,  135,  135,   95,   32,   18,   19,   95,
 /*  1000 */    36,  106,  106,   24,   25,   26,  106,  112,  113,  135,
 /*  1010 */   106,   32,  135,  135,   95,   36,   95,   38,  123,  135,
 /*  1020 */    41,   42,   43,   44,   45,  106,  135,  106,  135,  135,
 /*  1030 */    18,   19,  111,    1,    2,   95,   24,   25,   26,  135,
 /*  1040 */    95,   95,  135,  135,   32,  135,  106,   95,   36,  135,
 /*  1050 */    38,  106,  106,   41,   42,   43,   44,   45,  106,   14,
 /*  1060 */    15,   16,   17,   18,   19,   20,   21,   22,    1,    2,
 /*  1070 */   135,  135,  135,   28,  135,  135,  135,   32,  135,  135,
 /*  1080 */   135,   36,   50,   51,   52,   53,   54,   55,   56,   57,
 /*  1090 */    58,   59,    1,   15,   16,   17,   18,   19,   20,   21,
 /*  1100 */    22,   95,   95,  135,   95,  135,   28,  135,  135,  135,
 /*  1110 */    32,  135,  106,  106,   36,  106,   95,   50,   51,   52,
 /*  1120 */    53,   54,   55,   56,   57,   58,   59,  106,   95,   95,
 /*  1130 */   135,  135,  135,  135,  135,  135,  135,  135,  135,  106,
 /*  1140 */   106,   50,   51,   52,   53,   54,   55,   56,   57,   58,
 /*  1150 */    59,  135,  135,  135,   95,   95,   95,   95,   16,   17,
 /*  1160 */    18,   19,   20,   21,   22,  106,  106,  106,  106,   95,
 /*  1170 */    28,  135,  135,  135,   32,  135,  135,   95,   36,   95,
 /*  1180 */   106,  135,  135,  135,  135,  135,  135,  135,  106,  135,
 /*  1190 */   106,
};
#define YY_SHIFT_USE_DFLT (-25)
#define YY_SHIFT_COUNT (230)
#define YY_SHIFT_MIN   (-24)
#define YY_SHIFT_MAX   (1142)
static const short yy_shift_ofst[] = {
 /*     0 */   -25,  532,  471,  593,  593,  593,  593,  593,  593,  593,
 /*    10 */   704,  685,  704,  504,  504,  799,  876,  876,  876,  876,
 /*    20 */   979,  979,  760,  760,  760,  760,  760,  760,  760,  760,
 /*    30 */   760,  876,  979,  979,  979,  979, 1012,  979,  979,  979,
 /*    40 */   420,  979,  979,  979,  979,  979,  979,  979,  979,  979,
 /*    50 */   979,  979,  979,  979,  979,  979,  979,  979,  979,  979,
 /*    60 */   979,  979,  979,  979,  979,  979,  979,  979,  979,  979,
 /*    70 */   979,  979,  979,  979,  979,  979,  979,  410,  436,  436,
 /*    80 */   436,  410,  410,  436,  436,  436,  459,  435,  406,  406,
 /*    90 */   412,  656,  689,  741,  861,  832,  569,  935,  935,  964,
 /*   100 */   935,  935,  935,  935,  935,  935,  935,  935,  935,  935,
 /*   110 */   935,  935,  935,  935,  935,  935,  935,  935,  935,  935,
 /*   120 */   884, 1067, 1032, 1045, 1091, 1078, 1142,  626,  626,  472,
 /*   130 */   472,   35,  247,  243,  140,  136,    1,  -22,  -22,  -22,
 /*   140 */   -22,  -22,  -22,  125,  119,  139,   88,   90,   64,   45,
 /*   150 */    71,  113,  -24,  -21,  285,  285,  391,  386,  381,  380,
 /*   160 */   376,  373,  405,  366,  387,  356,  351,  343,  313,  337,
 /*   170 */   285,  285,  285,  341,  335,  328,  269,  327,  323,  331,
 /*   180 */   326,  325,  318,  322,  320,  302,  308,  301,  292,  296,
 /*   190 */   274,  280,  273,  299,  268,  267,  285,  249,  244,  184,
 /*   200 */   245,  230,  236,  229,  218,  233,  226,  191,  184,  175,
 /*   210 */   157,  225,  221,  207,  206,  200,  185,  172,  167,  166,
 /*   220 */   178,  135,  146,  129,  133,  128,   46,   78,   66,   25,
 /*   230 */    13,
};
#define YY_REDUCE_USE_DFLT (-94)
#define YY_REDUCE_COUNT (90)
#define YY_REDUCE_MIN   (-93)
#define YY_REDUCE_MAX   (1084)
static const short yy_reduce_ofst[] = {
 /*     0 */   124,  357,  303,  250,  196,  143,   89,   36,  -18,  -71,
 /*    10 */   852,  731,  895,  -93,  -58,  761,  618,  585,  515,  507,
 /*    20 */   101,   -6,  921,  818,  816,  793,  677,  676,  584,  316,
 /*    30 */   209,   11,  675,  669,  638,  498,  448,  315,  281,  208,
 /*    40 */   -32, 1084, 1082, 1074, 1062, 1061, 1060, 1059, 1034, 1033,
 /*    50 */  1021, 1009, 1007, 1006,  952,  946,  945,  940,  919,  904,
 /*    60 */   900,  896,  866,  797,  778,  766,  733,  727,  724,  537,
 /*    70 */   426,  404,  334,  227,  173,  120,  118,   14,   70,  372,
 /*    80 */   371,  342,  336,  363,  362,  361,  354,  339,  358,  353,
 /*    90 */   352,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   334,  503,  503,  503,  503,  503,  503,  503,  503,  503,
 /*    10 */   482,  506,  506,  485,  506,  506,  399,  399,  399,  399,
 /*    20 */   388,  388,  506,  506,  506,  506,  506,  506,  506,  506,
 /*    30 */   506,  506,  506,  506,  506,  506,  506,  506,  506,  506,
 /*    40 */   470,  506,  506,  506,  506,  506,  506,  506,  506,  506,
 /*    50 */   506,  506,  506,  506,  506,  506,  506,  506,  506,  506,
 /*    60 */   506,  506,  506,  506,  506,  506,  506,  506,  506,  506,
 /*    70 */   506,  506,  506,  506,  506,  506,  506,  506,  382,  506,
 /*    80 */   506,  505,  504,  506,  506,  506,  406,  506,  506,  506,
 /*    90 */   506,  426,  426,  506,  506,  506,  506,  451,  449,  506,
 /*   100 */   462,  461,  460,  459,  458,  457,  456,  455,  454,  453,
 /*   110 */   447,  433,  432,  431,  430,  429,  428,  386,  395,  397,
 /*   120 */   392,  394,  393,  421,  445,  422,  420,  419,  418,  414,
 /*   130 */   413,  506,  506,  506,  506,  506,  506,  425,  424,  423,
 /*   140 */   417,  416,  415,  506,  437,  506,  506,  506,  506,  437,
 /*   150 */   506,  392,  403,  346,  441,  439,  374,  506,  506,  506,
 /*   160 */   506,  506,  486,  506,  481,  506,  506,  506,  469,  506,
 /*   170 */   448,  440,  438,  506,  506,  506,  506,  506,  506,  435,
 /*   180 */   506,  506,  506,  506,  506,  506,  506,  506,  506,  506,
 /*   190 */   506,  506,  506,  400,  391,  506,  389,  506,  506,  378,
 /*   200 */   506,  403,  506,  392,  403,  506,  506,  506,  506,  506,
 /*   210 */   506,  506,  506,  506,  506,  506,  506,  506,  506,  506,
 /*   220 */   383,  347,  506,  506,  506,  506,  506,  506,  506,  506,
 /*   230 */   506,  375,  359,  471,  502,  501,  500,  496,  495,  494,
 /*   240 */   493,  492,  491,  490,  489,  484,  483,  488,  487,  480,
 /*   250 */   479,  478,  477,  476,  475,  474,  473,  472,  468,  467,
 /*   260 */   466,  465,  464,  463,  446,  452,  450,  401,  402,  407,
 /*   270 */   405,  408,  499,  497,  436,  434,  427,  498,  412,  411,
 /*   280 */   410,  409,  398,  396,  387,  384,  379,  404,  394,  393,
 /*   290 */   391,  390,  377,  376,  373,  372,  371,  370,  369,  368,
 /*   300 */   367,  385,  366,  365,  364,  363,  362,  361,  360,  358,
 /*   310 */   357,  356,  354,  355,  353,  352,  351,  350,  348,  381,
 /*   320 */   380,  349,  345,  344,  343,  342,  341,  340,  339,  338,
 /*   330 */   337,  336,  335,
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
  "LPAREN",        "RPAREN",        "LBRACKET",      "RBRACKET",    
  "LSQBRACKET",    "RSQBRACKET",    "KILLS",         "STRING",      
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
  "vdefAssign_global_stmt",  "cdef_global_stmt",  "blockStmt",     "dottedName",  
  "fdef_header",   "nameList",      "stmt",          "bodyStmt",    
  "return_stmt",   "lbracket",      "rbracket",      "bodyStmtList",
  "vdefAssign_stmt",  "cdef_stmt",     "assign_stmt",   "funcexpr",    
  "actionStmt",    "if_stmt",       "while_stmt",    "for_stmt",    
  "foreach_stmt",  "continue_stmt",  "break_stmt",    "numList_nonEmpty",
  "nameList_nonEmpty",  "exprList_nonEmpty",  "expr",          "exprList",    
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
 /*   6 */ "chunk ::= vdef_stmt SEMICOLON",
 /*   7 */ "chunk ::= vdefAssign_global_stmt SEMICOLON",
 /*   8 */ "chunk ::= cdef_global_stmt SEMICOLON",
 /*   9 */ "chunk ::= blockStmt",
 /*  10 */ "dottedName ::= NAME",
 /*  11 */ "dottedName ::= dottedName PERIOD NAME",
 /*  12 */ "import_chunk ::= IMPORT dottedName AS NAME",
 /*  13 */ "import_chunk ::= IMPORT dottedName",
 /*  14 */ "fdef_header ::= FUNCTION NAME LPAREN nameList RPAREN",
 /*  15 */ "fdef_chunk ::= fdef_header stmt",
 /*  16 */ "fdecl_chunk ::= FUNCTION NAME LPAREN nameList RPAREN SEMICOLON",
 /*  17 */ "stmt ::= error SEMICOLON",
 /*  18 */ "stmt ::= bodyStmt",
 /*  19 */ "stmt ::= return_stmt SEMICOLON",
 /*  20 */ "lbracket ::= LBRACKET",
 /*  21 */ "rbracket ::= RBRACKET",
 /*  22 */ "blockStmt ::= lbracket RBRACKET",
 /*  23 */ "blockStmt ::= lbracket return_stmt SEMICOLON rbracket",
 /*  24 */ "blockStmt ::= lbracket bodyStmtList rbracket",
 /*  25 */ "blockStmt ::= lbracket bodyStmtList return_stmt SEMICOLON rbracket",
 /*  26 */ "blockStmt ::= lbracket error RBRACKET",
 /*  27 */ "bodyStmt ::= blockStmt",
 /*  28 */ "bodyStmt ::= SEMICOLON",
 /*  29 */ "bodyStmt ::= vdef_stmt SEMICOLON",
 /*  30 */ "bodyStmt ::= vdefAssign_stmt SEMICOLON",
 /*  31 */ "bodyStmt ::= cdef_stmt SEMICOLON",
 /*  32 */ "bodyStmt ::= assign_stmt SEMICOLON",
 /*  33 */ "bodyStmt ::= funcexpr SEMICOLON",
 /*  34 */ "bodyStmt ::= actionStmt",
 /*  35 */ "bodyStmt ::= if_stmt",
 /*  36 */ "bodyStmt ::= while_stmt",
 /*  37 */ "bodyStmt ::= for_stmt",
 /*  38 */ "bodyStmt ::= foreach_stmt",
 /*  39 */ "bodyStmt ::= continue_stmt SEMICOLON",
 /*  40 */ "bodyStmt ::= break_stmt SEMICOLON",
 /*  41 */ "bodyStmtList ::= error",
 /*  42 */ "bodyStmtList ::= bodyStmt",
 /*  43 */ "bodyStmtList ::= bodyStmtList bodyStmt",
 /*  44 */ "bodyStmtList ::= bodyStmtList error",
 /*  45 */ "numList_nonEmpty ::= NUMBER",
 /*  46 */ "numList_nonEmpty ::= numList_nonEmpty COMMA NUMBER",
 /*  47 */ "nameList_nonEmpty ::= NAME",
 /*  48 */ "nameList_nonEmpty ::= nameList_nonEmpty COMMA NAME",
 /*  49 */ "nameList ::=",
 /*  50 */ "nameList ::= nameList_nonEmpty",
 /*  51 */ "exprList_nonEmpty ::= funcexpr LSQBRACKET LSQBRACKET numList_nonEmpty RSQBRACKET RSQBRACKET",
 /*  52 */ "expr ::= funcexpr LSQBRACKET LSQBRACKET NUMBER RSQBRACKET RSQBRACKET",
 /*  53 */ "exprList_nonEmpty ::= expr",
 /*  54 */ "exprList_nonEmpty ::= exprList_nonEmpty COMMA exprList_nonEmpty",
 /*  55 */ "exprList ::=",
 /*  56 */ "exprList ::= exprList_nonEmpty",
 /*  57 */ "expr ::= NUMBER",
 /*  58 */ "expr ::= KILLS",
 /*  59 */ "expr ::= NAME",
 /*  60 */ "expr ::= expr PERIOD NAME",
 /*  61 */ "expr ::= expr LSQBRACKET expr RSQBRACKET",
 /*  62 */ "fArgs_nonEmpty ::= expr",
 /*  63 */ "fArgs_nonEmpty ::= STRING",
 /*  64 */ "fArgs_nonEmpty ::= NAME ASSIGN expr",
 /*  65 */ "fArgs_nonEmpty ::= fArgs_nonEmpty COMMA fArgs_nonEmpty",
 /*  66 */ "fArgs ::=",
 /*  67 */ "fArgs ::= fArgs_nonEmpty",
 /*  68 */ "funcexpr ::= NAME LPAREN fArgs RPAREN",
 /*  69 */ "funcexpr ::= expr LPAREN fArgs RPAREN",
 /*  70 */ "expr ::= funcexpr",
 /*  71 */ "expr ::= LPAREN expr RPAREN",
 /*  72 */ "commaSkippable ::= COMMA",
 /*  73 */ "commaSkippable ::=",
 /*  74 */ "expr ::= LSQBRACKET exprList commaSkippable RSQBRACKET",
 /*  75 */ "expr ::= L2V LPAREN lexpr RPAREN",
 /*  76 */ "expr ::= MAPSTRING LPAREN STRING RPAREN",
 /*  77 */ "expr ::= UNIT LPAREN STRING RPAREN",
 /*  78 */ "expr ::= SWITCH LPAREN STRING RPAREN",
 /*  79 */ "expr ::= LOCATION LPAREN STRING RPAREN",
 /*  80 */ "expr ::= expr PLUS expr",
 /*  81 */ "expr ::= expr MINUS expr",
 /*  82 */ "expr ::= expr MULTIPLY expr",
 /*  83 */ "expr ::= expr DIVIDE expr",
 /*  84 */ "expr ::= expr MOD expr",
 /*  85 */ "expr ::= expr LSHIFT expr",
 /*  86 */ "expr ::= expr RSHIFT expr",
 /*  87 */ "expr ::= expr BITAND expr",
 /*  88 */ "expr ::= expr BITOR expr",
 /*  89 */ "expr ::= expr BITXOR expr",
 /*  90 */ "expr ::= PLUS expr",
 /*  91 */ "expr ::= MINUS expr",
 /*  92 */ "expr ::= BITNOT expr",
 /*  93 */ "lexpr ::= expr",
 /*  94 */ "lexpr ::= LPAREN lexpr RPAREN",
 /*  95 */ "lexpr ::= expr EQ expr",
 /*  96 */ "lexpr ::= expr NE expr",
 /*  97 */ "lexpr ::= expr LE expr",
 /*  98 */ "lexpr ::= expr LT expr",
 /*  99 */ "lexpr ::= expr GE expr",
 /* 100 */ "lexpr ::= expr GT expr",
 /* 101 */ "lexpr ::= lexpr LAND lexpr",
 /* 102 */ "lexpr ::= lexpr LOR lexpr",
 /* 103 */ "lexpr ::= LNOT lexpr",
 /* 104 */ "vdef_stmt ::= VAR nameList_nonEmpty",
 /* 105 */ "vdefAssign_stmt ::= VAR nameList_nonEmpty ASSIGN exprList_nonEmpty",
 /* 106 */ "vdefAssign_global_stmt ::= VAR nameList_nonEmpty ASSIGN exprList_nonEmpty",
 /* 107 */ "cdef_stmt ::= CONST nameList_nonEmpty ASSIGN exprList_nonEmpty",
 /* 108 */ "cdef_global_stmt ::= CONST nameList_nonEmpty ASSIGN exprList_nonEmpty",
 /* 109 */ "lvalue ::= NAME",
 /* 110 */ "lvalue ::= expr LSQBRACKET expr RSQBRACKET",
 /* 111 */ "lvalue ::= expr PERIOD NAME",
 /* 112 */ "lvalueList_nonEmpty ::= lvalue",
 /* 113 */ "lvalueList_nonEmpty ::= lvalueList_nonEmpty COMMA lvalue",
 /* 114 */ "assign_stmt ::= lvalue ASSIGN expr",
 /* 115 */ "assign_stmt ::= lvalueList_nonEmpty ASSIGN exprList_nonEmpty",
 /* 116 */ "assign_stmt ::= INC expr",
 /* 117 */ "assign_stmt ::= expr INC",
 /* 118 */ "assign_stmt ::= DEC expr",
 /* 119 */ "assign_stmt ::= expr DEC",
 /* 120 */ "assign_stmt ::= lvalue IADD expr",
 /* 121 */ "assign_stmt ::= lvalue ISUB expr",
 /* 122 */ "assign_stmt ::= lvalue IMUL expr",
 /* 123 */ "assign_stmt ::= lvalue IDIV expr",
 /* 124 */ "assign_stmt ::= lvalue IMOD expr",
 /* 125 */ "assign_stmt ::= lvalue ILSH expr",
 /* 126 */ "assign_stmt ::= lvalue IRSH expr",
 /* 127 */ "assign_stmt ::= lvalue IBND expr",
 /* 128 */ "assign_stmt ::= lvalue IBOR expr",
 /* 129 */ "assign_stmt ::= lvalue IBXR expr",
 /* 130 */ "if_start ::= IF",
 /* 131 */ "if_header ::= if_start LPAREN lexpr RPAREN",
 /* 132 */ "if_block ::= if_header stmt",
 /* 133 */ "elif_start ::= ELSE IF",
 /* 134 */ "elif_header ::= elif_start LPAREN lexpr RPAREN",
 /* 135 */ "if_block ::= if_block elif_header stmt",
 /* 136 */ "else_header ::= ELSE",
 /* 137 */ "if_stmt ::= if_block",
 /* 138 */ "if_stmt ::= if_block else_header stmt",
 /* 139 */ "while_start ::= WHILE",
 /* 140 */ "while_header ::= while_start LPAREN lexpr RPAREN",
 /* 141 */ "while_stmt ::= while_header stmt",
 /* 142 */ "for_opener ::= FOR LPAREN",
 /* 143 */ "for_init_stmt_nonEmpty ::= vdef_stmt",
 /* 144 */ "for_init_stmt_nonEmpty ::= vdefAssign_stmt",
 /* 145 */ "for_init_stmt_nonEmpty ::= cdef_stmt",
 /* 146 */ "for_init_stmt_nonEmpty ::= assign_stmt",
 /* 147 */ "for_init_stmt_nonEmpty ::= for_init_stmt_nonEmpty COMMA for_init_stmt_nonEmpty",
 /* 148 */ "for_init_stmt ::= for_init_stmt_nonEmpty",
 /* 149 */ "for_init_stmt ::=",
 /* 150 */ "for_action_stmt_nonEmpty ::= assign_stmt",
 /* 151 */ "for_action_stmt_nonEmpty ::= for_action_stmt_nonEmpty COMMA for_action_stmt_nonEmpty",
 /* 152 */ "for_action_stmt ::=",
 /* 153 */ "for_action_stmt ::= for_action_stmt_nonEmpty",
 /* 154 */ "for_header1 ::= for_opener for_init_stmt SEMICOLON",
 /* 155 */ "for_header2 ::= for_header1 lexpr SEMICOLON",
 /* 156 */ "for_header ::= for_header2 for_action_stmt RPAREN",
 /* 157 */ "for_stmt ::= for_header stmt",
 /* 158 */ "foreach_opener ::= FOREACH LPAREN",
 /* 159 */ "foreach_header ::= foreach_opener nameList_nonEmpty COLON exprList_nonEmpty RPAREN",
 /* 160 */ "foreach_stmt ::= foreach_header stmt",
 /* 161 */ "continue_stmt ::= CONTINUE",
 /* 162 */ "break_stmt ::= BREAK",
 /* 163 */ "return_stmt ::= RETURN exprList",
 /* 164 */ "lexpr ::= CONDITIONNAME LPAREN fArgs RPAREN",
 /* 165 */ "lexpr ::= KILLS LPAREN fArgs RPAREN",
 /* 166 */ "lexpr ::= CONDITIONNAME LPAREN RPAREN",
 /* 167 */ "action ::= ACTIONNAME LPAREN fArgs RPAREN SEMICOLON",
 /* 168 */ "actions ::= action action",
 /* 169 */ "actions ::= actions action",
 /* 170 */ "actionStmt_start ::=",
 /* 171 */ "actionStmt ::= actionStmt_start action",
 /* 172 */ "actionStmt ::= actionStmt_start actions",
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
#line 39 "parser\\epparser.lemon"
 delete (yypminor->yy0); 
#line 889 "parser\\epparser.c"
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
  { 83, 1 },
  { 83, 3 },
  { 76, 4 },
  { 76, 2 },
  { 84, 5 },
  { 77, 2 },
  { 78, 6 },
  { 86, 2 },
  { 86, 1 },
  { 86, 2 },
  { 89, 1 },
  { 90, 1 },
  { 82, 2 },
  { 82, 4 },
  { 82, 3 },
  { 82, 5 },
  { 82, 3 },
  { 87, 1 },
  { 87, 1 },
  { 87, 2 },
  { 87, 2 },
  { 87, 2 },
  { 87, 2 },
  { 87, 2 },
  { 87, 1 },
  { 87, 1 },
  { 87, 1 },
  { 87, 1 },
  { 87, 1 },
  { 87, 2 },
  { 87, 2 },
  { 91, 1 },
  { 91, 1 },
  { 91, 2 },
  { 91, 2 },
  { 103, 1 },
  { 103, 3 },
  { 104, 1 },
  { 104, 3 },
  { 85, 0 },
  { 85, 1 },
  { 105, 6 },
  { 106, 6 },
  { 105, 1 },
  { 105, 3 },
  { 107, 0 },
  { 107, 1 },
  { 106, 1 },
  { 106, 1 },
  { 106, 1 },
  { 106, 3 },
  { 106, 4 },
  { 108, 1 },
  { 108, 1 },
  { 108, 3 },
  { 108, 3 },
  { 109, 0 },
  { 109, 1 },
  { 95, 4 },
  { 95, 4 },
  { 106, 1 },
  { 106, 3 },
  { 110, 1 },
  { 110, 0 },
  { 106, 4 },
  { 106, 4 },
  { 106, 4 },
  { 106, 4 },
  { 106, 4 },
  { 106, 4 },
  { 106, 3 },
  { 106, 3 },
  { 106, 3 },
  { 106, 3 },
  { 106, 3 },
  { 106, 3 },
  { 106, 3 },
  { 106, 3 },
  { 106, 3 },
  { 106, 3 },
  { 106, 2 },
  { 106, 2 },
  { 106, 2 },
  { 111, 1 },
  { 111, 3 },
  { 111, 3 },
  { 111, 3 },
  { 111, 3 },
  { 111, 3 },
  { 111, 3 },
  { 111, 3 },
  { 111, 3 },
  { 111, 3 },
  { 111, 2 },
  { 79, 2 },
  { 92, 4 },
  { 80, 4 },
  { 93, 4 },
  { 81, 4 },
  { 112, 1 },
  { 112, 4 },
  { 112, 3 },
  { 113, 1 },
  { 113, 3 },
  { 94, 3 },
  { 94, 3 },
  { 94, 2 },
  { 94, 2 },
  { 94, 2 },
  { 94, 2 },
  { 94, 3 },
  { 94, 3 },
  { 94, 3 },
  { 94, 3 },
  { 94, 3 },
  { 94, 3 },
  { 94, 3 },
  { 94, 3 },
  { 94, 3 },
  { 94, 3 },
  { 114, 1 },
  { 115, 4 },
  { 116, 2 },
  { 117, 2 },
  { 118, 4 },
  { 116, 3 },
  { 119, 1 },
  { 97, 1 },
  { 97, 3 },
  { 120, 1 },
  { 121, 4 },
  { 98, 2 },
  { 122, 2 },
  { 123, 1 },
  { 123, 1 },
  { 123, 1 },
  { 123, 1 },
  { 123, 3 },
  { 124, 1 },
  { 124, 0 },
  { 125, 1 },
  { 125, 3 },
  { 126, 0 },
  { 126, 1 },
  { 127, 3 },
  { 128, 3 },
  { 129, 3 },
  { 99, 2 },
  { 130, 2 },
  { 131, 5 },
  { 100, 2 },
  { 101, 1 },
  { 102, 1 },
  { 88, 2 },
  { 111, 4 },
  { 111, 4 },
  { 111, 3 },
  { 132, 5 },
  { 133, 2 },
  { 133, 2 },
  { 134, 0 },
  { 96, 2 },
  { 96, 2 },
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
#line 74 "parser\\epparser.lemon"
{
    throw_error(48993, "Misplaced block statement");
}
#line 1359 "parser\\epparser.c"
        break;
      case 10: /* dottedName ::= NAME */
      case 45: /* numList_nonEmpty ::= NUMBER */ yytestcase(yyruleno==45);
      case 47: /* nameList_nonEmpty ::= NAME */ yytestcase(yyruleno==47);
      case 50: /* nameList ::= nameList_nonEmpty */ yytestcase(yyruleno==50);
      case 53: /* exprList_nonEmpty ::= expr */ yytestcase(yyruleno==53);
      case 56: /* exprList ::= exprList_nonEmpty */ yytestcase(yyruleno==56);
      case 57: /* expr ::= NUMBER */ yytestcase(yyruleno==57);
      case 62: /* fArgs_nonEmpty ::= expr */ yytestcase(yyruleno==62);
      case 63: /* fArgs_nonEmpty ::= STRING */ yytestcase(yyruleno==63);
      case 67: /* fArgs ::= fArgs_nonEmpty */ yytestcase(yyruleno==67);
      case 70: /* expr ::= funcexpr */ yytestcase(yyruleno==70);
      case 93: /* lexpr ::= expr */ yytestcase(yyruleno==93);
      case 112: /* lvalueList_nonEmpty ::= lvalue */ yytestcase(yyruleno==112);
#line 80 "parser\\epparser.lemon"
{ yygotominor.yy0 = yymsp[0].minor.yy0; }
#line 1376 "parser\\epparser.c"
        break;
      case 11: /* dottedName ::= dottedName PERIOD NAME */
#line 81 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = yymsp[-2].minor.yy0->data + "." + yymsp[0].minor.yy0->data;
    delete yymsp[-2].minor.yy0;
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1385 "parser\\epparser.c"
        break;
      case 12: /* import_chunk ::= IMPORT dottedName AS NAME */
#line 87 "parser\\epparser.lemon"
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
#line 1401 "parser\\epparser.c"
        break;
      case 13: /* import_chunk ::= IMPORT dottedName */
#line 100 "parser\\epparser.lemon"
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
#line 1417 "parser\\epparser.c"
        break;
      case 14: /* fdef_header ::= FUNCTION NAME LPAREN nameList RPAREN */
#line 114 "parser\\epparser.lemon"
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
#line 1450 "parser\\epparser.c"
        break;
      case 15: /* fdef_chunk ::= fdef_header stmt */
#line 144 "parser\\epparser.lemon"
{
    if(MAP_DEBUG){
        ps->gen << "MDBG_POPF()" << std::endl;
    }
    ps->gen.unindent(true);
    ps->closure.popScope();
    currentFunction = "";
}
#line 1462 "parser\\epparser.c"
        break;
      case 16: /* fdecl_chunk ::= FUNCTION NAME LPAREN nameList RPAREN SEMICOLON */
#line 153 "parser\\epparser.lemon"
{
    // Preprocess yymsp[-4].minor.yy0
    funcNamePreprocess(yymsp[-4].minor.yy0->data);
    if(!ps->closure.declareFunction(yymsp[-4].minor.yy0->data)) {
        throw_error(72461, "Declaring function with non-function yymsp[-4].minor.yy0 " + yymsp[-4].minor.yy0->data, yymsp[-4].minor.yy0->line);
    }
}
#line 1473 "parser\\epparser.c"
        break;
      case 17: /* stmt ::= error SEMICOLON */
#line 162 "parser\\epparser.lemon"
{ throw_error(6974, "Error while parsing statement", yymsp[0].minor.yy0->line); delete yymsp[0].minor.yy0; }
#line 1478 "parser\\epparser.c"
        break;
      case 20: /* lbracket ::= LBRACKET */
#line 168 "parser\\epparser.lemon"
{ ps->closure.pushScope(); }
#line 1483 "parser\\epparser.c"
        break;
      case 21: /* rbracket ::= RBRACKET */
#line 169 "parser\\epparser.lemon"
{ ps->closure.popScope(); }
#line 1488 "parser\\epparser.c"
        break;
      case 22: /* blockStmt ::= lbracket RBRACKET */
#line 171 "parser\\epparser.lemon"
{
    ps->closure.popScope();
}
#line 1495 "parser\\epparser.c"
        break;
      case 26: /* blockStmt ::= lbracket error RBRACKET */
#line 177 "parser\\epparser.lemon"
{
    throw_error(6298, "Block not terminated properly.", yymsp[0].minor.yy0->line);
    ps->closure.popScope();
    delete yymsp[0].minor.yy0;
}
#line 1504 "parser\\epparser.c"
        break;
      case 33: /* bodyStmt ::= funcexpr SEMICOLON */
#line 189 "parser\\epparser.lemon"
{ ps->gen << yymsp[-1].minor.yy0->data << std::endl; }
#line 1509 "parser\\epparser.c"
        break;
      case 41: /* bodyStmtList ::= error */
      case 44: /* bodyStmtList ::= bodyStmtList error */ yytestcase(yyruleno==44);
#line 199 "parser\\epparser.lemon"
{
    throw_error(8510, "Incomplete statement");
}
#line 1517 "parser\\epparser.c"
        break;
      case 46: /* numList_nonEmpty ::= numList_nonEmpty COMMA NUMBER */
      case 48: /* nameList_nonEmpty ::= nameList_nonEmpty COMMA NAME */ yytestcase(yyruleno==48);
      case 113: /* lvalueList_nonEmpty ::= lvalueList_nonEmpty COMMA lvalue */ yytestcase(yyruleno==113);
#line 212 "parser\\epparser.lemon"
{ yygotominor.yy0 = commaConcat(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1524 "parser\\epparser.c"
        break;
      case 49: /* nameList ::= */
      case 55: /* exprList ::= */ yytestcase(yyruleno==55);
      case 66: /* fArgs ::= */ yytestcase(yyruleno==66);
#line 215 "parser\\epparser.lemon"
{ yygotominor.yy0 = genEmpty(); }
#line 1531 "parser\\epparser.c"
        break;
      case 51: /* exprList_nonEmpty ::= funcexpr LSQBRACKET LSQBRACKET numList_nonEmpty RSQBRACKET RSQBRACKET */
#line 218 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "_SRET(" + yymsp[-5].minor.yy0->data + ", [" + yymsp[-2].minor.yy0->data + "])";
    delete yymsp[-5].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1540 "parser\\epparser.c"
        break;
      case 52: /* expr ::= funcexpr LSQBRACKET LSQBRACKET NUMBER RSQBRACKET RSQBRACKET */
#line 225 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-5].minor.yy0->data + "[" + yymsp[-2].minor.yy0->data + "]";
    delete yymsp[-5].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1549 "parser\\epparser.c"
        break;
      case 54: /* exprList_nonEmpty ::= exprList_nonEmpty COMMA exprList_nonEmpty */
#line 233 "parser\\epparser.lemon"
{ yygotominor.yy0 = new Token((yymsp[-2].minor.yy0->data) + ", " + (yymsp[0].minor.yy0->data), yymsp[0].minor.yy0); delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1554 "parser\\epparser.c"
        break;
      case 58: /* expr ::= KILLS */
#line 240 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = "4";
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1562 "parser\\epparser.c"
        break;
      case 59: /* expr ::= NAME */
#line 245 "parser\\epparser.lemon"
{
    checkIsRValue(yymsp[0].minor.yy0->data, yymsp[0].minor.yy0->line);
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1570 "parser\\epparser.c"
        break;
      case 60: /* expr ::= expr PERIOD NAME */
#line 250 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + "." + yymsp[0].minor.yy0->data;
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1579 "parser\\epparser.c"
        break;
      case 61: /* expr ::= expr LSQBRACKET expr RSQBRACKET */
#line 256 "parser\\epparser.lemon"
{
    yymsp[-3].minor.yy0->data = yymsp[-3].minor.yy0->data + "[" + yymsp[-1].minor.yy0->data + "]";
    delete yymsp[-1].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 1588 "parser\\epparser.c"
        break;
      case 64: /* fArgs_nonEmpty ::= NAME ASSIGN expr */
#line 265 "parser\\epparser.lemon"
{  // Keyword argument
    yymsp[0].minor.yy0->data = yymsp[-2].minor.yy0->data + "=" + yymsp[0].minor.yy0->data;
    yymsp[0].minor.yy0->type = TOKEN_TEMP;
    yygotominor.yy0 = yymsp[0].minor.yy0;
    delete yymsp[-2].minor.yy0;
}
#line 1598 "parser\\epparser.c"
        break;
      case 65: /* fArgs_nonEmpty ::= fArgs_nonEmpty COMMA fArgs_nonEmpty */
#line 272 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data;
    yymsp[0].minor.yy0->type = TOKEN_TEMP;
    yygotominor.yy0 = yymsp[0].minor.yy0;
    delete yymsp[-2].minor.yy0;
}
#line 1608 "parser\\epparser.c"
        break;
      case 68: /* funcexpr ::= NAME LPAREN fArgs RPAREN */
#line 282 "parser\\epparser.lemon"
{
    functionCalledInMultipleActions = true;

    // Preprocess yymsp[-3].minor.yy0
    funcNamePreprocess(yymsp[-3].minor.yy0->data);
    checkIsFunction(yymsp[-3].minor.yy0->data, yymsp[-3].minor.yy0->line);
    yymsp[-3].minor.yy0->data += "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 1621 "parser\\epparser.c"
        break;
      case 69: /* funcexpr ::= expr LPAREN fArgs RPAREN */
#line 292 "parser\\epparser.lemon"
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
#line 1645 "parser\\epparser.c"
        break;
      case 71: /* expr ::= LPAREN expr RPAREN */
      case 94: /* lexpr ::= LPAREN lexpr RPAREN */ yytestcase(yyruleno==94);
#line 316 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1654 "parser\\epparser.c"
        break;
      case 74: /* expr ::= LSQBRACKET exprList commaSkippable RSQBRACKET */
#line 324 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "_ARR(FlattenList([" + yymsp[-2].minor.yy0->data + "]))";
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1662 "parser\\epparser.c"
        break;
      case 75: /* expr ::= L2V LPAREN lexpr RPAREN */
#line 329 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "_L2V(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1670 "parser\\epparser.c"
        break;
      case 76: /* expr ::= MAPSTRING LPAREN STRING RPAREN */
#line 334 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetStringIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1678 "parser\\epparser.c"
        break;
      case 77: /* expr ::= UNIT LPAREN STRING RPAREN */
#line 339 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "EncodeUnit(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1686 "parser\\epparser.c"
        break;
      case 78: /* expr ::= SWITCH LPAREN STRING RPAREN */
#line 344 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "EncodeSwitch(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1694 "parser\\epparser.c"
        break;
      case 79: /* expr ::= LOCATION LPAREN STRING RPAREN */
#line 349 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetLocationIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1702 "parser\\epparser.c"
        break;
      case 80: /* expr ::= expr PLUS expr */
#line 355 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "+",  yymsp[0].minor.yy0); }
#line 1707 "parser\\epparser.c"
        break;
      case 81: /* expr ::= expr MINUS expr */
#line 356 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "-",  yymsp[0].minor.yy0); }
#line 1712 "parser\\epparser.c"
        break;
      case 82: /* expr ::= expr MULTIPLY expr */
#line 357 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "*",  yymsp[0].minor.yy0); }
#line 1717 "parser\\epparser.c"
        break;
      case 83: /* expr ::= expr DIVIDE expr */
#line 358 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "//", yymsp[0].minor.yy0); }
#line 1722 "parser\\epparser.c"
        break;
      case 84: /* expr ::= expr MOD expr */
#line 359 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "%",  yymsp[0].minor.yy0); }
#line 1727 "parser\\epparser.c"
        break;
      case 85: /* expr ::= expr LSHIFT expr */
#line 360 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = "_LSH(" + yymsp[-2].minor.yy0->data + "," + yymsp[0].minor.yy0->data + ")";
    delete yymsp[-2].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0);
}
#line 1736 "parser\\epparser.c"
        break;
      case 86: /* expr ::= expr RSHIFT expr */
#line 365 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, ">>", yymsp[0].minor.yy0); }
#line 1741 "parser\\epparser.c"
        break;
      case 87: /* expr ::= expr BITAND expr */
#line 366 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "&",  yymsp[0].minor.yy0); }
#line 1746 "parser\\epparser.c"
        break;
      case 88: /* expr ::= expr BITOR expr */
#line 367 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "|",  yymsp[0].minor.yy0); }
#line 1751 "parser\\epparser.c"
        break;
      case 89: /* expr ::= expr BITXOR expr */
#line 368 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "^",  yymsp[0].minor.yy0); }
#line 1756 "parser\\epparser.c"
        break;
      case 90: /* expr ::= PLUS expr */
#line 371 "parser\\epparser.lemon"
{ yymsp[0].minor.yy0->data = "+" + yymsp[0].minor.yy0->data; yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0); }
#line 1761 "parser\\epparser.c"
        break;
      case 91: /* expr ::= MINUS expr */
#line 372 "parser\\epparser.lemon"
{ yymsp[0].minor.yy0->data = "-" + yymsp[0].minor.yy0->data; yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0); }
#line 1766 "parser\\epparser.c"
        break;
      case 92: /* expr ::= BITNOT expr */
#line 373 "parser\\epparser.lemon"
{ yymsp[0].minor.yy0->data = "~" + yymsp[0].minor.yy0->data; yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0); }
#line 1771 "parser\\epparser.c"
        break;
      case 95: /* lexpr ::= expr EQ expr */
#line 383 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "==", yymsp[0].minor.yy0); }
#line 1776 "parser\\epparser.c"
        break;
      case 96: /* lexpr ::= expr NE expr */
#line 384 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genEmpty();
    yygotominor.yy0->line = yymsp[0].minor.yy0->line;

    yygotominor.yy0->type = TOKEN_NE;
    yygotominor.yy0->subToken[0] = yymsp[-2].minor.yy0;
    yygotominor.yy0->subToken[1] = yymsp[0].minor.yy0;
    yygotominor.yy0->data = yymsp[-2].minor.yy0->data + " != " + yymsp[0].minor.yy0->data;
}
#line 1789 "parser\\epparser.c"
        break;
      case 97: /* lexpr ::= expr LE expr */
#line 394 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "<=", yymsp[0].minor.yy0); }
#line 1794 "parser\\epparser.c"
        break;
      case 98: /* lexpr ::= expr LT expr */
#line 395 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "<",  yymsp[0].minor.yy0); }
#line 1799 "parser\\epparser.c"
        break;
      case 99: /* lexpr ::= expr GE expr */
#line 396 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, ">=", yymsp[0].minor.yy0); }
#line 1804 "parser\\epparser.c"
        break;
      case 100: /* lexpr ::= expr GT expr */
#line 397 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, ">" , yymsp[0].minor.yy0); }
#line 1809 "parser\\epparser.c"
        break;
      case 101: /* lexpr ::= lexpr LAND lexpr */
#line 400 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genEmpty();
    yygotominor.yy0->line = yymsp[0].minor.yy0->line;

    // Generate data!
    yygotominor.yy0->type = TOKEN_LAND;
    yygotominor.yy0->subToken[0] = yymsp[-2].minor.yy0;
    yygotominor.yy0->subToken[1] = yymsp[0].minor.yy0;
    yygotominor.yy0->data = "[" + flatListGetter(yygotominor.yy0, TOKEN_LAND) + "]";
}
#line 1823 "parser\\epparser.c"
        break;
      case 102: /* lexpr ::= lexpr LOR lexpr */
#line 412 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genEmpty();
    yygotominor.yy0->line = yymsp[0].minor.yy0->line;

    // Generate data!
    yygotominor.yy0->type = TOKEN_LOR;
    yygotominor.yy0->subToken[0] = yymsp[-2].minor.yy0;
    yygotominor.yy0->subToken[1] = yymsp[0].minor.yy0;
    yygotominor.yy0->data = "EUDOr(" + flatListGetter(yygotominor.yy0, TOKEN_LOR) + ")";
}
#line 1837 "parser\\epparser.c"
        break;
      case 103: /* lexpr ::= LNOT lexpr */
#line 423 "parser\\epparser.lemon"
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
#line 1855 "parser\\epparser.c"
        break;
      case 104: /* vdef_stmt ::= VAR nameList_nonEmpty */
#line 440 "parser\\epparser.lemon"
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
#line 1879 "parser\\epparser.c"
        break;
      case 105: /* vdefAssign_stmt ::= VAR nameList_nonEmpty ASSIGN exprList_nonEmpty */
#line 461 "parser\\epparser.lemon"
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
#line 1904 "parser\\epparser.c"
        break;
      case 106: /* vdefAssign_global_stmt ::= VAR nameList_nonEmpty ASSIGN exprList_nonEmpty */
#line 483 "parser\\epparser.lemon"
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
#line 1924 "parser\\epparser.c"
        break;
      case 107: /* cdef_stmt ::= CONST nameList_nonEmpty ASSIGN exprList_nonEmpty */
#line 500 "parser\\epparser.lemon"
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
#line 1946 "parser\\epparser.c"
        break;
      case 108: /* cdef_global_stmt ::= CONST nameList_nonEmpty ASSIGN exprList_nonEmpty */
#line 519 "parser\\epparser.lemon"
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
#line 1968 "parser\\epparser.c"
        break;
      case 109: /* lvalue ::= NAME */
#line 539 "parser\\epparser.lemon"
{
    checkIsVariable(yymsp[0].minor.yy0->data, yymsp[0].minor.yy0->line);
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1976 "parser\\epparser.c"
        break;
      case 110: /* lvalue ::= expr LSQBRACKET expr RSQBRACKET */
#line 544 "parser\\epparser.lemon"
{
    checkIsConstant(yymsp[-3].minor.yy0->data, yymsp[-3].minor.yy0->line);
    yymsp[-1].minor.yy0->data = "_ARRW(" + yymsp[-3].minor.yy0->data + ", " + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
    delete yymsp[-3].minor.yy0;
}
#line 1986 "parser\\epparser.c"
        break;
      case 111: /* lvalue ::= expr PERIOD NAME */
#line 551 "parser\\epparser.lemon"
{
    checkIsConstant(yymsp[-2].minor.yy0->data, yymsp[-2].minor.yy0->line);
    yymsp[0].minor.yy0->data = "_ATTW(" + yymsp[-2].minor.yy0->data + ", '" + yymsp[0].minor.yy0->data + "')";
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0);
    delete yymsp[-2].minor.yy0;
}
#line 1996 "parser\\epparser.c"
        break;
      case 114: /* assign_stmt ::= lvalue ASSIGN expr */
#line 560 "parser\\epparser.lemon"
{
    ps->gen << yymsp[-2].minor.yy0->data << " << (" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 2004 "parser\\epparser.c"
        break;
      case 115: /* assign_stmt ::= lvalueList_nonEmpty ASSIGN exprList_nonEmpty */
#line 565 "parser\\epparser.lemon"
{
    ps->gen << "_SV([" << yymsp[-2].minor.yy0->data << "], [" << yymsp[0].minor.yy0->data << "])" << std::endl;
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 2012 "parser\\epparser.c"
        break;
      case 116: /* assign_stmt ::= INC expr */
#line 573 "parser\\epparser.lemon"
{ ps->gen << yymsp[0].minor.yy0->data << ".__iadd__(1)" << std::endl; delete yymsp[0].minor.yy0; }
#line 2017 "parser\\epparser.c"
        break;
      case 117: /* assign_stmt ::= expr INC */
#line 574 "parser\\epparser.lemon"
{ ps->gen << yymsp[-1].minor.yy0->data << ".__iadd__(1)" << std::endl; delete yymsp[-1].minor.yy0; }
#line 2022 "parser\\epparser.c"
        break;
      case 118: /* assign_stmt ::= DEC expr */
#line 575 "parser\\epparser.lemon"
{ ps->gen << yymsp[0].minor.yy0->data << ".__isub__(1)" << std::endl; delete yymsp[0].minor.yy0; }
#line 2027 "parser\\epparser.c"
        break;
      case 119: /* assign_stmt ::= expr DEC */
#line 576 "parser\\epparser.lemon"
{ ps->gen << yymsp[-1].minor.yy0->data << ".__isub__(1)" << std::endl; delete yymsp[-1].minor.yy0; }
#line 2032 "parser\\epparser.c"
        break;
      case 120: /* assign_stmt ::= lvalue IADD expr */
#line 577 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__iadd__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2037 "parser\\epparser.c"
        break;
      case 121: /* assign_stmt ::= lvalue ISUB expr */
#line 578 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__isub__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2042 "parser\\epparser.c"
        break;
      case 122: /* assign_stmt ::= lvalue IMUL expr */
#line 579 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__imul__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2047 "parser\\epparser.c"
        break;
      case 123: /* assign_stmt ::= lvalue IDIV expr */
#line 580 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ifloordiv__("  << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2052 "parser\\epparser.c"
        break;
      case 124: /* assign_stmt ::= lvalue IMOD expr */
#line 581 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__imod__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2057 "parser\\epparser.c"
        break;
      case 125: /* assign_stmt ::= lvalue ILSH expr */
#line 582 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ilshift__("    << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2062 "parser\\epparser.c"
        break;
      case 126: /* assign_stmt ::= lvalue IRSH expr */
#line 583 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__irshift__("    << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2067 "parser\\epparser.c"
        break;
      case 127: /* assign_stmt ::= lvalue IBND expr */
#line 584 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__iand__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2072 "parser\\epparser.c"
        break;
      case 128: /* assign_stmt ::= lvalue IBOR expr */
#line 585 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ior__("        << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2077 "parser\\epparser.c"
        break;
      case 129: /* assign_stmt ::= lvalue IBXR expr */
#line 586 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ixor__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2082 "parser\\epparser.c"
        break;
      case 130: /* if_start ::= IF */
#line 589 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDIf()" << std::endl;
}
#line 2090 "parser\\epparser.c"
        break;
      case 131: /* if_header ::= if_start LPAREN lexpr RPAREN */
      case 134: /* elif_header ::= elif_start LPAREN lexpr RPAREN */ yytestcase(yyruleno==134);
      case 140: /* while_header ::= while_start LPAREN lexpr RPAREN */ yytestcase(yyruleno==140);
#line 594 "parser\\epparser.lemon"
{
    writeNegatableCondition(yymsp[-3].minor.yy0, yymsp[-1].minor.yy0);
    ps->gen.indent();
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 2101 "parser\\epparser.c"
        break;
      case 133: /* elif_start ::= ELSE IF */
#line 602 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen.unindent(false);
    ps->gen << yygotominor.yy0->data << " = EUDElseIf()" << std::endl;
}
#line 2110 "parser\\epparser.c"
        break;
      case 136: /* else_header ::= ELSE */
#line 616 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "if EUDElse()():" << std::endl;
    ps->gen.indent();
}
#line 2119 "parser\\epparser.c"
        break;
      case 137: /* if_stmt ::= if_block */
      case 138: /* if_stmt ::= if_block else_header stmt */ yytestcase(yyruleno==138);
#line 622 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndIf()" << std::endl;
}
#line 2128 "parser\\epparser.c"
        break;
      case 139: /* while_start ::= WHILE */
#line 634 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDWhile()" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2137 "parser\\epparser.c"
        break;
      case 141: /* while_stmt ::= while_header stmt */
#line 646 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndWhile()" << std::endl;
}
#line 2145 "parser\\epparser.c"
        break;
      case 142: /* for_opener ::= FOR LPAREN */
      case 158: /* foreach_opener ::= FOREACH LPAREN */ yytestcase(yyruleno==158);
#line 652 "parser\\epparser.lemon"
{
    ps->closure.pushScope();
}
#line 2153 "parser\\epparser.c"
        break;
      case 154: /* for_header1 ::= for_opener for_init_stmt SEMICOLON */
#line 670 "parser\\epparser.lemon"
{
    // opening for lexpr
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDWhile()" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2163 "parser\\epparser.c"
        break;
      case 155: /* for_header2 ::= for_header1 lexpr SEMICOLON */
#line 677 "parser\\epparser.lemon"
{
    writeNegatableCondition(yymsp[-2].minor.yy0, yymsp[-1].minor.yy0);
    ps->gen.indent();
    delete yymsp[-2].minor.yy0; delete yymsp[-1].minor.yy0;

    // Opening for assign_statement
    yygotominor.yy0 = genTemp(yymsp[-1].minor.yy0);
    ps->gen << "def " << yygotominor.yy0->data <<"():" << std::endl;
    ps->gen.indent();
}
#line 2177 "parser\\epparser.c"
        break;
      case 156: /* for_header ::= for_header2 for_action_stmt RPAREN */
#line 688 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-2].minor.yy0;
    ps->gen.unindent(false);
}
#line 2185 "parser\\epparser.c"
        break;
      case 157: /* for_stmt ::= for_header stmt */
#line 693 "parser\\epparser.lemon"
{
    ps->gen << "EUDSetContinuePoint()" << std::endl;
    ps->gen << yymsp[-1].minor.yy0->data << "()" << std::endl;
    ps->gen.unindent(false);
    ps->gen << "EUDEndWhile()" << std::endl;
    ps->closure.popScope();
}
#line 2196 "parser\\epparser.c"
        break;
      case 159: /* foreach_header ::= foreach_opener nameList_nonEmpty COLON exprList_nonEmpty RPAREN */
#line 708 "parser\\epparser.lemon"
{
    commaListIter(yymsp[-3].minor.yy0->data, [&](std::string& s) {
        ps->closure.defVariable(s);
    });
    ps->gen << "for " << yymsp[-3].minor.yy0->data << " in " << yymsp[-1].minor.yy0->data << ":" << std::endl;
    ps->gen.indent();
}
#line 2207 "parser\\epparser.c"
        break;
      case 160: /* foreach_stmt ::= foreach_header stmt */
#line 716 "parser\\epparser.lemon"
{
    ps->gen.unindent(true);
    ps->closure.popScope();
}
#line 2215 "parser\\epparser.c"
        break;
      case 161: /* continue_stmt ::= CONTINUE */
#line 724 "parser\\epparser.lemon"
{
    ps->gen << "EUDContinue()" << std::endl;
}
#line 2222 "parser\\epparser.c"
        break;
      case 162: /* break_stmt ::= BREAK */
#line 728 "parser\\epparser.lemon"
{
    ps->gen << "EUDBreak()" << std::endl;
}
#line 2229 "parser\\epparser.c"
        break;
      case 163: /* return_stmt ::= RETURN exprList */
#line 735 "parser\\epparser.lemon"
{
    if(MAP_DEBUG){
        ps->gen << "MDBG_POPF()" << std::endl;
    }
    ps->gen << "EUDReturn(" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2240 "parser\\epparser.c"
        break;
      case 164: /* lexpr ::= CONDITIONNAME LPAREN fArgs RPAREN */
      case 165: /* lexpr ::= KILLS LPAREN fArgs RPAREN */ yytestcase(yyruleno==165);
#line 746 "parser\\epparser.lemon"
{
    yymsp[-3].minor.yy0->data = yymsp[-3].minor.yy0->data + "(" + yymsp[-1].minor.yy0->data + ")";
    delete yymsp[-1].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 2250 "parser\\epparser.c"
        break;
      case 166: /* lexpr ::= CONDITIONNAME LPAREN RPAREN */
#line 758 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + "()";
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 2258 "parser\\epparser.c"
        break;
      case 167: /* action ::= ACTIONNAME LPAREN fArgs RPAREN SEMICOLON */
#line 763 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[-4].minor.yy0);
    yygotominor.yy0->data =  yymsp[-4].minor.yy0->data + "(" + yymsp[-2].minor.yy0->data + ")";
    delete yymsp[-4].minor.yy0; delete yymsp[-2].minor.yy0;
}
#line 2267 "parser\\epparser.c"
        break;
      case 168: /* actions ::= action action */
      case 169: /* actions ::= actions action */ yytestcase(yyruleno==169);
#line 769 "parser\\epparser.lemon"
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
#line 2290 "parser\\epparser.c"
        break;
      case 170: /* actionStmt_start ::= */
#line 807 "parser\\epparser.lemon"
{
    functionCalledInMultipleActions = false;
}
#line 2297 "parser\\epparser.c"
        break;
      case 171: /* actionStmt ::= actionStmt_start action */
#line 811 "parser\\epparser.lemon"
{
    ps->gen << "DoActions(" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2305 "parser\\epparser.c"
        break;
      case 172: /* actionStmt ::= actionStmt_start actions */
#line 816 "parser\\epparser.lemon"
{
    ps->gen << "DoActions([" << std::endl;
    ps->gen.indent();
    ps->gen << yymsp[0].minor.yy0->data << std::endl;
    ps->gen.unindent(false);
    ps->gen << "])" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2317 "parser\\epparser.c"
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
      /* (8) chunk ::= cdef_global_stmt SEMICOLON */ yytestcase(yyruleno==8);
      /* (18) stmt ::= bodyStmt */ yytestcase(yyruleno==18);
      /* (19) stmt ::= return_stmt SEMICOLON */ yytestcase(yyruleno==19);
      /* (23) blockStmt ::= lbracket return_stmt SEMICOLON rbracket */ yytestcase(yyruleno==23);
      /* (24) blockStmt ::= lbracket bodyStmtList rbracket */ yytestcase(yyruleno==24);
      /* (25) blockStmt ::= lbracket bodyStmtList return_stmt SEMICOLON rbracket */ yytestcase(yyruleno==25);
      /* (27) bodyStmt ::= blockStmt */ yytestcase(yyruleno==27);
      /* (28) bodyStmt ::= SEMICOLON */ yytestcase(yyruleno==28);
      /* (29) bodyStmt ::= vdef_stmt SEMICOLON */ yytestcase(yyruleno==29);
      /* (30) bodyStmt ::= vdefAssign_stmt SEMICOLON */ yytestcase(yyruleno==30);
      /* (31) bodyStmt ::= cdef_stmt SEMICOLON */ yytestcase(yyruleno==31);
      /* (32) bodyStmt ::= assign_stmt SEMICOLON */ yytestcase(yyruleno==32);
      /* (34) bodyStmt ::= actionStmt */ yytestcase(yyruleno==34);
      /* (35) bodyStmt ::= if_stmt */ yytestcase(yyruleno==35);
      /* (36) bodyStmt ::= while_stmt */ yytestcase(yyruleno==36);
      /* (37) bodyStmt ::= for_stmt */ yytestcase(yyruleno==37);
      /* (38) bodyStmt ::= foreach_stmt */ yytestcase(yyruleno==38);
      /* (39) bodyStmt ::= continue_stmt SEMICOLON */ yytestcase(yyruleno==39);
      /* (40) bodyStmt ::= break_stmt SEMICOLON */ yytestcase(yyruleno==40);
      /* (42) bodyStmtList ::= bodyStmt */ yytestcase(yyruleno==42);
      /* (43) bodyStmtList ::= bodyStmtList bodyStmt */ yytestcase(yyruleno==43);
      /* (72) commaSkippable ::= COMMA */ yytestcase(yyruleno==72);
      /* (73) commaSkippable ::= */ yytestcase(yyruleno==73);
      /* (132) if_block ::= if_header stmt */ yytestcase(yyruleno==132);
      /* (135) if_block ::= if_block elif_header stmt */ yytestcase(yyruleno==135);
      /* (143) for_init_stmt_nonEmpty ::= vdef_stmt */ yytestcase(yyruleno==143);
      /* (144) for_init_stmt_nonEmpty ::= vdefAssign_stmt */ yytestcase(yyruleno==144);
      /* (145) for_init_stmt_nonEmpty ::= cdef_stmt */ yytestcase(yyruleno==145);
      /* (146) for_init_stmt_nonEmpty ::= assign_stmt */ yytestcase(yyruleno==146);
      /* (147) for_init_stmt_nonEmpty ::= for_init_stmt_nonEmpty COMMA for_init_stmt_nonEmpty */ yytestcase(yyruleno==147);
      /* (148) for_init_stmt ::= for_init_stmt_nonEmpty */ yytestcase(yyruleno==148);
      /* (149) for_init_stmt ::= */ yytestcase(yyruleno==149);
      /* (150) for_action_stmt_nonEmpty ::= assign_stmt */ yytestcase(yyruleno==150);
      /* (151) for_action_stmt_nonEmpty ::= for_action_stmt_nonEmpty COMMA for_action_stmt_nonEmpty */ yytestcase(yyruleno==151);
      /* (152) for_action_stmt ::= */ yytestcase(yyruleno==152);
      /* (153) for_action_stmt ::= for_action_stmt_nonEmpty */ yytestcase(yyruleno==153);
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
#line 2412 "parser\\epparser.c"
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
#line 830 "parser\\epparser.lemon"


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
#line 2708 "parser\\epparser.c"
