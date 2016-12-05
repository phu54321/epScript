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
#define YYNOCODE 129
#define YYACTIONTYPE unsigned short int
#define ParseTOKENTYPE Token*
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  int yy257;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL  ParserStruct* ps ;
#define ParseARG_PDECL , ParserStruct* ps 
#define ParseARG_FETCH  ParserStruct* ps  = yypParser->ps 
#define ParseARG_STORE yypParser->ps  = ps 
#define YYNSTATE 318
#define YYNRULE 163
#define YYERRORSYMBOL 69
#define YYERRSYMDT yy257
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
#define YY_ACTTAB_COUNT (1255)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   205,  235,  191,   28,   29,   18,   28,   29,  201,   73,
 /*    10 */   199,  295,  189,  101,  305,  303,  204,    2,  115,  138,
 /*    20 */   200,  198,  143,  287,  286,  285,  284,  283,  193,  192,
 /*    30 */   185,  234,  263,  101,  188,  257,   28,   29,  115,  138,
 /*    40 */   156,    8,   40,  316,  271,  108,  153,    6,   10,   38,
 /*    50 */   206,  205,   22,   13,    5,   79,    4,   78,   77,  201,
 /*    60 */   236,  199,  295,  313,  184,  250,  303,  204,    2,  312,
 /*    70 */    74,  200,  198,  143,  287,  286,  285,  284,  283,  193,
 /*    80 */   192,  154,    7,    3,  101,  188,  289,   37,  206,  115,
 /*    90 */   138,  156,    8,   40,  197,  159,  108,  153,    6,   10,
 /*   100 */    19,  311,  191,   22,   13,    5,   79,    4,   78,   77,
 /*   110 */   205,  235,  191,  109,  213,  180,  161,  208,  201,  206,
 /*   120 */   199,  295,  212,  101,  247,  303,  204,    2,  115,  138,
 /*   130 */   200,  198,  143,  287,  286,  285,  284,  283,  193,  192,
 /*   140 */    14,  137,  191,  101,  188,   28,   29,   75,  115,  138,
 /*   150 */   156,    8,   40,  110,  158,  108,  153,    6,   10,   35,
 /*   160 */    36,  205,   22,   13,    5,   79,    4,   78,   77,  201,
 /*   170 */   233,  199,  295,  209,  251,  244,  303,  204,    2,  309,
 /*   180 */    34,  200,  198,  143,  287,  286,  285,  284,  283,  193,
 /*   190 */   192,  207,   28,   29,  101,  191,   28,   29,  210,  115,
 /*   200 */   138,  156,    8,   40,   33,  206,  101,  153,    6,   10,
 /*   210 */   308,  253,  188,   22,   13,    5,   79,    4,   78,   77,
 /*   220 */   205,  248,  183,  108,  163,  245,   39,  191,  201,  206,
 /*   230 */   199,  295,  306,  196,  231,  303,  204,    2,   89,  197,
 /*   240 */   200,  198,  143,  287,  286,  285,  284,  283,  193,  192,
 /*   250 */   482,   11,  191,  101,  188,  304,  229,  302,  115,  138,
 /*   260 */   156,    8,   40,  121,  157,  108,  153,    6,   10,  191,
 /*   270 */    84,  205,   22,   13,    5,   79,    4,   78,   77,  201,
 /*   280 */    86,  199,  295,   83,  126,  228,  303,  204,    2,  293,
 /*   290 */   292,  200,  198,  143,  287,  286,  285,  284,  283,  193,
 /*   300 */   192,  291,  290,  191,  101,  188,  195,  194,  288,  115,
 /*   310 */   138,  156,    8,   40,  120,  135,  108,  153,    6,   10,
 /*   320 */   191,  282,  188,   22,   13,    5,   79,    4,   78,   77,
 /*   330 */   205,   85,  183,  108,  225,  127,  281,  191,  201,   19,
 /*   340 */   199,  295,  276,  273,  221,  303,  204,    2,  133,  187,
 /*   350 */   200,  198,  143,  287,  286,  285,  284,  283,  193,  192,
 /*   360 */    82,   39,  272,  101,  188,   31,   17,   32,  115,  138,
 /*   370 */   156,    8,   40,  178,  144,  108,  153,    6,   10,  191,
 /*   380 */   177,  145,   22,   13,    5,   79,    4,   78,   77,  201,
 /*   390 */    86,  199,  295,  268,  262,  175,  219,  203,    2,  174,
 /*   400 */     1,  200,  198,  143,  287,  286,  285,  284,  283,  193,
 /*   410 */   192,  267,  172,  171,  101,  191,  266,  169,   29,  115,
 /*   420 */   138,  156,    8,   40,  168,  265,  132,  153,    6,   10,
 /*   430 */   191,  256,  264,   22,   13,    5,   79,    4,   78,   77,
 /*   440 */   279,  109,  191,  180,  162,  259,   15,  113,  201,  255,
 /*   450 */   199,  295,  254,  131,   25,  280,  202,    2,  297,  249,
 /*   460 */   200,  198,  143,  287,  286,  285,  284,  283,  193,  192,
 /*   470 */    24,   23,  243,  101,  191,   12,  237,  230,  115,  138,
 /*   480 */   156,    8,   40,   16,  224,   86,  153,    6,   10,  166,
 /*   490 */   191,  298,   22,   13,    5,   79,    4,   78,   77,   61,
 /*   500 */    60,  119,   69,   70,   68,   59,  278,  111,  294,  146,
 /*   510 */   220,  296,   62,   18,  301,  300,   21,   73,  277,  299,
 /*   520 */   189,  141,  182,  179,  176,  173,  170,   81,   80,   67,
 /*   530 */    66,   72,   71,   69,   70,   68,  186,  140,  307,  252,
 /*   540 */   148,  246,  152,  149,   18,  227,  226,   20,   73,  148,
 /*   550 */   191,  189,  223,  139,  136,  222,  134,  191,   61,   60,
 /*   560 */   155,  109,  483,  269,   59,  278,  111,  294,   86,  483,
 /*   570 */   483,   62,  261,  301,  299,   21,  483,  277,  191,  483,
 /*   580 */   483,  182,  179,  176,  173,  170,   81,   80,  191,  118,
 /*   590 */    72,   71,   69,   70,   68,  483,  483,  483,  252,  117,
 /*   600 */   246,  152,  149,   18,  227,  226,   20,   73,  148,  191,
 /*   610 */   189,  483,  483,  483,  483,  483,  191,   61,   60,  483,
 /*   620 */   114,  483,  191,   59,  278,  111,  294,   86,  483,  483,
 /*   630 */    62,  260,  301,  116,   21,  483,  277,  191,  191,  483,
 /*   640 */   182,  179,  176,  173,  170,   81,   80,  483,  109,   86,
 /*   650 */   180,  167,  483,  125,  483,  191,  483,  252,  483,  246,
 /*   660 */   152,  149,  483,  227,  226,   20,   88,  148,   58,   56,
 /*   670 */    55,   54,   53,   57,   64,   63,   65,   67,   66,   72,
 /*   680 */    71,   69,   70,   68,  191,  483,  483,  483,  483,  483,
 /*   690 */   483,  483,   18,  274,  483,  109,   73,  180,  147,  189,
 /*   700 */    58,   56,   55,   54,   53,   57,   64,   63,   65,   67,
 /*   710 */    66,   72,   71,   69,   70,   68,   27,  483,  483,  483,
 /*   720 */   242,  483,  240,  483,   18,  483,  483,  483,   73,   61,
 /*   730 */    60,  189,  241,  239,  191,   59,  278,  190,  318,  483,
 /*   740 */   483,  483,   30,  483,  483,  101,   21,  191,  181,  483,
 /*   750 */   115,  138,  182,  179,  176,  173,  170,  483,  130,  191,
 /*   760 */    26,  151,  150,  483,  191,  191,  214,  483,  211,  483,
 /*   770 */   129,  301,  191,   61,   60,  128,  107,  483,  165,   59,
 /*   780 */   278,  190,  483,   86,   76,   80,   30,  124,  483,  483,
 /*   790 */    21,  483,  181,  483,  483,  483,  182,  179,  176,  173,
 /*   800 */   170,  483,  317,  218,  315,  314,  217,  216,  215,  310,
 /*   810 */     9,   61,   60,  483,  483,    2,  191,   59,  278,  142,
 /*   820 */   483,  483,  165,  483,   62,  258,  483,   86,   21,  483,
 /*   830 */   277,  123,  270,  483,  182,  179,  176,  173,  170,  191,
 /*   840 */   191,   61,   60,  483,  483,  191,  483,   59,  278,  111,
 /*   850 */   106,   86,  191,  483,   62,  122,  105,  483,   21,  483,
 /*   860 */   277,  483,  483,  104,  182,  179,  176,  173,  170,   81,
 /*   870 */    80,  191,   64,   63,   65,   67,   66,   72,   71,   69,
 /*   880 */    70,   68,  109,  483,  180,  164,  483,  483,  191,  242,
 /*   890 */    18,  240,  483,  483,   73,  275,  483,  189,  483,  103,
 /*   900 */   483,  241,  239,  191,   64,   63,   65,   67,   66,   72,
 /*   910 */    71,   69,   70,   68,  101,  483,  191,  191,  483,  115,
 /*   920 */   138,  483,   18,  274,  191,  483,   73,  102,   87,  189,
 /*   930 */   238,  483,  483,  483,  483,  100,   64,   63,   65,   67,
 /*   940 */    66,   72,   71,   69,   70,   68,  483,  483,  483,  483,
 /*   950 */   483,  483,  483,  483,   18,  191,   61,   60,   73,  112,
 /*   960 */   191,  189,   59,  278,  142,  191,   99,  191,  483,   62,
 /*   970 */   483,   98,  483,   21,  191,  277,   97,  270,   96,  182,
 /*   980 */   179,  176,  173,  170,  483,   95,  191,  191,   61,   60,
 /*   990 */   483,  483,  483,  191,   59,  278,  111,   94,   93,  191,
 /*  1000 */   483,   62,  232,  483,   92,   21,  483,  277,  483,  483,
 /*  1010 */    91,  182,  179,  176,  173,  170,  375,  375,  375,  375,
 /*  1020 */   375,  375,  375,  375,  375,  375,  483,  483,  191,  483,
 /*  1030 */   483,  483,  483,  483,   19,  483,  483,  483,  375,   90,
 /*  1040 */   483,  375,  483,  483,  483,  483,  483,  483,   64,   63,
 /*  1050 */    65,   67,   66,   72,   71,   69,   70,   68,  483,  483,
 /*  1060 */   483,  483,  483,  483,  483,  483,   18,  483,  483,  483,
 /*  1070 */    73,  483,  483,  189,  483,  483,  483,  483,  483,  483,
 /*  1080 */    64,   63,   65,   67,   66,   72,   71,   69,   70,   68,
 /*  1090 */   483,  483,  483,  483,  483,  483,  483,  483,   18,  483,
 /*  1100 */    61,   60,   52,  483,  483,  160,   59,  278,  190,  483,
 /*  1110 */   483,  483,  483,   62,  483,  483,  483,   21,  483,  277,
 /*  1120 */   483,  483,  483,  182,  179,  176,  173,  170,  483,  483,
 /*  1130 */   483,  483,   61,   60,  483,  483,  483,  483,   59,  278,
 /*  1140 */   111,  425,  425,  483,  483,   62,  483,  483,  483,   21,
 /*  1150 */   483,  277,  483,  424,  424,  182,  179,  176,  173,  170,
 /*  1160 */    63,   65,   67,   66,   72,   71,   69,   70,   68,  483,
 /*  1170 */   483,  483,  483,  483,  483,  483,  483,   18,  483,  483,
 /*  1180 */   483,   73,  483,  483,  189,  483,  483,  483,  425,  425,
 /*  1190 */   425,  425,  425,  425,  425,  425,  425,  425,   51,  483,
 /*  1200 */   424,  424,  424,  424,  424,  424,  424,  424,  424,  424,
 /*  1210 */    65,   67,   66,   72,   71,   69,   70,   68,  483,  483,
 /*  1220 */   483,  483,  483,  483,  483,  483,   18,  483,  483,  483,
 /*  1230 */    73,  483,  483,  189,  483,  483,  483,  483,  483,  483,
 /*  1240 */   483,  483,  483,  483,  483,   50,   49,   48,   47,   46,
 /*  1250 */    45,   44,   43,   42,   41,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    69,   90,   91,    3,    4,   31,    3,    4,   77,   35,
 /*    10 */    79,   80,   38,  102,   83,   84,   85,   86,  107,  108,
 /*    20 */    89,   90,   91,   92,   93,   94,   95,   96,   97,   98,
 /*    30 */     2,  120,   32,  102,   91,   32,    3,    4,  107,  108,
 /*    40 */   109,  110,  111,   27,  101,  102,  115,  116,  117,    1,
 /*    50 */     2,   69,  121,  122,  123,  124,  125,  126,  127,   77,
 /*    60 */    27,   79,   80,   27,   36,   83,   84,   85,   86,   27,
 /*    70 */     1,   89,   90,   91,   92,   93,   94,   95,   96,   97,
 /*    80 */    98,  112,  113,  114,  102,   91,   27,    1,    2,  107,
 /*    90 */   108,  109,  110,  111,   35,  101,  102,  115,  116,  117,
 /*   100 */    31,   27,   91,  121,  122,  123,  124,  125,  126,  127,
 /*   110 */    69,   90,   91,  102,   26,  104,  105,   32,   77,    2,
 /*   120 */    79,   80,   29,  102,   83,   84,   85,   86,  107,  108,
 /*   130 */    89,   90,   91,   92,   93,   94,   95,   96,   97,   98,
 /*   140 */     2,  120,   91,  102,   91,    3,    4,   31,  107,  108,
 /*   150 */   109,  110,  111,  102,  101,  102,  115,  116,  117,    1,
 /*   160 */     2,   69,  121,  122,  123,  124,  125,  126,  127,   77,
 /*   170 */    32,   79,   80,   82,   32,   83,   84,   85,   86,   26,
 /*   180 */    63,   89,   90,   91,   92,   93,   94,   95,   96,   97,
 /*   190 */    98,  100,    3,    4,  102,   91,    3,    4,   26,  107,
 /*   200 */   108,  109,  110,  111,    1,    2,  102,  115,  116,  117,
 /*   210 */    27,  107,   91,  121,  122,  123,  124,  125,  126,  127,
 /*   220 */    69,   32,  101,  102,  103,   32,    2,   91,   77,    2,
 /*   230 */    79,   80,   26,   35,   83,   84,   85,   86,  102,   35,
 /*   240 */    89,   90,   91,   92,   93,   94,   95,   96,   97,   98,
 /*   250 */    71,   72,   91,  102,   91,   27,   32,   27,  107,  108,
 /*   260 */   109,  110,  111,  102,  101,  102,  115,  116,  117,   91,
 /*   270 */    27,   69,  121,  122,  123,  124,  125,  126,  127,   77,
 /*   280 */   102,   79,   80,   27,  106,   83,   84,   85,   86,   27,
 /*   290 */    27,   89,   90,   91,   92,   93,   94,   95,   96,   97,
 /*   300 */    98,   27,   27,   91,  102,   91,   25,   36,   36,  107,
 /*   310 */   108,  109,  110,  111,  102,  101,  102,  115,  116,  117,
 /*   320 */    91,   27,   91,  121,  122,  123,  124,  125,  126,  127,
 /*   330 */    69,  102,  101,  102,  103,  106,   27,   91,   77,   31,
 /*   340 */    79,   80,   26,   25,   83,   84,   85,   86,  102,   35,
 /*   350 */    89,   90,   91,   92,   93,   94,   95,   96,   97,   98,
 /*   360 */    35,    2,   36,  102,   91,   31,   31,    2,  107,  108,
 /*   370 */   109,  110,  111,   31,  101,  102,  115,  116,  117,   91,
 /*   380 */    39,   69,  121,  122,  123,  124,  125,  126,  127,   77,
 /*   390 */   102,   79,   80,   32,  106,   31,   84,   85,   86,   39,
 /*   400 */    88,   89,   90,   91,   92,   93,   94,   95,   96,   97,
 /*   410 */    98,   32,   31,   39,  102,   91,   32,   31,    4,  107,
 /*   420 */   108,  109,  110,  111,   39,   32,  102,  115,  116,  117,
 /*   430 */    91,   36,   32,  121,  122,  123,  124,  125,  126,  127,
 /*   440 */    69,  102,   91,  104,  105,   32,   31,   26,   77,   32,
 /*   450 */    79,   80,   32,  102,   31,   84,   85,   86,   87,   58,
 /*   460 */    89,   90,   91,   92,   93,   94,   95,   96,   97,   98,
 /*   470 */    31,   31,   31,  102,   91,    2,   27,   31,  107,  108,
 /*   480 */   109,  110,  111,   31,   27,  102,  115,  116,  117,  106,
 /*   490 */    91,   87,  121,  122,  123,  124,  125,  126,  127,   18,
 /*   500 */    19,  102,   20,   21,   22,   24,   25,   26,   27,   32,
 /*   510 */    34,   87,   31,   31,   33,   34,   35,   35,   37,   34,
 /*   520 */    38,   99,   41,   42,   43,   44,   45,   46,   47,   16,
 /*   530 */    17,   18,   19,   20,   21,   22,   25,  100,   26,   58,
 /*   540 */    68,   60,   61,   62,   31,   64,   65,   66,   35,   68,
 /*   550 */    91,   38,  126,  100,  100,  126,  100,   91,   18,   19,
 /*   560 */    59,  102,  128,  104,   24,   25,   26,   27,  102,  128,
 /*   570 */   128,   31,  106,   33,   34,   35,  128,   37,   91,  128,
 /*   580 */   128,   41,   42,   43,   44,   45,   46,   47,   91,  102,
 /*   590 */    18,   19,   20,   21,   22,  128,  128,  128,   58,  102,
 /*   600 */    60,   61,   62,   31,   64,   65,   66,   35,   68,   91,
 /*   610 */    38,  128,  128,  128,  128,  128,   91,   18,   19,  128,
 /*   620 */   102,  128,   91,   24,   25,   26,   27,  102,  128,  128,
 /*   630 */    31,  106,   33,  102,   35,  128,   37,   91,   91,  128,
 /*   640 */    41,   42,   43,   44,   45,   46,   47,  128,  102,  102,
 /*   650 */   104,  105,  128,  106,  128,   91,  128,   58,  128,   60,
 /*   660 */    61,   62,  128,   64,   65,   66,  102,   68,    7,    8,
 /*   670 */     9,   10,   11,   12,   13,   14,   15,   16,   17,   18,
 /*   680 */    19,   20,   21,   22,   91,  128,  128,  128,  128,  128,
 /*   690 */   128,  128,   31,   32,  128,  102,   35,  104,  105,   38,
 /*   700 */     7,    8,    9,   10,   11,   12,   13,   14,   15,   16,
 /*   710 */    17,   18,   19,   20,   21,   22,    5,  128,  128,  128,
 /*   720 */    77,  128,   79,  128,   31,  128,  128,  128,   35,   18,
 /*   730 */    19,   38,   89,   90,   91,   24,   25,   26,    0,  128,
 /*   740 */   128,  128,   31,  128,  128,  102,   35,   91,   37,  128,
 /*   750 */   107,  108,   41,   42,   43,   44,   45,  128,  102,   91,
 /*   760 */     5,  118,  119,  128,   91,   91,   28,  128,   30,  128,
 /*   770 */   102,   33,   91,   18,   19,  102,  102,  128,   67,   24,
 /*   780 */    25,   26,  128,  102,   46,   47,   31,  106,  128,  128,
 /*   790 */    35,  128,   37,  128,  128,  128,   41,   42,   43,   44,
 /*   800 */    45,  128,   73,   74,   75,   76,   77,   78,   79,   80,
 /*   810 */    81,   18,   19,  128,  128,   86,   91,   24,   25,   26,
 /*   820 */   128,  128,   67,  128,   31,   32,  128,  102,   35,  128,
 /*   830 */    37,  106,   39,  128,   41,   42,   43,   44,   45,   91,
 /*   840 */    91,   18,   19,  128,  128,   91,  128,   24,   25,   26,
 /*   850 */   102,  102,   91,  128,   31,  106,  102,  128,   35,  128,
 /*   860 */    37,  128,  128,  102,   41,   42,   43,   44,   45,   46,
 /*   870 */    47,   91,   13,   14,   15,   16,   17,   18,   19,   20,
 /*   880 */    21,   22,  102,  128,  104,  105,  128,  128,   91,   77,
 /*   890 */    31,   79,  128,  128,   35,   36,  128,   38,  128,  102,
 /*   900 */   128,   89,   90,   91,   13,   14,   15,   16,   17,   18,
 /*   910 */    19,   20,   21,   22,  102,  128,   91,   91,  128,  107,
 /*   920 */   108,  128,   31,   32,   91,  128,   35,  102,  102,   38,
 /*   930 */   118,  128,  128,  128,  128,  102,   13,   14,   15,   16,
 /*   940 */    17,   18,   19,   20,   21,   22,  128,  128,  128,  128,
 /*   950 */   128,  128,  128,  128,   31,   91,   18,   19,   35,   36,
 /*   960 */    91,   38,   24,   25,   26,   91,  102,   91,  128,   31,
 /*   970 */   128,  102,  128,   35,   91,   37,  102,   39,  102,   41,
 /*   980 */    42,   43,   44,   45,  128,  102,   91,   91,   18,   19,
 /*   990 */   128,  128,  128,   91,   24,   25,   26,  102,  102,   91,
 /*  1000 */   128,   31,   32,  128,  102,   35,  128,   37,  128,  128,
 /*  1010 */   102,   41,   42,   43,   44,   45,   13,   14,   15,   16,
 /*  1020 */    17,   18,   19,   20,   21,   22,  128,  128,   91,  128,
 /*  1030 */   128,  128,  128,  128,   31,  128,  128,  128,   35,  102,
 /*  1040 */   128,   38,  128,  128,  128,  128,  128,  128,   13,   14,
 /*  1050 */    15,   16,   17,   18,   19,   20,   21,   22,  128,  128,
 /*  1060 */   128,  128,  128,  128,  128,  128,   31,  128,  128,  128,
 /*  1070 */    35,  128,  128,   38,  128,  128,  128,  128,  128,  128,
 /*  1080 */    13,   14,   15,   16,   17,   18,   19,   20,   21,   22,
 /*  1090 */   128,  128,  128,  128,  128,  128,  128,  128,   31,  128,
 /*  1100 */    18,   19,   35,  128,  128,   38,   24,   25,   26,  128,
 /*  1110 */   128,  128,  128,   31,  128,  128,  128,   35,  128,   37,
 /*  1120 */   128,  128,  128,   41,   42,   43,   44,   45,  128,  128,
 /*  1130 */   128,  128,   18,   19,  128,  128,  128,  128,   24,   25,
 /*  1140 */    26,    1,    2,  128,  128,   31,  128,  128,  128,   35,
 /*  1150 */   128,   37,  128,    1,    2,   41,   42,   43,   44,   45,
 /*  1160 */    14,   15,   16,   17,   18,   19,   20,   21,   22,  128,
 /*  1170 */   128,  128,  128,  128,  128,  128,  128,   31,  128,  128,
 /*  1180 */   128,   35,  128,  128,   38,  128,  128,  128,   48,   49,
 /*  1190 */    50,   51,   52,   53,   54,   55,   56,   57,    1,  128,
 /*  1200 */    48,   49,   50,   51,   52,   53,   54,   55,   56,   57,
 /*  1210 */    15,   16,   17,   18,   19,   20,   21,   22,  128,  128,
 /*  1220 */   128,  128,  128,  128,  128,  128,   31,  128,  128,  128,
 /*  1230 */    35,  128,  128,   38,  128,  128,  128,  128,  128,  128,
 /*  1240 */   128,  128,  128,  128,  128,   48,   49,   50,   51,   52,
 /*  1250 */    53,   54,   55,   56,   57,
};
#define YY_SHIFT_USE_DFLT (-27)
#define YY_SHIFT_COUNT (218)
#define YY_SHIFT_MIN   (-26)
#define YY_SHIFT_MAX   (1197)
static const short yy_shift_ofst[] = {
 /*     0 */   -27,  540,  481,  599,  599,  599,  599,  599,  599,  599,
 /*    10 */   823,  738,  823,  970, 1114,  793,  938,  938,  938,  938,
 /*    20 */  1082, 1082,  711,  711,  711,  711,  755,  755,  711,  711,
 /*    30 */   711,  711,  938, 1082, 1082, 1082, 1114, 1082, 1082, 1082,
 /*    40 */   501, 1082, 1082, 1082, 1082, 1082, 1082, 1082, 1082, 1082,
 /*    50 */  1082, 1082, 1082, 1082, 1082, 1082, 1082, 1082, 1082, 1082,
 /*    60 */  1082, 1082, 1082, 1082, 1082, 1082, 1082, 1082, 1082, 1082,
 /*    70 */  1082, 1082, 1082, 1082, 1082,  512,  512,  472,  472,  512,
 /*    80 */   512,  512,  511,  485,  485,  661,  693,  923,  891,  859,
 /*    90 */  1035, 1035, 1035, 1035, 1035, 1035, 1035, 1035, 1035, 1035,
 /*   100 */  1035, 1067, 1035, 1035, 1035, 1035, 1035, 1035, 1035, 1035,
 /*   110 */  1035, 1003, 1152, 1140, 1146, 1197, 1195,  513,  572,  572,
 /*   120 */   482,  482,   33,  193,  189,  142,    3,    0,  -26,  -26,
 /*   130 */   -26,  -26,  -26,  -26,  203,  224,  117,  138,  158,   86,
 /*   140 */    48,   28,   69,   59,  359,  476,  457,  477,  452,  446,
 /*   150 */   449,  473,  441,  440,  439,  401,  423,  359,  359,  359,
 /*   160 */   421,  420,  417,  395,  413,  415,  414,  400,  393,  385,
 /*   170 */   386,  384,  374,  381,  379,  360,  364,  361,  341,  342,
 /*   180 */   365,  335,  334,  359,  326,  318,  271,  325,  314,  316,
 /*   190 */   308,  204,  309,  294,  272,  271,  281,  198,  275,  274,
 /*   200 */   263,  262,  256,  243,  230,  228,  206,  227,  183,   85,
 /*   210 */   116,  172,  153,   93,   88,   74,   42,   36,   16,
};
#define YY_REDUCE_USE_DFLT (-90)
#define YY_REDUCE_COUNT (84)
#define YY_REDUCE_MIN   (-89)
#define YY_REDUCE_MAX   (937)
static const short yy_reduce_ofst[] = {
 /*     0 */   179,  371,  312,  261,  202,  151,   92,   41,  -18,  -69,
 /*    10 */   643,  729,  812,   21,  -89,  780,  593,  546,  339,   11,
 /*    20 */   231,  121,  749,  725,  681,  547,  525,  466,  383,  288,
 /*    30 */   229,  178,  459,  273,  214,  163,  104,   53,   -6,  -57,
 /*    40 */   -31,  937,  908,  902,  896,  895,  883,  876,  874,  869,
 /*    50 */   864,  833,  826,  825,  797,  761,  754,  748,  674,  673,
 /*    60 */   668,  656,  564,  531,  518,  497,  487,  399,  351,  324,
 /*    70 */   246,  212,  161,  136,   51,   91,  456,  429,  426,  454,
 /*    80 */   453,  437,  422,  424,  404,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   319,  481,  481,  481,  481,  481,  481,  481,  481,  481,
 /*    10 */   459,  481,  481,  481,  481,  481,  382,  382,  382,  382,
 /*    20 */   371,  371,  481,  481,  481,  481,  481,  481,  481,  481,
 /*    30 */   481,  481,  481,  481,  481,  481,  481,  481,  481,  481,
 /*    40 */   447,  481,  481,  481,  481,  481,  481,  481,  481,  481,
 /*    50 */   481,  481,  481,  481,  481,  481,  481,  481,  481,  481,
 /*    60 */   481,  481,  481,  481,  481,  481,  481,  481,  481,  481,
 /*    70 */   481,  481,  481,  481,  481,  365,  481,  480,  479,  481,
 /*    80 */   481,  481,  481,  481,  481,  407,  407,  481,  481,  481,
 /*    90 */   439,  438,  437,  436,  435,  434,  433,  432,  431,  430,
 /*   100 */   428,  481,  414,  413,  412,  411,  410,  409,  369,  378,
 /*   110 */   380,  423,  377,  376,  402,  426,  403,  401,  400,  399,
 /*   120 */   395,  394,  481,  481,  481,  481,  481,  481,  406,  405,
 /*   130 */   404,  398,  397,  396,  419,  481,  481,  481,  481,  481,
 /*   140 */   419,  481,  375,  386,  421,  357,  481,  481,  481,  481,
 /*   150 */   481,  458,  481,  481,  481,  446,  481,  429,  422,  420,
 /*   160 */   481,  481,  481,  481,  481,  481,  416,  481,  481,  481,
 /*   170 */   481,  481,  481,  481,  481,  481,  481,  481,  481,  481,
 /*   180 */   383,  374,  481,  372,  481,  481,  361,  481,  386,  481,
 /*   190 */   375,  386,  481,  481,  481,  481,  481,  481,  481,  481,
 /*   200 */   481,  481,  481,  481,  481,  481,  481,  366,  330,  481,
 /*   210 */   481,  481,  481,  329,  481,  481,  481,  481,  481,  358,
 /*   220 */   342,  448,  478,  477,  476,  472,  471,  470,  469,  468,
 /*   230 */   467,  466,  465,  464,  461,  460,  463,  462,  457,  456,
 /*   240 */   455,  454,  453,  452,  451,  450,  449,  445,  444,  443,
 /*   250 */   442,  441,  440,  427,  384,  385,  388,  389,  475,  473,
 /*   260 */   418,  417,  415,  408,  474,  393,  392,  391,  390,  381,
 /*   270 */   379,  370,  367,  362,  387,  377,  376,  374,  373,  360,
 /*   280 */   359,  356,  355,  354,  353,  352,  351,  350,  368,  349,
 /*   290 */   348,  347,  346,  345,  344,  343,  341,  340,  339,  337,
 /*   300 */   338,  336,  335,  334,  333,  331,  364,  363,  332,  328,
 /*   310 */   327,  326,  325,  324,  323,  322,  321,  320,
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
  "fdecl_chunk",   "vdef_stmt",     "vdefAssign_global_stmt",  "cdef_stmt",   
  "blockStmt",     "fdef_header",   "nameList",      "stmt",        
  "bodyStmt",      "return_stmt",   "lbracket",      "rbracket",    
  "bodyStmtList",  "vdefAssign_stmt",  "assign_stmt",   "funcexpr",    
  "actionStmt",    "if_stmt",       "while_stmt",    "for_stmt",    
  "foreach_stmt",  "continue_stmt",  "break_stmt",    "numList_nonEmpty",
  "nameList_nonEmpty",  "exprList_nonEmpty",  "expr",          "exprList",    
  "fArgs_nonEmpty",  "fArgs",         "lexpr",         "lvalue",      
  "lvalueList_nonEmpty",  "if_start",      "if_header",     "if_block",    
  "elif_start",    "elif_header",   "else_header",   "while_start", 
  "while_header",  "for_opener",    "for_init_stmt_nonEmpty",  "for_init_stmt",
  "for_action_stmt_nonEmpty",  "for_header1",   "for_header2",   "for_header",  
  "foreach_opener",  "foreach_header",  "action",        "actions",     
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
 /* 112 */ "assign_stmt ::= lvalue IADD expr",
 /* 113 */ "assign_stmt ::= lvalue ISUB expr",
 /* 114 */ "assign_stmt ::= lvalue IMUL expr",
 /* 115 */ "assign_stmt ::= lvalue IDIV expr",
 /* 116 */ "assign_stmt ::= lvalue IMOD expr",
 /* 117 */ "assign_stmt ::= lvalue ILSH expr",
 /* 118 */ "assign_stmt ::= lvalue IRSH expr",
 /* 119 */ "assign_stmt ::= lvalue IBND expr",
 /* 120 */ "assign_stmt ::= lvalue IBOR expr",
 /* 121 */ "assign_stmt ::= lvalue IBXR expr",
 /* 122 */ "if_start ::= IF",
 /* 123 */ "if_header ::= if_start LPAREN lexpr RPAREN",
 /* 124 */ "if_block ::= if_header stmt",
 /* 125 */ "elif_start ::= ELSE IF",
 /* 126 */ "elif_header ::= elif_start LPAREN lexpr RPAREN",
 /* 127 */ "if_block ::= if_block elif_header stmt",
 /* 128 */ "else_header ::= ELSE",
 /* 129 */ "if_stmt ::= if_block",
 /* 130 */ "if_stmt ::= if_block else_header stmt",
 /* 131 */ "while_start ::= WHILE",
 /* 132 */ "while_header ::= while_start LPAREN lexpr RPAREN",
 /* 133 */ "while_stmt ::= while_header stmt",
 /* 134 */ "for_opener ::= FOR LPAREN",
 /* 135 */ "for_init_stmt_nonEmpty ::= vdef_stmt",
 /* 136 */ "for_init_stmt_nonEmpty ::= vdefAssign_stmt",
 /* 137 */ "for_init_stmt_nonEmpty ::= cdef_stmt",
 /* 138 */ "for_init_stmt_nonEmpty ::= assign_stmt",
 /* 139 */ "for_init_stmt_nonEmpty ::= for_init_stmt_nonEmpty COMMA for_init_stmt_nonEmpty",
 /* 140 */ "for_init_stmt ::= for_init_stmt_nonEmpty",
 /* 141 */ "for_init_stmt ::=",
 /* 142 */ "for_action_stmt_nonEmpty ::= assign_stmt",
 /* 143 */ "for_action_stmt_nonEmpty ::= for_action_stmt_nonEmpty COMMA for_action_stmt_nonEmpty",
 /* 144 */ "for_header1 ::= for_opener for_init_stmt SEMICOLON",
 /* 145 */ "for_header2 ::= for_header1 lexpr SEMICOLON",
 /* 146 */ "for_header ::= for_header2 for_action_stmt_nonEmpty RPAREN",
 /* 147 */ "for_header ::= for_header2 RPAREN",
 /* 148 */ "for_stmt ::= for_header stmt",
 /* 149 */ "foreach_opener ::= FOREACH LPAREN",
 /* 150 */ "foreach_header ::= foreach_opener nameList_nonEmpty COLON exprList_nonEmpty RPAREN",
 /* 151 */ "foreach_stmt ::= foreach_header stmt",
 /* 152 */ "continue_stmt ::= CONTINUE",
 /* 153 */ "break_stmt ::= BREAK",
 /* 154 */ "return_stmt ::= RETURN exprList",
 /* 155 */ "lexpr ::= CONDITIONNAME LPAREN fArgs RPAREN",
 /* 156 */ "lexpr ::= KILLS LPAREN fArgs RPAREN",
 /* 157 */ "lexpr ::= CONDITIONNAME LPAREN RPAREN",
 /* 158 */ "action ::= ACTIONNAME LPAREN fArgs RPAREN SEMICOLON",
 /* 159 */ "actions ::= action action",
 /* 160 */ "actions ::= actions action",
 /* 161 */ "actionStmt ::= action",
 /* 162 */ "actionStmt ::= actions",
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
#line 35 "parser\\epparser.lemon"
 delete (yypminor->yy0); 
#line 880 "parser\\epparser.c"
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
  { 73, 1 },
  { 73, 2 },
  { 73, 2 },
  { 73, 2 },
  { 73, 1 },
  { 74, 4 },
  { 74, 2 },
  { 81, 5 },
  { 75, 2 },
  { 76, 6 },
  { 83, 2 },
  { 83, 1 },
  { 83, 2 },
  { 86, 1 },
  { 87, 1 },
  { 80, 2 },
  { 80, 4 },
  { 80, 3 },
  { 80, 5 },
  { 80, 3 },
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
  { 88, 1 },
  { 88, 2 },
  { 88, 2 },
  { 99, 1 },
  { 99, 3 },
  { 100, 1 },
  { 100, 3 },
  { 82, 0 },
  { 82, 1 },
  { 101, 6 },
  { 102, 6 },
  { 101, 1 },
  { 101, 3 },
  { 103, 0 },
  { 103, 1 },
  { 102, 1 },
  { 102, 1 },
  { 102, 1 },
  { 102, 3 },
  { 102, 4 },
  { 104, 1 },
  { 104, 1 },
  { 104, 3 },
  { 104, 3 },
  { 105, 0 },
  { 105, 1 },
  { 91, 4 },
  { 91, 4 },
  { 102, 1 },
  { 102, 3 },
  { 102, 3 },
  { 102, 4 },
  { 102, 4 },
  { 102, 4 },
  { 102, 4 },
  { 102, 4 },
  { 102, 3 },
  { 102, 3 },
  { 102, 3 },
  { 102, 3 },
  { 102, 3 },
  { 102, 3 },
  { 102, 3 },
  { 102, 3 },
  { 102, 3 },
  { 102, 3 },
  { 102, 2 },
  { 102, 2 },
  { 102, 2 },
  { 106, 1 },
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
  { 106, 3 },
  { 77, 2 },
  { 89, 4 },
  { 78, 4 },
  { 79, 4 },
  { 107, 1 },
  { 107, 4 },
  { 107, 3 },
  { 108, 1 },
  { 108, 3 },
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
  { 109, 1 },
  { 110, 4 },
  { 111, 2 },
  { 112, 2 },
  { 113, 4 },
  { 111, 3 },
  { 114, 1 },
  { 93, 1 },
  { 93, 3 },
  { 115, 1 },
  { 116, 4 },
  { 94, 2 },
  { 117, 2 },
  { 118, 1 },
  { 118, 1 },
  { 118, 1 },
  { 118, 1 },
  { 118, 3 },
  { 119, 1 },
  { 119, 0 },
  { 120, 1 },
  { 120, 3 },
  { 121, 3 },
  { 122, 3 },
  { 123, 3 },
  { 123, 2 },
  { 95, 2 },
  { 124, 2 },
  { 125, 5 },
  { 96, 2 },
  { 97, 1 },
  { 98, 1 },
  { 85, 2 },
  { 106, 4 },
  { 106, 4 },
  { 106, 3 },
  { 126, 5 },
  { 127, 2 },
  { 127, 2 },
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
      case 9: /* chunk ::= blockStmt */
#line 70 "parser\\epparser.lemon"
{
    throw_error(48993, "Misplaced block statement");
}
#line 1340 "parser\\epparser.c"
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
#line 1351 "parser\\epparser.c"
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
#line 1362 "parser\\epparser.c"
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
#line 1390 "parser\\epparser.c"
        break;
      case 13: /* fdef_chunk ::= fdef_header stmt */
      case 151: /* foreach_stmt ::= foreach_header stmt */ yytestcase(yyruleno==151);
#line 118 "parser\\epparser.lemon"
{
    ps->gen.unindent(true);
    ps->closure.popScope();
}
#line 1399 "parser\\epparser.c"
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
#line 1410 "parser\\epparser.c"
        break;
      case 15: /* stmt ::= error SEMICOLON */
#line 132 "parser\\epparser.lemon"
{ throw_error(6974, "Error while parsing statement", yymsp[0].minor.yy0->line); delete yymsp[0].minor.yy0; }
#line 1415 "parser\\epparser.c"
        break;
      case 18: /* lbracket ::= LBRACKET */
#line 138 "parser\\epparser.lemon"
{ ps->closure.pushScope(); }
#line 1420 "parser\\epparser.c"
        break;
      case 19: /* rbracket ::= RBRACKET */
#line 139 "parser\\epparser.lemon"
{ ps->closure.popScope(); }
#line 1425 "parser\\epparser.c"
        break;
      case 20: /* blockStmt ::= lbracket RBRACKET */
#line 141 "parser\\epparser.lemon"
{
    ps->gen << "pass" << std::endl;
    ps->closure.popScope();
}
#line 1433 "parser\\epparser.c"
        break;
      case 24: /* blockStmt ::= lbracket error RBRACKET */
#line 148 "parser\\epparser.lemon"
{
    throw_error(6298, "Block not terminated properly.", yymsp[0].minor.yy0->line);
    ps->gen << "pass" << std::endl;
    ps->closure.popScope();
    delete yymsp[0].minor.yy0;
}
#line 1443 "parser\\epparser.c"
        break;
      case 31: /* bodyStmt ::= funcexpr SEMICOLON */
#line 161 "parser\\epparser.lemon"
{ ps->gen << yymsp[-1].minor.yy0->data << std::endl; }
#line 1448 "parser\\epparser.c"
        break;
      case 39: /* bodyStmtList ::= error */
#line 171 "parser\\epparser.lemon"
{
    throw_error(8510, "Incomplete statement");
    ps->gen << "pass" << std::endl;
}
#line 1456 "parser\\epparser.c"
        break;
      case 42: /* bodyStmtList ::= bodyStmtList error */
#line 178 "parser\\epparser.lemon"
{
    throw_error(8510, "Incomplete statement");
}
#line 1463 "parser\\epparser.c"
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
#line 1480 "parser\\epparser.c"
        break;
      case 44: /* numList_nonEmpty ::= numList_nonEmpty COMMA NUMBER */
      case 46: /* nameList_nonEmpty ::= nameList_nonEmpty COMMA NAME */ yytestcase(yyruleno==46);
      case 109: /* lvalueList_nonEmpty ::= lvalueList_nonEmpty COMMA lvalue */ yytestcase(yyruleno==109);
#line 185 "parser\\epparser.lemon"
{ yygotominor.yy0 = commaConcat(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1487 "parser\\epparser.c"
        break;
      case 47: /* nameList ::= */
      case 53: /* exprList ::= */ yytestcase(yyruleno==53);
      case 64: /* fArgs ::= */ yytestcase(yyruleno==64);
#line 188 "parser\\epparser.lemon"
{ yygotominor.yy0 = genEmpty(); }
#line 1494 "parser\\epparser.c"
        break;
      case 49: /* exprList_nonEmpty ::= funcexpr LSQBRACKET LSQBRACKET numList_nonEmpty RSQBRACKET RSQBRACKET */
#line 191 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "_SRET(" + yymsp[-5].minor.yy0->data + ", [" + yymsp[-2].minor.yy0->data + "])";
    delete yymsp[-5].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1503 "parser\\epparser.c"
        break;
      case 50: /* expr ::= funcexpr LSQBRACKET LSQBRACKET NUMBER RSQBRACKET RSQBRACKET */
#line 198 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-5].minor.yy0->data + "[" + yymsp[-2].minor.yy0->data + "]";
    delete yymsp[-5].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1512 "parser\\epparser.c"
        break;
      case 52: /* exprList_nonEmpty ::= exprList_nonEmpty COMMA exprList_nonEmpty */
#line 206 "parser\\epparser.lemon"
{ yygotominor.yy0 = new Token((yymsp[-2].minor.yy0->data) + ", " + (yymsp[0].minor.yy0->data), yymsp[0].minor.yy0); delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1517 "parser\\epparser.c"
        break;
      case 56: /* expr ::= KILLS */
#line 213 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = "4";
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1525 "parser\\epparser.c"
        break;
      case 57: /* expr ::= NAME */
#line 218 "parser\\epparser.lemon"
{
    checkIsRValue(yymsp[0].minor.yy0->data, yymsp[0].minor.yy0->line);
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1533 "parser\\epparser.c"
        break;
      case 58: /* expr ::= expr PERIOD NAME */
#line 223 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + "." + yymsp[0].minor.yy0->data;
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1542 "parser\\epparser.c"
        break;
      case 59: /* expr ::= expr LSQBRACKET expr RSQBRACKET */
#line 229 "parser\\epparser.lemon"
{
    yymsp[-3].minor.yy0->data = yymsp[-3].minor.yy0->data + "[" + yymsp[-1].minor.yy0->data + "]";
    delete yymsp[-1].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 1551 "parser\\epparser.c"
        break;
      case 62: /* fArgs_nonEmpty ::= NAME ASSIGN expr */
#line 238 "parser\\epparser.lemon"
{  // Keyword argument
    yymsp[0].minor.yy0->data = yymsp[-2].minor.yy0->data + "=" + yymsp[0].minor.yy0->data;
    yymsp[0].minor.yy0->type = TOKEN_TEMP;
    yygotominor.yy0 = yymsp[0].minor.yy0;
    delete yymsp[-2].minor.yy0;
}
#line 1561 "parser\\epparser.c"
        break;
      case 63: /* fArgs_nonEmpty ::= fArgs_nonEmpty COMMA fArgs_nonEmpty */
#line 245 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data;
    yymsp[0].minor.yy0->type = TOKEN_TEMP;
    yygotominor.yy0 = yymsp[0].minor.yy0;
    delete yymsp[-2].minor.yy0;
}
#line 1571 "parser\\epparser.c"
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
#line 1584 "parser\\epparser.c"
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
#line 1608 "parser\\epparser.c"
        break;
      case 69: /* expr ::= LPAREN expr RPAREN */
      case 90: /* lexpr ::= LPAREN lexpr RPAREN */ yytestcase(yyruleno==90);
#line 289 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1617 "parser\\epparser.c"
        break;
      case 70: /* expr ::= LSQBRACKET exprList RSQBRACKET */
#line 294 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "EUDArray(FlattenList([" + yymsp[-1].minor.yy0->data + "]))";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1625 "parser\\epparser.c"
        break;
      case 71: /* expr ::= L2V LPAREN lexpr RPAREN */
#line 299 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "_L2V(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = genTemp(yymsp[-1].minor.yy0);
}
#line 1633 "parser\\epparser.c"
        break;
      case 72: /* expr ::= MAPSTRING LPAREN STRING RPAREN */
#line 304 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetStringIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1641 "parser\\epparser.c"
        break;
      case 73: /* expr ::= UNIT LPAREN STRING RPAREN */
#line 309 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "EncodeUnit(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1649 "parser\\epparser.c"
        break;
      case 74: /* expr ::= SWITCH LPAREN STRING RPAREN */
#line 314 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "EncodeSwitch(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1657 "parser\\epparser.c"
        break;
      case 75: /* expr ::= LOCATION LPAREN STRING RPAREN */
#line 319 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetLocationIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1665 "parser\\epparser.c"
        break;
      case 76: /* expr ::= expr PLUS expr */
#line 325 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "+",  yymsp[0].minor.yy0); }
#line 1670 "parser\\epparser.c"
        break;
      case 77: /* expr ::= expr MINUS expr */
#line 326 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "-",  yymsp[0].minor.yy0); }
#line 1675 "parser\\epparser.c"
        break;
      case 78: /* expr ::= expr MULTIPLY expr */
#line 327 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "*",  yymsp[0].minor.yy0); }
#line 1680 "parser\\epparser.c"
        break;
      case 79: /* expr ::= expr DIVIDE expr */
#line 328 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "//", yymsp[0].minor.yy0); }
#line 1685 "parser\\epparser.c"
        break;
      case 80: /* expr ::= expr MOD expr */
#line 329 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "%",  yymsp[0].minor.yy0); }
#line 1690 "parser\\epparser.c"
        break;
      case 81: /* expr ::= expr LSHIFT expr */
#line 330 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "<<", yymsp[0].minor.yy0); }
#line 1695 "parser\\epparser.c"
        break;
      case 82: /* expr ::= expr RSHIFT expr */
#line 331 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, ">>", yymsp[0].minor.yy0); }
#line 1700 "parser\\epparser.c"
        break;
      case 83: /* expr ::= expr BITAND expr */
#line 332 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "&",  yymsp[0].minor.yy0); }
#line 1705 "parser\\epparser.c"
        break;
      case 84: /* expr ::= expr BITOR expr */
#line 333 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "|",  yymsp[0].minor.yy0); }
#line 1710 "parser\\epparser.c"
        break;
      case 85: /* expr ::= expr BITXOR expr */
#line 334 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "^",  yymsp[0].minor.yy0); }
#line 1715 "parser\\epparser.c"
        break;
      case 86: /* expr ::= PLUS expr */
#line 337 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = +" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1720 "parser\\epparser.c"
        break;
      case 87: /* expr ::= MINUS expr */
#line 338 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = -" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1725 "parser\\epparser.c"
        break;
      case 88: /* expr ::= BITNOT expr */
#line 339 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = ~" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1730 "parser\\epparser.c"
        break;
      case 91: /* lexpr ::= expr EQ expr */
#line 349 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "==", yymsp[0].minor.yy0); }
#line 1735 "parser\\epparser.c"
        break;
      case 92: /* lexpr ::= expr NE expr */
#line 350 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "!=", yymsp[0].minor.yy0); }
#line 1740 "parser\\epparser.c"
        break;
      case 93: /* lexpr ::= expr LE expr */
#line 351 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "<=", yymsp[0].minor.yy0); }
#line 1745 "parser\\epparser.c"
        break;
      case 94: /* lexpr ::= expr LT expr */
#line 352 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "<",  yymsp[0].minor.yy0); }
#line 1750 "parser\\epparser.c"
        break;
      case 95: /* lexpr ::= expr GE expr */
#line 353 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, ">=", yymsp[0].minor.yy0); }
#line 1755 "parser\\epparser.c"
        break;
      case 96: /* lexpr ::= expr GT expr */
#line 354 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, ">" , yymsp[0].minor.yy0); }
#line 1760 "parser\\epparser.c"
        break;
      case 97: /* lexpr ::= lexpr LAND lexpr */
#line 357 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "[" + yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data + "]";
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1769 "parser\\epparser.c"
        break;
      case 98: /* lexpr ::= lexpr LOR lexpr */
#line 363 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "EUDOr([" + yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data + "])";
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1778 "parser\\epparser.c"
        break;
      case 99: /* lexpr ::= LNOT lexpr */
#line 369 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = "EUDNot([" + yymsp[0].minor.yy0->data + "])";
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0);
}
#line 1786 "parser\\epparser.c"
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
#line 1810 "parser\\epparser.c"
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
#line 1835 "parser\\epparser.c"
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
#line 1859 "parser\\epparser.c"
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
#line 1881 "parser\\epparser.c"
        break;
      case 105: /* lvalue ::= NAME */
#line 463 "parser\\epparser.lemon"
{
    checkIsVariable(yymsp[0].minor.yy0->data, yymsp[0].minor.yy0->line);
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1889 "parser\\epparser.c"
        break;
      case 106: /* lvalue ::= expr LSQBRACKET expr RSQBRACKET */
#line 468 "parser\\epparser.lemon"
{
    checkIsConstant(yymsp[-3].minor.yy0->data, yymsp[-3].minor.yy0->line);
    yymsp[-1].minor.yy0->data = "_ARRW(" + yymsp[-3].minor.yy0->data + ", " + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
    delete yymsp[-3].minor.yy0;
}
#line 1899 "parser\\epparser.c"
        break;
      case 107: /* lvalue ::= expr PERIOD NAME */
#line 475 "parser\\epparser.lemon"
{
    checkIsConstant(yymsp[-2].minor.yy0->data, yymsp[-2].minor.yy0->line);
    yymsp[0].minor.yy0->data = "_ATTW(" + yymsp[-2].minor.yy0->data + ", '" + yymsp[0].minor.yy0->data + "')";
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0);
    delete yymsp[-2].minor.yy0;
}
#line 1909 "parser\\epparser.c"
        break;
      case 110: /* assign_stmt ::= lvalue ASSIGN expr */
#line 484 "parser\\epparser.lemon"
{
    ps->gen << yymsp[-2].minor.yy0->data << " << (" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 1917 "parser\\epparser.c"
        break;
      case 111: /* assign_stmt ::= lvalueList_nonEmpty ASSIGN exprList_nonEmpty */
#line 489 "parser\\epparser.lemon"
{
    ps->gen << "_SV([" << yymsp[-2].minor.yy0->data << "], [" << yymsp[0].minor.yy0->data << "])" << std::endl;
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 1925 "parser\\epparser.c"
        break;
      case 112: /* assign_stmt ::= lvalue IADD expr */
#line 497 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__iadd__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1930 "parser\\epparser.c"
        break;
      case 113: /* assign_stmt ::= lvalue ISUB expr */
#line 498 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__isub__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1935 "parser\\epparser.c"
        break;
      case 114: /* assign_stmt ::= lvalue IMUL expr */
#line 499 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__imul__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1940 "parser\\epparser.c"
        break;
      case 115: /* assign_stmt ::= lvalue IDIV expr */
#line 500 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ifloordiv__("  << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1945 "parser\\epparser.c"
        break;
      case 116: /* assign_stmt ::= lvalue IMOD expr */
#line 501 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__imod__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1950 "parser\\epparser.c"
        break;
      case 117: /* assign_stmt ::= lvalue ILSH expr */
#line 502 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ilshift__("    << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1955 "parser\\epparser.c"
        break;
      case 118: /* assign_stmt ::= lvalue IRSH expr */
#line 503 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__irshift__("    << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1960 "parser\\epparser.c"
        break;
      case 119: /* assign_stmt ::= lvalue IBND expr */
#line 504 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__iand__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1965 "parser\\epparser.c"
        break;
      case 120: /* assign_stmt ::= lvalue IBOR expr */
#line 505 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ior__("        << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1970 "parser\\epparser.c"
        break;
      case 121: /* assign_stmt ::= lvalue IBXR expr */
#line 506 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ixor__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1975 "parser\\epparser.c"
        break;
      case 122: /* if_start ::= IF */
#line 509 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDIf()" << std::endl;
}
#line 1983 "parser\\epparser.c"
        break;
      case 123: /* if_header ::= if_start LPAREN lexpr RPAREN */
      case 132: /* while_header ::= while_start LPAREN lexpr RPAREN */ yytestcase(yyruleno==132);
#line 514 "parser\\epparser.lemon"
{
    ps->gen << "if " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data << "):" << std::endl;
    ps->gen.indent();
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1993 "parser\\epparser.c"
        break;
      case 125: /* elif_start ::= ELSE IF */
#line 522 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen.unindent(false);
    ps->gen << yygotominor.yy0->data << " = EUDElseIf()" << std::endl;
}
#line 2002 "parser\\epparser.c"
        break;
      case 126: /* elif_header ::= elif_start LPAREN lexpr RPAREN */
#line 528 "parser\\epparser.lemon"
{
    ps->gen << "if " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data <<"):" << std::endl;
    ps->gen.indent();
}
#line 2010 "parser\\epparser.c"
        break;
      case 128: /* else_header ::= ELSE */
#line 535 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "if EUDElse()():" << std::endl;
    ps->gen.indent();
}
#line 2019 "parser\\epparser.c"
        break;
      case 129: /* if_stmt ::= if_block */
      case 130: /* if_stmt ::= if_block else_header stmt */ yytestcase(yyruleno==130);
#line 541 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndIf()" << std::endl;
}
#line 2028 "parser\\epparser.c"
        break;
      case 131: /* while_start ::= WHILE */
#line 553 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDWhile()" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2037 "parser\\epparser.c"
        break;
      case 133: /* while_stmt ::= while_header stmt */
#line 565 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndWhile()" << std::endl;
}
#line 2045 "parser\\epparser.c"
        break;
      case 134: /* for_opener ::= FOR LPAREN */
      case 149: /* foreach_opener ::= FOREACH LPAREN */ yytestcase(yyruleno==149);
