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
#define YYNOCODE 133
#define YYACTIONTYPE unsigned short int
#define ParseTOKENTYPE Token*
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  int yy265;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL  ParserStruct* ps ;
#define ParseARG_PDECL , ParserStruct* ps 
#define ParseARG_FETCH  ParserStruct* ps  = yypParser->ps 
#define ParseARG_STORE yypParser->ps  = ps 
#define YYNSTATE 329
#define YYNRULE 170
#define YYERRORSYMBOL 71
#define YYERRSYMDT yy265
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
#define YY_ACTTAB_COUNT (1233)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   213,  197,  242,  199,  298,   18,   28,   29,  209,   75,
 /*    10 */   207,  304,  327,  205,   91,  314,  312,  212,    2,  122,
 /*    20 */   145,  208,  206,  150,  296,  295,  294,  293,  292,  201,
 /*    30 */   200,  324,  241,  199,   91,  196,  272,   38,  214,  122,
 /*    40 */   145,  164,    8,   40,  117,  280,  115,  161,    6,   10,
 /*    50 */   221,  213,  220,   22,   13,    5,   82,    4,   76,  209,
 /*    60 */    77,  207,  304,   28,   29,  323,  257,  312,  212,    2,
 /*    70 */    37,  214,  208,  206,  150,  296,  295,  294,  293,  292,
 /*    80 */   201,  200,  162,    7,    3,   91,  196,  243,  322,   19,
 /*    90 */   122,  145,  164,    8,   40,   78,  167,  115,  161,    6,
 /*   100 */    10,  319,  213,  199,   22,   13,    5,   82,    4,  214,
 /*   110 */   209,   77,  207,  304,  116,   14,  278,  254,  312,  212,
 /*   120 */     2,   39,  199,  208,  206,  150,  296,  295,  294,  293,
 /*   130 */   292,  201,  200,   97,   81,   80,   91,  196,  260,   35,
 /*   140 */    36,  122,  145,  164,    8,   40,  240,  166,  115,  161,
 /*   150 */     6,   10,  236,  213,  193,   22,   13,    5,   82,    4,
 /*   160 */   318,  209,   77,  207,  304,   33,  214,  218,  251,  312,
 /*   170 */   212,    2,   34,  217,  208,  206,  150,  296,  295,  294,
 /*   180 */   293,  292,  201,  200,  216,  317,  199,   91,  196,  192,
 /*   190 */   214,  215,  122,  145,  164,    8,   40,   94,  165,  115,
 /*   200 */   161,    6,   10,  315,  213,  199,   22,   13,    5,   82,
 /*   210 */     4,  204,  209,   77,  207,  304,  128,  500,   11,  238,
 /*   220 */   312,  212,    2,  203,  199,  208,  206,  150,  296,  295,
 /*   230 */   294,  293,  292,  201,  200,  127,  313,  199,   91,  196,
 /*   240 */   202,  311,   87,  122,  145,  164,    8,   40,  140,  142,
 /*   250 */   115,  161,    6,   10,   86,  213,  199,   22,   13,    5,
 /*   260 */    82,    4,  297,  209,   77,  207,  304,  139,  291,  302,
 /*   270 */   235,  312,  212,    2,  301,  199,  208,  206,  150,  296,
 /*   280 */   295,  294,  293,  292,  201,  200,  138,  300,  199,   91,
 /*   290 */   196,  205,  299,  290,  122,  145,  164,    8,   40,  126,
 /*   300 */   152,  115,  161,    6,   10,   19,  213,  199,   22,   13,
 /*   310 */     5,   82,    4,  285,  209,   77,  207,  304,  125,  195,
 /*   320 */    85,  228,  312,  212,    2,  282,  199,  208,  206,  150,
 /*   330 */   296,  295,  294,  293,  292,  201,  200,   90,  281,  199,
 /*   340 */    91,  133,   39,   31,   17,  122,  145,  164,    8,   40,
 /*   350 */   124,   32,  186,  161,    6,   10,  185,  153,  199,   22,
 /*   360 */    13,    5,   82,    4,  277,  209,   77,  207,  304,  116,
 /*   370 */   183,  188,  169,  226,  211,    2,  276,    1,  208,  206,
 /*   380 */   150,  296,  295,  294,  293,  292,  201,  200,  180,  182,
 /*   390 */   199,   91,  199,  179,  275,  177,  122,  145,  164,    8,
 /*   400 */    40,  121,  274,   89,  161,    6,   10,  134,  288,  199,
 /*   410 */    22,   13,    5,   82,    4,  176,  209,   77,  207,  304,
 /*   420 */   116,  273,  188,  170,  289,  210,    2,  306,  199,  208,
 /*   430 */   206,  150,  296,  295,  294,  293,  292,  201,  200,   90,
 /*   440 */    29,  199,   91,  271,   15,  265,  268,  122,  145,  164,
 /*   450 */     8,   40,  123,  264,  263,  161,    6,   10,  120,  256,
 /*   460 */    25,   22,   13,    5,   82,    4,   63,   62,   77,   71,
 /*   470 */    72,   70,   61,  287,  118,  303,  199,  197,   24,   23,
 /*   480 */    64,   18,  310,  309,   21,   75,  286,   93,  250,  190,
 /*   490 */   187,  184,  181,  178,   84,   83,   42,   41,  199,   63,
 /*   500 */    62,   28,   29,   12,  244,   61,  287,  118,  259,  137,
 /*   510 */   253,  160,  157,   64,  234,  233,   20,   21,  154,  286,
 /*   520 */   237,  199,  190,  187,  184,  181,  178,   63,   62,   42,
 /*   530 */    41,  266,  136,   61,  287,  118,  303,  199,  199,   16,
 /*   540 */   231,   64,  151,  310,  308,   21,  227,  286,  135,  114,
 /*   550 */   190,  187,  184,  181,  178,   84,   83,   42,   41,   66,
 /*   560 */    65,   67,   69,   68,   74,   73,   71,   72,   70,  259,
 /*   570 */   199,  253,  160,  157,  197,  234,  233,   20,   18,  320,
 /*   580 */   196,   90,   75,  284,  307,  174,  308,  199,   63,   62,
 /*   590 */   191,  115,  171,  305,   61,  287,  118,  303,  116,  148,
 /*   600 */   188,  175,   64,  194,  310,  147,   21,  316,  286,  199,
 /*   610 */   156,  190,  187,  184,  181,  178,   84,   83,   42,   41,
 /*   620 */   113,   74,   73,   71,   72,   70,   28,   29,   28,   29,
 /*   630 */   259,  197,  253,  160,  157,   18,  234,  233,   20,   75,
 /*   640 */    60,   58,   57,   56,   55,   59,   66,   65,   67,   69,
 /*   650 */    68,   74,   73,   71,   72,   70,  258,  199,  255,  146,
 /*   660 */   196,  197,  143,  230,  229,   18,  283,  141,  112,   75,
 /*   670 */   191,  115,  232,   60,   58,   57,   56,   55,   59,   66,
 /*   680 */    65,   67,   69,   68,   74,   73,   71,   72,   70,  163,
 /*   690 */   501,  242,  199,  199,  197,  501,  501,  501,   18,   63,
 /*   700 */    62,  199,   75,   91,  111,   61,  287,  118,  122,  145,
 /*   710 */   501,  501,  116,   64,  188,  155,  501,   21,  501,  286,
 /*   720 */   501,  144,  190,  187,  184,  181,  178,   84,   83,   42,
 /*   730 */    41,  199,   63,   62,  501,  501,  501,  199,   61,  287,
 /*   740 */   118,  501,  116,  199,  188,  172,   64,  239,  110,  501,
 /*   750 */    21,  501,  286,  501,  109,  190,  187,  184,  181,  178,
 /*   760 */    28,   29,   42,   41,   66,   65,   67,   69,   68,   74,
 /*   770 */    73,   71,   72,   70,  199,   27,  501,  501,  249,  168,
 /*   780 */   247,  501,  501,   18,  501,   92,  501,   54,   63,   62,
 /*   790 */   252,  248,  246,  199,   61,  287,  198,  436,  436,  262,
 /*   800 */   261,  501,   30,  501,   91,   26,   21,  501,  189,  122,
 /*   810 */   145,  190,  187,  184,  181,  178,  199,  501,   63,   62,
 /*   820 */   159,  158,  199,  199,   61,  287,  198,   90,   19,  501,
 /*   830 */   501,  270,   30,   90,  108,  501,   21,  269,  189,  173,
 /*   840 */   501,  190,  187,  184,  181,  178,  436,  436,  436,  436,
 /*   850 */   436,  436,  436,  436,  436,  436,  199,   63,   62,  199,
 /*   860 */   501,  501,  199,   61,  287,  149,  501,  107,  199,  173,
 /*   870 */    90,   64,  267,  106,  132,   21,  501,  286,  279,  105,
 /*   880 */   190,  187,  184,  181,  178,   66,   65,   67,   69,   68,
 /*   890 */    74,   73,   71,   72,   70,  199,  501,  501,  501,  501,
 /*   900 */   197,  199,  501,  501,   18,  283,   90,  501,   75,  501,
 /*   910 */   131,  501,  104,  199,   66,   65,   67,   69,   68,   74,
 /*   920 */    73,   71,   72,   70,   90,  501,  501,  501,  130,  197,
 /*   930 */   501,  501,  199,   18,   63,   62,  501,   75,  119,  199,
 /*   940 */    61,  287,  149,   90,  501,  199,  501,  129,   64,  501,
 /*   950 */   103,  501,   21,  501,  286,  279,  102,  190,  187,  184,
 /*   960 */   181,  178,   66,   65,   67,   69,   68,   74,   73,   71,
 /*   970 */    72,   70,  199,  199,  501,  199,  199,  197,  199,  199,
 /*   980 */   501,   18,  501,  101,  100,   75,   99,   98,  501,   96,
 /*   990 */    95,   66,   65,   67,   69,   68,   74,   73,   71,   72,
 /*  1000 */    70,  501,  501,  501,  501,  501,  168,  501,  501,  501,
 /*  1010 */    18,   63,   62,  501,   54,  501,  501,   61,  287,  198,
 /*  1020 */   501,  501,  501,  501,  501,   64,  501,  501,  501,   21,
 /*  1030 */   501,  286,  501,  501,  190,  187,  184,  181,  178,  501,
 /*  1040 */   501,  501,  501,  501,   63,   62,  501,  438,  438,  501,
 /*  1050 */    61,  287,  118,  501,  501,  501,  501,  501,   64,  501,
 /*  1060 */   501,  501,   21,  501,  286,  501,  501,  190,  187,  184,
 /*  1070 */   181,  178,  501,   65,   67,   69,   68,   74,   73,   71,
 /*  1080 */    72,   70,  437,  437,  501,  501,  501,  197,  501,  501,
 /*  1090 */   501,   18,  501,  501,  501,   75,  438,  438,  438,  438,
 /*  1100 */   438,  438,  438,  438,  438,  438,   53,   67,   69,   68,
 /*  1110 */    74,   73,   71,   72,   70,  501,  501,  501,  501,  501,
 /*  1120 */   197,  501,  501,  501,   18,  501,  501,  501,   75,  501,
 /*  1130 */   501,  437,  437,  437,  437,  437,  437,  437,  437,  437,
 /*  1140 */   437,  501,  501,  501,  501,  501,  501,  501,  501,  501,
 /*  1150 */   501,  501,  501,  501,  501,   52,   51,   50,   49,   48,
 /*  1160 */    47,   46,   45,   44,   43,  501,  501,  501,  501,  501,
 /*  1170 */   501,  501,   69,   68,   74,   73,   71,   72,   70,  501,
 /*  1180 */   249,  501,  247,  501,  197,  329,  501,  501,   18,  501,
 /*  1190 */   501,  501,   75,  248,  246,  199,  328,  225,  326,  325,
 /*  1200 */   224,  223,  222,  321,  501,    9,   91,  501,  501,  501,
 /*  1210 */     2,  122,  145,  501,   88,  501,  219,  501,  501,  310,
 /*  1220 */   501,  501,  245,  501,  501,  501,  501,  501,  501,  501,
 /*  1230 */   501,   79,   83,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    71,   28,   93,   94,   27,   32,    3,    4,   79,   36,
 /*    10 */    81,   82,   27,   36,  105,   86,   87,   88,   89,  110,
 /*    20 */   111,   92,   93,   94,   95,   96,   97,   98,   99,  100,
 /*    30 */   101,   27,  123,   94,  105,   94,   33,    1,    2,  110,
 /*    40 */   111,  112,  113,  114,  105,  104,  105,  118,  119,  120,
 /*    50 */    28,   71,   30,  124,  125,  126,  127,  128,    1,   79,
 /*    60 */   131,   81,   82,    3,    4,   27,   86,   87,   88,   89,
 /*    70 */     1,    2,   92,   93,   94,   95,   96,   97,   98,   99,
 /*    80 */   100,  101,  115,  116,  117,  105,   94,   27,   27,   32,
 /*    90 */   110,  111,  112,  113,  114,   32,  104,  105,  118,  119,
 /*   100 */   120,   26,   71,   94,  124,  125,  126,  127,  128,    2,
 /*   110 */    79,  131,   81,   82,  105,    2,  107,   86,   87,   88,
 /*   120 */    89,    2,   94,   92,   93,   94,   95,   96,   97,   98,
 /*   130 */    99,  100,  101,  105,  129,  130,  105,   94,  110,    1,
 /*   140 */     2,  110,  111,  112,  113,  114,   33,  104,  105,  118,
 /*   150 */   119,  120,   33,   71,    2,  124,  125,  126,  127,  128,
 /*   160 */    26,   79,  131,   81,   82,    1,    2,   26,   86,   87,
 /*   170 */    88,   89,   65,   85,   92,   93,   94,   95,   96,   97,
 /*   180 */    98,   99,  100,  101,   33,   27,   94,  105,   94,   37,
 /*   190 */     2,  103,  110,  111,  112,  113,  114,  105,  104,  105,
 /*   200 */   118,  119,  120,   26,   71,   94,  124,  125,  126,  127,
 /*   210 */   128,   36,   79,  131,   81,   82,  105,   73,   74,   86,
 /*   220 */    87,   88,   89,   25,   94,   92,   93,   94,   95,   96,
 /*   230 */    97,   98,   99,  100,  101,  105,   27,   94,  105,   94,
 /*   240 */    37,   27,   27,  110,  111,  112,  113,  114,  105,  104,
 /*   250 */   105,  118,  119,  120,   27,   71,   94,  124,  125,  126,
 /*   260 */   127,  128,   37,   79,  131,   81,   82,  105,   27,   27,
 /*   270 */    86,   87,   88,   89,   27,   94,   92,   93,   94,   95,
 /*   280 */    96,   97,   98,   99,  100,  101,  105,   27,   94,  105,
 /*   290 */    94,   36,   27,   27,  110,  111,  112,  113,  114,  105,
 /*   300 */   104,  105,  118,  119,  120,   32,   71,   94,  124,  125,
 /*   310 */   126,  127,  128,   26,   79,  131,   81,   82,  105,   36,
 /*   320 */    36,   86,   87,   88,   89,   25,   94,   92,   93,   94,
 /*   330 */    95,   96,   97,   98,   99,  100,  101,  105,   37,   94,
 /*   340 */   105,  109,    2,   32,   32,  110,  111,  112,  113,  114,
 /*   350 */   105,    2,   32,  118,  119,  120,   39,   71,   94,  124,
 /*   360 */   125,  126,  127,  128,   33,   79,  131,   81,   82,  105,
 /*   370 */    32,  107,  108,   87,   88,   89,   33,   91,   92,   93,
 /*   380 */    94,   95,   96,   97,   98,   99,  100,  101,   32,   39,
 /*   390 */    94,  105,   94,   39,   33,   32,  110,  111,  112,  113,
 /*   400 */   114,  105,   33,  105,  118,  119,  120,  109,   71,   94,
 /*   410 */   124,  125,  126,  127,  128,   39,   79,  131,   81,   82,
 /*   420 */   105,   33,  107,  108,   87,   88,   89,   90,   94,   92,
 /*   430 */    93,   94,   95,   96,   97,   98,   99,  100,  101,  105,
 /*   440 */     4,   94,  105,  109,   32,   37,   33,  110,  111,  112,
 /*   450 */   113,  114,  105,   33,   33,  118,  119,  120,   26,   60,
 /*   460 */    32,  124,  125,  126,  127,  128,   18,   19,  131,   20,
 /*   470 */    21,   22,   24,   25,   26,   27,   94,   28,   32,   32,
 /*   480 */    32,   32,   34,   35,   36,   36,   38,  105,   32,   41,
 /*   490 */    42,   43,   44,   45,   46,   47,   48,   49,   94,   18,
 /*   500 */    19,    3,    4,    2,   27,   24,   25,   26,   60,  105,
 /*   510 */    62,   63,   64,   32,   66,   67,   68,   36,   33,   38,
 /*   520 */    32,   94,   41,   42,   43,   44,   45,   18,   19,   48,
 /*   530 */    49,   33,  105,   24,   25,   26,   27,   94,   94,   32,
 /*   540 */    27,   32,   83,   34,   35,   36,   35,   38,  105,  105,
 /*   550 */    41,   42,   43,   44,   45,   46,   47,   48,   49,   13,
 /*   560 */    14,   15,   16,   17,   18,   19,   20,   21,   22,   60,
 /*   570 */    94,   62,   63,   64,   28,   66,   67,   68,   32,   26,
 /*   580 */    94,  105,   36,   37,   90,  109,   35,   94,   18,   19,
 /*   590 */   104,  105,  106,   90,   24,   25,   26,   27,  105,  102,
 /*   600 */   107,  108,   32,   25,   34,  103,   36,   26,   38,   94,
 /*   610 */    70,   41,   42,   43,   44,   45,   46,   47,   48,   49,
 /*   620 */   105,   18,   19,   20,   21,   22,    3,    4,    3,    4,
 /*   630 */    60,   28,   62,   63,   64,   32,   66,   67,   68,   36,
 /*   640 */     7,    8,    9,   10,   11,   12,   13,   14,   15,   16,
 /*   650 */    17,   18,   19,   20,   21,   22,   33,   94,   33,  103,
 /*   660 */    94,   28,  103,  129,  129,   32,   33,  103,  105,   36,
 /*   670 */   104,  105,  106,    7,    8,    9,   10,   11,   12,   13,
 /*   680 */    14,   15,   16,   17,   18,   19,   20,   21,   22,   61,
 /*   690 */   132,   93,   94,   94,   28,  132,  132,  132,   32,   18,
 /*   700 */    19,   94,   36,  105,  105,   24,   25,   26,  110,  111,
 /*   710 */   132,  132,  105,   32,  107,  108,  132,   36,  132,   38,
 /*   720 */   132,  123,   41,   42,   43,   44,   45,   46,   47,   48,
 /*   730 */    49,   94,   18,   19,  132,  132,  132,   94,   24,   25,
 /*   740 */    26,  132,  105,   94,  107,  108,   32,   33,  105,  132,
 /*   750 */    36,  132,   38,  132,  105,   41,   42,   43,   44,   45,
 /*   760 */     3,    4,   48,   49,   13,   14,   15,   16,   17,   18,
 /*   770 */    19,   20,   21,   22,   94,    5,  132,  132,   79,   28,
 /*   780 */    81,  132,  132,   32,  132,  105,  132,   36,   18,   19,
 /*   790 */    33,   92,   93,   94,   24,   25,   26,    1,    2,   48,
 /*   800 */    49,  132,   32,  132,  105,    5,   36,  132,   38,  110,
 /*   810 */   111,   41,   42,   43,   44,   45,   94,  132,   18,   19,
 /*   820 */   121,  122,   94,   94,   24,   25,   26,  105,   32,  132,
 /*   830 */   132,  109,   32,  105,  105,  132,   36,  109,   38,   69,
 /*   840 */   132,   41,   42,   43,   44,   45,   50,   51,   52,   53,
 /*   850 */    54,   55,   56,   57,   58,   59,   94,   18,   19,   94,
 /*   860 */   132,  132,   94,   24,   25,   26,  132,  105,   94,   69,
 /*   870 */   105,   32,   33,  105,  109,   36,  132,   38,   39,  105,
 /*   880 */    41,   42,   43,   44,   45,   13,   14,   15,   16,   17,
 /*   890 */    18,   19,   20,   21,   22,   94,  132,  132,  132,  132,
 /*   900 */    28,   94,  132,  132,   32,   33,  105,  132,   36,  132,
 /*   910 */   109,  132,  105,   94,   13,   14,   15,   16,   17,   18,
 /*   920 */    19,   20,   21,   22,  105,  132,  132,  132,  109,   28,
 /*   930 */   132,  132,   94,   32,   18,   19,  132,   36,   37,   94,
 /*   940 */    24,   25,   26,  105,  132,   94,  132,  109,   32,  132,
 /*   950 */   105,  132,   36,  132,   38,   39,  105,   41,   42,   43,
 /*   960 */    44,   45,   13,   14,   15,   16,   17,   18,   19,   20,
 /*   970 */    21,   22,   94,   94,  132,   94,   94,   28,   94,   94,
 /*   980 */   132,   32,  132,  105,  105,   36,  105,  105,  132,  105,
 /*   990 */   105,   13,   14,   15,   16,   17,   18,   19,   20,   21,
 /*  1000 */    22,  132,  132,  132,  132,  132,   28,  132,  132,  132,
 /*  1010 */    32,   18,   19,  132,   36,  132,  132,   24,   25,   26,
 /*  1020 */   132,  132,  132,  132,  132,   32,  132,  132,  132,   36,
 /*  1030 */   132,   38,  132,  132,   41,   42,   43,   44,   45,  132,
 /*  1040 */   132,  132,  132,  132,   18,   19,  132,    1,    2,  132,
 /*  1050 */    24,   25,   26,  132,  132,  132,  132,  132,   32,  132,
 /*  1060 */   132,  132,   36,  132,   38,  132,  132,   41,   42,   43,
 /*  1070 */    44,   45,  132,   14,   15,   16,   17,   18,   19,   20,
 /*  1080 */    21,   22,    1,    2,  132,  132,  132,   28,  132,  132,
 /*  1090 */   132,   32,  132,  132,  132,   36,   50,   51,   52,   53,
 /*  1100 */    54,   55,   56,   57,   58,   59,    1,   15,   16,   17,
 /*  1110 */    18,   19,   20,   21,   22,  132,  132,  132,  132,  132,
 /*  1120 */    28,  132,  132,  132,   32,  132,  132,  132,   36,  132,
 /*  1130 */   132,   50,   51,   52,   53,   54,   55,   56,   57,   58,
 /*  1140 */    59,  132,  132,  132,  132,  132,  132,  132,  132,  132,
 /*  1150 */   132,  132,  132,  132,  132,   50,   51,   52,   53,   54,
 /*  1160 */    55,   56,   57,   58,   59,  132,  132,  132,  132,  132,
 /*  1170 */   132,  132,   16,   17,   18,   19,   20,   21,   22,  132,
 /*  1180 */    79,  132,   81,  132,   28,    0,  132,  132,   32,  132,
 /*  1190 */   132,  132,   36,   92,   93,   94,   75,   76,   77,   78,
 /*  1200 */    79,   80,   81,   82,  132,   84,  105,  132,  132,  132,
 /*  1210 */    89,  110,  111,  132,   29,  132,   31,  132,  132,   34,
 /*  1220 */   132,  132,  121,  132,  132,  132,  132,  132,  132,  132,
 /*  1230 */   132,   46,   47,
};
#define YY_SHIFT_USE_DFLT (-28)
#define YY_SHIFT_COUNT (225)
#define YY_SHIFT_MIN   (-27)
#define YY_SHIFT_MAX   (1185)
static const short yy_shift_ofst[] = {
 /*     0 */   -28,  509,  448,  570,  570,  570,  570,  570,  570,  570,
 /*    10 */   681, 1185,  681,  714,  481,  839,  916,  916,  916,  916,
 /*    20 */   993,  993,  770,  770,  770,  770,  800,  800,  770,  770,
 /*    30 */   770,  770,  916,  993,  993,  993, 1026,  993,  993,  993,
 /*    40 */   628,  993,  993,  993,  993,  993,  993,  993,  993,  993,
 /*    50 */   993,  993,  993,  993,  993,  993,  993,  993,  993,  993,
 /*    60 */   993,  993,  993,  993,  993,  993,  993,  993,  993,  993,
 /*    70 */   993,  993,  993,  993,  993,  993,  993,  540,  581,  581,
 /*    80 */   540,  540,  581,  581,  581,  578,  551,  551,  553,  633,
 /*    90 */   666,  751,  901,  872,  546,  949,  949,  978,  949,  949,
 /*   100 */   949,  949,  949,  949,  949,  949,  949,  949,  949,  949,
 /*   110 */   949,  949,  949,  949,  949,  949,  949,  949,  796, 1081,
 /*   120 */  1046, 1059, 1105, 1092, 1156,  603,  603,  449,  449,   60,
 /*   130 */   757,  625,  623,  498,    3,  -27,  -27,  -27,  -27,  -27,
 /*   140 */   -27,  164,  119,  107,  113,  138,   69,   36,  152,   57,
 /*   150 */   -23,   22,  340,  511,  513,  485,  507,  488,  477,  501,
 /*   160 */   456,  447,  446,  399,  428,  340,  340,  340,  432,  421,
 /*   170 */   420,  408,  413,  412,  436,  388,  369,  376,  363,  361,
 /*   180 */   354,  356,  343,  350,  338,  331,  317,  320,  349,  312,
 /*   190 */   311,  340,  301,  300,  203,  284,  283,  287,  273,  255,
 /*   200 */   266,  241,  225,  203,  198,  175,  265,  260,  247,  242,
 /*   210 */   227,  215,  214,  209,  177,  188,  158,  151,   63,  141,
 /*   220 */   134,   75,   61,   38,    4,  -15,
};
#define YY_REDUCE_USE_DFLT (-92)
#define YY_REDUCE_COUNT (88)
#define YY_REDUCE_MIN   (-91)
#define YY_REDUCE_MAX   (1121)
static const short yy_reduce_ofst[] = {
 /*     0 */   144,  337,  286,  235,  184,  133,   82,   31,  -20,  -71,
 /*    10 */   699, 1121, 1101,  598,  -91,  637,  607,  493,  315,  264,
 /*    20 */   566,  486,  838,  819,  801,  765,  728,  722,  476,  334,
 /*    30 */   298,  232,    9,  196,  145,   94,   28,   43,   -8,  -59,
 /*    40 */   -33,  885,  884,  882,  881,  879,  878,  851,  845,  807,
 /*    50 */   774,  768,  762,  729,  680,  649,  643,  599,  563,  515,
 /*    60 */   444,  443,  427,  404,  382,  347,  296,  245,  213,  194,
 /*    70 */   181,  162,  143,  130,  111,   92,  -61,    5,   88,  564,
 /*    80 */   535,  534,  559,  556,  502,  497,  503,  494,  459,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   330,  496,  496,  496,  496,  496,  496,  496,  496,  496,
 /*    10 */   476,  499,  499,  499,  499,  499,  395,  395,  395,  395,
 /*    20 */   384,  384,  499,  499,  499,  499,  499,  499,  499,  499,
 /*    30 */   499,  499,  499,  499,  499,  499,  499,  499,  499,  499,
 /*    40 */   464,  499,  499,  499,  499,  499,  499,  499,  499,  499,
 /*    50 */   499,  499,  499,  499,  499,  499,  499,  499,  499,  499,
 /*    60 */   499,  499,  499,  499,  499,  499,  499,  499,  499,  499,
 /*    70 */   499,  499,  499,  499,  499,  499,  499,  499,  378,  499,
 /*    80 */   498,  497,  499,  499,  499,  499,  499,  499,  499,  420,
 /*    90 */   420,  499,  499,  499,  499,  445,  443,  499,  456,  455,
 /*   100 */   454,  453,  452,  451,  450,  449,  448,  447,  441,  427,
 /*   110 */   426,  425,  424,  423,  422,  382,  391,  393,  388,  390,
 /*   120 */   389,  415,  439,  416,  414,  413,  412,  408,  407,  499,
 /*   130 */   499,  499,  499,  499,  499,  419,  418,  417,  411,  410,
 /*   140 */   409,  432,  499,  499,  499,  499,  499,  432,  499,  388,
 /*   150 */   399,  342,  434,  370,  499,  499,  499,  499,  499,  475,
 /*   160 */   499,  499,  499,  463,  499,  442,  435,  433,  499,  499,
 /*   170 */   499,  499,  499,  499,  429,  499,  499,  499,  499,  499,
 /*   180 */   499,  499,  499,  499,  499,  499,  499,  499,  396,  387,
 /*   190 */   499,  385,  499,  499,  374,  499,  399,  499,  388,  399,
 /*   200 */   499,  499,  499,  499,  499,  499,  499,  499,  499,  499,
 /*   210 */   499,  499,  499,  499,  499,  379,  343,  499,  499,  499,
 /*   220 */   499,  499,  499,  499,  499,  499,  371,  355,  465,  495,
 /*   230 */   494,  493,  489,  488,  487,  486,  485,  484,  483,  482,
 /*   240 */   481,  478,  477,  480,  479,  474,  473,  472,  471,  470,
 /*   250 */   469,  468,  467,  466,  462,  461,  460,  459,  458,  457,
 /*   260 */   440,  446,  444,  397,  398,  401,  402,  492,  490,  431,
 /*   270 */   430,  428,  421,  491,  406,  405,  404,  403,  394,  392,
 /*   280 */   383,  380,  375,  400,  390,  389,  387,  386,  373,  372,
 /*   290 */   369,  368,  367,  366,  365,  364,  363,  381,  362,  361,
 /*   300 */   360,  359,  358,  357,  356,  354,  353,  352,  350,  351,
 /*   310 */   349,  348,  347,  346,  344,  377,  376,  345,  341,  340,
 /*   320 */   339,  338,  337,  336,  335,  334,  333,  332,  331,
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
  "vdefAssign_global_stmt",  "cdef_stmt",     "blockStmt",     "dottedName",  
  "fdef_header",   "nameList",      "stmt",          "bodyStmt",    
  "return_stmt",   "lbracket",      "rbracket",      "bodyStmtList",
  "vdefAssign_stmt",  "assign_stmt",   "funcexpr",      "actionStmt",  
  "if_stmt",       "while_stmt",    "for_stmt",      "foreach_stmt",
  "continue_stmt",  "break_stmt",    "numList_nonEmpty",  "nameList_nonEmpty",
  "exprList_nonEmpty",  "expr",          "exprList",      "fArgs_nonEmpty",
  "fArgs",         "lexpr",         "lvalue",        "lvalueList_nonEmpty",
  "if_start",      "if_header",     "if_block",      "elif_start",  
  "elif_header",   "else_header",   "while_start",   "while_header",
  "for_opener",    "for_init_stmt_nonEmpty",  "for_init_stmt",  "for_action_stmt_nonEmpty",
  "for_header1",   "for_header2",   "for_header",    "foreach_opener",
  "foreach_header",  "action",        "actions",       "actionStmt_start",
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
 /*  72 */ "expr ::= LSQBRACKET exprList RSQBRACKET",
 /*  73 */ "expr ::= L2V LPAREN lexpr RPAREN",
 /*  74 */ "expr ::= MAPSTRING LPAREN STRING RPAREN",
 /*  75 */ "expr ::= UNIT LPAREN STRING RPAREN",
 /*  76 */ "expr ::= SWITCH LPAREN STRING RPAREN",
 /*  77 */ "expr ::= LOCATION LPAREN STRING RPAREN",
 /*  78 */ "expr ::= expr PLUS expr",
 /*  79 */ "expr ::= expr MINUS expr",
 /*  80 */ "expr ::= expr MULTIPLY expr",
 /*  81 */ "expr ::= expr DIVIDE expr",
 /*  82 */ "expr ::= expr MOD expr",
 /*  83 */ "expr ::= expr LSHIFT expr",
 /*  84 */ "expr ::= expr RSHIFT expr",
 /*  85 */ "expr ::= expr BITAND expr",
 /*  86 */ "expr ::= expr BITOR expr",
 /*  87 */ "expr ::= expr BITXOR expr",
 /*  88 */ "expr ::= PLUS expr",
 /*  89 */ "expr ::= MINUS expr",
 /*  90 */ "expr ::= BITNOT expr",
 /*  91 */ "lexpr ::= expr",
 /*  92 */ "lexpr ::= LPAREN lexpr RPAREN",
 /*  93 */ "lexpr ::= expr EQ expr",
 /*  94 */ "lexpr ::= expr NE expr",
 /*  95 */ "lexpr ::= expr LE expr",
 /*  96 */ "lexpr ::= expr LT expr",
 /*  97 */ "lexpr ::= expr GE expr",
 /*  98 */ "lexpr ::= expr GT expr",
 /*  99 */ "lexpr ::= lexpr LAND lexpr",
 /* 100 */ "lexpr ::= lexpr LOR lexpr",
 /* 101 */ "lexpr ::= LNOT lexpr",
 /* 102 */ "lexpr ::= LNOT LNOT lexpr",
 /* 103 */ "vdef_stmt ::= VAR nameList_nonEmpty",
 /* 104 */ "vdefAssign_stmt ::= VAR nameList_nonEmpty ASSIGN exprList_nonEmpty",
 /* 105 */ "vdefAssign_global_stmt ::= VAR nameList_nonEmpty ASSIGN exprList_nonEmpty",
 /* 106 */ "cdef_stmt ::= CONST nameList_nonEmpty ASSIGN exprList_nonEmpty",
 /* 107 */ "lvalue ::= NAME",
 /* 108 */ "lvalue ::= expr LSQBRACKET expr RSQBRACKET",
 /* 109 */ "lvalue ::= expr PERIOD NAME",
 /* 110 */ "lvalueList_nonEmpty ::= lvalue",
 /* 111 */ "lvalueList_nonEmpty ::= lvalueList_nonEmpty COMMA lvalue",
 /* 112 */ "assign_stmt ::= lvalue ASSIGN expr",
 /* 113 */ "assign_stmt ::= lvalueList_nonEmpty ASSIGN exprList_nonEmpty",
 /* 114 */ "assign_stmt ::= INC expr",
 /* 115 */ "assign_stmt ::= expr INC",
 /* 116 */ "assign_stmt ::= DEC expr",
 /* 117 */ "assign_stmt ::= expr DEC",
 /* 118 */ "assign_stmt ::= lvalue IADD expr",
 /* 119 */ "assign_stmt ::= lvalue ISUB expr",
 /* 120 */ "assign_stmt ::= lvalue IMUL expr",
 /* 121 */ "assign_stmt ::= lvalue IDIV expr",
 /* 122 */ "assign_stmt ::= lvalue IMOD expr",
 /* 123 */ "assign_stmt ::= lvalue ILSH expr",
 /* 124 */ "assign_stmt ::= lvalue IRSH expr",
 /* 125 */ "assign_stmt ::= lvalue IBND expr",
 /* 126 */ "assign_stmt ::= lvalue IBOR expr",
 /* 127 */ "assign_stmt ::= lvalue IBXR expr",
 /* 128 */ "if_start ::= IF",
 /* 129 */ "if_header ::= if_start LPAREN lexpr RPAREN",
 /* 130 */ "if_block ::= if_header stmt",
 /* 131 */ "elif_start ::= ELSE IF",
 /* 132 */ "elif_header ::= elif_start LPAREN lexpr RPAREN",
 /* 133 */ "if_block ::= if_block elif_header stmt",
 /* 134 */ "else_header ::= ELSE",
 /* 135 */ "if_stmt ::= if_block",
 /* 136 */ "if_stmt ::= if_block else_header stmt",
 /* 137 */ "while_start ::= WHILE",
 /* 138 */ "while_header ::= while_start LPAREN lexpr RPAREN",
 /* 139 */ "while_stmt ::= while_header stmt",
 /* 140 */ "for_opener ::= FOR LPAREN",
 /* 141 */ "for_init_stmt_nonEmpty ::= vdef_stmt",
 /* 142 */ "for_init_stmt_nonEmpty ::= vdefAssign_stmt",
 /* 143 */ "for_init_stmt_nonEmpty ::= cdef_stmt",
 /* 144 */ "for_init_stmt_nonEmpty ::= assign_stmt",
 /* 145 */ "for_init_stmt_nonEmpty ::= for_init_stmt_nonEmpty COMMA for_init_stmt_nonEmpty",
 /* 146 */ "for_init_stmt ::= for_init_stmt_nonEmpty",
 /* 147 */ "for_init_stmt ::=",
 /* 148 */ "for_action_stmt_nonEmpty ::= assign_stmt",
 /* 149 */ "for_action_stmt_nonEmpty ::= for_action_stmt_nonEmpty COMMA for_action_stmt_nonEmpty",
 /* 150 */ "for_header1 ::= for_opener for_init_stmt SEMICOLON",
 /* 151 */ "for_header2 ::= for_header1 lexpr SEMICOLON",
 /* 152 */ "for_header ::= for_header2 for_action_stmt_nonEmpty RPAREN",
 /* 153 */ "for_header ::= for_header2 RPAREN",
 /* 154 */ "for_stmt ::= for_header stmt",
 /* 155 */ "foreach_opener ::= FOREACH LPAREN",
 /* 156 */ "foreach_header ::= foreach_opener nameList_nonEmpty COLON exprList_nonEmpty RPAREN",
 /* 157 */ "foreach_stmt ::= foreach_header stmt",
 /* 158 */ "continue_stmt ::= CONTINUE",
 /* 159 */ "break_stmt ::= BREAK",
 /* 160 */ "return_stmt ::= RETURN exprList",
 /* 161 */ "lexpr ::= CONDITIONNAME LPAREN fArgs RPAREN",
 /* 162 */ "lexpr ::= KILLS LPAREN fArgs RPAREN",
 /* 163 */ "lexpr ::= CONDITIONNAME LPAREN RPAREN",
 /* 164 */ "action ::= ACTIONNAME LPAREN fArgs RPAREN SEMICOLON",
 /* 165 */ "actions ::= action action",
 /* 166 */ "actions ::= actions action",
 /* 167 */ "actionStmt_start ::=",
 /* 168 */ "actionStmt ::= actionStmt_start action",
 /* 169 */ "actionStmt ::= actionStmt_start actions",
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
#line 886 "parser\\epparser.c"
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
  { 102, 1 },
  { 102, 3 },
  { 103, 1 },
  { 103, 3 },
  { 85, 0 },
  { 85, 1 },
  { 104, 6 },
  { 105, 6 },
  { 104, 1 },
  { 104, 3 },
  { 106, 0 },
  { 106, 1 },
  { 105, 1 },
  { 105, 1 },
  { 105, 1 },
  { 105, 3 },
  { 105, 4 },
  { 107, 1 },
  { 107, 1 },
  { 107, 3 },
  { 107, 3 },
  { 108, 0 },
  { 108, 1 },
  { 94, 4 },
  { 94, 4 },
  { 105, 1 },
  { 105, 3 },
  { 105, 3 },
  { 105, 4 },
  { 105, 4 },
  { 105, 4 },
  { 105, 4 },
  { 105, 4 },
  { 105, 3 },
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
  { 105, 2 },
  { 105, 2 },
  { 109, 1 },
  { 109, 3 },
  { 109, 3 },
  { 109, 3 },
  { 109, 3 },
  { 109, 3 },
  { 109, 3 },
  { 109, 3 },
  { 109, 3 },
  { 109, 3 },
  { 109, 2 },
  { 109, 3 },
  { 79, 2 },
  { 92, 4 },
  { 80, 4 },
  { 81, 4 },
  { 110, 1 },
  { 110, 4 },
  { 110, 3 },
  { 111, 1 },
  { 111, 3 },
  { 93, 3 },
  { 93, 3 },
  { 93, 2 },
  { 93, 2 },
  { 93, 2 },
  { 93, 2 },
  { 93, 3 },
  { 93, 3 },
  { 93, 3 },
  { 93, 3 },
  { 93, 3 },
  { 93, 3 },
  { 93, 3 },
  { 93, 3 },
  { 93, 3 },
  { 93, 3 },
  { 112, 1 },
  { 113, 4 },
  { 114, 2 },
  { 115, 2 },
  { 116, 4 },
  { 114, 3 },
  { 117, 1 },
  { 96, 1 },
  { 96, 3 },
  { 118, 1 },
  { 119, 4 },
  { 97, 2 },
  { 120, 2 },
  { 121, 1 },
  { 121, 1 },
  { 121, 1 },
  { 121, 1 },
  { 121, 3 },
  { 122, 1 },
  { 122, 0 },
  { 123, 1 },
  { 123, 3 },
  { 124, 3 },
  { 125, 3 },
  { 126, 3 },
  { 126, 2 },
  { 98, 2 },
  { 127, 2 },
  { 128, 5 },
  { 99, 2 },
  { 100, 1 },
  { 101, 1 },
  { 88, 2 },
  { 109, 4 },
  { 109, 4 },
  { 109, 3 },
  { 129, 5 },
  { 130, 2 },
  { 130, 2 },
  { 131, 0 },
  { 95, 2 },
  { 95, 2 },
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
#line 1353 "parser\\epparser.c"
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
      case 91: /* lexpr ::= expr */ yytestcase(yyruleno==91);
      case 102: /* lexpr ::= LNOT LNOT lexpr */ yytestcase(yyruleno==102);
      case 110: /* lvalueList_nonEmpty ::= lvalue */ yytestcase(yyruleno==110);
#line 76 "parser\\epparser.lemon"
{ yygotominor.yy0 = yymsp[0].minor.yy0; }
#line 1371 "parser\\epparser.c"
        break;
      case 11: /* dottedName ::= dottedName PERIOD NAME */
#line 77 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = yymsp[-2].minor.yy0->data + "." + yymsp[0].minor.yy0->data;
    delete yymsp[-2].minor.yy0;
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1380 "parser\\epparser.c"
        break;
      case 12: /* import_chunk ::= IMPORT dottedName AS NAME */
#line 83 "parser\\epparser.lemon"
{
    if(!ps->closure.defModule(yymsp[0].minor.yy0->data)) {
        throw_error(6754, "Importing already-declared module " + yymsp[0].minor.yy0->data, yymsp[0].minor.yy0->line);
    }
    ps->gen << "import " << impPathProcess(yymsp[-2].minor.yy0->data) << " as " << yymsp[0].minor.yy0->data << std::endl;
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 1391 "parser\\epparser.c"
        break;
      case 13: /* import_chunk ::= IMPORT dottedName */
#line 91 "parser\\epparser.lemon"
{
    std::string modname = impPathGetModule(yymsp[0].minor.yy0->data);
    if(!ps->closure.defModule(modname)) {
        throw_error(6754, "Importing already-declared module " + modname, yymsp[0].minor.yy0->line);
    }
    ps->gen << "import " << impPathProcess(yymsp[0].minor.yy0->data) << " as " << modname << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1403 "parser\\epparser.c"
        break;
      case 14: /* fdef_header ::= FUNCTION NAME LPAREN nameList RPAREN */
#line 101 "parser\\epparser.lemon"
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
#line 1431 "parser\\epparser.c"
        break;
      case 15: /* fdef_chunk ::= fdef_header stmt */
      case 157: /* foreach_stmt ::= foreach_header stmt */ yytestcase(yyruleno==157);
#line 126 "parser\\epparser.lemon"
{
    ps->gen.unindent(true);
    ps->closure.popScope();
}
#line 1440 "parser\\epparser.c"
        break;
      case 16: /* fdecl_chunk ::= FUNCTION NAME LPAREN nameList RPAREN SEMICOLON */
#line 131 "parser\\epparser.lemon"
{
    // Preprocess yymsp[-4].minor.yy0
    funcNamePreprocess(yymsp[-4].minor.yy0->data);
    if(!ps->closure.declareFunction(yymsp[-4].minor.yy0->data)) {
        throw_error(72461, "Declaring function with non-function yymsp[-4].minor.yy0 " + yymsp[-4].minor.yy0->data, yymsp[-4].minor.yy0->line);
    }
}
#line 1451 "parser\\epparser.c"
        break;
      case 17: /* stmt ::= error SEMICOLON */
#line 140 "parser\\epparser.lemon"
{ throw_error(6974, "Error while parsing statement", yymsp[0].minor.yy0->line); delete yymsp[0].minor.yy0; }
#line 1456 "parser\\epparser.c"
        break;
      case 20: /* lbracket ::= LBRACKET */
#line 146 "parser\\epparser.lemon"
{ ps->closure.pushScope(); }
#line 1461 "parser\\epparser.c"
        break;
      case 21: /* rbracket ::= RBRACKET */
#line 147 "parser\\epparser.lemon"
{ ps->closure.popScope(); }
#line 1466 "parser\\epparser.c"
        break;
      case 22: /* blockStmt ::= lbracket RBRACKET */
#line 149 "parser\\epparser.lemon"
{
    ps->gen << "pass" << std::endl;
    ps->closure.popScope();
}
#line 1474 "parser\\epparser.c"
        break;
      case 26: /* blockStmt ::= lbracket error RBRACKET */
#line 156 "parser\\epparser.lemon"
{
    throw_error(6298, "Block not terminated properly.", yymsp[0].minor.yy0->line);
    ps->gen << "pass" << std::endl;
    ps->closure.popScope();
    delete yymsp[0].minor.yy0;
}
#line 1484 "parser\\epparser.c"
        break;
      case 33: /* bodyStmt ::= funcexpr SEMICOLON */
#line 169 "parser\\epparser.lemon"
{ ps->gen << yymsp[-1].minor.yy0->data << std::endl; }
#line 1489 "parser\\epparser.c"
        break;
      case 41: /* bodyStmtList ::= error */
#line 179 "parser\\epparser.lemon"
{
    throw_error(8510, "Incomplete statement");
    ps->gen << "pass" << std::endl;
}
#line 1497 "parser\\epparser.c"
        break;
      case 44: /* bodyStmtList ::= bodyStmtList error */
#line 186 "parser\\epparser.lemon"
{
    throw_error(8510, "Incomplete statement");
}
#line 1504 "parser\\epparser.c"
        break;
      case 46: /* numList_nonEmpty ::= numList_nonEmpty COMMA NUMBER */
      case 48: /* nameList_nonEmpty ::= nameList_nonEmpty COMMA NAME */ yytestcase(yyruleno==48);
      case 111: /* lvalueList_nonEmpty ::= lvalueList_nonEmpty COMMA lvalue */ yytestcase(yyruleno==111);
#line 193 "parser\\epparser.lemon"
{ yygotominor.yy0 = commaConcat(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1511 "parser\\epparser.c"
        break;
      case 49: /* nameList ::= */
      case 55: /* exprList ::= */ yytestcase(yyruleno==55);
      case 66: /* fArgs ::= */ yytestcase(yyruleno==66);
#line 196 "parser\\epparser.lemon"
{ yygotominor.yy0 = genEmpty(); }
#line 1518 "parser\\epparser.c"
        break;
      case 51: /* exprList_nonEmpty ::= funcexpr LSQBRACKET LSQBRACKET numList_nonEmpty RSQBRACKET RSQBRACKET */
#line 199 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "_SRET(" + yymsp[-5].minor.yy0->data + ", [" + yymsp[-2].minor.yy0->data + "])";
    delete yymsp[-5].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1527 "parser\\epparser.c"
        break;
      case 52: /* expr ::= funcexpr LSQBRACKET LSQBRACKET NUMBER RSQBRACKET RSQBRACKET */
#line 206 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-5].minor.yy0->data + "[" + yymsp[-2].minor.yy0->data + "]";
    delete yymsp[-5].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1536 "parser\\epparser.c"
        break;
      case 54: /* exprList_nonEmpty ::= exprList_nonEmpty COMMA exprList_nonEmpty */
#line 214 "parser\\epparser.lemon"
{ yygotominor.yy0 = new Token((yymsp[-2].minor.yy0->data) + ", " + (yymsp[0].minor.yy0->data), yymsp[0].minor.yy0); delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1541 "parser\\epparser.c"
        break;
      case 58: /* expr ::= KILLS */
#line 221 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = "4";
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1549 "parser\\epparser.c"
        break;
      case 59: /* expr ::= NAME */
#line 226 "parser\\epparser.lemon"
{
    checkIsRValue(yymsp[0].minor.yy0->data, yymsp[0].minor.yy0->line);
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1557 "parser\\epparser.c"
        break;
      case 60: /* expr ::= expr PERIOD NAME */
#line 231 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + "." + yymsp[0].minor.yy0->data;
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1566 "parser\\epparser.c"
        break;
      case 61: /* expr ::= expr LSQBRACKET expr RSQBRACKET */
#line 237 "parser\\epparser.lemon"
{
    yymsp[-3].minor.yy0->data = yymsp[-3].minor.yy0->data + "[" + yymsp[-1].minor.yy0->data + "]";
    delete yymsp[-1].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 1575 "parser\\epparser.c"
        break;
      case 64: /* fArgs_nonEmpty ::= NAME ASSIGN expr */
#line 246 "parser\\epparser.lemon"
{  // Keyword argument
    yymsp[0].minor.yy0->data = yymsp[-2].minor.yy0->data + "=" + yymsp[0].minor.yy0->data;
    yymsp[0].minor.yy0->type = TOKEN_TEMP;
    yygotominor.yy0 = yymsp[0].minor.yy0;
    delete yymsp[-2].minor.yy0;
}
#line 1585 "parser\\epparser.c"
        break;
      case 65: /* fArgs_nonEmpty ::= fArgs_nonEmpty COMMA fArgs_nonEmpty */
#line 253 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data;
    yymsp[0].minor.yy0->type = TOKEN_TEMP;
    yygotominor.yy0 = yymsp[0].minor.yy0;
    delete yymsp[-2].minor.yy0;
}
#line 1595 "parser\\epparser.c"
        break;
      case 68: /* funcexpr ::= NAME LPAREN fArgs RPAREN */
#line 263 "parser\\epparser.lemon"
{
    functionCalledInMultipleActions = true;

    // Preprocess yymsp[-3].minor.yy0
    funcNamePreprocess(yymsp[-3].minor.yy0->data);
    checkIsFunction(yymsp[-3].minor.yy0->data, yymsp[-3].minor.yy0->line);
    yymsp[-3].minor.yy0->data += "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 1608 "parser\\epparser.c"
        break;
      case 69: /* funcexpr ::= expr LPAREN fArgs RPAREN */
#line 273 "parser\\epparser.lemon"
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
#line 1632 "parser\\epparser.c"
        break;
      case 71: /* expr ::= LPAREN expr RPAREN */
      case 92: /* lexpr ::= LPAREN lexpr RPAREN */ yytestcase(yyruleno==92);
#line 297 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1641 "parser\\epparser.c"
        break;
      case 72: /* expr ::= LSQBRACKET exprList RSQBRACKET */
#line 302 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "EUDArray(FlattenList([" + yymsp[-1].minor.yy0->data + "]))";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1649 "parser\\epparser.c"
        break;
      case 73: /* expr ::= L2V LPAREN lexpr RPAREN */
#line 307 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "_L2V(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1657 "parser\\epparser.c"
        break;
      case 74: /* expr ::= MAPSTRING LPAREN STRING RPAREN */
#line 312 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetStringIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1665 "parser\\epparser.c"
        break;
      case 75: /* expr ::= UNIT LPAREN STRING RPAREN */
#line 317 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "EncodeUnit(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1673 "parser\\epparser.c"
        break;
      case 76: /* expr ::= SWITCH LPAREN STRING RPAREN */
#line 322 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "EncodeSwitch(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1681 "parser\\epparser.c"
        break;
      case 77: /* expr ::= LOCATION LPAREN STRING RPAREN */
#line 327 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetLocationIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1689 "parser\\epparser.c"
        break;
      case 78: /* expr ::= expr PLUS expr */
#line 333 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "+",  yymsp[0].minor.yy0); }
#line 1694 "parser\\epparser.c"
        break;
      case 79: /* expr ::= expr MINUS expr */
#line 334 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "-",  yymsp[0].minor.yy0); }
#line 1699 "parser\\epparser.c"
        break;
      case 80: /* expr ::= expr MULTIPLY expr */
#line 335 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "*",  yymsp[0].minor.yy0); }
#line 1704 "parser\\epparser.c"
        break;
      case 81: /* expr ::= expr DIVIDE expr */
#line 336 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "//", yymsp[0].minor.yy0); }
#line 1709 "parser\\epparser.c"
        break;
      case 82: /* expr ::= expr MOD expr */
#line 337 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "%",  yymsp[0].minor.yy0); }
#line 1714 "parser\\epparser.c"
        break;
      case 83: /* expr ::= expr LSHIFT expr */
#line 338 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "<<", yymsp[0].minor.yy0); }
#line 1719 "parser\\epparser.c"
        break;
      case 84: /* expr ::= expr RSHIFT expr */
#line 339 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, ">>", yymsp[0].minor.yy0); }
#line 1724 "parser\\epparser.c"
        break;
      case 85: /* expr ::= expr BITAND expr */
#line 340 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "&",  yymsp[0].minor.yy0); }
#line 1729 "parser\\epparser.c"
        break;
      case 86: /* expr ::= expr BITOR expr */
#line 341 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "|",  yymsp[0].minor.yy0); }
#line 1734 "parser\\epparser.c"
        break;
      case 87: /* expr ::= expr BITXOR expr */
#line 342 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "^",  yymsp[0].minor.yy0); }
#line 1739 "parser\\epparser.c"
        break;
      case 88: /* expr ::= PLUS expr */
#line 345 "parser\\epparser.lemon"
{ yymsp[0].minor.yy0->data = "+" + yymsp[0].minor.yy0->data; yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0); }
#line 1744 "parser\\epparser.c"
        break;
      case 89: /* expr ::= MINUS expr */
#line 346 "parser\\epparser.lemon"
{ yymsp[0].minor.yy0->data = "-" + yymsp[0].minor.yy0->data; yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0); }
#line 1749 "parser\\epparser.c"
        break;
      case 90: /* expr ::= BITNOT expr */
#line 347 "parser\\epparser.lemon"
{ yymsp[0].minor.yy0->data = "~" + yymsp[0].minor.yy0->data; yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0); }
#line 1754 "parser\\epparser.c"
        break;
      case 93: /* lexpr ::= expr EQ expr */
#line 357 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "==", yymsp[0].minor.yy0); }
#line 1759 "parser\\epparser.c"
        break;
      case 94: /* lexpr ::= expr NE expr */
#line 358 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "!=", yymsp[0].minor.yy0); }
#line 1764 "parser\\epparser.c"
        break;
      case 95: /* lexpr ::= expr LE expr */
#line 359 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "<=", yymsp[0].minor.yy0); }
#line 1769 "parser\\epparser.c"
        break;
      case 96: /* lexpr ::= expr LT expr */
#line 360 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "<",  yymsp[0].minor.yy0); }
#line 1774 "parser\\epparser.c"
        break;
      case 97: /* lexpr ::= expr GE expr */
#line 361 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, ">=", yymsp[0].minor.yy0); }
#line 1779 "parser\\epparser.c"
        break;
      case 98: /* lexpr ::= expr GT expr */
#line 362 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, ">" , yymsp[0].minor.yy0); }
#line 1784 "parser\\epparser.c"
        break;
      case 99: /* lexpr ::= lexpr LAND lexpr */
#line 365 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genEmpty();
    yygotominor.yy0->line = yymsp[0].minor.yy0->line;

    // Generate data!
    yygotominor.yy0->type = TOKEN_AST_LEXPR_AND;
    yygotominor.yy0->subToken[0] = yymsp[-2].minor.yy0;
    yygotominor.yy0->subToken[1] = yymsp[0].minor.yy0;
    yygotominor.yy0->data = "[" + flatListGetter(yygotominor.yy0, TOKEN_AST_LEXPR_AND) + "]";
}
#line 1798 "parser\\epparser.c"
        break;
      case 100: /* lexpr ::= lexpr LOR lexpr */
#line 377 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genEmpty();
    yygotominor.yy0->line = yymsp[0].minor.yy0->line;

    // Generate data!
    yygotominor.yy0->type = TOKEN_AST_LEXPR_OR;
    yygotominor.yy0->subToken[0] = yymsp[-2].minor.yy0;
    yygotominor.yy0->subToken[1] = yymsp[0].minor.yy0;
    yygotominor.yy0->data = "EUDOr(" + flatListGetter(yygotominor.yy0, TOKEN_AST_LEXPR_OR) + ")";
}
#line 1812 "parser\\epparser.c"
        break;
      case 101: /* lexpr ::= LNOT lexpr */
#line 388 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = "EUDNot([" + yymsp[0].minor.yy0->data + "])";
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0);
}
#line 1820 "parser\\epparser.c"
        break;
      case 103: /* vdef_stmt ::= VAR nameList_nonEmpty */
#line 398 "parser\\epparser.lemon"
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
#line 1844 "parser\\epparser.c"
        break;
      case 104: /* vdefAssign_stmt ::= VAR nameList_nonEmpty ASSIGN exprList_nonEmpty */
#line 419 "parser\\epparser.lemon"
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
#line 1869 "parser\\epparser.c"
        break;
      case 105: /* vdefAssign_global_stmt ::= VAR nameList_nonEmpty ASSIGN exprList_nonEmpty */
#line 441 "parser\\epparser.lemon"
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
#line 1893 "parser\\epparser.c"
        break;
      case 106: /* cdef_stmt ::= CONST nameList_nonEmpty ASSIGN exprList_nonEmpty */
#line 462 "parser\\epparser.lemon"
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
#line 1915 "parser\\epparser.c"
        break;
      case 107: /* lvalue ::= NAME */
#line 482 "parser\\epparser.lemon"
{
    checkIsVariable(yymsp[0].minor.yy0->data, yymsp[0].minor.yy0->line);
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1923 "parser\\epparser.c"
        break;
      case 108: /* lvalue ::= expr LSQBRACKET expr RSQBRACKET */
#line 487 "parser\\epparser.lemon"
{
    checkIsConstant(yymsp[-3].minor.yy0->data, yymsp[-3].minor.yy0->line);
    yymsp[-1].minor.yy0->data = "_ARRW(" + yymsp[-3].minor.yy0->data + ", " + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
    delete yymsp[-3].minor.yy0;
}
#line 1933 "parser\\epparser.c"
        break;
      case 109: /* lvalue ::= expr PERIOD NAME */
#line 494 "parser\\epparser.lemon"
{
    checkIsConstant(yymsp[-2].minor.yy0->data, yymsp[-2].minor.yy0->line);
    yymsp[0].minor.yy0->data = "_ATTW(" + yymsp[-2].minor.yy0->data + ", '" + yymsp[0].minor.yy0->data + "')";
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0);
    delete yymsp[-2].minor.yy0;
}
#line 1943 "parser\\epparser.c"
        break;
      case 112: /* assign_stmt ::= lvalue ASSIGN expr */
#line 503 "parser\\epparser.lemon"
{
    ps->gen << yymsp[-2].minor.yy0->data << " << (" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 1951 "parser\\epparser.c"
        break;
      case 113: /* assign_stmt ::= lvalueList_nonEmpty ASSIGN exprList_nonEmpty */
#line 508 "parser\\epparser.lemon"
{
    ps->gen << "_SV([" << yymsp[-2].minor.yy0->data << "], [" << yymsp[0].minor.yy0->data << "])" << std::endl;
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 1959 "parser\\epparser.c"
        break;
      case 114: /* assign_stmt ::= INC expr */
#line 516 "parser\\epparser.lemon"
{ ps->gen << yymsp[0].minor.yy0->data << ".__iadd__(1)" << std::endl; delete yymsp[0].minor.yy0; }
#line 1964 "parser\\epparser.c"
        break;
      case 115: /* assign_stmt ::= expr INC */
#line 517 "parser\\epparser.lemon"
{ ps->gen << yymsp[-1].minor.yy0->data << ".__iadd__(1)" << std::endl; delete yymsp[-1].minor.yy0; }
#line 1969 "parser\\epparser.c"
        break;
      case 116: /* assign_stmt ::= DEC expr */
#line 518 "parser\\epparser.lemon"
{ ps->gen << yymsp[0].minor.yy0->data << ".__isub__(1)" << std::endl; delete yymsp[0].minor.yy0; }
#line 1974 "parser\\epparser.c"
        break;
      case 117: /* assign_stmt ::= expr DEC */
#line 519 "parser\\epparser.lemon"
{ ps->gen << yymsp[-1].minor.yy0->data << ".__isub__(1)" << std::endl; delete yymsp[-1].minor.yy0; }
#line 1979 "parser\\epparser.c"
        break;
      case 118: /* assign_stmt ::= lvalue IADD expr */
#line 520 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__iadd__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1984 "parser\\epparser.c"
        break;
      case 119: /* assign_stmt ::= lvalue ISUB expr */
#line 521 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__isub__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1989 "parser\\epparser.c"
        break;
      case 120: /* assign_stmt ::= lvalue IMUL expr */
#line 522 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__imul__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1994 "parser\\epparser.c"
        break;
      case 121: /* assign_stmt ::= lvalue IDIV expr */
#line 523 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ifloordiv__("  << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1999 "parser\\epparser.c"
        break;
      case 122: /* assign_stmt ::= lvalue IMOD expr */
#line 524 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__imod__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2004 "parser\\epparser.c"
        break;
      case 123: /* assign_stmt ::= lvalue ILSH expr */
#line 525 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ilshift__("    << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2009 "parser\\epparser.c"
        break;
      case 124: /* assign_stmt ::= lvalue IRSH expr */
#line 526 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__irshift__("    << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2014 "parser\\epparser.c"
        break;
      case 125: /* assign_stmt ::= lvalue IBND expr */
#line 527 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__iand__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2019 "parser\\epparser.c"
        break;
      case 126: /* assign_stmt ::= lvalue IBOR expr */
#line 528 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ior__("        << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2024 "parser\\epparser.c"
        break;
      case 127: /* assign_stmt ::= lvalue IBXR expr */
#line 529 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ixor__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2029 "parser\\epparser.c"
        break;
      case 128: /* if_start ::= IF */
#line 532 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDIf()" << std::endl;
}
#line 2037 "parser\\epparser.c"
        break;
      case 129: /* if_header ::= if_start LPAREN lexpr RPAREN */
      case 138: /* while_header ::= while_start LPAREN lexpr RPAREN */ yytestcase(yyruleno==138);
#line 537 "parser\\epparser.lemon"
{
    ps->gen << "if " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data << "):" << std::endl;
    ps->gen.indent();
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 2047 "parser\\epparser.c"
        break;
      case 131: /* elif_start ::= ELSE IF */
#line 545 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen.unindent(false);
    ps->gen << yygotominor.yy0->data << " = EUDElseIf()" << std::endl;
}
#line 2056 "parser\\epparser.c"
        break;
      case 132: /* elif_header ::= elif_start LPAREN lexpr RPAREN */
#line 551 "parser\\epparser.lemon"
{
    ps->gen << "if " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data <<"):" << std::endl;
    ps->gen.indent();
}
#line 2064 "parser\\epparser.c"
        break;
      case 134: /* else_header ::= ELSE */
#line 558 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "if EUDElse()():" << std::endl;
    ps->gen.indent();
}
#line 2073 "parser\\epparser.c"
        break;
      case 135: /* if_stmt ::= if_block */
      case 136: /* if_stmt ::= if_block else_header stmt */ yytestcase(yyruleno==136);
#line 564 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndIf()" << std::endl;
}
#line 2082 "parser\\epparser.c"
        break;
      case 137: /* while_start ::= WHILE */
