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
#define YYNOCODE 93
#define YYACTIONTYPE unsigned short int
#define ParseTOKENTYPE Token*
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  int yy185;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL  PyGenerator* pGen ;
#define ParseARG_PDECL , PyGenerator* pGen 
#define ParseARG_FETCH  PyGenerator* pGen  = yypParser->pGen 
#define ParseARG_STORE yypParser->pGen  = pGen 
#define YYNSTATE 211
#define YYNRULE 102
#define YYERRORSYMBOL 53
#define YYERRSYMDT yy185
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
#define YY_ACTTAB_COUNT (575)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */    78,  132,  132,   30,  125,   86,  155,   93,  138,  210,
 /*    10 */   153,  152,  150,  151,  149,  148,    2,  181,  139,  104,
 /*    20 */     6,  145,    5,  100,    4,  144,    3,  143,  142,  141,
 /*    30 */    19,  124,  208,  140,   94,   48,   47,  146,  209,   86,
 /*    40 */   131,   93,  206,  131,  153,  152,  150,  151,  149,  148,
 /*    50 */    46,  137,  139,  104,    6,  145,    5,  100,    4,  144,
 /*    60 */     3,  143,  142,  141,  121,   53,   72,  140,   94,   48,
 /*    70 */    47,  146,  205,   86,  132,   93,  203,  207,  153,  152,
 /*    80 */   150,  151,  149,  148,  126,  101,  139,  104,    6,  145,
 /*    90 */     5,  100,    4,  144,    3,  143,  142,  141,  121,   53,
 /*   100 */   177,  140,   94,   48,   47,  146,  128,   86,   51,   93,
 /*   110 */   204,   31,  153,  152,  150,  151,  149,  148,  202,  168,
 /*   120 */   139,  104,    6,  145,    5,  100,    4,  144,    3,  143,
 /*   130 */   142,  141,  121,   53,  103,  140,   94,   48,   47,  146,
 /*   140 */   187,   86,   31,   93,  201,   18,  153,  152,  150,  151,
 /*   150 */   149,  148,  200,  165,  139,  104,    6,  145,    5,  100,
 /*   160 */     4,  144,    3,  143,  142,  141,  121,   53,  176,  140,
 /*   170 */    94,   48,   47,  146,  172,   86,  120,   93,  118,  184,
 /*   180 */   153,  152,  150,  151,  149,  148,  123,  163,  139,  104,
 /*   190 */     6,  145,    5,  100,    4,  144,    3,  143,  142,  141,
 /*   200 */   119,  132,   29,  140,   94,   48,   47,  146,  124,   86,
 /*   210 */    19,   93,  115,  122,  153,  152,  150,  151,  149,  148,
 /*   220 */   114,  180,  139,  104,    6,  145,    5,  100,    4,  144,
 /*   230 */     3,  143,  142,  141,  197,  131,   21,  140,  209,   48,
 /*   240 */    47,  146,   41,   42,   40,   28,   26,   25,   24,   23,
 /*   250 */    27,   36,   35,   37,   39,   38,   45,   43,   41,   42,
 /*   260 */    40,   12,   36,   35,   37,   39,   38,   45,   43,   41,
 /*   270 */    42,   40,  207,  131,   34,   33,   85,  127,   65,  198,
 /*   280 */    32,  199,  117,  131,   22,   44,  112,   31,  116,  196,
 /*   290 */   113,  110,  107,  121,   53,  175,   11,   35,   37,   39,
 /*   300 */    38,   45,   43,   41,   42,   40,  111,  102,  109,   34,
 /*   310 */    33,  135,   14,  134,  108,   32,  199,  117,   20,  195,
 /*   320 */    44,   13,   14,  116,  182,  113,  110,  107,  106,   34,
 /*   330 */    33,  129,    7,  136,  105,   32,  199,  117,   31,  133,
 /*   340 */    44,  171,  102,  116,  174,  113,  110,  107,  170,  194,
 /*   350 */    77,   36,   35,   37,   39,   38,   45,   43,   41,   42,
 /*   360 */    40,   50,  154,    1,  179,  178,   31,  164,  167,   99,
 /*   370 */    15,   98,   97,   10,   17,  169,   96,   36,   35,   37,
 /*   380 */    39,   38,   45,   43,   41,   42,   40,    9,   36,   35,
 /*   390 */    37,   39,   38,   45,   43,   41,   42,   40,   34,   33,
 /*   400 */    13,   14,  185,  160,   32,  199,  117,  121,   75,   44,
 /*   410 */   186,  211,  116,  183,  113,  110,  107,   34,   33,   84,
 /*   420 */   127,   65,   49,   32,  199,  117,  162,  166,   44,  121,
 /*   430 */    56,  116,  174,  113,  110,  107,   34,   33,   81,  127,
 /*   440 */    65,  161,   32,  199,  117,   18,   16,   44,   52,   91,
 /*   450 */   116,   77,  113,  110,  107,   92,  159,   87,  127,   65,
 /*   460 */   130,  158,   50,  154,    1,  155,  178,  121,   57,  167,
 /*   470 */    99,  147,   98,   97,   95,   17,   89,   96,   80,  127,
 /*   480 */    65,   34,   33,   88,  121,   57,   73,   32,  199,  117,
 /*   490 */   121,   76,   44,   74,  173,  116,   82,  113,  110,  107,
 /*   500 */   121,   57,  128,   37,   39,   38,   45,   43,   41,   42,
 /*   510 */    40,   79,   39,   38,   45,   43,   41,   42,   40,  121,
 /*   520 */    53,   71,   45,   43,   41,   42,   40,   83,  121,  193,
 /*   530 */   121,  192,   90,  121,  191,  121,   70,  157,  121,   69,
 /*   540 */   121,   68,  121,   66,  156,  121,   67,  314,    8,  121,
 /*   550 */   190,  121,  189,  121,  188,  121,   64,  315,  121,   55,
 /*   560 */   121,   54,  121,   63,   96,  121,   62,  121,   61,  121,
 /*   570 */    60,  121,   59,  121,   58,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    53,    1,    1,    2,    1,   58,   38,   60,   40,   26,
 /*    10 */    63,   64,   65,   66,   67,   68,   69,   70,   71,   72,
 /*    20 */    73,   74,   75,   76,   77,   78,   79,   80,   81,   82,
 /*    30 */    29,   28,   26,   86,   53,   88,   89,   90,   38,   58,
 /*    40 */     1,   60,   26,    1,   63,   64,   65,   66,   67,   68,
 /*    50 */    29,   70,   71,   72,   73,   74,   75,   76,   77,   78,
 /*    60 */    79,   80,   81,   82,   60,   61,   62,   86,   53,   88,
 /*    70 */    89,   90,   30,   58,    1,   60,   25,   38,   63,   64,
 /*    80 */    65,   66,   67,   68,   27,   70,   71,   72,   73,   74,
 /*    90 */    75,   76,   77,   78,   79,   80,   81,   82,   60,   61,
 /*   100 */    62,   86,   53,   88,   89,   90,   26,   58,   27,   60,
 /*   110 */    30,    1,   63,   64,   65,   66,   67,   68,   28,   70,
 /*   120 */    71,   72,   73,   74,   75,   76,   77,   78,   79,   80,
 /*   130 */    81,   82,   60,   61,   62,   86,   53,   88,   89,   90,
 /*   140 */    30,   58,    1,   60,   25,    1,   63,   64,   65,   66,
 /*   150 */    67,   68,   28,   70,   71,   72,   73,   74,   75,   76,
 /*   160 */    77,   78,   79,   80,   81,   82,   60,   61,   62,   86,
 /*   170 */    53,   88,   89,   90,   30,   58,   27,   60,   25,   38,
 /*   180 */    63,   64,   65,   66,   67,   68,    1,   70,   71,   72,
 /*   190 */    73,   74,   75,   76,   77,   78,   79,   80,   81,   82,
 /*   200 */    27,    1,    2,   86,   53,   88,   89,   90,   28,   58,
 /*   210 */    29,   60,   29,   28,   63,   64,   65,   66,   67,   68,
 /*   220 */    33,   70,   71,   72,   73,   74,   75,   76,   77,   78,
 /*   230 */    79,   80,   81,   82,   30,    1,    2,   86,   38,   88,
 /*   240 */    89,   90,   20,   21,   22,    7,    8,    9,   10,   11,
 /*   250 */    12,   13,   14,   15,   16,   17,   18,   19,   20,   21,
 /*   260 */    22,    5,   13,   14,   15,   16,   17,   18,   19,   20,
 /*   270 */    21,   22,   38,    1,   18,   19,   59,   60,   61,   30,
 /*   280 */    24,   25,   26,    1,    2,   29,   29,    1,   32,   30,
 /*   290 */    34,   35,   36,   60,   61,   62,    5,   14,   15,   16,
 /*   300 */    17,   18,   19,   20,   21,   22,   33,   51,   29,   18,
 /*   310 */    19,   63,    4,   65,   33,   24,   25,   26,   46,   30,
 /*   320 */    29,    3,    4,   32,   38,   34,   35,   36,   29,   18,
 /*   330 */    19,   83,   84,   85,   33,   24,   25,   26,    1,   91,
 /*   340 */    29,   30,   51,   32,   33,   34,   35,   36,   30,   30,
 /*   350 */    26,   13,   14,   15,   16,   17,   18,   19,   20,   21,
 /*   360 */    22,   37,   38,   39,   40,   41,    1,   30,   44,   45,
 /*   370 */    29,   47,   48,   29,   50,   43,   52,   13,   14,   15,
 /*   380 */    16,   17,   18,   19,   20,   21,   22,   29,   13,   14,
 /*   390 */    15,   16,   17,   18,   19,   20,   21,   22,   18,   19,
 /*   400 */     3,    4,   38,   38,   24,   25,   26,   60,   61,   29,
 /*   410 */    30,    0,   32,   38,   34,   35,   36,   18,   19,   59,
 /*   420 */    60,   61,   29,   24,   25,   26,   38,   30,   29,   60,
 /*   430 */    61,   32,   33,   34,   35,   36,   18,   19,   59,   60,
 /*   440 */    61,   38,   24,   25,   26,    1,   29,   29,   37,   58,
 /*   450 */    32,   26,   34,   35,   36,   26,   38,   59,   60,   61,
 /*   460 */    49,   38,   37,   38,   39,   38,   41,   60,   61,   44,
 /*   470 */    45,   38,   47,   48,   30,   50,   25,   52,   59,   60,
 /*   480 */    61,   18,   19,   57,   60,   61,   58,   24,   25,   26,
 /*   490 */    60,   61,   29,   26,   87,   32,   58,   34,   35,   36,
 /*   500 */    60,   61,   26,   15,   16,   17,   18,   19,   20,   21,
 /*   510 */    22,   87,   16,   17,   18,   19,   20,   21,   22,   60,
 /*   520 */    61,   62,   18,   19,   20,   21,   22,   87,   60,   61,
 /*   530 */    60,   61,   58,   60,   61,   60,   61,   88,   60,   61,
 /*   540 */    60,   61,   60,   61,   88,   60,   61,   55,   56,   60,
 /*   550 */    61,   60,   61,   60,   61,   60,   61,   92,   60,   61,
 /*   560 */    60,   61,   60,   61,   52,   60,   61,   60,   61,   60,
 /*   570 */    61,   60,   61,   60,   61,
};
#define YY_SHIFT_USE_DFLT (-33)
#define YY_SHIFT_COUNT (132)
#define YY_SHIFT_MIN   (-32)
#define YY_SHIFT_MAX   (512)
static const short yy_shift_ofst[] = {
 /*     0 */   -33,  425,  324,  425,  425,  425,  425,  425,  411,  256,
 /*    10 */   311,  291,  291,  256,  256,  256,  399,  418,  399,  380,
 /*    20 */   463,  463,  463,  463,  463,  463,  463,  463,  463,  463,
 /*    30 */   463,  463,  463,  463,  463,  463,  463,  463,  463,  463,
 /*    40 */   463,  463,  463,  463,  463,  463,   80,  512,  512,  476,
 /*    50 */   467,  451,  429,  238,  375,  364,  249,  338,  338,  338,
 /*    60 */   338,  338,  338,  338,  338,  338,  283,  488,  496,  504,
 /*    70 */   504,  397,  318,  234,  200,  222,  222,    1,  -32,  444,
 /*    80 */   365,  337,  272,  144,  286,  141,  282,  110,  185,    3,
 /*    90 */    42,   39,    0,  433,  427,  423,  417,  403,  388,  393,
 /*   100 */   358,  332,  344,  308,  341,  319,  301,  299,  289,  281,
 /*   110 */   279,  259,  273,  257,  204,  187,  183,  181,  180,  153,
 /*   120 */   173,  149,  124,  119,   90,   51,   81,   57,   73,   21,
 /*   130 */    16,    6,  -17,
};
#define YY_REDUCE_USE_DFLT (-54)
#define YY_REDUCE_COUNT (52)
#define YY_REDUCE_MIN   (-53)
#define YY_REDUCE_MAX   (513)
static const short yy_reduce_ofst[] = {
 /*     0 */   492,  -53,  151,  117,   83,   49,   15,  -19,  248,  459,
 /*    10 */   440,  233,  106,   72,   38,    4,  424,  419,  407,  398,
 /*    20 */   379,  360,  217,  513,  511,  509,  507,  505,  502,  500,
 /*    30 */   498,  495,  493,  491,  489,  485,  482,  480,  478,  475,
 /*    40 */   473,  470,  468,  430,  369,  347,  474,  456,  449,  438,
 /*    50 */   428,  426,  391,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   311,  313,  313,  313,  313,  313,  313,  313,  313,  313,
 /*    10 */   313,  313,  313,  313,  313,  313,  313,  313,  313,  313,
 /*    20 */   313,  313,  313,  313,  313,  313,  313,  313,  313,  313,
 /*    30 */   313,  313,  313,  313,  313,  313,  313,  313,  313,  313,
 /*    40 */   313,  313,  313,  313,  313,  313,  313,  290,  289,  313,
 /*    50 */   313,  313,  313,  313,  313,  313,  313,  281,  248,  247,
 /*    60 */   246,  245,  244,  243,  219,  218,  238,  239,  237,  236,
 /*    70 */   235,  313,  313,  313,  313,  230,  231,  313,  313,  313,
 /*    80 */   313,  313,  313,  313,  313,  313,  313,  313,  313,  313,
 /*    90 */   313,  313,  313,  313,  313,  313,  313,  313,  313,  313,
 /*   100 */   313,  265,  313,  250,  313,  313,  313,  313,  313,  313,
 /*   110 */   313,  313,  313,  313,  313,  313,  313,  221,  313,  313,
 /*   120 */   313,  224,  313,  313,  313,  313,  313,  224,  313,  313,
 /*   130 */   313,  313,  313,  312,  310,  309,  308,  278,  262,  307,
 /*   140 */   306,  305,  304,  303,  302,  301,  300,  299,  298,  297,
 /*   150 */   296,  295,  294,  293,  292,  291,  288,  287,  286,  279,
 /*   160 */   280,  274,  273,  272,  271,  270,  269,  268,  267,  266,
 /*   170 */   264,  285,  284,  283,  282,  252,  251,  249,  263,  261,
 /*   180 */   260,  259,  256,  254,  258,  257,  223,  222,  242,  241,
 /*   190 */   240,  234,  233,  232,  229,  228,  227,  226,  225,  220,
 /*   200 */   216,  213,  217,  212,  277,  276,  275,  255,  215,  253,
 /*   210 */   214,
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
  "MAPSTRING",     "STRING",        "UNIT",          "SWITCH",      
  "LOCATION",      "VAR",           "SEMICOLON",     "LBRACKET",    
  "RBRACKET",      "IF",            "IFX",           "ELSE",        
  "WHILE",         "FOR",           "COLON",         "CONTINUE",    
  "BREAK",         "FUNCTION",      "RETURN",        "CONDITIONNAME",
  "ACTIONNAME",    "error",         "nt",            "program",     
  "chunks",        "numList",       "nameList",      "exprList",    
  "funcexpr",      "expr",          "lexpr",         "vdef_stmt",   
  "vdefAssign_stmt",  "vdefMulti_stmt",  "vdefMultiAssign_stmt",  "assign_stmt", 
  "assignMulti_stmt",  "stmtList",      "stmt",          "block",       
  "if_start",      "if_header",     "if_stmt",       "else_header", 
  "while_start",   "while_header",  "while_stmt",    "foreach_header",
  "foreach_stmt",  "continue_stmt",  "break_stmt",    "function_start",
  "function_header",  "fdef_chunk",    "return_stmt",   "caExpr",      
  "action",        "actions",       "actionStmt",    "chunk",       
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
 /*  15 */ "expr ::= MAPSTRING LPAREN STRING RPAREN",
 /*  16 */ "expr ::= UNIT LPAREN STRING RPAREN",
 /*  17 */ "expr ::= SWITCH LPAREN STRING RPAREN",
 /*  18 */ "expr ::= LOCATION LPAREN STRING RPAREN",
 /*  19 */ "expr ::= expr PLUS expr",
 /*  20 */ "expr ::= expr MINUS expr",
 /*  21 */ "expr ::= expr MULTIPLY expr",
 /*  22 */ "expr ::= expr DIVIDE expr",
 /*  23 */ "expr ::= expr MOD expr",
 /*  24 */ "expr ::= expr LSHIFT expr",
 /*  25 */ "expr ::= expr RSHIFT expr",
 /*  26 */ "expr ::= expr BITAND expr",
 /*  27 */ "expr ::= expr BITOR expr",
 /*  28 */ "expr ::= expr BITXOR expr",
 /*  29 */ "expr ::= PLUS expr",
 /*  30 */ "expr ::= MINUS expr",
 /*  31 */ "expr ::= BITNOT expr",
 /*  32 */ "lexpr ::= expr EQ expr",
 /*  33 */ "lexpr ::= expr NE expr",
 /*  34 */ "lexpr ::= expr LE expr",
 /*  35 */ "lexpr ::= expr LT expr",
 /*  36 */ "lexpr ::= expr GE expr",
 /*  37 */ "lexpr ::= expr GT expr",
 /*  38 */ "lexpr ::= lexpr LAND lexpr",
 /*  39 */ "lexpr ::= lexpr LOR lexpr",
 /*  40 */ "lexpr ::= LNOT lexpr",
 /*  41 */ "lexpr ::= LNOT LNOT lexpr",
 /*  42 */ "vdef_stmt ::= VAR NAME SEMICOLON",
 /*  43 */ "vdefAssign_stmt ::= VAR NAME ASSIGN expr SEMICOLON",
 /*  44 */ "vdefMulti_stmt ::= VAR nameList SEMICOLON",
 /*  45 */ "vdefMultiAssign_stmt ::= VAR nameList ASSIGN exprList SEMICOLON",
 /*  46 */ "assign_stmt ::= NAME ASSIGN expr SEMICOLON",
 /*  47 */ "assignMulti_stmt ::= nameList ASSIGN exprList SEMICOLON",
 /*  48 */ "stmtList ::= stmt",
 /*  49 */ "stmtList ::= stmtList stmt",
 /*  50 */ "block ::= LBRACKET stmtList RBRACKET",
 /*  51 */ "block ::= LBRACKET error RBRACKET",
 /*  52 */ "if_start ::= IF",
 /*  53 */ "if_header ::= if_start LPAREN lexpr RPAREN",
 /*  54 */ "if_stmt ::= if_header stmt",
 /*  55 */ "else_header ::= if_header stmt ELSE",
 /*  56 */ "if_stmt ::= else_header stmt",
 /*  57 */ "while_start ::= WHILE",
 /*  58 */ "while_header ::= while_start LPAREN lexpr RPAREN",
 /*  59 */ "while_stmt ::= while_header stmt",
 /*  60 */ "foreach_header ::= FOR LPAREN nameList COLON exprList RPAREN",
 /*  61 */ "foreach_stmt ::= foreach_header stmt",
 /*  62 */ "continue_stmt ::= CONTINUE SEMICOLON",
 /*  63 */ "break_stmt ::= BREAK SEMICOLON",
 /*  64 */ "function_start ::= FUNCTION NAME",
 /*  65 */ "function_header ::= function_start LPAREN nameList RPAREN",
 /*  66 */ "function_header ::= function_start LPAREN RPAREN",
 /*  67 */ "fdef_chunk ::= function_header stmt",
 /*  68 */ "return_stmt ::= RETURN SEMICOLON",
 /*  69 */ "return_stmt ::= RETURN exprList SEMICOLON",
 /*  70 */ "caExpr ::= expr",
 /*  71 */ "caExpr ::= STRING",
 /*  72 */ "caExpr ::= caExpr COMMA caExpr",
 /*  73 */ "lexpr ::= CONDITIONNAME LPAREN caExpr RPAREN",
 /*  74 */ "lexpr ::= CONDITIONNAME LPAREN RPAREN",
 /*  75 */ "action ::= ACTIONNAME LPAREN caExpr RPAREN SEMICOLON",
 /*  76 */ "actions ::= action action",
 /*  77 */ "actions ::= actions action",
 /*  78 */ "actionStmt ::= action",
 /*  79 */ "actionStmt ::= actions",
 /*  80 */ "stmt ::= error SEMICOLON",
 /*  81 */ "stmt ::= SEMICOLON",
 /*  82 */ "stmt ::= vdef_stmt",
 /*  83 */ "stmt ::= vdefAssign_stmt",
 /*  84 */ "stmt ::= vdefMultiAssign_stmt",
 /*  85 */ "stmt ::= vdefMulti_stmt",
 /*  86 */ "stmt ::= assign_stmt",
 /*  87 */ "stmt ::= assignMulti_stmt",
 /*  88 */ "stmt ::= funcexpr SEMICOLON",
 /*  89 */ "stmt ::= actionStmt",
 /*  90 */ "stmt ::= if_stmt",
 /*  91 */ "stmt ::= while_stmt",
 /*  92 */ "stmt ::= foreach_stmt",
 /*  93 */ "stmt ::= continue_stmt",
 /*  94 */ "stmt ::= break_stmt",
 /*  95 */ "stmt ::= return_stmt",
 /*  96 */ "stmt ::= block",
 /*  97 */ "chunk ::= fdef_chunk",
 /*  98 */ "chunk ::= vdef_stmt",
 /*  99 */ "chunk ::= vdefMulti_stmt",
 /* 100 */ "chunks ::=",
 /* 101 */ "chunks ::= chunks chunk",
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
    case 54: /* nt */
{
#line 28 "parser/epparser.lemon"
 delete (yypminor->yy0); 
#line 641 "parser/epparser.c"
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
  { 55, 1 },
  { 57, 3 },
  { 57, 3 },
  { 58, 3 },
  { 58, 3 },
  { 59, 6 },
  { 61, 6 },
  { 59, 1 },
  { 59, 3 },
  { 61, 1 },
  { 61, 1 },
  { 60, 4 },
  { 60, 3 },
  { 61, 1 },
  { 61, 3 },
  { 61, 4 },
  { 61, 4 },
  { 61, 4 },
  { 61, 4 },
  { 61, 3 },
  { 61, 3 },
  { 61, 3 },
  { 61, 3 },
  { 61, 3 },
  { 61, 3 },
  { 61, 3 },
  { 61, 3 },
  { 61, 3 },
  { 61, 3 },
  { 61, 2 },
  { 61, 2 },
  { 61, 2 },
  { 62, 3 },
  { 62, 3 },
  { 62, 3 },
  { 62, 3 },
  { 62, 3 },
  { 62, 3 },
  { 62, 3 },
  { 62, 3 },
  { 62, 2 },
  { 62, 3 },
  { 63, 3 },
  { 64, 5 },
  { 65, 3 },
  { 66, 5 },
  { 67, 4 },
  { 68, 4 },
  { 69, 1 },
  { 69, 2 },
  { 71, 3 },
  { 71, 3 },
  { 72, 1 },
  { 73, 4 },
  { 74, 2 },
  { 75, 3 },
  { 74, 2 },
  { 76, 1 },
  { 77, 4 },
  { 78, 2 },
  { 79, 6 },
  { 80, 2 },
  { 81, 2 },
  { 82, 2 },
  { 83, 2 },
  { 84, 4 },
  { 84, 3 },
  { 85, 2 },
  { 86, 2 },
  { 86, 3 },
  { 87, 1 },
  { 87, 1 },
  { 87, 3 },
  { 62, 4 },
  { 62, 3 },
  { 88, 5 },
  { 89, 2 },
  { 89, 2 },
  { 90, 1 },
  { 90, 1 },
  { 70, 2 },
  { 70, 1 },
  { 70, 1 },
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
  { 70, 1 },
  { 70, 1 },
  { 91, 1 },
  { 91, 1 },
  { 91, 1 },
  { 56, 0 },
  { 56, 2 },
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
#line 1042 "parser/epparser.c"
        break;
      case 3: /* nameList ::= NAME COMMA NAME */
      case 4: /* nameList ::= nameList COMMA NAME */ yytestcase(yyruleno==4);
      case 8: /* exprList ::= exprList COMMA expr */ yytestcase(yyruleno==8);
#line 62 "parser/epparser.lemon"
{ yygotominor.yy0 = new Token((yymsp[-2].minor.yy0->data) + ", " + (yymsp[0].minor.yy0->data), yymsp[0].minor.yy0); delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1049 "parser/epparser.c"
        break;
      case 5: /* exprList ::= funcexpr LSQBRACKET LSQBRACKET numList RSQBRACKET RSQBRACKET */
      case 6: /* expr ::= funcexpr LSQBRACKET LSQBRACKET NUMBER RSQBRACKET RSQBRACKET */ yytestcase(yyruleno==6);
#line 64 "parser/epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[-2].minor.yy0);
    (*pGen) << yygotominor.yy0->data << " = _SRET(" << yymsp[-5].minor.yy0->data << ", [" << yymsp[-2].minor.yy0->data << "])" << std::endl;
    delete yymsp[-5].minor.yy0; delete yymsp[-2].minor.yy0;
}
#line 1059 "parser/epparser.c"
        break;
      case 7: /* exprList ::= expr */
      case 9: /* expr ::= NUMBER */ yytestcase(yyruleno==9);
      case 13: /* expr ::= funcexpr */ yytestcase(yyruleno==13);
      case 41: /* lexpr ::= LNOT LNOT lexpr */ yytestcase(yyruleno==41);
      case 70: /* caExpr ::= expr */ yytestcase(yyruleno==70);
      case 71: /* caExpr ::= STRING */ yytestcase(yyruleno==71);
#line 75 "parser/epparser.lemon"
{ yygotominor.yy0 = yymsp[0].minor.yy0; }
#line 1069 "parser/epparser.c"
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
#line 1080 "parser/epparser.c"
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
#line 1100 "parser/epparser.c"
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
#line 1121 "parser/epparser.c"
        break;
      case 14: /* expr ::= LPAREN expr RPAREN */
#line 128 "parser/epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0, *pGen);
}
#line 1129 "parser/epparser.c"
        break;
      case 15: /* expr ::= MAPSTRING LPAREN STRING RPAREN */
#line 133 "parser/epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "EncodeString(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0, *pGen);
}
#line 1137 "parser/epparser.c"
        break;
      case 16: /* expr ::= UNIT LPAREN STRING RPAREN */
