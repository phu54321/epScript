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
#define YYNOCODE 84
#define YYACTIONTYPE unsigned short int
#define ParseTOKENTYPE Token*
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  int yy167;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL  PyGenerator* pGen ;
#define ParseARG_PDECL , PyGenerator* pGen 
#define ParseARG_FETCH  PyGenerator* pGen  = yypParser->pGen 
#define ParseARG_STORE yypParser->pGen  = pGen 
#define YYNSTATE 182
#define YYNRULE 89
#define YYERRORSYMBOL 47
#define YYERRSYMDT yy167
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
#define YY_ACTTAB_COUNT (519)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */    74,   39,   40,   38,  113,   81,  112,  102,   51,   44,
 /*    10 */   133,  132,  130,  131,  129,  128,    2,  155,  120,   97,
 /*    20 */     6,  126,    5,   94,    4,  125,    3,  124,  123,  122,
 /*    30 */    88,  113,  112,  121,  127,   81,  180,  102,   51,  106,
 /*    40 */   133,  132,  130,  131,  129,  128,   18,  118,  120,   97,
 /*    50 */     6,  126,    5,   94,    4,  125,    3,  124,  123,  122,
 /*    60 */    88,  176,   29,  121,  127,   81,  105,  102,   51,  104,
 /*    70 */   133,  132,  130,  131,  129,  128,  181,   95,  120,   97,
 /*    80 */     6,  126,    5,   94,    4,  125,    3,  124,  123,  122,
 /*    90 */    88,  162,  179,  121,  127,   81,  103,  102,   51,  107,
 /*   100 */   133,  132,  130,  131,  129,  128,  177,  146,  120,   97,
 /*   110 */     6,  126,    5,   94,    4,  125,    3,  124,  123,  122,
 /*   120 */    88,  112,   20,  121,  127,   81,   47,  102,   51,  174,
 /*   130 */   133,  132,  130,  131,  129,  128,  173,  143,  120,   97,
 /*   140 */     6,  126,    5,   94,    4,  125,    3,  124,  123,  122,
 /*   150 */    88,  172,   29,  121,  127,   81,  171,  102,   51,  101,
 /*   160 */   133,  132,  130,  131,  129,  128,  100,  141,  120,   97,
 /*   170 */     6,  126,    5,   94,    4,  125,    3,  124,  123,  122,
 /*   180 */    88,  142,   99,  121,  127,   81,   29,  102,   51,  105,
 /*   190 */   133,  132,  130,  131,  129,  128,   16,  154,  120,   97,
 /*   200 */     6,  126,    5,   94,    4,  125,    3,  124,  123,  122,
 /*   210 */    32,   31,   15,  121,  127,   89,   30,  170,   73,   14,
 /*   220 */   135,   42,  119,  112,   46,  134,    1,  153,  152,  113,
 /*   230 */    27,  145,   93,  147,   92,   91,   29,    9,   90,   26,
 /*   240 */    24,   23,   22,   21,   25,   34,   33,   35,   37,   36,
 /*   250 */    43,   41,   39,   40,   38,  178,   32,   31,   80,  108,
 /*   260 */    61,  180,   30,  170,   73,  109,   10,   42,  159,  175,
 /*   270 */    46,  134,    1,   45,  152,  102,   71,  145,   93,  140,
 /*   280 */    92,   91,  139,    9,   90,   34,   33,   35,   37,   36,
 /*   290 */    43,   41,   39,   40,   38,   37,   36,   43,   41,   39,
 /*   300 */    40,   38,  169,   34,   33,   35,   37,   36,   43,   41,
 /*   310 */    39,   40,   38,   17,  116,  136,  115,   43,   41,   39,
 /*   320 */    40,   38,  135,  160,   34,   33,   35,   37,   36,   43,
 /*   330 */    41,   39,   40,   38,  110,    7,  117,   13,   14,  114,
 /*   340 */    79,  108,   61,   86,  158,   34,   33,   35,   37,   36,
 /*   350 */    43,   41,   39,   40,   38,   77,  108,   61,   75,  108,
 /*   360 */    61,   82,  108,   61,  148,  157,   34,   33,   35,   37,
 /*   370 */    36,   43,   41,   39,   40,   38,  113,   28,  102,   53,
 /*   380 */    33,   35,   37,   36,   43,   41,   39,   40,   38,   35,
 /*   390 */    37,   36,   43,   41,   39,   40,   38,   13,   14,   32,
 /*   400 */    31,   12,   83,   29,   16,   30,  170,   98,  102,   72,
 /*   410 */    42,  161,  182,   11,   32,   31,  112,   19,  102,  168,
 /*   420 */    30,  170,   98,   87,  144,   42,   32,   31,   29,   76,
 /*   430 */   108,   61,   30,  170,   98,  156,   69,   42,   84,   32,
 /*   440 */    31,  102,   49,   68,   48,   30,  170,   98,  178,   70,
 /*   450 */    42,   32,   31,   78,  137,  109,  111,   30,  170,   98,
 /*   460 */   138,  273,   42,  102,  167,  102,   49,  151,  102,   49,
 /*   470 */    96,  102,   49,  150,  102,  166,  102,   49,  149,  102,
 /*   480 */    49,   67,  102,   66,  102,   65,  102,   64,  102,   62,
 /*   490 */   102,   63,  102,  165,  102,  164,  102,  163,  102,   60,
 /*   500 */   102,   52,  102,   50,   85,  102,   59,  102,   58,  102,
 /*   510 */    57,  102,   56,  102,   55,  102,   54,  272,    8,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    47,   20,   21,   22,    1,   52,    1,   54,   55,   29,
 /*    10 */    57,   58,   59,   60,   61,   62,   63,   64,   65,   66,
 /*    20 */    67,   68,   69,   70,   71,   72,   73,   74,   75,   76,
 /*    30 */    47,    1,    1,   80,   81,   52,   33,   54,   55,    1,
 /*    40 */    57,   58,   59,   60,   61,   62,   41,   64,   65,   66,
 /*    50 */    67,   68,   69,   70,   71,   72,   73,   74,   75,   76,
 /*    60 */    47,   30,    1,   80,   81,   52,   28,   54,   55,    1,
 /*    70 */    57,   58,   59,   60,   61,   62,   26,   64,   65,   66,
 /*    80 */    67,   68,   69,   70,   71,   72,   73,   74,   75,   76,
 /*    90 */    47,   30,   26,   80,   81,   52,   28,   54,   55,   27,
 /*   100 */    57,   58,   59,   60,   61,   62,   26,   64,   65,   66,
 /*   110 */    67,   68,   69,   70,   71,   72,   73,   74,   75,   76,
 /*   120 */    47,    1,    2,   80,   81,   52,   27,   54,   55,   25,
 /*   130 */    57,   58,   59,   60,   61,   62,   28,   64,   65,   66,
 /*   140 */    67,   68,   69,   70,   71,   72,   73,   74,   75,   76,
 /*   150 */    47,   25,    1,   80,   81,   52,   28,   54,   55,   27,
 /*   160 */    57,   58,   59,   60,   61,   62,   27,   64,   65,   66,
 /*   170 */    67,   68,   69,   70,   71,   72,   73,   74,   75,   76,
 /*   180 */    47,   30,   25,   80,   81,   52,    1,   54,   55,   28,
 /*   190 */    57,   58,   59,   60,   61,   62,   29,   64,   65,   66,
 /*   200 */    67,   68,   69,   70,   71,   72,   73,   74,   75,   76,
 /*   210 */    18,   19,   29,   80,   81,   30,   24,   25,   26,    4,
 /*   220 */    33,   29,   35,    1,   32,   33,   34,   35,   36,    1,
 /*   230 */     2,   39,   40,   38,   42,   43,    1,   45,   46,    7,
 /*   240 */     8,    9,   10,   11,   12,   13,   14,   15,   16,   17,
 /*   250 */    18,   19,   20,   21,   22,   33,   18,   19,   53,   54,
 /*   260 */    55,   33,   24,   25,   26,   26,   29,   29,   33,   30,
 /*   270 */    32,   33,   34,   29,   36,   54,   55,   39,   40,   33,
 /*   280 */    42,   43,   33,   45,   46,   13,   14,   15,   16,   17,
 /*   290 */    18,   19,   20,   21,   22,   16,   17,   18,   19,   20,
 /*   300 */    21,   22,   30,   13,   14,   15,   16,   17,   18,   19,
 /*   310 */    20,   21,   22,   29,   57,   33,   59,   18,   19,   20,
 /*   320 */    21,   22,   33,   33,   13,   14,   15,   16,   17,   18,
 /*   330 */    19,   20,   21,   22,   77,   78,   79,    3,    4,   82,
 /*   340 */    53,   54,   55,   52,   33,   13,   14,   15,   16,   17,
 /*   350 */    18,   19,   20,   21,   22,   53,   54,   55,   53,   54,
 /*   360 */    55,   53,   54,   55,   30,   33,   13,   14,   15,   16,
 /*   370 */    17,   18,   19,   20,   21,   22,    1,    2,   54,   55,
 /*   380 */    14,   15,   16,   17,   18,   19,   20,   21,   22,   15,
 /*   390 */    16,   17,   18,   19,   20,   21,   22,    3,    4,   18,
 /*   400 */    19,    5,   51,    1,   29,   24,   25,   26,   54,   55,
 /*   410 */    29,   30,    0,    5,   18,   19,    1,    2,   54,   55,
 /*   420 */    24,   25,   26,   26,   30,   29,   18,   19,    1,   53,
 /*   430 */    54,   55,   24,   25,   26,   33,   52,   29,   25,   18,
 /*   440 */    19,   54,   55,   56,   32,   24,   25,   26,   33,   26,
 /*   450 */    29,   18,   19,   52,   33,   26,   44,   24,   25,   26,
 /*   460 */    33,   83,   29,   54,   55,   54,   55,   56,   54,   55,
 /*   470 */    56,   54,   55,   56,   54,   55,   54,   55,   56,   54,
 /*   480 */    55,   56,   54,   55,   54,   55,   54,   55,   54,   55,
 /*   490 */    54,   55,   54,   55,   54,   55,   54,   55,   54,   55,
 /*   500 */    54,   55,   54,   55,   52,   54,   55,   54,   55,   54,
 /*   510 */    55,   54,   55,   54,   55,   54,   55,   49,   50,
};
#define YY_SHIFT_USE_DFLT (-21)
#define YY_SHIFT_COUNT (113)
#define YY_SHIFT_MIN   (-20)
#define YY_SHIFT_MAX   (433)
static const short yy_shift_ofst[] = {
 /*     0 */   -21,  238,  192,  238,  238,  238,  238,  238,  412,  421,
 /*    10 */   396,  408,  408,  396,  396,  396,  381,  433,  433,  433,
 /*    20 */   433,  433,  433,  433,  433,  433,  433,  433,  433,  433,
 /*    30 */   433,  433,  433,  433,  433,  433,  433,  433,  433,  433,
 /*    40 */   433,  433,  433,  433,  239,  429,  423,  413,  397,  232,
 /*    50 */   332,  311,  290,  272,  353,  353,  353,  353,  353,  353,
 /*    60 */   353,  353,  366,  374,  279,  299,  299,  394,  334,  415,
 /*    70 */   228,  -19,  -19,  375,  187,  185,  427,  151,    5,  402,
 /*    80 */   235,  120,   61,   68,   38,   31,  222,    3,  289,  282,
 /*    90 */   284,  249,  246,  244,  237,  195,  215,  183,  167,  161,
 /*   100 */   157,  139,  132,  128,  126,  108,  104,   99,   72,   30,
 /*   110 */   -20,   80,   66,   50,
};
#define YY_REDUCE_USE_DFLT (-48)
#define YY_REDUCE_COUNT (48)
#define YY_REDUCE_MIN   (-47)
#define YY_REDUCE_MAX   (468)
static const short yy_reduce_ofst[] = {
 /*     0 */   468,  -47,  133,  103,   73,   43,   13,  -17,  257,  376,
 /*    10 */   425,  422,  417,  414,  411,  387,  308,  305,  302,  287,
 /*    20 */   205,  461,  459,  457,  455,  453,  451,  448,  446,  444,
 /*    30 */   442,  440,  438,  436,  434,  432,  430,  428,  420,  409,
 /*    40 */   364,  354,  324,  221,  452,  401,  384,  351,  291,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   269,  271,  271,  271,  271,  271,  271,  271,  271,  271,
 /*    10 */   271,  271,  271,  271,  271,  271,  271,  271,  271,  271,
 /*    20 */   271,  271,  271,  271,  271,  271,  271,  271,  271,  271,
 /*    30 */   271,  271,  271,  271,  271,  271,  271,  271,  271,  271,
 /*    40 */   271,  271,  271,  271,  271,  271,  271,  271,  271,  271,
 /*    50 */   271,  271,  271,  271,  215,  214,  213,  212,  211,  210,
 /*    60 */   190,  189,  205,  206,  204,  203,  202,  271,  271,  271,
 /*    70 */   271,  197,  198,  192,  271,  271,  271,  271,  271,  271,
 /*    80 */   271,  271,  271,  271,  271,  271,  271,  271,  271,  271,
 /*    90 */   271,  271,  271,  271,  271,  232,  217,  271,  192,  271,
 /*   100 */   271,  271,  195,  271,  271,  271,  271,  271,  195,  271,
 /*   110 */   271,  271,  271,  271,  270,  268,  267,  266,  245,  229,
 /*   120 */   265,  264,  263,  262,  261,  260,  259,  258,  256,  255,
 /*   130 */   254,  253,  252,  251,  250,  249,  248,  246,  247,  241,
 /*   140 */   240,  239,  238,  237,  236,  235,  234,  233,  231,  219,
 /*   150 */   218,  216,  230,  228,  227,  226,  223,  221,  257,  225,
 /*   160 */   224,  194,  193,  209,  208,  207,  201,  200,  199,  196,
 /*   170 */   191,  187,  184,  188,  183,  244,  243,  242,  222,  186,
 /*   180 */   220,  185,
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
  "return_stmt",   "actionStmt",    "chunk",       
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
 /*  66 */ "actionStmt ::= ACTIONNAME LPAREN exprList RPAREN SEMICOLON",
 /*  67 */ "stmt ::= error SEMICOLON",
 /*  68 */ "stmt ::= SEMICOLON",
 /*  69 */ "stmt ::= vdef_stmt",
 /*  70 */ "stmt ::= vdefAssign_stmt",
 /*  71 */ "stmt ::= vdefMultiAssign_stmt",
 /*  72 */ "stmt ::= vdefMulti_stmt",
 /*  73 */ "stmt ::= assign_stmt",
 /*  74 */ "stmt ::= assignMulti_stmt",
 /*  75 */ "stmt ::= expr SEMICOLON",
 /*  76 */ "stmt ::= actionStmt",
 /*  77 */ "stmt ::= if_stmt",
 /*  78 */ "stmt ::= while_stmt",
 /*  79 */ "stmt ::= foreach_stmt",
 /*  80 */ "stmt ::= continue_stmt",
 /*  81 */ "stmt ::= break_stmt",
 /*  82 */ "stmt ::= return_stmt",
 /*  83 */ "stmt ::= block",
 /*  84 */ "chunk ::= fdef_chunk",
 /*  85 */ "chunk ::= vdef_stmt",
 /*  86 */ "chunk ::= vdefMulti_stmt",
 /*  87 */ "chunks ::=",
 /*  88 */ "chunks ::= chunks chunk",
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
#line 608 "parser/epparser.c"
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
  { 82, 1 },
  { 82, 1 },
  { 82, 1 },
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
#line 55 "parser/epparser.lemon"
{
    yygotominor.yy0 = new Token(yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data, yymsp[0].minor.yy0);
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 996 "parser/epparser.c"
        break;
      case 3: /* nameList ::= NAME COMMA NAME */
      case 4: /* nameList ::= nameList COMMA NAME */ yytestcase(yyruleno==4);
      case 8: /* exprList ::= exprList COMMA expr */ yytestcase(yyruleno==8);
#line 63 "parser/epparser.lemon"
{ yygotominor.yy0 = new Token((yymsp[-2].minor.yy0->data) + ", " + (yymsp[0].minor.yy0->data), yymsp[0].minor.yy0); delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1003 "parser/epparser.c"
        break;
      case 5: /* exprList ::= funcexpr LSQBRACKET LSQBRACKET numList RSQBRACKET RSQBRACKET */
      case 6: /* expr ::= funcexpr LSQBRACKET LSQBRACKET NUMBER RSQBRACKET RSQBRACKET */ yytestcase(yyruleno==6);
#line 65 "parser/epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[-2].minor.yy0);
    (*pGen) << yygotominor.yy0->data << " = _SRET(" << yymsp[-5].minor.yy0->data << ", [" << yymsp[-2].minor.yy0->data << "])" << std::endl;
    delete yymsp[-5].minor.yy0; delete yymsp[-2].minor.yy0;
}
#line 1013 "parser/epparser.c"
        break;
      case 7: /* exprList ::= expr */
      case 9: /* expr ::= NUMBER */ yytestcase(yyruleno==9);
      case 13: /* expr ::= funcexpr */ yytestcase(yyruleno==13);
      case 37: /* lexpr ::= LNOT LNOT lexpr */ yytestcase(yyruleno==37);
#line 76 "parser/epparser.lemon"
{ yygotominor.yy0 = yymsp[0].minor.yy0; }
#line 1021 "parser/epparser.c"
        break;
      case 10: /* expr ::= NAME */
#line 81 "parser/epparser.lemon"
{
    if(pGen->undefined(yymsp[0].minor.yy0->data)) {
        throw_error(yymsp[0].minor.yy0->line, 103, ("Undeclared variable \'" + (yymsp[0].minor.yy0->data) + "\'"));
        pGen->namedef(yymsp[0].minor.yy0->data);
    }
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1032 "parser/epparser.c"
        break;
      case 11: /* funcexpr ::= NAME LPAREN exprList RPAREN */
#line 90 "parser/epparser.lemon"
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
#line 1052 "parser/epparser.c"
        break;
      case 12: /* funcexpr ::= NAME LPAREN RPAREN */
#line 108 "parser/epparser.lemon"
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
#line 1073 "parser/epparser.c"
        break;
      case 14: /* expr ::= LPAREN expr RPAREN */
#line 129 "parser/epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0, *pGen);
}
#line 1081 "parser/epparser.c"
        break;
      case 15: /* expr ::= expr PLUS expr */
#line 134 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "+",  yymsp[0].minor.yy0, *pGen); }
#line 1086 "parser/epparser.c"
        break;
      case 16: /* expr ::= expr MINUS expr */
#line 135 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "-",  yymsp[0].minor.yy0, *pGen); }
#line 1091 "parser/epparser.c"
        break;
      case 17: /* expr ::= expr MULTIPLY expr */
#line 136 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "*",  yymsp[0].minor.yy0, *pGen); }
#line 1096 "parser/epparser.c"
        break;
      case 18: /* expr ::= expr DIVIDE expr */
#line 137 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "//", yymsp[0].minor.yy0, *pGen); }
#line 1101 "parser/epparser.c"
        break;
      case 19: /* expr ::= expr MOD expr */
#line 138 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "%",  yymsp[0].minor.yy0, *pGen); }
#line 1106 "parser/epparser.c"
        break;
      case 20: /* expr ::= expr LSHIFT expr */
#line 139 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<<", yymsp[0].minor.yy0, *pGen); }
#line 1111 "parser/epparser.c"
        break;
      case 21: /* expr ::= expr RSHIFT expr */
#line 140 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">>", yymsp[0].minor.yy0, *pGen); }
#line 1116 "parser/epparser.c"
        break;
      case 22: /* expr ::= expr BITAND expr */
#line 141 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "&",  yymsp[0].minor.yy0, *pGen); }
#line 1121 "parser/epparser.c"
        break;
      case 23: /* expr ::= expr BITOR expr */
#line 142 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "|",  yymsp[0].minor.yy0, *pGen); }
#line 1126 "parser/epparser.c"
        break;
      case 24: /* expr ::= expr BITXOR expr */
#line 143 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "^",  yymsp[0].minor.yy0, *pGen); }
#line 1131 "parser/epparser.c"
        break;
      case 25: /* expr ::= PLUS expr */
#line 146 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = +" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1136 "parser/epparser.c"
        break;
      case 26: /* expr ::= MINUS expr */
#line 147 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = -" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1141 "parser/epparser.c"
        break;
      case 27: /* expr ::= BITNOT expr */
#line 148 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = ~" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1146 "parser/epparser.c"
        break;
      case 28: /* lexpr ::= expr EQ expr */
#line 151 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "==", yymsp[0].minor.yy0, *pGen); }
#line 1151 "parser/epparser.c"
        break;
      case 29: /* lexpr ::= expr NE expr */
#line 152 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "!=", yymsp[0].minor.yy0, *pGen); }
#line 1156 "parser/epparser.c"
        break;
      case 30: /* lexpr ::= expr LE expr */
#line 153 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<=", yymsp[0].minor.yy0, *pGen); }
#line 1161 "parser/epparser.c"
        break;
      case 31: /* lexpr ::= expr LT expr */
#line 154 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<",  yymsp[0].minor.yy0, *pGen); }
#line 1166 "parser/epparser.c"
        break;
      case 32: /* lexpr ::= expr GE expr */
#line 155 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">=", yymsp[0].minor.yy0, *pGen); }
#line 1171 "parser/epparser.c"
        break;
      case 33: /* lexpr ::= expr GT expr */
#line 156 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">" , yymsp[0].minor.yy0, *pGen); }
#line 1176 "parser/epparser.c"
        break;
      case 34: /* lexpr ::= lexpr LAND lexpr */
#line 158 "parser/epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "[" + yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data + "]";
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0, *pGen);
}
#line 1185 "parser/epparser.c"
        break;
      case 35: /* lexpr ::= lexpr LOR lexpr */
