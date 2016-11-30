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
#define YYNSTATE 232
#define YYNRULE 114
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
 /*     0 */   140,   47,   46,   43,   44,   42,   26,  210,  208,   93,
 /*    10 */   284,  225,  221,  219,  218,    7,  222,  138,  209,  207,
 /*    20 */   139,  205,  204,  203,  202,  201,  200,   18,   19,   43,
 /*    30 */    44,   42,  125,  145,  106,    5,   48,  171,  140,   59,
 /*    40 */   103,    3,    2,   52,   51,  210,  208,   93,  143,   27,
 /*    50 */   165,  219,  218,    7,  143,  191,  209,  207,  139,  205,
 /*    60 */   204,  203,  202,  201,  200,   18,   19,  104,    4,    1,
 /*    70 */   125,  135,  106,    5,   48,  143,  140,   26,  103,    3,
 /*    80 */     2,   52,   51,  210,  208,   93,  143,   24,  162,  219,
 /*    90 */   218,    7,  226,  166,  209,  207,  139,  205,  204,  203,
 /*   100 */   202,  201,  200,   18,   19,  223,  134,  158,  125,  224,
 /*   110 */   106,    5,   48,  143,  140,  198,  103,    3,    2,   52,
 /*   120 */    51,  210,  208,   93,  347,    9,  159,  219,  218,    7,
 /*   130 */   220,  163,  209,  207,  139,  205,  204,  203,  202,  201,
 /*   140 */   200,   18,   19,   49,  133,  136,  125,  206,  106,    5,
 /*   150 */    48,   26,  140,   56,  103,    3,    2,   52,   51,  210,
 /*   160 */   208,   93,  197,   23,  157,  219,  218,    7,  196,  160,
 /*   170 */   209,  207,  139,  205,  204,  203,  202,  201,  200,  132,
 /*   180 */   195,  194,  169,  130,  125,  128,  106,    5,   48,   26,
 /*   190 */   140,  129,  103,    3,    2,   52,   51,  210,  208,   93,
 /*   200 */   284,  134,  149,  219,  218,    7,  126,  127,  209,  207,
 /*   210 */   139,  205,  204,  203,  202,  201,  200,  285,  156,   12,
 /*   220 */   168,   20,  125,  122,  106,    5,   48,   26,   96,  190,
 /*   230 */   103,    3,    2,   52,   51,  210,  208,   93,  121,  118,
 /*   240 */   119,  147,   58,  189,  116,    8,  209,  207,  139,  205,
 /*   250 */   204,  203,  202,  201,  200,  115,  188,  113,  154,  112,
 /*   260 */   125,  187,  106,    5,   48,  143,   25,   19,  103,    3,
 /*   270 */     2,   52,   51,  210,  208,   93,   10,   22,  176,  199,
 /*   280 */    57,  143,  213,  173,  209,  207,  139,  205,  204,  203,
 /*   290 */   202,  201,  200,  155,  152,   15,  170,  164,  125,   14,
 /*   300 */   106,    5,   48,   13,   53,  148,  103,    3,    2,   52,
 /*   310 */    51,   11,  170,   97,   33,   31,   30,   29,   28,   32,
 /*   320 */    38,   37,   39,   41,   40,   47,   46,   43,   44,   42,
 /*   330 */    17,   38,   37,   39,   41,   40,   47,   46,   43,   44,
 /*   340 */    42,  225,  215,   36,   35,  144,   92,  131,  151,   34,
 /*   350 */   193,   90,  131,   99,   78,   45,   68,   16,  177,  125,
 /*   360 */   214,   68,  107,  109,  125,  124,  123,  120,  117,  114,
 /*   370 */    36,   35,  212,   91,  105,   87,   34,  193,   90,   85,
 /*   380 */   110,  348,   45,   37,   39,   41,   40,   47,   46,   43,
 /*   390 */    44,   42,  124,  123,  120,  117,  114,   36,   35,  131,
 /*   400 */   150,   82,   95,   34,  193,   90,  137,  110,   60,   45,
 /*   410 */   175,  125,   81,  348,   89,   69,  348,  178,  125,  124,
 /*   420 */   123,  120,  117,  114,   36,   35,  348,  348,  348,  348,
 /*   430 */    34,  193,   90,  348,  348,  348,   45,   41,   40,   47,
 /*   440 */    46,   43,   44,   42,  178,  348,  124,  123,  120,  117,
 /*   450 */   114,   36,   35,  348,  348,  131,  348,   34,  193,   90,
 /*   460 */   131,  348,  348,   45,   60,  153,  348,  125,  181,   68,
 /*   470 */    98,  109,  125,  124,  123,  120,  117,  114,   94,  348,
 /*   480 */   348,  348,  348,  348,  211,  348,  215,  348,  348,   39,
 /*   490 */    41,   40,   47,   46,   43,   44,   42,   55,   54,  167,
 /*   500 */   348,  161,  102,   94,  101,  100,   21,  348,   99,  211,
 /*   510 */   348,  216,  231,  230,  229,  228,  227,  348,  141,    6,
 /*   520 */   348,  348,   55,   54,  167,  348,  161,  102,   94,  101,
 /*   530 */   100,   21,  348,   99,  211,  217,  348,  348,  348,  348,
 /*   540 */   348,  131,  348,  348,  348,  348,  348,   55,   54,  167,
 /*   550 */    79,  161,  102,  125,  101,  100,   21,  348,   99,  348,
 /*   560 */   348,   38,   37,   39,   41,   40,   47,   46,   43,   44,
 /*   570 */    42,  348,  348,  348,   36,   35,  232,  348,  348,  192,
 /*   580 */    34,  193,   90,  131,  348,  348,   45,  348,  348,  348,
 /*   590 */   348,  348,   68,  108,  109,  125,  124,  123,  120,  117,
 /*   600 */   114,  137,  348,  146,  348,  142,  137,  348,  137,  172,
 /*   610 */    69,  348,  348,  125,   88,   69,   86,   69,  125,  131,
 /*   620 */   125,   50,   54,  348,  348,  348,  137,  348,   80,  348,
 /*   630 */   131,  125,  137,  348,   84,   69,  131,  348,  125,   60,
 /*   640 */    83,   69,  125,  111,  125,   60,  131,  348,  125,  180,
 /*   650 */   348,  348,  131,  348,  131,   60,  348,  348,  125,  179,
 /*   660 */   131,   60,  348,   60,  125,   77,  125,   76,  348,   60,
 /*   670 */   131,  131,  125,   75,  348,  131,  131,  131,  348,   61,
 /*   680 */   174,  131,  125,  125,  186,  185,   74,  125,  125,  125,
 /*   690 */    73,  131,  131,  125,  348,  348,  131,  131,  131,  348,
 /*   700 */    72,   70,  348,  125,  125,   71,  184,  183,  125,  125,
 /*   710 */   125,  348,  131,  131,  131,  348,  348,  348,  131,  131,
 /*   720 */   131,  182,   67,   66,  125,  125,  125,   65,   64,   63,
 /*   730 */   125,  125,  125,  131,  348,  348,  348,  348,  348,  348,
 /*   740 */   348,  348,   62,  348,  348,  125,
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
 /*   130 */    32,   31,   75,   76,   77,   78,   79,   80,   81,   82,
 /*   140 */    83,    3,    4,   30,    1,   35,   89,   32,   91,   92,
 /*   150 */    93,    1,   57,   35,   97,   98,   99,  100,  101,   64,
 /*   160 */    65,   66,   25,   51,   69,   70,   71,   72,   36,   31,
 /*   170 */    75,   76,   77,   78,   79,   80,   81,   82,   83,   36,
 /*   180 */    25,   36,   32,   35,   89,   25,   91,   92,   93,    1,
 /*   190 */    57,   35,   97,   98,   99,  100,  101,   64,   65,   66,
 /*   200 */    30,   36,   69,   70,   71,   72,   26,   37,   75,   76,
 /*   210 */    77,   78,   79,   80,   81,   82,   83,   30,   32,   30,
 /*   220 */    32,   30,   89,   30,   91,   92,   93,    1,   57,   31,
 /*   230 */    97,   98,   99,  100,  101,   64,   65,   66,   38,   38,
 /*   240 */    30,   70,   71,   31,   30,   74,   75,   76,   77,   78,
 /*   250 */    79,   80,   81,   82,   83,   38,   31,   30,   32,   38,
 /*   260 */    89,   31,   91,   92,   93,    1,    2,    4,   97,   98,
 /*   270 */    99,  100,  101,   64,   65,   66,   30,    1,   31,   70,
 /*   280 */    71,    1,   73,   31,   75,   76,   77,   78,   79,   80,
 /*   290 */    81,   82,   83,   32,   32,   30,   32,   47,   89,   30,
 /*   300 */    91,   92,   93,   30,   30,   34,   97,   98,   99,  100,
 /*   310 */   101,   30,   32,   31,    7,    8,    9,   10,   11,   12,
 /*   320 */    13,   14,   15,   16,   17,   18,   19,   20,   21,   22,
 /*   330 */     5,   13,   14,   15,   16,   17,   18,   19,   20,   21,
 /*   340 */    22,   26,   34,   18,   19,   66,   25,   77,  100,   24,
 /*   350 */    25,   26,   77,   56,   66,   30,   86,    5,   88,   89,
 /*   360 */    73,   86,   87,   88,   89,   40,   41,   42,   43,   44,
 /*   370 */    18,   19,   73,   84,   48,   66,   24,   25,   26,   66,
 /*   380 */    55,  102,   30,   14,   15,   16,   17,   18,   19,   20,
 /*   390 */    21,   22,   40,   41,   42,   43,   44,   18,   19,   77,
 /*   400 */   100,   66,   66,   24,   25,   26,   77,   55,   86,   30,
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
#define YY_SHIFT_COUNT (146)
#define YY_SHIFT_MIN   (-20)
#define YY_SHIFT_MAX   (576)
static const short yy_shift_ofst[] = {
 /*     0 */   -21,  502,  502,  502,  502,  502,  502,  477,  452,  576,
 /*    10 */   379,  406,  406,  325,  325,  325,  352,  352,  325,  325,
 /*    20 */   325,  433,  406,  556,  556,  556,  556,  556,  556,  556,
 /*    30 */   556,  556,  556,  556,  556,  556,  556,  556,  556,  556,
 /*    40 */   556,  556,  556,  556,  556,  556,  556,  556,  326,  -15,
 /*    50 */   315,  297,  297,  315,  315,  315,  321,  308,  308,  315,
 /*    60 */   307,  548,  318,  318,  318,  318,  318,  318,  318,  318,
 /*    70 */   369,  474,  421,  -17,  -17,  138,  100,   62,  264,    9,
 /*    80 */     9,   24,  280,  226,   76,  112,  188,   85,  150,    5,
 /*    90 */   170,  143,   70,   47,  -20,   74,  271,  262,  282,  281,
 /*   100 */   261,  186,  274,  273,  269,  250,  265,  252,  247,  276,
 /*   110 */   246,  263,  230,  221,  227,  225,  217,  214,  212,  201,
 /*   120 */   210,  198,  200,  193,  191,  189,  187,  180,  165,  160,
 /*   130 */   156,  148,  145,  155,  132,  137,  118,  110,   89,  115,
 /*   140 */    98,  113,   83,   66,   53,   11,    7,
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
 /*    40 */   604,  600,  599,  598,  594,  593,  542,  464,  -27,  336,
 /*    50 */   335,  300,  248,  313,  309,  288,  289,  299,  287,  279,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   233,  346,  346,  346,  346,  346,  346,  346,  346,  346,
 /*    10 */   346,  279,  279,  346,  346,  346,  346,  346,  346,  346,
 /*    20 */   346,  346,  346,  346,  346,  346,  346,  346,  346,  346,
 /*    30 */   346,  346,  346,  346,  346,  346,  346,  346,  346,  346,
 /*    40 */   346,  346,  346,  346,  346,  346,  346,  346,  328,  346,
 /*    50 */   346,  345,  344,  346,  346,  346,  346,  346,  346,  346,
 /*    60 */   346,  346,  312,  311,  310,  309,  308,  307,  280,  274,
 /*    70 */   302,  303,  301,  300,  299,  346,  346,  346,  346,  294,
 /*    80 */   295,  346,  346,  346,  346,  346,  346,  346,  346,  346,
 /*    90 */   277,  346,  346,  346,  270,  346,  346,  346,  346,  346,
 /*   100 */   346,  346,  346,  346,  346,  327,  346,  346,  346,  283,
 /*   110 */   346,  314,  346,  346,  346,  346,  346,  346,  346,  346,
 /*   120 */   346,  346,  346,  346,  346,  346,  278,  346,  346,  346,
 /*   130 */   346,  287,  346,  346,  346,  346,  346,  287,  346,  346,
 /*   140 */   346,  346,  346,  346,  239,  346,  346,  266,  253,  329,
 /*   150 */   343,  342,  341,  337,  338,  336,  335,  334,  333,  332,
 /*   160 */   331,  330,  326,  325,  324,  323,  322,  321,  319,  318,
 /*   170 */   317,  320,  275,  286,  296,  340,  339,  282,  281,  316,
 /*   180 */   315,  313,  306,  305,  304,  298,  297,  293,  292,  291,
 /*   190 */   290,  289,  288,  276,  272,  269,  273,  268,  285,  267,
 /*   200 */   265,  264,  263,  262,  261,  260,  259,  258,  257,  256,
 /*   210 */   255,  254,  252,  251,  250,  248,  249,  247,  246,  245,
 /*   220 */   244,  243,  242,  241,  240,  270,  271,  238,  237,  236,
 /*   230 */   235,  234,
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
  "vdef_stmt",     "cdef_stmt",     "nameList",      "function_start",
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
 /*   7 */ "import_chunk ::= FROM NAME IMPORT nameList",
 /*   8 */ "function_start ::= FUNCTION NAME",
 /*   9 */ "function_header ::= function_start LPAREN nameList RPAREN",
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
 /*  36 */ "numList_nonEmpty ::= NUMBER COMMA NUMBER",
 /*  37 */ "numList_nonEmpty ::= numList_nonEmpty COMMA NUMBER",
 /*  38 */ "nameList ::= NAME",
 /*  39 */ "nameList ::= nameList COMMA NAME",
 /*  40 */ "exprList ::= funcexpr LSQBRACKET LSQBRACKET numList_nonEmpty RSQBRACKET RSQBRACKET",
 /*  41 */ "expr ::= funcexpr LSQBRACKET LSQBRACKET NUMBER RSQBRACKET RSQBRACKET",
 /*  42 */ "exprList ::= expr",
 /*  43 */ "exprList ::= exprList COMMA exprList",
 /*  44 */ "expr ::= NUMBER",
 /*  45 */ "expr ::= NAME",
 /*  46 */ "expr ::= NAME PERIOD NAME",
 /*  47 */ "fArgs ::=",
 /*  48 */ "fArgsAny ::= expr",
 /*  49 */ "fArgsAny ::= STRING",
 /*  50 */ "fArgsAny ::= fArgsAny COMMA fArgsAny",
 /*  51 */ "fArgs ::= fArgsAny",
 /*  52 */ "funcName ::= NAME",
 /*  53 */ "funcName ::= NAME PERIOD NAME",
 /*  54 */ "funcexpr ::= funcName LPAREN fArgs RPAREN",
 /*  55 */ "expr ::= funcexpr",
 /*  56 */ "expr ::= LPAREN expr RPAREN",
 /*  57 */ "expr ::= L2V LPAREN lexpr RPAREN",
 /*  58 */ "expr ::= MAPSTRING LPAREN STRING RPAREN",
 /*  59 */ "expr ::= UNIT LPAREN STRING RPAREN",
 /*  60 */ "expr ::= SWITCH LPAREN STRING RPAREN",
 /*  61 */ "expr ::= LOCATION LPAREN STRING RPAREN",
 /*  62 */ "expr ::= expr PLUS expr",
 /*  63 */ "expr ::= expr MINUS expr",
 /*  64 */ "expr ::= expr MULTIPLY expr",
 /*  65 */ "expr ::= expr DIVIDE expr",
 /*  66 */ "expr ::= expr MOD expr",
 /*  67 */ "expr ::= expr LSHIFT expr",
 /*  68 */ "expr ::= expr RSHIFT expr",
 /*  69 */ "expr ::= expr BITAND expr",
 /*  70 */ "expr ::= expr BITOR expr",
 /*  71 */ "expr ::= expr BITXOR expr",
 /*  72 */ "expr ::= PLUS expr",
 /*  73 */ "expr ::= MINUS expr",
 /*  74 */ "expr ::= BITNOT expr",
 /*  75 */ "lexpr ::= expr EQ expr",
 /*  76 */ "lexpr ::= expr NE expr",
 /*  77 */ "lexpr ::= expr LE expr",
 /*  78 */ "lexpr ::= expr LT expr",
 /*  79 */ "lexpr ::= expr GE expr",
 /*  80 */ "lexpr ::= expr GT expr",
 /*  81 */ "lexpr ::= lexpr LAND lexpr",
 /*  82 */ "lexpr ::= lexpr LOR lexpr",
 /*  83 */ "lexpr ::= LNOT lexpr",
 /*  84 */ "lexpr ::= LNOT LNOT lexpr",
 /*  85 */ "vdef_stmt ::= VAR nameList SEMICOLON",
 /*  86 */ "vdefAssign_stmt ::= VAR nameList ASSIGN exprList SEMICOLON",
 /*  87 */ "cdef_stmt ::= CONST nameList ASSIGN exprList SEMICOLON",
 /*  88 */ "assign_stmt ::= nameList ASSIGN exprList SEMICOLON",
 /*  89 */ "if_start ::= IF",
 /*  90 */ "if_header ::= if_start LPAREN lexpr RPAREN",
 /*  91 */ "if_block ::= if_header stmt",
 /*  92 */ "elif_start ::= ELSE IF",
 /*  93 */ "elif_header ::= elif_start LPAREN lexpr RPAREN",
 /*  94 */ "if_block ::= if_block elif_header stmt",
 /*  95 */ "else_header ::= ELSE",
 /*  96 */ "if_stmt ::= if_block",
 /*  97 */ "if_stmt ::= if_block else_header stmt",
 /*  98 */ "while_start ::= WHILE",
 /*  99 */ "while_header ::= while_start LPAREN lexpr RPAREN",
 /* 100 */ "while_stmt ::= while_header stmt",
 /* 101 */ "foreach_header ::= FOR LPAREN nameList COLON exprList RPAREN",
 /* 102 */ "foreach_stmt ::= foreach_header stmt",
 /* 103 */ "continue_stmt ::= CONTINUE SEMICOLON",
 /* 104 */ "break_stmt ::= BREAK SEMICOLON",
 /* 105 */ "return_stmt ::= RETURN SEMICOLON",
 /* 106 */ "return_stmt ::= RETURN exprList SEMICOLON",
 /* 107 */ "lexpr ::= CONDITIONNAME LPAREN fArgs RPAREN",
 /* 108 */ "lexpr ::= CONDITIONNAME LPAREN RPAREN",
 /* 109 */ "action ::= ACTIONNAME LPAREN fArgs RPAREN SEMICOLON",
 /* 110 */ "actions ::= action action",
 /* 111 */ "actions ::= actions action",
 /* 112 */ "actionStmt ::= action",
 /* 113 */ "actionStmt ::= actions",
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
#line 700 "parser/epparser.c"
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
  { 84, 3 },
  { 84, 3 },
  { 66, 1 },
  { 66, 3 },
  { 85, 6 },
  { 86, 6 },
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
      case 7: /* import_chunk ::= FROM NAME IMPORT nameList */
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
#line 1119 "parser/epparser.c"
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
#line 1132 "parser/epparser.c"
        break;
      case 9: /* function_header ::= function_start LPAREN nameList RPAREN */
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
#line 1151 "parser/epparser.c"
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
#line 1162 "parser/epparser.c"
        break;
      case 11: /* fdef_chunk ::= function_header stmt */
      case 102: /* foreach_stmt ::= foreach_header stmt */ yytestcase(yyruleno==102);
#line 112 "parser/epparser.lemon"
{
    ps->gen.unindent(true);
    ps->closure.popScope();
}
#line 1171 "parser/epparser.c"
        break;
      case 12: /* stmt ::= error SEMICOLON */
#line 119 "parser/epparser.lemon"
{ throw_error(yymsp[0].minor.yy0->line, 6974, "Error while parsing statement"); }
#line 1176 "parser/epparser.c"
        break;
      case 15: /* lbracket ::= LBRACKET */
#line 124 "parser/epparser.lemon"
{ ps->closure.pushScope(); }
#line 1181 "parser/epparser.c"
        break;
      case 16: /* rbracket ::= RBRACKET */
#line 125 "parser/epparser.lemon"
{ ps->closure.popScope(); }
#line 1186 "parser/epparser.c"
        break;
      case 17: /* stmt ::= lbracket RBRACKET */
#line 127 "parser/epparser.lemon"
{
    ps->gen << "pass" << std::endl;
    ps->closure.popScope();
}
#line 1194 "parser/epparser.c"
        break;
      case 21: /* stmt ::= lbracket error RBRACKET */
#line 134 "parser/epparser.lemon"
{
    throw_error(yymsp[0].minor.yy0->line, 6298, "Block not terminated properly.");
    ps->closure.popScope();
}
#line 1202 "parser/epparser.c"
        break;
      case 27: /* bodyStmt ::= funcexpr SEMICOLON */
#line 144 "parser/epparser.lemon"
{ ps->gen << yymsp[-1].minor.yy0->data << std::endl; }
#line 1207 "parser/epparser.c"
        break;
      case 36: /* numList_nonEmpty ::= NUMBER COMMA NUMBER */
      case 37: /* numList_nonEmpty ::= numList_nonEmpty COMMA NUMBER */ yytestcase(yyruleno==37);
#line 161 "parser/epparser.lemon"
{
    yygotominor.yy0 = new Token(yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data, yymsp[0].minor.yy0);
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 1216 "parser/epparser.c"
        break;
      case 38: /* nameList ::= NAME */
      case 42: /* exprList ::= expr */ yytestcase(yyruleno==42);
      case 44: /* expr ::= NUMBER */ yytestcase(yyruleno==44);
      case 48: /* fArgsAny ::= expr */ yytestcase(yyruleno==48);
      case 49: /* fArgsAny ::= STRING */ yytestcase(yyruleno==49);
      case 51: /* fArgs ::= fArgsAny */ yytestcase(yyruleno==51);
      case 55: /* expr ::= funcexpr */ yytestcase(yyruleno==55);
      case 84: /* lexpr ::= LNOT LNOT lexpr */ yytestcase(yyruleno==84);
#line 170 "parser/epparser.lemon"
{ yygotominor.yy0 = yymsp[0].minor.yy0; }
#line 1228 "parser/epparser.c"
        break;
      case 39: /* nameList ::= nameList COMMA NAME */
      case 43: /* exprList ::= exprList COMMA exprList */ yytestcase(yyruleno==43);
#line 171 "parser/epparser.lemon"
{ yygotominor.yy0 = new Token((yymsp[-2].minor.yy0->data) + ", " + (yymsp[0].minor.yy0->data), yymsp[0].minor.yy0); delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1234 "parser/epparser.c"
        break;
      case 40: /* exprList ::= funcexpr LSQBRACKET LSQBRACKET numList_nonEmpty RSQBRACKET RSQBRACKET */
      case 41: /* expr ::= funcexpr LSQBRACKET LSQBRACKET NUMBER RSQBRACKET RSQBRACKET */ yytestcase(yyruleno==41);
#line 173 "parser/epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[-2].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = _SRET(" << yymsp[-5].minor.yy0->data << ", [" << yymsp[-2].minor.yy0->data << "])" << std::endl;
    delete yymsp[-5].minor.yy0; delete yymsp[-2].minor.yy0;
}
#line 1244 "parser/epparser.c"
        break;
      case 45: /* expr ::= NAME */
#line 190 "parser/epparser.lemon"
{
    if(!ps->closure.getConstant(yymsp[0].minor.yy0->data) && !ps->closure.getVariable(yymsp[0].minor.yy0->data)) {
        throw_error(yymsp[0].minor.yy0->line, 103, ("Undeclared \'" + (yymsp[0].minor.yy0->data) + "\'"));
        ps->closure.defVariable(yymsp[0].minor.yy0->data);
    }
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1255 "parser/epparser.c"
        break;
      case 46: /* expr ::= NAME PERIOD NAME */
#line 198 "parser/epparser.lemon"
{
    if(!ps->closure.getConstant(yymsp[-2].minor.yy0->data)) {
        throw_error(yymsp[-2].minor.yy0->line, 103, ("Undeclared constant \'" + (yymsp[-2].minor.yy0->data) + "\'"));
        ps->closure.defConstant(yymsp[-2].minor.yy0->data);
    }
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + "." + yymsp[0].minor.yy0->data;
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0, ps->gen);
}
#line 1268 "parser/epparser.c"
        break;
      case 47: /* fArgs ::= */
#line 209 "parser/epparser.lemon"
{
    yygotominor.yy0 = new Token(TOKEN_TEMP, "", -1);
}
#line 1275 "parser/epparser.c"
        break;
      case 50: /* fArgsAny ::= fArgsAny COMMA fArgsAny */
#line 215 "parser/epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data;
    yymsp[-2].minor.yy0->type = TOKEN_TEMP;
    yygotominor.yy0 = yymsp[-2].minor.yy0;
    delete yymsp[0].minor.yy0;
}
#line 1285 "parser/epparser.c"
        break;
      case 52: /* funcName ::= NAME */
#line 224 "parser/epparser.lemon"
{
    funcNamePreprocess(yymsp[0].minor.yy0->data);
    if (!ps->closure.getFunction(yymsp[0].minor.yy0->data)) {
        throw_error(yymsp[0].minor.yy0->line, 4449, ("Undefined function " + yymsp[0].minor.yy0->data));
        ps->closure.defFunction(yymsp[0].minor.yy0->data);
    }
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1297 "parser/epparser.c"
        break;
      case 53: /* funcName ::= NAME PERIOD NAME */
#line 232 "parser/epparser.lemon"
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
#line 1319 "parser/epparser.c"
        break;
      case 54: /* funcexpr ::= funcName LPAREN fArgs RPAREN */
#line 251 "parser/epparser.lemon"
{
    // Preprocess yymsp[-3].minor.yy0
    yymsp[-3].minor.yy0->data += "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0, ps->gen);
}
#line 1328 "parser/epparser.c"
        break;
      case 56: /* expr ::= LPAREN expr RPAREN */
#line 260 "parser/epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0, ps->gen);
}
#line 1336 "parser/epparser.c"
        break;
      case 57: /* expr ::= L2V LPAREN lexpr RPAREN */
#line 265 "parser/epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "_L2V(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = genTemp(yymsp[-1].minor.yy0);
}
#line 1344 "parser/epparser.c"
        break;
      case 58: /* expr ::= MAPSTRING LPAREN STRING RPAREN */