#line 138 "parser/epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "EncodeUnit(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0, *pGen);
}
#line 1145 "parser/epparser.c"
        break;
      case 17: /* expr ::= SWITCH LPAREN STRING RPAREN */
#line 143 "parser/epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "EncodeSwitch(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0, *pGen);
}
#line 1153 "parser/epparser.c"
        break;
      case 18: /* expr ::= LOCATION LPAREN STRING RPAREN */
#line 148 "parser/epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "EncodeLocation(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0, *pGen);
}
#line 1161 "parser/epparser.c"
        break;
      case 19: /* expr ::= expr PLUS expr */
#line 153 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "+",  yymsp[0].minor.yy0, *pGen); }
#line 1166 "parser/epparser.c"
        break;
      case 20: /* expr ::= expr MINUS expr */
#line 154 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "-",  yymsp[0].minor.yy0, *pGen); }
#line 1171 "parser/epparser.c"
        break;
      case 21: /* expr ::= expr MULTIPLY expr */
#line 155 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "*",  yymsp[0].minor.yy0, *pGen); }
#line 1176 "parser/epparser.c"
        break;
      case 22: /* expr ::= expr DIVIDE expr */
#line 156 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "//", yymsp[0].minor.yy0, *pGen); }
#line 1181 "parser/epparser.c"
        break;
      case 23: /* expr ::= expr MOD expr */
