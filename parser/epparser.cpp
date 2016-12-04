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
#define YYNSTATE 314
#define YYNRULE 159
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
#define YY_ACTTAB_COUNT (1326)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   203,  312,  230,  189,   18,   38,  204,  199,   73,  197,
 /*    10 */   290,  187,  310,  100,  300,  298,  202,    2,  113,  136,
 /*    20 */   198,  196,  140,  282,  281,  280,  279,  278,  191,  190,
 /*    30 */   309,  229,  100,  185,  308,   28,   29,  113,  136,  154,
 /*    40 */     8,   40,  180,  107,  161,  151,    6,   10,   68,   69,
 /*    50 */    67,   22,   13,    5,   78,    4,   77,   76,  203,   18,
 /*    60 */   230,  189,  204,   73,  258,  199,  187,  197,  290,   37,
 /*    70 */   204,  100,  245,  298,  202,    2,  113,  136,  198,  196,
 /*    80 */   140,  282,  281,  280,  279,  278,  191,  190,  204,  135,
 /*    90 */   100,  185,  304,   28,   29,  113,  136,  154,    8,   40,
 /*   100 */   180,  107,  220,  151,    6,   10,  208,  189,  207,   22,
 /*   110 */    13,    5,   78,    4,   77,   76,  203,  108,  182,  186,
 /*   120 */   159,  284,  252,  199,  306,  197,  290,   28,   29,  195,
 /*   130 */   242,  298,  202,    2,   35,   36,  198,  196,  140,  282,
 /*   140 */   281,  280,  279,  278,  191,  190,   33,  204,  100,   34,
 /*   150 */   189,  231,  181,  113,  136,  154,    8,   40,   28,   29,
 /*   160 */    85,  151,    6,   10,  124,  189,  305,   22,   13,    5,
 /*   170 */    78,    4,   77,   76,  203,  108,  185,  186,  160,   28,
 /*   180 */    29,  199,  189,  197,  290,  264,  107,  246,  239,  298,
 /*   190 */   202,    2,   88,   74,  198,  196,  140,  282,  281,  280,
 /*   200 */   279,  278,  191,  190,  301,  303,  100,  299,  243,  297,
 /*   210 */   302,  113,  136,  154,    8,   40,   28,   29,  194,  151,
 /*   220 */     6,   10,   83,  189,   82,   22,   13,    5,   78,    4,
 /*   230 */    77,   76,  203,  108,  185,  186,  165,  288,   14,  199,
 /*   240 */   189,  197,  290,  157,  107,  240,  226,  298,  202,    2,
 /*   250 */    87,  287,  198,  196,  140,  282,  281,  280,  279,  278,
 /*   260 */   191,  190,  474,   11,  100,  152,    7,    3,  228,  113,
 /*   270 */   136,  154,    8,   40,  286,  193,  285,  151,    6,   10,
 /*   280 */   192,  189,  283,   22,   13,    5,   78,    4,   77,   76,
 /*   290 */   203,  108,  185,  186,  145,   39,  277,  199,  189,  197,
 /*   300 */   290,  156,  107,  276,  223,  298,  202,    2,  119,  195,
 /*   310 */   198,  196,  140,  282,  281,  280,  279,  278,  191,  190,
 /*   320 */    19,  271,  100,  189,  189,  224,   32,  113,  136,  154,
 /*   330 */     8,   40,  184,  100,  118,  151,    6,   10,  248,  189,
 /*   340 */    81,   22,   13,    5,   78,    4,   77,   76,  203,  108,
 /*   350 */   185,  186,  162,  266,   39,  199,  189,  197,  290,  155,
 /*   360 */   107,  265,  216,  298,  202,    2,  131,   31,  198,  196,
 /*   370 */   140,  282,  281,  280,  279,  278,  191,  190,   17,  175,
 /*   380 */   100,  185,  189,  263,  176,  113,  136,  154,    8,   40,
 /*   390 */   133,  107,   84,  151,    6,   10,  125,  173,  185,   22,
 /*   400 */    13,    5,   78,    4,   77,   76,  143,  142,  107,  189,
 /*   410 */   189,  172,  262,  199,  170,  197,  290,  169,  261,  130,
 /*   420 */    85,  214,  201,    2,  257,    1,  198,  196,  140,  282,
 /*   430 */   281,  280,  279,  278,  191,  190,  167,  166,  100,  189,
 /*   440 */   189,  260,  259,  113,  136,  154,    8,   40,   29,  129,
 /*   450 */    85,  151,    6,   10,  164,  189,  189,   22,   13,    5,
 /*   460 */    78,    4,   77,   76,  274,  108,   85,  268,  189,   15,
 /*   470 */   256,  199,  254,  197,  290,  251,  111,  250,  117,  275,
 /*   480 */   200,    2,  292,  249,  198,  196,  140,  282,  281,  280,
 /*   490 */   279,  278,  191,  190,   25,  244,  100,  189,  189,   24,
 /*   500 */    23,  113,  136,  154,    8,   40,  238,  116,   85,  151,
 /*   510 */     6,   10,  255,  232,  189,   22,   13,    5,   78,    4,
 /*   520 */    77,   76,   61,   60,  115,   12,  189,  225,   59,  273,
 /*   530 */   109,  289,  189,   16,  219,   72,   85,  296,  295,   21,
 /*   540 */   123,  272,  112,  215,  144,  179,  177,  174,  171,  168,
 /*   550 */    80,   79,   66,   65,   71,   70,   68,   69,   67,  294,
 /*   560 */   293,  291,  247,  189,  241,  150,  147,   18,  222,  221,
 /*   570 */    20,   73,  146,   85,  187,  139,  189,  122,  183,  138,
 /*   580 */   301,   61,   60,  189,  218,  189,  114,   59,  273,  109,
 /*   590 */   289,  217,  146,  128,   72,   85,  296,  294,   21,  121,
 /*   600 */   272,  189,  189,  137,  179,  177,  174,  171,  168,   80,
 /*   610 */    79,  127,  126,   71,   70,   68,   69,   67,  475,  134,
 /*   620 */   132,  247,  189,  241,  150,  147,   18,  222,  221,   20,
 /*   630 */    73,  146,   85,  187,  189,  153,  120,  141,  475,  475,
 /*   640 */    61,   60,  189,  475,  106,  475,   59,  273,  109,  289,
 /*   650 */   189,  475,  105,   72,  475,  296,  475,   21,  475,  272,
 /*   660 */   104,  189,  189,  179,  177,  174,  171,  168,   80,   79,
 /*   670 */   475,  103,  102,  475,  475,  189,  475,  475,  475,  189,
 /*   680 */   247,  475,  241,  150,  147,  101,  222,  221,   20,   86,
 /*   690 */   146,   58,   56,   55,   54,   53,   57,   63,   62,   64,
 /*   700 */    66,   65,   71,   70,   68,   69,   67,  189,  189,  475,
 /*   710 */   475,  475,  475,  475,  475,   18,  267,   99,   98,   73,
 /*   720 */   475,  475,  187,   58,   56,   55,   54,   53,   57,   63,
 /*   730 */    62,   64,   66,   65,   71,   70,   68,   69,   67,   27,
 /*   740 */   314,  475,  475,  475,  475,  189,  475,   18,  475,  475,
 /*   750 */   475,   73,   61,   60,  187,   97,  189,  189,   59,  273,
 /*   760 */   188,  475,  475,  475,  189,   30,   96,   95,  209,   21,
 /*   770 */   206,  178,  189,  296,   94,  179,  177,  174,  171,  168,
 /*   780 */   189,  189,   93,   26,  189,  189,   75,   79,  475,  475,
 /*   790 */    92,   91,  475,  475,   90,   89,   61,   60,  475,  475,
 /*   800 */   475,  163,   59,  273,  188,  475,  475,  475,  475,   30,
 /*   810 */   475,  475,  475,   21,  475,  178,  475,  475,  475,  179,
 /*   820 */   177,  174,  171,  168,  475,  313,  213,  311,  212,  211,
 /*   830 */   210,  307,  205,    9,   61,   60,  475,  475,    2,  475,
 /*   840 */    59,  273,  188,  475,  475,  163,  475,   72,  253,  475,
 /*   850 */   475,   21,  475,  272,  475,  269,  475,  179,  177,  174,
 /*   860 */   171,  168,  475,  475,   61,   60,  475,  475,  475,  475,
 /*   870 */    59,  273,  109,  475,  475,  475,  475,   72,  475,  475,
 /*   880 */   475,   21,  475,  272,  475,  475,  475,  179,  177,  174,
 /*   890 */   171,  168,   80,   79,  475,   63,   62,   64,   66,   65,
 /*   900 */    71,   70,   68,   69,   67,  475,  475,  475,  475,  475,
 /*   910 */   475,  475,  475,   18,  475,  475,  475,   73,  270,  475,
 /*   920 */   187,  475,  475,  475,  475,  475,  475,   63,   62,   64,
 /*   930 */    66,   65,   71,   70,   68,   69,   67,  475,  475,  475,
 /*   940 */   475,  475,  475,  475,  475,   18,  267,  475,  475,   73,
 /*   950 */   475,  475,  187,  475,  475,  475,  475,  475,  475,   63,
 /*   960 */    62,   64,   66,   65,   71,   70,   68,   69,   67,  475,
 /*   970 */   475,  475,  475,  475,  475,  475,  475,   18,  475,   61,
 /*   980 */    60,   73,  110,  475,  187,   59,  273,  188,  475,  475,
 /*   990 */   475,  475,   72,  475,  475,  475,   21,  475,  272,  475,
 /*  1000 */   269,  475,  179,  177,  174,  171,  168,  475,  475,  475,
 /*  1010 */   475,   61,   60,  475,  475,  475,  475,   59,  273,  109,
 /*  1020 */   475,  475,  475,  475,   72,  227,  475,  475,   21,  475,
 /*  1030 */   272,  475,  475,  475,  179,  177,  174,  171,  168,  368,
 /*  1040 */   368,  368,  368,  368,  368,  368,  368,  368,  368,  475,
 /*  1050 */   475,  475,  475,  475,  475,  475,  475,   19,  475,  475,
 /*  1060 */   475,  368,  475,  475,  368,  475,  475,  475,  475,  475,
 /*  1070 */   475,   63,   62,   64,   66,   65,   71,   70,   68,   69,
 /*  1080 */    67,  475,  475,  475,  475,  475,  475,  475,  475,   18,
 /*  1090 */   475,  475,  475,   73,  475,  475,  187,  475,  475,  475,
 /*  1100 */   475,  475,  475,   63,   62,   64,   66,   65,   71,   70,
 /*  1110 */    68,   69,   67,  475,  475,  475,  475,  475,  475,  475,
 /*  1120 */   475,   18,  475,   61,   60,   52,  475,  475,  158,   59,
 /*  1130 */   273,  188,  475,  475,  475,  475,   72,  475,  475,  475,
 /*  1140 */    21,  475,  272,  475,  475,  475,  179,  177,  174,  171,
 /*  1150 */   168,  475,  475,  475,  475,   61,   60,  475,  475,  475,
 /*  1160 */   475,   59,  273,  109,  417,  417,  475,  475,   72,  475,
 /*  1170 */   475,  475,   21,  475,  272,  475,  416,  416,  179,  177,
 /*  1180 */   174,  171,  168,   62,   64,   66,   65,   71,   70,   68,
 /*  1190 */    69,   67,  475,  475,  475,  475,  475,  475,  475,  475,
 /*  1200 */    18,  475,  475,  475,   73,  475,  475,  187,  475,  475,
 /*  1210 */   475,  417,  417,  417,  417,  417,  417,  417,  417,  417,
 /*  1220 */   417,   51,  475,  416,  416,  416,  416,  416,  416,  416,
 /*  1230 */   416,  416,  416,   64,   66,   65,   71,   70,   68,   69,
 /*  1240 */    67,  475,  475,  475,  475,  475,  475,  475,  475,   18,
 /*  1250 */   475,  475,  475,   73,  475,  475,  187,  475,  475,  475,
 /*  1260 */   475,  475,  475,  475,  475,  237,  475,  235,   50,   49,
 /*  1270 */    48,   47,   46,   45,   44,   43,   42,   41,  236,  234,
 /*  1280 */   189,  475,  475,  475,  237,  475,  235,  475,  475,  475,
 /*  1290 */   100,  475,  475,  475,  475,  113,  136,  236,  234,  189,
 /*  1300 */   475,  475,  475,  475,  475,  475,  149,  148,  475,  100,
 /*  1310 */   475,  475,  475,  475,  113,  136,  475,  475,  475,  475,
 /*  1320 */   475,  475,  475,  475,  475,  233,
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
 /*   110 */   121,  122,  123,  124,  125,  126,   69,  101,    2,  103,
 /*   120 */   104,   27,   32,   76,   26,   78,   79,    3,    4,   35,
 /*   130 */    83,   84,   85,   86,    1,    2,   89,   90,   91,   92,
 /*   140 */    93,   94,   95,   96,   97,   98,    1,    2,  101,   63,
 /*   150 */    91,   27,   36,  106,  107,  108,  109,  110,    3,    4,
 /*   160 */   101,  114,  115,  116,  105,   91,   26,  120,  121,  122,
 /*   170 */   123,  124,  125,  126,   69,  101,   91,  103,  104,    3,
 /*   180 */     4,   76,   91,   78,   79,  100,  101,   32,   83,   84,
 /*   190 */    85,   86,  101,   31,   89,   90,   91,   92,   93,   94,
 /*   200 */    95,   96,   97,   98,   26,   26,  101,   27,   32,   27,
 /*   210 */    32,  106,  107,  108,  109,  110,    3,    4,   35,  114,
 /*   220 */   115,  116,   27,   91,   27,  120,  121,  122,  123,  124,
 /*   230 */   125,  126,   69,  101,   91,  103,  104,   27,    2,   76,
 /*   240 */    91,   78,   79,  100,  101,   32,   83,   84,   85,   86,
 /*   250 */   101,   27,   89,   90,   91,   92,   93,   94,   95,   96,
 /*   260 */    97,   98,   71,   72,  101,  111,  112,  113,   32,  106,
 /*   270 */   107,  108,  109,  110,   27,   25,   27,  114,  115,  116,
 /*   280 */    36,   91,   36,  120,  121,  122,  123,  124,  125,  126,
 /*   290 */    69,  101,   91,  103,  104,    2,   27,   76,   91,   78,
 /*   300 */    79,  100,  101,   27,   83,   84,   85,   86,  101,   35,
 /*   310 */    89,   90,   91,   92,   93,   94,   95,   96,   97,   98,
 /*   320 */    31,   26,  101,   91,   91,   32,    2,  106,  107,  108,
 /*   330 */   109,  110,   35,  101,  101,  114,  115,  116,  106,   91,
 /*   340 */    35,  120,  121,  122,  123,  124,  125,  126,   69,  101,
 /*   350 */    91,  103,  104,   25,    2,   76,   91,   78,   79,  100,
 /*   360 */   101,   36,   83,   84,   85,   86,  101,   31,   89,   90,
 /*   370 */    91,   92,   93,   94,   95,   96,   97,   98,   31,   39,
 /*   380 */   101,   91,   91,   32,   31,  106,  107,  108,  109,  110,
 /*   390 */   100,  101,  101,  114,  115,  116,  105,   31,   91,  120,
 /*   400 */   121,  122,  123,  124,  125,  126,   69,  100,  101,   91,
 /*   410 */    91,   39,   32,   76,   31,   78,   79,   39,   32,  101,
 /*   420 */   101,   84,   85,   86,  105,   88,   89,   90,   91,   92,
 /*   430 */    93,   94,   95,   96,   97,   98,   31,   39,  101,   91,
 /*   440 */    91,   32,   32,  106,  107,  108,  109,  110,    4,  101,
 /*   450 */   101,  114,  115,  116,  105,   91,   91,  120,  121,  122,
 /*   460 */   123,  124,  125,  126,   69,  101,  101,  103,   91,   31,
 /*   470 */   105,   76,   32,   78,   79,   36,   26,   32,  101,   84,
 /*   480 */    85,   86,   87,   32,   89,   90,   91,   92,   93,   94,
 /*   490 */    95,   96,   97,   98,   31,   58,  101,   91,   91,   31,
 /*   500 */    31,  106,  107,  108,  109,  110,   31,  101,  101,  114,
 /*   510 */   115,  116,  105,   27,   91,  120,  121,  122,  123,  124,
 /*   520 */   125,  126,   18,   19,  101,    2,   91,   31,   24,   25,
 /*   530 */    26,   27,   91,   31,   27,   31,  101,   33,   34,   35,
 /*   540 */   105,   37,  101,   34,   32,   41,   42,   43,   44,   45,
 /*   550 */    46,   47,   16,   17,   18,   19,   20,   21,   22,   34,
 /*   560 */    87,   87,   58,   91,   60,   61,   62,   31,   64,   65,
 /*   570 */    66,   35,   68,  101,   38,   99,   91,  105,   25,   82,
 /*   580 */    26,   18,   19,   91,  125,   91,  101,   24,   25,   26,
 /*   590 */    27,  125,   68,  101,   31,  101,   33,   34,   35,  105,
 /*   600 */    37,   91,   91,   82,   41,   42,   43,   44,   45,   46,
 /*   610 */    47,  101,  101,   18,   19,   20,   21,   22,  127,   82,
 /*   620 */    82,   58,   91,   60,   61,   62,   31,   64,   65,   66,
 /*   630 */    35,   68,  101,   38,   91,   59,  105,   82,  127,  127,
 /*   640 */    18,   19,   91,  127,  101,  127,   24,   25,   26,   27,
 /*   650 */    91,  127,  101,   31,  127,   33,  127,   35,  127,   37,
 /*   660 */   101,   91,   91,   41,   42,   43,   44,   45,   46,   47,
 /*   670 */   127,  101,  101,  127,  127,   91,  127,  127,  127,   91,
 /*   680 */    58,  127,   60,   61,   62,  101,   64,   65,   66,  101,
 /*   690 */    68,    7,    8,    9,   10,   11,   12,   13,   14,   15,
 /*   700 */    16,   17,   18,   19,   20,   21,   22,   91,   91,  127,
 /*   710 */   127,  127,  127,  127,  127,   31,   32,  101,  101,   35,
 /*   720 */   127,  127,   38,    7,    8,    9,   10,   11,   12,   13,
 /*   730 */    14,   15,   16,   17,   18,   19,   20,   21,   22,    5,
 /*   740 */     0,  127,  127,  127,  127,   91,  127,   31,  127,  127,
 /*   750 */   127,   35,   18,   19,   38,  101,   91,   91,   24,   25,
 /*   760 */    26,  127,  127,  127,   91,   31,  101,  101,   28,   35,
 /*   770 */    30,   37,   91,   33,  101,   41,   42,   43,   44,   45,
 /*   780 */    91,   91,  101,    5,   91,   91,   46,   47,  127,  127,
 /*   790 */   101,  101,  127,  127,  101,  101,   18,   19,  127,  127,
 /*   800 */   127,   67,   24,   25,   26,  127,  127,  127,  127,   31,
 /*   810 */   127,  127,  127,   35,  127,   37,  127,  127,  127,   41,
 /*   820 */    42,   43,   44,   45,  127,   73,   74,   75,   76,   77,
 /*   830 */    78,   79,   80,   81,   18,   19,  127,  127,   86,  127,
 /*   840 */    24,   25,   26,  127,  127,   67,  127,   31,   32,  127,
 /*   850 */   127,   35,  127,   37,  127,   39,  127,   41,   42,   43,
 /*   860 */    44,   45,  127,  127,   18,   19,  127,  127,  127,  127,
 /*   870 */    24,   25,   26,  127,  127,  127,  127,   31,  127,  127,
 /*   880 */   127,   35,  127,   37,  127,  127,  127,   41,   42,   43,
 /*   890 */    44,   45,   46,   47,  127,   13,   14,   15,   16,   17,
 /*   900 */    18,   19,   20,   21,   22,  127,  127,  127,  127,  127,
 /*   910 */   127,  127,  127,   31,  127,  127,  127,   35,   36,  127,
 /*   920 */    38,  127,  127,  127,  127,  127,  127,   13,   14,   15,
 /*   930 */    16,   17,   18,   19,   20,   21,   22,  127,  127,  127,
 /*   940 */   127,  127,  127,  127,  127,   31,   32,  127,  127,   35,
 /*   950 */   127,  127,   38,  127,  127,  127,  127,  127,  127,   13,
 /*   960 */    14,   15,   16,   17,   18,   19,   20,   21,   22,  127,
 /*   970 */   127,  127,  127,  127,  127,  127,  127,   31,  127,   18,
 /*   980 */    19,   35,   36,  127,   38,   24,   25,   26,  127,  127,
 /*   990 */   127,  127,   31,  127,  127,  127,   35,  127,   37,  127,
 /*  1000 */    39,  127,   41,   42,   43,   44,   45,  127,  127,  127,
 /*  1010 */   127,   18,   19,  127,  127,  127,  127,   24,   25,   26,
 /*  1020 */   127,  127,  127,  127,   31,   32,  127,  127,   35,  127,
 /*  1030 */    37,  127,  127,  127,   41,   42,   43,   44,   45,   13,
 /*  1040 */    14,   15,   16,   17,   18,   19,   20,   21,   22,  127,
 /*  1050 */   127,  127,  127,  127,  127,  127,  127,   31,  127,  127,
 /*  1060 */   127,   35,  127,  127,   38,  127,  127,  127,  127,  127,
 /*  1070 */   127,   13,   14,   15,   16,   17,   18,   19,   20,   21,
 /*  1080 */    22,  127,  127,  127,  127,  127,  127,  127,  127,   31,
 /*  1090 */   127,  127,  127,   35,  127,  127,   38,  127,  127,  127,
 /*  1100 */   127,  127,  127,   13,   14,   15,   16,   17,   18,   19,
 /*  1110 */    20,   21,   22,  127,  127,  127,  127,  127,  127,  127,
 /*  1120 */   127,   31,  127,   18,   19,   35,  127,  127,   38,   24,
 /*  1130 */    25,   26,  127,  127,  127,  127,   31,  127,  127,  127,
 /*  1140 */    35,  127,   37,  127,  127,  127,   41,   42,   43,   44,
 /*  1150 */    45,  127,  127,  127,  127,   18,   19,  127,  127,  127,
 /*  1160 */   127,   24,   25,   26,    1,    2,  127,  127,   31,  127,
 /*  1170 */   127,  127,   35,  127,   37,  127,    1,    2,   41,   42,
 /*  1180 */    43,   44,   45,   14,   15,   16,   17,   18,   19,   20,
 /*  1190 */    21,   22,  127,  127,  127,  127,  127,  127,  127,  127,
 /*  1200 */    31,  127,  127,  127,   35,  127,  127,   38,  127,  127,
 /*  1210 */   127,   48,   49,   50,   51,   52,   53,   54,   55,   56,
 /*  1220 */    57,    1,  127,   48,   49,   50,   51,   52,   53,   54,
 /*  1230 */    55,   56,   57,   15,   16,   17,   18,   19,   20,   21,
 /*  1240 */    22,  127,  127,  127,  127,  127,  127,  127,  127,   31,
 /*  1250 */   127,  127,  127,   35,  127,  127,   38,  127,  127,  127,
 /*  1260 */   127,  127,  127,  127,  127,   76,  127,   78,   48,   49,
 /*  1270 */    50,   51,   52,   53,   54,   55,   56,   57,   89,   90,
 /*  1280 */    91,  127,  127,  127,   76,  127,   78,  127,  127,  127,
 /*  1290 */   101,  127,  127,  127,  127,  106,  107,   89,   90,   91,
 /*  1300 */   127,  127,  127,  127,  127,  127,  117,  118,  127,  101,
 /*  1310 */   127,  127,  127,  127,  106,  107,  127,  127,  127,  127,
 /*  1320 */   127,  127,  127,  127,  127,  117,
};
#define YY_SHIFT_USE_DFLT (-28)
#define YY_SHIFT_COUNT (213)
#define YY_SHIFT_MIN   (-27)
#define YY_SHIFT_MAX   (1220)
static const short yy_shift_ofst[] = {
 /*     0 */   -28,  563,  504,  622,  622,  622,  622,  622,  622,  622,
 /*    10 */   846,  740,  846,  993, 1137,  816,  961,  961,  961,  961,
 /*    20 */  1105, 1105,  734,  734,  734,  734,  778,  778,  734,  734,
 /*    30 */   734,  734,  961, 1105, 1105, 1105, 1137, 1105, 1105, 1105,
 /*    40 */   576, 1105, 1105, 1105, 1105, 1105, 1105, 1105, 1105, 1105,
 /*    50 */  1105, 1105, 1105, 1105, 1105, 1105, 1105, 1105, 1105, 1105,
 /*    60 */  1105, 1105, 1105, 1105, 1105, 1105, 1105, 1105, 1105, 1105,
 /*    70 */  1105, 1105, 1105, 1105,  178,  554,  524,  524,  554,  554,
 /*    80 */   554,  553,  525,  525,  684,  716,  946,  914,  882, 1058,
 /*    90 */  1058, 1058, 1058, 1058, 1058, 1058, 1058, 1058, 1058, 1058,
 /*   100 */  1090, 1058, 1058, 1058, 1058, 1058, 1058, 1058, 1058, 1026,
 /*   110 */  1175, 1163, 1169, 1220, 1218,  536,  595,  595,   28,   28,
 /*   120 */   124,  213,  176,  155,   90,   32,  -27,  -27,  -27,  -27,
 /*   130 */   -27,  -27,  145,  293,   86,  236,  133,   68,    4,  116,
 /*   140 */    94,   60,  352,  509,  507,  512,  502,  496,  486,  523,
 /*   150 */   475,  469,  468,  437,  463,  352,  352,  352,  450,  451,
 /*   160 */   445,  439,  440,  438,  444,  410,  409,  398,  405,  386,
 /*   170 */   378,  383,  380,  372,  366,  351,  340,  353,  347,  336,
 /*   180 */   352,  325,  328,  244,  305,  297,  324,  295,  289,  274,
 /*   190 */   276,  269,  246,  244,  250,  183,  249,  247,  224,  210,
 /*   200 */   197,  195,  182,  180,  179,  162,  140,   98,   79,   80,
 /*   210 */     7,    3,  -15,  -26,
};
#define YY_REDUCE_USE_DFLT (-89)
#define YY_REDUCE_COUNT (83)
#define YY_REDUCE_MIN   (-88)
#define YY_REDUCE_MAX   (1208)
static const short yy_reduce_ofst[] = {
 /*     0 */   191,  395,  337,  279,  221,  163,  105,   47,  -11,  -69,
 /*    10 */  1189,  752, 1208,  -30,  -88,  248,  190,  132,   74,   16,
 /*    20 */     0,  -58,  531,  494,  472,  435,  407,  365,  349,  319,
 /*    30 */   291,   59,  364,  307,  290,  259,  232,  201,  143,   85,
 /*    40 */   154,  694,  693,  690,  689,  681,  673,  666,  665,  654,
 /*    50 */   617,  616,  588,  584,  571,  570,  559,  551,  543,  511,
 /*    60 */   510,  492,  485,  441,  423,  406,  377,  348,  318,  265,
 /*    70 */   233,  207,  149,   91,  555,  538,  466,  459,  537,  521,
 /*    80 */   497,  476,  474,  473,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   315,  473,  473,  473,  473,  473,  473,  473,  473,  473,
 /*    10 */   451,  473,  473,  473,  473,  473,  374,  374,  374,  374,
 /*    20 */   364,  364,  473,  473,  473,  473,  473,  473,  473,  473,
 /*    30 */   473,  473,  473,  473,  473,  473,  473,  473,  473,  473,
 /*    40 */   439,  473,  473,  473,  473,  473,  473,  473,  473,  473,
 /*    50 */   473,  473,  473,  473,  473,  473,  473,  473,  473,  473,
 /*    60 */   473,  473,  473,  473,  473,  473,  473,  473,  473,  473,
 /*    70 */   473,  473,  473,  473,  473,  473,  472,  471,  473,  473,
 /*    80 */   473,  473,  473,  473,  399,  399,  473,  473,  473,  431,
 /*    90 */   430,  429,  428,  427,  426,  425,  424,  423,  422,  420,
 /*   100 */   473,  406,  405,  404,  403,  402,  401,  362,  371,  415,
 /*   110 */   370,  369,  394,  418,  395,  393,  392,  391,  387,  386,
 /*   120 */   473,  473,  473,  473,  473,  473,  398,  397,  396,  390,
 /*   130 */   389,  388,  411,  473,  473,  473,  473,  473,  411,  473,
 /*   140 */   378,  473,  413,  473,  473,  473,  473,  473,  473,  450,
 /*   150 */   473,  473,  473,  438,  473,  421,  414,  412,  473,  473,
 /*   160 */   473,  473,  473,  473,  408,  473,  473,  473,  473,  473,
 /*   170 */   473,  473,  473,  473,  473,  473,  473,  473,  367,  473,
 /*   180 */   365,  473,  473,  356,  473,  378,  375,  473,  368,  378,
 /*   190 */   473,  473,  473,  473,  473,  473,  473,  473,  473,  473,
 /*   200 */   473,  473,  473,  473,  473,  473,  473,  473,  324,  473,
 /*   210 */   473,  473,  473,  473,  353,  338,  440,  470,  469,  468,
 /*   220 */   464,  463,  462,  461,  460,  459,  458,  457,  456,  453,
 /*   230 */   452,  455,  454,  449,  448,  447,  446,  445,  444,  443,
 /*   240 */   442,  441,  437,  436,  435,  434,  433,  432,  419,  376,
 /*   250 */   377,  380,  381,  467,  465,  410,  409,  407,  400,  466,
 /*   260 */   385,  384,  383,  382,  363,  360,  357,  379,  373,  372,
 /*   270 */   370,  369,  367,  366,  355,  354,  352,  351,  350,  349,
 /*   280 */   348,  347,  346,  361,  345,  344,  343,  342,  341,  340,
 /*   290 */   339,  337,  336,  335,  333,  334,  332,  331,  330,  329,
 /*   300 */   328,  358,  327,  359,  326,  325,  323,  322,  321,  320,
 /*   310 */   319,  318,  317,  316,
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
 /*  85 */ "lexpr ::= expr",
 /*  86 */ "lexpr ::= LPAREN lexpr RPAREN",
 /*  87 */ "lexpr ::= expr EQ expr",
 /*  88 */ "lexpr ::= expr NE expr",
 /*  89 */ "lexpr ::= expr LE expr",
 /*  90 */ "lexpr ::= expr LT expr",
 /*  91 */ "lexpr ::= expr GE expr",
 /*  92 */ "lexpr ::= expr GT expr",
 /*  93 */ "lexpr ::= lexpr LAND lexpr",
 /*  94 */ "lexpr ::= lexpr LOR lexpr",
 /*  95 */ "lexpr ::= LNOT lexpr",
 /*  96 */ "lexpr ::= LNOT LNOT lexpr",
 /*  97 */ "vdef_stmt ::= VAR nameList_nonEmpty",
 /*  98 */ "vdefAssign_stmt ::= VAR nameList_nonEmpty ASSIGN exprList_nonEmpty",
 /*  99 */ "vdefAssign_global_stmt ::= VAR nameList_nonEmpty ASSIGN exprList_nonEmpty",
 /* 100 */ "cdef_stmt ::= CONST nameList_nonEmpty ASSIGN exprList_nonEmpty",
 /* 101 */ "lvalue ::= NAME",
 /* 102 */ "lvalue ::= expr LSQBRACKET expr RSQBRACKET",
 /* 103 */ "lvalue ::= expr PERIOD NAME",
 /* 104 */ "lvalueList_nonEmpty ::= lvalue",
 /* 105 */ "lvalueList_nonEmpty ::= lvalueList_nonEmpty COMMA lvalue",
 /* 106 */ "assign_stmt ::= lvalue ASSIGN expr",
 /* 107 */ "assign_stmt ::= lvalueList_nonEmpty ASSIGN exprList_nonEmpty",
 /* 108 */ "assign_stmt ::= lvalue IADD expr",
 /* 109 */ "assign_stmt ::= lvalue ISUB expr",
 /* 110 */ "assign_stmt ::= lvalue IMUL expr",
 /* 111 */ "assign_stmt ::= lvalue IDIV expr",
 /* 112 */ "assign_stmt ::= lvalue IMOD expr",
 /* 113 */ "assign_stmt ::= lvalue ILSH expr",
 /* 114 */ "assign_stmt ::= lvalue IRSH expr",
 /* 115 */ "assign_stmt ::= lvalue IBND expr",
 /* 116 */ "assign_stmt ::= lvalue IBOR expr",
 /* 117 */ "assign_stmt ::= lvalue IBXR expr",
 /* 118 */ "if_start ::= IF",
 /* 119 */ "if_header ::= if_start LPAREN lexpr RPAREN",
 /* 120 */ "if_block ::= if_header stmt",
 /* 121 */ "elif_start ::= ELSE IF",
 /* 122 */ "elif_header ::= elif_start LPAREN lexpr RPAREN",
 /* 123 */ "if_block ::= if_block elif_header stmt",
 /* 124 */ "else_header ::= ELSE",
 /* 125 */ "if_stmt ::= if_block",
 /* 126 */ "if_stmt ::= if_block else_header stmt",
 /* 127 */ "while_start ::= WHILE",
 /* 128 */ "while_header ::= while_start LPAREN lexpr RPAREN",
 /* 129 */ "while_stmt ::= while_header stmt",
 /* 130 */ "for_opener ::= FOR LPAREN",
 /* 131 */ "for_init_stmt_nonEmpty ::= vdef_stmt",
 /* 132 */ "for_init_stmt_nonEmpty ::= vdefAssign_stmt",
 /* 133 */ "for_init_stmt_nonEmpty ::= cdef_stmt",
 /* 134 */ "for_init_stmt_nonEmpty ::= assign_stmt",
 /* 135 */ "for_init_stmt_nonEmpty ::= for_init_stmt_nonEmpty COMMA for_init_stmt_nonEmpty",
 /* 136 */ "for_init_stmt ::= for_init_stmt_nonEmpty",
 /* 137 */ "for_init_stmt ::=",
 /* 138 */ "for_action_stmt_nonEmpty ::= assign_stmt",
 /* 139 */ "for_action_stmt_nonEmpty ::= for_action_stmt_nonEmpty COMMA for_action_stmt_nonEmpty",
 /* 140 */ "for_header1 ::= for_opener for_init_stmt SEMICOLON",
 /* 141 */ "for_header2 ::= for_header1 lexpr SEMICOLON",
 /* 142 */ "for_header ::= for_header2 for_action_stmt_nonEmpty RPAREN",
 /* 143 */ "for_header ::= for_header2 RPAREN",
 /* 144 */ "for_stmt ::= for_header stmt",
 /* 145 */ "foreach_opener ::= FOREACH LPAREN",
 /* 146 */ "foreach_header ::= foreach_opener nameList_nonEmpty COLON exprList_nonEmpty RPAREN",
 /* 147 */ "foreach_stmt ::= foreach_header stmt",
 /* 148 */ "continue_stmt ::= CONTINUE",
 /* 149 */ "break_stmt ::= BREAK",
 /* 150 */ "return_stmt ::= RETURN exprList",
 /* 151 */ "lexpr ::= CONDITIONNAME LPAREN fArgs RPAREN",
 /* 152 */ "lexpr ::= KILLS LPAREN fArgs RPAREN",
 /* 153 */ "lexpr ::= CONDITIONNAME LPAREN RPAREN",
 /* 154 */ "action ::= ACTIONNAME LPAREN fArgs RPAREN SEMICOLON",
 /* 155 */ "actions ::= action action",
 /* 156 */ "actions ::= actions action",
 /* 157 */ "actionStmt ::= action",
 /* 158 */ "actionStmt ::= actions",
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
#line 888 "parser\\epparser.c"
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
  { 105, 1 },
  { 105, 3 },
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
#line 1344 "parser\\epparser.c"
        break;
      case 9: /* import_chunk ::= IMPORT NAME AS NAME */
#line 73 "parser\\epparser.lemon"
{
    if(!ps->closure.defModule(yymsp[0].minor.yy0->data)) {
        throw_error(6754, "Importing already-declared module " + yymsp[0].minor.yy0->data, yymsp[0].minor.yy0->line);
    }
    ps->gen << "import _" << yymsp[-2].minor.yy0->data << " as " << yymsp[0].minor.yy0->data << std::endl;
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 1355 "parser\\epparser.c"
        break;
      case 10: /* import_chunk ::= IMPORT NAME */
#line 81 "parser\\epparser.lemon"
{
    if(!ps->closure.defModule(yymsp[0].minor.yy0->data)) {
        throw_error(6754, "Importing already-declared module " + yymsp[0].minor.yy0->data, yymsp[0].minor.yy0->line);
    }
    ps->gen << "import _" << yymsp[0].minor.yy0->data << " as " << yymsp[0].minor.yy0->data << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1366 "parser\\epparser.c"
        break;
      case 11: /* function_start ::= FUNCTION NAME */
#line 90 "parser\\epparser.lemon"
{
    // Preprocess yymsp[0].minor.yy0
    funcNamePreprocess(yymsp[0].minor.yy0->data);
    if(!ps->closure.defFunction(yymsp[0].minor.yy0->data)) {
        throw_error(4495, "Duplicate function " + yymsp[0].minor.yy0->data, yymsp[0].minor.yy0->line);
    }
    ps->closure.pushScope();
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1379 "parser\\epparser.c"
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
            throw_error(196, ("Redeclaration of variable \'" + varname + "\'"), yymsp[-1].minor.yy0->line);
        }
    });

    tmpIndex = 1;
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1398 "parser\\epparser.c"
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
#line 1409 "parser\\epparser.c"
        break;
      case 14: /* fdef_chunk ::= function_header stmt */
      case 147: /* foreach_stmt ::= foreach_header stmt */ yytestcase(yyruleno==147);
#line 124 "parser\\epparser.lemon"
{
    ps->gen.unindent(true);
    ps->closure.popScope();
}
#line 1418 "parser\\epparser.c"
        break;
      case 15: /* stmt ::= error SEMICOLON */
#line 131 "parser\\epparser.lemon"
{ throw_error(6974, "Error while parsing statement", yymsp[0].minor.yy0->line); delete yymsp[0].minor.yy0; }
#line 1423 "parser\\epparser.c"
        break;
      case 18: /* lbracket ::= LBRACKET */
#line 137 "parser\\epparser.lemon"
{ ps->closure.pushScope(); }
#line 1428 "parser\\epparser.c"
        break;
      case 19: /* rbracket ::= RBRACKET */
#line 138 "parser\\epparser.lemon"
{ ps->closure.popScope(); }
#line 1433 "parser\\epparser.c"
        break;
      case 20: /* blockStmt ::= lbracket RBRACKET */
#line 140 "parser\\epparser.lemon"
{
    ps->gen << "pass" << std::endl;
    ps->closure.popScope();
}
#line 1441 "parser\\epparser.c"
        break;
      case 24: /* blockStmt ::= lbracket error RBRACKET */
#line 147 "parser\\epparser.lemon"
{
    throw_error(6298, "Block not terminated properly.", yymsp[0].minor.yy0->line);
    ps->closure.popScope();
    delete yymsp[0].minor.yy0;
}
#line 1450 "parser\\epparser.c"
        break;
      case 31: /* bodyStmt ::= funcexpr SEMICOLON */
#line 159 "parser\\epparser.lemon"
{ ps->gen << yymsp[-1].minor.yy0->data << std::endl; }
#line 1455 "parser\\epparser.c"
        break;
      case 41: /* bodyStmtList ::= bodyStmtList error */
#line 171 "parser\\epparser.lemon"
{
    throw_error(8510, "Incomplete statement");
}
#line 1462 "parser\\epparser.c"
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
      case 85: /* lexpr ::= expr */ yytestcase(yyruleno==85);
      case 96: /* lexpr ::= LNOT LNOT lexpr */ yytestcase(yyruleno==96);
      case 104: /* lvalueList_nonEmpty ::= lvalue */ yytestcase(yyruleno==104);
#line 177 "parser\\epparser.lemon"
{ yygotominor.yy0 = yymsp[0].minor.yy0; }
#line 1478 "parser\\epparser.c"
        break;
      case 43: /* numList_nonEmpty ::= numList_nonEmpty COMMA NUMBER */
      case 45: /* nameList_nonEmpty ::= nameList_nonEmpty COMMA NAME */ yytestcase(yyruleno==45);
      case 105: /* lvalueList_nonEmpty ::= lvalueList_nonEmpty COMMA lvalue */ yytestcase(yyruleno==105);
#line 178 "parser\\epparser.lemon"
{ yygotominor.yy0 = commaConcat(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1485 "parser\\epparser.c"
        break;
      case 46: /* exprList_nonEmpty ::= funcexpr LSQBRACKET LSQBRACKET numList_nonEmpty RSQBRACKET RSQBRACKET */
#line 182 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "_SRET(" + yymsp[-5].minor.yy0->data + ", [" + yymsp[-2].minor.yy0->data + "])";
    delete yymsp[-5].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1494 "parser\\epparser.c"
        break;
      case 47: /* expr ::= funcexpr LSQBRACKET LSQBRACKET NUMBER RSQBRACKET RSQBRACKET */
#line 189 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-5].minor.yy0->data + "[" + yymsp[-2].minor.yy0->data + "]";
    delete yymsp[-5].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1503 "parser\\epparser.c"
        break;
      case 49: /* exprList_nonEmpty ::= exprList_nonEmpty COMMA exprList_nonEmpty */
#line 197 "parser\\epparser.lemon"
{ yygotominor.yy0 = new Token((yymsp[-2].minor.yy0->data) + ", " + (yymsp[0].minor.yy0->data), yymsp[0].minor.yy0); delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1508 "parser\\epparser.c"
        break;
      case 50: /* exprList ::= */
      case 60: /* fArgs ::= */ yytestcase(yyruleno==60);
#line 199 "parser\\epparser.lemon"
{ yygotominor.yy0 = genEmpty(); }
#line 1514 "parser\\epparser.c"
        break;
      case 53: /* expr ::= KILLS */
#line 204 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = "4";
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1522 "parser\\epparser.c"
        break;
      case 54: /* expr ::= NAME */
#line 209 "parser\\epparser.lemon"
{
    checkIsRValue(yymsp[0].minor.yy0->data, yymsp[0].minor.yy0->line);
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1530 "parser\\epparser.c"
        break;
      case 55: /* expr ::= expr PERIOD NAME */
#line 214 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + "." + yymsp[0].minor.yy0->data;
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1539 "parser\\epparser.c"
        break;
      case 56: /* expr ::= expr LSQBRACKET expr RSQBRACKET */
#line 220 "parser\\epparser.lemon"
{
    yymsp[-3].minor.yy0->data = yymsp[-3].minor.yy0->data + "[" + yymsp[-1].minor.yy0->data + "]";
    delete yymsp[-1].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 1548 "parser\\epparser.c"
        break;
      case 59: /* fArgs_nonEmpty ::= fArgs_nonEmpty COMMA fArgs_nonEmpty */
#line 229 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data;
    yymsp[-2].minor.yy0->type = TOKEN_TEMP;
    yygotominor.yy0 = yymsp[-2].minor.yy0;
    delete yymsp[0].minor.yy0;
}
#line 1558 "parser\\epparser.c"
        break;
      case 62: /* funcexpr ::= NAME LPAREN fArgs RPAREN */
#line 239 "parser\\epparser.lemon"
{
    // Preprocess yymsp[-3].minor.yy0
    funcNamePreprocess(yymsp[-3].minor.yy0->data);
    checkIsFunction(yymsp[-3].minor.yy0->data, yymsp[-3].minor.yy0->line);
    yymsp[-3].minor.yy0->data += "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 1569 "parser\\epparser.c"
        break;
      case 63: /* funcexpr ::= expr LPAREN fArgs RPAREN */
#line 247 "parser\\epparser.lemon"
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
#line 1591 "parser\\epparser.c"
        break;
      case 65: /* expr ::= LPAREN expr RPAREN */
      case 86: /* lexpr ::= LPAREN lexpr RPAREN */ yytestcase(yyruleno==86);
#line 269 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1600 "parser\\epparser.c"
        break;
      case 66: /* expr ::= LSQBRACKET exprList RSQBRACKET */
#line 274 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "EUDArray(FlattenList([" + yymsp[-1].minor.yy0->data + "]))";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1608 "parser\\epparser.c"
        break;
      case 67: /* expr ::= L2V LPAREN lexpr RPAREN */
#line 279 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "_L2V(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = genTemp(yymsp[-1].minor.yy0);
}
#line 1616 "parser\\epparser.c"
        break;
      case 68: /* expr ::= MAPSTRING LPAREN STRING RPAREN */
#line 284 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetStringIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1624 "parser\\epparser.c"
        break;
      case 69: /* expr ::= UNIT LPAREN STRING RPAREN */
#line 289 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "EncodeUnit(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1632 "parser\\epparser.c"
        break;
      case 70: /* expr ::= SWITCH LPAREN STRING RPAREN */
#line 294 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "EncodeSwitch(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1640 "parser\\epparser.c"
        break;
      case 71: /* expr ::= LOCATION LPAREN STRING RPAREN */
#line 299 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetLocationIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1648 "parser\\epparser.c"
        break;
      case 72: /* expr ::= expr PLUS expr */
#line 305 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "+",  yymsp[0].minor.yy0); }
#line 1653 "parser\\epparser.c"
        break;
      case 73: /* expr ::= expr MINUS expr */
#line 306 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "-",  yymsp[0].minor.yy0); }
#line 1658 "parser\\epparser.c"
        break;
      case 74: /* expr ::= expr MULTIPLY expr */
#line 307 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "*",  yymsp[0].minor.yy0); }
#line 1663 "parser\\epparser.c"
        break;
      case 75: /* expr ::= expr DIVIDE expr */
#line 308 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "//", yymsp[0].minor.yy0); }
#line 1668 "parser\\epparser.c"
        break;
      case 76: /* expr ::= expr MOD expr */
#line 309 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "%",  yymsp[0].minor.yy0); }
#line 1673 "parser\\epparser.c"
        break;
      case 77: /* expr ::= expr LSHIFT expr */
#line 310 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "<<", yymsp[0].minor.yy0); }
#line 1678 "parser\\epparser.c"
        break;
      case 78: /* expr ::= expr RSHIFT expr */
#line 311 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, ">>", yymsp[0].minor.yy0); }
#line 1683 "parser\\epparser.c"
        break;
      case 79: /* expr ::= expr BITAND expr */
#line 312 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "&",  yymsp[0].minor.yy0); }
#line 1688 "parser\\epparser.c"
        break;
      case 80: /* expr ::= expr BITOR expr */
#line 313 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "|",  yymsp[0].minor.yy0); }
#line 1693 "parser\\epparser.c"
        break;
      case 81: /* expr ::= expr BITXOR expr */
#line 314 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "^",  yymsp[0].minor.yy0); }
#line 1698 "parser\\epparser.c"
        break;
      case 82: /* expr ::= PLUS expr */
#line 317 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = +" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1703 "parser\\epparser.c"
        break;
      case 83: /* expr ::= MINUS expr */
#line 318 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = -" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1708 "parser\\epparser.c"
        break;
      case 84: /* expr ::= BITNOT expr */
#line 319 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = ~" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1713 "parser\\epparser.c"
        break;
      case 87: /* lexpr ::= expr EQ expr */
#line 329 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "==", yymsp[0].minor.yy0); }
#line 1718 "parser\\epparser.c"
        break;
      case 88: /* lexpr ::= expr NE expr */
#line 330 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "!=", yymsp[0].minor.yy0); }
#line 1723 "parser\\epparser.c"
        break;
      case 89: /* lexpr ::= expr LE expr */
#line 331 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "<=", yymsp[0].minor.yy0); }
#line 1728 "parser\\epparser.c"
        break;
      case 90: /* lexpr ::= expr LT expr */
#line 332 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "<",  yymsp[0].minor.yy0); }
#line 1733 "parser\\epparser.c"
        break;
      case 91: /* lexpr ::= expr GE expr */
#line 333 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, ">=", yymsp[0].minor.yy0); }
#line 1738 "parser\\epparser.c"
        break;
      case 92: /* lexpr ::= expr GT expr */
#line 334 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, ">" , yymsp[0].minor.yy0); }
#line 1743 "parser\\epparser.c"
        break;
      case 93: /* lexpr ::= lexpr LAND lexpr */
#line 337 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "[" + yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data + "]";
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1752 "parser\\epparser.c"
        break;
      case 94: /* lexpr ::= lexpr LOR lexpr */
#line 343 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "EUDOr([" + yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data + "])";
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1761 "parser\\epparser.c"
        break;
      case 95: /* lexpr ::= LNOT lexpr */
#line 349 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = "EUDNot([" + yymsp[0].minor.yy0->data + "])";
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0);
}
#line 1769 "parser\\epparser.c"
        break;
      case 97: /* vdef_stmt ::= VAR nameList_nonEmpty */
#line 359 "parser\\epparser.lemon"
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
#line 1793 "parser\\epparser.c"
        break;
      case 98: /* vdefAssign_stmt ::= VAR nameList_nonEmpty ASSIGN exprList_nonEmpty */
#line 380 "parser\\epparser.lemon"
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
#line 1818 "parser\\epparser.c"
        break;
      case 99: /* vdefAssign_global_stmt ::= VAR nameList_nonEmpty ASSIGN exprList_nonEmpty */
#line 402 "parser\\epparser.lemon"
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
#line 1842 "parser\\epparser.c"
        break;
      case 100: /* cdef_stmt ::= CONST nameList_nonEmpty ASSIGN exprList_nonEmpty */
#line 423 "parser\\epparser.lemon"
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
#line 1864 "parser\\epparser.c"
        break;
      case 101: /* lvalue ::= NAME */
#line 443 "parser\\epparser.lemon"
{
    checkIsVariable(yymsp[0].minor.yy0->data, yymsp[0].minor.yy0->line);
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1872 "parser\\epparser.c"
        break;
      case 102: /* lvalue ::= expr LSQBRACKET expr RSQBRACKET */
#line 448 "parser\\epparser.lemon"
{
    checkIsConstant(yymsp[-3].minor.yy0->data, yymsp[-3].minor.yy0->line);
    yymsp[-1].minor.yy0->data = "_ARRW(" + yymsp[-3].minor.yy0->data + ", " + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
    delete yymsp[-3].minor.yy0;
}
#line 1882 "parser\\epparser.c"
        break;
      case 103: /* lvalue ::= expr PERIOD NAME */
#line 455 "parser\\epparser.lemon"
{
    checkIsConstant(yymsp[-2].minor.yy0->data, yymsp[-2].minor.yy0->line);
    yymsp[0].minor.yy0->data = "_ATTW(" + yymsp[-2].minor.yy0->data + ", '" + yymsp[0].minor.yy0->data + "')";
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0);
    delete yymsp[-2].minor.yy0;
}
#line 1892 "parser\\epparser.c"
        break;
      case 106: /* assign_stmt ::= lvalue ASSIGN expr */
#line 464 "parser\\epparser.lemon"
{
    ps->gen << yymsp[-2].minor.yy0->data << " << (" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 1900 "parser\\epparser.c"
        break;
      case 107: /* assign_stmt ::= lvalueList_nonEmpty ASSIGN exprList_nonEmpty */
#line 469 "parser\\epparser.lemon"
{
    ps->gen << "_SV([" << yymsp[-2].minor.yy0->data << "], [" << yymsp[0].minor.yy0->data << "])" << std::endl;
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 1908 "parser\\epparser.c"
        break;
      case 108: /* assign_stmt ::= lvalue IADD expr */
#line 477 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__iadd__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1913 "parser\\epparser.c"
        break;
      case 109: /* assign_stmt ::= lvalue ISUB expr */
#line 478 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__isub__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1918 "parser\\epparser.c"
        break;
      case 110: /* assign_stmt ::= lvalue IMUL expr */
#line 479 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__imul__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1923 "parser\\epparser.c"
        break;
      case 111: /* assign_stmt ::= lvalue IDIV expr */
#line 480 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ifloordiv__("  << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1928 "parser\\epparser.c"
        break;
      case 112: /* assign_stmt ::= lvalue IMOD expr */
#line 481 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__imod__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1933 "parser\\epparser.c"
        break;
      case 113: /* assign_stmt ::= lvalue ILSH expr */
#line 482 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ilshift__("    << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1938 "parser\\epparser.c"
        break;
      case 114: /* assign_stmt ::= lvalue IRSH expr */
#line 483 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__irshift__("    << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1943 "parser\\epparser.c"
        break;
      case 115: /* assign_stmt ::= lvalue IBND expr */
#line 484 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__iand__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1948 "parser\\epparser.c"
        break;
      case 116: /* assign_stmt ::= lvalue IBOR expr */
#line 485 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ior__("        << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1953 "parser\\epparser.c"
        break;
      case 117: /* assign_stmt ::= lvalue IBXR expr */
#line 486 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ixor__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1958 "parser\\epparser.c"
        break;
      case 118: /* if_start ::= IF */
#line 489 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDIf()" << std::endl;
}
#line 1966 "parser\\epparser.c"
        break;
      case 119: /* if_header ::= if_start LPAREN lexpr RPAREN */
      case 128: /* while_header ::= while_start LPAREN lexpr RPAREN */ yytestcase(yyruleno==128);
#line 494 "parser\\epparser.lemon"
{
    ps->gen << "if " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data << "):" << std::endl;
    ps->gen.indent();
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1976 "parser\\epparser.c"
        break;
      case 121: /* elif_start ::= ELSE IF */
#line 502 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen.unindent(false);
    ps->gen << yygotominor.yy0->data << " = EUDElseIf()" << std::endl;
}
#line 1985 "parser\\epparser.c"
        break;
      case 122: /* elif_header ::= elif_start LPAREN lexpr RPAREN */
#line 508 "parser\\epparser.lemon"
{
    ps->gen << "if " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data <<"):" << std::endl;
    ps->gen.indent();
}
#line 1993 "parser\\epparser.c"
        break;
      case 124: /* else_header ::= ELSE */
#line 515 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "if EUDElse()():" << std::endl;
    ps->gen.indent();
}
#line 2002 "parser\\epparser.c"
        break;
      case 125: /* if_stmt ::= if_block */
      case 126: /* if_stmt ::= if_block else_header stmt */ yytestcase(yyruleno==126);
#line 521 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndIf()" << std::endl;
}
#line 2011 "parser\\epparser.c"
        break;
      case 127: /* while_start ::= WHILE */
#line 533 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDWhile()" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2020 "parser\\epparser.c"
        break;
      case 129: /* while_stmt ::= while_header stmt */
#line 545 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndWhile()" << std::endl;
}
#line 2028 "parser\\epparser.c"
        break;
      case 130: /* for_opener ::= FOR LPAREN */
      case 145: /* foreach_opener ::= FOREACH LPAREN */ yytestcase(yyruleno==145);
#line 551 "parser\\epparser.lemon"
{
    ps->closure.pushScope();
}
#line 2036 "parser\\epparser.c"
        break;
      case 140: /* for_header1 ::= for_opener for_init_stmt SEMICOLON */
#line 567 "parser\\epparser.lemon"
{
    // opening for lexpr
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDWhile()" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2046 "parser\\epparser.c"
        break;
      case 141: /* for_header2 ::= for_header1 lexpr SEMICOLON */
#line 574 "parser\\epparser.lemon"
{
    ps->gen << "if " << yymsp[-2].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data << "):" << std::endl;
    ps->gen.indent();
    delete yymsp[-2].minor.yy0; delete yymsp[-1].minor.yy0;

    // Opening for assign_statement
    yygotominor.yy0 = genTemp(yymsp[-1].minor.yy0);
    ps->gen << "def " << yygotominor.yy0->data <<"():" << std::endl;
    ps->gen.indent();
}
#line 2060 "parser\\epparser.c"
        break;
      case 142: /* for_header ::= for_header2 for_action_stmt_nonEmpty RPAREN */
#line 585 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-2].minor.yy0;
    ps->gen.unindent(false);
}
#line 2068 "parser\\epparser.c"
        break;
      case 143: /* for_header ::= for_header2 RPAREN */
#line 590 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
    ps->gen << "pass" << std::endl;
    ps->gen.unindent(false);
}
#line 2077 "parser\\epparser.c"
        break;
      case 144: /* for_stmt ::= for_header stmt */