#line 270 "parser/epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetStringIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0, ps->gen);
}
#line 1352 "parser/epparser.c"
        break;
      case 59: /* expr ::= UNIT LPAREN STRING RPAREN */
#line 275 "parser/epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetUnitIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0, ps->gen);
}
#line 1360 "parser/epparser.c"
        break;
      case 60: /* expr ::= SWITCH LPAREN STRING RPAREN */
#line 280 "parser/epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetSwitchIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0, ps->gen);
}
#line 1368 "parser/epparser.c"
        break;
      case 61: /* expr ::= LOCATION LPAREN STRING RPAREN */
#line 285 "parser/epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetLocationIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0, ps->gen);
}
#line 1376 "parser/epparser.c"
        break;
      case 62: /* expr ::= expr PLUS expr */
#line 291 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "+",  yymsp[0].minor.yy0, ps->gen); }
#line 1381 "parser/epparser.c"
        break;
      case 63: /* expr ::= expr MINUS expr */
#line 292 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "-",  yymsp[0].minor.yy0, ps->gen); }
#line 1386 "parser/epparser.c"
        break;
      case 64: /* expr ::= expr MULTIPLY expr */
#line 293 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "*",  yymsp[0].minor.yy0, ps->gen); }
#line 1391 "parser/epparser.c"
        break;
      case 65: /* expr ::= expr DIVIDE expr */
