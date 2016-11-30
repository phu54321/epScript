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
#define YYNOCODE 116
#define YYACTIONTYPE unsigned short int
#define ParseTOKENTYPE Token*
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  int yy231;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL  ParserStruct* ps ;
#define ParseARG_PDECL , ParserStruct* ps 
#define ParseARG_FETCH  ParserStruct* ps  = yypParser->ps 
#define ParseARG_STORE yypParser->ps  = ps 
#define YYNSTATE 276
#define YYNRULE 140
#define YYERRORSYMBOL 58
#define YYERRSYMDT yy231
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
#define YY_ACTTAB_COUNT (920)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   168,   54,   52,   50,   51,   49,  274,  164,  162,   31,
 /*    10 */   171,  194,  265,  263,  167,    9,   29,  171,  163,  161,
 /*    20 */   160,  249,  248,  247,  246,  245,  159,  158,  120,   99,
 /*    30 */   115,    5,    1,  127,  153,  173,  120,   99,  117,    6,
 /*    40 */    56,  193,  122,   73,  114,    4,   10,  153,  272,  127,
 /*    50 */    17,   32,    3,   61,    2,   60,   59,  168,  109,   73,
 /*    60 */   184,  271,  171,  153,  164,  162,   28,   62,  194,  209,
 /*    70 */   263,  167,    9,  417,   11,  163,  161,  160,  249,  248,
 /*    80 */   247,  246,  245,  159,  158,  120,   99,  155,   68,  119,
 /*    90 */   127,  153,  267,  120,   99,  117,    6,   56,   97,  214,
 /*   100 */    73,  114,    4,   10,  153,  152,  152,   17,   32,    3,
 /*   110 */    61,    2,   60,   59,  168,   74,   71,  130,  128,  153,
 /*   120 */   153,  164,  162,   50,   51,   49,  206,  263,  167,    9,
 /*   130 */   171,  171,  163,  161,  160,  249,  248,  247,  246,  245,
 /*   140 */   159,  158,  270,  269,  268,   57,  264,  127,  153,  266,
 /*   150 */   120,   99,  117,    6,   56,  334,  121,   73,  114,    4,
 /*   160 */    10,  153,  152,  152,   17,   32,    3,   61,    2,   60,
 /*   170 */    59,  168,   74,   90,  130,  107,  153,  153,  164,  162,
 /*   180 */    27,   98,   33,  203,  263,  167,    9,  191,   30,  163,
 /*   190 */   161,  160,  249,  248,  247,  246,  245,  159,  158,  262,
 /*   200 */   333,   67,   66,  254,  155,  153,  157,  120,   99,  117,
 /*   210 */     6,   56,  192,   23,   24,  114,    4,   10,  188,  152,
 /*   220 */   253,   17,   32,    3,   61,    2,   60,   59,  168,   74,
 /*   230 */   276,  130,  129,  153,  252,  164,  162,  195,  251,  250,
 /*   240 */   190,  263,  167,    9,  244,  243,  163,  161,  160,  249,
 /*   250 */   248,  247,  246,  245,  159,  158,  124,  333,  174,  156,
 /*   260 */   170,   55,  153,  147,  120,   99,  117,    6,   56,  154,
 /*   270 */   240,   15,  114,    4,   10,   58,   63,  127,   17,   32,
 /*   280 */     3,   61,    2,   60,   59,  168,  118,   73,   23,   24,
 /*   290 */   123,  153,  164,  162,   98,  151,  150,  187,  263,  167,
 /*   300 */     9,  149,  148,  163,  161,  160,  249,  248,  247,  246,
 /*   310 */   245,  159,  158,   65,   63,  239,  146,  235,   25,  153,
 /*   320 */   143,  120,   99,  117,    6,   56,  142,  234,  140,  114,
 /*   330 */     4,   10,  139,  233,  127,   17,   32,    3,   61,    2,
 /*   340 */    60,   59,  168,   95,   73,   23,   24,  137,  153,  164,
 /*   350 */   162,  232,  136,  134,  180,  263,  167,    9,  133,  231,
 /*   360 */   163,  161,  160,  249,  248,  247,  246,  245,  159,  158,
 /*   370 */    24,   13,   26,  126,  210,  219,  153,  217,  120,   99,
 /*   380 */   117,    6,   56,   64,  216,  215,  114,    4,   10,   30,
 /*   390 */   152,  152,   17,   32,    3,   61,    2,   60,   59,  105,
 /*   400 */    74,   70,  220,   34,  153,  153,  164,  162,  213,   20,
 /*   410 */   208,   19,  178,  166,   18,  202,    8,  163,  161,  160,
 /*   420 */   249,  248,  247,  246,  245,  159,  158,   12,  196,   23,
 /*   430 */    24,  189,  183,  153,   14,  120,   99,  117,    6,   56,
 /*   440 */   106,  179,  172,  114,    4,   10,  269,  152,  258,   17,
 /*   450 */    32,    3,   61,    2,   60,   59,  241,   69,  207,   23,
 /*   460 */    24,  153,   92,  164,  162,  259,  256,  101,  125,  242,
 /*   470 */   165,  102,  257,  100,  163,  161,  160,  249,  248,  247,
 /*   480 */   246,  245,  159,  158,  212,   98,   96,  108,  204,  182,
 /*   490 */   153,  104,  120,   99,  117,    6,   56,  116,  181,  103,
 /*   500 */   114,    4,   10,  418,  418,  418,   17,   32,    3,   61,
 /*   510 */     2,   60,   59,  418,   40,   38,   37,   36,   35,   39,
 /*   520 */    45,   44,   46,   48,   47,   54,   52,   50,   51,   49,
 /*   530 */    22,   45,   44,   46,   48,   47,   54,   52,   50,   51,
 /*   540 */    49,  418,  418,   43,   42,  418,  418,  418,  152,   41,
 /*   550 */   238,   93,  418,  418,  237,  418,   53,   21,   69,  418,
 /*   560 */   418,  418,  153,  224,  418,  145,  144,  141,  138,  135,
 /*   570 */    43,   42,  418,  418,  418,  418,   41,  238,   93,  418,
 /*   580 */   418,  131,  418,   53,   46,   48,   47,   54,   52,   50,
 /*   590 */    51,   49,  145,  144,  141,  138,  135,   43,   42,  418,
 /*   600 */   418,  201,  199,   41,  238,   93,  418,  418,  131,  418,
 /*   610 */    53,  218,  200,  198,  418,  418,  418,  221,  418,  145,
 /*   620 */   144,  141,  138,  135,   94,  255,  418,  418,  418,  418,
 /*   630 */   120,   99,  260,  418,  418,  418,  418,  418,   94,  255,
 /*   640 */   418,  112,  111,   65,   63,  211,  259,  205,  113,  110,
 /*   650 */   152,  186,  185,   16,  418,  108,  418,   65,   63,  211,
 /*   660 */    91,  205,  113,  110,  153,  186,  185,   16,  418,  108,
 /*   670 */    94,  255,  418,  418,  418,  418,  418,  261,  418,   45,
 /*   680 */    44,   46,   48,   47,   54,   52,   50,   51,   49,   65,
 /*   690 */    63,  211,  152,  205,  113,  110,  418,  186,  185,   16,
 /*   700 */   418,  108,   69,  152,  418,  418,  153,  132,   43,   42,
 /*   710 */   152,  418,  418,   69,   41,  238,   93,  153,  223,  418,
 /*   720 */    69,   53,  418,  418,  153,  222,  418,  418,  221,  418,
 /*   730 */   145,  144,  141,  138,  135,   45,   44,   46,   48,   47,
 /*   740 */    54,   52,   50,   51,   49,  418,  418,  418,  418,   43,
 /*   750 */    42,  418,  418,  418,  236,   41,  238,   93,  418,  418,
 /*   760 */   418,  418,   53,  418,  418,  418,  418,  418,  418,  418,
 /*   770 */   418,  145,  144,  141,  138,  135,  418,   44,   46,   48,
 /*   780 */    47,   54,   52,   50,   51,   49,  418,  418,   48,   47,
 /*   790 */    54,   52,   50,   51,   49,  418,  418,  201,  199,  275,
 /*   800 */   177,  273,  176,  175,  152,  169,    7,  152,  200,  198,
 /*   810 */   418,  418,  418,  418,   69,  418,  418,   69,  153,   89,
 /*   820 */   152,  153,   88,  418,  418,  418,  120,   99,  152,  418,
 /*   830 */    69,  418,  418,  418,  153,   87,  152,  197,   69,  418,
 /*   840 */   418,  418,  153,   86,  418,  418,  230,  418,  418,  418,
 /*   850 */   153,  152,  152,  152,  152,  418,  418,  418,  418,  152,
 /*   860 */   152,  229,  228,   85,   84,  153,  153,  153,  153,   83,
 /*   870 */    81,  152,  152,  153,  153,  418,  418,  152,  152,  152,
 /*   880 */   152,   82,  227,  418,  418,  153,  153,  226,  225,   80,
 /*   890 */    79,  153,  153,  153,  153,  418,  152,  152,  152,  152,
 /*   900 */   418,  418,  418,  418,  418,  152,   78,   77,   76,   75,
 /*   910 */   153,  153,  153,  153,  418,   72,  418,  418,  418,  153,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    58,   18,   19,   20,   21,   22,   27,   65,   66,    1,
 /*    10 */     2,   77,   70,   71,   72,   73,    1,    2,   76,   77,
 /*    20 */    78,   79,   80,   81,   82,   83,   84,   85,   94,   95,
 /*    30 */    99,  100,  101,   78,   92,   26,   94,   95,   96,   97,
 /*    40 */    98,  107,   87,   88,  102,  103,  104,   92,   27,   78,
 /*    50 */   108,  109,  110,  111,  112,  113,  114,   58,   87,   88,
 /*    60 */    89,   27,    2,   92,   65,   66,    1,    2,   77,   70,
 /*    70 */    71,   72,   73,   60,   61,   76,   77,   78,   79,   80,
 /*    80 */    81,   82,   83,   84,   85,   94,   95,   35,   29,   37,
 /*    90 */    78,   92,   32,   94,   95,   96,   97,   98,  107,   87,
 /*   100 */    88,  102,  103,  104,   92,   78,   78,  108,  109,  110,
 /*   110 */   111,  112,  113,  114,   58,   88,   88,   90,   91,   92,
 /*   120 */    92,   65,   66,   20,   21,   22,   70,   71,   72,   73,
 /*   130 */     2,    2,   76,   77,   78,   79,   80,   81,   82,   83,
 /*   140 */    84,   85,   26,   26,   26,   31,   27,   78,   92,   32,
 /*   150 */    94,   95,   96,   97,   98,   31,   87,   88,  102,  103,
 /*   160 */   104,   92,   78,   78,  108,  109,  110,  111,  112,  113,
 /*   170 */   114,   58,   88,   88,   90,   91,   92,   92,   65,   66,
 /*   180 */    52,   26,    2,   70,   71,   72,   73,   32,    2,   76,
 /*   190 */    77,   78,   79,   80,   81,   82,   83,   84,   85,   27,
 /*   200 */    31,   27,   27,   27,   35,   92,   37,   94,   95,   96,
 /*   210 */    97,   98,   32,    3,    4,  102,  103,  104,   32,   78,
 /*   220 */    27,  108,  109,  110,  111,  112,  113,  114,   58,   88,
 /*   230 */     0,   90,   91,   92,   27,   65,   66,   27,   27,   27,
 /*   240 */    70,   71,   72,   73,   27,   27,   76,   77,   78,   79,
 /*   250 */    80,   81,   82,   83,   84,   85,    2,   31,   28,   26,
 /*   260 */    30,   35,   92,   37,   94,   95,   96,   97,   98,   26,
 /*   270 */    36,   31,  102,  103,  104,   45,   46,   78,  108,  109,
 /*   280 */   110,  111,  112,  113,  114,   58,   87,   88,    3,    4,
 /*   290 */    36,   92,   65,   66,   26,   35,   35,   70,   71,   72,
 /*   300 */    73,   25,   36,   76,   77,   78,   79,   80,   81,   82,
 /*   310 */    83,   84,   85,   45,   46,   36,   26,   32,   31,   92,
 /*   320 */    31,   94,   95,   96,   97,   98,   38,   32,   31,  102,
 /*   330 */   103,  104,   38,   32,   78,  108,  109,  110,  111,  112,
 /*   340 */   113,  114,   58,   87,   88,    3,    4,   31,   92,   65,
 /*   350 */    66,   32,   38,   31,   70,   71,   72,   73,   38,   32,
 /*   360 */    76,   77,   78,   79,   80,   81,   82,   83,   84,   85,
 /*   370 */     4,   31,    2,   35,   32,   32,   92,   32,   94,   95,
 /*   380 */    96,   97,   98,   35,   25,   36,  102,  103,  104,    2,
 /*   390 */    78,   78,  108,  109,  110,  111,  112,  113,  114,   58,
 /*   400 */    88,   88,   90,    1,   92,   92,   65,   66,   26,   31,
 /*   410 */    47,   31,   71,   72,   31,   31,   75,   76,   77,   78,
 /*   420 */    79,   80,   81,   82,   83,   84,   85,    2,   27,    3,
 /*   430 */     4,   31,   27,   92,   31,   94,   95,   96,   97,   98,
 /*   440 */    32,   34,   67,  102,  103,  104,   26,   78,   74,  108,
 /*   450 */   109,  110,  111,  112,  113,  114,   58,   88,   32,    3,
 /*   460 */     4,   92,   93,   65,   66,   34,   74,   86,   25,   71,
 /*   470 */    72,   67,   74,   67,   76,   77,   78,   79,   80,   81,
 /*   480 */    82,   83,   84,   85,   94,   26,   67,   57,   32,  113,
 /*   490 */    92,   67,   94,   95,   96,   97,   98,   48,  113,   67,
 /*   500 */   102,  103,  104,  115,  115,  115,  108,  109,  110,  111,
 /*   510 */   112,  113,  114,  115,    7,    8,    9,   10,   11,   12,
 /*   520 */    13,   14,   15,   16,   17,   18,   19,   20,   21,   22,
 /*   530 */     5,   13,   14,   15,   16,   17,   18,   19,   20,   21,
 /*   540 */    22,  115,  115,   18,   19,  115,  115,  115,   78,   24,
 /*   550 */    25,   26,  115,  115,   36,  115,   31,    5,   88,  115,
 /*   560 */   115,  115,   92,   93,  115,   40,   41,   42,   43,   44,
 /*   570 */    18,   19,  115,  115,  115,  115,   24,   25,   26,  115,
 /*   580 */   115,   56,  115,   31,   15,   16,   17,   18,   19,   20,
 /*   590 */    21,   22,   40,   41,   42,   43,   44,   18,   19,  115,
 /*   600 */   115,   65,   66,   24,   25,   26,  115,  115,   56,  115,
 /*   610 */    31,   32,   76,   77,  115,  115,  115,   38,  115,   40,
 /*   620 */    41,   42,   43,   44,   26,   27,  115,  115,  115,  115,
 /*   630 */    94,   95,   34,  115,  115,  115,  115,  115,   26,   27,
 /*   640 */   115,  105,  106,   45,   46,   47,   34,   49,   50,   51,
 /*   650 */    78,   53,   54,   55,  115,   57,  115,   45,   46,   47,
 /*   660 */    88,   49,   50,   51,   92,   53,   54,   55,  115,   57,
 /*   670 */    26,   27,  115,  115,  115,  115,  115,   33,  115,   13,
 /*   680 */    14,   15,   16,   17,   18,   19,   20,   21,   22,   45,
 /*   690 */    46,   47,   78,   49,   50,   51,  115,   53,   54,   55,
 /*   700 */   115,   57,   88,   78,  115,  115,   92,   93,   18,   19,
 /*   710 */    78,  115,  115,   88,   24,   25,   26,   92,   93,  115,
 /*   720 */    88,   31,  115,  115,   92,   93,  115,  115,   38,  115,
 /*   730 */    40,   41,   42,   43,   44,   13,   14,   15,   16,   17,
 /*   740 */    18,   19,   20,   21,   22,  115,  115,  115,  115,   18,
 /*   750 */    19,  115,  115,  115,   32,   24,   25,   26,  115,  115,
 /*   760 */   115,  115,   31,  115,  115,  115,  115,  115,  115,  115,
 /*   770 */   115,   40,   41,   42,   43,   44,  115,   14,   15,   16,
 /*   780 */    17,   18,   19,   20,   21,   22,  115,  115,   16,   17,
 /*   790 */    18,   19,   20,   21,   22,  115,  115,   65,   66,   62,
 /*   800 */    63,   64,   65,   66,   78,   68,   69,   78,   76,   77,
 /*   810 */   115,  115,  115,  115,   88,  115,  115,   88,   92,   93,
 /*   820 */    78,   92,   93,  115,  115,  115,   94,   95,   78,  115,
 /*   830 */    88,  115,  115,  115,   92,   93,   78,  105,   88,  115,
 /*   840 */   115,  115,   92,   93,  115,  115,   88,  115,  115,  115,
 /*   850 */    92,   78,   78,   78,   78,  115,  115,  115,  115,   78,
 /*   860 */    78,   88,   88,   88,   88,   92,   92,   92,   92,   88,
 /*   870 */    88,   78,   78,   92,   92,  115,  115,   78,   78,   78,
 /*   880 */    78,   88,   88,  115,  115,   92,   92,   88,   88,   88,
 /*   890 */    88,   92,   92,   92,   92,  115,   78,   78,   78,   78,
 /*   900 */   115,  115,  115,  115,  115,   78,   88,   88,   88,   88,
 /*   910 */    92,   92,   92,   92,  115,   88,  115,  115,  115,   92,
};
#define YY_SHIFT_USE_DFLT (-22)
#define YY_SHIFT_COUNT (177)
#define YY_SHIFT_MIN   (-21)
#define YY_SHIFT_MAX   (772)
static const short yy_shift_ofst[] = {
 /*     0 */   -22,  644,  644,  644,  644,  644,  644,  644,  612,  598,
 /*    10 */   268,  230,  268,  579,  690,  690,  731,  525,  525,  525,
 /*    20 */   525,  552,  552,  525,  525,  525,  690,  731,  731,  731,
 /*    30 */   731,  731,  155,  459,  731,  731,  731,  731,  731,  731,
 /*    40 */   731,  731,  731,  731,  731,  731,  731,  731,  731,  731,
 /*    50 */   731,  731,  731,  731,  731,  731,  449,  117,  420,  430,
 /*    60 */   430,  420,  459,  420,  443,  420,  431,  431,  420,  507,
 /*    70 */   722,  518,  666,  666,  666,  666,  666,  666,  666,  666,
 /*    80 */   666,  763,  569,  772,  -17,  -17,  210,  456,  426,  342,
 /*    90 */   103,  103,  285,  226,  169,  186,  128,  180,   52,   65,
 /*   100 */    15,  254,    8,   60,  129,  407,  405,  408,  403,  387,
 /*   110 */   400,  401,  425,  384,  383,  380,  363,  378,  387,  382,
 /*   120 */   402,  387,  387,  349,  359,  266,  348,  338,  345,  343,
 /*   130 */   370,  340,  366,  327,  320,  322,  319,  314,  316,  301,
 /*   140 */   294,  297,  295,  288,  289,  287,  124,  290,  279,  266,
 /*   150 */   276,  261,  260,  240,  234,  243,  124,  233,  218,  217,
 /*   160 */   212,  211,  207,  193,  176,  175,  174,  172,  119,  114,
 /*   170 */   118,  116,  129,   59,    9,   34,   21,  -21,
};
#define YY_REDUCE_USE_DFLT (-70)
#define YY_REDUCE_COUNT (68)
#define YY_REDUCE_MIN   (-69)
#define YY_REDUCE_MAX   (827)
static const short yy_reduce_ofst[] = {
 /*     0 */    13,  284,  227,  170,  113,   56,   -1,  -58,  398,  341,
 /*    10 */   536,  737,  732,  141,   84,   27,  -29,  750,  742,  729,
 /*    20 */   726,  632,  625,  614,  470,  369,  312,  256,  199,   69,
 /*    30 */    12,  -45,   -9,  -66,  827,  821,  820,  819,  818,  802,
 /*    40 */   801,  800,  799,  794,  793,  782,  781,  776,  775,  774,
 /*    50 */   773,  758,  572,  313,   85,   28,  -69,  432,  424,  385,
 /*    60 */   376,  419,  390,  406,  381,  404,  392,  374,  375,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   277,  416,  416,  416,  416,  416,  416,  416,  416,  416,
 /*    10 */   395,  416,  416,  416,  331,  331,  322,  416,  416,  416,
 /*    20 */   416,  416,  416,  416,  416,  416,  416,  416,  416,  416,
 /*    30 */   416,  416,  416,  416,  416,  416,  416,  416,  416,  416,
 /*    40 */   416,  416,  416,  416,  416,  416,  416,  416,  416,  416,
 /*    50 */   416,  416,  416,  416,  416,  416,  383,  416,  416,  415,
 /*    60 */   414,  416,  416,  416,  416,  416,  416,  416,  416,  416,
 /*    70 */   416,  416,  374,  320,  328,  361,  360,  359,  358,  357,
 /*    80 */   356,  351,  352,  350,  349,  348,  416,  416,  416,  416,
 /*    90 */   343,  344,  416,  325,  369,  416,  416,  416,  369,  416,
 /*   100 */   416,  416,  366,  416,  366,  416,  416,  416,  416,  323,
 /*   110 */   416,  416,  394,  416,  416,  416,  382,  416,  375,  416,
 /*   120 */   372,  368,  367,  416,  416,  314,  416,  336,  416,  416,
 /*   130 */   332,  416,  363,  416,  416,  416,  416,  416,  416,  416,
 /*   140 */   416,  416,  416,  416,  416,  416,  326,  416,  416,  416,
 /*   150 */   416,  416,  336,  416,  416,  416,  371,  416,  416,  416,
 /*   160 */   416,  416,  416,  416,  416,  416,  416,  416,  416,  416,
 /*   170 */   416,  416,  283,  416,  416,  416,  416,  416,  311,  297,
 /*   180 */   384,  413,  412,  411,  408,  407,  406,  405,  404,  403,
 /*   190 */   402,  401,  400,  397,  396,  399,  398,  393,  392,  391,
 /*   200 */   390,  389,  388,  387,  386,  385,  381,  380,  379,  378,
 /*   210 */   377,  376,  373,  371,  321,  318,  315,  335,  410,  409,
 /*   220 */   330,  329,  365,  364,  362,  355,  354,  353,  347,  346,
 /*   230 */   345,  342,  341,  340,  339,  338,  337,  327,  324,  319,
 /*   240 */   370,  313,  312,  310,  309,  308,  307,  306,  305,  304,
 /*   250 */   303,  302,  301,  300,  299,  298,  296,  295,  294,  292,
 /*   260 */   293,  291,  290,  289,  288,  287,  286,  285,  284,  316,
 /*   270 */   317,  282,  281,  280,  279,  278,
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
  "LOCATION",      "VAR",           "CONST",         "IF",          
  "ELSE",          "WHILE",         "FOR",           "FOREACH",     
  "COLON",         "CONTINUE",      "BREAK",         "RETURN",      
  "CONDITIONNAME",  "ACTIONNAME",    "error",         "nt",          
  "program",       "chunks",        "chunk",         "import_chunk",
  "fdef_chunk",    "vdef_stmt",     "cdef_stmt",     "nameList_nonEmpty",
  "function_start",  "function_header",  "stmt",          "bodyStmt",    
  "return_stmt",   "lbracket",      "rbracket",      "bodyStmtList",
  "vdefAssign_stmt",  "assign_stmt",   "funcexpr",      "actionStmt",  
  "if_stmt",       "while_stmt",    "for_stmt",      "foreach_stmt",
  "continue_stmt",  "break_stmt",    "numList_nonEmpty",  "exprList_nonEmpty",
  "expr",          "exprList",      "fArgs_nonEmpty",  "fArgs",       
  "funcName",      "lexpr",         "lvalue",        "lvalueList_nonEmpty",
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
 /*  17 */ "stmt ::= lbracket RBRACKET",
 /*  18 */ "stmt ::= lbracket return_stmt SEMICOLON rbracket",
 /*  19 */ "stmt ::= lbracket bodyStmtList rbracket",
 /*  20 */ "stmt ::= lbracket bodyStmtList return_stmt SEMICOLON rbracket",
 /*  21 */ "stmt ::= lbracket error RBRACKET",
 /*  22 */ "bodyStmt ::= SEMICOLON",
 /*  23 */ "bodyStmt ::= vdef_stmt SEMICOLON",
 /*  24 */ "bodyStmt ::= vdefAssign_stmt SEMICOLON",
 /*  25 */ "bodyStmt ::= cdef_stmt SEMICOLON",
 /*  26 */ "bodyStmt ::= assign_stmt SEMICOLON",
 /*  27 */ "bodyStmt ::= funcexpr SEMICOLON",
 /*  28 */ "bodyStmt ::= actionStmt",
 /*  29 */ "bodyStmt ::= if_stmt",
 /*  30 */ "bodyStmt ::= while_stmt",
 /*  31 */ "bodyStmt ::= for_stmt",
 /*  32 */ "bodyStmt ::= foreach_stmt",
 /*  33 */ "bodyStmt ::= continue_stmt SEMICOLON",
 /*  34 */ "bodyStmt ::= break_stmt SEMICOLON",
 /*  35 */ "bodyStmtList ::= bodyStmt",
 /*  36 */ "bodyStmtList ::= bodyStmtList bodyStmt",
 /*  37 */ "bodyStmtList ::= bodyStmtList error",
 /*  38 */ "numList_nonEmpty ::= NUMBER",
 /*  39 */ "numList_nonEmpty ::= numList_nonEmpty COMMA NUMBER",
 /*  40 */ "nameList_nonEmpty ::= NAME",
 /*  41 */ "nameList_nonEmpty ::= nameList_nonEmpty COMMA NAME",
 /*  42 */ "exprList_nonEmpty ::= funcexpr LSQBRACKET LSQBRACKET numList_nonEmpty RSQBRACKET RSQBRACKET",
 /*  43 */ "expr ::= funcexpr LSQBRACKET LSQBRACKET NUMBER RSQBRACKET RSQBRACKET",
 /*  44 */ "exprList_nonEmpty ::= expr",
 /*  45 */ "exprList_nonEmpty ::= exprList_nonEmpty COMMA exprList_nonEmpty",
 /*  46 */ "exprList ::=",
 /*  47 */ "exprList ::= exprList_nonEmpty",
 /*  48 */ "expr ::= NUMBER",
 /*  49 */ "expr ::= NAME",
 /*  50 */ "expr ::= NAME PERIOD NAME",
 /*  51 */ "expr ::= NAME LSQBRACKET expr RSQBRACKET",
 /*  52 */ "fArgs_nonEmpty ::= expr",
 /*  53 */ "fArgs_nonEmpty ::= STRING",
 /*  54 */ "fArgs_nonEmpty ::= fArgs_nonEmpty COMMA fArgs_nonEmpty",
 /*  55 */ "fArgs ::=",
 /*  56 */ "fArgs ::= fArgs_nonEmpty",
 /*  57 */ "funcName ::= NAME",
 /*  58 */ "funcName ::= NAME PERIOD NAME",
 /*  59 */ "funcexpr ::= funcName LPAREN fArgs RPAREN",
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
 /*  94 */ "lvalue ::= NAME LSQBRACKET NAME RSQBRACKET",
 /*  95 */ "lvalue ::= NAME PERIOD NAME",
 /*  96 */ "lvalueList_nonEmpty ::= lvalue",
 /*  97 */ "lvalueList_nonEmpty ::= lvalueList_nonEmpty COMMA lvalue",
 /*  98 */ "assign_stmt ::= lvalue ASSIGN expr",
 /*  99 */ "assign_stmt ::= lvalueList_nonEmpty ASSIGN exprList_nonEmpty",
 /* 100 */ "if_start ::= IF",
 /* 101 */ "if_header ::= if_start LPAREN lexpr RPAREN",
 /* 102 */ "if_block ::= if_header stmt",
 /* 103 */ "elif_start ::= ELSE IF",
 /* 104 */ "elif_header ::= elif_start LPAREN lexpr RPAREN",
 /* 105 */ "if_block ::= if_block elif_header stmt",
 /* 106 */ "else_header ::= ELSE",
 /* 107 */ "if_stmt ::= if_block",
 /* 108 */ "if_stmt ::= if_block else_header stmt",
 /* 109 */ "while_start ::= WHILE",
 /* 110 */ "while_header ::= while_start LPAREN lexpr RPAREN",
 /* 111 */ "while_stmt ::= while_header stmt",
 /* 112 */ "for_opener ::= FOR LPAREN",
 /* 113 */ "for_init_stmt_nonEmpty ::= vdef_stmt",
 /* 114 */ "for_init_stmt_nonEmpty ::= vdefAssign_stmt",
 /* 115 */ "for_init_stmt_nonEmpty ::= cdef_stmt",
 /* 116 */ "for_init_stmt_nonEmpty ::= assign_stmt",
 /* 117 */ "for_init_stmt_nonEmpty ::= for_init_stmt_nonEmpty COMMA for_init_stmt_nonEmpty",
 /* 118 */ "for_init_stmt ::= for_init_stmt_nonEmpty",
 /* 119 */ "for_init_stmt ::=",
 /* 120 */ "for_action_stmt_nonEmpty ::= assign_stmt",
 /* 121 */ "for_action_stmt_nonEmpty ::= for_action_stmt_nonEmpty COMMA for_action_stmt_nonEmpty",
 /* 122 */ "for_header1 ::= for_opener for_init_stmt SEMICOLON",
 /* 123 */ "for_header2 ::= for_header1 lexpr SEMICOLON",
 /* 124 */ "for_header ::= for_header2 for_action_stmt_nonEmpty RPAREN",
 /* 125 */ "for_header ::= for_header2 RPAREN",
 /* 126 */ "for_stmt ::= for_header stmt",
 /* 127 */ "foreach_opener ::= FOREACH LPAREN",
 /* 128 */ "foreach_header ::= foreach_opener nameList_nonEmpty COLON exprList_nonEmpty RPAREN",
 /* 129 */ "foreach_stmt ::= foreach_header stmt",
 /* 130 */ "continue_stmt ::= CONTINUE",
 /* 131 */ "break_stmt ::= BREAK",
 /* 132 */ "return_stmt ::= RETURN exprList",
 /* 133 */ "lexpr ::= CONDITIONNAME LPAREN fArgs RPAREN",
 /* 134 */ "lexpr ::= CONDITIONNAME LPAREN RPAREN",
 /* 135 */ "action ::= ACTIONNAME LPAREN fArgs RPAREN SEMICOLON",
 /* 136 */ "actions ::= action action",
 /* 137 */ "actions ::= actions action",
 /* 138 */ "actionStmt ::= action",
 /* 139 */ "actionStmt ::= actions",
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
    case 59: /* nt */
{
#line 31 "parser\\epparser.lemon"
 delete (yypminor->yy0); 
#line 772 "parser\\epparser.c"
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
  { 60, 1 },
  { 61, 0 },
  { 61, 2 },
  { 62, 2 },
  { 62, 1 },
  { 62, 2 },
  { 62, 2 },
  { 63, 4 },
  { 68, 2 },
  { 69, 4 },
  { 69, 3 },
  { 64, 2 },
  { 70, 2 },
  { 70, 1 },
  { 70, 2 },
  { 73, 1 },
  { 74, 1 },
  { 70, 2 },
  { 70, 4 },
  { 70, 3 },
  { 70, 5 },
  { 70, 3 },
  { 71, 1 },
  { 71, 2 },
  { 71, 2 },
  { 71, 2 },
  { 71, 2 },
  { 71, 2 },
  { 71, 1 },
  { 71, 1 },
  { 71, 1 },
  { 71, 1 },
  { 71, 1 },
  { 71, 2 },
  { 71, 2 },
  { 75, 1 },
  { 75, 2 },
  { 75, 2 },
  { 86, 1 },
  { 86, 3 },
  { 67, 1 },
  { 67, 3 },
  { 87, 6 },
  { 88, 6 },
  { 87, 1 },
  { 87, 3 },
  { 89, 0 },
  { 89, 1 },
  { 88, 1 },
  { 88, 1 },
  { 88, 3 },
  { 88, 4 },
  { 90, 1 },
  { 90, 1 },
  { 90, 3 },
  { 91, 0 },
  { 91, 1 },
  { 92, 1 },
  { 92, 3 },
  { 78, 4 },
  { 88, 1 },
  { 88, 3 },
  { 88, 4 },
  { 88, 4 },
  { 88, 4 },
  { 88, 4 },
  { 88, 4 },
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
  { 88, 2 },
  { 88, 2 },
  { 88, 2 },
  { 93, 3 },
  { 93, 3 },
  { 93, 3 },
  { 93, 3 },
  { 93, 3 },
  { 93, 3 },
  { 93, 3 },
  { 93, 3 },
  { 93, 2 },
  { 93, 3 },
  { 65, 2 },
  { 76, 4 },
  { 66, 4 },
  { 94, 1 },
  { 94, 4 },
  { 94, 3 },
  { 95, 1 },
  { 95, 3 },
  { 77, 3 },
  { 77, 3 },
  { 96, 1 },
  { 97, 4 },
  { 98, 2 },
  { 99, 2 },
  { 100, 4 },
  { 98, 3 },
  { 101, 1 },
  { 80, 1 },
  { 80, 3 },
  { 102, 1 },
  { 103, 4 },
  { 81, 2 },
  { 104, 2 },
  { 105, 1 },
  { 105, 1 },
  { 105, 1 },
  { 105, 1 },
  { 105, 3 },
  { 106, 1 },
  { 106, 0 },
  { 107, 1 },
  { 107, 3 },
  { 108, 3 },
  { 109, 3 },
  { 110, 3 },
  { 110, 2 },
  { 82, 2 },
  { 111, 2 },
  { 112, 5 },
  { 83, 2 },
  { 84, 1 },
  { 85, 1 },
  { 72, 2 },
  { 93, 4 },
  { 93, 3 },
  { 113, 5 },
  { 114, 2 },
  { 114, 2 },
  { 79, 1 },
  { 79, 1 },
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
#line 1216 "parser\\epparser.c"
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
#line 1229 "parser\\epparser.c"
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
#line 1248 "parser\\epparser.c"
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
#line 1259 "parser\\epparser.c"
        break;
      case 11: /* fdef_chunk ::= function_header stmt */
      case 129: /* foreach_stmt ::= foreach_header stmt */ yytestcase(yyruleno==129);
#line 112 "parser\\epparser.lemon"
{
    ps->gen.unindent(true);
    ps->closure.popScope();
}
#line 1268 "parser\\epparser.c"
        break;
      case 12: /* stmt ::= error SEMICOLON */
#line 119 "parser\\epparser.lemon"
{ throw_error(6974, "Error while parsing statement"); }
#line 1273 "parser\\epparser.c"
        break;
      case 15: /* lbracket ::= LBRACKET */
#line 125 "parser\\epparser.lemon"
{ ps->closure.pushScope(); }
#line 1278 "parser\\epparser.c"
        break;
      case 16: /* rbracket ::= RBRACKET */
#line 126 "parser\\epparser.lemon"
{ ps->closure.popScope(); }
#line 1283 "parser\\epparser.c"
        break;
      case 17: /* stmt ::= lbracket RBRACKET */
#line 128 "parser\\epparser.lemon"
{
    ps->gen << "pass" << std::endl;
    ps->closure.popScope();
}
#line 1291 "parser\\epparser.c"
        break;
      case 21: /* stmt ::= lbracket error RBRACKET */
#line 135 "parser\\epparser.lemon"
{
    throw_error(6298, "Block not terminated properly.");
    ps->closure.popScope();
}
#line 1299 "parser\\epparser.c"
        break;
      case 27: /* bodyStmt ::= funcexpr SEMICOLON */
#line 145 "parser\\epparser.lemon"
{ ps->gen << yymsp[-1].minor.yy0->data << std::endl; }
#line 1304 "parser\\epparser.c"
        break;
      case 37: /* bodyStmtList ::= bodyStmtList error */
#line 157 "parser\\epparser.lemon"
{
    throw_error(8510, "Incomplete statement");
}
#line 1311 "parser\\epparser.c"
        break;
      case 38: /* numList_nonEmpty ::= NUMBER */
      case 40: /* nameList_nonEmpty ::= NAME */ yytestcase(yyruleno==40);
      case 44: /* exprList_nonEmpty ::= expr */ yytestcase(yyruleno==44);
      case 47: /* exprList ::= exprList_nonEmpty */ yytestcase(yyruleno==47);
      case 48: /* expr ::= NUMBER */ yytestcase(yyruleno==48);
      case 52: /* fArgs_nonEmpty ::= expr */ yytestcase(yyruleno==52);
      case 53: /* fArgs_nonEmpty ::= STRING */ yytestcase(yyruleno==53);
      case 56: /* fArgs ::= fArgs_nonEmpty */ yytestcase(yyruleno==56);
      case 60: /* expr ::= funcexpr */ yytestcase(yyruleno==60);
      case 89: /* lexpr ::= LNOT LNOT lexpr */ yytestcase(yyruleno==89);
      case 96: /* lvalueList_nonEmpty ::= lvalue */ yytestcase(yyruleno==96);
#line 163 "parser\\epparser.lemon"
{ yygotominor.yy0 = yymsp[0].minor.yy0; }
#line 1326 "parser\\epparser.c"
        break;
      case 39: /* numList_nonEmpty ::= numList_nonEmpty COMMA NUMBER */
      case 41: /* nameList_nonEmpty ::= nameList_nonEmpty COMMA NAME */ yytestcase(yyruleno==41);
      case 97: /* lvalueList_nonEmpty ::= lvalueList_nonEmpty COMMA lvalue */ yytestcase(yyruleno==97);
#line 164 "parser\\epparser.lemon"
{ yygotominor.yy0 = commaConcat(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1333 "parser\\epparser.c"
        break;
      case 42: /* exprList_nonEmpty ::= funcexpr LSQBRACKET LSQBRACKET numList_nonEmpty RSQBRACKET RSQBRACKET */
#line 168 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "_SRET(" + yymsp[-5].minor.yy0->data + ", [" + yymsp[-2].minor.yy0->data + "])";
    delete yymsp[-5].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1342 "parser\\epparser.c"
        break;
      case 43: /* expr ::= funcexpr LSQBRACKET LSQBRACKET NUMBER RSQBRACKET RSQBRACKET */
#line 175 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-5].minor.yy0->data + "[" + yymsp[-2].minor.yy0->data + "]";
    delete yymsp[-5].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1351 "parser\\epparser.c"
        break;
      case 45: /* exprList_nonEmpty ::= exprList_nonEmpty COMMA exprList_nonEmpty */
#line 183 "parser\\epparser.lemon"
{ yygotominor.yy0 = new Token((yymsp[-2].minor.yy0->data) + ", " + (yymsp[0].minor.yy0->data), yymsp[0].minor.yy0); delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1356 "parser\\epparser.c"
        break;
      case 46: /* exprList ::= */
      case 55: /* fArgs ::= */ yytestcase(yyruleno==55);
#line 185 "parser\\epparser.lemon"
{ yygotominor.yy0 = genEmpty(); }
#line 1362 "parser\\epparser.c"
        break;
      case 49: /* expr ::= NAME */
#line 190 "parser\\epparser.lemon"
{
    checkIsRValue(yymsp[0].minor.yy0->data);
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1370 "parser\\epparser.c"
        break;
      case 50: /* expr ::= NAME PERIOD NAME */
#line 195 "parser\\epparser.lemon"
{
    checkIsConstant(yymsp[-2].minor.yy0->data);
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + "." + yymsp[0].minor.yy0->data;
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1380 "parser\\epparser.c"
        break;
      case 51: /* expr ::= NAME LSQBRACKET expr RSQBRACKET */
#line 202 "parser\\epparser.lemon"
{
    checkIsConstant(yymsp[-3].minor.yy0->data);
    yymsp[-3].minor.yy0->data = yymsp[-3].minor.yy0->data + "[" + yymsp[-1].minor.yy0->data + "]";
    delete yymsp[-1].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 1390 "parser\\epparser.c"
        break;
      case 54: /* fArgs_nonEmpty ::= fArgs_nonEmpty COMMA fArgs_nonEmpty */
#line 212 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data;
    yymsp[-2].minor.yy0->type = TOKEN_TEMP;
    yygotominor.yy0 = yymsp[-2].minor.yy0;
    delete yymsp[0].minor.yy0;
}
#line 1400 "parser\\epparser.c"
        break;
      case 57: /* funcName ::= NAME */
#line 222 "parser\\epparser.lemon"
{
    funcNamePreprocess(yymsp[0].minor.yy0->data);
    checkIsFunction(yymsp[0].minor.yy0->data);
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1409 "parser\\epparser.c"
        break;
      case 58: /* funcName ::= NAME PERIOD NAME */
#line 228 "parser\\epparser.lemon"
{
    // Preprocess name
    checkIsConstant(yymsp[-2].minor.yy0->data);
    yymsp[0].minor.yy0->data = yymsp[-2].minor.yy0->data + "." + yymsp[0].minor.yy0->data;
    delete yymsp[-2].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0);
}
#line 1420 "parser\\epparser.c"
        break;
      case 59: /* funcexpr ::= funcName LPAREN fArgs RPAREN */
#line 236 "parser\\epparser.lemon"
{
    // Preprocess yymsp[-3].minor.yy0
    yymsp[-3].minor.yy0->data += "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 1429 "parser\\epparser.c"
        break;
      case 61: /* expr ::= LPAREN expr RPAREN */
#line 245 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1437 "parser\\epparser.c"
        break;
      case 62: /* expr ::= L2V LPAREN lexpr RPAREN */
#line 250 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "_L2V(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = genTemp(yymsp[-1].minor.yy0);
}
#line 1445 "parser\\epparser.c"
        break;
      case 63: /* expr ::= MAPSTRING LPAREN STRING RPAREN */
#line 255 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetStringIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1453 "parser\\epparser.c"
        break;
      case 64: /* expr ::= UNIT LPAREN STRING RPAREN */
#line 260 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetUnitIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1461 "parser\\epparser.c"
        break;
      case 65: /* expr ::= SWITCH LPAREN STRING RPAREN */
#line 265 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetSwitchIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1469 "parser\\epparser.c"
        break;
      case 66: /* expr ::= LOCATION LPAREN STRING RPAREN */
#line 270 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetLocationIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1477 "parser\\epparser.c"
        break;
      case 67: /* expr ::= expr PLUS expr */
#line 276 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "+",  yymsp[0].minor.yy0); }
#line 1482 "parser\\epparser.c"
        break;
      case 68: /* expr ::= expr MINUS expr */
#line 277 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "-",  yymsp[0].minor.yy0); }
#line 1487 "parser\\epparser.c"
        break;
      case 69: /* expr ::= expr MULTIPLY expr */
#line 278 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "*",  yymsp[0].minor.yy0); }
#line 1492 "parser\\epparser.c"
        break;
      case 70: /* expr ::= expr DIVIDE expr */
#line 279 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "//", yymsp[0].minor.yy0); }
#line 1497 "parser\\epparser.c"
        break;
      case 71: /* expr ::= expr MOD expr */
#line 280 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "%",  yymsp[0].minor.yy0); }
#line 1502 "parser\\epparser.c"
        break;
      case 72: /* expr ::= expr LSHIFT expr */
#line 281 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<<", yymsp[0].minor.yy0); }
#line 1507 "parser\\epparser.c"
        break;
      case 73: /* expr ::= expr RSHIFT expr */
#line 282 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">>", yymsp[0].minor.yy0); }
#line 1512 "parser\\epparser.c"
        break;
      case 74: /* expr ::= expr BITAND expr */
#line 283 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "&",  yymsp[0].minor.yy0); }
#line 1517 "parser\\epparser.c"
        break;
      case 75: /* expr ::= expr BITOR expr */
#line 284 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "|",  yymsp[0].minor.yy0); }
#line 1522 "parser\\epparser.c"
        break;
      case 76: /* expr ::= expr BITXOR expr */
#line 285 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "^",  yymsp[0].minor.yy0); }
#line 1527 "parser\\epparser.c"
        break;
      case 77: /* expr ::= PLUS expr */
#line 288 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = +" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1532 "parser\\epparser.c"
        break;
      case 78: /* expr ::= MINUS expr */
#line 289 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = -" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1537 "parser\\epparser.c"
        break;
      case 79: /* expr ::= BITNOT expr */
#line 290 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = ~" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1542 "parser\\epparser.c"
        break;
      case 80: /* lexpr ::= expr EQ expr */
#line 294 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "==", yymsp[0].minor.yy0); }
#line 1547 "parser\\epparser.c"
        break;
      case 81: /* lexpr ::= expr NE expr */
#line 295 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "!=", yymsp[0].minor.yy0); }
#line 1552 "parser\\epparser.c"
        break;
      case 82: /* lexpr ::= expr LE expr */
#line 296 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<=", yymsp[0].minor.yy0); }
#line 1557 "parser\\epparser.c"
        break;
      case 83: /* lexpr ::= expr LT expr */
#line 297 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<",  yymsp[0].minor.yy0); }
#line 1562 "parser\\epparser.c"
        break;
      case 84: /* lexpr ::= expr GE expr */
#line 298 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">=", yymsp[0].minor.yy0); }
#line 1567 "parser\\epparser.c"
        break;
      case 85: /* lexpr ::= expr GT expr */
#line 299 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">" , yymsp[0].minor.yy0); }
#line 1572 "parser\\epparser.c"
        break;
      case 86: /* lexpr ::= lexpr LAND lexpr */
#line 301 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "[" + yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data + "]";
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1581 "parser\\epparser.c"
        break;
      case 87: /* lexpr ::= lexpr LOR lexpr */
#line 307 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "EUDOr([" + yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data + "])";
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1590 "parser\\epparser.c"
        break;
      case 88: /* lexpr ::= LNOT lexpr */
#line 313 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = "EUDNot([" + yymsp[0].minor.yy0->data + "])";
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0);
}
#line 1598 "parser\\epparser.c"
        break;
      case 90: /* vdef_stmt ::= VAR nameList_nonEmpty */
#line 323 "parser\\epparser.lemon"
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
#line 1622 "parser\\epparser.c"
        break;
      case 91: /* vdefAssign_stmt ::= VAR nameList_nonEmpty ASSIGN exprList_nonEmpty */
#line 344 "parser\\epparser.lemon"
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
#line 1647 "parser\\epparser.c"
        break;
      case 92: /* cdef_stmt ::= CONST nameList_nonEmpty ASSIGN exprList_nonEmpty */
#line 366 "parser\\epparser.lemon"
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
#line 1669 "parser\\epparser.c"
        break;
      case 93: /* lvalue ::= NAME */
#line 387 "parser\\epparser.lemon"
{
    checkIsVariable(yymsp[0].minor.yy0->data);
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1677 "parser\\epparser.c"
        break;
      case 94: /* lvalue ::= NAME LSQBRACKET NAME RSQBRACKET */
#line 392 "parser\\epparser.lemon"
{
    checkIsConstant(yymsp[-3].minor.yy0->data);
    yymsp[-1].minor.yy0->data = "_ARRW(" + yymsp[-3].minor.yy0->data + ", " + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
    delete yymsp[-3].minor.yy0;
}
#line 1687 "parser\\epparser.c"
        break;
      case 95: /* lvalue ::= NAME PERIOD NAME */
#line 399 "parser\\epparser.lemon"
{
    checkIsConstant(yymsp[-2].minor.yy0->data);
    yymsp[0].minor.yy0->data = "_ATTW(" + yymsp[-2].minor.yy0->data + ", '" + yymsp[0].minor.yy0->data + "')";
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0);
    delete yymsp[-2].minor.yy0;
}
#line 1697 "parser\\epparser.c"
        break;
      case 98: /* assign_stmt ::= lvalue ASSIGN expr */
#line 408 "parser\\epparser.lemon"
{
    ps->gen << yymsp[-2].minor.yy0->data << " << (" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 1705 "parser\\epparser.c"
        break;
      case 99: /* assign_stmt ::= lvalueList_nonEmpty ASSIGN exprList_nonEmpty */
#line 413 "parser\\epparser.lemon"
{
    ps->gen << "_SV([" << yymsp[-2].minor.yy0->data << "], [" << yymsp[0].minor.yy0->data << "])" << std::endl;
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 1713 "parser\\epparser.c"
        break;
      case 100: /* if_start ::= IF */
#line 419 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDIf()" << std::endl;
}
#line 1721 "parser\\epparser.c"
        break;
      case 101: /* if_header ::= if_start LPAREN lexpr RPAREN */
      case 110: /* while_header ::= while_start LPAREN lexpr RPAREN */ yytestcase(yyruleno==110);
#line 423 "parser\\epparser.lemon"
{
    ps->gen << "if " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data << "):" << std::endl;
    ps->gen.indent();
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1731 "parser\\epparser.c"
        break;
      case 103: /* elif_start ::= ELSE IF */
#line 431 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen.unindent(false);
    ps->gen << yygotominor.yy0->data << " = EUDElseIf()" << std::endl;
}
#line 1740 "parser\\epparser.c"
        break;
      case 104: /* elif_header ::= elif_start LPAREN lexpr RPAREN */
#line 437 "parser\\epparser.lemon"
{
    ps->gen << "if " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data <<"):" << std::endl;
    ps->gen.indent();
}
#line 1748 "parser\\epparser.c"
        break;
      case 106: /* else_header ::= ELSE */
#line 444 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "if EUDElse()():" << std::endl;
    ps->gen.indent();
}
#line 1757 "parser\\epparser.c"
        break;
      case 107: /* if_stmt ::= if_block */
      case 108: /* if_stmt ::= if_block else_header stmt */ yytestcase(yyruleno==108);
#line 450 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndIf()" << std::endl;
}
#line 1766 "parser\\epparser.c"
        break;
      case 109: /* while_start ::= WHILE */
#line 462 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDWhile()" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1775 "parser\\epparser.c"
        break;
      case 111: /* while_stmt ::= while_header stmt */
#line 474 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndWhile()" << std::endl;
}
#line 1783 "parser\\epparser.c"
        break;
      case 112: /* for_opener ::= FOR LPAREN */
      case 127: /* foreach_opener ::= FOREACH LPAREN */ yytestcase(yyruleno==127);
#line 480 "parser\\epparser.lemon"
{
    ps->closure.pushScope();
}
#line 1791 "parser\\epparser.c"
        break;
      case 122: /* for_header1 ::= for_opener for_init_stmt SEMICOLON */
#line 496 "parser\\epparser.lemon"
{
    // opening for lexpr
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDWhile()" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1801 "parser\\epparser.c"
        break;
      case 123: /* for_header2 ::= for_header1 lexpr SEMICOLON */
#line 503 "parser\\epparser.lemon"
{
    ps->gen << "if " << yymsp[-2].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data << "):" << std::endl;
    ps->gen.indent();
    delete yymsp[-2].minor.yy0; delete yymsp[-1].minor.yy0;

    // Opening for assign_statement
    yygotominor.yy0 = genTemp(yymsp[-1].minor.yy0);
    ps->gen << "def " << yygotominor.yy0->data <<"():" << std::endl;
    ps->gen.indent();
}
#line 1815 "parser\\epparser.c"
        break;
      case 124: /* for_header ::= for_header2 for_action_stmt_nonEmpty RPAREN */
#line 514 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-2].minor.yy0;
    ps->gen.unindent(false);
}
#line 1823 "parser\\epparser.c"
        break;
      case 125: /* for_header ::= for_header2 RPAREN */
#line 519 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
    ps->gen << "pass" << std::endl;
    ps->gen.unindent(false);
}
#line 1832 "parser\\epparser.c"
        break;
      case 126: /* for_stmt ::= for_header stmt */
#line 525 "parser\\epparser.lemon"
{
    ps->gen << yymsp[-1].minor.yy0->data << "()" << std::endl;
    ps->gen.unindent(false);
    ps->gen << "EUDEndWhile()" << std::endl;
    ps->closure.popScope();
}
#line 1842 "parser\\epparser.c"
        break;
      case 128: /* foreach_header ::= foreach_opener nameList_nonEmpty COLON exprList_nonEmpty RPAREN */
#line 539 "parser\\epparser.lemon"
{
    commaListIter(yymsp[-3].minor.yy0->data, [&](std::string& s) {
        ps->closure.defVariable(s);
    });
    ps->gen << "for " << yymsp[-3].minor.yy0->data << " in " << yymsp[-1].minor.yy0->data << ":" << std::endl;
    ps->gen.indent();
}
#line 1853 "parser\\epparser.c"
        break;
      case 130: /* continue_stmt ::= CONTINUE */
#line 555 "parser\\epparser.lemon"
{
    ps->gen << "EUDContinue()" << std::endl;
}
#line 1860 "parser\\epparser.c"
        break;
      case 131: /* break_stmt ::= BREAK */
#line 559 "parser\\epparser.lemon"
{
    ps->gen << "EUDBreak()" << std::endl;
}
#line 1867 "parser\\epparser.c"
        break;
      case 132: /* return_stmt ::= RETURN exprList */
#line 566 "parser\\epparser.lemon"
{
    ps->gen << "EUDReturn(" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1875 "parser\\epparser.c"
        break;
      case 133: /* lexpr ::= CONDITIONNAME LPAREN fArgs RPAREN */
#line 574 "parser\\epparser.lemon"
{
    yymsp[-3].minor.yy0->data = yymsp[-3].minor.yy0->data + "(" + yymsp[-1].minor.yy0->data + ")";
    delete yymsp[-1].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 1884 "parser\\epparser.c"
        break;
      case 134: /* lexpr ::= CONDITIONNAME LPAREN RPAREN */
#line 580 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + "()";
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1892 "parser\\epparser.c"
        break;
      case 135: /* action ::= ACTIONNAME LPAREN fArgs RPAREN SEMICOLON */
#line 585 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[-4].minor.yy0);
    yygotominor.yy0->data =  yymsp[-4].minor.yy0->data + "(" + yymsp[-2].minor.yy0->data + ")";
    delete yymsp[-4].minor.yy0; delete yymsp[-2].minor.yy0;
}
#line 1901 "parser\\epparser.c"
        break;
      case 136: /* actions ::= action action */
      case 137: /* actions ::= actions action */ yytestcase(yyruleno==137);
#line 591 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
    yymsp[-1].minor.yy0->data += ",\n" + yymsp[0].minor.yy0->data;
    delete yymsp[0].minor.yy0;
}
#line 1911 "parser\\epparser.c"
        break;
      case 138: /* actionStmt ::= action */
#line 603 "parser\\epparser.lemon"
{
    ps->gen << "DoActions(" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1919 "parser\\epparser.c"
        break;
      case 139: /* actionStmt ::= actions */
#line 608 "parser\\epparser.lemon"
{
    ps->gen << "DoActions([" << std::endl;
    ps->gen.indent();
    ps->gen << yymsp[0].minor.yy0->data << std::endl;
    ps->gen.unindent(false);
    ps->gen << "])" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1931 "parser\\epparser.c"
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
      /* (18) stmt ::= lbracket return_stmt SEMICOLON rbracket */ yytestcase(yyruleno==18);
      /* (19) stmt ::= lbracket bodyStmtList rbracket */ yytestcase(yyruleno==19);
      /* (20) stmt ::= lbracket bodyStmtList return_stmt SEMICOLON rbracket */ yytestcase(yyruleno==20);
      /* (22) bodyStmt ::= SEMICOLON */ yytestcase(yyruleno==22);
      /* (23) bodyStmt ::= vdef_stmt SEMICOLON */ yytestcase(yyruleno==23);
      /* (24) bodyStmt ::= vdefAssign_stmt SEMICOLON */ yytestcase(yyruleno==24);
      /* (25) bodyStmt ::= cdef_stmt SEMICOLON */ yytestcase(yyruleno==25);
      /* (26) bodyStmt ::= assign_stmt SEMICOLON */ yytestcase(yyruleno==26);
      /* (28) bodyStmt ::= actionStmt */ yytestcase(yyruleno==28);
      /* (29) bodyStmt ::= if_stmt */ yytestcase(yyruleno==29);
      /* (30) bodyStmt ::= while_stmt */ yytestcase(yyruleno==30);
      /* (31) bodyStmt ::= for_stmt */ yytestcase(yyruleno==31);
      /* (32) bodyStmt ::= foreach_stmt */ yytestcase(yyruleno==32);
      /* (33) bodyStmt ::= continue_stmt SEMICOLON */ yytestcase(yyruleno==33);
      /* (34) bodyStmt ::= break_stmt SEMICOLON */ yytestcase(yyruleno==34);
      /* (35) bodyStmtList ::= bodyStmt */ yytestcase(yyruleno==35);
      /* (36) bodyStmtList ::= bodyStmtList bodyStmt */ yytestcase(yyruleno==36);
      /* (102) if_block ::= if_header stmt */ yytestcase(yyruleno==102);
      /* (105) if_block ::= if_block elif_header stmt */ yytestcase(yyruleno==105);
      /* (113) for_init_stmt_nonEmpty ::= vdef_stmt */ yytestcase(yyruleno==113);
      /* (114) for_init_stmt_nonEmpty ::= vdefAssign_stmt */ yytestcase(yyruleno==114);
      /* (115) for_init_stmt_nonEmpty ::= cdef_stmt */ yytestcase(yyruleno==115);
      /* (116) for_init_stmt_nonEmpty ::= assign_stmt */ yytestcase(yyruleno==116);
      /* (117) for_init_stmt_nonEmpty ::= for_init_stmt_nonEmpty COMMA for_init_stmt_nonEmpty */ yytestcase(yyruleno==117);
      /* (118) for_init_stmt ::= for_init_stmt_nonEmpty */ yytestcase(yyruleno==118);
      /* (119) for_init_stmt ::= */ yytestcase(yyruleno==119);
      /* (120) for_action_stmt_nonEmpty ::= assign_stmt */ yytestcase(yyruleno==120);
      /* (121) for_action_stmt_nonEmpty ::= for_action_stmt_nonEmpty COMMA for_action_stmt_nonEmpty */ yytestcase(yyruleno==121);
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
#line 2019 "parser\\epparser.c"
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
#line 622 "parser\\epparser.lemon"


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
#line 2272 "parser\\epparser.c"