#line 571 "parser\\epparser.lemon"
{
    ps->closure.pushScope();
}
#line 2053 "parser\\epparser.c"
        break;
      case 144: /* for_header1 ::= for_opener for_init_stmt SEMICOLON */
#line 587 "parser\\epparser.lemon"
{
    // opening for lexpr
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDWhile()" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2063 "parser\\epparser.c"
        break;
      case 145: /* for_header2 ::= for_header1 lexpr SEMICOLON */
#line 594 "parser\\epparser.lemon"
{
    ps->gen << "if " << yymsp[-2].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data << "):" << std::endl;
    ps->gen.indent();
    delete yymsp[-2].minor.yy0; delete yymsp[-1].minor.yy0;

    // Opening for assign_statement
    yygotominor.yy0 = genTemp(yymsp[-1].minor.yy0);
    ps->gen << "def " << yygotominor.yy0->data <<"():" << std::endl;
    ps->gen.indent();
}
#line 2077 "parser\\epparser.c"
        break;
      case 146: /* for_header ::= for_header2 for_action_stmt_nonEmpty RPAREN */
#line 605 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-2].minor.yy0;
    ps->gen.unindent(false);
}
#line 2085 "parser\\epparser.c"
        break;
      case 147: /* for_header ::= for_header2 RPAREN */
