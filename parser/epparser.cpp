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
#include "tokenAdapter.h"
#include "parserUtilities.h"

struct ParserStruct {
    PyGenerator gen;
    ClosureManager closure;
};

int currentTokenizingLine;
#line 28 "parser\\epparser.c"
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
#define YYNOCODE 105
#define YYACTIONTYPE unsigned short int
#define ParseTOKENTYPE Token*
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  int yy209;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL  ParserStruct* ps ;
#define ParseARG_PDECL , ParserStruct* ps 
#define ParseARG_FETCH  ParserStruct* ps  = yypParser->ps 
#define ParseARG_STORE yypParser->ps  = ps 
#define YYNSTATE 239
#define YYNRULE 118
#define YYERRORSYMBOL 57
#define YYERRSYMDT yy209
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
#define YY_ACTTAB_COUNT (731)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */    98,   90,  144,   71,  149,   89,  132,  150,   97,   44,
 /*    10 */    45,   43,  132,  206,  181,  180,  179,  178,  177,  109,
 /*    20 */     5,   49,  157,   18,   19,  238,  174,  106,    3,  173,
 /*    30 */     2,  172,  171,  170,  107,    4,    1,  167,   59,   58,
 /*    40 */   175,  168,   98,    7,  210,  144,   71,   89,  147,  132,
 /*    50 */    97,  142,  229,  134,  132,  258,  181,  180,  179,  178,
 /*    60 */   177,  109,    5,   49,  199,  237,  149,   28,  174,  106,
 /*    70 */     3,  173,    2,  172,  171,  170,  147,   25,  141,  167,
 /*    80 */    59,   58,  175,  168,   98,    7,   88,  144,   71,   89,
 /*    90 */    27,  132,   97,  140,  110,  236,  132,  143,  181,  180,
 /*   100 */   179,  178,  177,  109,    5,   49,  196,   18,   19,   60,
 /*   110 */   174,  106,    3,  173,    2,  172,  171,  170,  148,  146,
 /*   120 */   139,  167,   59,   58,  175,  168,   98,    7,   86,  144,
 /*   130 */    71,   89,  235,  132,   97,   26,  200,  234,  132,   24,
 /*   140 */   181,  180,  179,  178,  177,  109,    5,   49,  193,   18,
 /*   150 */    19,  233,  174,  106,    3,  173,    2,  172,  171,  170,
 /*   160 */   232,  148,  145,  167,   59,   58,  175,  168,   98,    7,
 /*   170 */    85,  144,   71,   89,  209,  132,   97,  236,  197,  137,
 /*   180 */   132,  136,  181,  180,  179,  178,  177,  109,    5,   49,
 /*   190 */   191,   18,   19,  135,  174,  106,    3,  173,    2,  172,
 /*   200 */   171,  170,   26,  148,   87,  167,   59,   58,  175,  168,
 /*   210 */    98,    7,  141,  138,   70,   89,  215,  132,   97,   26,
 /*   220 */   194,  128,  132,  133,  181,  180,  179,  178,  177,  109,
 /*   230 */     5,   49,  158,  192,  148,  104,  174,  106,    3,  173,
 /*   240 */     2,  172,  171,  170,  259,  148,  156,  167,   59,   58,
 /*   250 */   175,  168,   96,    7,   84,  144,   71,   89,  203,  132,
 /*   260 */    97,  138,   81,   12,  132,  132,  181,  180,  179,  178,
 /*   270 */   177,  109,    5,   49,   26,   26,  148,  111,  174,  106,
 /*   280 */     3,  173,    2,  172,  171,  170,  358,    9,   20,   56,
 /*   290 */    59,   58,  175,  166,    8,   89,  138,   61,   97,  129,
 /*   300 */   132,   83,  132,  228,  181,  180,  179,  178,  177,  109,
 /*   310 */     5,   49,  126,  202,  188,  125,  174,  106,    3,  173,
 /*   320 */     2,  172,  171,  170,  227,  123,  122,   57,   59,   58,
 /*   330 */   175,  165,  226,  120,  163,   34,   32,   31,   30,   29,
 /*   340 */    33,   39,   38,   40,   42,   41,   48,   47,   44,   45,
 /*   350 */    43,   17,  119,  225,   39,   38,   40,   42,   41,   48,
 /*   360 */    47,   44,   45,   43,   37,   36,   19,   10,   22,  214,
 /*   370 */    35,  231,   91,  230,  138,   61,  208,   46,  132,  219,
 /*   380 */   131,  130,  127,  124,  121,  211,   16,   39,   38,   40,
 /*   390 */    42,   41,   48,   47,   44,   45,   43,  117,  207,   37,
 /*   400 */    36,   50,  205,   15,   14,   35,  231,   91,   13,  138,
 /*   410 */    82,  198,   46,  132,  204,  131,  130,  127,  124,  121,
 /*   420 */    39,   38,   40,   42,   41,   48,   47,   44,   45,   43,
 /*   430 */    52,   23,  117,  190,   37,   36,  189,   11,  186,   94,
 /*   440 */    35,  231,   91,   99,  183,  176,  216,   46,  213,  159,
 /*   450 */   131,  130,  127,  124,  121,   92,   51,  138,   61,   37,
 /*   460 */    36,  132,  118,   93,  101,   35,  231,   91,  164,  162,
 /*   470 */   185,  216,   46,  184,  150,  131,  130,  127,  124,  121,
 /*   480 */   160,  359,  138,   61,   37,   36,  132,  218,  108,  359,
 /*   490 */    35,  231,   91,  359,   80,  138,   63,   46,  359,  132,
 /*   500 */   131,  130,  127,  124,  121,  359,  187,   53,  182,   54,
 /*   510 */   201,   80,  195,  105,  359,  103,  102,  359,   21,  359,
 /*   520 */   101,  359,  164,  359,   53,  182,   54,  201,   80,  195,
 /*   530 */   105,  359,  103,  102,  359,   21,  359,  101,  359,  161,
 /*   540 */   359,   53,  182,   54,  201,  359,  195,  105,  359,  103,
 /*   550 */   102,  359,   21,  359,  101,  169,   37,   36,  359,  359,
 /*   560 */   359,  359,   35,  231,   91,  359,  138,   61,  359,   46,
 /*   570 */   132,  217,  131,  130,  127,  124,  121,   38,   40,   42,
 /*   580 */    41,   48,   47,   44,   45,   43,  359,  359,   40,   42,
 /*   590 */    41,   48,   47,   44,   45,   43,   42,   41,   48,   47,
 /*   600 */    44,   45,   43,  239,  153,  359,  152,   48,   47,   44,
 /*   610 */    45,   43,  138,   70,  114,  116,  132,  359,  138,   70,
 /*   620 */   100,  116,  132,  359,  112,    6,  154,  359,  359,  138,
 /*   630 */    70,  115,  116,  132,  359,  155,  151,  138,  212,  138,
 /*   640 */   224,  132,   55,  132,   54,  359,  138,   61,  359,  359,
 /*   650 */   132,   79,  113,  359,  359,  138,   61,  359,   95,  132,
 /*   660 */    78,  138,   61,  138,  223,  132,   77,  132,  359,  138,
 /*   670 */    76,  359,  359,  132,  138,   75,  138,   74,  132,  359,
 /*   680 */   132,  138,   72,  359,  359,  132,  138,   73,  138,  222,
 /*   690 */   132,  359,  132,  359,  359,  138,  221,  138,  220,  132,
 /*   700 */   359,  132,  138,   69,  138,   68,  132,  359,  132,  138,
 /*   710 */    67,  359,  359,  132,  359,  359,  138,   66,  138,   65,
 /*   720 */   132,  359,  132,  359,  138,   64,  138,   62,  132,  359,
 /*   730 */   132,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    57,   64,   65,   66,    1,   62,   69,   26,   65,   20,
 /*    10 */    21,   22,   69,   32,   71,   72,   73,   74,   75,   76,
 /*    20 */    77,   78,   79,    3,    4,   26,   83,   84,   85,   86,
 /*    30 */    87,   88,   89,   90,   80,   81,   82,   94,   95,   96,
 /*    40 */    97,   98,   57,  100,   64,   65,   66,   62,    1,   69,
 /*    50 */    65,    1,   32,   29,   69,   31,   71,   72,   73,   74,
 /*    60 */    75,   76,   77,   78,   79,   26,    1,    2,   83,   84,
 /*    70 */    85,   86,   87,   88,   89,   90,    1,    2,   28,   94,
 /*    80 */    95,   96,   97,   98,   57,  100,   64,   65,   66,   62,
 /*    90 */     2,   69,   65,    1,   29,   40,   69,   27,   71,   72,
 /*   100 */    73,   74,   75,   76,   77,   78,   79,    3,    4,   27,
 /*   110 */    83,   84,   85,   86,   87,   88,   89,   90,   62,   63,
 /*   120 */    28,   94,   95,   96,   97,   98,   57,  100,   64,   65,
 /*   130 */    66,   62,   25,   69,   65,    1,   32,   28,   69,    2,
 /*   140 */    71,   72,   73,   74,   75,   76,   77,   78,   79,    3,
 /*   150 */     4,   25,   83,   84,   85,   86,   87,   88,   89,   90,
 /*   160 */    28,   62,   63,   94,   95,   96,   97,   98,   57,  100,
 /*   170 */    64,   65,   66,   62,   40,   69,   65,   40,   32,   27,
 /*   180 */    69,   27,   71,   72,   73,   74,   75,   76,   77,   78,
 /*   190 */    79,    3,    4,   25,   83,   84,   85,   86,   87,   88,
 /*   200 */    89,   90,    1,   62,   63,   94,   95,   96,   97,   98,
 /*   210 */    57,  100,   28,   65,   66,   62,   68,   69,   65,    1,
 /*   220 */    32,   30,   69,   26,   71,   72,   73,   74,   75,   76,
 /*   230 */    77,   78,   79,   32,   62,   63,   83,   84,   85,   86,
 /*   240 */    87,   88,   89,   90,   31,   62,   63,   94,   95,   96,
 /*   250 */    97,   98,   57,  100,   64,   65,   66,   62,   40,   69,
 /*   260 */    65,   65,   66,   31,   69,   69,   71,   72,   73,   74,
 /*   270 */    75,   76,   77,   78,    1,    1,   62,   63,   83,   84,
 /*   280 */    85,   86,   87,   88,   89,   90,   59,   60,   31,   94,
 /*   290 */    95,   96,   97,   98,   99,   62,   65,   66,   65,   31,
 /*   300 */    69,   70,   69,   32,   71,   72,   73,   74,   75,   76,
 /*   310 */    77,   78,   31,   40,   40,   30,   83,   84,   85,   86,
 /*   320 */    87,   88,   89,   90,   32,   31,   30,   94,   95,   96,
 /*   330 */    97,   98,   32,   31,  101,    7,    8,    9,   10,   11,
 /*   340 */    12,   13,   14,   15,   16,   17,   18,   19,   20,   21,
 /*   350 */    22,    5,   30,   32,   13,   14,   15,   16,   17,   18,
 /*   360 */    19,   20,   21,   22,   18,   19,    4,   31,    1,   32,
 /*   370 */    24,   25,   26,   32,   65,   66,   26,   31,   69,   70,
 /*   380 */    34,   35,   36,   37,   38,   32,    5,   13,   14,   15,
 /*   390 */    16,   17,   18,   19,   20,   21,   22,   51,   32,   18,
 /*   400 */    19,   31,   26,   31,   31,   24,   25,   26,   31,   65,
 /*   410 */    66,   42,   31,   69,   40,   34,   35,   36,   37,   38,
 /*   420 */    13,   14,   15,   16,   17,   18,   19,   20,   21,   22,
 /*   430 */    31,   46,   51,   40,   18,   19,   40,   31,   40,   26,
 /*   440 */    24,   25,   26,   32,   40,   40,   30,   31,   32,   54,
 /*   450 */    34,   35,   36,   37,   38,   61,   56,   65,   66,   18,
 /*   460 */    19,   69,   70,   25,   52,   24,   25,   26,   54,  101,
 /*   470 */    95,   30,   31,   95,   26,   34,   35,   36,   37,   38,
 /*   480 */   101,  104,   65,   66,   18,   19,   69,   70,   43,  104,
 /*   490 */    24,   25,   26,  104,   26,   65,   66,   31,  104,   69,
 /*   500 */    34,   35,   36,   37,   38,  104,   40,   39,   40,   41,
 /*   510 */    42,   26,   44,   45,  104,   47,   48,  104,   50,  104,
 /*   520 */    52,  104,   54,  104,   39,   40,   41,   42,   26,   44,
 /*   530 */    45,  104,   47,   48,  104,   50,  104,   52,  104,   54,
 /*   540 */   104,   39,   40,   41,   42,  104,   44,   45,  104,   47,
 /*   550 */    48,  104,   50,  104,   52,   53,   18,   19,  104,  104,
 /*   560 */   104,  104,   24,   25,   26,  104,   65,   66,  104,   31,
 /*   570 */    69,   70,   34,   35,   36,   37,   38,   14,   15,   16,
 /*   580 */    17,   18,   19,   20,   21,   22,  104,  104,   15,   16,
 /*   590 */    17,   18,   19,   20,   21,   22,   16,   17,   18,   19,
 /*   600 */    20,   21,   22,    0,   71,  104,   73,   18,   19,   20,
 /*   610 */    21,   22,   65,   66,   67,   68,   69,  104,   65,   66,
 /*   620 */    67,   68,   69,  104,   91,   92,   93,  104,  104,   65,
 /*   630 */    66,   67,   68,   69,  104,  102,  103,   65,   66,   65,
 /*   640 */    66,   69,   39,   69,   41,  104,   65,   66,  104,  104,
 /*   650 */    69,   70,   49,  104,  104,   65,   66,  104,   55,   69,
 /*   660 */    70,   65,   66,   65,   66,   69,   70,   69,  104,   65,
 /*   670 */    66,  104,  104,   69,   65,   66,   65,   66,   69,  104,
 /*   680 */    69,   65,   66,  104,  104,   69,   65,   66,   65,   66,
 /*   690 */    69,  104,   69,  104,  104,   65,   66,   65,   66,   69,
 /*   700 */   104,   69,   65,   66,   65,   66,   69,  104,   69,   65,
 /*   710 */    66,  104,  104,   69,  104,  104,   65,   66,   65,   66,
 /*   720 */    69,  104,   69,  104,   65,   66,   65,   66,   69,  104,
 /*   730 */    69,
};
#define YY_SHIFT_USE_DFLT (-20)
#define YY_SHIFT_COUNT (150)
#define YY_SHIFT_MIN   (-19)
#define YY_SHIFT_MAX   (603)
static const short yy_shift_ofst[] = {
 /*     0 */   -20,  502,  502,  502,  502,  502,  502,  485,  468,  603,
 /*    10 */   416,  441,  441,  346,  346,  346,  381,  381,  346,  346,
 /*    20 */   346,  466,  441,  538,  538,  538,  538,  538,  538,  538,
 /*    30 */   538,  538,  538,  538,  538,  538,  538,  538,  538,  538,
 /*    40 */   538,  538,  538,  538,  538,  538,  538,  538,  538,  445,
 /*    50 */   -19,  448,  448,  448,  448,  448,  414,  414,  412,  412,
 /*    60 */   438,  328,  374,  341,  407,  407,  407,  407,  407,  407,
 /*    70 */   407,  407,  563,  573,  580,  589,  589,  188,  146,  104,
 /*    80 */    65,  -11,  -11,   20,  274,  201,  273,  137,  218,   75,
 /*    90 */   134,   24,   92,   50,  400,  413,  395,  405,  404,  398,
 /*   100 */   411,  406,  396,  393,  385,  399,  377,  373,  369,  372,
 /*   110 */   376,  366,  370,  350,  353,  337,  367,  336,  362,  321,
 /*   120 */   322,  302,  300,  296,  294,  292,  285,  281,  271,  191,
 /*   130 */   268,  257,  232,  213,  197,  184,  168,  154,  152,  132,
 /*   140 */   126,  109,  107,   82,   70,   88,   55,   39,   47,   -1,
 /*   150 */     3,
};
#define YY_REDUCE_USE_DFLT (-64)
#define YY_REDUCE_COUNT (60)
#define YY_REDUCE_MIN   (-63)
#define YY_REDUCE_MAX   (661)
static const short yy_reduce_ofst[] = {
 /*     0 */   227,  153,  111,   69,   27,  -15,  -57,  195,  233,  533,
 /*    10 */   564,  553,  547,  596,  590,  581,  501,  417,  392,  309,
 /*    20 */   231,  190,  148,  106,   64,   22,  -20,  -63,  661,  659,
 /*    30 */   653,  651,  644,  639,  637,  632,  630,  623,  621,  616,
 /*    40 */   611,  609,  604,  598,  574,  572,  430,  344,  196,  -46,
 /*    50 */   214,  183,  172,  141,   99,   56,  379,  368,  378,  375,
 /*    60 */   394,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   355,  357,  357,  357,  357,  357,  357,  357,  357,  357,
 /*    10 */   357,  253,  253,  357,  357,  357,  357,  357,  357,  357,
 /*    20 */   357,  357,  357,  357,  357,  357,  357,  357,  357,  357,
 /*    30 */   357,  357,  357,  357,  357,  357,  357,  357,  357,  357,
 /*    40 */   357,  357,  357,  357,  357,  357,  357,  357,  357,  303,
 /*    50 */   357,  357,  357,  357,  357,  357,  357,  357,  324,  323,
 /*    60 */   357,  357,  357,  357,  286,  285,  284,  283,  282,  281,
 /*    70 */   254,  248,  276,  277,  275,  274,  273,  357,  357,  357,
 /*    80 */   258,  268,  269,  357,  357,  357,  357,  357,  357,  357,
 /*    90 */   357,  251,  357,  357,  357,  357,  357,  357,  357,  357,
 /*   100 */   357,  357,  357,  357,  357,  357,  357,  357,  302,  357,
 /*   110 */   357,  357,  357,  357,  357,  357,  257,  357,  288,  357,
 /*   120 */   357,  357,  357,  357,  357,  357,  357,  357,  357,  357,
 /*   130 */   357,  357,  357,  252,  357,  357,  357,  357,  261,  357,
 /*   140 */   357,  357,  357,  357,  261,  357,  357,  357,  245,  357,
 /*   150 */   244,  356,  354,  353,  352,  351,  350,  315,  304,  349,
 /*   160 */   346,  345,  348,  347,  342,  340,  339,  344,  343,  341,
 /*   170 */   338,  337,  336,  335,  334,  333,  332,  331,  330,  329,
 /*   180 */   328,  327,  326,  325,  322,  321,  320,  316,  317,  311,
 /*   190 */   310,  309,  308,  307,  306,  305,  301,  300,  299,  298,
 /*   200 */   297,  296,  292,  295,  294,  259,  314,  313,  312,  293,
 /*   210 */   249,  260,  270,  319,  318,  256,  255,  290,  289,  287,
 /*   220 */   280,  279,  278,  272,  271,  267,  266,  265,  264,  263,
 /*   230 */   262,  250,  246,  241,  247,  240,  291,  243,  242,
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
  "$",             "COMMA",         "ASSIGN",        "LOR",         
  "LAND",          "LNOT",          "DOUBLE_LNOT",   "EQ",          
  "LE",            "LT",            "GE",            "GT",          
  "NE",            "BITOR",         "BITXOR",        "BITAND",      
  "LSHIFT",        "RSHIFT",        "PLUS",          "MINUS",       
  "DIVIDE",        "MULTIPLY",      "MOD",           "UNARY",       
  "BITNOT",        "NUMBER",        "NAME",          "LSQBRACKET",  
  "RSQBRACKET",    "PERIOD",        "STRING",        "LPAREN",      
  "RPAREN",        "FUNCCALL",      "L2V",           "MAPSTRING",   
  "UNIT",          "SWITCH",        "LOCATION",      "VAR",         
  "SEMICOLON",     "CONST",         "IF",            "ELSE",        
  "WHILE",         "FOR",           "COLON",         "CONTINUE",    
  "BREAK",         "FUNCTION",      "RETURN",        "CONDITIONNAME",
  "ACTIONNAME",    "LBRACKET",      "RBRACKET",      "FROM",        
  "IMPORT",        "error",         "nt",            "program",     
  "chunks",        "numList",       "nameListMulti",  "nameList",    
  "exprList",      "funcexpr",      "expr",          "fArgs",       
  "fArgsAny",      "funcName",      "lexpr",         "vdef_stmt",   
  "vdefAssign_stmt",  "cdef_stmt",     "assign_stmt",   "assignMulti_stmt",
  "if_start",      "if_header",     "if_block",      "stmt",        
  "elif_start",    "elif_header",   "else_header",   "if_stmt",     
  "while_start",   "while_header",  "while_stmt",    "foreach_header",
  "foreach_stmt",  "continue_stmt",  "break_stmt",    "function_start",
  "function_header",  "fdef_chunk",    "return_stmt",   "action",      
  "actions",       "actionStmt",    "bodyStmt",      "bodyStmtList",
  "lbracket",      "rbracket",      "import_chunk",  "chunk",       
};
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *const yyRuleName[] = {
 /*   0 */ "program ::= chunks",
 /*   1 */ "numList ::= NUMBER COMMA NUMBER",
 /*   2 */ "numList ::= numList COMMA NUMBER",
 /*   3 */ "nameListMulti ::= NAME COMMA NAME",
 /*   4 */ "nameListMulti ::= nameListMulti COMMA NAME",
 /*   5 */ "nameList ::= NAME",
 /*   6 */ "nameList ::= nameListMulti",
 /*   7 */ "exprList ::= funcexpr LSQBRACKET LSQBRACKET numList RSQBRACKET RSQBRACKET",
 /*   8 */ "expr ::= funcexpr LSQBRACKET LSQBRACKET NUMBER RSQBRACKET RSQBRACKET",
 /*   9 */ "exprList ::= expr",
 /*  10 */ "exprList ::= exprList COMMA exprList",
 /*  11 */ "expr ::= NUMBER",
 /*  12 */ "expr ::= NAME",
 /*  13 */ "expr ::= NAME PERIOD NAME",
 /*  14 */ "fArgs ::=",
 /*  15 */ "fArgsAny ::= expr",
 /*  16 */ "fArgsAny ::= STRING",
 /*  17 */ "fArgsAny ::= fArgsAny COMMA fArgsAny",
 /*  18 */ "fArgs ::= fArgsAny",
 /*  19 */ "funcName ::= NAME",
 /*  20 */ "funcName ::= NAME PERIOD NAME",
 /*  21 */ "funcexpr ::= funcName LPAREN fArgs RPAREN",
 /*  22 */ "expr ::= funcexpr",
 /*  23 */ "expr ::= LPAREN expr RPAREN",
 /*  24 */ "expr ::= L2V LPAREN lexpr RPAREN",
 /*  25 */ "expr ::= MAPSTRING LPAREN STRING RPAREN",
 /*  26 */ "expr ::= UNIT LPAREN STRING RPAREN",
 /*  27 */ "expr ::= SWITCH LPAREN STRING RPAREN",
 /*  28 */ "expr ::= LOCATION LPAREN STRING RPAREN",
 /*  29 */ "expr ::= expr PLUS expr",
 /*  30 */ "expr ::= expr MINUS expr",
 /*  31 */ "expr ::= expr MULTIPLY expr",
 /*  32 */ "expr ::= expr DIVIDE expr",
 /*  33 */ "expr ::= expr MOD expr",
 /*  34 */ "expr ::= expr LSHIFT expr",
 /*  35 */ "expr ::= expr RSHIFT expr",
 /*  36 */ "expr ::= expr BITAND expr",
 /*  37 */ "expr ::= expr BITOR expr",
 /*  38 */ "expr ::= expr BITXOR expr",
 /*  39 */ "expr ::= PLUS expr",
 /*  40 */ "expr ::= MINUS expr",
 /*  41 */ "expr ::= BITNOT expr",
 /*  42 */ "lexpr ::= expr EQ expr",
 /*  43 */ "lexpr ::= expr NE expr",
 /*  44 */ "lexpr ::= expr LE expr",
 /*  45 */ "lexpr ::= expr LT expr",
 /*  46 */ "lexpr ::= expr GE expr",
 /*  47 */ "lexpr ::= expr GT expr",
 /*  48 */ "lexpr ::= lexpr LAND lexpr",
 /*  49 */ "lexpr ::= lexpr LOR lexpr",
 /*  50 */ "lexpr ::= LNOT lexpr",
 /*  51 */ "lexpr ::= LNOT LNOT lexpr",
 /*  52 */ "vdef_stmt ::= VAR nameList SEMICOLON",
 /*  53 */ "vdefAssign_stmt ::= VAR nameList ASSIGN exprList SEMICOLON",
 /*  54 */ "cdef_stmt ::= CONST nameList ASSIGN exprList SEMICOLON",
 /*  55 */ "assign_stmt ::= NAME ASSIGN expr SEMICOLON",
 /*  56 */ "assignMulti_stmt ::= nameListMulti ASSIGN exprList SEMICOLON",
 /*  57 */ "if_start ::= IF",
 /*  58 */ "if_header ::= if_start LPAREN lexpr RPAREN",
 /*  59 */ "if_block ::= if_header stmt",
 /*  60 */ "elif_start ::= ELSE IF",
 /*  61 */ "elif_header ::= elif_start LPAREN lexpr RPAREN",
 /*  62 */ "if_block ::= if_block elif_header stmt",
 /*  63 */ "else_header ::= ELSE",
 /*  64 */ "if_stmt ::= if_block",
 /*  65 */ "if_stmt ::= if_block else_header stmt",
 /*  66 */ "while_start ::= WHILE",
 /*  67 */ "while_header ::= while_start LPAREN lexpr RPAREN",
 /*  68 */ "while_stmt ::= while_header stmt",
 /*  69 */ "foreach_header ::= FOR LPAREN nameList COLON exprList RPAREN",
 /*  70 */ "foreach_stmt ::= foreach_header stmt",
 /*  71 */ "continue_stmt ::= CONTINUE SEMICOLON",
 /*  72 */ "break_stmt ::= BREAK SEMICOLON",
 /*  73 */ "function_start ::= FUNCTION NAME",
 /*  74 */ "function_header ::= function_start LPAREN nameList RPAREN",
 /*  75 */ "function_header ::= function_start LPAREN RPAREN",
 /*  76 */ "fdef_chunk ::= function_header stmt",
 /*  77 */ "return_stmt ::= RETURN SEMICOLON",
 /*  78 */ "return_stmt ::= RETURN exprList SEMICOLON",
 /*  79 */ "lexpr ::= CONDITIONNAME LPAREN fArgs RPAREN",
 /*  80 */ "lexpr ::= CONDITIONNAME LPAREN RPAREN",
 /*  81 */ "action ::= ACTIONNAME LPAREN fArgs RPAREN SEMICOLON",
 /*  82 */ "actions ::= action action",
 /*  83 */ "actions ::= actions action",
 /*  84 */ "actionStmt ::= action",
 /*  85 */ "actionStmt ::= actions",
 /*  86 */ "stmt ::= error SEMICOLON",
 /*  87 */ "bodyStmt ::= SEMICOLON",
 /*  88 */ "bodyStmt ::= vdef_stmt",
 /*  89 */ "bodyStmt ::= vdefAssign_stmt",
 /*  90 */ "bodyStmt ::= cdef_stmt",
 /*  91 */ "bodyStmt ::= assign_stmt",
 /*  92 */ "bodyStmt ::= assignMulti_stmt",
 /*  93 */ "bodyStmt ::= funcexpr SEMICOLON",
 /*  94 */ "bodyStmt ::= actionStmt",
 /*  95 */ "bodyStmt ::= if_stmt",
 /*  96 */ "bodyStmt ::= while_stmt",
 /*  97 */ "bodyStmt ::= foreach_stmt",
 /*  98 */ "bodyStmt ::= continue_stmt",
 /*  99 */ "bodyStmt ::= break_stmt",
 /* 100 */ "bodyStmtList ::= bodyStmt",
 /* 101 */ "bodyStmtList ::= bodyStmtList bodyStmt",
 /* 102 */ "lbracket ::= LBRACKET",
 /* 103 */ "rbracket ::= RBRACKET",
 /* 104 */ "stmt ::= bodyStmt",
 /* 105 */ "stmt ::= return_stmt",
 /* 106 */ "stmt ::= lbracket RBRACKET",
 /* 107 */ "stmt ::= lbracket return_stmt rbracket",
 /* 108 */ "stmt ::= lbracket bodyStmtList rbracket",
 /* 109 */ "stmt ::= lbracket bodyStmtList return_stmt rbracket",
 /* 110 */ "stmt ::= lbracket error RBRACKET",
 /* 111 */ "import_chunk ::= FROM NAME IMPORT nameList",
 /* 112 */ "chunk ::= import_chunk",
 /* 113 */ "chunk ::= fdef_chunk",
 /* 114 */ "chunk ::= vdef_stmt",
 /* 115 */ "chunk ::= cdef_stmt",
 /* 116 */ "chunks ::=",
 /* 117 */ "chunks ::= chunks chunk",
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
    case 58: /* nt */
{
#line 30 "parser\\epparser.lemon"
 delete (yypminor->yy0); 
#line 704 "parser\\epparser.c"
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
  { 59, 1 },
  { 61, 3 },
  { 61, 3 },
  { 62, 3 },
  { 62, 3 },
  { 63, 1 },
  { 63, 1 },
  { 64, 6 },
  { 66, 6 },
  { 64, 1 },
  { 64, 3 },
  { 66, 1 },
  { 66, 1 },
  { 66, 3 },
  { 67, 0 },
  { 68, 1 },
  { 68, 1 },
  { 68, 3 },
  { 67, 1 },
  { 69, 1 },
  { 69, 3 },
  { 65, 4 },
  { 66, 1 },
  { 66, 3 },
  { 66, 4 },
  { 66, 4 },
  { 66, 4 },
  { 66, 4 },
  { 66, 4 },
  { 66, 3 },
  { 66, 3 },
  { 66, 3 },
  { 66, 3 },
  { 66, 3 },
  { 66, 3 },
  { 66, 3 },
  { 66, 3 },
  { 66, 3 },
  { 66, 3 },
  { 66, 2 },
  { 66, 2 },
  { 66, 2 },
  { 70, 3 },
  { 70, 3 },
  { 70, 3 },
  { 70, 3 },
  { 70, 3 },
  { 70, 3 },
  { 70, 3 },
  { 70, 3 },
  { 70, 2 },
  { 70, 3 },
  { 71, 3 },
  { 72, 5 },
  { 73, 5 },
  { 74, 4 },
  { 75, 4 },
  { 76, 1 },
  { 77, 4 },
  { 78, 2 },
  { 80, 2 },
  { 81, 4 },
  { 78, 3 },
  { 82, 1 },
  { 83, 1 },
  { 83, 3 },
  { 84, 1 },
  { 85, 4 },
  { 86, 2 },
  { 87, 6 },
  { 88, 2 },
  { 89, 2 },
  { 90, 2 },
  { 91, 2 },
  { 92, 4 },
  { 92, 3 },
  { 93, 2 },
  { 94, 2 },
  { 94, 3 },
  { 70, 4 },
  { 70, 3 },
  { 95, 5 },
  { 96, 2 },
  { 96, 2 },
  { 97, 1 },
  { 97, 1 },
  { 79, 2 },
  { 98, 1 },
  { 98, 1 },
  { 98, 1 },
  { 98, 1 },
  { 98, 1 },
  { 98, 1 },
  { 98, 2 },
  { 98, 1 },
  { 98, 1 },
  { 98, 1 },
  { 98, 1 },
  { 98, 1 },
  { 98, 1 },
  { 99, 1 },
  { 99, 2 },
  { 100, 1 },
  { 101, 1 },
  { 79, 1 },
  { 79, 1 },
  { 79, 2 },
  { 79, 3 },
  { 79, 3 },
  { 79, 4 },
  { 79, 3 },
  { 102, 4 },
  { 103, 1 },
  { 103, 1 },
  { 103, 1 },
  { 103, 1 },
  { 60, 0 },
  { 60, 2 },
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
      case 1: /* numList ::= NUMBER COMMA NUMBER */
      case 2: /* numList ::= numList COMMA NUMBER */ yytestcase(yyruleno==2);
#line 56 "parser\\epparser.lemon"
{
    yygotominor.yy0 = new Token(yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data, yymsp[0].minor.yy0);
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 1121 "parser\\epparser.c"
        break;
      case 3: /* nameListMulti ::= NAME COMMA NAME */
      case 4: /* nameListMulti ::= nameListMulti COMMA NAME */ yytestcase(yyruleno==4);
      case 10: /* exprList ::= exprList COMMA exprList */ yytestcase(yyruleno==10);
#line 65 "parser\\epparser.lemon"
{ yygotominor.yy0 = new Token((yymsp[-2].minor.yy0->data) + ", " + (yymsp[0].minor.yy0->data), yymsp[0].minor.yy0); delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1128 "parser\\epparser.c"
        break;
      case 5: /* nameList ::= NAME */
      case 6: /* nameList ::= nameListMulti */ yytestcase(yyruleno==6);
      case 9: /* exprList ::= expr */ yytestcase(yyruleno==9);
      case 11: /* expr ::= NUMBER */ yytestcase(yyruleno==11);
      case 15: /* fArgsAny ::= expr */ yytestcase(yyruleno==15);
      case 16: /* fArgsAny ::= STRING */ yytestcase(yyruleno==16);
      case 18: /* fArgs ::= fArgsAny */ yytestcase(yyruleno==18);
      case 22: /* expr ::= funcexpr */ yytestcase(yyruleno==22);
      case 51: /* lexpr ::= LNOT LNOT lexpr */ yytestcase(yyruleno==51);
#line 67 "parser\\epparser.lemon"
{ yygotominor.yy0 = yymsp[0].minor.yy0; }
#line 1141 "parser\\epparser.c"
        break;
      case 7: /* exprList ::= funcexpr LSQBRACKET LSQBRACKET numList RSQBRACKET RSQBRACKET */
      case 8: /* expr ::= funcexpr LSQBRACKET LSQBRACKET NUMBER RSQBRACKET RSQBRACKET */ yytestcase(yyruleno==8);
#line 70 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[-2].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = _SRET(" << yymsp[-5].minor.yy0->data << ", [" << yymsp[-2].minor.yy0->data << "])" << std::endl;
    delete yymsp[-5].minor.yy0; delete yymsp[-2].minor.yy0;
}
#line 1151 "parser\\epparser.c"
        break;
      case 12: /* expr ::= NAME */
#line 87 "parser\\epparser.lemon"
{
    if(!ps->closure.getConstant(yymsp[0].minor.yy0->data) && !ps->closure.getVariable(yymsp[0].minor.yy0->data)) {
        throw_error(yymsp[0].minor.yy0->line, 103, ("Undeclared \'" + (yymsp[0].minor.yy0->data) + "\'"));
        ps->closure.defVariable(yymsp[0].minor.yy0->data);
    }
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1162 "parser\\epparser.c"
        break;
      case 13: /* expr ::= NAME PERIOD NAME */
#line 95 "parser\\epparser.lemon"
{
    if(!ps->closure.getConstant(yymsp[-2].minor.yy0->data)) {
        throw_error(yymsp[-2].minor.yy0->line, 103, ("Undeclared constant \'" + (yymsp[-2].minor.yy0->data) + "\'"));
        ps->closure.defConstant(yymsp[-2].minor.yy0->data);
    }
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + "." + yymsp[0].minor.yy0->data;
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0, ps->gen);
}
#line 1175 "parser\\epparser.c"
        break;
      case 14: /* fArgs ::= */
#line 106 "parser\\epparser.lemon"
{
    yygotominor.yy0 = new Token(TOKEN_TEMP, "", -1);
}
#line 1182 "parser\\epparser.c"
        break;
      case 17: /* fArgsAny ::= fArgsAny COMMA fArgsAny */
#line 112 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data;
    yymsp[-2].minor.yy0->type = TOKEN_TEMP;
    yygotominor.yy0 = yymsp[-2].minor.yy0;
    delete yymsp[0].minor.yy0;
}
#line 1192 "parser\\epparser.c"
        break;
      case 19: /* funcName ::= NAME */
#line 121 "parser\\epparser.lemon"
{
    funcNamePreprocess(yymsp[0].minor.yy0->data);
    if (!ps->closure.getFunction(yymsp[0].minor.yy0->data)) {
        throw_error(yymsp[0].minor.yy0->line, 4449, ("Undefined function " + yymsp[0].minor.yy0->data));
        ps->closure.defFunction(yymsp[0].minor.yy0->data);
    }
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1204 "parser\\epparser.c"
        break;
      case 20: /* funcName ::= NAME PERIOD NAME */
#line 129 "parser\\epparser.lemon"
{
    // Preprocess name
    if (!ps->closure.getConstant(yymsp[-2].minor.yy0->data)) {
        if(ps->closure.defFunction(yymsp[-2].minor.yy0->data)) {
            throw_error(yymsp[-2].minor.yy0->line, 8200, ("Undefined constant " + yymsp[-2].minor.yy0->data));
        }
        else if(ps->closure.getVariable(yymsp[-2].minor.yy0->data)) {
            throw_error(yymsp[-2].minor.yy0->line, 8208, ("Normal variable cannot have methods : " + yymsp[-2].minor.yy0->data));
        }
        else {
            throw_error(yymsp[-2].minor.yy0->line, 553, ("Calling method of non-constant : " + yymsp[-2].minor.yy0->data));
        }
    }

    yymsp[0].minor.yy0->data = yymsp[-2].minor.yy0->data + "." + yymsp[0].minor.yy0->data;
    delete yymsp[-2].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0, ps->gen);
}
#line 1226 "parser\\epparser.c"
        break;
      case 21: /* funcexpr ::= funcName LPAREN fArgs RPAREN */
#line 148 "parser\\epparser.lemon"
{
    // Preprocess yymsp[-3].minor.yy0
    yymsp[-3].minor.yy0->data += "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0, ps->gen);
}
#line 1235 "parser\\epparser.c"
        break;
      case 23: /* expr ::= LPAREN expr RPAREN */
#line 157 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0, ps->gen);
}
#line 1243 "parser\\epparser.c"
        break;
      case 24: /* expr ::= L2V LPAREN lexpr RPAREN */
#line 162 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "_L2V(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = genTemp(yymsp[-1].minor.yy0);
}
#line 1251 "parser\\epparser.c"
        break;
      case 25: /* expr ::= MAPSTRING LPAREN STRING RPAREN */
