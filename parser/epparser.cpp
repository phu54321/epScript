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
#define YYNOCODE 143
#define YYACTIONTYPE unsigned short int
#define ParseTOKENTYPE Token*
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  int yy285;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL  ParserStruct* ps ;
#define ParseARG_PDECL , ParserStruct* ps 
#define ParseARG_FETCH  ParserStruct* ps  = yypParser->ps 
#define ParseARG_STORE yypParser->ps  = ps 
#define YYNSTATE 354
#define YYNRULE 181
#define YYERRORSYMBOL 73
#define YYERRSYMDT yy285
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
#define YY_ACTTAB_COUNT (1486)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   232,   74,   73,   71,   72,   70,  322,  210,  167,  228,
 /*    10 */   213,  215,  328,   85,  164,   18,  338,  224,  352,  303,
 /*    20 */   118,   76,  336,  231,    2,  146,  233,  227,  226,  225,
 /*    30 */   160,  320,  319,  318,  317,  316,  220,  219,   77,  240,
 /*    40 */    96,  239,  267,  217,  209,  146,  130,  155,  183,    9,
 /*    50 */    78,  249,  348,   96,  180,    7,   12,  232,  146,  130,
 /*    60 */   155,   32,   14,    6,   88,    5,  228,  213,   81,  328,
 /*    70 */    19,  236,  266,  282,  347,  234,  208,  118,   91,  336,
 /*    80 */   231,    2,  146,  233,  227,  226,  225,  160,  320,  319,
 /*    90 */   318,  317,  316,  220,  219,  346,   57,   96,   54,   55,
 /*   100 */   213,  343,  146,  130,  155,  183,    9,   78,   31,  186,
 /*   110 */   118,  180,    7,   12,  232,  146,  342,  217,   32,   14,
 /*   120 */     6,   88,    5,  228,  237,   81,  328,  115,  302,   26,
 /*   130 */   279,   57,  146,   54,   55,   82,  336,  231,    2,  262,
 /*   140 */   235,  227,  226,  225,  160,  320,  319,  318,  317,  316,
 /*   150 */   220,  219,  341,   57,   96,   54,   55,  268,  339,  146,
 /*   160 */   130,  155,  183,    9,   78,   30,  233,  233,  180,    7,
 /*   170 */    12,  232,  181,    8,    4,   32,   14,    6,   88,    5,
 /*   180 */   228,  213,   81,  328,  337,  291,   57,  276,   54,   55,
 /*   190 */   208,  118,  258,  336,  231,    2,  146,  335,  227,  226,
 /*   200 */   225,  160,  320,  319,  318,  317,  316,  220,  219,   94,
 /*   210 */    57,   96,   54,   55,  213,   93,  146,  130,  155,  183,
 /*   220 */     9,   78,  326,  185,  118,  180,    7,   12,  232,  146,
 /*   230 */   325,  217,   32,   14,    6,   88,    5,  228,  217,   81,
 /*   240 */   328,  100,  283,  324,  264,  165,  146,  323,  103,  234,
 /*   250 */   336,  231,    2,  146,  285,  227,  226,  225,  160,  320,
 /*   260 */   319,  318,  317,  316,  220,  219,  223,   57,   96,   54,
 /*   270 */    55,   87,   86,  146,  130,  155,  183,    9,   78,   29,
 /*   280 */   222,  233,  180,    7,   12,  232,   27,  221,   28,   32,
 /*   290 */    14,    6,   88,    5,  228,  213,   81,  328,   25,  280,
 /*   300 */   233,  261,    3,  246,  184,  118,  321,  336,  231,    2,
 /*   310 */   146,  315,  227,  226,  225,  160,  320,  319,  318,  317,
 /*   320 */   316,  220,  219,  314,   57,   96,   54,   55,  213,   20,
 /*   330 */   146,  130,  155,  183,    9,   78,   19,  153,  118,  180,
 /*   340 */     7,   12,  232,  146,  224,  217,   32,   14,    6,   88,
 /*   350 */     5,  228,  213,   81,  328,   99,  277,  310,  254,  212,
 /*   360 */   141,  163,  118,   92,  336,  231,    2,  146,   23,  227,
 /*   370 */   226,  225,  160,  320,  319,  318,  317,  316,  220,  219,
 /*   380 */   305,   24,   96,  233,  536,   11,  304,  146,  130,  155,
 /*   390 */   183,    9,   78,   31,   58,  205,  180,    7,   12,  232,
 /*   400 */   204,  301,  202,   32,   14,    6,   88,    5,  228,  213,
 /*   410 */    81,  328,  201,  300,  199,  247,  198,  196,  162,  118,
 /*   420 */   299,  336,  231,    2,  146,  298,  227,  226,  225,  160,
 /*   430 */   320,  319,  318,  317,  316,  220,  219,  195,   55,   96,
 /*   440 */    16,  292,  217,  295,  146,  130,  155,  183,    9,   78,
 /*   450 */   290,  289,  136,  180,    7,   12,  170,  146,  288,  217,
 /*   460 */    32,   14,    6,   88,    5,  228,  215,   81,  328,  135,
 /*   470 */    18,  128,   35,  281,  146,   34,   76,   13,  252,  230,
 /*   480 */     2,   33,    1,  227,  226,  225,  160,  320,  319,  318,
 /*   490 */   317,  316,  220,  219,  275,  269,   96,   15,  265,  263,
 /*   500 */   257,  146,  130,  155,  183,    9,   78,  171,   17,  253,
 /*   510 */   180,    7,   12,  312,  168,  251,  166,   32,   14,    6,
 /*   520 */    88,    5,  228,   80,   81,  328,  248,  245,  344,  161,
 /*   530 */   331,  332,  329,  158,  211,  313,  229,    2,  330,  293,
 /*   540 */   227,  226,  225,  160,  320,  319,  318,  317,  316,  220,
 /*   550 */   219,  157,  191,   96,  340,  156,  173,  154,  146,  130,
 /*   560 */   155,  183,    9,   78,  256,  255,   50,  180,    7,   12,
 /*   570 */   152,  182,  151,  150,   32,   14,    6,   88,    5,   53,
 /*   580 */    52,   81,   71,   72,   70,   51,  311,  126,  327,  537,
 /*   590 */   215,  537,  537,   75,   18,  537,  334,   90,  333,   22,
 /*   600 */    76,  218,  537,  537,  207,  206,  203,  200,  197,  537,
 /*   610 */    89,   37,   36,  537,  537,  537,  537,  537,  537,   50,
 /*   620 */   537,  537,  537,  284,  537,  278,  179,  174,  260,  259,
 /*   630 */    21,  193,   53,   52,  537,  537,  537,  537,   51,  311,
 /*   640 */   126,  327,  537,  537,  537,  537,   75,  537,  537,  334,
 /*   650 */    90,  332,   22,  537,  218,  537,  537,  207,  206,  203,
 /*   660 */   200,  197,  537,   89,   37,   36,  537,  537,  537,  537,
 /*   670 */   537,  537,   50,  537,  537,  537,  284,  537,  278,  179,
 /*   680 */   174,  260,  259,   21,  193,   53,   52,  537,  537,  537,
 /*   690 */   537,   51,  311,  126,  327,  537,  537,  537,  537,   75,
 /*   700 */   537,  537,  334,   90,  537,   22,  537,  218,  537,  537,
 /*   710 */   207,  206,  203,  200,  197,  217,   89,   37,   36,  473,
 /*   720 */   537,  473,  537,  537,  537,  125,  537,  214,  188,  284,
 /*   730 */   146,  278,  179,  174,  260,  259,   21,  193,   64,   62,
 /*   740 */    61,   60,   59,   63,   66,   65,   67,   69,   68,   74,
 /*   750 */    73,   71,   72,   70,  537,  217,  537,  537,  537,  187,
 /*   760 */   537,  537,  537,   18,  537,  125,  537,  214,  189,   49,
 /*   770 */   146,  473,  473,  473,  473,  473,  473,  473,  473,  473,
 /*   780 */   473,  287,  286,  537,  537,  537,  537,  537,  537,  537,
 /*   790 */    64,   62,   61,   60,   59,   63,   66,   65,   67,   69,
 /*   800 */    68,   74,   73,   71,   72,   70,  537,  537,  537,  537,
 /*   810 */   537,  215,  537,  537,  537,   18,  537,  537,  537,  537,
 /*   820 */   537,   76,  309,  537,   64,   62,   61,   60,   59,   63,
 /*   830 */    66,   65,   67,   69,   68,   74,   73,   71,   72,   70,
 /*   840 */   537,  537,  217,  537,  537,  215,  537,  537,  537,   18,
 /*   850 */   306,  537,  125,  537,  307,   76,  274,  146,   64,   62,
 /*   860 */    61,   60,   59,   63,   66,   65,   67,   69,   68,   74,
 /*   870 */    73,   71,   72,   70,  273,  272,  271,  217,  537,  215,
 /*   880 */   217,  217,  537,   18,  537,  537,  537,   96,  537,   76,
 /*   890 */   149,  148,  146,  130,  155,  146,  146,  537,  537,   56,
 /*   900 */   537,  537,  537,  537,  178,  177,  537,  537,   64,   62,
 /*   910 */    61,   60,   59,   63,   66,   65,   67,   69,   68,   74,
 /*   920 */    73,   71,   72,   70,  537,  537,  217,  537,  537,  215,
 /*   930 */   537,  537,  537,   18,  537,  537,  147,  537,  537,   76,
 /*   940 */   127,  146,   64,   62,   61,   60,   59,   63,   66,   65,
 /*   950 */    67,   69,   68,   74,   73,   71,   72,   70,  537,  217,
 /*   960 */   217,  537,  537,  215,  537,  537,  537,   18,  537,  125,
 /*   970 */   134,  214,  190,   76,  146,  146,   64,   62,   61,   60,
 /*   980 */    59,   63,   66,   65,   67,   69,   68,   74,   73,   71,
 /*   990 */    72,   70,   50,  217,  217,  537,  537,  187,  537,  537,
 /*  1000 */   217,   18,  537,  133,  132,   53,   52,   49,  146,  146,
 /*  1010 */   129,   51,  311,  126,  217,  146,  537,  537,  537,   75,
 /*  1020 */   537,  537,  537,   90,  131,   22,   50,  218,  537,  146,
 /*  1030 */   207,  206,  203,  200,  197,  537,   89,   37,   36,   53,
 /*  1040 */    52,  537,  537,  537,  537,   51,  311,  159,  217,  537,
 /*  1050 */   537,  537,  537,   75,  294,  537,  537,  193,  124,   22,
 /*  1060 */    50,  218,  308,  146,  207,  206,  203,  200,  197,  537,
 /*  1070 */   537,  537,  537,   53,   52,  217,  537,  537,  537,   51,
 /*  1080 */   311,  126,  217,  537,  537,  123,  537,   75,  537,  537,
 /*  1090 */   146,  193,  122,   22,   50,  218,  537,  146,  207,  206,
 /*  1100 */   203,  200,  197,  537,  537,   37,   36,   53,   52,  217,
 /*  1110 */   537,  537,  537,   51,  311,  159,  217,  537,  537,  121,
 /*  1120 */   537,   75,  537,  537,  146,  193,  120,   22,   50,  218,
 /*  1130 */   308,  146,  207,  206,  203,  200,  197,  537,  537,  537,
 /*  1140 */   537,   53,   52,  217,  537,  537,  537,   51,  311,  216,
 /*  1150 */   217,  537,  537,  119,  537,   75,  537,  537,  146,  193,
 /*  1160 */   117,   22,   50,  218,   48,  142,  207,  206,  203,  200,
 /*  1170 */   197,  537,  537,  537,  537,   53,   52,  471,  537,  471,
 /*  1180 */   537,   51,  311,  126,  217,  537,  537,  537,  537,   75,
 /*  1190 */   537,  537,  537,  193,   98,   22,  537,  218,  217,  146,
 /*  1200 */   207,  206,  203,  200,  197,  537,  537,  537,  125,   19,
 /*  1210 */   214,  172,  537,  146,  537,  537,   47,   46,   45,   44,
 /*  1220 */    43,   42,   41,   40,   39,   38,  537,  193,  537,  471,
 /*  1230 */   471,  471,  471,  471,  471,  471,  471,  471,  471,  353,
 /*  1240 */   244,  351,  350,  349,  243,  242,  241,  345,  472,   10,
 /*  1250 */   472,  274,  250,   79,  537,  537,  537,  537,  537,    2,
 /*  1260 */    65,   67,   69,   68,   74,   73,   71,   72,   70,  273,
 /*  1270 */   272,  271,  217,  537,  215,  537,  537,  537,   18,  537,
 /*  1280 */   267,  217,   96,  537,   76,  537,  537,  146,  130,  155,
 /*  1290 */   537,   96,  537,  537,  537,  537,  146,  130,  155,  270,
 /*  1300 */   472,  472,  472,  472,  472,  472,  472,  472,  472,  472,
 /*  1310 */   176,  175,  537,  537,  537,  537,  537,   67,   69,   68,
 /*  1320 */    74,   73,   71,   72,   70,  537,  537,  537,  537,  537,
 /*  1330 */   215,  537,  537,  537,   18,  354,  537,  537,  537,  217,
 /*  1340 */    76,   69,   68,   74,   73,   71,   72,   70,  537,  125,
 /*  1350 */   537,  214,  192,  215,  146,  537,  537,   18,  537,  537,
 /*  1360 */   537,  537,  537,   76,  217,   95,  217,  238,  217,  537,
 /*  1370 */   169,  334,   84,  537,  116,  537,  117,  537,  117,  146,
 /*  1380 */   537,  297,  217,  194,  217,   83,  217,  537,  217,  537,
 /*  1390 */   537,  537,  145,  537,  144,  217,  143,  146,  117,  146,
 /*  1400 */   537,  146,  217,  296,  537,   97,  217,  537,  217,  217,
 /*  1410 */   146,  537,  114,  537,  537,  217,  113,  146,  112,  111,
 /*  1420 */   537,  146,  217,  146,  146,  110,  217,  537,  217,  537,
 /*  1430 */   146,  537,  109,  537,  217,  537,  108,  146,  107,  537,
 /*  1440 */   537,  146,  537,  146,  106,  217,  217,  217,  217,  146,
 /*  1450 */   537,  537,  537,  537,  537,  105,  104,  102,  101,  537,
 /*  1460 */   146,  146,  146,  146,  537,  537,  537,  217,  217,  217,
 /*  1470 */   217,  537,  537,  537,  537,  537,  537,  117,  117,  117,
 /*  1480 */   117,  537,  140,  139,  138,  137,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    73,   19,   20,   21,   22,   23,   28,    3,   32,   82,
 /*    10 */   103,   29,   85,   37,   38,   33,   89,   39,   28,  112,
 /*    20 */   113,   39,   95,   96,   97,  118,    3,  100,  101,  102,
 /*    30 */   103,  104,  105,  106,  107,  108,  109,  110,    1,   29,
 /*    40 */   113,   31,  102,  103,   40,  118,  119,  120,  121,  122,
 /*    50 */   123,   28,   28,  113,  127,  128,  129,   73,  118,  119,
 /*    60 */   120,  134,  135,  136,  137,  138,   82,  103,  141,   85,
 /*    70 */    33,   88,  132,   89,   28,   92,  112,  113,  114,   95,
 /*    80 */    96,   97,  118,    3,  100,  101,  102,  103,  104,  105,
 /*    90 */   106,  107,  108,  109,  110,   28,    2,  113,    4,    5,
 /*   100 */   103,   27,  118,  119,  120,  121,  122,  123,    3,  112,
 /*   110 */   113,  127,  128,  129,   73,  118,   27,  103,  134,  135,
 /*   120 */   136,  137,  138,   82,   27,  141,   85,  113,   34,   49,
 /*   130 */    89,    2,  118,    4,    5,   33,   95,   96,   97,   34,
 /*   140 */    34,  100,  101,  102,  103,  104,  105,  106,  107,  108,
 /*   150 */   109,  110,   28,    2,  113,    4,    5,   28,   27,  118,
 /*   160 */   119,  120,  121,  122,  123,    1,    3,    3,  127,  128,
 /*   170 */   129,   73,  124,  125,  126,  134,  135,  136,  137,  138,
 /*   180 */    82,  103,  141,   85,   28,   34,    2,   89,    4,    5,
 /*   190 */   112,  113,  114,   95,   96,   97,  118,   28,  100,  101,
 /*   200 */   102,  103,  104,  105,  106,  107,  108,  109,  110,   28,
 /*   210 */     2,  113,    4,    5,  103,   28,  118,  119,  120,  121,
 /*   220 */   122,  123,   28,  112,  113,  127,  128,  129,   73,  118,
 /*   230 */    28,  103,  134,  135,  136,  137,  138,   82,  103,  141,
 /*   240 */    85,  113,   34,   28,   89,   88,  118,   28,  113,   92,
 /*   250 */    95,   96,   97,  118,  119,  100,  101,  102,  103,  104,
 /*   260 */   105,  106,  107,  108,  109,  110,   39,    2,  113,    4,
 /*   270 */     5,  139,  140,  118,  119,  120,  121,  122,  123,    1,
 /*   280 */    26,    3,  127,  128,  129,   73,    1,   40,    3,  134,
 /*   290 */   135,  136,  137,  138,   82,  103,  141,   85,    1,   34,
 /*   300 */     3,   89,   93,   94,  112,  113,   40,   95,   96,   97,
 /*   310 */   118,   28,  100,  101,  102,  103,  104,  105,  106,  107,
 /*   320 */   108,  109,  110,   28,    2,  113,    4,    5,  103,   33,
 /*   330 */   118,  119,  120,  121,  122,  123,   33,  112,  113,  127,
 /*   340 */   128,  129,   73,  118,   39,  103,  134,  135,  136,  137,
 /*   350 */   138,   82,  103,  141,   85,  113,   34,   27,   89,   39,
 /*   360 */   118,  112,  113,   39,   95,   96,   97,  118,    3,  100,
 /*   370 */   101,  102,  103,  104,  105,  106,  107,  108,  109,  110,
 /*   380 */    26,    1,  113,    3,   75,   76,   40,  118,  119,  120,
 /*   390 */   121,  122,  123,    3,   33,   33,  127,  128,  129,   73,
 /*   400 */    42,   34,   33,  134,  135,  136,  137,  138,   82,  103,
 /*   410 */   141,   85,   42,   34,   33,   89,   42,   33,  112,  113,
 /*   420 */    34,   95,   96,   97,  118,   34,  100,  101,  102,  103,
 /*   430 */   104,  105,  106,  107,  108,  109,  110,   42,    5,  113,
 /*   440 */    33,   40,  103,   34,  118,  119,  120,  121,  122,  123,
 /*   450 */    34,   34,  113,  127,  128,  129,   73,  118,   34,  103,
 /*   460 */   134,  135,  136,  137,  138,   82,   29,  141,   85,  113,
 /*   470 */    33,   27,   33,   63,  118,   33,   39,    3,   95,   96,
 /*   480 */    97,   33,   99,  100,  101,  102,  103,  104,  105,  106,
 /*   490 */   107,  108,  109,  110,   33,   28,  113,    3,   34,   33,
 /*   500 */    28,  118,  119,  120,  121,  122,  123,   34,   33,   38,
 /*   510 */   127,  128,  129,   73,   27,   36,   27,  134,  135,  136,
 /*   520 */   137,  138,   82,   33,  141,   85,   34,   28,   27,   86,
 /*   530 */    98,   38,   98,  111,   26,   95,   96,   97,   98,    3,
 /*   540 */   100,  101,  102,  103,  104,  105,  106,  107,  108,  109,
 /*   550 */   110,   92,  117,  113,   27,   92,   72,   92,  118,  119,
 /*   560 */   120,  121,  122,  123,  139,  139,    6,  127,  128,  129,
 /*   570 */    92,   64,   92,   92,  134,  135,  136,  137,  138,   19,
 /*   580 */    20,  141,   21,   22,   23,   25,   26,   27,   28,  142,
 /*   590 */    29,  142,  142,   33,   33,  142,   36,   37,   38,   39,
 /*   600 */    39,   41,  142,  142,   44,   45,   46,   47,   48,  142,
 /*   610 */    50,   51,   52,  142,  142,  142,  142,  142,  142,    6,
 /*   620 */   142,  142,  142,   63,  142,   65,   66,   67,   68,   69,
 /*   630 */    70,   71,   19,   20,  142,  142,  142,  142,   25,   26,
 /*   640 */    27,   28,  142,  142,  142,  142,   33,  142,  142,   36,
 /*   650 */    37,   38,   39,  142,   41,  142,  142,   44,   45,   46,
 /*   660 */    47,   48,  142,   50,   51,   52,  142,  142,  142,  142,
 /*   670 */   142,  142,    6,  142,  142,  142,   63,  142,   65,   66,
 /*   680 */    67,   68,   69,   70,   71,   19,   20,  142,  142,  142,
 /*   690 */   142,   25,   26,   27,   28,  142,  142,  142,  142,   33,
 /*   700 */   142,  142,   36,   37,  142,   39,  142,   41,  142,  142,
 /*   710 */    44,   45,   46,   47,   48,  103,   50,   51,   52,    1,
 /*   720 */   142,    3,  142,  142,  142,  113,  142,  115,  116,   63,
 /*   730 */   118,   65,   66,   67,   68,   69,   70,   71,    8,    9,
 /*   740 */    10,   11,   12,   13,   14,   15,   16,   17,   18,   19,
 /*   750 */    20,   21,   22,   23,  142,  103,  142,  142,  142,   29,
 /*   760 */   142,  142,  142,   33,  142,  113,  142,  115,  116,   39,
 /*   770 */   118,   53,   54,   55,   56,   57,   58,   59,   60,   61,
 /*   780 */    62,   51,   52,  142,  142,  142,  142,  142,  142,  142,
 /*   790 */     8,    9,   10,   11,   12,   13,   14,   15,   16,   17,
 /*   800 */    18,   19,   20,   21,   22,   23,  142,  142,  142,  142,
 /*   810 */   142,   29,  142,  142,  142,   33,  142,  142,  142,  142,
 /*   820 */   142,   39,   40,  142,    8,    9,   10,   11,   12,   13,
 /*   830 */    14,   15,   16,   17,   18,   19,   20,   21,   22,   23,
 /*   840 */   142,  142,  103,  142,  142,   29,  142,  142,  142,   33,
 /*   850 */    34,  142,  113,  142,  115,   39,   82,  118,    8,    9,
 /*   860 */    10,   11,   12,   13,   14,   15,   16,   17,   18,   19,
 /*   870 */    20,   21,   22,   23,  100,  101,  102,  103,  142,   29,
 /*   880 */   103,  103,  142,   33,  142,  142,  142,  113,  142,   39,
 /*   890 */   113,  113,  118,  119,  120,  118,  118,  142,  142,   49,
 /*   900 */   142,  142,  142,  142,  130,  131,  142,  142,    8,    9,
 /*   910 */    10,   11,   12,   13,   14,   15,   16,   17,   18,   19,
 /*   920 */    20,   21,   22,   23,  142,  142,  103,  142,  142,   29,
 /*   930 */   142,  142,  142,   33,  142,  142,  113,  142,  142,   39,
 /*   940 */    40,  118,    8,    9,   10,   11,   12,   13,   14,   15,
 /*   950 */    16,   17,   18,   19,   20,   21,   22,   23,  142,  103,
 /*   960 */   103,  142,  142,   29,  142,  142,  142,   33,  142,  113,
 /*   970 */   113,  115,  116,   39,  118,  118,    8,    9,   10,   11,
 /*   980 */    12,   13,   14,   15,   16,   17,   18,   19,   20,   21,
 /*   990 */    22,   23,    6,  103,  103,  142,  142,   29,  142,  142,
 /*  1000 */   103,   33,  142,  113,  113,   19,   20,   39,  118,  118,
 /*  1010 */   113,   25,   26,   27,  103,  118,  142,  142,  142,   33,
 /*  1020 */   142,  142,  142,   37,  113,   39,    6,   41,  142,  118,
 /*  1030 */    44,   45,   46,   47,   48,  142,   50,   51,   52,   19,
 /*  1040 */    20,  142,  142,  142,  142,   25,   26,   27,  103,  142,
 /*  1050 */   142,  142,  142,   33,   34,  142,  142,   71,  113,   39,
 /*  1060 */     6,   41,   42,  118,   44,   45,   46,   47,   48,  142,
 /*  1070 */   142,  142,  142,   19,   20,  103,  142,  142,  142,   25,
 /*  1080 */    26,   27,  103,  142,  142,  113,  142,   33,  142,  142,
 /*  1090 */   118,   71,  113,   39,    6,   41,  142,  118,   44,   45,
 /*  1100 */    46,   47,   48,  142,  142,   51,   52,   19,   20,  103,
 /*  1110 */   142,  142,  142,   25,   26,   27,  103,  142,  142,  113,
 /*  1120 */   142,   33,  142,  142,  118,   71,  113,   39,    6,   41,
 /*  1130 */    42,  118,   44,   45,   46,   47,   48,  142,  142,  142,
 /*  1140 */   142,   19,   20,  103,  142,  142,  142,   25,   26,   27,
 /*  1150 */   103,  142,  142,  113,  142,   33,  142,  142,  118,   71,
 /*  1160 */   113,   39,    6,   41,    1,  118,   44,   45,   46,   47,
 /*  1170 */    48,  142,  142,  142,  142,   19,   20,    1,  142,    3,
 /*  1180 */   142,   25,   26,   27,  103,  142,  142,  142,  142,   33,
 /*  1190 */   142,  142,  142,   71,  113,   39,  142,   41,  103,  118,
 /*  1200 */    44,   45,   46,   47,   48,  142,  142,  142,  113,   33,
 /*  1210 */   115,  116,  142,  118,  142,  142,   53,   54,   55,   56,
 /*  1220 */    57,   58,   59,   60,   61,   62,  142,   71,  142,   53,
 /*  1230 */    54,   55,   56,   57,   58,   59,   60,   61,   62,   77,
 /*  1240 */    78,   79,   80,   81,   82,   83,   84,   85,    1,   87,
 /*  1250 */     3,   82,   90,   91,  142,  142,  142,  142,  142,   97,
 /*  1260 */    15,   16,   17,   18,   19,   20,   21,   22,   23,  100,
 /*  1270 */   101,  102,  103,  142,   29,  142,  142,  142,   33,  142,
 /*  1280 */   102,  103,  113,  142,   39,  142,  142,  118,  119,  120,
 /*  1290 */   142,  113,  142,  142,  142,  142,  118,  119,  120,  130,
 /*  1300 */    53,   54,   55,   56,   57,   58,   59,   60,   61,   62,
 /*  1310 */   132,  133,  142,  142,  142,  142,  142,   16,   17,   18,
 /*  1320 */    19,   20,   21,   22,   23,  142,  142,  142,  142,  142,
 /*  1330 */    29,  142,  142,  142,   33,    0,  142,  142,  142,  103,
 /*  1340 */    39,   17,   18,   19,   20,   21,   22,   23,  142,  113,
 /*  1350 */   142,  115,  116,   29,  118,  142,  142,   33,  142,  142,
 /*  1360 */   142,  142,  142,   39,  103,   30,  103,   32,  103,  142,
 /*  1370 */    35,   36,   37,  142,  113,  142,  113,  142,  113,  118,
 /*  1380 */   142,  118,  103,  118,  103,   50,  103,  142,  103,  142,
 /*  1390 */   142,  142,  113,  142,  113,  103,  113,  118,  113,  118,
 /*  1400 */   142,  118,  103,  118,  142,  113,  103,  142,  103,  103,
 /*  1410 */   118,  142,  113,  142,  142,  103,  113,  118,  113,  113,
 /*  1420 */   142,  118,  103,  118,  118,  113,  103,  142,  103,  142,
 /*  1430 */   118,  142,  113,  142,  103,  142,  113,  118,  113,  142,
 /*  1440 */   142,  118,  142,  118,  113,  103,  103,  103,  103,  118,
 /*  1450 */   142,  142,  142,  142,  142,  113,  113,  113,  113,  142,
 /*  1460 */   118,  118,  118,  118,  142,  142,  142,  103,  103,  103,
 /*  1470 */   103,  142,  142,  142,  142,  142,  142,  113,  113,  113,
 /*  1480 */   113,  142,  118,  118,  118,  118,
};
#define YY_SHIFT_USE_DFLT (-25)
#define YY_SHIFT_COUNT (244)
#define YY_SHIFT_MIN   (-24)
#define YY_SHIFT_MAX   (1335)
static const short yy_shift_ofst[] = {
 /*     0 */   -25,  613,  560,  666,  666,  666,  666,  666,  666,  666,
 /*    10 */   666, 1335,  986,  986, 1054, 1054, 1020, 1088, 1088, 1088,
 /*    20 */  1088, 1122, 1122, 1088, 1122, 1122, 1122, 1122, 1156, 1122,
 /*    30 */  1122, 1122, 1122, 1122, 1122, 1122, 1122, 1122, 1122, 1122,
 /*    40 */  1122, 1122, 1122, 1122, 1122, 1122, 1122, 1122, 1122, 1122,
 /*    50 */  1122, 1122, 1122, 1122, 1122, 1122, 1122, 1122, 1122, 1122,
 /*    60 */  1122, 1122, 1122, 1122, 1122, 1122, 1122, 1122, 1122, 1122,
 /*    70 */  1122, 1122, 1122, 1122, 1122, 1122, 1122, 1122,  507,  -24,
 /*    80 */   527,  484,  527,  527,  527,  527,  484,  484,  527,  527,
 /*    90 */   527,  536,  508,  493,  493,  501,  730,  900,  850,  816,
 /*   100 */   782,  934,  934,  968,  934,  934,  934,  934,  934,  934,
 /*   110 */   934,  934,  934,  934,  934,  934,  934,  934,  934,  934,
 /*   120 */   934,  934,  934,  934,  934,  934, 1176, 1247,  718, 1245,
 /*   130 */  1163, 1301, 1324,  -18,  -18,  561,  561,  129,  322,  265,
 /*   140 */   208,  151,   94,  437,  437,  437,  184,  437,  437,  437,
 /*   150 */   380,  297,   23,  105,   80,  285,  278,  164,    4,   37,
 /*   160 */   -22,   10,  390,  390,  499,  492,  490,  489,  479,  487,
 /*   170 */   471,  472,  473,  475,  466,  464,  494,  467,  474,  461,
 /*   180 */   448,  442,  410,  439,  390,  390,  390,  444,  424,  417,
 /*   190 */   416,  401,  409,  407,  433,  391,  395,  384,  386,  374,
 /*   200 */   381,  379,  370,  369,  367,  358,  362,  361,  390,  346,
 /*   210 */   354,  247,  324,  320,  365,  330,  303,  305,  296,  295,
 /*   220 */   283,  266,  247,  254,  227,  219,  215,  202,  194,  187,
 /*   230 */   181,  169,  156,  131,  163,  124,  106,  102,   97,   89,
 /*   240 */    74,   67,   46,   24,  -10,
};
#define YY_REDUCE_USE_DFLT (-94)
#define YY_REDUCE_COUNT (95)
#define YY_REDUCE_MIN   (-93)
#define YY_REDUCE_MAX   (1367)
static const short yy_reduce_ofst[] = {
 /*     0 */   309,  440,  383,  326,  269,  212,  155,   98,   41,  -16,
 /*    10 */   -73, 1162,  774, 1169, 1178,  -60, 1236, 1095,  856,  652,
 /*    20 */   612,   78,  -36,  739,  306,  249,  225,  192,  135,  111,
 /*    30 */    -3,  -93, 1367, 1366, 1365, 1364, 1345, 1344, 1343, 1342,
 /*    40 */  1331, 1325, 1323, 1319, 1312, 1306, 1305, 1303, 1299, 1292,
 /*    50 */  1285, 1283, 1281, 1279, 1265, 1263, 1261, 1081, 1047, 1040,
 /*    60 */  1013, 1006,  979,  972,  945,  911,  897,  891,  890,  857,
 /*    70 */   823,  778,  777,  356,  339,  242,  128,   14,   48,  209,
 /*    80 */   157,  132,  -17,  481,  480,  478,  426,  425,  465,  463,
 /*    90 */   459,  435,  422,  434,  432,  443,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   355,  532,  532,  532,  532,  532,  532,  532,  532,  532,
 /*    10 */   532,  535,  511,  535,  514,  535,  535,  428,  428,  428,
 /*    20 */   428,  417,  417,  535,  535,  535,  535,  535,  535,  535,
 /*    30 */   535,  535,  535,  535,  535,  535,  535,  535,  535,  535,
 /*    40 */   535,  535,  535,  535,  535,  535,  535,  535,  535,  535,
 /*    50 */   535,  535,  535,  535,  535,  535,  535,  535,  535,  535,
 /*    60 */   535,  535,  535,  535,  535,  535,  535,  535,  535,  535,
 /*    70 */   535,  535,  535,  535,  535,  535,  535,  535,  499,  535,
 /*    80 */   411,  535,  411,  535,  535,  535,  534,  533,  535,  535,
 /*    90 */   535,  435,  535,  535,  535,  535,  535,  535,  535,  535,
 /*   100 */   535,  480,  478,  535,  491,  490,  489,  488,  487,  486,
 /*   110 */   485,  484,  483,  482,  476,  426,  442,  535,  415,  462,
 /*   120 */   461,  460,  459,  458,  457,  424,  421,  423,  422,  451,
 /*   130 */   474,  452,  450,  449,  448,  444,  443,  535,  535,  535,
 /*   140 */   535,  535,  535,  455,  454,  453,  535,  447,  446,  445,
 /*   150 */   535,  466,  535,  535,  535,  535,  535,  466,  535,  421,
 /*   160 */   432,  368,  470,  468,  535,  535,  535,  535,  535,  535,
 /*   170 */   403,  535,  535,  535,  535,  535,  515,  535,  510,  535,
 /*   180 */   535,  535,  498,  535,  477,  469,  467,  535,  535,  535,
 /*   190 */   535,  535,  535,  535,  464,  535,  535,  535,  535,  535,
 /*   200 */   535,  535,  535,  535,  535,  535,  535,  535,  418,  535,
 /*   210 */   535,  407,  535,  432,  429,  535,  421,  432,  420,  535,
 /*   220 */   535,  535,  535,  535,  535,  535,  535,  535,  535,  535,
 /*   230 */   535,  535,  535,  535,  412,  369,  535,  535,  535,  535,
 /*   240 */   535,  535,  535,  535,  535,  378,  377,  376,  375,  374,
 /*   250 */   373,  372,  404,  388,  500,  531,  530,  529,  525,  524,
 /*   260 */   523,  522,  521,  520,  519,  518,  513,  512,  517,  516,
 /*   270 */   509,  508,  507,  506,  505,  504,  503,  502,  501,  497,
 /*   280 */   496,  495,  494,  493,  492,  475,  481,  479,  527,  430,
 /*   290 */   431,  456,  436,  434,  528,  526,  465,  463,  441,  440,
 /*   300 */   439,  438,  437,  416,  413,  408,  433,  427,  425,  423,
 /*   310 */   422,  419,  406,  405,  402,  401,  400,  399,  398,  397,
 /*   320 */   396,  414,  395,  394,  393,  392,  391,  390,  389,  387,
 /*   330 */   386,  385,  383,  384,  382,  381,  380,  379,  370,  410,
 /*   340 */   409,  371,  367,  366,  365,  364,  363,  362,  361,  360,
 /*   350 */   359,  358,  357,  356,
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
  "fArgs",         "commaSkippable",  "lexpr",         "lvalue",      
  "lvalueList_nonEmpty",  "if_start",      "if_header",     "if_block",    
  "elif_start",    "elif_header",   "else_header",   "while_start", 
  "while_header",  "for_opener",    "for_init_stmt_nonEmpty",  "for_init_stmt",
  "for_action_stmt_nonEmpty",  "for_action_stmt",  "for_header1",   "for_header2", 
  "for_header",    "foreach_opener",  "foreach_header",  "action",      
  "actions",       "actionStmt_start",
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
 /*  88 */ "expr ::= lexpr QMARK expr COLON expr",
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
    case 74: /* nt */
{
#line 40 "parser\\epparser.lemon"
 delete (yypminor->yy0); 
#line 961 "parser\\epparser.c"
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
  { 122, 4 },
  { 123, 2 },
  { 124, 2 },
  { 125, 4 },
  { 123, 3 },
  { 126, 1 },
  { 105, 1 },
  { 105, 3 },
  { 127, 1 },
  { 128, 4 },
  { 106, 2 },
  { 129, 2 },
  { 130, 1 },
  { 130, 1 },
  { 130, 1 },
  { 130, 1 },
  { 130, 3 },
  { 131, 1 },
  { 131, 0 },
  { 132, 1 },
  { 132, 3 },
  { 133, 0 },
  { 133, 1 },
  { 134, 3 },
  { 135, 3 },
  { 136, 3 },
  { 107, 2 },
  { 137, 2 },
  { 138, 5 },
  { 108, 2 },
  { 109, 1 },
  { 110, 1 },
  { 96, 2 },
  { 118, 4 },
  { 118, 4 },
  { 118, 3 },
  { 139, 5 },
  { 140, 2 },
  { 140, 2 },
  { 141, 0 },
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
#line 1439 "parser\\epparser.c"
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
#line 1455 "parser\\epparser.c"
        break;
      case 12: /* dottedName ::= dottedName PERIOD NAME */
#line 84 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = yymsp[-2].minor.yy0->data + "." + yymsp[0].minor.yy0->data;
    delete yymsp[-2].minor.yy0;
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1464 "parser\\epparser.c"
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
#line 1480 "parser\\epparser.c"
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
#line 1496 "parser\\epparser.c"
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
#line 1529 "parser\\epparser.c"
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
#line 1541 "parser\\epparser.c"
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
#line 1552 "parser\\epparser.c"
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
#line 1570 "parser\\epparser.c"
        break;
      case 19: /* object_body ::= object_header */
#line 182 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1577 "parser\\epparser.c"
        break;
      case 20: /* object_body ::= object_body VAR nameList_nonEmpty SEMICOLON */
#line 186 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-3].minor.yy0;
    yygotominor.yy0->line = yymsp[-1].minor.yy0->line;
    yygotominor.yy0->data += ", " + yymsp[-1].minor.yy0->data;
    delete yymsp[-1].minor.yy0;
}
#line 1587 "parser\\epparser.c"
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
#line 1627 "parser\\epparser.c"
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
#line 1640 "parser\\epparser.c"
        break;
      case 23: /* object_body ::= object_body method_chunk */
#line 240 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-1].minor.yy0;
    yygotominor.yy0->line = yymsp[0].minor.yy0->line;
    delete yymsp[0].minor.yy0;
}
#line 1649 "parser\\epparser.c"
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
#line 1668 "parser\\epparser.c"
        break;
      case 25: /* stmt ::= error SEMICOLON */
