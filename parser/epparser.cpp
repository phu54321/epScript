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
#define YYNOCODE 144
#define YYACTIONTYPE unsigned short int
#define ParseTOKENTYPE Token*
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  int yy287;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL  ParserStruct* ps ;
#define ParseARG_PDECL , ParserStruct* ps 
#define ParseARG_FETCH  ParserStruct* ps  = yypParser->ps 
#define ParseARG_STORE yypParser->ps  = ps 
#define YYNSTATE 356
#define YYNRULE 183
#define YYERRORSYMBOL 73
#define YYERRSYMDT yy287
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
#define YY_ACTTAB_COUNT (1492)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   234,   74,   73,   71,   72,   70,  324,   35,  165,  230,
 /*    10 */   215,  217,  330,   85,  162,   18,  340,  226,  235,  305,
 /*    20 */   119,   76,  338,  233,    2,  144,  235,  229,  228,  227,
 /*    30 */   158,  322,  321,  320,  319,  318,  222,  221,  264,   57,
 /*    40 */    96,   54,   55,  251,  215,  144,  131,  153,  354,  185,
 /*    50 */     9,   78,   77,  188,  119,  180,    7,   12,  234,  144,
 /*    60 */    87,   86,   27,   14,    6,   88,    5,  230,  215,   81,
 /*    70 */   330,  304,   26,   57,  284,   54,   55,  210,  119,   91,
 /*    80 */   338,  233,    2,  144,   19,  229,  228,  227,  158,  322,
 /*    90 */   321,  320,  319,  318,  222,  221,  212,   57,   96,   54,
 /*   100 */    55,  215,  238,  144,  131,  153,  236,  185,    9,   78,
 /*   110 */   210,  119,  260,  180,    7,   12,  144,    3,  248,  234,
 /*   120 */    27,   14,    6,   88,    5,  540,   11,   81,  230,  293,
 /*   130 */   217,  330,  345,  211,   18,  281,  182,    8,    4,  350,
 /*   140 */    76,  338,  233,    2,  349,  344,  229,  228,  227,  158,
 /*   150 */   322,  321,  320,  319,  318,  222,  221,  163,  242,   96,
 /*   160 */   241,  236,  348,  215,  144,  131,  153,  239,  185,    9,
 /*   170 */    78,   82,  187,  119,  180,    7,   12,  234,  144,  237,
 /*   180 */   219,   27,   14,    6,   88,    5,  230,  219,   81,  330,
 /*   190 */   116,  343,   34,  278,  235,  144,   33,  104,  235,  338,
 /*   200 */   233,    2,  144,  287,  229,  228,  227,  158,  322,  321,
 /*   210 */   320,  319,  318,  222,  221,  235,   31,   96,   32,   25,
 /*   220 */   215,  235,  144,  131,  153,  341,  185,    9,   78,  186,
 /*   230 */   119,  225,  180,    7,   12,  144,  339,  337,  234,   27,
 /*   240 */    14,    6,   88,    5,   94,   93,   81,  230,  328,   24,
 /*   250 */   330,  235,  327,  326,  266,  325,  224,  317,   23,  223,
 /*   260 */   338,  233,    2,  316,   20,  229,  228,  227,  158,  322,
 /*   270 */   321,  320,  319,  318,  222,  221,   19,  323,   96,  226,
 /*   280 */   312,  214,  215,  144,  131,  153,   92,  185,    9,   78,
 /*   290 */   307,  151,  119,  180,    7,   12,  234,  144,  306,  219,
 /*   300 */    27,   14,    6,   88,    5,  230,  215,   81,  330,  100,
 /*   310 */    35,   58,  263,  207,  144,  161,  119,  206,  338,  233,
 /*   320 */     2,  144,  303,  229,  228,  227,  158,  322,  321,  320,
 /*   330 */   319,  318,  222,  221,  204,  203,   96,  302,  201,  215,
 /*   340 */   301,  144,  131,  153,  200,  185,    9,   78,  160,  119,
 /*   350 */   198,  180,    7,   12,  144,  197,   55,  234,   27,   14,
 /*   360 */     6,   88,    5,  300,   16,   81,  230,  297,  294,  330,
 /*   370 */   292,  291,  290,  256,  129,  285,   30,  283,   29,  338,
 /*   380 */   233,    2,  282,  279,  229,  228,  227,  158,  322,  321,
 /*   390 */   320,  319,  318,  222,  221,  219,   28,   96,  277,   13,
 /*   400 */   271,  219,  144,  131,  153,   99,  185,    9,   78,  270,
 /*   410 */   138,  137,  180,    7,   12,  234,  144,   15,  219,   27,
 /*   420 */    14,    6,   88,    5,  230,  219,   81,  330,  136,  267,
 /*   430 */   265,  249,   17,  144,  169,  147,  259,  338,  233,    2,
 /*   440 */   144,  253,  229,  228,  227,  158,  322,  321,  320,  319,
 /*   450 */   318,  222,  221,  219,  255,   96,  166,  164,   80,  247,
 /*   460 */   144,  131,  153,  146,  185,    9,   78,  250,  144,  159,
 /*   470 */   180,    7,   12,  346,  333,  334,  168,   27,   14,    6,
 /*   480 */    88,    5,  331,  213,   81,  230,  156,  193,  330,  295,
 /*   490 */   155,  342,  258,  154,  152,  171,  257,  541,  254,  232,
 /*   500 */     2,  150,    1,  229,  228,  227,  158,  322,  321,  320,
 /*   510 */   319,  318,  222,  221,  219,  183,   96,  541,  149,  148,
 /*   520 */   219,  144,  131,  153,  145,  185,    9,   78,  541,  144,
 /*   530 */   135,  180,    7,   12,  314,  144,  541,  219,   27,   14,
 /*   540 */     6,   88,    5,  230,  541,   81,  330,  134,  541,  541,
 /*   550 */   541,  541,  144,  541,  541,  541,  315,  231,    2,  332,
 /*   560 */   541,  229,  228,  227,  158,  322,  321,  320,  319,  318,
 /*   570 */   222,  221,  219,  541,   96,  541,  541,  541,  541,  144,
 /*   580 */   131,  153,  133,  185,    9,   78,  541,  144,   50,  180,
 /*   590 */     7,   12,  541,  541,  541,  541,   27,   14,    6,   88,
 /*   600 */     5,   53,   52,   81,  541,  541,  541,   51,  313,  127,
 /*   610 */   329,  541,  541,  541,  541,   75,  541,  541,  336,   90,
 /*   620 */   335,   22,  541,  220,  541,  219,  209,  208,  205,  202,
 /*   630 */   199,  541,   89,   37,   36,  126,  541,  216,  190,  541,
 /*   640 */   144,   50,  541,  541,  541,  286,  541,  280,  178,  172,
 /*   650 */   262,  261,   21,  195,   53,   52,  541,  541,  541,  541,
 /*   660 */    51,  313,  127,  329,  541,  541,  541,  541,   75,  541,
 /*   670 */   541,  336,   90,  334,   22,  541,  220,  541,  219,  209,
 /*   680 */   208,  205,  202,  199,  541,   89,   37,   36,  126,  541,
 /*   690 */   216,  191,  541,  144,   50,  541,  541,  541,  286,  541,
 /*   700 */   280,  178,  172,  262,  261,   21,  195,   53,   52,  541,
 /*   710 */   541,  541,  541,   51,  313,  127,  329,  541,  541,  541,
 /*   720 */   541,   75,  541,  541,  336,   90,  541,   22,  541,  220,
 /*   730 */   541,  541,  209,  208,  205,  202,  199,  219,   89,   37,
 /*   740 */    36,  475,  541,  475,  541,  541,  541,  126,  541,  216,
 /*   750 */   192,  286,  144,  280,  178,  172,  262,  261,   21,  195,
 /*   760 */    64,   62,   61,   60,   59,   63,   66,   65,   67,   69,
 /*   770 */    68,   74,   73,   71,   72,   70,  541,  219,  541,  541,
 /*   780 */   541,  189,  541,  541,  541,   18,  541,  126,  541,  216,
 /*   790 */   170,   49,  144,  475,  475,  475,  475,  475,  475,  475,
 /*   800 */   475,  475,  475,  289,  288,  541,  541,  541,  541,  541,
 /*   810 */   541,  541,   64,   62,   61,   60,   59,   63,   66,   65,
 /*   820 */    67,   69,   68,   74,   73,   71,   72,   70,  541,  541,
 /*   830 */   541,  541,  541,  217,  541,  541,  541,   18,  541,  541,
 /*   840 */   541,  541,  541,   76,  311,  541,   64,   62,   61,   60,
 /*   850 */    59,   63,   66,   65,   67,   69,   68,   74,   73,   71,
 /*   860 */    72,   70,  541,  541,  219,  541,  541,  217,  541,  541,
 /*   870 */   541,   18,  308,  541,  126,  541,  309,   76,  276,  144,
 /*   880 */    64,   62,   61,   60,   59,   63,   66,   65,   67,   69,
 /*   890 */    68,   74,   73,   71,   72,   70,  275,  274,  273,  219,
 /*   900 */   541,  217,  219,  541,  541,   18,  541,  541,  219,   96,
 /*   910 */   541,   76,  101,  541,  144,  131,  153,  140,  101,  541,
 /*   920 */   184,   56,  541,  140,  541,  541,  181,  177,  176,  541,
 /*   930 */    64,   62,   61,   60,   59,   63,   66,   65,   67,   69,
 /*   940 */    68,   74,   73,   71,   72,   70,  541,  541,  219,  541,
 /*   950 */   541,  217,  541,  541,  541,   18,  541,  541,  130,  541,
 /*   960 */   541,   76,  128,  144,   64,   62,   61,   60,   59,   63,
 /*   970 */    66,   65,   67,   69,   68,   74,   73,   71,   72,   70,
 /*   980 */   541,  219,  219,  541,  541,  217,  541,  541,  541,   18,
 /*   990 */   541,  126,  132,  216,  194,   76,  144,  144,   64,   62,
 /*  1000 */    61,   60,   59,   63,   66,   65,   67,   69,   68,   74,
 /*  1010 */    73,   71,   72,   70,   50,  541,  541,  541,  541,  189,
 /*  1020 */   541,  541,  541,   18,   71,   72,   70,   53,   52,   49,
 /*  1030 */   541,  541,  217,   51,  313,  127,   18,  541,  541,  541,
 /*  1040 */   541,   75,   76,  541,  541,   90,  541,   22,   50,  220,
 /*  1050 */   541,  541,  209,  208,  205,  202,  199,  541,   89,   37,
 /*  1060 */    36,   53,   52,  541,  541,  541,  541,   51,  313,  157,
 /*  1070 */   219,  541,  541,  541,  541,   75,  296,  541,  541,  195,
 /*  1080 */   125,   22,   50,  220,  310,  144,  209,  208,  205,  202,
 /*  1090 */   199,  541,  541,  541,  541,   53,   52,  219,  541,  541,
 /*  1100 */   541,   51,  313,  127,  219,  541,  541,  124,  541,   75,
 /*  1110 */   541,  541,  144,  195,  123,   22,   50,  220,  541,  144,
 /*  1120 */   209,  208,  205,  202,  199,  541,  541,   37,   36,   53,
 /*  1130 */    52,  219,  541,  541,  541,   51,  313,  157,  219,  541,
 /*  1140 */   541,  122,  541,   75,  541,  541,  144,  195,  121,   22,
 /*  1150 */    50,  220,  310,  144,  209,  208,  205,  202,  199,  541,
 /*  1160 */   541,  541,  541,   53,   52,  219,  541,  541,  541,   51,
 /*  1170 */   313,  218,  219,  541,  541,  120,  541,   75,  541,  541,
 /*  1180 */   144,  195,  118,   22,   50,  220,   48,  139,  209,  208,
 /*  1190 */   205,  202,  199,  541,  541,  541,  541,   53,   52,  473,
 /*  1200 */   356,  473,  541,   51,  313,  127,  219,  541,  541,  541,
 /*  1210 */   541,   75,  541,  541,  541,  195,   98,   22,  219,  220,
 /*  1220 */   541,  144,  209,  208,  205,  202,  199,  541,  117,  541,
 /*  1230 */    95,   19,  240,  144,  541,  167,  336,   84,   47,   46,
 /*  1240 */    45,   44,   43,   42,   41,   40,   39,   38,  541,  195,
 /*  1250 */    83,  473,  473,  473,  473,  473,  473,  473,  473,  473,
 /*  1260 */   473,  355,  246,  353,  352,  351,  245,  244,  243,  347,
 /*  1270 */   474,   10,  474,  541,  252,   79,  541,  541,  541,  541,
 /*  1280 */   541,    2,   65,   67,   69,   68,   74,   73,   71,   72,
 /*  1290 */    70,  541,  541,  219,  219,  219,  217,  541,  541,  541,
 /*  1300 */    18,  269,  219,  101,  118,  101,   76,  541,  140,  299,
 /*  1310 */   140,  179,   96,  175,  541,  541,  541,  144,  131,  153,
 /*  1320 */   541,  541,  474,  474,  474,  474,  474,  474,  474,  474,
 /*  1330 */   474,  474,  174,  173,  541,  541,  541,  541,  541,   67,
 /*  1340 */    69,   68,   74,   73,   71,   72,   70,  541,  541,  541,
 /*  1350 */   541,  541,  217,  276,  541,  541,   18,  541,  541,  541,
 /*  1360 */   541,  541,   76,   69,   68,   74,   73,   71,   72,   70,
 /*  1370 */   541,  275,  274,  273,  219,  217,  541,  269,  219,   18,
 /*  1380 */   541,  541,  541,  541,   96,   76,  219,  541,   96,  144,
 /*  1390 */   131,  153,  541,  144,  131,  153,  118,  219,  541,  219,
 /*  1400 */   219,  196,  272,  541,  541,  541,  219,  143,  268,  142,
 /*  1410 */   141,  541,  144,  219,  144,  144,  118,  219,  541,  541,
 /*  1420 */   541,  298,  541,   97,  541,  541,  541,  115,  144,  219,
 /*  1430 */   219,  219,  144,  219,  541,  541,  541,  219,  541,  114,
 /*  1440 */   113,  112,  541,  111,  144,  144,  144,  110,  144,  541,
 /*  1450 */   219,  541,  144,  541,  541,  541,  219,  219,  541,  541,
 /*  1460 */   109,  541,  541,  541,  541,  144,  108,  107,  219,  219,
 /*  1470 */   219,  144,  144,  541,  541,  541,  219,  541,  106,  105,
 /*  1480 */   103,  541,  541,  144,  144,  144,  102,  541,  541,  541,
 /*  1490 */   541,  144,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    73,   19,   20,   21,   22,   23,   28,    3,   32,   82,
 /*    10 */   103,   29,   85,   37,   38,   33,   89,   39,    3,  112,
 /*    20 */   113,   39,   95,   96,   97,  118,    3,  100,  101,  102,
 /*    30 */   103,  104,  105,  106,  107,  108,  109,  110,   34,    2,
 /*    40 */   113,    4,    5,   28,  103,  118,  119,  120,   28,  122,
 /*    50 */   123,  124,    1,  112,  113,  128,  129,  130,   73,  118,
 /*    60 */   140,  141,  135,  136,  137,  138,  139,   82,  103,  142,
 /*    70 */    85,   34,   49,    2,   89,    4,    5,  112,  113,  114,
 /*    80 */    95,   96,   97,  118,   33,  100,  101,  102,  103,  104,
 /*    90 */   105,  106,  107,  108,  109,  110,    3,    2,  113,    4,
 /*   100 */     5,  103,   88,  118,  119,  120,   92,  122,  123,  124,
 /*   110 */   112,  113,  114,  128,  129,  130,  118,   93,   94,   73,
 /*   120 */   135,  136,  137,  138,  139,   75,   76,  142,   82,   34,
 /*   130 */    29,   85,   27,   40,   33,   89,  125,  126,  127,   28,
 /*   140 */    39,   95,   96,   97,   28,   27,  100,  101,  102,  103,
 /*   150 */   104,  105,  106,  107,  108,  109,  110,   88,   29,  113,
 /*   160 */    31,   92,   28,  103,  118,  119,  120,   27,  122,  123,
 /*   170 */   124,   33,  112,  113,  128,  129,  130,   73,  118,   34,
 /*   180 */   103,  135,  136,  137,  138,  139,   82,  103,  142,   85,
 /*   190 */   113,   28,    1,   89,    3,  118,    1,  113,    3,   95,
 /*   200 */    96,   97,  118,  119,  100,  101,  102,  103,  104,  105,
 /*   210 */   106,  107,  108,  109,  110,    3,    1,  113,    3,    1,
 /*   220 */   103,    3,  118,  119,  120,   27,  122,  123,  124,  112,
 /*   230 */   113,   39,  128,  129,  130,  118,   28,   28,   73,  135,
 /*   240 */   136,  137,  138,  139,   28,   28,  142,   82,   28,    1,
 /*   250 */    85,    3,   28,   28,   89,   28,   26,   28,    3,   40,
 /*   260 */    95,   96,   97,   28,   33,  100,  101,  102,  103,  104,
 /*   270 */   105,  106,  107,  108,  109,  110,   33,   40,  113,   39,
 /*   280 */    27,   39,  103,  118,  119,  120,   39,  122,  123,  124,
 /*   290 */    26,  112,  113,  128,  129,  130,   73,  118,   40,  103,
 /*   300 */   135,  136,  137,  138,  139,   82,  103,  142,   85,  113,
 /*   310 */     3,   33,   89,   33,  118,  112,  113,   42,   95,   96,
 /*   320 */    97,  118,   34,  100,  101,  102,  103,  104,  105,  106,
 /*   330 */   107,  108,  109,  110,   33,   42,  113,   34,   33,  103,
 /*   340 */    34,  118,  119,  120,   42,  122,  123,  124,  112,  113,
 /*   350 */    33,  128,  129,  130,  118,   42,    5,   73,  135,  136,
 /*   360 */   137,  138,  139,   34,   33,  142,   82,   34,   40,   85,
 /*   370 */    34,   34,   34,   89,   27,   34,   33,   63,   33,   95,
 /*   380 */    96,   97,   34,   34,  100,  101,  102,  103,  104,  105,
 /*   390 */   106,  107,  108,  109,  110,  103,   33,  113,   33,    3,
 /*   400 */    28,  103,  118,  119,  120,  113,  122,  123,  124,   28,
 /*   410 */   118,  113,  128,  129,  130,   73,  118,    3,  103,  135,
 /*   420 */   136,  137,  138,  139,   82,  103,  142,   85,  113,   34,
 /*   430 */    33,   89,   33,  118,   34,  113,   28,   95,   96,   97,
 /*   440 */   118,   36,  100,  101,  102,  103,  104,  105,  106,  107,
 /*   450 */   108,  109,  110,  103,   38,  113,   27,   27,   33,   28,
 /*   460 */   118,  119,  120,  113,  122,  123,  124,   34,  118,   86,
 /*   470 */   128,  129,  130,   27,   98,   38,   73,  135,  136,  137,
 /*   480 */   138,  139,   98,   26,  142,   82,  111,  117,   85,    3,
 /*   490 */    92,   27,  140,   92,   92,   72,  140,  143,   95,   96,
 /*   500 */    97,   92,   99,  100,  101,  102,  103,  104,  105,  106,
 /*   510 */   107,  108,  109,  110,  103,   64,  113,  143,   92,   92,
 /*   520 */   103,  118,  119,  120,  113,  122,  123,  124,  143,  118,
 /*   530 */   113,  128,  129,  130,   73,  118,  143,  103,  135,  136,
 /*   540 */   137,  138,  139,   82,  143,  142,   85,  113,  143,  143,
 /*   550 */   143,  143,  118,  143,  143,  143,   95,   96,   97,   98,
 /*   560 */   143,  100,  101,  102,  103,  104,  105,  106,  107,  108,
 /*   570 */   109,  110,  103,  143,  113,  143,  143,  143,  143,  118,
 /*   580 */   119,  120,  113,  122,  123,  124,  143,  118,    6,  128,
 /*   590 */   129,  130,  143,  143,  143,  143,  135,  136,  137,  138,
 /*   600 */   139,   19,   20,  142,  143,  143,  143,   25,   26,   27,
 /*   610 */    28,  143,  143,  143,  143,   33,  143,  143,   36,   37,
 /*   620 */    38,   39,  143,   41,  143,  103,   44,   45,   46,   47,
 /*   630 */    48,  143,   50,   51,   52,  113,  143,  115,  116,  143,
 /*   640 */   118,    6,  143,  143,  143,   63,  143,   65,   66,   67,
 /*   650 */    68,   69,   70,   71,   19,   20,  143,  143,  143,  143,
 /*   660 */    25,   26,   27,   28,  143,  143,  143,  143,   33,  143,
 /*   670 */   143,   36,   37,   38,   39,  143,   41,  143,  103,   44,
 /*   680 */    45,   46,   47,   48,  143,   50,   51,   52,  113,  143,
 /*   690 */   115,  116,  143,  118,    6,  143,  143,  143,   63,  143,
 /*   700 */    65,   66,   67,   68,   69,   70,   71,   19,   20,  143,
 /*   710 */   143,  143,  143,   25,   26,   27,   28,  143,  143,  143,
 /*   720 */   143,   33,  143,  143,   36,   37,  143,   39,  143,   41,
 /*   730 */   143,  143,   44,   45,   46,   47,   48,  103,   50,   51,
 /*   740 */    52,    1,  143,    3,  143,  143,  143,  113,  143,  115,
 /*   750 */   116,   63,  118,   65,   66,   67,   68,   69,   70,   71,
 /*   760 */     8,    9,   10,   11,   12,   13,   14,   15,   16,   17,
 /*   770 */    18,   19,   20,   21,   22,   23,  143,  103,  143,  143,
 /*   780 */   143,   29,  143,  143,  143,   33,  143,  113,  143,  115,
 /*   790 */   116,   39,  118,   53,   54,   55,   56,   57,   58,   59,
 /*   800 */    60,   61,   62,   51,   52,  143,  143,  143,  143,  143,
 /*   810 */   143,  143,    8,    9,   10,   11,   12,   13,   14,   15,
 /*   820 */    16,   17,   18,   19,   20,   21,   22,   23,  143,  143,
 /*   830 */   143,  143,  143,   29,  143,  143,  143,   33,  143,  143,
 /*   840 */   143,  143,  143,   39,   40,  143,    8,    9,   10,   11,
 /*   850 */    12,   13,   14,   15,   16,   17,   18,   19,   20,   21,
 /*   860 */    22,   23,  143,  143,  103,  143,  143,   29,  143,  143,
 /*   870 */   143,   33,   34,  143,  113,  143,  115,   39,   82,  118,
 /*   880 */     8,    9,   10,   11,   12,   13,   14,   15,   16,   17,
 /*   890 */    18,   19,   20,   21,   22,   23,  100,  101,  102,  103,
 /*   900 */   143,   29,  103,  143,  143,   33,  143,  143,  103,  113,
 /*   910 */   143,   39,  113,  143,  118,  119,  120,  118,  113,  143,
 /*   920 */   121,   49,  143,  118,  143,  143,  121,  131,  132,  143,
 /*   930 */     8,    9,   10,   11,   12,   13,   14,   15,   16,   17,
 /*   940 */    18,   19,   20,   21,   22,   23,  143,  143,  103,  143,
 /*   950 */   143,   29,  143,  143,  143,   33,  143,  143,  113,  143,
 /*   960 */   143,   39,   40,  118,    8,    9,   10,   11,   12,   13,
 /*   970 */    14,   15,   16,   17,   18,   19,   20,   21,   22,   23,
 /*   980 */   143,  103,  103,  143,  143,   29,  143,  143,  143,   33,
 /*   990 */   143,  113,  113,  115,  116,   39,  118,  118,    8,    9,
 /*  1000 */    10,   11,   12,   13,   14,   15,   16,   17,   18,   19,
 /*  1010 */    20,   21,   22,   23,    6,  143,  143,  143,  143,   29,
 /*  1020 */   143,  143,  143,   33,   21,   22,   23,   19,   20,   39,
 /*  1030 */   143,  143,   29,   25,   26,   27,   33,  143,  143,  143,
 /*  1040 */   143,   33,   39,  143,  143,   37,  143,   39,    6,   41,
 /*  1050 */   143,  143,   44,   45,   46,   47,   48,  143,   50,   51,
 /*  1060 */    52,   19,   20,  143,  143,  143,  143,   25,   26,   27,
 /*  1070 */   103,  143,  143,  143,  143,   33,   34,  143,  143,   71,
 /*  1080 */   113,   39,    6,   41,   42,  118,   44,   45,   46,   47,
 /*  1090 */    48,  143,  143,  143,  143,   19,   20,  103,  143,  143,
 /*  1100 */   143,   25,   26,   27,  103,  143,  143,  113,  143,   33,
 /*  1110 */   143,  143,  118,   71,  113,   39,    6,   41,  143,  118,
 /*  1120 */    44,   45,   46,   47,   48,  143,  143,   51,   52,   19,
 /*  1130 */    20,  103,  143,  143,  143,   25,   26,   27,  103,  143,
 /*  1140 */   143,  113,  143,   33,  143,  143,  118,   71,  113,   39,
 /*  1150 */     6,   41,   42,  118,   44,   45,   46,   47,   48,  143,
 /*  1160 */   143,  143,  143,   19,   20,  103,  143,  143,  143,   25,
 /*  1170 */    26,   27,  103,  143,  143,  113,  143,   33,  143,  143,
 /*  1180 */   118,   71,  113,   39,    6,   41,    1,  118,   44,   45,
 /*  1190 */    46,   47,   48,  143,  143,  143,  143,   19,   20,    1,
 /*  1200 */     0,    3,  143,   25,   26,   27,  103,  143,  143,  143,
 /*  1210 */   143,   33,  143,  143,  143,   71,  113,   39,  103,   41,
 /*  1220 */   143,  118,   44,   45,   46,   47,   48,  143,  113,  143,
 /*  1230 */    30,   33,   32,  118,  143,   35,   36,   37,   53,   54,
 /*  1240 */    55,   56,   57,   58,   59,   60,   61,   62,  143,   71,
 /*  1250 */    50,   53,   54,   55,   56,   57,   58,   59,   60,   61,
 /*  1260 */    62,   77,   78,   79,   80,   81,   82,   83,   84,   85,
 /*  1270 */     1,   87,    3,  143,   90,   91,  143,  143,  143,  143,
 /*  1280 */   143,   97,   15,   16,   17,   18,   19,   20,   21,   22,
 /*  1290 */    23,  143,  143,  103,  103,  103,   29,  143,  143,  143,
 /*  1300 */    33,  102,  103,  113,  113,  113,   39,  143,  118,  118,
 /*  1310 */   118,  121,  113,  121,  143,  143,  143,  118,  119,  120,
 /*  1320 */   143,  143,   53,   54,   55,   56,   57,   58,   59,   60,
 /*  1330 */    61,   62,  133,  134,  143,  143,  143,  143,  143,   16,
 /*  1340 */    17,   18,   19,   20,   21,   22,   23,  143,  143,  143,
 /*  1350 */   143,  143,   29,   82,  143,  143,   33,  143,  143,  143,
 /*  1360 */   143,  143,   39,   17,   18,   19,   20,   21,   22,   23,
 /*  1370 */   143,  100,  101,  102,  103,   29,  143,  102,  103,   33,
 /*  1380 */   143,  143,  143,  143,  113,   39,  103,  143,  113,  118,
 /*  1390 */   119,  120,  143,  118,  119,  120,  113,  103,  143,  103,
 /*  1400 */   103,  118,  131,  143,  143,  143,  103,  113,  133,  113,
 /*  1410 */   113,  143,  118,  103,  118,  118,  113,  103,  143,  143,
 /*  1420 */   143,  118,  143,  113,  143,  143,  143,  113,  118,  103,
 /*  1430 */   103,  103,  118,  103,  143,  143,  143,  103,  143,  113,
 /*  1440 */   113,  113,  143,  113,  118,  118,  118,  113,  118,  143,
 /*  1450 */   103,  143,  118,  143,  143,  143,  103,  103,  143,  143,
 /*  1460 */   113,  143,  143,  143,  143,  118,  113,  113,  103,  103,
 /*  1470 */   103,  118,  118,  143,  143,  143,  103,  143,  113,  113,
 /*  1480 */   113,  143,  143,  118,  118,  118,  113,  143,  143,  143,
 /*  1490 */   143,  118,
};
#define YY_SHIFT_USE_DFLT (-25)
#define YY_SHIFT_COUNT (246)
#define YY_SHIFT_MIN   (-24)
#define YY_SHIFT_MAX   (1346)
static const short yy_shift_ofst[] = {
 /*     0 */   -25,  635,  582,  688,  688,  688,  688,  688,  688,  688,
 /*    10 */   688, 1200, 1008, 1008, 1076, 1076, 1042, 1110, 1110, 1110,
 /*    20 */  1110, 1144, 1144, 1110, 1144, 1144, 1144, 1144, 1144, 1144,
 /*    30 */  1144, 1144, 1178, 1144, 1144, 1144, 1144, 1144, 1144, 1144,
 /*    40 */  1144, 1144, 1144, 1144, 1144, 1144, 1144, 1144, 1144, 1144,
 /*    50 */  1144, 1144, 1144, 1144, 1144, 1144, 1144, 1144, 1144, 1144,
 /*    60 */  1144, 1144, 1144, 1144, 1144, 1144, 1144, 1144, 1144, 1144,
 /*    70 */  1144, 1144, 1144, 1144, 1144, 1144, 1144, 1144,  451,  -24,
 /*    80 */   464,  423,  464,  464,  464,  464,  423,  423,  464,  464,
 /*    90 */   464,  486,  457,  437,  437,  446,  752,  922,  872,  838,
 /*   100 */   804,  956,  956,  956,  990,  956,  956,  956,  956,  956,
 /*   110 */   956,  956,  956,  956,  956,  956,  956,  956,  956,  956,
 /*   120 */   956,  956,  956,  956,  956,  956,  956, 1198, 1269,  740,
 /*   130 */  1267, 1185, 1323, 1346,  -18,  -18, 1003, 1003,   95,   37,
 /*   140 */    71,  101,  101,  101,   71,  101,  101,  101,  248,  218,
 /*   150 */    15,    4,   23,  215,  195,  191,   93,   51,  -22,  129,
 /*   160 */   307,  307,  431,  433,  425,  430,  405,  429,  416,  408,
 /*   170 */   400,  399,  397,  395,  414,  381,  372,  396,  365,  349,
 /*   180 */   363,  348,  345,  314,  341,  343,  307,  307,  307,  347,
 /*   190 */   338,  337,  336,  328,  333,  331,  351,  329,  313,  317,
 /*   200 */   306,  302,  305,  303,  293,  301,  288,  275,  280,  278,
 /*   210 */   307,  258,  264,  219,  247,  242,  255,  253,  243,  240,
 /*   220 */   231,  235,  229,  237,  219,  230,  192,  227,  225,  224,
 /*   230 */   220,  217,  216,  209,  208,  198,  212,  163,  145,  138,
 /*   240 */   140,  118,  105,  134,  116,  111,   20,
};
#define YY_REDUCE_USE_DFLT (-94)
#define YY_REDUCE_COUNT (95)
#define YY_REDUCE_MIN   (-93)
#define YY_REDUCE_MAX   (1373)
static const short yy_reduce_ofst[] = {
 /*     0 */    50,  461,  403,  342,  284,  223,  165,  104,   46,  -15,
 /*    10 */   -73, 1184,  796, 1271, 1199, 1275,  878,  674,  634,  575,
 /*    20 */   522,   -2,  -35,  761,  236,  203,  179, 1192, 1190,  805,
 /*    30 */   799,  117,   84,   60,  -59,  -93, 1373, 1367, 1366, 1365,
 /*    40 */  1354, 1353, 1347, 1334, 1330, 1328, 1327, 1326, 1314, 1310,
 /*    50 */  1303, 1297, 1296, 1294, 1283, 1191, 1115, 1103, 1069, 1062,
 /*    60 */  1035, 1028, 1001,  994,  967,  879,  845,  469,  434,  417,
 /*    70 */   411,  350,  322,  315,  298,  292,  196,   77,   11,   24,
 /*    80 */    69,  -80,   14,  427,  426,  409,  356,  352,  402,  401,
 /*    90 */   398,  370,  375,  384,  376,  383,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   357,  536,  536,  536,  536,  536,  536,  536,  536,  536,
 /*    10 */   536,  539,  515,  539,  518,  539,  539,  430,  430,  430,
 /*    20 */   430,  419,  419,  539,  539,  539,  539,  539,  539,  539,
 /*    30 */   539,  539,  539,  539,  539,  539,  539,  539,  539,  539,
 /*    40 */   539,  539,  539,  539,  539,  539,  539,  539,  539,  539,
 /*    50 */   539,  539,  539,  539,  539,  539,  539,  539,  539,  539,
 /*    60 */   539,  539,  539,  539,  539,  539,  539,  539,  539,  539,
 /*    70 */   539,  539,  539,  539,  539,  539,  539,  539,  503,  539,
 /*    80 */   413,  539,  413,  539,  539,  539,  538,  537,  539,  539,
 /*    90 */   539,  437,  539,  539,  539,  539,  539,  539,  539,  539,
 /*   100 */   539,  494,  482,  480,  539,  493,  492,  491,  490,  489,
 /*   110 */   488,  487,  486,  485,  484,  478,  428,  444,  539,  417,
 /*   120 */   464,  463,  462,  461,  460,  459,  426,  423,  425,  424,
 /*   130 */   453,  476,  454,  452,  451,  450,  446,  445,  539,  539,
 /*   140 */   495,  457,  456,  455,  539,  449,  448,  447,  539,  468,
 /*   150 */   539,  539,  539,  539,  539,  468,  539,  423,  434,  370,
 /*   160 */   472,  470,  539,  539,  539,  539,  539,  539,  405,  539,
 /*   170 */   539,  539,  539,  539,  519,  539,  539,  514,  539,  539,
 /*   180 */   539,  539,  539,  502,  539,  539,  479,  471,  469,  539,
 /*   190 */   539,  539,  539,  539,  539,  539,  466,  539,  539,  539,
 /*   200 */   539,  539,  539,  539,  539,  539,  539,  539,  539,  539,
 /*   210 */   420,  539,  539,  409,  539,  434,  431,  539,  423,  434,
 /*   220 */   422,  539,  539,  539,  539,  539,  539,  539,  539,  539,
 /*   230 */   539,  539,  539,  539,  539,  539,  414,  371,  539,  539,
 /*   240 */   539,  539,  539,  539,  539,  539,  539,  380,  379,  378,
 /*   250 */   377,  376,  375,  374,  406,  390,  504,  535,  534,  533,
 /*   260 */   529,  528,  527,  526,  525,  524,  523,  522,  517,  516,
 /*   270 */   521,  520,  513,  512,  511,  510,  509,  508,  507,  506,
 /*   280 */   505,  501,  500,  499,  498,  497,  496,  477,  483,  481,
 /*   290 */   531,  432,  433,  458,  438,  436,  532,  530,  467,  465,
 /*   300 */   443,  442,  441,  440,  439,  418,  415,  410,  435,  429,
 /*   310 */   427,  425,  424,  421,  408,  407,  404,  403,  402,  401,
 /*   320 */   400,  399,  398,  416,  397,  396,  395,  394,  393,  392,
 /*   330 */   391,  389,  388,  387,  385,  386,  384,  383,  382,  381,
 /*   340 */   372,  412,  411,  373,  369,  368,  367,  366,  365,  364,
 /*   350 */   363,  362,  361,  360,  359,  358,
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
  "$",             "ASSIGN",        "QMARK",         "COMMA",       
  "LOR",           "LAND",          "LNOT",          "DOUBLE_LNOT", 
  "EQ",            "LE",            "LT",            "GE",          
  "GT",            "NE",            "BITOR",         "BITXOR",      
  "BITAND",        "LSHIFT",        "RSHIFT",        "PLUS",        
  "MINUS",         "DIVIDE",        "MULTIPLY",      "MOD",         
  "UNARY",         "BITNOT",        "NUMBER",        "NAME",        
  "SEMICOLON",     "PERIOD",        "IMPORT",        "AS",          
  "FUNCTION",      "LPAREN",        "RPAREN",        "OBJECT",      
  "LBRACKET",      "VAR",           "RBRACKET",      "LSQBRACKET",  
  "RSQBRACKET",    "KILLS",         "STRING",        "FUNCCALL",    
  "L2V",           "MAPSTRING",     "UNIT",          "SWITCH",      
  "LOCATION",      "COLON",         "CONST",         "INC",         
  "DEC",           "IADD",          "ISUB",          "IMUL",        
  "IDIV",          "IMOD",          "ILSH",          "IRSH",        
  "IBND",          "IBOR",          "IBXR",          "IF",          
  "ELSE",          "WHILE",         "FOR",           "FOREACH",     
  "CONTINUE",      "BREAK",         "RETURN",        "CONDITIONNAME",
  "ACTIONNAME",    "error",         "nt",            "program",     
  "chunks",        "chunk",         "import_chunk",  "fdef_chunk",  
  "fdecl_chunk",   "object_chunk",  "vdef_stmt",     "vdefAssign_global_stmt",
  "cdef_global_stmt",  "blockStmt",     "dottedName",    "fdef_header", 
  "nameList",      "stmt",          "object_header",  "object_body", 
  "nameList_nonEmpty",  "method_header",  "method_chunk",  "bodyStmt",    
  "return_stmt",   "lbracket",      "rbracket",      "bodyStmtList",
  "vdefAssign_stmt",  "cdef_stmt",     "assign_stmt",   "funcexpr",    
  "actionStmt",    "if_stmt",       "while_stmt",    "for_stmt",    
  "foreach_stmt",  "continue_stmt",  "break_stmt",    "numList_nonEmpty",
  "exprList_nonEmpty",  "expr",          "exprList",      "fArgs_nonEmpty",
  "fArgs",         "commaSkippable",  "condition",     "lvalue",      
  "lvalueList_nonEmpty",  "expr_or_condition",  "if_start",      "if_header",   
  "if_block",      "elif_start",    "elif_header",   "else_header", 
  "while_start",   "while_header",  "for_opener",    "for_init_stmt_nonEmpty",
  "for_init_stmt",  "for_action_stmt_nonEmpty",  "for_action_stmt",  "for_header1", 
  "for_header2",   "for_header",    "foreach_opener",  "foreach_header",
  "action",        "actions",       "actionStmt_start",
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
 /*  83 */ "expr ::= L2V LPAREN condition RPAREN",
 /*  84 */ "expr ::= MAPSTRING LPAREN STRING RPAREN",
 /*  85 */ "expr ::= UNIT LPAREN STRING RPAREN",
 /*  86 */ "expr ::= SWITCH LPAREN STRING RPAREN",
 /*  87 */ "expr ::= LOCATION LPAREN STRING RPAREN",
 /*  88 */ "expr ::= condition QMARK expr COLON expr",
 /*  89 */ "expr ::= expr PLUS expr",
 /*  90 */ "expr ::= expr MINUS expr",
 /*  91 */ "expr ::= expr MULTIPLY expr",
 /*  92 */ "expr ::= expr DIVIDE expr",
 /*  93 */ "expr ::= expr MOD expr",
 /*  94 */ "expr ::= expr LSHIFT expr",
 /*  95 */ "expr ::= expr RSHIFT expr",
 /*  96 */ "expr ::= expr BITAND expr",
 /*  97 */ "expr ::= expr BITOR expr",
 /*  98 */ "expr ::= expr BITXOR expr",
 /*  99 */ "expr ::= PLUS expr",
 /* 100 */ "expr ::= MINUS expr",
 /* 101 */ "expr ::= BITNOT expr",
 /* 102 */ "condition ::= LPAREN condition RPAREN",
 /* 103 */ "condition ::= expr EQ expr",
 /* 104 */ "condition ::= expr NE expr",
 /* 105 */ "condition ::= expr LE expr",
 /* 106 */ "condition ::= expr LT expr",
 /* 107 */ "condition ::= expr GE expr",
 /* 108 */ "condition ::= expr GT expr",
 /* 109 */ "condition ::= condition LAND condition",
 /* 110 */ "condition ::= condition LOR condition",
 /* 111 */ "condition ::= LNOT condition",
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
 /* 138 */ "expr_or_condition ::= expr",
 /* 139 */ "expr_or_condition ::= condition",
 /* 140 */ "if_start ::= IF",
 /* 141 */ "if_header ::= if_start LPAREN expr_or_condition RPAREN",
 /* 142 */ "if_block ::= if_header stmt",
 /* 143 */ "elif_start ::= ELSE IF",
 /* 144 */ "elif_header ::= elif_start LPAREN expr_or_condition RPAREN",
 /* 145 */ "if_block ::= if_block elif_header stmt",
 /* 146 */ "else_header ::= ELSE",
 /* 147 */ "if_stmt ::= if_block",
 /* 148 */ "if_stmt ::= if_block else_header stmt",
 /* 149 */ "while_start ::= WHILE",
 /* 150 */ "while_header ::= while_start LPAREN expr_or_condition RPAREN",
 /* 151 */ "while_stmt ::= while_header stmt",
 /* 152 */ "for_opener ::= FOR LPAREN",
 /* 153 */ "for_init_stmt_nonEmpty ::= vdef_stmt",
 /* 154 */ "for_init_stmt_nonEmpty ::= vdefAssign_stmt",
 /* 155 */ "for_init_stmt_nonEmpty ::= cdef_stmt",
 /* 156 */ "for_init_stmt_nonEmpty ::= assign_stmt",
 /* 157 */ "for_init_stmt_nonEmpty ::= for_init_stmt_nonEmpty COMMA for_init_stmt_nonEmpty",
 /* 158 */ "for_init_stmt ::= for_init_stmt_nonEmpty",
 /* 159 */ "for_init_stmt ::=",
 /* 160 */ "for_action_stmt_nonEmpty ::= assign_stmt",
 /* 161 */ "for_action_stmt_nonEmpty ::= for_action_stmt_nonEmpty COMMA for_action_stmt_nonEmpty",
 /* 162 */ "for_action_stmt ::=",
 /* 163 */ "for_action_stmt ::= for_action_stmt_nonEmpty",
 /* 164 */ "for_header1 ::= for_opener for_init_stmt SEMICOLON",
 /* 165 */ "for_header2 ::= for_header1 expr_or_condition SEMICOLON",
 /* 166 */ "for_header ::= for_header2 for_action_stmt RPAREN",
 /* 167 */ "for_stmt ::= for_header stmt",
 /* 168 */ "foreach_opener ::= FOREACH LPAREN",
 /* 169 */ "foreach_header ::= foreach_opener nameList_nonEmpty COLON exprList_nonEmpty RPAREN",
 /* 170 */ "foreach_stmt ::= foreach_header stmt",
 /* 171 */ "continue_stmt ::= CONTINUE",
 /* 172 */ "break_stmt ::= BREAK",
 /* 173 */ "return_stmt ::= RETURN exprList",
 /* 174 */ "condition ::= CONDITIONNAME LPAREN fArgs RPAREN",
 /* 175 */ "condition ::= KILLS LPAREN fArgs RPAREN",
 /* 176 */ "condition ::= CONDITIONNAME LPAREN RPAREN",
 /* 177 */ "action ::= ACTIONNAME LPAREN fArgs RPAREN SEMICOLON",
 /* 178 */ "actions ::= action action",
 /* 179 */ "actions ::= actions action",
 /* 180 */ "actionStmt_start ::=",
 /* 181 */ "actionStmt ::= actionStmt_start action",
 /* 182 */ "actionStmt ::= actionStmt_start actions",
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
    case 74: /* nt */
{
#line 40 "parser\\epparser.lemon"
 delete (yypminor->yy0); 
#line 965 "parser\\epparser.c"
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
  { 75, 1 },
  { 76, 0 },
  { 76, 2 },
  { 77, 2 },
  { 77, 1 },
  { 77, 1 },
  { 77, 1 },
  { 77, 2 },
  { 77, 2 },
  { 77, 2 },
  { 77, 1 },
  { 86, 1 },
  { 86, 3 },
  { 78, 4 },
  { 78, 2 },
  { 87, 5 },
  { 79, 2 },
  { 80, 6 },
  { 90, 3 },
  { 91, 1 },
  { 91, 4 },
  { 93, 5 },
  { 94, 2 },
  { 91, 2 },
  { 81, 3 },
  { 89, 2 },
  { 89, 1 },
  { 89, 2 },
  { 97, 1 },
  { 98, 1 },
  { 85, 2 },
  { 85, 4 },
  { 85, 3 },
  { 85, 5 },
  { 85, 3 },
  { 95, 1 },
  { 95, 1 },
  { 95, 2 },
  { 95, 2 },
  { 95, 2 },
  { 95, 2 },
  { 95, 2 },
  { 95, 1 },
  { 95, 1 },
  { 95, 1 },
  { 95, 1 },
  { 95, 1 },
  { 95, 2 },
  { 95, 2 },
  { 99, 1 },
  { 99, 1 },
  { 99, 2 },
  { 99, 2 },
  { 111, 1 },
  { 111, 3 },
  { 92, 1 },
  { 92, 3 },
  { 88, 0 },
  { 88, 1 },
  { 112, 6 },
  { 113, 6 },
  { 112, 1 },
  { 112, 3 },
  { 114, 0 },
  { 114, 1 },
  { 113, 1 },
  { 113, 1 },
  { 113, 1 },
  { 113, 3 },
  { 113, 4 },
  { 115, 1 },
  { 115, 1 },
  { 115, 3 },
  { 115, 3 },
  { 116, 0 },
  { 116, 1 },
  { 103, 4 },
  { 103, 4 },
  { 113, 1 },
  { 113, 3 },
  { 117, 1 },
  { 117, 0 },
  { 113, 4 },
  { 113, 4 },
  { 113, 4 },
  { 113, 4 },
  { 113, 4 },
  { 113, 4 },
  { 113, 5 },
  { 113, 3 },
  { 113, 3 },
  { 113, 3 },
  { 113, 3 },
  { 113, 3 },
  { 113, 3 },
  { 113, 3 },
  { 113, 3 },
  { 113, 3 },
  { 113, 3 },
  { 113, 2 },
  { 113, 2 },
  { 113, 2 },
  { 118, 3 },
  { 118, 3 },
  { 118, 3 },
  { 118, 3 },
  { 118, 3 },
  { 118, 3 },
  { 118, 3 },
  { 118, 3 },
  { 118, 3 },
  { 118, 2 },
  { 82, 2 },
  { 100, 4 },
  { 83, 4 },
  { 101, 4 },
  { 84, 4 },
  { 119, 1 },
  { 119, 4 },
  { 119, 3 },
  { 120, 1 },
  { 120, 3 },
  { 102, 3 },
  { 102, 3 },
  { 102, 2 },
  { 102, 2 },
  { 102, 2 },
  { 102, 2 },
  { 102, 3 },
  { 102, 3 },
  { 102, 3 },
  { 102, 3 },
  { 102, 3 },
  { 102, 3 },
  { 102, 3 },
  { 102, 3 },
  { 102, 3 },
  { 102, 3 },
  { 121, 1 },
  { 121, 1 },
  { 122, 1 },
  { 123, 4 },
  { 124, 2 },
  { 125, 2 },
  { 126, 4 },
  { 124, 3 },
  { 127, 1 },
  { 105, 1 },
  { 105, 3 },
  { 128, 1 },
  { 129, 4 },
  { 106, 2 },
  { 130, 2 },
  { 131, 1 },
  { 131, 1 },
  { 131, 1 },
  { 131, 1 },
  { 131, 3 },
  { 132, 1 },
  { 132, 0 },
  { 133, 1 },
  { 133, 3 },
  { 134, 0 },
  { 134, 1 },
  { 135, 3 },
  { 136, 3 },
  { 137, 3 },
  { 107, 2 },
  { 138, 2 },
  { 139, 5 },
  { 108, 2 },
  { 109, 1 },
  { 110, 1 },
  { 96, 2 },
  { 118, 4 },
  { 118, 4 },
  { 118, 3 },
  { 140, 5 },
  { 141, 2 },
  { 141, 2 },
  { 142, 0 },
  { 104, 2 },
  { 104, 2 },
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
#line 77 "parser\\epparser.lemon"
{
    throw_error(48993, "Misplaced block statement");
}
#line 1445 "parser\\epparser.c"
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
      case 120: /* lvalueList_nonEmpty ::= lvalue */ yytestcase(yyruleno==120);
#line 83 "parser\\epparser.lemon"
{ yygotominor.yy0 = yymsp[0].minor.yy0; }
#line 1461 "parser\\epparser.c"
        break;
      case 12: /* dottedName ::= dottedName PERIOD NAME */
#line 84 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = yymsp[-2].minor.yy0->data + "." + yymsp[0].minor.yy0->data;
    delete yymsp[-2].minor.yy0;
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1470 "parser\\epparser.c"
        break;
      case 13: /* import_chunk ::= IMPORT dottedName AS NAME */
#line 90 "parser\\epparser.lemon"
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
#line 1486 "parser\\epparser.c"
        break;
      case 14: /* import_chunk ::= IMPORT dottedName */
#line 103 "parser\\epparser.lemon"
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
#line 1502 "parser\\epparser.c"
        break;
      case 15: /* fdef_header ::= FUNCTION NAME LPAREN nameList RPAREN */
#line 117 "parser\\epparser.lemon"
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
#line 1535 "parser\\epparser.c"
        break;
      case 16: /* fdef_chunk ::= fdef_header stmt */
#line 147 "parser\\epparser.lemon"
{
    if(MAP_DEBUG){
        ps->gen << "MDBG_POPF()" << std::endl;
    }
    ps->gen.unindent(true);
    ps->closure.popScope();
    currentFunction = "";
}
#line 1547 "parser\\epparser.c"
        break;
      case 17: /* fdecl_chunk ::= FUNCTION NAME LPAREN nameList RPAREN SEMICOLON */
#line 156 "parser\\epparser.lemon"
{
    // Preprocess yymsp[-4].minor.yy0
    funcNamePreprocess(yymsp[-4].minor.yy0->data);
    if(!ps->closure.declareFunction(yymsp[-4].minor.yy0->data)) {
        throw_error(72461, "Declaring function with non-function yymsp[-4].minor.yy0 " + yymsp[-4].minor.yy0->data, yymsp[-4].minor.yy0->line);
    }
}
#line 1558 "parser\\epparser.c"
        break;
      case 18: /* object_header ::= OBJECT NAME LBRACKET */
#line 167 "parser\\epparser.lemon"
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
#line 1576 "parser\\epparser.c"
        break;
      case 19: /* object_body ::= object_header */
      case 138: /* expr_or_condition ::= expr */ yytestcase(yyruleno==138);
      case 139: /* expr_or_condition ::= condition */ yytestcase(yyruleno==139);
#line 182 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1585 "parser\\epparser.c"
        break;
      case 20: /* object_body ::= object_body VAR nameList_nonEmpty SEMICOLON */
#line 186 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-3].minor.yy0;
    yygotominor.yy0->line = yymsp[-1].minor.yy0->line;
    yygotominor.yy0->data += ", " + yymsp[-1].minor.yy0->data;
    delete yymsp[-1].minor.yy0;
}
#line 1595 "parser\\epparser.c"
        break;
      case 21: /* method_header ::= FUNCTION NAME LPAREN nameList RPAREN */
#line 193 "parser\\epparser.lemon"
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
#line 1635 "parser\\epparser.c"
        break;
      case 22: /* method_chunk ::= method_header stmt */
#line 230 "parser\\epparser.lemon"
{
    if(MAP_DEBUG){
        ps->gen << "MDBG_POPF()" << std::endl;
    }
    ps->gen.unindent(true);
    ps->closure.popScope();
    currentFunction = "";
    yygotominor.yy0 = yymsp[-1].minor.yy0;
}
#line 1648 "parser\\epparser.c"
        break;
      case 23: /* object_body ::= object_body method_chunk */
#line 240 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
    yygotominor.yy0->line = yymsp[0].minor.yy0->line;
    delete yymsp[0].minor.yy0;
}
#line 1657 "parser\\epparser.c"
        break;
      case 24: /* object_chunk ::= object_body RBRACKET SEMICOLON */
