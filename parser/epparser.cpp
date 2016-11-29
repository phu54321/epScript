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
#define YYNSTATE 226
#define YYNRULE 111
#define YYERRORSYMBOL 54
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
#define YY_ACTTAB_COUNT (628)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */    82,   44,   45,   43,  225,   91,  133,   57,   97,   76,
 /*    10 */   140,   33,  164,  163,  161,  162,  160,  159,    2,  192,
 /*    20 */     1,  150,  110,    7,   26,  223,  139,   23,  156,  105,
 /*    30 */     5,  155,    4,  154,  153,  152,  140,   34,   98,  151,
 /*    40 */    53,   52,  157,   91,  221,  140,   97,  224,  139,   25,
 /*    50 */   164,  163,  161,  162,  160,  159,  113,  147,    1,  150,
 /*    60 */   110,    7,   26,  222,  139,   18,  156,  105,    5,  155,
 /*    70 */     4,  154,  153,  152,   15,   16,   98,  151,   53,   52,
 /*    80 */   157,   91,  224,  129,   97,   15,   16,   49,  164,  163,
 /*    90 */   161,  162,  160,  159,  112,  182,    1,  150,  110,    7,
 /*   100 */    26,  222,  183,  140,  156,  105,    5,  155,    4,  154,
 /*   110 */   153,  152,  139,  180,   98,  151,   53,   52,  157,   91,
 /*   120 */    21,  111,   97,   15,   16,  220,  164,  163,  161,  162,
 /*   130 */   160,  159,  132,  179,    1,  150,  110,    7,   26,   88,
 /*   140 */   115,   67,  156,  105,    5,  155,    4,  154,  153,  152,
 /*   150 */   203,  177,   98,  151,   53,   52,  157,   91,   21,  131,
 /*   160 */    97,  197,  115,   67,  164,  163,  161,  162,  160,  159,
 /*   170 */   130,  176,    1,  150,  110,    7,   26,   87,  115,   67,
 /*   180 */   156,  105,    5,  155,    4,  154,  153,  152,  185,   24,
 /*   190 */    98,  151,   53,   52,  157,   91,  129,   24,   97,   85,
 /*   200 */   115,   67,  164,  163,  161,  162,  160,  159,  218,  174,
 /*   210 */     1,  150,  110,    7,   26,  133,   68,  204,  156,  105,
 /*   220 */     5,  155,    4,  154,  153,  152,  196,   24,   98,  151,
 /*   230 */    53,   52,  157,   91,  194,   24,   97,  106,    6,    3,
 /*   240 */   164,  163,  161,  162,  160,  159,   18,  149,    1,  150,
 /*   250 */   110,    7,   26,   84,  115,   67,  156,  105,    5,  155,
 /*   260 */     4,  154,  153,  152,  171,  175,   98,  151,   53,   52,
 /*   270 */   157,   91,  133,   79,   97,  133,   68,   83,  164,  163,
 /*   280 */   161,  162,  160,  159,  126,  191,    1,  150,  110,    7,
 /*   290 */    26,  133,   68,   92,  156,  105,    5,  155,    4,  154,
 /*   300 */   153,  152,  133,   68,   86,  151,   53,   52,  157,   32,
 /*   310 */    30,   29,   28,   27,   31,   39,   38,   40,   42,   41,
 /*   320 */    48,   46,   44,   45,   43,   37,   36,  166,  125,  148,
 /*   330 */   122,   35,  217,  128,  135,  103,  205,   47,  202,   14,
 /*   340 */   127,  124,  121,  118,   48,   46,   44,   45,   43,  135,
 /*   350 */   146,  136,   37,   36,  133,   57,  219,  188,   35,  217,
 /*   360 */   128,  215,  133,   57,   47,  109,   13,  127,  124,  121,
 /*   370 */   118,  133,   57,   21,  187,  133,   57,  123,  186,   37,
 /*   380 */    36,  135,  134,  214,  108,   35,  217,  128,  120,  133,
 /*   390 */    57,   47,   75,  119,  127,  124,  121,  118,  117,  133,
 /*   400 */    57,  213,   74,   99,  133,   60,   37,   36,  133,   80,
 /*   410 */   116,  108,   35,  217,  128,  133,  211,  205,   47,  184,
 /*   420 */   212,  127,  124,  121,  118,  133,  210,  133,  209,  133,
 /*   430 */    73,  133,   72,   81,   38,   40,   42,   41,   48,   46,
 /*   440 */    44,   45,   43,  114,   54,  165,  193,  190,  189,   55,
 /*   450 */   178,  104,  200,  102,  101,  199,   20,  198,  100,   39,
 /*   460 */    38,   40,   42,   41,   48,   46,   44,   45,   43,   40,
 /*   470 */    42,   41,   48,   46,   44,   45,   43,  216,   39,   38,
 /*   480 */    40,   42,   41,   48,   46,   44,   45,   43,  133,   71,
 /*   490 */    17,   39,   38,   40,   42,   41,   48,   46,   44,   45,
 /*   500 */    43,  133,   69,  201,  133,   70,   37,   36,  181,  133,
 /*   510 */   208,   16,   35,  217,  128,   12,  195,  205,   47,   37,
 /*   520 */    36,  127,  124,  121,  118,   35,  217,  128,  133,  207,
 /*   530 */    81,   47,  133,  206,  127,  124,  121,  118,   22,  170,
 /*   540 */    11,   54,  165,  193,   10,  189,   51,  178,  104,  226,
 /*   550 */   102,  101,   19,   20,   95,  100,   39,   38,   40,   42,
 /*   560 */    41,   48,   46,   44,   45,   43,   37,   36,  133,   59,
 /*   570 */   133,   58,   35,  217,  128,  133,   66,  173,   47,  133,
 /*   580 */    65,  127,  124,  121,  118,  143,   56,  142,  172,   42,
 /*   590 */    41,   48,   46,   44,   45,   43,  169,  138,  133,   64,
 /*   600 */   166,   96,  133,   63,  133,   62,  133,   61,  158,  137,
 /*   610 */     8,  144,  338,    9,   50,   94,  145,  141,   93,   90,
 /*   620 */   168,   89,   78,   77,  167,  100,  136,  107,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    54,   20,   21,   22,   26,   59,   62,   63,   62,   65,
 /*    10 */     1,    2,   66,   67,   68,   69,   70,   71,   72,   73,
 /*    20 */    74,   75,   76,   77,   78,   26,    1,    2,   82,   83,
 /*    30 */    84,   85,   86,   87,   88,   89,    1,    2,   54,   93,
 /*    40 */    94,   95,   96,   59,   26,    1,   62,   38,    1,    2,
 /*    50 */    66,   67,   68,   69,   70,   71,    1,   73,   74,   75,
 /*    60 */    76,   77,   78,   38,    1,   30,   82,   83,   84,   85,
 /*    70 */    86,   87,   88,   89,    3,    4,   54,   93,   94,   95,
 /*    80 */    96,   59,   38,   28,   62,    3,    4,   30,   66,   67,
 /*    90 */    68,   69,   70,   71,    1,   73,   74,   75,   76,   77,
 /*   100 */    78,   38,   31,    1,   82,   83,   84,   85,   86,   87,
 /*   110 */    88,   89,    1,   31,   54,   93,   94,   95,   96,   59,
 /*   120 */     1,   28,   62,    3,    4,   31,   66,   67,   68,   69,
 /*   130 */    70,   71,   27,   73,   74,   75,   76,   77,   78,   61,
 /*   140 */    62,   63,   82,   83,   84,   85,   86,   87,   88,   89,
 /*   150 */    31,   31,   54,   93,   94,   95,   96,   59,    1,   27,
 /*   160 */    62,   61,   62,   63,   66,   67,   68,   69,   70,   71,
 /*   170 */    25,   73,   74,   75,   76,   77,   78,   61,   62,   63,
 /*   180 */    82,   83,   84,   85,   86,   87,   88,   89,   31,    1,
 /*   190 */    54,   93,   94,   95,   96,   59,   28,    1,   62,   61,
 /*   200 */    62,   63,   66,   67,   68,   69,   70,   71,   28,   73,
 /*   210 */    74,   75,   76,   77,   78,   62,   63,   64,   82,   83,
 /*   220 */    84,   85,   86,   87,   88,   89,   38,    1,   54,   93,
 /*   230 */    94,   95,   96,   59,   38,    1,   62,   79,   80,   81,
 /*   240 */    66,   67,   68,   69,   70,   71,   30,   73,   74,   75,
 /*   250 */    76,   77,   78,   61,   62,   63,   82,   83,   84,   85,
 /*   260 */    86,   87,   88,   89,   38,   31,   54,   93,   94,   95,
 /*   270 */    96,   59,   62,   63,   62,   62,   63,   64,   66,   67,
 /*   280 */    68,   69,   70,   71,   30,   73,   74,   75,   76,   77,
 /*   290 */    78,   62,   63,   64,   82,   83,   84,   85,   86,   87,
 /*   300 */    88,   89,   62,   63,   64,   93,   94,   95,   96,    7,
 /*   310 */     8,    9,   10,   11,   12,   13,   14,   15,   16,   17,
 /*   320 */    18,   19,   20,   21,   22,   18,   19,   38,   29,   40,
 /*   330 */    29,   24,   25,   26,   59,   60,   29,   30,   31,    5,
 /*   340 */    33,   34,   35,   36,   18,   19,   20,   21,   22,   59,
 /*   350 */    60,   26,   18,   19,   62,   63,   31,   65,   24,   25,
 /*   360 */    26,   31,   62,   63,   30,   65,    5,   33,   34,   35,
 /*   370 */    36,   62,   63,    1,   65,   62,   63,   30,   65,   18,
 /*   380 */    19,   59,   60,   31,   50,   24,   25,   26,   30,   62,
 /*   390 */    63,   30,   65,   29,   33,   34,   35,   36,   30,   62,
 /*   400 */    63,   31,   65,   31,   62,   63,   18,   19,   62,   63,
 /*   410 */    29,   50,   24,   25,   26,   62,   63,   29,   30,   31,
 /*   420 */    31,   33,   34,   35,   36,   62,   63,   62,   63,   62,
 /*   430 */    63,   62,   63,   26,   14,   15,   16,   17,   18,   19,
 /*   440 */    20,   21,   22,   27,   37,   38,   39,   40,   41,   27,
 /*   450 */    43,   44,   25,   46,   47,   25,   49,   28,   51,   13,
 /*   460 */    14,   15,   16,   17,   18,   19,   20,   21,   22,   15,
 /*   470 */    16,   17,   18,   19,   20,   21,   22,   31,   13,   14,
 /*   480 */    15,   16,   17,   18,   19,   20,   21,   22,   62,   63,
 /*   490 */    30,   13,   14,   15,   16,   17,   18,   19,   20,   21,
 /*   500 */    22,   62,   63,   38,   62,   63,   18,   19,   41,   62,
 /*   510 */    63,    4,   24,   25,   26,   30,   38,   29,   30,   18,
 /*   520 */    19,   33,   34,   35,   36,   24,   25,   26,   62,   63,
 /*   530 */    26,   30,   62,   63,   33,   34,   35,   36,   45,   38,
 /*   540 */    30,   37,   38,   39,   30,   41,   30,   43,   44,    0,
 /*   550 */    46,   47,   30,   49,   26,   51,   13,   14,   15,   16,
 /*   560 */    17,   18,   19,   20,   21,   22,   18,   19,   62,   63,
 /*   570 */    62,   63,   24,   25,   26,   62,   63,   38,   30,   62,
 /*   580 */    63,   33,   34,   35,   36,   66,   37,   68,   38,   16,
 /*   590 */    17,   18,   19,   20,   21,   22,   38,   48,   62,   63,
 /*   600 */    38,   52,   62,   63,   62,   63,   62,   63,   38,   90,
 /*   610 */    91,   92,   56,   57,   53,   26,   97,   98,   59,   25,
 /*   620 */    94,   58,   26,   59,   94,   51,   26,   42,
};
#define YY_SHIFT_USE_DFLT (-23)
#define YY_SHIFT_COUNT (140)
#define YY_SHIFT_MIN   (-22)
#define YY_SHIFT_MAX   (600)
static const short yy_shift_ofst[] = {
 /*     0 */   -23,  504,  407,  504,  504,  504,  504,  504,  504,  549,
 /*    10 */   334,  334,  388,  361,  361,  334,  334,  334,  307,  488,
 /*    20 */   501,  488,  548,  548,  548,  548,  585,  548,  548,  548,
 /*    30 */   548,  548,  548,  548,  548,  548,  548,  548,  548,  548,
 /*    40 */   548,  548,  548,  548,  548,  548,  548,  548,  548,  325,
 /*    50 */   600,  600,  574,  574,  596,  594,  589,  302,  478,  465,
 /*    60 */   446,  543,  543,  543,  543,  543,  543,  543,  543,  420,
 /*    70 */   454,  573,  326,  326,  120,   82,   71,   25,    9,  -19,
 /*    80 */   -19,   35,  289,  372,  226,  234,  157,  196,  188,   93,
 /*    90 */    55,   47,  119,   63,   44,  561,  528,  570,  562,  558,
 /*   100 */   522,  550,  539,  493,  516,  514,  510,  467,  485,  507,
 /*   110 */   460,  429,  430,  427,  422,  416,  389,  381,  368,  370,
 /*   120 */   364,  358,  352,  301,  347,  330,  299,  254,  216,  180,
 /*   130 */   168,  145,  132,  105,   94,  111,  102,   57,   18,   -1,
 /*   140 */   -22,
};
#define YY_REDUCE_USE_DFLT (-57)
#define YY_REDUCE_COUNT (56)
#define YY_REDUCE_MIN   (-56)
#define YY_REDUCE_MAX   (564)
static const short yy_reduce_ofst[] = {
 /*     0 */   556,  -54,  212,  174,  136,   98,   60,   22,  -16,  519,
 /*    10 */   337,  327,  240,  313,  309,  300,  292,  -56,  229,  213,
 /*    20 */   192,  153,  138,  116,  100,   78,  158,  544,  542,  540,
 /*    30 */   536,  517,  513,  508,  506,  470,  466,  447,  442,  439,
 /*    40 */   426,  369,  367,  365,  363,  353,  346,  342,  210,  322,
 /*    50 */   290,  275,  530,  526,  564,  563,  559,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   335,  337,  337,  337,  337,  337,  337,  337,  337,  337,
 /*    10 */   337,  337,  337,  337,  337,  337,  337,  337,  337,  337,
 /*    20 */   337,  337,  337,  337,  337,  337,  291,  337,  337,  337,
 /*    30 */   337,  337,  337,  337,  337,  337,  337,  337,  337,  337,
 /*    40 */   337,  337,  337,  337,  337,  337,  337,  337,  337,  337,
 /*    50 */   337,  337,  312,  311,  337,  337,  337,  337,  337,  337,
 /*    60 */   337,  268,  267,  266,  265,  264,  263,  235,  239,  258,
 /*    70 */   259,  257,  256,  255,  337,  337,  337,  337,  337,  250,
 /*    80 */   251,  337,  337,  337,  337,  337,  337,  337,  337,  337,
 /*    90 */   337,  337,  337,  337,  337,  337,  337,  337,  337,  337,
 /*   100 */   337,  337,  337,  337,  337,  337,  337,  290,  337,  270,
 /*   110 */   337,  337,  337,  337,  337,  244,  337,  337,  337,  337,
 /*   120 */   337,  337,  337,  337,  337,  337,  337,  337,  238,  337,
 /*   130 */   337,  337,  337,  244,  337,  232,  231,  337,  337,  337,
 /*   140 */   337,  336,  334,  333,  332,  331,  330,  303,  283,  292,
 /*   150 */   329,  328,  327,  326,  325,  324,  323,  322,  321,  320,
 /*   160 */   319,  318,  317,  316,  315,  314,  313,  310,  309,  308,
 /*   170 */   304,  305,  299,  298,  297,  296,  295,  294,  293,  289,
 /*   180 */   288,  287,  286,  285,  307,  306,  272,  271,  269,  284,
 /*   190 */   282,  280,  279,  281,  276,  274,  278,  236,  233,  228,
 /*   200 */   227,  277,  243,  242,  241,  240,  262,  261,  260,  254,
 /*   210 */   253,  252,  249,  248,  247,  246,  245,  237,  234,  302,
 /*   220 */   301,  300,  275,  230,  273,  229,
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
  "LOCATION",      "VAR",           "SEMICOLON",     "LBRACKET",    
  "RBRACKET",      "IF",            "ELSE",          "WHILE",       
  "FOR",           "COLON",         "CONTINUE",      "BREAK",       
  "FUNCTION",      "RETURN",        "CONDITIONNAME",  "ACTIONNAME",  
  "FROM",          "IMPORT",        "error",         "nt",          
  "program",       "chunks",        "numList",       "nameListMulti",
  "nameList",      "exprList",      "funcexpr",      "expr",        
  "fArgs",         "lexpr",         "vdef_stmt",     "vdefAssign_stmt",
  "vdefMulti_stmt",  "vdefMultiAssign_stmt",  "assign_stmt",   "assignMulti_stmt",
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
 /*  47 */ "vdef_stmt ::= VAR NAME SEMICOLON",
 /*  48 */ "vdefAssign_stmt ::= VAR NAME ASSIGN expr SEMICOLON",
 /*  49 */ "vdefMulti_stmt ::= VAR nameListMulti SEMICOLON",
 /*  50 */ "vdefMultiAssign_stmt ::= VAR nameListMulti ASSIGN exprList SEMICOLON",
 /*  51 */ "assign_stmt ::= NAME ASSIGN expr SEMICOLON",
 /*  52 */ "assignMulti_stmt ::= nameListMulti ASSIGN exprList SEMICOLON",
 /*  53 */ "stmtList ::= stmt",
 /*  54 */ "stmtList ::= stmtList stmt",
 /*  55 */ "blockStart ::= LBRACKET",
 /*  56 */ "block ::= blockStart stmtList RBRACKET",
 /*  57 */ "block ::= blockStart error RBRACKET",
 /*  58 */ "if_start ::= IF",
 /*  59 */ "if_header ::= if_start LPAREN lexpr RPAREN",
 /*  60 */ "if_block ::= if_header stmt",
 /*  61 */ "elif_start ::= ELSE IF",
 /*  62 */ "elif_header ::= elif_start LPAREN lexpr RPAREN",
 /*  63 */ "if_block ::= if_block elif_header stmt",
 /*  64 */ "else_header ::= ELSE",
 /*  65 */ "if_stmt ::= if_block",
 /*  66 */ "if_stmt ::= if_block else_header stmt",
 /*  67 */ "while_start ::= WHILE",
 /*  68 */ "while_header ::= while_start LPAREN lexpr RPAREN",
 /*  69 */ "while_stmt ::= while_header stmt",
 /*  70 */ "foreach_header ::= FOR LPAREN nameList COLON exprList RPAREN",
 /*  71 */ "foreach_stmt ::= foreach_header stmt",
 /*  72 */ "continue_stmt ::= CONTINUE SEMICOLON",
 /*  73 */ "break_stmt ::= BREAK SEMICOLON",
 /*  74 */ "function_start ::= FUNCTION NAME",
 /*  75 */ "function_header ::= function_start LPAREN nameList RPAREN",
 /*  76 */ "function_header ::= function_start LPAREN RPAREN",
 /*  77 */ "fdef_chunk ::= function_header stmt",
 /*  78 */ "return_stmt ::= RETURN SEMICOLON",
 /*  79 */ "return_stmt ::= RETURN exprList SEMICOLON",
 /*  80 */ "lexpr ::= CONDITIONNAME LPAREN fArgs RPAREN",
 /*  81 */ "lexpr ::= CONDITIONNAME LPAREN RPAREN",
 /*  82 */ "action ::= ACTIONNAME LPAREN fArgs RPAREN SEMICOLON",
 /*  83 */ "actions ::= action action",
 /*  84 */ "actions ::= actions action",
 /*  85 */ "actionStmt ::= action",
 /*  86 */ "actionStmt ::= actions",
 /*  87 */ "stmt ::= error SEMICOLON",
 /*  88 */ "stmt ::= SEMICOLON",
 /*  89 */ "stmt ::= vdef_stmt",
 /*  90 */ "stmt ::= vdefAssign_stmt",
 /*  91 */ "stmt ::= vdefMultiAssign_stmt",
 /*  92 */ "stmt ::= vdefMulti_stmt",
 /*  93 */ "stmt ::= assign_stmt",
 /*  94 */ "stmt ::= assignMulti_stmt",
 /*  95 */ "stmt ::= funcexpr SEMICOLON",
 /*  96 */ "stmt ::= actionStmt",
 /*  97 */ "stmt ::= if_stmt",
 /*  98 */ "stmt ::= while_stmt",
 /*  99 */ "stmt ::= foreach_stmt",
 /* 100 */ "stmt ::= continue_stmt",
 /* 101 */ "stmt ::= break_stmt",
 /* 102 */ "stmt ::= return_stmt",
 /* 103 */ "stmt ::= block",
 /* 104 */ "import_chunk ::= FROM NAME IMPORT nameList",
 /* 105 */ "chunk ::= import_chunk",
 /* 106 */ "chunk ::= fdef_chunk",
 /* 107 */ "chunk ::= vdef_stmt",
 /* 108 */ "chunk ::= vdefMulti_stmt",
 /* 109 */ "chunks ::=",
 /* 110 */ "chunks ::= chunks chunk",
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
    case 55: /* nt */
{
#line 29 "parser\\epparser.lemon"
 delete (yypminor->yy0); 
#line 670 "parser\\epparser.c"
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
  { 56, 1 },
  { 58, 3 },
  { 58, 3 },
  { 59, 3 },
  { 59, 3 },
  { 60, 1 },
  { 60, 1 },
  { 61, 6 },
  { 63, 6 },
  { 61, 1 },
  { 61, 3 },
  { 63, 1 },
  { 63, 1 },
  { 64, 1 },
  { 64, 1 },
  { 64, 3 },
  { 62, 4 },
  { 62, 3 },
  { 63, 1 },
  { 63, 3 },
  { 63, 4 },
  { 63, 4 },
  { 63, 4 },
  { 63, 4 },
  { 63, 3 },
  { 63, 3 },
  { 63, 3 },
  { 63, 3 },
  { 63, 3 },
  { 63, 3 },
  { 63, 3 },
  { 63, 3 },
  { 63, 3 },
  { 63, 3 },
  { 63, 2 },
  { 63, 2 },
  { 63, 2 },
  { 65, 3 },
  { 65, 3 },
  { 65, 3 },
  { 65, 3 },
  { 65, 3 },
  { 65, 3 },
  { 65, 3 },
  { 65, 3 },
  { 65, 2 },
  { 65, 3 },
  { 66, 3 },
  { 67, 5 },
  { 68, 3 },
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
  { 65, 4 },
  { 65, 3 },
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
  { 57, 0 },
  { 57, 2 },
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
#line 1080 "parser\\epparser.c"
        break;
      case 3: /* nameListMulti ::= NAME COMMA NAME */
      case 4: /* nameListMulti ::= nameListMulti COMMA NAME */ yytestcase(yyruleno==4);
      case 10: /* exprList ::= exprList COMMA exprList */ yytestcase(yyruleno==10);
#line 63 "parser\\epparser.lemon"
{ yygotominor.yy0 = new Token((yymsp[-2].minor.yy0->data) + ", " + (yymsp[0].minor.yy0->data), yymsp[0].minor.yy0); delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1087 "parser\\epparser.c"
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
#line 1099 "parser\\epparser.c"
        break;
      case 7: /* exprList ::= funcexpr LSQBRACKET LSQBRACKET numList RSQBRACKET RSQBRACKET */
      case 8: /* expr ::= funcexpr LSQBRACKET LSQBRACKET NUMBER RSQBRACKET RSQBRACKET */ yytestcase(yyruleno==8);
#line 68 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[-2].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = _SRET(" << yymsp[-5].minor.yy0->data << ", [" << yymsp[-2].minor.yy0->data << "])" << std::endl;
    delete yymsp[-5].minor.yy0; delete yymsp[-2].minor.yy0;
}
#line 1109 "parser\\epparser.c"
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
#line 1120 "parser\\epparser.c"
        break;
      case 15: /* fArgs ::= fArgs COMMA fArgs */
#line 96 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data;
    yymsp[-2].minor.yy0->type = TOKEN_TEMP;
    yygotominor.yy0 = yymsp[-2].minor.yy0;
}
#line 1129 "parser\\epparser.c"
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
#line 1144 "parser\\epparser.c"
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
#line 1159 "parser\\epparser.c"
        break;
      case 19: /* expr ::= LPAREN expr RPAREN */
#line 130 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0, ps->gen);
}
#line 1167 "parser\\epparser.c"
        break;
      case 20: /* expr ::= MAPSTRING LPAREN STRING RPAREN */