#line 263 "parser\\epparser.lemon"
{ throw_error(6974, "Error while parsing statement", yymsp[0].minor.yy0->line); delete yymsp[0].minor.yy0; }
#line 1673 "parser\\epparser.c"
        break;
      case 28: /* lbracket ::= LBRACKET */
#line 269 "parser\\epparser.lemon"
{ ps->closure.pushScope(); }
#line 1678 "parser\\epparser.c"
        break;
      case 29: /* rbracket ::= RBRACKET */
#line 270 "parser\\epparser.lemon"
{ ps->closure.popScope(); }
#line 1683 "parser\\epparser.c"
        break;
      case 30: /* blockStmt ::= lbracket RBRACKET */
#line 272 "parser\\epparser.lemon"
{
    ps->closure.popScope();
}
#line 1690 "parser\\epparser.c"
        break;
      case 34: /* blockStmt ::= lbracket error RBRACKET */
#line 278 "parser\\epparser.lemon"
{
    throw_error(6298, "Block not terminated properly.", yymsp[0].minor.yy0->line);
    ps->closure.popScope();
    delete yymsp[0].minor.yy0;
}
#line 1699 "parser\\epparser.c"
        break;
      case 41: /* bodyStmt ::= funcexpr SEMICOLON */
#line 290 "parser\\epparser.lemon"
{ ps->gen << yymsp[-1].minor.yy0->data << std::endl; }
#line 1704 "parser\\epparser.c"
        break;
      case 49: /* bodyStmtList ::= error */
      case 52: /* bodyStmtList ::= bodyStmtList error */ yytestcase(yyruleno==52);