#line 246 "parser\\epparser.lemon"
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
#line 1676 "parser\\epparser.c"
        break;
      case 25: /* stmt ::= error SEMICOLON */
#line 263 "parser\\epparser.lemon"
{ throw_error(6974, "Error while parsing statement", yymsp[0].minor.yy0->line); delete yymsp[0].minor.yy0; }
#line 1681 "parser\\epparser.c"
        break;
      case 28: /* lbracket ::= LBRACKET */
#line 269 "parser\\epparser.lemon"
{ ps->closure.pushScope(); }
#line 1686 "parser\\epparser.c"
        break;
      case 29: /* rbracket ::= RBRACKET */
#line 270 "parser\\epparser.lemon"
{ ps->closure.popScope(); }
#line 1691 "parser\\epparser.c"
        break;
      case 30: /* blockStmt ::= lbracket RBRACKET */
#line 272 "parser\\epparser.lemon"
{
    ps->closure.popScope();
}
#line 1698 "parser\\epparser.c"
        break;
      case 34: /* blockStmt ::= lbracket error RBRACKET */
#line 278 "parser\\epparser.lemon"
{
    throw_error(6298, "Block not terminated properly.", yymsp[0].minor.yy0->line);
    ps->closure.popScope();
    delete yymsp[0].minor.yy0;
}
#line 1707 "parser\\epparser.c"
        break;
      case 41: /* bodyStmt ::= funcexpr SEMICOLON */