#line 135 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetStringIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0, ps->gen);
}
#line 1175 "parser\\epparser.c"
        break;
      case 21: /* expr ::= UNIT LPAREN STRING RPAREN */
#line 140 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetUnitIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0, ps->gen);
}
#line 1183 "parser\\epparser.c"
        break;
      case 22: /* expr ::= SWITCH LPAREN STRING RPAREN */
#line 145 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetSwitchIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0, ps->gen);
}
#line 1191 "parser\\epparser.c"
        break;
      case 23: /* expr ::= LOCATION LPAREN STRING RPAREN */
#line 150 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetLocationIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0, ps->gen);
}
#line 1199 "parser\\epparser.c"
        break;
      case 24: /* expr ::= expr PLUS expr */
#line 155 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "+",  yymsp[0].minor.yy0, ps->gen); }
#line 1204 "parser\\epparser.c"
        break;
      case 25: /* expr ::= expr MINUS expr */
#line 156 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "-",  yymsp[0].minor.yy0, ps->gen); }
#line 1209 "parser\\epparser.c"
        break;
      case 26: /* expr ::= expr MULTIPLY expr */
#line 157 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "*",  yymsp[0].minor.yy0, ps->gen); }
#line 1214 "parser\\epparser.c"
        break;
      case 27: /* expr ::= expr DIVIDE expr */
