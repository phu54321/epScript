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
#define YYNOCODE 106
#define YYACTIONTYPE unsigned short int
#define ParseTOKENTYPE Token*
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  int yy211;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL  ParserStruct* ps ;
#define ParseARG_PDECL , ParserStruct* ps 
#define ParseARG_FETCH  ParserStruct* ps  = yypParser->ps 
#define ParseARG_STORE yypParser->ps  = ps 
#define YYNSTATE 247
#define YYNRULE 123
#define YYERRORSYMBOL 57
#define YYERRSYMDT yy211
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
#define YY_ACTTAB_COUNT (796)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   152,   48,   46,   44,   45,   43,  156,  224,  222,   44,
 /*    10 */    45,   43,  235,  233,  232,    8,  155,   25,  223,  221,
 /*    20 */   151,  219,  218,  217,  216,  215,  214,   62,  303,   19,
 /*    30 */    20,  240,  148,  146,  150,  115,   94,  113,    5,   50,
 /*    40 */   155,  152,   26,  110,    3,    2,   54,   53,  224,  222,
 /*    50 */   111,    4,    1,  175,  233,  232,    8,  117,  206,  223,
 /*    60 */   221,  151,  219,  218,  217,  216,  215,  214,  241,  303,
 /*    70 */   183,  155,   27,   49,  146,  140,  115,   94,  113,    5,
 /*    80 */    50,   26,  152,  155,  110,    3,    2,   54,   53,  224,
 /*    90 */   222,  155,  116,   26,  172,  233,  232,    8,  238,  187,
 /*   100 */   223,  221,  151,  219,  218,  217,  216,  215,  214,  182,
 /*   110 */   239,   19,   20,   56,   24,  146,  236,  115,   94,  113,
 /*   120 */     5,   50,  237,  152,  168,  110,    3,    2,   54,   53,
 /*   130 */   224,  222,  148,   23,  114,  169,  233,  232,    8,  234,
 /*   140 */   176,  223,  221,  151,  219,  218,  217,  216,  215,  214,
 /*   150 */   371,    9,   19,   20,   51,  220,  146,  149,  115,   94,
 /*   160 */   113,    5,   50,   26,  152,  304,  110,    3,    2,   54,
 /*   170 */    53,  224,  222,  147,  211,   12,  167,  233,  232,    8,
 /*   180 */   144,  173,  223,  221,  151,  219,  218,  217,  216,  215,
 /*   190 */   214,  178,  143,   19,   20,  142,  141,  146,  139,  115,
 /*   200 */    94,  113,    5,   50,  155,  152,   21,  110,    3,    2,
 /*   210 */    54,   53,  224,  222,  210,  136,  133,  160,  233,  232,
 /*   220 */     8,  135,  170,  223,  221,  151,  219,  218,  217,  216,
 /*   230 */   215,  214,  187,  205,  132,  129,  204,  130,  146,  203,
 /*   240 */   115,   94,  113,    5,   50,  127,  101,  126,  110,    3,
 /*   250 */     2,   54,   53,  224,  222,  202,   20,   10,   22,  158,
 /*   260 */    61,  190,  119,    7,  223,  221,  151,  219,  218,  217,
 /*   270 */   216,  215,  214,  188,   58,  186,  185,   28,   16,  146,
 /*   280 */   180,  115,   94,  113,    5,   50,   15,  212,  166,  110,
 /*   290 */     3,    2,   54,   53,  224,  222,  174,   14,   55,  165,
 /*   300 */   213,   60,   26,  227,   11,  223,  221,  151,  219,  218,
 /*   310 */   217,  216,  215,  214,  164,  102,  163,  100,  159,  228,
 /*   320 */   146,  239,  115,   94,  113,    5,   50,   83,  229,  226,
 /*   330 */   110,    3,    2,   54,   53,  118,  179,   98,   34,   32,
 /*   340 */    31,   30,   29,   33,   39,   38,   40,   42,   41,   48,
 /*   350 */    46,   44,   45,   43,   18,   39,   38,   40,   42,   41,
 /*   360 */    48,   46,   44,   45,   43,   96,   93,   37,   36,   91,
 /*   370 */   145,  162,  104,   35,  209,   87,  112,  161,  208,   63,
 /*   380 */    47,   17,  372,  146,   86,   89,   99,  372,  372,  138,
 /*   390 */   137,  134,  131,  128,   37,   36,  372,  372,  372,  372,
 /*   400 */    35,  209,   87,  372,  124,  372,  372,   47,   40,   42,
 /*   410 */    41,   48,   46,   44,   45,   43,  138,  137,  134,  131,
 /*   420 */   128,   37,   36,  372,  120,  372,  372,   35,  209,   87,
 /*   430 */   372,  124,   97,   67,   47,  189,  372,  146,  372,  372,
 /*   440 */   372,  192,  372,  138,  137,  134,  131,  128,   37,   36,
 /*   450 */   372,  145,  372,  372,   35,  209,   87,  372,  372,  372,
 /*   460 */    68,   47,  123,  121,  146,  372,  372,  145,  192,  372,
 /*   470 */   138,  137,  134,  131,  128,   88,   63,  372,  225,  372,
 /*   480 */   146,  195,  372,  230,   39,   38,   40,   42,   41,   48,
 /*   490 */    46,   44,   45,   43,   59,   57,  177,  247,  171,  109,
 /*   500 */   181,  108,  107,   13,  372,  104,  120,  372,  372,  372,
 /*   510 */    88,  372,  372,  225,  106,   67,  105,  372,  229,  146,
 /*   520 */   372,  372,  372,  372,  157,   88,  372,  154,  225,   59,
 /*   530 */    57,  177,  231,  171,  109,  372,  108,  107,   13,  372,
 /*   540 */   104,  145,   52,   57,   59,   57,  177,  372,  171,  109,
 /*   550 */    66,  108,  107,   13,  146,  104,  372,  372,   39,   38,
 /*   560 */    40,   42,   41,   48,   46,   44,   45,   43,   37,   36,
 /*   570 */   372,  372,  372,  372,   35,  209,   87,  207,  372,  372,
 /*   580 */   372,   47,   42,   41,   48,   46,   44,   45,   43,  372,
 /*   590 */   138,  137,  134,  131,  128,   39,   38,   40,   42,   41,
 /*   600 */    48,   46,   44,   45,   43,   38,   40,   42,   41,   48,
 /*   610 */    46,   44,   45,   43,  246,  245,  244,  243,  242,  372,
 /*   620 */   153,    6,  372,  145,  372,  372,  372,  372,  372,  145,
 /*   630 */   372,  372,   68,  372,  123,  103,  146,  120,   68,  120,
 /*   640 */   123,  122,  146,  372,  372,  184,   67,   95,   67,  372,
 /*   650 */   146,  372,  146,  120,  372,  120,  372,  372,  372,  372,
 /*   660 */   145,   92,   67,   90,   67,  145,  146,  372,  146,   68,
 /*   670 */   372,  191,  145,  146,   63,  145,  372,  372,  146,  125,
 /*   680 */   372,   63,  145,  372,   63,  146,  194,  372,  146,  193,
 /*   690 */   145,   63,  145,  372,  372,  146,   82,  372,  145,   63,
 /*   700 */   372,   63,  372,  146,   81,  146,   80,   84,  372,  372,
 /*   710 */   145,  146,  145,  145,  372,  145,  372,  372,  145,   65,
 /*   720 */   145,   85,  201,  146,  200,  146,  146,  199,  146,   79,
 /*   730 */   145,  146,  372,  146,  372,  372,  372,  372,  145,   78,
 /*   740 */   145,  145,  372,  146,  372,  372,  145,   77,  372,   75,
 /*   750 */    76,  146,  145,  146,  146,  198,  372,  145,  372,  146,
 /*   760 */   145,  197,  145,  145,  372,  146,  196,  372,  145,   74,
 /*   770 */   146,   73,   72,  146,  145,  146,  146,   71,  372,  145,
 /*   780 */   372,  146,  145,   70,  372,  372,  372,  146,   69,  372,
 /*   790 */   372,   64,  146,  372,  372,  146,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    57,   18,   19,   20,   21,   22,   26,   64,   65,   20,
 /*    10 */    21,   22,   69,   70,   71,   72,    1,    2,   75,   76,
 /*    20 */    77,   78,   79,   80,   81,   82,   83,   28,   31,    3,
 /*    30 */     4,   26,   35,   90,   37,   92,   93,   94,   95,   96,
 /*    40 */     1,   57,    1,  100,  101,  102,  103,  104,   64,   65,
 /*    50 */    97,   98,   99,   69,   70,   71,   72,    1,   32,   75,
 /*    60 */    76,   77,   78,   79,   80,   81,   82,   83,   29,   31,
 /*    70 */    29,    1,    2,   35,   90,   37,   92,   93,   94,   95,
 /*    80 */    96,    1,   57,    1,  100,  101,  102,  103,  104,   64,
 /*    90 */    65,    1,   36,    1,   69,   70,   71,   72,   26,   29,
 /*   100 */    75,   76,   77,   78,   79,   80,   81,   82,   83,   29,
 /*   110 */    26,    3,    4,    1,    2,   90,   32,   92,   93,   94,
 /*   120 */    95,   96,   32,   57,   32,  100,  101,  102,  103,  104,
 /*   130 */    64,   65,   35,   51,   37,   69,   70,   71,   72,   29,
 /*   140 */    32,   75,   76,   77,   78,   79,   80,   81,   82,   83,
 /*   150 */    59,   60,    3,    4,   31,   29,   90,   26,   92,   93,
 /*   160 */    94,   95,   96,    1,   57,   31,  100,  101,  102,  103,
 /*   170 */   104,   64,   65,   26,   36,   31,   69,   70,   71,   72,
 /*   180 */    35,   32,   75,   76,   77,   78,   79,   80,   81,   82,
 /*   190 */    83,   29,   35,    3,    4,   25,   36,   90,   26,   92,
 /*   200 */    93,   94,   95,   96,    1,   57,   31,  100,  101,  102,
 /*   210 */   103,  104,   64,   65,   36,   31,   31,   69,   70,   71,
 /*   220 */    72,   38,   32,   75,   76,   77,   78,   79,   80,   81,
 /*   230 */    82,   83,   29,   32,   38,   38,   32,   31,   90,   32,
 /*   240 */    92,   93,   94,   95,   96,   31,   57,   38,  100,  101,
 /*   250 */   102,  103,  104,   64,   65,   32,    4,   31,    1,   70,
 /*   260 */    71,   32,   35,   74,   75,   76,   77,   78,   79,   80,
 /*   270 */    81,   82,   83,   32,   35,   25,   36,    2,   31,   90,
 /*   280 */    26,   92,   93,   94,   95,   96,   31,   57,   29,  100,
 /*   290 */   101,  102,  103,  104,   64,   65,   47,   31,   31,   29,
 /*   300 */    70,   71,    1,   73,   31,   75,   76,   77,   78,   79,
 /*   310 */    80,   81,   82,   83,   29,   32,   29,   66,   34,   73,
 /*   320 */    90,   26,   92,   93,   94,   95,   96,   66,   34,   73,
 /*   330 */   100,  101,  102,  103,  104,   25,   92,   84,    7,    8,
 /*   340 */     9,   10,   11,   12,   13,   14,   15,   16,   17,   18,
 /*   350 */    19,   20,   21,   22,    5,   13,   14,   15,   16,   17,
 /*   360 */    18,   19,   20,   21,   22,   66,   26,   18,   19,   66,
 /*   370 */    77,  103,   56,   24,   25,   26,   48,  103,   36,   86,
 /*   380 */    31,    5,  105,   90,   91,   66,   66,  105,  105,   40,
 /*   390 */    41,   42,   43,   44,   18,   19,  105,  105,  105,  105,
 /*   400 */    24,   25,   26,  105,   55,  105,  105,   31,   15,   16,
 /*   410 */    17,   18,   19,   20,   21,   22,   40,   41,   42,   43,
 /*   420 */    44,   18,   19,  105,   77,  105,  105,   24,   25,   26,
 /*   430 */   105,   55,   85,   86,   31,   32,  105,   90,  105,  105,
 /*   440 */   105,   38,  105,   40,   41,   42,   43,   44,   18,   19,
 /*   450 */   105,   77,  105,  105,   24,   25,   26,  105,  105,  105,
 /*   460 */    86,   31,   88,   89,   90,  105,  105,   77,   38,  105,
 /*   470 */    40,   41,   42,   43,   44,   26,   86,  105,   29,  105,
 /*   480 */    90,   91,  105,   34,   13,   14,   15,   16,   17,   18,
 /*   490 */    19,   20,   21,   22,   45,   46,   47,    0,   49,   50,
 /*   500 */    29,   52,   53,   54,  105,   56,   77,  105,  105,  105,
 /*   510 */    26,  105,  105,   29,   85,   86,   87,  105,   34,   90,
 /*   520 */   105,  105,  105,  105,   27,   26,  105,   30,   29,   45,
 /*   530 */    46,   47,   33,   49,   50,  105,   52,   53,   54,  105,
 /*   540 */    56,   77,   45,   46,   45,   46,   47,  105,   49,   50,
 /*   550 */    86,   52,   53,   54,   90,   56,  105,  105,   13,   14,
 /*   560 */    15,   16,   17,   18,   19,   20,   21,   22,   18,   19,
 /*   570 */   105,  105,  105,  105,   24,   25,   26,   32,  105,  105,
 /*   580 */   105,   31,   16,   17,   18,   19,   20,   21,   22,  105,
 /*   590 */    40,   41,   42,   43,   44,   13,   14,   15,   16,   17,
 /*   600 */    18,   19,   20,   21,   22,   14,   15,   16,   17,   18,
 /*   610 */    19,   20,   21,   22,   61,   62,   63,   64,   65,  105,
 /*   620 */    67,   68,  105,   77,  105,  105,  105,  105,  105,   77,
 /*   630 */   105,  105,   86,  105,   88,   89,   90,   77,   86,   77,
 /*   640 */    88,   89,   90,  105,  105,   85,   86,   85,   86,  105,
 /*   650 */    90,  105,   90,   77,  105,   77,  105,  105,  105,  105,
 /*   660 */    77,   85,   86,   85,   86,   77,   90,  105,   90,   86,
 /*   670 */   105,   88,   77,   90,   86,   77,  105,  105,   90,   91,
 /*   680 */   105,   86,   77,  105,   86,   90,   91,  105,   90,   91,
 /*   690 */    77,   86,   77,  105,  105,   90,   91,  105,   77,   86,
 /*   700 */   105,   86,  105,   90,   91,   90,   91,   86,  105,  105,
 /*   710 */    77,   90,   77,   77,  105,   77,  105,  105,   77,   86,
 /*   720 */    77,   86,   86,   90,   86,   90,   90,   86,   90,   86,
 /*   730 */    77,   90,  105,   90,  105,  105,  105,  105,   77,   86,
 /*   740 */    77,   77,  105,   90,  105,  105,   77,   86,  105,   86,
 /*   750 */    86,   90,   77,   90,   90,   86,  105,   77,  105,   90,
 /*   760 */    77,   86,   77,   77,  105,   90,   86,  105,   77,   86,
 /*   770 */    90,   86,   86,   90,   77,   90,   90,   86,  105,   77,
 /*   780 */   105,   90,   77,   86,  105,  105,  105,   90,   86,  105,
 /*   790 */   105,   86,   90,  105,  105,   90,
};
#define YY_SHIFT_USE_DFLT (-21)
#define YY_SHIFT_COUNT (157)
#define YY_SHIFT_MIN   (-20)
#define YY_SHIFT_MAX   (591)
static const short yy_shift_ofst[] = {
 /*     0 */   -21,  499,  499,  499,  499,  499,  499,  484,  449,  497,
 /*    10 */   403,  430,  430,  550,  349,  349,  349,  376,  376,  349,
 /*    20 */   349,  349,  430,  550,  550,  550,  550,  550,  550,  550,
 /*    30 */   550,  550,  550,  550,  550,  550,  550,  550,  550,  550,
 /*    40 */   550,  550,  550,  550,  550,  550,  550,  550,  550,  550,
 /*    50 */   328,   84,  295,  316,  316,  295,  340,  295,  310,  295,
 /*    60 */   294,  294,  295,  331,  471,  545,  342,  582,  582,  582,
 /*    70 */   582,  582,  582,  582,  582,  591,  393,  566,  -17,  -17,
 /*    80 */   190,  149,  108,   70,  -11,  -11,   26,   38,   -3,  203,
 /*    90 */    92,   82,  162,   97,  112,   80,   15,   41,   56,   90,
 /*   100 */    39,  284,  287,  283,  273,  285,  301,  270,  259,  267,
 /*   110 */   266,  255,  249,  247,  254,  275,  240,  250,  160,  239,
 /*   120 */   227,  241,  229,  257,  226,  252,  223,  209,  214,  207,
 /*   130 */   197,  206,  204,  196,  185,  201,  183,  184,  175,  134,
 /*   140 */   172,  178,  160,  170,  157,  145,  144,  138,  147,  134,
 /*   150 */   131,  126,  110,  123,   72,    5,   -1,  -20,
};
#define YY_REDUCE_USE_DFLT (-58)
#define YY_REDUCE_COUNT (62)
#define YY_REDUCE_MIN   (-57)
#define YY_REDUCE_MAX   (705)
static const short yy_reduce_ofst[] = {
 /*     0 */    91,  148,  107,   66,   25,  -16,  -57,  230,  189,  553,
 /*    10 */   552,  546,  374,  429,  615,  613,  605,  598,  595,  588,
 /*    20 */   390,  293,  583,  578,  576,  562,  560,  347,  705,  702,
 /*    30 */   697,  691,  686,  685,  683,  680,  675,  669,  664,  663,
 /*    40 */   661,  653,  643,  641,  638,  636,  635,  633,  621,  464,
 /*    50 */   -47,  320,  319,  274,  268,  303,  244,  299,  253,  261,
 /*    60 */   256,  246,  251,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   248,  370,  370,  370,  370,  370,  370,  370,  370,  370,
 /*    10 */   370,  301,  301,  292,  370,  370,  370,  370,  370,  370,
 /*    20 */   370,  370,  370,  370,  370,  370,  370,  370,  370,  370,
 /*    30 */   370,  370,  370,  370,  370,  370,  370,  370,  370,  370,
 /*    40 */   370,  370,  370,  370,  370,  370,  370,  370,  370,  370,
 /*    50 */   353,  370,  370,  369,  368,  370,  370,  370,  370,  370,
 /*    60 */   370,  370,  370,  370,  370,  370,  370,  290,  298,  331,
 /*    70 */   330,  329,  328,  327,  326,  321,  322,  320,  319,  318,
 /*    80 */   370,  370,  370,  370,  313,  314,  370,  295,  339,  370,
 /*    90 */   370,  370,  370,  339,  370,  370,  370,  370,  370,  370,
 /*   100 */   370,  370,  370,  370,  370,  370,  293,  370,  370,  370,
 /*   110 */   370,  370,  352,  370,  370,  342,  370,  370,  284,  370,
 /*   120 */   306,  370,  370,  302,  370,  333,  370,  370,  370,  370,
 /*   130 */   370,  370,  370,  370,  370,  370,  370,  370,  370,  296,
 /*   140 */   370,  370,  370,  370,  370,  306,  370,  370,  370,  341,
 /*   150 */   370,  370,  370,  370,  370,  370,  370,  370,  281,  268,
 /*   160 */   354,  367,  366,  365,  362,  361,  360,  359,  358,  357,
 /*   170 */   356,  355,  351,  350,  349,  348,  347,  346,  345,  343,
 /*   180 */   341,  344,  338,  337,  291,  288,  285,  336,  305,  364,
 /*   190 */   363,  300,  299,  335,  334,  332,  325,  324,  323,  317,
 /*   200 */   316,  315,  312,  311,  310,  309,  308,  307,  297,  294,
 /*   210 */   289,  340,  283,  282,  280,  279,  278,  277,  276,  275,
 /*   220 */   274,  273,  272,  271,  270,  269,  267,  266,  265,  263,
 /*   230 */   264,  262,  261,  260,  259,  258,  257,  256,  255,  286,
 /*   240 */   287,  254,  253,  252,  251,  250,  249,
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
  "lvalue",        "lvalueList_nonEmpty",  "if_start",      "if_header",   
  "if_block",      "elif_start",    "elif_header",   "else_header", 
  "while_start",   "while_header",  "foreach_header",  "action",      
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
 /*  36 */ "bodyStmtList ::= bodyStmtList error",
 /*  37 */ "numList_nonEmpty ::= NUMBER",
 /*  38 */ "numList_nonEmpty ::= numList_nonEmpty COMMA NUMBER",
 /*  39 */ "nameList_nonEmpty ::= NAME",
 /*  40 */ "nameList_nonEmpty ::= nameList_nonEmpty COMMA NAME",
 /*  41 */ "exprList_nonEmpty ::= funcexpr LSQBRACKET LSQBRACKET numList_nonEmpty RSQBRACKET RSQBRACKET",
 /*  42 */ "expr ::= funcexpr LSQBRACKET LSQBRACKET NUMBER RSQBRACKET RSQBRACKET",
 /*  43 */ "exprList_nonEmpty ::= expr",
 /*  44 */ "exprList_nonEmpty ::= exprList_nonEmpty COMMA exprList_nonEmpty",
 /*  45 */ "exprList ::=",
 /*  46 */ "exprList ::= exprList_nonEmpty",
 /*  47 */ "expr ::= NUMBER",
 /*  48 */ "expr ::= NAME",
 /*  49 */ "expr ::= NAME PERIOD NAME",
 /*  50 */ "expr ::= NAME LSQBRACKET expr RSQBRACKET",
 /*  51 */ "fArgs_nonEmpty ::= expr",
 /*  52 */ "fArgs_nonEmpty ::= STRING",
 /*  53 */ "fArgs_nonEmpty ::= fArgs_nonEmpty COMMA fArgs_nonEmpty",
 /*  54 */ "fArgs ::=",
 /*  55 */ "fArgs ::= fArgs_nonEmpty",
 /*  56 */ "funcName ::= NAME",
 /*  57 */ "funcName ::= NAME PERIOD NAME",
 /*  58 */ "funcexpr ::= funcName LPAREN fArgs RPAREN",
 /*  59 */ "expr ::= funcexpr",
 /*  60 */ "expr ::= LPAREN expr RPAREN",
 /*  61 */ "expr ::= L2V LPAREN lexpr RPAREN",
 /*  62 */ "expr ::= MAPSTRING LPAREN STRING RPAREN",
 /*  63 */ "expr ::= UNIT LPAREN STRING RPAREN",
 /*  64 */ "expr ::= SWITCH LPAREN STRING RPAREN",
 /*  65 */ "expr ::= LOCATION LPAREN STRING RPAREN",
 /*  66 */ "expr ::= expr PLUS expr",
 /*  67 */ "expr ::= expr MINUS expr",
 /*  68 */ "expr ::= expr MULTIPLY expr",
 /*  69 */ "expr ::= expr DIVIDE expr",
 /*  70 */ "expr ::= expr MOD expr",
 /*  71 */ "expr ::= expr LSHIFT expr",
 /*  72 */ "expr ::= expr RSHIFT expr",
 /*  73 */ "expr ::= expr BITAND expr",
 /*  74 */ "expr ::= expr BITOR expr",
 /*  75 */ "expr ::= expr BITXOR expr",
 /*  76 */ "expr ::= PLUS expr",
 /*  77 */ "expr ::= MINUS expr",
 /*  78 */ "expr ::= BITNOT expr",
 /*  79 */ "lexpr ::= expr EQ expr",
 /*  80 */ "lexpr ::= expr NE expr",
 /*  81 */ "lexpr ::= expr LE expr",
 /*  82 */ "lexpr ::= expr LT expr",
 /*  83 */ "lexpr ::= expr GE expr",
 /*  84 */ "lexpr ::= expr GT expr",
 /*  85 */ "lexpr ::= lexpr LAND lexpr",
 /*  86 */ "lexpr ::= lexpr LOR lexpr",
 /*  87 */ "lexpr ::= LNOT lexpr",
 /*  88 */ "lexpr ::= LNOT LNOT lexpr",
 /*  89 */ "vdef_stmt ::= VAR nameList_nonEmpty SEMICOLON",
 /*  90 */ "vdefAssign_stmt ::= VAR nameList_nonEmpty ASSIGN exprList_nonEmpty SEMICOLON",
 /*  91 */ "cdef_stmt ::= CONST nameList_nonEmpty ASSIGN exprList_nonEmpty SEMICOLON",
 /*  92 */ "lvalue ::= NAME",
 /*  93 */ "lvalue ::= NAME LSQBRACKET NAME RSQBRACKET",
 /*  94 */ "lvalue ::= NAME PERIOD NAME",
 /*  95 */ "lvalueList_nonEmpty ::= lvalue",
 /*  96 */ "lvalueList_nonEmpty ::= lvalueList_nonEmpty COMMA lvalue",
 /*  97 */ "assign_stmt ::= lvalue ASSIGN expr SEMICOLON",
 /*  98 */ "assign_stmt ::= lvalueList_nonEmpty ASSIGN exprList_nonEmpty SEMICOLON",
 /*  99 */ "if_start ::= IF",
 /* 100 */ "if_header ::= if_start LPAREN lexpr RPAREN",
 /* 101 */ "if_block ::= if_header stmt",
 /* 102 */ "elif_start ::= ELSE IF",
 /* 103 */ "elif_header ::= elif_start LPAREN lexpr RPAREN",
 /* 104 */ "if_block ::= if_block elif_header stmt",
 /* 105 */ "else_header ::= ELSE",
 /* 106 */ "if_stmt ::= if_block",
 /* 107 */ "if_stmt ::= if_block else_header stmt",
 /* 108 */ "while_start ::= WHILE",
 /* 109 */ "while_header ::= while_start LPAREN lexpr RPAREN",
 /* 110 */ "while_stmt ::= while_header stmt",
 /* 111 */ "foreach_header ::= FOR LPAREN nameList_nonEmpty COLON exprList_nonEmpty RPAREN",
 /* 112 */ "foreach_stmt ::= foreach_header stmt",
 /* 113 */ "continue_stmt ::= CONTINUE SEMICOLON",
 /* 114 */ "break_stmt ::= BREAK SEMICOLON",
 /* 115 */ "return_stmt ::= RETURN exprList SEMICOLON",
 /* 116 */ "lexpr ::= CONDITIONNAME LPAREN fArgs RPAREN",
 /* 117 */ "lexpr ::= CONDITIONNAME LPAREN RPAREN",
 /* 118 */ "action ::= ACTIONNAME LPAREN fArgs RPAREN SEMICOLON",
 /* 119 */ "actions ::= action action",
 /* 120 */ "actions ::= actions action",
 /* 121 */ "actionStmt ::= action",
 /* 122 */ "actionStmt ::= actions",
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
#line 31 "parser\\epparser.lemon"
 delete (yypminor->yy0); 
#line 724 "parser\\epparser.c"
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
  { 86, 4 },
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
  { 92, 1 },
  { 92, 4 },
  { 92, 3 },
  { 93, 1 },
  { 93, 3 },
  { 76, 4 },
  { 76, 4 },
  { 94, 1 },
  { 95, 4 },
  { 96, 2 },
  { 97, 2 },
  { 98, 4 },
  { 96, 3 },
  { 99, 1 },
  { 79, 1 },
  { 79, 3 },
  { 100, 1 },
  { 101, 4 },
  { 80, 2 },
  { 102, 6 },
  { 81, 2 },
  { 82, 2 },
  { 83, 2 },
  { 71, 3 },
  { 91, 4 },
  { 91, 3 },
  { 103, 5 },
  { 104, 2 },
  { 104, 2 },
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
#line 66 "parser\\epparser.lemon"
{
    commaListIter(yymsp[-1].minor.yy0->data, [&](std::string varname) {
        funcNamePreprocess(varname);
        if(!ps->closure.defFunction(varname)) {
            throw_error(8118, ("Importing already-declared function " + varname));
        }
        else ps->gen << "from " << yymsp[-3].minor.yy0->data << " import " << varname << std::endl;
    });
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1151 "parser\\epparser.c"
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
#line 1164 "parser\\epparser.c"
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
#line 1183 "parser\\epparser.c"
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
#line 1194 "parser\\epparser.c"
        break;
      case 11: /* fdef_chunk ::= function_header stmt */
      case 112: /* foreach_stmt ::= foreach_header stmt */ yytestcase(yyruleno==112);
#line 112 "parser\\epparser.lemon"
{
    ps->gen.unindent(true);
    ps->closure.popScope();
}
#line 1203 "parser\\epparser.c"
        break;
      case 12: /* stmt ::= error SEMICOLON */
#line 119 "parser\\epparser.lemon"
{ throw_error(6974, "Error while parsing statement"); }
#line 1208 "parser\\epparser.c"
        break;
      case 15: /* lbracket ::= LBRACKET */
#line 125 "parser\\epparser.lemon"
{ ps->closure.pushScope(); }
#line 1213 "parser\\epparser.c"
        break;
      case 16: /* rbracket ::= RBRACKET */
#line 126 "parser\\epparser.lemon"
{ ps->closure.popScope(); }
#line 1218 "parser\\epparser.c"
        break;
      case 17: /* stmt ::= lbracket RBRACKET */
#line 128 "parser\\epparser.lemon"
{
    ps->gen << "pass" << std::endl;
    ps->closure.popScope();
}
#line 1226 "parser\\epparser.c"
        break;
      case 21: /* stmt ::= lbracket error RBRACKET */
#line 135 "parser\\epparser.lemon"
{
    throw_error(6298, "Block not terminated properly.");
    ps->closure.popScope();
}
#line 1234 "parser\\epparser.c"
        break;
      case 27: /* bodyStmt ::= funcexpr SEMICOLON */
#line 145 "parser\\epparser.lemon"
{ ps->gen << yymsp[-1].minor.yy0->data << std::endl; }
#line 1239 "parser\\epparser.c"
        break;
      case 36: /* bodyStmtList ::= bodyStmtList error */
#line 156 "parser\\epparser.lemon"
{
    throw_error(8510, "Incomplete statement");
}
#line 1246 "parser\\epparser.c"
        break;
      case 37: /* numList_nonEmpty ::= NUMBER */
      case 39: /* nameList_nonEmpty ::= NAME */ yytestcase(yyruleno==39);
      case 43: /* exprList_nonEmpty ::= expr */ yytestcase(yyruleno==43);
      case 46: /* exprList ::= exprList_nonEmpty */ yytestcase(yyruleno==46);
      case 47: /* expr ::= NUMBER */ yytestcase(yyruleno==47);
      case 51: /* fArgs_nonEmpty ::= expr */ yytestcase(yyruleno==51);
      case 52: /* fArgs_nonEmpty ::= STRING */ yytestcase(yyruleno==52);
      case 55: /* fArgs ::= fArgs_nonEmpty */ yytestcase(yyruleno==55);
      case 59: /* expr ::= funcexpr */ yytestcase(yyruleno==59);
      case 88: /* lexpr ::= LNOT LNOT lexpr */ yytestcase(yyruleno==88);
      case 95: /* lvalueList_nonEmpty ::= lvalue */ yytestcase(yyruleno==95);
#line 162 "parser\\epparser.lemon"
{ yygotominor.yy0 = yymsp[0].minor.yy0; }
#line 1261 "parser\\epparser.c"
        break;
      case 38: /* numList_nonEmpty ::= numList_nonEmpty COMMA NUMBER */
      case 40: /* nameList_nonEmpty ::= nameList_nonEmpty COMMA NAME */ yytestcase(yyruleno==40);
      case 96: /* lvalueList_nonEmpty ::= lvalueList_nonEmpty COMMA lvalue */ yytestcase(yyruleno==96);
#line 163 "parser\\epparser.lemon"
{ yygotominor.yy0 = commaConcat(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1268 "parser\\epparser.c"
        break;
      case 41: /* exprList_nonEmpty ::= funcexpr LSQBRACKET LSQBRACKET numList_nonEmpty RSQBRACKET RSQBRACKET */
#line 167 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "_SRET(" + yymsp[-5].minor.yy0->data + ", [" + yymsp[-2].minor.yy0->data + "])";
    delete yymsp[-5].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1277 "parser\\epparser.c"
        break;
      case 42: /* expr ::= funcexpr LSQBRACKET LSQBRACKET NUMBER RSQBRACKET RSQBRACKET */
#line 174 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-5].minor.yy0->data + "[" + yymsp[-2].minor.yy0->data + "]";
    delete yymsp[-5].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1286 "parser\\epparser.c"
        break;
      case 44: /* exprList_nonEmpty ::= exprList_nonEmpty COMMA exprList_nonEmpty */
#line 182 "parser\\epparser.lemon"
{ yygotominor.yy0 = new Token((yymsp[-2].minor.yy0->data) + ", " + (yymsp[0].minor.yy0->data), yymsp[0].minor.yy0); delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1291 "parser\\epparser.c"
        break;
      case 45: /* exprList ::= */
      case 54: /* fArgs ::= */ yytestcase(yyruleno==54);
#line 184 "parser\\epparser.lemon"
{ yygotominor.yy0 = genEmpty(); }
#line 1297 "parser\\epparser.c"
        break;
      case 48: /* expr ::= NAME */
#line 189 "parser\\epparser.lemon"
{
    checkIsRValue(yymsp[0].minor.yy0->data);
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1305 "parser\\epparser.c"
        break;
      case 49: /* expr ::= NAME PERIOD NAME */
#line 194 "parser\\epparser.lemon"
{
    checkIsConstant(yymsp[-2].minor.yy0->data);
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + "." + yymsp[0].minor.yy0->data;
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1315 "parser\\epparser.c"
        break;
      case 50: /* expr ::= NAME LSQBRACKET expr RSQBRACKET */
#line 201 "parser\\epparser.lemon"
{
    checkIsConstant(yymsp[-3].minor.yy0->data);
    yymsp[-3].minor.yy0->data = yymsp[-3].minor.yy0->data + "[" + yymsp[-1].minor.yy0->data + "]";
    delete yymsp[-1].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 1325 "parser\\epparser.c"
        break;
      case 53: /* fArgs_nonEmpty ::= fArgs_nonEmpty COMMA fArgs_nonEmpty */
#line 211 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data;
    yymsp[-2].minor.yy0->type = TOKEN_TEMP;
    yygotominor.yy0 = yymsp[-2].minor.yy0;
    delete yymsp[0].minor.yy0;
}
#line 1335 "parser\\epparser.c"
        break;
      case 56: /* funcName ::= NAME */
#line 221 "parser\\epparser.lemon"
{
    funcNamePreprocess(yymsp[0].minor.yy0->data);
    checkIsFunction(yymsp[0].minor.yy0->data);
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1344 "parser\\epparser.c"
        break;
      case 57: /* funcName ::= NAME PERIOD NAME */
#line 227 "parser\\epparser.lemon"
{
    // Preprocess name
    checkIsConstant(yymsp[-2].minor.yy0->data);
    yymsp[0].minor.yy0->data = yymsp[-2].minor.yy0->data + "." + yymsp[0].minor.yy0->data;
    delete yymsp[-2].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0);
}
#line 1355 "parser\\epparser.c"
        break;
      case 58: /* funcexpr ::= funcName LPAREN fArgs RPAREN */
#line 235 "parser\\epparser.lemon"
{
    // Preprocess yymsp[-3].minor.yy0
    yymsp[-3].minor.yy0->data += "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 1364 "parser\\epparser.c"
        break;
      case 60: /* expr ::= LPAREN expr RPAREN */
#line 244 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1372 "parser\\epparser.c"
        break;
      case 61: /* expr ::= L2V LPAREN lexpr RPAREN */
#line 249 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "_L2V(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = genTemp(yymsp[-1].minor.yy0);
}
#line 1380 "parser\\epparser.c"
        break;
      case 62: /* expr ::= MAPSTRING LPAREN STRING RPAREN */
#line 254 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetStringIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1388 "parser\\epparser.c"
        break;
      case 63: /* expr ::= UNIT LPAREN STRING RPAREN */
#line 259 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetUnitIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1396 "parser\\epparser.c"
        break;
      case 64: /* expr ::= SWITCH LPAREN STRING RPAREN */
#line 264 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetSwitchIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1404 "parser\\epparser.c"
        break;
      case 65: /* expr ::= LOCATION LPAREN STRING RPAREN */
#line 269 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetLocationIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1412 "parser\\epparser.c"
        break;
      case 66: /* expr ::= expr PLUS expr */
#line 275 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "+",  yymsp[0].minor.yy0); }
#line 1417 "parser\\epparser.c"
        break;
      case 67: /* expr ::= expr MINUS expr */
#line 276 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "-",  yymsp[0].minor.yy0); }
#line 1422 "parser\\epparser.c"
        break;
      case 68: /* expr ::= expr MULTIPLY expr */
#line 277 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "*",  yymsp[0].minor.yy0); }
#line 1427 "parser\\epparser.c"
        break;
      case 69: /* expr ::= expr DIVIDE expr */
#line 278 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "//", yymsp[0].minor.yy0); }
#line 1432 "parser\\epparser.c"
        break;
      case 70: /* expr ::= expr MOD expr */
#line 279 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "%",  yymsp[0].minor.yy0); }
#line 1437 "parser\\epparser.c"
        break;
      case 71: /* expr ::= expr LSHIFT expr */
#line 280 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<<", yymsp[0].minor.yy0); }
#line 1442 "parser\\epparser.c"
        break;
      case 72: /* expr ::= expr RSHIFT expr */
#line 281 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">>", yymsp[0].minor.yy0); }
#line 1447 "parser\\epparser.c"
        break;
      case 73: /* expr ::= expr BITAND expr */
#line 282 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "&",  yymsp[0].minor.yy0); }
#line 1452 "parser\\epparser.c"
        break;
      case 74: /* expr ::= expr BITOR expr */
#line 283 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "|",  yymsp[0].minor.yy0); }
#line 1457 "parser\\epparser.c"
        break;
      case 75: /* expr ::= expr BITXOR expr */
#line 284 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "^",  yymsp[0].minor.yy0); }
#line 1462 "parser\\epparser.c"
        break;
      case 76: /* expr ::= PLUS expr */
#line 287 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = +" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1467 "parser\\epparser.c"
        break;
      case 77: /* expr ::= MINUS expr */
#line 288 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = -" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1472 "parser\\epparser.c"
        break;
      case 78: /* expr ::= BITNOT expr */
#line 289 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = ~" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1477 "parser\\epparser.c"
        break;
      case 79: /* lexpr ::= expr EQ expr */
#line 293 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "==", yymsp[0].minor.yy0); }
#line 1482 "parser\\epparser.c"
        break;
      case 80: /* lexpr ::= expr NE expr */
#line 294 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "!=", yymsp[0].minor.yy0); }
#line 1487 "parser\\epparser.c"
        break;
      case 81: /* lexpr ::= expr LE expr */
#line 295 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<=", yymsp[0].minor.yy0); }
#line 1492 "parser\\epparser.c"
        break;
      case 82: /* lexpr ::= expr LT expr */
#line 296 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<",  yymsp[0].minor.yy0); }
#line 1497 "parser\\epparser.c"
        break;
      case 83: /* lexpr ::= expr GE expr */
#line 297 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">=", yymsp[0].minor.yy0); }
#line 1502 "parser\\epparser.c"
        break;
      case 84: /* lexpr ::= expr GT expr */
#line 298 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">" , yymsp[0].minor.yy0); }
#line 1507 "parser\\epparser.c"
        break;
      case 85: /* lexpr ::= lexpr LAND lexpr */
#line 300 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "[" + yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data + "]";
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1516 "parser\\epparser.c"
        break;
      case 86: /* lexpr ::= lexpr LOR lexpr */
#line 306 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "EUDOr([" + yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data + "])";
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1525 "parser\\epparser.c"
        break;
      case 87: /* lexpr ::= LNOT lexpr */
#line 312 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = "EUDNot([" + yymsp[0].minor.yy0->data + "])";
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0);
}
#line 1533 "parser\\epparser.c"
        break;
      case 89: /* vdef_stmt ::= VAR nameList_nonEmpty SEMICOLON */
#line 322 "parser\\epparser.lemon"
{
    std::string& s = yymsp[-1].minor.yy0->data;
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

    delete yymsp[-1].minor.yy0;
}
#line 1557 "parser\\epparser.c"
        break;
      case 90: /* vdefAssign_stmt ::= VAR nameList_nonEmpty ASSIGN exprList_nonEmpty SEMICOLON */
#line 343 "parser\\epparser.lemon"
{
    std::string& s = yymsp[-3].minor.yy0->data;
    int varCount = std::count(s.begin(), s.end(), ',') + 1;

    // Register variables.
    commaListIter(s, [&](std::string& varname) {
        if(!ps->closure.defVariable(varname)) {
            throw_error(7998, ("Redeclaration of variable \'" + varname + "\'"));
        }
    });

    if(varCount == 1) {
        ps->gen << s << " = EUDVariable()" << std::endl;
        ps->gen << s << " << (" << yymsp[-1].minor.yy0->data << ")" << std::endl;
    }
    else {
        ps->gen << s << " = _MVAR([" << yymsp[-1].minor.yy0->data << "])" << std::endl;
    }

    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1582 "parser\\epparser.c"
        break;
      case 91: /* cdef_stmt ::= CONST nameList_nonEmpty ASSIGN exprList_nonEmpty SEMICOLON */
#line 365 "parser\\epparser.lemon"
{
    std::string& s = yymsp[-3].minor.yy0->data;
    int nameCount = std::count(s.begin(), s.end(), ',') + 1;

    // Register constants.
    commaListIter(s, [&](std::string& constname) {
        if(!ps->closure.defConstant(constname)) {
            throw_error(7719, ("Redeclaration of constant \'" + constname + "\'"));
        }
    });
    if(nameCount == 1) {
        ps->gen << s << " = " << yymsp[-1].minor.yy0->data << std::endl;
    }
    else {
        ps->gen << s << " = List2Assignable([" << yymsp[-1].minor.yy0->data << "])" << std::endl;
    }
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1604 "parser\\epparser.c"
        break;
      case 92: /* lvalue ::= NAME */
#line 386 "parser\\epparser.lemon"
{
    checkIsVariable(yymsp[0].minor.yy0->data);
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1612 "parser\\epparser.c"
        break;
      case 93: /* lvalue ::= NAME LSQBRACKET NAME RSQBRACKET */
#line 391 "parser\\epparser.lemon"
{
    checkIsConstant(yymsp[-3].minor.yy0->data);
    yymsp[-1].minor.yy0->data = "_ARRW(" + yymsp[-3].minor.yy0->data + ", " + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
    delete yymsp[-3].minor.yy0;
}
#line 1622 "parser\\epparser.c"
        break;
      case 94: /* lvalue ::= NAME PERIOD NAME */
#line 398 "parser\\epparser.lemon"
{
    checkIsConstant(yymsp[-2].minor.yy0->data);
    yymsp[0].minor.yy0->data = "_ATTW(" + yymsp[-2].minor.yy0->data + ", '" + yymsp[0].minor.yy0->data + "')";
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0);
    delete yymsp[-2].minor.yy0;
}
#line 1632 "parser\\epparser.c"
        break;
      case 97: /* assign_stmt ::= lvalue ASSIGN expr SEMICOLON */
#line 407 "parser\\epparser.lemon"
{
    ps->gen << yymsp[-3].minor.yy0->data << " << (" << yymsp[-1].minor.yy0->data << ")" << std::endl;
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1640 "parser\\epparser.c"
        break;
      case 98: /* assign_stmt ::= lvalueList_nonEmpty ASSIGN exprList_nonEmpty SEMICOLON */
#line 412 "parser\\epparser.lemon"
{
    ps->gen << "_SV([" << yymsp[-3].minor.yy0->data << "], [" << yymsp[-1].minor.yy0->data << "])" << std::endl;
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1648 "parser\\epparser.c"
        break;
      case 99: /* if_start ::= IF */
#line 418 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDIf()" << std::endl;
}
#line 1656 "parser\\epparser.c"
        break;
      case 100: /* if_header ::= if_start LPAREN lexpr RPAREN */
      case 109: /* while_header ::= while_start LPAREN lexpr RPAREN */ yytestcase(yyruleno==109);
#line 422 "parser\\epparser.lemon"
{
    ps->gen << "if " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data << "):" << std::endl;
    ps->gen.indent();
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1666 "parser\\epparser.c"
        break;
      case 102: /* elif_start ::= ELSE IF */
#line 430 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen.unindent(false);
    ps->gen << yygotominor.yy0->data << " = EUDElseIf()" << std::endl;
}
#line 1675 "parser\\epparser.c"
        break;
      case 103: /* elif_header ::= elif_start LPAREN lexpr RPAREN */
#line 436 "parser\\epparser.lemon"
{
    ps->gen << "if " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data <<"):" << std::endl;
    ps->gen.indent();
}
#line 1683 "parser\\epparser.c"
        break;
      case 105: /* else_header ::= ELSE */
#line 443 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "if EUDElse()():" << std::endl;
    ps->gen.indent();
}
#line 1692 "parser\\epparser.c"
        break;
      case 106: /* if_stmt ::= if_block */
      case 107: /* if_stmt ::= if_block else_header stmt */ yytestcase(yyruleno==107);
#line 449 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndIf()" << std::endl;
}
#line 1701 "parser\\epparser.c"
        break;
      case 108: /* while_start ::= WHILE */
#line 461 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDWhile()" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1710 "parser\\epparser.c"
        break;
      case 110: /* while_stmt ::= while_header stmt */
#line 473 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndWhile()" << std::endl;
}
#line 1718 "parser\\epparser.c"
        break;
      case 111: /* foreach_header ::= FOR LPAREN nameList_nonEmpty COLON exprList_nonEmpty RPAREN */
#line 479 "parser\\epparser.lemon"
{
    ps->closure.pushScope();
    commaListIter(yymsp[-3].minor.yy0->data, [&](std::string& s) {
        ps->closure.defVariable(s);
    });
    ps->gen << "for " << yymsp[-3].minor.yy0->data << " in " << yymsp[-1].minor.yy0->data << ":" << std::endl;
    ps->gen.indent();
}
#line 1730 "parser\\epparser.c"
        break;
      case 113: /* continue_stmt ::= CONTINUE SEMICOLON */
#line 495 "parser\\epparser.lemon"
{
    ps->gen << "EUDContinue()" << std::endl;
}
#line 1737 "parser\\epparser.c"
        break;
      case 114: /* break_stmt ::= BREAK SEMICOLON */
#line 499 "parser\\epparser.lemon"
{
    ps->gen << "EUDBreak()" << std::endl;
}
#line 1744 "parser\\epparser.c"
        break;
      case 115: /* return_stmt ::= RETURN exprList SEMICOLON */
#line 506 "parser\\epparser.lemon"
{
    ps->gen << "EUDReturn(" << yymsp[-1].minor.yy0->data << ")" << std::endl;
    delete yymsp[-1].minor.yy0;
}
#line 1752 "parser\\epparser.c"
        break;
      case 116: /* lexpr ::= CONDITIONNAME LPAREN fArgs RPAREN */
#line 514 "parser\\epparser.lemon"
{
    yymsp[-3].minor.yy0->data = yymsp[-3].minor.yy0->data + "(" + yymsp[-1].minor.yy0->data + ")";
    delete yymsp[-1].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 1761 "parser\\epparser.c"
        break;
      case 117: /* lexpr ::= CONDITIONNAME LPAREN RPAREN */
#line 520 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + "()";
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1769 "parser\\epparser.c"
        break;
      case 118: /* action ::= ACTIONNAME LPAREN fArgs RPAREN SEMICOLON */
#line 525 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[-4].minor.yy0);
    yygotominor.yy0->data =  yymsp[-4].minor.yy0->data + "(" + yymsp[-2].minor.yy0->data + ")";
    delete yymsp[-4].minor.yy0; delete yymsp[-2].minor.yy0;
}
#line 1778 "parser\\epparser.c"
        break;
      case 119: /* actions ::= action action */
      case 120: /* actions ::= actions action */ yytestcase(yyruleno==120);
#line 531 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
    yymsp[-1].minor.yy0->data += ",\n" + yymsp[0].minor.yy0->data;
    delete yymsp[0].minor.yy0;
}
#line 1788 "parser\\epparser.c"
        break;
      case 121: /* actionStmt ::= action */
#line 543 "parser\\epparser.lemon"
{
    ps->gen << "DoActions(" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1796 "parser\\epparser.c"
        break;
      case 122: /* actionStmt ::= actions */
#line 548 "parser\\epparser.lemon"
{
    ps->gen << "DoActions([" << std::endl;
    ps->gen.indent();
    ps->gen << yymsp[0].minor.yy0->data << std::endl;
    ps->gen.unindent(false);
    ps->gen << "])" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1808 "parser\\epparser.c"
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
      /* (101) if_block ::= if_header stmt */ yytestcase(yyruleno==101);
      /* (104) if_block ::= if_block elif_header stmt */ yytestcase(yyruleno==104);
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
#line 1886 "parser\\epparser.c"
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
#line 562 "parser\\epparser.lemon"


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
#line 2139 "parser\\epparser.c"
