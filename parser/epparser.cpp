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
#line 27 "parser\\epparser.c"
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
#define YYNOCODE 100
#define YYACTIONTYPE unsigned short int
#define ParseTOKENTYPE Token*
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  int yy199;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL  ParserStruct* ps ;
#define ParseARG_PDECL , ParserStruct* ps 
#define ParseARG_FETCH  ParserStruct* ps  = yypParser->ps 
#define ParseARG_STORE yypParser->ps  = ps 
#define YYNSTATE 224
#define YYNRULE 109
#define YYERRORSYMBOL 55
#define YYERRSYMDT yy199
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
#define YY_ACTTAB_COUNT (611)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */    80,   44,   45,   43,  139,   88,  223,   25,   95,  104,
 /*    10 */     6,    3,  163,  162,  161,  160,  159,    2,  191,    1,
 /*    20 */   150,  108,    7,   27,  137,  139,   34,  156,  103,    5,
 /*    30 */   155,    4,  154,  153,  152,   15,   16,   96,  151,   56,
 /*    40 */    55,  157,   88,   25,  199,   95,   89,  134,   68,  163,
 /*    50 */   162,  161,  160,  159,   18,  147,    1,  150,  108,    7,
 /*    60 */    27,  137,   24,  182,  156,  103,    5,  155,    4,  154,
 /*    70 */   153,  152,   15,   16,   96,  151,   56,   55,  157,   88,
 /*    80 */   194,  222,   95,  200,  134,   68,  163,  162,  161,  160,
 /*    90 */   159,  132,  181,    1,  150,  108,    7,   27,   26,   23,
 /*   100 */   179,  156,  103,    5,  155,    4,  154,  153,  152,   15,
 /*   110 */    16,   96,  151,   56,   55,  157,   88,   21,  131,   95,
 /*   120 */    87,  134,   68,  163,  162,  161,  160,  159,  130,  178,
 /*   130 */     1,  150,  108,    7,   27,  221,  221,  176,  156,  103,
 /*   140 */     5,  155,    4,  154,  153,  152,   25,  202,   96,  151,
 /*   150 */    56,   55,  157,   88,   21,  129,   95,   85,  134,   68,
 /*   160 */   163,  162,  161,  160,  159,   25,  175,    1,  150,  108,
 /*   170 */     7,   27,   83,  134,   68,  156,  103,    5,  155,    4,
 /*   180 */   154,  153,  152,  193,  184,   96,  151,   56,   55,  157,
 /*   190 */    88,   25,  133,   95,  128,   67,  203,  163,  162,  161,
 /*   200 */   160,  159,  170,  173,    1,  150,  108,    7,   27,  128,
 /*   210 */    67,   81,  156,  103,    5,  155,    4,  154,  153,  152,
 /*   220 */    57,  174,   96,  151,   56,   55,  157,   88,   21,  219,
 /*   230 */    95,   82,  134,   68,  163,  162,  161,  160,  159,  220,
 /*   240 */   149,    1,  150,  108,    7,   27,  128,   67,   90,  156,
 /*   250 */   103,    5,  155,    4,  154,  153,  152,  218,   97,   96,
 /*   260 */   151,   56,   55,  157,   88,  128,   58,   95,   76,  138,
 /*   270 */   136,  163,  162,  161,  160,  159,  217,  190,    1,  150,
 /*   280 */   108,    7,   27,  128,   67,   84,  156,  103,    5,  155,
 /*   290 */     4,  154,  153,  152,  138,  135,  127,  151,   56,   55,
 /*   300 */   157,   33,   31,   30,   29,   28,   32,   39,   38,   40,
 /*   310 */    42,   41,   48,   47,   44,   45,   43,   77,   39,   38,
 /*   320 */    40,   42,   41,   48,   47,   44,   45,   43,   52,  164,
 /*   330 */    53,  192,  189,  188,  224,  177,  102,  165,  100,   99,
 /*   340 */   148,   20,  126,   98,  138,   86,  140,   37,   36,  128,
 /*   350 */    58,  196,   75,   35,  216,  124,  138,  101,  204,   46,
 /*   360 */   201,   14,  123,  120,  117,  114,   48,   47,   44,   45,
 /*   370 */    43,   54,  131,   53,   37,   36,  128,   58,  125,  187,
 /*   380 */    35,  216,  124,  111,  138,  146,   46,   94,   18,  123,
 /*   390 */   120,  117,  114,  138,  109,   13,   39,   38,   40,   42,
 /*   400 */    41,   48,   47,   44,   45,   43,  122,  106,   37,   36,
 /*   410 */   128,   78,  128,   79,   35,  216,  124,  128,   60,  214,
 /*   420 */    46,  195,  121,  123,  120,  117,  114,   37,   36,  128,
 /*   430 */    58,  119,  107,   35,  216,  124,   77,  118,  204,   46,
 /*   440 */   183,  106,  123,  120,  117,  114,  116,   52,  164,   53,
 /*   450 */   192,  213,  188,  115,  177,  102,  212,  100,   99,  113,
 /*   460 */    20,  112,   98,   39,   38,   40,   42,   41,   48,   47,
 /*   470 */    44,   45,   43,  211,  128,  210,   37,   36,  128,  209,
 /*   480 */   198,  215,   35,  216,  124,  128,  208,  204,   46,   37,
 /*   490 */    36,  123,  120,  117,  114,   35,  216,  124,   49,  128,
 /*   500 */    58,   46,  186,  197,  123,  120,  117,  114,   17,  169,
 /*   510 */    37,   36,  128,   58,   12,  185,   35,  216,  124,  128,
 /*   520 */    73,  180,   46,   11,   16,  123,  120,  117,  114,  128,
 /*   530 */    72,   38,   40,   42,   41,   48,   47,   44,   45,   43,
 /*   540 */    22,   40,   42,   41,   48,   47,   44,   45,   43,   42,
 /*   550 */    41,   48,   47,   44,   45,   43,  143,   50,  142,  128,
 /*   560 */    58,  172,   74,  128,   71,  128,   69,   10,  128,   70,
 /*   570 */   128,  207,   93,  128,  206,  128,  205,  128,   59,  110,
 /*   580 */     8,  144,  128,   66,  128,   65,  145,  141,  171,   51,
 /*   590 */   128,   64,  128,   63,  128,   62,   19,  128,   61,  334,
 /*   600 */     9,  168,  165,  158,   91,   92,   98,  167,  140,  166,
 /*   610 */   105,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    55,   20,   21,   22,    1,   60,   26,    1,   63,   79,
 /*    10 */    80,   81,   67,   68,   69,   70,   71,   72,   73,   74,
 /*    20 */    75,   76,   77,   78,    1,    1,    2,   82,   83,   84,
 /*    30 */    85,   86,   87,   88,   89,    3,    4,   55,   93,   94,
 /*    40 */    95,   96,   60,    1,   38,   63,   62,   63,   64,   67,
 /*    50 */    68,   69,   70,   71,   30,   73,   74,   75,   76,   77,
 /*    60 */    78,    1,    2,   31,   82,   83,   84,   85,   86,   87,
 /*    70 */    88,   89,    3,    4,   55,   93,   94,   95,   96,   60,
 /*    80 */    38,   26,   63,   62,   63,   64,   67,   68,   69,   70,
 /*    90 */    71,    1,   73,   74,   75,   76,   77,   78,    2,    2,
 /*   100 */    31,   82,   83,   84,   85,   86,   87,   88,   89,    3,
 /*   110 */     4,   55,   93,   94,   95,   96,   60,    1,   28,   63,
 /*   120 */    62,   63,   64,   67,   68,   69,   70,   71,    1,   73,
 /*   130 */    74,   75,   76,   77,   78,   38,   38,   31,   82,   83,
 /*   140 */    84,   85,   86,   87,   88,   89,    1,   31,   55,   93,
 /*   150 */    94,   95,   96,   60,    1,   28,   63,   62,   63,   64,
 /*   160 */    67,   68,   69,   70,   71,    1,   73,   74,   75,   76,
 /*   170 */    77,   78,   62,   63,   64,   82,   83,   84,   85,   86,
 /*   180 */    87,   88,   89,   38,   31,   55,   93,   94,   95,   96,
 /*   190 */    60,    1,   27,   63,   63,   64,   65,   67,   68,   69,
 /*   200 */    70,   71,   38,   73,   74,   75,   76,   77,   78,   63,
 /*   210 */    64,   65,   82,   83,   84,   85,   86,   87,   88,   89,
 /*   220 */    27,   31,   55,   93,   94,   95,   96,   60,    1,   28,
 /*   230 */    63,   62,   63,   64,   67,   68,   69,   70,   71,   25,
 /*   240 */    73,   74,   75,   76,   77,   78,   63,   64,   65,   82,
 /*   250 */    83,   84,   85,   86,   87,   88,   89,   25,   31,   55,
 /*   260 */    93,   94,   95,   96,   60,   63,   64,   63,   66,   60,
 /*   270 */    61,   67,   68,   69,   70,   71,   28,   73,   74,   75,
 /*   280 */    76,   77,   78,   63,   64,   65,   82,   83,   84,   85,
 /*   290 */    86,   87,   88,   89,   60,   61,   27,   93,   94,   95,
 /*   300 */    96,    7,    8,    9,   10,   11,   12,   13,   14,   15,
 /*   310 */    16,   17,   18,   19,   20,   21,   22,   26,   13,   14,
 /*   320 */    15,   16,   17,   18,   19,   20,   21,   22,   37,   38,
 /*   330 */    39,   40,   41,   42,    0,   44,   45,   38,   47,   48,
 /*   340 */    41,   50,   27,   52,   60,   61,   26,   18,   19,   63,
 /*   350 */    64,   31,   66,   24,   25,   26,   60,   61,   29,   30,
 /*   360 */    31,    5,   33,   34,   35,   36,   18,   19,   20,   21,
 /*   370 */    22,   37,   28,   39,   18,   19,   63,   64,   25,   66,
 /*   380 */    24,   25,   26,   49,   60,   61,   30,   53,   30,   33,
 /*   390 */    34,   35,   36,   60,   61,    5,   13,   14,   15,   16,
 /*   400 */    17,   18,   19,   20,   21,   22,   30,   51,   18,   19,
 /*   410 */    63,   64,   63,   64,   24,   25,   26,   63,   64,   31,
 /*   420 */    30,   38,   29,   33,   34,   35,   36,   18,   19,   63,
 /*   430 */    64,   30,   66,   24,   25,   26,   26,   29,   29,   30,
 /*   440 */    31,   51,   33,   34,   35,   36,   30,   37,   38,   39,
 /*   450 */    40,   31,   42,   29,   44,   45,   31,   47,   48,   30,
 /*   460 */    50,   29,   52,   13,   14,   15,   16,   17,   18,   19,
 /*   470 */    20,   21,   22,   31,   63,   64,   18,   19,   63,   64,
 /*   480 */    26,   31,   24,   25,   26,   63,   64,   29,   30,   18,
 /*   490 */    19,   33,   34,   35,   36,   24,   25,   26,   30,   63,
 /*   500 */    64,   30,   66,   31,   33,   34,   35,   36,   30,   38,
 /*   510 */    18,   19,   63,   64,   30,   66,   24,   25,   26,   63,
 /*   520 */    64,   42,   30,   30,    4,   33,   34,   35,   36,   63,
 /*   530 */    64,   14,   15,   16,   17,   18,   19,   20,   21,   22,
 /*   540 */    46,   15,   16,   17,   18,   19,   20,   21,   22,   16,
 /*   550 */    17,   18,   19,   20,   21,   22,   67,   54,   69,   63,
 /*   560 */    64,   38,   66,   63,   64,   63,   64,   30,   63,   64,
 /*   570 */    63,   64,   26,   63,   64,   63,   64,   63,   64,   90,
 /*   580 */    91,   92,   63,   64,   63,   64,   97,   98,   38,   30,
 /*   590 */    63,   64,   63,   64,   63,   64,   30,   63,   64,   57,
 /*   600 */    58,   38,   38,   38,   59,   25,   52,   94,   26,   94,
 /*   610 */    43,
};
#define YY_SHIFT_USE_DFLT (-21)
#define YY_SHIFT_COUNT (140)
#define YY_SHIFT_MIN   (-20)
#define YY_SHIFT_MAX   (582)
static const short yy_shift_ofst[] = {
 /*     0 */   -21,  410,  291,  410,  410,  410,  410,  410,  410,  334,
 /*    10 */   356,  356,  409,  390,  390,  356,  356,  356,  329,  458,
 /*    20 */   471,  458,  492,  492,  492,  492,  492,  567,  492,  492,
 /*    30 */   492,  492,  492,  492,  492,  492,  492,  492,  492,  492,
 /*    40 */   492,  492,  492,  492,  492,  492,  492,  492,  492,  320,
 /*    50 */   582,  582,  582,  582,  582,  554,  554,  580,  294,  383,
 /*    60 */   450,  305,  305,  305,  305,  305,  305,  305,  305,  517,
 /*    70 */   526,  533,  348,  348,  106,   69,   32,   24,  -19,  -19,
 /*    80 */   299,  227,  164,  190,  153,  145,   97,   42,   60,    6,
 /*    90 */   116,  127,   90,  503,  546,  565,  564,  563,  566,  550,
 /*   100 */   523,  494,  559,  537,  493,  479,  484,  520,  478,  472,
 /*   110 */   468,  454,  442,  432,  429,  425,  424,  416,  420,  408,
 /*   120 */   401,  388,  393,  376,  358,  344,  353,  315,  269,  248,
 /*   130 */   232,  201,  214,  193,  165,   96,   98,   55,   23,  -20,
 /*   140 */     3,
};
#define YY_REDUCE_USE_DFLT (-71)
#define YY_REDUCE_COUNT (57)
#define YY_REDUCE_MIN   (-70)
#define YY_REDUCE_MAX   (545)
static const short yy_reduce_ofst[] = {
 /*     0 */   542,  -55,  204,  167,  130,   93,   56,   19,  -18,  489,
 /*    10 */   496,  286,  220,  449,  436,  366,  313,  202,  183,  146,
 /*    20 */   169,  131,  110,   95,   58,   21,  -16,  -70,  534,  531,
 /*    30 */   529,  527,  521,  519,  514,  512,  510,  507,  505,  502,
 /*    40 */   500,  466,  456,  422,  415,  411,  354,  349,  347,  333,
 /*    50 */   324,  296,  284,  234,  209,  515,  513,  545,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   331,  333,  333,  333,  333,  333,  333,  333,  333,  333,
 /*    10 */   333,  333,  333,  333,  333,  333,  333,  333,  333,  333,
 /*    20 */   333,  333,  333,  333,  333,  333,  333,  288,  333,  333,
 /*    30 */   333,  333,  333,  333,  333,  333,  333,  333,  333,  333,
 /*    40 */   333,  333,  333,  333,  333,  333,  333,  333,  333,  333,
 /*    50 */   333,  333,  333,  333,  333,  309,  308,  333,  333,  333,
 /*    60 */   333,  266,  265,  264,  263,  262,  261,  237,  233,  256,
 /*    70 */   257,  255,  254,  253,  333,  333,  333,  333,  248,  249,
 /*    80 */   333,  333,  333,  333,  333,  333,  333,  333,  333,  333,
 /*    90 */   333,  333,  333,  333,  333,  333,  333,  333,  333,  333,
 /*   100 */   333,  333,  333,  333,  333,  287,  333,  268,  333,  333,
 /*   110 */   333,  333,  333,  333,  333,  333,  333,  333,  333,  333,
 /*   120 */   333,  333,  333,  333,  236,  333,  333,  333,  242,  333,
 /*   130 */   333,  333,  333,  333,  242,  333,  333,  333,  230,  333,
 /*   140 */   229,  332,  330,  329,  328,  327,  326,  300,  280,  289,
 /*   150 */   325,  324,  323,  322,  321,  320,  319,  318,  317,  316,
 /*   160 */   315,  314,  313,  312,  311,  310,  307,  306,  305,  301,
 /*   170 */   302,  296,  295,  294,  293,  292,  291,  290,  286,  285,
 /*   180 */   284,  283,  282,  304,  303,  270,  269,  267,  281,  279,
 /*   190 */   277,  276,  278,  272,  275,  274,  299,  298,  297,  273,
 /*   200 */   234,  241,  240,  239,  238,  260,  259,  258,  252,  251,
 /*   210 */   250,  247,  246,  245,  244,  243,  235,  231,  226,  232,
 /*   220 */   225,  271,  228,  227,
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
  "RSQBRACKET",    "STRING",        "LPAREN",        "RPAREN",      
  "FUNCCALL",      "MAPSTRING",     "UNIT",          "SWITCH",      
  "LOCATION",      "VAR",           "SEMICOLON",     "CONST",       
  "LBRACKET",      "RBRACKET",      "IF",            "ELSE",        
  "WHILE",         "FOR",           "COLON",         "CONTINUE",    
  "BREAK",         "FUNCTION",      "RETURN",        "CONDITIONNAME",
  "ACTIONNAME",    "FROM",          "IMPORT",        "error",       
  "nt",            "program",       "chunks",        "numList",     
  "nameListMulti",  "nameList",      "exprList",      "funcexpr",    
  "expr",          "fArgs",         "lexpr",         "vdef_stmt",   
  "vdefAssign_stmt",  "cdef_stmt",     "assign_stmt",   "assignMulti_stmt",
  "stmtList",      "stmt",          "blockStart",    "block",       
  "if_start",      "if_header",     "if_block",      "elif_start",  
  "elif_header",   "else_header",   "if_stmt",       "while_start", 
  "while_header",  "while_stmt",    "foreach_header",  "foreach_stmt",
  "continue_stmt",  "break_stmt",    "function_start",  "function_header",
  "fdef_chunk",    "return_stmt",   "action",        "actions",     
  "actionStmt",    "import_chunk",  "chunk",       
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
 /*  13 */ "fArgs ::= expr",
 /*  14 */ "fArgs ::= STRING",
 /*  15 */ "fArgs ::= fArgs COMMA fArgs",
 /*  16 */ "funcexpr ::= NAME LPAREN fArgs RPAREN",
 /*  17 */ "funcexpr ::= NAME LPAREN RPAREN",
 /*  18 */ "expr ::= funcexpr",
 /*  19 */ "expr ::= LPAREN expr RPAREN",
 /*  20 */ "expr ::= MAPSTRING LPAREN STRING RPAREN",
 /*  21 */ "expr ::= UNIT LPAREN STRING RPAREN",
 /*  22 */ "expr ::= SWITCH LPAREN STRING RPAREN",
 /*  23 */ "expr ::= LOCATION LPAREN STRING RPAREN",
 /*  24 */ "expr ::= expr PLUS expr",
 /*  25 */ "expr ::= expr MINUS expr",
 /*  26 */ "expr ::= expr MULTIPLY expr",
 /*  27 */ "expr ::= expr DIVIDE expr",
 /*  28 */ "expr ::= expr MOD expr",
 /*  29 */ "expr ::= expr LSHIFT expr",
 /*  30 */ "expr ::= expr RSHIFT expr",
 /*  31 */ "expr ::= expr BITAND expr",
 /*  32 */ "expr ::= expr BITOR expr",
 /*  33 */ "expr ::= expr BITXOR expr",
 /*  34 */ "expr ::= PLUS expr",
 /*  35 */ "expr ::= MINUS expr",
 /*  36 */ "expr ::= BITNOT expr",
 /*  37 */ "lexpr ::= expr EQ expr",
 /*  38 */ "lexpr ::= expr NE expr",
 /*  39 */ "lexpr ::= expr LE expr",
 /*  40 */ "lexpr ::= expr LT expr",
 /*  41 */ "lexpr ::= expr GE expr",
 /*  42 */ "lexpr ::= expr GT expr",
 /*  43 */ "lexpr ::= lexpr LAND lexpr",
 /*  44 */ "lexpr ::= lexpr LOR lexpr",
 /*  45 */ "lexpr ::= LNOT lexpr",
 /*  46 */ "lexpr ::= LNOT LNOT lexpr",
 /*  47 */ "vdef_stmt ::= VAR nameList SEMICOLON",
 /*  48 */ "vdefAssign_stmt ::= VAR nameList ASSIGN exprList SEMICOLON",
 /*  49 */ "cdef_stmt ::= CONST nameList ASSIGN exprList SEMICOLON",
 /*  50 */ "assign_stmt ::= NAME ASSIGN expr SEMICOLON",
 /*  51 */ "assignMulti_stmt ::= nameListMulti ASSIGN exprList SEMICOLON",
 /*  52 */ "stmtList ::= stmt",
 /*  53 */ "stmtList ::= stmtList stmt",
 /*  54 */ "blockStart ::= LBRACKET",
 /*  55 */ "block ::= blockStart stmtList RBRACKET",
 /*  56 */ "block ::= blockStart error RBRACKET",
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
 /*  87 */ "stmt ::= SEMICOLON",
 /*  88 */ "stmt ::= vdef_stmt",
 /*  89 */ "stmt ::= vdefAssign_stmt",
 /*  90 */ "stmt ::= cdef_stmt",
 /*  91 */ "stmt ::= assign_stmt",
 /*  92 */ "stmt ::= assignMulti_stmt",
 /*  93 */ "stmt ::= funcexpr SEMICOLON",
 /*  94 */ "stmt ::= actionStmt",
 /*  95 */ "stmt ::= if_stmt",
 /*  96 */ "stmt ::= while_stmt",
 /*  97 */ "stmt ::= foreach_stmt",
 /*  98 */ "stmt ::= continue_stmt",
 /*  99 */ "stmt ::= break_stmt",
 /* 100 */ "stmt ::= return_stmt",
 /* 101 */ "stmt ::= block",
 /* 102 */ "import_chunk ::= FROM NAME IMPORT nameList",
 /* 103 */ "chunk ::= import_chunk",
 /* 104 */ "chunk ::= fdef_chunk",
 /* 105 */ "chunk ::= vdef_stmt",
 /* 106 */ "chunk ::= cdef_stmt",
 /* 107 */ "chunks ::=",
 /* 108 */ "chunks ::= chunks chunk",
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
    case 56: /* nt */
{
#line 29 "parser\\epparser.lemon"
 delete (yypminor->yy0); 
#line 666 "parser\\epparser.c"
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
  { 57, 1 },
  { 59, 3 },
  { 59, 3 },
  { 60, 3 },
  { 60, 3 },
  { 61, 1 },
  { 61, 1 },
  { 62, 6 },
  { 64, 6 },
  { 62, 1 },
  { 62, 3 },
  { 64, 1 },
  { 64, 1 },
  { 65, 1 },
  { 65, 1 },
  { 65, 3 },
  { 63, 4 },
  { 63, 3 },
  { 64, 1 },
  { 64, 3 },
  { 64, 4 },
  { 64, 4 },
  { 64, 4 },
  { 64, 4 },
  { 64, 3 },
  { 64, 3 },
  { 64, 3 },
  { 64, 3 },
  { 64, 3 },
  { 64, 3 },
  { 64, 3 },
  { 64, 3 },
  { 64, 3 },
  { 64, 3 },
  { 64, 2 },
  { 64, 2 },
  { 64, 2 },
  { 66, 3 },
  { 66, 3 },
  { 66, 3 },
  { 66, 3 },
  { 66, 3 },
  { 66, 3 },
  { 66, 3 },
  { 66, 3 },
  { 66, 2 },
  { 66, 3 },
  { 67, 3 },
  { 68, 5 },
  { 69, 5 },
  { 70, 4 },
  { 71, 4 },
  { 72, 1 },
  { 72, 2 },
  { 74, 1 },
  { 75, 3 },
  { 75, 3 },
  { 76, 1 },
  { 77, 4 },
  { 78, 2 },
  { 79, 2 },
  { 80, 4 },
  { 78, 3 },
  { 81, 1 },
  { 82, 1 },
  { 82, 3 },
  { 83, 1 },
  { 84, 4 },
  { 85, 2 },
  { 86, 6 },
  { 87, 2 },
  { 88, 2 },
  { 89, 2 },
  { 90, 2 },
  { 91, 4 },
  { 91, 3 },
  { 92, 2 },
  { 93, 2 },
  { 93, 3 },
  { 66, 4 },
  { 66, 3 },
  { 94, 5 },
  { 95, 2 },
  { 95, 2 },
  { 96, 1 },
  { 96, 1 },
  { 73, 2 },
  { 73, 1 },
  { 73, 1 },
  { 73, 1 },
  { 73, 1 },
  { 73, 1 },
  { 73, 1 },
  { 73, 2 },
  { 73, 1 },
  { 73, 1 },
  { 73, 1 },
  { 73, 1 },
  { 73, 1 },
  { 73, 1 },
  { 73, 1 },
  { 73, 1 },
  { 97, 4 },
  { 98, 1 },
  { 98, 1 },
  { 98, 1 },
  { 98, 1 },
  { 58, 0 },
  { 58, 2 },
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
#line 55 "parser\\epparser.lemon"
{
    yygotominor.yy0 = new Token(yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data, yymsp[0].minor.yy0);
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 1074 "parser\\epparser.c"
        break;
      case 3: /* nameListMulti ::= NAME COMMA NAME */
      case 4: /* nameListMulti ::= nameListMulti COMMA NAME */ yytestcase(yyruleno==4);
      case 10: /* exprList ::= exprList COMMA exprList */ yytestcase(yyruleno==10);
#line 63 "parser\\epparser.lemon"
{ yygotominor.yy0 = new Token((yymsp[-2].minor.yy0->data) + ", " + (yymsp[0].minor.yy0->data), yymsp[0].minor.yy0); delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1081 "parser\\epparser.c"
        break;
      case 5: /* nameList ::= NAME */
      case 6: /* nameList ::= nameListMulti */ yytestcase(yyruleno==6);
      case 9: /* exprList ::= expr */ yytestcase(yyruleno==9);
      case 11: /* expr ::= NUMBER */ yytestcase(yyruleno==11);
      case 13: /* fArgs ::= expr */ yytestcase(yyruleno==13);
      case 14: /* fArgs ::= STRING */ yytestcase(yyruleno==14);
      case 18: /* expr ::= funcexpr */ yytestcase(yyruleno==18);
      case 46: /* lexpr ::= LNOT LNOT lexpr */ yytestcase(yyruleno==46);
#line 65 "parser\\epparser.lemon"
{ yygotominor.yy0 = yymsp[0].minor.yy0; }
#line 1093 "parser\\epparser.c"
        break;
      case 7: /* exprList ::= funcexpr LSQBRACKET LSQBRACKET numList RSQBRACKET RSQBRACKET */
      case 8: /* expr ::= funcexpr LSQBRACKET LSQBRACKET NUMBER RSQBRACKET RSQBRACKET */ yytestcase(yyruleno==8);
#line 68 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[-2].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = _SRET(" << yymsp[-5].minor.yy0->data << ", [" << yymsp[-2].minor.yy0->data << "])" << std::endl;
    delete yymsp[-5].minor.yy0; delete yymsp[-2].minor.yy0;
}
#line 1103 "parser\\epparser.c"
        break;
      case 12: /* expr ::= NAME */
#line 85 "parser\\epparser.lemon"
{
    if(!ps->closure.getConstant(yymsp[0].minor.yy0->data) && !ps->closure.getVariable(yymsp[0].minor.yy0->data)) {
        throw_error(yymsp[0].minor.yy0->line, 103, ("Undeclared variable \'" + (yymsp[0].minor.yy0->data) + "\'"));
        ps->closure.defVariable(yymsp[0].minor.yy0->data);
    }
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1114 "parser\\epparser.c"
        break;
      case 15: /* fArgs ::= fArgs COMMA fArgs */
#line 96 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data;
    yymsp[-2].minor.yy0->type = TOKEN_TEMP;
    yygotominor.yy0 = yymsp[-2].minor.yy0;
}
#line 1123 "parser\\epparser.c"
        break;
      case 16: /* funcexpr ::= NAME LPAREN fArgs RPAREN */
#line 102 "parser\\epparser.lemon"
{
    // Preprocess yymsp[-3].minor.yy0
    funcNamePreprocess(yymsp[-3].minor.yy0->data);
    if (!ps->closure.getFunction(yymsp[-3].minor.yy0->data)) {
        throw_error(yymsp[-3].minor.yy0->line, 4449, ("Undefined function " + yymsp[-3].minor.yy0->data));
        ps->closure.defFunction(yymsp[-3].minor.yy0->data);
    }

    yymsp[-3].minor.yy0->data += "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0, ps->gen);
}
#line 1138 "parser\\epparser.c"
        break;
      case 17: /* funcexpr ::= NAME LPAREN RPAREN */
#line 115 "parser\\epparser.lemon"
{
    // Preprocess yymsp[-2].minor.yy0
    funcNamePreprocess(yymsp[-2].minor.yy0->data);
    if (!ps->closure.getFunction(yymsp[-2].minor.yy0->data)) {
        throw_error(yymsp[-2].minor.yy0->line, 4449, ("Undefined function " + yymsp[-2].minor.yy0->data));
        ps->closure.defFunction(yymsp[-2].minor.yy0->data);
    }

    yymsp[-2].minor.yy0->data += "()";
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0, ps->gen);
}
#line 1153 "parser\\epparser.c"
        break;
      case 19: /* expr ::= LPAREN expr RPAREN */
#line 130 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0, ps->gen);
}
#line 1161 "parser\\epparser.c"
        break;
      case 20: /* expr ::= MAPSTRING LPAREN STRING RPAREN */
#line 135 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetStringIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0, ps->gen);
}
#line 1169 "parser\\epparser.c"
        break;
      case 21: /* expr ::= UNIT LPAREN STRING RPAREN */
