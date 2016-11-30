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
#define YYNSTATE 234
#define YYNRULE 114
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
#define YY_ACTTAB_COUNT (645)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   100,  148,  144,  147,  233,   90,  142,  137,   99,   45,
 /*    10 */    46,   44,  176,  175,  174,  173,  172,  110,    5,   28,
 /*    20 */   152,  112,    6,  149,  169,  107,    3,  168,    2,  167,
 /*    30 */   166,  165,  150,  146,  136,  162,   59,   58,  170,  163,
 /*    40 */   100,    7,   26,  144,   29,   90,  135,  232,   99,  108,
 /*    50 */     4,    1,  176,  175,  174,  173,  172,  110,    5,   28,
 /*    60 */   194,   16,   17,  231,  169,  107,    3,  168,    2,  167,
 /*    70 */   166,  165,   19,  134,   27,  162,   59,   58,  170,  163,
 /*    80 */   203,    7,  100,   91,  139,   71,  138,   90,  230,  224,
 /*    90 */    99,  204,  139,   71,  176,  175,  174,  173,  172,  110,
 /*   100 */     5,   28,  191,   16,   17,   60,  169,  107,    3,  168,
 /*   110 */     2,  167,  166,  165,   22,   16,   17,  162,   59,   58,
 /*   120 */   170,  163,  100,    7,   89,  139,   71,   90,  142,   25,
 /*   130 */    99,  195,   22,  229,  176,  175,  174,  173,  172,  110,
 /*   140 */     5,   28,  188,  192,  209,  228,  169,  107,    3,  168,
 /*   150 */     2,  167,  166,  165,   87,  139,   71,  162,   59,   58,
 /*   160 */   170,  163,  206,    7,  100,   86,  139,   71,  227,   90,
 /*   170 */   130,  132,   99,  133,   70,  210,  176,  175,  174,  173,
 /*   180 */   172,  110,    5,   28,  186,   16,   17,  131,  169,  107,
 /*   190 */     3,  168,    2,  167,  166,  165,  133,   70,   84,  162,
 /*   200 */    59,   58,  170,  163,  100,    7,   85,  139,   71,   90,
 /*   210 */    19,   26,   99,  189,  136,   24,  176,  175,  174,  173,
 /*   220 */   172,  110,    5,   28,  153,  133,   70,   92,  169,  107,
 /*   230 */     3,  168,    2,  167,  166,  165,  143,  141,   18,  162,
 /*   240 */    59,   58,  170,  163,  126,    7,   98,  133,   61,  198,
 /*   250 */    83,   90,  231,  223,   99,  133,   70,   93,  176,  175,
 /*   260 */   174,  173,  172,  110,    5,   28,  133,   61,  125,  214,
 /*   270 */   169,  107,    3,  168,    2,  167,  166,  165,  123,   26,
 /*   280 */   122,   56,   59,   58,  170,  161,    8,  145,  133,   61,
 /*   290 */    90,  115,  200,   99,  222,   26,  120,  176,  175,  174,
 /*   300 */   173,  172,  110,    5,   28,  133,   61,   26,  213,  169,
 /*   310 */   107,    3,  168,    2,  167,  166,  165,  197,  143,  140,
 /*   320 */    57,   59,   58,  170,  160,  187,   22,  158,   35,   33,
 /*   330 */    32,   31,   30,   34,   40,   39,   41,   43,   42,   49,
 /*   340 */    48,   45,   46,   44,  119,  183,   38,   37,  133,   61,
 /*   350 */   221,  212,   36,  226,  129,  116,  101,  211,   47,  205,
 /*   360 */    15,  128,  127,  124,  121,  118,   49,   48,   45,   46,
 /*   370 */    44,  143,   88,   38,   37,  133,   61,  117,   79,   36,
 /*   380 */   226,  129,  220,  143,  105,   47,   13,   14,  128,  127,
 /*   390 */   124,  121,  118,  133,   61,   17,   78,  143,  151,  202,
 /*   400 */    38,   37,  143,  111,   50,  114,   36,  226,  129,  201,
 /*   410 */   133,   81,   47,  133,   82,  128,  127,  124,  121,  118,
 /*   420 */   349,    9,  133,   61,   12,   77,   11,   38,   37,  133,
 /*   430 */    63,  193,  114,   36,  226,  129,  133,  207,  211,   47,
 /*   440 */   208,   10,  128,  127,  124,  121,  118,   38,   37,  133,
 /*   450 */   219,   52,   23,   36,  226,  129,  133,  218,  211,   47,
 /*   460 */    96,  185,  128,  127,  124,  121,  118,   38,   37,  184,
 /*   470 */   133,   76,   20,   36,  226,  129,  133,   75,  181,   47,
 /*   480 */    80,  154,  128,  127,  124,  121,  118,   51,  182,  178,
 /*   490 */   133,   74,   53,  177,   54,  196,  171,  190,  106,   95,
 /*   500 */   104,  103,   80,   21,  102,  102,  180,  159,  133,   72,
 /*   510 */   133,   73,  133,  217,   53,  177,   54,  196,   94,  190,
 /*   520 */   106,   80,  104,  103,  159,   21,  145,  102,  179,  156,
 /*   530 */   133,  216,  109,   53,  177,   54,  196,  350,  190,  106,
 /*   540 */   350,  104,  103,  157,   21,  155,  102,  164,   40,   39,
 /*   550 */    41,   43,   42,   49,   48,   45,   46,   44,   41,   43,
 /*   560 */    42,   49,   48,   45,   46,   44,  225,   40,   39,   41,
 /*   570 */    43,   42,   49,   48,   45,   46,   44,   43,   42,   49,
 /*   580 */    48,   45,   46,   44,  133,  215,  133,   69,   38,   37,
 /*   590 */   234,  350,  350,  199,   36,  226,  129,  350,  133,   68,
 /*   600 */    47,  133,   67,  128,  127,  124,  121,  118,   40,   39,
 /*   610 */    41,   43,   42,   49,   48,   45,   46,   44,   39,   41,
 /*   620 */    43,   42,   49,   48,   45,   46,   44,  350,   55,  350,
 /*   630 */    54,  133,   66,  133,   65,  133,   64,  350,  113,  133,
 /*   640 */    62,  350,  350,  350,   97,
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
 /*   100 */    74,   75,   76,    3,    4,   27,   80,   81,   82,   83,
 /*   110 */    84,   85,   86,   87,    1,    3,    4,   91,   92,   93,
 /*   120 */    94,   95,   56,   97,   63,   64,   65,   61,    1,    2,
 /*   130 */    64,   31,    1,   28,   68,   69,   70,   71,   72,   73,
 /*   140 */    74,   75,   76,   31,   31,   25,   80,   81,   82,   83,
 /*   150 */    84,   85,   86,   87,   63,   64,   65,   91,   92,   93,
 /*   160 */    94,   95,   31,   97,   56,   63,   64,   65,   28,   61,
 /*   170 */    25,   27,   64,   64,   65,   66,   68,   69,   70,   71,
 /*   180 */    72,   73,   74,   75,   76,    3,    4,   27,   80,   81,
 /*   190 */    82,   83,   84,   85,   86,   87,   64,   65,   66,   91,
 /*   200 */    92,   93,   94,   95,   56,   97,   63,   64,   65,   61,
 /*   210 */    30,    1,   64,   31,   28,    2,   68,   69,   70,   71,
 /*   220 */    72,   73,   74,   75,   76,   64,   65,   66,   80,   81,
 /*   230 */    82,   83,   84,   85,   86,   87,   61,   62,   30,   91,
 /*   240 */    92,   93,   94,   95,   30,   97,   56,   64,   65,   39,
 /*   250 */    67,   61,   39,   31,   64,   64,   65,   66,   68,   69,
 /*   260 */    70,   71,   72,   73,   74,   75,   64,   65,   29,   67,
 /*   270 */    80,   81,   82,   83,   84,   85,   86,   87,   30,    1,
 /*   280 */    29,   91,   92,   93,   94,   95,   96,   26,   64,   65,
 /*   290 */    61,   67,   31,   64,   31,    1,   30,   68,   69,   70,
 /*   300 */    71,   72,   73,   74,   75,   64,   65,    1,   67,   80,
 /*   310 */    81,   82,   83,   84,   85,   86,   87,   39,   61,   62,
 /*   320 */    91,   92,   93,   94,   95,   31,    1,   98,    7,    8,
 /*   330 */     9,   10,   11,   12,   13,   14,   15,   16,   17,   18,
 /*   340 */    19,   20,   21,   22,   29,   39,   18,   19,   64,   65,
 /*   350 */    31,   67,   24,   25,   26,   29,   31,   29,   30,   31,
 /*   360 */     5,   33,   34,   35,   36,   37,   18,   19,   20,   21,
 /*   370 */    22,   61,   62,   18,   19,   64,   65,   30,   67,   24,
 /*   380 */    25,   26,   31,   61,   62,   30,   30,    5,   33,   34,
 /*   390 */    35,   36,   37,   64,   65,    4,   67,   61,   62,   26,
 /*   400 */    18,   19,   61,   62,   30,   50,   24,   25,   26,   31,
 /*   410 */    64,   65,   30,   64,   65,   33,   34,   35,   36,   37,
 /*   420 */    58,   59,   64,   65,   30,   67,   30,   18,   19,   64,
 /*   430 */    65,   41,   50,   24,   25,   26,   64,   65,   29,   30,
 /*   440 */    31,   30,   33,   34,   35,   36,   37,   18,   19,   64,
 /*   450 */    65,   30,   45,   24,   25,   26,   64,   65,   29,   30,
 /*   460 */    26,   39,   33,   34,   35,   36,   37,   18,   19,   39,
 /*   470 */    64,   65,   30,   24,   25,   26,   64,   65,   39,   30,
 /*   480 */    26,   53,   33,   34,   35,   36,   37,   55,   39,   39,
 /*   490 */    64,   65,   38,   39,   40,   41,   39,   43,   44,   25,
 /*   500 */    46,   47,   26,   49,   51,   51,   92,   53,   64,   65,
 /*   510 */    64,   65,   64,   65,   38,   39,   40,   41,   60,   43,
 /*   520 */    44,   26,   46,   47,   53,   49,   26,   51,   92,   53,
 /*   530 */    64,   65,   42,   38,   39,   40,   41,  101,   43,   44,
 /*   540 */   101,   46,   47,   98,   49,   98,   51,   52,   13,   14,
 /*   550 */    15,   16,   17,   18,   19,   20,   21,   22,   15,   16,
 /*   560 */    17,   18,   19,   20,   21,   22,   31,   13,   14,   15,
 /*   570 */    16,   17,   18,   19,   20,   21,   22,   16,   17,   18,
 /*   580 */    19,   20,   21,   22,   64,   65,   64,   65,   18,   19,
 /*   590 */     0,  101,  101,   39,   24,   25,   26,  101,   64,   65,
 /*   600 */    30,   64,   65,   33,   34,   35,   36,   37,   13,   14,
 /*   610 */    15,   16,   17,   18,   19,   20,   21,   22,   14,   15,
 /*   620 */    16,   17,   18,   19,   20,   21,   22,  101,   38,  101,
 /*   630 */    40,   64,   65,   64,   65,   64,   65,  101,   48,   64,
 /*   640 */    65,  101,  101,  101,   54,
};
#define YY_SHIFT_USE_DFLT (-23)
#define YY_SHIFT_COUNT (145)
#define YY_SHIFT_MIN   (-22)
#define YY_SHIFT_MAX   (604)
static const short yy_shift_ofst[] = {
 /*     0 */   -23,  495,  495,  495,  495,  495,  495,  476,  454,  590,
 /*    10 */   355,  355,  355,  409,  382,  382,  355,  355,  355,  328,
 /*    20 */   429,  449,  429,  570,  570,  570,  570,  570,  490,  570,
 /*    30 */   570,  570,  570,  570,  570,  570,  570,  570,  570,  570,
 /*    40 */   570,  570,  570,  570,  570,  570,  570,  570,  570,  570,
 /*    50 */   261,  500,  500,  500,  500,  500,  471,  471,  453,  453,
 /*    60 */   474,  321,  554,  535,  595,  595,  595,  595,  595,  595,
 /*    70 */   595,  595,  604,  543,  561,  348,  348,  182,  112,  100,
 /*    80 */    42,  -11,  -11,   58,  325,  306,  294,  278,  213,  210,
 /*    90 */   127,   41,  131,  113,   45,    6,  432,  434,  428,  457,
 /*   100 */   450,  439,  442,  430,  422,  407,  421,  411,  396,  390,
 /*   110 */   394,  378,  374,  373,  356,  391,  351,  326,  347,  319,
 /*   120 */   315,  266,  263,  251,  248,  222,  239,  214,  208,  180,
 /*   130 */   186,  145,  160,  144,  140,  120,  105,   63,   78,   59,
 /*   140 */    72,   24,   21,    5,  -22,    1,
};
#define YY_REDUCE_USE_DFLT (-68)
#define YY_REDUCE_COUNT (60)
#define YY_REDUCE_MIN   (-67)
#define YY_REDUCE_MAX   (575)
static const short yy_reduce_ofst[] = {
 /*     0 */   362,  148,  108,   66,   26,  -16,  -56,  190,  229,  -67,
 /*    10 */   358,  329,  311,  191,  284,  241,  224,  202,  183,  161,
 /*    20 */   132,  143,  109,  102,   91,   61,   28,   20,  -28,  575,
 /*    30 */   571,  569,  567,  537,  534,  522,  520,  466,  448,  446,
 /*    40 */   444,  426,  412,  406,  392,  385,  372,  365,  349,  346,
 /*    50 */   341,  336,  322,  310,  257,  175,  447,  445,  436,  414,
 /*    60 */   458,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   346,  348,  348,  348,  348,  348,  348,  348,  348,  348,
 /*    10 */   348,  348,  348,  348,  348,  348,  348,  348,  348,  348,
 /*    20 */   348,  348,  348,  348,  348,  348,  348,  348,  294,  348,
 /*    30 */   348,  348,  348,  348,  348,  348,  348,  348,  348,  348,
 /*    40 */   348,  348,  348,  348,  348,  348,  348,  348,  348,  348,
 /*    50 */   348,  348,  348,  348,  348,  348,  348,  348,  315,  314,
 /*    60 */   348,  348,  348,  348,  277,  276,  275,  274,  273,  272,
 /*    70 */   247,  243,  267,  268,  266,  265,  264,  348,  348,  348,
 /*    80 */   348,  259,  260,  348,  348,  348,  348,  348,  348,  348,
 /*    90 */   348,  348,  348,  348,  348,  348,  348,  348,  348,  348,
 /*   100 */   348,  348,  348,  348,  348,  348,  348,  348,  348,  293,
 /*   110 */   348,  348,  348,  348,  348,  279,  348,  348,  348,  348,
 /*   120 */   348,  348,  348,  348,  348,  348,  348,  348,  348,  246,
 /*   130 */   348,  348,  348,  252,  348,  348,  348,  348,  348,  252,
 /*   140 */   348,  348,  348,  240,  348,  239,  347,  345,  344,  343,
 /*   150 */   342,  341,  306,  295,  340,  337,  336,  339,  338,  333,
 /*   160 */   331,  330,  335,  334,  332,  329,  328,  327,  326,  325,
 /*   170 */   324,  323,  322,  321,  320,  319,  318,  317,  316,  313,
 /*   180 */   312,  311,  307,  308,  302,  301,  300,  299,  298,  297,
 /*   190 */   296,  292,  291,  290,  289,  288,  287,  283,  286,  285,
 /*   200 */   305,  304,  303,  284,  244,  251,  250,  261,  310,  309,
 /*   210 */   249,  248,  281,  280,  278,  271,  270,  269,  263,  262,
 /*   220 */   258,  257,  256,  255,  254,  253,  245,  241,  236,  242,
 /*   230 */   235,  282,  238,  237,
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
 /*  96 */ "bodyStmtList ::= bodyStmt",
 /*  97 */ "bodyStmtList ::= bodyStmtList bodyStmt",
 /*  98 */ "lbracket ::= LBRACKET",
 /*  99 */ "rbracket ::= RBRACKET",
 /* 100 */ "stmt ::= bodyStmt",
 /* 101 */ "stmt ::= return_stmt",
 /* 102 */ "stmt ::= lbracket RBRACKET",
 /* 103 */ "stmt ::= lbracket return_stmt rbracket",
 /* 104 */ "stmt ::= lbracket bodyStmtList rbracket",
 /* 105 */ "stmt ::= lbracket bodyStmtList return_stmt rbracket",
 /* 106 */ "stmt ::= lbracket error RBRACKET",
 /* 107 */ "import_chunk ::= FROM NAME IMPORT nameList",
 /* 108 */ "chunk ::= import_chunk",
 /* 109 */ "chunk ::= fdef_chunk",
 /* 110 */ "chunk ::= vdef_stmt",
 /* 111 */ "chunk ::= cdef_stmt",
 /* 112 */ "chunks ::=",
 /* 113 */ "chunks ::= chunks chunk",
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
#line 680 "parser\\epparser.c"
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
  { 96, 1 },
  { 96, 2 },
  { 97, 1 },
  { 98, 1 },
  { 76, 1 },
  { 76, 1 },
  { 76, 2 },
  { 76, 3 },
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
#line 1093 "parser\\epparser.c"
        break;
      case 3: /* nameListMulti ::= NAME COMMA NAME */
      case 4: /* nameListMulti ::= nameListMulti COMMA NAME */ yytestcase(yyruleno==4);
      case 10: /* exprList ::= exprList COMMA exprList */ yytestcase(yyruleno==10);
#line 63 "parser\\epparser.lemon"
{ yygotominor.yy0 = new Token((yymsp[-2].minor.yy0->data) + ", " + (yymsp[0].minor.yy0->data), yymsp[0].minor.yy0); delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1100 "parser\\epparser.c"
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
#line 1112 "parser\\epparser.c"
        break;
      case 7: /* exprList ::= funcexpr LSQBRACKET LSQBRACKET numList RSQBRACKET RSQBRACKET */
      case 8: /* expr ::= funcexpr LSQBRACKET LSQBRACKET NUMBER RSQBRACKET RSQBRACKET */ yytestcase(yyruleno==8);
#line 68 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[-2].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = _SRET(" << yymsp[-5].minor.yy0->data << ", [" << yymsp[-2].minor.yy0->data << "])" << std::endl;
    delete yymsp[-5].minor.yy0; delete yymsp[-2].minor.yy0;
}
#line 1122 "parser\\epparser.c"
        break;
      case 12: /* expr ::= NAME */
#line 85 "parser\\epparser.lemon"
{
    if(!ps->closure.getConstant(yymsp[0].minor.yy0->data) && !ps->closure.getVariable(yymsp[0].minor.yy0->data)) {
        throw_error(yymsp[0].minor.yy0->line, 103, ("Undeclared \'" + (yymsp[0].minor.yy0->data) + "\'"));
        ps->closure.defVariable(yymsp[0].minor.yy0->data);
    }
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1133 "parser\\epparser.c"
        break;
      case 15: /* fArgs ::= fArgs COMMA fArgs */
#line 96 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data;
    yymsp[-2].minor.yy0->type = TOKEN_TEMP;
    yygotominor.yy0 = yymsp[-2].minor.yy0;
}
#line 1142 "parser\\epparser.c"
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
#line 1157 "parser\\epparser.c"
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
#line 1172 "parser\\epparser.c"
        break;
      case 19: /* expr ::= LPAREN expr RPAREN */
#line 131 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0, ps->gen);
}
#line 1180 "parser\\epparser.c"
        break;
      case 20: /* expr ::= L2V LPAREN lexpr RPAREN */