#line 167 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetStringIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0, ps->gen);
}
#line 1259 "parser\\epparser.c"
        break;
      case 26: /* expr ::= UNIT LPAREN STRING RPAREN */
#line 172 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetUnitIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0, ps->gen);
}
#line 1267 "parser\\epparser.c"
        break;
      case 27: /* expr ::= SWITCH LPAREN STRING RPAREN */
#line 177 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetSwitchIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0, ps->gen);
}
#line 1275 "parser\\epparser.c"
        break;
      case 28: /* expr ::= LOCATION LPAREN STRING RPAREN */
#line 182 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetLocationIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0, ps->gen);
}
#line 1283 "parser\\epparser.c"
        break;
      case 29: /* expr ::= expr PLUS expr */
#line 188 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "+",  yymsp[0].minor.yy0, ps->gen); }
#line 1288 "parser\\epparser.c"
        break;
      case 30: /* expr ::= expr MINUS expr */
#line 189 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "-",  yymsp[0].minor.yy0, ps->gen); }
#line 1293 "parser\\epparser.c"
        break;
      case 31: /* expr ::= expr MULTIPLY expr */
#line 190 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "*",  yymsp[0].minor.yy0, ps->gen); }
#line 1298 "parser\\epparser.c"
        break;
      case 32: /* expr ::= expr DIVIDE expr */