#line 294 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "//", yymsp[0].minor.yy0, ps->gen); }
#line 1396 "parser/epparser.c"
        break;
      case 66: /* expr ::= expr MOD expr */
#line 295 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "%",  yymsp[0].minor.yy0, ps->gen); }
#line 1401 "parser/epparser.c"
        break;
      case 67: /* expr ::= expr LSHIFT expr */
#line 296 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<<", yymsp[0].minor.yy0, ps->gen); }
#line 1406 "parser/epparser.c"
        break;
      case 68: /* expr ::= expr RSHIFT expr */
#line 297 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">>", yymsp[0].minor.yy0, ps->gen); }
#line 1411 "parser/epparser.c"
        break;
      case 69: /* expr ::= expr BITAND expr */
#line 298 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "&",  yymsp[0].minor.yy0, ps->gen); }
#line 1416 "parser/epparser.c"
        break;
      case 70: /* expr ::= expr BITOR expr */
#line 299 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "|",  yymsp[0].minor.yy0, ps->gen); }
#line 1421 "parser/epparser.c"
        break;
      case 71: /* expr ::= expr BITXOR expr */
#line 300 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "^",  yymsp[0].minor.yy0, ps->gen); }
#line 1426 "parser/epparser.c"
        break;
      case 72: /* expr ::= PLUS expr */