#line 596 "parser\\epparser.lemon"
{
    ps->gen << yymsp[-1].minor.yy0->data << "()" << std::endl;
    ps->gen.unindent(false);
    ps->gen << "EUDEndWhile()" << std::endl;
    ps->closure.popScope();
}
#line 2087 "parser\\epparser.c"
        break;
      case 146: /* foreach_header ::= foreach_opener nameList_nonEmpty COLON exprList_nonEmpty RPAREN */
#line 610 "parser\\epparser.lemon"
{
    commaListIter(yymsp[-3].minor.yy0->data, [&](std::string& s) {
        ps->closure.defVariable(s);
    });
    ps->gen << "for " << yymsp[-3].minor.yy0->data << " in " << yymsp[-1].minor.yy0->data << ":" << std::endl;
    ps->gen.indent();
}
#line 2098 "parser\\epparser.c"
        break;
      case 148: /* continue_stmt ::= CONTINUE */
#line 626 "parser\\epparser.lemon"
{
    ps->gen << "EUDContinue()" << std::endl;
}
#line 2105 "parser\\epparser.c"
        break;
      case 149: /* break_stmt ::= BREAK */
#line 630 "parser\\epparser.lemon"
{
    ps->gen << "EUDBreak()" << std::endl;
}
#line 2112 "parser\\epparser.c"
        break;
      case 150: /* return_stmt ::= RETURN exprList */
