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
#define YYNOCODE 101
#define YYACTIONTYPE unsigned short int
#define ParseTOKENTYPE Token*
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  int yy201;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL  ParserStruct* ps ;
#define ParseARG_PDECL , ParserStruct* ps 
#define ParseARG_FETCH  ParserStruct* ps  = yypParser->ps 
#define ParseARG_STORE yypParser->ps  = ps 
#define YYNSTATE 228
#define YYNRULE 110
#define YYERRORSYMBOL 56
#define YYERRSYMDT yy201
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
#define YY_ACTTAB_COUNT (633)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */    82,  142,   45,   46,   44,   89,   26,  140,   97,  106,
 /*    10 */     6,    3,  166,  165,  164,  163,  162,    2,  189,    1,
 /*    20 */   153,  108,    7,   28,   26,  142,   29,  159,  105,    5,
 /*    30 */   158,    4,  157,  156,  155,   16,   17,   98,  154,   57,
 /*    40 */    56,  160,   89,   26,  197,   97,   90,  137,   69,  166,
 /*    50 */   165,  164,  163,  162,   19,  150,    1,  153,  108,    7,
 /*    60 */    28,  227,  192,  218,  159,  105,    5,  158,    4,  157,
 /*    70 */   156,  155,   16,   17,   98,  154,   57,   56,  160,   89,
 /*    80 */    22,  191,   97,   16,   17,  226,  166,  165,  164,  163,
 /*    90 */   162,  225,  184,    1,  153,  108,    7,   28,   16,   17,
 /*   100 */   185,  159,  105,    5,  158,    4,  157,  156,  155,   27,
 /*   110 */   203,  182,  154,   57,   56,  160,   98,  198,  137,   69,
 /*   120 */   136,   89,  131,   59,   97,   81,  179,   58,  166,  165,
 /*   130 */   164,  163,  162,   24,  181,    1,  153,  108,    7,   28,
 /*   140 */    88,  137,   69,  159,  105,    5,  158,    4,  157,  156,
 /*   150 */   155,  140,   25,   98,  154,   57,   56,  160,   89,  141,
 /*   160 */   139,   97,   86,  137,   69,  166,  165,  164,  163,  162,
 /*   170 */   225,  178,    1,  153,  108,    7,   28,   85,  137,   69,
 /*   180 */   159,  105,    5,  158,    4,  157,  156,  155,   84,  137,
 /*   190 */    69,  154,   57,   56,  160,   98,  131,   68,  204,  223,
 /*   200 */    89,  131,   79,   97,  131,   68,   83,  166,  165,  164,
 /*   210 */   163,  162,  224,  176,    1,  153,  108,    7,   28,  131,
 /*   220 */    68,   91,  159,  105,    5,  158,    4,  157,  156,  155,
 /*   230 */   141,  138,   98,  154,   57,   56,  160,   89,  131,   59,
 /*   240 */    97,  208,  135,  221,  166,  165,  164,  163,  162,  222,
 /*   250 */   152,    1,  153,  108,    7,   28,  131,   68,   92,  159,
 /*   260 */   105,    5,  158,    4,  157,  156,  155,  130,   22,  134,
 /*   270 */   154,   57,   56,  160,   98,  131,   59,  129,  113,   89,
 /*   280 */   131,   59,   97,  207,  133,  128,  166,  165,  164,  163,
 /*   290 */   162,  134,  188,    1,  153,  108,    7,   28,  200,   26,
 /*   300 */    19,  159,  105,    5,  158,    4,  157,  156,  155,  141,
 /*   310 */    87,  132,  154,   57,   56,  160,   35,   33,   32,   31,
 /*   320 */    30,   34,   40,   39,   41,   43,   42,   49,   48,   45,
 /*   330 */    46,   44,   38,   37,  141,  103,   18,  173,   36,  220,
 /*   340 */   127,  141,  149,  205,   47,  199,   15,  126,  125,  122,
 /*   350 */   119,  116,   49,   48,   45,   46,   44,  141,  109,   38,
 /*   360 */    37,  131,   59,  124,  206,   36,  220,  127,   26,  131,
 /*   370 */    59,   47,   77,   22,  126,  125,  122,  119,  116,  131,
 /*   380 */    80,   14,   39,   41,   43,   42,   49,   48,   45,   46,
 /*   390 */    44,  131,   61,  112,   38,   37,  131,   59,  177,   76,
 /*   400 */    36,  220,  127,   99,  131,   59,   47,   75,  123,  126,
 /*   410 */   125,  122,  119,  116,   38,   37,  168,  131,  201,  151,
 /*   420 */    36,  220,  127,  131,  213,  205,   47,  202,  112,  126,
 /*   430 */   125,  122,  119,  116,  131,  212,   78,   41,   43,   42,
 /*   440 */    49,   48,   45,   46,   44,  131,   74,  121,   53,  167,
 /*   450 */    54,  190,  187,  186,  217,  180,  104,  143,  102,  101,
 /*   460 */   216,   21,  194,  100,  131,   73,  120,   38,   37,  131,
 /*   470 */    72,  131,   70,   36,  220,  127,  131,   71,  205,   47,
 /*   480 */   131,  211,  126,  125,  122,  119,  116,   38,   37,  131,
 /*   490 */   210,  131,  209,   36,  220,  127,  131,   67,  118,   47,
 /*   500 */    78,  117,  126,  125,  122,  119,  116,  215,  172,  131,
 /*   510 */    66,  115,   53,  167,   54,  190,  114,  186,   17,  180,
 /*   520 */   104,  214,  102,  101,   13,   21,   50,  100,   40,   39,
 /*   530 */    41,   43,   42,   49,   48,   45,   46,   44,  196,   43,
 /*   540 */    42,   49,   48,   45,   46,   44,  219,   40,   39,   41,
 /*   550 */    43,   42,   49,   48,   45,   46,   44,  131,   65,  131,
 /*   560 */    64,  131,   63,  195,  131,   62,   12,  183,   38,   37,
 /*   570 */   131,   60,   11,  193,   36,  220,  127,  146,  228,  145,
 /*   580 */    47,   10,   52,  126,  125,  122,  119,  116,   40,   39,
 /*   590 */    41,   43,   42,   49,   48,   45,   46,   44,  339,    9,
 /*   600 */   110,    8,  147,   23,  175,  174,   20,  148,  144,  171,
 /*   610 */   168,  161,   95,   51,   93,   94,   55,  170,   54,  143,
 /*   620 */   100,  169,  340,  107,  340,  340,  340,  340,  111,  340,
 /*   630 */   340,  340,   96,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    56,    1,   20,   21,   22,   61,    1,    1,   64,   80,
 /*    10 */    81,   82,   68,   69,   70,   71,   72,   73,   74,   75,
 /*    20 */    76,   77,   78,   79,    1,    1,    2,   83,   84,   85,
 /*    30 */    86,   87,   88,   89,   90,    3,    4,   56,   94,   95,
 /*    40 */    96,   97,   61,    1,   39,   64,   63,   64,   65,   68,
 /*    50 */    69,   70,   71,   72,   30,   74,   75,   76,   77,   78,
 /*    60 */    79,   26,   39,   31,   83,   84,   85,   86,   87,   88,
 /*    70 */    89,   90,    3,    4,   56,   94,   95,   96,   97,   61,
 /*    80 */     1,   39,   64,    3,    4,   26,   68,   69,   70,   71,
 /*    90 */    72,   39,   74,   75,   76,   77,   78,   79,    3,    4,
 /*   100 */    31,   83,   84,   85,   86,   87,   88,   89,   90,    2,
 /*   110 */    31,   31,   94,   95,   96,   97,   56,   63,   64,   65,
 /*   120 */    27,   61,   64,   65,   64,   67,   31,   27,   68,   69,
 /*   130 */    70,   71,   72,    2,   74,   75,   76,   77,   78,   79,
 /*   140 */    63,   64,   65,   83,   84,   85,   86,   87,   88,   89,
 /*   150 */    90,    1,    2,   56,   94,   95,   96,   97,   61,   61,
 /*   160 */    62,   64,   63,   64,   65,   68,   69,   70,   71,   72,
 /*   170 */    39,   74,   75,   76,   77,   78,   79,   63,   64,   65,
 /*   180 */    83,   84,   85,   86,   87,   88,   89,   90,   63,   64,
 /*   190 */    65,   94,   95,   96,   97,   56,   64,   65,   66,   28,
 /*   200 */    61,   64,   65,   64,   64,   65,   66,   68,   69,   70,
 /*   210 */    71,   72,   25,   74,   75,   76,   77,   78,   79,   64,
 /*   220 */    65,   66,   83,   84,   85,   86,   87,   88,   89,   90,
 /*   230 */    61,   62,   56,   94,   95,   96,   97,   61,   64,   65,
 /*   240 */    64,   67,    1,   28,   68,   69,   70,   71,   72,   25,
 /*   250 */    74,   75,   76,   77,   78,   79,   64,   65,   66,   83,
 /*   260 */    84,   85,   86,   87,   88,   89,   90,   27,    1,   28,
 /*   270 */    94,   95,   96,   97,   56,   64,   65,   27,   67,   61,
 /*   280 */    64,   65,   64,   67,    1,   25,   68,   69,   70,   71,
 /*   290 */    72,   28,   74,   75,   76,   77,   78,   79,   31,    1,
 /*   300 */    30,   83,   84,   85,   86,   87,   88,   89,   90,   61,
 /*   310 */    62,   28,   94,   95,   96,   97,    7,    8,    9,   10,
 /*   320 */    11,   12,   13,   14,   15,   16,   17,   18,   19,   20,
 /*   330 */    21,   22,   18,   19,   61,   62,   30,   39,   24,   25,
 /*   340 */    26,   61,   62,   29,   30,   31,    5,   33,   34,   35,
 /*   350 */    36,   37,   18,   19,   20,   21,   22,   61,   62,   18,
 /*   360 */    19,   64,   65,   30,   67,   24,   25,   26,    1,   64,
 /*   370 */    65,   30,   67,    1,   33,   34,   35,   36,   37,   64,
 /*   380 */    65,    5,   14,   15,   16,   17,   18,   19,   20,   21,
 /*   390 */    22,   64,   65,   52,   18,   19,   64,   65,   31,   67,
 /*   400 */    24,   25,   26,   31,   64,   65,   30,   67,   29,   33,
 /*   410 */    34,   35,   36,   37,   18,   19,   39,   64,   65,   42,
 /*   420 */    24,   25,   26,   64,   65,   29,   30,   31,   52,   33,
 /*   430 */    34,   35,   36,   37,   64,   65,   26,   15,   16,   17,
 /*   440 */    18,   19,   20,   21,   22,   64,   65,   30,   38,   39,
 /*   450 */    40,   41,   42,   43,   31,   45,   46,   26,   48,   49,
 /*   460 */    31,   51,   31,   53,   64,   65,   29,   18,   19,   64,
 /*   470 */    65,   64,   65,   24,   25,   26,   64,   65,   29,   30,
 /*   480 */    64,   65,   33,   34,   35,   36,   37,   18,   19,   64,
 /*   490 */    65,   64,   65,   24,   25,   26,   64,   65,   30,   30,
 /*   500 */    26,   29,   33,   34,   35,   36,   37,   31,   39,   64,
 /*   510 */    65,   30,   38,   39,   40,   41,   29,   43,    4,   45,
 /*   520 */    46,   31,   48,   49,   30,   51,   30,   53,   13,   14,
 /*   530 */    15,   16,   17,   18,   19,   20,   21,   22,   26,   16,
 /*   540 */    17,   18,   19,   20,   21,   22,   31,   13,   14,   15,
 /*   550 */    16,   17,   18,   19,   20,   21,   22,   64,   65,   64,
 /*   560 */    65,   64,   65,   31,   64,   65,   30,   43,   18,   19,
 /*   570 */    64,   65,   30,   39,   24,   25,   26,   68,    0,   70,
 /*   580 */    30,   30,   30,   33,   34,   35,   36,   37,   13,   14,
 /*   590 */    15,   16,   17,   18,   19,   20,   21,   22,   58,   59,
 /*   600 */    91,   92,   93,   47,   39,   39,   30,   98,   99,   39,
 /*   610 */    39,   39,   26,   55,   60,   25,   38,   95,   40,   26,
 /*   620 */    53,   95,  100,   44,  100,  100,  100,  100,   50,  100,
 /*   630 */   100,  100,   54,
};
#define YY_SHIFT_USE_DFLT (-19)
#define YY_SHIFT_COUNT (143)
#define YY_SHIFT_MIN   (-18)
#define YY_SHIFT_MAX   (593)
static const short yy_shift_ofst[] = {
 /*     0 */   -19,  474,  410,  474,  474,  474,  474,  474,  474,  578,
 /*    10 */   341,  341,  341,  396,  376,  376,  341,  341,  341,  314,
 /*    20 */   449,  469,  449,  550,  550,  550,  550,  550,  579,  550,
 /*    30 */   550,  550,  550,  550,  550,  550,  550,  550,  550,  550,
 /*    40 */   550,  550,  550,  550,  550,  550,  550,  550,  550,  550,
 /*    50 */   431,  593,  593,  593,  593,  593,  567,  567,  590,  309,
 /*    60 */   534,  515,  575,  575,  575,  575,  575,  575,  575,  575,
 /*    70 */   368,  422,  523,  334,  334,   95,   80,   69,   24,  -18,
 /*    80 */   -18,   32,  377,  372,  298,  367,   42,  131,   23,  150,
 /*    90 */     5,  267,   79,  283,  241,  558,  586,  572,  571,  570,
 /*   100 */   576,  566,  565,  556,  552,  551,  542,  524,  536,  532,
 /*   110 */   496,  512,  494,  514,  490,  487,  481,  476,  472,  468,
 /*   120 */   429,  437,  417,  423,  379,  333,  306,  270,  263,  260,
 /*   130 */   250,  240,  215,  224,  171,  187,  100,   93,  107,   52,
 /*   140 */    59,    6,   35,    0,
};
#define YY_REDUCE_USE_DFLT (-72)
#define YY_REDUCE_COUNT (58)
#define YY_REDUCE_MIN   (-71)
#define YY_REDUCE_MAX   (554)
static const short yy_reduce_ofst[] = {
 /*     0 */   540,  -56,  218,  176,  139,   97,   60,   18,  -19,  509,
 /*    10 */   340,  332,  305,  192,  297,  216,  211,  174,   58,  155,
 /*    20 */   140,  125,  132,  114,   99,   77,   54,  -17,  -71,  506,
 /*    30 */   500,  497,  495,  493,  445,  432,  427,  425,  416,  412,
 /*    40 */   407,  405,  400,  381,  370,  359,  353,  327,  315,  137,
 /*    50 */   296,  280,  273,  248,  169,   98,  526,  522,  554,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   336,  338,  338,  338,  338,  338,  338,  338,  338,  338,
 /*    10 */   338,  338,  338,  338,  338,  338,  338,  338,  338,  338,
 /*    20 */   338,  338,  338,  338,  338,  338,  338,  338,  293,  338,
 /*    30 */   338,  338,  338,  338,  338,  338,  338,  338,  338,  338,
 /*    40 */   338,  338,  338,  338,  338,  338,  338,  338,  338,  338,
 /*    50 */   338,  338,  338,  338,  338,  338,  314,  313,  338,  338,
 /*    60 */   338,  338,  271,  270,  269,  268,  267,  266,  241,  237,
 /*    70 */   261,  262,  260,  259,  258,  338,  338,  338,  338,  253,
 /*    80 */   254,  338,  338,  338,  338,  338,  338,  338,  338,  338,
 /*    90 */   338,  338,  338,  338,  338,  338,  338,  338,  338,  338,
 /*   100 */   338,  338,  338,  338,  338,  338,  338,  292,  338,  338,
 /*   110 */   338,  338,  338,  273,  338,  338,  338,  338,  338,  338,
 /*   120 */   338,  338,  338,  338,  338,  338,  338,  240,  338,  338,
 /*   130 */   338,  246,  338,  338,  338,  338,  338,  246,  338,  338,
 /*   140 */   338,  234,  338,  233,  337,  335,  334,  333,  332,  331,
 /*   150 */   305,  285,  294,  330,  329,  328,  327,  326,  325,  324,
 /*   160 */   323,  322,  321,  320,  319,  318,  317,  316,  315,  312,
 /*   170 */   311,  310,  306,  307,  301,  300,  299,  298,  297,  296,
 /*   180 */   295,  291,  290,  289,  288,  287,  286,  284,  282,  281,
 /*   190 */   283,  277,  280,  279,  304,  303,  302,  278,  238,  245,
 /*   200 */   244,  255,  309,  308,  243,  242,  275,  274,  272,  265,
 /*   210 */   264,  263,  257,  256,  252,  251,  250,  249,  248,  247,
 /*   220 */   239,  235,  230,  236,  229,  276,  232,  231,
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
  "CONST",         "LBRACKET",      "RBRACKET",      "IF",          
  "ELSE",          "WHILE",         "FOR",           "COLON",       
  "CONTINUE",      "BREAK",         "FUNCTION",      "RETURN",      
  "CONDITIONNAME",  "ACTIONNAME",    "FROM",          "IMPORT",      
  "error",         "nt",            "program",       "chunks",      
  "numList",       "nameListMulti",  "nameList",      "exprList",    
  "funcexpr",      "expr",          "fArgs",         "lexpr",       
  "vdef_stmt",     "vdefAssign_stmt",  "cdef_stmt",     "assign_stmt", 
  "assignMulti_stmt",  "stmtList",      "stmt",          "blockStart",  
  "block",         "if_start",      "if_header",     "if_block",    
  "elif_start",    "elif_header",   "else_header",   "if_stmt",     
  "while_start",   "while_header",  "while_stmt",    "foreach_header",
  "foreach_stmt",  "continue_stmt",  "break_stmt",    "function_start",
  "function_header",  "fdef_chunk",    "return_stmt",   "action",      
  "actions",       "actionStmt",    "import_chunk",  "chunk",       
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
 /*  91 */ "stmt ::= cdef_stmt",
 /*  92 */ "stmt ::= assign_stmt",
 /*  93 */ "stmt ::= assignMulti_stmt",
 /*  94 */ "stmt ::= funcexpr SEMICOLON",
 /*  95 */ "stmt ::= actionStmt",
 /*  96 */ "stmt ::= if_stmt",
 /*  97 */ "stmt ::= while_stmt",
 /*  98 */ "stmt ::= foreach_stmt",
 /*  99 */ "stmt ::= continue_stmt",
 /* 100 */ "stmt ::= break_stmt",
 /* 101 */ "stmt ::= return_stmt",
 /* 102 */ "stmt ::= block",
 /* 103 */ "import_chunk ::= FROM NAME IMPORT nameList",
 /* 104 */ "chunk ::= import_chunk",
 /* 105 */ "chunk ::= fdef_chunk",
 /* 106 */ "chunk ::= vdef_stmt",
 /* 107 */ "chunk ::= cdef_stmt",
 /* 108 */ "chunks ::=",
 /* 109 */ "chunks ::= chunks chunk",
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
#line 671 "parser\\epparser.c"
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
  { 73, 2 },
  { 75, 1 },
  { 76, 3 },
  { 76, 3 },
  { 77, 1 },
  { 78, 4 },
  { 79, 2 },
  { 80, 2 },
  { 81, 4 },
  { 79, 3 },
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
  { 67, 4 },
  { 67, 3 },
  { 95, 5 },
  { 96, 2 },
  { 96, 2 },
  { 97, 1 },
  { 97, 1 },
  { 74, 2 },
  { 74, 1 },
  { 74, 1 },
  { 74, 1 },
  { 74, 1 },
  { 74, 1 },
  { 74, 1 },
  { 74, 2 },
  { 74, 1 },
  { 74, 1 },
  { 74, 1 },
  { 74, 1 },
  { 74, 1 },
  { 74, 1 },
  { 74, 1 },
  { 74, 1 },
  { 98, 4 },
  { 99, 1 },
  { 99, 1 },
  { 99, 1 },
  { 99, 1 },
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
      case 47: /* lexpr ::= LNOT LNOT lexpr */ yytestcase(yyruleno==47);
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
#line 131 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0, ps->gen);
}
#line 1167 "parser\\epparser.c"
        break;
      case 20: /* expr ::= L2V LPAREN lexpr RPAREN */