#line 136 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "_L2V(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = genTemp(yymsp[-1].minor.yy0);
}
#line 1188 "parser\\epparser.c"
        break;
      case 21: /* expr ::= MAPSTRING LPAREN STRING RPAREN */
#line 141 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetStringIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0, ps->gen);
}
#line 1196 "parser\\epparser.c"
        break;
      case 22: /* expr ::= UNIT LPAREN STRING RPAREN */
#line 146 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetUnitIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0, ps->gen);
}
#line 1204 "parser\\epparser.c"
        break;
      case 23: /* expr ::= SWITCH LPAREN STRING RPAREN */
#line 151 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetSwitchIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0, ps->gen);
}
#line 1212 "parser\\epparser.c"
        break;
      case 24: /* expr ::= LOCATION LPAREN STRING RPAREN */
#line 156 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetLocationIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0, ps->gen);
}
#line 1220 "parser\\epparser.c"
        break;
      case 25: /* expr ::= expr PLUS expr */
#line 162 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "+",  yymsp[0].minor.yy0, ps->gen); }
#line 1225 "parser\\epparser.c"
        break;
      case 26: /* expr ::= expr MINUS expr */
#line 163 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "-",  yymsp[0].minor.yy0, ps->gen); }
#line 1230 "parser\\epparser.c"
        break;
      case 27: /* expr ::= expr MULTIPLY expr */