#line 140 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetUnitIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0, ps->gen);
}
#line 1177 "parser\\epparser.c"
        break;
      case 22: /* expr ::= SWITCH LPAREN STRING RPAREN */
#line 145 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetSwitchIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0, ps->gen);
}
#line 1185 "parser\\epparser.c"
        break;
      case 23: /* expr ::= LOCATION LPAREN STRING RPAREN */
#line 150 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetLocationIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0, ps->gen);
}
#line 1193 "parser\\epparser.c"
        break;
      case 24: /* expr ::= expr PLUS expr */
#line 155 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "+",  yymsp[0].minor.yy0, ps->gen); }
#line 1198 "parser\\epparser.c"
        break;
      case 25: /* expr ::= expr MINUS expr */
#line 156 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "-",  yymsp[0].minor.yy0, ps->gen); }
#line 1203 "parser\\epparser.c"
        break;
      case 26: /* expr ::= expr MULTIPLY expr */
#line 157 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "*",  yymsp[0].minor.yy0, ps->gen); }
#line 1208 "parser\\epparser.c"
        break;
      case 27: /* expr ::= expr DIVIDE expr */
#line 158 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "//", yymsp[0].minor.yy0, ps->gen); }
#line 1213 "parser\\epparser.c"
        break;
      case 28: /* expr ::= expr MOD expr */
