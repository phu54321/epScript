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
#include <sstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <regex>

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
std::string currentFunction;
std::string currentModule;
bool functionCalledInMultipleActions;
bool PARSER_DEBUG = false;
bool MAP_DEBUG = false;

#line 38 "parser\\epparser.c"
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
#define YYNOCODE 142
#define YYACTIONTYPE unsigned short int
#define ParseTOKENTYPE Token*
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  int yy283;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL  ParserStruct* ps ;
#define ParseARG_PDECL , ParserStruct* ps 
#define ParseARG_FETCH  ParserStruct* ps  = yypParser->ps 
#define ParseARG_STORE yypParser->ps  = ps 
#define YYNSTATE 352
#define YYNRULE 181
#define YYERRORSYMBOL 72
#define YYERRSYMDT yy283
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
#define YY_ACTTAB_COUNT (1349)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   229,   75,   74,   72,   73,   71,  209,   77,  212,  225,
 /*    10 */   213,  213,  326,  350,   19,   19,  336,  207,  121,   90,
 /*    20 */    76,   76,  334,  228,    2,   39,  230,  224,  223,  222,
 /*    30 */   157,  318,  317,  316,  315,  314,  217,  216,   20,  346,
 /*    40 */    97,  264,  215,  208,   28,   29,  128,  152,  180,    9,
 /*    50 */    41,  237,   97,  236,  177,    7,   12,  229,  128,  152,
 /*    60 */   215,   23,   14,    6,   87,    5,  225,  212,   80,  326,
 /*    70 */    96,  173,  172,  279,  294,  139,  207,  121,  255,  334,
 /*    80 */   228,    2,   38,  230,  224,  223,  222,  157,  318,  317,
 /*    90 */   316,  315,  314,  217,  216,  352,  164,   97,  264,  215,
 /*   100 */   215,   84,  161,  128,  152,  180,    9,   41,  341,   97,
 /*   110 */   123,  177,    7,   12,  345,  128,  152,  215,   23,   14,
 /*   120 */     6,   87,    5,  229,   94,   80,  235,  103,  263,  166,
 /*   130 */   332,   83,  225,  282,  215,  326,   28,   29,  215,  276,
 /*   140 */   178,    8,    4,   82,   95,  334,  228,    2,  100,  140,
 /*   150 */   224,  223,  222,  157,  318,  317,  316,  315,  314,  217,
 /*   160 */   216,   36,   37,   97,   28,   29,  289,   28,   29,  128,
 /*   170 */   152,  180,    9,   41,  344,   28,   29,  177,    7,   12,
 /*   180 */   229,  340,   28,   29,   23,   14,    6,   87,    5,  225,
 /*   190 */   212,   80,  326,   40,  280,  230,  273,  277,   81,  302,
 /*   200 */   121,  234,  334,  228,    2,  274,  265,  224,  223,  222,
 /*   210 */   157,  318,  317,  316,  315,  314,  217,  216,   34,  230,
 /*   220 */    97,  233,  212,  215,  259,  231,  128,  152,  180,    9,
 /*   230 */    41,  183,  121,   96,  177,    7,   12,  215,  293,  230,
 /*   240 */   232,   23,   14,    6,   87,    5,  229,   96,   80,   72,
 /*   250 */    73,   71,  190,  215,  339,  225,  230,  213,  326,   35,
 /*   260 */   320,   19,  261,  122,  246,  204,  185,   76,  334,  228,
 /*   270 */     2,  221,  337,  224,  223,  222,  157,  318,  317,  316,
 /*   280 */   315,  314,  217,  216,   33,  230,   97,  335,  212,  215,
 /*   290 */    86,   85,  128,  152,  180,    9,   41,  182,  121,   96,
 /*   300 */   177,    7,   12,  229,  292,  219,  215,   23,   14,    6,
 /*   310 */    87,    5,  225,  212,   80,  326,  122,  162,  300,  258,
 /*   320 */   333,  231,  181,  121,  220,  334,  228,    2,    3,  243,
 /*   330 */   224,  223,  222,  157,  318,  317,  316,  315,  314,  217,
 /*   340 */   216,  534,   11,   97,   93,  212,  215,   92,  324,  128,
 /*   350 */   152,  180,    9,   41,  150,  121,   96,  177,    7,   12,
 /*   360 */   215,  138,  323,  322,   23,   14,    6,   87,    5,  229,
 /*   370 */   122,   80,  204,  186,  215,  321,  215,  215,  225,  218,
 /*   380 */   215,  326,  319,  313,  134,  251,  122,  133,  204,  191,
 /*   390 */    96,  334,  228,    2,   20,  137,  224,  223,  222,  157,
 /*   400 */   318,  317,  316,  315,  314,  217,  216,  312,  221,   97,
 /*   410 */   307,  212,  215,  211,   91,  128,  152,  180,    9,   41,
 /*   420 */   160,  121,   96,  177,    7,   12,  229,  136,  304,  215,
 /*   430 */    23,   14,    6,   87,    5,  225,  212,   80,  326,   96,
 /*   440 */    40,  215,  244,  303,  135,  159,  121,   31,  334,  228,
 /*   450 */     2,  146,  201,  224,  223,  222,  157,  318,  317,  316,
 /*   460 */   315,  314,  217,  216,   32,  198,   97,  215,  215,  215,
 /*   470 */   299,   18,  128,  152,  180,    9,   41,  145,  144,  132,
 /*   480 */   177,    7,   12,  215,  202,  199,  196,   23,   14,    6,
 /*   490 */    87,    5,  167,  131,   80,  215,  215,  298,  297,  215,
 /*   500 */   215,  225,  195,  215,  326,  122,  130,  204,  169,  122,
 /*   510 */   127,  204,  188,  129,  249,  227,    2,  193,    1,  224,
 /*   520 */   223,  222,  157,  318,  317,  316,  315,  314,  217,  216,
 /*   530 */   296,  295,   97,  215,  215,  215,  192,   29,  128,  152,
 /*   540 */   180,    9,   41,   99,  143,  142,  177,    7,   12,  310,
 /*   550 */    16,  287,  215,   23,   14,    6,   87,    5,  225,  215,
 /*   560 */    80,  326,  141,  291,  286,  215,  126,  285,   26,  120,
 /*   570 */   278,  311,  226,    2,  328,  119,  224,  223,  222,  157,
 /*   580 */   318,  317,  316,  315,  314,  217,  216,   25,   24,   97,
 /*   590 */   215,  215,  215,  272,   13,  128,  152,  180,    9,   41,
 /*   600 */   118,  117,  116,  177,    7,   12,  266,   15,  215,  215,
 /*   610 */    23,   14,    6,   87,    5,   64,   63,   80,  115,   98,
 /*   620 */   262,   62,  309,  124,  325,  260,  215,   17,  215,   65,
 /*   630 */   254,  168,  332,   89,  331,   22,  114,  308,  113,  250,
 /*   640 */   206,  203,  200,  197,  194,   88,   43,   42,   67,   66,
 /*   650 */    68,   70,   69,   75,   74,   72,   73,   71,  281,  215,
 /*   660 */   275,  176,  171,  213,  257,  256,   21,   19,  248,  112,
 /*   670 */   165,  163,  215,   76,  306,   79,  242,   64,   63,  215,
 /*   680 */   215,  158,  111,   62,  309,  124,  325,  245,  215,  110,
 /*   690 */   109,   65,  342,  330,  332,   89,  330,   22,  108,  308,
 /*   700 */   155,  329,  206,  203,  200,  197,  194,   88,   43,   42,
 /*   710 */    67,   66,   68,   70,   69,   75,   74,   72,   73,   71,
 /*   720 */   281,  215,  275,  176,  171,  213,  257,  256,   21,   19,
 /*   730 */   305,  107,  215,  327,  210,   76,  187,  288,  154,   64,
 /*   740 */    63,  215,  106,  338,  215,   62,  309,  124,  325,  153,
 /*   750 */   215,  105,  215,   65,  104,  151,  332,   89,  170,   22,
 /*   760 */   102,  308,  101,  253,  206,  203,  200,  197,  194,   88,
 /*   770 */    43,   42,  252,  149,  148,  147,  179,  535,  535,  535,
 /*   780 */   535,  535,  281,  535,  275,  176,  171,  535,  257,  256,
 /*   790 */    21,  535,   61,   59,   58,   57,   56,   60,   67,   66,
 /*   800 */    68,   70,   69,   75,   74,   72,   73,   71,  535,  535,
 /*   810 */   535,  535,  535,  213,  535,  535,  535,   19,  305,  535,
 /*   820 */   535,  535,  535,   76,  535,   61,   59,   58,   57,   56,
 /*   830 */    60,   67,   66,   68,   70,   69,   75,   74,   72,   73,
 /*   840 */    71,  535,  535,  535,  535,  535,  213,   64,   63,  535,
 /*   850 */    19,  535,  535,   62,  309,  124,   76,  535,  535,  535,
 /*   860 */   535,   65,  535,  535,  535,   89,  535,   22,  535,  308,
 /*   870 */   535,  535,  206,  203,  200,  197,  194,   88,   43,   42,
 /*   880 */   535,   67,   66,   68,   70,   69,   75,   74,   72,   73,
 /*   890 */    71,  535,  535,  535,   27,  535,  184,  535,  535,  535,
 /*   900 */    19,  535,  535,  535,  535,  535,   55,   64,   63,  535,
 /*   910 */   535,  535,  535,   62,  309,  214,  535,  284,  283,  535,
 /*   920 */   535,   30,  535,  535,  535,  535,  535,   22,  535,  205,
 /*   930 */   535,  535,  206,  203,  200,  197,  194,  535,  535,  535,
 /*   940 */    64,   63,  535,  535,  535,  535,   62,  309,  156,  535,
 /*   950 */   535,  535,  535,  535,   65,  290,  535,  535,  535,  189,
 /*   960 */    22,  535,  308,  301,  535,  206,  203,  200,  197,  194,
 /*   970 */   535,  535,  535,   64,   63,  535,  535,  535,  535,   62,
 /*   980 */   309,  124,  535,  535,  535,  535,  535,   65,  535,  535,
 /*   990 */   535,  535,  535,   22,  535,  308,  535,  535,  206,  203,
 /*  1000 */   200,  197,  194,   54,   43,   42,  535,   67,   66,   68,
 /*  1010 */    70,   69,   75,   74,   72,   73,   71,   64,   63,  469,
 /*  1020 */   469,  535,  213,   62,  309,  156,   19,  535,  535,  535,
 /*  1030 */   535,   65,   76,  125,  535,  535,  535,   22,  535,  308,
 /*  1040 */   301,  535,  206,  203,  200,  197,  194,  535,  535,  535,
 /*  1050 */    20,  535,  535,   53,   52,   51,   50,   49,   48,   47,
 /*  1060 */    46,   45,   44,  535,  535,  535,  535,  535,  535,  469,
 /*  1070 */   469,  469,  469,  469,  469,  469,  469,  469,  469,  535,
 /*  1080 */   535,  535,  535,   67,   66,   68,   70,   69,   75,   74,
 /*  1090 */    72,   73,   71,  535,  535,  535,  535,  535,  213,  535,
 /*  1100 */   535,  535,   19,  535,  535,  271,  535,  535,   76,  535,
 /*  1110 */   535,  535,   67,   66,   68,   70,   69,   75,   74,   72,
 /*  1120 */    73,   71,  535,  270,  269,  268,  215,  184,  535,  535,
 /*  1130 */   535,   19,   64,   63,  535,  535,   97,   55,   62,  309,
 /*  1140 */   214,  535,  128,  152,  535,  535,   65,  535,  535,  535,
 /*  1150 */   535,  535,   22,  267,  308,  535,  535,  206,  203,  200,
 /*  1160 */   197,  194,  535,  535,  535,   64,   63,  535,  535,  535,
 /*  1170 */   535,   62,  309,  124,  535,  535,  535,  535,  535,   65,
 /*  1180 */   535,  535,  535,  535,  535,   22,  535,  308,  535,  535,
 /*  1190 */   206,  203,  200,  197,  194,  351,  241,  349,  348,  347,
 /*  1200 */   240,  239,  238,  343,  535,   10,  535,  535,  247,   78,
 /*  1210 */   471,  471,  535,  535,  535,    2,   66,   68,   70,   69,
 /*  1220 */    75,   74,   72,   73,   71,  470,  470,  535,  535,  535,
 /*  1230 */   213,  535,  535,  535,   19,  535,  535,  535,  535,  535,
 /*  1240 */    76,  535,  535,  535,  535,  535,  535,  535,  535,  535,
 /*  1250 */   535,  535,  535,  535,  535,  535,  535,  535,  535,  535,
 /*  1260 */   471,  471,  471,  471,  471,  471,  471,  471,  471,  471,
 /*  1270 */   535,  535,  535,  535,  535,  470,  470,  470,  470,  470,
 /*  1280 */   470,  470,  470,  470,  470,   68,   70,   69,   75,   74,
 /*  1290 */    72,   73,   71,  535,  535,  535,  535,  535,  213,  271,
 /*  1300 */   535,  535,   19,  535,  535,  535,  535,  535,   76,   70,
 /*  1310 */    69,   75,   74,   72,   73,   71,  535,  270,  269,  268,
 /*  1320 */   215,  213,  535,  535,  535,   19,  535,  535,  535,  535,
 /*  1330 */    97,   76,  535,  535,  535,  535,  128,  152,  535,  535,
 /*  1340 */   535,  535,  535,  535,  535,  535,  535,  175,  174,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    72,   18,   19,   20,   21,   22,    2,    1,  102,   81,
 /*    10 */    28,   28,   84,   27,   32,   32,   88,  111,  112,  113,
 /*    20 */    38,   38,   94,   95,   96,    1,    2,   99,  100,  101,
 /*    30 */   102,  103,  104,  105,  106,  107,  108,  109,   32,   27,
 /*    40 */   112,  101,  102,   39,    3,    4,  118,  119,  120,  121,
 /*    50 */   122,   28,  112,   30,  126,  127,  128,   72,  118,  119,
 /*    60 */   102,  133,  134,  135,  136,  137,   81,  102,  140,   84,
 /*    70 */   112,  131,  132,   88,   33,  117,  111,  112,  113,   94,
 /*    80 */    95,   96,    1,    2,   99,  100,  101,  102,  103,  104,
 /*    90 */   105,  106,  107,  108,  109,    0,   31,  112,  101,  102,
 /*   100 */   102,   36,   37,  118,  119,  120,  121,  122,   26,  112,
 /*   110 */   112,  126,  127,  128,   27,  118,  119,  102,  133,  134,
 /*   120 */   135,  136,  137,   72,   29,  140,   31,  112,  131,   34,
 /*   130 */    35,   36,   81,  118,  102,   84,    3,    4,  102,   88,
 /*   140 */   123,  124,  125,   48,  112,   94,   95,   96,  112,  117,
 /*   150 */    99,  100,  101,  102,  103,  104,  105,  106,  107,  108,
 /*   160 */   109,    1,    2,  112,    3,    4,   33,    3,    4,  118,
 /*   170 */   119,  120,  121,  122,   27,    3,    4,  126,  127,  128,
 /*   180 */    72,   26,    3,    4,  133,  134,  135,  136,  137,   81,
 /*   190 */   102,  140,   84,    2,   33,    2,   88,   33,   32,  111,
 /*   200 */   112,   26,   94,   95,   96,   33,   27,   99,  100,  101,
 /*   210 */   102,  103,  104,  105,  106,  107,  108,  109,    1,    2,
 /*   220 */   112,   87,  102,  102,   33,   91,  118,  119,  120,  121,
 /*   230 */   122,  111,  112,  112,  126,  127,  128,  102,  117,    2,
 /*   240 */    33,  133,  134,  135,  136,  137,   72,  112,  140,   20,
 /*   250 */    21,   22,  117,  102,   27,   81,    2,   28,   84,   66,
 /*   260 */    27,   32,   88,  112,   27,  114,  115,   38,   94,   95,
 /*   270 */    96,   38,   26,   99,  100,  101,  102,  103,  104,  105,
 /*   280 */   106,  107,  108,  109,    1,    2,  112,   27,  102,  102,
 /*   290 */   138,  139,  118,  119,  120,  121,  122,  111,  112,  112,
 /*   300 */   126,  127,  128,   72,  117,   25,  102,  133,  134,  135,
 /*   310 */   136,  137,   81,  102,  140,   84,  112,   87,  114,   88,
 /*   320 */    27,   91,  111,  112,   38,   94,   95,   96,   92,   93,
 /*   330 */    99,  100,  101,  102,  103,  104,  105,  106,  107,  108,
 /*   340 */   109,   74,   75,  112,   27,  102,  102,   27,   27,  118,
 /*   350 */   119,  120,  121,  122,  111,  112,  112,  126,  127,  128,
 /*   360 */   102,  117,   27,   27,  133,  134,  135,  136,  137,   72,
 /*   370 */   112,  140,  114,  115,  102,   27,  102,  102,   81,   39,
 /*   380 */   102,   84,   39,   27,  112,   88,  112,  112,  114,  115,
 /*   390 */   112,   94,   95,   96,   32,  117,   99,  100,  101,  102,
 /*   400 */   103,  104,  105,  106,  107,  108,  109,   27,   38,  112,
 /*   410 */    26,  102,  102,   38,   38,  118,  119,  120,  121,  122,
 /*   420 */   111,  112,  112,  126,  127,  128,   72,  117,   25,  102,
 /*   430 */   133,  134,  135,  136,  137,   81,  102,  140,   84,  112,
 /*   440 */     2,  102,   88,   39,  117,  111,  112,   32,   94,   95,
 /*   450 */    96,  112,   41,   99,  100,  101,  102,  103,  104,  105,
 /*   460 */   106,  107,  108,  109,    2,   41,  112,  102,  102,  102,
 /*   470 */    33,   32,  118,  119,  120,  121,  122,  112,  112,  112,
 /*   480 */   126,  127,  128,  102,   32,   32,   32,  133,  134,  135,
 /*   490 */   136,  137,   72,  112,  140,  102,  102,   33,   33,  102,
 /*   500 */   102,   81,   41,  102,   84,  112,  112,  114,  115,  112,
 /*   510 */   112,  114,  115,  112,   94,   95,   96,   32,   98,   99,
 /*   520 */   100,  101,  102,  103,  104,  105,  106,  107,  108,  109,
 /*   530 */    33,   33,  112,  102,  102,  102,   41,    4,  118,  119,
 /*   540 */   120,  121,  122,  112,  112,  112,  126,  127,  128,   72,
 /*   550 */    32,   39,  102,  133,  134,  135,  136,  137,   81,  102,
 /*   560 */   140,   84,  112,   33,   33,  102,   26,   33,   32,  112,
 /*   570 */    61,   94,   95,   96,   97,  112,   99,  100,  101,  102,
 /*   580 */   103,  104,  105,  106,  107,  108,  109,   32,   32,  112,
 /*   590 */   102,  102,  102,   32,    2,  118,  119,  120,  121,  122,
 /*   600 */   112,  112,  112,  126,  127,  128,   27,    2,  102,  102,
 /*   610 */   133,  134,  135,  136,  137,   18,   19,  140,  112,  112,
 /*   620 */    33,   24,   25,   26,   27,   32,  102,   32,  102,   32,
 /*   630 */    27,   33,   35,   36,   37,   38,  112,   40,  112,   37,
 /*   640 */    43,   44,   45,   46,   47,   48,   49,   50,   13,   14,
 /*   650 */    15,   16,   17,   18,   19,   20,   21,   22,   61,  102,
 /*   660 */    63,   64,   65,   28,   67,   68,   69,   32,   35,  112,
 /*   670 */    26,   26,  102,   38,   39,   32,   27,   18,   19,  102,
 /*   680 */   102,   85,  112,   24,   25,   26,   27,   33,  102,  112,
 /*   690 */   112,   32,   26,   37,   35,   36,   37,   38,  112,   40,
 /*   700 */   110,   97,   43,   44,   45,   46,   47,   48,   49,   50,
 /*   710 */    13,   14,   15,   16,   17,   18,   19,   20,   21,   22,
 /*   720 */    61,  102,   63,   64,   65,   28,   67,   68,   69,   32,
 /*   730 */    33,  112,  102,   97,   25,   38,  116,    2,   91,   18,
 /*   740 */    19,  102,  112,   26,  102,   24,   25,   26,   27,   91,
 /*   750 */   102,  112,  102,   32,  112,   91,   35,   36,   71,   38,
 /*   760 */   112,   40,  112,  138,   43,   44,   45,   46,   47,   48,
 /*   770 */    49,   50,  138,   91,   91,   91,   62,  141,  141,  141,
 /*   780 */   141,  141,   61,  141,   63,   64,   65,  141,   67,   68,
 /*   790 */    69,  141,    7,    8,    9,   10,   11,   12,   13,   14,
 /*   800 */    15,   16,   17,   18,   19,   20,   21,   22,  141,  141,
 /*   810 */   141,  141,  141,   28,  141,  141,  141,   32,   33,  141,
 /*   820 */   141,  141,  141,   38,  141,    7,    8,    9,   10,   11,
 /*   830 */    12,   13,   14,   15,   16,   17,   18,   19,   20,   21,
 /*   840 */    22,  141,  141,  141,  141,  141,   28,   18,   19,  141,
 /*   850 */    32,  141,  141,   24,   25,   26,   38,  141,  141,  141,
 /*   860 */   141,   32,  141,  141,  141,   36,  141,   38,  141,   40,
 /*   870 */   141,  141,   43,   44,   45,   46,   47,   48,   49,   50,
 /*   880 */   141,   13,   14,   15,   16,   17,   18,   19,   20,   21,
 /*   890 */    22,  141,  141,  141,    5,  141,   28,  141,  141,  141,
 /*   900 */    32,  141,  141,  141,  141,  141,   38,   18,   19,  141,
 /*   910 */   141,  141,  141,   24,   25,   26,  141,   49,   50,  141,
 /*   920 */   141,   32,  141,  141,  141,  141,  141,   38,  141,   40,
 /*   930 */   141,  141,   43,   44,   45,   46,   47,  141,  141,  141,
 /*   940 */    18,   19,  141,  141,  141,  141,   24,   25,   26,  141,
 /*   950 */   141,  141,  141,  141,   32,   33,  141,  141,  141,   70,
 /*   960 */    38,  141,   40,   41,  141,   43,   44,   45,   46,   47,
 /*   970 */   141,  141,  141,   18,   19,  141,  141,  141,  141,   24,
 /*   980 */    25,   26,  141,  141,  141,  141,  141,   32,  141,  141,
 /*   990 */   141,  141,  141,   38,  141,   40,  141,  141,   43,   44,
 /*  1000 */    45,   46,   47,    1,   49,   50,  141,   13,   14,   15,
 /*  1010 */    16,   17,   18,   19,   20,   21,   22,   18,   19,    1,
 /*  1020 */     2,  141,   28,   24,   25,   26,   32,  141,  141,  141,
 /*  1030 */   141,   32,   38,   39,  141,  141,  141,   38,  141,   40,
 /*  1040 */    41,  141,   43,   44,   45,   46,   47,  141,  141,  141,
 /*  1050 */    32,  141,  141,   51,   52,   53,   54,   55,   56,   57,
 /*  1060 */    58,   59,   60,  141,  141,  141,  141,  141,  141,   51,
 /*  1070 */    52,   53,   54,   55,   56,   57,   58,   59,   60,  141,
 /*  1080 */   141,  141,  141,   13,   14,   15,   16,   17,   18,   19,
 /*  1090 */    20,   21,   22,  141,  141,  141,  141,  141,   28,  141,
 /*  1100 */   141,  141,   32,  141,  141,   81,  141,  141,   38,  141,
 /*  1110 */   141,  141,   13,   14,   15,   16,   17,   18,   19,   20,
 /*  1120 */    21,   22,  141,   99,  100,  101,  102,   28,  141,  141,
 /*  1130 */   141,   32,   18,   19,  141,  141,  112,   38,   24,   25,
 /*  1140 */    26,  141,  118,  119,  141,  141,   32,  141,  141,  141,
 /*  1150 */   141,  141,   38,  129,   40,  141,  141,   43,   44,   45,
 /*  1160 */    46,   47,  141,  141,  141,   18,   19,  141,  141,  141,
 /*  1170 */   141,   24,   25,   26,  141,  141,  141,  141,  141,   32,
 /*  1180 */   141,  141,  141,  141,  141,   38,  141,   40,  141,  141,
 /*  1190 */    43,   44,   45,   46,   47,   76,   77,   78,   79,   80,
 /*  1200 */    81,   82,   83,   84,  141,   86,  141,  141,   89,   90,
 /*  1210 */     1,    2,  141,  141,  141,   96,   14,   15,   16,   17,
 /*  1220 */    18,   19,   20,   21,   22,    1,    2,  141,  141,  141,
 /*  1230 */    28,  141,  141,  141,   32,  141,  141,  141,  141,  141,
 /*  1240 */    38,  141,  141,  141,  141,  141,  141,  141,  141,  141,
 /*  1250 */   141,  141,  141,  141,  141,  141,  141,  141,  141,  141,
 /*  1260 */    51,   52,   53,   54,   55,   56,   57,   58,   59,   60,
 /*  1270 */   141,  141,  141,  141,  141,   51,   52,   53,   54,   55,
 /*  1280 */    56,   57,   58,   59,   60,   15,   16,   17,   18,   19,
 /*  1290 */    20,   21,   22,  141,  141,  141,  141,  141,   28,   81,
 /*  1300 */   141,  141,   32,  141,  141,  141,  141,  141,   38,   16,
 /*  1310 */    17,   18,   19,   20,   21,   22,  141,   99,  100,  101,
 /*  1320 */   102,   28,  141,  141,  141,   32,  141,  141,  141,  141,
 /*  1330 */   112,   38,  141,  141,  141,  141,  118,  119,  141,  141,
 /*  1340 */   141,  141,  141,  141,  141,  141,  141,  129,  130,
};
#define YY_SHIFT_USE_DFLT (-19)
#define YY_SHIFT_COUNT (241)
#define YY_SHIFT_MIN   (-18)
#define YY_SHIFT_MAX   (1293)
static const short yy_shift_ofst[] = {
 /*     0 */   -19,  659,  597,  721,  721,  721,  721,  721,  721,  721,
 /*    10 */   721,   95,  829,  829,  955,  955,  922,  999,  999,  999,
 /*    20 */   999, 1114, 1114,  889,  889,  889,  889,  889,  889,  889,
 /*    30 */   889,  889,  999, 1114, 1114, 1114, 1114, 1147, 1114, 1114,
 /*    40 */  1114,  714, 1114, 1114, 1114, 1114, 1114, 1114, 1114, 1114,
 /*    50 */  1114, 1114, 1114, 1114, 1114, 1114, 1114, 1114, 1114, 1114,
 /*    60 */  1114, 1114, 1114, 1114, 1114, 1114, 1114, 1114, 1114, 1114,
 /*    70 */  1114, 1114, 1114, 1114, 1114, 1114, 1114, 1114,   65,  717,
 /*    80 */   687,  717,  717,  717,  717,  687,  687,  717,  717,  717,
 /*    90 */   735,  709,  656,  656,  666,  785,  818,  868,  994,  697,
 /*   100 */   635, 1070, 1070, 1099, 1070, 1070, 1070, 1070, 1070, 1070,
 /*   110 */  1070, 1070, 1070, 1070, 1070, 1070, 1070, 1070, 1070, 1070,
 /*   120 */  1070, 1070, 1070, 1070, 1018, 1224, 1209, 1202, 1002, 1270,
 /*   130 */  1293,  -17,  -17,  229,  229,  179,  172,  164,  161,  133,
 /*   140 */    41,  -18,  -18,  -18,  -18,  -18,  -18,  283,  217,  237,
 /*   150 */   191,  193,  160,   81,   24,    4,    6,  233,   23,  438,
 /*   160 */   438,  649,  654,  643,  645,  633,  644,  602,  603,  598,
 /*   170 */   595,  593,  587,  605,  579,  592,  561,  556,  555,  509,
 /*   180 */   536,  438,  438,  438,  540,  534,  531,  512,  530,  518,
 /*   190 */   533,  498,  497,  495,  485,  465,  461,  454,  464,  424,
 /*   200 */   453,  437,  411,  452,  462,  439,  415,  438,  404,  403,
 /*   210 */   340,  376,  375,  384,  362,  370,  380,  356,  343,  340,
 /*   220 */   280,  286,  348,  336,  335,  321,  320,  317,  293,  260,
 /*   230 */   246,  254,  227,  207,  166,  175,  155,   82,  147,   87,
 /*   240 */    12,  -14,
};
#define YY_REDUCE_USE_DFLT (-95)
#define YY_REDUCE_COUNT (94)
#define YY_REDUCE_MIN   (-94)
#define YY_REDUCE_MAX   (1218)
static const short yy_reduce_ofst[] = {
 /*     0 */   267,  477,  420,  354,  297,  231,  174,  108,   51,  -15,
 /*    10 */   -72, 1119, 1218, 1024,  -60,   -3,  397,  393,  274,  258,
 /*    20 */   151,  -35,  -94,  327,  310,  278,  244,  187,  135,  121,
 /*    30 */    32,  -42,  204,  334,  309,  243,  211,   15,  186,  120,
 /*    40 */    88,   17,  650,  648,  642,  639,  630,  619,  586,  578,
 /*    50 */   577,  570,  557,  526,  524,  507,  506,  490,  489,  488,
 /*    60 */   463,  457,  450,  433,  432,  431,  401,  398,  394,  381,
 /*    70 */   367,  366,  365,  339,  275,  272,   36,   -2,  236,  230,
 /*    80 */   152,  134,  684,  683,  682,  634,  625,  664,  658,  647,
 /*    90 */   620,  590,  636,  604,  596,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   353,  530,  530,  530,  530,  530,  530,  530,  530,  530,
 /*    10 */   530,  533,  509,  533,  512,  533,  533,  426,  426,  426,
 /*    20 */   426,  415,  415,  533,  533,  533,  533,  533,  533,  533,
 /*    30 */   533,  533,  533,  533,  533,  533,  533,  533,  533,  533,
 /*    40 */   533,  497,  533,  533,  533,  533,  533,  533,  533,  533,
 /*    50 */   533,  533,  533,  533,  533,  533,  533,  533,  533,  533,
 /*    60 */   533,  533,  533,  533,  533,  533,  533,  533,  533,  533,
 /*    70 */   533,  533,  533,  533,  533,  533,  533,  533,  533,  409,
 /*    80 */   533,  409,  533,  533,  533,  532,  531,  533,  533,  533,
 /*    90 */   433,  533,  533,  533,  533,  453,  453,  533,  533,  533,
 /*   100 */   533,  478,  476,  533,  489,  488,  487,  486,  485,  484,
 /*   110 */   483,  482,  481,  480,  474,  460,  459,  458,  457,  456,
 /*   120 */   455,  413,  422,  424,  419,  421,  420,  448,  472,  449,
 /*   130 */   447,  446,  445,  441,  440,  533,  533,  533,  533,  533,
 /*   140 */   533,  452,  451,  450,  444,  443,  442,  533,  464,  533,
 /*   150 */   533,  533,  533,  533,  464,  533,  419,  430,  366,  468,
 /*   160 */   466,  533,  533,  533,  533,  533,  533,  401,  533,  533,
 /*   170 */   533,  533,  533,  513,  533,  508,  533,  533,  533,  496,
 /*   180 */   533,  475,  467,  465,  533,  533,  533,  533,  533,  533,
 /*   190 */   462,  533,  533,  533,  533,  533,  533,  533,  533,  533,
 /*   200 */   533,  533,  533,  533,  427,  418,  533,  416,  533,  533,
 /*   210 */   405,  533,  430,  533,  419,  430,  533,  533,  533,  533,
 /*   220 */   533,  533,  533,  533,  533,  533,  533,  533,  533,  533,
 /*   230 */   533,  410,  367,  533,  533,  533,  533,  533,  533,  533,
 /*   240 */   533,  533,  376,  375,  374,  373,  372,  371,  370,  402,
 /*   250 */   386,  498,  529,  528,  527,  523,  522,  521,  520,  519,
 /*   260 */   518,  517,  516,  511,  510,  515,  514,  507,  506,  505,
 /*   270 */   504,  503,  502,  501,  500,  499,  495,  494,  493,  492,
 /*   280 */   491,  490,  473,  479,  477,  428,  429,  434,  432,  435,
 /*   290 */   526,  524,  463,  461,  454,  525,  439,  438,  437,  436,
 /*   300 */   425,  423,  414,  411,  406,  431,  421,  420,  418,  417,
 /*   310 */   404,  403,  400,  399,  398,  397,  396,  395,  394,  412,
 /*   320 */   393,  392,  391,  390,  389,  388,  387,  385,  384,  383,
 /*   330 */   381,  382,  380,  379,  378,  377,  368,  408,  407,  369,
 /*   340 */   365,  364,  363,  362,  361,  360,  359,  358,  357,  356,
 /*   350 */   355,  354,
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
  "PERIOD",        "IMPORT",        "AS",            "FUNCTION",    
  "LPAREN",        "RPAREN",        "OBJECT",        "LBRACKET",    
  "VAR",           "RBRACKET",      "LSQBRACKET",    "RSQBRACKET",  
  "KILLS",         "STRING",        "FUNCCALL",      "L2V",         
  "MAPSTRING",     "UNIT",          "SWITCH",        "LOCATION",    
  "CONST",         "INC",           "DEC",           "IADD",        
  "ISUB",          "IMUL",          "IDIV",          "IMOD",        
  "ILSH",          "IRSH",          "IBND",          "IBOR",        
  "IBXR",          "IF",            "ELSE",          "WHILE",       
  "FOR",           "FOREACH",       "COLON",         "CONTINUE",    
  "BREAK",         "RETURN",        "CONDITIONNAME",  "ACTIONNAME",  
  "error",         "nt",            "program",       "chunks",      
  "chunk",         "import_chunk",  "fdef_chunk",    "fdecl_chunk", 
  "object_chunk",  "vdef_stmt",     "vdefAssign_global_stmt",  "cdef_global_stmt",
  "blockStmt",     "dottedName",    "fdef_header",   "nameList",    
  "stmt",          "object_header",  "object_body",   "nameList_nonEmpty",
  "method_header",  "method_chunk",  "bodyStmt",      "return_stmt", 
  "lbracket",      "rbracket",      "bodyStmtList",  "vdefAssign_stmt",
  "cdef_stmt",     "assign_stmt",   "funcexpr",      "actionStmt",  
  "if_stmt",       "while_stmt",    "for_stmt",      "foreach_stmt",
  "continue_stmt",  "break_stmt",    "numList_nonEmpty",  "exprList_nonEmpty",
  "expr",          "exprList",      "fArgs_nonEmpty",  "fArgs",       
  "commaSkippable",  "lexpr",         "lvalue",        "lvalueList_nonEmpty",
  "if_start",      "if_header",     "if_block",      "elif_start",  
  "elif_header",   "else_header",   "while_start",   "while_header",
  "for_opener",    "for_init_stmt_nonEmpty",  "for_init_stmt",  "for_action_stmt_nonEmpty",
  "for_action_stmt",  "for_header1",   "for_header2",   "for_header",  
  "foreach_opener",  "foreach_header",  "action",        "actions",     
  "actionStmt_start",
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
 /*   5 */ "chunk ::= fdecl_chunk",
 /*   6 */ "chunk ::= object_chunk",
 /*   7 */ "chunk ::= vdef_stmt SEMICOLON",
 /*   8 */ "chunk ::= vdefAssign_global_stmt SEMICOLON",
 /*   9 */ "chunk ::= cdef_global_stmt SEMICOLON",
 /*  10 */ "chunk ::= blockStmt",
 /*  11 */ "dottedName ::= NAME",
 /*  12 */ "dottedName ::= dottedName PERIOD NAME",
 /*  13 */ "import_chunk ::= IMPORT dottedName AS NAME",
 /*  14 */ "import_chunk ::= IMPORT dottedName",
 /*  15 */ "fdef_header ::= FUNCTION NAME LPAREN nameList RPAREN",
 /*  16 */ "fdef_chunk ::= fdef_header stmt",
 /*  17 */ "fdecl_chunk ::= FUNCTION NAME LPAREN nameList RPAREN SEMICOLON",
 /*  18 */ "object_header ::= OBJECT NAME LBRACKET",
 /*  19 */ "object_body ::= object_header",
 /*  20 */ "object_body ::= object_body VAR nameList_nonEmpty SEMICOLON",
 /*  21 */ "method_header ::= FUNCTION NAME LPAREN nameList RPAREN",
 /*  22 */ "method_chunk ::= method_header stmt",
 /*  23 */ "object_body ::= object_body method_chunk",
 /*  24 */ "object_chunk ::= object_body RBRACKET SEMICOLON",
 /*  25 */ "stmt ::= error SEMICOLON",
 /*  26 */ "stmt ::= bodyStmt",
 /*  27 */ "stmt ::= return_stmt SEMICOLON",
 /*  28 */ "lbracket ::= LBRACKET",
 /*  29 */ "rbracket ::= RBRACKET",
 /*  30 */ "blockStmt ::= lbracket RBRACKET",
 /*  31 */ "blockStmt ::= lbracket return_stmt SEMICOLON rbracket",
 /*  32 */ "blockStmt ::= lbracket bodyStmtList rbracket",
 /*  33 */ "blockStmt ::= lbracket bodyStmtList return_stmt SEMICOLON rbracket",
 /*  34 */ "blockStmt ::= lbracket error RBRACKET",
 /*  35 */ "bodyStmt ::= blockStmt",
 /*  36 */ "bodyStmt ::= SEMICOLON",
 /*  37 */ "bodyStmt ::= vdef_stmt SEMICOLON",
 /*  38 */ "bodyStmt ::= vdefAssign_stmt SEMICOLON",
 /*  39 */ "bodyStmt ::= cdef_stmt SEMICOLON",
 /*  40 */ "bodyStmt ::= assign_stmt SEMICOLON",
 /*  41 */ "bodyStmt ::= funcexpr SEMICOLON",
 /*  42 */ "bodyStmt ::= actionStmt",
 /*  43 */ "bodyStmt ::= if_stmt",
 /*  44 */ "bodyStmt ::= while_stmt",
 /*  45 */ "bodyStmt ::= for_stmt",
 /*  46 */ "bodyStmt ::= foreach_stmt",
 /*  47 */ "bodyStmt ::= continue_stmt SEMICOLON",
 /*  48 */ "bodyStmt ::= break_stmt SEMICOLON",
 /*  49 */ "bodyStmtList ::= error",
 /*  50 */ "bodyStmtList ::= bodyStmt",
 /*  51 */ "bodyStmtList ::= bodyStmtList bodyStmt",
 /*  52 */ "bodyStmtList ::= bodyStmtList error",
 /*  53 */ "numList_nonEmpty ::= NUMBER",
 /*  54 */ "numList_nonEmpty ::= numList_nonEmpty COMMA NUMBER",
 /*  55 */ "nameList_nonEmpty ::= NAME",
 /*  56 */ "nameList_nonEmpty ::= nameList_nonEmpty COMMA NAME",
 /*  57 */ "nameList ::=",
 /*  58 */ "nameList ::= nameList_nonEmpty",
 /*  59 */ "exprList_nonEmpty ::= funcexpr LSQBRACKET LSQBRACKET numList_nonEmpty RSQBRACKET RSQBRACKET",
 /*  60 */ "expr ::= funcexpr LSQBRACKET LSQBRACKET NUMBER RSQBRACKET RSQBRACKET",
 /*  61 */ "exprList_nonEmpty ::= expr",
 /*  62 */ "exprList_nonEmpty ::= exprList_nonEmpty COMMA exprList_nonEmpty",
 /*  63 */ "exprList ::=",
 /*  64 */ "exprList ::= exprList_nonEmpty",
 /*  65 */ "expr ::= NUMBER",
 /*  66 */ "expr ::= KILLS",
 /*  67 */ "expr ::= NAME",
 /*  68 */ "expr ::= expr PERIOD NAME",
 /*  69 */ "expr ::= expr LSQBRACKET expr RSQBRACKET",
 /*  70 */ "fArgs_nonEmpty ::= expr",
 /*  71 */ "fArgs_nonEmpty ::= STRING",
 /*  72 */ "fArgs_nonEmpty ::= NAME ASSIGN expr",
 /*  73 */ "fArgs_nonEmpty ::= fArgs_nonEmpty COMMA fArgs_nonEmpty",
 /*  74 */ "fArgs ::=",
 /*  75 */ "fArgs ::= fArgs_nonEmpty",
 /*  76 */ "funcexpr ::= NAME LPAREN fArgs RPAREN",
 /*  77 */ "funcexpr ::= expr LPAREN fArgs RPAREN",
 /*  78 */ "expr ::= funcexpr",
 /*  79 */ "expr ::= LPAREN expr RPAREN",
 /*  80 */ "commaSkippable ::= COMMA",
 /*  81 */ "commaSkippable ::=",
 /*  82 */ "expr ::= LSQBRACKET exprList commaSkippable RSQBRACKET",
 /*  83 */ "expr ::= L2V LPAREN lexpr RPAREN",
 /*  84 */ "expr ::= MAPSTRING LPAREN STRING RPAREN",
 /*  85 */ "expr ::= UNIT LPAREN STRING RPAREN",
 /*  86 */ "expr ::= SWITCH LPAREN STRING RPAREN",
 /*  87 */ "expr ::= LOCATION LPAREN STRING RPAREN",
 /*  88 */ "expr ::= expr PLUS expr",
 /*  89 */ "expr ::= expr MINUS expr",
 /*  90 */ "expr ::= expr MULTIPLY expr",
 /*  91 */ "expr ::= expr DIVIDE expr",
 /*  92 */ "expr ::= expr MOD expr",
 /*  93 */ "expr ::= expr LSHIFT expr",
 /*  94 */ "expr ::= expr RSHIFT expr",
 /*  95 */ "expr ::= expr BITAND expr",
 /*  96 */ "expr ::= expr BITOR expr",
 /*  97 */ "expr ::= expr BITXOR expr",
 /*  98 */ "expr ::= PLUS expr",
 /*  99 */ "expr ::= MINUS expr",
 /* 100 */ "expr ::= BITNOT expr",
 /* 101 */ "lexpr ::= expr",
 /* 102 */ "lexpr ::= LPAREN lexpr RPAREN",
 /* 103 */ "lexpr ::= expr EQ expr",
 /* 104 */ "lexpr ::= expr NE expr",
 /* 105 */ "lexpr ::= expr LE expr",
 /* 106 */ "lexpr ::= expr LT expr",
 /* 107 */ "lexpr ::= expr GE expr",
 /* 108 */ "lexpr ::= expr GT expr",
 /* 109 */ "lexpr ::= lexpr LAND lexpr",
 /* 110 */ "lexpr ::= lexpr LOR lexpr",
 /* 111 */ "lexpr ::= LNOT lexpr",
 /* 112 */ "vdef_stmt ::= VAR nameList_nonEmpty",
 /* 113 */ "vdefAssign_stmt ::= VAR nameList_nonEmpty ASSIGN exprList_nonEmpty",
 /* 114 */ "vdefAssign_global_stmt ::= VAR nameList_nonEmpty ASSIGN exprList_nonEmpty",
 /* 115 */ "cdef_stmt ::= CONST nameList_nonEmpty ASSIGN exprList_nonEmpty",
 /* 116 */ "cdef_global_stmt ::= CONST nameList_nonEmpty ASSIGN exprList_nonEmpty",
 /* 117 */ "lvalue ::= NAME",
 /* 118 */ "lvalue ::= expr LSQBRACKET expr RSQBRACKET",
 /* 119 */ "lvalue ::= expr PERIOD NAME",
 /* 120 */ "lvalueList_nonEmpty ::= lvalue",
 /* 121 */ "lvalueList_nonEmpty ::= lvalueList_nonEmpty COMMA lvalue",
 /* 122 */ "assign_stmt ::= lvalue ASSIGN expr",
 /* 123 */ "assign_stmt ::= lvalueList_nonEmpty ASSIGN exprList_nonEmpty",
 /* 124 */ "assign_stmt ::= INC expr",
 /* 125 */ "assign_stmt ::= expr INC",
 /* 126 */ "assign_stmt ::= DEC expr",
 /* 127 */ "assign_stmt ::= expr DEC",
 /* 128 */ "assign_stmt ::= lvalue IADD expr",
 /* 129 */ "assign_stmt ::= lvalue ISUB expr",
 /* 130 */ "assign_stmt ::= lvalue IMUL expr",
 /* 131 */ "assign_stmt ::= lvalue IDIV expr",
 /* 132 */ "assign_stmt ::= lvalue IMOD expr",
 /* 133 */ "assign_stmt ::= lvalue ILSH expr",
 /* 134 */ "assign_stmt ::= lvalue IRSH expr",
 /* 135 */ "assign_stmt ::= lvalue IBND expr",
 /* 136 */ "assign_stmt ::= lvalue IBOR expr",
 /* 137 */ "assign_stmt ::= lvalue IBXR expr",
 /* 138 */ "if_start ::= IF",
 /* 139 */ "if_header ::= if_start LPAREN lexpr RPAREN",
 /* 140 */ "if_block ::= if_header stmt",
 /* 141 */ "elif_start ::= ELSE IF",
 /* 142 */ "elif_header ::= elif_start LPAREN lexpr RPAREN",
 /* 143 */ "if_block ::= if_block elif_header stmt",
 /* 144 */ "else_header ::= ELSE",
 /* 145 */ "if_stmt ::= if_block",
 /* 146 */ "if_stmt ::= if_block else_header stmt",
 /* 147 */ "while_start ::= WHILE",
 /* 148 */ "while_header ::= while_start LPAREN lexpr RPAREN",
 /* 149 */ "while_stmt ::= while_header stmt",
 /* 150 */ "for_opener ::= FOR LPAREN",
 /* 151 */ "for_init_stmt_nonEmpty ::= vdef_stmt",
 /* 152 */ "for_init_stmt_nonEmpty ::= vdefAssign_stmt",
 /* 153 */ "for_init_stmt_nonEmpty ::= cdef_stmt",
 /* 154 */ "for_init_stmt_nonEmpty ::= assign_stmt",
 /* 155 */ "for_init_stmt_nonEmpty ::= for_init_stmt_nonEmpty COMMA for_init_stmt_nonEmpty",
 /* 156 */ "for_init_stmt ::= for_init_stmt_nonEmpty",
 /* 157 */ "for_init_stmt ::=",
 /* 158 */ "for_action_stmt_nonEmpty ::= assign_stmt",
 /* 159 */ "for_action_stmt_nonEmpty ::= for_action_stmt_nonEmpty COMMA for_action_stmt_nonEmpty",
 /* 160 */ "for_action_stmt ::=",
 /* 161 */ "for_action_stmt ::= for_action_stmt_nonEmpty",
 /* 162 */ "for_header1 ::= for_opener for_init_stmt SEMICOLON",
 /* 163 */ "for_header2 ::= for_header1 lexpr SEMICOLON",
 /* 164 */ "for_header ::= for_header2 for_action_stmt RPAREN",
 /* 165 */ "for_stmt ::= for_header stmt",
 /* 166 */ "foreach_opener ::= FOREACH LPAREN",
 /* 167 */ "foreach_header ::= foreach_opener nameList_nonEmpty COLON exprList_nonEmpty RPAREN",
 /* 168 */ "foreach_stmt ::= foreach_header stmt",
 /* 169 */ "continue_stmt ::= CONTINUE",
 /* 170 */ "break_stmt ::= BREAK",
 /* 171 */ "return_stmt ::= RETURN exprList",
 /* 172 */ "lexpr ::= CONDITIONNAME LPAREN fArgs RPAREN",
 /* 173 */ "lexpr ::= KILLS LPAREN fArgs RPAREN",
 /* 174 */ "lexpr ::= CONDITIONNAME LPAREN RPAREN",
 /* 175 */ "action ::= ACTIONNAME LPAREN fArgs RPAREN SEMICOLON",
 /* 176 */ "actions ::= action action",
 /* 177 */ "actions ::= actions action",
 /* 178 */ "actionStmt_start ::=",
 /* 179 */ "actionStmt ::= actionStmt_start action",
 /* 180 */ "actionStmt ::= actionStmt_start actions",
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
    case 73: /* nt */
{
#line 40 "parser\\epparser.lemon"
 delete (yypminor->yy0); 
#line 933 "parser\\epparser.c"
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
  { 74, 1 },
  { 75, 0 },
  { 75, 2 },
  { 76, 2 },
  { 76, 1 },
  { 76, 1 },
  { 76, 1 },
  { 76, 2 },
  { 76, 2 },
  { 76, 2 },
  { 76, 1 },
  { 85, 1 },
  { 85, 3 },
  { 77, 4 },
  { 77, 2 },
  { 86, 5 },
  { 78, 2 },
  { 79, 6 },
  { 89, 3 },
  { 90, 1 },
  { 90, 4 },
  { 92, 5 },
  { 93, 2 },
  { 90, 2 },
  { 80, 3 },
  { 88, 2 },
  { 88, 1 },
  { 88, 2 },
  { 96, 1 },
  { 97, 1 },
  { 84, 2 },
  { 84, 4 },
  { 84, 3 },
  { 84, 5 },
  { 84, 3 },
  { 94, 1 },
  { 94, 1 },
  { 94, 2 },
  { 94, 2 },
  { 94, 2 },
  { 94, 2 },
  { 94, 2 },
  { 94, 1 },
  { 94, 1 },
  { 94, 1 },
  { 94, 1 },
  { 94, 1 },
  { 94, 2 },
  { 94, 2 },
  { 98, 1 },
  { 98, 1 },
  { 98, 2 },
  { 98, 2 },
  { 110, 1 },
  { 110, 3 },
  { 91, 1 },
  { 91, 3 },
  { 87, 0 },
  { 87, 1 },
  { 111, 6 },
  { 112, 6 },
  { 111, 1 },
  { 111, 3 },
  { 113, 0 },
  { 113, 1 },
  { 112, 1 },
  { 112, 1 },
  { 112, 1 },
  { 112, 3 },
  { 112, 4 },
  { 114, 1 },
  { 114, 1 },
  { 114, 3 },
  { 114, 3 },
  { 115, 0 },
  { 115, 1 },
  { 102, 4 },
  { 102, 4 },
  { 112, 1 },
  { 112, 3 },
  { 116, 1 },
  { 116, 0 },
  { 112, 4 },
  { 112, 4 },
  { 112, 4 },
  { 112, 4 },
  { 112, 4 },
  { 112, 4 },
  { 112, 3 },
  { 112, 3 },
  { 112, 3 },
  { 112, 3 },
  { 112, 3 },
  { 112, 3 },
  { 112, 3 },
  { 112, 3 },
  { 112, 3 },
  { 112, 3 },
  { 112, 2 },
  { 112, 2 },
  { 112, 2 },
  { 117, 1 },
  { 117, 3 },
  { 117, 3 },
  { 117, 3 },
  { 117, 3 },
  { 117, 3 },
  { 117, 3 },
  { 117, 3 },
  { 117, 3 },
  { 117, 3 },
  { 117, 2 },
  { 81, 2 },
  { 99, 4 },
  { 82, 4 },
  { 100, 4 },
  { 83, 4 },
  { 118, 1 },
  { 118, 4 },
  { 118, 3 },
  { 119, 1 },
  { 119, 3 },
  { 101, 3 },
  { 101, 3 },
  { 101, 2 },
  { 101, 2 },
  { 101, 2 },
  { 101, 2 },
  { 101, 3 },
  { 101, 3 },
  { 101, 3 },
  { 101, 3 },
  { 101, 3 },
  { 101, 3 },
  { 101, 3 },
  { 101, 3 },
  { 101, 3 },
  { 101, 3 },
  { 120, 1 },
  { 121, 4 },
  { 122, 2 },
  { 123, 2 },
  { 124, 4 },
  { 122, 3 },
  { 125, 1 },
  { 104, 1 },
  { 104, 3 },
  { 126, 1 },
  { 127, 4 },
  { 105, 2 },
  { 128, 2 },
  { 129, 1 },
  { 129, 1 },
  { 129, 1 },
  { 129, 1 },
  { 129, 3 },
  { 130, 1 },
  { 130, 0 },
  { 131, 1 },
  { 131, 3 },
  { 132, 0 },
  { 132, 1 },
  { 133, 3 },
  { 134, 3 },
  { 135, 3 },
  { 106, 2 },
  { 136, 2 },
  { 137, 5 },
  { 107, 2 },
  { 108, 1 },
  { 109, 1 },
  { 95, 2 },
  { 117, 4 },
  { 117, 4 },
  { 117, 3 },
  { 138, 5 },
  { 139, 2 },
  { 139, 2 },
  { 140, 0 },
  { 103, 2 },
  { 103, 2 },
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
      case 10: /* chunk ::= blockStmt */
#line 76 "parser\\epparser.lemon"
{
    throw_error(48993, "Misplaced block statement");
}
#line 1411 "parser\\epparser.c"
        break;
      case 11: /* dottedName ::= NAME */
      case 53: /* numList_nonEmpty ::= NUMBER */ yytestcase(yyruleno==53);
      case 55: /* nameList_nonEmpty ::= NAME */ yytestcase(yyruleno==55);
      case 58: /* nameList ::= nameList_nonEmpty */ yytestcase(yyruleno==58);
      case 61: /* exprList_nonEmpty ::= expr */ yytestcase(yyruleno==61);
      case 64: /* exprList ::= exprList_nonEmpty */ yytestcase(yyruleno==64);
      case 65: /* expr ::= NUMBER */ yytestcase(yyruleno==65);
      case 70: /* fArgs_nonEmpty ::= expr */ yytestcase(yyruleno==70);
      case 71: /* fArgs_nonEmpty ::= STRING */ yytestcase(yyruleno==71);
      case 75: /* fArgs ::= fArgs_nonEmpty */ yytestcase(yyruleno==75);
      case 78: /* expr ::= funcexpr */ yytestcase(yyruleno==78);
      case 101: /* lexpr ::= expr */ yytestcase(yyruleno==101);
      case 120: /* lvalueList_nonEmpty ::= lvalue */ yytestcase(yyruleno==120);
#line 82 "parser\\epparser.lemon"
{ yygotominor.yy0 = yymsp[0].minor.yy0; }
#line 1428 "parser\\epparser.c"
        break;
      case 12: /* dottedName ::= dottedName PERIOD NAME */
#line 83 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = yymsp[-2].minor.yy0->data + "." + yymsp[0].minor.yy0->data;
    delete yymsp[-2].minor.yy0;
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1437 "parser\\epparser.c"
        break;
      case 13: /* import_chunk ::= IMPORT dottedName AS NAME */
#line 89 "parser\\epparser.lemon"
{
    std::string impPath, impModname;
    impPathProcess(yymsp[-2].minor.yy0->data, impPath, impModname);

    if(!ps->closure.defModule(yymsp[0].minor.yy0->data)) {
        throw_error(6754, "Importing already-declared module " + yymsp[0].minor.yy0->data, yymsp[0].minor.yy0->line);
    }

    if(!impPath.empty()) ps->gen << "from " << impPath << " ";
    ps->gen << "import " << impModname << " as " << yymsp[0].minor.yy0->data << std::endl;
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 1453 "parser\\epparser.c"
        break;
      case 14: /* import_chunk ::= IMPORT dottedName */
#line 102 "parser\\epparser.lemon"
{
    std::string impPath, impModname;
    impPathProcess(yymsp[0].minor.yy0->data, impPath, impModname);

    if(!ps->closure.defModule(impModname)) {
        throw_error(6754, "Importing already-declared module " + impModname, yymsp[0].minor.yy0->line);
    }

    if(!impPath.empty()) ps->gen << "from " << impPath << " ";
    ps->gen << "import " << impModname << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 1469 "parser\\epparser.c"
        break;
      case 15: /* fdef_header ::= FUNCTION NAME LPAREN nameList RPAREN */
#line 116 "parser\\epparser.lemon"
{
    // Preprocess yymsp[-3].minor.yy0
    funcNamePreprocess(yymsp[-3].minor.yy0->data);
    if(!ps->closure.defFunction(yymsp[-3].minor.yy0->data)) {
        throw_error(4495, "Duplicate function " + yymsp[-3].minor.yy0->data, yymsp[-3].minor.yy0->line);
    }

    ps->gen << "@EUDFunc" << std::endl;
    ps->gen << "def " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data << "):" << std::endl;
    ps->gen.indent();

    ps->closure.pushScope();
    currentFunction = yymsp[-3].minor.yy0->data;

    if(MAP_DEBUG) {
         ps->gen << "MDBG_PUSHF(\'" << currentFunction << "\', \'" << currentModule << "\')" << std::endl;
    }

    // Register variables.
    commaListIter(yymsp[-1].minor.yy0->data, [&](std::string& varname) {
        if(!ps->closure.defVariable(varname)) {
            throw_error(196, ("Redeclaration of variable \'" + varname + "\'"), yymsp[-1].minor.yy0->line);
        }
    });

    tmpIndex = 1;
    delete yymsp[-3].minor.yy0;
    delete yymsp[-1].minor.yy0;
}
#line 1502 "parser\\epparser.c"
        break;
      case 16: /* fdef_chunk ::= fdef_header stmt */
#line 146 "parser\\epparser.lemon"
{
    if(MAP_DEBUG){
        ps->gen << "MDBG_POPF()" << std::endl;
    }
    ps->gen.unindent(true);
    ps->closure.popScope();
    currentFunction = "";
}
#line 1514 "parser\\epparser.c"
        break;
      case 17: /* fdecl_chunk ::= FUNCTION NAME LPAREN nameList RPAREN SEMICOLON */
#line 155 "parser\\epparser.lemon"
{
    // Preprocess yymsp[-4].minor.yy0
    funcNamePreprocess(yymsp[-4].minor.yy0->data);
    if(!ps->closure.declareFunction(yymsp[-4].minor.yy0->data)) {
        throw_error(72461, "Declaring function with non-function yymsp[-4].minor.yy0 " + yymsp[-4].minor.yy0->data, yymsp[-4].minor.yy0->line);
    }
}
#line 1525 "parser\\epparser.c"
        break;
      case 18: /* object_header ::= OBJECT NAME LBRACKET */
#line 166 "parser\\epparser.lemon"
{
    ps->gen << "class " << yymsp[-1].minor.yy0->data << "(EUDStruct):\n";
    ps->gen.indent();

    funcNamePreprocess(yymsp[-1].minor.yy0->data);
    if(!ps->closure.declareFunction(yymsp[-1].minor.yy0->data)) {
        throw_error(8228, "Declaring object with non-function yymsp[-1].minor.yy0 " + yymsp[-1].minor.yy0->data, yymsp[-1].minor.yy0->line);
    }
    ps->closure.pushScope();

    yygotominor.yy0 = yymsp[-2].minor.yy0;
    yygotominor.yy0->data = yymsp[-1].minor.yy0->data;  // Add object yymsp[-1].minor.yy0
    delete yymsp[-1].minor.yy0;
}
#line 1543 "parser\\epparser.c"
        break;
      case 19: /* object_body ::= object_header */
#line 181 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1550 "parser\\epparser.c"
        break;
      case 20: /* object_body ::= object_body VAR nameList_nonEmpty SEMICOLON */
#line 185 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-3].minor.yy0;
    yygotominor.yy0->line = yymsp[-1].minor.yy0->line;
    yygotominor.yy0->data += ", " + yymsp[-1].minor.yy0->data;
    delete yymsp[-1].minor.yy0;
}
#line 1560 "parser\\epparser.c"
        break;
      case 21: /* method_header ::= FUNCTION NAME LPAREN nameList RPAREN */
#line 192 "parser\\epparser.lemon"
{
    // Method can't be called directly, so we shouldn't have to register it to closure.
    // duplicate method names should be checked at python-compile time.

    ps->gen << "@EUDMethod" << std::endl;

    ps->closure.pushScope();
    // Register variables.
    std::string _this = "this";  // This may be modified...?
    if(!ps->closure.defConstant(_this)) {
        throw_error(656, ("Redeclaration of variable \'this\'"), yymsp[-1].minor.yy0->line);
    }
    commaListIter(yymsp[-1].minor.yy0->data, [&](std::string& varname) {
        if(!ps->closure.defVariable(varname)) {
            throw_error(2656, ("Redeclaration of variable \'" + varname + "\'"), yymsp[-1].minor.yy0->line);
        }
    });

    // Add default argument 'self'
    if (yymsp[-1].minor.yy0->data.size() != 0) {
        ps->gen << "def " << yymsp[-3].minor.yy0->data << "(" << _this << ", " << yymsp[-1].minor.yy0->data << "):" << std::endl;
    } else {
        ps->gen << "def " << yymsp[-3].minor.yy0->data << "(" << _this << "):" << std::endl;
    }
    ps->gen.indent();

    currentFunction = yymsp[-3].minor.yy0->data;

    if(MAP_DEBUG) {
         ps->gen << "MDBG_PUSHF(\'" << currentFunction << "\', \'" << currentModule << "\')" << std::endl;
    }

    tmpIndex = 1;
    delete yymsp[-1].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 1600 "parser\\epparser.c"
        break;
      case 22: /* method_chunk ::= method_header stmt */
#line 229 "parser\\epparser.lemon"
{
    if(MAP_DEBUG){
        ps->gen << "MDBG_POPF()" << std::endl;
    }
    ps->gen.unindent(true);
    ps->closure.popScope();
    currentFunction = "";
    yygotominor.yy0 = yymsp[-1].minor.yy0;
}
#line 1613 "parser\\epparser.c"
        break;
      case 23: /* object_body ::= object_body method_chunk */
#line 239 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
    yygotominor.yy0->line = yymsp[0].minor.yy0->line;
    delete yymsp[0].minor.yy0;
}
#line 1622 "parser\\epparser.c"
        break;
      case 24: /* object_chunk ::= object_body RBRACKET SEMICOLON */
#line 245 "parser\\epparser.lemon"
{
    ps->gen << "_fields_ = [";
    bool isFirst = true;
    commaListIter(yymsp[-2].minor.yy0->data, [&](std::string& varname) {
        if (isFirst) {
            isFirst = false;
            return;
        }
        ps->gen << "'" << varname << "', ";
    });
    ps->gen << "]\n";
    ps->gen.unindent(true);
    ps->closure.popScope();
    delete yymsp[-2].minor.yy0;
}
#line 1641 "parser\\epparser.c"
        break;
      case 25: /* stmt ::= error SEMICOLON */
#line 262 "parser\\epparser.lemon"
{ throw_error(6974, "Error while parsing statement", yymsp[0].minor.yy0->line); delete yymsp[0].minor.yy0; }
#line 1646 "parser\\epparser.c"
        break;
      case 28: /* lbracket ::= LBRACKET */
#line 268 "parser\\epparser.lemon"
{ ps->closure.pushScope(); }
#line 1651 "parser\\epparser.c"
        break;
      case 29: /* rbracket ::= RBRACKET */
#line 269 "parser\\epparser.lemon"
{ ps->closure.popScope(); }
#line 1656 "parser\\epparser.c"
        break;
      case 30: /* blockStmt ::= lbracket RBRACKET */
#line 271 "parser\\epparser.lemon"
{
    ps->closure.popScope();
}
#line 1663 "parser\\epparser.c"
        break;
      case 34: /* blockStmt ::= lbracket error RBRACKET */
#line 277 "parser\\epparser.lemon"
{
    throw_error(6298, "Block not terminated properly.", yymsp[0].minor.yy0->line);
    ps->closure.popScope();
    delete yymsp[0].minor.yy0;
}
#line 1672 "parser\\epparser.c"
        break;
      case 41: /* bodyStmt ::= funcexpr SEMICOLON */
#line 289 "parser\\epparser.lemon"
{ ps->gen << yymsp[-1].minor.yy0->data << std::endl; }
#line 1677 "parser\\epparser.c"
        break;
      case 49: /* bodyStmtList ::= error */
      case 52: /* bodyStmtList ::= bodyStmtList error */ yytestcase(yyruleno==52);
#line 299 "parser\\epparser.lemon"
{
    throw_error(8510, "Incomplete statement");
}
#line 1685 "parser\\epparser.c"
        break;
      case 54: /* numList_nonEmpty ::= numList_nonEmpty COMMA NUMBER */
      case 56: /* nameList_nonEmpty ::= nameList_nonEmpty COMMA NAME */ yytestcase(yyruleno==56);
      case 121: /* lvalueList_nonEmpty ::= lvalueList_nonEmpty COMMA lvalue */ yytestcase(yyruleno==121);
#line 312 "parser\\epparser.lemon"
{ yygotominor.yy0 = commaConcat(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1692 "parser\\epparser.c"
        break;
      case 57: /* nameList ::= */
      case 63: /* exprList ::= */ yytestcase(yyruleno==63);
      case 74: /* fArgs ::= */ yytestcase(yyruleno==74);
#line 315 "parser\\epparser.lemon"
{ yygotominor.yy0 = genEmpty(); }
#line 1699 "parser\\epparser.c"
        break;
      case 59: /* exprList_nonEmpty ::= funcexpr LSQBRACKET LSQBRACKET numList_nonEmpty RSQBRACKET RSQBRACKET */
#line 318 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "_SRET(" + yymsp[-5].minor.yy0->data + ", [" + yymsp[-2].minor.yy0->data + "])";
    delete yymsp[-5].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1708 "parser\\epparser.c"
        break;
      case 60: /* expr ::= funcexpr LSQBRACKET LSQBRACKET NUMBER RSQBRACKET RSQBRACKET */
#line 325 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-5].minor.yy0->data + "[" + yymsp[-2].minor.yy0->data + "]";
    delete yymsp[-5].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1717 "parser\\epparser.c"
        break;
      case 62: /* exprList_nonEmpty ::= exprList_nonEmpty COMMA exprList_nonEmpty */
#line 333 "parser\\epparser.lemon"
{ yygotominor.yy0 = new Token((yymsp[-2].minor.yy0->data) + ", " + (yymsp[0].minor.yy0->data), yymsp[0].minor.yy0); delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1722 "parser\\epparser.c"
        break;
      case 66: /* expr ::= KILLS */
#line 340 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = "4";
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1730 "parser\\epparser.c"
        break;
      case 67: /* expr ::= NAME */
#line 345 "parser\\epparser.lemon"
{
    checkIsRValue(yymsp[0].minor.yy0->data, yymsp[0].minor.yy0->line);
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1738 "parser\\epparser.c"
        break;
      case 68: /* expr ::= expr PERIOD NAME */
#line 350 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + "." + yymsp[0].minor.yy0->data;
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1747 "parser\\epparser.c"
        break;
      case 69: /* expr ::= expr LSQBRACKET expr RSQBRACKET */
#line 356 "parser\\epparser.lemon"
{
    yymsp[-3].minor.yy0->data = yymsp[-3].minor.yy0->data + "[" + yymsp[-1].minor.yy0->data + "]";
    delete yymsp[-1].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 1756 "parser\\epparser.c"
        break;
      case 72: /* fArgs_nonEmpty ::= NAME ASSIGN expr */
#line 365 "parser\\epparser.lemon"
{  // Keyword argument
    yymsp[0].minor.yy0->data = yymsp[-2].minor.yy0->data + "=" + yymsp[0].minor.yy0->data;
    yymsp[0].minor.yy0->type = TOKEN_TEMP;
    yygotominor.yy0 = yymsp[0].minor.yy0;
    delete yymsp[-2].minor.yy0;
}
#line 1766 "parser\\epparser.c"
        break;
      case 73: /* fArgs_nonEmpty ::= fArgs_nonEmpty COMMA fArgs_nonEmpty */
#line 372 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data;
    yymsp[0].minor.yy0->type = TOKEN_TEMP;
    yygotominor.yy0 = yymsp[0].minor.yy0;
    delete yymsp[-2].minor.yy0;
}
#line 1776 "parser\\epparser.c"
        break;
      case 76: /* funcexpr ::= NAME LPAREN fArgs RPAREN */
#line 382 "parser\\epparser.lemon"
{
    functionCalledInMultipleActions = true;

    // Preprocess yymsp[-3].minor.yy0
    funcNamePreprocess(yymsp[-3].minor.yy0->data);
    checkIsFunction(yymsp[-3].minor.yy0->data, yymsp[-3].minor.yy0->line);
    yymsp[-3].minor.yy0->data += "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 1789 "parser\\epparser.c"
        break;
      case 77: /* funcexpr ::= expr LPAREN fArgs RPAREN */
#line 392 "parser\\epparser.lemon"
{
    functionCalledInMultipleActions = true;

    // If calling function imported from another module, add f_ prefix to function yymsp[-3].minor.yy0.
    static std::regex prefixedFuncNameRegex("^[a-z][_a-zA-Z0-9]*");
    std::string& nameStr = yymsp[-3].minor.yy0->data;
    if(std::count(nameStr.begin(), nameStr.end(), '.') == 1) {
        size_t p = nameStr.find('.');
        std::string moduleName = nameStr.substr(0, p);
        std::string funcName = nameStr.substr(p + 1);
        if (closure->isModule(moduleName) && std::regex_match(funcName, prefixedFuncNameRegex)) {
            funcNamePreprocess(funcName);
            yymsp[-3].minor.yy0->data = moduleName + '.' + funcName;
        }
    }

    // Preprocess yymsp[-3].minor.yy0
    yymsp[-3].minor.yy0->data += "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 1813 "parser\\epparser.c"
        break;
      case 79: /* expr ::= LPAREN expr RPAREN */
      case 102: /* lexpr ::= LPAREN lexpr RPAREN */ yytestcase(yyruleno==102);
#line 420 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1822 "parser\\epparser.c"
        break;
      case 82: /* expr ::= LSQBRACKET exprList commaSkippable RSQBRACKET */
#line 428 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "_ARR(FlattenList([" + yymsp[-2].minor.yy0->data + "]))";
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1830 "parser\\epparser.c"
        break;
      case 83: /* expr ::= L2V LPAREN lexpr RPAREN */
#line 433 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "_L2V(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1838 "parser\\epparser.c"
        break;
      case 84: /* expr ::= MAPSTRING LPAREN STRING RPAREN */
#line 438 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetStringIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1846 "parser\\epparser.c"
        break;
      case 85: /* expr ::= UNIT LPAREN STRING RPAREN */
#line 443 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "EncodeUnit(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1854 "parser\\epparser.c"
        break;
      case 86: /* expr ::= SWITCH LPAREN STRING RPAREN */
#line 448 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "EncodeSwitch(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1862 "parser\\epparser.c"
        break;
      case 87: /* expr ::= LOCATION LPAREN STRING RPAREN */
#line 453 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetLocationIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1870 "parser\\epparser.c"
        break;
      case 88: /* expr ::= expr PLUS expr */
#line 459 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "+",  yymsp[0].minor.yy0); }
#line 1875 "parser\\epparser.c"
        break;
      case 89: /* expr ::= expr MINUS expr */
#line 460 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "-",  yymsp[0].minor.yy0); }
#line 1880 "parser\\epparser.c"
        break;
      case 90: /* expr ::= expr MULTIPLY expr */
#line 461 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "*",  yymsp[0].minor.yy0); }
#line 1885 "parser\\epparser.c"
        break;
      case 91: /* expr ::= expr DIVIDE expr */
#line 462 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "//", yymsp[0].minor.yy0); }
#line 1890 "parser\\epparser.c"
        break;
      case 92: /* expr ::= expr MOD expr */
#line 463 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "%",  yymsp[0].minor.yy0); }
#line 1895 "parser\\epparser.c"
        break;
      case 93: /* expr ::= expr LSHIFT expr */
#line 464 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = "_LSH(" + yymsp[-2].minor.yy0->data + "," + yymsp[0].minor.yy0->data + ")";
    delete yymsp[-2].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0);
}
#line 1904 "parser\\epparser.c"
        break;
      case 94: /* expr ::= expr RSHIFT expr */
#line 469 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, ">>", yymsp[0].minor.yy0); }
#line 1909 "parser\\epparser.c"
        break;
      case 95: /* expr ::= expr BITAND expr */
#line 470 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "&",  yymsp[0].minor.yy0); }
#line 1914 "parser\\epparser.c"
        break;
      case 96: /* expr ::= expr BITOR expr */
#line 471 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "|",  yymsp[0].minor.yy0); }
#line 1919 "parser\\epparser.c"
        break;
      case 97: /* expr ::= expr BITXOR expr */
#line 472 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "^",  yymsp[0].minor.yy0); }
#line 1924 "parser\\epparser.c"
        break;
      case 98: /* expr ::= PLUS expr */
#line 475 "parser\\epparser.lemon"
{ yymsp[0].minor.yy0->data = "+" + yymsp[0].minor.yy0->data; yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0); }
#line 1929 "parser\\epparser.c"
        break;
      case 99: /* expr ::= MINUS expr */
#line 476 "parser\\epparser.lemon"
{ yymsp[0].minor.yy0->data = "-" + yymsp[0].minor.yy0->data; yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0); }
#line 1934 "parser\\epparser.c"
        break;
      case 100: /* expr ::= BITNOT expr */
#line 477 "parser\\epparser.lemon"
{ yymsp[0].minor.yy0->data = "~" + yymsp[0].minor.yy0->data; yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0); }
#line 1939 "parser\\epparser.c"
        break;
      case 103: /* lexpr ::= expr EQ expr */
#line 487 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "==", yymsp[0].minor.yy0); }
#line 1944 "parser\\epparser.c"
        break;
      case 104: /* lexpr ::= expr NE expr */
#line 488 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genEmpty();
    yygotominor.yy0->line = yymsp[0].minor.yy0->line;

    yygotominor.yy0->type = TOKEN_NE;
    yygotominor.yy0->subToken[0] = yymsp[-2].minor.yy0;
    yygotominor.yy0->subToken[1] = yymsp[0].minor.yy0;
    yygotominor.yy0->data = yymsp[-2].minor.yy0->data + " != " + yymsp[0].minor.yy0->data;
}
#line 1957 "parser\\epparser.c"
        break;
      case 105: /* lexpr ::= expr LE expr */
#line 498 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "<=", yymsp[0].minor.yy0); }
#line 1962 "parser\\epparser.c"
        break;
      case 106: /* lexpr ::= expr LT expr */
#line 499 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "<",  yymsp[0].minor.yy0); }
#line 1967 "parser\\epparser.c"
        break;
      case 107: /* lexpr ::= expr GE expr */
#line 500 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, ">=", yymsp[0].minor.yy0); }
#line 1972 "parser\\epparser.c"
        break;
      case 108: /* lexpr ::= expr GT expr */
#line 501 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, ">" , yymsp[0].minor.yy0); }
#line 1977 "parser\\epparser.c"
        break;
      case 109: /* lexpr ::= lexpr LAND lexpr */
#line 504 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genEmpty();
    yygotominor.yy0->line = yymsp[0].minor.yy0->line;

    // Generate data!
    yygotominor.yy0->type = TOKEN_LAND;
    yygotominor.yy0->subToken[0] = yymsp[-2].minor.yy0;
    yygotominor.yy0->subToken[1] = yymsp[0].minor.yy0;

    std::stringstream ss;
    ss << "EUDSCAnd()";
    shortCircuitCondListGetter(ss, yygotominor.yy0, TOKEN_LAND);
    ss << "()";
    yygotominor.yy0->data = ss.str();
}
#line 1996 "parser\\epparser.c"
        break;
      case 110: /* lexpr ::= lexpr LOR lexpr */
#line 521 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genEmpty();
    yygotominor.yy0->line = yymsp[0].minor.yy0->line;

    // Generate data!
    yygotominor.yy0->type = TOKEN_LOR;
    yygotominor.yy0->subToken[0] = yymsp[-2].minor.yy0;
    yygotominor.yy0->subToken[1] = yymsp[0].minor.yy0;

    std::stringstream ss;
    ss << "EUDSCOr()";
    shortCircuitCondListGetter(ss, yygotominor.yy0, TOKEN_LOR);
    ss << "()";
    yygotominor.yy0->data = ss.str();
}
#line 2015 "parser\\epparser.c"
        break;
      case 111: /* lexpr ::= LNOT lexpr */
#line 537 "parser\\epparser.lemon"
{
    if(yymsp[0].minor.yy0->type == TOKEN_LNOT) {
        yygotominor.yy0 = yymsp[0].minor.yy0->subToken[0];
        yymsp[0].minor.yy0->subToken[0] = nullptr;
        delete yymsp[0].minor.yy0;
    }
    else {
        yygotominor.yy0 = genEmpty();
        yygotominor.yy0->line = yymsp[0].minor.yy0->line;
        yygotominor.yy0->type = TOKEN_LNOT;
        yygotominor.yy0->data = "EUDNot(" + yymsp[0].minor.yy0->data + ")";
        yygotominor.yy0->subToken[0] = yymsp[0].minor.yy0;
    }
}
#line 2033 "parser\\epparser.c"
        break;
      case 112: /* vdef_stmt ::= VAR nameList_nonEmpty */
#line 554 "parser\\epparser.lemon"
{
    std::string& s = yymsp[0].minor.yy0->data;
    int varCount = std::count(s.begin(), s.end(), ',') + 1;

    // Register variables.
    commaListIter(s, [&](std::string& varname) {
        if(!ps->closure.defVariable(varname)) {
            throw_error(196, ("Redeclaration of variable \'" + varname + "\'"), yymsp[0].minor.yy0->line);
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
#line 2057 "parser\\epparser.c"
        break;
      case 113: /* vdefAssign_stmt ::= VAR nameList_nonEmpty ASSIGN exprList_nonEmpty */
#line 575 "parser\\epparser.lemon"
{
    std::string& s = yymsp[-2].minor.yy0->data;
    int varCount = std::count(s.begin(), s.end(), ',') + 1;

    // Register variables.
    commaListIter(s, [&](std::string& varname) {
        if(!ps->closure.defVariable(varname)) {
            throw_error(7998, ("Redeclaration of variable \'" + varname + "\'"), yymsp[-2].minor.yy0->line);
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
#line 2082 "parser\\epparser.c"
        break;
      case 114: /* vdefAssign_global_stmt ::= VAR nameList_nonEmpty ASSIGN exprList_nonEmpty */
#line 597 "parser\\epparser.lemon"
{
    std::string& s = yymsp[-2].minor.yy0->data;
    int varCount = std::count(s.begin(), s.end(), ',') + 1;

    // Register variables.
    commaListIter(s, [&](std::string& varname) {
        if(!ps->closure.defVariable(varname)) {
            throw_error(7998, ("Redeclaration of variable \'" + varname + "\'"), yymsp[-2].minor.yy0->line);
        }
    });

    ps->gen << s << " = EUDCreateVariables(" << varCount << ")" << std::endl;
    ps->gen << "_IGVA([" << s << "], lambda: [" << yymsp[0].minor.yy0->data << "])" << std::endl;

    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 2102 "parser\\epparser.c"
        break;
      case 115: /* cdef_stmt ::= CONST nameList_nonEmpty ASSIGN exprList_nonEmpty */
#line 614 "parser\\epparser.lemon"
{
    std::string& s = yymsp[-2].minor.yy0->data;
    int nameCount = std::count(s.begin(), s.end(), ',') + 1;

    // Register constants.
    commaListIter(s, [&](std::string& constname) {
        if(!ps->closure.defConstant(constname)) {
            throw_error(7719, ("Redeclaration of constant \'" + constname + "\'"), yymsp[-2].minor.yy0->line);
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
#line 2124 "parser\\epparser.c"
        break;
      case 116: /* cdef_global_stmt ::= CONST nameList_nonEmpty ASSIGN exprList_nonEmpty */
#line 633 "parser\\epparser.lemon"
{
    std::string& s = yymsp[-2].minor.yy0->data;
    int nameCount = std::count(s.begin(), s.end(), ',') + 1;

    // Register constants.
    commaListIter(s, [&](std::string& constname) {
        if(!ps->closure.defConstant(constname)) {
            throw_error(7719, ("Redeclaration of constant \'" + constname + "\'"), yymsp[-2].minor.yy0->line);
        }
    });
    if(nameCount == 1) {
        ps->gen << s << " = _CGFW(lambda: [" << yymsp[0].minor.yy0->data << "], 1)[0]" << std::endl;
    }
    else {
        ps->gen << s << " = List2Assignable(_CGFW(lambda: [" << yymsp[0].minor.yy0->data << "], nameCount))" << std::endl;
    }
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 2146 "parser\\epparser.c"
        break;
      case 117: /* lvalue ::= NAME */
#line 653 "parser\\epparser.lemon"
{
    checkIsVariable(yymsp[0].minor.yy0->data, yymsp[0].minor.yy0->line);
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 2154 "parser\\epparser.c"
        break;
      case 118: /* lvalue ::= expr LSQBRACKET expr RSQBRACKET */
#line 658 "parser\\epparser.lemon"
{
    checkIsConstant(yymsp[-3].minor.yy0->data, yymsp[-3].minor.yy0->line);
    yymsp[-1].minor.yy0->data = "_ARRW(" + yymsp[-3].minor.yy0->data + ", " + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
    delete yymsp[-3].minor.yy0;
}
#line 2164 "parser\\epparser.c"
        break;
      case 119: /* lvalue ::= expr PERIOD NAME */
#line 665 "parser\\epparser.lemon"
{
    checkIsConstant(yymsp[-2].minor.yy0->data, yymsp[-2].minor.yy0->line);
    yymsp[0].minor.yy0->data = "_ATTW(" + yymsp[-2].minor.yy0->data + ", '" + yymsp[0].minor.yy0->data + "')";
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0);
    delete yymsp[-2].minor.yy0;
}
#line 2174 "parser\\epparser.c"
        break;
      case 122: /* assign_stmt ::= lvalue ASSIGN expr */
#line 674 "parser\\epparser.lemon"
{
    ps->gen << yymsp[-2].minor.yy0->data << " << (" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 2182 "parser\\epparser.c"
        break;
      case 123: /* assign_stmt ::= lvalueList_nonEmpty ASSIGN exprList_nonEmpty */
#line 679 "parser\\epparser.lemon"
{
    ps->gen << "_SV([" << yymsp[-2].minor.yy0->data << "], [" << yymsp[0].minor.yy0->data << "])" << std::endl;
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 2190 "parser\\epparser.c"
        break;
      case 124: /* assign_stmt ::= INC expr */
#line 687 "parser\\epparser.lemon"
{ ps->gen << yymsp[0].minor.yy0->data << ".__iadd__(1)" << std::endl; delete yymsp[0].minor.yy0; }
#line 2195 "parser\\epparser.c"
        break;
      case 125: /* assign_stmt ::= expr INC */
#line 688 "parser\\epparser.lemon"
{ ps->gen << yymsp[-1].minor.yy0->data << ".__iadd__(1)" << std::endl; delete yymsp[-1].minor.yy0; }
#line 2200 "parser\\epparser.c"
        break;
      case 126: /* assign_stmt ::= DEC expr */
#line 689 "parser\\epparser.lemon"
{ ps->gen << yymsp[0].minor.yy0->data << ".__isub__(1)" << std::endl; delete yymsp[0].minor.yy0; }
#line 2205 "parser\\epparser.c"
        break;
      case 127: /* assign_stmt ::= expr DEC */
#line 690 "parser\\epparser.lemon"
{ ps->gen << yymsp[-1].minor.yy0->data << ".__isub__(1)" << std::endl; delete yymsp[-1].minor.yy0; }
#line 2210 "parser\\epparser.c"
        break;
      case 128: /* assign_stmt ::= lvalue IADD expr */
#line 691 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__iadd__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2215 "parser\\epparser.c"
        break;
      case 129: /* assign_stmt ::= lvalue ISUB expr */
#line 692 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__isub__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2220 "parser\\epparser.c"
        break;
      case 130: /* assign_stmt ::= lvalue IMUL expr */
#line 693 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__imul__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2225 "parser\\epparser.c"
        break;
      case 131: /* assign_stmt ::= lvalue IDIV expr */
#line 694 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ifloordiv__("  << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2230 "parser\\epparser.c"
        break;
      case 132: /* assign_stmt ::= lvalue IMOD expr */
#line 695 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__imod__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2235 "parser\\epparser.c"
        break;
      case 133: /* assign_stmt ::= lvalue ILSH expr */
#line 696 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ilshift__("    << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2240 "parser\\epparser.c"
        break;
      case 134: /* assign_stmt ::= lvalue IRSH expr */
#line 697 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__irshift__("    << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2245 "parser\\epparser.c"
        break;
      case 135: /* assign_stmt ::= lvalue IBND expr */
#line 698 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__iand__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2250 "parser\\epparser.c"
        break;
      case 136: /* assign_stmt ::= lvalue IBOR expr */
#line 699 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ior__("        << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2255 "parser\\epparser.c"
        break;
      case 137: /* assign_stmt ::= lvalue IBXR expr */
#line 700 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ixor__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2260 "parser\\epparser.c"
        break;
      case 138: /* if_start ::= IF */
#line 703 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDIf()" << std::endl;
}
#line 2268 "parser\\epparser.c"
        break;
      case 139: /* if_header ::= if_start LPAREN lexpr RPAREN */
      case 142: /* elif_header ::= elif_start LPAREN lexpr RPAREN */ yytestcase(yyruleno==142);
      case 148: /* while_header ::= while_start LPAREN lexpr RPAREN */ yytestcase(yyruleno==148);
#line 708 "parser\\epparser.lemon"
{
    writeCsOpener(*pGen, yymsp[-3].minor.yy0, yymsp[-1].minor.yy0);
    ps->gen.indent();
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 2279 "parser\\epparser.c"
        break;
      case 141: /* elif_start ::= ELSE IF */
#line 716 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen.unindent(false);
    ps->gen << yygotominor.yy0->data << " = EUDElseIf()" << std::endl;
}
#line 2288 "parser\\epparser.c"
        break;
      case 144: /* else_header ::= ELSE */
#line 730 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "if EUDElse()():" << std::endl;
    ps->gen.indent();
}
#line 2297 "parser\\epparser.c"
        break;
      case 145: /* if_stmt ::= if_block */
      case 146: /* if_stmt ::= if_block else_header stmt */ yytestcase(yyruleno==146);
#line 736 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndIf()" << std::endl;
}
#line 2306 "parser\\epparser.c"
        break;
      case 147: /* while_start ::= WHILE */
#line 748 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDWhile()" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2315 "parser\\epparser.c"
        break;
      case 149: /* while_stmt ::= while_header stmt */
#line 760 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndWhile()" << std::endl;
}
#line 2323 "parser\\epparser.c"
        break;
      case 150: /* for_opener ::= FOR LPAREN */
      case 166: /* foreach_opener ::= FOREACH LPAREN */ yytestcase(yyruleno==166);
#line 766 "parser\\epparser.lemon"
{
    ps->closure.pushScope();
}
#line 2331 "parser\\epparser.c"
        break;
      case 162: /* for_header1 ::= for_opener for_init_stmt SEMICOLON */
#line 784 "parser\\epparser.lemon"
{
    // opening for lexpr
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDWhile()" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2341 "parser\\epparser.c"
        break;
      case 163: /* for_header2 ::= for_header1 lexpr SEMICOLON */
#line 791 "parser\\epparser.lemon"
{
    writeCsOpener(*pGen, yymsp[-2].minor.yy0, yymsp[-1].minor.yy0);
    ps->gen.indent();
    delete yymsp[-2].minor.yy0; delete yymsp[-1].minor.yy0;

    // Opening for assign_statement
    yygotominor.yy0 = genTemp(yymsp[-1].minor.yy0);
    ps->gen << "def " << yygotominor.yy0->data <<"():" << std::endl;
    ps->gen.indent();
}
#line 2355 "parser\\epparser.c"
        break;
      case 164: /* for_header ::= for_header2 for_action_stmt RPAREN */
#line 802 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-2].minor.yy0;
    ps->gen.unindent(false);
}
#line 2363 "parser\\epparser.c"
        break;
      case 165: /* for_stmt ::= for_header stmt */
#line 807 "parser\\epparser.lemon"
{
    ps->gen << "EUDSetContinuePoint()" << std::endl;
    ps->gen << yymsp[-1].minor.yy0->data << "()" << std::endl;
    ps->gen.unindent(false);
    ps->gen << "EUDEndWhile()" << std::endl;
    ps->closure.popScope();
}
#line 2374 "parser\\epparser.c"
        break;
      case 167: /* foreach_header ::= foreach_opener nameList_nonEmpty COLON exprList_nonEmpty RPAREN */
#line 822 "parser\\epparser.lemon"
{
    commaListIter(yymsp[-3].minor.yy0->data, [&](std::string& s) {
        ps->closure.defVariable(s);
    });
    ps->gen << "for " << yymsp[-3].minor.yy0->data << " in " << yymsp[-1].minor.yy0->data << ":" << std::endl;
    ps->gen.indent();
}
#line 2385 "parser\\epparser.c"
        break;
      case 168: /* foreach_stmt ::= foreach_header stmt */
#line 830 "parser\\epparser.lemon"
{
    ps->gen.unindent(true);
    ps->closure.popScope();
}
#line 2393 "parser\\epparser.c"
        break;
      case 169: /* continue_stmt ::= CONTINUE */
#line 838 "parser\\epparser.lemon"
{
    ps->gen << "EUDContinue()" << std::endl;
}
#line 2400 "parser\\epparser.c"
        break;
      case 170: /* break_stmt ::= BREAK */
#line 842 "parser\\epparser.lemon"
{
    ps->gen << "EUDBreak()" << std::endl;
}
#line 2407 "parser\\epparser.c"
        break;
      case 171: /* return_stmt ::= RETURN exprList */
#line 849 "parser\\epparser.lemon"
{
    if(MAP_DEBUG){
        ps->gen << "MDBG_POPF()" << std::endl;
    }
    ps->gen << "EUDReturn(" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2418 "parser\\epparser.c"
        break;
      case 172: /* lexpr ::= CONDITIONNAME LPAREN fArgs RPAREN */
      case 173: /* lexpr ::= KILLS LPAREN fArgs RPAREN */ yytestcase(yyruleno==173);
#line 860 "parser\\epparser.lemon"
{
    yymsp[-3].minor.yy0->data = yymsp[-3].minor.yy0->data + "(" + yymsp[-1].minor.yy0->data + ")";
    delete yymsp[-1].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 2428 "parser\\epparser.c"
        break;
      case 174: /* lexpr ::= CONDITIONNAME LPAREN RPAREN */
#line 872 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + "()";
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 2436 "parser\\epparser.c"
        break;
      case 175: /* action ::= ACTIONNAME LPAREN fArgs RPAREN SEMICOLON */
#line 877 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[-4].minor.yy0);
    yygotominor.yy0->data =  yymsp[-4].minor.yy0->data + "(" + yymsp[-2].minor.yy0->data + ")";
    delete yymsp[-4].minor.yy0; delete yymsp[-2].minor.yy0;
}
#line 2445 "parser\\epparser.c"
        break;
      case 176: /* actions ::= action action */
      case 177: /* actions ::= actions action */ yytestcase(yyruleno==177);
#line 883 "parser\\epparser.lemon"
{
    if(functionCalledInMultipleActions) {
        ps->gen << "DoActions([" << std::endl;
        ps->gen.indent();
        ps->gen << yymsp[-1].minor.yy0->data << std::endl;
        ps->gen.unindent(false);
        ps->gen << "])" << std::endl;

        delete yymsp[-1].minor.yy0;
        yygotominor.yy0 = yymsp[0].minor.yy0;
    }
    else {
        yymsp[0].minor.yy0->data = yymsp[-1].minor.yy0->data + ",\n" + yymsp[0].minor.yy0->data;
        yygotominor.yy0 = yymsp[0].minor.yy0;
        delete yymsp[-1].minor.yy0;
    }
    functionCalledInMultipleActions = false;
}
#line 2468 "parser\\epparser.c"
        break;
      case 178: /* actionStmt_start ::= */
#line 921 "parser\\epparser.lemon"
{
    functionCalledInMultipleActions = false;
}
#line 2475 "parser\\epparser.c"
        break;
      case 179: /* actionStmt ::= actionStmt_start action */
#line 925 "parser\\epparser.lemon"
{
    ps->gen << "DoActions(" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2483 "parser\\epparser.c"
        break;
      case 180: /* actionStmt ::= actionStmt_start actions */
#line 930 "parser\\epparser.lemon"
{
    ps->gen << "DoActions([" << std::endl;
    ps->gen.indent();
    ps->gen << yymsp[0].minor.yy0->data << std::endl;
    ps->gen.unindent(false);
    ps->gen << "])" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2495 "parser\\epparser.c"
        break;
      default:
      /* (0) program ::= chunks */ yytestcase(yyruleno==0);
      /* (1) chunks ::= */ yytestcase(yyruleno==1);
      /* (2) chunks ::= chunks chunk */ yytestcase(yyruleno==2);
      /* (3) chunk ::= import_chunk SEMICOLON */ yytestcase(yyruleno==3);
      /* (4) chunk ::= fdef_chunk */ yytestcase(yyruleno==4);
      /* (5) chunk ::= fdecl_chunk */ yytestcase(yyruleno==5);
      /* (6) chunk ::= object_chunk */ yytestcase(yyruleno==6);
      /* (7) chunk ::= vdef_stmt SEMICOLON */ yytestcase(yyruleno==7);
      /* (8) chunk ::= vdefAssign_global_stmt SEMICOLON */ yytestcase(yyruleno==8);
      /* (9) chunk ::= cdef_global_stmt SEMICOLON */ yytestcase(yyruleno==9);
      /* (26) stmt ::= bodyStmt */ yytestcase(yyruleno==26);
      /* (27) stmt ::= return_stmt SEMICOLON */ yytestcase(yyruleno==27);
      /* (31) blockStmt ::= lbracket return_stmt SEMICOLON rbracket */ yytestcase(yyruleno==31);
      /* (32) blockStmt ::= lbracket bodyStmtList rbracket */ yytestcase(yyruleno==32);
      /* (33) blockStmt ::= lbracket bodyStmtList return_stmt SEMICOLON rbracket */ yytestcase(yyruleno==33);
      /* (35) bodyStmt ::= blockStmt */ yytestcase(yyruleno==35);
      /* (36) bodyStmt ::= SEMICOLON */ yytestcase(yyruleno==36);
      /* (37) bodyStmt ::= vdef_stmt SEMICOLON */ yytestcase(yyruleno==37);
      /* (38) bodyStmt ::= vdefAssign_stmt SEMICOLON */ yytestcase(yyruleno==38);
      /* (39) bodyStmt ::= cdef_stmt SEMICOLON */ yytestcase(yyruleno==39);
      /* (40) bodyStmt ::= assign_stmt SEMICOLON */ yytestcase(yyruleno==40);
      /* (42) bodyStmt ::= actionStmt */ yytestcase(yyruleno==42);
      /* (43) bodyStmt ::= if_stmt */ yytestcase(yyruleno==43);
      /* (44) bodyStmt ::= while_stmt */ yytestcase(yyruleno==44);
      /* (45) bodyStmt ::= for_stmt */ yytestcase(yyruleno==45);
      /* (46) bodyStmt ::= foreach_stmt */ yytestcase(yyruleno==46);
      /* (47) bodyStmt ::= continue_stmt SEMICOLON */ yytestcase(yyruleno==47);
      /* (48) bodyStmt ::= break_stmt SEMICOLON */ yytestcase(yyruleno==48);
      /* (50) bodyStmtList ::= bodyStmt */ yytestcase(yyruleno==50);
      /* (51) bodyStmtList ::= bodyStmtList bodyStmt */ yytestcase(yyruleno==51);
      /* (80) commaSkippable ::= COMMA */ yytestcase(yyruleno==80);
      /* (81) commaSkippable ::= */ yytestcase(yyruleno==81);
      /* (140) if_block ::= if_header stmt */ yytestcase(yyruleno==140);
      /* (143) if_block ::= if_block elif_header stmt */ yytestcase(yyruleno==143);
      /* (151) for_init_stmt_nonEmpty ::= vdef_stmt */ yytestcase(yyruleno==151);
      /* (152) for_init_stmt_nonEmpty ::= vdefAssign_stmt */ yytestcase(yyruleno==152);
      /* (153) for_init_stmt_nonEmpty ::= cdef_stmt */ yytestcase(yyruleno==153);
      /* (154) for_init_stmt_nonEmpty ::= assign_stmt */ yytestcase(yyruleno==154);
      /* (155) for_init_stmt_nonEmpty ::= for_init_stmt_nonEmpty COMMA for_init_stmt_nonEmpty */ yytestcase(yyruleno==155);
      /* (156) for_init_stmt ::= for_init_stmt_nonEmpty */ yytestcase(yyruleno==156);
      /* (157) for_init_stmt ::= */ yytestcase(yyruleno==157);
      /* (158) for_action_stmt_nonEmpty ::= assign_stmt */ yytestcase(yyruleno==158);
      /* (159) for_action_stmt_nonEmpty ::= for_action_stmt_nonEmpty COMMA for_action_stmt_nonEmpty */ yytestcase(yyruleno==159);
      /* (160) for_action_stmt ::= */ yytestcase(yyruleno==160);
      /* (161) for_action_stmt ::= for_action_stmt_nonEmpty */ yytestcase(yyruleno==161);
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
#line 32 "parser\\epparser.lemon"

    throw_error(-1, "Unrecoverable error");
#line 2591 "parser\\epparser.c"
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
#line 944 "parser\\epparser.lemon"


PyGenerator* pGen;
ClosureManager* closure;

std::string ParseString(const std::string& fname, const std::string& code, bool addComment)
{
    // Module name from fname
    // last \/ ~ first .
    auto lpos = fname.find_last_of("\\/");
    if(lpos == std::string::npos) lpos = 0;
    else lpos++;
    auto rpos = fname.find_first_of(".", lpos);
    if(rpos == std::string::npos) rpos = fname.size();
    currentModule = fname.substr(lpos, rpos - lpos);

    // Main code
    Tokenizer tok(code);
    void* pParser = ParseAlloc (malloc);
    ParserStruct ps;
    Token* token;
    currentTokenizingLine = 0;
    pGen = &ps.gen;
    closure = &ps.closure;
    functionCalledInMultipleActions = false;

    if(PARSER_DEBUG) std::cout << "Parsing string [[[\n" << code.c_str() << "\n]]]\n";
    if(MAP_DEBUG) {
        ps.gen <<
            "try:\n"
            "   MDBG_LOG = GetEUDNamespace()['MDBG_LOG']\n"
            "   MDBG_PUSHF = GetEUDNamespace()['MDBG_PUSHF']\n"
            "   MDBG_POPF = GetEUDNamespace()['MDBG_POPF']\n"
            "except KeyError:\n"
            "    mdbg_dbepd = EPD(Db(b'0123456789ABCDEFFEDCBA9876543210' + bytes(32 * 2048)))\n"
            "    mdbg_dbc = EUDVariable()\n"
            "    \n"
            "    @EUDRegistered\n"
            "    def MDBG_LOG(line):\n"
            "        lIdf = b2i4(u2b('%4d' % line))\n"
            "        DoActions(SetMemoryEPD(mdbg_dbepd + 3 + mdbg_dbc, SetTo, lIdf))\n"
            "    \n"
            "    \n"
            "    @EUDRegistered\n"
            "    def MDBG_PUSHF(f_name, m_name):\n"
            "        global mdbg_dbc\n"
            "        data = ((u2b(m_name) + bytes(12))[:12] + b'   0' + (u2b(f_name) + bytes(16))[:16])\n"
            "        mdbg_dbc += 8\n"
            "        DoActions([SetMemoryEPD(mdbg_dbepd + i + mdbg_dbc, SetTo, b2i4(data, i * 4)) for i in range(8)])\n"
            "    \n"
            "    @EUDRegistered\n"
            "    def MDBG_POPF():\n"
            "        global mdbg_dbc\n"
            "        DoActions([SetMemoryEPD(mdbg_dbepd + i + mdbg_dbc, SetTo, 0) for i in range(8)])\n"
            "        mdbg_dbc -= 8\n"
            "\n";
    }

    tmpIndex = 1;
    resetParserErrorNum();
    while ((token = tok.getToken()) != nullptr) {
        if (currentTokenizingLine != tok.getCurrentLine()) {
            if(addComment) {
                currentTokenizingLine = tok.getCurrentLine();
                ps.gen << "# (Line " << currentTokenizingLine << ") " << trim(tok.getCurrentLineString()) << std::endl;
                if(MAP_DEBUG && !currentFunction.empty()) {
                    ps.gen << "MDBG_LOG(" << currentTokenizingLine << ")" << std::endl;
                }
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
#line 2887 "parser\\epparser.c"