#line 157 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "%",  yymsp[0].minor.yy0, *pGen); }
#line 1186 "parser/epparser.c"
        break;
      case 24: /* expr ::= expr LSHIFT expr */
#line 158 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<<", yymsp[0].minor.yy0, *pGen); }
#line 1191 "parser/epparser.c"
        break;
      case 25: /* expr ::= expr RSHIFT expr */
#line 159 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">>", yymsp[0].minor.yy0, *pGen); }
#line 1196 "parser/epparser.c"
        break;
      case 26: /* expr ::= expr BITAND expr */
#line 160 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "&",  yymsp[0].minor.yy0, *pGen); }
#line 1201 "parser/epparser.c"
        break;
      case 27: /* expr ::= expr BITOR expr */
#line 161 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "|",  yymsp[0].minor.yy0, *pGen); }
#line 1206 "parser/epparser.c"
        break;
      case 28: /* expr ::= expr BITXOR expr */
#line 162 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "^",  yymsp[0].minor.yy0, *pGen); }
#line 1211 "parser/epparser.c"
        break;
      case 29: /* expr ::= PLUS expr */
#line 165 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = +" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1216 "parser/epparser.c"
        break;
      case 30: /* expr ::= MINUS expr */
#line 166 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = -" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1221 "parser/epparser.c"
        break;
      case 31: /* expr ::= BITNOT expr */