#line 158 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "//", yymsp[0].minor.yy0, ps->gen); }
#line 1219 "parser\\epparser.c"
        break;
      case 28: /* expr ::= expr MOD expr */
#line 159 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "%",  yymsp[0].minor.yy0, ps->gen); }
#line 1224 "parser\\epparser.c"
        break;
      case 29: /* expr ::= expr LSHIFT expr */
#line 160 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<<", yymsp[0].minor.yy0, ps->gen); }
#line 1229 "parser\\epparser.c"
        break;
      case 30: /* expr ::= expr RSHIFT expr */
#line 161 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">>", yymsp[0].minor.yy0, ps->gen); }
#line 1234 "parser\\epparser.c"
        break;
      case 31: /* expr ::= expr BITAND expr */
#line 162 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "&",  yymsp[0].minor.yy0, ps->gen); }
#line 1239 "parser\\epparser.c"
        break;
      case 32: /* expr ::= expr BITOR expr */
#line 163 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "|",  yymsp[0].minor.yy0, ps->gen); }
#line 1244 "parser\\epparser.c"
        break;
      case 33: /* expr ::= expr BITXOR expr */
#line 164 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "^",  yymsp[0].minor.yy0, ps->gen); }
#line 1249 "parser\\epparser.c"
        break;
      case 34: /* expr ::= PLUS expr */