#line 300 "parser\\epparser.lemon"
{
    throw_error(8510, "Incomplete statement");
}
#line 1712 "parser\\epparser.c"
        break;
      case 54: /* numList_nonEmpty ::= numList_nonEmpty COMMA NUMBER */
      case 56: /* nameList_nonEmpty ::= nameList_nonEmpty COMMA NAME */ yytestcase(yyruleno==56);
      case 121: /* lvalueList_nonEmpty ::= lvalueList_nonEmpty COMMA lvalue */ yytestcase(yyruleno==121);
#line 313 "parser\\epparser.lemon"
{ yygotominor.yy0 = commaConcat(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1719 "parser\\epparser.c"
        break;
      case 57: /* nameList ::= */
      case 63: /* exprList ::= */ yytestcase(yyruleno==63);
      case 74: /* fArgs ::= */ yytestcase(yyruleno==74);
#line 316 "parser\\epparser.lemon"
{ yygotominor.yy0 = genEmpty(); }
#line 1726 "parser\\epparser.c"
        break;
      case 59: /* exprList_nonEmpty ::= funcexpr LSQBRACKET LSQBRACKET numList_nonEmpty RSQBRACKET RSQBRACKET */
#line 319 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "_SRET(" + yymsp[-5].minor.yy0->data + ", [" + yymsp[-2].minor.yy0->data + "])";
    delete yymsp[-5].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1735 "parser\\epparser.c"
        break;
      case 60: /* expr ::= funcexpr LSQBRACKET LSQBRACKET NUMBER RSQBRACKET RSQBRACKET */
#line 326 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-5].minor.yy0->data + "[" + yymsp[-2].minor.yy0->data + "]";
    delete yymsp[-5].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1744 "parser\\epparser.c"
        break;
      case 62: /* exprList_nonEmpty ::= exprList_nonEmpty COMMA exprList_nonEmpty */
#line 334 "parser\\epparser.lemon"
{ yygotominor.yy0 = new Token((yymsp[-2].minor.yy0->data) + ", " + (yymsp[0].minor.yy0->data), yymsp[0].minor.yy0); delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1749 "parser\\epparser.c"
        break;
      case 66: /* expr ::= KILLS */
#line 341 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = "4";
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1757 "parser\\epparser.c"
        break;
      case 67: /* expr ::= NAME */
#line 346 "parser\\epparser.lemon"
{
    checkIsRValue(yymsp[0].minor.yy0->data, yymsp[0].minor.yy0->line);
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1765 "parser\\epparser.c"
        break;
      case 68: /* expr ::= expr PERIOD NAME */
#line 351 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + "." + yymsp[0].minor.yy0->data;
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1774 "parser\\epparser.c"
        break;
      case 69: /* expr ::= expr LSQBRACKET expr RSQBRACKET */
#line 357 "parser\\epparser.lemon"
{
    yymsp[-3].minor.yy0->data = yymsp[-3].minor.yy0->data + "[" + yymsp[-1].minor.yy0->data + "]";
    delete yymsp[-1].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 1783 "parser\\epparser.c"
        break;
      case 72: /* fArgs_nonEmpty ::= NAME ASSIGN expr */
#line 366 "parser\\epparser.lemon"
{  // Keyword argument
    yymsp[0].minor.yy0->data = yymsp[-2].minor.yy0->data + "=" + yymsp[0].minor.yy0->data;
    yymsp[0].minor.yy0->type = TOKEN_TEMP;
    yygotominor.yy0 = yymsp[0].minor.yy0;
    delete yymsp[-2].minor.yy0;
}
#line 1793 "parser\\epparser.c"
        break;
      case 73: /* fArgs_nonEmpty ::= fArgs_nonEmpty COMMA fArgs_nonEmpty */
#line 373 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data;
    yymsp[0].minor.yy0->type = TOKEN_TEMP;
    yygotominor.yy0 = yymsp[0].minor.yy0;
    delete yymsp[-2].minor.yy0;
}
#line 1803 "parser\\epparser.c"
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
#line 1816 "parser\\epparser.c"
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
#line 1840 "parser\\epparser.c"
        break;
      case 79: /* expr ::= LPAREN expr RPAREN */
      case 102: /* lexpr ::= LPAREN lexpr RPAREN */ yytestcase(yyruleno==102);
#line 421 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1849 "parser\\epparser.c"
        break;
      case 82: /* expr ::= LSQBRACKET exprList commaSkippable RSQBRACKET */
#line 429 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "_ARR(FlattenList([" + yymsp[-2].minor.yy0->data + "]))";
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1857 "parser\\epparser.c"
        break;
      case 83: /* expr ::= L2V LPAREN lexpr RPAREN */
#line 434 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "_L2V(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1865 "parser\\epparser.c"
        break;
      case 84: /* expr ::= MAPSTRING LPAREN STRING RPAREN */
#line 439 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetStringIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1873 "parser\\epparser.c"
        break;
      case 85: /* expr ::= UNIT LPAREN STRING RPAREN */
#line 444 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "EncodeUnit(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1881 "parser\\epparser.c"
        break;
      case 86: /* expr ::= SWITCH LPAREN STRING RPAREN */
#line 449 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "EncodeSwitch(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1889 "parser\\epparser.c"
        break;
      case 87: /* expr ::= LOCATION LPAREN STRING RPAREN */
#line 454 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetLocationIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1897 "parser\\epparser.c"
        break;
      case 88: /* expr ::= lexpr QMARK expr COLON expr */
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
#line 1911 "parser\\epparser.c"
        break;
      case 89: /* expr ::= expr PLUS expr */
#line 472 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "+",  yymsp[0].minor.yy0); }
#line 1916 "parser\\epparser.c"
        break;
      case 90: /* expr ::= expr MINUS expr */
#line 473 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "-",  yymsp[0].minor.yy0); }
#line 1921 "parser\\epparser.c"
        break;
      case 91: /* expr ::= expr MULTIPLY expr */
#line 474 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "*",  yymsp[0].minor.yy0); }
#line 1926 "parser\\epparser.c"
        break;
      case 92: /* expr ::= expr DIVIDE expr */
#line 475 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "//", yymsp[0].minor.yy0); }
#line 1931 "parser\\epparser.c"
        break;
      case 93: /* expr ::= expr MOD expr */
#line 476 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "%",  yymsp[0].minor.yy0); }
#line 1936 "parser\\epparser.c"
        break;
      case 94: /* expr ::= expr LSHIFT expr */
#line 477 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = "_LSH(" + yymsp[-2].minor.yy0->data + "," + yymsp[0].minor.yy0->data + ")";
    delete yymsp[-2].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0);
}
#line 1945 "parser\\epparser.c"
        break;
      case 95: /* expr ::= expr RSHIFT expr */
#line 482 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, ">>", yymsp[0].minor.yy0); }
#line 1950 "parser\\epparser.c"
        break;
      case 96: /* expr ::= expr BITAND expr */
#line 483 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "&",  yymsp[0].minor.yy0); }
#line 1955 "parser\\epparser.c"
        break;
      case 97: /* expr ::= expr BITOR expr */
#line 484 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "|",  yymsp[0].minor.yy0); }
#line 1960 "parser\\epparser.c"
        break;
      case 98: /* expr ::= expr BITXOR expr */
#line 485 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "^",  yymsp[0].minor.yy0); }
#line 1965 "parser\\epparser.c"
        break;
      case 99: /* expr ::= PLUS expr */
#line 488 "parser\\epparser.lemon"
{ yymsp[0].minor.yy0->data = "+" + yymsp[0].minor.yy0->data; yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0); }
#line 1970 "parser\\epparser.c"
        break;
      case 100: /* expr ::= MINUS expr */
#line 489 "parser\\epparser.lemon"
{ yymsp[0].minor.yy0->data = "-" + yymsp[0].minor.yy0->data; yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0); }
#line 1975 "parser\\epparser.c"
        break;
      case 101: /* expr ::= BITNOT expr */
