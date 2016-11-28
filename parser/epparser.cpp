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
#include "epparser.h"
#include "pygen.h"
#include "tokenAdapter.h"
#include "parserUtilities.h"

int currentTokenizingLine;
#line 21 "parser/epparser.c"
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
#define YYNOCODE 86
#define YYACTIONTYPE unsigned short int
#define ParseTOKENTYPE Token*
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  int yy171;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL  PyGenerator* pGen ;
#define ParseARG_PDECL , PyGenerator* pGen 
#define ParseARG_FETCH  PyGenerator* pGen  = yypParser->pGen 
#define ParseARG_STORE yypParser->pGen  = pGen 
#define YYNSTATE 186
#define YYNRULE 93
#define YYERRORSYMBOL 47
#define YYERRSYMDT yy171
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
#define YY_ACTTAB_COUNT (536)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */    76,  185,  115,   28,  108,   83,  183,  104,   53,  115,
 /*    10 */   135,  134,  132,  133,  131,  130,    2,  159,  122,   99,
 /*    20 */     6,  128,    5,   96,    4,  127,    3,  126,  125,  124,
 /*    30 */    16,  107,   90,  123,   46,   45,  129,   83,  114,  104,
 /*    40 */    53,  184,  135,  134,  132,  133,  131,  130,  181,  120,
 /*    50 */   122,   99,    6,  128,    5,   96,    4,  127,    3,  126,
 /*    60 */   125,  124,  115,   27,   90,  123,   46,   45,  129,   83,
 /*    70 */   182,  104,   53,  186,  135,  134,  132,  133,  131,  130,
 /*    80 */   106,   97,  122,   99,    6,  128,    5,   96,    4,  127,
 /*    90 */     3,  126,  125,  124,  184,  114,   20,  123,   46,   45,
 /*   100 */   129,   90,   39,   40,   38,   50,   83,  105,  104,   53,
 /*   110 */   114,  135,  134,  132,  133,  131,  130,  113,  150,  122,
 /*   120 */    99,    6,  128,    5,   96,    4,  127,    3,  126,  125,
 /*   130 */   124,  114,   19,   90,  123,   46,   45,  129,   83,  180,
 /*   140 */   104,   53,   29,  135,  134,  132,  133,  131,  130,   44,
 /*   150 */   147,  122,   99,    6,  128,    5,   96,    4,  127,    3,
 /*   160 */   126,  125,  124,  182,  104,   73,  123,   46,   45,  129,
 /*   170 */    90,  166,   29,   13,   14,   83,   29,  104,   53,   29,
 /*   180 */   135,  134,  132,  133,  131,  130,   29,  145,  122,   99,
 /*   190 */     6,  128,    5,   96,    4,  127,    3,  126,  125,  124,
 /*   200 */   152,  146,   90,  123,   46,   45,  129,   83,  163,  104,
 /*   210 */    53,  160,  135,  134,  132,  133,  131,  130,  142,  158,
 /*   220 */   122,   99,    6,  128,    5,   96,    4,  127,    3,  126,
 /*   230 */   125,  124,  115,   32,   31,  123,   46,   45,  129,   30,
 /*   240 */   174,   75,  111,  137,   42,  121,  179,   48,  136,    1,
 /*   250 */   157,  156,  114,  109,  149,   95,   49,   94,   93,   29,
 /*   260 */     9,   92,   26,   24,   23,   22,   21,   25,   34,   33,
 /*   270 */    35,   37,   36,   43,   41,   39,   40,   38,  178,   32,
 /*   280 */    31,   82,  110,   63,  177,   30,  174,   75,   91,  176,
 /*   290 */    42,  175,   18,   48,  136,    1,  103,  156,  104,   55,
 /*   300 */   149,   95,  102,   94,   93,  107,    9,   92,   34,   33,
 /*   310 */    35,   37,   36,   43,   41,   39,   40,   38,   37,   36,
 /*   320 */    43,   41,   39,   40,   38,  173,   34,   33,   35,   37,
 /*   330 */    36,   43,   41,   39,   40,   38,   16,  118,   15,  117,
 /*   340 */    43,   41,   39,   40,   38,  101,  164,   34,   33,   35,
 /*   350 */    37,   36,   43,   41,   39,   40,   38,  112,    7,  119,
 /*   360 */    13,   14,  104,   74,  116,  104,  172,  162,   34,   33,
 /*   370 */    35,   37,   36,   43,   41,   39,   40,   38,   81,  110,
 /*   380 */    63,   79,  110,   63,   77,  110,   63,  148,  161,   34,
 /*   390 */    33,   35,   37,   36,   43,   41,   39,   40,   38,   14,
 /*   400 */    84,  110,   63,   33,   35,   37,   36,   43,   41,   39,
 /*   410 */    40,   38,   35,   37,   36,   43,   41,   39,   40,   38,
 /*   420 */   104,  171,   32,   31,   12,  104,   51,   70,   30,  174,
 /*   430 */   100,  104,  170,   42,  165,   10,   11,   32,   31,  104,
 /*   440 */    51,  155,   88,   30,  174,  100,  104,   68,   42,   32,
 /*   450 */    31,  151,  104,   51,   98,   30,  174,  100,  280,    8,
 /*   460 */    42,  144,   32,   31,  104,   51,  154,   47,   30,  174,
 /*   470 */   100,  104,   67,   42,   32,   31,   89,  141,  104,   66,
 /*   480 */    30,  174,  100,  104,   64,   42,  104,   65,  104,   51,
 /*   490 */   153,  104,   51,   69,   78,  110,   63,  143,   86,  104,
 /*   500 */   169,  104,  168,  104,  167,  104,   62,  104,   54,  104,
 /*   510 */    52,  104,   61,   17,  140,  104,   60,  104,   59,  104,
 /*   520 */    58,  104,   57,  104,   56,  137,   85,   72,   71,   80,
 /*   530 */   111,   92,   87,  139,  281,  138,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    47,   26,    1,    2,    1,   52,   26,   54,   55,    1,
 /*    10 */    57,   58,   59,   60,   61,   62,   63,   64,   65,   66,
 /*    20 */    67,   68,   69,   70,   71,   72,   73,   74,   75,   76,
 /*    30 */    29,   28,   47,   80,   81,   82,   83,   52,    1,   54,
 /*    40 */    55,   33,   57,   58,   59,   60,   61,   62,   26,   64,
 /*    50 */    65,   66,   67,   68,   69,   70,   71,   72,   73,   74,
 /*    60 */    75,   76,    1,    2,   47,   80,   81,   82,   83,   52,
 /*    70 */    33,   54,   55,    0,   57,   58,   59,   60,   61,   62,
 /*    80 */     1,   64,   65,   66,   67,   68,   69,   70,   71,   72,
 /*    90 */    73,   74,   75,   76,   33,    1,    2,   80,   81,   82,
 /*   100 */    83,   47,   20,   21,   22,   32,   52,   28,   54,   55,
 /*   110 */     1,   57,   58,   59,   60,   61,   62,   44,   64,   65,
 /*   120 */    66,   67,   68,   69,   70,   71,   72,   73,   74,   75,
 /*   130 */    76,    1,    2,   47,   80,   81,   82,   83,   52,   30,
 /*   140 */    54,   55,    1,   57,   58,   59,   60,   61,   62,   29,
 /*   150 */    64,   65,   66,   67,   68,   69,   70,   71,   72,   73,
 /*   160 */    74,   75,   76,   33,   54,   55,   80,   81,   82,   83,
 /*   170 */    47,   30,    1,    3,    4,   52,    1,   54,   55,    1,
 /*   180 */    57,   58,   59,   60,   61,   62,    1,   64,   65,   66,
 /*   190 */    67,   68,   69,   70,   71,   72,   73,   74,   75,   76,
 /*   200 */    30,   30,   47,   80,   81,   82,   83,   52,   33,   54,
 /*   210 */    55,   33,   57,   58,   59,   60,   61,   62,   33,   64,
 /*   220 */    65,   66,   67,   68,   69,   70,   71,   72,   73,   74,
 /*   230 */    75,   76,    1,   18,   19,   80,   81,   82,   83,   24,
 /*   240 */    25,   26,   26,   33,   29,   35,   30,   32,   33,   34,
 /*   250 */    35,   36,    1,   27,   39,   40,   27,   42,   43,    1,
 /*   260 */    45,   46,    7,    8,    9,   10,   11,   12,   13,   14,
 /*   270 */    15,   16,   17,   18,   19,   20,   21,   22,   25,   18,
 /*   280 */    19,   53,   54,   55,   28,   24,   25,   26,   30,   25,
 /*   290 */    29,   28,   41,   32,   33,   34,   27,   36,   54,   55,
 /*   300 */    39,   40,   27,   42,   43,   28,   45,   46,   13,   14,
 /*   310 */    15,   16,   17,   18,   19,   20,   21,   22,   16,   17,
 /*   320 */    18,   19,   20,   21,   22,   30,   13,   14,   15,   16,
 /*   330 */    17,   18,   19,   20,   21,   22,   29,   57,   29,   59,
 /*   340 */    18,   19,   20,   21,   22,   25,   33,   13,   14,   15,
 /*   350 */    16,   17,   18,   19,   20,   21,   22,   77,   78,   79,
 /*   360 */     3,    4,   54,   55,   84,   54,   55,   33,   13,   14,
 /*   370 */    15,   16,   17,   18,   19,   20,   21,   22,   53,   54,
 /*   380 */    55,   53,   54,   55,   53,   54,   55,   30,   33,   13,
 /*   390 */    14,   15,   16,   17,   18,   19,   20,   21,   22,    4,
 /*   400 */    53,   54,   55,   14,   15,   16,   17,   18,   19,   20,
 /*   410 */    21,   22,   15,   16,   17,   18,   19,   20,   21,   22,
 /*   420 */    54,   55,   18,   19,    5,   54,   55,   56,   24,   25,
 /*   430 */    26,   54,   55,   29,   30,   29,    5,   18,   19,   54,
 /*   440 */    55,   56,   52,   24,   25,   26,   54,   55,   29,   18,
 /*   450 */    19,   38,   54,   55,   56,   24,   25,   26,   49,   50,
 /*   460 */    29,   33,   18,   19,   54,   55,   56,   29,   24,   25,
 /*   470 */    26,   54,   55,   29,   18,   19,   26,   33,   54,   55,
 /*   480 */    24,   25,   26,   54,   55,   29,   54,   55,   54,   55,
 /*   490 */    56,   54,   55,   56,   53,   54,   55,   33,   25,   54,
 /*   500 */    55,   54,   55,   54,   55,   54,   55,   54,   55,   54,
 /*   510 */    55,   54,   55,   29,   33,   54,   55,   54,   55,   54,
 /*   520 */    55,   54,   55,   54,   55,   33,   51,   26,   52,   52,
 /*   530 */    26,   46,   52,   81,   85,   81,
};
#define YY_SHIFT_USE_DFLT (-26)
#define YY_SHIFT_COUNT (115)
#define YY_SHIFT_MIN   (-25)
#define YY_SHIFT_MAX   (504)
static const short yy_shift_ofst[] = {
 /*     0 */   -26,  261,  215,  261,  261,  261,  261,  261,   73,  444,
 /*    10 */   419,  431,  431,  419,  419,  419,  404,  456,  456,  456,
 /*    20 */   456,  456,  456,  456,  456,  456,  456,  456,  456,  456,
 /*    30 */   456,  456,  456,  456,  456,  456,  456,  456,  456,  456,
 /*    40 */   456,  456,  456,  456,  216,  485,  485,  504,  501,  473,
 /*    50 */   450,  255,  355,  334,  313,  295,  376,  376,  376,  376,
 /*    60 */   376,  376,  376,  376,  389,  397,  302,  322,  322,  357,
 /*    70 */   170,  130,   61,   82,   82,    1,  210,  258,  185,  171,
 /*    80 */   251,  178,  175,   94,  141,   79,    3,  109,   37,    8,
 /*    90 */   492,  481,  484,  464,  428,  438,  406,  413,  395,  309,
 /*   100 */   307,  277,  320,  275,  269,  263,  264,  256,  253,  229,
 /*   110 */   226,  231,  120,   22,  -20,  -25,
};
#define YY_REDUCE_USE_DFLT (-48)
#define YY_REDUCE_COUNT (50)
#define YY_REDUCE_MIN   (-47)
#define YY_REDUCE_MAX   (480)
static const short yy_reduce_ofst[] = {
 /*     0 */   409,  -47,  155,  123,   86,   54,   17,  -15,  280,  441,
 /*    10 */   437,  434,  410,  398,  385,  371,  347,  331,  328,  325,
 /*    20 */   228,  469,  467,  465,  463,  461,  457,  455,  453,  451,
 /*    30 */   449,  447,  445,  432,  429,  424,  417,  392,  377,  366,
 /*    40 */   311,  308,  244,  110,  480,  454,  452,  477,  476,  475,
 /*    50 */   390,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   277,  279,  279,  279,  279,  279,  279,  279,  279,  279,
 /*    10 */   279,  279,  279,  279,  279,  279,  279,  279,  279,  279,
 /*    20 */   279,  279,  279,  279,  279,  279,  279,  279,  279,  279,
 /*    30 */   279,  279,  279,  279,  279,  279,  279,  279,  279,  279,
 /*    40 */   279,  279,  279,  279,  279,  256,  255,  279,  279,  279,
 /*    50 */   279,  279,  279,  279,  279,  279,  219,  218,  217,  216,
 /*    60 */   215,  214,  194,  193,  209,  210,  208,  207,  206,  279,
 /*    70 */   279,  279,  279,  201,  202,  196,  279,  279,  279,  279,
 /*    80 */   279,  279,  279,  279,  279,  279,  279,  279,  279,  279,
 /*    90 */   279,  279,  279,  279,  279,  279,  279,  236,  221,  279,
 /*   100 */   196,  279,  279,  279,  199,  279,  279,  279,  279,  279,
 /*   110 */   199,  279,  279,  279,  279,  279,  278,  276,  275,  274,
 /*   120 */   249,  233,  273,  272,  271,  270,  269,  268,  267,  266,
 /*   130 */   264,  263,  262,  261,  260,  259,  258,  257,  254,  253,
 /*   140 */   252,  250,  251,  245,  244,  243,  242,  241,  240,  239,
 /*   150 */   238,  237,  235,  223,  222,  220,  234,  232,  231,  230,
 /*   160 */   227,  225,  265,  229,  228,  198,  197,  213,  212,  211,
 /*   170 */   205,  204,  203,  200,  195,  191,  188,  192,  187,  248,
 /*   180 */   247,  246,  226,  190,  224,  189,
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
  "RSQBRACKET",    "LPAREN",        "RPAREN",        "FUNCCALL",    
  "VAR",           "SEMICOLON",     "LBRACKET",      "RBRACKET",    
  "IF",            "IFX",           "ELSE",          "WHILE",       
  "FOR",           "COLON",         "CONTINUE",      "BREAK",       
  "FUNCTION",      "RETURN",        "ACTIONNAME",    "error",       
  "nt",            "program",       "chunks",        "numList",     
  "nameList",      "exprList",      "funcexpr",      "expr",        
  "lexpr",         "vdef_stmt",     "vdefAssign_stmt",  "vdefMulti_stmt",
  "vdefMultiAssign_stmt",  "assign_stmt",   "assignMulti_stmt",  "stmtList",    
  "stmt",          "block",         "if_start",      "if_header",   
  "if_stmt",       "else_header",   "while_start",   "while_header",
  "while_stmt",    "foreach_header",  "foreach_stmt",  "continue_stmt",
  "break_stmt",    "function_start",  "function_header",  "fdef_chunk",  
  "return_stmt",   "action",        "actions",       "actionStmt",  
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
 /*   3 */ "nameList ::= NAME COMMA NAME",
 /*   4 */ "nameList ::= nameList COMMA NAME",
 /*   5 */ "exprList ::= funcexpr LSQBRACKET LSQBRACKET numList RSQBRACKET RSQBRACKET",
 /*   6 */ "expr ::= funcexpr LSQBRACKET LSQBRACKET NUMBER RSQBRACKET RSQBRACKET",
 /*   7 */ "exprList ::= expr",
 /*   8 */ "exprList ::= exprList COMMA expr",
 /*   9 */ "expr ::= NUMBER",
 /*  10 */ "expr ::= NAME",
 /*  11 */ "funcexpr ::= NAME LPAREN exprList RPAREN",
 /*  12 */ "funcexpr ::= NAME LPAREN RPAREN",
 /*  13 */ "expr ::= funcexpr",
 /*  14 */ "expr ::= LPAREN expr RPAREN",
 /*  15 */ "expr ::= expr PLUS expr",
 /*  16 */ "expr ::= expr MINUS expr",
 /*  17 */ "expr ::= expr MULTIPLY expr",
 /*  18 */ "expr ::= expr DIVIDE expr",
 /*  19 */ "expr ::= expr MOD expr",
 /*  20 */ "expr ::= expr LSHIFT expr",
 /*  21 */ "expr ::= expr RSHIFT expr",
 /*  22 */ "expr ::= expr BITAND expr",
 /*  23 */ "expr ::= expr BITOR expr",
 /*  24 */ "expr ::= expr BITXOR expr",
 /*  25 */ "expr ::= PLUS expr",
 /*  26 */ "expr ::= MINUS expr",
 /*  27 */ "expr ::= BITNOT expr",
 /*  28 */ "lexpr ::= expr EQ expr",
 /*  29 */ "lexpr ::= expr NE expr",
 /*  30 */ "lexpr ::= expr LE expr",
 /*  31 */ "lexpr ::= expr LT expr",
 /*  32 */ "lexpr ::= expr GE expr",
 /*  33 */ "lexpr ::= expr GT expr",
 /*  34 */ "lexpr ::= lexpr LAND lexpr",
 /*  35 */ "lexpr ::= lexpr LOR lexpr",
 /*  36 */ "lexpr ::= LNOT lexpr",
 /*  37 */ "lexpr ::= LNOT LNOT lexpr",
 /*  38 */ "vdef_stmt ::= VAR NAME SEMICOLON",
 /*  39 */ "vdefAssign_stmt ::= VAR NAME ASSIGN expr SEMICOLON",
 /*  40 */ "vdefMulti_stmt ::= VAR nameList SEMICOLON",
 /*  41 */ "vdefMultiAssign_stmt ::= VAR nameList ASSIGN exprList SEMICOLON",
 /*  42 */ "assign_stmt ::= NAME ASSIGN expr SEMICOLON",
 /*  43 */ "assignMulti_stmt ::= nameList ASSIGN exprList SEMICOLON",
 /*  44 */ "stmtList ::= stmt",
 /*  45 */ "stmtList ::= stmtList stmt",
 /*  46 */ "block ::= LBRACKET stmtList RBRACKET",
 /*  47 */ "block ::= LBRACKET error RBRACKET",
 /*  48 */ "if_start ::= IF",
 /*  49 */ "if_header ::= if_start LPAREN lexpr RPAREN",
 /*  50 */ "if_stmt ::= if_header stmt",
 /*  51 */ "else_header ::= if_header stmt ELSE",
 /*  52 */ "if_stmt ::= else_header stmt",
 /*  53 */ "while_start ::= WHILE",
 /*  54 */ "while_header ::= while_start LPAREN lexpr RPAREN",
 /*  55 */ "while_stmt ::= while_header stmt",
 /*  56 */ "foreach_header ::= FOR LPAREN nameList COLON exprList RPAREN",
 /*  57 */ "foreach_stmt ::= foreach_header stmt",
 /*  58 */ "continue_stmt ::= CONTINUE SEMICOLON",
 /*  59 */ "break_stmt ::= BREAK SEMICOLON",
 /*  60 */ "function_start ::= FUNCTION NAME",
 /*  61 */ "function_header ::= function_start LPAREN nameList RPAREN",
 /*  62 */ "function_header ::= function_start LPAREN RPAREN",
 /*  63 */ "fdef_chunk ::= function_header stmt",
 /*  64 */ "return_stmt ::= RETURN SEMICOLON",
 /*  65 */ "return_stmt ::= RETURN exprList SEMICOLON",
 /*  66 */ "action ::= ACTIONNAME LPAREN exprList RPAREN SEMICOLON",
 /*  67 */ "actions ::= action action",
 /*  68 */ "actions ::= actions action",
 /*  69 */ "actionStmt ::= action",
 /*  70 */ "actionStmt ::= actions",
 /*  71 */ "stmt ::= error SEMICOLON",
 /*  72 */ "stmt ::= SEMICOLON",
 /*  73 */ "stmt ::= vdef_stmt",
 /*  74 */ "stmt ::= vdefAssign_stmt",
 /*  75 */ "stmt ::= vdefMultiAssign_stmt",
 /*  76 */ "stmt ::= vdefMulti_stmt",
 /*  77 */ "stmt ::= assign_stmt",
 /*  78 */ "stmt ::= assignMulti_stmt",
 /*  79 */ "stmt ::= expr SEMICOLON",
 /*  80 */ "stmt ::= actionStmt",
 /*  81 */ "stmt ::= if_stmt",
 /*  82 */ "stmt ::= while_stmt",
 /*  83 */ "stmt ::= foreach_stmt",
 /*  84 */ "stmt ::= continue_stmt",
 /*  85 */ "stmt ::= break_stmt",
 /*  86 */ "stmt ::= return_stmt",
 /*  87 */ "stmt ::= block",
 /*  88 */ "chunk ::= fdef_chunk",
 /*  89 */ "chunk ::= vdef_stmt",
 /*  90 */ "chunk ::= vdefMulti_stmt",
 /*  91 */ "chunks ::=",
 /*  92 */ "chunks ::= chunks chunk",
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
    case 48: /* nt */
{
#line 28 "parser/epparser.lemon"
 delete (yypminor->yy0); 
#line 618 "parser/epparser.c"
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
  { 49, 1 },
  { 51, 3 },
  { 51, 3 },
  { 52, 3 },
  { 52, 3 },
  { 53, 6 },
  { 55, 6 },
  { 53, 1 },
  { 53, 3 },
  { 55, 1 },
  { 55, 1 },
  { 54, 4 },
  { 54, 3 },
  { 55, 1 },
  { 55, 3 },
  { 55, 3 },
  { 55, 3 },
  { 55, 3 },
  { 55, 3 },
  { 55, 3 },
  { 55, 3 },
  { 55, 3 },
  { 55, 3 },
  { 55, 3 },
  { 55, 3 },
  { 55, 2 },
  { 55, 2 },
  { 55, 2 },
  { 56, 3 },
  { 56, 3 },
  { 56, 3 },
  { 56, 3 },
  { 56, 3 },
  { 56, 3 },
  { 56, 3 },
  { 56, 3 },
  { 56, 2 },
  { 56, 3 },
  { 57, 3 },
  { 58, 5 },
  { 59, 3 },
  { 60, 5 },
  { 61, 4 },
  { 62, 4 },
  { 63, 1 },
  { 63, 2 },
  { 65, 3 },
  { 65, 3 },
  { 66, 1 },
  { 67, 4 },
  { 68, 2 },
  { 69, 3 },
  { 68, 2 },
  { 70, 1 },
  { 71, 4 },
  { 72, 2 },
  { 73, 6 },
  { 74, 2 },
  { 75, 2 },
  { 76, 2 },
  { 77, 2 },
  { 78, 4 },
  { 78, 3 },
  { 79, 2 },
  { 80, 2 },
  { 80, 3 },
  { 81, 5 },
  { 82, 2 },
  { 82, 2 },
  { 83, 1 },
  { 83, 1 },
  { 64, 2 },
  { 64, 1 },
  { 64, 1 },
  { 64, 1 },
  { 64, 1 },
  { 64, 1 },
  { 64, 1 },
  { 64, 1 },
  { 64, 2 },
  { 64, 1 },
  { 64, 1 },
  { 64, 1 },
  { 64, 1 },
  { 64, 1 },
  { 64, 1 },
  { 64, 1 },
  { 64, 1 },
  { 84, 1 },
  { 84, 1 },
  { 84, 1 },
  { 50, 0 },
  { 50, 2 },
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
#line 54 "parser/epparser.lemon"
{
    yygotominor.yy0 = new Token(yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data, yymsp[0].minor.yy0);
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 1010 "parser/epparser.c"
        break;
      case 3: /* nameList ::= NAME COMMA NAME */
      case 4: /* nameList ::= nameList COMMA NAME */ yytestcase(yyruleno==4);
      case 8: /* exprList ::= exprList COMMA expr */ yytestcase(yyruleno==8);
#line 62 "parser/epparser.lemon"
{ yygotominor.yy0 = new Token((yymsp[-2].minor.yy0->data) + ", " + (yymsp[0].minor.yy0->data), yymsp[0].minor.yy0); delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1017 "parser/epparser.c"
        break;
      case 5: /* exprList ::= funcexpr LSQBRACKET LSQBRACKET numList RSQBRACKET RSQBRACKET */
      case 6: /* expr ::= funcexpr LSQBRACKET LSQBRACKET NUMBER RSQBRACKET RSQBRACKET */ yytestcase(yyruleno==6);
#line 64 "parser/epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[-2].minor.yy0);
    (*pGen) << yygotominor.yy0->data << " = _SRET(" << yymsp[-5].minor.yy0->data << ", [" << yymsp[-2].minor.yy0->data << "])" << std::endl;
    delete yymsp[-5].minor.yy0; delete yymsp[-2].minor.yy0;
}
#line 1027 "parser/epparser.c"
        break;
      case 7: /* exprList ::= expr */
      case 9: /* expr ::= NUMBER */ yytestcase(yyruleno==9);
      case 13: /* expr ::= funcexpr */ yytestcase(yyruleno==13);
      case 37: /* lexpr ::= LNOT LNOT lexpr */ yytestcase(yyruleno==37);
#line 75 "parser/epparser.lemon"
{ yygotominor.yy0 = yymsp[0].minor.yy0; }
#line 1035 "parser/epparser.c"
        break;
      case 10: /* expr ::= NAME */
#line 80 "parser/epparser.lemon"
{
    if(pGen->undefined(yymsp[0].minor.yy0->data)) {
        throw_error(yymsp[0].minor.yy0->line, 103, ("Undeclared variable \'" + (yymsp[0].minor.yy0->data) + "\'"));
        pGen->namedef(yymsp[0].minor.yy0->data);
    }
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1046 "parser/epparser.c"
        break;
      case 11: /* funcexpr ::= NAME LPAREN exprList RPAREN */
#line 89 "parser/epparser.lemon"
{
    // Preprocess yymsp[-3].minor.yy0
    if(yymsp[-3].minor.yy0->data[0] == '_' || ('A' <= yymsp[-3].minor.yy0->data[0] && yymsp[-3].minor.yy0->data[0] <= 'Z'));  // Name starts with uppercase -> Don't modify
    else {
        yymsp[-3].minor.yy0->data = "f_" + yymsp[-3].minor.yy0->data;
    }
    /*
    if (pGen->undefined(yymsp[-3].minor.yy0->data)) {
        throw_error(yymsp[-3].minor.yy0->line, 4449, ("Undefined function " + yymsp[-3].minor.yy0->data));
        pGen->namedef(yymsp[-3].minor.yy0->data);
    }
    */

    yymsp[-3].minor.yy0->data += "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0, *pGen);
}
#line 1066 "parser/epparser.c"
        break;
      case 12: /* funcexpr ::= NAME LPAREN RPAREN */
#line 107 "parser/epparser.lemon"
{
    // Preprocess yymsp[-2].minor.yy0
    if(yymsp[-2].minor.yy0->data[0] == '_' || ('A' <= yymsp[-2].minor.yy0->data[0] && yymsp[-2].minor.yy0->data[0] <= 'Z'));  // Name starts with uppercase -> Don't modify
    else {
        yymsp[-2].minor.yy0->data = "f_" + yymsp[-2].minor.yy0->data;
    }

    /*
    if (pGen->undefined(yymsp[-2].minor.yy0->data)) {
        throw_error(yymsp[-2].minor.yy0->line, 4449, ("Undefined function " + yymsp[-2].minor.yy0->data));
        pGen->namedef(yymsp[-2].minor.yy0->data);
    }
    */

    yymsp[-2].minor.yy0->data += "()";
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0, *pGen);
}
#line 1087 "parser/epparser.c"
        break;
      case 14: /* expr ::= LPAREN expr RPAREN */
#line 128 "parser/epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0, *pGen);
}
#line 1095 "parser/epparser.c"
        break;
      case 15: /* expr ::= expr PLUS expr */
#line 133 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "+",  yymsp[0].minor.yy0, *pGen); }
#line 1100 "parser/epparser.c"
        break;
      case 16: /* expr ::= expr MINUS expr */
#line 134 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "-",  yymsp[0].minor.yy0, *pGen); }
#line 1105 "parser/epparser.c"
        break;
      case 17: /* expr ::= expr MULTIPLY expr */
#line 135 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "*",  yymsp[0].minor.yy0, *pGen); }
#line 1110 "parser/epparser.c"
        break;
      case 18: /* expr ::= expr DIVIDE expr */
#line 136 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "//", yymsp[0].minor.yy0, *pGen); }
#line 1115 "parser/epparser.c"
        break;
      case 19: /* expr ::= expr MOD expr */
#line 137 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "%",  yymsp[0].minor.yy0, *pGen); }
#line 1120 "parser/epparser.c"
        break;
      case 20: /* expr ::= expr LSHIFT expr */
#line 138 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<<", yymsp[0].minor.yy0, *pGen); }
#line 1125 "parser/epparser.c"
        break;
      case 21: /* expr ::= expr RSHIFT expr */
#line 139 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">>", yymsp[0].minor.yy0, *pGen); }
#line 1130 "parser/epparser.c"
        break;
      case 22: /* expr ::= expr BITAND expr */
#line 140 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "&",  yymsp[0].minor.yy0, *pGen); }
#line 1135 "parser/epparser.c"
        break;
      case 23: /* expr ::= expr BITOR expr */
#line 141 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "|",  yymsp[0].minor.yy0, *pGen); }
#line 1140 "parser/epparser.c"
        break;
      case 24: /* expr ::= expr BITXOR expr */
#line 142 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "^",  yymsp[0].minor.yy0, *pGen); }
#line 1145 "parser/epparser.c"
        break;
      case 25: /* expr ::= PLUS expr */
#line 145 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = +" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1150 "parser/epparser.c"
        break;
      case 26: /* expr ::= MINUS expr */
#line 146 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = -" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1155 "parser/epparser.c"
        break;
      case 27: /* expr ::= BITNOT expr */
#line 147 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = ~" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1160 "parser/epparser.c"
        break;
      case 28: /* lexpr ::= expr EQ expr */
#line 150 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "==", yymsp[0].minor.yy0, *pGen); }
#line 1165 "parser/epparser.c"
        break;
      case 29: /* lexpr ::= expr NE expr */
#line 151 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "!=", yymsp[0].minor.yy0, *pGen); }
#line 1170 "parser/epparser.c"
        break;
      case 30: /* lexpr ::= expr LE expr */
#line 152 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<=", yymsp[0].minor.yy0, *pGen); }
#line 1175 "parser/epparser.c"
        break;
      case 31: /* lexpr ::= expr LT expr */
#line 153 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<",  yymsp[0].minor.yy0, *pGen); }
#line 1180 "parser/epparser.c"
        break;
      case 32: /* lexpr ::= expr GE expr */
#line 154 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">=", yymsp[0].minor.yy0, *pGen); }
#line 1185 "parser/epparser.c"
        break;
      case 33: /* lexpr ::= expr GT expr */
#line 155 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">" , yymsp[0].minor.yy0, *pGen); }
#line 1190 "parser/epparser.c"
        break;
      case 34: /* lexpr ::= lexpr LAND lexpr */
#line 157 "parser/epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "[" + yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data + "]";
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0, *pGen);
}
#line 1199 "parser/epparser.c"
        break;
      case 35: /* lexpr ::= lexpr LOR lexpr */
