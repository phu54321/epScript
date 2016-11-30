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
#define YYNRULE 153
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
 /*     0 */   199,  181,   18,  148,    7,    3,   71,  195,  193,  183,
 /*    10 */   258,  105,  294,  292,  198,    2,  303,  284,  301,  194,
 /*    20 */   192,  136,  276,  275,  274,  273,  272,  187,  186,   28,
 /*    30 */    29,   98,  225,  185,   28,   29,  111,  132,  150,    8,
 /*    40 */    38,  178,  300,   98,  147,    6,   10,  204,  111,  132,
 /*    50 */    22,   13,    5,   76,    4,   75,   74,  199,  252,  278,
 /*    60 */   298,  224,  202,  241,  195,  193,  295,  191,  202,  240,
 /*    70 */   292,  198,    2,   82,  284,  177,  194,  192,  136,  276,
 /*    80 */   275,  274,  273,  272,  187,  186,   28,   29,   98,  225,
 /*    90 */   185,   28,   29,  111,  132,  150,    8,   38,  296,  202,
 /*   100 */    98,  147,    6,   10,  299,  111,  132,   22,   13,    5,
 /*   110 */    76,    4,   75,   74,  199,  238,   36,  202,  131,   14,
 /*   120 */   235,  195,  193,   32,   28,   29,  237,  292,  198,    2,
 /*   130 */   297,  284,   72,  194,  192,  136,  276,  275,  274,  273,
 /*   140 */   272,  187,  186,   35,  202,   98,  181,  293,  226,  223,
 /*   150 */   111,  132,  150,    8,   38,  176,  105,  157,  147,    6,
 /*   160 */    10,   33,   34,  181,   22,   13,    5,   76,    4,   75,
 /*   170 */    74,  199,  176,  105,  215,   37,  291,  185,  195,  193,
 /*   180 */   459,   12,   81,  234,  292,  198,    2,  106,  284,  262,
 /*   190 */   194,  192,  136,  276,  275,  274,  273,  272,  187,  186,
 /*   200 */   190,   80,   98,  181,  185,  219,  282,  111,  132,  150,
 /*   210 */     8,   38,  153,  105,   83,  147,    6,   10,  122,  185,
 /*   220 */   185,   22,   13,    5,   76,    4,   75,   74,  199,  106,
 /*   230 */    83,  182,  155,  281,  251,  195,  193,  280,  279,  189,
 /*   240 */   221,  292,  198,    2,  188,  284,  271,  194,  192,  136,
 /*   250 */   276,  275,  274,  273,  272,  187,  186,  277,  270,   98,
 /*   260 */   181,  185,  265,   19,  111,  132,  150,    8,   38,  152,
 /*   270 */   105,   83,  147,    6,   10,  160,  185,  185,   22,   13,
 /*   280 */     5,   76,    4,   75,   74,  199,  106,   83,  182,  156,
 /*   290 */   191,  250,  195,  193,   31,  180,   79,  218,  292,  198,
 /*   300 */     2,  260,  284,  259,  194,  192,  136,  276,  275,  274,
 /*   310 */   273,  272,  187,  186,   37,  257,   98,  185,  185,   30,
 /*   320 */    17,  111,  132,  150,    8,   38,  172,   98,   86,  147,
 /*   330 */     6,   10,  243,  185,  185,   22,   13,    5,   76,    4,
 /*   340 */    75,   74,  199,  106,   83,  182,  161,  171,  249,  195,
 /*   350 */   193,  169,  168,  256,  211,  292,  198,    2,  166,  284,
 /*   360 */   255,  194,  192,  136,  276,  275,  274,  273,  272,  187,
 /*   370 */   186,  165,  162,   98,  181,  185,  163,   29,  111,  132,
 /*   380 */   150,    8,   38,  151,  105,   83,  147,    6,   10,  121,
 /*   390 */   185,  254,   22,   13,    5,   76,    4,   75,   74,  139,
 /*   400 */   106,  181,  182,  141,  253,   15,  195,  193,  248,  245,
 /*   410 */   129,  105,  209,  197,    2,  246,  284,    1,  194,  192,
 /*   420 */   136,  276,  275,  274,  273,  272,  187,  186,  244,  109,
 /*   430 */    98,  185,  185,   25,   11,  111,  132,  150,    8,   38,
 /*   440 */   239,   85,   83,  147,    6,   10,  120,  185,  185,   22,
 /*   450 */    13,    5,   76,    4,   75,   74,  268,  106,   83,  182,
 /*   460 */   158,   24,  119,  195,  193,   23,  227,  233,  220,  269,
 /*   470 */   196,    2,  286,  284,   16,  194,  192,  136,  276,  275,
 /*   480 */   274,  273,  272,  187,  186,  140,  214,   98,  185,  185,
 /*   490 */   210,  203,  111,  132,  150,    8,   38,  298,  117,   83,
 /*   500 */   147,    6,   10,  118,  287,  185,   22,   13,    5,   76,
 /*   510 */     4,   75,   74,   59,   58,  116,   66,   67,   65,   57,
 /*   520 */   267,  107,  283,  185,  288,  285,   70,   18,  290,  289,
 /*   530 */    21,   71,  266,  128,  183,  179,  175,  173,  170,  167,
 /*   540 */   164,   78,   77,   64,   63,   69,   68,   66,   67,   65,
 /*   550 */   135,  134,  133,  242,  142,  236,  146,  143,   18,  217,
 /*   560 */   216,   20,   71,  142,  305,  183,  185,  185,  213,  130,
 /*   570 */   212,  149,   59,   58,  185,  138,  127,  126,   57,  267,
 /*   580 */   107,  283,  137,  185,  115,   70,  460,  290,  288,   21,
 /*   590 */   460,  266,  205,  114,  201,  175,  173,  170,  167,  164,
 /*   600 */    78,   77,  460,  185,   69,   68,   66,   67,   65,  460,
 /*   610 */    73,   77,  242,  113,  236,  146,  143,   18,  217,  216,
 /*   620 */    20,   71,  142,  185,  183,  185,  460,  460,  460,  460,
 /*   630 */   460,   59,   58,  110,  460,  112,  460,   57,  267,  107,
 /*   640 */   283,  460,  460,  460,   70,  460,  290,  460,   21,  460,
 /*   650 */   266,  460,  460,  460,  175,  173,  170,  167,  164,   78,
 /*   660 */    77,  304,  208,  302,  207,  206,  460,  200,    9,  460,
 /*   670 */   185,  242,  460,  236,  146,  143,  460,  217,  216,   20,
 /*   680 */   125,  142,   56,   54,   53,   52,   51,   55,   61,   60,
 /*   690 */    62,   64,   63,   69,   68,   66,   67,   65,   27,  185,
 /*   700 */   460,  460,  460,  460,  185,  185,   18,  460,  460,  124,
 /*   710 */    71,   59,   58,  183,  123,  104,  185,   57,  267,  184,
 /*   720 */   460,  460,  185,  185,   70,  460,  103,  460,   21,  185,
 /*   730 */   174,  185,  102,  101,  175,  173,  170,  167,  164,  100,
 /*   740 */   460,   99,   26,  460,  460,  460,  460,  185,  185,  185,
 /*   750 */   460,  460,  460,  460,  185,   59,   58,   84,   97,   96,
 /*   760 */   159,   57,  267,  184,   95,  460,  185,  460,   70,  460,
 /*   770 */   460,  460,   21,  185,  174,  185,   94,  185,  175,  173,
 /*   780 */   170,  167,  164,   93,  460,   92,  185,   91,  185,  460,
 /*   790 */   460,  460,  460,   59,   58,  185,   90,  460,   89,   57,
 /*   800 */   267,  184,  460,  185,  159,   88,   70,  247,  460,  460,
 /*   810 */    21,  460,  266,   87,  263,  460,  175,  173,  170,  167,
 /*   820 */   164,  460,  460,   59,   58,  460,  460,  460,  460,   57,
 /*   830 */   267,  107,  460,  460,  460,  460,   70,  460,  460,  460,
 /*   840 */    21,  460,  266,  460,  460,  460,  175,  173,  170,  167,
 /*   850 */   164,   78,   77,  460,   61,   60,   62,   64,   63,   69,
 /*   860 */    68,   66,   67,   65,  460,  460,  460,  460,  460,  460,
 /*   870 */   460,  460,   18,  460,  460,  460,   71,  264,  460,  183,
 /*   880 */   460,  460,  460,  460,  460,  460,   61,   60,   62,   64,
 /*   890 */    63,   69,   68,   66,   67,   65,  460,  460,  460,  460,
 /*   900 */   460,  460,  460,  460,   18,  261,  460,  460,   71,  460,
 /*   910 */   460,  183,  460,  460,  460,  460,  460,  460,   61,   60,
 /*   920 */    62,   64,   63,   69,   68,   66,   67,   65,  460,  460,
 /*   930 */   460,  460,  460,  460,  460,  460,   18,  460,   59,   58,
 /*   940 */    71,  108,  460,  183,   57,  267,  184,  460,  460,  460,
 /*   950 */   460,   70,  460,  460,  460,   21,  460,  266,  460,  263,
 /*   960 */   460,  175,  173,  170,  167,  164,  460,  460,  460,  460,
 /*   970 */    59,   58,  460,  460,  460,  460,   57,  267,  107,  460,
 /*   980 */   460,  460,  460,   70,  222,  460,  460,   21,  460,  266,
 /*   990 */   460,  460,  460,  175,  173,  170,  167,  164,  356,  356,
 /*  1000 */   356,  356,  356,  356,  356,  356,  356,  356,  460,  460,
 /*  1010 */   460,  460,  460,  460,  460,  460,   19,  460,  460,  460,
 /*  1020 */   356,  460,  460,  356,  460,  460,  460,  460,  460,  460,
 /*  1030 */    61,   60,   62,   64,   63,   69,   68,   66,   67,   65,
 /*  1040 */   460,  460,  460,  460,  460,  460,  460,  460,   18,  460,
 /*  1050 */   460,  460,   71,  460,  460,  183,  460,  460,  460,  460,
 /*  1060 */   460,  460,   61,   60,   62,   64,   63,   69,   68,   66,
 /*  1070 */    67,   65,  460,  460,  460,  460,  460,  460,  460,  460,
 /*  1080 */    18,  460,   59,   58,   50,  460,  460,  154,   57,  267,
 /*  1090 */   184,  460,  460,  460,  460,   70,  460,  460,  460,   21,
 /*  1100 */   460,  266,  460,  460,  460,  175,  173,  170,  167,  164,
 /*  1110 */   460,  460,  460,  460,   59,   58,  460,  460,  460,  460,
 /*  1120 */    57,  267,  107,  402,  402,  460,  460,   70,  460,  460,
 /*  1130 */   460,   21,  460,  266,  460,  401,  401,  175,  173,  170,
 /*  1140 */   167,  164,   60,   62,   64,   63,   69,   68,   66,   67,
 /*  1150 */    65,  460,  460,  460,  460,  460,  460,  460,  460,   18,
 /*  1160 */   460,  460,  460,   71,  460,  460,  183,  460,  460,  460,
 /*  1170 */   402,  402,  402,  402,  402,  402,  402,  402,  402,  402,
 /*  1180 */    49,  460,  401,  401,  401,  401,  401,  401,  401,  401,
 /*  1190 */   401,  401,   62,   64,   63,   69,   68,   66,   67,   65,
 /*  1200 */   460,  460,  460,  460,  460,  460,  460,  460,   18,  460,
 /*  1210 */   460,  460,   71,  460,  460,  183,  460,  460,  460,  460,
 /*  1220 */   460,  460,  460,  460,  460,  232,  230,   48,   47,   46,
 /*  1230 */    45,   44,   43,   42,   41,   40,   39,  231,  229,  185,
 /*  1240 */   460,  460,  460,  460,  460,  460,  460,  232,  230,   98,
 /*  1250 */   460,  460,  460,  460,  111,  132,  460,  460,  460,  231,
 /*  1260 */   229,  185,  460,  460,  460,  145,  144,  460,  460,  460,
 /*  1270 */   460,   98,  460,  460,  460,  460,  111,  132,  460,  460,
 /*  1280 */   460,  460,  460,  460,  460,  460,  460,  228,
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
 /*    90 */    90,    3,    4,  105,  106,  107,  108,  109,   32,    2,
 /*   100 */   100,  113,  114,  115,   26,  105,  106,  119,  120,  121,
 /*   110 */   122,  123,  124,  125,   69,   32,    1,    2,  118,    2,
 /*   120 */    32,   76,   77,   63,    3,    4,   81,   82,   83,   84,
 /*   130 */    26,   86,   31,   88,   89,   90,   91,   92,   93,   94,
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
 /*   490 */    34,   78,  105,  106,  107,  108,  109,   26,  100,  100,
 /*   500 */   113,  114,  115,  104,   85,   90,  119,  120,  121,  122,
 /*   510 */   123,  124,  125,   18,   19,  100,   20,   21,   22,   24,
 /*   520 */    25,   26,   27,   90,   34,   85,   31,   31,   33,   34,
 /*   530 */    35,   35,   37,  100,   38,   25,   41,   42,   43,   44,
 /*   540 */    45,   46,   47,   16,   17,   18,   19,   20,   21,   22,
 /*   550 */    98,   78,   78,   58,   68,   60,   61,   62,   31,   64,
 /*   560 */    65,   66,   35,   68,    0,   38,   90,   90,  124,   78,
 /*   570 */   124,   59,   18,   19,   90,   78,  100,  100,   24,   25,
 /*   580 */    26,   27,   78,   90,  100,   31,  126,   33,   34,   35,
 /*   590 */   126,   37,   28,  100,   30,   41,   42,   43,   44,   45,
 /*   600 */    46,   47,  126,   90,   18,   19,   20,   21,   22,  126,
 /*   610 */    46,   47,   58,  100,   60,   61,   62,   31,   64,   65,
 /*   620 */    66,   35,   68,   90,   38,   90,  126,  126,  126,  126,
 /*   630 */   126,   18,   19,  100,  126,  100,  126,   24,   25,   26,
 /*   640 */    27,  126,  126,  126,   31,  126,   33,  126,   35,  126,
 /*   650 */    37,  126,  126,  126,   41,   42,   43,   44,   45,   46,
 /*   660 */    47,   73,   74,   75,   76,   77,  126,   79,   80,  126,
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
#define YY_SHIFT_COUNT (208)
#define YY_SHIFT_MIN   (-29)
#define YY_SHIFT_MAX   (1179)
static const short yy_shift_ofst[] = {
 /*     0 */   -30,  554,  495,  613,  613,  613,  613,  613,  613,  613,
 /*    10 */   805,  805,  564,  952, 1096,  775,  920,  920,  920,  920,
 /*    20 */  1064, 1064,  693,  693,  693,  693,  737,  737,  693,  693,
 /*    30 */   693,  920, 1064, 1064, 1096, 1064, 1064, 1064,  512, 1064,
 /*    40 */  1064, 1064, 1064, 1064, 1064, 1064, 1064, 1064, 1064, 1064,
 /*    50 */  1064, 1064, 1064, 1064, 1064, 1064, 1064, 1064, 1064, 1064,
 /*    60 */  1064, 1064, 1064, 1064, 1064, 1064, 1064, 1064, 1064, 1064,
 /*    70 */  1064, 1064,   34,  471,  486,  486,  471,  471,  471,  510,
 /*    80 */   490,  490,  471,  675,  905,  873,  841, 1017, 1017, 1017,
 /*    90 */  1017, 1017, 1017, 1017, 1017, 1017, 1017, 1017, 1049, 1017,
 /*   100 */  1017, 1017, 1017, 1017, 1017, 1017, 1017,  985, 1134, 1122,
 /*   110 */  1128, 1179, 1177,  527,  586,  586,  496,  496,  121,   88,
 /*   120 */    83,   31,   26,  -29,  -29,  -29,  -29,  -29,  -29,  173,
 /*   130 */    60,  117,  160,  142,  115,   39,   32,   66,   97,  456,
 /*   140 */   459,  453,  443,  437,  439,  432,  436,  434,  430,  382,
 /*   150 */   402,  312,  312,  312,  403,  396,  377,  379,  376,  374,
 /*   160 */   373,  372,  359,  333,  345,  328,  332,  327,  321,  313,
 /*   170 */   320,  283,  308,  295,  289,  288,  312,  267,  276,  208,
 /*   180 */   261,  260,  292,  236,  232,  255,  231,  219,  221,  208,
 /*   190 */   214,  165,  211,  210,  206,  179,  174,  155,  149,  120,
 /*   200 */   101,  104,   78,   97,   44,   21,   15,   -9,  -11,
};
#define YY_REDUCE_USE_DFLT (-108)
#define YY_REDUCE_COUNT (82)
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
 /*    70 */   341,  228,  504,  497,  446,  444,  491,  474,  473,  452,
 /*    80 */   440,  419,  413,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   306,  458,  458,  458,  458,  458,  458,  458,  458,  458,
 /*    10 */   436,  458,  458,  458,  458,  458,  362,  362,  362,  362,
 /*    20 */   352,  352,  458,  458,  458,  458,  458,  458,  458,  458,
 /*    30 */   458,  458,  458,  458,  458,  458,  458,  458,  424,  458,
 /*    40 */   458,  458,  458,  458,  458,  458,  458,  458,  458,  458,
 /*    50 */   458,  458,  458,  458,  458,  458,  458,  458,  458,  458,
 /*    60 */   458,  458,  458,  458,  458,  458,  458,  458,  458,  458,
 /*    70 */   458,  458,  458,  458,  457,  456,  458,  458,  458,  458,
 /*    80 */   458,  458,  458,  458,  458,  458,  458,  416,  415,  414,
 /*    90 */   413,  412,  411,  410,  409,  408,  407,  405,  458,  392,
 /*   100 */   391,  390,  389,  388,  387,  350,  359,  400,  358,  357,
 /*   110 */   382,  403,  383,  381,  380,  379,  375,  374,  458,  458,
 /*   120 */   458,  458,  458,  386,  385,  384,  378,  377,  376,  458,
 /*   130 */   458,  458,  458,  458,  397,  458,  366,  458,  397,  458,
 /*   140 */   458,  458,  458,  458,  458,  435,  458,  458,  458,  423,
 /*   150 */   458,  406,  399,  398,  458,  458,  458,  458,  458,  458,
 /*   160 */   394,  458,  458,  458,  458,  458,  458,  458,  458,  458,
 /*   170 */   458,  458,  458,  458,  355,  458,  353,  458,  458,  344,
 /*   180 */   458,  366,  363,  458,  356,  366,  458,  458,  458,  458,
 /*   190 */   458,  458,  458,  458,  458,  458,  458,  458,  458,  458,
 /*   200 */   458,  458,  458,  312,  458,  458,  458,  458,  458,  341,
 /*   210 */   326,  425,  455,  454,  453,  449,  448,  447,  446,  445,
 /*   220 */   444,  443,  442,  441,  438,  437,  440,  439,  434,  433,
 /*   230 */   432,  431,  430,  429,  428,  427,  426,  422,  421,  420,
 /*   240 */   419,  418,  417,  404,  364,  365,  368,  452,  450,  396,
 /*   250 */   395,  393,  369,  451,  373,  372,  371,  370,  351,  348,
 /*   260 */   345,  367,  361,  360,  358,  357,  355,  354,  343,  342,
 /*   270 */   340,  339,  338,  337,  336,  335,  334,  349,  333,  332,
 /*   280 */   331,  330,  329,  328,  327,  325,  324,  323,  321,  322,
 /*   290 */   320,  319,  318,  317,  316,  315,  314,  313,  346,  347,
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
  "FROM",          "IMPORT",        "FUNCTION",      "LPAREN",      
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
  "vdef_stmt",     "cdef_stmt",     "nameList_nonEmpty",  "function_start",
  "function_header",  "stmt",          "bodyStmt",      "return_stmt", 
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
 /*   7 */ "import_chunk ::= FROM NAME IMPORT nameList_nonEmpty",
 /*   8 */ "function_start ::= FUNCTION NAME",
 /*   9 */ "function_header ::= function_start LPAREN nameList_nonEmpty RPAREN",
 /*  10 */ "function_header ::= function_start LPAREN RPAREN",
 /*  11 */ "fdef_chunk ::= function_header stmt",
 /*  12 */ "stmt ::= error SEMICOLON",
 /*  13 */ "stmt ::= bodyStmt",
 /*  14 */ "stmt ::= return_stmt SEMICOLON",
 /*  15 */ "lbracket ::= LBRACKET",
 /*  16 */ "rbracket ::= RBRACKET",
 /*  17 */ "blockStmt ::= lbracket RBRACKET",
 /*  18 */ "blockStmt ::= lbracket return_stmt SEMICOLON rbracket",
 /*  19 */ "blockStmt ::= lbracket bodyStmtList rbracket",
 /*  20 */ "blockStmt ::= lbracket bodyStmtList return_stmt SEMICOLON rbracket",
 /*  21 */ "blockStmt ::= lbracket error RBRACKET",
 /*  22 */ "bodyStmt ::= blockStmt",
 /*  23 */ "bodyStmt ::= SEMICOLON",
 /*  24 */ "bodyStmt ::= vdef_stmt SEMICOLON",
 /*  25 */ "bodyStmt ::= vdefAssign_stmt SEMICOLON",
 /*  26 */ "bodyStmt ::= cdef_stmt SEMICOLON",
 /*  27 */ "bodyStmt ::= assign_stmt SEMICOLON",
 /*  28 */ "bodyStmt ::= funcexpr SEMICOLON",
 /*  29 */ "bodyStmt ::= actionStmt",
 /*  30 */ "bodyStmt ::= if_stmt",
 /*  31 */ "bodyStmt ::= while_stmt",
 /*  32 */ "bodyStmt ::= for_stmt",
 /*  33 */ "bodyStmt ::= foreach_stmt",
 /*  34 */ "bodyStmt ::= continue_stmt SEMICOLON",
 /*  35 */ "bodyStmt ::= break_stmt SEMICOLON",
 /*  36 */ "bodyStmtList ::= bodyStmt",
 /*  37 */ "bodyStmtList ::= bodyStmtList bodyStmt",
 /*  38 */ "bodyStmtList ::= bodyStmtList error",
 /*  39 */ "numList_nonEmpty ::= NUMBER",
 /*  40 */ "numList_nonEmpty ::= numList_nonEmpty COMMA NUMBER",
 /*  41 */ "nameList_nonEmpty ::= NAME",
 /*  42 */ "nameList_nonEmpty ::= nameList_nonEmpty COMMA NAME",
 /*  43 */ "exprList_nonEmpty ::= funcexpr LSQBRACKET LSQBRACKET numList_nonEmpty RSQBRACKET RSQBRACKET",
 /*  44 */ "expr ::= funcexpr LSQBRACKET LSQBRACKET NUMBER RSQBRACKET RSQBRACKET",
 /*  45 */ "exprList_nonEmpty ::= expr",
 /*  46 */ "exprList_nonEmpty ::= exprList_nonEmpty COMMA exprList_nonEmpty",
 /*  47 */ "exprList ::=",
 /*  48 */ "exprList ::= exprList_nonEmpty",
 /*  49 */ "expr ::= NUMBER",
 /*  50 */ "expr ::= KILLS",
 /*  51 */ "expr ::= NAME",
 /*  52 */ "expr ::= expr PERIOD NAME",
 /*  53 */ "expr ::= expr LSQBRACKET expr RSQBRACKET",
 /*  54 */ "fArgs_nonEmpty ::= expr",
 /*  55 */ "fArgs_nonEmpty ::= STRING",
 /*  56 */ "fArgs_nonEmpty ::= fArgs_nonEmpty COMMA fArgs_nonEmpty",
 /*  57 */ "fArgs ::=",
 /*  58 */ "fArgs ::= fArgs_nonEmpty",
 /*  59 */ "funcexpr ::= NAME LPAREN fArgs RPAREN",
 /*  60 */ "funcexpr ::= expr LPAREN fArgs RPAREN",
 /*  61 */ "expr ::= funcexpr",
 /*  62 */ "expr ::= LPAREN expr RPAREN",
 /*  63 */ "expr ::= LSQBRACKET exprList RSQBRACKET",
 /*  64 */ "expr ::= L2V LPAREN lexpr RPAREN",
 /*  65 */ "expr ::= MAPSTRING LPAREN STRING RPAREN",
 /*  66 */ "expr ::= UNIT LPAREN STRING RPAREN",
 /*  67 */ "expr ::= SWITCH LPAREN STRING RPAREN",
 /*  68 */ "expr ::= LOCATION LPAREN STRING RPAREN",
 /*  69 */ "expr ::= expr PLUS expr",
 /*  70 */ "expr ::= expr MINUS expr",
 /*  71 */ "expr ::= expr MULTIPLY expr",
 /*  72 */ "expr ::= expr DIVIDE expr",
 /*  73 */ "expr ::= expr MOD expr",
 /*  74 */ "expr ::= expr LSHIFT expr",
 /*  75 */ "expr ::= expr RSHIFT expr",
 /*  76 */ "expr ::= expr BITAND expr",
 /*  77 */ "expr ::= expr BITOR expr",
 /*  78 */ "expr ::= expr BITXOR expr",
 /*  79 */ "expr ::= PLUS expr",
 /*  80 */ "expr ::= MINUS expr",
 /*  81 */ "expr ::= BITNOT expr",
 /*  82 */ "lexpr ::= expr EQ expr",
 /*  83 */ "lexpr ::= expr NE expr",
 /*  84 */ "lexpr ::= expr LE expr",
 /*  85 */ "lexpr ::= expr LT expr",
 /*  86 */ "lexpr ::= expr GE expr",
 /*  87 */ "lexpr ::= expr GT expr",
 /*  88 */ "lexpr ::= lexpr LAND lexpr",
 /*  89 */ "lexpr ::= lexpr LOR lexpr",
 /*  90 */ "lexpr ::= LNOT lexpr",
 /*  91 */ "lexpr ::= LNOT LNOT lexpr",
 /*  92 */ "vdef_stmt ::= VAR nameList_nonEmpty",
 /*  93 */ "vdefAssign_stmt ::= VAR nameList_nonEmpty ASSIGN exprList_nonEmpty",
 /*  94 */ "cdef_stmt ::= CONST nameList_nonEmpty ASSIGN exprList_nonEmpty",
 /*  95 */ "lvalue ::= NAME",
 /*  96 */ "lvalue ::= expr LSQBRACKET expr RSQBRACKET",
 /*  97 */ "lvalue ::= expr PERIOD NAME",
 /*  98 */ "lvalueList_nonEmpty ::= lvalue",
 /*  99 */ "lvalueList_nonEmpty ::= lvalueList_nonEmpty COMMA lvalue",
 /* 100 */ "assign_stmt ::= lvalue ASSIGN expr",
 /* 101 */ "assign_stmt ::= lvalueList_nonEmpty ASSIGN exprList_nonEmpty",
 /* 102 */ "assign_stmt ::= lvalue IADD expr",
 /* 103 */ "assign_stmt ::= lvalue ISUB expr",
 /* 104 */ "assign_stmt ::= lvalue IMUL expr",
 /* 105 */ "assign_stmt ::= lvalue IDIV expr",
 /* 106 */ "assign_stmt ::= lvalue IMOD expr",
 /* 107 */ "assign_stmt ::= lvalue ILSH expr",
 /* 108 */ "assign_stmt ::= lvalue IRSH expr",
 /* 109 */ "assign_stmt ::= lvalue IBND expr",
 /* 110 */ "assign_stmt ::= lvalue IBOR expr",
 /* 111 */ "assign_stmt ::= lvalue IBXR expr",
 /* 112 */ "if_start ::= IF",
 /* 113 */ "if_header ::= if_start LPAREN lexpr RPAREN",
 /* 114 */ "if_block ::= if_header stmt",
 /* 115 */ "elif_start ::= ELSE IF",
 /* 116 */ "elif_header ::= elif_start LPAREN lexpr RPAREN",
 /* 117 */ "if_block ::= if_block elif_header stmt",
 /* 118 */ "else_header ::= ELSE",
 /* 119 */ "if_stmt ::= if_block",
 /* 120 */ "if_stmt ::= if_block else_header stmt",
 /* 121 */ "while_start ::= WHILE",
 /* 122 */ "while_header ::= while_start LPAREN lexpr RPAREN",
 /* 123 */ "while_stmt ::= while_header stmt",
 /* 124 */ "for_opener ::= FOR LPAREN",
 /* 125 */ "for_init_stmt_nonEmpty ::= vdef_stmt",
 /* 126 */ "for_init_stmt_nonEmpty ::= vdefAssign_stmt",
 /* 127 */ "for_init_stmt_nonEmpty ::= cdef_stmt",
 /* 128 */ "for_init_stmt_nonEmpty ::= assign_stmt",
 /* 129 */ "for_init_stmt_nonEmpty ::= for_init_stmt_nonEmpty COMMA for_init_stmt_nonEmpty",
 /* 130 */ "for_init_stmt ::= for_init_stmt_nonEmpty",
 /* 131 */ "for_init_stmt ::=",
 /* 132 */ "for_action_stmt_nonEmpty ::= assign_stmt",
 /* 133 */ "for_action_stmt_nonEmpty ::= for_action_stmt_nonEmpty COMMA for_action_stmt_nonEmpty",
 /* 134 */ "for_header1 ::= for_opener for_init_stmt SEMICOLON",
 /* 135 */ "for_header2 ::= for_header1 lexpr SEMICOLON",
 /* 136 */ "for_header ::= for_header2 for_action_stmt_nonEmpty RPAREN",
 /* 137 */ "for_header ::= for_header2 RPAREN",
 /* 138 */ "for_stmt ::= for_header stmt",
 /* 139 */ "foreach_opener ::= FOREACH LPAREN",
 /* 140 */ "foreach_header ::= foreach_opener nameList_nonEmpty COLON exprList_nonEmpty RPAREN",
 /* 141 */ "foreach_stmt ::= foreach_header stmt",
 /* 142 */ "continue_stmt ::= CONTINUE",
 /* 143 */ "break_stmt ::= BREAK",
 /* 144 */ "return_stmt ::= RETURN exprList",
 /* 145 */ "lexpr ::= CONDITIONNAME LPAREN fArgs RPAREN",
 /* 146 */ "lexpr ::= KILLS LPAREN fArgs RPAREN",
 /* 147 */ "lexpr ::= CONDITIONNAME LPAREN RPAREN",
 /* 148 */ "action ::= ACTIONNAME LPAREN fArgs RPAREN SEMICOLON",
 /* 149 */ "actions ::= action action",
 /* 150 */ "actions ::= actions action",
 /* 151 */ "actionStmt ::= action",
 /* 152 */ "actionStmt ::= actions",
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
#line 870 "parser\\epparser.c"
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
  { 79, 2 },
  { 80, 4 },
  { 80, 3 },
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
  { 78, 1 },
  { 78, 3 },
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
      case 7: /* import_chunk ::= FROM NAME IMPORT nameList_nonEmpty */
