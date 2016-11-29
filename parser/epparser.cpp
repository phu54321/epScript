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
#define YYNOCODE 102
#define YYACTIONTYPE unsigned short int
#define ParseTOKENTYPE Token*
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  int yy203;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL  ParserStruct* ps ;
#define ParseARG_PDECL , ParserStruct* ps 
#define ParseARG_FETCH  ParserStruct* ps  = yypParser->ps 
#define ParseARG_STORE yypParser->ps  = ps 
#define YYNSTATE 230
#define YYNRULE 112
#define YYERRORSYMBOL 56
#define YYERRSYMDT yy203
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
#define YY_ACTTAB_COUNT (598)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */    99,  147,  143,  146,  229,   89,  141,  136,   98,   44,
 /*    10 */    45,   43,  172,  171,  170,  169,  168,  109,    5,   27,
 /*    20 */   151,  111,    6,  148,  165,  106,    3,  164,    2,  163,
 /*    30 */   162,  161,  149,  145,  135,  158,   58,   57,  166,  159,
 /*    40 */    99,   55,   25,  143,   28,   89,  134,  228,   98,  107,
 /*    50 */     4,    1,  172,  171,  170,  169,  168,  109,    5,   27,
 /*    60 */   190,   15,   16,  227,  165,  106,    3,  164,    2,  163,
 /*    70 */   162,  161,   18,  133,   26,  158,   58,   57,  166,  159,
 /*    80 */   199,   55,   99,   90,  138,   70,  137,   89,  226,  220,
 /*    90 */    98,  200,  138,   70,  172,  171,  170,  169,  168,  109,
 /*   100 */     5,   27,  187,   15,   16,   97,  165,  106,    3,  164,
 /*   110 */     2,  163,  162,  161,   21,   15,   16,  158,   58,   57,
 /*   120 */   166,  159,   99,   55,   88,  138,   70,   89,  141,   24,
 /*   130 */    98,  191,   21,  225,  172,  171,  170,  169,  168,  109,
 /*   140 */     5,   27,  184,  188,  205,    7,  165,  106,    3,  164,
 /*   150 */     2,  163,  162,  161,   86,  138,   70,  158,   58,   57,
 /*   160 */   166,  159,  202,   55,   99,   85,  138,   70,   59,   89,
 /*   170 */   132,   80,   98,  132,   69,  206,  172,  171,  170,  169,
 /*   180 */   168,  109,    5,   27,  182,   15,   16,  224,  165,  106,
 /*   190 */     3,  164,    2,  163,  162,  161,  132,   69,   83,  158,
 /*   200 */    58,   57,  166,  159,   99,   55,   84,  138,   70,   89,
 /*   210 */   142,  140,   98,  185,  142,  139,  172,  171,  170,  169,
 /*   220 */   168,  109,    5,   27,  152,  132,   69,   91,  165,  106,
 /*   230 */     3,  164,    2,  163,  162,  161,   23,  142,   87,  158,
 /*   240 */    58,   57,  166,  159,   89,   55,  223,   98,  132,   69,
 /*   250 */    92,  172,  171,  170,  169,  168,  109,    5,   27,  132,
 /*   260 */    60,   25,   82,  165,  106,    3,  164,    2,  163,  162,
 /*   270 */   161,   25,   25,  227,   56,   58,   57,  166,  157,  131,
 /*   280 */    21,  155,   34,   32,   31,   30,   29,   33,   39,   38,
 /*   290 */    40,   42,   41,   48,   47,   44,   45,   43,   25,  194,
 /*   300 */    37,   36,  183,  142,  104,  130,   35,  222,  128,  193,
 /*   310 */   100,  207,   46,  201,   14,  127,  126,  123,  120,  117,
 /*   320 */    48,   47,   44,   45,   43,  142,  150,   37,   36,  132,
 /*   330 */    60,  129,  210,   35,  222,  128,  179,  142,  110,   46,
 /*   340 */   124,   13,  127,  126,  123,  120,  117,  132,   60,  135,
 /*   350 */   114,  144,  132,   81,   37,   36,  196,  132,   62,  113,
 /*   360 */    35,  222,  128,  132,  203,   18,   46,  132,  215,  127,
 /*   370 */   126,  123,  120,  117,  132,  214,  132,   60,   17,  209,
 /*   380 */   125,   37,   36,  132,   75,  219,  113,   35,  222,  128,
 /*   390 */   132,   74,  207,   46,  204,  122,  127,  126,  123,  120,
 /*   400 */   117,   37,   36,  132,   73,  343,    8,   35,  222,  128,
 /*   410 */   132,   71,  207,   46,  121,  218,  127,  126,  123,  120,
 /*   420 */   117,   37,   36,  132,   72,  132,  213,   35,  222,  128,
 /*   430 */   119,  132,  212,   46,   79,  118,  127,  126,  123,  120,
 /*   440 */   117,  217,  178,  116,  132,  211,   52,  173,   53,  192,
 /*   450 */   115,  186,  105,  216,  103,  102,   79,   20,   16,  101,
 /*   460 */   197,  156,  132,   60,   12,  208,  132,   68,   52,  173,
 /*   470 */    53,  192,  198,  186,  105,   49,  103,  102,   11,   20,
 /*   480 */   189,  101,  160,   39,   38,   40,   42,   41,   48,   47,
 /*   490 */    44,   45,   43,   40,   42,   41,   48,   47,   44,   45,
 /*   500 */    43,  221,   39,   38,   40,   42,   41,   48,   47,   44,
 /*   510 */    45,   43,   42,   41,   48,   47,   44,   45,   43,  132,
 /*   520 */    60,   10,   78,   37,   36,  230,  132,   67,  195,   35,
 /*   530 */   222,  128,   22,  132,   60,   46,   77,    9,  127,  126,
 /*   540 */   123,  120,  117,   39,   38,   40,   42,   41,   48,   47,
 /*   550 */    44,   45,   43,   38,   40,   42,   41,   48,   47,   44,
 /*   560 */    45,   43,   51,   54,   19,   53,  132,   60,  181,   76,
 /*   570 */   132,   66,  180,  112,  132,   65,  132,   64,   95,   96,
 /*   580 */   132,   63,  132,   61,  177,  174,  167,   93,  153,   94,
 /*   590 */   176,   50,  101,  175,  144,  154,  156,  108,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    56,   68,    1,   70,   26,   61,    1,    1,   64,   20,
 /*    10 */    21,   22,   68,   69,   70,   71,   72,   73,   74,   75,
 /*    20 */    76,   88,   89,   90,   80,   81,   82,   83,   84,   85,
 /*    30 */    86,   87,   99,  100,   28,   91,   92,   93,   94,   95,
 /*    40 */    56,   97,    1,    1,    2,   61,    1,   26,   64,   77,
 /*    50 */    78,   79,   68,   69,   70,   71,   72,   73,   74,   75,
 /*    60 */    76,    3,    4,   39,   80,   81,   82,   83,   84,   85,
 /*    70 */    86,   87,   30,   28,    2,   91,   92,   93,   94,   95,
 /*    80 */    39,   97,   56,   63,   64,   65,   27,   61,   25,   31,
 /*    90 */    64,   63,   64,   65,   68,   69,   70,   71,   72,   73,
 /*   100 */    74,   75,   76,    3,    4,   56,   80,   81,   82,   83,
 /*   110 */    84,   85,   86,   87,    1,    3,    4,   91,   92,   93,
 /*   120 */    94,   95,   56,   97,   63,   64,   65,   61,    1,    2,
 /*   130 */    64,   31,    1,   28,   68,   69,   70,   71,   72,   73,
 /*   140 */    74,   75,   76,   31,   31,   96,   80,   81,   82,   83,
 /*   150 */    84,   85,   86,   87,   63,   64,   65,   91,   92,   93,
 /*   160 */    94,   95,   31,   97,   56,   63,   64,   65,   27,   61,
 /*   170 */    64,   65,   64,   64,   65,   66,   68,   69,   70,   71,
 /*   180 */    72,   73,   74,   75,   76,    3,    4,   25,   80,   81,
 /*   190 */    82,   83,   84,   85,   86,   87,   64,   65,   66,   91,
 /*   200 */    92,   93,   94,   95,   56,   97,   63,   64,   65,   61,
 /*   210 */    61,   62,   64,   31,   61,   62,   68,   69,   70,   71,
 /*   220 */    72,   73,   74,   75,   76,   64,   65,   66,   80,   81,
 /*   230 */    82,   83,   84,   85,   86,   87,    2,   61,   62,   91,
 /*   240 */    92,   93,   94,   95,   61,   97,   28,   64,   64,   65,
 /*   250 */    66,   68,   69,   70,   71,   72,   73,   74,   75,   64,
 /*   260 */    65,    1,   67,   80,   81,   82,   83,   84,   85,   86,
 /*   270 */    87,    1,    1,   39,   91,   92,   93,   94,   95,   27,
 /*   280 */     1,   98,    7,    8,    9,   10,   11,   12,   13,   14,
 /*   290 */    15,   16,   17,   18,   19,   20,   21,   22,    1,   39,
 /*   300 */    18,   19,   31,   61,   62,   27,   24,   25,   26,   39,
 /*   310 */    31,   29,   30,   31,    5,   33,   34,   35,   36,   37,
 /*   320 */    18,   19,   20,   21,   22,   61,   62,   18,   19,   64,
 /*   330 */    65,   25,   67,   24,   25,   26,   39,   61,   62,   30,
 /*   340 */    29,    5,   33,   34,   35,   36,   37,   64,   65,   28,
 /*   350 */    67,   26,   64,   65,   18,   19,   31,   64,   65,   50,
 /*   360 */    24,   25,   26,   64,   65,   30,   30,   64,   65,   33,
 /*   370 */    34,   35,   36,   37,   64,   65,   64,   65,   30,   67,
 /*   380 */    30,   18,   19,   64,   65,   31,   50,   24,   25,   26,
 /*   390 */    64,   65,   29,   30,   31,   30,   33,   34,   35,   36,
 /*   400 */    37,   18,   19,   64,   65,   58,   59,   24,   25,   26,
 /*   410 */    64,   65,   29,   30,   29,   31,   33,   34,   35,   36,
 /*   420 */    37,   18,   19,   64,   65,   64,   65,   24,   25,   26,
 /*   430 */    30,   64,   65,   30,   26,   29,   33,   34,   35,   36,
 /*   440 */    37,   31,   39,   30,   64,   65,   38,   39,   40,   41,
 /*   450 */    29,   43,   44,   31,   46,   47,   26,   49,    4,   51,
 /*   460 */    31,   53,   64,   65,   30,   67,   64,   65,   38,   39,
 /*   470 */    40,   41,   26,   43,   44,   30,   46,   47,   30,   49,
 /*   480 */    41,   51,   52,   13,   14,   15,   16,   17,   18,   19,
 /*   490 */    20,   21,   22,   15,   16,   17,   18,   19,   20,   21,
 /*   500 */    22,   31,   13,   14,   15,   16,   17,   18,   19,   20,
 /*   510 */    21,   22,   16,   17,   18,   19,   20,   21,   22,   64,
 /*   520 */    65,   30,   67,   18,   19,    0,   64,   65,   39,   24,
 /*   530 */    25,   26,   45,   64,   65,   30,   67,   30,   33,   34,
 /*   540 */    35,   36,   37,   13,   14,   15,   16,   17,   18,   19,
 /*   550 */    20,   21,   22,   14,   15,   16,   17,   18,   19,   20,
 /*   560 */    21,   22,   30,   38,   30,   40,   64,   65,   39,   67,
 /*   570 */    64,   65,   39,   48,   64,   65,   64,   65,   26,   54,
 /*   580 */    64,   65,   64,   65,   39,   39,   39,   60,   53,   25,
 /*   590 */    92,   55,   51,   92,   26,   98,   53,   42,
};
#define YY_SHIFT_USE_DFLT (-23)
#define YY_SHIFT_COUNT (144)
#define YY_SHIFT_MIN   (-22)
#define YY_SHIFT_MAX   (568)
static const short yy_shift_ofst[] = {
 /*     0 */   -23,  430,  430,  430,  430,  430,  430,  408,  525,  309,
 /*    10 */   309,  309,  363,  336,  336,  309,  309,  309,  282,  383,
 /*    20 */   403,  383,  505,  505,  505,  505,  505,  555,  505,  505,
 /*    30 */   505,  505,  505,  505,  505,  505,  505,  505,  505,  505,
 /*    40 */   505,  505,  505,  505,  505,  505,  505,  505,  505,  325,
 /*    50 */   568,  568,  568,  568,  568,  -23,  543,  541,  541,  564,
 /*    60 */   275,  489,  470,  530,  530,  530,  530,  530,  530,  530,
 /*    70 */   530,  539,  478,  496,  302,  302,  182,  112,  100,   42,
 /*    80 */   -11,  -11,   58,  279,  297,  271,  270,  234,  260,  127,
 /*    90 */    41,  131,  113,   45,    6,  536,  552,  535,  547,  546,
 /*   100 */   545,  534,  533,  529,  487,  532,  507,  491,  439,  448,
 /*   110 */   429,  445,  446,  434,  454,  422,  421,  413,  410,  406,
 /*   120 */   400,  384,  385,  365,  354,  311,  350,  348,  335,  321,
 /*   130 */   306,  278,  252,  218,  162,  105,   63,  141,   59,   72,
 /*   140 */    24,   21,    5,  -22,    1,
};
#define YY_REDUCE_USE_DFLT (-68)
#define YY_REDUCE_COUNT (59)
#define YY_REDUCE_MIN   (-67)
#define YY_REDUCE_MAX   (527)
static const short yy_reduce_ofst[] = {
 /*     0 */   347,  148,  108,   66,   26,  -16,  -56,  183,  -67,  502,
 /*    10 */   469,  455,  184,  398,  312,  283,  265,  195,  161,  132,
 /*    20 */   143,  109,  102,   91,   61,   28,   20,  -28,  518,  516,
 /*    30 */   512,  510,  506,  462,  402,  380,  367,  361,  359,  346,
 /*    40 */   339,  326,  319,  310,  303,  299,  293,  288,  106,  276,
 /*    50 */   264,  242,  176,  153,  149,   49,  497,  501,  498,  527,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   340,  342,  342,  342,  342,  342,  342,  342,  342,  342,
 /*    10 */   342,  342,  342,  342,  342,  342,  342,  342,  342,  342,
 /*    20 */   342,  342,  342,  342,  342,  342,  342,  290,  342,  342,
 /*    30 */   342,  342,  342,  342,  342,  342,  342,  342,  342,  342,
 /*    40 */   342,  342,  342,  342,  342,  342,  342,  342,  342,  342,
 /*    50 */   342,  342,  342,  342,  342,  326,  342,  311,  310,  342,
 /*    60 */   342,  342,  342,  273,  272,  271,  270,  269,  268,  243,
 /*    70 */   239,  263,  264,  262,  261,  260,  342,  342,  342,  342,
 /*    80 */   255,  256,  342,  342,  342,  342,  342,  342,  342,  342,
 /*    90 */   342,  342,  342,  342,  342,  342,  342,  342,  342,  342,
 /*   100 */   342,  342,  342,  342,  342,  342,  342,  342,  289,  342,
 /*   110 */   342,  342,  342,  342,  275,  342,  342,  342,  342,  342,
 /*   120 */   342,  342,  342,  342,  342,  342,  342,  342,  242,  342,
 /*   130 */   342,  342,  248,  342,  342,  342,  342,  342,  248,  342,
 /*   140 */   342,  342,  236,  342,  235,  341,  339,  338,  337,  336,
 /*   150 */   335,  302,  291,  334,  333,  332,  329,  327,  331,  330,
 /*   160 */   328,  325,  324,  323,  322,  321,  320,  319,  318,  317,
 /*   170 */   316,  315,  314,  313,  312,  309,  308,  307,  303,  304,
 /*   180 */   298,  297,  296,  295,  294,  293,  292,  288,  287,  286,
 /*   190 */   285,  284,  283,  279,  282,  281,  301,  300,  299,  280,
 /*   200 */   240,  247,  246,  257,  306,  305,  245,  244,  277,  276,
 /*   210 */   274,  267,  266,  265,  259,  258,  254,  253,  252,  251,
 /*   220 */   250,  249,  241,  237,  232,  238,  231,  278,  234,  233,
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
  "FUNCCALL",      "L2V",           "MAPSTRING",     "UNIT",        
  "SWITCH",        "LOCATION",      "VAR",           "SEMICOLON",   
  "CONST",         "IF",            "ELSE",          "WHILE",       
  "FOR",           "COLON",         "CONTINUE",      "BREAK",       
  "FUNCTION",      "RETURN",        "CONDITIONNAME",  "ACTIONNAME",  
  "LBRACKET",      "RBRACKET",      "FROM",          "IMPORT",      
  "error",         "nt",            "program",       "chunks",      
  "numList",       "nameListMulti",  "nameList",      "exprList",    
  "funcexpr",      "expr",          "fArgs",         "lexpr",       
  "vdef_stmt",     "vdefAssign_stmt",  "cdef_stmt",     "assign_stmt", 
  "assignMulti_stmt",  "if_start",      "if_header",     "if_block",    
  "stmt",          "elif_start",    "elif_header",   "else_header", 
  "if_stmt",       "while_start",   "while_header",  "while_stmt",  
  "foreach_header",  "foreach_stmt",  "continue_stmt",  "break_stmt",  
  "function_start",  "function_header",  "fdef_chunk",    "return_stmt", 
  "action",        "actions",       "actionStmt",    "bodyStmt",    
  "bodyStmtList",  "lbracket",      "rbracket",      "import_chunk",
  "chunk",       
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
 /*  20 */ "expr ::= L2V LPAREN lexpr RPAREN",
 /*  21 */ "expr ::= MAPSTRING LPAREN STRING RPAREN",
 /*  22 */ "expr ::= UNIT LPAREN STRING RPAREN",
 /*  23 */ "expr ::= SWITCH LPAREN STRING RPAREN",
 /*  24 */ "expr ::= LOCATION LPAREN STRING RPAREN",
 /*  25 */ "expr ::= expr PLUS expr",
 /*  26 */ "expr ::= expr MINUS expr",
 /*  27 */ "expr ::= expr MULTIPLY expr",
 /*  28 */ "expr ::= expr DIVIDE expr",
 /*  29 */ "expr ::= expr MOD expr",
 /*  30 */ "expr ::= expr LSHIFT expr",
 /*  31 */ "expr ::= expr RSHIFT expr",
 /*  32 */ "expr ::= expr BITAND expr",
 /*  33 */ "expr ::= expr BITOR expr",
 /*  34 */ "expr ::= expr BITXOR expr",
 /*  35 */ "expr ::= PLUS expr",
 /*  36 */ "expr ::= MINUS expr",
 /*  37 */ "expr ::= BITNOT expr",
 /*  38 */ "lexpr ::= expr EQ expr",
 /*  39 */ "lexpr ::= expr NE expr",
 /*  40 */ "lexpr ::= expr LE expr",
 /*  41 */ "lexpr ::= expr LT expr",
 /*  42 */ "lexpr ::= expr GE expr",
 /*  43 */ "lexpr ::= expr GT expr",
 /*  44 */ "lexpr ::= lexpr LAND lexpr",
 /*  45 */ "lexpr ::= lexpr LOR lexpr",
 /*  46 */ "lexpr ::= LNOT lexpr",
 /*  47 */ "lexpr ::= LNOT LNOT lexpr",
 /*  48 */ "vdef_stmt ::= VAR nameList SEMICOLON",
 /*  49 */ "vdefAssign_stmt ::= VAR nameList ASSIGN exprList SEMICOLON",
 /*  50 */ "cdef_stmt ::= CONST nameList ASSIGN exprList SEMICOLON",
 /*  51 */ "assign_stmt ::= NAME ASSIGN expr SEMICOLON",
 /*  52 */ "assignMulti_stmt ::= nameListMulti ASSIGN exprList SEMICOLON",
 /*  53 */ "if_start ::= IF",
 /*  54 */ "if_header ::= if_start LPAREN lexpr RPAREN",
 /*  55 */ "if_block ::= if_header stmt",
 /*  56 */ "elif_start ::= ELSE IF",
 /*  57 */ "elif_header ::= elif_start LPAREN lexpr RPAREN",
 /*  58 */ "if_block ::= if_block elif_header stmt",
 /*  59 */ "else_header ::= ELSE",
 /*  60 */ "if_stmt ::= if_block",
 /*  61 */ "if_stmt ::= if_block else_header stmt",
 /*  62 */ "while_start ::= WHILE",
 /*  63 */ "while_header ::= while_start LPAREN lexpr RPAREN",
 /*  64 */ "while_stmt ::= while_header stmt",
 /*  65 */ "foreach_header ::= FOR LPAREN nameList COLON exprList RPAREN",
 /*  66 */ "foreach_stmt ::= foreach_header stmt",
 /*  67 */ "continue_stmt ::= CONTINUE SEMICOLON",
 /*  68 */ "break_stmt ::= BREAK SEMICOLON",
 /*  69 */ "function_start ::= FUNCTION NAME",
 /*  70 */ "function_header ::= function_start LPAREN nameList RPAREN",
 /*  71 */ "function_header ::= function_start LPAREN RPAREN",
 /*  72 */ "fdef_chunk ::= function_header stmt",
 /*  73 */ "return_stmt ::= RETURN SEMICOLON",
 /*  74 */ "return_stmt ::= RETURN exprList SEMICOLON",
 /*  75 */ "lexpr ::= CONDITIONNAME LPAREN fArgs RPAREN",
 /*  76 */ "lexpr ::= CONDITIONNAME LPAREN RPAREN",
 /*  77 */ "action ::= ACTIONNAME LPAREN fArgs RPAREN SEMICOLON",
 /*  78 */ "actions ::= action action",
 /*  79 */ "actions ::= actions action",
 /*  80 */ "actionStmt ::= action",
 /*  81 */ "actionStmt ::= actions",
 /*  82 */ "stmt ::= error SEMICOLON",
 /*  83 */ "bodyStmt ::= SEMICOLON",
 /*  84 */ "bodyStmt ::= vdef_stmt",
 /*  85 */ "bodyStmt ::= vdefAssign_stmt",
 /*  86 */ "bodyStmt ::= cdef_stmt",
 /*  87 */ "bodyStmt ::= assign_stmt",
 /*  88 */ "bodyStmt ::= assignMulti_stmt",
 /*  89 */ "bodyStmt ::= funcexpr SEMICOLON",
 /*  90 */ "bodyStmt ::= actionStmt",
 /*  91 */ "bodyStmt ::= if_stmt",
 /*  92 */ "bodyStmt ::= while_stmt",
 /*  93 */ "bodyStmt ::= foreach_stmt",
 /*  94 */ "bodyStmt ::= continue_stmt",
 /*  95 */ "bodyStmt ::= break_stmt",
 /*  96 */ "bodyStmtList ::=",
 /*  97 */ "bodyStmtList ::= bodyStmtList bodyStmt",
 /*  98 */ "lbracket ::= LBRACKET",
 /*  99 */ "rbracket ::= RBRACKET",
 /* 100 */ "stmt ::= bodyStmt",
 /* 101 */ "stmt ::= return_stmt",
 /* 102 */ "stmt ::= lbracket bodyStmtList rbracket",
 /* 103 */ "stmt ::= lbracket bodyStmtList return_stmt rbracket",
 /* 104 */ "stmt ::= lbracket error RBRACKET",
 /* 105 */ "import_chunk ::= FROM NAME IMPORT nameList",
 /* 106 */ "chunk ::= import_chunk",
 /* 107 */ "chunk ::= fdef_chunk",
 /* 108 */ "chunk ::= vdef_stmt",
 /* 109 */ "chunk ::= cdef_stmt",
 /* 110 */ "chunks ::=",
 /* 111 */ "chunks ::= chunks chunk",
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
    case 57: /* nt */
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
  { 58, 1 },
  { 60, 3 },
  { 60, 3 },
  { 61, 3 },
  { 61, 3 },
  { 62, 1 },
  { 62, 1 },
  { 63, 6 },
  { 65, 6 },
  { 63, 1 },
  { 63, 3 },
  { 65, 1 },
  { 65, 1 },
  { 66, 1 },
  { 66, 1 },
  { 66, 3 },
  { 64, 4 },
  { 64, 3 },
  { 65, 1 },
  { 65, 3 },
  { 65, 4 },
  { 65, 4 },
  { 65, 4 },
  { 65, 4 },
  { 65, 4 },
  { 65, 3 },
  { 65, 3 },
  { 65, 3 },
  { 65, 3 },
  { 65, 3 },
  { 65, 3 },
  { 65, 3 },
  { 65, 3 },
  { 65, 3 },
  { 65, 3 },
  { 65, 2 },
  { 65, 2 },
  { 65, 2 },
  { 67, 3 },
  { 67, 3 },
  { 67, 3 },
  { 67, 3 },
  { 67, 3 },
  { 67, 3 },
  { 67, 3 },
  { 67, 3 },
  { 67, 2 },
  { 67, 3 },
  { 68, 3 },
  { 69, 5 },
  { 70, 5 },
  { 71, 4 },
  { 72, 4 },
  { 73, 1 },
  { 74, 4 },
  { 75, 2 },
  { 77, 2 },
  { 78, 4 },
  { 75, 3 },
  { 79, 1 },
  { 80, 1 },
  { 80, 3 },
  { 81, 1 },
  { 82, 4 },
  { 83, 2 },
  { 84, 6 },
  { 85, 2 },
  { 86, 2 },
  { 87, 2 },
  { 88, 2 },
  { 89, 4 },
  { 89, 3 },
  { 90, 2 },
  { 91, 2 },
  { 91, 3 },
  { 67, 4 },
  { 67, 3 },
  { 92, 5 },
  { 93, 2 },
  { 93, 2 },
  { 94, 1 },
  { 94, 1 },
  { 76, 2 },
  { 95, 1 },
  { 95, 1 },
  { 95, 1 },
  { 95, 1 },
  { 95, 1 },
  { 95, 1 },
  { 95, 2 },
  { 95, 1 },
  { 95, 1 },
  { 95, 1 },
  { 95, 1 },
  { 95, 1 },
  { 95, 1 },
  { 96, 0 },
  { 96, 2 },
  { 97, 1 },
  { 98, 1 },
  { 76, 1 },
  { 76, 1 },
  { 76, 3 },
  { 76, 4 },
  { 76, 3 },
  { 99, 4 },
  { 100, 1 },
  { 100, 1 },
  { 100, 1 },
  { 100, 1 },
  { 59, 0 },
  { 59, 2 },
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
#line 1077 "parser\\epparser.c"
        break;
      case 3: /* nameListMulti ::= NAME COMMA NAME */
      case 4: /* nameListMulti ::= nameListMulti COMMA NAME */ yytestcase(yyruleno==4);
      case 10: /* exprList ::= exprList COMMA exprList */ yytestcase(yyruleno==10);
#line 63 "parser\\epparser.lemon"
{ yygotominor.yy0 = new Token((yymsp[-2].minor.yy0->data) + ", " + (yymsp[0].minor.yy0->data), yymsp[0].minor.yy0); delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1084 "parser\\epparser.c"
        break;
      case 5: /* nameList ::= NAME */
      case 6: /* nameList ::= nameListMulti */ yytestcase(yyruleno==6);
      case 9: /* exprList ::= expr */ yytestcase(yyruleno==9);
      case 11: /* expr ::= NUMBER */ yytestcase(yyruleno==11);
      case 13: /* fArgs ::= expr */ yytestcase(yyruleno==13);
      case 14: /* fArgs ::= STRING */ yytestcase(yyruleno==14);
      case 18: /* expr ::= funcexpr */ yytestcase(yyruleno==18);
      case 47: /* lexpr ::= LNOT LNOT lexpr */ yytestcase(yyruleno==47);
#line 65 "parser\\epparser.lemon"
{ yygotominor.yy0 = yymsp[0].minor.yy0; }
#line 1096 "parser\\epparser.c"
        break;
      case 7: /* exprList ::= funcexpr LSQBRACKET LSQBRACKET numList RSQBRACKET RSQBRACKET */
      case 8: /* expr ::= funcexpr LSQBRACKET LSQBRACKET NUMBER RSQBRACKET RSQBRACKET */ yytestcase(yyruleno==8);
#line 68 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[-2].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = _SRET(" << yymsp[-5].minor.yy0->data << ", [" << yymsp[-2].minor.yy0->data << "])" << std::endl;
    delete yymsp[-5].minor.yy0; delete yymsp[-2].minor.yy0;
}
#line 1106 "parser\\epparser.c"
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
#line 1117 "parser\\epparser.c"
        break;
      case 15: /* fArgs ::= fArgs COMMA fArgs */
#line 96 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data;
    yymsp[-2].minor.yy0->type = TOKEN_TEMP;
    yygotominor.yy0 = yymsp[-2].minor.yy0;
}
#line 1126 "parser\\epparser.c"
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
#line 1141 "parser\\epparser.c"
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
#line 1156 "parser\\epparser.c"
        break;
      case 19: /* expr ::= LPAREN expr RPAREN */