#line 163 "parser/epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "EUDOr([" + yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data + "])";
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0, *pGen);
}
#line 1208 "parser/epparser.c"
        break;
      case 36: /* lexpr ::= LNOT lexpr */
#line 169 "parser/epparser.lemon"
{
    yymsp[0].minor.yy0->data = "EUDNot([" + yymsp[0].minor.yy0->data + "])";
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0, *pGen);
}
#line 1216 "parser/epparser.c"
        break;
      case 38: /* vdef_stmt ::= VAR NAME SEMICOLON */
#line 178 "parser/epparser.lemon"
{
    (*pGen) << yymsp[-1].minor.yy0->data << " = EUDVariable()" << std::endl;
    pGen->namedef(yymsp[-1].minor.yy0->data);
    delete yymsp[-1].minor.yy0;
}
#line 1225 "parser/epparser.c"
        break;
      case 39: /* vdefAssign_stmt ::= VAR NAME ASSIGN expr SEMICOLON */
#line 184 "parser/epparser.lemon"
{
    (*pGen) << yymsp[-3].minor.yy0->data << " = _MVAR([" << yymsp[-1].minor.yy0->data << "])" << std::endl;
    if(!pGen->namedef(yymsp[-3].minor.yy0->data)) {
        throw_error(yymsp[-3].minor.yy0->line, 196, ("Redeclaration of variable \'" + (yymsp[-3].minor.yy0->data) + "\'"));
    }
    delete yymsp[-3].minor.yy0;
}
#line 1236 "parser/epparser.c"
        break;
      case 40: /* vdefMulti_stmt ::= VAR nameList SEMICOLON */