#line 191 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "//", yymsp[0].minor.yy0, ps->gen); }
#line 1303 "parser\\epparser.c"
        break;
      case 33: /* expr ::= expr MOD expr */
#line 192 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "%",  yymsp[0].minor.yy0, ps->gen); }
#line 1308 "parser\\epparser.c"
        break;
      case 34: /* expr ::= expr LSHIFT expr */
#line 193 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<<", yymsp[0].minor.yy0, ps->gen); }
#line 1313 "parser\\epparser.c"
        break;
      case 35: /* expr ::= expr RSHIFT expr */
#line 194 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">>", yymsp[0].minor.yy0, ps->gen); }
#line 1318 "parser\\epparser.c"
        break;
      case 36: /* expr ::= expr BITAND expr */
#line 195 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "&",  yymsp[0].minor.yy0, ps->gen); }
#line 1323 "parser\\epparser.c"
        break;
      case 37: /* expr ::= expr BITOR expr */
#line 196 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "|",  yymsp[0].minor.yy0, ps->gen); }
#line 1328 "parser\\epparser.c"
        break;
      case 38: /* expr ::= expr BITXOR expr */
#line 197 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "^",  yymsp[0].minor.yy0, ps->gen); }
#line 1333 "parser\\epparser.c"
        break;
      case 39: /* expr ::= PLUS expr */
