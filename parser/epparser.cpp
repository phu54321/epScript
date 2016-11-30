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
#define YYNSTATE 275
#define YYNRULE 141
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
#define YY_ACTTAB_COUNT (1085)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   173,   52,   53,   51,   25,   26,  176,  169,  167,  124,
 /*    10 */     7,    3,  264,  262,  172,    2,   56,  254,  157,  168,
 /*    20 */   166,  111,  246,  245,  244,  243,  242,  161,  160,  273,
 /*    30 */    56,   82,  157,  230,  135,  154,  266,  128,  100,  126,
 /*    40 */     8,   58,  271,  130,   74,  123,    6,   10,  154,  270,
 /*    50 */   135,   19,   12,    5,   63,    4,   62,   61,  173,  118,
 /*    60 */    74,  189,   25,   26,  154,  169,  167,  176,  248,  333,
 /*    70 */   214,  262,  172,    2,  236,  254,  165,  168,  166,  111,
 /*    80 */   246,  245,  244,  243,  242,  161,  160,  178,  268,   82,
 /*    90 */   269,  215,  135,  154,  265,  128,  100,  126,    8,   58,
 /*   100 */   132,  218,   74,  123,    6,   10,  154,  158,  158,   19,
 /*   110 */    12,    5,   63,    4,   62,   61,  173,   81,   72,  138,
 /*   120 */   136,  154,  154,  169,  167,   25,   26,  267,  211,  262,
 /*   130 */   172,    2,   69,  254,  131,  168,  166,  111,  246,  245,
 /*   140 */   244,  243,  242,  161,  160,  417,   14,   82,   59,  200,
 /*   150 */   135,  154,  263,  128,  100,  126,    8,   58,  261,  129,
 /*   160 */    74,  123,    6,   10,  154,  158,  158,   19,   12,    5,
 /*   170 */    63,    4,   62,   61,  173,   81,   89,  138,  116,  154,
 /*   180 */   154,  169,  167,   34,  176,   68,  208,  262,  172,    2,
 /*   190 */    67,  254,  176,  168,  166,  111,  246,  245,  244,  243,
 /*   200 */   242,  161,  160,   32,  176,   82,   30,   31,  158,  154,
 /*   210 */   252,  128,  100,  126,    8,   58,  251,  163,   82,  123,
 /*   220 */     6,   10,  154,  158,  217,   19,   12,    5,   63,    4,
 /*   230 */    62,   61,  173,   81,  250,  138,  137,  154,   13,  169,
 /*   240 */   167,  249,   29,  164,  195,  262,  172,    2,  162,  254,
 /*   250 */   241,  168,  166,  111,  246,  245,  244,  243,  242,  161,
 /*   260 */   160,  247,  240,   82,   95,  165,  135,  154,  197,  128,
 /*   270 */   100,  126,    8,   58,  156,  127,   74,  123,    6,   10,
 /*   280 */   154,  334,  135,   19,   12,    5,   63,    4,   62,   61,
 /*   290 */   173,   97,   74,  369,  369,  333,  154,  169,  167,   17,
 /*   300 */    27,  151,  192,  262,  172,    2,  234,  254,  148,  168,
 /*   310 */   166,  111,  246,  245,  244,  243,  242,  161,  160,  150,
 /*   320 */   147,   82,  145,  333,  158,  154,  233,  128,  100,  126,
 /*   330 */     8,   58,  232,  144,   88,  123,    6,   10,  154,  158,
 /*   340 */   158,   19,   12,    5,   63,    4,   62,   61,  173,   81,
 /*   350 */   109,  225,  142,  154,  154,  169,  167,  231,  141,   26,
 /*   360 */   185,  262,  172,    2,   15,  254,   28,  168,  166,  111,
 /*   370 */   246,  245,  244,  243,  242,  161,  160,  371,  371,   82,
 /*   380 */    25,   26,  158,  154,  224,  128,  100,  126,    8,   58,
 /*   390 */   222,  134,   70,  123,    6,   10,  154,   94,  158,   19,
 /*   400 */    12,    5,   63,    4,   62,   61,  114,  334,  108,  212,
 /*   410 */    25,   26,  154,  169,  167,   65,  220,  219,   33,  183,
 /*   420 */   171,    2,   35,  254,    1,  168,  166,  111,  246,  245,
 /*   430 */   244,  243,  242,  161,  160,   33,   22,   82,   11,  209,
 /*   440 */   158,  154,  213,  128,  100,  126,    8,   58,   21,   20,
 /*   450 */    70,  123,    6,   10,  154,  229,  207,   19,   12,    5,
 /*   460 */    63,    4,   62,   61,  238,  193,  201,  115,  194,   16,
 /*   470 */   188,  169,  167,  268,  184,  177,  257,  239,  170,    2,
 /*   480 */   256,  254,  258,  168,  166,  111,  246,  245,  244,  243,
 /*   490 */   242,  161,  160,  255,  103,   82,  275,  102,  101,  154,
 /*   500 */   133,  128,  100,  126,    8,   58,  187,  117,   98,  123,
 /*   510 */     6,   10,  186,  113,  125,   19,   12,    5,   63,    4,
 /*   520 */    62,   61,   43,   42,  179,  112,  175,  418,   41,  237,
 /*   530 */    96,  253,  418,  418,  418,   45,  418,  260,  259,  418,
 /*   540 */   418,   60,   64,  418,  153,  152,  149,  146,  143,   66,
 /*   550 */    64,  216,  158,  210,  122,  119,  418,  191,  190,   18,
 /*   560 */   418,  117,   70,   43,   42,  418,  154,  140,  418,   41,
 /*   570 */   237,   96,  253,  418,  418,  418,   45,  418,  260,  258,
 /*   580 */   418,  418,  418,  418,  418,  153,  152,  149,  146,  143,
 /*   590 */    66,   64,  216,  418,  210,  122,  119,  418,  191,  190,
 /*   600 */    18,  418,  117,  418,   43,   42,  158,  418,  158,  418,
 /*   610 */    41,  237,   96,  253,  418,  418,   70,   45,   70,  260,
 /*   620 */   154,  228,  154,  227,  418,  418,  153,  152,  149,  146,
 /*   630 */   143,   66,   64,  216,  418,  210,  122,  119,  418,  191,
 /*   640 */   190,   18,  418,  117,   44,   39,   38,   37,   36,   40,
 /*   650 */    47,   46,   48,   50,   49,   55,   54,   52,   53,   51,
 /*   660 */    47,   46,   48,   50,   49,   55,   54,   52,   53,   51,
 /*   670 */   418,  158,   56,  418,  157,  418,  418,  418,  418,  418,
 /*   680 */   418,  107,   56,  221,  157,  154,   47,   46,   48,   50,
 /*   690 */    49,   55,   54,   52,   53,   51,  418,  418,   24,  158,
 /*   700 */   274,  182,  272,  181,  180,  235,  174,    9,   56,   70,
 /*   710 */   157,   43,   42,  154,   93,  418,  418,   41,  237,  155,
 /*   720 */   418,  418,  418,  418,   45,   23,  418,  418,  206,  204,
 /*   730 */   418,  418,  418,  153,  152,  149,  146,  143,   43,   42,
 /*   740 */   205,  203,  158,  158,   41,  237,  155,  418,  418,  139,
 /*   750 */   418,   45,   82,   87,  418,  418,  154,  154,  128,  100,
 /*   760 */   153,  152,  149,  146,  143,   43,   42,  158,  418,  121,
 /*   770 */   120,   41,  237,  155,  418,  418,  139,   70,   45,  223,
 /*   780 */   418,  154,   92,  418,  418,  226,  418,  153,  152,  149,
 /*   790 */   146,  143,   43,   42,  418,  418,  418,  418,   41,  237,
 /*   800 */    96,  418,  418,  418,  418,   45,   50,   49,   55,   54,
 /*   810 */    52,   53,   51,  418,  153,  152,  149,  146,  143,   66,
 /*   820 */    64,  418,  418,  418,  418,   56,  418,  157,   47,   46,
 /*   830 */    48,   50,   49,   55,   54,   52,   53,   51,   55,   54,
 /*   840 */    52,   53,   51,  418,  158,  199,  158,  418,  418,  418,
 /*   850 */    57,  418,  159,  418,   70,   56,   82,  157,  154,   91,
 /*   860 */   154,  418,  128,  100,   47,   46,   48,   50,   49,   55,
 /*   870 */    54,   52,   53,   51,  418,  198,  418,  418,  418,  418,
 /*   880 */   418,  418,  418,   43,   42,  158,   56,  158,  157,   41,
 /*   890 */   237,  155,  418,  418,  418,   70,   45,   86,  418,  154,
 /*   900 */    90,  154,  418,  226,  418,  153,  152,  149,  146,  143,
 /*   910 */    43,   42,  158,  418,  418,  158,   41,  237,   96,  418,
 /*   920 */   418,  418,   85,   45,  196,   83,  154,  418,  418,  154,
 /*   930 */   418,  418,  153,  152,  149,  146,  143,  418,   46,   48,
 /*   940 */    50,   49,   55,   54,   52,   53,   51,  418,  418,   48,
 /*   950 */    50,   49,   55,   54,   52,   53,   51,   43,   42,   56,
 /*   960 */   418,  157,  418,   41,  237,  110,  418,  418,  418,   56,
 /*   970 */    45,  157,  418,  418,  206,  204,  418,  418,  418,  153,
 /*   980 */   152,  149,  146,  143,   43,   42,  205,  203,  158,  158,
 /*   990 */    41,  237,  155,  418,  418,  418,  418,   45,   82,   84,
 /*  1000 */   418,  418,  154,  154,  128,  100,  153,  152,  149,  146,
 /*  1010 */   143,   43,   42,  418,  418,  202,  158,   41,  237,   96,
 /*  1020 */   418,  418,  418,  418,   45,  418,   71,  418,  199,  158,
 /*  1030 */   154,  418,  418,  153,  152,  149,  146,  143,  158,   82,
 /*  1040 */   418,  158,  418,  154,  418,  128,  100,  418,   80,  158,
 /*  1050 */   158,  106,  154,  418,  418,  154,  418,  418,   99,  105,
 /*  1060 */   104,  158,  158,  154,  154,  418,  418,  158,  158,  158,
 /*  1070 */   158,   79,   78,  418,  418,  154,  154,   77,   76,   75,
 /*  1080 */    73,  154,  154,  154,  154,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    58,   20,   21,   22,    3,    4,    2,   65,   66,  100,
 /*    10 */   101,  102,   70,   71,   72,   73,   35,   75,   37,   77,
 /*    20 */    78,   79,   80,   81,   82,   83,   84,   85,   86,   27,
 /*    30 */    35,   89,   37,   32,   79,   93,   32,   95,   96,   97,
 /*    40 */    98,   99,   27,   88,   89,  103,  104,  105,   93,   27,
 /*    50 */    79,  109,  110,  111,  112,  113,  114,  115,   58,   88,
 /*    60 */    89,   90,    3,    4,   93,   65,   66,    2,   27,   31,
 /*    70 */    70,   71,   72,   73,   36,   75,   35,   77,   78,   79,
 /*    80 */    80,   81,   82,   83,   84,   85,   86,   26,   26,   89,
 /*    90 */    26,   32,   79,   93,   32,   95,   96,   97,   98,   99,
 /*   100 */     2,   88,   89,  103,  104,  105,   93,   79,   79,  109,
 /*   110 */   110,  111,  112,  113,  114,  115,   58,   89,   89,   91,
 /*   120 */    92,   93,   93,   65,   66,    3,    4,   26,   70,   71,
 /*   130 */    72,   73,   29,   75,   36,   77,   78,   79,   80,   81,
 /*   140 */    82,   83,   84,   85,   86,   60,   61,   89,   31,   27,
 /*   150 */    79,   93,   27,   95,   96,   97,   98,   99,   27,   88,
 /*   160 */    89,  103,  104,  105,   93,   79,   79,  109,  110,  111,
 /*   170 */   112,  113,  114,  115,   58,   89,   89,   91,   92,   93,
 /*   180 */    93,   65,   66,    1,    2,   27,   70,   71,   72,   73,
 /*   190 */    27,   75,    2,   77,   78,   79,   80,   81,   82,   83,
 /*   200 */    84,   85,   86,    1,    2,   89,    1,    2,   79,   93,
 /*   210 */    27,   95,   96,   97,   98,   99,   27,   25,   89,  103,
 /*   220 */   104,  105,   93,   79,   95,  109,  110,  111,  112,  113,
 /*   230 */   114,  115,   58,   89,   27,   91,   92,   93,    2,   65,
 /*   240 */    66,   27,   52,   35,   70,   71,   72,   73,   36,   75,
 /*   250 */    27,   77,   78,   79,   80,   81,   82,   83,   84,   85,
 /*   260 */    86,   36,   27,   89,   26,   35,   79,   93,   32,   95,
 /*   270 */    96,   97,   98,   99,   26,   88,   89,  103,  104,  105,
 /*   280 */    93,   31,   79,  109,  110,  111,  112,  113,  114,  115,
 /*   290 */    58,   88,   89,    1,    2,   31,   93,   65,   66,   31,
 /*   300 */    31,   31,   70,   71,   72,   73,   32,   75,   31,   77,
 /*   310 */    78,   79,   80,   81,   82,   83,   84,   85,   86,   38,
 /*   320 */    38,   89,   31,   31,   79,   93,   32,   95,   96,   97,
 /*   330 */    98,   99,   32,   38,   89,  103,  104,  105,   93,   79,
 /*   340 */    79,  109,  110,  111,  112,  113,  114,  115,   58,   89,
 /*   350 */    89,   91,   31,   93,   93,   65,   66,   32,   38,    4,
 /*   360 */    70,   71,   72,   73,   31,   75,    2,   77,   78,   79,
 /*   370 */    80,   81,   82,   83,   84,   85,   86,    1,    2,   89,
 /*   380 */     3,    4,   79,   93,   32,   95,   96,   97,   98,   99,
 /*   390 */    32,   35,   89,  103,  104,  105,   93,   94,   79,  109,
 /*   400 */   110,  111,  112,  113,  114,  115,   58,   31,   89,   32,
 /*   410 */     3,    4,   93,   65,   66,   35,   25,   36,    2,   71,
 /*   420 */    72,   73,    1,   75,   76,   77,   78,   79,   80,   81,
 /*   430 */    82,   83,   84,   85,   86,    2,   31,   89,    2,   32,
 /*   440 */    79,   93,   47,   95,   96,   97,   98,   99,   31,   31,
 /*   450 */    89,  103,  104,  105,   93,   94,   31,  109,  110,  111,
 /*   460 */   112,  113,  114,  115,   58,   32,   27,   32,   31,   31,
 /*   470 */    27,   65,   66,   26,   34,   67,   74,   71,   72,   73,
 /*   480 */    74,   75,   34,   77,   78,   79,   80,   81,   82,   83,
 /*   490 */    84,   85,   86,   74,   67,   89,    0,   87,   67,   93,
 /*   500 */    25,   95,   96,   97,   98,   99,  114,   57,   67,  103,
 /*   510 */   104,  105,  114,   67,   48,  109,  110,  111,  112,  113,
 /*   520 */   114,  115,   18,   19,   28,   67,   30,  116,   24,   25,
 /*   530 */    26,   27,  116,  116,  116,   31,  116,   33,   34,  116,
 /*   540 */   116,   45,   46,  116,   40,   41,   42,   43,   44,   45,
 /*   550 */    46,   47,   79,   49,   50,   51,  116,   53,   54,   55,
 /*   560 */   116,   57,   89,   18,   19,  116,   93,   94,  116,   24,
 /*   570 */    25,   26,   27,  116,  116,  116,   31,  116,   33,   34,
 /*   580 */   116,  116,  116,  116,  116,   40,   41,   42,   43,   44,
 /*   590 */    45,   46,   47,  116,   49,   50,   51,  116,   53,   54,
 /*   600 */    55,  116,   57,  116,   18,   19,   79,  116,   79,  116,
 /*   610 */    24,   25,   26,   27,  116,  116,   89,   31,   89,   33,
 /*   620 */    93,   94,   93,   94,  116,  116,   40,   41,   42,   43,
 /*   630 */    44,   45,   46,   47,  116,   49,   50,   51,  116,   53,
 /*   640 */    54,   55,  116,   57,    7,    8,    9,   10,   11,   12,
 /*   650 */    13,   14,   15,   16,   17,   18,   19,   20,   21,   22,
 /*   660 */    13,   14,   15,   16,   17,   18,   19,   20,   21,   22,
 /*   670 */   116,   79,   35,  116,   37,  116,  116,  116,  116,  116,
 /*   680 */   116,   89,   35,   36,   37,   93,   13,   14,   15,   16,
 /*   690 */    17,   18,   19,   20,   21,   22,  116,  116,    5,   79,
 /*   700 */    62,   63,   64,   65,   66,   32,   68,   69,   35,   89,
 /*   710 */    37,   18,   19,   93,   94,  116,  116,   24,   25,   26,
 /*   720 */   116,  116,  116,  116,   31,    5,  116,  116,   65,   66,
 /*   730 */   116,  116,  116,   40,   41,   42,   43,   44,   18,   19,
 /*   740 */    77,   78,   79,   79,   24,   25,   26,  116,  116,   56,
 /*   750 */   116,   31,   89,   89,  116,  116,   93,   93,   95,   96,
 /*   760 */    40,   41,   42,   43,   44,   18,   19,   79,  116,  106,
 /*   770 */   107,   24,   25,   26,  116,  116,   56,   89,   31,   32,
 /*   780 */   116,   93,   94,  116,  116,   38,  116,   40,   41,   42,
 /*   790 */    43,   44,   18,   19,  116,  116,  116,  116,   24,   25,
 /*   800 */    26,  116,  116,  116,  116,   31,   16,   17,   18,   19,
 /*   810 */    20,   21,   22,  116,   40,   41,   42,   43,   44,   45,
 /*   820 */    46,  116,  116,  116,  116,   35,  116,   37,   13,   14,
 /*   830 */    15,   16,   17,   18,   19,   20,   21,   22,   18,   19,
 /*   840 */    20,   21,   22,  116,   79,   78,   79,  116,  116,  116,
 /*   850 */    35,  116,   37,  116,   89,   35,   89,   37,   93,   94,
 /*   860 */    93,  116,   95,   96,   13,   14,   15,   16,   17,   18,
 /*   870 */    19,   20,   21,   22,  116,  108,  116,  116,  116,  116,
 /*   880 */   116,  116,  116,   18,   19,   79,   35,   79,   37,   24,
 /*   890 */    25,   26,  116,  116,  116,   89,   31,   89,  116,   93,
 /*   900 */    94,   93,  116,   38,  116,   40,   41,   42,   43,   44,
 /*   910 */    18,   19,   79,  116,  116,   79,   24,   25,   26,  116,
 /*   920 */   116,  116,   89,   31,   32,   89,   93,  116,  116,   93,
 /*   930 */   116,  116,   40,   41,   42,   43,   44,  116,   14,   15,
 /*   940 */    16,   17,   18,   19,   20,   21,   22,  116,  116,   15,
 /*   950 */    16,   17,   18,   19,   20,   21,   22,   18,   19,   35,
 /*   960 */   116,   37,  116,   24,   25,   26,  116,  116,  116,   35,
 /*   970 */    31,   37,  116,  116,   65,   66,  116,  116,  116,   40,
 /*   980 */    41,   42,   43,   44,   18,   19,   77,   78,   79,   79,
 /*   990 */    24,   25,   26,  116,  116,  116,  116,   31,   89,   89,
 /*  1000 */   116,  116,   93,   93,   95,   96,   40,   41,   42,   43,
 /*  1010 */    44,   18,   19,  116,  116,  106,   79,   24,   25,   26,
 /*  1020 */   116,  116,  116,  116,   31,  116,   89,  116,   78,   79,
 /*  1030 */    93,  116,  116,   40,   41,   42,   43,   44,   79,   89,
 /*  1040 */   116,   79,  116,   93,  116,   95,   96,  116,   89,   79,
 /*  1050 */    79,   89,   93,  116,  116,   93,  116,  116,  108,   89,
 /*  1060 */    89,   79,   79,   93,   93,  116,  116,   79,   79,   79,
 /*  1070 */    79,   89,   89,  116,  116,   93,   93,   89,   89,   89,
 /*  1080 */    89,   93,   93,   93,   93,
};
#define YY_SHIFT_USE_DFLT (-20)
#define YY_SHIFT_COUNT (182)
#define YY_SHIFT_MIN   (-19)
#define YY_SHIFT_MAX   (993)
static const short yy_shift_ofst[] = {
 /*     0 */   -20,  545,  504,  586,  586,  586,  586,  586,  586,  586,
 /*    10 */   774,  774,  892,  993,  496,  747,  865,  865,  966,  693,
 /*    20 */   693,  693,  693,  720,  720,  693,  693,  693,  865,  966,
 /*    30 */   966,  993,  966,  966,  966,  966,  966,  966,  966,  966,
 /*    40 */   966,  966,  966,  966,  966,  966,  966,  966,  966,  966,
 /*    50 */   966,  966,  966,  966,  966,  966,  966,  939,  466,   62,
 /*    60 */   447,  450,  450,  447,  447,  475,  447,  448,  448,  447,
 /*    70 */   637,  673,  647,  851,  851,  851,  851,  851,  851,  851,
 /*    80 */   851,  851,  815,  924,  934,  790,  820,  820,  -19,  -19,
 /*    90 */   122,  407,  377,   59,    1,  376,  292,  433,  190,  236,
 /*   100 */   205,  202,   98,  182,   -5,   -5,   -5,   -5,   -5,   -5,
 /*   110 */    38,   41,    4,   65,  440,  443,  435,  438,  416,  437,
 /*   120 */   439,  436,  425,  418,  417,  395,  405,  416,  421,  416,
 /*   130 */   416,  381,  391,  212,  380,  356,  358,  352,  364,  333,
 /*   140 */   355,  325,  320,  321,  300,  295,  291,  294,  282,  277,
 /*   150 */   274,  281,  270,  269,  268,  264,  250,  248,  230,  238,
 /*   160 */   235,  223,  225,  212,  192,  208,  214,  207,  189,  183,
 /*   170 */   163,  158,  131,  125,  117,  101,   64,   65,  103,   61,
 /*   180 */    22,   15,    2,
};
#define YY_REDUCE_USE_DFLT (-92)
#define YY_REDUCE_COUNT (69)
#define YY_REDUCE_MIN   (-91)
#define YY_REDUCE_MAX   (991)
static const short yy_reduce_ofst[] = {
 /*     0 */    85,  406,  348,  290,  232,  174,  116,   58,    0,  -58,
 /*    10 */   663,  909,  950,  767,  638,  144,   86,   28,  -29,  806,
 /*    20 */   765,  688,  620,  529,  527,  473,  361,  303,  260,  203,
 /*    30 */   187,  129,   71,   13,  -45,  991,  990,  989,  988,  983,
 /*    40 */   982,  971,  970,  962,  959,  937,  910,  836,  833,  808,
 /*    50 */   664,  592,  319,  261,  245,   87,   29,   29,  -91,  458,
 /*    60 */   446,  398,  392,  441,  431,  410,  427,  419,  402,  408,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   276,  416,  416,  416,  416,  416,  416,  416,  416,  416,
 /*    10 */   395,  416,  416,  416,  416,  416,  331,  331,  322,  416,
 /*    20 */   416,  416,  416,  416,  416,  416,  416,  416,  416,  416,
 /*    30 */   416,  416,  416,  416,  416,  416,  416,  416,  416,  416,
 /*    40 */   416,  416,  416,  416,  416,  416,  416,  416,  416,  416,
 /*    50 */   416,  416,  416,  416,  416,  416,  416,  416,  383,  416,
 /*    60 */   416,  415,  414,  416,  416,  416,  416,  416,  416,  416,
 /*    70 */   416,  416,  416,  374,  320,  361,  360,  359,  358,  357,
 /*    80 */   356,  328,  416,  351,  352,  350,  349,  348,  344,  343,
 /*    90 */   416,  416,  416,  416,  416,  326,  325,  416,  416,  416,
 /*   100 */   416,  416,  416,  366,  355,  354,  353,  347,  346,  345,
 /*   110 */   325,  336,  416,  366,  416,  416,  416,  416,  323,  416,
 /*   120 */   416,  394,  416,  416,  416,  382,  416,  375,  372,  368,
 /*   130 */   367,  416,  416,  314,  416,  336,  416,  416,  332,  416,
 /*   140 */   363,  416,  416,  416,  416,  416,  416,  416,  416,  416,
 /*   150 */   416,  416,  416,  416,  416,  325,  326,  416,  336,  416,
 /*   160 */   416,  416,  416,  416,  416,  416,  416,  416,  416,  416,
 /*   170 */   416,  416,  416,  416,  416,  416,  416,  282,  416,  416,
 /*   180 */   416,  416,  416,  311,  296,  384,  413,  412,  411,  408,
 /*   190 */   407,  406,  405,  404,  403,  402,  401,  400,  397,  396,
 /*   200 */   399,  398,  393,  392,  391,  390,  389,  388,  387,  386,
 /*   210 */   385,  381,  380,  379,  378,  377,  376,  373,  321,  318,
 /*   220 */   315,  327,  335,  410,  409,  330,  329,  365,  364,  362,
 /*   230 */   338,  342,  341,  340,  339,  337,  370,  324,  313,  312,
 /*   240 */   310,  309,  308,  307,  306,  305,  304,  319,  303,  302,
 /*   250 */   301,  300,  299,  298,  297,  295,  294,  293,  291,  292,
 /*   260 */   290,  289,  288,  287,  286,  285,  284,  283,  316,  317,
 /*   270 */   281,  280,  279,  278,  277,
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
 /*  15 */ "lbracket ::= LBRACKET",
 /*  16 */ "rbracket ::= RBRACKET",
 /*  17 */ "blockStmt ::= lbracket RBRACKET",
 /*  18 */ "blockStmt ::= lbracket return_stmt SEMICOLON rbracket",
 /*  19 */ "blockStmt ::= lbracket bodyStmtList rbracket",
 /*  20 */ "blockStmt ::= lbracket bodyStmtList return_stmt SEMICOLON rbracket",
 /*  21 */ "blockStmt ::= lbracket error RBRACKET",
 /*  22 */ "bodyStmt ::= blockStmt",
 /*  23 */ "bodyStmt ::= SEMICOLON",
 /*  24 */ "bodyStmt ::= vdef_stmt SEMICOLON",
 /*  25 */ "bodyStmt ::= vdefAssign_stmt SEMICOLON",
 /*  26 */ "bodyStmt ::= cdef_stmt SEMICOLON",
 /*  27 */ "bodyStmt ::= assign_stmt SEMICOLON",
 /*  28 */ "bodyStmt ::= funcexpr SEMICOLON",
 /*  29 */ "bodyStmt ::= actionStmt",
 /*  30 */ "bodyStmt ::= if_stmt",
 /*  31 */ "bodyStmt ::= while_stmt",
 /*  32 */ "bodyStmt ::= for_stmt",
 /*  33 */ "bodyStmt ::= foreach_stmt",
 /*  34 */ "bodyStmt ::= continue_stmt SEMICOLON",
 /*  35 */ "bodyStmt ::= break_stmt SEMICOLON",
 /*  36 */ "bodyStmtList ::= bodyStmt",
 /*  37 */ "bodyStmtList ::= bodyStmtList bodyStmt",
 /*  38 */ "bodyStmtList ::= bodyStmtList error",
 /*  39 */ "numList_nonEmpty ::= NUMBER",
 /*  40 */ "numList_nonEmpty ::= numList_nonEmpty COMMA NUMBER",
 /*  41 */ "nameList_nonEmpty ::= NAME",
 /*  42 */ "nameList_nonEmpty ::= nameList_nonEmpty COMMA NAME",
 /*  43 */ "exprList_nonEmpty ::= funcexpr LSQBRACKET LSQBRACKET numList_nonEmpty RSQBRACKET RSQBRACKET",
 /*  44 */ "expr ::= funcexpr LSQBRACKET LSQBRACKET NUMBER RSQBRACKET RSQBRACKET",
 /*  45 */ "exprList_nonEmpty ::= expr",
 /*  46 */ "exprList_nonEmpty ::= exprList_nonEmpty COMMA exprList_nonEmpty",
 /*  47 */ "exprList ::=",
 /*  48 */ "exprList ::= exprList_nonEmpty",
 /*  49 */ "expr ::= NUMBER",
 /*  50 */ "expr ::= NAME",
 /*  51 */ "expr ::= expr PERIOD NAME",
 /*  52 */ "expr ::= expr LSQBRACKET expr RSQBRACKET",
 /*  53 */ "fArgs_nonEmpty ::= expr",
 /*  54 */ "fArgs_nonEmpty ::= STRING",
 /*  55 */ "fArgs_nonEmpty ::= fArgs_nonEmpty COMMA fArgs_nonEmpty",
 /*  56 */ "fArgs ::=",
 /*  57 */ "fArgs ::= fArgs_nonEmpty",
 /*  58 */ "funcName ::= NAME",
 /*  59 */ "funcName ::= expr PERIOD NAME",
 /*  60 */ "funcexpr ::= funcName LPAREN fArgs RPAREN",
 /*  61 */ "expr ::= funcexpr",
 /*  62 */ "expr ::= LPAREN expr RPAREN",
 /*  63 */ "expr ::= L2V LPAREN lexpr RPAREN",
 /*  64 */ "expr ::= MAPSTRING LPAREN STRING RPAREN",
 /*  65 */ "expr ::= UNIT LPAREN STRING RPAREN",
 /*  66 */ "expr ::= SWITCH LPAREN STRING RPAREN",
 /*  67 */ "expr ::= LOCATION LPAREN STRING RPAREN",
 /*  68 */ "expr ::= expr PLUS expr",
 /*  69 */ "expr ::= expr MINUS expr",
 /*  70 */ "expr ::= expr MULTIPLY expr",
 /*  71 */ "expr ::= expr DIVIDE expr",
 /*  72 */ "expr ::= expr MOD expr",
 /*  73 */ "expr ::= expr LSHIFT expr",
 /*  74 */ "expr ::= expr RSHIFT expr",
 /*  75 */ "expr ::= expr BITAND expr",
 /*  76 */ "expr ::= expr BITOR expr",
 /*  77 */ "expr ::= expr BITXOR expr",
 /*  78 */ "expr ::= PLUS expr",
 /*  79 */ "expr ::= MINUS expr",
 /*  80 */ "expr ::= BITNOT expr",
 /*  81 */ "lexpr ::= expr EQ expr",
 /*  82 */ "lexpr ::= expr NE expr",
 /*  83 */ "lexpr ::= expr LE expr",
 /*  84 */ "lexpr ::= expr LT expr",
 /*  85 */ "lexpr ::= expr GE expr",
 /*  86 */ "lexpr ::= expr GT expr",
 /*  87 */ "lexpr ::= lexpr LAND lexpr",
 /*  88 */ "lexpr ::= lexpr LOR lexpr",
 /*  89 */ "lexpr ::= LNOT lexpr",
 /*  90 */ "lexpr ::= LNOT LNOT lexpr",
 /*  91 */ "vdef_stmt ::= VAR nameList_nonEmpty",
 /*  92 */ "vdefAssign_stmt ::= VAR nameList_nonEmpty ASSIGN exprList_nonEmpty",
 /*  93 */ "cdef_stmt ::= CONST nameList_nonEmpty ASSIGN exprList_nonEmpty",
 /*  94 */ "lvalue ::= NAME",
 /*  95 */ "lvalue ::= expr LSQBRACKET NAME RSQBRACKET",
 /*  96 */ "lvalue ::= expr PERIOD NAME",
 /*  97 */ "lvalueList_nonEmpty ::= lvalue",
 /*  98 */ "lvalueList_nonEmpty ::= lvalueList_nonEmpty COMMA lvalue",
 /*  99 */ "assign_stmt ::= lvalue ASSIGN expr",
 /* 100 */ "assign_stmt ::= lvalueList_nonEmpty ASSIGN exprList_nonEmpty",
 /* 101 */ "if_start ::= IF",
 /* 102 */ "if_header ::= if_start LPAREN lexpr RPAREN",
 /* 103 */ "if_block ::= if_header stmt",
 /* 104 */ "elif_start ::= ELSE IF",
 /* 105 */ "elif_header ::= elif_start LPAREN lexpr RPAREN",
 /* 106 */ "if_block ::= if_block elif_header stmt",
 /* 107 */ "else_header ::= ELSE",
 /* 108 */ "if_stmt ::= if_block",
 /* 109 */ "if_stmt ::= if_block else_header stmt",
 /* 110 */ "while_start ::= WHILE",
 /* 111 */ "while_header ::= while_start LPAREN lexpr RPAREN",
 /* 112 */ "while_stmt ::= while_header stmt",
 /* 113 */ "for_opener ::= FOR LPAREN",
 /* 114 */ "for_init_stmt_nonEmpty ::= vdef_stmt",
 /* 115 */ "for_init_stmt_nonEmpty ::= vdefAssign_stmt",
 /* 116 */ "for_init_stmt_nonEmpty ::= cdef_stmt",
 /* 117 */ "for_init_stmt_nonEmpty ::= assign_stmt",
 /* 118 */ "for_init_stmt_nonEmpty ::= for_init_stmt_nonEmpty COMMA for_init_stmt_nonEmpty",
 /* 119 */ "for_init_stmt ::= for_init_stmt_nonEmpty",
 /* 120 */ "for_init_stmt ::=",
 /* 121 */ "for_action_stmt_nonEmpty ::= assign_stmt",
 /* 122 */ "for_action_stmt_nonEmpty ::= for_action_stmt_nonEmpty COMMA for_action_stmt_nonEmpty",
 /* 123 */ "for_header1 ::= for_opener for_init_stmt SEMICOLON",
 /* 124 */ "for_header2 ::= for_header1 lexpr SEMICOLON",
 /* 125 */ "for_header ::= for_header2 for_action_stmt_nonEmpty RPAREN",
 /* 126 */ "for_header ::= for_header2 RPAREN",
 /* 127 */ "for_stmt ::= for_header stmt",
 /* 128 */ "foreach_opener ::= FOREACH LPAREN",
 /* 129 */ "foreach_header ::= foreach_opener nameList_nonEmpty COLON exprList_nonEmpty RPAREN",
 /* 130 */ "foreach_stmt ::= foreach_header stmt",
 /* 131 */ "continue_stmt ::= CONTINUE",
 /* 132 */ "break_stmt ::= BREAK",
 /* 133 */ "return_stmt ::= RETURN exprList",
 /* 134 */ "lexpr ::= CONDITIONNAME LPAREN fArgs RPAREN",
 /* 135 */ "lexpr ::= CONDITIONNAME LPAREN RPAREN",
 /* 136 */ "action ::= ACTIONNAME LPAREN fArgs RPAREN SEMICOLON",
 /* 137 */ "actions ::= action action",
 /* 138 */ "actions ::= actions action",
 /* 139 */ "actionStmt ::= action",
 /* 140 */ "actionStmt ::= actions",
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
#line 808 "parser\\epparser.c"
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
#line 1253 "parser\\epparser.c"
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
#line 1266 "parser\\epparser.c"
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
#line 1285 "parser\\epparser.c"
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
#line 1296 "parser\\epparser.c"
        break;
      case 11: /* fdef_chunk ::= function_header stmt */
      case 130: /* foreach_stmt ::= foreach_header stmt */ yytestcase(yyruleno==130);
#line 112 "parser\\epparser.lemon"
{
    ps->gen.unindent(true);
    ps->closure.popScope();
}
#line 1305 "parser\\epparser.c"
        break;
      case 12: /* stmt ::= error SEMICOLON */
#line 119 "parser\\epparser.lemon"
{ throw_error(6974, "Error while parsing statement"); }
#line 1310 "parser\\epparser.c"
        break;
      case 15: /* lbracket ::= LBRACKET */
#line 125 "parser\\epparser.lemon"
{ ps->closure.pushScope(); }
#line 1315 "parser\\epparser.c"
        break;
      case 16: /* rbracket ::= RBRACKET */
#line 126 "parser\\epparser.lemon"
{ ps->closure.popScope(); }
#line 1320 "parser\\epparser.c"
        break;
      case 17: /* blockStmt ::= lbracket RBRACKET */
#line 128 "parser\\epparser.lemon"
{
    ps->gen << "pass" << std::endl;
    ps->closure.popScope();
}
#line 1328 "parser\\epparser.c"
        break;
      case 21: /* blockStmt ::= lbracket error RBRACKET */
#line 135 "parser\\epparser.lemon"
{
    throw_error(6298, "Block not terminated properly.");
    ps->closure.popScope();
}
#line 1336 "parser\\epparser.c"
        break;
      case 28: /* bodyStmt ::= funcexpr SEMICOLON */
#line 146 "parser\\epparser.lemon"
{ ps->gen << yymsp[-1].minor.yy0->data << std::endl; }
#line 1341 "parser\\epparser.c"
        break;
      case 38: /* bodyStmtList ::= bodyStmtList error */
#line 158 "parser\\epparser.lemon"
{
    throw_error(8510, "Incomplete statement");
}
#line 1348 "parser\\epparser.c"
        break;
      case 39: /* numList_nonEmpty ::= NUMBER */
      case 41: /* nameList_nonEmpty ::= NAME */ yytestcase(yyruleno==41);
      case 45: /* exprList_nonEmpty ::= expr */ yytestcase(yyruleno==45);
      case 48: /* exprList ::= exprList_nonEmpty */ yytestcase(yyruleno==48);
      case 49: /* expr ::= NUMBER */ yytestcase(yyruleno==49);
      case 53: /* fArgs_nonEmpty ::= expr */ yytestcase(yyruleno==53);
      case 54: /* fArgs_nonEmpty ::= STRING */ yytestcase(yyruleno==54);
      case 57: /* fArgs ::= fArgs_nonEmpty */ yytestcase(yyruleno==57);
      case 61: /* expr ::= funcexpr */ yytestcase(yyruleno==61);
      case 90: /* lexpr ::= LNOT LNOT lexpr */ yytestcase(yyruleno==90);
      case 97: /* lvalueList_nonEmpty ::= lvalue */ yytestcase(yyruleno==97);
#line 164 "parser\\epparser.lemon"
{ yygotominor.yy0 = yymsp[0].minor.yy0; }
#line 1363 "parser\\epparser.c"
        break;
      case 40: /* numList_nonEmpty ::= numList_nonEmpty COMMA NUMBER */
      case 42: /* nameList_nonEmpty ::= nameList_nonEmpty COMMA NAME */ yytestcase(yyruleno==42);
      case 98: /* lvalueList_nonEmpty ::= lvalueList_nonEmpty COMMA lvalue */ yytestcase(yyruleno==98);
#line 165 "parser\\epparser.lemon"
{ yygotominor.yy0 = commaConcat(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1370 "parser\\epparser.c"
        break;
      case 43: /* exprList_nonEmpty ::= funcexpr LSQBRACKET LSQBRACKET numList_nonEmpty RSQBRACKET RSQBRACKET */
#line 169 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "_SRET(" + yymsp[-5].minor.yy0->data + ", [" + yymsp[-2].minor.yy0->data + "])";
    delete yymsp[-5].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1379 "parser\\epparser.c"
        break;
      case 44: /* expr ::= funcexpr LSQBRACKET LSQBRACKET NUMBER RSQBRACKET RSQBRACKET */
#line 176 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-5].minor.yy0->data + "[" + yymsp[-2].minor.yy0->data + "]";
    delete yymsp[-5].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1388 "parser\\epparser.c"
        break;
      case 46: /* exprList_nonEmpty ::= exprList_nonEmpty COMMA exprList_nonEmpty */
#line 184 "parser\\epparser.lemon"
{ yygotominor.yy0 = new Token((yymsp[-2].minor.yy0->data) + ", " + (yymsp[0].minor.yy0->data), yymsp[0].minor.yy0); delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1393 "parser\\epparser.c"
        break;
      case 47: /* exprList ::= */
      case 56: /* fArgs ::= */ yytestcase(yyruleno==56);
#line 186 "parser\\epparser.lemon"
{ yygotominor.yy0 = genEmpty(); }
#line 1399 "parser\\epparser.c"
        break;
      case 50: /* expr ::= NAME */
#line 191 "parser\\epparser.lemon"
{
    checkIsRValue(yymsp[0].minor.yy0->data);
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1407 "parser\\epparser.c"
        break;
      case 51: /* expr ::= expr PERIOD NAME */
#line 196 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + "." + yymsp[0].minor.yy0->data;
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1416 "parser\\epparser.c"
        break;
      case 52: /* expr ::= expr LSQBRACKET expr RSQBRACKET */
#line 202 "parser\\epparser.lemon"
{
    yymsp[-3].minor.yy0->data = yymsp[-3].minor.yy0->data + "[" + yymsp[-1].minor.yy0->data + "]";
    delete yymsp[-1].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 1425 "parser\\epparser.c"
        break;
      case 55: /* fArgs_nonEmpty ::= fArgs_nonEmpty COMMA fArgs_nonEmpty */
#line 211 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data;
    yymsp[-2].minor.yy0->type = TOKEN_TEMP;
    yygotominor.yy0 = yymsp[-2].minor.yy0;
    delete yymsp[0].minor.yy0;
}
#line 1435 "parser\\epparser.c"
        break;
      case 58: /* funcName ::= NAME */
#line 221 "parser\\epparser.lemon"
{
    funcNamePreprocess(yymsp[0].minor.yy0->data);
    checkIsFunction(yymsp[0].minor.yy0->data);
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1444 "parser\\epparser.c"
        break;
      case 59: /* funcName ::= expr PERIOD NAME */
#line 227 "parser\\epparser.lemon"
{
    // Preprocess name
    yymsp[0].minor.yy0->data = yymsp[-2].minor.yy0->data + "." + yymsp[0].minor.yy0->data;
    delete yymsp[-2].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0);
}
#line 1454 "parser\\epparser.c"
        break;
      case 60: /* funcexpr ::= funcName LPAREN fArgs RPAREN */
#line 234 "parser\\epparser.lemon"
{
    // Preprocess yymsp[-3].minor.yy0
    yymsp[-3].minor.yy0->data += "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 1463 "parser\\epparser.c"
        break;
      case 62: /* expr ::= LPAREN expr RPAREN */
#line 243 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1471 "parser\\epparser.c"
        break;
      case 63: /* expr ::= L2V LPAREN lexpr RPAREN */
#line 248 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "_L2V(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = genTemp(yymsp[-1].minor.yy0);
}
#line 1479 "parser\\epparser.c"
        break;
      case 64: /* expr ::= MAPSTRING LPAREN STRING RPAREN */
#line 253 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetStringIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1487 "parser\\epparser.c"
        break;
      case 65: /* expr ::= UNIT LPAREN STRING RPAREN */
#line 258 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetUnitIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1495 "parser\\epparser.c"
        break;
      case 66: /* expr ::= SWITCH LPAREN STRING RPAREN */
#line 263 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetSwitchIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1503 "parser\\epparser.c"
        break;
      case 67: /* expr ::= LOCATION LPAREN STRING RPAREN */
#line 268 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetLocationIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1511 "parser\\epparser.c"
        break;
      case 68: /* expr ::= expr PLUS expr */
#line 274 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "+",  yymsp[0].minor.yy0); }
#line 1516 "parser\\epparser.c"
        break;
      case 69: /* expr ::= expr MINUS expr */
#line 275 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "-",  yymsp[0].minor.yy0); }
#line 1521 "parser\\epparser.c"
        break;
      case 70: /* expr ::= expr MULTIPLY expr */
#line 276 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "*",  yymsp[0].minor.yy0); }
#line 1526 "parser\\epparser.c"
        break;
      case 71: /* expr ::= expr DIVIDE expr */
#line 277 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "//", yymsp[0].minor.yy0); }
#line 1531 "parser\\epparser.c"
        break;
      case 72: /* expr ::= expr MOD expr */
#line 278 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "%",  yymsp[0].minor.yy0); }
#line 1536 "parser\\epparser.c"
        break;
      case 73: /* expr ::= expr LSHIFT expr */
#line 279 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<<", yymsp[0].minor.yy0); }
#line 1541 "parser\\epparser.c"
        break;
      case 74: /* expr ::= expr RSHIFT expr */
#line 280 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">>", yymsp[0].minor.yy0); }
#line 1546 "parser\\epparser.c"
        break;
      case 75: /* expr ::= expr BITAND expr */
#line 281 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "&",  yymsp[0].minor.yy0); }
#line 1551 "parser\\epparser.c"
        break;
      case 76: /* expr ::= expr BITOR expr */
#line 282 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "|",  yymsp[0].minor.yy0); }
#line 1556 "parser\\epparser.c"
        break;
      case 77: /* expr ::= expr BITXOR expr */
#line 283 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "^",  yymsp[0].minor.yy0); }
#line 1561 "parser\\epparser.c"
        break;
      case 78: /* expr ::= PLUS expr */
#line 286 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = +" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1566 "parser\\epparser.c"
        break;
      case 79: /* expr ::= MINUS expr */
#line 287 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = -" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1571 "parser\\epparser.c"
        break;
      case 80: /* expr ::= BITNOT expr */
#line 288 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = ~" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1576 "parser\\epparser.c"
        break;
      case 81: /* lexpr ::= expr EQ expr */
#line 292 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "==", yymsp[0].minor.yy0); }
#line 1581 "parser\\epparser.c"
        break;
      case 82: /* lexpr ::= expr NE expr */
#line 293 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "!=", yymsp[0].minor.yy0); }
#line 1586 "parser\\epparser.c"
        break;
      case 83: /* lexpr ::= expr LE expr */
#line 294 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<=", yymsp[0].minor.yy0); }
#line 1591 "parser\\epparser.c"
        break;
      case 84: /* lexpr ::= expr LT expr */
#line 295 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<",  yymsp[0].minor.yy0); }
#line 1596 "parser\\epparser.c"
        break;
      case 85: /* lexpr ::= expr GE expr */
#line 296 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">=", yymsp[0].minor.yy0); }
#line 1601 "parser\\epparser.c"
        break;
      case 86: /* lexpr ::= expr GT expr */
#line 297 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">" , yymsp[0].minor.yy0); }
#line 1606 "parser\\epparser.c"
        break;
      case 87: /* lexpr ::= lexpr LAND lexpr */
#line 299 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "[" + yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data + "]";
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1615 "parser\\epparser.c"
        break;
      case 88: /* lexpr ::= lexpr LOR lexpr */
#line 305 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "EUDOr([" + yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data + "])";
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1624 "parser\\epparser.c"
        break;
      case 89: /* lexpr ::= LNOT lexpr */
#line 311 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = "EUDNot([" + yymsp[0].minor.yy0->data + "])";
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0);
}
#line 1632 "parser\\epparser.c"
        break;
      case 91: /* vdef_stmt ::= VAR nameList_nonEmpty */
#line 321 "parser\\epparser.lemon"
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
#line 1656 "parser\\epparser.c"
        break;
      case 92: /* vdefAssign_stmt ::= VAR nameList_nonEmpty ASSIGN exprList_nonEmpty */
#line 342 "parser\\epparser.lemon"
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
#line 1681 "parser\\epparser.c"
        break;
      case 93: /* cdef_stmt ::= CONST nameList_nonEmpty ASSIGN exprList_nonEmpty */
#line 364 "parser\\epparser.lemon"
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
#line 1703 "parser\\epparser.c"
        break;
      case 94: /* lvalue ::= NAME */
#line 385 "parser\\epparser.lemon"
{
    checkIsVariable(yymsp[0].minor.yy0->data);
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1711 "parser\\epparser.c"
        break;
      case 95: /* lvalue ::= expr LSQBRACKET NAME RSQBRACKET */
#line 390 "parser\\epparser.lemon"
{
    checkIsConstant(yymsp[-3].minor.yy0->data);
    yymsp[-1].minor.yy0->data = "_ARRW(" + yymsp[-3].minor.yy0->data + ", " + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
    delete yymsp[-3].minor.yy0;
}
#line 1721 "parser\\epparser.c"
        break;
      case 96: /* lvalue ::= expr PERIOD NAME */
#line 397 "parser\\epparser.lemon"
{
    checkIsConstant(yymsp[-2].minor.yy0->data);
    yymsp[0].minor.yy0->data = "_ATTW(" + yymsp[-2].minor.yy0->data + ", '" + yymsp[0].minor.yy0->data + "')";
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0);
    delete yymsp[-2].minor.yy0;
}
#line 1731 "parser\\epparser.c"
        break;
      case 99: /* assign_stmt ::= lvalue ASSIGN expr */
#line 406 "parser\\epparser.lemon"
{
    ps->gen << yymsp[-2].minor.yy0->data << " << (" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 1739 "parser\\epparser.c"
        break;
      case 100: /* assign_stmt ::= lvalueList_nonEmpty ASSIGN exprList_nonEmpty */
#line 411 "parser\\epparser.lemon"
{
    ps->gen << "_SV([" << yymsp[-2].minor.yy0->data << "], [" << yymsp[0].minor.yy0->data << "])" << std::endl;
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 1747 "parser\\epparser.c"
        break;
      case 101: /* if_start ::= IF */
#line 417 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDIf()" << std::endl;
}
#line 1755 "parser\\epparser.c"
        break;
      case 102: /* if_header ::= if_start LPAREN lexpr RPAREN */
      case 111: /* while_header ::= while_start LPAREN lexpr RPAREN */ yytestcase(yyruleno==111);
#line 421 "parser\\epparser.lemon"
{
    ps->gen << "if " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data << "):" << std::endl;
    ps->gen.indent();
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1765 "parser\\epparser.c"
        break;
      case 104: /* elif_start ::= ELSE IF */
#line 429 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen.unindent(false);
    ps->gen << yygotominor.yy0->data << " = EUDElseIf()" << std::endl;
}
#line 1774 "parser\\epparser.c"
        break;
      case 105: /* elif_header ::= elif_start LPAREN lexpr RPAREN */
#line 435 "parser\\epparser.lemon"
{
    ps->gen << "if " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data <<"):" << std::endl;
    ps->gen.indent();
}
#line 1782 "parser\\epparser.c"
        break;
      case 107: /* else_header ::= ELSE */
#line 442 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "if EUDElse()():" << std::endl;
    ps->gen.indent();
}
#line 1791 "parser\\epparser.c"
        break;
      case 108: /* if_stmt ::= if_block */
      case 109: /* if_stmt ::= if_block else_header stmt */ yytestcase(yyruleno==109);
#line 448 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndIf()" << std::endl;
}
#line 1800 "parser\\epparser.c"
        break;
      case 110: /* while_start ::= WHILE */
#line 460 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDWhile()" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1809 "parser\\epparser.c"
        break;
      case 112: /* while_stmt ::= while_header stmt */
#line 472 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndWhile()" << std::endl;
}
#line 1817 "parser\\epparser.c"
        break;
      case 113: /* for_opener ::= FOR LPAREN */
      case 128: /* foreach_opener ::= FOREACH LPAREN */ yytestcase(yyruleno==128);
#line 478 "parser\\epparser.lemon"
{
    ps->closure.pushScope();
}
#line 1825 "parser\\epparser.c"
        break;
      case 123: /* for_header1 ::= for_opener for_init_stmt SEMICOLON */
#line 494 "parser\\epparser.lemon"
{
    // opening for lexpr
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDWhile()" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1835 "parser\\epparser.c"
        break;
      case 124: /* for_header2 ::= for_header1 lexpr SEMICOLON */
#line 501 "parser\\epparser.lemon"
{
    ps->gen << "if " << yymsp[-2].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data << "):" << std::endl;
    ps->gen.indent();
    delete yymsp[-2].minor.yy0; delete yymsp[-1].minor.yy0;

    // Opening for assign_statement
    yygotominor.yy0 = genTemp(yymsp[-1].minor.yy0);
    ps->gen << "def " << yygotominor.yy0->data <<"():" << std::endl;
    ps->gen.indent();
}
#line 1849 "parser\\epparser.c"
        break;
      case 125: /* for_header ::= for_header2 for_action_stmt_nonEmpty RPAREN */
#line 512 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-2].minor.yy0;
    ps->gen.unindent(false);
}
#line 1857 "parser\\epparser.c"
        break;
      case 126: /* for_header ::= for_header2 RPAREN */
#line 517 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
    ps->gen << "pass" << std::endl;
    ps->gen.unindent(false);
}
#line 1866 "parser\\epparser.c"
        break;
      case 127: /* for_stmt ::= for_header stmt */
