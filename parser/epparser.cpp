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
#define YYNSTATE 278
#define YYNRULE 142
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
 /*     0 */   104,   54,   52,   50,   51,   49,  172,  165,  163,   50,
 /*    10 */    51,   49,  267,  264,  169,    2,  156,  255,  120,  164,
 /*    20 */   162,  161,  248,  247,  246,  245,  244,  160,  159,  116,
 /*    30 */     7,    3,  265,  261,  128,  154,  269,  121,   99,  118,
 /*    40 */     8,   56,  125,  123,   73,  115,    6,   10,  154,   98,
 /*    50 */   128,   17,   32,    5,   61,    4,   60,   59,  104,  110,
 /*    60 */    73,  184,   23,   24,  154,  165,  163,  174,   65,   63,
 /*    70 */   209,  264,  169,    2,  276,  255,  124,  164,  162,  161,
 /*    80 */   248,  247,  246,  245,  244,  160,  159,  274,  266,  273,
 /*    90 */   172,  235,  128,  154,  265,  121,   99,  118,    8,   56,
 /*   100 */   272,  214,   73,  115,    6,   10,  154,  153,  153,   17,
 /*   110 */    32,    5,   61,    4,   60,   59,  104,   74,   71,  131,
 /*   120 */   129,  154,  154,  165,  163,   23,   24,   68,  206,  264,
 /*   130 */   169,    2,  270,  255,   57,  164,  162,  161,  248,  247,
 /*   140 */   246,  245,  244,  160,  159,  263,   31,  172,   67,  195,
 /*   150 */   128,  154,  271,  121,   99,  118,    8,   56,  268,  122,
 /*   160 */    73,  115,    6,   10,  154,  153,  153,   17,   32,    5,
 /*   170 */    61,    4,   60,   59,  104,   74,   90,  131,  108,  154,
 /*   180 */   154,  165,  163,   29,  172,  265,  203,  264,  169,    2,
 /*   190 */    66,  255,  253,  164,  162,  161,  248,  247,  246,  245,
 /*   200 */   244,  160,  159,  252,   98,   23,   24,  251,  128,  154,
 /*   210 */   191,  121,   99,  118,    8,   56,  250,  119,   73,  115,
 /*   220 */     6,   10,  154,  153,  172,   17,   32,    5,   61,    4,
 /*   230 */    60,   59,  104,   74,  210,  131,  130,  154,  249,  165,
 /*   240 */   163,   28,   62,  243,  190,  264,  169,    2,  242,  255,
 /*   250 */    33,  164,  162,  161,  248,  247,  246,  245,  244,  160,
 /*   260 */   159,  157,  337,  155,  338,   30,  156,  154,  158,  121,
 /*   270 */    99,  118,    8,   56,   27,  240,  194,  115,    6,   10,
 /*   280 */   192,   15,  128,   17,   32,    5,   61,    4,   60,   59,
 /*   290 */   104,   95,   73,  121,   99,  188,  154,  165,  163,  152,
 /*   300 */   151,  150,  187,  264,  169,    2,  193,  255,  149,  164,
 /*   310 */   162,  161,  248,  247,  246,  245,  244,  160,  159,  239,
 /*   320 */   337,  421,   11,  147,   55,  154,  148,  121,   99,  118,
 /*   330 */     8,   56,   25,  144,  194,  115,    6,   10,  143,  153,
 /*   340 */   234,   17,   32,    5,   61,    4,   60,   59,  104,   69,
 /*   350 */   141,  121,   99,  154,   92,  165,  163,  233,  140,  138,
 /*   360 */   180,  264,  169,    2,   97,  255,  232,  164,  162,  161,
 /*   370 */   248,  247,  246,  245,  244,  160,  159,  137,  135,   23,
 /*   380 */    24,  134,  153,  154,  231,  121,   99,  118,    8,   56,
 /*   390 */    24,   13,   70,  115,    6,   10,  154,  153,   26,   17,
 /*   400 */    32,    5,   61,    4,   60,   59,  103,   74,  207,  220,
 /*   410 */   219,  154,  217,  165,  163,  216,  127,   64,   30,  179,
 /*   420 */   168,    2,   34,  255,    1,  164,  162,  161,  248,  247,
 /*   430 */   246,  245,  244,  160,  159,  215,   23,   24,  213,   20,
 /*   440 */   153,  154,  208,  121,   99,  118,    8,   56,   19,   18,
 /*   450 */    69,  115,    6,   10,  154,  224,  153,   17,   32,    5,
 /*   460 */    61,    4,   60,   59,  167,  204,   91,  202,   12,  196,
 /*   470 */   154,  165,  163,  107,  189,   14,  183,  241,  166,    2,
 /*   480 */   257,  255,  173,  164,  162,  161,  248,  247,  246,  245,
 /*   490 */   244,  160,  159,  271,  258,  259,  256,  102,  101,  154,
 /*   500 */   126,  121,   99,  118,    8,   56,  100,   98,  212,  115,
 /*   510 */     6,   10,   96,  109,  182,   17,   32,    5,   61,    4,
 /*   520 */    60,   59,  106,   40,   38,   37,   36,   35,   39,   45,
 /*   530 */    44,   46,   48,   47,   54,   52,   50,   51,   49,  181,
 /*   540 */   105,  117,  422,   94,  254,  422,  422,  422,  422,  422,
 /*   550 */   262,  260,   45,   44,   46,   48,   47,   54,   52,   50,
 /*   560 */    51,   49,   65,   63,  211,  422,  205,  114,  111,  153,
 /*   570 */   186,  185,   16,  422,  109,  237,  422,   94,  254,  230,
 /*   580 */   422,  422,  422,  154,  262,  259,   45,   44,   46,   48,
 /*   590 */    47,   54,   52,   50,   51,   49,   65,   63,  211,  422,
 /*   600 */   205,  114,  111,   22,  186,  185,   16,  278,  109,   48,
 /*   610 */    47,   54,   52,   50,   51,   49,   43,   42,  422,  422,
 /*   620 */   422,  422,   41,  238,   93,  422,  422,  422,  422,   53,
 /*   630 */    21,  422,  422,  422,  422,  175,  422,  171,  146,  145,
 /*   640 */   142,  139,  136,   43,   42,  422,  422,  422,  422,   41,
 /*   650 */   238,   93,   58,   63,  132,  422,   53,   46,   48,   47,
 /*   660 */    54,   52,   50,   51,   49,  146,  145,  142,  139,  136,
 /*   670 */    43,   42,  422,  422,  422,  153,   41,  238,   93,  422,
 /*   680 */   422,  132,  422,   53,  218,  229,  422,  422,  422,  154,
 /*   690 */   221,  422,  146,  145,  142,  139,  136,   94,  254,  422,
 /*   700 */   422,  422,  422,  422,  262,   44,   46,   48,   47,   54,
 /*   710 */    52,   50,   51,   49,  422,  422,   65,   63,  211,  153,
 /*   720 */   205,  114,  111,  422,  186,  185,   16,  422,  109,   69,
 /*   730 */   153,  422,  422,  154,  133,   43,   42,  153,  422,  153,
 /*   740 */    69,   41,  238,   93,  154,  223,  422,   69,   53,   69,
 /*   750 */   422,  154,  222,  154,   89,  221,  422,  146,  145,  142,
 /*   760 */   139,  136,   45,   44,   46,   48,   47,   54,   52,   50,
 /*   770 */    51,   49,  422,  201,  199,  422,   43,   42,  201,  199,
 /*   780 */   422,  236,   41,  238,   93,  200,  198,  422,  422,   53,
 /*   790 */   200,  198,  422,  422,  422,  422,  422,  153,  146,  145,
 /*   800 */   142,  139,  136,  121,   99,  422,  422,   69,  121,   99,
 /*   810 */   422,  154,   88,  422,  113,  112,  153,  422,  422,  197,
 /*   820 */   422,  277,  178,  275,  177,  176,   69,  170,    9,  153,
 /*   830 */   154,   87,  153,  422,  422,  153,  422,  422,  422,   69,
 /*   840 */   153,  153,  228,  154,   86,   85,  154,  153,  153,  154,
 /*   850 */    84,   83,  422,  153,  154,  154,  153,   81,   82,  153,
 /*   860 */   422,  154,  154,  227,  153,  153,  226,  154,  422,  225,
 /*   870 */   154,  153,  422,  154,   80,   79,  422,  153,  154,  154,
 /*   880 */   153,   78,  153,  153,  422,  154,  422,   77,  422,  422,
 /*   890 */    76,  154,   75,   72,  154,  422,  154,  154,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    58,   18,   19,   20,   21,   22,    2,   65,   66,   20,
 /*    10 */    21,   22,   70,   71,   72,   73,   35,   75,   37,   77,
 /*    20 */    78,   79,   80,   81,   82,   83,   84,   85,   86,  100,
 /*    30 */   101,  102,   33,   34,   79,   93,   32,   95,   96,   97,
 /*    40 */    98,   99,    2,   88,   89,  103,  104,  105,   93,   26,
 /*    50 */    79,  109,  110,  111,  112,  113,  114,  115,   58,   88,
 /*    60 */    89,   90,    3,    4,   93,   65,   66,   26,   45,   46,
 /*    70 */    70,   71,   72,   73,   27,   75,   36,   77,   78,   79,
 /*    80 */    80,   81,   82,   83,   84,   85,   86,   27,   27,   27,
 /*    90 */     2,   32,   79,   93,   33,   95,   96,   97,   98,   99,
 /*   100 */    26,   88,   89,  103,  104,  105,   93,   79,   79,  109,
 /*   110 */   110,  111,  112,  113,  114,  115,   58,   89,   89,   91,
 /*   120 */    92,   93,   93,   65,   66,    3,    4,   29,   70,   71,
 /*   130 */    72,   73,   26,   75,   31,   77,   78,   79,   80,   81,
 /*   140 */    82,   83,   84,   85,   86,   27,    1,    2,   27,   27,
 /*   150 */    79,   93,   26,   95,   96,   97,   98,   99,   32,   88,
 /*   160 */    89,  103,  104,  105,   93,   79,   79,  109,  110,  111,
 /*   170 */   112,  113,  114,  115,   58,   89,   89,   91,   92,   93,
 /*   180 */    93,   65,   66,    1,    2,   33,   70,   71,   72,   73,
 /*   190 */    27,   75,   27,   77,   78,   79,   80,   81,   82,   83,
 /*   200 */    84,   85,   86,   27,   26,    3,    4,   27,   79,   93,
 /*   210 */    32,   95,   96,   97,   98,   99,   27,   88,   89,  103,
 /*   220 */   104,  105,   93,   79,    2,  109,  110,  111,  112,  113,
 /*   230 */   114,  115,   58,   89,   32,   91,   92,   93,   27,   65,
 /*   240 */    66,    1,    2,   27,   70,   71,   72,   73,   27,   75,
 /*   250 */     2,   77,   78,   79,   80,   81,   82,   83,   84,   85,
 /*   260 */    86,   26,   31,   26,   31,    2,   35,   93,   37,   95,
 /*   270 */    96,   97,   98,   99,   52,   36,   78,  103,  104,  105,
 /*   280 */    32,   31,   79,  109,  110,  111,  112,  113,  114,  115,
 /*   290 */    58,   88,   89,   95,   96,   32,   93,   65,   66,   35,
 /*   300 */    35,   25,   70,   71,   72,   73,  108,   75,   36,   77,
 /*   310 */    78,   79,   80,   81,   82,   83,   84,   85,   86,   36,
 /*   320 */    31,   60,   61,   26,   35,   93,   37,   95,   96,   97,
 /*   330 */    98,   99,   31,   31,   78,  103,  104,  105,   38,   79,
 /*   340 */    32,  109,  110,  111,  112,  113,  114,  115,   58,   89,
 /*   350 */    31,   95,   96,   93,   94,   65,   66,   32,   38,   31,
 /*   360 */    70,   71,   72,   73,  108,   75,   32,   77,   78,   79,
 /*   370 */    80,   81,   82,   83,   84,   85,   86,   38,   31,    3,
 /*   380 */     4,   38,   79,   93,   32,   95,   96,   97,   98,   99,
 /*   390 */     4,   31,   89,  103,  104,  105,   93,   79,    2,  109,
 /*   400 */   110,  111,  112,  113,  114,  115,   58,   89,   32,   91,
 /*   410 */    32,   93,   32,   65,   66,   25,   35,   35,    2,   71,
 /*   420 */    72,   73,    1,   75,   76,   77,   78,   79,   80,   81,
 /*   430 */    82,   83,   84,   85,   86,   36,    3,    4,   26,   31,
 /*   440 */    79,   93,   47,   95,   96,   97,   98,   99,   31,   31,
 /*   450 */    89,  103,  104,  105,   93,   94,   79,  109,  110,  111,
 /*   460 */   112,  113,  114,  115,   58,   32,   89,   31,    2,   27,
 /*   470 */    93,   65,   66,   32,   31,   31,   27,   71,   72,   73,
 /*   480 */    74,   75,   67,   77,   78,   79,   80,   81,   82,   83,
 /*   490 */    84,   85,   86,   26,   74,   34,   74,   67,   87,   93,
 /*   500 */    25,   95,   96,   97,   98,   99,   67,   26,   95,  103,
 /*   510 */   104,  105,   67,   57,  114,  109,  110,  111,  112,  113,
 /*   520 */   114,  115,   67,    7,    8,    9,   10,   11,   12,   13,
 /*   530 */    14,   15,   16,   17,   18,   19,   20,   21,   22,  114,
 /*   540 */    67,   48,  116,   26,   27,  116,  116,  116,  116,  116,
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
#define YY_SHIFT_COUNT (178)
#define YY_SHIFT_MIN   (-19)
#define YY_SHIFT_MAX   (758)
static const short yy_shift_ofst[] = {
 /*     0 */   -20,  551,  517,  671,  671,  671,  671,  671,  671,  671,
 /*    10 */    23,  607,   23,  652,  717,  717,  758,  598,  598,  598,
 /*    20 */   598,  625,  625,  598,  598,  598,  717,  758,  758,  758,
 /*    30 */   758,  758,  178,  481,  758,  758,  758,  758,  758,  758,
 /*    40 */   758,  758,  758,  758,  758,  758,  758,  758,  758,  758,
 /*    50 */   758,  758,  758,  758,  758,  758,  493,  126,  467,  456,
 /*    60 */   456,  467,  481,  467,  475,  467,  461,  461,  467,  516,
 /*    70 */   749,  539,  573,  573,  573,  573,  573,  573,  573,  573,
 /*    80 */   573,  691,  642,  593,  -17,  -17,  122,  433,  376,  202,
 /*    90 */   -11,  -11,   59,  289,  231,  263,  222,  248,  -19,  240,
 /*   100 */   182,   40,  145,   -1,   61,    4,   88,  449,  441,  444,
 /*   110 */   416,  443,  442,  466,  436,  418,  417,  395,  408,  416,
 /*   120 */   412,  421,  416,  416,  399,  390,  272,  382,  381,  380,
 /*   130 */   378,  396,  360,  386,  352,  343,  347,  334,  339,  328,
 /*   140 */   325,  320,  319,  308,  300,  302,  301,  233,  297,  283,
 /*   150 */   272,  276,  265,  264,  250,  239,  237,  233,  235,  221,
 /*   160 */   216,  211,  189,  180,  176,  165,  163,  152,  121,  118,
 /*   170 */   103,  106,   74,   88,   98,   41,   62,   60,   47,
};
#define YY_REDUCE_USE_DFLT (-72)
#define YY_REDUCE_COUNT (68)
#define YY_REDUCE_MIN   (-71)
#define YY_REDUCE_MAX   (804)
static const short yy_reduce_ofst[] = {
 /*     0 */   261,  406,  348,  290,  232,  174,  116,   58,    0,  -58,
 /*    10 */   708,  759,  713,  144,   86,   28,  -29,  750,  737,  718,
 /*    20 */   660,  658,  651,  640,  361,  260,  318,  203,  129,   71,
 /*    30 */    13,  -45,  256,  198,  804,  803,  801,  798,  792,  786,
 /*    40 */   785,  780,  777,  774,  769,  768,  762,  761,  756,  753,
 /*    50 */   596,  490,  377,  303,   87,   29,  -71,  473,  455,  425,
 /*    60 */   400,  445,  413,  439,  411,  430,  422,  420,  415,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   279,  420,  420,  420,  420,  420,  420,  420,  420,  420,
 /*    10 */   399,  420,  420,  420,  335,  335,  326,  420,  420,  420,
 /*    20 */   420,  420,  420,  420,  420,  420,  420,  420,  420,  420,
 /*    30 */   420,  420,  420,  420,  420,  420,  420,  420,  420,  420,
 /*    40 */   420,  420,  420,  420,  420,  420,  420,  420,  420,  420,
 /*    50 */   420,  420,  420,  420,  420,  420,  387,  420,  420,  419,
 /*    60 */   418,  420,  420,  420,  420,  420,  420,  420,  420,  420,
 /*    70 */   420,  420,  378,  324,  332,  365,  364,  363,  362,  361,
 /*    80 */   360,  355,  356,  354,  353,  352,  420,  420,  420,  420,
 /*    90 */   347,  348,  420,  329,  373,  420,  420,  420,  373,  420,
 /*   100 */   420,  420,  370,  420,  420,  420,  370,  420,  420,  420,
 /*   110 */   327,  420,  420,  398,  420,  420,  420,  386,  420,  379,
 /*   120 */   420,  376,  372,  371,  420,  420,  318,  420,  340,  420,
 /*   130 */   420,  336,  420,  367,  420,  420,  420,  420,  420,  420,
 /*   140 */   420,  420,  420,  420,  420,  420,  420,  330,  420,  420,
 /*   150 */   420,  420,  420,  340,  420,  420,  420,  375,  420,  420,
 /*   160 */   420,  420,  420,  420,  420,  420,  420,  317,  420,  420,
 /*   170 */   420,  420,  420,  285,  420,  420,  420,  420,  420,  315,
 /*   180 */   388,  417,  416,  415,  412,  411,  410,  409,  408,  407,
 /*   190 */   406,  405,  404,  401,  400,  403,  402,  397,  396,  395,
 /*   200 */   394,  393,  392,  391,  390,  389,  385,  384,  383,  382,
 /*   210 */   381,  380,  377,  375,  325,  322,  319,  339,  414,  413,
 /*   220 */   334,  333,  369,  368,  366,  359,  358,  357,  351,  350,
 /*   230 */   349,  346,  345,  344,  343,  342,  341,  331,  328,  323,
 /*   240 */   374,  316,  314,  313,  312,  311,  310,  309,  308,  307,
 /*   250 */   306,  305,  304,  303,  302,  301,  299,  298,  297,  295,
 /*   260 */   296,  300,  294,  292,  291,  293,  290,  289,  288,  287,
 /*   270 */   286,  320,  321,  284,  283,  282,  281,  280,
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
 /*  15 */ "lbracket ::= error LBRACKET",
 /*  16 */ "lbracket ::= LBRACKET",
 /*  17 */ "rbracket ::= RBRACKET",
 /*  18 */ "blockStmt ::= lbracket RBRACKET",
 /*  19 */ "blockStmt ::= lbracket return_stmt SEMICOLON rbracket",
 /*  20 */ "blockStmt ::= lbracket bodyStmtList rbracket",
 /*  21 */ "blockStmt ::= lbracket bodyStmtList return_stmt SEMICOLON rbracket",
 /*  22 */ "blockStmt ::= lbracket error RBRACKET",
 /*  23 */ "bodyStmt ::= blockStmt",
 /*  24 */ "bodyStmt ::= SEMICOLON",
 /*  25 */ "bodyStmt ::= vdef_stmt SEMICOLON",
 /*  26 */ "bodyStmt ::= vdefAssign_stmt SEMICOLON",
 /*  27 */ "bodyStmt ::= cdef_stmt SEMICOLON",
 /*  28 */ "bodyStmt ::= assign_stmt SEMICOLON",
 /*  29 */ "bodyStmt ::= funcexpr SEMICOLON",
 /*  30 */ "bodyStmt ::= actionStmt",
 /*  31 */ "bodyStmt ::= if_stmt",
 /*  32 */ "bodyStmt ::= while_stmt",
 /*  33 */ "bodyStmt ::= for_stmt",
 /*  34 */ "bodyStmt ::= foreach_stmt",
 /*  35 */ "bodyStmt ::= continue_stmt SEMICOLON",
 /*  36 */ "bodyStmt ::= break_stmt SEMICOLON",
 /*  37 */ "bodyStmtList ::= bodyStmt",
 /*  38 */ "bodyStmtList ::= bodyStmtList bodyStmt",
 /*  39 */ "bodyStmtList ::= bodyStmtList error",
 /*  40 */ "numList_nonEmpty ::= NUMBER",
 /*  41 */ "numList_nonEmpty ::= numList_nonEmpty COMMA NUMBER",
 /*  42 */ "nameList_nonEmpty ::= NAME",
 /*  43 */ "nameList_nonEmpty ::= nameList_nonEmpty COMMA NAME",
 /*  44 */ "exprList_nonEmpty ::= funcexpr LSQBRACKET LSQBRACKET numList_nonEmpty RSQBRACKET RSQBRACKET",
 /*  45 */ "expr ::= funcexpr LSQBRACKET LSQBRACKET NUMBER RSQBRACKET RSQBRACKET",
 /*  46 */ "exprList_nonEmpty ::= expr",
 /*  47 */ "exprList_nonEmpty ::= exprList_nonEmpty COMMA exprList_nonEmpty",
 /*  48 */ "exprList ::=",
 /*  49 */ "exprList ::= exprList_nonEmpty",
 /*  50 */ "expr ::= NUMBER",
 /*  51 */ "expr ::= NAME",
 /*  52 */ "expr ::= NAME PERIOD NAME",
 /*  53 */ "expr ::= NAME LSQBRACKET expr RSQBRACKET",
 /*  54 */ "fArgs_nonEmpty ::= expr",
 /*  55 */ "fArgs_nonEmpty ::= STRING",
 /*  56 */ "fArgs_nonEmpty ::= fArgs_nonEmpty COMMA fArgs_nonEmpty",
 /*  57 */ "fArgs ::=",
 /*  58 */ "fArgs ::= fArgs_nonEmpty",
 /*  59 */ "funcName ::= NAME",
 /*  60 */ "funcName ::= NAME PERIOD NAME",
 /*  61 */ "funcexpr ::= funcName LPAREN fArgs RPAREN",
 /*  62 */ "expr ::= funcexpr",
 /*  63 */ "expr ::= LPAREN expr RPAREN",
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
 /*  96 */ "lvalue ::= NAME LSQBRACKET NAME RSQBRACKET",
 /*  97 */ "lvalue ::= NAME PERIOD NAME",
 /*  98 */ "lvalueList_nonEmpty ::= lvalue",
 /*  99 */ "lvalueList_nonEmpty ::= lvalueList_nonEmpty COMMA lvalue",
 /* 100 */ "assign_stmt ::= lvalue ASSIGN expr",
 /* 101 */ "assign_stmt ::= lvalueList_nonEmpty ASSIGN exprList_nonEmpty",
 /* 102 */ "if_start ::= IF",
 /* 103 */ "if_header ::= if_start LPAREN lexpr RPAREN",
 /* 104 */ "if_block ::= if_header stmt",
 /* 105 */ "elif_start ::= ELSE IF",
 /* 106 */ "elif_header ::= elif_start LPAREN lexpr RPAREN",
 /* 107 */ "if_block ::= if_block elif_header stmt",
 /* 108 */ "else_header ::= ELSE",
 /* 109 */ "if_stmt ::= if_block",
 /* 110 */ "if_stmt ::= if_block else_header stmt",
 /* 111 */ "while_start ::= WHILE",
 /* 112 */ "while_header ::= while_start LPAREN lexpr RPAREN",
 /* 113 */ "while_stmt ::= while_header stmt",
 /* 114 */ "for_opener ::= FOR LPAREN",
 /* 115 */ "for_init_stmt_nonEmpty ::= vdef_stmt",
 /* 116 */ "for_init_stmt_nonEmpty ::= vdefAssign_stmt",
 /* 117 */ "for_init_stmt_nonEmpty ::= cdef_stmt",
 /* 118 */ "for_init_stmt_nonEmpty ::= assign_stmt",
 /* 119 */ "for_init_stmt_nonEmpty ::= for_init_stmt_nonEmpty COMMA for_init_stmt_nonEmpty",
 /* 120 */ "for_init_stmt ::= for_init_stmt_nonEmpty",
 /* 121 */ "for_init_stmt ::=",
 /* 122 */ "for_action_stmt_nonEmpty ::= assign_stmt",
 /* 123 */ "for_action_stmt_nonEmpty ::= for_action_stmt_nonEmpty COMMA for_action_stmt_nonEmpty",
 /* 124 */ "for_header1 ::= for_opener for_init_stmt SEMICOLON",
 /* 125 */ "for_header2 ::= for_header1 lexpr SEMICOLON",
 /* 126 */ "for_header ::= for_header2 for_action_stmt_nonEmpty RPAREN",
 /* 127 */ "for_header ::= for_header2 RPAREN",
 /* 128 */ "for_stmt ::= for_header stmt",
 /* 129 */ "foreach_opener ::= FOREACH LPAREN",
 /* 130 */ "foreach_header ::= foreach_opener nameList_nonEmpty COLON exprList_nonEmpty RPAREN",
 /* 131 */ "foreach_stmt ::= foreach_header stmt",
 /* 132 */ "continue_stmt ::= CONTINUE",
 /* 133 */ "break_stmt ::= BREAK",
 /* 134 */ "return_stmt ::= RETURN exprList",
 /* 135 */ "lexpr ::= CONDITIONNAME LPAREN fArgs RPAREN",
 /* 136 */ "lexpr ::= CONDITIONNAME LPAREN RPAREN",
 /* 137 */ "action ::= ACTIONNAME LPAREN fArgs RPAREN SEMICOLON",
 /* 138 */ "actions ::= action action",
 /* 139 */ "actions ::= actions action",
 /* 140 */ "actionStmt ::= action",
 /* 141 */ "actionStmt ::= actions",
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
#line 770 "parser\\epparser.c"
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
  { 73, 2 },
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
      case 131: /* foreach_stmt ::= foreach_header stmt */ yytestcase(yyruleno==131);
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
      case 15: /* lbracket ::= error LBRACKET */
#line 125 "parser\\epparser.lemon"
{
    throw_error(9036, "Invalid control structure?");
    ps->closure.pushScope();
}
#line 1281 "parser\\epparser.c"
        break;
      case 16: /* lbracket ::= LBRACKET */
#line 129 "parser\\epparser.lemon"
{ ps->closure.pushScope(); }
#line 1286 "parser\\epparser.c"
        break;
      case 17: /* rbracket ::= RBRACKET */
#line 130 "parser\\epparser.lemon"
{ ps->closure.popScope(); }
#line 1291 "parser\\epparser.c"
        break;
      case 18: /* blockStmt ::= lbracket RBRACKET */
#line 132 "parser\\epparser.lemon"
{
    ps->gen << "pass" << std::endl;
    ps->closure.popScope();
}
#line 1299 "parser\\epparser.c"
        break;
      case 22: /* blockStmt ::= lbracket error RBRACKET */
#line 139 "parser\\epparser.lemon"
{
    throw_error(6298, "Block not terminated properly.");
    ps->closure.popScope();
}
#line 1307 "parser\\epparser.c"
        break;
      case 29: /* bodyStmt ::= funcexpr SEMICOLON */
#line 150 "parser\\epparser.lemon"
{ ps->gen << yymsp[-1].minor.yy0->data << std::endl; }
#line 1312 "parser\\epparser.c"
        break;
      case 39: /* bodyStmtList ::= bodyStmtList error */
#line 162 "parser\\epparser.lemon"
{
    throw_error(8510, "Incomplete statement");
}
#line 1319 "parser\\epparser.c"
        break;
      case 40: /* numList_nonEmpty ::= NUMBER */
      case 42: /* nameList_nonEmpty ::= NAME */ yytestcase(yyruleno==42);
      case 46: /* exprList_nonEmpty ::= expr */ yytestcase(yyruleno==46);
      case 49: /* exprList ::= exprList_nonEmpty */ yytestcase(yyruleno==49);
      case 50: /* expr ::= NUMBER */ yytestcase(yyruleno==50);
      case 54: /* fArgs_nonEmpty ::= expr */ yytestcase(yyruleno==54);
      case 55: /* fArgs_nonEmpty ::= STRING */ yytestcase(yyruleno==55);
      case 58: /* fArgs ::= fArgs_nonEmpty */ yytestcase(yyruleno==58);
      case 62: /* expr ::= funcexpr */ yytestcase(yyruleno==62);
      case 91: /* lexpr ::= LNOT LNOT lexpr */ yytestcase(yyruleno==91);
      case 98: /* lvalueList_nonEmpty ::= lvalue */ yytestcase(yyruleno==98);
#line 168 "parser\\epparser.lemon"
{ yygotominor.yy0 = yymsp[0].minor.yy0; }
#line 1334 "parser\\epparser.c"
        break;
      case 41: /* numList_nonEmpty ::= numList_nonEmpty COMMA NUMBER */
      case 43: /* nameList_nonEmpty ::= nameList_nonEmpty COMMA NAME */ yytestcase(yyruleno==43);
      case 99: /* lvalueList_nonEmpty ::= lvalueList_nonEmpty COMMA lvalue */ yytestcase(yyruleno==99);
#line 169 "parser\\epparser.lemon"
{ yygotominor.yy0 = commaConcat(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1341 "parser\\epparser.c"
        break;
      case 44: /* exprList_nonEmpty ::= funcexpr LSQBRACKET LSQBRACKET numList_nonEmpty RSQBRACKET RSQBRACKET */
#line 173 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "_SRET(" + yymsp[-5].minor.yy0->data + ", [" + yymsp[-2].minor.yy0->data + "])";
    delete yymsp[-5].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1350 "parser\\epparser.c"
        break;
      case 45: /* expr ::= funcexpr LSQBRACKET LSQBRACKET NUMBER RSQBRACKET RSQBRACKET */
#line 180 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-5].minor.yy0->data + "[" + yymsp[-2].minor.yy0->data + "]";
    delete yymsp[-5].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1359 "parser\\epparser.c"
        break;
      case 47: /* exprList_nonEmpty ::= exprList_nonEmpty COMMA exprList_nonEmpty */
#line 188 "parser\\epparser.lemon"
{ yygotominor.yy0 = new Token((yymsp[-2].minor.yy0->data) + ", " + (yymsp[0].minor.yy0->data), yymsp[0].minor.yy0); delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1364 "parser\\epparser.c"
        break;
      case 48: /* exprList ::= */
      case 57: /* fArgs ::= */ yytestcase(yyruleno==57);
#line 190 "parser\\epparser.lemon"
{ yygotominor.yy0 = genEmpty(); }
#line 1370 "parser\\epparser.c"
        break;
      case 51: /* expr ::= NAME */
#line 195 "parser\\epparser.lemon"
{
    checkIsRValue(yymsp[0].minor.yy0->data);
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1378 "parser\\epparser.c"
        break;
      case 52: /* expr ::= NAME PERIOD NAME */
#line 200 "parser\\epparser.lemon"
{
    checkIsConstant(yymsp[-2].minor.yy0->data);
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + "." + yymsp[0].minor.yy0->data;
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1388 "parser\\epparser.c"
        break;
      case 53: /* expr ::= NAME LSQBRACKET expr RSQBRACKET */
#line 207 "parser\\epparser.lemon"
{
    checkIsConstant(yymsp[-3].minor.yy0->data);
    yymsp[-3].minor.yy0->data = yymsp[-3].minor.yy0->data + "[" + yymsp[-1].minor.yy0->data + "]";
    delete yymsp[-1].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 1398 "parser\\epparser.c"
        break;
      case 56: /* fArgs_nonEmpty ::= fArgs_nonEmpty COMMA fArgs_nonEmpty */
#line 217 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data;
    yymsp[-2].minor.yy0->type = TOKEN_TEMP;
    yygotominor.yy0 = yymsp[-2].minor.yy0;
    delete yymsp[0].minor.yy0;
}
#line 1408 "parser\\epparser.c"
        break;
      case 59: /* funcName ::= NAME */
#line 227 "parser\\epparser.lemon"
{
    funcNamePreprocess(yymsp[0].minor.yy0->data);
    checkIsFunction(yymsp[0].minor.yy0->data);
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1417 "parser\\epparser.c"
        break;
      case 60: /* funcName ::= NAME PERIOD NAME */
#line 233 "parser\\epparser.lemon"
{
    // Preprocess name
    checkIsConstant(yymsp[-2].minor.yy0->data);
    yymsp[0].minor.yy0->data = yymsp[-2].minor.yy0->data + "." + yymsp[0].minor.yy0->data;
    delete yymsp[-2].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0);
}
#line 1428 "parser\\epparser.c"
        break;
      case 61: /* funcexpr ::= funcName LPAREN fArgs RPAREN */
#line 241 "parser\\epparser.lemon"
{
    // Preprocess yymsp[-3].minor.yy0
    yymsp[-3].minor.yy0->data += "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 1437 "parser\\epparser.c"
        break;
      case 63: /* expr ::= LPAREN expr RPAREN */
#line 250 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1445 "parser\\epparser.c"
        break;
      case 64: /* expr ::= L2V LPAREN lexpr RPAREN */
#line 255 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "_L2V(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = genTemp(yymsp[-1].minor.yy0);
}
#line 1453 "parser\\epparser.c"
        break;
      case 65: /* expr ::= MAPSTRING LPAREN STRING RPAREN */
#line 260 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetStringIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1461 "parser\\epparser.c"
        break;
      case 66: /* expr ::= UNIT LPAREN STRING RPAREN */
#line 265 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetUnitIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1469 "parser\\epparser.c"
        break;
      case 67: /* expr ::= SWITCH LPAREN STRING RPAREN */
#line 270 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetSwitchIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1477 "parser\\epparser.c"
        break;
      case 68: /* expr ::= LOCATION LPAREN STRING RPAREN */
#line 275 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetLocationIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1485 "parser\\epparser.c"
        break;
      case 69: /* expr ::= expr PLUS expr */
#line 281 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "+",  yymsp[0].minor.yy0); }
#line 1490 "parser\\epparser.c"
        break;
      case 70: /* expr ::= expr MINUS expr */
#line 282 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "-",  yymsp[0].minor.yy0); }
#line 1495 "parser\\epparser.c"
        break;
      case 71: /* expr ::= expr MULTIPLY expr */
#line 283 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "*",  yymsp[0].minor.yy0); }
#line 1500 "parser\\epparser.c"
        break;
      case 72: /* expr ::= expr DIVIDE expr */
#line 284 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "//", yymsp[0].minor.yy0); }
#line 1505 "parser\\epparser.c"
        break;
      case 73: /* expr ::= expr MOD expr */
#line 285 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "%",  yymsp[0].minor.yy0); }
#line 1510 "parser\\epparser.c"
        break;
      case 74: /* expr ::= expr LSHIFT expr */
#line 286 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<<", yymsp[0].minor.yy0); }
#line 1515 "parser\\epparser.c"
        break;
      case 75: /* expr ::= expr RSHIFT expr */
#line 287 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">>", yymsp[0].minor.yy0); }
#line 1520 "parser\\epparser.c"
        break;
      case 76: /* expr ::= expr BITAND expr */
#line 288 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "&",  yymsp[0].minor.yy0); }
#line 1525 "parser\\epparser.c"
        break;
      case 77: /* expr ::= expr BITOR expr */
#line 289 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "|",  yymsp[0].minor.yy0); }
#line 1530 "parser\\epparser.c"
        break;
      case 78: /* expr ::= expr BITXOR expr */
#line 290 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "^",  yymsp[0].minor.yy0); }
#line 1535 "parser\\epparser.c"
        break;
      case 79: /* expr ::= PLUS expr */
#line 293 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = +" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1540 "parser\\epparser.c"
        break;
      case 80: /* expr ::= MINUS expr */
#line 294 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = -" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1545 "parser\\epparser.c"
        break;
      case 81: /* expr ::= BITNOT expr */
#line 295 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = ~" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1550 "parser\\epparser.c"
        break;
      case 82: /* lexpr ::= expr EQ expr */
#line 299 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "==", yymsp[0].minor.yy0); }
#line 1555 "parser\\epparser.c"
        break;
      case 83: /* lexpr ::= expr NE expr */
#line 300 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "!=", yymsp[0].minor.yy0); }
#line 1560 "parser\\epparser.c"
        break;
      case 84: /* lexpr ::= expr LE expr */
#line 301 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<=", yymsp[0].minor.yy0); }
#line 1565 "parser\\epparser.c"
        break;
      case 85: /* lexpr ::= expr LT expr */
#line 302 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<",  yymsp[0].minor.yy0); }
#line 1570 "parser\\epparser.c"
        break;
      case 86: /* lexpr ::= expr GE expr */
#line 303 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">=", yymsp[0].minor.yy0); }
#line 1575 "parser\\epparser.c"
        break;
      case 87: /* lexpr ::= expr GT expr */
#line 304 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">" , yymsp[0].minor.yy0); }
#line 1580 "parser\\epparser.c"
        break;
      case 88: /* lexpr ::= lexpr LAND lexpr */
#line 306 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "[" + yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data + "]";
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1589 "parser\\epparser.c"
        break;
      case 89: /* lexpr ::= lexpr LOR lexpr */
#line 312 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "EUDOr([" + yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data + "])";
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1598 "parser\\epparser.c"
        break;
      case 90: /* lexpr ::= LNOT lexpr */
#line 318 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = "EUDNot([" + yymsp[0].minor.yy0->data + "])";
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0);
}
#line 1606 "parser\\epparser.c"
        break;
      case 92: /* vdef_stmt ::= VAR nameList_nonEmpty */
#line 328 "parser\\epparser.lemon"
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
#line 1630 "parser\\epparser.c"
        break;
      case 93: /* vdefAssign_stmt ::= VAR nameList_nonEmpty ASSIGN exprList_nonEmpty */
#line 349 "parser\\epparser.lemon"
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
#line 1655 "parser\\epparser.c"
        break;
      case 94: /* cdef_stmt ::= CONST nameList_nonEmpty ASSIGN exprList_nonEmpty */
#line 371 "parser\\epparser.lemon"
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
#line 1677 "parser\\epparser.c"
        break;
      case 95: /* lvalue ::= NAME */
#line 392 "parser\\epparser.lemon"
{
    checkIsVariable(yymsp[0].minor.yy0->data);
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1685 "parser\\epparser.c"
        break;
      case 96: /* lvalue ::= NAME LSQBRACKET NAME RSQBRACKET */
#line 397 "parser\\epparser.lemon"
{
    checkIsConstant(yymsp[-3].minor.yy0->data);
    yymsp[-1].minor.yy0->data = "_ARRW(" + yymsp[-3].minor.yy0->data + ", " + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
    delete yymsp[-3].minor.yy0;
}
#line 1695 "parser\\epparser.c"
        break;
      case 97: /* lvalue ::= NAME PERIOD NAME */
#line 404 "parser\\epparser.lemon"
{
    checkIsConstant(yymsp[-2].minor.yy0->data);
    yymsp[0].minor.yy0->data = "_ATTW(" + yymsp[-2].minor.yy0->data + ", '" + yymsp[0].minor.yy0->data + "')";
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0);
    delete yymsp[-2].minor.yy0;
}
#line 1705 "parser\\epparser.c"
        break;
      case 100: /* assign_stmt ::= lvalue ASSIGN expr */
#line 413 "parser\\epparser.lemon"
{
    ps->gen << yymsp[-2].minor.yy0->data << " << (" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 1713 "parser\\epparser.c"
        break;
      case 101: /* assign_stmt ::= lvalueList_nonEmpty ASSIGN exprList_nonEmpty */
#line 418 "parser\\epparser.lemon"
{
    ps->gen << "_SV([" << yymsp[-2].minor.yy0->data << "], [" << yymsp[0].minor.yy0->data << "])" << std::endl;
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 1721 "parser\\epparser.c"
        break;
      case 102: /* if_start ::= IF */
#line 424 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDIf()" << std::endl;
}
#line 1729 "parser\\epparser.c"
        break;
      case 103: /* if_header ::= if_start LPAREN lexpr RPAREN */
      case 112: /* while_header ::= while_start LPAREN lexpr RPAREN */ yytestcase(yyruleno==112);
#line 428 "parser\\epparser.lemon"
{
    ps->gen << "if " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data << "):" << std::endl;
    ps->gen.indent();
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1739 "parser\\epparser.c"
        break;
      case 105: /* elif_start ::= ELSE IF */
#line 436 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen.unindent(false);
    ps->gen << yygotominor.yy0->data << " = EUDElseIf()" << std::endl;
}
#line 1748 "parser\\epparser.c"
        break;
      case 106: /* elif_header ::= elif_start LPAREN lexpr RPAREN */
#line 442 "parser\\epparser.lemon"
{
    ps->gen << "if " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data <<"):" << std::endl;
    ps->gen.indent();
}
#line 1756 "parser\\epparser.c"
        break;
      case 108: /* else_header ::= ELSE */
#line 449 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "if EUDElse()():" << std::endl;
    ps->gen.indent();
}
#line 1765 "parser\\epparser.c"
        break;
      case 109: /* if_stmt ::= if_block */
      case 110: /* if_stmt ::= if_block else_header stmt */ yytestcase(yyruleno==110);
#line 455 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndIf()" << std::endl;
}
#line 1774 "parser\\epparser.c"
        break;
      case 111: /* while_start ::= WHILE */
#line 467 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDWhile()" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1783 "parser\\epparser.c"
        break;
      case 113: /* while_stmt ::= while_header stmt */
#line 479 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndWhile()" << std::endl;
}
#line 1791 "parser\\epparser.c"
        break;
      case 114: /* for_opener ::= FOR LPAREN */
      case 129: /* foreach_opener ::= FOREACH LPAREN */ yytestcase(yyruleno==129);
#line 485 "parser\\epparser.lemon"
{
    ps->closure.pushScope();
}
#line 1799 "parser\\epparser.c"
        break;
      case 124: /* for_header1 ::= for_opener for_init_stmt SEMICOLON */
#line 501 "parser\\epparser.lemon"
{
    // opening for lexpr
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDWhile()" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1809 "parser\\epparser.c"
        break;
      case 125: /* for_header2 ::= for_header1 lexpr SEMICOLON */
#line 508 "parser\\epparser.lemon"
{
    ps->gen << "if " << yymsp[-2].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data << "):" << std::endl;
    ps->gen.indent();
    delete yymsp[-2].minor.yy0; delete yymsp[-1].minor.yy0;

    // Opening for assign_statement
    yygotominor.yy0 = genTemp(yymsp[-1].minor.yy0);
    ps->gen << "def " << yygotominor.yy0->data <<"():" << std::endl;
    ps->gen.indent();
}
#line 1823 "parser\\epparser.c"
        break;
      case 126: /* for_header ::= for_header2 for_action_stmt_nonEmpty RPAREN */
#line 519 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-2].minor.yy0;
    ps->gen.unindent(false);
}
#line 1831 "parser\\epparser.c"
        break;
      case 127: /* for_header ::= for_header2 RPAREN */
#line 524 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
    ps->gen << "pass" << std::endl;
    ps->gen.unindent(false);
}
#line 1840 "parser\\epparser.c"
        break;
      case 128: /* for_stmt ::= for_header stmt */
#line 530 "parser\\epparser.lemon"
{
    ps->gen << yymsp[-1].minor.yy0->data << "()" << std::endl;
    ps->gen.unindent(false);
    ps->gen << "EUDEndWhile()" << std::endl;
    ps->closure.popScope();
}
#line 1850 "parser\\epparser.c"
        break;
      case 130: /* foreach_header ::= foreach_opener nameList_nonEmpty COLON exprList_nonEmpty RPAREN */
#line 544 "parser\\epparser.lemon"
{
    commaListIter(yymsp[-3].minor.yy0->data, [&](std::string& s) {
        ps->closure.defVariable(s);
    });
    ps->gen << "for " << yymsp[-3].minor.yy0->data << " in " << yymsp[-1].minor.yy0->data << ":" << std::endl;
    ps->gen.indent();
}
#line 1861 "parser\\epparser.c"
        break;
      case 132: /* continue_stmt ::= CONTINUE */
#line 560 "parser\\epparser.lemon"
{
    ps->gen << "EUDContinue()" << std::endl;
}
#line 1868 "parser\\epparser.c"
        break;
      case 133: /* break_stmt ::= BREAK */
#line 564 "parser\\epparser.lemon"
{
    ps->gen << "EUDBreak()" << std::endl;
}
#line 1875 "parser\\epparser.c"
        break;
      case 134: /* return_stmt ::= RETURN exprList */
#line 571 "parser\\epparser.lemon"
{
    ps->gen << "EUDReturn(" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1883 "parser\\epparser.c"
        break;
      case 135: /* lexpr ::= CONDITIONNAME LPAREN fArgs RPAREN */
#line 579 "parser\\epparser.lemon"
{
    yymsp[-3].minor.yy0->data = yymsp[-3].minor.yy0->data + "(" + yymsp[-1].minor.yy0->data + ")";
    delete yymsp[-1].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 1892 "parser\\epparser.c"
        break;
      case 136: /* lexpr ::= CONDITIONNAME LPAREN RPAREN */
#line 585 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + "()";
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1900 "parser\\epparser.c"
        break;
      case 137: /* action ::= ACTIONNAME LPAREN fArgs RPAREN SEMICOLON */
#line 590 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[-4].minor.yy0);
    yygotominor.yy0->data =  yymsp[-4].minor.yy0->data + "(" + yymsp[-2].minor.yy0->data + ")";
    delete yymsp[-4].minor.yy0; delete yymsp[-2].minor.yy0;
}
#line 1909 "parser\\epparser.c"
        break;
      case 138: /* actions ::= action action */
      case 139: /* actions ::= actions action */ yytestcase(yyruleno==139);
#line 596 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
    yymsp[-1].minor.yy0->data += ",\n" + yymsp[0].minor.yy0->data;
    delete yymsp[0].minor.yy0;
}
#line 1919 "parser\\epparser.c"
        break;
      case 140: /* actionStmt ::= action */
#line 608 "parser\\epparser.lemon"
{
    ps->gen << "DoActions(" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1927 "parser\\epparser.c"
        break;
      case 141: /* actionStmt ::= actions */
#line 613 "parser\\epparser.lemon"
{
    ps->gen << "DoActions([" << std::endl;
    ps->gen.indent();
    ps->gen << yymsp[0].minor.yy0->data << std::endl;
    ps->gen.unindent(false);
    ps->gen << "])" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1939 "parser\\epparser.c"
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
      /* (19) blockStmt ::= lbracket return_stmt SEMICOLON rbracket */ yytestcase(yyruleno==19);
      /* (20) blockStmt ::= lbracket bodyStmtList rbracket */ yytestcase(yyruleno==20);
      /* (21) blockStmt ::= lbracket bodyStmtList return_stmt SEMICOLON rbracket */ yytestcase(yyruleno==21);
      /* (23) bodyStmt ::= blockStmt */ yytestcase(yyruleno==23);
      /* (24) bodyStmt ::= SEMICOLON */ yytestcase(yyruleno==24);
      /* (25) bodyStmt ::= vdef_stmt SEMICOLON */ yytestcase(yyruleno==25);
      /* (26) bodyStmt ::= vdefAssign_stmt SEMICOLON */ yytestcase(yyruleno==26);
      /* (27) bodyStmt ::= cdef_stmt SEMICOLON */ yytestcase(yyruleno==27);
      /* (28) bodyStmt ::= assign_stmt SEMICOLON */ yytestcase(yyruleno==28);
      /* (30) bodyStmt ::= actionStmt */ yytestcase(yyruleno==30);
      /* (31) bodyStmt ::= if_stmt */ yytestcase(yyruleno==31);
      /* (32) bodyStmt ::= while_stmt */ yytestcase(yyruleno==32);
      /* (33) bodyStmt ::= for_stmt */ yytestcase(yyruleno==33);
      /* (34) bodyStmt ::= foreach_stmt */ yytestcase(yyruleno==34);
      /* (35) bodyStmt ::= continue_stmt SEMICOLON */ yytestcase(yyruleno==35);
      /* (36) bodyStmt ::= break_stmt SEMICOLON */ yytestcase(yyruleno==36);
      /* (37) bodyStmtList ::= bodyStmt */ yytestcase(yyruleno==37);
      /* (38) bodyStmtList ::= bodyStmtList bodyStmt */ yytestcase(yyruleno==38);
      /* (104) if_block ::= if_header stmt */ yytestcase(yyruleno==104);
      /* (107) if_block ::= if_block elif_header stmt */ yytestcase(yyruleno==107);
      /* (115) for_init_stmt_nonEmpty ::= vdef_stmt */ yytestcase(yyruleno==115);
      /* (116) for_init_stmt_nonEmpty ::= vdefAssign_stmt */ yytestcase(yyruleno==116);
      /* (117) for_init_stmt_nonEmpty ::= cdef_stmt */ yytestcase(yyruleno==117);
      /* (118) for_init_stmt_nonEmpty ::= assign_stmt */ yytestcase(yyruleno==118);
      /* (119) for_init_stmt_nonEmpty ::= for_init_stmt_nonEmpty COMMA for_init_stmt_nonEmpty */ yytestcase(yyruleno==119);
      /* (120) for_init_stmt ::= for_init_stmt_nonEmpty */ yytestcase(yyruleno==120);
      /* (121) for_init_stmt ::= */ yytestcase(yyruleno==121);
      /* (122) for_action_stmt_nonEmpty ::= assign_stmt */ yytestcase(yyruleno==122);
      /* (123) for_action_stmt_nonEmpty ::= for_action_stmt_nonEmpty COMMA for_action_stmt_nonEmpty */ yytestcase(yyruleno==123);
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
#line 2028 "parser\\epparser.c"
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
#line 627 "parser\\epparser.lemon"


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
#line 2281 "parser\\epparser.c"