#line 490 "parser\\epparser.lemon"
{ yymsp[0].minor.yy0->data = "~" + yymsp[0].minor.yy0->data; yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0); }
#line 1980 "parser\\epparser.c"
        break;
      case 103: /* lexpr ::= expr EQ expr */
#line 499 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "==", yymsp[0].minor.yy0); }
#line 1985 "parser\\epparser.c"
        break;
      case 104: /* lexpr ::= expr NE expr */
#line 500 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genEmpty();
    yygotominor.yy0->line = yymsp[0].minor.yy0->line;

    yygotominor.yy0->type = TOKEN_NE;
    yygotominor.yy0->subToken[0] = yymsp[-2].minor.yy0;
    yygotominor.yy0->subToken[1] = yymsp[0].minor.yy0;
    yygotominor.yy0->data = yymsp[-2].minor.yy0->data + " != " + yymsp[0].minor.yy0->data;
}
#line 1998 "parser\\epparser.c"
        break;
      case 105: /* lexpr ::= expr LE expr */
#line 510 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "<=", yymsp[0].minor.yy0); }
#line 2003 "parser\\epparser.c"
        break;
      case 106: /* lexpr ::= expr LT expr */
#line 511 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "<",  yymsp[0].minor.yy0); }
#line 2008 "parser\\epparser.c"
        break;
      case 107: /* lexpr ::= expr GE expr */