#line 610 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
    ps->gen << "pass" << std::endl;
    ps->gen.unindent(false);
}
#line 2094 "parser\\epparser.c"
        break;
      case 148: /* for_stmt ::= for_header stmt */
#line 616 "parser\\epparser.lemon"
{
    ps->gen << "EUDSetContinuePoint()" << std::endl;
    ps->gen << yymsp[-1].minor.yy0->data << "()" << std::endl;
    ps->gen.unindent(false);
    ps->gen << "EUDEndWhile()" << std::endl;
    ps->closure.popScope();
}
#line 2105 "parser\\epparser.c"
        break;
      case 150: /* foreach_header ::= foreach_opener nameList_nonEmpty COLON exprList_nonEmpty RPAREN */
#line 631 "parser\\epparser.lemon"
{
    commaListIter(yymsp[-3].minor.yy0->data, [&](std::string& s) {
        ps->closure.defVariable(s);
    });
    ps->gen << "for " << yymsp[-3].minor.yy0->data << " in " << yymsp[-1].minor.yy0->data << ":" << std::endl;
    ps->gen.indent();
}
#line 2116 "parser\\epparser.c"
        break;
      case 152: /* continue_stmt ::= CONTINUE */
#line 647 "parser\\epparser.lemon"
{
    ps->gen << "EUDContinue()" << std::endl;
}
#line 2123 "parser\\epparser.c"
        break;
      case 153: /* break_stmt ::= BREAK */