#line 131 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0, ps->gen);
}
#line 1164 "parser\\epparser.c"
        break;
      case 20: /* expr ::= L2V LPAREN lexpr RPAREN */
#line 136 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "_L2V(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = genTemp(yymsp[-1].minor.yy0);
}
#line 1172 "parser\\epparser.c"
        break;
      case 21: /* expr ::= MAPSTRING LPAREN STRING RPAREN */
#line 141 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetStringIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0, ps->gen);
}
#line 1180 "parser\\epparser.c"
        break;
      case 22: /* expr ::= UNIT LPAREN STRING RPAREN */
#line 146 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetUnitIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0, ps->gen);
}
#line 1188 "parser\\epparser.c"
        break;
      case 23: /* expr ::= SWITCH LPAREN STRING RPAREN */
#line 151 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetSwitchIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0, ps->gen);
}
#line 1196 "parser\\epparser.c"
        break;
      case 24: /* expr ::= LOCATION LPAREN STRING RPAREN */
#line 156 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetLocationIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0, ps->gen);
}
#line 1204 "parser\\epparser.c"
        break;
      case 25: /* expr ::= expr PLUS expr */
#line 162 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "+",  yymsp[0].minor.yy0, ps->gen); }
#line 1209 "parser\\epparser.c"
        break;
      case 26: /* expr ::= expr MINUS expr */