#line 159 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "%",  yymsp[0].minor.yy0, ps->gen); }
#line 1218 "parser\\epparser.c"
        break;
      case 29: /* expr ::= expr LSHIFT expr */
#line 160 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<<", yymsp[0].minor.yy0, ps->gen); }
#line 1223 "parser\\epparser.c"
        break;
      case 30: /* expr ::= expr RSHIFT expr */
#line 161 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">>", yymsp[0].minor.yy0, ps->gen); }
#line 1228 "parser\\epparser.c"
        break;
      case 31: /* expr ::= expr BITAND expr */
#line 162 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "&",  yymsp[0].minor.yy0, ps->gen); }
#line 1233 "parser\\epparser.c"
        break;
      case 32: /* expr ::= expr BITOR expr */
#line 163 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "|",  yymsp[0].minor.yy0, ps->gen); }
#line 1238 "parser\\epparser.c"
        break;
      case 33: /* expr ::= expr BITXOR expr */
#line 164 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "^",  yymsp[0].minor.yy0, ps->gen); }
#line 1243 "parser\\epparser.c"
        break;
      case 34: /* expr ::= PLUS expr */
#line 167 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = +" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1248 "parser\\epparser.c"
        break;
      case 35: /* expr ::= MINUS expr */
#line 168 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = -" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1253 "parser\\epparser.c"
        break;
      case 36: /* expr ::= BITNOT expr */