#line 136 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "_L2V(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = genTemp(yymsp[-1].minor.yy0);
}
#line 1175 "parser\\epparser.c"
        break;
      case 21: /* expr ::= MAPSTRING LPAREN STRING RPAREN */
#line 141 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetStringIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0, ps->gen);
}
#line 1183 "parser\\epparser.c"
        break;
      case 22: /* expr ::= UNIT LPAREN STRING RPAREN */
#line 146 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetUnitIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0, ps->gen);
}
#line 1191 "parser\\epparser.c"
        break;
      case 23: /* expr ::= SWITCH LPAREN STRING RPAREN */
#line 151 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetSwitchIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0, ps->gen);
}
#line 1199 "parser\\epparser.c"
        break;
      case 24: /* expr ::= LOCATION LPAREN STRING RPAREN */
#line 156 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetLocationIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0, ps->gen);
}
#line 1207 "parser\\epparser.c"
        break;
      case 25: /* expr ::= expr PLUS expr */
#line 162 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "+",  yymsp[0].minor.yy0, ps->gen); }
#line 1212 "parser\\epparser.c"
        break;
      case 26: /* expr ::= expr MINUS expr */
#line 163 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "-",  yymsp[0].minor.yy0, ps->gen); }
#line 1217 "parser\\epparser.c"
        break;
      case 27: /* expr ::= expr MULTIPLY expr */