#line 167 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = ~" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1226 "parser/epparser.c"
        break;
      case 32: /* lexpr ::= expr EQ expr */
#line 170 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "==", yymsp[0].minor.yy0, *pGen); }
#line 1231 "parser/epparser.c"
        break;
      case 33: /* lexpr ::= expr NE expr */
#line 171 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "!=", yymsp[0].minor.yy0, *pGen); }
#line 1236 "parser/epparser.c"
        break;
      case 34: /* lexpr ::= expr LE expr */
#line 172 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<=", yymsp[0].minor.yy0, *pGen); }
#line 1241 "parser/epparser.c"
        break;
      case 35: /* lexpr ::= expr LT expr */
#line 173 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, "<",  yymsp[0].minor.yy0, *pGen); }
#line 1246 "parser/epparser.c"
        break;
      case 36: /* lexpr ::= expr GE expr */
#line 174 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">=", yymsp[0].minor.yy0, *pGen); }
#line 1251 "parser/epparser.c"
        break;
      case 37: /* lexpr ::= expr GT expr */
#line 175 "parser/epparser.lemon"
{ yygotominor.yy0 = binaryMerge(yymsp[-2].minor.yy0, ">" , yymsp[0].minor.yy0, *pGen); }
#line 1256 "parser/epparser.c"
        break;
      case 38: /* lexpr ::= lexpr LAND lexpr */