#line 167 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = +" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1254 "parser\\epparser.c"
        break;
      case 35: /* expr ::= MINUS expr */
#line 168 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = -" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1259 "parser\\epparser.c"
        break;
      case 36: /* expr ::= BITNOT expr */
#line 169 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = ~" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1264 "parser\\epparser.c"
        break;
      case 37: /* lexpr ::= expr EQ expr */
#line 172 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "==", yymsp[0].minor.yy0, ps->gen); }
#line 1269 "parser\\epparser.c"
        break;
      case 38: /* lexpr ::= expr NE expr */
#line 173 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "!=", yymsp[0].minor.yy0, ps->gen); }
#line 1274 "parser\\epparser.c"
        break;
      case 39: /* lexpr ::= expr LE expr */
#line 174 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<=", yymsp[0].minor.yy0, ps->gen); }
#line 1279 "parser\\epparser.c"
        break;
      case 40: /* lexpr ::= expr LT expr */
#line 175 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<",  yymsp[0].minor.yy0, ps->gen); }
#line 1284 "parser\\epparser.c"
        break;
      case 41: /* lexpr ::= expr GE expr */
#line 176 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">=", yymsp[0].minor.yy0, ps->gen); }
#line 1289 "parser\\epparser.c"
        break;
      case 42: /* lexpr ::= expr GT expr */