#line 303 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = +" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1431 "parser/epparser.c"
        break;
      case 73: /* expr ::= MINUS expr */
#line 304 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = -" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1436 "parser/epparser.c"
        break;
      case 74: /* expr ::= BITNOT expr */
#line 305 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = ~" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1441 "parser/epparser.c"
        break;
      case 75: /* lexpr ::= expr EQ expr */
#line 309 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "==", yymsp[0].minor.yy0, ps->gen); }
#line 1446 "parser/epparser.c"
        break;
      case 76: /* lexpr ::= expr NE expr */
#line 310 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "!=", yymsp[0].minor.yy0, ps->gen); }
#line 1451 "parser/epparser.c"
        break;
      case 77: /* lexpr ::= expr LE expr */
#line 311 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<=", yymsp[0].minor.yy0, ps->gen); }
#line 1456 "parser/epparser.c"
        break;
      case 78: /* lexpr ::= expr LT expr */
#line 312 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<",  yymsp[0].minor.yy0, ps->gen); }
#line 1461 "parser/epparser.c"
        break;
      case 79: /* lexpr ::= expr GE expr */
#line 313 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">=", yymsp[0].minor.yy0, ps->gen); }
#line 1466 "parser/epparser.c"
        break;
      case 80: /* lexpr ::= expr GT expr */