#line 576 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDWhile()" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2091 "parser\\epparser.c"
        break;
      case 139: /* while_stmt ::= while_header stmt */
#line 588 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndWhile()" << std::endl;
}
#line 2099 "parser\\epparser.c"
        break;
      case 140: /* for_opener ::= FOR LPAREN */
      case 155: /* foreach_opener ::= FOREACH LPAREN */ yytestcase(yyruleno==155);
#line 594 "parser\\epparser.lemon"
{
    ps->closure.pushScope();
}
#line 2107 "parser\\epparser.c"
        break;
      case 150: /* for_header1 ::= for_opener for_init_stmt SEMICOLON */
#line 610 "parser\\epparser.lemon"
{
    // opening for lexpr
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDWhile()" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2117 "parser\\epparser.c"
        break;
      case 151: /* for_header2 ::= for_header1 lexpr SEMICOLON */
#line 617 "parser\\epparser.lemon"
{
    ps->gen << "if " << yymsp[-2].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data << "):" << std::endl;
    ps->gen.indent();
    delete yymsp[-2].minor.yy0; delete yymsp[-1].minor.yy0;

    // Opening for assign_statement
    yygotominor.yy0 = genTemp(yymsp[-1].minor.yy0);
    ps->gen << "def " << yygotominor.yy0->data <<"():" << std::endl;
    ps->gen.indent();
}
#line 2131 "parser\\epparser.c"
        break;
      case 152: /* for_header ::= for_header2 for_action_stmt_nonEmpty RPAREN */
#line 628 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-2].minor.yy0;
    ps->gen.unindent(false);
}
#line 2139 "parser\\epparser.c"
        break;
      case 153: /* for_header ::= for_header2 RPAREN */