#line 200 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = +" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1338 "parser\\epparser.c"
        break;
      case 40: /* expr ::= MINUS expr */
#line 201 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = -" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1343 "parser\\epparser.c"
        break;
      case 41: /* expr ::= BITNOT expr */
#line 202 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = ~" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1348 "parser\\epparser.c"
        break;
      case 42: /* lexpr ::= expr EQ expr */
#line 206 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "==", yymsp[0].minor.yy0, ps->gen); }
#line 1353 "parser\\epparser.c"
        break;
      case 43: /* lexpr ::= expr NE expr */
#line 207 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "!=", yymsp[0].minor.yy0, ps->gen); }
#line 1358 "parser\\epparser.c"
        break;
      case 44: /* lexpr ::= expr LE expr */
#line 208 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<=", yymsp[0].minor.yy0, ps->gen); }
#line 1363 "parser\\epparser.c"
        break;
      case 45: /* lexpr ::= expr LT expr */
#line 209 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<",  yymsp[0].minor.yy0, ps->gen); }
#line 1368 "parser\\epparser.c"
        break;
      case 46: /* lexpr ::= expr GE expr */
#line 210 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">=", yymsp[0].minor.yy0, ps->gen); }
#line 1373 "parser\\epparser.c"
        break;
      case 47: /* lexpr ::= expr GT expr */