#line 164 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "*",  yymsp[0].minor.yy0, ps->gen); }
#line 1222 "parser\\epparser.c"
        break;
      case 28: /* expr ::= expr DIVIDE expr */
#line 165 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "//", yymsp[0].minor.yy0, ps->gen); }
#line 1227 "parser\\epparser.c"
        break;
      case 29: /* expr ::= expr MOD expr */
#line 166 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "%",  yymsp[0].minor.yy0, ps->gen); }
#line 1232 "parser\\epparser.c"
        break;
      case 30: /* expr ::= expr LSHIFT expr */
#line 167 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<<", yymsp[0].minor.yy0, ps->gen); }
#line 1237 "parser\\epparser.c"
        break;
      case 31: /* expr ::= expr RSHIFT expr */
#line 168 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">>", yymsp[0].minor.yy0, ps->gen); }
#line 1242 "parser\\epparser.c"
        break;
      case 32: /* expr ::= expr BITAND expr */
#line 169 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "&",  yymsp[0].minor.yy0, ps->gen); }
#line 1247 "parser\\epparser.c"
        break;
      case 33: /* expr ::= expr BITOR expr */
#line 170 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "|",  yymsp[0].minor.yy0, ps->gen); }
#line 1252 "parser\\epparser.c"
        break;
      case 34: /* expr ::= expr BITXOR expr */