#line 177 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">" , yymsp[0].minor.yy0, ps->gen); }
#line 1294 "parser\\epparser.c"
        break;
      case 43: /* lexpr ::= lexpr LAND lexpr */
#line 179 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "[" + yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data + "]";
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0, ps->gen);
}
#line 1303 "parser\\epparser.c"
        break;
      case 44: /* lexpr ::= lexpr LOR lexpr */
#line 185 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "EUDOr([" + yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data + "])";
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0, ps->gen);
}
#line 1312 "parser\\epparser.c"
        break;
      case 45: /* lexpr ::= LNOT lexpr */
#line 191 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = "EUDNot([" + yymsp[0].minor.yy0->data + "])";
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0, ps->gen);
}
#line 1320 "parser\\epparser.c"
        break;
      case 47: /* vdef_stmt ::= VAR NAME SEMICOLON */
#line 201 "parser\\epparser.lemon"
{
    if(!ps->closure.defVariable(yymsp[-1].minor.yy0->data)) {
        throw_error(yymsp[-1].minor.yy0->line, 196, ("Redeclaration of variable \'" + (yymsp[-1].minor.yy0->data) + "\'"));
    }
    ps->gen << yymsp[-1].minor.yy0->data << " = EUDVariable()" << std::endl;
    delete yymsp[-1].minor.yy0;
}
#line 1331 "parser\\epparser.c"
        break;
      case 48: /* vdefAssign_stmt ::= VAR NAME ASSIGN expr SEMICOLON */