#line 163 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "-",  yymsp[0].minor.yy0, ps->gen); }
#line 1214 "parser\\epparser.c"
        break;
      case 27: /* expr ::= expr MULTIPLY expr */
#line 164 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "*",  yymsp[0].minor.yy0, ps->gen); }
#line 1219 "parser\\epparser.c"
        break;
      case 28: /* expr ::= expr DIVIDE expr */
#line 165 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "//", yymsp[0].minor.yy0, ps->gen); }
#line 1224 "parser\\epparser.c"
        break;
      case 29: /* expr ::= expr MOD expr */
#line 166 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "%",  yymsp[0].minor.yy0, ps->gen); }
#line 1229 "parser\\epparser.c"
        break;
      case 30: /* expr ::= expr LSHIFT expr */
#line 167 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<<", yymsp[0].minor.yy0, ps->gen); }
#line 1234 "parser\\epparser.c"
        break;
      case 31: /* expr ::= expr RSHIFT expr */
#line 168 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">>", yymsp[0].minor.yy0, ps->gen); }
#line 1239 "parser\\epparser.c"
        break;
      case 32: /* expr ::= expr BITAND expr */
#line 169 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "&",  yymsp[0].minor.yy0, ps->gen); }
#line 1244 "parser\\epparser.c"
        break;
      case 33: /* expr ::= expr BITOR expr */