#line 169 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = ~" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1258 "parser\\epparser.c"
        break;
      case 37: /* lexpr ::= expr EQ expr */
#line 172 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "==", yymsp[0].minor.yy0, ps->gen); }
#line 1263 "parser\\epparser.c"
        break;
      case 38: /* lexpr ::= expr NE expr */
#line 173 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "!=", yymsp[0].minor.yy0, ps->gen); }
#line 1268 "parser\\epparser.c"
        break;
      case 39: /* lexpr ::= expr LE expr */
#line 174 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<=", yymsp[0].minor.yy0, ps->gen); }
#line 1273 "parser\\epparser.c"
        break;
      case 40: /* lexpr ::= expr LT expr */
#line 175 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<",  yymsp[0].minor.yy0, ps->gen); }
#line 1278 "parser\\epparser.c"
        break;
      case 41: /* lexpr ::= expr GE expr */
#line 176 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">=", yymsp[0].minor.yy0, ps->gen); }
#line 1283 "parser\\epparser.c"
        break;
      case 42: /* lexpr ::= expr GT expr */
#line 177 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">" , yymsp[0].minor.yy0, ps->gen); }
#line 1288 "parser\\epparser.c"
        break;
      case 43: /* lexpr ::= lexpr LAND lexpr */
#line 179 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "[" + yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data + "]";
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0, ps->gen);
}
#line 1297 "parser\\epparser.c"
        break;
      case 44: /* lexpr ::= lexpr LOR lexpr */