#line 164 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "*",  yymsp[0].minor.yy0, ps->gen); }
#line 1235 "parser\\epparser.c"
        break;
      case 28: /* expr ::= expr DIVIDE expr */
#line 165 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "//", yymsp[0].minor.yy0, ps->gen); }
#line 1240 "parser\\epparser.c"
        break;
      case 29: /* expr ::= expr MOD expr */
#line 166 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "%",  yymsp[0].minor.yy0, ps->gen); }
#line 1245 "parser\\epparser.c"
        break;
      case 30: /* expr ::= expr LSHIFT expr */
#line 167 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<<", yymsp[0].minor.yy0, ps->gen); }
#line 1250 "parser\\epparser.c"
        break;
      case 31: /* expr ::= expr RSHIFT expr */
#line 168 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">>", yymsp[0].minor.yy0, ps->gen); }
#line 1255 "parser\\epparser.c"
        break;
      case 32: /* expr ::= expr BITAND expr */
#line 169 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "&",  yymsp[0].minor.yy0, ps->gen); }
#line 1260 "parser\\epparser.c"
        break;
      case 33: /* expr ::= expr BITOR expr */
#line 170 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "|",  yymsp[0].minor.yy0, ps->gen); }
#line 1265 "parser\\epparser.c"
        break;
      case 34: /* expr ::= expr BITXOR expr */