#line 164 "parser/epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "EUDOr([" + yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data + "])";
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0, *pGen);
}
#line 1194 "parser/epparser.c"
        break;
      case 36: /* lexpr ::= LNOT lexpr */
#line 170 "parser/epparser.lemon"
{
    yymsp[0].minor.yy0->data = "EUDNot([" + yymsp[0].minor.yy0->data + "])";
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0, *pGen);
}
#line 1202 "parser/epparser.c"
        break;
      case 38: /* vdef_stmt ::= VAR NAME SEMICOLON */
#line 179 "parser/epparser.lemon"
{
    (*pGen) << yymsp[-1].minor.yy0->data << " = EUDVariable()" << std::endl;
    pGen->namedef(yymsp[-1].minor.yy0->data);
    delete yymsp[-1].minor.yy0;
}
#line 1211 "parser/epparser.c"
        break;
      case 39: /* vdefAssign_stmt ::= VAR NAME ASSIGN expr SEMICOLON */
#line 185 "parser/epparser.lemon"
{
    (*pGen) << yymsp[-3].minor.yy0->data << " = _MVAR([" << yymsp[-1].minor.yy0->data << "])" << std::endl;
    if(!pGen->namedef(yymsp[-3].minor.yy0->data)) {
        throw_error(yymsp[-3].minor.yy0->line, 196, ("Redeclaration of variable \'" + (yymsp[-3].minor.yy0->data) + "\'"));
    }
    delete yymsp[-3].minor.yy0;
}
#line 1222 "parser/epparser.c"
        break;
      case 40: /* vdefMulti_stmt ::= VAR nameList SEMICOLON */