#line 171 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "^",  yymsp[0].minor.yy0, ps->gen); }
#line 1257 "parser\\epparser.c"
        break;
      case 35: /* expr ::= PLUS expr */
#line 174 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = +" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1262 "parser\\epparser.c"
        break;
      case 36: /* expr ::= MINUS expr */
#line 175 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = -" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1267 "parser\\epparser.c"
        break;
      case 37: /* expr ::= BITNOT expr */
#line 176 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = ~" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1272 "parser\\epparser.c"
        break;
      case 38: /* lexpr ::= expr EQ expr */
#line 180 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "==", yymsp[0].minor.yy0, ps->gen); }
#line 1277 "parser\\epparser.c"
        break;
      case 39: /* lexpr ::= expr NE expr */
#line 181 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "!=", yymsp[0].minor.yy0, ps->gen); }
#line 1282 "parser\\epparser.c"
        break;
      case 40: /* lexpr ::= expr LE expr */
#line 182 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<=", yymsp[0].minor.yy0, ps->gen); }
#line 1287 "parser\\epparser.c"
        break;
      case 41: /* lexpr ::= expr LT expr */
#line 183 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<",  yymsp[0].minor.yy0, ps->gen); }
#line 1292 "parser\\epparser.c"
        break;
      case 42: /* lexpr ::= expr GE expr */