#line 171 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "^",  yymsp[0].minor.yy0, ps->gen); }
#line 1270 "parser\\epparser.c"
        break;
      case 35: /* expr ::= PLUS expr */
#line 174 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = +" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1275 "parser\\epparser.c"
        break;
      case 36: /* expr ::= MINUS expr */
#line 175 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = -" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1280 "parser\\epparser.c"
        break;
      case 37: /* expr ::= BITNOT expr */
#line 176 "parser\\epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); ps->gen << yygotominor.yy0->data << " = ~" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1285 "parser\\epparser.c"
        break;
      case 38: /* lexpr ::= expr EQ expr */
#line 180 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "==", yymsp[0].minor.yy0, ps->gen); }
#line 1290 "parser\\epparser.c"
        break;
      case 39: /* lexpr ::= expr NE expr */
#line 181 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "!=", yymsp[0].minor.yy0, ps->gen); }
#line 1295 "parser\\epparser.c"
        break;
      case 40: /* lexpr ::= expr LE expr */
#line 182 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<=", yymsp[0].minor.yy0, ps->gen); }
#line 1300 "parser\\epparser.c"
        break;
      case 41: /* lexpr ::= expr LT expr */
#line 183 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<",  yymsp[0].minor.yy0, ps->gen); }
#line 1305 "parser\\epparser.c"
        break;
      case 42: /* lexpr ::= expr GE expr */
