/* Driver template for the LEMON parser generator.
** The author disclaims copyright to this source code.
*/
/* First off, code is included that follows the "include" declaration
** in the input grammar file. */
#include <stdio.h>
#line 1 "parser/epparser.lemon"

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
#line 28 "parser/epparser.c"
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
#define YYNOCODE 104
#define YYACTIONTYPE unsigned short int
#define ParseTOKENTYPE Token*
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  int yy207;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL  ParserStruct* ps ;
#define ParseARG_PDECL , ParserStruct* ps 
#define ParseARG_FETCH  ParserStruct* ps  = yypParser->ps 
#define ParseARG_STORE yypParser->ps  = ps 
#define YYNSTATE 231
#define YYNRULE 115
#define YYERRORSYMBOL 57
#define YYERRSYMDT yy207
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
#define YY_ACTTAB_COUNT (750)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   141,   47,   46,   43,   44,   42,  144,  208,  206,   91,
 /*    10 */   285,  285,  219,  217,  216,    7,  139,  128,  207,  205,
 /*    20 */   140,  203,  202,  201,  200,  199,  198,   19,   20,   43,
 /*    30 */    44,   42,  145,  126,  225,  107,    5,   48,  134,  141,
 /*    40 */    26,  104,    3,    2,   52,   51,  208,  206,   91,  144,
 /*    50 */    25,  164,  217,  216,    7,   59,  190,  207,  205,  140,
 /*    60 */   203,  202,  201,  200,  199,  198,   19,   20,  105,    4,
 /*    70 */     1,  157,  126,  133,  107,    5,   48,  169,  141,  144,
 /*    80 */   104,    3,    2,   52,   51,  208,  206,   91,  144,   27,
 /*    90 */   161,  217,  216,    7,  224,  165,  207,  205,  140,  203,
 /*   100 */   202,  201,  200,  199,  198,   19,   20,  144,   24,  222,
 /*   110 */   221,  126,  223,  107,    5,   48,   49,  141,  220,  104,
 /*   120 */     3,    2,   52,   51,  208,  206,   91,   26,  137,  158,
 /*   130 */   217,  216,    7,  144,  162,  207,  205,  140,  203,  202,
 /*   140 */   201,  200,  199,  198,   19,   20,  218,  347,    9,  204,
 /*   150 */   126,  196,  107,    5,   48,  170,  141,   26,  104,    3,
 /*   160 */     2,   52,   51,  208,  206,   91,   26,  135,  156,  217,
 /*   170 */   216,    7,   56,  159,  207,  205,  140,  203,  202,  201,
 /*   180 */   200,  199,  198,   23,  144,  168,  195,  194,  193,  126,
 /*   190 */   131,  107,    5,   48,  167,  141,  130,  104,    3,    2,
 /*   200 */    52,   51,  208,  206,   91,  129,  286,  149,  217,  216,
 /*   210 */     7,  127,  169,  207,  205,  140,  203,  202,  201,  200,
 /*   220 */   199,  198,   12,   21,  123,  122,  189,  120,  126,  188,
 /*   230 */   107,    5,   48,  119,   95,  117,  104,    3,    2,   52,
 /*   240 */    51,  208,  206,   91,  116,  187,  114,  147,   58,  113,
 /*   250 */   186,    8,  207,  205,  140,  203,  202,  201,  200,  199,
 /*   260 */   198,   20,   10,   22,  175,  172,   16,  126,  163,  107,
 /*   270 */     5,   48,   15,   14,   53,  104,    3,    2,   52,   51,
 /*   280 */   208,  206,   91,  155,  154,   26,  197,   57,  153,  211,
 /*   290 */    96,  207,  205,  140,  203,  202,  201,  200,  199,  198,
 /*   300 */    11,  152,  148,   94,  223,  213,  126,  212,  107,    5,
 /*   310 */    48,  210,   90,  136,  104,    3,    2,   52,   51,   78,
 /*   320 */   151,   98,   33,   31,   30,   29,   28,   32,   38,   37,
 /*   330 */    39,   41,   40,   47,   46,   43,   44,   42,   18,   86,
 /*   340 */    84,   38,   37,   39,   41,   40,   47,   46,   43,   44,
 /*   350 */    42,   36,   35,  150,  106,   82,   93,   34,  192,   89,
 /*   360 */   191,  348,  348,  348,   45,   17,   41,   40,   47,   46,
 /*   370 */    43,   44,   42,  125,  124,  121,  118,  115,   36,   35,
 /*   380 */   348,  348,  348,  348,   34,  192,   89,  348,  111,  348,
 /*   390 */   348,   45,   39,   41,   40,   47,   46,   43,   44,   42,
 /*   400 */   125,  124,  121,  118,  115,   36,   35,  348,  138,  348,
 /*   410 */   348,   34,  192,   89,  348,  111,   88,   69,   45,  174,
 /*   420 */   348,  126,  348,  348,  348,  177,  348,  125,  124,  121,
 /*   430 */   118,  115,   36,   35,  348,  132,  348,  348,   34,  192,
 /*   440 */    89,  348,  348,  348,   68,   45,  110,  108,  126,  348,
 /*   450 */   348,  132,  177,  348,  125,  124,  121,  118,  115,   92,
 /*   460 */    60,  348,  209,  348,  126,   81,  348,  213,   38,   37,
 /*   470 */    39,   41,   40,   47,   46,   43,   44,   42,   55,   54,
 /*   480 */   166,  231,  160,  103,  348,  102,  101,   13,  348,   98,
 /*   490 */   138,  348,  348,  348,   92,  348,  348,  209,  100,   69,
 /*   500 */    99,  348,  214,  126,  348,  348,  348,  348,  146,   92,
 /*   510 */   348,  143,  209,   55,   54,  166,  215,  160,  103,  348,
 /*   520 */   102,  101,   13,  348,   98,  132,   50,   54,   55,   54,
 /*   530 */   166,  348,  160,  103,   79,  102,  101,   13,  126,   98,
 /*   540 */    36,   35,  132,  348,  348,  348,   34,  192,   89,  348,
 /*   550 */   348,   60,  348,   45,  348,  126,  180,  348,  348,  348,
 /*   560 */   348,  348,  125,  124,  121,  118,  115,  348,   37,   39,
 /*   570 */    41,   40,   47,   46,   43,   44,   42,  230,  229,  228,
 /*   580 */   227,  226,  348,  142,    6,  348,  348,  132,  348,  348,
 /*   590 */   348,  348,  132,  348,  348,  348,   68,  348,  110,   97,
 /*   600 */   126,   68,  138,  110,  109,  126,  348,  348,  138,  348,
 /*   610 */   171,   69,  348,  348,  138,  126,   87,   69,  348,  348,
 /*   620 */   348,  126,   85,   69,  138,  132,  132,  126,  348,  348,
 /*   630 */   348,  348,   83,   69,   68,   60,  176,  126,  126,  126,
 /*   640 */   112,  132,  348,  132,  348,  348,  348,  348,  348,  132,
 /*   650 */    60,  132,   60,  348,  126,  179,  126,  178,   60,  132,
 /*   660 */    60,  132,  126,   77,  126,   76,  348,  348,   60,  348,
 /*   670 */    80,  348,  126,   75,  126,  348,  132,  132,  132,  132,
 /*   680 */   348,  348,  348,  348,  348,   61,  173,  185,  184,  126,
 /*   690 */   126,  126,  126,  132,  132,  132,  348,  348,  348,  348,
 /*   700 */   132,  132,   74,   73,   72,  348,  126,  126,  126,   70,
 /*   710 */    71,  132,  132,  126,  126,  348,  348,  132,  132,  132,
 /*   720 */   183,  182,  348,  348,  126,  126,  181,   67,   66,  132,
 /*   730 */   126,  126,  126,  348,  132,  132,  132,  348,   65,  348,
 /*   740 */   348,  348,  126,   64,   63,   62,  348,  126,  126,  126,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    57,   18,   19,   20,   21,   22,    1,   64,   65,   66,
 /*    10 */    31,   31,   69,   70,   71,   72,   37,   37,   75,   76,
 /*    20 */    77,   78,   79,   80,   81,   82,   83,    3,    4,   20,
 /*    30 */    21,   22,   26,   90,   29,   92,   93,   94,    1,   57,
 /*    40 */     1,   98,   99,  100,  101,  102,   64,   65,   66,    1,
 /*    50 */     2,   69,   70,   71,   72,   28,   32,   75,   76,   77,
 /*    60 */    78,   79,   80,   81,   82,   83,    3,    4,   95,   96,
 /*    70 */    97,   32,   90,   36,   92,   93,   94,   29,   57,    1,
 /*    80 */    98,   99,  100,  101,  102,   64,   65,   66,    1,    2,
 /*    90 */    69,   70,   71,   72,   26,   32,   75,   76,   77,   78,
 /*   100 */    79,   80,   81,   82,   83,    3,    4,    1,    2,   26,
 /*   110 */    32,   90,   26,   92,   93,   94,   31,   57,   32,   98,
 /*   120 */    99,  100,  101,  102,   64,   65,   66,    1,   35,   69,
 /*   130 */    70,   71,   72,    1,   32,   75,   76,   77,   78,   79,
 /*   140 */    80,   81,   82,   83,    3,    4,   29,   59,   60,   29,
 /*   150 */    90,   26,   92,   93,   94,   29,   57,    1,   98,   99,
 /*   160 */   100,  101,  102,   64,   65,   66,    1,   36,   69,   70,
 /*   170 */    71,   72,   35,   32,   75,   76,   77,   78,   79,   80,
 /*   180 */    81,   82,   83,   51,    1,   29,   36,   25,   36,   90,
 /*   190 */    35,   92,   93,   94,   29,   57,   35,   98,   99,  100,
 /*   200 */   101,  102,   64,   65,   66,   25,   31,   69,   70,   71,
 /*   210 */    72,   26,   29,   75,   76,   77,   78,   79,   80,   81,
 /*   220 */    82,   83,   31,   31,   31,   38,   32,   31,   90,   32,
 /*   230 */    92,   93,   94,   38,   57,   31,   98,   99,  100,  101,
 /*   240 */   102,   64,   65,   66,   38,   32,   31,   70,   71,   38,
 /*   250 */    32,   74,   75,   76,   77,   78,   79,   80,   81,   82,
 /*   260 */    83,    4,   31,    1,   32,   32,   31,   90,   47,   92,
 /*   270 */    93,   94,   31,   31,   31,   98,   99,  100,  101,  102,
 /*   280 */    64,   65,   66,   29,   29,    1,   70,   71,   29,   73,
 /*   290 */    32,   75,   76,   77,   78,   79,   80,   81,   82,   83,
 /*   300 */    31,   29,   34,   66,   26,   34,   90,   73,   92,   93,
 /*   310 */    94,   73,   84,   25,   98,   99,  100,  101,  102,   66,
 /*   320 */   101,   56,    7,    8,    9,   10,   11,   12,   13,   14,
 /*   330 */    15,   16,   17,   18,   19,   20,   21,   22,    5,   66,
 /*   340 */    66,   13,   14,   15,   16,   17,   18,   19,   20,   21,
 /*   350 */    22,   18,   19,  101,   48,   66,   66,   24,   25,   26,
 /*   360 */    32,  103,  103,  103,   31,    5,   16,   17,   18,   19,
 /*   370 */    20,   21,   22,   40,   41,   42,   43,   44,   18,   19,
 /*   380 */   103,  103,  103,  103,   24,   25,   26,  103,   55,  103,
 /*   390 */   103,   31,   15,   16,   17,   18,   19,   20,   21,   22,
 /*   400 */    40,   41,   42,   43,   44,   18,   19,  103,   77,  103,
 /*   410 */   103,   24,   25,   26,  103,   55,   85,   86,   31,   32,
 /*   420 */   103,   90,  103,  103,  103,   38,  103,   40,   41,   42,
 /*   430 */    43,   44,   18,   19,  103,   77,  103,  103,   24,   25,
 /*   440 */    26,  103,  103,  103,   86,   31,   88,   89,   90,  103,
 /*   450 */   103,   77,   38,  103,   40,   41,   42,   43,   44,   26,
 /*   460 */    86,  103,   29,  103,   90,   91,  103,   34,   13,   14,
 /*   470 */    15,   16,   17,   18,   19,   20,   21,   22,   45,   46,
 /*   480 */    47,    0,   49,   50,  103,   52,   53,   54,  103,   56,
 /*   490 */    77,  103,  103,  103,   26,  103,  103,   29,   85,   86,
 /*   500 */    87,  103,   34,   90,  103,  103,  103,  103,   27,   26,
 /*   510 */   103,   30,   29,   45,   46,   47,   33,   49,   50,  103,
 /*   520 */    52,   53,   54,  103,   56,   77,   45,   46,   45,   46,
 /*   530 */    47,  103,   49,   50,   86,   52,   53,   54,   90,   56,
 /*   540 */    18,   19,   77,  103,  103,  103,   24,   25,   26,  103,
 /*   550 */   103,   86,  103,   31,  103,   90,   91,  103,  103,  103,
 /*   560 */   103,  103,   40,   41,   42,   43,   44,  103,   14,   15,
 /*   570 */    16,   17,   18,   19,   20,   21,   22,   61,   62,   63,
 /*   580 */    64,   65,  103,   67,   68,  103,  103,   77,  103,  103,
 /*   590 */   103,  103,   77,  103,  103,  103,   86,  103,   88,   89,
 /*   600 */    90,   86,   77,   88,   89,   90,  103,  103,   77,  103,
 /*   610 */    85,   86,  103,  103,   77,   90,   85,   86,  103,  103,
 /*   620 */   103,   90,   85,   86,   77,   77,   77,   90,  103,  103,
 /*   630 */   103,  103,   85,   86,   86,   86,   88,   90,   90,   90,
 /*   640 */    91,   77,  103,   77,  103,  103,  103,  103,  103,   77,
 /*   650 */    86,   77,   86,  103,   90,   91,   90,   91,   86,   77,
 /*   660 */    86,   77,   90,   91,   90,   91,  103,  103,   86,  103,
 /*   670 */    86,  103,   90,   91,   90,  103,   77,   77,   77,   77,
 /*   680 */   103,  103,  103,  103,  103,   86,   86,   86,   86,   90,
 /*   690 */    90,   90,   90,   77,   77,   77,  103,  103,  103,  103,
 /*   700 */    77,   77,   86,   86,   86,  103,   90,   90,   90,   86,
 /*   710 */    86,   77,   77,   90,   90,  103,  103,   77,   77,   77,
 /*   720 */    86,   86,  103,  103,   90,   90,   86,   86,   86,   77,
 /*   730 */    90,   90,   90,  103,   77,   77,   77,  103,   86,  103,
 /*   740 */   103,  103,   90,   86,   86,   86,  103,   90,   90,   90,
};
#define YY_SHIFT_USE_DFLT (-22)
#define YY_SHIFT_COUNT (146)
#define YY_SHIFT_MIN   (-21)
#define YY_SHIFT_MAX   (554)
static const short yy_shift_ofst[] = {
 /*     0 */   -22,  483,  483,  483,  483,  483,  483,  468,  433,  481,
 /*    10 */   387,  414,  414,  522,  333,  333,  333,  360,  360,  333,
 /*    20 */   333,  333,  414,  522,  522,  522,  522,  522,  522,  522,
 /*    30 */   522,  522,  522,  522,  522,  522,  522,  522,  522,  522,
 /*    40 */   522,  522,  522,  522,  522,  522,  522,  522,  306,   86,
 /*    50 */   278,  265,  265,  278,  278,  278,  288,  271,  271,  278,
 /*    60 */   315,  328,  455,  455,  455,  455,  455,  455,  455,  455,
 /*    70 */   554,  377,  350,  -17,  -17,  141,  102,   63,   48,    9,
 /*    80 */     9,   24,  183,   39,  132,  165,  106,  156,  126,  -20,
 /*    90 */    37,   87,  -21,   78,    5,  268,  272,  258,  269,  259,
 /*   100 */   284,  255,  254,  243,  242,  241,  221,  235,  233,  232,
 /*   110 */   262,  231,  257,  218,  211,  215,  213,  206,  204,  197,
 /*   120 */   195,  196,  194,  187,  193,  192,  191,  175,  185,  131,
 /*   130 */   180,  161,  155,  152,  162,  150,  131,  137,   93,  125,
 /*   140 */   120,  117,   85,   83,   68,   27,    6,
};
#define YY_REDUCE_USE_DFLT (-58)
#define YY_REDUCE_COUNT (59)
#define YY_REDUCE_MIN   (-57)
#define YY_REDUCE_MAX   (659)
static const short yy_reduce_ofst[] = {
 /*     0 */    88,  138,   99,   60,   21,  -18,  -57,  177,  216,  516,
 /*    10 */   515,  510,  358,  413,  582,  574,  572,  566,  564,  549,
 /*    20 */   465,  374,  548,  547,  537,  531,  525,  331,  659,  658,
 /*    30 */   657,  652,  642,  641,  640,  635,  634,  624,  623,  618,
 /*    40 */   617,  616,  602,  601,  600,  599,  584,  448,  -27,  290,
 /*    50 */   289,  252,  219,  274,  273,  253,  228,  238,  234,  237,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   232,  346,  346,  346,  346,  346,  346,  346,  346,  346,
 /*    10 */   346,  283,  283,  275,  346,  346,  346,  346,  346,  346,
 /*    20 */   346,  346,  346,  346,  346,  346,  346,  346,  346,  346,
 /*    30 */   346,  346,  346,  346,  346,  346,  346,  346,  346,  346,
 /*    40 */   346,  346,  346,  346,  346,  346,  346,  346,  329,  346,
 /*    50 */   346,  345,  344,  346,  346,  346,  346,  346,  346,  346,
 /*    60 */   346,  346,  313,  312,  311,  310,  309,  308,  280,  273,
 /*    70 */   303,  304,  302,  301,  300,  346,  346,  346,  346,  295,
 /*    80 */   296,  346,  346,  346,  346,  346,  346,  346,  346,  278,
 /*    90 */   346,  346,  269,  346,  346,  346,  346,  346,  346,  346,
 /*   100 */   276,  346,  346,  346,  346,  346,  328,  346,  346,  346,
 /*   110 */   284,  346,  315,  346,  346,  346,  346,  346,  346,  346,
 /*   120 */   346,  346,  346,  346,  346,  346,  346,  279,  346,  346,
 /*   130 */   346,  346,  288,  346,  346,  346,  267,  346,  288,  346,
 /*   140 */   346,  346,  346,  346,  346,  346,  346,  265,  252,  330,
 /*   150 */   343,  342,  341,  338,  337,  336,  335,  334,  333,  332,
 /*   160 */   331,  327,  326,  325,  324,  323,  322,  320,  319,  318,
 /*   170 */   321,  274,  287,  297,  340,  339,  282,  281,  317,  316,
 /*   180 */   314,  307,  306,  305,  299,  298,  294,  293,  292,  291,
 /*   190 */   290,  289,  277,  271,  268,  272,  286,  266,  264,  263,
 /*   200 */   262,  261,  260,  259,  258,  257,  256,  255,  254,  253,
 /*   210 */   251,  250,  249,  247,  248,  246,  245,  244,  243,  242,
 /*   220 */   241,  240,  239,  269,  270,  238,  237,  236,  235,  234,
 /*   230 */   233,
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
  "BITNOT",        "NUMBER",        "NAME",          "FROM",        
  "IMPORT",        "SEMICOLON",     "FUNCTION",      "LPAREN",      
  "RPAREN",        "LBRACKET",      "RBRACKET",      "LSQBRACKET",  
  "RSQBRACKET",    "PERIOD",        "STRING",        "FUNCCALL",    
  "L2V",           "MAPSTRING",     "UNIT",          "SWITCH",      
  "LOCATION",      "VAR",           "CONST",         "IF",          
  "ELSE",          "WHILE",         "FOR",           "COLON",       
  "CONTINUE",      "BREAK",         "RETURN",        "CONDITIONNAME",
  "ACTIONNAME",    "error",         "nt",            "program",     
  "chunks",        "chunk",         "import_chunk",  "fdef_chunk",  
  "vdef_stmt",     "cdef_stmt",     "nameList_nonEmpty",  "function_start",
  "function_header",  "stmt",          "bodyStmt",      "return_stmt", 
  "lbracket",      "rbracket",      "bodyStmtList",  "vdefAssign_stmt",
  "assign_stmt",   "funcexpr",      "actionStmt",    "if_stmt",     
  "while_stmt",    "foreach_stmt",  "continue_stmt",  "break_stmt",  
  "numList_nonEmpty",  "exprList_nonEmpty",  "expr",          "exprList",    
  "fArgs_nonEmpty",  "fArgs",         "funcName",      "lexpr",       
  "if_start",      "if_header",     "if_block",      "elif_start",  
  "elif_header",   "else_header",   "while_start",   "while_header",
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
 /*   3 */ "chunk ::= import_chunk",
 /*   4 */ "chunk ::= fdef_chunk",
 /*   5 */ "chunk ::= vdef_stmt",
 /*   6 */ "chunk ::= cdef_stmt",
 /*   7 */ "import_chunk ::= FROM NAME IMPORT nameList_nonEmpty SEMICOLON",
 /*   8 */ "function_start ::= FUNCTION NAME",
 /*   9 */ "function_header ::= function_start LPAREN nameList_nonEmpty RPAREN",
 /*  10 */ "function_header ::= function_start LPAREN RPAREN",
 /*  11 */ "fdef_chunk ::= function_header stmt",
 /*  12 */ "stmt ::= error SEMICOLON",
 /*  13 */ "stmt ::= bodyStmt",
 /*  14 */ "stmt ::= return_stmt",
 /*  15 */ "lbracket ::= LBRACKET",
 /*  16 */ "rbracket ::= RBRACKET",
 /*  17 */ "stmt ::= lbracket RBRACKET",
 /*  18 */ "stmt ::= lbracket return_stmt rbracket",
 /*  19 */ "stmt ::= lbracket bodyStmtList rbracket",
 /*  20 */ "stmt ::= lbracket bodyStmtList return_stmt rbracket",
 /*  21 */ "stmt ::= lbracket error RBRACKET",
 /*  22 */ "bodyStmt ::= SEMICOLON",
 /*  23 */ "bodyStmt ::= vdef_stmt",
 /*  24 */ "bodyStmt ::= vdefAssign_stmt",
 /*  25 */ "bodyStmt ::= cdef_stmt",
 /*  26 */ "bodyStmt ::= assign_stmt",
 /*  27 */ "bodyStmt ::= funcexpr SEMICOLON",
 /*  28 */ "bodyStmt ::= actionStmt",
 /*  29 */ "bodyStmt ::= if_stmt",
 /*  30 */ "bodyStmt ::= while_stmt",
 /*  31 */ "bodyStmt ::= foreach_stmt",
 /*  32 */ "bodyStmt ::= continue_stmt",
 /*  33 */ "bodyStmt ::= break_stmt",
 /*  34 */ "bodyStmtList ::= bodyStmt",
 /*  35 */ "bodyStmtList ::= bodyStmtList bodyStmt",
 /*  36 */ "numList_nonEmpty ::= NUMBER",
 /*  37 */ "numList_nonEmpty ::= numList_nonEmpty COMMA NUMBER",
 /*  38 */ "nameList_nonEmpty ::= NAME",
 /*  39 */ "nameList_nonEmpty ::= nameList_nonEmpty COMMA NAME",
 /*  40 */ "exprList_nonEmpty ::= funcexpr LSQBRACKET LSQBRACKET numList_nonEmpty RSQBRACKET RSQBRACKET",
 /*  41 */ "expr ::= funcexpr LSQBRACKET LSQBRACKET NUMBER RSQBRACKET RSQBRACKET",
 /*  42 */ "exprList_nonEmpty ::= expr",
 /*  43 */ "exprList_nonEmpty ::= exprList_nonEmpty COMMA exprList_nonEmpty",
 /*  44 */ "exprList ::=",
 /*  45 */ "exprList ::= exprList_nonEmpty",
 /*  46 */ "expr ::= NUMBER",
 /*  47 */ "expr ::= NAME",
 /*  48 */ "expr ::= NAME PERIOD NAME",
 /*  49 */ "fArgs_nonEmpty ::= expr",
 /*  50 */ "fArgs_nonEmpty ::= STRING",
 /*  51 */ "fArgs_nonEmpty ::= fArgs_nonEmpty COMMA fArgs_nonEmpty",
 /*  52 */ "fArgs ::=",
 /*  53 */ "fArgs ::= fArgs_nonEmpty",
 /*  54 */ "funcName ::= NAME",
 /*  55 */ "funcName ::= NAME PERIOD NAME",
 /*  56 */ "funcexpr ::= funcName LPAREN fArgs RPAREN",
 /*  57 */ "expr ::= funcexpr",
 /*  58 */ "expr ::= LPAREN expr RPAREN",
 /*  59 */ "expr ::= L2V LPAREN lexpr RPAREN",
 /*  60 */ "expr ::= MAPSTRING LPAREN STRING RPAREN",
 /*  61 */ "expr ::= UNIT LPAREN STRING RPAREN",
 /*  62 */ "expr ::= SWITCH LPAREN STRING RPAREN",
 /*  63 */ "expr ::= LOCATION LPAREN STRING RPAREN",
 /*  64 */ "expr ::= expr PLUS expr",
 /*  65 */ "expr ::= expr MINUS expr",
 /*  66 */ "expr ::= expr MULTIPLY expr",
 /*  67 */ "expr ::= expr DIVIDE expr",
 /*  68 */ "expr ::= expr MOD expr",
 /*  69 */ "expr ::= expr LSHIFT expr",
 /*  70 */ "expr ::= expr RSHIFT expr",
 /*  71 */ "expr ::= expr BITAND expr",
 /*  72 */ "expr ::= expr BITOR expr",
 /*  73 */ "expr ::= expr BITXOR expr",
 /*  74 */ "expr ::= PLUS expr",
 /*  75 */ "expr ::= MINUS expr",
 /*  76 */ "expr ::= BITNOT expr",
 /*  77 */ "lexpr ::= expr EQ expr",
 /*  78 */ "lexpr ::= expr NE expr",
 /*  79 */ "lexpr ::= expr LE expr",
 /*  80 */ "lexpr ::= expr LT expr",
 /*  81 */ "lexpr ::= expr GE expr",
 /*  82 */ "lexpr ::= expr GT expr",
 /*  83 */ "lexpr ::= lexpr LAND lexpr",
 /*  84 */ "lexpr ::= lexpr LOR lexpr",
 /*  85 */ "lexpr ::= LNOT lexpr",
 /*  86 */ "lexpr ::= LNOT LNOT lexpr",
 /*  87 */ "vdef_stmt ::= VAR nameList_nonEmpty SEMICOLON",
 /*  88 */ "vdefAssign_stmt ::= VAR nameList_nonEmpty ASSIGN exprList_nonEmpty SEMICOLON",
 /*  89 */ "cdef_stmt ::= CONST nameList_nonEmpty ASSIGN exprList_nonEmpty SEMICOLON",
 /*  90 */ "assign_stmt ::= nameList_nonEmpty ASSIGN exprList_nonEmpty SEMICOLON",
 /*  91 */ "if_start ::= IF",
 /*  92 */ "if_header ::= if_start LPAREN lexpr RPAREN",
 /*  93 */ "if_block ::= if_header stmt",
 /*  94 */ "elif_start ::= ELSE IF",
 /*  95 */ "elif_header ::= elif_start LPAREN lexpr RPAREN",
 /*  96 */ "if_block ::= if_block elif_header stmt",
 /*  97 */ "else_header ::= ELSE",
 /*  98 */ "if_stmt ::= if_block",
 /*  99 */ "if_stmt ::= if_block else_header stmt",
 /* 100 */ "while_start ::= WHILE",
 /* 101 */ "while_header ::= while_start LPAREN lexpr RPAREN",
 /* 102 */ "while_stmt ::= while_header stmt",
 /* 103 */ "foreach_header ::= FOR LPAREN nameList_nonEmpty COLON exprList_nonEmpty RPAREN",
 /* 104 */ "foreach_stmt ::= foreach_header stmt",
 /* 105 */ "continue_stmt ::= CONTINUE SEMICOLON",
 /* 106 */ "break_stmt ::= BREAK SEMICOLON",
 /* 107 */ "return_stmt ::= RETURN exprList SEMICOLON",
 /* 108 */ "lexpr ::= CONDITIONNAME LPAREN fArgs RPAREN",
 /* 109 */ "lexpr ::= CONDITIONNAME LPAREN RPAREN",
 /* 110 */ "action ::= ACTIONNAME LPAREN fArgs RPAREN SEMICOLON",
 /* 111 */ "actions ::= action action",
 /* 112 */ "actions ::= actions action",
 /* 113 */ "actionStmt ::= action",
 /* 114 */ "actionStmt ::= actions",
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
#line 30 "parser/epparser.lemon"
 delete (yypminor->yy0); 
#line 701 "parser/epparser.c"
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
  { 60, 0 },
  { 60, 2 },
  { 61, 1 },
  { 61, 1 },
  { 61, 1 },
  { 61, 1 },
  { 62, 5 },
  { 67, 2 },
  { 68, 4 },
  { 68, 3 },
  { 63, 2 },
  { 69, 2 },
  { 69, 1 },
  { 69, 1 },
  { 72, 1 },
  { 73, 1 },
  { 69, 2 },
  { 69, 3 },
  { 69, 3 },
  { 69, 4 },
  { 69, 3 },
  { 70, 1 },
  { 70, 1 },
  { 70, 1 },
  { 70, 1 },
  { 70, 1 },
  { 70, 2 },
  { 70, 1 },
  { 70, 1 },
  { 70, 1 },
  { 70, 1 },
  { 70, 1 },
  { 70, 1 },
  { 74, 1 },
  { 74, 2 },
  { 84, 1 },
  { 84, 3 },
  { 66, 1 },
  { 66, 3 },
  { 85, 6 },
  { 86, 6 },
  { 85, 1 },
  { 85, 3 },
  { 87, 0 },
  { 87, 1 },
  { 86, 1 },
  { 86, 1 },
  { 86, 3 },
  { 88, 1 },
  { 88, 1 },
  { 88, 3 },
  { 89, 0 },
  { 89, 1 },
  { 90, 1 },
  { 90, 3 },
  { 77, 4 },
  { 86, 1 },
  { 86, 3 },
  { 86, 4 },
  { 86, 4 },
  { 86, 4 },
  { 86, 4 },
  { 86, 4 },
  { 86, 3 },
  { 86, 3 },
  { 86, 3 },
  { 86, 3 },
  { 86, 3 },
  { 86, 3 },
  { 86, 3 },
  { 86, 3 },
  { 86, 3 },
  { 86, 3 },
  { 86, 2 },
  { 86, 2 },
  { 86, 2 },
  { 91, 3 },
  { 91, 3 },
  { 91, 3 },
  { 91, 3 },
  { 91, 3 },
  { 91, 3 },
  { 91, 3 },
  { 91, 3 },
  { 91, 2 },
  { 91, 3 },
  { 64, 3 },
  { 75, 5 },
  { 65, 5 },
  { 76, 4 },
  { 92, 1 },
  { 93, 4 },
  { 94, 2 },
  { 95, 2 },
  { 96, 4 },
  { 94, 3 },
  { 97, 1 },
  { 79, 1 },
  { 79, 3 },
  { 98, 1 },
  { 99, 4 },
  { 80, 2 },
  { 100, 6 },
  { 81, 2 },
  { 82, 2 },
  { 83, 2 },
  { 71, 3 },
  { 91, 4 },
  { 91, 3 },
  { 101, 5 },
  { 102, 2 },
  { 102, 2 },
  { 78, 1 },
  { 78, 1 },
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
      case 7: /* import_chunk ::= FROM NAME IMPORT nameList_nonEmpty SEMICOLON */
#line 65 "parser/epparser.lemon"
{
    commaListIter(yymsp[-1].minor.yy0->data, [&](std::string varname) {
        funcNamePreprocess(varname);
        if(!ps->closure.defFunction(varname)) {
            throw_error(yymsp[-1].minor.yy0->line, 8118, ("Importing already-declared function " + varname));
        }
        else ps->gen << "from " << yymsp[-3].minor.yy0->data << " import " << varname << std::endl;
    });
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1120 "parser/epparser.c"
        break;
      case 8: /* function_start ::= FUNCTION NAME */
#line 77 "parser/epparser.lemon"
{
    // Preprocess yymsp[0].minor.yy0
    funcNamePreprocess(yymsp[0].minor.yy0->data);
    if(!ps->closure.defFunction(yymsp[0].minor.yy0->data)) {
        throw_error(yymsp[0].minor.yy0->line, 4495, "Duplicate function yymsp[0].minor.yy0 " + yymsp[0].minor.yy0->data);
    }
    ps->closure.pushScope();
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1133 "parser/epparser.c"
        break;
      case 9: /* function_header ::= function_start LPAREN nameList_nonEmpty RPAREN */
#line 87 "parser/epparser.lemon"
{
    ps->gen << "@EUDFunc" << std::endl;
    ps->gen << "def " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data << "):" << std::endl;
    ps->gen.indent();

    // Register variables.
    commaListIter(yymsp[-1].minor.yy0->data, [&](std::string& varname) {
        if(!ps->closure.defVariable(varname)) {
            throw_error(yymsp[-1].minor.yy0->line, 196, ("Redeclaration of variable \'" + varname + "\'"));
        }
    });

    tmpIndex = 1;
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1152 "parser/epparser.c"
        break;
      case 10: /* function_header ::= function_start LPAREN RPAREN */
#line 103 "parser/epparser.lemon"
{
    ps->gen << "@EUDFunc" << std::endl;
    ps->gen << "def " << yymsp[-2].minor.yy0->data << "():" << std::endl;
    ps->gen.indent();
    tmpIndex = 1;
    delete yymsp[-2].minor.yy0;
}
#line 1163 "parser/epparser.c"
        break;
      case 11: /* fdef_chunk ::= function_header stmt */
      case 104: /* foreach_stmt ::= foreach_header stmt */ yytestcase(yyruleno==104);
#line 111 "parser/epparser.lemon"
{
    ps->gen.unindent(true);
    ps->closure.popScope();
}
#line 1172 "parser/epparser.c"
        break;
      case 12: /* stmt ::= error SEMICOLON */
#line 118 "parser/epparser.lemon"
{ throw_error(yymsp[0].minor.yy0->line, 6974, "Error while parsing statement"); }
#line 1177 "parser/epparser.c"
        break;
      case 15: /* lbracket ::= LBRACKET */
#line 123 "parser/epparser.lemon"
{ ps->closure.pushScope(); }
#line 1182 "parser/epparser.c"
        break;
      case 16: /* rbracket ::= RBRACKET */
#line 124 "parser/epparser.lemon"
{ ps->closure.popScope(); }
#line 1187 "parser/epparser.c"
        break;
      case 17: /* stmt ::= lbracket RBRACKET */
#line 126 "parser/epparser.lemon"
{
    ps->gen << "pass" << std::endl;
    ps->closure.popScope();
}
#line 1195 "parser/epparser.c"
        break;
      case 21: /* stmt ::= lbracket error RBRACKET */
#line 133 "parser/epparser.lemon"
{
    throw_error(yymsp[0].minor.yy0->line, 6298, "Block not terminated properly.");
    ps->closure.popScope();
}
#line 1203 "parser/epparser.c"
        break;
      case 27: /* bodyStmt ::= funcexpr SEMICOLON */
#line 143 "parser/epparser.lemon"
{ ps->gen << yymsp[-1].minor.yy0->data << std::endl; }
#line 1208 "parser/epparser.c"
        break;
      case 36: /* numList_nonEmpty ::= NUMBER */
#line 157 "parser/epparser.lemon"
{
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1215 "parser/epparser.c"
        break;
      case 37: /* numList_nonEmpty ::= numList_nonEmpty COMMA NUMBER */
#line 161 "parser/epparser.lemon"
{
    yygotominor.yy0 = new Token(yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data, yymsp[0].minor.yy0);
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 1223 "parser/epparser.c"
        break;
      case 38: /* nameList_nonEmpty ::= NAME */
      case 42: /* exprList_nonEmpty ::= expr */ yytestcase(yyruleno==42);
      case 45: /* exprList ::= exprList_nonEmpty */ yytestcase(yyruleno==45);
      case 46: /* expr ::= NUMBER */ yytestcase(yyruleno==46);
      case 49: /* fArgs_nonEmpty ::= expr */ yytestcase(yyruleno==49);
      case 50: /* fArgs_nonEmpty ::= STRING */ yytestcase(yyruleno==50);
      case 53: /* fArgs ::= fArgs_nonEmpty */ yytestcase(yyruleno==53);
      case 57: /* expr ::= funcexpr */ yytestcase(yyruleno==57);
      case 86: /* lexpr ::= LNOT LNOT lexpr */ yytestcase(yyruleno==86);
#line 166 "parser/epparser.lemon"
{ yygotominor.yy0 = yymsp[0].minor.yy0; }
#line 1236 "parser/epparser.c"
        break;
      case 39: /* nameList_nonEmpty ::= nameList_nonEmpty COMMA NAME */
#line 167 "parser/epparser.lemon"
{
    yymsp[0].minor.yy0->data = yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data;
    delete yymsp[-2].minor.yy0;
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1245 "parser/epparser.c"
        break;
      case 40: /* exprList_nonEmpty ::= funcexpr LSQBRACKET LSQBRACKET numList_nonEmpty RSQBRACKET RSQBRACKET */
#line 173 "parser/epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "_SRET(" + yymsp[-5].minor.yy0->data + ", [" + yymsp[-2].minor.yy0->data + "])";
    delete yymsp[-5].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1254 "parser/epparser.c"
        break;
      case 41: /* expr ::= funcexpr LSQBRACKET LSQBRACKET NUMBER RSQBRACKET RSQBRACKET */
#line 180 "parser/epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-5].minor.yy0->data + "[" + yymsp[-2].minor.yy0->data + "]";
    delete yymsp[-5].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1263 "parser/epparser.c"
        break;
      case 43: /* exprList_nonEmpty ::= exprList_nonEmpty COMMA exprList_nonEmpty */
#line 188 "parser/epparser.lemon"
{ yygotominor.yy0 = new Token((yymsp[-2].minor.yy0->data) + ", " + (yymsp[0].minor.yy0->data), yymsp[0].minor.yy0); delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1268 "parser/epparser.c"
        break;
      case 44: /* exprList ::= */
      case 52: /* fArgs ::= */ yytestcase(yyruleno==52);
#line 190 "parser/epparser.lemon"
{ yygotominor.yy0 = genEmpty(); }
#line 1274 "parser/epparser.c"
        break;
      case 47: /* expr ::= NAME */
#line 195 "parser/epparser.lemon"
{
    if(!ps->closure.getConstant(yymsp[0].minor.yy0->data) && !ps->closure.getVariable(yymsp[0].minor.yy0->data)) {
        throw_error(yymsp[0].minor.yy0->line, 103, ("Undeclared \'" + (yymsp[0].minor.yy0->data) + "\'"));
        ps->closure.defVariable(yymsp[0].minor.yy0->data);
    }
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1285 "parser/epparser.c"
        break;
      case 48: /* expr ::= NAME PERIOD NAME */
#line 203 "parser/epparser.lemon"
{
    if(!ps->closure.getConstant(yymsp[-2].minor.yy0->data)) {
        throw_error(yymsp[-2].minor.yy0->line, 103, ("Undeclared constant \'" + (yymsp[-2].minor.yy0->data) + "\'"));
        ps->closure.defConstant(yymsp[-2].minor.yy0->data);
    }
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + "." + yymsp[0].minor.yy0->data;
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1298 "parser/epparser.c"
        break;
      case 51: /* fArgs_nonEmpty ::= fArgs_nonEmpty COMMA fArgs_nonEmpty */
#line 216 "parser/epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data;
    yymsp[-2].minor.yy0->type = TOKEN_TEMP;
    yygotominor.yy0 = yymsp[-2].minor.yy0;
    delete yymsp[0].minor.yy0;
}
#line 1308 "parser/epparser.c"
        break;
      case 54: /* funcName ::= NAME */
#line 226 "parser/epparser.lemon"
{
    funcNamePreprocess(yymsp[0].minor.yy0->data);
    if (!ps->closure.getFunction(yymsp[0].minor.yy0->data)) {
        throw_error(yymsp[0].minor.yy0->line, 4449, ("Undefined function " + yymsp[0].minor.yy0->data));
        ps->closure.defFunction(yymsp[0].minor.yy0->data);
    }
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1320 "parser/epparser.c"
        break;
      case 55: /* funcName ::= NAME PERIOD NAME */
#line 234 "parser/epparser.lemon"
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
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0);
}
#line 1342 "parser/epparser.c"
        break;
      case 56: /* funcexpr ::= funcName LPAREN fArgs RPAREN */
#line 253 "parser/epparser.lemon"
{
    // Preprocess yymsp[-3].minor.yy0
    yymsp[-3].minor.yy0->data += "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 1351 "parser/epparser.c"
        break;
      case 58: /* expr ::= LPAREN expr RPAREN */
#line 262 "parser/epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1359 "parser/epparser.c"
        break;
      case 59: /* expr ::= L2V LPAREN lexpr RPAREN */
#line 267 "parser/epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "_L2V(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = genTemp(yymsp[-1].minor.yy0);
}
#line 1367 "parser/epparser.c"
        break;
      case 60: /* expr ::= MAPSTRING LPAREN STRING RPAREN */
#line 272 "parser/epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetStringIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1375 "parser/epparser.c"
        break;
      case 61: /* expr ::= UNIT LPAREN STRING RPAREN */
#line 277 "parser/epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetUnitIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1383 "parser/epparser.c"
        break;
      case 62: /* expr ::= SWITCH LPAREN STRING RPAREN */
#line 282 "parser/epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetSwitchIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1391 "parser/epparser.c"
        break;
      case 63: /* expr ::= LOCATION LPAREN STRING RPAREN */
#line 287 "parser/epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetLocationIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1399 "parser/epparser.c"
        break;
      case 64: /* expr ::= expr PLUS expr */
#line 293 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "+",  yymsp[0].minor.yy0); }
#line 1404 "parser/epparser.c"
        break;
      case 65: /* expr ::= expr MINUS expr */
#line 294 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "-",  yymsp[0].minor.yy0); }
#line 1409 "parser/epparser.c"
        break;
      case 66: /* expr ::= expr MULTIPLY expr */
#line 295 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "*",  yymsp[0].minor.yy0); }
#line 1414 "parser/epparser.c"
        break;
      case 67: /* expr ::= expr DIVIDE expr */
#line 296 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "//", yymsp[0].minor.yy0); }
#line 1419 "parser/epparser.c"
        break;
      case 68: /* expr ::= expr MOD expr */
#line 297 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "%",  yymsp[0].minor.yy0); }
#line 1424 "parser/epparser.c"
        break;
      case 69: /* expr ::= expr LSHIFT expr */
#line 298 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<<", yymsp[0].minor.yy0); }
#line 1429 "parser/epparser.c"
        break;
      case 70: /* expr ::= expr RSHIFT expr */
#line 299 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">>", yymsp[0].minor.yy0); }
#line 1434 "parser/epparser.c"
        break;
      case 71: /* expr ::= expr BITAND expr */
#line 300 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "&",  yymsp[0].minor.yy0); }
#line 1439 "parser/epparser.c"
        break;
      case 72: /* expr ::= expr BITOR expr */
#line 301 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "|",  yymsp[0].minor.yy0); }
#line 1444 "parser/epparser.c"
        break;
      case 73: /* expr ::= expr BITXOR expr */
#line 302 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "^",  yymsp[0].minor.yy0); }
#line 1449 "parser/epparser.c"
        break;
      case 74: /* expr ::= PLUS expr */
#line 305 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = +" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1454 "parser/epparser.c"
        break;
      case 75: /* expr ::= MINUS expr */
#line 306 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = -" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1459 "parser/epparser.c"
        break;
      case 76: /* expr ::= BITNOT expr */
#line 307 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = ~" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1464 "parser/epparser.c"
        break;
      case 77: /* lexpr ::= expr EQ expr */
#line 311 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "==", yymsp[0].minor.yy0); }
#line 1469 "parser/epparser.c"
        break;
      case 78: /* lexpr ::= expr NE expr */
#line 312 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "!=", yymsp[0].minor.yy0); }
#line 1474 "parser/epparser.c"
        break;
      case 79: /* lexpr ::= expr LE expr */
#line 313 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<=", yymsp[0].minor.yy0); }
#line 1479 "parser/epparser.c"
        break;
      case 80: /* lexpr ::= expr LT expr */
#line 314 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<",  yymsp[0].minor.yy0); }
#line 1484 "parser/epparser.c"
        break;
      case 81: /* lexpr ::= expr GE expr */
#line 315 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">=", yymsp[0].minor.yy0); }
#line 1489 "parser/epparser.c"
        break;
      case 82: /* lexpr ::= expr GT expr */
#line 316 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">" , yymsp[0].minor.yy0); }
#line 1494 "parser/epparser.c"
        break;
      case 83: /* lexpr ::= lexpr LAND lexpr */
#line 318 "parser/epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "[" + yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data + "]";
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1503 "parser/epparser.c"
        break;
      case 84: /* lexpr ::= lexpr LOR lexpr */
#line 324 "parser/epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "EUDOr([" + yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data + "])";
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1512 "parser/epparser.c"
        break;
      case 85: /* lexpr ::= LNOT lexpr */
#line 330 "parser/epparser.lemon"
{
    yymsp[0].minor.yy0->data = "EUDNot([" + yymsp[0].minor.yy0->data + "])";
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0);
}
#line 1520 "parser/epparser.c"
        break;
      case 87: /* vdef_stmt ::= VAR nameList_nonEmpty SEMICOLON */
#line 340 "parser/epparser.lemon"
{
    std::string& s = yymsp[-1].minor.yy0->data;
    int varCount = std::count(s.begin(), s.end(), ',') + 1;

    // Register variables.
    commaListIter(s, [&](std::string& varname) {
        if(!ps->closure.defVariable(varname)) {
            throw_error(yymsp[-1].minor.yy0->line, 196, ("Redeclaration of variable \'" + varname + "\'"));
        }
    });

    if(varCount == 1) {
        ps->gen << s << " = EUDVariable()" << std::endl;
    }
    else {
        ps->gen << s << " = EUDCreateVariables(" << varCount << ")" << std::endl;
    }

    delete yymsp[-1].minor.yy0;
}
#line 1544 "parser/epparser.c"
        break;
      case 88: /* vdefAssign_stmt ::= VAR nameList_nonEmpty ASSIGN exprList_nonEmpty SEMICOLON */
#line 361 "parser/epparser.lemon"
{
    std::string& s = yymsp[-3].minor.yy0->data;
    int varCount = std::count(s.begin(), s.end(), ',') + 1;

    // Register variables.
    commaListIter(s, [&](std::string& varname) {
        if(!ps->closure.defVariable(varname)) {
            throw_error(yymsp[-3].minor.yy0->line, 196, ("Redeclaration of variable \'" + varname + "\'"));
        }
    });

    if(varCount == 1) {
        ps->gen << s << " = EUDVariable()" << std::endl;
        ps->gen << s << " << " << yymsp[-1].minor.yy0->data << std::endl;
    }
    else {
        ps->gen << s << " = _MVAR([" << yymsp[-1].minor.yy0->data << "])" << std::endl;
    }

    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1569 "parser/epparser.c"
        break;
      case 89: /* cdef_stmt ::= CONST nameList_nonEmpty ASSIGN exprList_nonEmpty SEMICOLON */
#line 383 "parser/epparser.lemon"
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
#line 1585 "parser/epparser.c"
        break;
      case 90: /* assign_stmt ::= nameList_nonEmpty ASSIGN exprList_nonEmpty SEMICOLON */
#line 396 "parser/epparser.lemon"
{
    if(yymsp[-3].minor.yy0->data.find(',') == std::string::npos) {
        ps->gen << yymsp[-3].minor.yy0->data << " << " << yymsp[-1].minor.yy0->data << std::endl;
    }
    else {
        ps->gen << "SetVariables([" << yymsp[-3].minor.yy0->data << "], [" << yymsp[-1].minor.yy0->data << "])" << std::endl;
    }
    commaListIter(yymsp[-3].minor.yy0->data, [&](std::string& varname) {
        if(!ps->closure.defVariable(varname)) {
            throw_error(yymsp[-3].minor.yy0->line, 103, ("Undeclared variable \'" + varname + "\'"));
            ps->closure.defVariable(varname);
        }
    });
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1604 "parser/epparser.c"
        break;
      case 91: /* if_start ::= IF */
#line 413 "parser/epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDIf()" << std::endl;
}
#line 1612 "parser/epparser.c"
        break;
      case 92: /* if_header ::= if_start LPAREN lexpr RPAREN */
      case 101: /* while_header ::= while_start LPAREN lexpr RPAREN */ yytestcase(yyruleno==101);
#line 417 "parser/epparser.lemon"
{
    ps->gen << "if " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data << "):" << std::endl;
    ps->gen.indent();
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1622 "parser/epparser.c"
        break;
      case 94: /* elif_start ::= ELSE IF */
#line 425 "parser/epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen.unindent(false);
    ps->gen << yygotominor.yy0->data << " = EUDElseIf()" << std::endl;
}
#line 1631 "parser/epparser.c"
        break;
      case 95: /* elif_header ::= elif_start LPAREN lexpr RPAREN */
#line 431 "parser/epparser.lemon"
{
    ps->gen << "if " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data <<"):" << std::endl;
    ps->gen.indent();
}
#line 1639 "parser/epparser.c"
        break;
      case 97: /* else_header ::= ELSE */
#line 438 "parser/epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "if EUDElse()():" << std::endl;
    ps->gen.indent();
}
#line 1648 "parser/epparser.c"
        break;
      case 98: /* if_stmt ::= if_block */
      case 99: /* if_stmt ::= if_block else_header stmt */ yytestcase(yyruleno==99);
#line 444 "parser/epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndIf()" << std::endl;
}
#line 1657 "parser/epparser.c"
        break;
      case 100: /* while_start ::= WHILE */
#line 456 "parser/epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDWhile()" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1666 "parser/epparser.c"
        break;
      case 102: /* while_stmt ::= while_header stmt */
#line 468 "parser/epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndWhile()" << std::endl;
}
#line 1674 "parser/epparser.c"
        break;
      case 103: /* foreach_header ::= FOR LPAREN nameList_nonEmpty COLON exprList_nonEmpty RPAREN */
#line 474 "parser/epparser.lemon"
{
    ps->closure.pushScope();
    commaListIter(yymsp[-3].minor.yy0->data, [&](std::string& s) {
        ps->closure.defVariable(s);
    });
    ps->gen << "for " << yymsp[-3].minor.yy0->data << " in " << yymsp[-1].minor.yy0->data << ":" << std::endl;
    ps->gen.indent();
}
#line 1686 "parser/epparser.c"
        break;
      case 105: /* continue_stmt ::= CONTINUE SEMICOLON */
#line 490 "parser/epparser.lemon"
{
    ps->gen << "EUDContinue()" << std::endl;
}
#line 1693 "parser/epparser.c"
        break;
      case 106: /* break_stmt ::= BREAK SEMICOLON */
#line 494 "parser/epparser.lemon"
{
    ps->gen << "EUDBreak()" << std::endl;
}
#line 1700 "parser/epparser.c"
        break;
      case 107: /* return_stmt ::= RETURN exprList SEMICOLON */
#line 501 "parser/epparser.lemon"
{
    ps->gen << "EUDReturn(" << yymsp[-1].minor.yy0->data << ")" << std::endl;
    delete yymsp[-1].minor.yy0;
}
#line 1708 "parser/epparser.c"
        break;
      case 108: /* lexpr ::= CONDITIONNAME LPAREN fArgs RPAREN */
#line 509 "parser/epparser.lemon"
{
    yymsp[-3].minor.yy0->data = yymsp[-3].minor.yy0->data + "(" + yymsp[-1].minor.yy0->data + ")";
    delete yymsp[-1].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 1717 "parser/epparser.c"
        break;
      case 109: /* lexpr ::= CONDITIONNAME LPAREN RPAREN */
#line 515 "parser/epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + "()";
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1725 "parser/epparser.c"
        break;
      case 110: /* action ::= ACTIONNAME LPAREN fArgs RPAREN SEMICOLON */
#line 520 "parser/epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[-4].minor.yy0);
    yygotominor.yy0->data =  yymsp[-4].minor.yy0->data + "(" + yymsp[-2].minor.yy0->data + ")";
    delete yymsp[-4].minor.yy0; delete yymsp[-2].minor.yy0;
}
#line 1734 "parser/epparser.c"
        break;
      case 111: /* actions ::= action action */
      case 112: /* actions ::= actions action */ yytestcase(yyruleno==112);
#line 526 "parser/epparser.lemon"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
    yymsp[-1].minor.yy0->data += ",\n" + yymsp[0].minor.yy0->data;
    delete yymsp[0].minor.yy0;
}
#line 1744 "parser/epparser.c"
        break;
      case 113: /* actionStmt ::= action */
#line 538 "parser/epparser.lemon"
{
    ps->gen << "DoActions(" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1752 "parser/epparser.c"
        break;
      case 114: /* actionStmt ::= actions */
#line 543 "parser/epparser.lemon"
{
    ps->gen << "DoActions([" << std::endl;
    ps->gen.indent();
    ps->gen << yymsp[0].minor.yy0->data << std::endl;
    ps->gen.unindent(false);
    ps->gen << "])" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1764 "parser/epparser.c"
        break;
      default:
      /* (0) program ::= chunks */ yytestcase(yyruleno==0);
      /* (1) chunks ::= */ yytestcase(yyruleno==1);
      /* (2) chunks ::= chunks chunk */ yytestcase(yyruleno==2);
      /* (3) chunk ::= import_chunk */ yytestcase(yyruleno==3);
      /* (4) chunk ::= fdef_chunk */ yytestcase(yyruleno==4);
      /* (5) chunk ::= vdef_stmt */ yytestcase(yyruleno==5);
      /* (6) chunk ::= cdef_stmt */ yytestcase(yyruleno==6);
      /* (13) stmt ::= bodyStmt */ yytestcase(yyruleno==13);
      /* (14) stmt ::= return_stmt */ yytestcase(yyruleno==14);
      /* (18) stmt ::= lbracket return_stmt rbracket */ yytestcase(yyruleno==18);
      /* (19) stmt ::= lbracket bodyStmtList rbracket */ yytestcase(yyruleno==19);
      /* (20) stmt ::= lbracket bodyStmtList return_stmt rbracket */ yytestcase(yyruleno==20);
      /* (22) bodyStmt ::= SEMICOLON */ yytestcase(yyruleno==22);
      /* (23) bodyStmt ::= vdef_stmt */ yytestcase(yyruleno==23);
      /* (24) bodyStmt ::= vdefAssign_stmt */ yytestcase(yyruleno==24);
      /* (25) bodyStmt ::= cdef_stmt */ yytestcase(yyruleno==25);
      /* (26) bodyStmt ::= assign_stmt */ yytestcase(yyruleno==26);
      /* (28) bodyStmt ::= actionStmt */ yytestcase(yyruleno==28);
      /* (29) bodyStmt ::= if_stmt */ yytestcase(yyruleno==29);
      /* (30) bodyStmt ::= while_stmt */ yytestcase(yyruleno==30);
      /* (31) bodyStmt ::= foreach_stmt */ yytestcase(yyruleno==31);
      /* (32) bodyStmt ::= continue_stmt */ yytestcase(yyruleno==32);
      /* (33) bodyStmt ::= break_stmt */ yytestcase(yyruleno==33);
      /* (34) bodyStmtList ::= bodyStmt */ yytestcase(yyruleno==34);
      /* (35) bodyStmtList ::= bodyStmtList bodyStmt */ yytestcase(yyruleno==35);
      /* (93) if_block ::= if_header stmt */ yytestcase(yyruleno==93);
      /* (96) if_block ::= if_block elif_header stmt */ yytestcase(yyruleno==96);
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
#line 22 "parser/epparser.lemon"

    errorOccured = true;
#line 1856 "parser/epparser.c"
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
#line 557 "parser/epparser.lemon"


int PARSER_DEBUG = 0;
PyGenerator* pGen;

std::string ParseString(const std::string& code, bool addComment)
{
    Tokenizer tok(code);
    void* pParser = ParseAlloc (malloc);
    ParserStruct ps;
    Token* token;
    currentTokenizingLine = 0;
    pGen = &ps.gen;

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
#line 2090 "parser/epparser.c"