#line 170 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "|",  yymsp[0].minor.yy0, ps->gen); }
#line 1249 "parser\\epparser.c"
        break;
      case 34: /* expr ::= expr BITXOR expr */
#line 171 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "^",  yymsp[0].minor.yy0, ps->gen); }
#line 1254 "parser\\epparser.c"
        break;
      case 35: /* expr ::= PLUS expr */
#line 174 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = +" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1259 "parser\\epparser.c"
        break;
      case 36: /* expr ::= MINUS expr */
#line 175 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = -" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1264 "parser\\epparser.c"
        break;
      case 37: /* expr ::= BITNOT expr */
#line 176 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = ~" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1269 "parser\\epparser.c"
        break;
      case 38: /* lexpr ::= expr EQ expr */
#line 180 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "==", yymsp[0].minor.yy0, ps->gen); }
#line 1274 "parser\\epparser.c"
        break;
      case 39: /* lexpr ::= expr NE expr */
#line 181 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "!=", yymsp[0].minor.yy0, ps->gen); }
#line 1279 "parser\\epparser.c"
        break;
      case 40: /* lexpr ::= expr LE expr */
#line 182 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<=", yymsp[0].minor.yy0, ps->gen); }
#line 1284 "parser\\epparser.c"
        break;
      case 41: /* lexpr ::= expr LT expr */