#line 184 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">=", yymsp[0].minor.yy0, ps->gen); }
#line 1310 "parser\\epparser.c"
        break;
      case 43: /* lexpr ::= expr GT expr */
#line 185 "parser\\epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">" , yymsp[0].minor.yy0, ps->gen); }
#line 1315 "parser\\epparser.c"
        break;
      case 44: /* lexpr ::= lexpr LAND lexpr */
#line 187 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "[" + yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data + "]";
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0, ps->gen);
}
#line 1324 "parser\\epparser.c"
        break;
      case 45: /* lexpr ::= lexpr LOR lexpr */
#line 193 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "EUDOr([" + yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data + "])";
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0, ps->gen);
}
#line 1333 "parser\\epparser.c"
        break;
      case 46: /* lexpr ::= LNOT lexpr */
#line 199 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = "EUDNot([" + yymsp[0].minor.yy0->data + "])";
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0, ps->gen);
}
#line 1341 "parser\\epparser.c"
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
#line 1358 "parser\\epparser.c"
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
#line 1374 "parser\\epparser.c"
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
#line 1390 "parser\\epparser.c"
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
#line 1402 "parser\\epparser.c"
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
#line 1418 "parser\\epparser.c"
        break;
      case 53: /* if_start ::= IF */
#line 272 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDIf()" << std::endl;
}
#line 1426 "parser\\epparser.c"
        break;
      case 54: /* if_header ::= if_start LPAREN lexpr RPAREN */
      case 63: /* while_header ::= while_start LPAREN lexpr RPAREN */ yytestcase(yyruleno==63);
