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
#define YYNSTATE 297
#define YYNRULE 150
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
#define YY_ACTTAB_COUNT (1200)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   193,   26,   27,   35,  196,   17,  179,  189,  187,   69,
 /*    10 */   295,  177,  286,  284,  192,    2,  103,  276,  255,  188,
 /*    20 */   186,  133,  268,  267,  266,  265,  264,  181,  180,  198,
 /*    30 */   249,   96,  219,  179,   26,   27,  107,  128,  148,    8,
 /*    40 */    36,  153,  293,   96,  145,    6,   10,  292,  107,  128,
 /*    50 */    20,   13,    5,   74,    4,   73,   72,  193,   26,   27,
 /*    60 */   196,  218,   80,  235,  189,  187,  146,    7,    3,  234,
 /*    70 */   284,  192,    2,  291,  276,  152,  188,  186,  133,  268,
 /*    80 */   267,  266,  265,  264,  181,  180,  196,  232,   96,  219,
 /*    90 */   179,   26,   27,  107,  128,  148,    8,   36,  289,   18,
 /*   100 */    96,  145,    6,   10,  241,  107,  128,   20,   13,    5,
 /*   110 */    74,    4,   73,   72,  193,  184,  288,  290,  127,   14,
 /*   120 */   229,  189,  187,  287,   26,   27,  231,  284,  192,    2,
 /*   130 */    70,  276,  285,  188,  186,  133,  268,  267,  266,  265,
 /*   140 */   264,  181,  180,   33,  196,   96,  156,  283,  220,  217,
 /*   150 */   107,  128,  148,    8,   36,  140,   95,  209,  145,    6,
 /*   160 */    10,   79,  179,   78,   20,   13,    5,   74,    4,   73,
 /*   170 */    72,  193,  103,  270,  176,  158,   31,   32,  189,  187,
 /*   180 */   274,  185,  273,  228,  284,  192,    2,  182,  276,  272,
 /*   190 */   188,  186,  133,  268,  267,  266,  265,  264,  181,  180,
 /*   200 */    34,  271,   96,  156,  179,  448,   12,  107,  128,  148,
 /*   210 */     8,   36,  151,   95,   81,  145,    6,   10,  118,  179,
 /*   220 */   183,   20,   13,    5,   74,    4,   73,   72,  193,  103,
 /*   230 */   213,  176,  159,  269,  196,  189,  187,  263,  262,  185,
 /*   240 */   215,  284,  192,    2,   18,  276,  258,  188,  186,  133,
 /*   250 */   268,  267,  266,  265,  264,  181,  180,   29,   28,   96,
 /*   260 */   156,  179,  173,  172,  107,  128,  148,    8,   36,  238,
 /*   270 */    95,   81,  145,    6,   10,  248,  179,  253,   20,   13,
 /*   280 */     5,   74,    4,   73,   72,  193,  103,  170,  176,  138,
 /*   290 */   169,  252,  189,  187,   30,  167,  166,  212,  284,  192,
 /*   300 */     2,  251,  276,  164,  188,  186,  133,  268,  267,  266,
 /*   310 */   265,  264,  181,  180,  163,  250,   96,  156,  179,   27,
 /*   320 */    15,  107,  128,  148,    8,   36,  150,   95,   81,  145,
 /*   330 */     6,   10,  162,  179,  245,   20,   13,    5,   74,    4,
 /*   340 */    73,   72,  193,  103,  105,  176,  160,  240,  243,  189,
 /*   350 */   187,  242,  155,   34,  205,  284,  192,    2,   76,  276,
 /*   360 */   239,  188,  186,  133,  268,  267,  266,  265,  264,  181,
 /*   370 */   180,   23,   22,   96,  179,  179,   21,  233,  107,  128,
 /*   380 */   148,    8,   36,  227,   96,   83,  145,    6,   10,  237,
 /*   390 */   221,   11,   20,   13,    5,   74,    4,   73,   72,  136,
 /*   400 */   156,  179,  214,   16,  208,  137,  189,  187,  204,  149,
 /*   410 */    95,   81,  203,  191,    2,  247,  276,    1,  188,  186,
 /*   420 */   133,  268,  267,  266,  265,  264,  181,  180,  290,  280,
 /*   430 */    96,  156,  179,  197,  279,  107,  128,  148,    8,   36,
 /*   440 */   125,   95,   81,  145,    6,   10,  246,  179,  277,   20,
 /*   450 */    13,    5,   74,    4,   73,   72,  260,   81,  179,  131,
 /*   460 */   154,  117,  130,  189,  187,  139,  147,  129,   82,  261,
 /*   470 */   190,    2,  278,  276,  126,  188,  186,  133,  268,  267,
 /*   480 */   266,  265,  264,  181,  180,  207,  135,   96,  179,  179,
 /*   490 */   206,  134,  107,  128,  148,    8,   36,  449,  113,  112,
 /*   500 */   145,    6,   10,  226,  224,  449,   20,   13,    5,   74,
 /*   510 */     4,   73,   72,   56,   55,  225,  223,  179,  297,   54,
 /*   520 */   259,  104,  275,  449,  449,  449,   68,   96,  282,  281,
 /*   530 */   449,  449,  107,  128,  449,  175,  174,  171,  168,  165,
 /*   540 */    77,   75,  449,  143,  142,  449,  199,  179,  195,  449,
 /*   550 */   449,  449,  236,  449,  230,  144,  141,   81,  211,  210,
 /*   560 */    19,  116,  139,   71,   75,  179,  179,  449,  449,  449,
 /*   570 */   449,   56,   55,  179,  449,  124,  123,   54,  259,  104,
 /*   580 */   275,  449,  179,  122,   68,  449,  282,  280,  449,  449,
 /*   590 */   449,  449,  111,  175,  174,  171,  168,  165,   77,   75,
 /*   600 */   296,  202,  294,  201,  200,  179,  194,    9,  449,  449,
 /*   610 */   236,  179,  230,  144,  141,   81,  211,  210,   19,  115,
 /*   620 */   139,   81,  179,  179,  449,  114,  449,  449,  449,   56,
 /*   630 */    55,  179,  110,  109,  449,   54,  259,  104,  275,  449,
 /*   640 */   449,  106,   68,  449,  282,  449,  449,  449,  179,  179,
 /*   650 */   179,  175,  174,  171,  168,  165,   77,   75,  108,  102,
 /*   660 */   121,  449,  449,  179,  449,  449,  449,  179,  236,  449,
 /*   670 */   230,  144,  141,  120,  211,  210,   19,  119,  139,   57,
 /*   680 */    52,   51,   50,   49,   53,   59,   58,   60,   62,   61,
 /*   690 */    67,   66,   64,   65,   63,   62,   61,   67,   66,   64,
 /*   700 */    65,   63,  179,   17,  449,  179,  449,   69,  449,  177,
 /*   710 */    17,  449,  101,  449,   69,  100,  177,   59,   58,   60,
 /*   720 */    62,   61,   67,   66,   64,   65,   63,  179,  179,   67,
 /*   730 */    66,   64,   65,   63,  179,   17,  449,   99,   98,   69,
 /*   740 */   257,  177,   17,  449,   97,  449,   69,  449,  177,   59,
 /*   750 */    58,   60,   62,   61,   67,   66,   64,   65,   63,  449,
 /*   760 */   179,   64,   65,   63,  179,  179,  449,   17,  254,  179,
 /*   770 */    94,   69,   17,  177,   93,   92,   69,  449,  177,   91,
 /*   780 */   449,  347,  347,  347,  347,  347,  347,  347,  347,  347,
 /*   790 */   347,  179,  179,  449,  449,  449,  449,  179,  449,   18,
 /*   800 */   449,   90,   89,  347,  449,  347,  449,   88,  449,  449,
 /*   810 */   449,  449,  449,   59,   58,   60,   62,   61,   67,   66,
 /*   820 */    64,   65,   63,  179,  179,  449,  449,  449,  179,  179,
 /*   830 */   449,   17,  449,   87,   86,   69,  449,  177,   85,   84,
 /*   840 */   449,  449,  449,  449,  449,   59,   58,   60,   62,   61,
 /*   850 */    67,   66,   64,   65,   63,  449,  449,   25,  449,  449,
 /*   860 */   449,  226,  224,   17,  449,  449,  449,   48,  449,  157,
 /*   870 */    56,   55,  449,  225,  223,  179,   54,  259,  178,  449,
 /*   880 */   449,  449,  449,   68,   24,   96,  449,  449,  449,  449,
 /*   890 */   107,  128,  175,  174,  171,  168,  165,   56,   55,  449,
 /*   900 */   449,  222,  449,   54,  259,  178,  449,  449,  449,  449,
 /*   910 */    68,  449,  449,  449,  449,  449,  449,  449,  161,  175,
 /*   920 */   174,  171,  168,  165,   56,   55,  449,  449,  449,  449,
 /*   930 */    54,  259,  178,  449,  449,  449,  449,   68,  244,  449,
 /*   940 */   449,  449,  449,  449,  256,  161,  175,  174,  171,  168,
 /*   950 */   165,   56,   55,  449,  449,  449,  449,   54,  259,  104,
 /*   960 */   449,  449,  449,  449,   68,  449,  392,  392,  449,  449,
 /*   970 */   449,  449,  449,  175,  174,  171,  168,  165,   77,   75,
 /*   980 */   449,  449,  449,  449,  449,  449,  449,  449,   58,   60,
 /*   990 */    62,   61,   67,   66,   64,   65,   63,  449,  449,  449,
 /*  1000 */   449,  449,  449,  449,  449,   17,  449,  449,  449,   69,
 /*  1010 */   449,  177,  392,  392,  392,  392,  392,  392,  392,  392,
 /*  1020 */   392,  392,  449,  449,   56,   55,  449,  449,  449,  449,
 /*  1030 */    54,  259,  178,  449,  449,  449,  449,   68,  449,  449,
 /*  1040 */   449,  449,  449,  449,  256,  449,  175,  174,  171,  168,
 /*  1050 */   165,   56,   55,  449,  449,  449,  449,   54,  259,  104,
 /*  1060 */    47,  449,  449,  449,   68,  216,  449,  449,  449,  449,
 /*  1070 */   449,  449,  449,  175,  174,  171,  168,  165,  449,  449,
 /*  1080 */    60,   62,   61,   67,   66,   64,   65,   63,  449,  449,
 /*  1090 */   449,  449,  449,  449,  449,  449,   17,  449,  449,  449,
 /*  1100 */    69,  449,  177,  449,  449,  449,   46,   45,   44,   43,
 /*  1110 */    42,   41,   40,   39,   38,   37,  449,  449,  449,   56,
 /*  1120 */    55,  449,  449,  449,  449,   54,  259,  178,  449,  449,
 /*  1130 */   449,  449,   68,  449,  449,  449,  449,  449,  449,  449,
 /*  1140 */   449,  175,  174,  171,  168,  165,   56,   55,  449,  449,
 /*  1150 */   449,  449,   54,  259,  132,  449,  449,  449,  449,   68,
 /*  1160 */   449,  449,  449,  449,  449,  449,  449,  449,  175,  174,
 /*  1170 */   171,  168,  165,   56,   55,  449,  449,  449,  449,   54,
 /*  1180 */   259,  104,  449,  449,  449,  449,   68,  449,  449,  449,
 /*  1190 */   449,  449,  449,  449,  449,  175,  174,  171,  168,  165,
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
 /*    90 */    89,    3,    4,  104,  105,  106,  107,  108,   26,   31,
 /*   100 */    99,  112,  113,  114,   36,  104,  105,  118,  119,  120,
 /*   110 */   121,  122,  123,  124,   68,   35,   32,   26,  117,    2,
 /*   120 */    32,   75,   76,   32,    3,    4,   80,   81,   82,   83,
 /*   130 */    31,   85,   27,   87,   88,   89,   90,   91,   92,   93,
 /*   140 */    94,   95,   96,    1,    2,   99,   89,   27,   27,   32,
 /*   150 */   104,  105,  106,  107,  108,   98,   99,  100,  112,  113,
 /*   160 */   114,   27,   89,   27,  118,  119,  120,  121,  122,  123,
 /*   170 */   124,   68,   99,   27,  101,  102,    1,    2,   75,   76,
 /*   180 */    27,   35,   27,   80,   81,   82,   83,   36,   85,   27,
 /*   190 */    87,   88,   89,   90,   91,   92,   93,   94,   95,   96,
 /*   200 */     2,   27,   99,   89,   89,   70,   71,  104,  105,  106,
 /*   210 */   107,  108,   98,   99,   99,  112,  113,  114,  103,   89,
 /*   220 */    25,  118,  119,  120,  121,  122,  123,  124,   68,   99,
 /*   230 */    32,  101,  102,   36,    2,   75,   76,   27,   27,   35,
 /*   240 */    80,   81,   82,   83,   31,   85,   26,   87,   88,   89,
 /*   250 */    90,   91,   92,   93,   94,   95,   96,    2,   31,   99,
 /*   260 */    89,   89,   31,   38,  104,  105,  106,  107,  108,   98,
 /*   270 */    99,   99,  112,  113,  114,  103,   89,   32,  118,  119,
 /*   280 */   120,  121,  122,  123,  124,   68,   99,   31,  101,  102,
 /*   290 */    38,   32,   75,   76,   62,   31,   38,   80,   81,   82,
 /*   300 */    83,   32,   85,   31,   87,   88,   89,   90,   91,   92,
 /*   310 */    93,   94,   95,   96,   38,   32,   99,   89,   89,    4,
 /*   320 */    31,  104,  105,  106,  107,  108,   98,   99,   99,  112,
 /*   330 */   113,  114,  103,   89,   32,  118,  119,  120,  121,  122,
 /*   340 */   123,  124,   68,   99,   26,  101,  102,   25,   32,   75,
 /*   350 */    76,   32,   35,    2,   80,   81,   82,   83,   35,   85,
 /*   360 */    36,   87,   88,   89,   90,   91,   92,   93,   94,   95,
 /*   370 */    96,   31,   31,   99,   89,   89,   31,   57,  104,  105,
 /*   380 */   106,  107,  108,   31,   99,   99,  112,  113,  114,  104,
 /*   390 */    27,    2,  118,  119,  120,  121,  122,  123,  124,   68,
 /*   400 */    89,   89,   31,   31,   27,   32,   75,   76,   34,   98,
 /*   410 */    99,   99,   81,   82,   83,  103,   85,   86,   87,   88,
 /*   420 */    89,   90,   91,   92,   93,   94,   95,   96,   26,   34,
 /*   430 */    99,   89,   89,   77,   84,  104,  105,  106,  107,  108,
 /*   440 */    98,   99,   99,  112,  113,  114,  103,   89,   84,  118,
 /*   450 */   119,  120,  121,  122,  123,  124,   68,   99,   89,   77,
 /*   460 */    25,  103,   97,   75,   76,   67,   58,   77,   99,   81,
 /*   470 */    82,   83,   84,   85,   77,   87,   88,   89,   90,   91,
 /*   480 */    92,   93,   94,   95,   96,  123,   77,   99,   89,   89,
 /*   490 */   123,   77,  104,  105,  106,  107,  108,  125,   99,   99,
 /*   500 */   112,  113,  114,   75,   76,  125,  118,  119,  120,  121,
 /*   510 */   122,  123,  124,   18,   19,   87,   88,   89,    0,   24,
 /*   520 */    25,   26,   27,  125,  125,  125,   31,   99,   33,   34,
 /*   530 */   125,  125,  104,  105,  125,   40,   41,   42,   43,   44,
 /*   540 */    45,   46,  125,  115,  116,  125,   28,   89,   30,  125,
 /*   550 */   125,  125,   57,  125,   59,   60,   61,   99,   63,   64,
 /*   560 */    65,  103,   67,   45,   46,   89,   89,  125,  125,  125,
 /*   570 */   125,   18,   19,   89,  125,   99,   99,   24,   25,   26,
 /*   580 */    27,  125,   89,   99,   31,  125,   33,   34,  125,  125,
 /*   590 */   125,  125,   99,   40,   41,   42,   43,   44,   45,   46,
 /*   600 */    72,   73,   74,   75,   76,   89,   78,   79,  125,  125,
 /*   610 */    57,   89,   59,   60,   61,   99,   63,   64,   65,  103,
 /*   620 */    67,   99,   89,   89,  125,  103,  125,  125,  125,   18,
 /*   630 */    19,   89,   99,   99,  125,   24,   25,   26,   27,  125,
 /*   640 */   125,   99,   31,  125,   33,  125,  125,  125,   89,   89,
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
 /*   790 */    22,   89,   89,  125,  125,  125,  125,   89,  125,   31,
 /*   800 */   125,   99,   99,   35,  125,   37,  125,   99,  125,  125,
 /*   810 */   125,  125,  125,   13,   14,   15,   16,   17,   18,   19,
 /*   820 */    20,   21,   22,   89,   89,  125,  125,  125,   89,   89,
 /*   830 */   125,   31,  125,   99,   99,   35,  125,   37,   99,   99,
 /*   840 */   125,  125,  125,  125,  125,   13,   14,   15,   16,   17,
 /*   850 */    18,   19,   20,   21,   22,  125,  125,    5,  125,  125,
 /*   860 */   125,   75,   76,   31,  125,  125,  125,   35,  125,   37,
 /*   870 */    18,   19,  125,   87,   88,   89,   24,   25,   26,  125,
 /*   880 */   125,  125,  125,   31,    5,   99,  125,  125,  125,  125,
 /*   890 */   104,  105,   40,   41,   42,   43,   44,   18,   19,  125,
 /*   900 */   125,  115,  125,   24,   25,   26,  125,  125,  125,  125,
 /*   910 */    31,  125,  125,  125,  125,  125,  125,  125,   66,   40,
 /*   920 */    41,   42,   43,   44,   18,   19,  125,  125,  125,  125,
 /*   930 */    24,   25,   26,  125,  125,  125,  125,   31,   32,  125,
 /*   940 */   125,  125,  125,  125,   38,   66,   40,   41,   42,   43,
 /*   950 */    44,   18,   19,  125,  125,  125,  125,   24,   25,   26,
 /*   960 */   125,  125,  125,  125,   31,  125,    1,    2,  125,  125,
 /*   970 */   125,  125,  125,   40,   41,   42,   43,   44,   45,   46,
 /*   980 */   125,  125,  125,  125,  125,  125,  125,  125,   14,   15,
 /*   990 */    16,   17,   18,   19,   20,   21,   22,  125,  125,  125,
 /*  1000 */   125,  125,  125,  125,  125,   31,  125,  125,  125,   35,
 /*  1010 */   125,   37,   47,   48,   49,   50,   51,   52,   53,   54,
 /*  1020 */    55,   56,  125,  125,   18,   19,  125,  125,  125,  125,
 /*  1030 */    24,   25,   26,  125,  125,  125,  125,   31,  125,  125,
 /*  1040 */   125,  125,  125,  125,   38,  125,   40,   41,   42,   43,
 /*  1050 */    44,   18,   19,  125,  125,  125,  125,   24,   25,   26,
 /*  1060 */     1,  125,  125,  125,   31,   32,  125,  125,  125,  125,
 /*  1070 */   125,  125,  125,   40,   41,   42,   43,   44,  125,  125,
 /*  1080 */    15,   16,   17,   18,   19,   20,   21,   22,  125,  125,
 /*  1090 */   125,  125,  125,  125,  125,  125,   31,  125,  125,  125,
 /*  1100 */    35,  125,   37,  125,  125,  125,   47,   48,   49,   50,
 /*  1110 */    51,   52,   53,   54,   55,   56,  125,  125,  125,   18,
 /*  1120 */    19,  125,  125,  125,  125,   24,   25,   26,  125,  125,
 /*  1130 */   125,  125,   31,  125,  125,  125,  125,  125,  125,  125,
 /*  1140 */   125,   40,   41,   42,   43,   44,   18,   19,  125,  125,
 /*  1150 */   125,  125,   24,   25,   26,  125,  125,  125,  125,   31,
 /*  1160 */   125,  125,  125,  125,  125,  125,  125,  125,   40,   41,
 /*  1170 */    42,   43,   44,   18,   19,  125,  125,  125,  125,   24,
 /*  1180 */    25,   26,  125,  125,  125,  125,   31,  125,  125,  125,
 /*  1190 */   125,  125,  125,  125,  125,   40,   41,   42,   43,   44,
};
#define YY_SHIFT_USE_DFLT (-27)
#define YY_SHIFT_COUNT (202)
#define YY_SHIFT_MIN   (-26)
#define YY_SHIFT_MAX   (1155)
static const short yy_shift_ofst[] = {
 /*     0 */   -27,  553,  495,  611,  611,  611,  611,  611,  611,  611,
 /*    10 */   933,  933,  518, 1033, 1155,  906, 1006, 1006, 1006, 1101,
 /*    20 */   852,  852,  852,  852,  879,  879,  852,  852,  852, 1006,
 /*    30 */  1101, 1101, 1155, 1101, 1101, 1101,  408, 1101, 1101, 1101,
 /*    40 */  1101, 1101, 1101, 1101, 1101, 1101, 1101, 1101, 1128, 1101,
 /*    50 */  1101, 1101, 1101, 1101, 1101, 1101, 1101, 1101, 1101, 1101,
 /*    60 */  1101, 1101, 1101, 1101, 1101, 1101, 1101, 1101, 1101, 1101,
 /*    70 */    91,  402,  398,  398,  402,  402,  435,  402,  395,  395,
 /*    80 */   402,  672,  736,  704,  800,  800,  800,  800,  800,  800,
 /*    90 */   800,  800,  800,  800,  800,  800,  832,  800,  800,  800,
 /*   100 */   800,  800,  800,  800,  768,  965,  974, 1059, 1065,  679,
 /*   110 */   711,  711,  741,  741,  121,   88,   55,   31,   -2,  -26,
 /*   120 */   -26,  -26,  -26,  -26,  -26,  198,  232,  117,  175,  142,
 /*   130 */    39,    2,   68,  146,   84,   58,  374,  377,  373,  372,
 /*   140 */   351,  371,  363,  389,  352,  345,  341,  320,  340,  351,
 /*   150 */   351,  351,  324,  322,  151,  323,  317,  318,  319,  316,
 /*   160 */   302,  289,  315,  283,  276,  272,  269,  258,  264,  259,
 /*   170 */   252,  256,  245,  225,  231,  227,  255,  220,  213,  204,
 /*   180 */   211,  210,  197,  151,  195,   80,  174,  162,  155,  153,
 /*   190 */   136,  134,  120,  105,   99,   72,   47,   58,   33,    3,
 /*   200 */    20,   15,  -17,
};
#define YY_REDUCE_USE_DFLT (-84)
#define YY_REDUCE_COUNT (80)
#define YY_REDUCE_MIN   (-83)
#define YY_REDUCE_MAX   (786)
static const short yy_reduce_ofst[] = {
 /*     0 */   135,  388,  331,  274,  217,  160,  103,   46,  -11,  -68,
 /*    10 */   428,  786,  528,    1,  -56,  244,  187,  130,   73,   57,
 /*    20 */   522,  516,  458,  358,  343,  312,  229,  172,  115,  -83,
 /*    30 */   342,  311,  285,  228,  171,  114,  -43,  740,  739,  735,
 /*    40 */   734,  708,  703,  702,  680,  676,  675,  671,  286,  645,
 /*    50 */   639,  638,  616,  613,  578,  574,  561,  560,  559,  542,
 /*    60 */   534,  533,  493,  484,  477,  476,  400,  399,  369,  286,
 /*    70 */   414,  409,  367,  362,  397,  390,  365,  382,  364,  350,
 /*    80 */   356,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   298,  447,  447,  447,  447,  447,  447,  447,  447,  447,
 /*    10 */   426,  447,  447,  447,  447,  447,  353,  353,  353,  344,
 /*    20 */   447,  447,  447,  447,  447,  447,  447,  447,  447,  447,
 /*    30 */   447,  447,  447,  447,  447,  447,  414,  447,  447,  447,
 /*    40 */   447,  447,  447,  447,  447,  447,  447,  447,  447,  447,
 /*    50 */   447,  447,  447,  447,  447,  447,  447,  447,  447,  447,
 /*    60 */   447,  447,  447,  447,  447,  447,  447,  447,  447,  447,
 /*    70 */   447,  447,  446,  445,  447,  447,  447,  447,  447,  447,
 /*    80 */   447,  447,  447,  447,  406,  405,  404,  403,  402,  401,
 /*    90 */   400,  399,  398,  397,  395,  342,  447,  382,  381,  380,
 /*   100 */   379,  378,  377,  350,  390,  348,  372,  393,  373,  371,
 /*   110 */   370,  369,  365,  364,  447,  447,  447,  447,  447,  376,
 /*   120 */   375,  374,  368,  367,  366,  447,  447,  447,  447,  447,
 /*   130 */   447,  387,  347,  357,  447,  387,  447,  447,  447,  447,
 /*   140 */   345,  447,  447,  425,  447,  447,  447,  413,  447,  396,
 /*   150 */   389,  388,  447,  447,  336,  447,  357,  447,  447,  447,
 /*   160 */   447,  447,  384,  447,  447,  447,  447,  447,  447,  447,
 /*   170 */   447,  447,  447,  447,  447,  447,  354,  447,  347,  357,
 /*   180 */   447,  447,  447,  447,  447,  447,  447,  447,  447,  447,
 /*   190 */   447,  447,  447,  447,  447,  447,  447,  304,  447,  447,
 /*   200 */   447,  447,  447,  333,  318,  415,  444,  443,  442,  439,
 /*   210 */   438,  437,  436,  435,  434,  433,  432,  431,  428,  427,
 /*   220 */   430,  429,  424,  423,  422,  421,  420,  419,  418,  417,
 /*   230 */   416,  412,  411,  410,  409,  408,  407,  394,  343,  340,
 /*   240 */   337,  391,  355,  356,  441,  440,  386,  385,  383,  359,
 /*   250 */   363,  362,  361,  360,  358,  352,  351,  349,  348,  346,
 /*   260 */   335,  334,  332,  331,  330,  329,  328,  327,  326,  341,
 /*   270 */   325,  324,  323,  322,  321,  320,  319,  317,  316,  315,
 /*   280 */   313,  314,  312,  311,  310,  309,  308,  307,  306,  305,
 /*   290 */   338,  339,  303,  302,  301,  300,  299,
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
 /*  62 */ "expr ::= L2V LPAREN lexpr RPAREN",
 /*  63 */ "expr ::= MAPSTRING LPAREN STRING RPAREN",
 /*  64 */ "expr ::= UNIT LPAREN STRING RPAREN",
 /*  65 */ "expr ::= SWITCH LPAREN STRING RPAREN",
 /*  66 */ "expr ::= LOCATION LPAREN STRING RPAREN",
 /*  67 */ "expr ::= expr PLUS expr",
 /*  68 */ "expr ::= expr MINUS expr",
 /*  69 */ "expr ::= expr MULTIPLY expr",
 /*  70 */ "expr ::= expr DIVIDE expr",
 /*  71 */ "expr ::= expr MOD expr",
 /*  72 */ "expr ::= expr LSHIFT expr",
 /*  73 */ "expr ::= expr RSHIFT expr",
 /*  74 */ "expr ::= expr BITAND expr",
 /*  75 */ "expr ::= expr BITOR expr",
 /*  76 */ "expr ::= expr BITXOR expr",
 /*  77 */ "expr ::= PLUS expr",
 /*  78 */ "expr ::= MINUS expr",
 /*  79 */ "expr ::= BITNOT expr",
 /*  80 */ "lexpr ::= expr EQ expr",
 /*  81 */ "lexpr ::= expr NE expr",
 /*  82 */ "lexpr ::= expr LE expr",
 /*  83 */ "lexpr ::= expr LT expr",
 /*  84 */ "lexpr ::= expr GE expr",
 /*  85 */ "lexpr ::= expr GT expr",
 /*  86 */ "lexpr ::= lexpr LAND lexpr",
 /*  87 */ "lexpr ::= lexpr LOR lexpr",
 /*  88 */ "lexpr ::= LNOT lexpr",
 /*  89 */ "lexpr ::= LNOT LNOT lexpr",
 /*  90 */ "vdef_stmt ::= VAR nameList_nonEmpty",
 /*  91 */ "vdefAssign_stmt ::= VAR nameList_nonEmpty ASSIGN exprList_nonEmpty",
 /*  92 */ "cdef_stmt ::= CONST nameList_nonEmpty ASSIGN exprList_nonEmpty",
 /*  93 */ "lvalue ::= NAME",
 /*  94 */ "lvalue ::= expr LSQBRACKET NAME RSQBRACKET",
 /*  95 */ "lvalue ::= expr PERIOD NAME",
 /*  96 */ "lvalueList_nonEmpty ::= lvalue",
 /*  97 */ "lvalueList_nonEmpty ::= lvalueList_nonEmpty COMMA lvalue",
 /*  98 */ "assign_stmt ::= lvalue ASSIGN expr",
 /*  99 */ "assign_stmt ::= lvalueList_nonEmpty ASSIGN exprList_nonEmpty",
 /* 100 */ "assign_stmt ::= lvalue IADD expr",
 /* 101 */ "assign_stmt ::= lvalue ISUB expr",
 /* 102 */ "assign_stmt ::= lvalue IMUL expr",
 /* 103 */ "assign_stmt ::= lvalue IDIV expr",
 /* 104 */ "assign_stmt ::= lvalue IMOD expr",
 /* 105 */ "assign_stmt ::= lvalue ILSH expr",
 /* 106 */ "assign_stmt ::= lvalue IRSH expr",
 /* 107 */ "assign_stmt ::= lvalue IBND expr",
 /* 108 */ "assign_stmt ::= lvalue IBOR expr",
 /* 109 */ "assign_stmt ::= lvalue IBXR expr",
 /* 110 */ "if_start ::= IF",
 /* 111 */ "if_header ::= if_start LPAREN lexpr RPAREN",
 /* 112 */ "if_block ::= if_header stmt",
 /* 113 */ "elif_start ::= ELSE IF",
 /* 114 */ "elif_header ::= elif_start LPAREN lexpr RPAREN",
 /* 115 */ "if_block ::= if_block elif_header stmt",
 /* 116 */ "else_header ::= ELSE",
 /* 117 */ "if_stmt ::= if_block",
 /* 118 */ "if_stmt ::= if_block else_header stmt",
 /* 119 */ "while_start ::= WHILE",
 /* 120 */ "while_header ::= while_start LPAREN lexpr RPAREN",
 /* 121 */ "while_stmt ::= while_header stmt",
 /* 122 */ "for_opener ::= FOR LPAREN",
 /* 123 */ "for_init_stmt_nonEmpty ::= vdef_stmt",
 /* 124 */ "for_init_stmt_nonEmpty ::= vdefAssign_stmt",
 /* 125 */ "for_init_stmt_nonEmpty ::= cdef_stmt",
 /* 126 */ "for_init_stmt_nonEmpty ::= assign_stmt",
 /* 127 */ "for_init_stmt_nonEmpty ::= for_init_stmt_nonEmpty COMMA for_init_stmt_nonEmpty",
 /* 128 */ "for_init_stmt ::= for_init_stmt_nonEmpty",
 /* 129 */ "for_init_stmt ::=",
 /* 130 */ "for_action_stmt_nonEmpty ::= assign_stmt",
 /* 131 */ "for_action_stmt_nonEmpty ::= for_action_stmt_nonEmpty COMMA for_action_stmt_nonEmpty",
 /* 132 */ "for_header1 ::= for_opener for_init_stmt SEMICOLON",
 /* 133 */ "for_header2 ::= for_header1 lexpr SEMICOLON",
 /* 134 */ "for_header ::= for_header2 for_action_stmt_nonEmpty RPAREN",
 /* 135 */ "for_header ::= for_header2 RPAREN",
 /* 136 */ "for_stmt ::= for_header stmt",
 /* 137 */ "foreach_opener ::= FOREACH LPAREN",
 /* 138 */ "foreach_header ::= foreach_opener nameList_nonEmpty COLON exprList_nonEmpty RPAREN",
 /* 139 */ "foreach_stmt ::= foreach_header stmt",
 /* 140 */ "continue_stmt ::= CONTINUE",
 /* 141 */ "break_stmt ::= BREAK",
 /* 142 */ "return_stmt ::= RETURN exprList",
 /* 143 */ "lexpr ::= CONDITIONNAME LPAREN fArgs RPAREN",
 /* 144 */ "lexpr ::= CONDITIONNAME LPAREN RPAREN",
 /* 145 */ "action ::= ACTIONNAME LPAREN fArgs RPAREN SEMICOLON",
 /* 146 */ "actions ::= action action",
 /* 147 */ "actions ::= actions action",
 /* 148 */ "actionStmt ::= action",
 /* 149 */ "actionStmt ::= actions",
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
#line 848 "parser\\epparser.c"
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
#line 1302 "parser\\epparser.c"
        break;
      case 8: /* function_start ::= FUNCTION NAME */
#line 78 "parser\\epparser.lemon"
{
    // Preprocess yymsp[0].minor.yy0
    funcNamePreprocess(yymsp[0].minor.yy0->data);
    if(!ps->closure.defFunction(yymsp[0].minor.yy0->data)) {
        throw_error(4495, "Duplicate function yymsp[0].minor.yy0 " + yymsp[0].minor.yy0->data);
    }
    ps->closure.pushScope();
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1315 "parser\\epparser.c"
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
#line 1334 "parser\\epparser.c"
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
#line 1345 "parser\\epparser.c"
        break;
      case 11: /* fdef_chunk ::= function_header stmt */
      case 139: /* foreach_stmt ::= foreach_header stmt */ yytestcase(yyruleno==139);
#line 112 "parser\\epparser.lemon"
{
    ps->gen.unindent(true);
    ps->closure.popScope();
}
#line 1354 "parser\\epparser.c"
        break;
      case 12: /* stmt ::= error SEMICOLON */
#line 119 "parser\\epparser.lemon"
{ throw_error(6974, "Error while parsing statement"); }
#line 1359 "parser\\epparser.c"
        break;
      case 15: /* lbracket ::= LBRACKET */
#line 125 "parser\\epparser.lemon"
{ ps->closure.pushScope(); }
#line 1364 "parser\\epparser.c"
        break;
      case 16: /* rbracket ::= RBRACKET */
#line 126 "parser\\epparser.lemon"
{ ps->closure.popScope(); }
#line 1369 "parser\\epparser.c"
        break;
      case 17: /* blockStmt ::= lbracket RBRACKET */
#line 128 "parser\\epparser.lemon"
{
    ps->gen << "pass" << std::endl;
    ps->closure.popScope();
}
#line 1377 "parser\\epparser.c"
        break;
      case 21: /* blockStmt ::= lbracket error RBRACKET */
#line 135 "parser\\epparser.lemon"
{
    throw_error(6298, "Block not terminated properly.");
    ps->closure.popScope();
}
#line 1385 "parser\\epparser.c"
        break;
      case 28: /* bodyStmt ::= funcexpr SEMICOLON */
#line 146 "parser\\epparser.lemon"
{ ps->gen << yymsp[-1].minor.yy0->data << std::endl; }
#line 1390 "parser\\epparser.c"
        break;
      case 38: /* bodyStmtList ::= bodyStmtList error */
#line 158 "parser\\epparser.lemon"
{
    throw_error(8510, "Incomplete statement");
}
#line 1397 "parser\\epparser.c"
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
      case 89: /* lexpr ::= LNOT LNOT lexpr */ yytestcase(yyruleno==89);
      case 96: /* lvalueList_nonEmpty ::= lvalue */ yytestcase(yyruleno==96);
#line 164 "parser\\epparser.lemon"
{ yygotominor.yy0 = yymsp[0].minor.yy0; }
#line 1412 "parser\\epparser.c"
        break;
      case 40: /* numList_nonEmpty ::= numList_nonEmpty COMMA NUMBER */
      case 42: /* nameList_nonEmpty ::= nameList_nonEmpty COMMA NAME */ yytestcase(yyruleno==42);
      case 97: /* lvalueList_nonEmpty ::= lvalueList_nonEmpty COMMA lvalue */ yytestcase(yyruleno==97);
#line 165 "parser\\epparser.lemon"
{ yygotominor.yy0 = commaConcat(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1419 "parser\\epparser.c"
        break;
      case 43: /* exprList_nonEmpty ::= funcexpr LSQBRACKET LSQBRACKET numList_nonEmpty RSQBRACKET RSQBRACKET */
#line 169 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "_SRET(" + yymsp[-5].minor.yy0->data + ", [" + yymsp[-2].minor.yy0->data + "])";
    delete yymsp[-5].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1428 "parser\\epparser.c"
        break;
      case 44: /* expr ::= funcexpr LSQBRACKET LSQBRACKET NUMBER RSQBRACKET RSQBRACKET */
#line 176 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-5].minor.yy0->data + "[" + yymsp[-2].minor.yy0->data + "]";
    delete yymsp[-5].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1437 "parser\\epparser.c"
        break;
      case 46: /* exprList_nonEmpty ::= exprList_nonEmpty COMMA exprList_nonEmpty */
#line 184 "parser\\epparser.lemon"
{ yygotominor.yy0 = new Token((yymsp[-2].minor.yy0->data) + ", " + (yymsp[0].minor.yy0->data), yymsp[0].minor.yy0); delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1442 "parser\\epparser.c"
        break;
      case 47: /* exprList ::= */
      case 56: /* fArgs ::= */ yytestcase(yyruleno==56);
#line 186 "parser\\epparser.lemon"
{ yygotominor.yy0 = genEmpty(); }
#line 1448 "parser\\epparser.c"
        break;
      case 50: /* expr ::= NAME */
#line 191 "parser\\epparser.lemon"
{
    checkIsRValue(yymsp[0].minor.yy0->data);
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1456 "parser\\epparser.c"
        break;
      case 51: /* expr ::= expr PERIOD NAME */
#line 196 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + "." + yymsp[0].minor.yy0->data;
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1465 "parser\\epparser.c"
        break;
      case 52: /* expr ::= expr LSQBRACKET expr RSQBRACKET */
#line 202 "parser\\epparser.lemon"
{
    yymsp[-3].minor.yy0->data = yymsp[-3].minor.yy0->data + "[" + yymsp[-1].minor.yy0->data + "]";
    delete yymsp[-1].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 1474 "parser\\epparser.c"
        break;
      case 55: /* fArgs_nonEmpty ::= fArgs_nonEmpty COMMA fArgs_nonEmpty */
#line 211 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data;
    yymsp[-2].minor.yy0->type = TOKEN_TEMP;
    yygotominor.yy0 = yymsp[-2].minor.yy0;
    delete yymsp[0].minor.yy0;
}
#line 1484 "parser\\epparser.c"
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
#line 1495 "parser\\epparser.c"
        break;
      case 59: /* funcexpr ::= expr LPAREN fArgs RPAREN */
#line 229 "parser\\epparser.lemon"
{
    // Preprocess yymsp[-3].minor.yy0
    yymsp[-3].minor.yy0->data += "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 1504 "parser\\epparser.c"
        break;
      case 61: /* expr ::= LPAREN expr RPAREN */
#line 238 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1512 "parser\\epparser.c"
        break;
      case 62: /* expr ::= L2V LPAREN lexpr RPAREN */
#line 243 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "_L2V(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = genTemp(yymsp[-1].minor.yy0);
}
#line 1520 "parser\\epparser.c"
        break;
      case 63: /* expr ::= MAPSTRING LPAREN STRING RPAREN */
#line 248 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetStringIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1528 "parser\\epparser.c"
        break;
      case 64: /* expr ::= UNIT LPAREN STRING RPAREN */
#line 253 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetUnitIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1536 "parser\\epparser.c"
        break;
      case 65: /* expr ::= SWITCH LPAREN STRING RPAREN */
#line 258 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetSwitchIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1544 "parser\\epparser.c"
        break;
      case 66: /* expr ::= LOCATION LPAREN STRING RPAREN */
#line 263 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetLocationIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1552 "parser\\epparser.c"
        break;
      case 67: /* expr ::= expr PLUS expr */
#line 269 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "+",  yymsp[0].minor.yy0); }
#line 1557 "parser\\epparser.c"
        break;
      case 68: /* expr ::= expr MINUS expr */
#line 270 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "-",  yymsp[0].minor.yy0); }
#line 1562 "parser\\epparser.c"
        break;
      case 69: /* expr ::= expr MULTIPLY expr */
#line 271 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "*",  yymsp[0].minor.yy0); }
#line 1567 "parser\\epparser.c"
        break;
      case 70: /* expr ::= expr DIVIDE expr */
#line 272 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "//", yymsp[0].minor.yy0); }
#line 1572 "parser\\epparser.c"
        break;
      case 71: /* expr ::= expr MOD expr */
#line 273 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "%",  yymsp[0].minor.yy0); }
#line 1577 "parser\\epparser.c"
        break;
      case 72: /* expr ::= expr LSHIFT expr */
#line 274 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<<", yymsp[0].minor.yy0); }
#line 1582 "parser\\epparser.c"
        break;
      case 73: /* expr ::= expr RSHIFT expr */
#line 275 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">>", yymsp[0].minor.yy0); }
#line 1587 "parser\\epparser.c"
        break;
      case 74: /* expr ::= expr BITAND expr */
#line 276 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "&",  yymsp[0].minor.yy0); }
#line 1592 "parser\\epparser.c"
        break;
      case 75: /* expr ::= expr BITOR expr */
#line 277 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "|",  yymsp[0].minor.yy0); }
#line 1597 "parser\\epparser.c"
        break;
      case 76: /* expr ::= expr BITXOR expr */
#line 278 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "^",  yymsp[0].minor.yy0); }
#line 1602 "parser\\epparser.c"
        break;
      case 77: /* expr ::= PLUS expr */
#line 281 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = +" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1607 "parser\\epparser.c"
        break;
      case 78: /* expr ::= MINUS expr */
#line 282 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = -" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1612 "parser\\epparser.c"
        break;
      case 79: /* expr ::= BITNOT expr */
#line 283 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = ~" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1617 "parser\\epparser.c"
        break;
      case 80: /* lexpr ::= expr EQ expr */
#line 287 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "==", yymsp[0].minor.yy0); }
#line 1622 "parser\\epparser.c"
        break;
      case 81: /* lexpr ::= expr NE expr */
#line 288 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "!=", yymsp[0].minor.yy0); }
#line 1627 "parser\\epparser.c"
        break;
      case 82: /* lexpr ::= expr LE expr */
#line 289 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<=", yymsp[0].minor.yy0); }
#line 1632 "parser\\epparser.c"
        break;
      case 83: /* lexpr ::= expr LT expr */
#line 290 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<",  yymsp[0].minor.yy0); }
#line 1637 "parser\\epparser.c"
        break;
      case 84: /* lexpr ::= expr GE expr */
#line 291 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">=", yymsp[0].minor.yy0); }
#line 1642 "parser\\epparser.c"
        break;
      case 85: /* lexpr ::= expr GT expr */
#line 292 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">" , yymsp[0].minor.yy0); }
#line 1647 "parser\\epparser.c"
        break;
      case 86: /* lexpr ::= lexpr LAND lexpr */
#line 294 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "[" + yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data + "]";
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1656 "parser\\epparser.c"
        break;
      case 87: /* lexpr ::= lexpr LOR lexpr */
#line 300 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "EUDOr([" + yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data + "])";
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1665 "parser\\epparser.c"
        break;
      case 88: /* lexpr ::= LNOT lexpr */
#line 306 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = "EUDNot([" + yymsp[0].minor.yy0->data + "])";
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0);
}
#line 1673 "parser\\epparser.c"
        break;
      case 90: /* vdef_stmt ::= VAR nameList_nonEmpty */
#line 316 "parser\\epparser.lemon"
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
#line 1697 "parser\\epparser.c"
        break;
      case 91: /* vdefAssign_stmt ::= VAR nameList_nonEmpty ASSIGN exprList_nonEmpty */
#line 337 "parser\\epparser.lemon"
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
#line 1722 "parser\\epparser.c"
        break;
      case 92: /* cdef_stmt ::= CONST nameList_nonEmpty ASSIGN exprList_nonEmpty */
#line 359 "parser\\epparser.lemon"
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
#line 1744 "parser\\epparser.c"
        break;
      case 93: /* lvalue ::= NAME */
#line 379 "parser\\epparser.lemon"
{
    checkIsVariable(yymsp[0].minor.yy0->data);
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1752 "parser\\epparser.c"
        break;
      case 94: /* lvalue ::= expr LSQBRACKET NAME RSQBRACKET */
#line 384 "parser\\epparser.lemon"
{
    checkIsConstant(yymsp[-3].minor.yy0->data);
    yymsp[-1].minor.yy0->data = "_ARRW(" + yymsp[-3].minor.yy0->data + ", " + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
    delete yymsp[-3].minor.yy0;
}
#line 1762 "parser\\epparser.c"
        break;
      case 95: /* lvalue ::= expr PERIOD NAME */
#line 391 "parser\\epparser.lemon"
{
    checkIsConstant(yymsp[-2].minor.yy0->data);
    yymsp[0].minor.yy0->data = "_ATTW(" + yymsp[-2].minor.yy0->data + ", '" + yymsp[0].minor.yy0->data + "')";
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0);
    delete yymsp[-2].minor.yy0;
}
#line 1772 "parser\\epparser.c"
        break;
      case 98: /* assign_stmt ::= lvalue ASSIGN expr */
#line 400 "parser\\epparser.lemon"
{
    ps->gen << yymsp[-2].minor.yy0->data << " << (" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 1780 "parser\\epparser.c"
        break;
      case 99: /* assign_stmt ::= lvalueList_nonEmpty ASSIGN exprList_nonEmpty */
#line 405 "parser\\epparser.lemon"
{
    ps->gen << "_SV([" << yymsp[-2].minor.yy0->data << "], [" << yymsp[0].minor.yy0->data << "])" << std::endl;
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 1788 "parser\\epparser.c"
        break;
      case 100: /* assign_stmt ::= lvalue IADD expr */
#line 410 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << " += "  << yymsp[0].minor.yy0->data << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1793 "parser\\epparser.c"
        break;
      case 101: /* assign_stmt ::= lvalue ISUB expr */
#line 411 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << " -= "  << yymsp[0].minor.yy0->data << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1798 "parser\\epparser.c"
        break;
      case 102: /* assign_stmt ::= lvalue IMUL expr */
#line 412 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << " *= "  << yymsp[0].minor.yy0->data << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1803 "parser\\epparser.c"
        break;
      case 103: /* assign_stmt ::= lvalue IDIV expr */
#line 413 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << " //= " << yymsp[0].minor.yy0->data << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1808 "parser\\epparser.c"
        break;
      case 104: /* assign_stmt ::= lvalue IMOD expr */
#line 414 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << " %= "  << yymsp[0].minor.yy0->data << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1813 "parser\\epparser.c"
        break;
      case 105: /* assign_stmt ::= lvalue ILSH expr */
#line 415 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << " <<= " << yymsp[0].minor.yy0->data << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1818 "parser\\epparser.c"
        break;
      case 106: /* assign_stmt ::= lvalue IRSH expr */
#line 416 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << " >>= " << yymsp[0].minor.yy0->data << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1823 "parser\\epparser.c"
        break;
      case 107: /* assign_stmt ::= lvalue IBND expr */
#line 417 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << " &= "  << yymsp[0].minor.yy0->data << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1828 "parser\\epparser.c"
        break;
      case 108: /* assign_stmt ::= lvalue IBOR expr */
#line 418 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << " |= "  << yymsp[0].minor.yy0->data << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1833 "parser\\epparser.c"
        break;
      case 109: /* assign_stmt ::= lvalue IBXR expr */
#line 419 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << " ^= "  << yymsp[0].minor.yy0->data << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1838 "parser\\epparser.c"
        break;
      case 110: /* if_start ::= IF */
#line 422 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDIf()" << std::endl;
}
#line 1846 "parser\\epparser.c"
        break;
      case 111: /* if_header ::= if_start LPAREN lexpr RPAREN */
      case 120: /* while_header ::= while_start LPAREN lexpr RPAREN */ yytestcase(yyruleno==120);
#line 426 "parser\\epparser.lemon"
{
    ps->gen << "if " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data << "):" << std::endl;
    ps->gen.indent();
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1856 "parser\\epparser.c"
        break;
      case 113: /* elif_start ::= ELSE IF */
#line 434 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen.unindent(false);
    ps->gen << yygotominor.yy0->data << " = EUDElseIf()" << std::endl;
}
#line 1865 "parser\\epparser.c"
        break;
      case 114: /* elif_header ::= elif_start LPAREN lexpr RPAREN */
#line 440 "parser\\epparser.lemon"
{
    ps->gen << "if " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data <<"):" << std::endl;
    ps->gen.indent();
}
#line 1873 "parser\\epparser.c"
        break;
      case 116: /* else_header ::= ELSE */
#line 447 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "if EUDElse()():" << std::endl;
    ps->gen.indent();
}
#line 1882 "parser\\epparser.c"
        break;
      case 117: /* if_stmt ::= if_block */
      case 118: /* if_stmt ::= if_block else_header stmt */ yytestcase(yyruleno==118);
#line 453 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndIf()" << std::endl;
}
#line 1891 "parser\\epparser.c"
        break;
      case 119: /* while_start ::= WHILE */
#line 465 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDWhile()" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1900 "parser\\epparser.c"
        break;
      case 121: /* while_stmt ::= while_header stmt */
#line 477 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndWhile()" << std::endl;
}
#line 1908 "parser\\epparser.c"
        break;
      case 122: /* for_opener ::= FOR LPAREN */
      case 137: /* foreach_opener ::= FOREACH LPAREN */ yytestcase(yyruleno==137);
#line 483 "parser\\epparser.lemon"
{
    ps->closure.pushScope();
}
#line 1916 "parser\\epparser.c"
        break;
      case 132: /* for_header1 ::= for_opener for_init_stmt SEMICOLON */
#line 499 "parser\\epparser.lemon"
{
    // opening for lexpr
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDWhile()" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1926 "parser\\epparser.c"
        break;
      case 133: /* for_header2 ::= for_header1 lexpr SEMICOLON */
#line 506 "parser\\epparser.lemon"
{
    ps->gen << "if " << yymsp[-2].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data << "):" << std::endl;
    ps->gen.indent();
    delete yymsp[-2].minor.yy0; delete yymsp[-1].minor.yy0;

    // Opening for assign_statement
    yygotominor.yy0 = genTemp(yymsp[-1].minor.yy0);
    ps->gen << "def " << yygotominor.yy0->data <<"():" << std::endl;
    ps->gen.indent();
}
#line 1940 "parser\\epparser.c"
        break;
      case 134: /* for_header ::= for_header2 for_action_stmt_nonEmpty RPAREN */
#line 517 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-2].minor.yy0;
    ps->gen.unindent(false);
}
#line 1948 "parser\\epparser.c"
        break;
      case 135: /* for_header ::= for_header2 RPAREN */
#line 522 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
    ps->gen << "pass" << std::endl;
    ps->gen.unindent(false);
}
#line 1957 "parser\\epparser.c"
        break;
      case 136: /* for_stmt ::= for_header stmt */
#line 528 "parser\\epparser.lemon"
{
    ps->gen << yymsp[-1].minor.yy0->data << "()" << std::endl;
    ps->gen.unindent(false);
    ps->gen << "EUDEndWhile()" << std::endl;
    ps->closure.popScope();
}
#line 1967 "parser\\epparser.c"
        break;
      case 138: /* foreach_header ::= foreach_opener nameList_nonEmpty COLON exprList_nonEmpty RPAREN */
#line 542 "parser\\epparser.lemon"
{
    commaListIter(yymsp[-3].minor.yy0->data, [&](std::string& s) {
        ps->closure.defVariable(s);
    });
    ps->gen << "for " << yymsp[-3].minor.yy0->data << " in " << yymsp[-1].minor.yy0->data << ":" << std::endl;
    ps->gen.indent();
}
#line 1978 "parser\\epparser.c"
        break;
      case 140: /* continue_stmt ::= CONTINUE */
#line 558 "parser\\epparser.lemon"
{
    ps->gen << "EUDContinue()" << std::endl;
}
#line 1985 "parser\\epparser.c"
        break;
      case 141: /* break_stmt ::= BREAK */
#line 562 "parser\\epparser.lemon"
{
    ps->gen << "EUDBreak()" << std::endl;
}
#line 1992 "parser\\epparser.c"
        break;
      case 142: /* return_stmt ::= RETURN exprList */
#line 569 "parser\\epparser.lemon"
{
    ps->gen << "EUDReturn(" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2000 "parser\\epparser.c"
        break;
      case 143: /* lexpr ::= CONDITIONNAME LPAREN fArgs RPAREN */
#line 577 "parser\\epparser.lemon"
{
    yymsp[-3].minor.yy0->data = yymsp[-3].minor.yy0->data + "(" + yymsp[-1].minor.yy0->data + ")";
    delete yymsp[-1].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 2009 "parser\\epparser.c"
        break;
      case 144: /* lexpr ::= CONDITIONNAME LPAREN RPAREN */
#line 583 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + "()";
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 2017 "parser\\epparser.c"
        break;
      case 145: /* action ::= ACTIONNAME LPAREN fArgs RPAREN SEMICOLON */
#line 588 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[-4].minor.yy0);
    yygotominor.yy0->data =  yymsp[-4].minor.yy0->data + "(" + yymsp[-2].minor.yy0->data + ")";
    delete yymsp[-4].minor.yy0; delete yymsp[-2].minor.yy0;
}
#line 2026 "parser\\epparser.c"
        break;
      case 146: /* actions ::= action action */
      case 147: /* actions ::= actions action */ yytestcase(yyruleno==147);
#line 594 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
    yymsp[-1].minor.yy0->data += ",\n" + yymsp[0].minor.yy0->data;
    delete yymsp[0].minor.yy0;
}
#line 2036 "parser\\epparser.c"
        break;
      case 148: /* actionStmt ::= action */
#line 606 "parser\\epparser.lemon"
{
    ps->gen << "DoActions(" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2044 "parser\\epparser.c"
        break;
      case 149: /* actionStmt ::= actions */
#line 611 "parser\\epparser.lemon"
{
    ps->gen << "DoActions([" << std::endl;
    ps->gen.indent();
    ps->gen << yymsp[0].minor.yy0->data << std::endl;
    ps->gen.unindent(false);
    ps->gen << "])" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2056 "parser\\epparser.c"
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
      /* (112) if_block ::= if_header stmt */ yytestcase(yyruleno==112);
      /* (115) if_block ::= if_block elif_header stmt */ yytestcase(yyruleno==115);
      /* (123) for_init_stmt_nonEmpty ::= vdef_stmt */ yytestcase(yyruleno==123);
      /* (124) for_init_stmt_nonEmpty ::= vdefAssign_stmt */ yytestcase(yyruleno==124);
      /* (125) for_init_stmt_nonEmpty ::= cdef_stmt */ yytestcase(yyruleno==125);
      /* (126) for_init_stmt_nonEmpty ::= assign_stmt */ yytestcase(yyruleno==126);
      /* (127) for_init_stmt_nonEmpty ::= for_init_stmt_nonEmpty COMMA for_init_stmt_nonEmpty */ yytestcase(yyruleno==127);
      /* (128) for_init_stmt ::= for_init_stmt_nonEmpty */ yytestcase(yyruleno==128);
      /* (129) for_init_stmt ::= */ yytestcase(yyruleno==129);
      /* (130) for_action_stmt_nonEmpty ::= assign_stmt */ yytestcase(yyruleno==130);
      /* (131) for_action_stmt_nonEmpty ::= for_action_stmt_nonEmpty COMMA for_action_stmt_nonEmpty */ yytestcase(yyruleno==131);
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
#line 2145 "parser\\epparser.c"
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
#line 625 "parser\\epparser.lemon"


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
#line 2398 "parser\\epparser.c"