#line 183 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<",  yymsp[0].minor.yy0, ps->gen); }
#line 1289 "parser\\epparser.c"
        break;
      case 42: /* lexpr ::= expr GE expr */
#line 184 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">=", yymsp[0].minor.yy0, ps->gen); }
#line 1294 "parser\\epparser.c"
        break;
      case 43: /* lexpr ::= expr GT expr */
#line 185 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">" , yymsp[0].minor.yy0, ps->gen); }
#line 1299 "parser\\epparser.c"
        break;
      case 44: /* lexpr ::= lexpr LAND lexpr */
#line 187 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "[" + yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data + "]";
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0, ps->gen);
}
#line 1308 "parser\\epparser.c"
        break;
      case 45: /* lexpr ::= lexpr LOR lexpr */
#line 193 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "EUDOr([" + yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data + "])";
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0, ps->gen);
}
#line 1317 "parser\\epparser.c"
        break;
      case 46: /* lexpr ::= LNOT lexpr */
#line 199 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = "EUDNot([" + yymsp[0].minor.yy0->data + "])";
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0, ps->gen);
}
#line 1325 "parser\\epparser.c"
        break;
      case 48: /* vdef_stmt ::= VAR nameList SEMICOLON */
#line 209 "parser\\epparser.lemon"
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
#line 1342 "parser\\epparser.c"
        break;
      case 49: /* vdefAssign_stmt ::= VAR nameList ASSIGN exprList SEMICOLON */