#line 633 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
    ps->gen << "pass" << std::endl;
    ps->gen.unindent(false);
}
#line 2148 "parser\\epparser.c"
        break;
      case 154: /* for_stmt ::= for_header stmt */
#line 639 "parser\\epparser.lemon"
{
    ps->gen << "EUDSetContinuePoint()" << std::endl;
    ps->gen << yymsp[-1].minor.yy0->data << "()" << std::endl;
    ps->gen.unindent(false);
    ps->gen << "EUDEndWhile()" << std::endl;
    ps->closure.popScope();
}
#line 2159 "parser\\epparser.c"
        break;
      case 156: /* foreach_header ::= foreach_opener nameList_nonEmpty COLON exprList_nonEmpty RPAREN */
#line 654 "parser\\epparser.lemon"
{
    commaListIter(yymsp[-3].minor.yy0->data, [&](std::string& s) {
        ps->closure.defVariable(s);
    });
    ps->gen << "for " << yymsp[-3].minor.yy0->data << " in " << yymsp[-1].minor.yy0->data << ":" << std::endl;
    ps->gen.indent();
}
#line 2170 "parser\\epparser.c"
        break;
      case 158: /* continue_stmt ::= CONTINUE */
#line 670 "parser\\epparser.lemon"
{
    ps->gen << "EUDContinue()" << std::endl;
}
#line 2177 "parser\\epparser.c"
        break;
      case 159: /* break_stmt ::= BREAK */