#line 290 "parser\\epparser.lemon"
{ ps->gen << yymsp[-1].minor.yy0->data << std::endl; }
#line 1712 "parser\\epparser.c"
        break;
      case 49: /* bodyStmtList ::= error */
      case 52: /* bodyStmtList ::= bodyStmtList error */ yytestcase(yyruleno==52);
#line 300 "parser\\epparser.lemon"
{
    throw_error(8510, "Incomplete statement");
}
#line 1720 "parser\\epparser.c"
        break;
      case 54: /* numList_nonEmpty ::= numList_nonEmpty COMMA NUMBER */
      case 56: /* nameList_nonEmpty ::= nameList_nonEmpty COMMA NAME */ yytestcase(yyruleno==56);
      case 121: /* lvalueList_nonEmpty ::= lvalueList_nonEmpty COMMA lvalue */ yytestcase(yyruleno==121);
#line 313 "parser\\epparser.lemon"
{ yygotominor.yy0 = commaConcat(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1727 "parser\\epparser.c"
        break;
      case 57: /* nameList ::= */
      case 63: /* exprList ::= */ yytestcase(yyruleno==63);
      case 74: /* fArgs ::= */ yytestcase(yyruleno==74);
#line 316 "parser\\epparser.lemon"
{ yygotominor.yy0 = genEmpty(); }
#line 1734 "parser\\epparser.c"
        break;
      case 59: /* exprList_nonEmpty ::= funcexpr LSQBRACKET LSQBRACKET numList_nonEmpty RSQBRACKET RSQBRACKET */
#line 319 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "_SRET(" + yymsp[-5].minor.yy0->data + ", [" + yymsp[-2].minor.yy0->data + "])";
    delete yymsp[-5].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1743 "parser\\epparser.c"
        break;
      case 60: /* expr ::= funcexpr LSQBRACKET LSQBRACKET NUMBER RSQBRACKET RSQBRACKET */
#line 326 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-5].minor.yy0->data + "[" + yymsp[-2].minor.yy0->data + "]";
    delete yymsp[-5].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1752 "parser\\epparser.c"
        break;
      case 62: /* exprList_nonEmpty ::= exprList_nonEmpty COMMA exprList_nonEmpty */
#line 334 "parser\\epparser.lemon"
{ yygotominor.yy0 = new Token((yymsp[-2].minor.yy0->data) + ", " + (yymsp[0].minor.yy0->data), yymsp[0].minor.yy0); delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1757 "parser\\epparser.c"
        break;
      case 66: /* expr ::= KILLS */
#line 341 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = "4";
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1765 "parser\\epparser.c"
        break;
      case 67: /* expr ::= NAME */
#line 346 "parser\\epparser.lemon"
{
    checkIsRValue(yymsp[0].minor.yy0->data, yymsp[0].minor.yy0->line);
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1773 "parser\\epparser.c"
        break;
      case 68: /* expr ::= expr PERIOD NAME */
#line 351 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + "." + yymsp[0].minor.yy0->data;
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1782 "parser\\epparser.c"
        break;
      case 69: /* expr ::= expr LSQBRACKET expr RSQBRACKET */
#line 357 "parser\\epparser.lemon"
{
    yymsp[-3].minor.yy0->data = yymsp[-3].minor.yy0->data + "[" + yymsp[-1].minor.yy0->data + "]";
    delete yymsp[-1].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 1791 "parser\\epparser.c"
        break;
      case 72: /* fArgs_nonEmpty ::= NAME ASSIGN expr */
#line 366 "parser\\epparser.lemon"
{  // Keyword argument
    yymsp[0].minor.yy0->data = yymsp[-2].minor.yy0->data + "=" + yymsp[0].minor.yy0->data;
    yymsp[0].minor.yy0->type = TOKEN_TEMP;
    yygotominor.yy0 = yymsp[0].minor.yy0;
    delete yymsp[-2].minor.yy0;
}
#line 1801 "parser\\epparser.c"
        break;
      case 73: /* fArgs_nonEmpty ::= fArgs_nonEmpty COMMA fArgs_nonEmpty */
#line 373 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data;
    yymsp[0].minor.yy0->type = TOKEN_TEMP;
    yygotominor.yy0 = yymsp[0].minor.yy0;
    delete yymsp[-2].minor.yy0;
}
#line 1811 "parser\\epparser.c"
        break;
      case 76: /* funcexpr ::= NAME LPAREN fArgs RPAREN */
#line 383 "parser\\epparser.lemon"
{
    functionCalledInMultipleActions = true;

    // Preprocess yymsp[-3].minor.yy0
    funcNamePreprocess(yymsp[-3].minor.yy0->data);
    checkIsFunction(yymsp[-3].minor.yy0->data, yymsp[-3].minor.yy0->line);
    yymsp[-3].minor.yy0->data += "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 1824 "parser\\epparser.c"
        break;
      case 77: /* funcexpr ::= expr LPAREN fArgs RPAREN */
#line 393 "parser\\epparser.lemon"
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
#line 1848 "parser\\epparser.c"
        break;
      case 79: /* expr ::= LPAREN expr RPAREN */
      case 102: /* condition ::= LPAREN condition RPAREN */ yytestcase(yyruleno==102);
#line 421 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1857 "parser\\epparser.c"
        break;
      case 82: /* expr ::= LSQBRACKET exprList commaSkippable RSQBRACKET */
#line 429 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "_ARR(FlattenList([" + yymsp[-2].minor.yy0->data + "]))";
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1865 "parser\\epparser.c"
        break;
      case 83: /* expr ::= L2V LPAREN condition RPAREN */
#line 434 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "_L2V(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1873 "parser\\epparser.c"
        break;
      case 84: /* expr ::= MAPSTRING LPAREN STRING RPAREN */
#line 439 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetStringIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1881 "parser\\epparser.c"
        break;
      case 85: /* expr ::= UNIT LPAREN STRING RPAREN */
#line 444 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "EncodeUnit(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1889 "parser\\epparser.c"
        break;
      case 86: /* expr ::= SWITCH LPAREN STRING RPAREN */
#line 449 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "EncodeSwitch(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1897 "parser\\epparser.c"
        break;
      case 87: /* expr ::= LOCATION LPAREN STRING RPAREN */
#line 454 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetLocationIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1905 "parser\\epparser.c"
        break;
      case 88: /* expr ::= condition QMARK expr COLON expr */
#line 460 "parser\\epparser.lemon"
{
    std::stringstream ss;
    ss << "EUDTernary";
    applyNegativeOptimization(ss, yymsp[-4].minor.yy0);
    ss << "(" << yymsp[-2].minor.yy0->data << ")(" << yymsp[0].minor.yy0->data << ")";
    yymsp[0].minor.yy0->data = ss.str();
    delete yymsp[-4].minor.yy0;
    delete yymsp[-2].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0);
}
#line 1919 "parser\\epparser.c"
        break;
      case 89: /* expr ::= expr PLUS expr */
#line 472 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "+",  yymsp[0].minor.yy0); }
#line 1924 "parser\\epparser.c"
        break;
      case 90: /* expr ::= expr MINUS expr */
#line 473 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "-",  yymsp[0].minor.yy0); }
#line 1929 "parser\\epparser.c"
        break;
      case 91: /* expr ::= expr MULTIPLY expr */
#line 474 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "*",  yymsp[0].minor.yy0); }
#line 1934 "parser\\epparser.c"
        break;
      case 92: /* expr ::= expr DIVIDE expr */
#line 475 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "//", yymsp[0].minor.yy0); }
#line 1939 "parser\\epparser.c"
        break;
      case 93: /* expr ::= expr MOD expr */
#line 476 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "%",  yymsp[0].minor.yy0); }
#line 1944 "parser\\epparser.c"
        break;
      case 94: /* expr ::= expr LSHIFT expr */
#line 477 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = "_LSH(" + yymsp[-2].minor.yy0->data + "," + yymsp[0].minor.yy0->data + ")";
    delete yymsp[-2].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0);
}
#line 1953 "parser\\epparser.c"
        break;
      case 95: /* expr ::= expr RSHIFT expr */
#line 482 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, ">>", yymsp[0].minor.yy0); }
#line 1958 "parser\\epparser.c"
        break;
      case 96: /* expr ::= expr BITAND expr */
#line 483 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "&",  yymsp[0].minor.yy0); }
#line 1963 "parser\\epparser.c"
        break;
      case 97: /* expr ::= expr BITOR expr */
#line 484 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "|",  yymsp[0].minor.yy0); }
#line 1968 "parser\\epparser.c"
        break;
      case 98: /* expr ::= expr BITXOR expr */
#line 485 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "^",  yymsp[0].minor.yy0); }
#line 1973 "parser\\epparser.c"
        break;
      case 99: /* expr ::= PLUS expr */
#line 488 "parser\\epparser.lemon"
{ yymsp[0].minor.yy0->data = "+" + yymsp[0].minor.yy0->data; yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0); }
#line 1978 "parser\\epparser.c"
        break;
      case 100: /* expr ::= MINUS expr */
#line 489 "parser\\epparser.lemon"
{ yymsp[0].minor.yy0->data = "-" + yymsp[0].minor.yy0->data; yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0); }
#line 1983 "parser\\epparser.c"
        break;
      case 101: /* expr ::= BITNOT expr */