#line 314 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">" , yymsp[0].minor.yy0, ps->gen); }
#line 1471 "parser/epparser.c"
        break;
      case 81: /* lexpr ::= lexpr LAND lexpr */
#line 316 "parser/epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "[" + yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data + "]";
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0, ps->gen);
}
#line 1480 "parser/epparser.c"
        break;
      case 82: /* lexpr ::= lexpr LOR lexpr */
#line 322 "parser/epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "EUDOr([" + yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data + "])";
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0, ps->gen);
}
#line 1489 "parser/epparser.c"
        break;
      case 83: /* lexpr ::= LNOT lexpr */
#line 328 "parser/epparser.lemon"
{
    yymsp[0].minor.yy0->data = "EUDNot([" + yymsp[0].minor.yy0->data + "])";
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0, ps->gen);
}
#line 1497 "parser/epparser.c"
        break;
      case 85: /* vdef_stmt ::= VAR nameList SEMICOLON */
#line 338 "parser/epparser.lemon"
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
#line 1514 "parser/epparser.c"
        break;
      case 86: /* vdefAssign_stmt ::= VAR nameList ASSIGN exprList SEMICOLON */
#line 352 "parser/epparser.lemon"
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
#line 1530 "parser/epparser.c"
        break;
      case 87: /* cdef_stmt ::= CONST nameList ASSIGN exprList SEMICOLON */