#line 177 "parser/epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "[" + yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data + "]";
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0, *pGen);
}
#line 1265 "parser/epparser.c"
        break;
      case 39: /* lexpr ::= lexpr LOR lexpr */
#line 183 "parser/epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "EUDOr([" + yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data + "])";
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0, *pGen);
}
#line 1274 "parser/epparser.c"
        break;
      case 40: /* lexpr ::= LNOT lexpr */
#line 189 "parser/epparser.lemon"
{
    yymsp[0].minor.yy0->data = "EUDNot([" + yymsp[0].minor.yy0->data + "])";
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0, *pGen);
}
#line 1282 "parser/epparser.c"
        break;
      case 42: /* vdef_stmt ::= VAR NAME SEMICOLON */
#line 199 "parser/epparser.lemon"
{
    (*pGen) << yymsp[-1].minor.yy0->data << " = EUDVariable()" << std::endl;
    pGen->namedef(yymsp[-1].minor.yy0->data);
    delete yymsp[-1].minor.yy0;
}
#line 1291 "parser/epparser.c"
        break;
      case 43: /* vdefAssign_stmt ::= VAR NAME ASSIGN expr SEMICOLON */
#line 205 "parser/epparser.lemon"
{
    (*pGen) << yymsp[-3].minor.yy0->data << " = _MVAR([" << yymsp[-1].minor.yy0->data << "])" << std::endl;
    if(!pGen->namedef(yymsp[-3].minor.yy0->data)) {
        throw_error(yymsp[-3].minor.yy0->line, 196, ("Redeclaration of variable \'" + (yymsp[-3].minor.yy0->data) + "\'"));
    }
    delete yymsp[-3].minor.yy0;
}
#line 1302 "parser/epparser.c"
        break;
      case 44: /* vdefMulti_stmt ::= VAR nameList SEMICOLON */
