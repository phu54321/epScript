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
#define YYNOCODE 126
#define YYACTIONTYPE unsigned short int
#define ParseTOKENTYPE Token*
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  int yy251;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL  ParserStruct* ps ;
#define ParseARG_PDECL , ParserStruct* ps 
#define ParseARG_FETCH  ParserStruct* ps  = yypParser->ps 
#define ParseARG_STORE yypParser->ps  = ps 
#define YYNSTATE 300
#define YYNRULE 151
#define YYERRORSYMBOL 68
#define YYERRSYMDT yy251
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
#define YY_ACTTAB_COUNT (1195)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   196,   27,   28,   35,  199,   17,  182,  192,  190,   70,
 /*    10 */   298,  180,  289,  287,  195,    2,  105,  279,  258,  191,
 /*    20 */   189,  135,  271,  270,  269,  268,  267,  184,  183,  201,
 /*    30 */   249,   97,  222,  182,   27,   28,  110,  131,  149,    8,
 /*    40 */    37,  175,  296,   97,  146,    6,   10,  295,  110,  131,
 /*    50 */    21,   13,    5,   75,    4,   74,   73,  196,   27,   28,
 /*    60 */   199,  221,   81,  238,  192,  190,  147,    7,    3,  237,
 /*    70 */   287,  195,    2,  294,  279,  174,  191,  189,  135,  271,
 /*    80 */   270,  269,  268,  267,  184,  183,  199,  235,   97,  222,
 /*    90 */   182,   27,   28,  110,  131,  149,    8,   37,   34,  199,
 /*   100 */    97,  146,    6,   10,  292,  110,  131,   21,   13,    5,
 /*   110 */    75,    4,   74,   73,  196,  187,  291,   14,  130,   36,
 /*   120 */   232,  192,  190,   71,   27,   28,  234,  287,  195,    2,
 /*   130 */   185,  279,  288,  191,  189,  135,  271,  270,  269,  268,
 /*   140 */   267,  184,  183,   32,   33,   97,  178,  220,  223,  216,
 /*   150 */   110,  131,  149,    8,   37,  173,  104,  156,  146,    6,
 /*   160 */    10,  272,  182,  286,   21,   13,    5,   75,    4,   74,
 /*   170 */    73,  196,  105,  273,  179,  154,  293,  199,  192,  190,
 /*   180 */    80,  188,  290,  231,  287,  195,    2,  188,  279,  186,
 /*   190 */   191,  189,  135,  271,  270,  269,  268,  267,  184,  183,
 /*   200 */    79,  277,   97,  178,  452,   12,  276,  110,  131,  149,
 /*   210 */     8,   37,  173,  104,  212,  146,    6,   10,  275,  182,
 /*   220 */   274,   21,   13,    5,   75,    4,   74,   73,  196,  105,
 /*   230 */   266,  179,  155,  265,  182,  192,  190,   31,   18,  261,
 /*   240 */   218,  287,  195,    2,   85,  279,  177,  191,  189,  135,
 /*   250 */   271,  270,  269,  268,  267,  184,  183,   30,   78,   97,
 /*   260 */   178,  182,  256,  255,  110,  131,  149,    8,   37,  254,
 /*   270 */   104,   82,  146,    6,   10,  121,  182,   36,   21,   13,
 /*   280 */     5,   75,    4,   74,   73,  196,  105,   29,  179,  140,
 /*   290 */   170,  169,  192,  190,  253,  167,  166,  215,  287,  195,
 /*   300 */     2,  252,  279,  164,  191,  189,  135,  271,  270,  269,
 /*   310 */   268,  267,  184,  183,  163,  251,   97,  178,  182,  161,
 /*   320 */   160,  110,  131,  149,    8,   37,  152,  104,   82,  146,
 /*   330 */     6,   10,  248,  182,  182,   21,   13,    5,   75,    4,
 /*   340 */    74,   73,  196,  105,   84,  179,  157,  250,   28,  192,
 /*   350 */   190,   15,  243,  245,  208,  287,  195,    2,  242,  279,
 /*   360 */   241,  191,  189,  135,  271,  270,  269,  268,  267,  184,
 /*   370 */   183,  108,   24,   97,  178,  182,  236,   23,  110,  131,
 /*   380 */   149,    8,   37,  151,  104,   97,  146,    6,   10,   11,
 /*   390 */   240,   22,   21,   13,    5,   75,    4,   74,   73,  138,
 /*   400 */   178,  182,  230,  224,  217,   16,  192,  190,  211,  150,
 /*   410 */   104,   82,  206,  194,    2,  159,  279,    1,  191,  189,
 /*   420 */   135,  271,  270,  269,  268,  267,  184,  183,  139,  207,
 /*   430 */    97,  178,  182,  200,  293,  110,  131,  149,    8,   37,
 /*   440 */   128,  104,   82,  146,    6,   10,  247,  182,  282,   21,
 /*   450 */    13,    5,   75,    4,   74,   73,  263,   82,  182,  283,
 /*   460 */   134,  246,  280,  192,  190,  176,  133,  132,  116,  264,
 /*   470 */   193,    2,  281,  279,  129,  191,  189,  135,  271,  270,
 /*   480 */   269,  268,  267,  184,  183,  210,  141,   97,  182,  182,
 /*   490 */   209,  137,  110,  131,  149,    8,   37,  136,  115,  127,
 /*   500 */   146,    6,   10,  229,  227,  148,   21,   13,    5,   75,
 /*   510 */     4,   74,   73,   57,   56,  228,  226,  182,  300,   55,
 /*   520 */   262,  106,  278,  453,  453,  453,   69,   97,  285,  284,
 /*   530 */    20,  453,  110,  131,  453,  172,  171,  168,  165,  162,
 /*   540 */    77,   76,  453,  144,  143,  453,  202,  182,  198,  453,
 /*   550 */   453,  453,  239,  453,  233,  145,  142,   82,  214,  213,
 /*   560 */    19,  120,  141,   72,   76,  182,  182,  453,  453,  453,
 /*   570 */   453,   57,   56,  182,  453,  126,  125,   55,  262,  106,
 /*   580 */   278,  453,  182,  114,   69,  453,  285,  283,   20,  453,
 /*   590 */   453,  453,  113,  172,  171,  168,  165,  162,   77,   76,
 /*   600 */   299,  205,  297,  204,  203,  182,  197,    9,  453,  453,
 /*   610 */   239,  182,  233,  145,  142,   82,  214,  213,   19,  119,
 /*   620 */   141,   82,  182,  182,  453,  118,  453,  453,  453,   57,
 /*   630 */    56,  182,  112,  109,  453,   55,  262,  106,  278,  453,
 /*   640 */   453,   82,   69,  453,  285,  117,   20,  453,  182,  182,
 /*   650 */   182,  172,  171,  168,  165,  162,   77,   76,  111,  103,
 /*   660 */   124,  453,  453,  182,  453,  453,  453,  182,  239,  453,
 /*   670 */   233,  145,  142,  123,  214,  213,   19,  122,  141,   58,
 /*   680 */    53,   52,   51,   50,   54,   60,   59,   61,   63,   62,
 /*   690 */    68,   67,   65,   66,   64,   63,   62,   68,   67,   65,
 /*   700 */    66,   64,  182,   17,  453,  182,  453,   70,  453,  180,
 /*   710 */    17,  453,  102,  453,   70,  101,  180,   60,   59,   61,
 /*   720 */    63,   62,   68,   67,   65,   66,   64,  182,  182,   68,
 /*   730 */    67,   65,   66,   64,  182,   17,  453,  100,   99,   70,
 /*   740 */   260,  180,   17,  453,   98,  453,   70,  453,  180,   60,
 /*   750 */    59,   61,   63,   62,   68,   67,   65,   66,   64,  453,
 /*   760 */   182,   65,   66,   64,  182,  182,  453,   17,  257,  182,
 /*   770 */    83,   70,   17,  180,   96,   95,   70,  453,  180,   94,
 /*   780 */   453,   60,   59,   61,   63,   62,   68,   67,   65,   66,
 /*   790 */    64,  182,  182,   26,  453,  453,  453,  229,  227,   17,
 /*   800 */   453,   93,   92,   70,  107,  180,   57,   56,  182,  228,
 /*   810 */   226,  182,   55,  262,  181,  182,  453,  453,   91,   69,
 /*   820 */    25,   97,  453,   20,  453,   90,  110,  131,  172,  171,
 /*   830 */   168,  165,  162,   57,   56,  453,  453,  225,  182,   55,
 /*   840 */   262,  181,  182,  182,  453,  453,   69,  453,   89,  453,
 /*   850 */    20,  453,   88,   87,  158,  172,  171,  168,  165,  162,
 /*   860 */    57,   56,  182,  453,  453,  453,   55,  262,  181,  453,
 /*   870 */   453,  453,   86,   69,  244,  453,  453,   20,  453,  453,
 /*   880 */   259,  158,  172,  171,  168,  165,  162,   57,   56,  453,
 /*   890 */   453,  453,  453,   55,  262,  106,  453,  453,  453,  453,
 /*   900 */    69,  453,  453,  453,   20,  453,  453,  453,  453,  172,
 /*   910 */   171,  168,  165,  162,   77,   76,  453,  453,  350,  350,
 /*   920 */   350,  350,  350,  350,  350,  350,  350,  350,  453,  453,
 /*   930 */   453,  453,  453,  453,  453,  453,   18,  453,  453,  453,
 /*   940 */   350,  453,  350,  453,  453,  453,  453,  453,  453,  453,
 /*   950 */    60,   59,   61,   63,   62,   68,   67,   65,   66,   64,
 /*   960 */   453,  453,  453,  453,  453,  453,  453,  453,   17,  453,
 /*   970 */   453,  453,   70,  453,  180,  453,  453,  453,  453,  453,
 /*   980 */   453,  453,   60,   59,   61,   63,   62,   68,   67,   65,
 /*   990 */    66,   64,  453,  453,  453,  453,  453,  453,  453,  453,
 /*  1000 */    17,   57,   56,  453,   49,  453,  153,   55,  262,  181,
 /*  1010 */   453,  453,  453,  453,   69,  453,  453,  453,   20,  453,
 /*  1020 */   453,  259,  453,  172,  171,  168,  165,  162,   57,   56,
 /*  1030 */   453,  453,  453,  453,   55,  262,  106,  396,  396,  453,
 /*  1040 */   453,   69,  219,  453,  453,   20,  453,  395,  395,  453,
 /*  1050 */   172,  171,  168,  165,  162,  453,   59,   61,   63,   62,
 /*  1060 */    68,   67,   65,   66,   64,  453,  453,  453,  453,  453,
 /*  1070 */   453,  453,  453,   17,  453,  453,  453,   70,  453,  180,
 /*  1080 */   453,  453,  453,  396,  396,  396,  396,  396,  396,  396,
 /*  1090 */   396,  396,  396,  395,  395,  395,  395,  395,  395,  395,
 /*  1100 */   395,  395,  395,   57,   56,  453,  453,  453,  453,   55,
 /*  1110 */   262,  181,  453,  453,  453,  453,   69,  453,  453,  453,
 /*  1120 */    20,  453,  453,  453,  453,  172,  171,  168,  165,  162,
 /*  1130 */    57,   56,  453,  453,  453,  453,   55,  262,  106,   48,
 /*  1140 */   453,  453,  453,   69,  453,  453,  453,   20,  453,  453,
 /*  1150 */   453,  453,  172,  171,  168,  165,  162,  453,  453,   61,
 /*  1160 */    63,   62,   68,   67,   65,   66,   64,  453,  453,  453,
 /*  1170 */   453,  453,  453,  453,  453,   17,  453,  453,  453,   70,
 /*  1180 */   453,  180,  453,  453,  453,   47,   46,   45,   44,   43,
 /*  1190 */    42,   41,   40,   39,   38,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    68,    3,    4,    1,    2,   31,   89,   75,   76,   35,
 /*    10 */    27,   37,   80,   81,   82,   83,   99,   85,  101,   87,
 /*    20 */    88,   89,   90,   91,   92,   93,   94,   95,   96,   26,
 /*    30 */    32,   99,   88,   89,    3,    4,  104,  105,  106,  107,
 /*    40 */   108,    2,   27,   99,  112,  113,  114,   27,  104,  105,
 /*    50 */   118,  119,  120,  121,  122,  123,  124,   68,    3,    4,
 /*    60 */     2,  117,   29,   32,   75,   76,  109,  110,  111,   80,
 /*    70 */    81,   82,   83,   26,   85,   36,   87,   88,   89,   90,
 /*    80 */    91,   92,   93,   94,   95,   96,    2,   32,   99,   88,
 /*    90 */    89,    3,    4,  104,  105,  106,  107,  108,    1,    2,
 /*   100 */    99,  112,  113,  114,   26,  104,  105,  118,  119,  120,
 /*   110 */   121,  122,  123,  124,   68,   35,   32,    2,  117,    2,
 /*   120 */    32,   75,   76,   31,    3,    4,   80,   81,   82,   83,
 /*   130 */    36,   85,   27,   87,   88,   89,   90,   91,   92,   93,
 /*   140 */    94,   95,   96,    1,    2,   99,   89,   32,   27,   32,
 /*   150 */   104,  105,  106,  107,  108,   98,   99,  100,  112,  113,
 /*   160 */   114,   36,   89,   27,  118,  119,  120,  121,  122,  123,
 /*   170 */   124,   68,   99,   27,  101,  102,   26,    2,   75,   76,
 /*   180 */    27,   35,   32,   80,   81,   82,   83,   35,   85,   25,
 /*   190 */    87,   88,   89,   90,   91,   92,   93,   94,   95,   96,
 /*   200 */    27,   27,   99,   89,   70,   71,   27,  104,  105,  106,
 /*   210 */   107,  108,   98,   99,  100,  112,  113,  114,   27,   89,
 /*   220 */    27,  118,  119,  120,  121,  122,  123,  124,   68,   99,
 /*   230 */    27,  101,  102,   27,   89,   75,   76,   62,   31,   26,
 /*   240 */    80,   81,   82,   83,   99,   85,   35,   87,   88,   89,
 /*   250 */    90,   91,   92,   93,   94,   95,   96,    2,   35,   99,
 /*   260 */    89,   89,   25,   36,  104,  105,  106,  107,  108,   98,
 /*   270 */    99,   99,  112,  113,  114,  103,   89,    2,  118,  119,
 /*   280 */   120,  121,  122,  123,  124,   68,   99,   31,  101,  102,
 /*   290 */    31,   38,   75,   76,   32,   31,   38,   80,   81,   82,
 /*   300 */    83,   32,   85,   31,   87,   88,   89,   90,   91,   92,
 /*   310 */    93,   94,   95,   96,   38,   32,   99,   89,   89,   31,
 /*   320 */    38,  104,  105,  106,  107,  108,   98,   99,   99,  112,
 /*   330 */   113,  114,  103,   89,   89,  118,  119,  120,  121,  122,
 /*   340 */   123,  124,   68,   99,   99,  101,  102,   32,    4,   75,
 /*   350 */    76,   31,   36,   32,   80,   81,   82,   83,   32,   85,
 /*   360 */    32,   87,   88,   89,   90,   91,   92,   93,   94,   95,
 /*   370 */    96,   26,   31,   99,   89,   89,   57,   31,  104,  105,
 /*   380 */   106,  107,  108,   98,   99,   99,  112,  113,  114,    2,
 /*   390 */   104,   31,  118,  119,  120,  121,  122,  123,  124,   68,
 /*   400 */    89,   89,   31,   27,   31,   31,   75,   76,   27,   98,
 /*   410 */    99,   99,   81,   82,   83,  103,   85,   86,   87,   88,
 /*   420 */    89,   90,   91,   92,   93,   94,   95,   96,   32,   34,
 /*   430 */    99,   89,   89,   77,   26,  104,  105,  106,  107,  108,
 /*   440 */    98,   99,   99,  112,  113,  114,  103,   89,   84,  118,
 /*   450 */   119,  120,  121,  122,  123,  124,   68,   99,   89,   34,
 /*   460 */    97,  103,   84,   75,   76,   25,   77,   77,   99,   81,
 /*   470 */    82,   83,   84,   85,   77,   87,   88,   89,   90,   91,
 /*   480 */    92,   93,   94,   95,   96,  123,   67,   99,   89,   89,
 /*   490 */   123,   77,  104,  105,  106,  107,  108,   77,   99,   99,
 /*   500 */   112,  113,  114,   75,   76,   58,  118,  119,  120,  121,
 /*   510 */   122,  123,  124,   18,   19,   87,   88,   89,    0,   24,
 /*   520 */    25,   26,   27,  125,  125,  125,   31,   99,   33,   34,
 /*   530 */    35,  125,  104,  105,  125,   40,   41,   42,   43,   44,
 /*   540 */    45,   46,  125,  115,  116,  125,   28,   89,   30,  125,
 /*   550 */   125,  125,   57,  125,   59,   60,   61,   99,   63,   64,
 /*   560 */    65,  103,   67,   45,   46,   89,   89,  125,  125,  125,
 /*   570 */   125,   18,   19,   89,  125,   99,   99,   24,   25,   26,
 /*   580 */    27,  125,   89,   99,   31,  125,   33,   34,   35,  125,
 /*   590 */   125,  125,   99,   40,   41,   42,   43,   44,   45,   46,
 /*   600 */    72,   73,   74,   75,   76,   89,   78,   79,  125,  125,
 /*   610 */    57,   89,   59,   60,   61,   99,   63,   64,   65,  103,
 /*   620 */    67,   99,   89,   89,  125,  103,  125,  125,  125,   18,
 /*   630 */    19,   89,   99,   99,  125,   24,   25,   26,   27,  125,
 /*   640 */   125,   99,   31,  125,   33,  103,   35,  125,   89,   89,
 /*   650 */    89,   40,   41,   42,   43,   44,   45,   46,   99,   99,
 /*   660 */    99,  125,  125,   89,  125,  125,  125,   89,   57,  125,
 /*   670 */    59,   60,   61,   99,   63,   64,   65,   99,   67,    7,
 /*   680 */     8,    9,   10,   11,   12,   13,   14,   15,   16,   17,
 /*   690 */    18,   19,   20,   21,   22,   16,   17,   18,   19,   20,
 /*   700 */    21,   22,   89,   31,  125,   89,  125,   35,  125,   37,
 /*   710 */    31,  125,   99,  125,   35,   99,   37,   13,   14,   15,
 /*   720 */    16,   17,   18,   19,   20,   21,   22,   89,   89,   18,
 /*   730 */    19,   20,   21,   22,   89,   31,  125,   99,   99,   35,
 /*   740 */    36,   37,   31,  125,   99,  125,   35,  125,   37,   13,
 /*   750 */    14,   15,   16,   17,   18,   19,   20,   21,   22,  125,
 /*   760 */    89,   20,   21,   22,   89,   89,  125,   31,   32,   89,
 /*   770 */    99,   35,   31,   37,   99,   99,   35,  125,   37,   99,
 /*   780 */   125,   13,   14,   15,   16,   17,   18,   19,   20,   21,
 /*   790 */    22,   89,   89,    5,  125,  125,  125,   75,   76,   31,
 /*   800 */   125,   99,   99,   35,   36,   37,   18,   19,   89,   87,
 /*   810 */    88,   89,   24,   25,   26,   89,  125,  125,   99,   31,
 /*   820 */     5,   99,  125,   35,  125,   99,  104,  105,   40,   41,
 /*   830 */    42,   43,   44,   18,   19,  125,  125,  115,   89,   24,
 /*   840 */    25,   26,   89,   89,  125,  125,   31,  125,   99,  125,
 /*   850 */    35,  125,   99,   99,   66,   40,   41,   42,   43,   44,
 /*   860 */    18,   19,   89,  125,  125,  125,   24,   25,   26,  125,
 /*   870 */   125,  125,   99,   31,   32,  125,  125,   35,  125,  125,
 /*   880 */    38,   66,   40,   41,   42,   43,   44,   18,   19,  125,
 /*   890 */   125,  125,  125,   24,   25,   26,  125,  125,  125,  125,
 /*   900 */    31,  125,  125,  125,   35,  125,  125,  125,  125,   40,
 /*   910 */    41,   42,   43,   44,   45,   46,  125,  125,   13,   14,
 /*   920 */    15,   16,   17,   18,   19,   20,   21,   22,  125,  125,
 /*   930 */   125,  125,  125,  125,  125,  125,   31,  125,  125,  125,
 /*   940 */    35,  125,   37,  125,  125,  125,  125,  125,  125,  125,
 /*   950 */    13,   14,   15,   16,   17,   18,   19,   20,   21,   22,
 /*   960 */   125,  125,  125,  125,  125,  125,  125,  125,   31,  125,
 /*   970 */   125,  125,   35,  125,   37,  125,  125,  125,  125,  125,
 /*   980 */   125,  125,   13,   14,   15,   16,   17,   18,   19,   20,
 /*   990 */    21,   22,  125,  125,  125,  125,  125,  125,  125,  125,
 /*  1000 */    31,   18,   19,  125,   35,  125,   37,   24,   25,   26,
 /*  1010 */   125,  125,  125,  125,   31,  125,  125,  125,   35,  125,
 /*  1020 */   125,   38,  125,   40,   41,   42,   43,   44,   18,   19,
 /*  1030 */   125,  125,  125,  125,   24,   25,   26,    1,    2,  125,
 /*  1040 */   125,   31,   32,  125,  125,   35,  125,    1,    2,  125,
 /*  1050 */    40,   41,   42,   43,   44,  125,   14,   15,   16,   17,
 /*  1060 */    18,   19,   20,   21,   22,  125,  125,  125,  125,  125,
 /*  1070 */   125,  125,  125,   31,  125,  125,  125,   35,  125,   37,
 /*  1080 */   125,  125,  125,   47,   48,   49,   50,   51,   52,   53,
 /*  1090 */    54,   55,   56,   47,   48,   49,   50,   51,   52,   53,
 /*  1100 */    54,   55,   56,   18,   19,  125,  125,  125,  125,   24,
 /*  1110 */    25,   26,  125,  125,  125,  125,   31,  125,  125,  125,
 /*  1120 */    35,  125,  125,  125,  125,   40,   41,   42,   43,   44,
 /*  1130 */    18,   19,  125,  125,  125,  125,   24,   25,   26,    1,
 /*  1140 */   125,  125,  125,   31,  125,  125,  125,   35,  125,  125,
 /*  1150 */   125,  125,   40,   41,   42,   43,   44,  125,  125,   15,
 /*  1160 */    16,   17,   18,   19,   20,   21,   22,  125,  125,  125,
 /*  1170 */   125,  125,  125,  125,  125,   31,  125,  125,  125,   35,
 /*  1180 */   125,   37,  125,  125,  125,   47,   48,   49,   50,   51,
 /*  1190 */    52,   53,   54,   55,   56,
};
#define YY_SHIFT_USE_DFLT (-27)
#define YY_SHIFT_COUNT (205)
#define YY_SHIFT_MIN   (-26)
#define YY_SHIFT_MAX   (1144)
static const short yy_shift_ofst[] = {
 /*     0 */   -27,  553,  495,  611,  611,  611,  611,  611,  611,  611,
 /*    10 */   869,  869,  518, 1010, 1112,  842,  983,  983,  983, 1085,
 /*    20 */  1085,  788,  788,  788,  788,  815,  815,  788,  788,  788,
 /*    30 */   983, 1085, 1085, 1112, 1085, 1085, 1085,  447, 1085, 1085,
 /*    40 */  1085, 1085, 1085, 1085, 1085, 1085, 1085, 1085, 1085, 1085,
 /*    50 */  1085, 1085, 1085, 1085, 1085, 1085, 1085, 1085, 1085, 1085,
 /*    60 */  1085, 1085, 1085, 1085, 1085, 1085, 1085, 1085, 1085, 1085,
 /*    70 */  1085,  150,  408,  419,  419,  408,  408,  408,  440,  425,
 /*    80 */   425,  408,  672,  768,  736,  704,  937,  937,  937,  937,
 /*    90 */   937,  937,  937,  937,  937,  937,  937,  969,  937,  937,
 /*   100 */   937,  937,  937,  937,  937,  937,  905, 1046, 1036, 1042,
 /*   110 */  1138, 1144,  679,  711,  711,  741,  741,  121,   88,   55,
 /*   120 */    31,   -2,  -26,  -26,  -26,  -26,  -26,  -26,  117,  175,
 /*   130 */   115,  142,   97,    2,   39,  146,   84,   58,  395,  381,
 /*   140 */   396,  374,  373,  376,  387,  371,  360,  346,  319,  341,
 /*   150 */   275,  275,  275,  345,  328,  326,  316,  321,  320,  344,
 /*   160 */   315,  282,  288,  283,  276,  272,  269,  258,  264,  262,
 /*   170 */   253,  259,  256,  275,  227,  237,   94,  223,  211,  255,
 /*   180 */   213,  207,  152,  206,  203,  125,   94,  164,   80,  193,
 /*   190 */   191,  179,  174,  173,  153,  136,  105,   92,   78,   47,
 /*   200 */    58,   33,    3,   20,   15,  -17,
};
#define YY_REDUCE_USE_DFLT (-84)
#define YY_REDUCE_COUNT (81)
#define YY_REDUCE_MIN   (-83)
#define YY_REDUCE_MAX   (773)
static const short yy_reduce_ofst[] = {
 /*     0 */   134,  388,  331,  274,  217,  160,  103,   46,  -11,  -68,
 /*    10 */   428,  722,  528,    1,  -56,  244,  187,  130,   73,  114,
 /*    20 */    57,  542,  522,  516,  458,  358,  343,  312,  229,  172,
 /*    30 */   -83,  342,  311,  286,  285,  228,  171,  -43,  773,  754,
 /*    40 */   753,  749,  726,  719,  703,  702,  680,  676,  675,  671,
 /*    50 */   645,  639,  638,  616,  613,  578,  574,  561,  560,  559,
 /*    60 */   534,  533,  493,  484,  477,  476,  400,  399,  369,  245,
 /*    70 */   145,  420,  414,  367,  362,  397,  390,  389,  363,  378,
 /*    80 */   364,  356,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   301,  451,  451,  451,  451,  451,  451,  451,  451,  451,
 /*    10 */   430,  451,  451,  451,  451,  451,  356,  356,  356,  347,
 /*    20 */   347,  451,  451,  451,  451,  451,  451,  451,  451,  451,
 /*    30 */   451,  451,  451,  451,  451,  451,  451,  418,  451,  451,
 /*    40 */   451,  451,  451,  451,  451,  451,  451,  451,  451,  451,
 /*    50 */   451,  451,  451,  451,  451,  451,  451,  451,  451,  451,
 /*    60 */   451,  451,  451,  451,  451,  451,  451,  451,  451,  451,
 /*    70 */   451,  451,  451,  450,  449,  451,  451,  451,  451,  451,
 /*    80 */   451,  451,  451,  451,  451,  451,  410,  409,  408,  407,
 /*    90 */   406,  405,  404,  403,  402,  401,  399,  451,  386,  385,
 /*   100 */   384,  383,  382,  381,  345,  353,  394,  352,  351,  376,
 /*   110 */   397,  377,  375,  374,  373,  369,  368,  451,  451,  451,
 /*   120 */   451,  451,  380,  379,  378,  372,  371,  370,  451,  451,
 /*   130 */   451,  451,  451,  391,  451,  360,  451,  391,  451,  451,
 /*   140 */   451,  451,  451,  451,  429,  451,  451,  451,  417,  451,
 /*   150 */   400,  393,  392,  451,  451,  451,  451,  451,  451,  388,
 /*   160 */   451,  451,  451,  451,  451,  451,  451,  451,  451,  451,
 /*   170 */   451,  451,  451,  348,  451,  451,  339,  451,  360,  357,
 /*   180 */   451,  350,  360,  451,  451,  451,  451,  451,  451,  451,
 /*   190 */   451,  451,  451,  451,  451,  451,  451,  451,  451,  451,
 /*   200 */   307,  451,  451,  451,  451,  451,  336,  321,  419,  448,
 /*   210 */   447,  446,  443,  442,  441,  440,  439,  438,  437,  436,
 /*   220 */   435,  432,  431,  434,  433,  428,  427,  426,  425,  424,
 /*   230 */   423,  422,  421,  420,  416,  415,  414,  413,  412,  411,
 /*   240 */   398,  358,  359,  362,  445,  444,  390,  389,  387,  363,
 /*   250 */   367,  366,  365,  364,  346,  343,  340,  361,  355,  354,
 /*   260 */   352,  351,  349,  338,  337,  335,  334,  333,  332,  331,
 /*   270 */   330,  329,  344,  328,  327,  326,  325,  324,  323,  322,
 /*   280 */   320,  319,  318,  316,  317,  315,  314,  313,  312,  311,
 /*   290 */   310,  309,  308,  341,  342,  306,  305,  304,  303,  302,
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
  "RSQBRACKET",    "PERIOD",        "STRING",        "FUNCCALL",    
  "L2V",           "MAPSTRING",     "UNIT",          "SWITCH",      
  "LOCATION",      "VAR",           "CONST",         "IADD",        
  "ISUB",          "IMUL",          "IDIV",          "IMOD",        
  "ILSH",          "IRSH",          "IBND",          "IBOR",        
  "IBXR",          "IF",            "ELSE",          "WHILE",       
  "FOR",           "FOREACH",       "COLON",         "CONTINUE",    
  "BREAK",         "RETURN",        "CONDITIONNAME",  "ACTIONNAME",  
  "error",         "nt",            "program",       "chunks",      
  "chunk",         "import_chunk",  "fdef_chunk",    "vdef_stmt",   
  "cdef_stmt",     "nameList_nonEmpty",  "function_start",  "function_header",
  "stmt",          "bodyStmt",      "return_stmt",   "lbracket",    
  "rbracket",      "blockStmt",     "bodyStmtList",  "vdefAssign_stmt",
  "assign_stmt",   "funcexpr",      "actionStmt",    "if_stmt",     
  "while_stmt",    "for_stmt",      "foreach_stmt",  "continue_stmt",
  "break_stmt",    "numList_nonEmpty",  "exprList_nonEmpty",  "expr",        
  "exprList",      "fArgs_nonEmpty",  "fArgs",         "lexpr",       
  "lvalue",        "lvalueList_nonEmpty",  "if_start",      "if_header",   
  "if_block",      "elif_start",    "elif_header",   "else_header", 
  "while_start",   "while_header",  "for_opener",    "for_init_stmt_nonEmpty",
  "for_init_stmt",  "for_action_stmt_nonEmpty",  "for_header1",   "for_header2", 
  "for_header",    "foreach_opener",  "foreach_header",  "action",      
  "actions",     
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
 /*  50 */ "expr ::= NAME",
 /*  51 */ "expr ::= expr PERIOD NAME",
 /*  52 */ "expr ::= expr LSQBRACKET expr RSQBRACKET",
 /*  53 */ "fArgs_nonEmpty ::= expr",
 /*  54 */ "fArgs_nonEmpty ::= STRING",
 /*  55 */ "fArgs_nonEmpty ::= fArgs_nonEmpty COMMA fArgs_nonEmpty",
 /*  56 */ "fArgs ::=",
 /*  57 */ "fArgs ::= fArgs_nonEmpty",
 /*  58 */ "funcexpr ::= NAME LPAREN fArgs RPAREN",
 /*  59 */ "funcexpr ::= expr LPAREN fArgs RPAREN",
 /*  60 */ "expr ::= funcexpr",
 /*  61 */ "expr ::= LPAREN expr RPAREN",
 /*  62 */ "expr ::= LSQBRACKET exprList RSQBRACKET",
 /*  63 */ "expr ::= L2V LPAREN lexpr RPAREN",
 /*  64 */ "expr ::= MAPSTRING LPAREN STRING RPAREN",
 /*  65 */ "expr ::= UNIT LPAREN STRING RPAREN",
 /*  66 */ "expr ::= SWITCH LPAREN STRING RPAREN",
 /*  67 */ "expr ::= LOCATION LPAREN STRING RPAREN",
 /*  68 */ "expr ::= expr PLUS expr",
 /*  69 */ "expr ::= expr MINUS expr",
 /*  70 */ "expr ::= expr MULTIPLY expr",
 /*  71 */ "expr ::= expr DIVIDE expr",
 /*  72 */ "expr ::= expr MOD expr",
 /*  73 */ "expr ::= expr LSHIFT expr",
 /*  74 */ "expr ::= expr RSHIFT expr",
 /*  75 */ "expr ::= expr BITAND expr",
 /*  76 */ "expr ::= expr BITOR expr",
 /*  77 */ "expr ::= expr BITXOR expr",
 /*  78 */ "expr ::= PLUS expr",
 /*  79 */ "expr ::= MINUS expr",
 /*  80 */ "expr ::= BITNOT expr",
 /*  81 */ "lexpr ::= expr EQ expr",
 /*  82 */ "lexpr ::= expr NE expr",
 /*  83 */ "lexpr ::= expr LE expr",
 /*  84 */ "lexpr ::= expr LT expr",
 /*  85 */ "lexpr ::= expr GE expr",
 /*  86 */ "lexpr ::= expr GT expr",
 /*  87 */ "lexpr ::= lexpr LAND lexpr",
 /*  88 */ "lexpr ::= lexpr LOR lexpr",
 /*  89 */ "lexpr ::= LNOT lexpr",
 /*  90 */ "lexpr ::= LNOT LNOT lexpr",
 /*  91 */ "vdef_stmt ::= VAR nameList_nonEmpty",
 /*  92 */ "vdefAssign_stmt ::= VAR nameList_nonEmpty ASSIGN exprList_nonEmpty",
 /*  93 */ "cdef_stmt ::= CONST nameList_nonEmpty ASSIGN exprList_nonEmpty",
 /*  94 */ "lvalue ::= NAME",
 /*  95 */ "lvalue ::= expr LSQBRACKET expr RSQBRACKET",
 /*  96 */ "lvalue ::= expr PERIOD NAME",
 /*  97 */ "lvalueList_nonEmpty ::= lvalue",
 /*  98 */ "lvalueList_nonEmpty ::= lvalueList_nonEmpty COMMA lvalue",
 /*  99 */ "assign_stmt ::= lvalue ASSIGN expr",
 /* 100 */ "assign_stmt ::= lvalueList_nonEmpty ASSIGN exprList_nonEmpty",
 /* 101 */ "assign_stmt ::= lvalue IADD expr",
 /* 102 */ "assign_stmt ::= lvalue ISUB expr",
 /* 103 */ "assign_stmt ::= lvalue IMUL expr",
 /* 104 */ "assign_stmt ::= lvalue IDIV expr",
 /* 105 */ "assign_stmt ::= lvalue IMOD expr",
 /* 106 */ "assign_stmt ::= lvalue ILSH expr",
 /* 107 */ "assign_stmt ::= lvalue IRSH expr",
 /* 108 */ "assign_stmt ::= lvalue IBND expr",
 /* 109 */ "assign_stmt ::= lvalue IBOR expr",
 /* 110 */ "assign_stmt ::= lvalue IBXR expr",
 /* 111 */ "if_start ::= IF",
 /* 112 */ "if_header ::= if_start LPAREN lexpr RPAREN",
 /* 113 */ "if_block ::= if_header stmt",
 /* 114 */ "elif_start ::= ELSE IF",
 /* 115 */ "elif_header ::= elif_start LPAREN lexpr RPAREN",
 /* 116 */ "if_block ::= if_block elif_header stmt",
 /* 117 */ "else_header ::= ELSE",
 /* 118 */ "if_stmt ::= if_block",
 /* 119 */ "if_stmt ::= if_block else_header stmt",
 /* 120 */ "while_start ::= WHILE",
 /* 121 */ "while_header ::= while_start LPAREN lexpr RPAREN",
 /* 122 */ "while_stmt ::= while_header stmt",
 /* 123 */ "for_opener ::= FOR LPAREN",
 /* 124 */ "for_init_stmt_nonEmpty ::= vdef_stmt",
 /* 125 */ "for_init_stmt_nonEmpty ::= vdefAssign_stmt",
 /* 126 */ "for_init_stmt_nonEmpty ::= cdef_stmt",
 /* 127 */ "for_init_stmt_nonEmpty ::= assign_stmt",
 /* 128 */ "for_init_stmt_nonEmpty ::= for_init_stmt_nonEmpty COMMA for_init_stmt_nonEmpty",
 /* 129 */ "for_init_stmt ::= for_init_stmt_nonEmpty",
 /* 130 */ "for_init_stmt ::=",
 /* 131 */ "for_action_stmt_nonEmpty ::= assign_stmt",
 /* 132 */ "for_action_stmt_nonEmpty ::= for_action_stmt_nonEmpty COMMA for_action_stmt_nonEmpty",
 /* 133 */ "for_header1 ::= for_opener for_init_stmt SEMICOLON",
 /* 134 */ "for_header2 ::= for_header1 lexpr SEMICOLON",
 /* 135 */ "for_header ::= for_header2 for_action_stmt_nonEmpty RPAREN",
 /* 136 */ "for_header ::= for_header2 RPAREN",
 /* 137 */ "for_stmt ::= for_header stmt",
 /* 138 */ "foreach_opener ::= FOREACH LPAREN",
 /* 139 */ "foreach_header ::= foreach_opener nameList_nonEmpty COLON exprList_nonEmpty RPAREN",
 /* 140 */ "foreach_stmt ::= foreach_header stmt",
 /* 141 */ "continue_stmt ::= CONTINUE",
 /* 142 */ "break_stmt ::= BREAK",
 /* 143 */ "return_stmt ::= RETURN exprList",
 /* 144 */ "lexpr ::= CONDITIONNAME LPAREN fArgs RPAREN",
 /* 145 */ "lexpr ::= CONDITIONNAME LPAREN RPAREN",
 /* 146 */ "action ::= ACTIONNAME LPAREN fArgs RPAREN SEMICOLON",
 /* 147 */ "actions ::= action action",
 /* 148 */ "actions ::= actions action",
 /* 149 */ "actionStmt ::= action",
 /* 150 */ "actionStmt ::= actions",
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
    case 69: /* nt */
{
#line 31 "parser\\epparser.lemon"
 delete (yypminor->yy0); 
#line 849 "parser\\epparser.c"
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
  { 70, 1 },
  { 71, 0 },
  { 71, 2 },
  { 72, 2 },
  { 72, 1 },
  { 72, 2 },
  { 72, 2 },
  { 73, 4 },
  { 78, 2 },
  { 79, 4 },
  { 79, 3 },
  { 74, 2 },
  { 80, 2 },
  { 80, 1 },
  { 80, 2 },
  { 83, 1 },
  { 84, 1 },
  { 85, 2 },
  { 85, 4 },
  { 85, 3 },
  { 85, 5 },
  { 85, 3 },
  { 81, 1 },
  { 81, 1 },
  { 81, 2 },
  { 81, 2 },
  { 81, 2 },
  { 81, 2 },
  { 81, 2 },
  { 81, 1 },
  { 81, 1 },
  { 81, 1 },
  { 81, 1 },
  { 81, 1 },
  { 81, 2 },
  { 81, 2 },
  { 86, 1 },
  { 86, 2 },
  { 86, 2 },
  { 97, 1 },
  { 97, 3 },
  { 77, 1 },
  { 77, 3 },
  { 98, 6 },
  { 99, 6 },
  { 98, 1 },
  { 98, 3 },
  { 100, 0 },
  { 100, 1 },
  { 99, 1 },
  { 99, 1 },
  { 99, 3 },
  { 99, 4 },
  { 101, 1 },
  { 101, 1 },
  { 101, 3 },
  { 102, 0 },
  { 102, 1 },
  { 89, 4 },
  { 89, 4 },
  { 99, 1 },
  { 99, 3 },
  { 99, 3 },
  { 99, 4 },
  { 99, 4 },
  { 99, 4 },
  { 99, 4 },
  { 99, 4 },
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
  { 99, 2 },
  { 99, 2 },
  { 99, 2 },
  { 103, 3 },
  { 103, 3 },
  { 103, 3 },
  { 103, 3 },
  { 103, 3 },
  { 103, 3 },
  { 103, 3 },
  { 103, 3 },
  { 103, 2 },
  { 103, 3 },
  { 75, 2 },
  { 87, 4 },
  { 76, 4 },
  { 104, 1 },
  { 104, 4 },
  { 104, 3 },
  { 105, 1 },
  { 105, 3 },
  { 88, 3 },
  { 88, 3 },
  { 88, 3 },
  { 88, 3 },
  { 88, 3 },
  { 88, 3 },
  { 88, 3 },
  { 88, 3 },
  { 88, 3 },
  { 88, 3 },
  { 88, 3 },
  { 88, 3 },
  { 106, 1 },
  { 107, 4 },
  { 108, 2 },
  { 109, 2 },
  { 110, 4 },
  { 108, 3 },
  { 111, 1 },
  { 91, 1 },
  { 91, 3 },
  { 112, 1 },
  { 113, 4 },
  { 92, 2 },
  { 114, 2 },
  { 115, 1 },
  { 115, 1 },
  { 115, 1 },
  { 115, 1 },
  { 115, 3 },
  { 116, 1 },
  { 116, 0 },
  { 117, 1 },
  { 117, 3 },
  { 118, 3 },
  { 119, 3 },
  { 120, 3 },
  { 120, 2 },
  { 93, 2 },
  { 121, 2 },
  { 122, 5 },
  { 94, 2 },
  { 95, 1 },
  { 96, 1 },
  { 82, 2 },
  { 103, 4 },
  { 103, 3 },
  { 123, 5 },
  { 124, 2 },
  { 124, 2 },
  { 90, 1 },
  { 90, 1 },
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
#line 1304 "parser\\epparser.c"
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
#line 1317 "parser\\epparser.c"
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
#line 1336 "parser\\epparser.c"
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
#line 1347 "parser\\epparser.c"
        break;
      case 11: /* fdef_chunk ::= function_header stmt */
      case 140: /* foreach_stmt ::= foreach_header stmt */ yytestcase(yyruleno==140);
#line 112 "parser\\epparser.lemon"
{
    ps->gen.unindent(true);
    ps->closure.popScope();
}
#line 1356 "parser\\epparser.c"
        break;
      case 12: /* stmt ::= error SEMICOLON */
#line 119 "parser\\epparser.lemon"
{ throw_error(6974, "Error while parsing statement"); }
#line 1361 "parser\\epparser.c"
        break;
      case 15: /* lbracket ::= LBRACKET */
#line 125 "parser\\epparser.lemon"
{ ps->closure.pushScope(); }
#line 1366 "parser\\epparser.c"
        break;
      case 16: /* rbracket ::= RBRACKET */
#line 126 "parser\\epparser.lemon"
{ ps->closure.popScope(); }
#line 1371 "parser\\epparser.c"
        break;
      case 17: /* blockStmt ::= lbracket RBRACKET */
#line 128 "parser\\epparser.lemon"
{
    ps->gen << "pass" << std::endl;
    ps->closure.popScope();
}
#line 1379 "parser\\epparser.c"
        break;
      case 21: /* blockStmt ::= lbracket error RBRACKET */
#line 135 "parser\\epparser.lemon"
{
    throw_error(6298, "Block not terminated properly.");
    ps->closure.popScope();
}
#line 1387 "parser\\epparser.c"
        break;
      case 28: /* bodyStmt ::= funcexpr SEMICOLON */
#line 146 "parser\\epparser.lemon"
{ ps->gen << yymsp[-1].minor.yy0->data << std::endl; }
#line 1392 "parser\\epparser.c"
        break;
      case 38: /* bodyStmtList ::= bodyStmtList error */
#line 158 "parser\\epparser.lemon"
{
    throw_error(8510, "Incomplete statement");
}
#line 1399 "parser\\epparser.c"
        break;
      case 39: /* numList_nonEmpty ::= NUMBER */
      case 41: /* nameList_nonEmpty ::= NAME */ yytestcase(yyruleno==41);
      case 45: /* exprList_nonEmpty ::= expr */ yytestcase(yyruleno==45);
      case 48: /* exprList ::= exprList_nonEmpty */ yytestcase(yyruleno==48);
      case 49: /* expr ::= NUMBER */ yytestcase(yyruleno==49);
      case 53: /* fArgs_nonEmpty ::= expr */ yytestcase(yyruleno==53);
      case 54: /* fArgs_nonEmpty ::= STRING */ yytestcase(yyruleno==54);
      case 57: /* fArgs ::= fArgs_nonEmpty */ yytestcase(yyruleno==57);
      case 60: /* expr ::= funcexpr */ yytestcase(yyruleno==60);
      case 90: /* lexpr ::= LNOT LNOT lexpr */ yytestcase(yyruleno==90);
      case 97: /* lvalueList_nonEmpty ::= lvalue */ yytestcase(yyruleno==97);
#line 164 "parser\\epparser.lemon"
{ yygotominor.yy0 = yymsp[0].minor.yy0; }
#line 1414 "parser\\epparser.c"
        break;
      case 40: /* numList_nonEmpty ::= numList_nonEmpty COMMA NUMBER */
      case 42: /* nameList_nonEmpty ::= nameList_nonEmpty COMMA NAME */ yytestcase(yyruleno==42);
      case 98: /* lvalueList_nonEmpty ::= lvalueList_nonEmpty COMMA lvalue */ yytestcase(yyruleno==98);
#line 165 "parser\\epparser.lemon"
{ yygotominor.yy0 = commaConcat(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1421 "parser\\epparser.c"
        break;
      case 43: /* exprList_nonEmpty ::= funcexpr LSQBRACKET LSQBRACKET numList_nonEmpty RSQBRACKET RSQBRACKET */
#line 169 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "_SRET(" + yymsp[-5].minor.yy0->data + ", [" + yymsp[-2].minor.yy0->data + "])";
    delete yymsp[-5].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1430 "parser\\epparser.c"
        break;
      case 44: /* expr ::= funcexpr LSQBRACKET LSQBRACKET NUMBER RSQBRACKET RSQBRACKET */
#line 176 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-5].minor.yy0->data + "[" + yymsp[-2].minor.yy0->data + "]";
    delete yymsp[-5].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1439 "parser\\epparser.c"
        break;
      case 46: /* exprList_nonEmpty ::= exprList_nonEmpty COMMA exprList_nonEmpty */
#line 184 "parser\\epparser.lemon"
{ yygotominor.yy0 = new Token((yymsp[-2].minor.yy0->data) + ", " + (yymsp[0].minor.yy0->data), yymsp[0].minor.yy0); delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1444 "parser\\epparser.c"
        break;
      case 47: /* exprList ::= */
      case 56: /* fArgs ::= */ yytestcase(yyruleno==56);
#line 186 "parser\\epparser.lemon"
{ yygotominor.yy0 = genEmpty(); }
#line 1450 "parser\\epparser.c"
        break;
      case 50: /* expr ::= NAME */
#line 191 "parser\\epparser.lemon"
{
    checkIsRValue(yymsp[0].minor.yy0->data);
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1458 "parser\\epparser.c"
        break;
      case 51: /* expr ::= expr PERIOD NAME */
#line 196 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + "." + yymsp[0].minor.yy0->data;
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1467 "parser\\epparser.c"
        break;
      case 52: /* expr ::= expr LSQBRACKET expr RSQBRACKET */
#line 202 "parser\\epparser.lemon"
{
    yymsp[-3].minor.yy0->data = yymsp[-3].minor.yy0->data + "[" + yymsp[-1].minor.yy0->data + "]";
    delete yymsp[-1].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 1476 "parser\\epparser.c"
        break;
      case 55: /* fArgs_nonEmpty ::= fArgs_nonEmpty COMMA fArgs_nonEmpty */
#line 211 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data;
    yymsp[-2].minor.yy0->type = TOKEN_TEMP;
    yygotominor.yy0 = yymsp[-2].minor.yy0;
    delete yymsp[0].minor.yy0;
}
#line 1486 "parser\\epparser.c"
        break;
      case 58: /* funcexpr ::= NAME LPAREN fArgs RPAREN */
#line 221 "parser\\epparser.lemon"
{
    // Preprocess yymsp[-3].minor.yy0
    funcNamePreprocess(yymsp[-3].minor.yy0->data);
    checkIsFunction(yymsp[-3].minor.yy0->data);
    yymsp[-3].minor.yy0->data += "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 1497 "parser\\epparser.c"
        break;
      case 59: /* funcexpr ::= expr LPAREN fArgs RPAREN */
#line 229 "parser\\epparser.lemon"
{
    // Preprocess yymsp[-3].minor.yy0
    yymsp[-3].minor.yy0->data += "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 1506 "parser\\epparser.c"
        break;
      case 61: /* expr ::= LPAREN expr RPAREN */
#line 238 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1514 "parser\\epparser.c"
        break;
      case 62: /* expr ::= LSQBRACKET exprList RSQBRACKET */
#line 243 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "EUDArray(FlattenList[" + yymsp[-1].minor.yy0->data + "])";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1522 "parser\\epparser.c"
        break;
      case 63: /* expr ::= L2V LPAREN lexpr RPAREN */
#line 248 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "_L2V(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = genTemp(yymsp[-1].minor.yy0);
}
#line 1530 "parser\\epparser.c"
        break;
      case 64: /* expr ::= MAPSTRING LPAREN STRING RPAREN */
#line 253 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetStringIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1538 "parser\\epparser.c"
        break;
      case 65: /* expr ::= UNIT LPAREN STRING RPAREN */
#line 258 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "EncodeUnit(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1546 "parser\\epparser.c"
        break;
      case 66: /* expr ::= SWITCH LPAREN STRING RPAREN */
#line 263 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "EncodeSwitch(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1554 "parser\\epparser.c"
        break;
      case 67: /* expr ::= LOCATION LPAREN STRING RPAREN */
#line 268 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetLocationIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1562 "parser\\epparser.c"
        break;
      case 68: /* expr ::= expr PLUS expr */
#line 274 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "+",  yymsp[0].minor.yy0); }
#line 1567 "parser\\epparser.c"
        break;
      case 69: /* expr ::= expr MINUS expr */
#line 275 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "-",  yymsp[0].minor.yy0); }
#line 1572 "parser\\epparser.c"
        break;
      case 70: /* expr ::= expr MULTIPLY expr */
#line 276 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "*",  yymsp[0].minor.yy0); }
#line 1577 "parser\\epparser.c"
        break;
      case 71: /* expr ::= expr DIVIDE expr */
#line 277 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "//", yymsp[0].minor.yy0); }
#line 1582 "parser\\epparser.c"
        break;
      case 72: /* expr ::= expr MOD expr */
#line 278 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "%",  yymsp[0].minor.yy0); }
#line 1587 "parser\\epparser.c"
        break;
      case 73: /* expr ::= expr LSHIFT expr */
#line 279 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<<", yymsp[0].minor.yy0); }
#line 1592 "parser\\epparser.c"
        break;
      case 74: /* expr ::= expr RSHIFT expr */
#line 280 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">>", yymsp[0].minor.yy0); }
#line 1597 "parser\\epparser.c"
        break;
      case 75: /* expr ::= expr BITAND expr */
#line 281 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "&",  yymsp[0].minor.yy0); }
#line 1602 "parser\\epparser.c"
        break;
      case 76: /* expr ::= expr BITOR expr */
#line 282 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "|",  yymsp[0].minor.yy0); }
#line 1607 "parser\\epparser.c"
        break;
      case 77: /* expr ::= expr BITXOR expr */
#line 283 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "^",  yymsp[0].minor.yy0); }
#line 1612 "parser\\epparser.c"
        break;
      case 78: /* expr ::= PLUS expr */
#line 286 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = +" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1617 "parser\\epparser.c"
        break;
      case 79: /* expr ::= MINUS expr */
#line 287 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = -" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1622 "parser\\epparser.c"
        break;
      case 80: /* expr ::= BITNOT expr */
#line 288 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = ~" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1627 "parser\\epparser.c"
        break;
      case 81: /* lexpr ::= expr EQ expr */
#line 292 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "==", yymsp[0].minor.yy0); }
#line 1632 "parser\\epparser.c"
        break;
      case 82: /* lexpr ::= expr NE expr */
#line 293 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "!=", yymsp[0].minor.yy0); }
#line 1637 "parser\\epparser.c"
        break;
      case 83: /* lexpr ::= expr LE expr */
#line 294 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<=", yymsp[0].minor.yy0); }
#line 1642 "parser\\epparser.c"
        break;
      case 84: /* lexpr ::= expr LT expr */
#line 295 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<",  yymsp[0].minor.yy0); }
#line 1647 "parser\\epparser.c"
        break;
      case 85: /* lexpr ::= expr GE expr */
#line 296 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">=", yymsp[0].minor.yy0); }
#line 1652 "parser\\epparser.c"
        break;
      case 86: /* lexpr ::= expr GT expr */
#line 297 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">" , yymsp[0].minor.yy0); }
#line 1657 "parser\\epparser.c"
        break;
      case 87: /* lexpr ::= lexpr LAND lexpr */
#line 299 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "[" + yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data + "]";
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1666 "parser\\epparser.c"
        break;
      case 88: /* lexpr ::= lexpr LOR lexpr */
#line 305 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "EUDOr([" + yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data + "])";
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1675 "parser\\epparser.c"
        break;
      case 89: /* lexpr ::= LNOT lexpr */
#line 311 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = "EUDNot([" + yymsp[0].minor.yy0->data + "])";
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0);
}
#line 1683 "parser\\epparser.c"
        break;
      case 91: /* vdef_stmt ::= VAR nameList_nonEmpty */
#line 321 "parser\\epparser.lemon"
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
#line 1707 "parser\\epparser.c"
        break;
      case 92: /* vdefAssign_stmt ::= VAR nameList_nonEmpty ASSIGN exprList_nonEmpty */
#line 342 "parser\\epparser.lemon"
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
#line 1732 "parser\\epparser.c"
        break;
      case 93: /* cdef_stmt ::= CONST nameList_nonEmpty ASSIGN exprList_nonEmpty */
#line 364 "parser\\epparser.lemon"
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
#line 1754 "parser\\epparser.c"
        break;
      case 94: /* lvalue ::= NAME */
#line 384 "parser\\epparser.lemon"
{
    checkIsVariable(yymsp[0].minor.yy0->data);
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1762 "parser\\epparser.c"
        break;
      case 95: /* lvalue ::= expr LSQBRACKET expr RSQBRACKET */
#line 389 "parser\\epparser.lemon"
{
    checkIsConstant(yymsp[-3].minor.yy0->data);
    yymsp[-1].minor.yy0->data = "_ARRW(" + yymsp[-3].minor.yy0->data + ", " + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
    delete yymsp[-3].minor.yy0;
}
#line 1772 "parser\\epparser.c"
        break;
      case 96: /* lvalue ::= expr PERIOD NAME */
#line 396 "parser\\epparser.lemon"
{
    checkIsConstant(yymsp[-2].minor.yy0->data);
    yymsp[0].minor.yy0->data = "_ATTW(" + yymsp[-2].minor.yy0->data + ", '" + yymsp[0].minor.yy0->data + "')";
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0);
    delete yymsp[-2].minor.yy0;
}
#line 1782 "parser\\epparser.c"
        break;
      case 99: /* assign_stmt ::= lvalue ASSIGN expr */
#line 405 "parser\\epparser.lemon"
{
    ps->gen << yymsp[-2].minor.yy0->data << " << (" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 1790 "parser\\epparser.c"
        break;
      case 100: /* assign_stmt ::= lvalueList_nonEmpty ASSIGN exprList_nonEmpty */
#line 410 "parser\\epparser.lemon"
{
    ps->gen << "_SV([" << yymsp[-2].minor.yy0->data << "], [" << yymsp[0].minor.yy0->data << "])" << std::endl;
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 1798 "parser\\epparser.c"
        break;
      case 101: /* assign_stmt ::= lvalue IADD expr */
#line 418 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__iadd__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1803 "parser\\epparser.c"
        break;
      case 102: /* assign_stmt ::= lvalue ISUB expr */
#line 419 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__isub__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1808 "parser\\epparser.c"
        break;
      case 103: /* assign_stmt ::= lvalue IMUL expr */
#line 420 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__imul__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1813 "parser\\epparser.c"
        break;
      case 104: /* assign_stmt ::= lvalue IDIV expr */
#line 421 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ifloordiv__("  << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1818 "parser\\epparser.c"
        break;
      case 105: /* assign_stmt ::= lvalue IMOD expr */
#line 422 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__imod__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1823 "parser\\epparser.c"
        break;
      case 106: /* assign_stmt ::= lvalue ILSH expr */
#line 423 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ilshift__("    << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1828 "parser\\epparser.c"
        break;
      case 107: /* assign_stmt ::= lvalue IRSH expr */
#line 424 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__irshift__("    << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1833 "parser\\epparser.c"
        break;
      case 108: /* assign_stmt ::= lvalue IBND expr */
#line 425 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__iand__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1838 "parser\\epparser.c"
        break;
      case 109: /* assign_stmt ::= lvalue IBOR expr */
#line 426 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ior__("        << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1843 "parser\\epparser.c"
        break;
      case 110: /* assign_stmt ::= lvalue IBXR expr */
#line 427 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ixor__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1848 "parser\\epparser.c"
        break;
      case 111: /* if_start ::= IF */
#line 430 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDIf()" << std::endl;
}
#line 1856 "parser\\epparser.c"
        break;
      case 112: /* if_header ::= if_start LPAREN lexpr RPAREN */
      case 121: /* while_header ::= while_start LPAREN lexpr RPAREN */ yytestcase(yyruleno==121);
#line 434 "parser\\epparser.lemon"
{
    ps->gen << "if " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data << "):" << std::endl;
    ps->gen.indent();
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1866 "parser\\epparser.c"
        break;
      case 114: /* elif_start ::= ELSE IF */
#line 442 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen.unindent(false);
    ps->gen << yygotominor.yy0->data << " = EUDElseIf()" << std::endl;
}
#line 1875 "parser\\epparser.c"
        break;
      case 115: /* elif_header ::= elif_start LPAREN lexpr RPAREN */
#line 448 "parser\\epparser.lemon"
{
    ps->gen << "if " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data <<"):" << std::endl;
    ps->gen.indent();
}
#line 1883 "parser\\epparser.c"
        break;
      case 117: /* else_header ::= ELSE */
#line 455 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "if EUDElse()():" << std::endl;
    ps->gen.indent();
}
#line 1892 "parser\\epparser.c"
        break;
      case 118: /* if_stmt ::= if_block */
      case 119: /* if_stmt ::= if_block else_header stmt */ yytestcase(yyruleno==119);
#line 461 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndIf()" << std::endl;
}
#line 1901 "parser\\epparser.c"
        break;
      case 120: /* while_start ::= WHILE */
#line 473 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDWhile()" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1910 "parser\\epparser.c"
        break;
      case 122: /* while_stmt ::= while_header stmt */
#line 485 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndWhile()" << std::endl;
}
#line 1918 "parser\\epparser.c"
        break;
      case 123: /* for_opener ::= FOR LPAREN */
      case 138: /* foreach_opener ::= FOREACH LPAREN */ yytestcase(yyruleno==138);
#line 491 "parser\\epparser.lemon"
{
    ps->closure.pushScope();
}
#line 1926 "parser\\epparser.c"
        break;
      case 133: /* for_header1 ::= for_opener for_init_stmt SEMICOLON */
#line 507 "parser\\epparser.lemon"
{
    // opening for lexpr
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDWhile()" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1936 "parser\\epparser.c"
        break;
      case 134: /* for_header2 ::= for_header1 lexpr SEMICOLON */
#line 514 "parser\\epparser.lemon"
{
    ps->gen << "if " << yymsp[-2].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data << "):" << std::endl;
    ps->gen.indent();
    delete yymsp[-2].minor.yy0; delete yymsp[-1].minor.yy0;

    // Opening for assign_statement
    yygotominor.yy0 = genTemp(yymsp[-1].minor.yy0);
    ps->gen << "def " << yygotominor.yy0->data <<"():" << std::endl;
    ps->gen.indent();
}
#line 1950 "parser\\epparser.c"
        break;
      case 135: /* for_header ::= for_header2 for_action_stmt_nonEmpty RPAREN */
#line 525 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-2].minor.yy0;
    ps->gen.unindent(false);
}
#line 1958 "parser\\epparser.c"
        break;
      case 136: /* for_header ::= for_header2 RPAREN */
#line 530 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
    ps->gen << "pass" << std::endl;
    ps->gen.unindent(false);
}
#line 1967 "parser\\epparser.c"
        break;
      case 137: /* for_stmt ::= for_header stmt */
#line 536 "parser\\epparser.lemon"
{
    ps->gen << yymsp[-1].minor.yy0->data << "()" << std::endl;
    ps->gen.unindent(false);
    ps->gen << "EUDEndWhile()" << std::endl;
    ps->closure.popScope();
}
#line 1977 "parser\\epparser.c"
        break;
      case 139: /* foreach_header ::= foreach_opener nameList_nonEmpty COLON exprList_nonEmpty RPAREN */
#line 550 "parser\\epparser.lemon"
{
    commaListIter(yymsp[-3].minor.yy0->data, [&](std::string& s) {
        ps->closure.defVariable(s);
    });
    ps->gen << "for " << yymsp[-3].minor.yy0->data << " in " << yymsp[-1].minor.yy0->data << ":" << std::endl;
    ps->gen.indent();
}
#line 1988 "parser\\epparser.c"
        break;
      case 141: /* continue_stmt ::= CONTINUE */
#line 566 "parser\\epparser.lemon"
{
    ps->gen << "EUDContinue()" << std::endl;
}
#line 1995 "parser\\epparser.c"
        break;
      case 142: /* break_stmt ::= BREAK */
#line 570 "parser\\epparser.lemon"
{
    ps->gen << "EUDBreak()" << std::endl;
}
#line 2002 "parser\\epparser.c"
        break;
      case 143: /* return_stmt ::= RETURN exprList */
#line 577 "parser\\epparser.lemon"
{
    ps->gen << "EUDReturn(" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2010 "parser\\epparser.c"
        break;
      case 144: /* lexpr ::= CONDITIONNAME LPAREN fArgs RPAREN */
#line 585 "parser\\epparser.lemon"
{
    yymsp[-3].minor.yy0->data = yymsp[-3].minor.yy0->data + "(" + yymsp[-1].minor.yy0->data + ")";
    delete yymsp[-1].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 2019 "parser\\epparser.c"
        break;
      case 145: /* lexpr ::= CONDITIONNAME LPAREN RPAREN */
#line 591 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + "()";
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 2027 "parser\\epparser.c"
        break;
      case 146: /* action ::= ACTIONNAME LPAREN fArgs RPAREN SEMICOLON */
#line 596 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[-4].minor.yy0);
    yygotominor.yy0->data =  yymsp[-4].minor.yy0->data + "(" + yymsp[-2].minor.yy0->data + ")";
    delete yymsp[-4].minor.yy0; delete yymsp[-2].minor.yy0;
}
#line 2036 "parser\\epparser.c"
        break;
      case 147: /* actions ::= action action */
      case 148: /* actions ::= actions action */ yytestcase(yyruleno==148);
#line 602 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
    yymsp[-1].minor.yy0->data += ",\n" + yymsp[0].minor.yy0->data;
    delete yymsp[0].minor.yy0;
}
#line 2046 "parser\\epparser.c"
        break;
      case 149: /* actionStmt ::= action */
#line 614 "parser\\epparser.lemon"
{
    ps->gen << "DoActions(" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2054 "parser\\epparser.c"
        break;
      case 150: /* actionStmt ::= actions */
#line 619 "parser\\epparser.lemon"
{
    ps->gen << "DoActions([" << std::endl;
    ps->gen.indent();
    ps->gen << yymsp[0].minor.yy0->data << std::endl;
    ps->gen.unindent(false);
    ps->gen << "])" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2066 "parser\\epparser.c"
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
      /* (113) if_block ::= if_header stmt */ yytestcase(yyruleno==113);
      /* (116) if_block ::= if_block elif_header stmt */ yytestcase(yyruleno==116);
      /* (124) for_init_stmt_nonEmpty ::= vdef_stmt */ yytestcase(yyruleno==124);
      /* (125) for_init_stmt_nonEmpty ::= vdefAssign_stmt */ yytestcase(yyruleno==125);
      /* (126) for_init_stmt_nonEmpty ::= cdef_stmt */ yytestcase(yyruleno==126);
      /* (127) for_init_stmt_nonEmpty ::= assign_stmt */ yytestcase(yyruleno==127);
      /* (128) for_init_stmt_nonEmpty ::= for_init_stmt_nonEmpty COMMA for_init_stmt_nonEmpty */ yytestcase(yyruleno==128);
      /* (129) for_init_stmt ::= for_init_stmt_nonEmpty */ yytestcase(yyruleno==129);
      /* (130) for_init_stmt ::= */ yytestcase(yyruleno==130);
      /* (131) for_action_stmt_nonEmpty ::= assign_stmt */ yytestcase(yyruleno==131);
      /* (132) for_action_stmt_nonEmpty ::= for_action_stmt_nonEmpty COMMA for_action_stmt_nonEmpty */ yytestcase(yyruleno==132);
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
#line 2155 "parser\\epparser.c"
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
#line 633 "parser\\epparser.lemon"


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
#line 2408 "parser\\epparser.c"