#line 211 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">" , yymsp[0].minor.yy0, ps->gen); }
#line 1378 "parser\\epparser.c"
        break;
      case 48: /* lexpr ::= lexpr LAND lexpr */
#line 213 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "[" + yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data + "]";
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0, ps->gen);
}
#line 1387 "parser\\epparser.c"
        break;
      case 49: /* lexpr ::= lexpr LOR lexpr */
#line 219 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "EUDOr([" + yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data + "])";
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0, ps->gen);
}
#line 1396 "parser\\epparser.c"
        break;
      case 50: /* lexpr ::= LNOT lexpr */
#line 225 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = "EUDNot([" + yymsp[0].minor.yy0->data + "])";
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0, ps->gen);
}
#line 1404 "parser\\epparser.c"
        break;
      case 52: /* vdef_stmt ::= VAR nameList SEMICOLON */
#line 235 "parser\\epparser.lemon"
{
    std::string& s = yymsp[-1].minor.yy0->data;
    int varCount = std::count(s.begin(), s.end(), ',') + 1;

    // Register variables.
    commaListIter(s, [&](std::string& varname) {
        if(!ps->closure.defVariable(varname)) {
            throw_error(yymsp[-1].minor.yy0->line, 196, ("Redeclaration of variable \'" + varname + "\'"));
        }
    });
    ps->gen << s << " = EUDCreateVariables(" << varCount << ")" << std::endl;
    delete yymsp[-1].minor.yy0;
}
#line 1421 "parser\\epparser.c"
        break;
      case 53: /* vdefAssign_stmt ::= VAR nameList ASSIGN exprList SEMICOLON */