#line 512 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, ">=", yymsp[0].minor.yy0); }
#line 2013 "parser\\epparser.c"
        break;
      case 108: /* lexpr ::= expr GT expr */
#line 513 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, ">" , yymsp[0].minor.yy0); }
#line 2018 "parser\\epparser.c"
        break;
      case 109: /* lexpr ::= lexpr LAND lexpr */
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
#line 2037 "parser\\epparser.c"
        break;
      case 110: /* lexpr ::= lexpr LOR lexpr */
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
#line 2056 "parser\\epparser.c"
        break;
      case 111: /* lexpr ::= LNOT lexpr */
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
#line 2074 "parser\\epparser.c"
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
#line 2098 "parser\\epparser.c"
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
#line 2123 "parser\\epparser.c"
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
#line 2143 "parser\\epparser.c"
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
#line 2165 "parser\\epparser.c"
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
#line 2187 "parser\\epparser.c"
        break;
      case 117: /* lvalue ::= NAME */
#line 665 "parser\\epparser.lemon"
{
    checkIsVariable(yymsp[0].minor.yy0->data, yymsp[0].minor.yy0->line);
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 2195 "parser\\epparser.c"
        break;
      case 118: /* lvalue ::= expr LSQBRACKET expr RSQBRACKET */
#line 670 "parser\\epparser.lemon"
{
    checkIsConstant(yymsp[-3].minor.yy0->data, yymsp[-3].minor.yy0->line);
    yymsp[-1].minor.yy0->data = "_ARRW(" + yymsp[-3].minor.yy0->data + ", " + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
    delete yymsp[-3].minor.yy0;
}
#line 2205 "parser\\epparser.c"
        break;
      case 119: /* lvalue ::= expr PERIOD NAME */
#line 677 "parser\\epparser.lemon"
{
    checkIsConstant(yymsp[-2].minor.yy0->data, yymsp[-2].minor.yy0->line);
    yymsp[0].minor.yy0->data = "_ATTW(" + yymsp[-2].minor.yy0->data + ", '" + yymsp[0].minor.yy0->data + "')";
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0);
    delete yymsp[-2].minor.yy0;
}
#line 2215 "parser\\epparser.c"
        break;
      case 122: /* assign_stmt ::= lvalue ASSIGN expr */