#line 223 "parser\\epparser.lemon"
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
#line 1358 "parser\\epparser.c"
        break;
      case 50: /* cdef_stmt ::= CONST nameList ASSIGN exprList SEMICOLON */
#line 236 "parser\\epparser.lemon"
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
#line 1374 "parser\\epparser.c"
        break;
      case 51: /* assign_stmt ::= NAME ASSIGN expr SEMICOLON */
#line 249 "parser\\epparser.lemon"
{
    ps->gen << yymsp[-3].minor.yy0->data << " << " << yymsp[-1].minor.yy0->data << std::endl;
    if(!ps->closure.getVariable(yymsp[-3].minor.yy0->data)) {
        throw_error(yymsp[-3].minor.yy0->line, 103, ("Undeclared variable \'" + (yymsp[-3].minor.yy0->data) + "\'"));
        ps->closure.defVariable(yymsp[-3].minor.yy0->data);
    }
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1386 "parser\\epparser.c"
        break;
      case 52: /* assignMulti_stmt ::= nameListMulti ASSIGN exprList SEMICOLON */
#line 258 "parser\\epparser.lemon"
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
#line 1402 "parser\\epparser.c"
        break;
      case 53: /* if_start ::= IF */
#line 272 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDIf()" << std::endl;
}
#line 1410 "parser\\epparser.c"
        break;
      case 54: /* if_header ::= if_start LPAREN lexpr RPAREN */
      case 63: /* while_header ::= while_start LPAREN lexpr RPAREN */ yytestcase(yyruleno==63);