#line 209 "parser\\epparser.lemon"
{
    if(!ps->closure.defVariable(yymsp[-3].minor.yy0->data)) {
        throw_error(yymsp[-3].minor.yy0->line, 196, ("Redeclaration of variable \'" + (yymsp[-3].minor.yy0->data) + "\'"));
    }
    ps->gen << yymsp[-3].minor.yy0->data << " = _MVAR([" << yymsp[-1].minor.yy0->data << "])" << std::endl;
    delete yymsp[-3].minor.yy0;
}
#line 1342 "parser\\epparser.c"
        break;
      case 49: /* vdefMulti_stmt ::= VAR nameListMulti SEMICOLON */
#line 217 "parser\\epparser.lemon"
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
#line 1359 "parser\\epparser.c"
        break;
      case 50: /* vdefMultiAssign_stmt ::= VAR nameListMulti ASSIGN exprList SEMICOLON */
#line 231 "parser\\epparser.lemon"
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
#line 1375 "parser\\epparser.c"
        break;
      case 51: /* assign_stmt ::= NAME ASSIGN expr SEMICOLON */
#line 244 "parser\\epparser.lemon"
{
    ps->gen << yymsp[-3].minor.yy0->data << " << " << yymsp[-1].minor.yy0->data << std::endl;
    if(!ps->closure.getVariable(yymsp[-3].minor.yy0->data)) {
        throw_error(yymsp[-3].minor.yy0->line, 103, ("Undeclared variable \'" + (yymsp[-3].minor.yy0->data) + "\'"));
        ps->closure.defVariable(yymsp[-3].minor.yy0->data);
    }
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1387 "parser\\epparser.c"
        break;
      case 52: /* assignMulti_stmt ::= nameListMulti ASSIGN exprList SEMICOLON */
#line 253 "parser\\epparser.lemon"
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
#line 1403 "parser\\epparser.c"
        break;
      case 55: /* blockStart ::= LBRACKET */
#line 269 "parser\\epparser.lemon"
{
    ps->closure.pushScope();
}
#line 1410 "parser\\epparser.c"
        break;
      case 56: /* block ::= blockStart stmtList RBRACKET */
#line 273 "parser\\epparser.lemon"
{
    ps->closure.popScope();
}
#line 1417 "parser\\epparser.c"
        break;
      case 57: /* block ::= blockStart error RBRACKET */
#line 277 "parser\\epparser.lemon"
{
    throw_error(yymsp[0].minor.yy0->line, 6298, "Block not terminated properly.");
    ps->closure.popScope();
}
#line 1425 "parser\\epparser.c"
        break;
      case 58: /* if_start ::= IF */
#line 284 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDIf()" << std::endl;
}
#line 1433 "parser\\epparser.c"
        break;
      case 59: /* if_header ::= if_start LPAREN lexpr RPAREN */
      case 68: /* while_header ::= while_start LPAREN lexpr RPAREN */ yytestcase(yyruleno==68);