#line 637 "parser\\epparser.lemon"
{
    ps->gen << "EUDReturn(" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2120 "parser\\epparser.c"
        break;
      case 151: /* lexpr ::= CONDITIONNAME LPAREN fArgs RPAREN */
      case 152: /* lexpr ::= KILLS LPAREN fArgs RPAREN */ yytestcase(yyruleno==152);
#line 645 "parser\\epparser.lemon"
{
    yymsp[-3].minor.yy0->data = yymsp[-3].minor.yy0->data + "(" + yymsp[-1].minor.yy0->data + ")";
    delete yymsp[-1].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 2130 "parser\\epparser.c"
        break;
      case 153: /* lexpr ::= CONDITIONNAME LPAREN RPAREN */
#line 657 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + "()";
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 2138 "parser\\epparser.c"
        break;
      case 154: /* action ::= ACTIONNAME LPAREN fArgs RPAREN SEMICOLON */
#line 662 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[-4].minor.yy0);
    yygotominor.yy0->data =  yymsp[-4].minor.yy0->data + "(" + yymsp[-2].minor.yy0->data + ")";
    delete yymsp[-4].minor.yy0; delete yymsp[-2].minor.yy0;
}
#line 2147 "parser\\epparser.c"
        break;
      case 155: /* actions ::= action action */
      case 156: /* actions ::= actions action */ yytestcase(yyruleno==156);
#line 668 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
    yymsp[-1].minor.yy0->data += ",\n" + yymsp[0].minor.yy0->data;
    delete yymsp[0].minor.yy0;
}
#line 2157 "parser\\epparser.c"
        break;
      case 157: /* actionStmt ::= action */