#line 276 "parser\\epparser.lemon"
{
    ps->gen << "if " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data << "):" << std::endl;
    ps->gen.indent();
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1436 "parser\\epparser.c"
        break;
      case 56: /* elif_start ::= ELSE IF */
#line 284 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen.unindent(false);
    ps->gen << yygotominor.yy0->data << " = EUDElseIf()" << std::endl;
}
#line 1445 "parser\\epparser.c"
        break;
      case 57: /* elif_header ::= elif_start LPAREN lexpr RPAREN */
#line 290 "parser\\epparser.lemon"
{
    ps->gen << "if " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data <<"):" << std::endl;
    ps->gen.indent();
}
#line 1453 "parser\\epparser.c"
        break;
      case 59: /* else_header ::= ELSE */
#line 297 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "if EUDElse()():" << std::endl;
    ps->gen.indent();
}
#line 1462 "parser\\epparser.c"
        break;
      case 60: /* if_stmt ::= if_block */
      case 61: /* if_stmt ::= if_block else_header stmt */ yytestcase(yyruleno==61);
#line 303 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndIf()" << std::endl;
}
#line 1471 "parser\\epparser.c"
        break;
      case 62: /* while_start ::= WHILE */
#line 315 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDWhile()" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1480 "parser\\epparser.c"
        break;
      case 64: /* while_stmt ::= while_header stmt */