#line 365 "parser/epparser.lemon"
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
#line 1546 "parser/epparser.c"
        break;
      case 88: /* assign_stmt ::= nameList ASSIGN exprList SEMICOLON */
#line 378 "parser/epparser.lemon"
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
#line 1565 "parser/epparser.c"
        break;
      case 89: /* if_start ::= IF */
#line 395 "parser/epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDIf()" << std::endl;
}
#line 1573 "parser/epparser.c"
        break;
      case 90: /* if_header ::= if_start LPAREN lexpr RPAREN */
      case 99: /* while_header ::= while_start LPAREN lexpr RPAREN */ yytestcase(yyruleno==99);
#line 399 "parser/epparser.lemon"
{
    ps->gen << "if " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data << "):" << std::endl;
    ps->gen.indent();
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1583 "parser/epparser.c"
        break;
      case 92: /* elif_start ::= ELSE IF */
#line 407 "parser/epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen.unindent(false);
    ps->gen << yygotominor.yy0->data << " = EUDElseIf()" << std::endl;
}
#line 1592 "parser/epparser.c"
        break;
      case 93: /* elif_header ::= elif_start LPAREN lexpr RPAREN */
#line 413 "parser/epparser.lemon"
{
    ps->gen << "if " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data <<"):" << std::endl;
    ps->gen.indent();
}
#line 1600 "parser/epparser.c"
        break;
      case 95: /* else_header ::= ELSE */