#line 651 "parser\\epparser.lemon"
{
    ps->gen << "EUDBreak()" << std::endl;
}
#line 2130 "parser\\epparser.c"
        break;
      case 154: /* return_stmt ::= RETURN exprList */
#line 658 "parser\\epparser.lemon"
{
    ps->gen << "EUDReturn(" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2138 "parser\\epparser.c"
        break;
      case 155: /* lexpr ::= CONDITIONNAME LPAREN fArgs RPAREN */
      case 156: /* lexpr ::= KILLS LPAREN fArgs RPAREN */ yytestcase(yyruleno==156);
#line 666 "parser\\epparser.lemon"
{
    yymsp[-3].minor.yy0->data = yymsp[-3].minor.yy0->data + "(" + yymsp[-1].minor.yy0->data + ")";
    delete yymsp[-1].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 2148 "parser\\epparser.c"
        break;
      case 157: /* lexpr ::= CONDITIONNAME LPAREN RPAREN */
#line 678 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + "()";
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 2156 "parser\\epparser.c"
        break;
      case 158: /* action ::= ACTIONNAME LPAREN fArgs RPAREN SEMICOLON */
#line 683 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[-4].minor.yy0);
    yygotominor.yy0->data =  yymsp[-4].minor.yy0->data + "(" + yymsp[-2].minor.yy0->data + ")";
    delete yymsp[-4].minor.yy0; delete yymsp[-2].minor.yy0;
}
#line 2165 "parser\\epparser.c"
        break;
      case 159: /* actions ::= action action */
      case 160: /* actions ::= actions action */ yytestcase(yyruleno==160);
#line 689 "parser\\epparser.lemon"
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
#line 2188 "parser\\epparser.c"
        break;
      case 161: /* actionStmt ::= action */
#line 727 "parser\\epparser.lemon"
{
    ps->gen << "DoActions(" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2196 "parser\\epparser.c"
        break;
      case 162: /* actionStmt ::= actions */
#line 732 "parser\\epparser.lemon"
{
    ps->gen << "DoActions([" << std::endl;
    ps->gen.indent();
    ps->gen << yymsp[0].minor.yy0->data << std::endl;
    ps->gen.unindent(false);
    ps->gen << "])" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2208 "parser\\epparser.c"
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
      /* (124) if_block ::= if_header stmt */ yytestcase(yyruleno==124);
      /* (127) if_block ::= if_block elif_header stmt */ yytestcase(yyruleno==127);
      /* (135) for_init_stmt_nonEmpty ::= vdef_stmt */ yytestcase(yyruleno==135);
      /* (136) for_init_stmt_nonEmpty ::= vdefAssign_stmt */ yytestcase(yyruleno==136);
      /* (137) for_init_stmt_nonEmpty ::= cdef_stmt */ yytestcase(yyruleno==137);
      /* (138) for_init_stmt_nonEmpty ::= assign_stmt */ yytestcase(yyruleno==138);
      /* (139) for_init_stmt_nonEmpty ::= for_init_stmt_nonEmpty COMMA for_init_stmt_nonEmpty */ yytestcase(yyruleno==139);
      /* (140) for_init_stmt ::= for_init_stmt_nonEmpty */ yytestcase(yyruleno==140);
      /* (141) for_init_stmt ::= */ yytestcase(yyruleno==141);
      /* (142) for_action_stmt_nonEmpty ::= assign_stmt */ yytestcase(yyruleno==142);
      /* (143) for_action_stmt_nonEmpty ::= for_action_stmt_nonEmpty COMMA for_action_stmt_nonEmpty */ yytestcase(yyruleno==143);
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
#line 2299 "parser\\epparser.c"
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
#line 746 "parser\\epparser.lemon"


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
#line 2553 "parser\\epparser.c"