#line 523 "parser\\epparser.lemon"
{
    ps->gen << yymsp[-1].minor.yy0->data << "()" << std::endl;
    ps->gen.unindent(false);
    ps->gen << "EUDEndWhile()" << std::endl;
    ps->closure.popScope();
}
#line 1876 "parser\\epparser.c"
        break;
      case 129: /* foreach_header ::= foreach_opener nameList_nonEmpty COLON exprList_nonEmpty RPAREN */
#line 537 "parser\\epparser.lemon"
{
    commaListIter(yymsp[-3].minor.yy0->data, [&](std::string& s) {
        ps->closure.defVariable(s);
    });
    ps->gen << "for " << yymsp[-3].minor.yy0->data << " in " << yymsp[-1].minor.yy0->data << ":" << std::endl;
    ps->gen.indent();
}
#line 1887 "parser\\epparser.c"
        break;
      case 131: /* continue_stmt ::= CONTINUE */
#line 553 "parser\\epparser.lemon"
{
    ps->gen << "EUDContinue()" << std::endl;
}
#line 1894 "parser\\epparser.c"
        break;
      case 132: /* break_stmt ::= BREAK */
#line 557 "parser\\epparser.lemon"
{
    ps->gen << "EUDBreak()" << std::endl;
}
#line 1901 "parser\\epparser.c"
        break;
      case 133: /* return_stmt ::= RETURN exprList */