#line 674 "parser\\epparser.lemon"
{
    ps->gen << "EUDBreak()" << std::endl;
}
#line 2184 "parser\\epparser.c"
        break;
      case 160: /* return_stmt ::= RETURN exprList */
#line 681 "parser\\epparser.lemon"
{
    ps->gen << "EUDReturn(" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2192 "parser\\epparser.c"
        break;
      case 161: /* lexpr ::= CONDITIONNAME LPAREN fArgs RPAREN */
      case 162: /* lexpr ::= KILLS LPAREN fArgs RPAREN */ yytestcase(yyruleno==162);
#line 689 "parser\\epparser.lemon"
{
    yymsp[-3].minor.yy0->data = yymsp[-3].minor.yy0->data + "(" + yymsp[-1].minor.yy0->data + ")";
    delete yymsp[-1].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 2202 "parser\\epparser.c"
        break;
      case 163: /* lexpr ::= CONDITIONNAME LPAREN RPAREN */
#line 701 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + "()";
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 2210 "parser\\epparser.c"
        break;
      case 164: /* action ::= ACTIONNAME LPAREN fArgs RPAREN SEMICOLON */
#line 706 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[-4].minor.yy0);
    yygotominor.yy0->data =  yymsp[-4].minor.yy0->data + "(" + yymsp[-2].minor.yy0->data + ")";
    delete yymsp[-4].minor.yy0; delete yymsp[-2].minor.yy0;
}
#line 2219 "parser\\epparser.c"
        break;
      case 165: /* actions ::= action action */
      case 166: /* actions ::= actions action */ yytestcase(yyruleno==166);
#line 712 "parser\\epparser.lemon"
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
#line 2242 "parser\\epparser.c"
        break;
      case 167: /* actionStmt_start ::= */
#line 750 "parser\\epparser.lemon"
{
    functionCalledInMultipleActions = false;
}
#line 2249 "parser\\epparser.c"
        break;
      case 168: /* actionStmt ::= actionStmt_start action */
#line 754 "parser\\epparser.lemon"
{
    ps->gen << "DoActions(" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2257 "parser\\epparser.c"
        break;
      case 169: /* actionStmt ::= actionStmt_start actions */
#line 759 "parser\\epparser.lemon"
{
    ps->gen << "DoActions([" << std::endl;
    ps->gen.indent();
    ps->gen << yymsp[0].minor.yy0->data << std::endl;
    ps->gen.unindent(false);
    ps->gen << "])" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2269 "parser\\epparser.c"
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
      /* (130) if_block ::= if_header stmt */ yytestcase(yyruleno==130);
      /* (133) if_block ::= if_block elif_header stmt */ yytestcase(yyruleno==133);
      /* (141) for_init_stmt_nonEmpty ::= vdef_stmt */ yytestcase(yyruleno==141);
      /* (142) for_init_stmt_nonEmpty ::= vdefAssign_stmt */ yytestcase(yyruleno==142);
      /* (143) for_init_stmt_nonEmpty ::= cdef_stmt */ yytestcase(yyruleno==143);
      /* (144) for_init_stmt_nonEmpty ::= assign_stmt */ yytestcase(yyruleno==144);
      /* (145) for_init_stmt_nonEmpty ::= for_init_stmt_nonEmpty COMMA for_init_stmt_nonEmpty */ yytestcase(yyruleno==145);
      /* (146) for_init_stmt ::= for_init_stmt_nonEmpty */ yytestcase(yyruleno==146);
      /* (147) for_init_stmt ::= */ yytestcase(yyruleno==147);
      /* (148) for_action_stmt_nonEmpty ::= assign_stmt */ yytestcase(yyruleno==148);
      /* (149) for_action_stmt_nonEmpty ::= for_action_stmt_nonEmpty COMMA for_action_stmt_nonEmpty */ yytestcase(yyruleno==149);
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
#line 2360 "parser\\epparser.c"
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
#line 773 "parser\\epparser.lemon"


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
#line 2614 "parser\\epparser.c"