#line 490 "parser\\epparser.lemon"
{ yymsp[0].minor.yy0->data = "~" + yymsp[0].minor.yy0->data; yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0); }
#line 1988 "parser\\epparser.c"
        break;
      case 103: /* condition ::= expr EQ expr */
#line 499 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "==", yymsp[0].minor.yy0); }
#line 1993 "parser\\epparser.c"
        break;
      case 104: /* condition ::= expr NE expr */
#line 500 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genEmpty();
    yygotominor.yy0->line = yymsp[0].minor.yy0->line;

    yygotominor.yy0->type = TOKEN_NE;
    yygotominor.yy0->subToken[0] = yymsp[-2].minor.yy0;
    yygotominor.yy0->subToken[1] = yymsp[0].minor.yy0;
    yygotominor.yy0->data = yymsp[-2].minor.yy0->data + " != " + yymsp[0].minor.yy0->data;
}
#line 2006 "parser\\epparser.c"
        break;
      case 105: /* condition ::= expr LE expr */
#line 510 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "<=", yymsp[0].minor.yy0); }
#line 2011 "parser\\epparser.c"
        break;
      case 106: /* condition ::= expr LT expr */
#line 511 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "<",  yymsp[0].minor.yy0); }
#line 2016 "parser\\epparser.c"
        break;
      case 107: /* condition ::= expr GE expr */