#line 66 "parser\\epparser.lemon"
{
    commaListIter(yymsp[0].minor.yy0->data, [&](std::string varname) {
        funcNamePreprocess(varname);
        if(!ps->closure.defFunction(varname)) {
            throw_error(8118, ("Importing already-declared function " + varname));
        }
        else ps->gen << "from " << yymsp[-2].minor.yy0->data << " import " << varname << std::endl;
    });
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 1327 "parser\\epparser.c"
        break;
      case 8: /* function_start ::= FUNCTION NAME */
#line 78 "parser\\epparser.lemon"
{
    // Preprocess yymsp[0].minor.yy0
    funcNamePreprocess(yymsp[0].minor.yy0->data);
    if(!ps->closure.defFunction(yymsp[0].minor.yy0->data)) {
        throw_error(4495, "Duplicate function " + yymsp[0].minor.yy0->data);
    }
    ps->closure.pushScope();
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1340 "parser\\epparser.c"
        break;
      case 9: /* function_header ::= function_start LPAREN nameList_nonEmpty RPAREN */
#line 88 "parser\\epparser.lemon"
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
#line 1359 "parser\\epparser.c"
        break;
      case 10: /* function_header ::= function_start LPAREN RPAREN */
#line 104 "parser\\epparser.lemon"
{
    ps->gen << "@EUDFunc" << std::endl;
    ps->gen << "def " << yymsp[-2].minor.yy0->data << "():" << std::endl;
    ps->gen.indent();
    tmpIndex = 1;
    delete yymsp[-2].minor.yy0;
}
#line 1370 "parser\\epparser.c"
        break;
      case 11: /* fdef_chunk ::= function_header stmt */
      case 141: /* foreach_stmt ::= foreach_header stmt */ yytestcase(yyruleno==141);
#line 112 "parser\\epparser.lemon"
{
    ps->gen.unindent(true);
    ps->closure.popScope();
}
#line 1379 "parser\\epparser.c"
        break;
      case 12: /* stmt ::= error SEMICOLON */
#line 119 "parser\\epparser.lemon"
{ throw_error(6974, "Error while parsing statement"); }
#line 1384 "parser\\epparser.c"
        break;
      case 15: /* lbracket ::= LBRACKET */
#line 125 "parser\\epparser.lemon"
{ ps->closure.pushScope(); }
#line 1389 "parser\\epparser.c"
        break;
      case 16: /* rbracket ::= RBRACKET */
#line 126 "parser\\epparser.lemon"
{ ps->closure.popScope(); }
#line 1394 "parser\\epparser.c"
        break;
      case 17: /* blockStmt ::= lbracket RBRACKET */
#line 128 "parser\\epparser.lemon"
{
    ps->gen << "pass" << std::endl;
    ps->closure.popScope();
}
#line 1402 "parser\\epparser.c"
        break;
      case 21: /* blockStmt ::= lbracket error RBRACKET */
#line 135 "parser\\epparser.lemon"
{
    throw_error(6298, "Block not terminated properly.");
    ps->closure.popScope();
}
#line 1410 "parser\\epparser.c"
        break;
      case 28: /* bodyStmt ::= funcexpr SEMICOLON */
#line 146 "parser\\epparser.lemon"
{ ps->gen << yymsp[-1].minor.yy0->data << std::endl; }
#line 1415 "parser\\epparser.c"
        break;
      case 38: /* bodyStmtList ::= bodyStmtList error */
#line 158 "parser\\epparser.lemon"
{
    throw_error(8510, "Incomplete statement");
}
#line 1422 "parser\\epparser.c"
        break;
      case 39: /* numList_nonEmpty ::= NUMBER */
      case 41: /* nameList_nonEmpty ::= NAME */ yytestcase(yyruleno==41);
      case 45: /* exprList_nonEmpty ::= expr */ yytestcase(yyruleno==45);
      case 48: /* exprList ::= exprList_nonEmpty */ yytestcase(yyruleno==48);
      case 49: /* expr ::= NUMBER */ yytestcase(yyruleno==49);
      case 54: /* fArgs_nonEmpty ::= expr */ yytestcase(yyruleno==54);
      case 55: /* fArgs_nonEmpty ::= STRING */ yytestcase(yyruleno==55);
      case 58: /* fArgs ::= fArgs_nonEmpty */ yytestcase(yyruleno==58);
      case 61: /* expr ::= funcexpr */ yytestcase(yyruleno==61);
      case 91: /* lexpr ::= LNOT LNOT lexpr */ yytestcase(yyruleno==91);
      case 98: /* lvalueList_nonEmpty ::= lvalue */ yytestcase(yyruleno==98);
#line 164 "parser\\epparser.lemon"
{ yygotominor.yy0 = yymsp[0].minor.yy0; }
#line 1437 "parser\\epparser.c"
        break;
      case 40: /* numList_nonEmpty ::= numList_nonEmpty COMMA NUMBER */
      case 42: /* nameList_nonEmpty ::= nameList_nonEmpty COMMA NAME */ yytestcase(yyruleno==42);
      case 99: /* lvalueList_nonEmpty ::= lvalueList_nonEmpty COMMA lvalue */ yytestcase(yyruleno==99);
#line 165 "parser\\epparser.lemon"
{ yygotominor.yy0 = commaConcat(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1444 "parser\\epparser.c"
        break;
      case 43: /* exprList_nonEmpty ::= funcexpr LSQBRACKET LSQBRACKET numList_nonEmpty RSQBRACKET RSQBRACKET */
#line 169 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "_SRET(" + yymsp[-5].minor.yy0->data + ", [" + yymsp[-2].minor.yy0->data + "])";
    delete yymsp[-5].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1453 "parser\\epparser.c"
        break;
      case 44: /* expr ::= funcexpr LSQBRACKET LSQBRACKET NUMBER RSQBRACKET RSQBRACKET */
#line 176 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-5].minor.yy0->data + "[" + yymsp[-2].minor.yy0->data + "]";
    delete yymsp[-5].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1462 "parser\\epparser.c"
        break;
      case 46: /* exprList_nonEmpty ::= exprList_nonEmpty COMMA exprList_nonEmpty */
#line 184 "parser\\epparser.lemon"
{ yygotominor.yy0 = new Token((yymsp[-2].minor.yy0->data) + ", " + (yymsp[0].minor.yy0->data), yymsp[0].minor.yy0); delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1467 "parser\\epparser.c"
        break;
      case 47: /* exprList ::= */
      case 57: /* fArgs ::= */ yytestcase(yyruleno==57);
#line 186 "parser\\epparser.lemon"
{ yygotominor.yy0 = genEmpty(); }
#line 1473 "parser\\epparser.c"
        break;
      case 50: /* expr ::= KILLS */
#line 191 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = "4";
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1481 "parser\\epparser.c"
        break;
      case 51: /* expr ::= NAME */
#line 196 "parser\\epparser.lemon"
{
    checkIsRValue(yymsp[0].minor.yy0->data);
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1489 "parser\\epparser.c"
        break;
      case 52: /* expr ::= expr PERIOD NAME */
#line 201 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + "." + yymsp[0].minor.yy0->data;
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1498 "parser\\epparser.c"
        break;
      case 53: /* expr ::= expr LSQBRACKET expr RSQBRACKET */
#line 207 "parser\\epparser.lemon"
{
    yymsp[-3].minor.yy0->data = yymsp[-3].minor.yy0->data + "[" + yymsp[-1].minor.yy0->data + "]";
    delete yymsp[-1].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 1507 "parser\\epparser.c"
        break;
      case 56: /* fArgs_nonEmpty ::= fArgs_nonEmpty COMMA fArgs_nonEmpty */
#line 216 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data;
    yymsp[-2].minor.yy0->type = TOKEN_TEMP;
    yygotominor.yy0 = yymsp[-2].minor.yy0;
    delete yymsp[0].minor.yy0;
}
#line 1517 "parser\\epparser.c"
        break;
      case 59: /* funcexpr ::= NAME LPAREN fArgs RPAREN */
#line 226 "parser\\epparser.lemon"
{
    // Preprocess yymsp[-3].minor.yy0
    funcNamePreprocess(yymsp[-3].minor.yy0->data);
    checkIsFunction(yymsp[-3].minor.yy0->data);
    yymsp[-3].minor.yy0->data += "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 1528 "parser\\epparser.c"
        break;
      case 60: /* funcexpr ::= expr LPAREN fArgs RPAREN */
#line 234 "parser\\epparser.lemon"
{
    // Preprocess yymsp[-3].minor.yy0
    yymsp[-3].minor.yy0->data += "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 1537 "parser\\epparser.c"
        break;
      case 62: /* expr ::= LPAREN expr RPAREN */
#line 243 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1545 "parser\\epparser.c"
        break;
      case 63: /* expr ::= LSQBRACKET exprList RSQBRACKET */
#line 248 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "EUDArray(FlattenList([" + yymsp[-1].minor.yy0->data + "]))";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1553 "parser\\epparser.c"
        break;
      case 64: /* expr ::= L2V LPAREN lexpr RPAREN */
#line 253 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "_L2V(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = genTemp(yymsp[-1].minor.yy0);
}
#line 1561 "parser\\epparser.c"
        break;
      case 65: /* expr ::= MAPSTRING LPAREN STRING RPAREN */
#line 258 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetStringIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1569 "parser\\epparser.c"
        break;
      case 66: /* expr ::= UNIT LPAREN STRING RPAREN */
#line 263 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "EncodeUnit(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1577 "parser\\epparser.c"
        break;
      case 67: /* expr ::= SWITCH LPAREN STRING RPAREN */
#line 268 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "EncodeSwitch(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1585 "parser\\epparser.c"
        break;
      case 68: /* expr ::= LOCATION LPAREN STRING RPAREN */
#line 273 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetLocationIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1593 "parser\\epparser.c"
        break;
      case 69: /* expr ::= expr PLUS expr */
#line 279 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "+",  yymsp[0].minor.yy0); }
#line 1598 "parser\\epparser.c"
        break;
      case 70: /* expr ::= expr MINUS expr */
#line 280 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "-",  yymsp[0].minor.yy0); }
#line 1603 "parser\\epparser.c"
        break;
      case 71: /* expr ::= expr MULTIPLY expr */
#line 281 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "*",  yymsp[0].minor.yy0); }
#line 1608 "parser\\epparser.c"
        break;
      case 72: /* expr ::= expr DIVIDE expr */
#line 282 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "//", yymsp[0].minor.yy0); }
#line 1613 "parser\\epparser.c"
        break;
      case 73: /* expr ::= expr MOD expr */
#line 283 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "%",  yymsp[0].minor.yy0); }
#line 1618 "parser\\epparser.c"
        break;
      case 74: /* expr ::= expr LSHIFT expr */
#line 284 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<<", yymsp[0].minor.yy0); }
#line 1623 "parser\\epparser.c"
        break;
      case 75: /* expr ::= expr RSHIFT expr */
#line 285 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">>", yymsp[0].minor.yy0); }
#line 1628 "parser\\epparser.c"
        break;
      case 76: /* expr ::= expr BITAND expr */
#line 286 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "&",  yymsp[0].minor.yy0); }
#line 1633 "parser\\epparser.c"
        break;
      case 77: /* expr ::= expr BITOR expr */
#line 287 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "|",  yymsp[0].minor.yy0); }
#line 1638 "parser\\epparser.c"
        break;
      case 78: /* expr ::= expr BITXOR expr */
#line 288 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "^",  yymsp[0].minor.yy0); }
#line 1643 "parser\\epparser.c"
        break;
      case 79: /* expr ::= PLUS expr */
#line 291 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = +" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1648 "parser\\epparser.c"
        break;
      case 80: /* expr ::= MINUS expr */
#line 292 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = -" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1653 "parser\\epparser.c"
        break;
      case 81: /* expr ::= BITNOT expr */
#line 293 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = ~" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1658 "parser\\epparser.c"
        break;
      case 82: /* lexpr ::= expr EQ expr */
#line 297 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "==", yymsp[0].minor.yy0); }
#line 1663 "parser\\epparser.c"
        break;
      case 83: /* lexpr ::= expr NE expr */
#line 298 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "!=", yymsp[0].minor.yy0); }
#line 1668 "parser\\epparser.c"
        break;
      case 84: /* lexpr ::= expr LE expr */
#line 299 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<=", yymsp[0].minor.yy0); }
#line 1673 "parser\\epparser.c"
        break;
      case 85: /* lexpr ::= expr LT expr */
#line 300 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<",  yymsp[0].minor.yy0); }
#line 1678 "parser\\epparser.c"
        break;
      case 86: /* lexpr ::= expr GE expr */
#line 301 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">=", yymsp[0].minor.yy0); }
#line 1683 "parser\\epparser.c"
        break;
      case 87: /* lexpr ::= expr GT expr */
#line 302 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">" , yymsp[0].minor.yy0); }
#line 1688 "parser\\epparser.c"
        break;
      case 88: /* lexpr ::= lexpr LAND lexpr */
#line 304 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "[" + yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data + "]";
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1697 "parser\\epparser.c"
        break;
      case 89: /* lexpr ::= lexpr LOR lexpr */
#line 310 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "EUDOr([" + yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data + "])";
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1706 "parser\\epparser.c"
        break;
      case 90: /* lexpr ::= LNOT lexpr */
#line 316 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = "EUDNot([" + yymsp[0].minor.yy0->data + "])";
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0);
}
#line 1714 "parser\\epparser.c"
        break;
      case 92: /* vdef_stmt ::= VAR nameList_nonEmpty */
#line 326 "parser\\epparser.lemon"
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
#line 1738 "parser\\epparser.c"
        break;
      case 93: /* vdefAssign_stmt ::= VAR nameList_nonEmpty ASSIGN exprList_nonEmpty */
#line 347 "parser\\epparser.lemon"
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
#line 1763 "parser\\epparser.c"
        break;
      case 94: /* cdef_stmt ::= CONST nameList_nonEmpty ASSIGN exprList_nonEmpty */
#line 369 "parser\\epparser.lemon"
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
#line 1785 "parser\\epparser.c"
        break;
      case 95: /* lvalue ::= NAME */
#line 389 "parser\\epparser.lemon"
{
    checkIsVariable(yymsp[0].minor.yy0->data);
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1793 "parser\\epparser.c"
        break;
      case 96: /* lvalue ::= expr LSQBRACKET expr RSQBRACKET */
#line 394 "parser\\epparser.lemon"
{
    checkIsConstant(yymsp[-3].minor.yy0->data);
    yymsp[-1].minor.yy0->data = "_ARRW(" + yymsp[-3].minor.yy0->data + ", " + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
    delete yymsp[-3].minor.yy0;
}
#line 1803 "parser\\epparser.c"
        break;
      case 97: /* lvalue ::= expr PERIOD NAME */
#line 401 "parser\\epparser.lemon"
{
    checkIsConstant(yymsp[-2].minor.yy0->data);
    yymsp[0].minor.yy0->data = "_ATTW(" + yymsp[-2].minor.yy0->data + ", '" + yymsp[0].minor.yy0->data + "')";
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0);
    delete yymsp[-2].minor.yy0;
}
#line 1813 "parser\\epparser.c"
        break;
      case 100: /* assign_stmt ::= lvalue ASSIGN expr */
#line 410 "parser\\epparser.lemon"
{
    ps->gen << yymsp[-2].minor.yy0->data << " << (" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 1821 "parser\\epparser.c"
        break;
      case 101: /* assign_stmt ::= lvalueList_nonEmpty ASSIGN exprList_nonEmpty */
#line 415 "parser\\epparser.lemon"
{
    ps->gen << "_SV([" << yymsp[-2].minor.yy0->data << "], [" << yymsp[0].minor.yy0->data << "])" << std::endl;
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 1829 "parser\\epparser.c"
        break;
      case 102: /* assign_stmt ::= lvalue IADD expr */
#line 423 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__iadd__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1834 "parser\\epparser.c"
        break;
      case 103: /* assign_stmt ::= lvalue ISUB expr */
#line 424 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__isub__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1839 "parser\\epparser.c"
        break;
      case 104: /* assign_stmt ::= lvalue IMUL expr */
#line 425 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__imul__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1844 "parser\\epparser.c"
        break;
      case 105: /* assign_stmt ::= lvalue IDIV expr */
#line 426 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ifloordiv__("  << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1849 "parser\\epparser.c"
        break;
      case 106: /* assign_stmt ::= lvalue IMOD expr */
#line 427 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__imod__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1854 "parser\\epparser.c"
        break;
      case 107: /* assign_stmt ::= lvalue ILSH expr */
#line 428 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ilshift__("    << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1859 "parser\\epparser.c"
        break;
      case 108: /* assign_stmt ::= lvalue IRSH expr */
#line 429 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__irshift__("    << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1864 "parser\\epparser.c"
        break;
      case 109: /* assign_stmt ::= lvalue IBND expr */
#line 430 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__iand__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1869 "parser\\epparser.c"
        break;
      case 110: /* assign_stmt ::= lvalue IBOR expr */
#line 431 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ior__("        << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1874 "parser\\epparser.c"
        break;
      case 111: /* assign_stmt ::= lvalue IBXR expr */
#line 432 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ixor__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1879 "parser\\epparser.c"
        break;
      case 112: /* if_start ::= IF */
#line 435 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDIf()" << std::endl;
}
#line 1887 "parser\\epparser.c"
        break;
      case 113: /* if_header ::= if_start LPAREN lexpr RPAREN */
      case 122: /* while_header ::= while_start LPAREN lexpr RPAREN */ yytestcase(yyruleno==122);
#line 439 "parser\\epparser.lemon"
{
    ps->gen << "if " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data << "):" << std::endl;
    ps->gen.indent();
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1897 "parser\\epparser.c"
        break;
      case 115: /* elif_start ::= ELSE IF */
#line 447 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen.unindent(false);
    ps->gen << yygotominor.yy0->data << " = EUDElseIf()" << std::endl;
}
#line 1906 "parser\\epparser.c"
        break;
      case 116: /* elif_header ::= elif_start LPAREN lexpr RPAREN */
#line 453 "parser\\epparser.lemon"
{
    ps->gen << "if " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data <<"):" << std::endl;
    ps->gen.indent();
}
#line 1914 "parser\\epparser.c"
        break;
      case 118: /* else_header ::= ELSE */
#line 460 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "if EUDElse()():" << std::endl;
    ps->gen.indent();
}
#line 1923 "parser\\epparser.c"
        break;
      case 119: /* if_stmt ::= if_block */
      case 120: /* if_stmt ::= if_block else_header stmt */ yytestcase(yyruleno==120);
#line 466 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndIf()" << std::endl;
}
#line 1932 "parser\\epparser.c"
        break;
      case 121: /* while_start ::= WHILE */
#line 478 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDWhile()" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1941 "parser\\epparser.c"
        break;
      case 123: /* while_stmt ::= while_header stmt */
#line 490 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndWhile()" << std::endl;
}
#line 1949 "parser\\epparser.c"
        break;
      case 124: /* for_opener ::= FOR LPAREN */
      case 139: /* foreach_opener ::= FOREACH LPAREN */ yytestcase(yyruleno==139);
#line 496 "parser\\epparser.lemon"
{
    ps->closure.pushScope();
}
#line 1957 "parser\\epparser.c"
        break;
      case 134: /* for_header1 ::= for_opener for_init_stmt SEMICOLON */
#line 512 "parser\\epparser.lemon"
{
    // opening for lexpr
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDWhile()" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1967 "parser\\epparser.c"
        break;
      case 135: /* for_header2 ::= for_header1 lexpr SEMICOLON */
#line 519 "parser\\epparser.lemon"
{
    ps->gen << "if " << yymsp[-2].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data << "):" << std::endl;
    ps->gen.indent();
    delete yymsp[-2].minor.yy0; delete yymsp[-1].minor.yy0;

    // Opening for assign_statement
    yygotominor.yy0 = genTemp(yymsp[-1].minor.yy0);
    ps->gen << "def " << yygotominor.yy0->data <<"():" << std::endl;
    ps->gen.indent();
}
#line 1981 "parser\\epparser.c"
        break;
      case 136: /* for_header ::= for_header2 for_action_stmt_nonEmpty RPAREN */
#line 530 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-2].minor.yy0;
    ps->gen.unindent(false);
}
#line 1989 "parser\\epparser.c"
        break;
      case 137: /* for_header ::= for_header2 RPAREN */
#line 535 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
    ps->gen << "pass" << std::endl;
    ps->gen.unindent(false);
}
#line 1998 "parser\\epparser.c"
        break;
      case 138: /* for_stmt ::= for_header stmt */
#line 541 "parser\\epparser.lemon"
{
    ps->gen << yymsp[-1].minor.yy0->data << "()" << std::endl;
    ps->gen.unindent(false);
    ps->gen << "EUDEndWhile()" << std::endl;
    ps->closure.popScope();
}
#line 2008 "parser\\epparser.c"
        break;
      case 140: /* foreach_header ::= foreach_opener nameList_nonEmpty COLON exprList_nonEmpty RPAREN */
#line 555 "parser\\epparser.lemon"
{
    commaListIter(yymsp[-3].minor.yy0->data, [&](std::string& s) {
        ps->closure.defVariable(s);
    });
    ps->gen << "for " << yymsp[-3].minor.yy0->data << " in " << yymsp[-1].minor.yy0->data << ":" << std::endl;
    ps->gen.indent();
}
#line 2019 "parser\\epparser.c"
        break;
      case 142: /* continue_stmt ::= CONTINUE */
#line 571 "parser\\epparser.lemon"
{
    ps->gen << "EUDContinue()" << std::endl;
}
#line 2026 "parser\\epparser.c"
        break;
      case 143: /* break_stmt ::= BREAK */
#line 575 "parser\\epparser.lemon"
{
    ps->gen << "EUDBreak()" << std::endl;
}
#line 2033 "parser\\epparser.c"
        break;
      case 144: /* return_stmt ::= RETURN exprList */
#line 582 "parser\\epparser.lemon"
{
    ps->gen << "EUDReturn(" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2041 "parser\\epparser.c"
        break;
      case 145: /* lexpr ::= CONDITIONNAME LPAREN fArgs RPAREN */
      case 146: /* lexpr ::= KILLS LPAREN fArgs RPAREN */ yytestcase(yyruleno==146);
#line 590 "parser\\epparser.lemon"
{
    yymsp[-3].minor.yy0->data = yymsp[-3].minor.yy0->data + "(" + yymsp[-1].minor.yy0->data + ")";
    delete yymsp[-1].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 2051 "parser\\epparser.c"
        break;
      case 147: /* lexpr ::= CONDITIONNAME LPAREN RPAREN */
#line 602 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + "()";
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 2059 "parser\\epparser.c"
        break;
      case 148: /* action ::= ACTIONNAME LPAREN fArgs RPAREN SEMICOLON */
#line 607 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[-4].minor.yy0);
    yygotominor.yy0->data =  yymsp[-4].minor.yy0->data + "(" + yymsp[-2].minor.yy0->data + ")";
    delete yymsp[-4].minor.yy0; delete yymsp[-2].minor.yy0;
}
#line 2068 "parser\\epparser.c"
        break;
      case 149: /* actions ::= action action */
      case 150: /* actions ::= actions action */ yytestcase(yyruleno==150);
#line 613 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
    yymsp[-1].minor.yy0->data += ",\n" + yymsp[0].minor.yy0->data;
    delete yymsp[0].minor.yy0;
}
#line 2078 "parser\\epparser.c"
        break;
      case 151: /* actionStmt ::= action */
#line 625 "parser\\epparser.lemon"
{
    ps->gen << "DoActions(" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2086 "parser\\epparser.c"
        break;
      case 152: /* actionStmt ::= actions */
#line 630 "parser\\epparser.lemon"
{
    ps->gen << "DoActions([" << std::endl;
    ps->gen.indent();
    ps->gen << yymsp[0].minor.yy0->data << std::endl;
    ps->gen.unindent(false);
    ps->gen << "])" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2098 "parser\\epparser.c"
        break;
      default:
      /* (0) program ::= chunks */ yytestcase(yyruleno==0);
      /* (1) chunks ::= */ yytestcase(yyruleno==1);
      /* (2) chunks ::= chunks chunk */ yytestcase(yyruleno==2);
      /* (3) chunk ::= import_chunk SEMICOLON */ yytestcase(yyruleno==3);
      /* (4) chunk ::= fdef_chunk */ yytestcase(yyruleno==4);
      /* (5) chunk ::= vdef_stmt SEMICOLON */ yytestcase(yyruleno==5);
      /* (6) chunk ::= cdef_stmt SEMICOLON */ yytestcase(yyruleno==6);
      /* (13) stmt ::= bodyStmt */ yytestcase(yyruleno==13);
      /* (14) stmt ::= return_stmt SEMICOLON */ yytestcase(yyruleno==14);
      /* (18) blockStmt ::= lbracket return_stmt SEMICOLON rbracket */ yytestcase(yyruleno==18);
      /* (19) blockStmt ::= lbracket bodyStmtList rbracket */ yytestcase(yyruleno==19);
      /* (20) blockStmt ::= lbracket bodyStmtList return_stmt SEMICOLON rbracket */ yytestcase(yyruleno==20);
      /* (22) bodyStmt ::= blockStmt */ yytestcase(yyruleno==22);
      /* (23) bodyStmt ::= SEMICOLON */ yytestcase(yyruleno==23);
      /* (24) bodyStmt ::= vdef_stmt SEMICOLON */ yytestcase(yyruleno==24);
      /* (25) bodyStmt ::= vdefAssign_stmt SEMICOLON */ yytestcase(yyruleno==25);
      /* (26) bodyStmt ::= cdef_stmt SEMICOLON */ yytestcase(yyruleno==26);
      /* (27) bodyStmt ::= assign_stmt SEMICOLON */ yytestcase(yyruleno==27);
      /* (29) bodyStmt ::= actionStmt */ yytestcase(yyruleno==29);
      /* (30) bodyStmt ::= if_stmt */ yytestcase(yyruleno==30);
      /* (31) bodyStmt ::= while_stmt */ yytestcase(yyruleno==31);
      /* (32) bodyStmt ::= for_stmt */ yytestcase(yyruleno==32);
      /* (33) bodyStmt ::= foreach_stmt */ yytestcase(yyruleno==33);
      /* (34) bodyStmt ::= continue_stmt SEMICOLON */ yytestcase(yyruleno==34);
      /* (35) bodyStmt ::= break_stmt SEMICOLON */ yytestcase(yyruleno==35);
      /* (36) bodyStmtList ::= bodyStmt */ yytestcase(yyruleno==36);
      /* (37) bodyStmtList ::= bodyStmtList bodyStmt */ yytestcase(yyruleno==37);
      /* (114) if_block ::= if_header stmt */ yytestcase(yyruleno==114);
      /* (117) if_block ::= if_block elif_header stmt */ yytestcase(yyruleno==117);
      /* (125) for_init_stmt_nonEmpty ::= vdef_stmt */ yytestcase(yyruleno==125);
      /* (126) for_init_stmt_nonEmpty ::= vdefAssign_stmt */ yytestcase(yyruleno==126);
      /* (127) for_init_stmt_nonEmpty ::= cdef_stmt */ yytestcase(yyruleno==127);
      /* (128) for_init_stmt_nonEmpty ::= assign_stmt */ yytestcase(yyruleno==128);
      /* (129) for_init_stmt_nonEmpty ::= for_init_stmt_nonEmpty COMMA for_init_stmt_nonEmpty */ yytestcase(yyruleno==129);
      /* (130) for_init_stmt ::= for_init_stmt_nonEmpty */ yytestcase(yyruleno==130);
      /* (131) for_init_stmt ::= */ yytestcase(yyruleno==131);
      /* (132) for_action_stmt_nonEmpty ::= assign_stmt */ yytestcase(yyruleno==132);
      /* (133) for_action_stmt_nonEmpty ::= for_action_stmt_nonEmpty COMMA for_action_stmt_nonEmpty */ yytestcase(yyruleno==133);
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
#line 2187 "parser\\epparser.c"
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
#line 644 "parser\\epparser.lemon"


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
#line 2440 "parser\\epparser.c"