#line 249 "parser\\epparser.lemon"
{
    std::string& s = yymsp[-3].minor.yy0->data;

    // Register variables.
    commaListIter(s, [&](std::string& varname) {
        if(!ps->closure.defVariable(varname)) {
            throw_error(yymsp[-3].minor.yy0->line, 196, ("Redeclaration of variable \'" + varname + "\'"));
        }
    });
    ps->gen << s << " = _MVAR([" << yymsp[-1].minor.yy0->data << "])" << std::endl;
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1437 "parser\\epparser.c"
        break;
      case 54: /* cdef_stmt ::= CONST nameList ASSIGN exprList SEMICOLON */
#line 262 "parser\\epparser.lemon"
{
    std::string& s = yymsp[-3].minor.yy0->data;

    // Register constants.
    commaListIter(s, [&](std::string& constname) {
        if(!ps->closure.defConstant(constname)) {
            throw_error(yymsp[-3].minor.yy0->line, 196, ("Redeclaration of constant \'" + constname + "\'"));
        }
    });
    ps->gen << s << " = List2Assignable([" << yymsp[-1].minor.yy0->data << "])" << std::endl;
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1453 "parser\\epparser.c"
        break;
      case 55: /* assign_stmt ::= NAME ASSIGN expr SEMICOLON */
#line 275 "parser\\epparser.lemon"
{
    ps->gen << yymsp[-3].minor.yy0->data << " << " << yymsp[-1].minor.yy0->data << std::endl;
    if(!ps->closure.getVariable(yymsp[-3].minor.yy0->data)) {
        throw_error(yymsp[-3].minor.yy0->line, 103, ("Undeclared variable \'" + (yymsp[-3].minor.yy0->data) + "\'"));
        ps->closure.defVariable(yymsp[-3].minor.yy0->data);
    }
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1465 "parser\\epparser.c"
        break;
      case 56: /* assignMulti_stmt ::= nameListMulti ASSIGN exprList SEMICOLON */
#line 284 "parser\\epparser.lemon"
{
    ps->gen << "SetVariables([" << yymsp[-3].minor.yy0->data << "], [" << yymsp[-1].minor.yy0->data << "])" << std::endl;

    commaListIter(yymsp[-3].minor.yy0->data, [&](std::string& varname) {
        if(!ps->closure.defVariable(varname)) {
            throw_error(yymsp[-3].minor.yy0->line, 103, ("Undeclared variable \'" + varname + "\'"));
            ps->closure.defVariable(varname);
        }
    });

    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1481 "parser\\epparser.c"
        break;
      case 57: /* if_start ::= IF */
#line 298 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDIf()" << std::endl;
}
#line 1489 "parser\\epparser.c"
        break;
      case 58: /* if_header ::= if_start LPAREN lexpr RPAREN */
      case 67: /* while_header ::= while_start LPAREN lexpr RPAREN */ yytestcase(yyruleno==67);
#line 302 "parser\\epparser.lemon"
{
    ps->gen << "if " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data << "):" << std::endl;
    ps->gen.indent();
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1499 "parser\\epparser.c"
        break;
      case 60: /* elif_start ::= ELSE IF */
#line 310 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen.unindent(false);
    ps->gen << yygotominor.yy0->data << " = EUDElseIf()" << std::endl;
}
#line 1508 "parser\\epparser.c"
        break;
      case 61: /* elif_header ::= elif_start LPAREN lexpr RPAREN */
#line 316 "parser\\epparser.lemon"
{
    ps->gen << "if " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data <<"):" << std::endl;
    ps->gen.indent();
}
#line 1516 "parser\\epparser.c"
        break;
      case 63: /* else_header ::= ELSE */
#line 323 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "if EUDElse()():" << std::endl;
    ps->gen.indent();
}
#line 1525 "parser\\epparser.c"
        break;
      case 64: /* if_stmt ::= if_block */
      case 65: /* if_stmt ::= if_block else_header stmt */ yytestcase(yyruleno==65);
#line 329 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndIf()" << std::endl;
}
#line 1534 "parser\\epparser.c"
        break;
      case 66: /* while_start ::= WHILE */
#line 341 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDWhile()" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1543 "parser\\epparser.c"
        break;
      case 68: /* while_stmt ::= while_header stmt */
#line 353 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndWhile()" << std::endl;
}
#line 1551 "parser\\epparser.c"
        break;
      case 69: /* foreach_header ::= FOR LPAREN nameList COLON exprList RPAREN */