#line 185 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "EUDOr([" + yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data + "])";
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0, ps->gen);
}
#line 1306 "parser\\epparser.c"
        break;
      case 45: /* lexpr ::= LNOT lexpr */
#line 191 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = "EUDNot([" + yymsp[0].minor.yy0->data + "])";
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0, ps->gen);
}
#line 1314 "parser\\epparser.c"
        break;
      case 47: /* vdef_stmt ::= VAR nameList SEMICOLON */
#line 201 "parser\\epparser.lemon"
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
#line 1331 "parser\\epparser.c"
        break;
      case 48: /* vdefAssign_stmt ::= VAR nameList ASSIGN exprList SEMICOLON */
#line 215 "parser\\epparser.lemon"
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
#line 1347 "parser\\epparser.c"
        break;
      case 49: /* cdef_stmt ::= CONST nameList ASSIGN exprList SEMICOLON */
#line 228 "parser\\epparser.lemon"
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
#line 1363 "parser\\epparser.c"
        break;
      case 50: /* assign_stmt ::= NAME ASSIGN expr SEMICOLON */
#line 241 "parser\\epparser.lemon"
{
    ps->gen << yymsp[-3].minor.yy0->data << " << " << yymsp[-1].minor.yy0->data << std::endl;
    if(!ps->closure.getVariable(yymsp[-3].minor.yy0->data)) {
        throw_error(yymsp[-3].minor.yy0->line, 103, ("Undeclared variable \'" + (yymsp[-3].minor.yy0->data) + "\'"));
        ps->closure.defVariable(yymsp[-3].minor.yy0->data);
    }
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1375 "parser\\epparser.c"
        break;
      case 51: /* assignMulti_stmt ::= nameListMulti ASSIGN exprList SEMICOLON */
#line 250 "parser\\epparser.lemon"
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
#line 1391 "parser\\epparser.c"
        break;
      case 54: /* blockStart ::= LBRACKET */
#line 266 "parser\\epparser.lemon"
{
    ps->closure.pushScope();
}
#line 1398 "parser\\epparser.c"
        break;
      case 55: /* block ::= blockStart stmtList RBRACKET */
#line 270 "parser\\epparser.lemon"
{
    ps->closure.popScope();
}
#line 1405 "parser\\epparser.c"
        break;
      case 56: /* block ::= blockStart error RBRACKET */
#line 274 "parser\\epparser.lemon"
{
    throw_error(yymsp[0].minor.yy0->line, 6298, "Block not terminated properly.");
    ps->closure.popScope();
}
#line 1413 "parser\\epparser.c"
        break;
      case 57: /* if_start ::= IF */
#line 281 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDIf()" << std::endl;
}
#line 1421 "parser\\epparser.c"
        break;
      case 58: /* if_header ::= if_start LPAREN lexpr RPAREN */
      case 67: /* while_header ::= while_start LPAREN lexpr RPAREN */ yytestcase(yyruleno==67);