#line 686 "parser\\epparser.lemon"
{
    ps->gen << yymsp[-2].minor.yy0->data << " << (" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 2223 "parser\\epparser.c"
        break;
      case 123: /* assign_stmt ::= lvalueList_nonEmpty ASSIGN exprList_nonEmpty */
#line 691 "parser\\epparser.lemon"
{
    ps->gen << "_SV([" << yymsp[-2].minor.yy0->data << "], [" << yymsp[0].minor.yy0->data << "])" << std::endl;
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 2231 "parser\\epparser.c"
        break;
      case 124: /* assign_stmt ::= INC expr */
#line 699 "parser\\epparser.lemon"
{ ps->gen << yymsp[0].minor.yy0->data << ".__iadd__(1)" << std::endl; delete yymsp[0].minor.yy0; }
#line 2236 "parser\\epparser.c"
        break;
      case 125: /* assign_stmt ::= expr INC */
#line 700 "parser\\epparser.lemon"
{ ps->gen << yymsp[-1].minor.yy0->data << ".__iadd__(1)" << std::endl; delete yymsp[-1].minor.yy0; }
#line 2241 "parser\\epparser.c"
        break;
      case 126: /* assign_stmt ::= DEC expr */
#line 701 "parser\\epparser.lemon"
{ ps->gen << yymsp[0].minor.yy0->data << ".__isub__(1)" << std::endl; delete yymsp[0].minor.yy0; }
#line 2246 "parser\\epparser.c"
        break;
      case 127: /* assign_stmt ::= expr DEC */
#line 702 "parser\\epparser.lemon"
{ ps->gen << yymsp[-1].minor.yy0->data << ".__isub__(1)" << std::endl; delete yymsp[-1].minor.yy0; }
#line 2251 "parser\\epparser.c"
        break;
      case 128: /* assign_stmt ::= lvalue IADD expr */
#line 703 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__iadd__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2256 "parser\\epparser.c"
        break;
      case 129: /* assign_stmt ::= lvalue ISUB expr */
#line 704 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__isub__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2261 "parser\\epparser.c"
        break;
      case 130: /* assign_stmt ::= lvalue IMUL expr */
#line 705 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__imul__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2266 "parser\\epparser.c"
        break;
      case 131: /* assign_stmt ::= lvalue IDIV expr */
#line 706 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ifloordiv__("  << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2271 "parser\\epparser.c"
        break;
      case 132: /* assign_stmt ::= lvalue IMOD expr */
#line 707 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__imod__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2276 "parser\\epparser.c"
        break;
      case 133: /* assign_stmt ::= lvalue ILSH expr */
#line 708 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ilshift__("    << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2281 "parser\\epparser.c"
        break;
      case 134: /* assign_stmt ::= lvalue IRSH expr */
#line 709 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__irshift__("    << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2286 "parser\\epparser.c"
        break;
      case 135: /* assign_stmt ::= lvalue IBND expr */
#line 710 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__iand__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2291 "parser\\epparser.c"
        break;
      case 136: /* assign_stmt ::= lvalue IBOR expr */
#line 711 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ior__("        << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2296 "parser\\epparser.c"
        break;
      case 137: /* assign_stmt ::= lvalue IBXR expr */
#line 712 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ixor__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2301 "parser\\epparser.c"
        break;
      case 138: /* if_start ::= IF */
#line 715 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDIf()" << std::endl;
}
#line 2309 "parser\\epparser.c"
        break;
      case 139: /* if_header ::= if_start LPAREN lexpr RPAREN */
      case 142: /* elif_header ::= elif_start LPAREN lexpr RPAREN */ yytestcase(yyruleno==142);
      case 148: /* while_header ::= while_start LPAREN lexpr RPAREN */ yytestcase(yyruleno==148);
#line 720 "parser\\epparser.lemon"
{
    writeCsOpener(*pGen, yymsp[-3].minor.yy0, yymsp[-1].minor.yy0);
    ps->gen.indent();
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 2320 "parser\\epparser.c"
        break;
      case 141: /* elif_start ::= ELSE IF */
#line 728 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen.unindent(false);
    ps->gen << yygotominor.yy0->data << " = EUDElseIf()" << std::endl;
}
#line 2329 "parser\\epparser.c"
        break;
      case 144: /* else_header ::= ELSE */
#line 742 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "if EUDElse()():" << std::endl;
    ps->gen.indent();
}
#line 2338 "parser\\epparser.c"
        break;
      case 145: /* if_stmt ::= if_block */
      case 146: /* if_stmt ::= if_block else_header stmt */ yytestcase(yyruleno==146);