#line 564 "parser\\epparser.lemon"
{
    ps->gen << "EUDReturn(" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1909 "parser\\epparser.c"
        break;
      case 134: /* lexpr ::= CONDITIONNAME LPAREN fArgs RPAREN */
#line 572 "parser\\epparser.lemon"
{
    yymsp[-3].minor.yy0->data = yymsp[-3].minor.yy0->data + "(" + yymsp[-1].minor.yy0->data + ")";
    delete yymsp[-1].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 1918 "parser\\epparser.c"
        break;
      case 135: /* lexpr ::= CONDITIONNAME LPAREN RPAREN */
#line 578 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + "()";
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1926 "parser\\epparser.c"
        break;
      case 136: /* action ::= ACTIONNAME LPAREN fArgs RPAREN SEMICOLON */
#line 583 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[-4].minor.yy0);
    yygotominor.yy0->data =  yymsp[-4].minor.yy0->data + "(" + yymsp[-2].minor.yy0->data + ")";
    delete yymsp[-4].minor.yy0; delete yymsp[-2].minor.yy0;
}
#line 1935 "parser\\epparser.c"
        break;
      case 137: /* actions ::= action action */
      case 138: /* actions ::= actions action */ yytestcase(yyruleno==138);
#line 589 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
    yymsp[-1].minor.yy0->data += ",\n" + yymsp[0].minor.yy0->data;
    delete yymsp[0].minor.yy0;
}
#line 1945 "parser\\epparser.c"
        break;
      case 139: /* actionStmt ::= action */