#line 680 "parser\\epparser.lemon"
{
    ps->gen << "DoActions(" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2165 "parser\\epparser.c"
        break;
      case 158: /* actionStmt ::= actions */
#line 685 "parser\\epparser.lemon"
{
    ps->gen << "DoActions([" << std::endl;
    ps->gen.indent();
    ps->gen << yymsp[0].minor.yy0->data << std::endl;
    ps->gen.unindent(false);
    ps->gen << "])" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2177 "parser\\epparser.c"
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
      /* (120) if_block ::= if_header stmt */ yytestcase(yyruleno==120);
      /* (123) if_block ::= if_block elif_header stmt */ yytestcase(yyruleno==123);
      /* (131) for_init_stmt_nonEmpty ::= vdef_stmt */ yytestcase(yyruleno==131);
      /* (132) for_init_stmt_nonEmpty ::= vdefAssign_stmt */ yytestcase(yyruleno==132);
      /* (133) for_init_stmt_nonEmpty ::= cdef_stmt */ yytestcase(yyruleno==133);
      /* (134) for_init_stmt_nonEmpty ::= assign_stmt */ yytestcase(yyruleno==134);
      /* (135) for_init_stmt_nonEmpty ::= for_init_stmt_nonEmpty COMMA for_init_stmt_nonEmpty */ yytestcase(yyruleno==135);
      /* (136) for_init_stmt ::= for_init_stmt_nonEmpty */ yytestcase(yyruleno==136);
      /* (137) for_init_stmt ::= */ yytestcase(yyruleno==137);
      /* (138) for_action_stmt_nonEmpty ::= assign_stmt */ yytestcase(yyruleno==138);
      /* (139) for_action_stmt_nonEmpty ::= for_action_stmt_nonEmpty COMMA for_action_stmt_nonEmpty */ yytestcase(yyruleno==139);
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
#line 2267 "parser\\epparser.c"
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
#line 699 "parser\\epparser.lemon"


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
#line 2520 "parser\\epparser.c"