#line 213 "parser/epparser.lemon"
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
#line 1319 "parser/epparser.c"
        break;
      case 45: /* vdefMultiAssign_stmt ::= VAR nameList ASSIGN exprList SEMICOLON */
#line 227 "parser/epparser.lemon"
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
#line 1336 "parser/epparser.c"
        break;
      case 46: /* assign_stmt ::= NAME ASSIGN expr SEMICOLON */
#line 241 "parser/epparser.lemon"
{
    (*pGen) << yymsp[-3].minor.yy0->data << " << " << yymsp[-1].minor.yy0->data << std::endl;
    if(pGen->undefined(yymsp[-3].minor.yy0->data)) {
        throw_error(yymsp[-3].minor.yy0->line, 103, ("Undeclared variable \'" + (yymsp[-3].minor.yy0->data) + "\'"));
        pGen->namedef(yymsp[-3].minor.yy0->data);
    }
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1348 "parser/epparser.c"
        break;
      case 47: /* assignMulti_stmt ::= nameList ASSIGN exprList SEMICOLON */
#line 250 "parser/epparser.lemon"
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
#line 1364 "parser/epparser.c"
        break;
      case 51: /* block ::= LBRACKET error RBRACKET */
#line 267 "parser/epparser.lemon"
{
    throw_error(yymsp[0].minor.yy0->line, 6298, "Block not terminated properly.");
}
#line 1371 "parser/epparser.c"
        break;
      case 52: /* if_start ::= IF */
#line 273 "parser/epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    (*pGen) << yygotominor.yy0->data << " = EUDIf()" << std::endl;
}
#line 1379 "parser/epparser.c"
        break;
      case 53: /* if_header ::= if_start LPAREN lexpr RPAREN */
      case 58: /* while_header ::= while_start LPAREN lexpr RPAREN */ yytestcase(yyruleno==58);