#line 285 "parser\\epparser.lemon"
{
    ps->gen << "if " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data << "):" << std::endl;
    ps->gen.indent();
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1431 "parser\\epparser.c"
        break;
      case 60: /* elif_start ::= ELSE IF */
#line 293 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen.unindent(false);
    ps->gen << yygotominor.yy0->data << " = EUDElseIf()" << std::endl;
}
#line 1440 "parser\\epparser.c"
        break;
      case 61: /* elif_header ::= elif_start LPAREN lexpr RPAREN */
#line 299 "parser\\epparser.lemon"
{
    ps->gen << "if " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data <<"):" << std::endl;
    ps->gen.indent();
}
#line 1448 "parser\\epparser.c"
        break;
      case 63: /* else_header ::= ELSE */
#line 306 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "if EUDElse()():" << std::endl;
    ps->gen.indent();
}
#line 1457 "parser\\epparser.c"
        break;
      case 64: /* if_stmt ::= if_block */
      case 65: /* if_stmt ::= if_block else_header stmt */ yytestcase(yyruleno==65);
#line 312 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndIf()" << std::endl;
}
#line 1466 "parser\\epparser.c"
        break;
      case 66: /* while_start ::= WHILE */
#line 324 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDWhile()" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1475 "parser\\epparser.c"
        break;
      case 68: /* while_stmt ::= while_header stmt */