#line 184 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">=", yymsp[0].minor.yy0, ps->gen); }
#line 1297 "parser\\epparser.c"
        break;
      case 43: /* lexpr ::= expr GT expr */
#line 185 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">" , yymsp[0].minor.yy0, ps->gen); }
#line 1302 "parser\\epparser.c"
        break;
      case 44: /* lexpr ::= lexpr LAND lexpr */
#line 187 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "[" + yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data + "]";
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0, ps->gen);
}
#line 1311 "parser\\epparser.c"
        break;
      case 45: /* lexpr ::= lexpr LOR lexpr */
#line 193 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "EUDOr([" + yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data + "])";
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0, ps->gen);
}
#line 1320 "parser\\epparser.c"
        break;
      case 46: /* lexpr ::= LNOT lexpr */
#line 199 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = "EUDNot([" + yymsp[0].minor.yy0->data + "])";
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0, ps->gen);
}
#line 1328 "parser\\epparser.c"
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
#line 1345 "parser\\epparser.c"
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
#line 1361 "parser\\epparser.c"
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
#line 1377 "parser\\epparser.c"
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
#line 1389 "parser\\epparser.c"
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
#line 1405 "parser\\epparser.c"
        break;
      case 55: /* blockStart ::= LBRACKET */
#line 274 "parser\\epparser.lemon"
{
    ps->closure.pushScope();
}
#line 1412 "parser\\epparser.c"
        break;
      case 56: /* block ::= blockStart stmtList RBRACKET */