#line 277 "parser/epparser.lemon"
{
    (*pGen) << "if " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data << "):" << std::endl;
    pGen->indent();
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1389 "parser/epparser.c"
        break;
      case 54: /* if_stmt ::= if_header stmt */
      case 56: /* if_stmt ::= else_header stmt */ yytestcase(yyruleno==56);
#line 283 "parser/epparser.lemon"
{
    pGen->unindent(false);
    (*pGen) << "EUDEndIf()" << std::endl;
}
#line 1398 "parser/epparser.c"
        break;
      case 55: /* else_header ::= if_header stmt ELSE */
#line 288 "parser/epparser.lemon"
{
    pGen->unindent(false);
    (*pGen) << "if EUDElse()():" << std::endl;
    pGen->indent();
}
#line 1407 "parser/epparser.c"
        break;
      case 57: /* while_start ::= WHILE */
#line 301 "parser/epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    (*pGen) << yygotominor.yy0->data << " = EUDWhile()" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1416 "parser/epparser.c"
        break;
      case 59: /* while_stmt ::= while_header stmt */
#line 313 "parser/epparser.lemon"
{
    pGen->unindent(false);
    (*pGen) << "EUDEndWhile()" << std::endl;
}
#line 1424 "parser/epparser.c"
        break;
      case 60: /* foreach_header ::= FOR LPAREN nameList COLON exprList RPAREN */
#line 319 "parser/epparser.lemon"
{
    (*pGen) << "for " << yymsp[-3].minor.yy0->data << " in " << yymsp[-1].minor.yy0->data << ":" << std::endl;
    pGen->indent();
}
#line 1432 "parser/epparser.c"
        break;
      case 61: /* foreach_stmt ::= foreach_header stmt */
      case 67: /* fdef_chunk ::= function_header stmt */ yytestcase(yyruleno==67);
#line 324 "parser/epparser.lemon"
{
    pGen->unindent(true);
}
#line 1440 "parser/epparser.c"
        break;
      case 62: /* continue_stmt ::= CONTINUE SEMICOLON */
#line 330 "parser/epparser.lemon"
{
    (*pGen) << "EUDContinue()" << std::endl;
}
#line 1447 "parser/epparser.c"
        break;
      case 63: /* break_stmt ::= BREAK SEMICOLON */
#line 334 "parser/epparser.lemon"
{
    (*pGen) << "EUDBreak()" << std::endl;
}
#line 1454 "parser/epparser.c"
        break;
      case 64: /* function_start ::= FUNCTION NAME */
#line 339 "parser/epparser.lemon"
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
#line 1470 "parser/epparser.c"
        break;
      case 65: /* function_header ::= function_start LPAREN nameList RPAREN */
#line 352 "parser/epparser.lemon"
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
#line 1490 "parser/epparser.c"
        break;
      case 66: /* function_header ::= function_start LPAREN RPAREN */
#line 369 "parser/epparser.lemon"
{
    (*pGen) << "@EUDFunc" << std::endl;
    (*pGen) << "def " << yymsp[-2].minor.yy0->data << "():" << std::endl;
    pGen->indent();
    tmpIndex = 1;
    delete yymsp[-2].minor.yy0;
}
#line 1501 "parser/epparser.c"
        break;
      case 68: /* return_stmt ::= RETURN SEMICOLON */
#line 383 "parser/epparser.lemon"
{
    (*pGen) << "EUDReturn()" << std::endl;
}
#line 1508 "parser/epparser.c"
        break;
      case 69: /* return_stmt ::= RETURN exprList SEMICOLON */
#line 386 "parser/epparser.lemon"
{
    (*pGen) << "EUDReturn(" << yymsp[-1].minor.yy0->data << ")" << std::endl;
    delete yymsp[-1].minor.yy0;
}
#line 1516 "parser/epparser.c"
        break;
      case 72: /* caExpr ::= caExpr COMMA caExpr */
#line 396 "parser/epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data;
    yymsp[-2].minor.yy0->type = TOKEN_TEMP;
    yygotominor.yy0 = yymsp[-2].minor.yy0;
}
#line 1525 "parser/epparser.c"
        break;
      case 73: /* lexpr ::= CONDITIONNAME LPAREN caExpr RPAREN */