#line 327 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndWhile()" << std::endl;
}
#line 1488 "parser\\epparser.c"
        break;
      case 65: /* foreach_header ::= FOR LPAREN nameList COLON exprList RPAREN */
#line 333 "parser\\epparser.lemon"
{
    ps->closure.pushScope();
    commaListIter(yymsp[-3].minor.yy0->data, [&](std::string& s) {
        ps->closure.defVariable(s);
    });
    ps->gen << "for " << yymsp[-3].minor.yy0->data << " in " << yymsp[-1].minor.yy0->data << ":" << std::endl;
    ps->gen.indent();
}
#line 1500 "parser\\epparser.c"
        break;
      case 66: /* foreach_stmt ::= foreach_header stmt */
      case 72: /* fdef_chunk ::= function_header stmt */ yytestcase(yyruleno==72);
#line 342 "parser\\epparser.lemon"
{
    ps->gen.unindent(true);
    ps->closure.popScope();
}
#line 1509 "parser\\epparser.c"
        break;
      case 67: /* continue_stmt ::= CONTINUE SEMICOLON */
#line 349 "parser\\epparser.lemon"
{
    ps->gen << "EUDContinue()" << std::endl;
}
#line 1516 "parser\\epparser.c"
        break;
      case 68: /* break_stmt ::= BREAK SEMICOLON */
#line 353 "parser\\epparser.lemon"
{
    ps->gen << "EUDBreak()" << std::endl;
}
#line 1523 "parser\\epparser.c"
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
#line 1536 "parser\\epparser.c"
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
#line 1556 "parser\\epparser.c"
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
#line 1567 "parser\\epparser.c"
        break;
      case 73: /* return_stmt ::= RETURN SEMICOLON */
#line 400 "parser\\epparser.lemon"
{
    ps->gen << "EUDReturn()" << std::endl;
}
#line 1574 "parser\\epparser.c"
        break;
      case 74: /* return_stmt ::= RETURN exprList SEMICOLON */
#line 404 "parser\\epparser.lemon"
{
    ps->gen << "EUDReturn(" << yymsp[-1].minor.yy0->data << ")" << std::endl;
    delete yymsp[-1].minor.yy0;
}
#line 1582 "parser\\epparser.c"
        break;
      case 75: /* lexpr ::= CONDITIONNAME LPAREN fArgs RPAREN */
#line 412 "parser\\epparser.lemon"
{
    yymsp[-3].minor.yy0->data = yymsp[-3].minor.yy0->data + "(" + yymsp[-1].minor.yy0->data + ")";
    delete yymsp[-1].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0, ps->gen);
}
#line 1591 "parser\\epparser.c"
        break;
      case 76: /* lexpr ::= CONDITIONNAME LPAREN RPAREN */