#line 748 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndIf()" << std::endl;
}
#line 2347 "parser\\epparser.c"
        break;
      case 147: /* while_start ::= WHILE */
#line 760 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDWhile()" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2356 "parser\\epparser.c"
        break;
      case 149: /* while_stmt ::= while_header stmt */
#line 772 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndWhile()" << std::endl;
}
#line 2364 "parser\\epparser.c"
        break;
      case 150: /* for_opener ::= FOR LPAREN */
      case 166: /* foreach_opener ::= FOREACH LPAREN */ yytestcase(yyruleno==166);
#line 778 "parser\\epparser.lemon"
{
    ps->closure.pushScope();
}
#line 2372 "parser\\epparser.c"
        break;
      case 162: /* for_header1 ::= for_opener for_init_stmt SEMICOLON */
#line 796 "parser\\epparser.lemon"
{
    // opening for lexpr
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDWhile()" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2382 "parser\\epparser.c"
        break;
      case 163: /* for_header2 ::= for_header1 lexpr SEMICOLON */
#line 803 "parser\\epparser.lemon"
{
    writeCsOpener(*pGen, yymsp[-2].minor.yy0, yymsp[-1].minor.yy0);
    ps->gen.indent();
    delete yymsp[-2].minor.yy0; delete yymsp[-1].minor.yy0;

    // Opening for assign_statement
    yygotominor.yy0 = genTemp(yymsp[-1].minor.yy0);
    ps->gen << "def " << yygotominor.yy0->data <<"():" << std::endl;
    ps->gen.indent();
}
#line 2396 "parser\\epparser.c"
        break;
      case 164: /* for_header ::= for_header2 for_action_stmt RPAREN */
#line 814 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-2].minor.yy0;
    ps->gen.unindent(false);
}
#line 2404 "parser\\epparser.c"
        break;
      case 165: /* for_stmt ::= for_header stmt */