#line 512 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, ">=", yymsp[0].minor.yy0); }
#line 2021 "parser\\epparser.c"
        break;
      case 108: /* condition ::= expr GT expr */
#line 513 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, ">" , yymsp[0].minor.yy0); }
#line 2026 "parser\\epparser.c"
        break;
      case 109: /* condition ::= condition LAND condition */
#line 516 "parser\\epparser.lemon"
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
#line 2045 "parser\\epparser.c"
        break;
      case 110: /* condition ::= condition LOR condition */
#line 533 "parser\\epparser.lemon"
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
#line 2064 "parser\\epparser.c"
        break;
      case 111: /* condition ::= LNOT condition */
#line 549 "parser\\epparser.lemon"
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
#line 2082 "parser\\epparser.c"
        break;
      case 112: /* vdef_stmt ::= VAR nameList_nonEmpty */
#line 566 "parser\\epparser.lemon"
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
#line 2106 "parser\\epparser.c"
        break;
      case 113: /* vdefAssign_stmt ::= VAR nameList_nonEmpty ASSIGN exprList_nonEmpty */
#line 587 "parser\\epparser.lemon"
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
#line 2131 "parser\\epparser.c"
        break;
      case 114: /* vdefAssign_global_stmt ::= VAR nameList_nonEmpty ASSIGN exprList_nonEmpty */