#line 418 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + "()";
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0, ps->gen);
}
#line 1599 "parser\\epparser.c"
        break;
      case 77: /* action ::= ACTIONNAME LPAREN fArgs RPAREN SEMICOLON */
#line 423 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[-4].minor.yy0);
    yygotominor.yy0->data =  yymsp[-4].minor.yy0->data + "(" + yymsp[-2].minor.yy0->data + ")";
    delete yymsp[-4].minor.yy0; delete yymsp[-2].minor.yy0;
}
#line 1608 "parser\\epparser.c"
        break;
      case 78: /* actions ::= action action */
      case 79: /* actions ::= actions action */ yytestcase(yyruleno==79);
#line 429 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
    yymsp[-1].minor.yy0->data += ",\n" + yymsp[0].minor.yy0->data;
    delete yymsp[0].minor.yy0;
}
#line 1618 "parser\\epparser.c"
        break;
      case 80: /* actionStmt ::= action */
#line 441 "parser\\epparser.lemon"
{
    ps->gen << "DoActions(" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1626 "parser\\epparser.c"
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
#line 1638 "parser\\epparser.c"
        break;
      case 82: /* stmt ::= error SEMICOLON */
#line 457 "parser\\epparser.lemon"
{ throw_error(yymsp[0].minor.yy0->line, 6974, "Error while parsing statement"); }
#line 1643 "parser\\epparser.c"
        break;
      case 89: /* bodyStmt ::= funcexpr SEMICOLON */
#line 466 "parser\\epparser.lemon"
{ ps->gen << yymsp[-1].minor.yy0->data << std::endl; }
#line 1648 "parser\\epparser.c"
        break;
      case 98: /* lbracket ::= LBRACKET */
#line 477 "parser\\epparser.lemon"
{ ps->closure.pushScope(); }
#line 1653 "parser\\epparser.c"
        break;
      case 99: /* rbracket ::= RBRACKET */
#line 478 "parser\\epparser.lemon"
{ ps->closure.popScope(); }
#line 1658 "parser\\epparser.c"
        break;
      case 102: /* stmt ::= lbracket RBRACKET */
#line 482 "parser\\epparser.lemon"
{
    ps->gen << "pass" << std::endl;
    ps->closure.popScope();
}
#line 1666 "parser\\epparser.c"
        break;
      case 106: /* stmt ::= lbracket error RBRACKET */
#line 489 "parser\\epparser.lemon"
{
    throw_error(yymsp[0].minor.yy0->line, 6298, "Block not terminated properly.");
    ps->closure.popScope();
}
#line 1674 "parser\\epparser.c"
        break;
      case 107: /* import_chunk ::= FROM NAME IMPORT nameList */
#line 496 "parser\\epparser.lemon"
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
#line 1689 "parser\\epparser.c"
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
      /* (96) bodyStmtList ::= bodyStmt */ yytestcase(yyruleno==96);
      /* (97) bodyStmtList ::= bodyStmtList bodyStmt */ yytestcase(yyruleno==97);
      /* (100) stmt ::= bodyStmt */ yytestcase(yyruleno==100);
      /* (101) stmt ::= return_stmt */ yytestcase(yyruleno==101);
      /* (103) stmt ::= lbracket return_stmt rbracket */ yytestcase(yyruleno==103);
      /* (104) stmt ::= lbracket bodyStmtList rbracket */ yytestcase(yyruleno==104);
      /* (105) stmt ::= lbracket bodyStmtList return_stmt rbracket */ yytestcase(yyruleno==105);
      /* (108) chunk ::= import_chunk */ yytestcase(yyruleno==108);
      /* (109) chunk ::= fdef_chunk */ yytestcase(yyruleno==109);
      /* (110) chunk ::= vdef_stmt */ yytestcase(yyruleno==110);
      /* (111) chunk ::= cdef_stmt */ yytestcase(yyruleno==111);
      /* (112) chunks ::= */ yytestcase(yyruleno==112);
      /* (113) chunks ::= chunks chunk */ yytestcase(yyruleno==113);
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
#line 1782 "parser\\epparser.c"
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
#line 515 "parser\\epparser.lemon"


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
#line 2014 "parser\\epparser.c"