#line 420 "parser/epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "if EUDElse()():" << std::endl;
    ps->gen.indent();
}
#line 1609 "parser/epparser.c"
        break;
      case 96: /* if_stmt ::= if_block */
      case 97: /* if_stmt ::= if_block else_header stmt */ yytestcase(yyruleno==97);
#line 426 "parser/epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndIf()" << std::endl;
}
#line 1618 "parser/epparser.c"
        break;
      case 98: /* while_start ::= WHILE */
#line 438 "parser/epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDWhile()" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1627 "parser/epparser.c"
        break;
      case 100: /* while_stmt ::= while_header stmt */
#line 450 "parser/epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndWhile()" << std::endl;
}
#line 1635 "parser/epparser.c"
        break;
      case 101: /* foreach_header ::= FOR LPAREN nameList COLON exprList RPAREN */
#line 456 "parser/epparser.lemon"
{
    ps->closure.pushScope();
    commaListIter(yymsp[-3].minor.yy0->data, [&](std::string& s) {
        ps->closure.defVariable(s);
    });
    ps->gen << "for " << yymsp[-3].minor.yy0->data << " in " << yymsp[-1].minor.yy0->data << ":" << std::endl;
    ps->gen.indent();
}
#line 1647 "parser/epparser.c"
        break;
      case 103: /* continue_stmt ::= CONTINUE SEMICOLON */