#line 609 "parser\\epparser.lemon"
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
#line 2151 "parser\\epparser.c"
        break;
      case 115: /* cdef_stmt ::= CONST nameList_nonEmpty ASSIGN exprList_nonEmpty */
#line 626 "parser\\epparser.lemon"
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
#line 2173 "parser\\epparser.c"
        break;
      case 116: /* cdef_global_stmt ::= CONST nameList_nonEmpty ASSIGN exprList_nonEmpty */
#line 645 "parser\\epparser.lemon"
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
#line 2195 "parser\\epparser.c"
        break;
      case 117: /* lvalue ::= NAME */
#line 665 "parser\\epparser.lemon"
{
    checkIsVariable(yymsp[0].minor.yy0->data, yymsp[0].minor.yy0->line);
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 2203 "parser\\epparser.c"
        break;
      case 118: /* lvalue ::= expr LSQBRACKET expr RSQBRACKET */
#line 670 "parser\\epparser.lemon"
{
    checkIsConstant(yymsp[-3].minor.yy0->data, yymsp[-3].minor.yy0->line);
    yymsp[-1].minor.yy0->data = "_ARRW(" + yymsp[-3].minor.yy0->data + ", " + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
    delete yymsp[-3].minor.yy0;
}
#line 2213 "parser\\epparser.c"
        break;
      case 119: /* lvalue ::= expr PERIOD NAME */
#line 677 "parser\\epparser.lemon"
{
    checkIsConstant(yymsp[-2].minor.yy0->data, yymsp[-2].minor.yy0->line);
    yymsp[0].minor.yy0->data = "_ATTW(" + yymsp[-2].minor.yy0->data + ", '" + yymsp[0].minor.yy0->data + "')";
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0);
    delete yymsp[-2].minor.yy0;
}
#line 2223 "parser\\epparser.c"
        break;
      case 122: /* assign_stmt ::= lvalue ASSIGN expr */