#line 278 "parser\\epparser.lemon"
{
    ps->closure.popScope();
}
#line 1419 "parser\\epparser.c"
        break;
      case 57: /* block ::= blockStart error RBRACKET */
#line 282 "parser\\epparser.lemon"
{
    throw_error(yymsp[0].minor.yy0->line, 6298, "Block not terminated properly.");
    ps->closure.popScope();
}
#line 1427 "parser\\epparser.c"
        break;
      case 58: /* if_start ::= IF */
#line 289 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDIf()" << std::endl;
}
#line 1435 "parser\\epparser.c"
        break;
      case 59: /* if_header ::= if_start LPAREN lexpr RPAREN */
      case 68: /* while_header ::= while_start LPAREN lexpr RPAREN */ yytestcase(yyruleno==68);
#line 293 "parser\\epparser.lemon"
{
    ps->gen << "if " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data << "):" << std::endl;
    ps->gen.indent();
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1445 "parser\\epparser.c"
        break;
      case 61: /* elif_start ::= ELSE IF */
#line 301 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen.unindent(false);
    ps->gen << yygotominor.yy0->data << " = EUDElseIf()" << std::endl;
}
#line 1454 "parser\\epparser.c"
        break;
      case 62: /* elif_header ::= elif_start LPAREN lexpr RPAREN */
