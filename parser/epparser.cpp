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
#define YYNOCODE 117
#define YYACTIONTYPE unsigned short int
#define ParseTOKENTYPE Token*
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  int yy233;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL  ParserStruct* ps ;
#define ParseARG_PDECL , ParserStruct* ps 
#define ParseARG_FETCH  ParserStruct* ps  = yypParser->ps 
#define ParseARG_STORE yypParser->ps  = ps 
#define YYNSTATE 277
#define YYNRULE 141
#define YYERRORSYMBOL 58
#define YYERRSYMDT yy233
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
#define YY_ACTTAB_COUNT (898)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   168,   54,   52,   50,   51,   49,  171,  164,  162,   50,
 /*    10 */    51,   49,  266,  264,  167,    2,  155,  256,  119,  163,
 /*    20 */   161,  160,  249,  248,  247,  246,  245,  159,  158,  115,
 /*    30 */     7,    3,   31,  171,  127,  153,  268,  120,   99,  117,
 /*    40 */     8,   56,  124,  122,   73,  114,    6,   10,  153,   98,
 /*    50 */   127,   17,   32,    5,   61,    4,   60,   59,  168,  109,
 /*    60 */    73,  184,   23,   24,  153,  164,  162,  173,   65,   63,
 /*    70 */   209,  264,  167,    2,  275,  256,  123,  163,  161,  160,
 /*    80 */   249,  248,  247,  246,  245,  159,  158,  273,  270,  240,
 /*    90 */   272,  235,  127,  153,  267,  120,   99,  117,    8,   56,
 /*   100 */   271,  214,   73,  114,    6,   10,  153,  152,  152,   17,
 /*   110 */    32,    5,   61,    4,   60,   59,  168,   74,   71,  130,
 /*   120 */   128,  153,  153,  164,  162,   23,   24,   68,  206,  264,
 /*   130 */   167,    2,  171,  256,  269,  163,  161,  160,  249,  248,
 /*   140 */   247,  246,  245,  159,  158,   57,   29,  171,  265,  195,
 /*   150 */   127,  153,   98,  120,   99,  117,    8,   56,  191,  121,
 /*   160 */    73,  114,    6,   10,  153,  152,  152,   17,   32,    5,
 /*   170 */    61,    4,   60,   59,  168,   74,   90,  130,  107,  153,
 /*   180 */   153,  164,  162,   28,   62,  263,  203,  264,  167,    2,
 /*   190 */    67,  256,  171,  163,  161,  160,  249,  248,  247,  246,
 /*   200 */   245,  159,  158,  419,   11,   23,   24,   66,  127,  153,
 /*   210 */   254,  120,   99,  117,    8,   56,  253,  118,   73,  114,
 /*   220 */     6,   10,  153,  152,  252,   17,   32,    5,   61,    4,
 /*   230 */    60,   59,  168,   74,  210,  130,  129,  153,  251,  164,
 /*   240 */   162,  250,   27,  244,  190,  264,  167,    2,  243,  256,
 /*   250 */    33,  163,  161,  160,  249,  248,  247,  246,  245,  159,
 /*   260 */   158,  156,  335,  154,  336,   30,  155,  153,  157,  120,
 /*   270 */    99,  117,    8,   56,   15,  151,  194,  114,    6,   10,
 /*   280 */   192,  150,  127,   17,   32,    5,   61,    4,   60,   59,
 /*   290 */   168,   95,   73,  120,   99,  188,  153,  164,  162,  149,
 /*   300 */   148,  239,  187,  264,  167,    2,  193,  256,  146,  163,
 /*   310 */   161,  160,  249,  248,  247,  246,  245,  159,  158,   25,
 /*   320 */   335,  142,  143,  140,   55,  153,  147,  120,   99,  117,
 /*   330 */     8,   56,  234,  139,  194,  114,    6,   10,  233,  152,
 /*   340 */   137,   17,   32,    5,   61,    4,   60,   59,  168,   69,
 /*   350 */   136,  120,   99,  153,   92,  164,  162,  232,  134,  133,
 /*   360 */   180,  264,  167,    2,   97,  256,  231,  163,  161,  160,
 /*   370 */   249,  248,  247,  246,  245,  159,  158,   24,   13,   23,
 /*   380 */    24,   26,  152,  153,  219,  120,   99,  117,    8,   56,
 /*   390 */   217,  126,   70,  114,    6,   10,  153,  152,   64,   17,
 /*   400 */    32,    5,   61,    4,   60,   59,  105,   74,  207,  220,
 /*   410 */   216,  153,   30,  164,  162,   34,  215,  213,   20,  178,
 /*   420 */   166,    2,  208,  256,    1,  163,  161,  160,  249,  248,
 /*   430 */   247,  246,  245,  159,  158,   19,   23,   24,   18,  202,
 /*   440 */   152,  153,   12,  120,   99,  117,    8,   56,  196,  189,
 /*   450 */    69,  114,    6,   10,  153,  224,  152,   17,   32,    5,
 /*   460 */    61,    4,   60,   59,  241,  204,   91,   14,  183,  106,
 /*   470 */   153,  164,  162,  179,  270,  259,  172,  242,  165,    2,
 /*   480 */   258,  256,  102,  163,  161,  160,  249,  248,  247,  246,
 /*   490 */   245,  159,  158,  260,  257,  125,  100,  212,  101,  153,
 /*   500 */    98,  120,   99,  117,    8,   56,  182,  108,  181,  114,
 /*   510 */     6,   10,   96,  104,  103,   17,   32,    5,   61,    4,
 /*   520 */    60,   59,  420,   40,   38,   37,   36,   35,   39,   45,
 /*   530 */    44,   46,   48,   47,   54,   52,   50,   51,   49,  116,
 /*   540 */   420,  420,  420,   94,  255,  420,  420,  420,  420,  420,
 /*   550 */   262,  261,   45,   44,   46,   48,   47,   54,   52,   50,
 /*   560 */    51,   49,   65,   63,  211,  420,  205,  113,  110,  152,
 /*   570 */   186,  185,   16,  420,  108,  237,  420,   94,  255,  230,
 /*   580 */   420,  420,  420,  153,  262,  260,   45,   44,   46,   48,
 /*   590 */    47,   54,   52,   50,   51,   49,   65,   63,  211,  420,
 /*   600 */   205,  113,  110,   22,  186,  185,   16,  277,  108,   48,
 /*   610 */    47,   54,   52,   50,   51,   49,   43,   42,  420,  420,
 /*   620 */   420,  420,   41,  238,   93,  420,  420,  420,  420,   53,
 /*   630 */    21,  420,  420,  420,  420,  174,  420,  170,  145,  144,
 /*   640 */   141,  138,  135,   43,   42,  420,  420,  420,  420,   41,
 /*   650 */   238,   93,   58,   63,  131,  420,   53,   46,   48,   47,
 /*   660 */    54,   52,   50,   51,   49,  145,  144,  141,  138,  135,
 /*   670 */    43,   42,  420,  420,  420,  152,   41,  238,   93,  420,
 /*   680 */   420,  131,  420,   53,  218,  229,  420,  420,  420,  153,
 /*   690 */   221,  420,  145,  144,  141,  138,  135,   94,  255,  420,
 /*   700 */   420,  420,  420,  420,  262,   44,   46,   48,   47,   54,
 /*   710 */    52,   50,   51,   49,  420,  420,   65,   63,  211,  152,
 /*   720 */   205,  113,  110,  420,  186,  185,   16,  420,  108,   69,
 /*   730 */   152,  420,  420,  153,  132,   43,   42,  152,  420,  152,
 /*   740 */    69,   41,  238,   93,  153,  223,  420,   69,   53,   69,
 /*   750 */   420,  153,  222,  153,   89,  221,  420,  145,  144,  141,
 /*   760 */   138,  135,   45,   44,   46,   48,   47,   54,   52,   50,
 /*   770 */    51,   49,  420,  201,  199,  420,   43,   42,  201,  199,
 /*   780 */   420,  236,   41,  238,   93,  200,  198,  420,  420,   53,
 /*   790 */   200,  198,  420,  420,  420,  420,  420,  152,  145,  144,
 /*   800 */   141,  138,  135,  120,   99,  420,  420,   69,  120,   99,
 /*   810 */   420,  153,   88,  420,  112,  111,  152,  420,  420,  197,
 /*   820 */   420,  276,  177,  274,  176,  175,   69,  169,    9,  152,
 /*   830 */   153,   87,  152,  420,  420,  152,  420,  420,  420,   69,
 /*   840 */   152,  152,  228,  153,   86,   85,  153,  152,  152,  153,
 /*   850 */    84,   83,  420,  152,  153,  153,  152,   81,   82,  152,
 /*   860 */   420,  153,  153,  227,  152,  152,  226,  153,  420,  225,
 /*   870 */   153,  152,  420,  153,   80,   79,  420,  152,  153,  153,
 /*   880 */   152,   78,  152,  152,  420,  153,  420,   77,  420,  420,
 /*   890 */    76,  153,   75,   72,  153,  420,  153,  153,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    58,   18,   19,   20,   21,   22,    2,   65,   66,   20,
 /*    10 */    21,   22,   70,   71,   72,   73,   35,   75,   37,   77,
 /*    20 */    78,   79,   80,   81,   82,   83,   84,   85,   86,  100,
 /*    30 */   101,  102,    1,    2,   79,   93,   32,   95,   96,   97,
 /*    40 */    98,   99,    2,   88,   89,  103,  104,  105,   93,   26,
 /*    50 */    79,  109,  110,  111,  112,  113,  114,  115,   58,   88,
 /*    60 */    89,   90,    3,    4,   93,   65,   66,   26,   45,   46,
 /*    70 */    70,   71,   72,   73,   27,   75,   36,   77,   78,   79,
 /*    80 */    80,   81,   82,   83,   84,   85,   86,   27,   26,   36,
 /*    90 */    27,   32,   79,   93,   32,   95,   96,   97,   98,   99,
 /*   100 */    26,   88,   89,  103,  104,  105,   93,   79,   79,  109,
 /*   110 */   110,  111,  112,  113,  114,  115,   58,   89,   89,   91,
 /*   120 */    92,   93,   93,   65,   66,    3,    4,   29,   70,   71,
 /*   130 */    72,   73,    2,   75,   26,   77,   78,   79,   80,   81,
 /*   140 */    82,   83,   84,   85,   86,   31,    1,    2,   27,   27,
 /*   150 */    79,   93,   26,   95,   96,   97,   98,   99,   32,   88,
 /*   160 */    89,  103,  104,  105,   93,   79,   79,  109,  110,  111,
 /*   170 */   112,  113,  114,  115,   58,   89,   89,   91,   92,   93,
 /*   180 */    93,   65,   66,    1,    2,   27,   70,   71,   72,   73,
 /*   190 */    27,   75,    2,   77,   78,   79,   80,   81,   82,   83,
 /*   200 */    84,   85,   86,   60,   61,    3,    4,   27,   79,   93,
 /*   210 */    27,   95,   96,   97,   98,   99,   27,   88,   89,  103,
 /*   220 */   104,  105,   93,   79,   27,  109,  110,  111,  112,  113,
 /*   230 */   114,  115,   58,   89,   32,   91,   92,   93,   27,   65,
 /*   240 */    66,   27,   52,   27,   70,   71,   72,   73,   27,   75,
 /*   250 */     2,   77,   78,   79,   80,   81,   82,   83,   84,   85,
 /*   260 */    86,   26,   31,   26,   31,    2,   35,   93,   37,   95,
 /*   270 */    96,   97,   98,   99,   31,   35,   78,  103,  104,  105,
 /*   280 */    32,   35,   79,  109,  110,  111,  112,  113,  114,  115,
 /*   290 */    58,   88,   89,   95,   96,   32,   93,   65,   66,   25,
 /*   300 */    36,   36,   70,   71,   72,   73,  108,   75,   26,   77,
 /*   310 */    78,   79,   80,   81,   82,   83,   84,   85,   86,   31,
 /*   320 */    31,   38,   31,   31,   35,   93,   37,   95,   96,   97,
 /*   330 */    98,   99,   32,   38,   78,  103,  104,  105,   32,   79,
 /*   340 */    31,  109,  110,  111,  112,  113,  114,  115,   58,   89,
 /*   350 */    38,   95,   96,   93,   94,   65,   66,   32,   31,   38,
 /*   360 */    70,   71,   72,   73,  108,   75,   32,   77,   78,   79,
 /*   370 */    80,   81,   82,   83,   84,   85,   86,    4,   31,    3,
 /*   380 */     4,    2,   79,   93,   32,   95,   96,   97,   98,   99,
 /*   390 */    32,   35,   89,  103,  104,  105,   93,   79,   35,  109,
 /*   400 */   110,  111,  112,  113,  114,  115,   58,   89,   32,   91,
 /*   410 */    25,   93,    2,   65,   66,    1,   36,   26,   31,   71,
 /*   420 */    72,   73,   47,   75,   76,   77,   78,   79,   80,   81,
 /*   430 */    82,   83,   84,   85,   86,   31,    3,    4,   31,   31,
 /*   440 */    79,   93,    2,   95,   96,   97,   98,   99,   27,   31,
 /*   450 */    89,  103,  104,  105,   93,   94,   79,  109,  110,  111,
 /*   460 */   112,  113,  114,  115,   58,   32,   89,   31,   27,   32,
 /*   470 */    93,   65,   66,   34,   26,   74,   67,   71,   72,   73,
 /*   480 */    74,   75,   67,   77,   78,   79,   80,   81,   82,   83,
 /*   490 */    84,   85,   86,   34,   74,   25,   67,   95,   87,   93,
 /*   500 */    26,   95,   96,   97,   98,   99,  114,   57,  114,  103,
 /*   510 */   104,  105,   67,   67,   67,  109,  110,  111,  112,  113,
 /*   520 */   114,  115,  116,    7,    8,    9,   10,   11,   12,   13,
 /*   530 */    14,   15,   16,   17,   18,   19,   20,   21,   22,   48,
 /*   540 */   116,  116,  116,   26,   27,  116,  116,  116,  116,  116,
 /*   550 */    33,   34,   13,   14,   15,   16,   17,   18,   19,   20,
 /*   560 */    21,   22,   45,   46,   47,  116,   49,   50,   51,   79,
 /*   570 */    53,   54,   55,  116,   57,   36,  116,   26,   27,   89,
 /*   580 */   116,  116,  116,   93,   33,   34,   13,   14,   15,   16,
 /*   590 */    17,   18,   19,   20,   21,   22,   45,   46,   47,  116,
 /*   600 */    49,   50,   51,    5,   53,   54,   55,    0,   57,   16,
 /*   610 */    17,   18,   19,   20,   21,   22,   18,   19,  116,  116,
 /*   620 */   116,  116,   24,   25,   26,  116,  116,  116,  116,   31,
 /*   630 */     5,  116,  116,  116,  116,   28,  116,   30,   40,   41,
 /*   640 */    42,   43,   44,   18,   19,  116,  116,  116,  116,   24,
 /*   650 */    25,   26,   45,   46,   56,  116,   31,   15,   16,   17,
 /*   660 */    18,   19,   20,   21,   22,   40,   41,   42,   43,   44,
 /*   670 */    18,   19,  116,  116,  116,   79,   24,   25,   26,  116,
 /*   680 */   116,   56,  116,   31,   32,   89,  116,  116,  116,   93,
 /*   690 */    38,  116,   40,   41,   42,   43,   44,   26,   27,  116,
 /*   700 */   116,  116,  116,  116,   33,   14,   15,   16,   17,   18,
 /*   710 */    19,   20,   21,   22,  116,  116,   45,   46,   47,   79,
 /*   720 */    49,   50,   51,  116,   53,   54,   55,  116,   57,   89,
 /*   730 */    79,  116,  116,   93,   94,   18,   19,   79,  116,   79,
 /*   740 */    89,   24,   25,   26,   93,   94,  116,   89,   31,   89,
 /*   750 */   116,   93,   94,   93,   94,   38,  116,   40,   41,   42,
 /*   760 */    43,   44,   13,   14,   15,   16,   17,   18,   19,   20,
 /*   770 */    21,   22,  116,   65,   66,  116,   18,   19,   65,   66,
 /*   780 */   116,   32,   24,   25,   26,   77,   78,  116,  116,   31,
 /*   790 */    77,   78,  116,  116,  116,  116,  116,   79,   40,   41,
 /*   800 */    42,   43,   44,   95,   96,  116,  116,   89,   95,   96,
 /*   810 */   116,   93,   94,  116,  106,  107,   79,  116,  116,  106,
 /*   820 */   116,   62,   63,   64,   65,   66,   89,   68,   69,   79,
 /*   830 */    93,   94,   79,  116,  116,   79,  116,  116,  116,   89,
 /*   840 */    79,   79,   89,   93,   94,   89,   93,   79,   79,   93,
 /*   850 */    89,   89,  116,   79,   93,   93,   79,   89,   89,   79,
 /*   860 */   116,   93,   93,   89,   79,   79,   89,   93,  116,   89,
 /*   870 */    93,   79,  116,   93,   89,   89,  116,   79,   93,   93,
 /*   880 */    79,   89,   79,   79,  116,   93,  116,   89,  116,  116,
 /*   890 */    89,   93,   89,   89,   93,  116,   93,   93,
};
#define YY_SHIFT_USE_DFLT (-20)
#define YY_SHIFT_COUNT (177)
#define YY_SHIFT_MIN   (-19)
#define YY_SHIFT_MAX   (758)
static const short yy_shift_ofst[] = {
 /*     0 */   -20,  551,  517,  671,  671,  671,  671,  671,  671,  671,
 /*    10 */    23,  607,   23,  652,  717,  717,  758,  598,  598,  598,
 /*    20 */   598,  625,  625,  598,  598,  598,  717,  758,  758,  758,
 /*    30 */   758,  758,  126,  474,  758,  758,  758,  758,  758,  758,
 /*    40 */   758,  758,  758,  758,  758,  758,  758,  758,  758,  758,
 /*    50 */   758,  758,  758,  758,  758,  758,  491,   62,  448,  450,
 /*    60 */   450,  448,  474,  448,  470,  448,  459,  459,  448,  516,
 /*    70 */   749,  539,  573,  573,  573,  573,  573,  573,  573,  573,
 /*    80 */   573,  691,  642,  593,  -17,  -17,  122,  433,  376,  202,
 /*    90 */   -11,  -11,   59,  289,  231,  263,  190,  248,  -19,  182,
 /*   100 */   145,   40,   31,    4,  130,  439,  441,  437,  436,  410,
 /*   110 */   418,  421,  440,  408,  407,  404,  375,  387,  410,  391,
 /*   120 */   414,  410,  410,  380,  385,  264,  363,  356,  358,  352,
 /*   130 */   379,  347,  373,  334,  321,  327,  325,  312,  309,  306,
 /*   140 */   295,  292,  300,  283,  291,  288,  233,  282,  265,  264,
 /*   150 */   274,  246,  240,  243,   53,  237,  233,  235,  221,  216,
 /*   160 */   214,  211,  197,  189,  183,  180,  163,  158,  121,  114,
 /*   170 */   108,   74,  130,   98,   41,   63,   60,   47,
};
#define YY_REDUCE_USE_DFLT (-72)
#define YY_REDUCE_COUNT (68)
#define YY_REDUCE_MIN   (-71)
#define YY_REDUCE_MAX   (804)
static const short yy_reduce_ofst[] = {
 /*     0 */   143,  406,  348,  290,  232,  174,  116,   58,    0,  -58,
 /*    10 */   708,  759,  713,  144,   86,   28,  -29,  750,  737,  718,
 /*    20 */   660,  658,  651,  640,  361,  260,  318,  203,  129,   71,
 /*    30 */    13,  -45,  256,  198,  804,  803,  801,  798,  792,  786,
 /*    40 */   785,  780,  777,  774,  769,  768,  762,  761,  756,  753,
 /*    50 */   596,  490,  377,  303,   87,   29,  -71,  447,  446,  394,
 /*    60 */   392,  445,  402,  429,  411,  415,  420,  401,  409,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   278,  418,  418,  418,  418,  418,  418,  418,  418,  418,
 /*    10 */   397,  418,  418,  418,  333,  333,  324,  418,  418,  418,
 /*    20 */   418,  418,  418,  418,  418,  418,  418,  418,  418,  418,
 /*    30 */   418,  418,  418,  418,  418,  418,  418,  418,  418,  418,
 /*    40 */   418,  418,  418,  418,  418,  418,  418,  418,  418,  418,
 /*    50 */   418,  418,  418,  418,  418,  418,  385,  418,  418,  417,
 /*    60 */   416,  418,  418,  418,  418,  418,  418,  418,  418,  418,
 /*    70 */   418,  418,  376,  322,  330,  363,  362,  361,  360,  359,
 /*    80 */   358,  353,  354,  352,  351,  350,  418,  418,  418,  418,
 /*    90 */   345,  346,  418,  327,  371,  418,  418,  418,  371,  418,
 /*   100 */   418,  418,  368,  418,  368,  418,  418,  418,  418,  325,
 /*   110 */   418,  418,  396,  418,  418,  418,  384,  418,  377,  418,
 /*   120 */   374,  370,  369,  418,  418,  316,  418,  338,  418,  418,
 /*   130 */   334,  418,  365,  418,  418,  418,  418,  418,  418,  418,
 /*   140 */   418,  418,  418,  418,  418,  418,  328,  418,  418,  418,
 /*   150 */   418,  418,  338,  418,  418,  418,  373,  418,  418,  418,
 /*   160 */   418,  418,  418,  418,  418,  418,  418,  418,  418,  418,
 /*   170 */   418,  418,  284,  418,  418,  418,  418,  418,  313,  298,
 /*   180 */   386,  415,  414,  413,  410,  409,  408,  407,  406,  405,
 /*   190 */   404,  403,  402,  399,  398,  401,  400,  395,  394,  393,
 /*   200 */   392,  391,  390,  389,  388,  387,  383,  382,  381,  380,
 /*   210 */   379,  378,  375,  373,  323,  320,  317,  337,  412,  411,
 /*   220 */   332,  331,  367,  366,  364,  357,  356,  355,  349,  348,
 /*   230 */   347,  344,  343,  342,  341,  340,  339,  329,  326,  321,
 /*   240 */   372,  315,  314,  312,  311,  310,  309,  308,  307,  306,
 /*   250 */   305,  304,  303,  302,  301,  300,  299,  297,  296,  295,
 /*   260 */   293,  294,  292,  291,  290,  289,  288,  287,  286,  285,
 /*   270 */   318,  319,  283,  282,  281,  280,  279,
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
  "return_stmt",   "lbracket",      "rbracket",      "blockStmt",   
  "bodyStmtList",  "vdefAssign_stmt",  "assign_stmt",   "funcexpr",    
  "actionStmt",    "if_stmt",       "while_stmt",    "for_stmt",    
  "foreach_stmt",  "continue_stmt",  "break_stmt",    "numList_nonEmpty",
  "exprList_nonEmpty",  "expr",          "exprList",      "fArgs_nonEmpty",
  "fArgs",         "funcName",      "lexpr",         "lvalue",      
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
 /*  51 */ "expr ::= NAME PERIOD NAME",
 /*  52 */ "expr ::= NAME LSQBRACKET expr RSQBRACKET",
 /*  53 */ "fArgs_nonEmpty ::= expr",
 /*  54 */ "fArgs_nonEmpty ::= STRING",
 /*  55 */ "fArgs_nonEmpty ::= fArgs_nonEmpty COMMA fArgs_nonEmpty",
 /*  56 */ "fArgs ::=",
 /*  57 */ "fArgs ::= fArgs_nonEmpty",
 /*  58 */ "funcName ::= NAME",
 /*  59 */ "funcName ::= NAME PERIOD NAME",
 /*  60 */ "funcexpr ::= funcName LPAREN fArgs RPAREN",
 /*  61 */ "expr ::= funcexpr",
 /*  62 */ "expr ::= LPAREN expr RPAREN",
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
 /*  95 */ "lvalue ::= NAME LSQBRACKET NAME RSQBRACKET",
 /*  96 */ "lvalue ::= NAME PERIOD NAME",
 /*  97 */ "lvalueList_nonEmpty ::= lvalue",
 /*  98 */ "lvalueList_nonEmpty ::= lvalueList_nonEmpty COMMA lvalue",
 /*  99 */ "assign_stmt ::= lvalue ASSIGN expr",
 /* 100 */ "assign_stmt ::= lvalueList_nonEmpty ASSIGN exprList_nonEmpty",
 /* 101 */ "if_start ::= IF",
 /* 102 */ "if_header ::= if_start LPAREN lexpr RPAREN",
 /* 103 */ "if_block ::= if_header stmt",
 /* 104 */ "elif_start ::= ELSE IF",
 /* 105 */ "elif_header ::= elif_start LPAREN lexpr RPAREN",
 /* 106 */ "if_block ::= if_block elif_header stmt",
 /* 107 */ "else_header ::= ELSE",
 /* 108 */ "if_stmt ::= if_block",
 /* 109 */ "if_stmt ::= if_block else_header stmt",
 /* 110 */ "while_start ::= WHILE",
 /* 111 */ "while_header ::= while_start LPAREN lexpr RPAREN",
 /* 112 */ "while_stmt ::= while_header stmt",
 /* 113 */ "for_opener ::= FOR LPAREN",
 /* 114 */ "for_init_stmt_nonEmpty ::= vdef_stmt",
 /* 115 */ "for_init_stmt_nonEmpty ::= vdefAssign_stmt",
 /* 116 */ "for_init_stmt_nonEmpty ::= cdef_stmt",
 /* 117 */ "for_init_stmt_nonEmpty ::= assign_stmt",
 /* 118 */ "for_init_stmt_nonEmpty ::= for_init_stmt_nonEmpty COMMA for_init_stmt_nonEmpty",
 /* 119 */ "for_init_stmt ::= for_init_stmt_nonEmpty",
 /* 120 */ "for_init_stmt ::=",
 /* 121 */ "for_action_stmt_nonEmpty ::= assign_stmt",
 /* 122 */ "for_action_stmt_nonEmpty ::= for_action_stmt_nonEmpty COMMA for_action_stmt_nonEmpty",
 /* 123 */ "for_header1 ::= for_opener for_init_stmt SEMICOLON",
 /* 124 */ "for_header2 ::= for_header1 lexpr SEMICOLON",
 /* 125 */ "for_header ::= for_header2 for_action_stmt_nonEmpty RPAREN",
 /* 126 */ "for_header ::= for_header2 RPAREN",
 /* 127 */ "for_stmt ::= for_header stmt",
 /* 128 */ "foreach_opener ::= FOREACH LPAREN",
 /* 129 */ "foreach_header ::= foreach_opener nameList_nonEmpty COLON exprList_nonEmpty RPAREN",
 /* 130 */ "foreach_stmt ::= foreach_header stmt",
 /* 131 */ "continue_stmt ::= CONTINUE",
 /* 132 */ "break_stmt ::= BREAK",
 /* 133 */ "return_stmt ::= RETURN exprList",
 /* 134 */ "lexpr ::= CONDITIONNAME LPAREN fArgs RPAREN",
 /* 135 */ "lexpr ::= CONDITIONNAME LPAREN RPAREN",
 /* 136 */ "action ::= ACTIONNAME LPAREN fArgs RPAREN SEMICOLON",
 /* 137 */ "actions ::= action action",
 /* 138 */ "actions ::= actions action",
 /* 139 */ "actionStmt ::= action",
 /* 140 */ "actionStmt ::= actions",
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
#line 769 "parser\\epparser.c"
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
  { 75, 2 },
  { 75, 4 },
  { 75, 3 },
  { 75, 5 },
  { 75, 3 },
  { 71, 1 },
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
  { 76, 1 },
  { 76, 2 },
  { 76, 2 },
  { 87, 1 },
  { 87, 3 },
  { 67, 1 },
  { 67, 3 },
  { 88, 6 },
  { 89, 6 },
  { 88, 1 },
  { 88, 3 },
  { 90, 0 },
  { 90, 1 },
  { 89, 1 },
  { 89, 1 },
  { 89, 3 },
  { 89, 4 },
  { 91, 1 },
  { 91, 1 },
  { 91, 3 },
  { 92, 0 },
  { 92, 1 },
  { 93, 1 },
  { 93, 3 },
  { 79, 4 },
  { 89, 1 },
  { 89, 3 },
  { 89, 4 },
  { 89, 4 },
  { 89, 4 },
  { 89, 4 },
  { 89, 4 },
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
  { 89, 2 },
  { 89, 2 },
  { 89, 2 },
  { 94, 3 },
  { 94, 3 },
  { 94, 3 },
  { 94, 3 },
  { 94, 3 },
  { 94, 3 },
  { 94, 3 },
  { 94, 3 },
  { 94, 2 },
  { 94, 3 },
  { 65, 2 },
  { 77, 4 },
  { 66, 4 },
  { 95, 1 },
  { 95, 4 },
  { 95, 3 },
  { 96, 1 },
  { 96, 3 },
  { 78, 3 },
  { 78, 3 },
  { 97, 1 },
  { 98, 4 },
  { 99, 2 },
  { 100, 2 },
  { 101, 4 },
  { 99, 3 },
  { 102, 1 },
  { 81, 1 },
  { 81, 3 },
  { 103, 1 },
  { 104, 4 },
  { 82, 2 },
  { 105, 2 },
  { 106, 1 },
  { 106, 1 },
  { 106, 1 },
  { 106, 1 },
  { 106, 3 },
  { 107, 1 },
  { 107, 0 },
  { 108, 1 },
  { 108, 3 },
  { 109, 3 },
  { 110, 3 },
  { 111, 3 },
  { 111, 2 },
  { 83, 2 },
  { 112, 2 },
  { 113, 5 },
  { 84, 2 },
  { 85, 1 },
  { 86, 1 },
  { 72, 2 },
  { 94, 4 },
  { 94, 3 },
  { 114, 5 },
  { 115, 2 },
  { 115, 2 },
  { 80, 1 },
  { 80, 1 },
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
#line 1214 "parser\\epparser.c"
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
#line 1227 "parser\\epparser.c"
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
#line 1246 "parser\\epparser.c"
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
#line 1257 "parser\\epparser.c"
        break;
      case 11: /* fdef_chunk ::= function_header stmt */
      case 130: /* foreach_stmt ::= foreach_header stmt */ yytestcase(yyruleno==130);
#line 112 "parser\\epparser.lemon"
{
    ps->gen.unindent(true);
    ps->closure.popScope();
}
#line 1266 "parser\\epparser.c"
        break;
      case 12: /* stmt ::= error SEMICOLON */
#line 119 "parser\\epparser.lemon"
{ throw_error(6974, "Error while parsing statement"); }
#line 1271 "parser\\epparser.c"
        break;
      case 15: /* lbracket ::= LBRACKET */
#line 125 "parser\\epparser.lemon"
{ ps->closure.pushScope(); }
#line 1276 "parser\\epparser.c"
        break;
      case 16: /* rbracket ::= RBRACKET */
#line 126 "parser\\epparser.lemon"
{ ps->closure.popScope(); }
#line 1281 "parser\\epparser.c"
        break;
      case 17: /* blockStmt ::= lbracket RBRACKET */
#line 128 "parser\\epparser.lemon"
{
    ps->gen << "pass" << std::endl;
    ps->closure.popScope();
}
#line 1289 "parser\\epparser.c"
        break;
      case 21: /* blockStmt ::= lbracket error RBRACKET */
#line 135 "parser\\epparser.lemon"
{
    throw_error(6298, "Block not terminated properly.");
    ps->closure.popScope();
}
#line 1297 "parser\\epparser.c"
        break;
      case 28: /* bodyStmt ::= funcexpr SEMICOLON */
#line 146 "parser\\epparser.lemon"
{ ps->gen << yymsp[-1].minor.yy0->data << std::endl; }
#line 1302 "parser\\epparser.c"
        break;
      case 38: /* bodyStmtList ::= bodyStmtList error */
#line 158 "parser\\epparser.lemon"
{
    throw_error(8510, "Incomplete statement");
}
#line 1309 "parser\\epparser.c"
        break;
      case 39: /* numList_nonEmpty ::= NUMBER */
      case 41: /* nameList_nonEmpty ::= NAME */ yytestcase(yyruleno==41);
      case 45: /* exprList_nonEmpty ::= expr */ yytestcase(yyruleno==45);
      case 48: /* exprList ::= exprList_nonEmpty */ yytestcase(yyruleno==48);
      case 49: /* expr ::= NUMBER */ yytestcase(yyruleno==49);
      case 53: /* fArgs_nonEmpty ::= expr */ yytestcase(yyruleno==53);
      case 54: /* fArgs_nonEmpty ::= STRING */ yytestcase(yyruleno==54);
      case 57: /* fArgs ::= fArgs_nonEmpty */ yytestcase(yyruleno==57);
      case 61: /* expr ::= funcexpr */ yytestcase(yyruleno==61);
      case 90: /* lexpr ::= LNOT LNOT lexpr */ yytestcase(yyruleno==90);
      case 97: /* lvalueList_nonEmpty ::= lvalue */ yytestcase(yyruleno==97);
#line 164 "parser\\epparser.lemon"
{ yygotominor.yy0 = yymsp[0].minor.yy0; }
#line 1324 "parser\\epparser.c"
        break;
      case 40: /* numList_nonEmpty ::= numList_nonEmpty COMMA NUMBER */
      case 42: /* nameList_nonEmpty ::= nameList_nonEmpty COMMA NAME */ yytestcase(yyruleno==42);
      case 98: /* lvalueList_nonEmpty ::= lvalueList_nonEmpty COMMA lvalue */ yytestcase(yyruleno==98);
#line 165 "parser\\epparser.lemon"
{ yygotominor.yy0 = commaConcat(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1331 "parser\\epparser.c"
        break;
      case 43: /* exprList_nonEmpty ::= funcexpr LSQBRACKET LSQBRACKET numList_nonEmpty RSQBRACKET RSQBRACKET */
#line 169 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "_SRET(" + yymsp[-5].minor.yy0->data + ", [" + yymsp[-2].minor.yy0->data + "])";
    delete yymsp[-5].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1340 "parser\\epparser.c"
        break;
      case 44: /* expr ::= funcexpr LSQBRACKET LSQBRACKET NUMBER RSQBRACKET RSQBRACKET */
#line 176 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-5].minor.yy0->data + "[" + yymsp[-2].minor.yy0->data + "]";
    delete yymsp[-5].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1349 "parser\\epparser.c"
        break;
      case 46: /* exprList_nonEmpty ::= exprList_nonEmpty COMMA exprList_nonEmpty */
#line 184 "parser\\epparser.lemon"
{ yygotominor.yy0 = new Token((yymsp[-2].minor.yy0->data) + ", " + (yymsp[0].minor.yy0->data), yymsp[0].minor.yy0); delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1354 "parser\\epparser.c"
        break;
      case 47: /* exprList ::= */
      case 56: /* fArgs ::= */ yytestcase(yyruleno==56);
#line 186 "parser\\epparser.lemon"
{ yygotominor.yy0 = genEmpty(); }
#line 1360 "parser\\epparser.c"
        break;
      case 50: /* expr ::= NAME */
#line 191 "parser\\epparser.lemon"
{
    checkIsRValue(yymsp[0].minor.yy0->data);
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1368 "parser\\epparser.c"
        break;
      case 51: /* expr ::= NAME PERIOD NAME */
#line 196 "parser\\epparser.lemon"
{
    checkIsConstant(yymsp[-2].minor.yy0->data);
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + "." + yymsp[0].minor.yy0->data;
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1378 "parser\\epparser.c"
        break;
      case 52: /* expr ::= NAME LSQBRACKET expr RSQBRACKET */
#line 203 "parser\\epparser.lemon"
{
    checkIsConstant(yymsp[-3].minor.yy0->data);
    yymsp[-3].minor.yy0->data = yymsp[-3].minor.yy0->data + "[" + yymsp[-1].minor.yy0->data + "]";
    delete yymsp[-1].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 1388 "parser\\epparser.c"
        break;
      case 55: /* fArgs_nonEmpty ::= fArgs_nonEmpty COMMA fArgs_nonEmpty */
#line 213 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data;
    yymsp[-2].minor.yy0->type = TOKEN_TEMP;
    yygotominor.yy0 = yymsp[-2].minor.yy0;
    delete yymsp[0].minor.yy0;
}
#line 1398 "parser\\epparser.c"
        break;
      case 58: /* funcName ::= NAME */
#line 223 "parser\\epparser.lemon"
{
    funcNamePreprocess(yymsp[0].minor.yy0->data);
    checkIsFunction(yymsp[0].minor.yy0->data);
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1407 "parser\\epparser.c"
        break;
      case 59: /* funcName ::= NAME PERIOD NAME */
#line 229 "parser\\epparser.lemon"
{
    // Preprocess name
    checkIsConstant(yymsp[-2].minor.yy0->data);
    yymsp[0].minor.yy0->data = yymsp[-2].minor.yy0->data + "." + yymsp[0].minor.yy0->data;
    delete yymsp[-2].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0);
}
#line 1418 "parser\\epparser.c"
        break;
      case 60: /* funcexpr ::= funcName LPAREN fArgs RPAREN */
#line 237 "parser\\epparser.lemon"
{
    // Preprocess yymsp[-3].minor.yy0
    yymsp[-3].minor.yy0->data += "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 1427 "parser\\epparser.c"
        break;
      case 62: /* expr ::= LPAREN expr RPAREN */
#line 246 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1435 "parser\\epparser.c"
        break;
      case 63: /* expr ::= L2V LPAREN lexpr RPAREN */
#line 251 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "_L2V(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = genTemp(yymsp[-1].minor.yy0);
}
#line 1443 "parser\\epparser.c"
        break;
      case 64: /* expr ::= MAPSTRING LPAREN STRING RPAREN */
#line 256 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetStringIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1451 "parser\\epparser.c"
        break;
      case 65: /* expr ::= UNIT LPAREN STRING RPAREN */
#line 261 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetUnitIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1459 "parser\\epparser.c"
        break;
      case 66: /* expr ::= SWITCH LPAREN STRING RPAREN */
#line 266 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetSwitchIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1467 "parser\\epparser.c"
        break;
      case 67: /* expr ::= LOCATION LPAREN STRING RPAREN */
#line 271 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetLocationIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1475 "parser\\epparser.c"
        break;
      case 68: /* expr ::= expr PLUS expr */
#line 277 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "+",  yymsp[0].minor.yy0); }
#line 1480 "parser\\epparser.c"
        break;
      case 69: /* expr ::= expr MINUS expr */
#line 278 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "-",  yymsp[0].minor.yy0); }
#line 1485 "parser\\epparser.c"
        break;
      case 70: /* expr ::= expr MULTIPLY expr */
#line 279 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "*",  yymsp[0].minor.yy0); }
#line 1490 "parser\\epparser.c"
        break;
      case 71: /* expr ::= expr DIVIDE expr */
#line 280 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "//", yymsp[0].minor.yy0); }
#line 1495 "parser\\epparser.c"
        break;
      case 72: /* expr ::= expr MOD expr */
#line 281 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "%",  yymsp[0].minor.yy0); }
#line 1500 "parser\\epparser.c"
        break;
      case 73: /* expr ::= expr LSHIFT expr */
#line 282 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<<", yymsp[0].minor.yy0); }
#line 1505 "parser\\epparser.c"
        break;
      case 74: /* expr ::= expr RSHIFT expr */
#line 283 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">>", yymsp[0].minor.yy0); }
#line 1510 "parser\\epparser.c"
        break;
      case 75: /* expr ::= expr BITAND expr */
#line 284 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "&",  yymsp[0].minor.yy0); }
#line 1515 "parser\\epparser.c"
        break;
      case 76: /* expr ::= expr BITOR expr */
#line 285 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "|",  yymsp[0].minor.yy0); }
#line 1520 "parser\\epparser.c"
        break;
      case 77: /* expr ::= expr BITXOR expr */
#line 286 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "^",  yymsp[0].minor.yy0); }
#line 1525 "parser\\epparser.c"
        break;
      case 78: /* expr ::= PLUS expr */
#line 289 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = +" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1530 "parser\\epparser.c"
        break;
      case 79: /* expr ::= MINUS expr */
#line 290 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = -" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1535 "parser\\epparser.c"
        break;
      case 80: /* expr ::= BITNOT expr */
#line 291 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = ~" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1540 "parser\\epparser.c"
        break;
      case 81: /* lexpr ::= expr EQ expr */
#line 295 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "==", yymsp[0].minor.yy0); }
#line 1545 "parser\\epparser.c"
        break;
      case 82: /* lexpr ::= expr NE expr */
#line 296 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "!=", yymsp[0].minor.yy0); }
#line 1550 "parser\\epparser.c"
        break;
      case 83: /* lexpr ::= expr LE expr */
#line 297 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<=", yymsp[0].minor.yy0); }
#line 1555 "parser\\epparser.c"
        break;
      case 84: /* lexpr ::= expr LT expr */
#line 298 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<",  yymsp[0].minor.yy0); }
#line 1560 "parser\\epparser.c"
        break;
      case 85: /* lexpr ::= expr GE expr */
#line 299 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">=", yymsp[0].minor.yy0); }
#line 1565 "parser\\epparser.c"
        break;
      case 86: /* lexpr ::= expr GT expr */
#line 300 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">" , yymsp[0].minor.yy0); }
#line 1570 "parser\\epparser.c"
        break;
      case 87: /* lexpr ::= lexpr LAND lexpr */
#line 302 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "[" + yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data + "]";
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1579 "parser\\epparser.c"
        break;
      case 88: /* lexpr ::= lexpr LOR lexpr */
#line 308 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "EUDOr([" + yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data + "])";
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1588 "parser\\epparser.c"
        break;
      case 89: /* lexpr ::= LNOT lexpr */
#line 314 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = "EUDNot([" + yymsp[0].minor.yy0->data + "])";
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0);
}
#line 1596 "parser\\epparser.c"
        break;
      case 91: /* vdef_stmt ::= VAR nameList_nonEmpty */
#line 324 "parser\\epparser.lemon"
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
#line 1620 "parser\\epparser.c"
        break;
      case 92: /* vdefAssign_stmt ::= VAR nameList_nonEmpty ASSIGN exprList_nonEmpty */
#line 345 "parser\\epparser.lemon"
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
#line 1645 "parser\\epparser.c"
        break;
      case 93: /* cdef_stmt ::= CONST nameList_nonEmpty ASSIGN exprList_nonEmpty */
#line 367 "parser\\epparser.lemon"
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
#line 1667 "parser\\epparser.c"
        break;
      case 94: /* lvalue ::= NAME */
#line 388 "parser\\epparser.lemon"
{
    checkIsVariable(yymsp[0].minor.yy0->data);
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1675 "parser\\epparser.c"
        break;
      case 95: /* lvalue ::= NAME LSQBRACKET NAME RSQBRACKET */
#line 393 "parser\\epparser.lemon"
{
    checkIsConstant(yymsp[-3].minor.yy0->data);
    yymsp[-1].minor.yy0->data = "_ARRW(" + yymsp[-3].minor.yy0->data + ", " + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
    delete yymsp[-3].minor.yy0;
}
#line 1685 "parser\\epparser.c"
        break;
      case 96: /* lvalue ::= NAME PERIOD NAME */
#line 400 "parser\\epparser.lemon"
{
    checkIsConstant(yymsp[-2].minor.yy0->data);
    yymsp[0].minor.yy0->data = "_ATTW(" + yymsp[-2].minor.yy0->data + ", '" + yymsp[0].minor.yy0->data + "')";
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0);
    delete yymsp[-2].minor.yy0;
}
#line 1695 "parser\\epparser.c"
        break;
      case 99: /* assign_stmt ::= lvalue ASSIGN expr */
#line 409 "parser\\epparser.lemon"
{
    ps->gen << yymsp[-2].minor.yy0->data << " << (" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 1703 "parser\\epparser.c"
        break;
      case 100: /* assign_stmt ::= lvalueList_nonEmpty ASSIGN exprList_nonEmpty */
#line 414 "parser\\epparser.lemon"
{
    ps->gen << "_SV([" << yymsp[-2].minor.yy0->data << "], [" << yymsp[0].minor.yy0->data << "])" << std::endl;
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 1711 "parser\\epparser.c"
        break;
      case 101: /* if_start ::= IF */
#line 420 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDIf()" << std::endl;
}
#line 1719 "parser\\epparser.c"
        break;
      case 102: /* if_header ::= if_start LPAREN lexpr RPAREN */
      case 111: /* while_header ::= while_start LPAREN lexpr RPAREN */ yytestcase(yyruleno==111);
#line 424 "parser\\epparser.lemon"
{
    ps->gen << "if " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data << "):" << std::endl;
    ps->gen.indent();
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1729 "parser\\epparser.c"
        break;
      case 104: /* elif_start ::= ELSE IF */
#line 432 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen.unindent(false);
    ps->gen << yygotominor.yy0->data << " = EUDElseIf()" << std::endl;
}
#line 1738 "parser\\epparser.c"
        break;
      case 105: /* elif_header ::= elif_start LPAREN lexpr RPAREN */
#line 438 "parser\\epparser.lemon"
{
    ps->gen << "if " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data <<"):" << std::endl;
    ps->gen.indent();
}
#line 1746 "parser\\epparser.c"
        break;
      case 107: /* else_header ::= ELSE */
#line 445 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "if EUDElse()():" << std::endl;
    ps->gen.indent();
}
#line 1755 "parser\\epparser.c"
        break;
      case 108: /* if_stmt ::= if_block */
      case 109: /* if_stmt ::= if_block else_header stmt */ yytestcase(yyruleno==109);
#line 451 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndIf()" << std::endl;
}
#line 1764 "parser\\epparser.c"
        break;
      case 110: /* while_start ::= WHILE */
#line 463 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDWhile()" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1773 "parser\\epparser.c"
        break;
      case 112: /* while_stmt ::= while_header stmt */
#line 475 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndWhile()" << std::endl;
}
#line 1781 "parser\\epparser.c"
        break;
      case 113: /* for_opener ::= FOR LPAREN */
      case 128: /* foreach_opener ::= FOREACH LPAREN */ yytestcase(yyruleno==128);
#line 481 "parser\\epparser.lemon"
{
    ps->closure.pushScope();
}
#line 1789 "parser\\epparser.c"
        break;
      case 123: /* for_header1 ::= for_opener for_init_stmt SEMICOLON */
#line 497 "parser\\epparser.lemon"
{
    // opening for lexpr
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDWhile()" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1799 "parser\\epparser.c"
        break;
      case 124: /* for_header2 ::= for_header1 lexpr SEMICOLON */
#line 504 "parser\\epparser.lemon"
{
    ps->gen << "if " << yymsp[-2].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data << "):" << std::endl;
    ps->gen.indent();
    delete yymsp[-2].minor.yy0; delete yymsp[-1].minor.yy0;

    // Opening for assign_statement
    yygotominor.yy0 = genTemp(yymsp[-1].minor.yy0);
    ps->gen << "def " << yygotominor.yy0->data <<"():" << std::endl;
    ps->gen.indent();
}
#line 1813 "parser\\epparser.c"
        break;
      case 125: /* for_header ::= for_header2 for_action_stmt_nonEmpty RPAREN */
#line 515 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-2].minor.yy0;
    ps->gen.unindent(false);
}
#line 1821 "parser\\epparser.c"
        break;
      case 126: /* for_header ::= for_header2 RPAREN */
#line 520 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
    ps->gen << "pass" << std::endl;
    ps->gen.unindent(false);
}
#line 1830 "parser\\epparser.c"
        break;
      case 127: /* for_stmt ::= for_header stmt */
#line 526 "parser\\epparser.lemon"
{
    ps->gen << yymsp[-1].minor.yy0->data << "()" << std::endl;
    ps->gen.unindent(false);
    ps->gen << "EUDEndWhile()" << std::endl;
    ps->closure.popScope();
}
#line 1840 "parser\\epparser.c"
        break;
      case 129: /* foreach_header ::= foreach_opener nameList_nonEmpty COLON exprList_nonEmpty RPAREN */
#line 540 "parser\\epparser.lemon"
{
    commaListIter(yymsp[-3].minor.yy0->data, [&](std::string& s) {
        ps->closure.defVariable(s);
    });
    ps->gen << "for " << yymsp[-3].minor.yy0->data << " in " << yymsp[-1].minor.yy0->data << ":" << std::endl;
    ps->gen.indent();
}
#line 1851 "parser\\epparser.c"
        break;
      case 131: /* continue_stmt ::= CONTINUE */
#line 556 "parser\\epparser.lemon"
{
    ps->gen << "EUDContinue()" << std::endl;
}
#line 1858 "parser\\epparser.c"
        break;
      case 132: /* break_stmt ::= BREAK */
#line 560 "parser\\epparser.lemon"
{
    ps->gen << "EUDBreak()" << std::endl;
}
#line 1865 "parser\\epparser.c"
        break;
      case 133: /* return_stmt ::= RETURN exprList */
#line 567 "parser\\epparser.lemon"
{
    ps->gen << "EUDReturn(" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1873 "parser\\epparser.c"
        break;
      case 134: /* lexpr ::= CONDITIONNAME LPAREN fArgs RPAREN */
#line 575 "parser\\epparser.lemon"
{
    yymsp[-3].minor.yy0->data = yymsp[-3].minor.yy0->data + "(" + yymsp[-1].minor.yy0->data + ")";
    delete yymsp[-1].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 1882 "parser\\epparser.c"
        break;
      case 135: /* lexpr ::= CONDITIONNAME LPAREN RPAREN */
#line 581 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + "()";
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1890 "parser\\epparser.c"
        break;
      case 136: /* action ::= ACTIONNAME LPAREN fArgs RPAREN SEMICOLON */
#line 586 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[-4].minor.yy0);
    yygotominor.yy0->data =  yymsp[-4].minor.yy0->data + "(" + yymsp[-2].minor.yy0->data + ")";
    delete yymsp[-4].minor.yy0; delete yymsp[-2].minor.yy0;
}
#line 1899 "parser\\epparser.c"
        break;
      case 137: /* actions ::= action action */
      case 138: /* actions ::= actions action */ yytestcase(yyruleno==138);
#line 592 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
    yymsp[-1].minor.yy0->data += ",\n" + yymsp[0].minor.yy0->data;
    delete yymsp[0].minor.yy0;
}
#line 1909 "parser\\epparser.c"
        break;
      case 139: /* actionStmt ::= action */
#line 604 "parser\\epparser.lemon"
{
    ps->gen << "DoActions(" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1917 "parser\\epparser.c"
        break;
      case 140: /* actionStmt ::= actions */
#line 609 "parser\\epparser.lemon"
{
    ps->gen << "DoActions([" << std::endl;
    ps->gen.indent();
    ps->gen << yymsp[0].minor.yy0->data << std::endl;
    ps->gen.unindent(false);
    ps->gen << "])" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1929 "parser\\epparser.c"
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
      /* (103) if_block ::= if_header stmt */ yytestcase(yyruleno==103);
      /* (106) if_block ::= if_block elif_header stmt */ yytestcase(yyruleno==106);
      /* (114) for_init_stmt_nonEmpty ::= vdef_stmt */ yytestcase(yyruleno==114);
      /* (115) for_init_stmt_nonEmpty ::= vdefAssign_stmt */ yytestcase(yyruleno==115);
      /* (116) for_init_stmt_nonEmpty ::= cdef_stmt */ yytestcase(yyruleno==116);
      /* (117) for_init_stmt_nonEmpty ::= assign_stmt */ yytestcase(yyruleno==117);
      /* (118) for_init_stmt_nonEmpty ::= for_init_stmt_nonEmpty COMMA for_init_stmt_nonEmpty */ yytestcase(yyruleno==118);
      /* (119) for_init_stmt ::= for_init_stmt_nonEmpty */ yytestcase(yyruleno==119);
      /* (120) for_init_stmt ::= */ yytestcase(yyruleno==120);
      /* (121) for_action_stmt_nonEmpty ::= assign_stmt */ yytestcase(yyruleno==121);
      /* (122) for_action_stmt_nonEmpty ::= for_action_stmt_nonEmpty COMMA for_action_stmt_nonEmpty */ yytestcase(yyruleno==122);
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
#line 2018 "parser\\epparser.c"
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
#line 623 "parser\\epparser.lemon"


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
#line 2271 "parser\\epparser.c"