#line 288 "parser\\epparser.lemon"
{
    ps->gen << "if " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data << "):" << std::endl;
    ps->gen.indent();
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1443 "parser\\epparser.c"
        break;
      case 61: /* elif_start ::= ELSE IF */
#line 296 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen.unindent(false);
    ps->gen << yygotominor.yy0->data << " = EUDElseIf()" << std::endl;
}
#line 1452 "parser\\epparser.c"
        break;
      case 62: /* elif_header ::= elif_start LPAREN lexpr RPAREN */
#line 302 "parser\\epparser.lemon"
{
    ps->gen << "if " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data <<"):" << std::endl;
    ps->gen.indent();
}
#line 1460 "parser\\epparser.c"
        break;
      case 64: /* else_header ::= ELSE */
#line 309 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "if EUDElse()():" << std::endl;
    ps->gen.indent();
}
#line 1469 "parser\\epparser.c"
        break;
      case 65: /* if_stmt ::= if_block */
      case 66: /* if_stmt ::= if_block else_header stmt */ yytestcase(yyruleno==66);
#line 315 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndIf()" << std::endl;
}
#line 1478 "parser\\epparser.c"
        break;
      case 67: /* while_start ::= WHILE */
#line 327 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDWhile()" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1487 "parser\\epparser.c"
        break;
      case 69: /* while_stmt ::= while_header stmt */
#line 339 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndWhile()" << std::endl;
}
#line 1495 "parser\\epparser.c"
        break;
      case 70: /* foreach_header ::= FOR LPAREN nameList COLON exprList RPAREN */
#line 345 "parser\\epparser.lemon"
{
    ps->gen << "for " << yymsp[-3].minor.yy0->data << " in " << yymsp[-1].minor.yy0->data << ":" << std::endl;
    ps->gen.indent();
    commaListIter(yymsp[-3].minor.yy0->data, [&](std::string& s) {
        ps->closure.defVariable(s);
    });
}
#line 1506 "parser\\epparser.c"
        break;
      case 71: /* foreach_stmt ::= foreach_header stmt */
      case 77: /* fdef_chunk ::= function_header stmt */ yytestcase(yyruleno==77);
#line 353 "parser\\epparser.lemon"
{
    ps->gen.unindent(true);
}
#line 1514 "parser\\epparser.c"
        break;
      case 72: /* continue_stmt ::= CONTINUE SEMICOLON */
#line 359 "parser\\epparser.lemon"
{
    ps->gen << "EUDContinue()" << std::endl;
}
#line 1521 "parser\\epparser.c"
        break;
      case 73: /* break_stmt ::= BREAK SEMICOLON */
#line 363 "parser\\epparser.lemon"
{
    ps->gen << "EUDBreak()" << std::endl;
}
#line 1528 "parser\\epparser.c"
        break;
      case 74: /* function_start ::= FUNCTION NAME */
#line 368 "parser\\epparser.lemon"
{
    // Preprocess yymsp[0].minor.yy0
    funcNamePreprocess(yymsp[0].minor.yy0->data);
    yygotominor.yy0 = yymsp[0].minor.yy0;
    if(!ps->closure.defFunction(yymsp[0].minor.yy0->data)) {
        throw_error(yymsp[0].minor.yy0->line, 4495, "Duplicate function yymsp[0].minor.yy0 " + yymsp[0].minor.yy0->data);
    }
}
#line 1540 "parser\\epparser.c"
        break;
      case 75: /* function_header ::= function_start LPAREN nameList RPAREN */
#line 377 "parser\\epparser.lemon"
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
#line 1560 "parser\\epparser.c"
        break;
      case 76: /* function_header ::= function_start LPAREN RPAREN */
#line 394 "parser\\epparser.lemon"
{
    ps->gen << "@EUDFunc" << std::endl;
    ps->gen << "def " << yymsp[-2].minor.yy0->data << "():" << std::endl;
    ps->gen.indent();
    tmpIndex = 1;
    delete yymsp[-2].minor.yy0;
}
#line 1571 "parser\\epparser.c"
        break;
      case 78: /* return_stmt ::= RETURN SEMICOLON */
#line 408 "parser\\epparser.lemon"
{
    ps->gen << "EUDReturn()" << std::endl;
}
#line 1578 "parser\\epparser.c"
        break;
      case 79: /* return_stmt ::= RETURN exprList SEMICOLON */