#line 276 "parser\\epparser.lemon"
{
    ps->gen << "if " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data << "):" << std::endl;
    ps->gen.indent();
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1420 "parser\\epparser.c"
        break;
      case 56: /* elif_start ::= ELSE IF */
#line 284 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen.unindent(false);
    ps->gen << yygotominor.yy0->data << " = EUDElseIf()" << std::endl;
}
#line 1429 "parser\\epparser.c"
        break;
      case 57: /* elif_header ::= elif_start LPAREN lexpr RPAREN */
#line 290 "parser\\epparser.lemon"
{
    ps->gen << "if " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data <<"):" << std::endl;
    ps->gen.indent();
}
#line 1437 "parser\\epparser.c"
        break;
      case 59: /* else_header ::= ELSE */
#line 297 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "if EUDElse()():" << std::endl;
    ps->gen.indent();
}
#line 1446 "parser\\epparser.c"
        break;
      case 60: /* if_stmt ::= if_block */
      case 61: /* if_stmt ::= if_block else_header stmt */ yytestcase(yyruleno==61);
#line 303 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndIf()" << std::endl;
}
#line 1455 "parser\\epparser.c"
        break;
      case 62: /* while_start ::= WHILE */
#line 315 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDWhile()" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1464 "parser\\epparser.c"
        break;
      case 64: /* while_stmt ::= while_header stmt */
#line 327 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndWhile()" << std::endl;
}
#line 1472 "parser\\epparser.c"
        break;
      case 65: /* foreach_header ::= FOR LPAREN nameList COLON exprList RPAREN */
#line 333 "parser\\epparser.lemon"
{
    ps->gen << "for " << yymsp[-3].minor.yy0->data << " in " << yymsp[-1].minor.yy0->data << ":" << std::endl;
    ps->gen.indent();
    ps->closure.pushScope();
    commaListIter(yymsp[-3].minor.yy0->data, [&](std::string& s) {
        ps->closure.defVariable(s);
    });
}
#line 1484 "parser\\epparser.c"
        break;
      case 66: /* foreach_stmt ::= foreach_header stmt */
      case 72: /* fdef_chunk ::= function_header stmt */ yytestcase(yyruleno==72);
#line 342 "parser\\epparser.lemon"
{
    ps->gen.unindent(true);
    ps->closure.popScope();
}
#line 1493 "parser\\epparser.c"
        break;
      case 67: /* continue_stmt ::= CONTINUE SEMICOLON */
#line 349 "parser\\epparser.lemon"
{
    ps->gen << "EUDContinue()" << std::endl;
}
#line 1500 "parser\\epparser.c"
        break;
      case 68: /* break_stmt ::= BREAK SEMICOLON */
#line 353 "parser\\epparser.lemon"
{
    ps->gen << "EUDBreak()" << std::endl;
}
#line 1507 "parser\\epparser.c"
        break;
      case 69: /* function_start ::= FUNCTION NAME */
#line 358 "parser\\epparser.lemon"
{
    // Preprocess yymsp[0].minor.yy0
    funcNamePreprocess(yymsp[0].minor.yy0->data);
    yygotominor.yy0 = yymsp[0].minor.yy0;
    if(!ps->closure.defFunction(yymsp[0].minor.yy0->data)) {
        throw_error(yymsp[0].minor.yy0->line, 4495, "Duplicate function yymsp[0].minor.yy0 " + yymsp[0].minor.yy0->data);
    }
    ps->closure.pushScope();
}
#line 1520 "parser\\epparser.c"
        break;
      case 70: /* function_header ::= function_start LPAREN nameList RPAREN */
#line 368 "parser\\epparser.lemon"
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
#line 1540 "parser\\epparser.c"
        break;
      case 71: /* function_header ::= function_start LPAREN RPAREN */
#line 385 "parser\\epparser.lemon"
{
    ps->gen << "@EUDFunc" << std::endl;
    ps->gen << "def " << yymsp[-2].minor.yy0->data << "():" << std::endl;
    ps->gen.indent();
    tmpIndex = 1;
    delete yymsp[-2].minor.yy0;
}
#line 1551 "parser\\epparser.c"
        break;
      case 73: /* return_stmt ::= RETURN SEMICOLON */
#line 400 "parser\\epparser.lemon"
{
    ps->gen << "EUDReturn()" << std::endl;
}
#line 1558 "parser\\epparser.c"
        break;
      case 74: /* return_stmt ::= RETURN exprList SEMICOLON */
#line 404 "parser\\epparser.lemon"
{
    ps->gen << "EUDReturn(" << yymsp[-1].minor.yy0->data << ")" << std::endl;
    delete yymsp[-1].minor.yy0;
}
#line 1566 "parser\\epparser.c"
        break;
      case 75: /* lexpr ::= CONDITIONNAME LPAREN fArgs RPAREN */