#line 307 "parser\\epparser.lemon"
{
    ps->gen << "if " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data <<"):" << std::endl;
    ps->gen.indent();
}
#line 1462 "parser\\epparser.c"
        break;
      case 64: /* else_header ::= ELSE */
#line 314 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "if EUDElse()():" << std::endl;
    ps->gen.indent();
}
#line 1471 "parser\\epparser.c"
        break;
      case 65: /* if_stmt ::= if_block */
      case 66: /* if_stmt ::= if_block else_header stmt */ yytestcase(yyruleno==66);
#line 320 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndIf()" << std::endl;
}
#line 1480 "parser\\epparser.c"
        break;
      case 67: /* while_start ::= WHILE */
#line 332 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDWhile()" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1489 "parser\\epparser.c"
        break;
      case 69: /* while_stmt ::= while_header stmt */
#line 344 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndWhile()" << std::endl;
}
#line 1497 "parser\\epparser.c"
        break;
      case 70: /* foreach_header ::= FOR LPAREN nameList COLON exprList RPAREN */
#line 350 "parser\\epparser.lemon"
{
    ps->gen << "for " << yymsp[-3].minor.yy0->data << " in " << yymsp[-1].minor.yy0->data << ":" << std::endl;
    ps->gen.indent();
    commaListIter(yymsp[-3].minor.yy0->data, [&](std::string& s) {
        ps->closure.defVariable(s);
    });
}
#line 1508 "parser\\epparser.c"
        break;
      case 71: /* foreach_stmt ::= foreach_header stmt */
#line 358 "parser\\epparser.lemon"
{
    ps->gen.unindent(true);
}
#line 1515 "parser\\epparser.c"
        break;
      case 72: /* continue_stmt ::= CONTINUE SEMICOLON */
#line 364 "parser\\epparser.lemon"
{
    ps->gen << "EUDContinue()" << std::endl;
}
#line 1522 "parser\\epparser.c"
        break;
      case 73: /* break_stmt ::= BREAK SEMICOLON */
#line 368 "parser\\epparser.lemon"
{
    ps->gen << "EUDBreak()" << std::endl;
}
#line 1529 "parser\\epparser.c"
        break;
      case 74: /* function_start ::= FUNCTION NAME */
#line 373 "parser\\epparser.lemon"
{
    // Preprocess yymsp[0].minor.yy0
    funcNamePreprocess(yymsp[0].minor.yy0->data);
    yygotominor.yy0 = yymsp[0].minor.yy0;
    if(!ps->closure.defFunction(yymsp[0].minor.yy0->data)) {
        throw_error(yymsp[0].minor.yy0->line, 4495, "Duplicate function yymsp[0].minor.yy0 " + yymsp[0].minor.yy0->data);
    }
    ps->closure.pushScope();
}
#line 1542 "parser\\epparser.c"
        break;
      case 75: /* function_header ::= function_start LPAREN nameList RPAREN */
#line 383 "parser\\epparser.lemon"
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
#line 1562 "parser\\epparser.c"
        break;
      case 76: /* function_header ::= function_start LPAREN RPAREN */
#line 400 "parser\\epparser.lemon"
{
    ps->gen << "@EUDFunc" << std::endl;
    ps->gen << "def " << yymsp[-2].minor.yy0->data << "():" << std::endl;
    ps->gen.indent();
    tmpIndex = 1;
    delete yymsp[-2].minor.yy0;
}
#line 1573 "parser\\epparser.c"
        break;
      case 77: /* fdef_chunk ::= function_header stmt */
#line 408 "parser\\epparser.lemon"
{
    ps->gen.unindent(true);
    ps->closure.popScope();
}
#line 1581 "parser\\epparser.c"
        break;
      case 78: /* return_stmt ::= RETURN SEMICOLON */
#line 415 "parser\\epparser.lemon"
{
    ps->gen << "EUDReturn()" << std::endl;
}
#line 1588 "parser\\epparser.c"
        break;
      case 79: /* return_stmt ::= RETURN exprList SEMICOLON */