#line 412 "parser\\epparser.lemon"
{
    ps->gen << "EUDReturn(" << yymsp[-1].minor.yy0->data << ")" << std::endl;
    delete yymsp[-1].minor.yy0;
}
#line 1586 "parser\\epparser.c"
        break;
      case 80: /* lexpr ::= CONDITIONNAME LPAREN fArgs RPAREN */
#line 420 "parser\\epparser.lemon"
{
    yymsp[-3].minor.yy0->data = yymsp[-3].minor.yy0->data + "(" + yymsp[-1].minor.yy0->data + ")";
    delete yymsp[-1].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0, ps->gen);
}
#line 1595 "parser\\epparser.c"
        break;
      case 81: /* lexpr ::= CONDITIONNAME LPAREN RPAREN */
#line 426 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + "()";
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0, ps->gen);
}
#line 1603 "parser\\epparser.c"
        break;
      case 82: /* action ::= ACTIONNAME LPAREN fArgs RPAREN SEMICOLON */
#line 431 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[-4].minor.yy0);
    yygotominor.yy0->data =  yymsp[-4].minor.yy0->data + "(" + yymsp[-2].minor.yy0->data + ")";
    delete yymsp[-4].minor.yy0; delete yymsp[-2].minor.yy0;
}
#line 1612 "parser\\epparser.c"
        break;
      case 83: /* actions ::= action action */
      case 84: /* actions ::= actions action */ yytestcase(yyruleno==84);
#line 437 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
    yymsp[-1].minor.yy0->data += ",\n" + yymsp[0].minor.yy0->data;
    delete yymsp[0].minor.yy0;
}
#line 1622 "parser\\epparser.c"
        break;
      case 85: /* actionStmt ::= action */
#line 449 "parser\\epparser.lemon"
{
    ps->gen << "DoActions(" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1630 "parser\\epparser.c"
        break;
      case 86: /* actionStmt ::= actions */
#line 454 "parser\\epparser.lemon"
{
    ps->gen << "DoActions([" << std::endl;
    ps->gen.indent();
    ps->gen << yymsp[0].minor.yy0->data << std::endl;
    ps->gen.unindent(false);
    ps->gen << "])" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1642 "parser\\epparser.c"
        break;
      case 87: /* stmt ::= error SEMICOLON */
#line 465 "parser\\epparser.lemon"
{ throw_error(yymsp[0].minor.yy0->line, 6974, "Error while parsing statement"); }
#line 1647 "parser\\epparser.c"
        break;
      case 95: /* stmt ::= funcexpr SEMICOLON */
#line 475 "parser\\epparser.lemon"
{ ps->gen << yymsp[-1].minor.yy0->data << std::endl; }
#line 1652 "parser\\epparser.c"
        break;
      case 104: /* import_chunk ::= FROM NAME IMPORT nameList */
#line 488 "parser\\epparser.lemon"
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
#line 1667 "parser\\epparser.c"
        break;
      default:
      /* (0) program ::= chunks */ yytestcase(yyruleno==0);
      /* (53) stmtList ::= stmt */ yytestcase(yyruleno==53);
      /* (54) stmtList ::= stmtList stmt */ yytestcase(yyruleno==54);
      /* (60) if_block ::= if_header stmt */ yytestcase(yyruleno==60);
      /* (63) if_block ::= if_block elif_header stmt */ yytestcase(yyruleno==63);
      /* (88) stmt ::= SEMICOLON */ yytestcase(yyruleno==88);
      /* (89) stmt ::= vdef_stmt */ yytestcase(yyruleno==89);
      /* (90) stmt ::= vdefAssign_stmt */ yytestcase(yyruleno==90);
      /* (91) stmt ::= vdefMultiAssign_stmt */ yytestcase(yyruleno==91);
      /* (92) stmt ::= vdefMulti_stmt */ yytestcase(yyruleno==92);
      /* (93) stmt ::= assign_stmt */ yytestcase(yyruleno==93);
      /* (94) stmt ::= assignMulti_stmt */ yytestcase(yyruleno==94);
      /* (96) stmt ::= actionStmt */ yytestcase(yyruleno==96);
      /* (97) stmt ::= if_stmt */ yytestcase(yyruleno==97);
      /* (98) stmt ::= while_stmt */ yytestcase(yyruleno==98);
      /* (99) stmt ::= foreach_stmt */ yytestcase(yyruleno==99);
      /* (100) stmt ::= continue_stmt */ yytestcase(yyruleno==100);
      /* (101) stmt ::= break_stmt */ yytestcase(yyruleno==101);
      /* (102) stmt ::= return_stmt */ yytestcase(yyruleno==102);
      /* (103) stmt ::= block */ yytestcase(yyruleno==103);
      /* (105) chunk ::= import_chunk */ yytestcase(yyruleno==105);
      /* (106) chunk ::= fdef_chunk */ yytestcase(yyruleno==106);
      /* (107) chunk ::= vdef_stmt */ yytestcase(yyruleno==107);
      /* (108) chunk ::= vdefMulti_stmt */ yytestcase(yyruleno==108);
      /* (109) chunks ::= */ yytestcase(yyruleno==109);
      /* (110) chunks ::= chunks chunk */ yytestcase(yyruleno==110);
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
#line 1758 "parser\\epparser.c"
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
#line 507 "parser\\epparser.lemon"


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
#line 1988 "parser\\epparser.c"