#line 403 "parser/epparser.lemon"
{
    yymsp[-3].minor.yy0->data = yymsp[-3].minor.yy0->data + "(" + yymsp[-1].minor.yy0->data + ")";
    delete yymsp[-1].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0, *pGen);
}
#line 1534 "parser/epparser.c"
        break;
      case 74: /* lexpr ::= CONDITIONNAME LPAREN RPAREN */
#line 409 "parser/epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + "()";
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0, *pGen);
}
#line 1542 "parser/epparser.c"
        break;
      case 75: /* action ::= ACTIONNAME LPAREN caExpr RPAREN SEMICOLON */
#line 414 "parser/epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[-4].minor.yy0);
    yygotominor.yy0->data =  yymsp[-4].minor.yy0->data + "(" + yymsp[-2].minor.yy0->data + ")";
    delete yymsp[-4].minor.yy0; delete yymsp[-2].minor.yy0;
}
#line 1551 "parser/epparser.c"
        break;
      case 76: /* actions ::= action action */
      case 77: /* actions ::= actions action */ yytestcase(yyruleno==77);
#line 420 "parser/epparser.lemon"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
    yymsp[-1].minor.yy0->data += ",\n" + yymsp[0].minor.yy0->data;
    delete yymsp[0].minor.yy0;
}
#line 1561 "parser/epparser.c"
        break;
      case 78: /* actionStmt ::= action */
#line 432 "parser/epparser.lemon"
{
    (*pGen) << "DoEvents(" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1569 "parser/epparser.c"
        break;
      case 79: /* actionStmt ::= actions */
#line 437 "parser/epparser.lemon"
{
    (*pGen) << "DoEvents([" << std::endl;
    pGen->indent();
    (*pGen) << yymsp[0].minor.yy0->data << std::endl;
    pGen->unindent(false);
    (*pGen) << "])" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1581 "parser/epparser.c"
        break;
      case 80: /* stmt ::= error SEMICOLON */
#line 448 "parser/epparser.lemon"
{ throw_error(yymsp[0].minor.yy0->line, 6974, "Error while parsing statement"); }
#line 1586 "parser/epparser.c"
        break;
      case 88: /* stmt ::= funcexpr SEMICOLON */
#line 458 "parser/epparser.lemon"
{ (*pGen) << yymsp[-1].minor.yy0->data << std::endl; }
#line 1591 "parser/epparser.c"
        break;
      default:
      /* (0) program ::= chunks */ yytestcase(yyruleno==0);
      /* (48) stmtList ::= stmt */ yytestcase(yyruleno==48);
      /* (49) stmtList ::= stmtList stmt */ yytestcase(yyruleno==49);
      /* (50) block ::= LBRACKET stmtList RBRACKET */ yytestcase(yyruleno==50);
      /* (81) stmt ::= SEMICOLON */ yytestcase(yyruleno==81);
      /* (82) stmt ::= vdef_stmt */ yytestcase(yyruleno==82);
      /* (83) stmt ::= vdefAssign_stmt */ yytestcase(yyruleno==83);
      /* (84) stmt ::= vdefMultiAssign_stmt */ yytestcase(yyruleno==84);
      /* (85) stmt ::= vdefMulti_stmt */ yytestcase(yyruleno==85);
      /* (86) stmt ::= assign_stmt */ yytestcase(yyruleno==86);
      /* (87) stmt ::= assignMulti_stmt */ yytestcase(yyruleno==87);
      /* (89) stmt ::= actionStmt */ yytestcase(yyruleno==89);
      /* (90) stmt ::= if_stmt */ yytestcase(yyruleno==90);
      /* (91) stmt ::= while_stmt */ yytestcase(yyruleno==91);
      /* (92) stmt ::= foreach_stmt */ yytestcase(yyruleno==92);
      /* (93) stmt ::= continue_stmt */ yytestcase(yyruleno==93);
      /* (94) stmt ::= break_stmt */ yytestcase(yyruleno==94);
      /* (95) stmt ::= return_stmt */ yytestcase(yyruleno==95);
      /* (96) stmt ::= block */ yytestcase(yyruleno==96);
      /* (97) chunk ::= fdef_chunk */ yytestcase(yyruleno==97);
      /* (98) chunk ::= vdef_stmt */ yytestcase(yyruleno==98);
      /* (99) chunk ::= vdefMulti_stmt */ yytestcase(yyruleno==99);
      /* (100) chunks ::= */ yytestcase(yyruleno==100);
      /* (101) chunks ::= chunks chunk */ yytestcase(yyruleno==101);
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
#line 1666 "parser/epparser.c"
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
#line 1685 "parser/epparser.c"
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
#line 476 "parser/epparser.lemon"


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

    if(!errorOccured) return iwCollapse(pGen.str());
    else throw std::runtime_error("Invalid syntax");
}
#line 1920 "parser/epparser.c"