#line 336 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndWhile()" << std::endl;
}
#line 1483 "parser\\epparser.c"
        break;
      case 69: /* foreach_header ::= FOR LPAREN nameList COLON exprList RPAREN */
#line 342 "parser\\epparser.lemon"
{
    ps->gen << "for " << yymsp[-3].minor.yy0->data << " in " << yymsp[-1].minor.yy0->data << ":" << std::endl;
    ps->gen.indent();
    commaListIter(yymsp[-3].minor.yy0->data, [&](std::string& s) {
        ps->closure.defVariable(s);
    });
}
#line 1494 "parser\\epparser.c"
        break;
      case 70: /* foreach_stmt ::= foreach_header stmt */
      case 76: /* fdef_chunk ::= function_header stmt */ yytestcase(yyruleno==76);
#line 350 "parser\\epparser.lemon"
{
    ps->gen.unindent(true);
}
#line 1502 "parser\\epparser.c"
        break;
      case 71: /* continue_stmt ::= CONTINUE SEMICOLON */
#line 356 "parser\\epparser.lemon"
{
    ps->gen << "EUDContinue()" << std::endl;
}
#line 1509 "parser\\epparser.c"
        break;
      case 72: /* break_stmt ::= BREAK SEMICOLON */
#line 360 "parser\\epparser.lemon"
{
    ps->gen << "EUDBreak()" << std::endl;
}
#line 1516 "parser\\epparser.c"
        break;
      case 73: /* function_start ::= FUNCTION NAME */
#line 365 "parser\\epparser.lemon"
{
    // Preprocess yymsp[0].minor.yy0
    funcNamePreprocess(yymsp[0].minor.yy0->data);
    yygotominor.yy0 = yymsp[0].minor.yy0;
    if(!ps->closure.defFunction(yymsp[0].minor.yy0->data)) {
        throw_error(yymsp[0].minor.yy0->line, 4495, "Duplicate function yymsp[0].minor.yy0 " + yymsp[0].minor.yy0->data);
    }
}
#line 1528 "parser\\epparser.c"
        break;
      case 74: /* function_header ::= function_start LPAREN nameList RPAREN */
#line 374 "parser\\epparser.lemon"
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
#line 1548 "parser\\epparser.c"
        break;
      case 75: /* function_header ::= function_start LPAREN RPAREN */
#line 391 "parser\\epparser.lemon"
{
    ps->gen << "@EUDFunc" << std::endl;
    ps->gen << "def " << yymsp[-2].minor.yy0->data << "():" << std::endl;
    ps->gen.indent();
    tmpIndex = 1;
    delete yymsp[-2].minor.yy0;
}
#line 1559 "parser\\epparser.c"
        break;
      case 77: /* return_stmt ::= RETURN SEMICOLON */