#line 359 "parser\\epparser.lemon"
{
    ps->closure.pushScope();
    commaListIter(yymsp[-3].minor.yy0->data, [&](std::string& s) {
        ps->closure.defVariable(s);
    });
    ps->gen << "for " << yymsp[-3].minor.yy0->data << " in " << yymsp[-1].minor.yy0->data << ":" << std::endl;
    ps->gen.indent();
}
#line 1563 "parser\\epparser.c"
        break;
      case 70: /* foreach_stmt ::= foreach_header stmt */
      case 76: /* fdef_chunk ::= function_header stmt */ yytestcase(yyruleno==76);
#line 368 "parser\\epparser.lemon"
{
    ps->gen.unindent(true);
    ps->closure.popScope();
}
#line 1572 "parser\\epparser.c"
        break;
      case 71: /* continue_stmt ::= CONTINUE SEMICOLON */
#line 375 "parser\\epparser.lemon"
{
    ps->gen << "EUDContinue()" << std::endl;
}
#line 1579 "parser\\epparser.c"
        break;
      case 72: /* break_stmt ::= BREAK SEMICOLON */
#line 379 "parser\\epparser.lemon"
{
    ps->gen << "EUDBreak()" << std::endl;
}
#line 1586 "parser\\epparser.c"
        break;
      case 73: /* function_start ::= FUNCTION NAME */
#line 384 "parser\\epparser.lemon"
{
    // Preprocess yymsp[0].minor.yy0
    funcNamePreprocess(yymsp[0].minor.yy0->data);
    yygotominor.yy0 = yymsp[0].minor.yy0;
    if(!ps->closure.defFunction(yymsp[0].minor.yy0->data)) {
        throw_error(yymsp[0].minor.yy0->line, 4495, "Duplicate function yymsp[0].minor.yy0 " + yymsp[0].minor.yy0->data);
    }
    ps->closure.pushScope();
}
#line 1599 "parser\\epparser.c"
        break;
      case 74: /* function_header ::= function_start LPAREN nameList RPAREN */
#line 394 "parser\\epparser.lemon"
{
    ps->gen << "@EUDFunc" << std::endl;
    ps->gen << "def " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data << "):" << std::endl;
    ps->gen.indent();

    // Register variables.
    const std::string& s = yymsp[-1].minor.yy0->data;
    commaListIter(yymsp[-1].minor.yy0->data, [&](std::string& varname) {
        if(!ps->closure.defVariable(varname)) {
            throw_error(yymsp[-1].minor.yy0->line, 196, ("Redeclaration of variable \'" + varname + "\'"));
        }
    });

    tmpIndex = 1;
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1619 "parser\\epparser.c"
        break;
      case 75: /* function_header ::= function_start LPAREN RPAREN */
#line 411 "parser\\epparser.lemon"
{
    ps->gen << "@EUDFunc" << std::endl;
    ps->gen << "def " << yymsp[-2].minor.yy0->data << "():" << std::endl;
    ps->gen.indent();
    tmpIndex = 1;
    delete yymsp[-2].minor.yy0;
}
#line 1630 "parser\\epparser.c"
        break;
      case 77: /* return_stmt ::= RETURN SEMICOLON */
#line 426 "parser\\epparser.lemon"
{
    ps->gen << "EUDReturn()" << std::endl;
}
#line 1637 "parser\\epparser.c"
        break;
      case 78: /* return_stmt ::= RETURN exprList SEMICOLON */
#line 430 "parser\\epparser.lemon"
{
    ps->gen << "EUDReturn(" << yymsp[-1].minor.yy0->data << ")" << std::endl;
    delete yymsp[-1].minor.yy0;
}
#line 1645 "parser\\epparser.c"
        break;
      case 79: /* lexpr ::= CONDITIONNAME LPAREN fArgs RPAREN */
#line 438 "parser\\epparser.lemon"
{
    yymsp[-3].minor.yy0->data = yymsp[-3].minor.yy0->data + "(" + yymsp[-1].minor.yy0->data + ")";
    delete yymsp[-1].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0, ps->gen);
}
#line 1654 "parser\\epparser.c"
        break;
      case 80: /* lexpr ::= CONDITIONNAME LPAREN RPAREN */