#line 193 "parser/epparser.lemon"
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
#line 1239 "parser/epparser.c"
        break;
      case 41: /* vdefMultiAssign_stmt ::= VAR nameList ASSIGN exprList SEMICOLON */
#line 207 "parser/epparser.lemon"
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
#line 1256 "parser/epparser.c"
        break;
      case 42: /* assign_stmt ::= NAME ASSIGN expr SEMICOLON */
#line 221 "parser/epparser.lemon"
{
    (*pGen) << yymsp[-3].minor.yy0->data << " << " << yymsp[-1].minor.yy0->data << std::endl;
    if(pGen->undefined(yymsp[-3].minor.yy0->data)) {
        throw_error(yymsp[-3].minor.yy0->line, 103, ("Undeclared variable \'" + (yymsp[-3].minor.yy0->data) + "\'"));
        pGen->namedef(yymsp[-3].minor.yy0->data);
    }
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1268 "parser/epparser.c"
        break;
      case 43: /* assignMulti_stmt ::= nameList ASSIGN exprList SEMICOLON */
#line 230 "parser/epparser.lemon"
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
#line 1284 "parser/epparser.c"
        break;
      case 47: /* block ::= LBRACKET error RBRACKET */
#line 247 "parser/epparser.lemon"
{
    throw_error(yymsp[0].minor.yy0->line, 6298, "Block not terminated properly.");
}
#line 1291 "parser/epparser.c"
        break;
      case 48: /* if_start ::= IF */
#line 253 "parser/epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    (*pGen) << yygotominor.yy0->data << " = EUDIf()" << std::endl;
}
#line 1299 "parser/epparser.c"
        break;
      case 49: /* if_header ::= if_start LPAREN lexpr RPAREN */
      case 54: /* while_header ::= while_start LPAREN lexpr RPAREN */ yytestcase(yyruleno==54);