#line 405 "parser\\epparser.lemon"
{
    ps->gen << "EUDReturn()" << std::endl;
}
#line 1566 "parser\\epparser.c"
        break;
      case 78: /* return_stmt ::= RETURN exprList SEMICOLON */
#line 409 "parser\\epparser.lemon"
{
    ps->gen << "EUDReturn(" << yymsp[-1].minor.yy0->data << ")" << std::endl;
    delete yymsp[-1].minor.yy0;
}
#line 1574 "parser\\epparser.c"
        break;
      case 79: /* lexpr ::= CONDITIONNAME LPAREN fArgs RPAREN */
#line 417 "parser\\epparser.lemon"
{
    yymsp[-3].minor.yy0->data = yymsp[-3].minor.yy0->data + "(" + yymsp[-1].minor.yy0->data + ")";
    delete yymsp[-1].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0, ps->gen);
}
#line 1583 "parser\\epparser.c"
        break;
      case 80: /* lexpr ::= CONDITIONNAME LPAREN RPAREN */
#line 423 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + "()";
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0, ps->gen);
}
#line 1591 "parser\\epparser.c"
        break;
      case 81: /* action ::= ACTIONNAME LPAREN fArgs RPAREN SEMICOLON */
#line 428 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[-4].minor.yy0);
    yygotominor.yy0->data =  yymsp[-4].minor.yy0->data + "(" + yymsp[-2].minor.yy0->data + ")";
    delete yymsp[-4].minor.yy0; delete yymsp[-2].minor.yy0;
}
#line 1600 "parser\\epparser.c"
        break;
      case 82: /* actions ::= action action */
      case 83: /* actions ::= actions action */ yytestcase(yyruleno==83);
#line 434 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
    yymsp[-1].minor.yy0->data += ",\n" + yymsp[0].minor.yy0->data;
    delete yymsp[0].minor.yy0;
}
#line 1610 "parser\\epparser.c"
        break;
      case 84: /* actionStmt ::= action */
#line 446 "parser\\epparser.lemon"
{
    ps->gen << "DoActions(" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1618 "parser\\epparser.c"
        break;
      case 85: /* actionStmt ::= actions */
#line 451 "parser\\epparser.lemon"
{
    ps->gen << "DoActions([" << std::endl;
    ps->gen.indent();
    ps->gen << yymsp[0].minor.yy0->data << std::endl;
    ps->gen.unindent(false);
    ps->gen << "])" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1630 "parser\\epparser.c"
        break;
      case 86: /* stmt ::= error SEMICOLON */
#line 462 "parser\\epparser.lemon"
{ throw_error(yymsp[0].minor.yy0->line, 6974, "Error while parsing statement"); }
#line 1635 "parser\\epparser.c"
        break;
      case 93: /* stmt ::= funcexpr SEMICOLON */
#line 471 "parser\\epparser.lemon"
{ ps->gen << yymsp[-1].minor.yy0->data << std::endl; }
#line 1640 "parser\\epparser.c"
        break;
      case 102: /* import_chunk ::= FROM NAME IMPORT nameList */
#line 484 "parser\\epparser.lemon"
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
#line 1655 "parser\\epparser.c"
        break;
      default:
      /* (0) program ::= chunks */ yytestcase(yyruleno==0);
      /* (52) stmtList ::= stmt */ yytestcase(yyruleno==52);
      /* (53) stmtList ::= stmtList stmt */ yytestcase(yyruleno==53);
      /* (59) if_block ::= if_header stmt */ yytestcase(yyruleno==59);
      /* (62) if_block ::= if_block elif_header stmt */ yytestcase(yyruleno==62);
      /* (87) stmt ::= SEMICOLON */ yytestcase(yyruleno==87);
      /* (88) stmt ::= vdef_stmt */ yytestcase(yyruleno==88);
      /* (89) stmt ::= vdefAssign_stmt */ yytestcase(yyruleno==89);
      /* (90) stmt ::= cdef_stmt */ yytestcase(yyruleno==90);
      /* (91) stmt ::= assign_stmt */ yytestcase(yyruleno==91);
      /* (92) stmt ::= assignMulti_stmt */ yytestcase(yyruleno==92);
      /* (94) stmt ::= actionStmt */ yytestcase(yyruleno==94);
      /* (95) stmt ::= if_stmt */ yytestcase(yyruleno==95);
      /* (96) stmt ::= while_stmt */ yytestcase(yyruleno==96);
      /* (97) stmt ::= foreach_stmt */ yytestcase(yyruleno==97);
      /* (98) stmt ::= continue_stmt */ yytestcase(yyruleno==98);
      /* (99) stmt ::= break_stmt */ yytestcase(yyruleno==99);
      /* (100) stmt ::= return_stmt */ yytestcase(yyruleno==100);
      /* (101) stmt ::= block */ yytestcase(yyruleno==101);
      /* (103) chunk ::= import_chunk */ yytestcase(yyruleno==103);
      /* (104) chunk ::= fdef_chunk */ yytestcase(yyruleno==104);
      /* (105) chunk ::= vdef_stmt */ yytestcase(yyruleno==105);
      /* (106) chunk ::= cdef_stmt */ yytestcase(yyruleno==106);
      /* (107) chunks ::= */ yytestcase(yyruleno==107);
      /* (108) chunks ::= chunks chunk */ yytestcase(yyruleno==108);
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
#line 21 "parser\\epparser.lemon"

    errorOccured = true;
#line 1745 "parser\\epparser.c"
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
#line 503 "parser\\epparser.lemon"


int PARSER_DEBUG = 0;

std::string ParseString(const std::string& code)
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
            currentTokenizingLine = tok.getCurrentLine();
            ps.gen << "# (Line " << currentTokenizingLine << ") " << trim(tok.getCurrentLineString()) << std::endl;
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

    if(!errorOccured) return postProcessCode(ps.gen.str());
    else throw std::runtime_error("Invalid syntax");
}
#line 1975 "parser\\epparser.c"
