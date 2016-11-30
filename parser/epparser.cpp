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
#define YYNOCODE 103
#define YYACTIONTYPE unsigned short int
#define ParseTOKENTYPE Token*
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  int yy205;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL  ParserStruct* ps ;
#define ParseARG_PDECL , ParserStruct* ps 
#define ParseARG_FETCH  ParserStruct* ps  = yypParser->ps 
#define ParseARG_STORE yypParser->ps  = ps 
#define YYNSTATE 225
#define YYNRULE 113
#define YYERRORSYMBOL 57
#define YYERRSYMDT yy205
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
#define YY_ACTTAB_COUNT (746)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   133,   47,   46,   43,   44,   42,   26,  203,  201,   92,
 /*    10 */   276,  218,  214,  212,  211,    7,  215,  131,  202,  200,
 /*    20 */   132,  198,  197,  196,  195,  194,  193,   18,   19,   43,
 /*    30 */    44,   42,  124,  138,  105,    5,   48,  164,  133,   59,
 /*    40 */   102,    3,    2,   52,   51,  203,  201,   92,  136,   27,
 /*    50 */   158,  212,  211,    7,  136,  184,  202,  200,  132,  198,
 /*    60 */   197,  196,  195,  194,  193,   18,   19,  103,    4,    1,
 /*    70 */   124,  128,  105,    5,   48,  136,  133,   26,  102,    3,
 /*    80 */     2,   52,   51,  203,  201,   92,  136,   24,  155,  212,
 /*    90 */   211,    7,  219,  159,  202,  200,  132,  198,  197,  196,
 /*   100 */   195,  194,  193,   18,   19,  216,  127,  151,  124,  217,
 /*   110 */   105,    5,   48,   26,  133,  191,  102,    3,    2,   52,
 /*   120 */    51,  203,  201,   92,  339,    9,  152,  212,  211,    7,
 /*   130 */   136,  156,  202,  200,  132,  198,  197,  196,  195,  194,
 /*   140 */   193,   18,   19,   49,  162,  129,  124,  213,  105,    5,
 /*   150 */    48,   26,  133,  199,  102,    3,    2,   52,   51,  203,
 /*   160 */   201,   92,   56,  125,  150,  212,  211,    7,  189,  153,
 /*   170 */   202,  200,  132,  198,  197,  196,  195,  194,  193,  277,
 /*   180 */    23,  188,  161,   12,  124,   20,  105,    5,   48,   26,
 /*   190 */   133,  121,  102,    3,    2,   52,   51,  203,  201,   92,
 /*   200 */   276,  120,  142,  212,  211,    7,  183,  126,  202,  200,
 /*   210 */   132,  198,  197,  196,  195,  194,  193,  118,  117,  115,
 /*   220 */   147,  182,  124,  114,  105,    5,   48,  136,   95,  181,
 /*   230 */   102,    3,    2,   52,   51,  203,  201,   92,  112,  111,
 /*   240 */    19,  140,   58,  180,   10,    8,  202,  200,  132,  198,
 /*   250 */   197,  196,  195,  194,  193,   22,  169,   15,  163,  166,
 /*   260 */   124,   14,  105,    5,   48,  136,   25,  157,  102,    3,
 /*   270 */     2,   52,   51,  203,  201,   92,   13,   53,   11,  192,
 /*   280 */    57,  149,  206,  148,  202,  200,  132,  198,  197,  196,
 /*   290 */   195,  194,  193,   96,  141,  145,  163,  218,  124,  137,
 /*   300 */   105,    5,   48,  207,  190,  205,  102,    3,    2,   52,
 /*   310 */    51,  208,   98,   91,   33,   31,   30,   29,   28,   32,
 /*   320 */    38,   37,   39,   41,   40,   47,   46,   43,   44,   42,
 /*   330 */    17,   38,   37,   39,   41,   40,   47,   46,   43,   44,
 /*   340 */    42,  144,   78,   36,   35,  143,   87,  186,   85,   34,
 /*   350 */   187,   90,  186,   82,   94,   45,   68,   16,  170,  124,
 /*   360 */   104,   68,  106,  108,  124,  123,  122,  119,  116,  113,
 /*   370 */    36,   35,  340,  340,  340,  340,   34,  187,   90,  340,
 /*   380 */   109,  340,   45,   37,   39,   41,   40,   47,   46,   43,
 /*   390 */    44,   42,  123,  122,  119,  116,  113,   36,   35,  186,
 /*   400 */   340,  340,  340,   34,  187,   90,  130,  109,   60,   45,
 /*   410 */   168,  124,   81,  340,   89,   69,  340,  171,  124,  123,
 /*   420 */   122,  119,  116,  113,   36,   35,  340,  340,  340,  340,
 /*   430 */    34,  187,   90,  340,  340,  340,   45,   41,   40,   47,
 /*   440 */    46,   43,   44,   42,  171,  340,  123,  122,  119,  116,
 /*   450 */   113,   36,   35,  340,  340,  186,  340,   34,  187,   90,
 /*   460 */   186,  340,  340,   45,   60,  146,  340,  124,  174,   68,
 /*   470 */    97,  108,  124,  123,  122,  119,  116,  113,   93,  340,
 /*   480 */   340,  340,  340,  340,  204,  340,  208,  340,  340,   39,
 /*   490 */    41,   40,   47,   46,   43,   44,   42,   55,   54,  160,
 /*   500 */   340,  154,  101,   93,  100,   99,   21,  340,   98,  204,
 /*   510 */   340,  209,  224,  223,  222,  221,  220,  340,  134,    6,
 /*   520 */   340,  340,   55,   54,  160,  340,  154,  101,   93,  100,
 /*   530 */    99,   21,  340,   98,  204,  210,  340,  340,  340,  340,
 /*   540 */   340,  186,  340,  340,  340,  340,  340,   55,   54,  160,
 /*   550 */    79,  154,  101,  124,  100,   99,   21,  340,   98,  340,
 /*   560 */   340,   38,   37,   39,   41,   40,   47,   46,   43,   44,
 /*   570 */    42,  340,  340,  340,   36,   35,  225,  340,  340,  185,
 /*   580 */    34,  187,   90,  186,  340,  340,   45,  340,  340,  340,
 /*   590 */   340,  340,   68,  107,  108,  124,  123,  122,  119,  116,
 /*   600 */   113,  130,  340,  139,  340,  135,  130,  340,  130,  165,
 /*   610 */    69,  340,  340,  124,   88,   69,   86,   69,  124,  186,
 /*   620 */   124,   50,   54,  340,  340,  340,  130,  340,   80,  340,
 /*   630 */   186,  124,  130,  340,   84,   69,  186,  340,  124,   60,
 /*   640 */    83,   69,  124,  110,  124,   60,  186,  340,  124,  173,
 /*   650 */   340,  340,  186,  340,  186,   60,  340,  340,  124,  172,
 /*   660 */   186,   60,  340,   60,  124,   77,  124,   76,  340,   60,
 /*   670 */   186,  186,  124,   75,  340,  186,  186,  186,  340,   61,
 /*   680 */   167,  186,  124,  124,  179,  178,   74,  124,  124,  124,
 /*   690 */    73,  186,  186,  124,  340,  340,  186,  186,  186,  340,
 /*   700 */    72,   70,  340,  124,  124,   71,  177,  176,  124,  124,
 /*   710 */   124,  340,  186,  186,  186,  340,  340,  340,  186,  186,
 /*   720 */   186,  175,   67,   66,  124,  124,  124,   65,   64,   63,
 /*   730 */   124,  124,  124,  186,  340,  340,  340,  340,  340,  340,
 /*   740 */   340,  340,   62,  340,  340,  124,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    57,   18,   19,   20,   21,   22,    1,   64,   65,   66,
 /*    10 */    30,   26,   69,   70,   71,   72,   31,   37,   75,   76,
 /*    20 */    77,   78,   79,   80,   81,   82,   83,    3,    4,   20,
 /*    30 */    21,   22,   89,   26,   91,   92,   93,   32,   57,   28,
 /*    40 */    97,   98,   99,  100,  101,   64,   65,   66,    1,    2,
 /*    50 */    69,   70,   71,   72,    1,   31,   75,   76,   77,   78,
 /*    60 */    79,   80,   81,   82,   83,    3,    4,   94,   95,   96,
 /*    70 */    89,    1,   91,   92,   93,    1,   57,    1,   97,   98,
 /*    80 */    99,  100,  101,   64,   65,   66,    1,    2,   69,   70,
 /*    90 */    71,   72,   26,   31,   75,   76,   77,   78,   79,   80,
 /*   100 */    81,   82,   83,    3,    4,   31,   36,   31,   89,   26,
 /*   110 */    91,   92,   93,    1,   57,   26,   97,   98,   99,  100,
 /*   120 */   101,   64,   65,   66,   59,   60,   69,   70,   71,   72,
 /*   130 */     1,   31,   75,   76,   77,   78,   79,   80,   81,   82,
 /*   140 */    83,    3,    4,   30,   32,   35,   89,   32,   91,   92,
 /*   150 */    93,    1,   57,   32,   97,   98,   99,  100,  101,   64,
 /*   160 */    65,   66,   35,   26,   69,   70,   71,   72,   25,   31,
 /*   170 */    75,   76,   77,   78,   79,   80,   81,   82,   83,   30,
 /*   180 */    51,   36,   32,   30,   89,   30,   91,   92,   93,    1,
 /*   190 */    57,   30,   97,   98,   99,  100,  101,   64,   65,   66,
 /*   200 */    30,   38,   69,   70,   71,   72,   31,   37,   75,   76,
 /*   210 */    77,   78,   79,   80,   81,   82,   83,   30,   38,   30,
 /*   220 */    32,   31,   89,   38,   91,   92,   93,    1,   57,   31,
 /*   230 */    97,   98,   99,  100,  101,   64,   65,   66,   30,   38,
 /*   240 */     4,   70,   71,   31,   30,   74,   75,   76,   77,   78,
 /*   250 */    79,   80,   81,   82,   83,    1,   31,   30,   32,   31,
 /*   260 */    89,   30,   91,   92,   93,    1,    2,   47,   97,   98,
 /*   270 */    99,  100,  101,   64,   65,   66,   30,   30,   30,   70,
 /*   280 */    71,   32,   73,   32,   75,   76,   77,   78,   79,   80,
 /*   290 */    81,   82,   83,   31,   34,   32,   32,   26,   89,   66,
 /*   300 */    91,   92,   93,   73,   25,   73,   97,   98,   99,  100,
 /*   310 */   101,   34,   56,   84,    7,    8,    9,   10,   11,   12,
 /*   320 */    13,   14,   15,   16,   17,   18,   19,   20,   21,   22,
 /*   330 */     5,   13,   14,   15,   16,   17,   18,   19,   20,   21,
 /*   340 */    22,  100,   66,   18,   19,  100,   66,   77,   66,   24,
 /*   350 */    25,   26,   77,   66,   66,   30,   86,    5,   88,   89,
 /*   360 */    48,   86,   87,   88,   89,   40,   41,   42,   43,   44,
 /*   370 */    18,   19,  102,  102,  102,  102,   24,   25,   26,  102,
 /*   380 */    55,  102,   30,   14,   15,   16,   17,   18,   19,   20,
 /*   390 */    21,   22,   40,   41,   42,   43,   44,   18,   19,   77,
 /*   400 */   102,  102,  102,   24,   25,   26,   77,   55,   86,   30,
 /*   410 */    31,   89,   90,  102,   85,   86,  102,   38,   89,   40,
 /*   420 */    41,   42,   43,   44,   18,   19,  102,  102,  102,  102,
 /*   430 */    24,   25,   26,  102,  102,  102,   30,   16,   17,   18,
 /*   440 */    19,   20,   21,   22,   38,  102,   40,   41,   42,   43,
 /*   450 */    44,   18,   19,  102,  102,   77,  102,   24,   25,   26,
 /*   460 */    77,  102,  102,   30,   86,   32,  102,   89,   90,   86,
 /*   470 */    87,   88,   89,   40,   41,   42,   43,   44,   26,  102,
 /*   480 */   102,  102,  102,  102,   32,  102,   34,  102,  102,   15,
 /*   490 */    16,   17,   18,   19,   20,   21,   22,   45,   46,   47,
 /*   500 */   102,   49,   50,   26,   52,   53,   54,  102,   56,   32,
 /*   510 */   102,   34,   61,   62,   63,   64,   65,  102,   67,   68,
 /*   520 */   102,  102,   45,   46,   47,  102,   49,   50,   26,   52,
 /*   530 */    53,   54,  102,   56,   32,   33,  102,  102,  102,  102,
 /*   540 */   102,   77,  102,  102,  102,  102,  102,   45,   46,   47,
 /*   550 */    86,   49,   50,   89,   52,   53,   54,  102,   56,  102,
 /*   560 */   102,   13,   14,   15,   16,   17,   18,   19,   20,   21,
 /*   570 */    22,  102,  102,  102,   18,   19,    0,  102,  102,   31,
 /*   580 */    24,   25,   26,   77,  102,  102,   30,  102,  102,  102,
 /*   590 */   102,  102,   86,   87,   88,   89,   40,   41,   42,   43,
 /*   600 */    44,   77,  102,   27,  102,   29,   77,  102,   77,   85,
 /*   610 */    86,  102,  102,   89,   85,   86,   85,   86,   89,   77,
 /*   620 */    89,   45,   46,  102,  102,  102,   77,  102,   86,  102,
 /*   630 */    77,   89,   77,  102,   85,   86,   77,  102,   89,   86,
 /*   640 */    85,   86,   89,   90,   89,   86,   77,  102,   89,   90,
 /*   650 */   102,  102,   77,  102,   77,   86,  102,  102,   89,   90,
 /*   660 */    77,   86,  102,   86,   89,   90,   89,   90,  102,   86,
 /*   670 */    77,   77,   89,   90,  102,   77,   77,   77,  102,   86,
 /*   680 */    86,   77,   89,   89,   86,   86,   86,   89,   89,   89,
 /*   690 */    86,   77,   77,   89,  102,  102,   77,   77,   77,  102,
 /*   700 */    86,   86,  102,   89,   89,   86,   86,   86,   89,   89,
 /*   710 */    89,  102,   77,   77,   77,  102,  102,  102,   77,   77,
 /*   720 */    77,   86,   86,   86,   89,   89,   89,   86,   86,   86,
 /*   730 */    89,   89,   89,   77,  102,  102,  102,  102,  102,  102,
 /*   740 */   102,  102,   86,  102,  102,   89,
};
#define YY_SHIFT_USE_DFLT (-21)
#define YY_SHIFT_COUNT (139)
#define YY_SHIFT_MIN   (-20)
#define YY_SHIFT_MAX   (576)
static const short yy_shift_ofst[] = {
 /*     0 */   -21,  502,  502,  502,  502,  502,  502,  477,  452,  576,
 /*    10 */   379,  406,  406,  325,  325,  325,  352,  352,  325,  325,
 /*    20 */   325,  433,  406,  556,  556,  556,  556,  556,  556,  556,
 /*    30 */   556,  556,  556,  556,  556,  556,  556,  556,  556,  556,
 /*    40 */   556,  556,  556,  556,  556,  556,  556,  556,  312,  -15,
 /*    50 */   271,  256,  256,  271,  271,  271,  279,  277,  277,  271,
 /*    60 */   307,  548,  318,  318,  318,  318,  318,  318,  318,  318,
 /*    70 */   369,  474,  421,  -17,  -17,  138,  100,   62,  264,    9,
 /*    80 */     9,   24,  226,  188,   76,  129,  150,   85,  112,    5,
 /*    90 */   170,   70,   47,  -20,   74,  260,  263,  262,  248,  251,
 /*   100 */   249,  247,  246,  231,  220,  227,  228,  225,  254,  214,
 /*   110 */   236,  212,  201,  208,  198,  185,  189,  190,  180,  187,
 /*   120 */   175,  163,  161,  155,  153,  149,  137,  145,  143,  127,
 /*   130 */   110,   89,  121,  115,  113,   83,   66,   53,   11,    7,
};
#define YY_REDUCE_USE_DFLT (-58)
#define YY_REDUCE_COUNT (59)
#define YY_REDUCE_MIN   (-57)
#define YY_REDUCE_MAX   (656)
static const short yy_reduce_ofst[] = {
 /*     0 */    65,  133,   95,   57,   19,  -19,  -57,  171,  209,  451,
 /*    10 */   506,  383,  275,  583,  577,  575,  569,  559,  553,  378,
 /*    20 */   322,  555,  270,  549,  531,  529,  524,  329,  656,  643,
 /*    30 */   642,  641,  637,  636,  635,  621,  620,  619,  615,  614,
 /*    40 */   604,  600,  599,  598,  594,  593,  542,  464,  -27,  288,
 /*    50 */   287,  245,  241,  282,  280,  276,  229,  232,  230,  233,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   226,  338,  338,  338,  338,  338,  338,  338,  338,  338,
 /*    10 */   338,  271,  271,  338,  338,  338,  338,  338,  338,  338,
 /*    20 */   338,  338,  338,  338,  338,  338,  338,  338,  338,  338,
 /*    30 */   338,  338,  338,  338,  338,  338,  338,  338,  338,  338,
 /*    40 */   338,  338,  338,  338,  338,  338,  338,  338,  320,  338,
 /*    50 */   338,  337,  336,  338,  338,  338,  338,  338,  338,  338,
 /*    60 */   338,  338,  304,  303,  302,  301,  300,  299,  272,  266,
 /*    70 */   294,  295,  293,  292,  291,  338,  338,  338,  338,  286,
 /*    80 */   287,  338,  338,  338,  338,  338,  338,  338,  338,  338,
 /*    90 */   269,  338,  338,  263,  338,  338,  338,  338,  338,  338,
 /*   100 */   338,  338,  338,  338,  319,  338,  338,  338,  275,  338,
 /*   110 */   306,  338,  338,  338,  338,  338,  338,  338,  338,  338,
 /*   120 */   338,  338,  338,  338,  338,  270,  338,  338,  338,  338,
 /*   130 */   279,  338,  338,  338,  338,  338,  338,  232,  338,  338,
 /*   140 */   259,  246,  321,  335,  334,  333,  329,  330,  328,  327,
 /*   150 */   326,  325,  324,  323,  322,  318,  317,  316,  315,  314,
 /*   160 */   313,  311,  310,  309,  312,  267,  278,  288,  332,  331,
 /*   170 */   274,  273,  308,  307,  305,  298,  297,  296,  290,  289,
 /*   180 */   285,  284,  283,  282,  281,  280,  279,  268,  265,  262,
 /*   190 */   261,  277,  260,  258,  257,  256,  255,  254,  253,  252,
 /*   200 */   251,  250,  249,  248,  247,  245,  244,  243,  241,  242,
 /*   210 */   240,  239,  238,  237,  236,  235,  234,  233,  263,  264,
 /*   220 */   231,  230,  229,  228,  227,
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
  "IMPORT",        "FUNCTION",      "LPAREN",        "RPAREN",      
  "SEMICOLON",     "LBRACKET",      "RBRACKET",      "LSQBRACKET",  
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
  "numList_nonEmpty",  "exprList",      "expr",          "fArgs",       
  "fArgsAny",      "funcName",      "lexpr",         "if_start",    
  "if_header",     "if_block",      "elif_start",    "elif_header", 
  "else_header",   "while_start",   "while_header",  "foreach_header",
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
 /*   3 */ "chunk ::= import_chunk",
 /*   4 */ "chunk ::= fdef_chunk",
 /*   5 */ "chunk ::= vdef_stmt",
 /*   6 */ "chunk ::= cdef_stmt",
 /*   7 */ "import_chunk ::= FROM NAME IMPORT nameList_nonEmpty",
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
 /*  40 */ "exprList ::= funcexpr LSQBRACKET LSQBRACKET numList_nonEmpty RSQBRACKET RSQBRACKET",
 /*  41 */ "exprList ::= expr",
 /*  42 */ "exprList ::= exprList COMMA exprList",
 /*  43 */ "expr ::= NUMBER",
 /*  44 */ "expr ::= NAME",
 /*  45 */ "expr ::= NAME PERIOD NAME",
 /*  46 */ "fArgs ::=",
 /*  47 */ "fArgsAny ::= expr",
 /*  48 */ "fArgsAny ::= STRING",
 /*  49 */ "fArgsAny ::= fArgsAny COMMA fArgsAny",
 /*  50 */ "fArgs ::= fArgsAny",
 /*  51 */ "funcName ::= NAME",
 /*  52 */ "funcName ::= NAME PERIOD NAME",
 /*  53 */ "funcexpr ::= funcName LPAREN fArgs RPAREN",
 /*  54 */ "expr ::= funcexpr",
 /*  55 */ "expr ::= LPAREN expr RPAREN",
 /*  56 */ "expr ::= L2V LPAREN lexpr RPAREN",
 /*  57 */ "expr ::= MAPSTRING LPAREN STRING RPAREN",
 /*  58 */ "expr ::= UNIT LPAREN STRING RPAREN",
 /*  59 */ "expr ::= SWITCH LPAREN STRING RPAREN",
 /*  60 */ "expr ::= LOCATION LPAREN STRING RPAREN",
 /*  61 */ "expr ::= expr PLUS expr",
 /*  62 */ "expr ::= expr MINUS expr",
 /*  63 */ "expr ::= expr MULTIPLY expr",
 /*  64 */ "expr ::= expr DIVIDE expr",
 /*  65 */ "expr ::= expr MOD expr",
 /*  66 */ "expr ::= expr LSHIFT expr",
 /*  67 */ "expr ::= expr RSHIFT expr",
 /*  68 */ "expr ::= expr BITAND expr",
 /*  69 */ "expr ::= expr BITOR expr",
 /*  70 */ "expr ::= expr BITXOR expr",
 /*  71 */ "expr ::= PLUS expr",
 /*  72 */ "expr ::= MINUS expr",
 /*  73 */ "expr ::= BITNOT expr",
 /*  74 */ "lexpr ::= expr EQ expr",
 /*  75 */ "lexpr ::= expr NE expr",
 /*  76 */ "lexpr ::= expr LE expr",
 /*  77 */ "lexpr ::= expr LT expr",
 /*  78 */ "lexpr ::= expr GE expr",
 /*  79 */ "lexpr ::= expr GT expr",
 /*  80 */ "lexpr ::= lexpr LAND lexpr",
 /*  81 */ "lexpr ::= lexpr LOR lexpr",
 /*  82 */ "lexpr ::= LNOT lexpr",
 /*  83 */ "lexpr ::= LNOT LNOT lexpr",
 /*  84 */ "vdef_stmt ::= VAR nameList_nonEmpty SEMICOLON",
 /*  85 */ "vdefAssign_stmt ::= VAR nameList_nonEmpty ASSIGN exprList SEMICOLON",
 /*  86 */ "cdef_stmt ::= CONST nameList_nonEmpty ASSIGN exprList SEMICOLON",
 /*  87 */ "assign_stmt ::= nameList_nonEmpty ASSIGN exprList SEMICOLON",
 /*  88 */ "if_start ::= IF",
 /*  89 */ "if_header ::= if_start LPAREN lexpr RPAREN",
 /*  90 */ "if_block ::= if_header stmt",
 /*  91 */ "elif_start ::= ELSE IF",
 /*  92 */ "elif_header ::= elif_start LPAREN lexpr RPAREN",
 /*  93 */ "if_block ::= if_block elif_header stmt",
 /*  94 */ "else_header ::= ELSE",
 /*  95 */ "if_stmt ::= if_block",
 /*  96 */ "if_stmt ::= if_block else_header stmt",
 /*  97 */ "while_start ::= WHILE",
 /*  98 */ "while_header ::= while_start LPAREN lexpr RPAREN",
 /*  99 */ "while_stmt ::= while_header stmt",
 /* 100 */ "foreach_header ::= FOR LPAREN nameList_nonEmpty COLON exprList RPAREN",
 /* 101 */ "foreach_stmt ::= foreach_header stmt",
 /* 102 */ "continue_stmt ::= CONTINUE SEMICOLON",
 /* 103 */ "break_stmt ::= BREAK SEMICOLON",
 /* 104 */ "return_stmt ::= RETURN SEMICOLON",
 /* 105 */ "return_stmt ::= RETURN exprList SEMICOLON",
 /* 106 */ "lexpr ::= CONDITIONNAME LPAREN fArgs RPAREN",
 /* 107 */ "lexpr ::= CONDITIONNAME LPAREN RPAREN",
 /* 108 */ "action ::= ACTIONNAME LPAREN fArgs RPAREN SEMICOLON",
 /* 109 */ "actions ::= action action",
 /* 110 */ "actions ::= actions action",
 /* 111 */ "actionStmt ::= action",
 /* 112 */ "actionStmt ::= actions",
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
#line 697 "parser/epparser.c"
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
  { 62, 4 },
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
  { 85, 1 },
  { 85, 3 },
  { 86, 1 },
  { 86, 1 },
  { 86, 3 },
  { 87, 0 },
  { 88, 1 },
  { 88, 1 },
  { 88, 3 },
  { 87, 1 },
  { 89, 1 },
  { 89, 3 },
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
  { 90, 3 },
  { 90, 3 },
  { 90, 3 },
  { 90, 3 },
  { 90, 3 },
  { 90, 3 },
  { 90, 3 },
  { 90, 3 },
  { 90, 2 },
  { 90, 3 },
  { 64, 3 },
  { 75, 5 },
  { 65, 5 },
  { 76, 4 },
  { 91, 1 },
  { 92, 4 },
  { 93, 2 },
  { 94, 2 },
  { 95, 4 },
  { 93, 3 },
  { 96, 1 },
  { 79, 1 },
  { 79, 3 },
  { 97, 1 },
  { 98, 4 },
  { 80, 2 },
  { 99, 6 },
  { 81, 2 },
  { 82, 2 },
  { 83, 2 },
  { 71, 2 },
  { 71, 3 },
  { 90, 4 },
  { 90, 3 },
  { 100, 5 },
  { 101, 2 },
  { 101, 2 },
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
      case 7: /* import_chunk ::= FROM NAME IMPORT nameList_nonEmpty */
#line 65 "parser/epparser.lemon"
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
#line 1115 "parser/epparser.c"
        break;
      case 8: /* function_start ::= FUNCTION NAME */
#line 78 "parser/epparser.lemon"
{
    // Preprocess yymsp[0].minor.yy0
    funcNamePreprocess(yymsp[0].minor.yy0->data);
    if(!ps->closure.defFunction(yymsp[0].minor.yy0->data)) {
        throw_error(yymsp[0].minor.yy0->line, 4495, "Duplicate function yymsp[0].minor.yy0 " + yymsp[0].minor.yy0->data);
    }
    ps->closure.pushScope();
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1128 "parser/epparser.c"
        break;
      case 9: /* function_header ::= function_start LPAREN nameList_nonEmpty RPAREN */
#line 88 "parser/epparser.lemon"
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
#line 1147 "parser/epparser.c"
        break;
      case 10: /* function_header ::= function_start LPAREN RPAREN */
#line 104 "parser/epparser.lemon"
{
    ps->gen << "@EUDFunc" << std::endl;
    ps->gen << "def " << yymsp[-2].minor.yy0->data << "():" << std::endl;
    ps->gen.indent();
    tmpIndex = 1;
    delete yymsp[-2].minor.yy0;
}
#line 1158 "parser/epparser.c"
        break;
      case 11: /* fdef_chunk ::= function_header stmt */
      case 101: /* foreach_stmt ::= foreach_header stmt */ yytestcase(yyruleno==101);
#line 112 "parser/epparser.lemon"
{
    ps->gen.unindent(true);
    ps->closure.popScope();
}
#line 1167 "parser/epparser.c"
        break;
      case 12: /* stmt ::= error SEMICOLON */
#line 119 "parser/epparser.lemon"
{ throw_error(yymsp[0].minor.yy0->line, 6974, "Error while parsing statement"); }
#line 1172 "parser/epparser.c"
        break;
      case 15: /* lbracket ::= LBRACKET */
#line 124 "parser/epparser.lemon"
{ ps->closure.pushScope(); }
#line 1177 "parser/epparser.c"
        break;
      case 16: /* rbracket ::= RBRACKET */
#line 125 "parser/epparser.lemon"
{ ps->closure.popScope(); }
#line 1182 "parser/epparser.c"
        break;
      case 17: /* stmt ::= lbracket RBRACKET */
#line 127 "parser/epparser.lemon"
{
    ps->gen << "pass" << std::endl;
    ps->closure.popScope();
}
#line 1190 "parser/epparser.c"
        break;
      case 21: /* stmt ::= lbracket error RBRACKET */
#line 134 "parser/epparser.lemon"
{
    throw_error(yymsp[0].minor.yy0->line, 6298, "Block not terminated properly.");
    ps->closure.popScope();
}
#line 1198 "parser/epparser.c"
        break;
      case 27: /* bodyStmt ::= funcexpr SEMICOLON */
#line 144 "parser/epparser.lemon"
{ ps->gen << yymsp[-1].minor.yy0->data << std::endl; }
#line 1203 "parser/epparser.c"
        break;
      case 36: /* numList_nonEmpty ::= NUMBER */
#line 158 "parser/epparser.lemon"
{
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1210 "parser/epparser.c"
        break;
      case 37: /* numList_nonEmpty ::= numList_nonEmpty COMMA NUMBER */
#line 162 "parser/epparser.lemon"
{
    yygotominor.yy0 = new Token(yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data, yymsp[0].minor.yy0);
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 1218 "parser/epparser.c"
        break;
      case 38: /* nameList_nonEmpty ::= NAME */
      case 41: /* exprList ::= expr */ yytestcase(yyruleno==41);
      case 43: /* expr ::= NUMBER */ yytestcase(yyruleno==43);
      case 47: /* fArgsAny ::= expr */ yytestcase(yyruleno==47);
      case 48: /* fArgsAny ::= STRING */ yytestcase(yyruleno==48);
      case 50: /* fArgs ::= fArgsAny */ yytestcase(yyruleno==50);
      case 54: /* expr ::= funcexpr */ yytestcase(yyruleno==54);
      case 83: /* lexpr ::= LNOT LNOT lexpr */ yytestcase(yyruleno==83);
#line 167 "parser/epparser.lemon"
{ yygotominor.yy0 = yymsp[0].minor.yy0; }
#line 1230 "parser/epparser.c"
        break;
      case 39: /* nameList_nonEmpty ::= nameList_nonEmpty COMMA NAME */
#line 168 "parser/epparser.lemon"
{
    yymsp[0].minor.yy0->data = yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data;
    delete yymsp[-2].minor.yy0;
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1239 "parser/epparser.c"
        break;
      case 40: /* exprList ::= funcexpr LSQBRACKET LSQBRACKET numList_nonEmpty RSQBRACKET RSQBRACKET */
#line 174 "parser/epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[-2].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = _SRET(" << yymsp[-5].minor.yy0->data << ", [" << yymsp[-2].minor.yy0->data << "])" << std::endl;
    delete yymsp[-5].minor.yy0; delete yymsp[-2].minor.yy0;
}
#line 1248 "parser/epparser.c"
        break;
      case 42: /* exprList ::= exprList COMMA exprList */
#line 182 "parser/epparser.lemon"
{ yygotominor.yy0 = new Token((yymsp[-2].minor.yy0->data) + ", " + (yymsp[0].minor.yy0->data), yymsp[0].minor.yy0); delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1253 "parser/epparser.c"
        break;
      case 44: /* expr ::= NAME */
#line 186 "parser/epparser.lemon"
{
    if(!ps->closure.getConstant(yymsp[0].minor.yy0->data) && !ps->closure.getVariable(yymsp[0].minor.yy0->data)) {
        throw_error(yymsp[0].minor.yy0->line, 103, ("Undeclared \'" + (yymsp[0].minor.yy0->data) + "\'"));
        ps->closure.defVariable(yymsp[0].minor.yy0->data);
    }
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1264 "parser/epparser.c"
        break;
      case 45: /* expr ::= NAME PERIOD NAME */
#line 194 "parser/epparser.lemon"
{
    if(!ps->closure.getConstant(yymsp[-2].minor.yy0->data)) {
        throw_error(yymsp[-2].minor.yy0->line, 103, ("Undeclared constant \'" + (yymsp[-2].minor.yy0->data) + "\'"));
        ps->closure.defConstant(yymsp[-2].minor.yy0->data);
    }
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + "." + yymsp[0].minor.yy0->data;
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1277 "parser/epparser.c"
        break;
      case 46: /* fArgs ::= */
#line 205 "parser/epparser.lemon"
{ yygotominor.yy0 = genEmpty(); }
#line 1282 "parser/epparser.c"
        break;
      case 49: /* fArgsAny ::= fArgsAny COMMA fArgsAny */
#line 208 "parser/epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data;
    yymsp[-2].minor.yy0->type = TOKEN_TEMP;
    yygotominor.yy0 = yymsp[-2].minor.yy0;
    delete yymsp[0].minor.yy0;
}
#line 1292 "parser/epparser.c"
        break;
      case 51: /* funcName ::= NAME */
#line 217 "parser/epparser.lemon"
{
    funcNamePreprocess(yymsp[0].minor.yy0->data);
    if (!ps->closure.getFunction(yymsp[0].minor.yy0->data)) {
        throw_error(yymsp[0].minor.yy0->line, 4449, ("Undefined function " + yymsp[0].minor.yy0->data));
        ps->closure.defFunction(yymsp[0].minor.yy0->data);
    }
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1304 "parser/epparser.c"
        break;
      case 52: /* funcName ::= NAME PERIOD NAME */
#line 225 "parser/epparser.lemon"
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
#line 1326 "parser/epparser.c"
        break;
      case 53: /* funcexpr ::= funcName LPAREN fArgs RPAREN */
#line 244 "parser/epparser.lemon"
{
    // Preprocess yymsp[-3].minor.yy0
    yymsp[-3].minor.yy0->data += "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 1335 "parser/epparser.c"
        break;
      case 55: /* expr ::= LPAREN expr RPAREN */
#line 253 "parser/epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1343 "parser/epparser.c"
        break;
      case 56: /* expr ::= L2V LPAREN lexpr RPAREN */
#line 258 "parser/epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "_L2V(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = genTemp(yymsp[-1].minor.yy0);
}
#line 1351 "parser/epparser.c"
        break;
      case 57: /* expr ::= MAPSTRING LPAREN STRING RPAREN */
#line 263 "parser/epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetStringIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1359 "parser/epparser.c"
        break;
      case 58: /* expr ::= UNIT LPAREN STRING RPAREN */
#line 268 "parser/epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetUnitIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1367 "parser/epparser.c"
        break;
      case 59: /* expr ::= SWITCH LPAREN STRING RPAREN */
#line 273 "parser/epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetSwitchIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1375 "parser/epparser.c"
        break;
      case 60: /* expr ::= LOCATION LPAREN STRING RPAREN */
#line 278 "parser/epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetLocationIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1383 "parser/epparser.c"
        break;
      case 61: /* expr ::= expr PLUS expr */
#line 284 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "+",  yymsp[0].minor.yy0); }
#line 1388 "parser/epparser.c"
        break;
      case 62: /* expr ::= expr MINUS expr */
#line 285 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "-",  yymsp[0].minor.yy0); }
#line 1393 "parser/epparser.c"
        break;
      case 63: /* expr ::= expr MULTIPLY expr */
#line 286 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "*",  yymsp[0].minor.yy0); }
#line 1398 "parser/epparser.c"
        break;
      case 64: /* expr ::= expr DIVIDE expr */
#line 287 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "//", yymsp[0].minor.yy0); }
#line 1403 "parser/epparser.c"
        break;
      case 65: /* expr ::= expr MOD expr */
#line 288 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "%",  yymsp[0].minor.yy0); }
#line 1408 "parser/epparser.c"
        break;
      case 66: /* expr ::= expr LSHIFT expr */
#line 289 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<<", yymsp[0].minor.yy0); }
#line 1413 "parser/epparser.c"
        break;
      case 67: /* expr ::= expr RSHIFT expr */
#line 290 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">>", yymsp[0].minor.yy0); }
#line 1418 "parser/epparser.c"
        break;
      case 68: /* expr ::= expr BITAND expr */
#line 291 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "&",  yymsp[0].minor.yy0); }
#line 1423 "parser/epparser.c"
        break;
      case 69: /* expr ::= expr BITOR expr */
#line 292 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "|",  yymsp[0].minor.yy0); }
#line 1428 "parser/epparser.c"
        break;
      case 70: /* expr ::= expr BITXOR expr */
#line 293 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "^",  yymsp[0].minor.yy0); }
#line 1433 "parser/epparser.c"
        break;
      case 71: /* expr ::= PLUS expr */
#line 296 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = +" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1438 "parser/epparser.c"
        break;
      case 72: /* expr ::= MINUS expr */
#line 297 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = -" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1443 "parser/epparser.c"
        break;
      case 73: /* expr ::= BITNOT expr */
#line 298 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = ~" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1448 "parser/epparser.c"
        break;
      case 74: /* lexpr ::= expr EQ expr */
#line 302 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "==", yymsp[0].minor.yy0); }
#line 1453 "parser/epparser.c"
        break;
      case 75: /* lexpr ::= expr NE expr */
#line 303 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "!=", yymsp[0].minor.yy0); }
#line 1458 "parser/epparser.c"
        break;
      case 76: /* lexpr ::= expr LE expr */
#line 304 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<=", yymsp[0].minor.yy0); }
#line 1463 "parser/epparser.c"
        break;
      case 77: /* lexpr ::= expr LT expr */
#line 305 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<",  yymsp[0].minor.yy0); }
#line 1468 "parser/epparser.c"
        break;
      case 78: /* lexpr ::= expr GE expr */
#line 306 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">=", yymsp[0].minor.yy0); }
#line 1473 "parser/epparser.c"
        break;
      case 79: /* lexpr ::= expr GT expr */
#line 307 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">" , yymsp[0].minor.yy0); }
#line 1478 "parser/epparser.c"
        break;
      case 80: /* lexpr ::= lexpr LAND lexpr */
#line 309 "parser/epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "[" + yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data + "]";
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1487 "parser/epparser.c"
        break;
      case 81: /* lexpr ::= lexpr LOR lexpr */
#line 315 "parser/epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "EUDOr([" + yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data + "])";
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1496 "parser/epparser.c"
        break;
      case 82: /* lexpr ::= LNOT lexpr */
#line 321 "parser/epparser.lemon"
{
    yymsp[0].minor.yy0->data = "EUDNot([" + yymsp[0].minor.yy0->data + "])";
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0);
}
#line 1504 "parser/epparser.c"
        break;
      case 84: /* vdef_stmt ::= VAR nameList_nonEmpty SEMICOLON */
#line 331 "parser/epparser.lemon"
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
#line 1526 "parser/epparser.c"
        break;
      case 85: /* vdefAssign_stmt ::= VAR nameList_nonEmpty ASSIGN exprList SEMICOLON */
#line 350 "parser/epparser.lemon"
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
#line 1542 "parser/epparser.c"
        break;
      case 86: /* cdef_stmt ::= CONST nameList_nonEmpty ASSIGN exprList SEMICOLON */
#line 363 "parser/epparser.lemon"
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
#line 1558 "parser/epparser.c"
        break;
      case 87: /* assign_stmt ::= nameList_nonEmpty ASSIGN exprList SEMICOLON */
#line 376 "parser/epparser.lemon"
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
#line 1577 "parser/epparser.c"
        break;
      case 88: /* if_start ::= IF */
#line 393 "parser/epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDIf()" << std::endl;
}
#line 1585 "parser/epparser.c"
        break;
      case 89: /* if_header ::= if_start LPAREN lexpr RPAREN */
      case 98: /* while_header ::= while_start LPAREN lexpr RPAREN */ yytestcase(yyruleno==98);
#line 397 "parser/epparser.lemon"
{
    ps->gen << "if " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data << "):" << std::endl;
    ps->gen.indent();
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1595 "parser/epparser.c"
        break;
      case 91: /* elif_start ::= ELSE IF */
#line 405 "parser/epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen.unindent(false);
    ps->gen << yygotominor.yy0->data << " = EUDElseIf()" << std::endl;
}
#line 1604 "parser/epparser.c"
        break;
      case 92: /* elif_header ::= elif_start LPAREN lexpr RPAREN */
#line 411 "parser/epparser.lemon"
{
    ps->gen << "if " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data <<"):" << std::endl;
    ps->gen.indent();
}
#line 1612 "parser/epparser.c"
        break;
      case 94: /* else_header ::= ELSE */
#line 418 "parser/epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "if EUDElse()():" << std::endl;
    ps->gen.indent();
}
#line 1621 "parser/epparser.c"
        break;
      case 95: /* if_stmt ::= if_block */
      case 96: /* if_stmt ::= if_block else_header stmt */ yytestcase(yyruleno==96);
#line 424 "parser/epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndIf()" << std::endl;
}
#line 1630 "parser/epparser.c"
        break;
      case 97: /* while_start ::= WHILE */
#line 436 "parser/epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDWhile()" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1639 "parser/epparser.c"
        break;
      case 99: /* while_stmt ::= while_header stmt */
#line 448 "parser/epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndWhile()" << std::endl;
}
#line 1647 "parser/epparser.c"
        break;
      case 100: /* foreach_header ::= FOR LPAREN nameList_nonEmpty COLON exprList RPAREN */
#line 454 "parser/epparser.lemon"
{
    ps->closure.pushScope();
    commaListIter(yymsp[-3].minor.yy0->data, [&](std::string& s) {
        ps->closure.defVariable(s);
    });
    ps->gen << "for " << yymsp[-3].minor.yy0->data << " in " << yymsp[-1].minor.yy0->data << ":" << std::endl;
    ps->gen.indent();
}
#line 1659 "parser/epparser.c"
        break;
      case 102: /* continue_stmt ::= CONTINUE SEMICOLON */
#line 470 "parser/epparser.lemon"
{
    ps->gen << "EUDContinue()" << std::endl;
}
#line 1666 "parser/epparser.c"
        break;
      case 103: /* break_stmt ::= BREAK SEMICOLON */
#line 474 "parser/epparser.lemon"
{
    ps->gen << "EUDBreak()" << std::endl;
}
#line 1673 "parser/epparser.c"
        break;
      case 104: /* return_stmt ::= RETURN SEMICOLON */
#line 481 "parser/epparser.lemon"
{
    ps->gen << "EUDReturn()" << std::endl;
}
#line 1680 "parser/epparser.c"
        break;
      case 105: /* return_stmt ::= RETURN exprList SEMICOLON */
#line 485 "parser/epparser.lemon"
{
    ps->gen << "EUDReturn(" << yymsp[-1].minor.yy0->data << ")" << std::endl;
    delete yymsp[-1].minor.yy0;
}
#line 1688 "parser/epparser.c"
        break;
      case 106: /* lexpr ::= CONDITIONNAME LPAREN fArgs RPAREN */
#line 493 "parser/epparser.lemon"
{
    yymsp[-3].minor.yy0->data = yymsp[-3].minor.yy0->data + "(" + yymsp[-1].minor.yy0->data + ")";
    delete yymsp[-1].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 1697 "parser/epparser.c"
        break;
      case 107: /* lexpr ::= CONDITIONNAME LPAREN RPAREN */
#line 499 "parser/epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + "()";
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1705 "parser/epparser.c"
        break;
      case 108: /* action ::= ACTIONNAME LPAREN fArgs RPAREN SEMICOLON */
#line 504 "parser/epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[-4].minor.yy0);
    yygotominor.yy0->data =  yymsp[-4].minor.yy0->data + "(" + yymsp[-2].minor.yy0->data + ")";
    delete yymsp[-4].minor.yy0; delete yymsp[-2].minor.yy0;
}
#line 1714 "parser/epparser.c"
        break;
      case 109: /* actions ::= action action */
      case 110: /* actions ::= actions action */ yytestcase(yyruleno==110);
#line 510 "parser/epparser.lemon"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
    yymsp[-1].minor.yy0->data += ",\n" + yymsp[0].minor.yy0->data;
    delete yymsp[0].minor.yy0;
}
#line 1724 "parser/epparser.c"
        break;
      case 111: /* actionStmt ::= action */
#line 522 "parser/epparser.lemon"
{
    ps->gen << "DoActions(" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1732 "parser/epparser.c"
        break;
      case 112: /* actionStmt ::= actions */
#line 527 "parser/epparser.lemon"
{
    ps->gen << "DoActions([" << std::endl;
    ps->gen.indent();
    ps->gen << yymsp[0].minor.yy0->data << std::endl;
    ps->gen.unindent(false);
    ps->gen << "])" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1744 "parser/epparser.c"
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
      /* (90) if_block ::= if_header stmt */ yytestcase(yyruleno==90);
      /* (93) if_block ::= if_block elif_header stmt */ yytestcase(yyruleno==93);
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
#line 1836 "parser/epparser.c"
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
#line 541 "parser/epparser.lemon"


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
#line 2070 "parser/epparser.c"