#line 819 "parser\\epparser.lemon"
{
    ps->gen << "EUDSetContinuePoint()" << std::endl;
    ps->gen << yymsp[-1].minor.yy0->data << "()" << std::endl;
    ps->gen.unindent(false);
    ps->gen << "EUDEndWhile()" << std::endl;
    ps->closure.popScope();
}
#line 2415 "parser\\epparser.c"
        break;
      case 167: /* foreach_header ::= foreach_opener nameList_nonEmpty COLON exprList_nonEmpty RPAREN */
#line 834 "parser\\epparser.lemon"
{
    commaListIter(yymsp[-3].minor.yy0->data, [&](std::string& s) {
        ps->closure.defVariable(s);
    });
    ps->gen << "for " << yymsp[-3].minor.yy0->data << " in " << yymsp[-1].minor.yy0->data << ":" << std::endl;
    ps->gen.indent();
}
#line 2426 "parser\\epparser.c"
        break;
      case 168: /* foreach_stmt ::= foreach_header stmt */
#line 842 "parser\\epparser.lemon"
{
    ps->gen.unindent(true);
    ps->closure.popScope();
}
#line 2434 "parser\\epparser.c"
        break;
      case 169: /* continue_stmt ::= CONTINUE */
#line 850 "parser\\epparser.lemon"
{
    ps->gen << "EUDContinue()" << std::endl;
}
#line 2441 "parser\\epparser.c"
        break;
      case 170: /* break_stmt ::= BREAK */
#line 854 "parser\\epparser.lemon"
{
    ps->gen << "EUDBreak()" << std::endl;
}
#line 2448 "parser\\epparser.c"
        break;
      case 171: /* return_stmt ::= RETURN exprList */
#line 861 "parser\\epparser.lemon"
{
    if(MAP_DEBUG){
        ps->gen << "MDBG_POPF()" << std::endl;
    }
    ps->gen << "EUDReturn(" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2459 "parser\\epparser.c"
        break;
      case 172: /* lexpr ::= CONDITIONNAME LPAREN fArgs RPAREN */
      case 173: /* lexpr ::= KILLS LPAREN fArgs RPAREN */ yytestcase(yyruleno==173);
#line 872 "parser\\epparser.lemon"
{
    yymsp[-3].minor.yy0->data = yymsp[-3].minor.yy0->data + "(" + yymsp[-1].minor.yy0->data + ")";
    delete yymsp[-1].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 2469 "parser\\epparser.c"
        break;
      case 174: /* lexpr ::= CONDITIONNAME LPAREN RPAREN */
#line 884 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + "()";
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 2477 "parser\\epparser.c"
        break;
      case 175: /* action ::= ACTIONNAME LPAREN fArgs RPAREN SEMICOLON */
#line 889 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[-4].minor.yy0);
    yygotominor.yy0->data =  yymsp[-4].minor.yy0->data + "(" + yymsp[-2].minor.yy0->data + ")";
    delete yymsp[-4].minor.yy0; delete yymsp[-2].minor.yy0;
}
#line 2486 "parser\\epparser.c"
        break;
      case 176: /* actions ::= action action */
      case 177: /* actions ::= actions action */ yytestcase(yyruleno==177);
#line 895 "parser\\epparser.lemon"
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
#line 2509 "parser\\epparser.c"
        break;
      case 178: /* actionStmt_start ::= */
#line 933 "parser\\epparser.lemon"
{
    functionCalledInMultipleActions = false;
}
#line 2516 "parser\\epparser.c"
        break;
      case 179: /* actionStmt ::= actionStmt_start action */
#line 937 "parser\\epparser.lemon"
{
    ps->gen << "DoActions(" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2524 "parser\\epparser.c"
        break;
      case 180: /* actionStmt ::= actionStmt_start actions */
#line 942 "parser\\epparser.lemon"
{
    ps->gen << "DoActions([" << std::endl;
    ps->gen.indent();
    ps->gen << yymsp[0].minor.yy0->data << std::endl;
    ps->gen.unindent(false);
    ps->gen << "])" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2536 "parser\\epparser.c"
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
#line 2632 "parser\\epparser.c"
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
#line 956 "parser\\epparser.lemon"


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
#line 2928 "parser\\epparser.c"