#line 601 "parser\\epparser.lemon"
{
    ps->gen << "DoActions(" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1953 "parser\\epparser.c"
        break;
      case 140: /* actionStmt ::= actions */
#line 606 "parser\\epparser.lemon"
{
    ps->gen << "DoActions([" << std::endl;
    ps->gen.indent();
    ps->gen << yymsp[0].minor.yy0->data << std::endl;
    ps->gen.unindent(false);
    ps->gen << "])" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1965 "parser\\epparser.c"
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
      /* (18) blockStmt ::= lbracket return_stmt SEMICOLON rbracket */ yytestcase(yyruleno==18);
      /* (19) blockStmt ::= lbracket bodyStmtList rbracket */ yytestcase(yyruleno==19);
      /* (20) blockStmt ::= lbracket bodyStmtList return_stmt SEMICOLON rbracket */ yytestcase(yyruleno==20);
      /* (22) bodyStmt ::= blockStmt */ yytestcase(yyruleno==22);
      /* (23) bodyStmt ::= SEMICOLON */ yytestcase(yyruleno==23);
      /* (24) bodyStmt ::= vdef_stmt SEMICOLON */ yytestcase(yyruleno==24);
      /* (25) bodyStmt ::= vdefAssign_stmt SEMICOLON */ yytestcase(yyruleno==25);
      /* (26) bodyStmt ::= cdef_stmt SEMICOLON */ yytestcase(yyruleno==26);
      /* (27) bodyStmt ::= assign_stmt SEMICOLON */ yytestcase(yyruleno==27);
      /* (29) bodyStmt ::= actionStmt */ yytestcase(yyruleno==29);
      /* (30) bodyStmt ::= if_stmt */ yytestcase(yyruleno==30);
      /* (31) bodyStmt ::= while_stmt */ yytestcase(yyruleno==31);
      /* (32) bodyStmt ::= for_stmt */ yytestcase(yyruleno==32);
      /* (33) bodyStmt ::= foreach_stmt */ yytestcase(yyruleno==33);
      /* (34) bodyStmt ::= continue_stmt SEMICOLON */ yytestcase(yyruleno==34);
      /* (35) bodyStmt ::= break_stmt SEMICOLON */ yytestcase(yyruleno==35);
      /* (36) bodyStmtList ::= bodyStmt */ yytestcase(yyruleno==36);
      /* (37) bodyStmtList ::= bodyStmtList bodyStmt */ yytestcase(yyruleno==37);
      /* (103) if_block ::= if_header stmt */ yytestcase(yyruleno==103);
      /* (106) if_block ::= if_block elif_header stmt */ yytestcase(yyruleno==106);
      /* (114) for_init_stmt_nonEmpty ::= vdef_stmt */ yytestcase(yyruleno==114);
      /* (115) for_init_stmt_nonEmpty ::= vdefAssign_stmt */ yytestcase(yyruleno==115);
      /* (116) for_init_stmt_nonEmpty ::= cdef_stmt */ yytestcase(yyruleno==116);
      /* (117) for_init_stmt_nonEmpty ::= assign_stmt */ yytestcase(yyruleno==117);
      /* (118) for_init_stmt_nonEmpty ::= for_init_stmt_nonEmpty COMMA for_init_stmt_nonEmpty */ yytestcase(yyruleno==118);
      /* (119) for_init_stmt ::= for_init_stmt_nonEmpty */ yytestcase(yyruleno==119);
      /* (120) for_init_stmt ::= */ yytestcase(yyruleno==120);
      /* (121) for_action_stmt_nonEmpty ::= assign_stmt */ yytestcase(yyruleno==121);
      /* (122) for_action_stmt_nonEmpty ::= for_action_stmt_nonEmpty COMMA for_action_stmt_nonEmpty */ yytestcase(yyruleno==122);
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
#line 2054 "parser\\epparser.c"
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
#line 620 "parser\\epparser.lemon"


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
#line 2307 "parser\\epparser.c"