#line 686 "parser\\epparser.lemon"
{
    ps->gen << yymsp[-2].minor.yy0->data << " << (" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 2231 "parser\\epparser.c"
        break;
      case 123: /* assign_stmt ::= lvalueList_nonEmpty ASSIGN exprList_nonEmpty */
#line 691 "parser\\epparser.lemon"
{
    ps->gen << "_SV([" << yymsp[-2].minor.yy0->data << "], [" << yymsp[0].minor.yy0->data << "])" << std::endl;
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 2239 "parser\\epparser.c"
        break;
      case 124: /* assign_stmt ::= INC expr */
#line 699 "parser\\epparser.lemon"
{ ps->gen << yymsp[0].minor.yy0->data << ".__iadd__(1)" << std::endl; delete yymsp[0].minor.yy0; }
#line 2244 "parser\\epparser.c"
        break;
      case 125: /* assign_stmt ::= expr INC */
#line 700 "parser\\epparser.lemon"
{ ps->gen << yymsp[-1].minor.yy0->data << ".__iadd__(1)" << std::endl; delete yymsp[-1].minor.yy0; }
#line 2249 "parser\\epparser.c"
        break;
      case 126: /* assign_stmt ::= DEC expr */
#line 701 "parser\\epparser.lemon"
{ ps->gen << yymsp[0].minor.yy0->data << ".__isub__(1)" << std::endl; delete yymsp[0].minor.yy0; }
#line 2254 "parser\\epparser.c"
        break;
      case 127: /* assign_stmt ::= expr DEC */
#line 702 "parser\\epparser.lemon"
{ ps->gen << yymsp[-1].minor.yy0->data << ".__isub__(1)" << std::endl; delete yymsp[-1].minor.yy0; }
#line 2259 "parser\\epparser.c"
        break;
      case 128: /* assign_stmt ::= lvalue IADD expr */
#line 703 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__iadd__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2264 "parser\\epparser.c"
        break;
      case 129: /* assign_stmt ::= lvalue ISUB expr */
#line 704 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__isub__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2269 "parser\\epparser.c"
        break;
      case 130: /* assign_stmt ::= lvalue IMUL expr */
#line 705 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__imul__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2274 "parser\\epparser.c"
        break;
      case 131: /* assign_stmt ::= lvalue IDIV expr */
#line 706 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ifloordiv__("  << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2279 "parser\\epparser.c"
        break;
      case 132: /* assign_stmt ::= lvalue IMOD expr */
#line 707 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__imod__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2284 "parser\\epparser.c"
        break;
      case 133: /* assign_stmt ::= lvalue ILSH expr */
#line 708 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ilshift__("    << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2289 "parser\\epparser.c"
        break;
      case 134: /* assign_stmt ::= lvalue IRSH expr */
#line 709 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__irshift__("    << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2294 "parser\\epparser.c"
        break;
      case 135: /* assign_stmt ::= lvalue IBND expr */
#line 710 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__iand__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2299 "parser\\epparser.c"
        break;
      case 136: /* assign_stmt ::= lvalue IBOR expr */
#line 711 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ior__("        << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2304 "parser\\epparser.c"
        break;
      case 137: /* assign_stmt ::= lvalue IBXR expr */
#line 712 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ixor__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2309 "parser\\epparser.c"
        break;
      case 140: /* if_start ::= IF */
#line 723 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDIf()" << std::endl;
}
#line 2317 "parser\\epparser.c"
        break;
      case 141: /* if_header ::= if_start LPAREN expr_or_condition RPAREN */
      case 144: /* elif_header ::= elif_start LPAREN expr_or_condition RPAREN */ yytestcase(yyruleno==144);
      case 150: /* while_header ::= while_start LPAREN expr_or_condition RPAREN */ yytestcase(yyruleno==150);
#line 728 "parser\\epparser.lemon"
{
    writeCsOpener(*pGen, yymsp[-3].minor.yy0, yymsp[-1].minor.yy0);
    ps->gen.indent();
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 2328 "parser\\epparser.c"
        break;
      case 143: /* elif_start ::= ELSE IF */
#line 736 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen.unindent(false);
    ps->gen << yygotominor.yy0->data << " = EUDElseIf()" << std::endl;
}
#line 2337 "parser\\epparser.c"
        break;
      case 146: /* else_header ::= ELSE */
#line 750 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "if EUDElse()():" << std::endl;
    ps->gen.indent();
}
#line 2346 "parser\\epparser.c"
        break;
      case 147: /* if_stmt ::= if_block */
      case 148: /* if_stmt ::= if_block else_header stmt */ yytestcase(yyruleno==148);