#line 419 "parser\\epparser.lemon"
{
    ps->gen << "EUDReturn(" << yymsp[-1].minor.yy0->data << ")" << std::endl;
    delete yymsp[-1].minor.yy0;
}
#line 1596 "parser\\epparser.c"
        break;
      case 80: /* lexpr ::= CONDITIONNAME LPAREN fArgs RPAREN */
#line 427 "parser\\epparser.lemon"
{
    yymsp[-3].minor.yy0->data = yymsp[-3].minor.yy0->data + "(" + yymsp[-1].minor.yy0->data + ")";
    delete yymsp[-1].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0, ps->gen);
}
#line 1605 "parser\\epparser.c"
        break;
      case 81: /* lexpr ::= CONDITIONNAME LPAREN RPAREN */
#line 433 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + "()";
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0, ps->gen);
}
#line 1613 "parser\\epparser.c"
        break;
      case 82: /* action ::= ACTIONNAME LPAREN fArgs RPAREN SEMICOLON */
#line 438 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[-4].minor.yy0);
    yygotominor.yy0->data =  yymsp[-4].minor.yy0->data + "(" + yymsp[-2].minor.yy0->data + ")";
    delete yymsp[-4].minor.yy0; delete yymsp[-2].minor.yy0;
}
#line 1622 "parser\\epparser.c"
        break;
      case 83: /* actions ::= action action */
      case 84: /* actions ::= actions action */ yytestcase(yyruleno==84);
#line 444 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
    yymsp[-1].minor.yy0->data += ",\n" + yymsp[0].minor.yy0->data;
    delete yymsp[0].minor.yy0;
}
#line 1632 "parser\\epparser.c"
        break;
      case 85: /* actionStmt ::= action */
#line 456 "parser\\epparser.lemon"
{
    ps->gen << "DoActions(" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1640 "parser\\epparser.c"
        break;
      case 86: /* actionStmt ::= actions */
#line 461 "parser\\epparser.lemon"
{
    ps->gen << "DoActions([" << std::endl;
    ps->gen.indent();
    ps->gen << yymsp[0].minor.yy0->data << std::endl;
    ps->gen.unindent(false);
    ps->gen << "])" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1652 "parser\\epparser.c"
        break;
      case 87: /* stmt ::= error SEMICOLON */
#line 472 "parser\\epparser.lemon"
{ throw_error(yymsp[0].minor.yy0->line, 6974, "Error while parsing statement"); }
#line 1657 "parser\\epparser.c"
        break;
      case 94: /* stmt ::= funcexpr SEMICOLON */
#line 481 "parser\\epparser.lemon"
{ ps->gen << yymsp[-1].minor.yy0->data << std::endl; }
#line 1662 "parser\\epparser.c"
        break;
      case 103: /* import_chunk ::= FROM NAME IMPORT nameList */
#line 494 "parser\\epparser.lemon"
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
#line 1677 "parser\\epparser.c"
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
      /* (91) stmt ::= cdef_stmt */ yytestcase(yyruleno==91);
      /* (92) stmt ::= assign_stmt */ yytestcase(yyruleno==92);
      /* (93) stmt ::= assignMulti_stmt */ yytestcase(yyruleno==93);
      /* (95) stmt ::= actionStmt */ yytestcase(yyruleno==95);
      /* (96) stmt ::= if_stmt */ yytestcase(yyruleno==96);
      /* (97) stmt ::= while_stmt */ yytestcase(yyruleno==97);
      /* (98) stmt ::= foreach_stmt */ yytestcase(yyruleno==98);
      /* (99) stmt ::= continue_stmt */ yytestcase(yyruleno==99);
      /* (100) stmt ::= break_stmt */ yytestcase(yyruleno==100);
      /* (101) stmt ::= return_stmt */ yytestcase(yyruleno==101);
      /* (102) stmt ::= block */ yytestcase(yyruleno==102);
      /* (104) chunk ::= import_chunk */ yytestcase(yyruleno==104);
      /* (105) chunk ::= fdef_chunk */ yytestcase(yyruleno==105);
      /* (106) chunk ::= vdef_stmt */ yytestcase(yyruleno==106);
      /* (107) chunk ::= cdef_stmt */ yytestcase(yyruleno==107);
      /* (108) chunks ::= */ yytestcase(yyruleno==108);
      /* (109) chunks ::= chunks chunk */ yytestcase(yyruleno==109);
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
#line 1767 "parser\\epparser.c"
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
#line 513 "parser\\epparser.lemon"


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
#line 1997 "parser\\epparser.c"