#line 257 "parser/epparser.lemon"
{
    (*pGen) << "if " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data << "):" << std::endl;
    pGen->indent();
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1309 "parser/epparser.c"
        break;
      case 50: /* if_stmt ::= if_header stmt */
      case 52: /* if_stmt ::= else_header stmt */ yytestcase(yyruleno==52);
      case 55: /* while_stmt ::= while_header stmt */ yytestcase(yyruleno==55);
#line 263 "parser/epparser.lemon"
{
    pGen->unindent();
    (*pGen) << "EUDEndIf()" << std::endl;
}
#line 1319 "parser/epparser.c"
        break;
      case 51: /* else_header ::= if_header stmt ELSE */
#line 268 "parser/epparser.lemon"
{
    pGen->unindent();
    (*pGen) << "if EUDElse():" << std::endl;
    pGen->indent();
}
#line 1328 "parser/epparser.c"
        break;
      case 53: /* while_start ::= WHILE */
#line 281 "parser/epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    (*pGen) << yygotominor.yy0->data << " = EUDWhile()" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1337 "parser/epparser.c"
        break;
      case 56: /* foreach_header ::= FOR LPAREN nameList COLON exprList RPAREN */
#line 299 "parser/epparser.lemon"
{
    (*pGen) << "for " << yymsp[-3].minor.yy0->data << " in " << yymsp[-1].minor.yy0->data << ":" << std::endl;
    pGen->indent();
}
#line 1345 "parser/epparser.c"
        break;
      case 57: /* foreach_stmt ::= foreach_header stmt */
      case 63: /* fdef_chunk ::= function_header stmt */ yytestcase(yyruleno==63);
#line 304 "parser/epparser.lemon"
{
    pGen->unindent();
}
#line 1353 "parser/epparser.c"
        break;
      case 58: /* continue_stmt ::= CONTINUE SEMICOLON */
#line 310 "parser/epparser.lemon"
{
    (*pGen) << "EUDContinue()" << std::endl;
}
#line 1360 "parser/epparser.c"
        break;
      case 59: /* break_stmt ::= BREAK SEMICOLON */
#line 314 "parser/epparser.lemon"
{
    (*pGen) << "EUDBreak()" << std::endl;
}
#line 1367 "parser/epparser.c"
        break;
      case 60: /* function_start ::= FUNCTION NAME */
#line 319 "parser/epparser.lemon"
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
#line 1383 "parser/epparser.c"
        break;
      case 61: /* function_header ::= function_start LPAREN nameList RPAREN */
#line 332 "parser/epparser.lemon"
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
#line 1403 "parser/epparser.c"
        break;
      case 62: /* function_header ::= function_start LPAREN RPAREN */
#line 349 "parser/epparser.lemon"
{
    (*pGen) << "@EUDFunc" << std::endl;
    (*pGen) << "def " << yymsp[-2].minor.yy0->data << "():" << std::endl;
    pGen->indent();
    tmpIndex = 1;
    delete yymsp[-2].minor.yy0;
}
#line 1414 "parser/epparser.c"
        break;
      case 64: /* return_stmt ::= RETURN SEMICOLON */
#line 363 "parser/epparser.lemon"
{
    (*pGen) << "EUDReturn()" << std::endl;
}
#line 1421 "parser/epparser.c"
        break;
      case 65: /* return_stmt ::= RETURN exprList SEMICOLON */
#line 366 "parser/epparser.lemon"
{
    (*pGen) << "EUDReturn(" << yymsp[-1].minor.yy0->data << ")" << std::endl;
    delete yymsp[-1].minor.yy0;
}
#line 1429 "parser/epparser.c"
        break;
      case 66: /* actionStmt ::= ACTIONNAME LPAREN exprList RPAREN SEMICOLON */
#line 374 "parser/epparser.lemon"
{
    (*pGen) << "DoActions(" << yymsp[-4].minor.yy0->data << "(" << yymsp[-2].minor.yy0->data << "))" << std::endl;
    delete yymsp[-4].minor.yy0; delete yymsp[-2].minor.yy0;
}
#line 1437 "parser/epparser.c"
        break;
      case 67: /* stmt ::= error SEMICOLON */
#line 381 "parser/epparser.lemon"
{ throw_error(yymsp[0].minor.yy0->line, 6974, "Error while parsing statement"); }
#line 1442 "parser/epparser.c"
        break;
      case 75: /* stmt ::= expr SEMICOLON */
#line 391 "parser/epparser.lemon"
{ (*pGen) << yymsp[-1].minor.yy0->data << std::endl; }
#line 1447 "parser/epparser.c"
        break;
      default:
      /* (0) program ::= chunks */ yytestcase(yyruleno==0);
      /* (44) stmtList ::= stmt */ yytestcase(yyruleno==44);
      /* (45) stmtList ::= stmtList stmt */ yytestcase(yyruleno==45);
      /* (46) block ::= LBRACKET stmtList RBRACKET */ yytestcase(yyruleno==46);
      /* (68) stmt ::= SEMICOLON */ yytestcase(yyruleno==68);
      /* (69) stmt ::= vdef_stmt */ yytestcase(yyruleno==69);
      /* (70) stmt ::= vdefAssign_stmt */ yytestcase(yyruleno==70);
      /* (71) stmt ::= vdefMultiAssign_stmt */ yytestcase(yyruleno==71);
      /* (72) stmt ::= vdefMulti_stmt */ yytestcase(yyruleno==72);
      /* (73) stmt ::= assign_stmt */ yytestcase(yyruleno==73);
      /* (74) stmt ::= assignMulti_stmt */ yytestcase(yyruleno==74);
      /* (76) stmt ::= actionStmt */ yytestcase(yyruleno==76);
      /* (77) stmt ::= if_stmt */ yytestcase(yyruleno==77);
      /* (78) stmt ::= while_stmt */ yytestcase(yyruleno==78);
      /* (79) stmt ::= foreach_stmt */ yytestcase(yyruleno==79);
      /* (80) stmt ::= continue_stmt */ yytestcase(yyruleno==80);
      /* (81) stmt ::= break_stmt */ yytestcase(yyruleno==81);
      /* (82) stmt ::= return_stmt */ yytestcase(yyruleno==82);
      /* (83) stmt ::= block */ yytestcase(yyruleno==83);
      /* (84) chunk ::= fdef_chunk */ yytestcase(yyruleno==84);
      /* (85) chunk ::= vdef_stmt */ yytestcase(yyruleno==85);
      /* (86) chunk ::= vdefMulti_stmt */ yytestcase(yyruleno==86);
      /* (87) chunks ::= */ yytestcase(yyruleno==87);
      /* (88) chunks ::= chunks chunk */ yytestcase(yyruleno==88);
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
#line 1522 "parser/epparser.c"
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
#line 1541 "parser/epparser.c"
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
#line 409 "parser/epparser.lemon"


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
#line 1777 "parser/epparser.c"