#line 444 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + "()";
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0, ps->gen);
}
#line 1662 "parser\\epparser.c"
        break;
      case 81: /* action ::= ACTIONNAME LPAREN fArgs RPAREN SEMICOLON */
#line 449 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[-4].minor.yy0);
    yygotominor.yy0->data =  yymsp[-4].minor.yy0->data + "(" + yymsp[-2].minor.yy0->data + ")";
    delete yymsp[-4].minor.yy0; delete yymsp[-2].minor.yy0;
}
#line 1671 "parser\\epparser.c"
        break;
      case 82: /* actions ::= action action */
      case 83: /* actions ::= actions action */ yytestcase(yyruleno==83);
#line 455 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
    yymsp[-1].minor.yy0->data += ",\n" + yymsp[0].minor.yy0->data;
    delete yymsp[0].minor.yy0;
}
#line 1681 "parser\\epparser.c"
        break;
      case 84: /* actionStmt ::= action */
#line 467 "parser\\epparser.lemon"
{
    ps->gen << "DoActions(" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1689 "parser\\epparser.c"
        break;
      case 85: /* actionStmt ::= actions */
#line 472 "parser\\epparser.lemon"
{
    ps->gen << "DoActions([" << std::endl;
    ps->gen.indent();
    ps->gen << yymsp[0].minor.yy0->data << std::endl;
    ps->gen.unindent(false);
    ps->gen << "])" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1701 "parser\\epparser.c"
        break;
      case 86: /* stmt ::= error SEMICOLON */
#line 483 "parser\\epparser.lemon"
{ throw_error(yymsp[0].minor.yy0->line, 6974, "Error while parsing statement"); }
#line 1706 "parser\\epparser.c"
        break;
      case 93: /* bodyStmt ::= funcexpr SEMICOLON */
#line 492 "parser\\epparser.lemon"
{ ps->gen << yymsp[-1].minor.yy0->data << std::endl; }
#line 1711 "parser\\epparser.c"
        break;
      case 102: /* lbracket ::= LBRACKET */
#line 503 "parser\\epparser.lemon"
{ ps->closure.pushScope(); }
#line 1716 "parser\\epparser.c"
        break;
      case 103: /* rbracket ::= RBRACKET */
#line 504 "parser\\epparser.lemon"
{ ps->closure.popScope(); }
#line 1721 "parser\\epparser.c"
        break;
      case 106: /* stmt ::= lbracket RBRACKET */
#line 508 "parser\\epparser.lemon"
{
    ps->gen << "pass" << std::endl;
    ps->closure.popScope();
}
#line 1729 "parser\\epparser.c"
        break;
      case 110: /* stmt ::= lbracket error RBRACKET */
#line 515 "parser\\epparser.lemon"
{
    throw_error(yymsp[0].minor.yy0->line, 6298, "Block not terminated properly.");
    ps->closure.popScope();
}
#line 1737 "parser\\epparser.c"
        break;
      case 111: /* import_chunk ::= FROM NAME IMPORT nameList */
#line 522 "parser\\epparser.lemon"
{
    ps->gen << "from " << yymsp[-2].minor.yy0->data << " import " << yymsp[0].minor.yy0->data << std::endl;
    commaListIter(yymsp[0].minor.yy0->data, [&](std::string varname) {
        funcNamePreprocess(varname);
        if(!ps->closure.defFunction(varname)) {
            throw_error(yymsp[0].minor.yy0->line, 8118, ("Importing already-declared function " + varname));
        }
        else ps->gen << "from " << yymsp[-2].minor.yy0->data << " import " << varname << std::endl;
    });
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 1752 "parser\\epparser.c"
        break;
      default:
      /* (0) program ::= chunks */ yytestcase(yyruleno==0);
      /* (59) if_block ::= if_header stmt */ yytestcase(yyruleno==59);
      /* (62) if_block ::= if_block elif_header stmt */ yytestcase(yyruleno==62);
      /* (87) bodyStmt ::= SEMICOLON */ yytestcase(yyruleno==87);
      /* (88) bodyStmt ::= vdef_stmt */ yytestcase(yyruleno==88);
      /* (89) bodyStmt ::= vdefAssign_stmt */ yytestcase(yyruleno==89);
      /* (90) bodyStmt ::= cdef_stmt */ yytestcase(yyruleno==90);
      /* (91) bodyStmt ::= assign_stmt */ yytestcase(yyruleno==91);
      /* (92) bodyStmt ::= assignMulti_stmt */ yytestcase(yyruleno==92);
      /* (94) bodyStmt ::= actionStmt */ yytestcase(yyruleno==94);
      /* (95) bodyStmt ::= if_stmt */ yytestcase(yyruleno==95);
      /* (96) bodyStmt ::= while_stmt */ yytestcase(yyruleno==96);
      /* (97) bodyStmt ::= foreach_stmt */ yytestcase(yyruleno==97);
      /* (98) bodyStmt ::= continue_stmt */ yytestcase(yyruleno==98);
      /* (99) bodyStmt ::= break_stmt */ yytestcase(yyruleno==99);
      /* (100) bodyStmtList ::= bodyStmt */ yytestcase(yyruleno==100);
      /* (101) bodyStmtList ::= bodyStmtList bodyStmt */ yytestcase(yyruleno==101);
      /* (104) stmt ::= bodyStmt */ yytestcase(yyruleno==104);
      /* (105) stmt ::= return_stmt */ yytestcase(yyruleno==105);
      /* (107) stmt ::= lbracket return_stmt rbracket */ yytestcase(yyruleno==107);
      /* (108) stmt ::= lbracket bodyStmtList rbracket */ yytestcase(yyruleno==108);
      /* (109) stmt ::= lbracket bodyStmtList return_stmt rbracket */ yytestcase(yyruleno==109);
      /* (112) chunk ::= import_chunk */ yytestcase(yyruleno==112);
      /* (113) chunk ::= fdef_chunk */ yytestcase(yyruleno==113);
      /* (114) chunk ::= vdef_stmt */ yytestcase(yyruleno==114);
      /* (115) chunk ::= cdef_stmt */ yytestcase(yyruleno==115);
      /* (116) chunks ::= */ yytestcase(yyruleno==116);
      /* (117) chunks ::= chunks chunk */ yytestcase(yyruleno==117);
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
#line 22 "parser\\epparser.lemon"

    errorOccured = true;
#line 1845 "parser\\epparser.c"
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
#line 541 "parser\\epparser.lemon"


int PARSER_DEBUG = 0;

std::string ParseString(const std::string& code, bool addComment)
{
    Tokenizer tok(code);
    void* pParser = ParseAlloc (malloc);
    ParserStruct ps;
    Token* token;
    currentTokenizingLine = 0;

    if(PARSER_DEBUG) std::cout << "Parsing string [[[\n" << code.c_str() << "\n]]]\n";

    tmpIndex = 1;
    errorOccured = false;
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
            throw_error(token->line, 8104, "Invalid token");
        }
    }
    Parse (pParser, 0, nullptr, &ps);
    ParseFree(pParser, free );

    if(!errorOccured) return iwCollapse(ps.gen.str());
    else throw std::runtime_error("Invalid syntax");
}
#line 2077 "parser\\epparser.c"