#line 192 "parser/epparser.lemon"
{
    std::string& s = yymsp[-1].minor.yy0->data;
    int varCount = std::count(s.begin(), s.end(), ',') + 1;
    (*pGen) << s << " = EUDCreateVariables(" << varCount << ")" << std::endl;

    // Register variables.
    commaListIter(s, [&](const std::string& varname) {
        if(!pGen->namedef(varname)) {
            throw_error(yymsp[-1].minor.yy0->line, 196, ("Redeclaration of variable \'" + varname + "\'"));
        }
    });
    delete yymsp[-1].minor.yy0;
}
#line 1253 "parser/epparser.c"
        break;
      case 41: /* vdefMultiAssign_stmt ::= VAR nameList ASSIGN exprList SEMICOLON */
#line 206 "parser/epparser.lemon"
{
    std::string& s = yymsp[-3].minor.yy0->data;
    (*pGen) << s << " = _MVAR([" << yymsp[-1].minor.yy0->data << "])" << std::endl;

    // Register variables.
    commaListIter(s, [&](const std::string& varname) {
        if(!pGen->namedef(varname)) {
            throw_error(yymsp[-3].minor.yy0->line, 196, ("Redeclaration of variable \'" + varname + "\'"));
        }
    });

    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1270 "parser/epparser.c"
        break;
      case 42: /* assign_stmt ::= NAME ASSIGN expr SEMICOLON */
#line 220 "parser/epparser.lemon"
{
    (*pGen) << yymsp[-3].minor.yy0->data << " << " << yymsp[-1].minor.yy0->data << std::endl;
    if(pGen->undefined(yymsp[-3].minor.yy0->data)) {
        throw_error(yymsp[-3].minor.yy0->line, 103, ("Undeclared variable \'" + (yymsp[-3].minor.yy0->data) + "\'"));
        pGen->namedef(yymsp[-3].minor.yy0->data);
    }
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1282 "parser/epparser.c"
        break;
      case 43: /* assignMulti_stmt ::= nameList ASSIGN exprList SEMICOLON */
#line 229 "parser/epparser.lemon"
{
    (*pGen) << "SetVariables([" << yymsp[-3].minor.yy0->data << "], [" << yymsp[-1].minor.yy0->data << "])" << std::endl;

    commaListIter(yymsp[-3].minor.yy0->data, [&](const std::string& varname) {
        if(pGen->undefined(varname)) {
            throw_error(yymsp[-3].minor.yy0->line, 103, ("Undeclared variable \'" + varname + "\'"));
            pGen->namedef(varname);
        }
    });

    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1298 "parser/epparser.c"
        break;
      case 47: /* block ::= LBRACKET error RBRACKET */
#line 246 "parser/epparser.lemon"
{
    throw_error(yymsp[0].minor.yy0->line, 6298, "Block not terminated properly.");
}
#line 1305 "parser/epparser.c"
        break;
      case 48: /* if_start ::= IF */
#line 252 "parser/epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    (*pGen) << yygotominor.yy0->data << " = EUDIf()" << std::endl;
}
#line 1313 "parser/epparser.c"
        break;
      case 49: /* if_header ::= if_start LPAREN lexpr RPAREN */
      case 54: /* while_header ::= while_start LPAREN lexpr RPAREN */ yytestcase(yyruleno==54);
#line 256 "parser/epparser.lemon"
{
    (*pGen) << "if " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data << "):" << std::endl;
    pGen->indent();
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1323 "parser/epparser.c"
        break;
      case 50: /* if_stmt ::= if_header stmt */
      case 52: /* if_stmt ::= else_header stmt */ yytestcase(yyruleno==52);
      case 55: /* while_stmt ::= while_header stmt */ yytestcase(yyruleno==55);
#line 262 "parser/epparser.lemon"
{
    pGen->unindent();
    (*pGen) << "EUDEndIf()" << std::endl;
}
#line 1333 "parser/epparser.c"
        break;
      case 51: /* else_header ::= if_header stmt ELSE */
#line 267 "parser/epparser.lemon"
{
    pGen->unindent();
    (*pGen) << "if EUDElse():" << std::endl;
    pGen->indent();
}
#line 1342 "parser/epparser.c"
        break;
      case 53: /* while_start ::= WHILE */
#line 280 "parser/epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    (*pGen) << yygotominor.yy0->data << " = EUDWhile()" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1351 "parser/epparser.c"
        break;
      case 56: /* foreach_header ::= FOR LPAREN nameList COLON exprList RPAREN */
#line 298 "parser/epparser.lemon"
{
    (*pGen) << "for " << yymsp[-3].minor.yy0->data << " in " << yymsp[-1].minor.yy0->data << ":" << std::endl;
    pGen->indent();
}
#line 1359 "parser/epparser.c"
        break;
      case 57: /* foreach_stmt ::= foreach_header stmt */
      case 63: /* fdef_chunk ::= function_header stmt */ yytestcase(yyruleno==63);
#line 303 "parser/epparser.lemon"
{
    pGen->unindent();
}
#line 1367 "parser/epparser.c"
        break;
      case 58: /* continue_stmt ::= CONTINUE SEMICOLON */
#line 309 "parser/epparser.lemon"
{
    (*pGen) << "EUDContinue()" << std::endl;
}
#line 1374 "parser/epparser.c"
        break;
      case 59: /* break_stmt ::= BREAK SEMICOLON */
#line 313 "parser/epparser.lemon"
{
    (*pGen) << "EUDBreak()" << std::endl;
}
#line 1381 "parser/epparser.c"
        break;
      case 60: /* function_start ::= FUNCTION NAME */
#line 318 "parser/epparser.lemon"
{
    // Preprocess yymsp[0].minor.yy0
    if(yymsp[0].minor.yy0->data[0] == '_' || ('A' <= yymsp[0].minor.yy0->data[0] && yymsp[0].minor.yy0->data[0] <= 'Z'));  // Name starts with uppercase -> Don't modify
    else {
        yymsp[0].minor.yy0->data = "f_" + yymsp[0].minor.yy0->data;
    }

    yygotominor.yy0 = yymsp[0].minor.yy0;
    if(!pGen->namedef(yymsp[0].minor.yy0->data)) {
        throw_error(yymsp[0].minor.yy0->line, 4495, "Duplicate function yymsp[0].minor.yy0 " + yymsp[0].minor.yy0->data);
    }
}
#line 1397 "parser/epparser.c"
        break;
      case 61: /* function_header ::= function_start LPAREN nameList RPAREN */
#line 331 "parser/epparser.lemon"
{
    (*pGen) << "@EUDFunc" << std::endl;
    (*pGen) << "def " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data << "):" << std::endl;
    pGen->indent();

    // Register variables.
    const std::string& s = yymsp[-1].minor.yy0->data;
    commaListIter(yymsp[-1].minor.yy0->data, [&](const std::string& varname) {
        if(!pGen->namedef(varname)) {
            throw_error(yymsp[-1].minor.yy0->line, 196, ("Redeclaration of variable \'" + varname + "\'"));
        }
    });

    tmpIndex = 1;
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1417 "parser/epparser.c"
        break;
      case 62: /* function_header ::= function_start LPAREN RPAREN */
#line 348 "parser/epparser.lemon"
{
    (*pGen) << "@EUDFunc" << std::endl;
    (*pGen) << "def " << yymsp[-2].minor.yy0->data << "():" << std::endl;
    pGen->indent();
    tmpIndex = 1;
    delete yymsp[-2].minor.yy0;
}
#line 1428 "parser/epparser.c"
        break;
      case 64: /* return_stmt ::= RETURN SEMICOLON */
#line 362 "parser/epparser.lemon"
{
    (*pGen) << "EUDReturn()" << std::endl;
}
#line 1435 "parser/epparser.c"
        break;
      case 65: /* return_stmt ::= RETURN exprList SEMICOLON */
#line 365 "parser/epparser.lemon"
{
    (*pGen) << "EUDReturn(" << yymsp[-1].minor.yy0->data << ")" << std::endl;
    delete yymsp[-1].minor.yy0;
}
#line 1443 "parser/epparser.c"
        break;
      case 66: /* action ::= ACTIONNAME LPAREN exprList RPAREN SEMICOLON */
#line 373 "parser/epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[-4].minor.yy0);
    yygotominor.yy0->data =  yymsp[-4].minor.yy0->data + "(" + yymsp[-2].minor.yy0->data + ")";
    delete yymsp[-4].minor.yy0; delete yymsp[-2].minor.yy0;
}
#line 1452 "parser/epparser.c"
        break;
      case 67: /* actions ::= action action */
      case 68: /* actions ::= actions action */ yytestcase(yyruleno==68);
#line 379 "parser/epparser.lemon"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
    yymsp[-1].minor.yy0->data += ",\n" + yymsp[0].minor.yy0->data;
    delete yymsp[0].minor.yy0;
}
#line 1462 "parser/epparser.c"
        break;
      case 69: /* actionStmt ::= action */
#line 391 "parser/epparser.lemon"
{
    (*pGen) << "DoEvents(" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1470 "parser/epparser.c"
        break;
      case 70: /* actionStmt ::= actions */
#line 396 "parser/epparser.lemon"
{
    (*pGen) << "DoEvents([" << std::endl;
    pGen->indent();
    (*pGen) << yymsp[0].minor.yy0->data << std::endl;
    pGen->unindent(false);
    (*pGen) << "])" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1482 "parser/epparser.c"
        break;
      case 71: /* stmt ::= error SEMICOLON */
#line 407 "parser/epparser.lemon"
{ throw_error(yymsp[0].minor.yy0->line, 6974, "Error while parsing statement"); }
#line 1487 "parser/epparser.c"
        break;
      case 79: /* stmt ::= expr SEMICOLON */
#line 417 "parser/epparser.lemon"
{ (*pGen) << yymsp[-1].minor.yy0->data << std::endl; }
#line 1492 "parser/epparser.c"
        break;
      default:
      /* (0) program ::= chunks */ yytestcase(yyruleno==0);
      /* (44) stmtList ::= stmt */ yytestcase(yyruleno==44);
      /* (45) stmtList ::= stmtList stmt */ yytestcase(yyruleno==45);
      /* (46) block ::= LBRACKET stmtList RBRACKET */ yytestcase(yyruleno==46);
      /* (72) stmt ::= SEMICOLON */ yytestcase(yyruleno==72);
      /* (73) stmt ::= vdef_stmt */ yytestcase(yyruleno==73);
      /* (74) stmt ::= vdefAssign_stmt */ yytestcase(yyruleno==74);
      /* (75) stmt ::= vdefMultiAssign_stmt */ yytestcase(yyruleno==75);
      /* (76) stmt ::= vdefMulti_stmt */ yytestcase(yyruleno==76);
      /* (77) stmt ::= assign_stmt */ yytestcase(yyruleno==77);
      /* (78) stmt ::= assignMulti_stmt */ yytestcase(yyruleno==78);
      /* (80) stmt ::= actionStmt */ yytestcase(yyruleno==80);
      /* (81) stmt ::= if_stmt */ yytestcase(yyruleno==81);
      /* (82) stmt ::= while_stmt */ yytestcase(yyruleno==82);
      /* (83) stmt ::= foreach_stmt */ yytestcase(yyruleno==83);
      /* (84) stmt ::= continue_stmt */ yytestcase(yyruleno==84);
      /* (85) stmt ::= break_stmt */ yytestcase(yyruleno==85);
      /* (86) stmt ::= return_stmt */ yytestcase(yyruleno==86);
      /* (87) stmt ::= block */ yytestcase(yyruleno==87);
      /* (88) chunk ::= fdef_chunk */ yytestcase(yyruleno==88);
      /* (89) chunk ::= vdef_stmt */ yytestcase(yyruleno==89);
      /* (90) chunk ::= vdefMulti_stmt */ yytestcase(yyruleno==90);
      /* (91) chunks ::= */ yytestcase(yyruleno==91);
      /* (92) chunks ::= chunks chunk */ yytestcase(yyruleno==92);
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
#line 20 "parser/epparser.lemon"

    throw_error(-1, 629, "Unrecoverable error");
#line 1567 "parser/epparser.c"
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
#line 15 "parser/epparser.lemon"

    errorOccured = true;
    throw_error(currentTokenizingLine, 629, "General syntax error");
#line 1586 "parser/epparser.c"
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
#line 435 "parser/epparser.lemon"


// #define PARSER_DEBUG

std::string ParseString(const std::string& code)
{
    std::istringstream is(code);
    Tokenizer tok(is);
    void* pParser = ParseAlloc (malloc);
    PyGenerator pGen;
    Token* token;
    currentTokenizingLine = 0;

#ifdef PARSER_DEBUG
    std::cout << "Parsing string [[[\n" << code << "\n]]]\n";
#endif

    tmpIndex = 1;
    errorOccured = false;
    while ((token = tok.getToken()) != nullptr) {
        if (currentTokenizingLine != tok.getCurrentLine()) {
            currentTokenizingLine = tok.getCurrentLine();
            pGen << "# (Line " << currentTokenizingLine << ") " << trim(tok.getCurrentLineString()) << std::endl;
#ifdef PARSER_DEBUG
            printf("reading line %s\n", tok.getCurrentLineString().c_str());
#endif
        }
        if (tokenTypeConv(token)) {
            Parse (pParser, token->type, token, &pGen);
#ifdef PARSER_DEBUG
            ParseTrace(stdout, "-- ");
#endif
        }
        else {
            throw_error(token->line, 8104, "Invalid token");
        }
    }
    Parse (pParser, 0, nullptr, &pGen);
    ParseFree(pParser, free );

    if(!errorOccured) return pGen.str();
    // else throw std::runtime_error("Invalid syntax");
    return pGen.str();
}
#line 1822 "parser/epparser.c"