#line 472 "parser/epparser.lemon"
{
    ps->gen << "EUDContinue()" << std::endl;
}
#line 1654 "parser/epparser.c"
        break;
      case 104: /* break_stmt ::= BREAK SEMICOLON */
#line 476 "parser/epparser.lemon"
{
    ps->gen << "EUDBreak()" << std::endl;
}
#line 1661 "parser/epparser.c"
        break;
      case 105: /* return_stmt ::= RETURN SEMICOLON */
#line 483 "parser/epparser.lemon"
{
    ps->gen << "EUDReturn()" << std::endl;
}
#line 1668 "parser/epparser.c"
        break;
      case 106: /* return_stmt ::= RETURN exprList SEMICOLON */
#line 487 "parser/epparser.lemon"
{
    ps->gen << "EUDReturn(" << yymsp[-1].minor.yy0->data << ")" << std::endl;
    delete yymsp[-1].minor.yy0;
}
#line 1676 "parser/epparser.c"
        break;
      case 107: /* lexpr ::= CONDITIONNAME LPAREN fArgs RPAREN */
#line 495 "parser/epparser.lemon"
{
    yymsp[-3].minor.yy0->data = yymsp[-3].minor.yy0->data + "(" + yymsp[-1].minor.yy0->data + ")";
    delete yymsp[-1].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0, ps->gen);
}
#line 1685 "parser/epparser.c"
        break;
      case 108: /* lexpr ::= CONDITIONNAME LPAREN RPAREN */
#line 501 "parser/epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + "()";
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0, ps->gen);
}
#line 1693 "parser/epparser.c"
        break;
      case 109: /* action ::= ACTIONNAME LPAREN fArgs RPAREN SEMICOLON */
#line 506 "parser/epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[-4].minor.yy0);
    yygotominor.yy0->data =  yymsp[-4].minor.yy0->data + "(" + yymsp[-2].minor.yy0->data + ")";
    delete yymsp[-4].minor.yy0; delete yymsp[-2].minor.yy0;
}
#line 1702 "parser/epparser.c"
        break;
      case 110: /* actions ::= action action */
      case 111: /* actions ::= actions action */ yytestcase(yyruleno==111);
#line 512 "parser/epparser.lemon"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
    yymsp[-1].minor.yy0->data += ",\n" + yymsp[0].minor.yy0->data;
    delete yymsp[0].minor.yy0;
}
#line 1712 "parser/epparser.c"
        break;
      case 112: /* actionStmt ::= action */
#line 524 "parser/epparser.lemon"
{
    ps->gen << "DoActions(" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1720 "parser/epparser.c"
        break;
      case 113: /* actionStmt ::= actions */
#line 529 "parser/epparser.lemon"
{
    ps->gen << "DoActions([" << std::endl;
    ps->gen.indent();
    ps->gen << yymsp[0].minor.yy0->data << std::endl;
    ps->gen.unindent(false);
    ps->gen << "])" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1732 "parser/epparser.c"
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
      /* (91) if_block ::= if_header stmt */ yytestcase(yyruleno==91);
      /* (94) if_block ::= if_block elif_header stmt */ yytestcase(yyruleno==94);
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
#line 1824 "parser/epparser.c"
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
#line 543 "parser/epparser.lemon"


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
#line 2056 "parser/epparser.c"