#line 756 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndIf()" << std::endl;
}
#line 2355 "parser\\epparser.c"
        break;
      case 149: /* while_start ::= WHILE */
#line 768 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDWhile()" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2364 "parser\\epparser.c"
        break;
      case 151: /* while_stmt ::= while_header stmt */
#line 780 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndWhile()" << std::endl;
}
#line 2372 "parser\\epparser.c"
        break;
      case 152: /* for_opener ::= FOR LPAREN */
      case 168: /* foreach_opener ::= FOREACH LPAREN */ yytestcase(yyruleno==168);
#line 786 "parser\\epparser.lemon"
{
    ps->closure.pushScope();
}
#line 2380 "parser\\epparser.c"
        break;
      case 164: /* for_header1 ::= for_opener for_init_stmt SEMICOLON */
#line 804 "parser\\epparser.lemon"
{
    // opening for condition
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDWhile()" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2390 "parser\\epparser.c"
        break;
      case 165: /* for_header2 ::= for_header1 expr_or_condition SEMICOLON */
#line 811 "parser\\epparser.lemon"
{
    writeCsOpener(*pGen, yymsp[-2].minor.yy0, yymsp[-1].minor.yy0);
    ps->gen.indent();
    delete yymsp[-2].minor.yy0; delete yymsp[-1].minor.yy0;

    // Opening for assign_statement
    yygotominor.yy0 = genTemp(yymsp[-1].minor.yy0);
    ps->gen << "def " << yygotominor.yy0->data <<"():" << std::endl;
    ps->gen.indent();
}
#line 2404 "parser\\epparser.c"
        break;
      case 166: /* for_header ::= for_header2 for_action_stmt RPAREN */
#line 822 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-2].minor.yy0;
    ps->gen.unindent(false);
}
#line 2412 "parser\\epparser.c"
        break;
      case 167: /* for_stmt ::= for_header stmt */
#line 827 "parser\\epparser.lemon"
{
    ps->gen << "EUDSetContinuePoint()" << std::endl;
    ps->gen << yymsp[-1].minor.yy0->data << "()" << std::endl;
    ps->gen.unindent(false);
    ps->gen << "EUDEndWhile()" << std::endl;
    ps->closure.popScope();
}
#line 2423 "parser\\epparser.c"
        break;
      case 169: /* foreach_header ::= foreach_opener nameList_nonEmpty COLON exprList_nonEmpty RPAREN */
#line 842 "parser\\epparser.lemon"
{
    commaListIter(yymsp[-3].minor.yy0->data, [&](std::string& s) {
        ps->closure.defVariable(s);
    });
    ps->gen << "for " << yymsp[-3].minor.yy0->data << " in " << yymsp[-1].minor.yy0->data << ":" << std::endl;
    ps->gen.indent();
}
#line 2434 "parser\\epparser.c"
        break;
      case 170: /* foreach_stmt ::= foreach_header stmt */
#line 850 "parser\\epparser.lemon"
{
    ps->gen.unindent(true);
    ps->closure.popScope();
}
#line 2442 "parser\\epparser.c"
        break;
      case 171: /* continue_stmt ::= CONTINUE */
#line 858 "parser\\epparser.lemon"
{
    ps->gen << "EUDContinue()" << std::endl;
}
#line 2449 "parser\\epparser.c"
        break;
      case 172: /* break_stmt ::= BREAK */
#line 862 "parser\\epparser.lemon"
{
    ps->gen << "EUDBreak()" << std::endl;
}
#line 2456 "parser\\epparser.c"
        break;
      case 173: /* return_stmt ::= RETURN exprList */
#line 869 "parser\\epparser.lemon"
{
    if(MAP_DEBUG){
        ps->gen << "MDBG_POPF()" << std::endl;
    }
    ps->gen << "EUDReturn(" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2467 "parser\\epparser.c"
        break;
      case 174: /* condition ::= CONDITIONNAME LPAREN fArgs RPAREN */
      case 175: /* condition ::= KILLS LPAREN fArgs RPAREN */ yytestcase(yyruleno==175);
#line 880 "parser\\epparser.lemon"
{
    yymsp[-3].minor.yy0->data = yymsp[-3].minor.yy0->data + "(" + yymsp[-1].minor.yy0->data + ")";
    delete yymsp[-1].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 2477 "parser\\epparser.c"
        break;
      case 176: /* condition ::= CONDITIONNAME LPAREN RPAREN */
#line 892 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + "()";
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 2485 "parser\\epparser.c"
        break;
      case 177: /* action ::= ACTIONNAME LPAREN fArgs RPAREN SEMICOLON */
#line 897 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[-4].minor.yy0);
    yygotominor.yy0->data =  yymsp[-4].minor.yy0->data + "(" + yymsp[-2].minor.yy0->data + ")";
    delete yymsp[-4].minor.yy0; delete yymsp[-2].minor.yy0;
}
#line 2494 "parser\\epparser.c"
        break;
      case 178: /* actions ::= action action */
      case 179: /* actions ::= actions action */ yytestcase(yyruleno==179);
#line 903 "parser\\epparser.lemon"
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
#line 2517 "parser\\epparser.c"
        break;
      case 180: /* actionStmt_start ::= */
#line 941 "parser\\epparser.lemon"
{
    functionCalledInMultipleActions = false;
}
#line 2524 "parser\\epparser.c"
        break;
      case 181: /* actionStmt ::= actionStmt_start action */
#line 945 "parser\\epparser.lemon"
{
    ps->gen << "DoActions(" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2532 "parser\\epparser.c"
        break;
      case 182: /* actionStmt ::= actionStmt_start actions */
#line 950 "parser\\epparser.lemon"
{
    ps->gen << "DoActions([" << std::endl;
    ps->gen.indent();
    ps->gen << yymsp[0].minor.yy0->data << std::endl;
    ps->gen.unindent(false);
    ps->gen << "])" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2544 "parser\\epparser.c"
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
      /* (142) if_block ::= if_header stmt */ yytestcase(yyruleno==142);
      /* (145) if_block ::= if_block elif_header stmt */ yytestcase(yyruleno==145);
      /* (153) for_init_stmt_nonEmpty ::= vdef_stmt */ yytestcase(yyruleno==153);
      /* (154) for_init_stmt_nonEmpty ::= vdefAssign_stmt */ yytestcase(yyruleno==154);
      /* (155) for_init_stmt_nonEmpty ::= cdef_stmt */ yytestcase(yyruleno==155);
      /* (156) for_init_stmt_nonEmpty ::= assign_stmt */ yytestcase(yyruleno==156);
      /* (157) for_init_stmt_nonEmpty ::= for_init_stmt_nonEmpty COMMA for_init_stmt_nonEmpty */ yytestcase(yyruleno==157);
      /* (158) for_init_stmt ::= for_init_stmt_nonEmpty */ yytestcase(yyruleno==158);
      /* (159) for_init_stmt ::= */ yytestcase(yyruleno==159);
      /* (160) for_action_stmt_nonEmpty ::= assign_stmt */ yytestcase(yyruleno==160);
      /* (161) for_action_stmt_nonEmpty ::= for_action_stmt_nonEmpty COMMA for_action_stmt_nonEmpty */ yytestcase(yyruleno==161);
      /* (162) for_action_stmt ::= */ yytestcase(yyruleno==162);
      /* (163) for_action_stmt ::= for_action_stmt_nonEmpty */ yytestcase(yyruleno==163);
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
#line 2640 "parser\\epparser.c"
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
#line 964 "parser\\epparser.lemon"


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
#line 2936 "parser\\epparser.c"