#line 412 "parser\\epparser.lemon"
{
    yymsp[-3].minor.yy0->data = yymsp[-3].minor.yy0->data + "(" + yymsp[-1].minor.yy0->data + ")";
    delete yymsp[-1].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0, ps->gen);
}
#line 1575 "parser\\epparser.c"
        break;
      case 76: /* lexpr ::= CONDITIONNAME LPAREN RPAREN */
#line 418 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + "()";
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0, ps->gen);
}
#line 1583 "parser\\epparser.c"
        break;
      case 77: /* action ::= ACTIONNAME LPAREN fArgs RPAREN SEMICOLON */
#line 423 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[-4].minor.yy0);
    yygotominor.yy0->data =  yymsp[-4].minor.yy0->data + "(" + yymsp[-2].minor.yy0->data + ")";
    delete yymsp[-4].minor.yy0; delete yymsp[-2].minor.yy0;
}
#line 1592 "parser\\epparser.c"
        break;
      case 78: /* actions ::= action action */
      case 79: /* actions ::= actions action */ yytestcase(yyruleno==79);
#line 429 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
    yymsp[-1].minor.yy0->data += ",\n" + yymsp[0].minor.yy0->data;
    delete yymsp[0].minor.yy0;
}
#line 1602 "parser\\epparser.c"
        break;
      case 80: /* actionStmt ::= action */
#line 441 "parser\\epparser.lemon"
{
    ps->gen << "DoActions(" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1610 "parser\\epparser.c"
        break;
      case 81: /* actionStmt ::= actions */
#line 446 "parser\\epparser.lemon"
{
    ps->gen << "DoActions([" << std::endl;
    ps->gen.indent();
    ps->gen << yymsp[0].minor.yy0->data << std::endl;
    ps->gen.unindent(false);
    ps->gen << "])" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1622 "parser\\epparser.c"
        break;
      case 82: /* stmt ::= error SEMICOLON */
#line 457 "parser\\epparser.lemon"
{ throw_error(yymsp[0].minor.yy0->line, 6974, "Error while parsing statement"); }
#line 1627 "parser\\epparser.c"
        break;
      case 89: /* bodyStmt ::= funcexpr SEMICOLON */
#line 466 "parser\\epparser.lemon"
{ ps->gen << yymsp[-1].minor.yy0->data << std::endl; }
#line 1632 "parser\\epparser.c"
        break;
      case 98: /* lbracket ::= LBRACKET */
#line 477 "parser\\epparser.lemon"
{ ps->closure.pushScope(); }
#line 1637 "parser\\epparser.c"
        break;
      case 99: /* rbracket ::= RBRACKET */
#line 478 "parser\\epparser.lemon"
{ ps->closure.popScope(); }
#line 1642 "parser\\epparser.c"
        break;
      case 104: /* stmt ::= lbracket error RBRACKET */
#line 484 "parser\\epparser.lemon"
{
    throw_error(yymsp[0].minor.yy0->line, 6298, "Block not terminated properly.");
    ps->closure.popScope();
}
#line 1650 "parser\\epparser.c"
        break;
      case 105: /* import_chunk ::= FROM NAME IMPORT nameList */
#line 491 "parser\\epparser.lemon"
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
#line 1665 "parser\\epparser.c"
        break;
      default:
      /* (0) program ::= chunks */ yytestcase(yyruleno==0);
      /* (55) if_block ::= if_header stmt */ yytestcase(yyruleno==55);
      /* (58) if_block ::= if_block elif_header stmt */ yytestcase(yyruleno==58);
      /* (83) bodyStmt ::= SEMICOLON */ yytestcase(yyruleno==83);
      /* (84) bodyStmt ::= vdef_stmt */ yytestcase(yyruleno==84);
      /* (85) bodyStmt ::= vdefAssign_stmt */ yytestcase(yyruleno==85);
      /* (86) bodyStmt ::= cdef_stmt */ yytestcase(yyruleno==86);
      /* (87) bodyStmt ::= assign_stmt */ yytestcase(yyruleno==87);
      /* (88) bodyStmt ::= assignMulti_stmt */ yytestcase(yyruleno==88);
      /* (90) bodyStmt ::= actionStmt */ yytestcase(yyruleno==90);
      /* (91) bodyStmt ::= if_stmt */ yytestcase(yyruleno==91);
      /* (92) bodyStmt ::= while_stmt */ yytestcase(yyruleno==92);
      /* (93) bodyStmt ::= foreach_stmt */ yytestcase(yyruleno==93);
      /* (94) bodyStmt ::= continue_stmt */ yytestcase(yyruleno==94);
      /* (95) bodyStmt ::= break_stmt */ yytestcase(yyruleno==95);
      /* (96) bodyStmtList ::= */ yytestcase(yyruleno==96);
      /* (97) bodyStmtList ::= bodyStmtList bodyStmt */ yytestcase(yyruleno==97);
      /* (100) stmt ::= bodyStmt */ yytestcase(yyruleno==100);
      /* (101) stmt ::= return_stmt */ yytestcase(yyruleno==101);
      /* (102) stmt ::= lbracket bodyStmtList rbracket */ yytestcase(yyruleno==102);
      /* (103) stmt ::= lbracket bodyStmtList return_stmt rbracket */ yytestcase(yyruleno==103);
      /* (106) chunk ::= import_chunk */ yytestcase(yyruleno==106);
      /* (107) chunk ::= fdef_chunk */ yytestcase(yyruleno==107);
      /* (108) chunk ::= vdef_stmt */ yytestcase(yyruleno==108);
      /* (109) chunk ::= cdef_stmt */ yytestcase(yyruleno==109);
      /* (110) chunks ::= */ yytestcase(yyruleno==110);
      /* (111) chunks ::= chunks chunk */ yytestcase(yyruleno==111);
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
#line 1757 "parser\\epparser.c"
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
#line 510 "parser\\epparser.lemon"


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

    if(!errorOccured) return iwCollapse(ps.gen.str());
    else throw std::runtime_error("Invalid syntax");
}
#line 1987 "parser\\epparser.c"
