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

#line 37 "parser\\epparser.c"
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
#define YYNOCODE 138
#define YYACTIONTYPE unsigned short int
#define ParseTOKENTYPE Token*
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  int yy275;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL  ParserStruct* ps ;
#define ParseARG_PDECL , ParserStruct* ps 
#define ParseARG_FETCH  ParserStruct* ps  = yypParser->ps 
#define ParseARG_STORE yypParser->ps  = ps 
#define YYNSTATE 338
#define YYNRULE 175
#define YYERRORSYMBOL 72
#define YYERRSYMDT yy275
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
#define YY_ACTTAB_COUNT (1243)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   221,   74,   73,   71,   72,   70,  170,    7,    3,  217,
 /*    10 */    76,  205,  312,   38,  222,   18,  322,  320,  220,    2,
 /*    20 */    75,  225,  216,  215,  214,  152,  304,  303,  302,  301,
 /*    30 */   300,  209,  208,   27,   28,   39,   93,  204,   27,   28,
 /*    40 */   223,   19,  124,  147,  172,    8,   40,  199,  117,   86,
 /*    50 */   169,    6,   11,  221,  336,  250,  207,   22,   13,    5,
 /*    60 */    83,    4,  217,  280,   77,  312,  245,   93,  275,  265,
 /*    70 */   320,  220,    2,  124,  147,  216,  215,  214,  152,  304,
 /*    80 */   303,  302,  301,  300,  209,  208,  165,  164,  332,   93,
 /*    90 */   204,  229,  331,  228,  222,  124,  147,  172,    8,   40,
 /*   100 */   199,  117,  241,  169,    6,   11,   27,   28,  201,  221,
 /*   110 */    22,   13,    5,   83,    4,  205,  330,   77,  217,   18,
 /*   120 */   327,  312,   82,   81,   75,  262,  320,  220,    2,   78,
 /*   130 */   251,  216,  215,  214,  152,  304,  303,  302,  301,  300,
 /*   140 */   209,  208,   27,   28,  200,   93,  204,   27,   28,   37,
 /*   150 */   222,  124,  147,  172,    8,   40,  288,  117,   34,  169,
 /*   160 */     6,   11,  221,  326,  250,  207,   22,   13,    5,   83,
 /*   170 */     4,  217,  266,   77,  312,  226,   93,  263,  259,  320,
 /*   180 */   220,    2,  124,  147,  216,  215,  214,  152,  304,  303,
 /*   190 */   302,  301,  300,  209,  208,  249,   35,   36,   93,   27,
 /*   200 */    28,  306,   33,  222,  124,  147,  172,    8,   40,   32,
 /*   210 */   222,  213,  169,    6,   11,  514,   10,  325,  221,   22,
 /*   220 */    13,    5,   83,    4,  224,  222,   77,  217,  204,  260,
 /*   230 */   312,  323,  211,  321,  247,  320,  220,    2,  175,  117,
 /*   240 */   216,  215,  214,  152,  304,  303,  302,  301,  300,  209,
 /*   250 */   208,  319,   89,   88,   93,  204,  207,  310,  309,  308,
 /*   260 */   124,  147,  172,    8,   40,  174,  117,  119,  169,    6,
 /*   270 */    11,  221,  307,  212,  207,   22,   13,    5,   83,    4,
 /*   280 */   217,  207,   77,  312,  210,   99,  305,  244,  320,  220,
 /*   290 */     2,  268,   96,  216,  215,  214,  152,  304,  303,  302,
 /*   300 */   301,  300,  209,  208,  299,  298,  213,   93,  207,  207,
 /*   310 */   293,   19,  203,  124,  147,  172,    8,   40,   87,  130,
 /*   320 */   129,  169,    6,   11,  290,  289,   39,  221,   22,   13,
 /*   330 */     5,   83,    4,   30,   17,   77,  217,  204,   31,  312,
 /*   340 */   193,  194,  191,  237,  320,  220,    2,  173,  117,  216,
 /*   350 */   215,  214,  152,  304,  303,  302,  301,  300,  209,  208,
 /*   360 */   285,  284,  190,   93,  204,  207,  188,  273,  283,  124,
 /*   370 */   147,  172,    8,   40,  145,  117,  142,  169,    6,   11,
 /*   380 */   159,  187,  185,  204,   22,   13,    5,   83,    4,  217,
 /*   390 */   282,   77,  312,  155,  117,  184,  281,  235,  219,    2,
 /*   400 */    28,    1,  216,  215,  214,  152,  304,  303,  302,  301,
 /*   410 */   300,  209,  208,   15,  122,  277,   93,  207,  207,  272,
 /*   420 */   271,   25,  124,  147,  172,    8,   40,  264,  141,  140,
 /*   430 */   169,    6,   11,   24,   23,  207,  296,   22,   13,    5,
 /*   440 */    83,    4,  338,  258,   77,  217,   92,  252,  312,   12,
 /*   450 */    14,  135,  248,  297,  218,    2,  314,  246,  216,  215,
 /*   460 */   214,  152,  304,  303,  302,  301,  300,  209,  208,   16,
 /*   470 */   240,   90,   93,  227,  207,  236,  158,  318,  124,  147,
 /*   480 */   172,    8,   40,  160,  157,  128,  169,    6,   11,   80,
 /*   490 */    79,  156,  153,   22,   13,    5,   83,    4,   63,   62,
 /*   500 */    77,   71,   72,   70,   61,  295,  120,  311,  234,  205,
 /*   510 */   204,  328,   64,   18,  315,  318,  317,   21,   75,  294,
 /*   520 */   154,  117,  198,  195,  192,  189,  186,   85,   84,   42,
 /*   530 */    41,   66,   65,   67,   69,   68,   74,   73,   71,   72,
 /*   540 */    70,  267,  207,  261,  168,  163,  205,  243,  242,   20,
 /*   550 */    18,  207,  207,   91,  150,   75,  292,  316,  136,  207,
 /*   560 */    63,   62,  118,  127,  196,  177,   61,  295,  120,  311,
 /*   570 */   118,  207,  196,  178,   64,  313,  202,  318,  316,   21,
 /*   580 */   179,  294,  126,  274,  198,  195,  192,  189,  186,   85,
 /*   590 */    84,   42,   41,   66,   65,   67,   69,   68,   74,   73,
 /*   600 */    71,   72,   70,  267,  207,  261,  168,  163,  205,  243,
 /*   610 */   242,   20,   18,  291,  207,   92,  149,   75,  324,  148,
 /*   620 */   279,  207,   63,   62,  239,  118,  207,  286,   61,  295,
 /*   630 */   120,  311,  118,  146,  196,  183,   64,   92,  162,  318,
 /*   640 */   238,   21,  182,  294,  207,  207,  198,  195,  192,  189,
 /*   650 */   186,   85,   84,   42,   41,  118,   92,  196,  161,  207,
 /*   660 */   144,  278,  143,  207,  171,  267,  515,  261,  168,  163,
 /*   670 */   123,  243,  242,   20,  125,   60,   58,   57,   56,   55,
 /*   680 */    59,   66,   65,   67,   69,   68,   74,   73,   71,   72,
 /*   690 */    70,  207,  207,  207,  515,  515,  205,  515,  515,  515,
 /*   700 */    18,  291,   95,  139,  118,   75,  196,  180,   60,   58,
 /*   710 */    57,   56,   55,   59,   66,   65,   67,   69,   68,   74,
 /*   720 */    73,   71,   72,   70,  515,  207,  207,  515,  207,  205,
 /*   730 */   515,  515,  207,   18,   63,   62,  138,  137,   75,   92,
 /*   740 */    61,  295,  120,  116,  134,  207,  207,  515,   64,  515,
 /*   750 */   515,  515,  515,   21,  515,  294,  115,  114,  198,  195,
 /*   760 */   192,  189,  186,   85,   84,   42,   41,   66,   65,   67,
 /*   770 */    69,   68,   74,   73,   71,   72,   70,  207,  207,   26,
 /*   780 */   515,  515,  176,  515,  207,  207,   18,  515,  113,   92,
 /*   790 */   515,   54,   63,   62,  133,  112,   92,  515,   61,  295,
 /*   800 */   206,  132,  515,  270,  269,  515,   29,  515,  515,  515,
 /*   810 */   207,   21,  207,  197,  207,  515,  198,  195,  192,  189,
 /*   820 */   186,   92,  515,  111,  207,   94,  131,  515,  515,  515,
 /*   830 */   207,  207,   63,   62,  207,  110,  515,  207,   61,  295,
 /*   840 */   151,  109,  108,  515,  181,  107,   64,  276,  106,  515,
 /*   850 */   515,   21,  515,  294,  287,  207,  198,  195,  192,  189,
 /*   860 */   186,  207,  207,   63,   62,  207,  105,  207,  207,   61,
 /*   870 */   295,  120,  104,  103,  207,  207,  102,   64,  101,  100,
 /*   880 */   515,  515,   21,  515,  294,   98,   97,  198,  195,  192,
 /*   890 */   189,  186,  515,  515,   42,   41,   66,   65,   67,   69,
 /*   900 */    68,   74,   73,   71,   72,   70,  451,  451,  515,  515,
 /*   910 */   515,  205,  515,  515,  515,   18,   63,   62,  449,  449,
 /*   920 */    75,  121,   61,  295,  151,  515,  515,  515,  515,  515,
 /*   930 */    64,  515,  515,  515,  515,   21,  515,  294,  287,  515,
 /*   940 */   198,  195,  192,  189,  186,  515,  515,  515,  515,   19,
 /*   950 */   515,  515,  515,  515,  515,  515,  451,  451,  451,  451,
 /*   960 */   451,  451,  451,  451,  451,  451,  515,  515,  449,  449,
 /*   970 */   449,  449,  449,  449,  449,  449,  449,  449,  515,  515,
 /*   980 */   515,  515,   66,   65,   67,   69,   68,   74,   73,   71,
 /*   990 */    72,   70,  515,  515,  515,  515,  515,  205,  515,  515,
 /*  1000 */   515,   18,  515,  515,  515,  515,   75,  515,  515,  515,
 /*  1010 */   515,   66,   65,   67,   69,   68,   74,   73,   71,   72,
 /*  1020 */    70,  515,  515,  515,  515,  515,  176,  515,  515,  515,
 /*  1030 */    18,   63,   62,  515,  515,   54,  515,   61,  295,  206,
 /*  1040 */   515,  515,  515,  515,  515,   64,  515,  515,  515,  515,
 /*  1050 */    21,  515,  294,  515,  515,  198,  195,  192,  189,  186,
 /*  1060 */   515,  515,  515,  515,   63,   62,  515,  450,  450,  515,
 /*  1070 */    61,  295,  120,  515,  515,  515,  515,  515,   64,  515,
 /*  1080 */   515,  515,  515,   21,  515,  294,  515,  515,  198,  195,
 /*  1090 */   192,  189,  186,   65,   67,   69,   68,   74,   73,   71,
 /*  1100 */    72,   70,   53,  515,  515,  515,  515,  205,  515,  515,
 /*  1110 */   515,   18,  515,  515,  515,  515,   75,  450,  450,  450,
 /*  1120 */   450,  450,  450,  450,  450,  450,  450,   67,   69,   68,
 /*  1130 */    74,   73,   71,   72,   70,  515,  515,  515,  515,  515,
 /*  1140 */   205,  515,  515,  515,   18,  515,  515,  515,  515,   75,
 /*  1150 */   515,  515,   52,   51,   50,   49,   48,   47,   46,   45,
 /*  1160 */    44,   43,  337,  233,  335,  334,  333,  232,  231,  230,
 /*  1170 */   329,  515,    9,  257,  515,  515,  515,    2,   69,   68,
 /*  1180 */    74,   73,   71,   72,   70,  515,  256,  255,  254,  207,
 /*  1190 */   205,  515,  515,  515,   18,  515,  515,  515,  257,   75,
 /*  1200 */    93,  515,  515,  515,  515,  515,  124,  147,  515,  515,
 /*  1210 */   515,  256,  255,  254,  207,  515,  515,  167,  166,  515,
 /*  1220 */   515,  515,  515,  515,  515,   93,  515,  515,  515,  515,
 /*  1230 */   515,  124,  147,  515,  515,  515,  515,  515,  515,  515,
 /*  1240 */   515,  515,  253,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    72,   18,   19,   20,   21,   22,  119,  120,  121,   81,
 /*    10 */     1,   28,   84,    1,    2,   32,   88,   89,   90,   91,
 /*    20 */    37,   87,   94,   95,   96,   97,   98,   99,  100,  101,
 /*    30 */   102,  103,  104,    3,    4,    2,  108,   97,    3,    4,
 /*    40 */   106,   32,  114,  115,  116,  117,  118,  107,  108,  109,
 /*    50 */   122,  123,  124,   72,   27,   96,   97,  129,  130,  131,
 /*    60 */   132,  133,   81,   33,  136,   84,   33,  108,   33,   88,
 /*    70 */    89,   90,   91,  114,  115,   94,   95,   96,   97,   98,
 /*    80 */    99,  100,  101,  102,  103,  104,  127,  128,   27,  108,
 /*    90 */    97,   28,   27,   30,    2,  114,  115,  116,  117,  118,
 /*   100 */   107,  108,  109,  122,  123,  124,    3,    4,    2,   72,
 /*   110 */   129,  130,  131,  132,  133,   28,   27,  136,   81,   32,
 /*   120 */    26,   84,  134,  135,   37,   88,   89,   90,   91,   32,
 /*   130 */    27,   94,   95,   96,   97,   98,   99,  100,  101,  102,
 /*   140 */   103,  104,    3,    4,   38,  108,   97,    3,    4,    1,
 /*   150 */     2,  114,  115,  116,  117,  118,  107,  108,   66,  122,
 /*   160 */   123,  124,   72,   26,   96,   97,  129,  130,  131,  132,
 /*   170 */   133,   81,   33,  136,   84,   26,  108,   33,   88,   89,
 /*   180 */    90,   91,  114,  115,   94,   95,   96,   97,   98,   99,
 /*   190 */   100,  101,  102,  103,  104,  127,    1,    2,  108,    3,
 /*   200 */     4,   27,    1,    2,  114,  115,  116,  117,  118,    1,
 /*   210 */     2,   37,  122,  123,  124,   74,   75,   27,   72,  129,
 /*   220 */   130,  131,  132,  133,   33,    2,  136,   81,   97,   33,
 /*   230 */    84,   26,   25,   27,   88,   89,   90,   91,  107,  108,
 /*   240 */    94,   95,   96,   97,   98,   99,  100,  101,  102,  103,
 /*   250 */   104,   27,   27,   27,  108,   97,   97,   27,   27,   27,
 /*   260 */   114,  115,  116,  117,  118,  107,  108,  108,  122,  123,
 /*   270 */   124,   72,   27,   37,   97,  129,  130,  131,  132,  133,
 /*   280 */    81,   97,  136,   84,   38,  108,   38,   88,   89,   90,
 /*   290 */    91,  114,  108,   94,   95,   96,   97,   98,   99,  100,
 /*   300 */   101,  102,  103,  104,   27,   27,   37,  108,   97,   97,
 /*   310 */    26,   32,   37,  114,  115,  116,  117,  118,   37,  108,
 /*   320 */   108,  122,  123,  124,   25,   38,    2,   72,  129,  130,
 /*   330 */   131,  132,  133,   32,   32,  136,   81,   97,    2,   84,
 /*   340 */    40,   32,   32,   88,   89,   90,   91,  107,  108,   94,
 /*   350 */    95,   96,   97,   98,   99,  100,  101,  102,  103,  104,
 /*   360 */    33,   33,   40,  108,   97,   97,   32,   38,   33,  114,
 /*   370 */   115,  116,  117,  118,  107,  108,  108,  122,  123,  124,
 /*   380 */    72,   40,   32,   97,  129,  130,  131,  132,  133,   81,
 /*   390 */    33,  136,   84,  107,  108,   40,   33,   89,   90,   91,
 /*   400 */     4,   93,   94,   95,   96,   97,   98,   99,  100,  101,
 /*   410 */   102,  103,  104,   32,   26,   33,  108,   97,   97,   33,
 /*   420 */    33,   32,  114,  115,  116,  117,  118,   61,  108,  108,
 /*   430 */   122,  123,  124,   32,   32,   97,   72,  129,  130,  131,
 /*   440 */   132,  133,    0,   32,  136,   81,  108,   27,   84,    2,
 /*   450 */     2,  113,   33,   89,   90,   91,   92,   32,   94,   95,
 /*   460 */    96,   97,   98,   99,  100,  101,  102,  103,  104,   32,
 /*   470 */    27,   29,  108,   31,   97,   36,   34,   35,  114,  115,
 /*   480 */   116,  117,  118,   33,   26,  108,  122,  123,  124,   47,
 /*   490 */    48,   35,   85,  129,  130,  131,  132,  133,   18,   19,
 /*   500 */   136,   20,   21,   22,   24,   25,   26,   27,   36,   28,
 /*   510 */    97,   26,   32,   32,   92,   35,   36,   37,   37,   39,
 /*   520 */   107,  108,   42,   43,   44,   45,   46,   47,   48,   49,
 /*   530 */    50,   13,   14,   15,   16,   17,   18,   19,   20,   21,
 /*   540 */    22,   61,   97,   63,   64,   65,   28,   67,   68,   69,
 /*   550 */    32,   97,   97,  108,  105,   37,   38,   36,  113,   97,
 /*   560 */    18,   19,  108,  108,  110,  111,   24,   25,   26,   27,
 /*   570 */   108,   97,  110,  111,   32,   92,   25,   35,   36,   37,
 /*   580 */   112,   39,  108,    2,   42,   43,   44,   45,   46,   47,
 /*   590 */    48,   49,   50,   13,   14,   15,   16,   17,   18,   19,
 /*   600 */    20,   21,   22,   61,   97,   63,   64,   65,   28,   67,
 /*   610 */    68,   69,   32,   33,   97,  108,  106,   37,   26,  106,
 /*   620 */   113,   97,   18,   19,  134,  108,   97,  110,   24,   25,
 /*   630 */    26,   27,  108,  106,  110,  111,   32,  108,   71,   35,
 /*   640 */   134,   37,  113,   39,   97,   97,   42,   43,   44,   45,
 /*   650 */    46,   47,   48,   49,   50,  108,  108,  110,  111,   97,
 /*   660 */   106,  113,  106,   97,   62,   61,  137,   63,   64,   65,
 /*   670 */   108,   67,   68,   69,  108,    7,    8,    9,   10,   11,
 /*   680 */    12,   13,   14,   15,   16,   17,   18,   19,   20,   21,
 /*   690 */    22,   97,   97,   97,  137,  137,   28,  137,  137,  137,
 /*   700 */    32,   33,  108,  108,  108,   37,  110,  111,    7,    8,
 /*   710 */     9,   10,   11,   12,   13,   14,   15,   16,   17,   18,
 /*   720 */    19,   20,   21,   22,  137,   97,   97,  137,   97,   28,
 /*   730 */   137,  137,   97,   32,   18,   19,  108,  108,   37,  108,
 /*   740 */    24,   25,   26,  108,  113,   97,   97,  137,   32,  137,
 /*   750 */   137,  137,  137,   37,  137,   39,  108,  108,   42,   43,
 /*   760 */    44,   45,   46,   47,   48,   49,   50,   13,   14,   15,
 /*   770 */    16,   17,   18,   19,   20,   21,   22,   97,   97,    5,
 /*   780 */   137,  137,   28,  137,   97,   97,   32,  137,  108,  108,
 /*   790 */   137,   37,   18,   19,  113,  108,  108,  137,   24,   25,
 /*   800 */    26,  113,  137,   49,   50,  137,   32,  137,  137,  137,
 /*   810 */    97,   37,   97,   39,   97,  137,   42,   43,   44,   45,
 /*   820 */    46,  108,  137,  108,   97,  108,  113,  137,  137,  137,
 /*   830 */    97,   97,   18,   19,   97,  108,  137,   97,   24,   25,
 /*   840 */    26,  108,  108,  137,   70,  108,   32,   33,  108,  137,
 /*   850 */   137,   37,  137,   39,   40,   97,   42,   43,   44,   45,
 /*   860 */    46,   97,   97,   18,   19,   97,  108,   97,   97,   24,
 /*   870 */    25,   26,  108,  108,   97,   97,  108,   32,  108,  108,
 /*   880 */   137,  137,   37,  137,   39,  108,  108,   42,   43,   44,
 /*   890 */    45,   46,  137,  137,   49,   50,   13,   14,   15,   16,
 /*   900 */    17,   18,   19,   20,   21,   22,    1,    2,  137,  137,
 /*   910 */   137,   28,  137,  137,  137,   32,   18,   19,    1,    2,
 /*   920 */    37,   38,   24,   25,   26,  137,  137,  137,  137,  137,
 /*   930 */    32,  137,  137,  137,  137,   37,  137,   39,   40,  137,
 /*   940 */    42,   43,   44,   45,   46,  137,  137,  137,  137,   32,
 /*   950 */   137,  137,  137,  137,  137,  137,   51,   52,   53,   54,
 /*   960 */    55,   56,   57,   58,   59,   60,  137,  137,   51,   52,
 /*   970 */    53,   54,   55,   56,   57,   58,   59,   60,  137,  137,
 /*   980 */   137,  137,   13,   14,   15,   16,   17,   18,   19,   20,
 /*   990 */    21,   22,  137,  137,  137,  137,  137,   28,  137,  137,
 /*  1000 */   137,   32,  137,  137,  137,  137,   37,  137,  137,  137,
 /*  1010 */   137,   13,   14,   15,   16,   17,   18,   19,   20,   21,
 /*  1020 */    22,  137,  137,  137,  137,  137,   28,  137,  137,  137,
 /*  1030 */    32,   18,   19,  137,  137,   37,  137,   24,   25,   26,
 /*  1040 */   137,  137,  137,  137,  137,   32,  137,  137,  137,  137,
 /*  1050 */    37,  137,   39,  137,  137,   42,   43,   44,   45,   46,
 /*  1060 */   137,  137,  137,  137,   18,   19,  137,    1,    2,  137,
 /*  1070 */    24,   25,   26,  137,  137,  137,  137,  137,   32,  137,
 /*  1080 */   137,  137,  137,   37,  137,   39,  137,  137,   42,   43,
 /*  1090 */    44,   45,   46,   14,   15,   16,   17,   18,   19,   20,
 /*  1100 */    21,   22,    1,  137,  137,  137,  137,   28,  137,  137,
 /*  1110 */   137,   32,  137,  137,  137,  137,   37,   51,   52,   53,
 /*  1120 */    54,   55,   56,   57,   58,   59,   60,   15,   16,   17,
 /*  1130 */    18,   19,   20,   21,   22,  137,  137,  137,  137,  137,
 /*  1140 */    28,  137,  137,  137,   32,  137,  137,  137,  137,   37,
 /*  1150 */   137,  137,   51,   52,   53,   54,   55,   56,   57,   58,
 /*  1160 */    59,   60,   76,   77,   78,   79,   80,   81,   82,   83,
 /*  1170 */    84,  137,   86,   81,  137,  137,  137,   91,   16,   17,
 /*  1180 */    18,   19,   20,   21,   22,  137,   94,   95,   96,   97,
 /*  1190 */    28,  137,  137,  137,   32,  137,  137,  137,   81,   37,
 /*  1200 */   108,  137,  137,  137,  137,  137,  114,  115,  137,  137,
 /*  1210 */   137,   94,   95,   96,   97,  137,  137,  125,  126,  137,
 /*  1220 */   137,  137,  137,  137,  137,  108,  137,  137,  137,  137,
 /*  1230 */   137,  114,  115,  137,  137,  137,  137,  137,  137,  137,
 /*  1240 */   137,  137,  125,
};
#define YY_SHIFT_USE_DFLT (-18)
#define YY_SHIFT_COUNT (233)
#define YY_SHIFT_MIN   (-17)
#define YY_SHIFT_MAX   (1162)
static const short yy_shift_ofst[] = {
 /*     0 */   -18,  542,  480,  604,  604,  604,  604,  604,  604,  604,
 /*    10 */   442,  716,  716,  845,  845,  814,  898,  898,  898,  898,
 /*    20 */  1013, 1013,  774,  774,  774,  774,  774,  774,  774,  774,
 /*    30 */   774,  898, 1013, 1013, 1013, 1013, 1046, 1013, 1013, 1013,
 /*    40 */   602, 1013, 1013, 1013, 1013, 1013, 1013, 1013, 1013, 1013,
 /*    50 */  1013, 1013, 1013, 1013, 1013, 1013, 1013, 1013, 1013, 1013,
 /*    60 */  1013, 1013, 1013, 1013, 1013, 1013, 1013, 1013, 1013, 1013,
 /*    70 */  1013, 1013, 1013, 1013, 1013, 1013, 1013,  567,  592,  592,
 /*    80 */   592,  567,  567,  592,  592,  592,  581,  551,  521,  521,
 /*    90 */   485,  668,  701,  754,  883,  580,  518,  969,  969,  998,
 /*   100 */   969,  969,  969,  969,  969,  969,  969,  969,  969,  969,
 /*   110 */   969,  969,  969,  969,  969,  969,  969,  969,  969,  969,
 /*   120 */   917, 1066,  905, 1079, 1101, 1112, 1162,  -17,  -17,  481,
 /*   130 */   481,  103,  196,  144,  139,   35,   30,   87,   87,   87,
 /*   140 */    87,   87,   87,  208,  201,   33,   92,  195,  148,   12,
 /*   150 */   106,    9,  174,   63,  324,  324,  472,  456,  458,  439,
 /*   160 */   443,  450,  437,  425,  419,  448,  420,  447,  411,  402,
 /*   170 */   401,  366,  389,  324,  324,  324,  388,  387,  386,  329,
 /*   180 */   382,  381,  396,  363,  357,  355,  350,  335,  341,  334,
 /*   190 */   328,  322,  310,  327,  300,  309,  336,  302,  301,  324,
 /*   200 */   287,  299,  246,  281,  275,  284,  279,  269,  278,  277,
 /*   210 */   248,  246,  207,  236,  245,  232,  231,  230,  226,  225,
 /*   220 */   224,  206,  205,  223,  190,  191,   97,  149,  137,   94,
 /*   230 */    89,   65,   61,   27,
};
#define YY_REDUCE_USE_DFLT (-114)
#define YY_REDUCE_COUNT (90)
#define YY_REDUCE_MIN   (-113)
#define YY_REDUCE_MAX   (1117)
static const short yy_reduce_ofst[] = {
 /*     0 */   141,  364,  308,  255,  199,  146,   90,   37,  -19,  -72,
 /*    10 */  1086, 1092, 1117,  -41,   68,  596,  547,  524,  462,  454,
 /*    20 */    -7,  -60,  713,  688,  681,  631,  548,  529,  507,  445,
 /*    30 */   338,  517,  413,  286,  267,  240,  177,  158,  131,   49,
 /*    40 */  -113,  778,  777,  771,  770,  768,  765,  764,  758,  740,
 /*    50 */   737,  734,  733,  727,  717,  715,  687,  680,  649,  648,
 /*    60 */   635,  629,  628,  595,  594,  566,  562,  474,  455,  377,
 /*    70 */   321,  320,  268,  212,  211,  184,  159,  -12,  -66,  556,
 /*    80 */   554,  506,  490,  527,  513,  510,  468,  449,  483,  422,
 /*    90 */   407,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   339,  510,  510,  510,  510,  510,  510,  510,  510,  510,
 /*    10 */   513,  489,  513,  492,  513,  513,  406,  406,  406,  406,
 /*    20 */   395,  395,  513,  513,  513,  513,  513,  513,  513,  513,
 /*    30 */   513,  513,  513,  513,  513,  513,  513,  513,  513,  513,
 /*    40 */   477,  513,  513,  513,  513,  513,  513,  513,  513,  513,
 /*    50 */   513,  513,  513,  513,  513,  513,  513,  513,  513,  513,
 /*    60 */   513,  513,  513,  513,  513,  513,  513,  513,  513,  513,
 /*    70 */   513,  513,  513,  513,  513,  513,  513,  513,  389,  513,
 /*    80 */   513,  512,  511,  513,  513,  513,  413,  513,  513,  513,
 /*    90 */   513,  433,  433,  513,  513,  513,  513,  458,  456,  513,
 /*   100 */   469,  468,  467,  466,  465,  464,  463,  462,  461,  460,
 /*   110 */   454,  440,  439,  438,  437,  436,  435,  393,  402,  404,
 /*   120 */   399,  401,  400,  428,  452,  429,  427,  426,  425,  421,
 /*   130 */   420,  513,  513,  513,  513,  513,  513,  432,  431,  430,
 /*   140 */   424,  423,  422,  513,  444,  513,  513,  513,  513,  444,
 /*   150 */   513,  399,  410,  352,  448,  446,  513,  513,  513,  381,
 /*   160 */   513,  513,  513,  513,  513,  493,  513,  488,  513,  513,
 /*   170 */   513,  476,  513,  455,  447,  445,  513,  513,  513,  513,
 /*   180 */   513,  513,  442,  513,  513,  513,  513,  513,  513,  513,
 /*   190 */   513,  513,  513,  513,  513,  513,  407,  398,  513,  396,
 /*   200 */   513,  513,  385,  513,  410,  513,  399,  410,  513,  513,
 /*   210 */   513,  513,  513,  513,  513,  513,  513,  513,  513,  513,
 /*   220 */   513,  513,  513,  390,  353,  513,  513,  513,  513,  513,
 /*   230 */   513,  513,  513,  513,  356,  382,  366,  478,  509,  508,
 /*   240 */   507,  503,  502,  501,  500,  499,  498,  497,  496,  491,
 /*   250 */   490,  495,  494,  487,  486,  485,  484,  483,  482,  481,
 /*   260 */   480,  479,  475,  474,  473,  472,  471,  470,  453,  459,
 /*   270 */   457,  408,  409,  414,  412,  415,  506,  504,  443,  441,
 /*   280 */   434,  505,  419,  418,  417,  416,  405,  403,  394,  391,
 /*   290 */   386,  411,  401,  400,  398,  397,  384,  383,  380,  379,
 /*   300 */   378,  377,  376,  375,  374,  392,  373,  372,  371,  370,
 /*   310 */   369,  368,  367,  365,  364,  363,  361,  362,  360,  359,
 /*   320 */   358,  357,  354,  388,  387,  355,  351,  350,  349,  348,
 /*   330 */   347,  346,  345,  344,  343,  342,  341,  340,
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
  "RBRACKET",      "LSQBRACKET",    "RSQBRACKET",    "KILLS",       
  "STRING",        "FUNCCALL",      "L2V",           "MAPSTRING",   
  "UNIT",          "SWITCH",        "LOCATION",      "VAR",         
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
  "stmt",          "bodyStmt",      "return_stmt",   "lbracket",    
  "rbracket",      "bodyStmtList",  "vdefAssign_stmt",  "cdef_stmt",   
  "assign_stmt",   "funcexpr",      "actionStmt",    "if_stmt",     
  "while_stmt",    "for_stmt",      "foreach_stmt",  "continue_stmt",
  "break_stmt",    "numList_nonEmpty",  "nameList_nonEmpty",  "exprList_nonEmpty",
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
 /*  18 */ "object_chunk ::= OBJECT NAME LBRACKET RBRACKET",
 /*  19 */ "stmt ::= error SEMICOLON",
 /*  20 */ "stmt ::= bodyStmt",
 /*  21 */ "stmt ::= return_stmt SEMICOLON",
 /*  22 */ "lbracket ::= LBRACKET",
 /*  23 */ "rbracket ::= RBRACKET",
 /*  24 */ "blockStmt ::= lbracket RBRACKET",
 /*  25 */ "blockStmt ::= lbracket return_stmt SEMICOLON rbracket",
 /*  26 */ "blockStmt ::= lbracket bodyStmtList rbracket",
 /*  27 */ "blockStmt ::= lbracket bodyStmtList return_stmt SEMICOLON rbracket",
 /*  28 */ "blockStmt ::= lbracket error RBRACKET",
 /*  29 */ "bodyStmt ::= blockStmt",
 /*  30 */ "bodyStmt ::= SEMICOLON",
 /*  31 */ "bodyStmt ::= vdef_stmt SEMICOLON",
 /*  32 */ "bodyStmt ::= vdefAssign_stmt SEMICOLON",
 /*  33 */ "bodyStmt ::= cdef_stmt SEMICOLON",
 /*  34 */ "bodyStmt ::= assign_stmt SEMICOLON",
 /*  35 */ "bodyStmt ::= funcexpr SEMICOLON",
 /*  36 */ "bodyStmt ::= actionStmt",
 /*  37 */ "bodyStmt ::= if_stmt",
 /*  38 */ "bodyStmt ::= while_stmt",
 /*  39 */ "bodyStmt ::= for_stmt",
 /*  40 */ "bodyStmt ::= foreach_stmt",
 /*  41 */ "bodyStmt ::= continue_stmt SEMICOLON",
 /*  42 */ "bodyStmt ::= break_stmt SEMICOLON",
 /*  43 */ "bodyStmtList ::= error",
 /*  44 */ "bodyStmtList ::= bodyStmt",
 /*  45 */ "bodyStmtList ::= bodyStmtList bodyStmt",
 /*  46 */ "bodyStmtList ::= bodyStmtList error",
 /*  47 */ "numList_nonEmpty ::= NUMBER",
 /*  48 */ "numList_nonEmpty ::= numList_nonEmpty COMMA NUMBER",
 /*  49 */ "nameList_nonEmpty ::= NAME",
 /*  50 */ "nameList_nonEmpty ::= nameList_nonEmpty COMMA NAME",
 /*  51 */ "nameList ::=",
 /*  52 */ "nameList ::= nameList_nonEmpty",
 /*  53 */ "exprList_nonEmpty ::= funcexpr LSQBRACKET LSQBRACKET numList_nonEmpty RSQBRACKET RSQBRACKET",
 /*  54 */ "expr ::= funcexpr LSQBRACKET LSQBRACKET NUMBER RSQBRACKET RSQBRACKET",
 /*  55 */ "exprList_nonEmpty ::= expr",
 /*  56 */ "exprList_nonEmpty ::= exprList_nonEmpty COMMA exprList_nonEmpty",
 /*  57 */ "exprList ::=",
 /*  58 */ "exprList ::= exprList_nonEmpty",
 /*  59 */ "expr ::= NUMBER",
 /*  60 */ "expr ::= KILLS",
 /*  61 */ "expr ::= NAME",
 /*  62 */ "expr ::= expr PERIOD NAME",
 /*  63 */ "expr ::= expr LSQBRACKET expr RSQBRACKET",
 /*  64 */ "fArgs_nonEmpty ::= expr",
 /*  65 */ "fArgs_nonEmpty ::= STRING",
 /*  66 */ "fArgs_nonEmpty ::= NAME ASSIGN expr",
 /*  67 */ "fArgs_nonEmpty ::= fArgs_nonEmpty COMMA fArgs_nonEmpty",
 /*  68 */ "fArgs ::=",
 /*  69 */ "fArgs ::= fArgs_nonEmpty",
 /*  70 */ "funcexpr ::= NAME LPAREN fArgs RPAREN",
 /*  71 */ "funcexpr ::= expr LPAREN fArgs RPAREN",
 /*  72 */ "expr ::= funcexpr",
 /*  73 */ "expr ::= LPAREN expr RPAREN",
 /*  74 */ "commaSkippable ::= COMMA",
 /*  75 */ "commaSkippable ::=",
 /*  76 */ "expr ::= LSQBRACKET exprList commaSkippable RSQBRACKET",
 /*  77 */ "expr ::= L2V LPAREN lexpr RPAREN",
 /*  78 */ "expr ::= MAPSTRING LPAREN STRING RPAREN",
 /*  79 */ "expr ::= UNIT LPAREN STRING RPAREN",
 /*  80 */ "expr ::= SWITCH LPAREN STRING RPAREN",
 /*  81 */ "expr ::= LOCATION LPAREN STRING RPAREN",
 /*  82 */ "expr ::= expr PLUS expr",
 /*  83 */ "expr ::= expr MINUS expr",
 /*  84 */ "expr ::= expr MULTIPLY expr",
 /*  85 */ "expr ::= expr DIVIDE expr",
 /*  86 */ "expr ::= expr MOD expr",
 /*  87 */ "expr ::= expr LSHIFT expr",
 /*  88 */ "expr ::= expr RSHIFT expr",
 /*  89 */ "expr ::= expr BITAND expr",
 /*  90 */ "expr ::= expr BITOR expr",
 /*  91 */ "expr ::= expr BITXOR expr",
 /*  92 */ "expr ::= PLUS expr",
 /*  93 */ "expr ::= MINUS expr",
 /*  94 */ "expr ::= BITNOT expr",
 /*  95 */ "lexpr ::= expr",
 /*  96 */ "lexpr ::= LPAREN lexpr RPAREN",
 /*  97 */ "lexpr ::= expr EQ expr",
 /*  98 */ "lexpr ::= expr NE expr",
 /*  99 */ "lexpr ::= expr LE expr",
 /* 100 */ "lexpr ::= expr LT expr",
 /* 101 */ "lexpr ::= expr GE expr",
 /* 102 */ "lexpr ::= expr GT expr",
 /* 103 */ "lexpr ::= lexpr LAND lexpr",
 /* 104 */ "lexpr ::= lexpr LOR lexpr",
 /* 105 */ "lexpr ::= LNOT lexpr",
 /* 106 */ "vdef_stmt ::= VAR nameList_nonEmpty",
 /* 107 */ "vdefAssign_stmt ::= VAR nameList_nonEmpty ASSIGN exprList_nonEmpty",
 /* 108 */ "vdefAssign_global_stmt ::= VAR nameList_nonEmpty ASSIGN exprList_nonEmpty",
 /* 109 */ "cdef_stmt ::= CONST nameList_nonEmpty ASSIGN exprList_nonEmpty",
 /* 110 */ "cdef_global_stmt ::= CONST nameList_nonEmpty ASSIGN exprList_nonEmpty",
 /* 111 */ "lvalue ::= NAME",
 /* 112 */ "lvalue ::= expr LSQBRACKET expr RSQBRACKET",
 /* 113 */ "lvalue ::= expr PERIOD NAME",
 /* 114 */ "lvalueList_nonEmpty ::= lvalue",
 /* 115 */ "lvalueList_nonEmpty ::= lvalueList_nonEmpty COMMA lvalue",
 /* 116 */ "assign_stmt ::= lvalue ASSIGN expr",
 /* 117 */ "assign_stmt ::= lvalueList_nonEmpty ASSIGN exprList_nonEmpty",
 /* 118 */ "assign_stmt ::= INC expr",
 /* 119 */ "assign_stmt ::= expr INC",
 /* 120 */ "assign_stmt ::= DEC expr",
 /* 121 */ "assign_stmt ::= expr DEC",
 /* 122 */ "assign_stmt ::= lvalue IADD expr",
 /* 123 */ "assign_stmt ::= lvalue ISUB expr",
 /* 124 */ "assign_stmt ::= lvalue IMUL expr",
 /* 125 */ "assign_stmt ::= lvalue IDIV expr",
 /* 126 */ "assign_stmt ::= lvalue IMOD expr",
 /* 127 */ "assign_stmt ::= lvalue ILSH expr",
 /* 128 */ "assign_stmt ::= lvalue IRSH expr",
 /* 129 */ "assign_stmt ::= lvalue IBND expr",
 /* 130 */ "assign_stmt ::= lvalue IBOR expr",
 /* 131 */ "assign_stmt ::= lvalue IBXR expr",
 /* 132 */ "if_start ::= IF",
 /* 133 */ "if_header ::= if_start LPAREN lexpr RPAREN",
 /* 134 */ "if_block ::= if_header stmt",
 /* 135 */ "elif_start ::= ELSE IF",
 /* 136 */ "elif_header ::= elif_start LPAREN lexpr RPAREN",
 /* 137 */ "if_block ::= if_block elif_header stmt",
 /* 138 */ "else_header ::= ELSE",
 /* 139 */ "if_stmt ::= if_block",
 /* 140 */ "if_stmt ::= if_block else_header stmt",
 /* 141 */ "while_start ::= WHILE",
 /* 142 */ "while_header ::= while_start LPAREN lexpr RPAREN",
 /* 143 */ "while_stmt ::= while_header stmt",
 /* 144 */ "for_opener ::= FOR LPAREN",
 /* 145 */ "for_init_stmt_nonEmpty ::= vdef_stmt",
 /* 146 */ "for_init_stmt_nonEmpty ::= vdefAssign_stmt",
 /* 147 */ "for_init_stmt_nonEmpty ::= cdef_stmt",
 /* 148 */ "for_init_stmt_nonEmpty ::= assign_stmt",
 /* 149 */ "for_init_stmt_nonEmpty ::= for_init_stmt_nonEmpty COMMA for_init_stmt_nonEmpty",
 /* 150 */ "for_init_stmt ::= for_init_stmt_nonEmpty",
 /* 151 */ "for_init_stmt ::=",
 /* 152 */ "for_action_stmt_nonEmpty ::= assign_stmt",
 /* 153 */ "for_action_stmt_nonEmpty ::= for_action_stmt_nonEmpty COMMA for_action_stmt_nonEmpty",
 /* 154 */ "for_action_stmt ::=",
 /* 155 */ "for_action_stmt ::= for_action_stmt_nonEmpty",
 /* 156 */ "for_header1 ::= for_opener for_init_stmt SEMICOLON",
 /* 157 */ "for_header2 ::= for_header1 lexpr SEMICOLON",
 /* 158 */ "for_header ::= for_header2 for_action_stmt RPAREN",
 /* 159 */ "for_stmt ::= for_header stmt",
 /* 160 */ "foreach_opener ::= FOREACH LPAREN",
 /* 161 */ "foreach_header ::= foreach_opener nameList_nonEmpty COLON exprList_nonEmpty RPAREN",
 /* 162 */ "foreach_stmt ::= foreach_header stmt",
 /* 163 */ "continue_stmt ::= CONTINUE",
 /* 164 */ "break_stmt ::= BREAK",
 /* 165 */ "return_stmt ::= RETURN exprList",
 /* 166 */ "lexpr ::= CONDITIONNAME LPAREN fArgs RPAREN",
 /* 167 */ "lexpr ::= KILLS LPAREN fArgs RPAREN",
 /* 168 */ "lexpr ::= CONDITIONNAME LPAREN RPAREN",
 /* 169 */ "action ::= ACTIONNAME LPAREN fArgs RPAREN SEMICOLON",
 /* 170 */ "actions ::= action action",
 /* 171 */ "actions ::= actions action",
 /* 172 */ "actionStmt_start ::=",
 /* 173 */ "actionStmt ::= actionStmt_start action",
 /* 174 */ "actionStmt ::= actionStmt_start actions",
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
#line 39 "parser\\epparser.lemon"
 delete (yypminor->yy0); 
#line 902 "parser\\epparser.c"
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
  { 80, 4 },
  { 88, 2 },
  { 88, 1 },
  { 88, 2 },
  { 91, 1 },
  { 92, 1 },
  { 84, 2 },
  { 84, 4 },
  { 84, 3 },
  { 84, 5 },
  { 84, 3 },
  { 89, 1 },
  { 89, 1 },
  { 89, 2 },
  { 89, 2 },
  { 89, 2 },
  { 89, 2 },
  { 89, 2 },
  { 89, 1 },
  { 89, 1 },
  { 89, 1 },
  { 89, 1 },
  { 89, 1 },
  { 89, 2 },
  { 89, 2 },
  { 93, 1 },
  { 93, 1 },
  { 93, 2 },
  { 93, 2 },
  { 105, 1 },
  { 105, 3 },
  { 106, 1 },
  { 106, 3 },
  { 87, 0 },
  { 87, 1 },
  { 107, 6 },
  { 108, 6 },
  { 107, 1 },
  { 107, 3 },
  { 109, 0 },
  { 109, 1 },
  { 108, 1 },
  { 108, 1 },
  { 108, 1 },
  { 108, 3 },
  { 108, 4 },
  { 110, 1 },
  { 110, 1 },
  { 110, 3 },
  { 110, 3 },
  { 111, 0 },
  { 111, 1 },
  { 97, 4 },
  { 97, 4 },
  { 108, 1 },
  { 108, 3 },
  { 112, 1 },
  { 112, 0 },
  { 108, 4 },
  { 108, 4 },
  { 108, 4 },
  { 108, 4 },
  { 108, 4 },
  { 108, 4 },
  { 108, 3 },
  { 108, 3 },
  { 108, 3 },
  { 108, 3 },
  { 108, 3 },
  { 108, 3 },
  { 108, 3 },
  { 108, 3 },
  { 108, 3 },
  { 108, 3 },
  { 108, 2 },
  { 108, 2 },
  { 108, 2 },
  { 113, 1 },
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
  { 81, 2 },
  { 94, 4 },
  { 82, 4 },
  { 95, 4 },
  { 83, 4 },
  { 114, 1 },
  { 114, 4 },
  { 114, 3 },
  { 115, 1 },
  { 115, 3 },
  { 96, 3 },
  { 96, 3 },
  { 96, 2 },
  { 96, 2 },
  { 96, 2 },
  { 96, 2 },
  { 96, 3 },
  { 96, 3 },
  { 96, 3 },
  { 96, 3 },
  { 96, 3 },
  { 96, 3 },
  { 96, 3 },
  { 96, 3 },
  { 96, 3 },
  { 96, 3 },
  { 116, 1 },
  { 117, 4 },
  { 118, 2 },
  { 119, 2 },
  { 120, 4 },
  { 118, 3 },
  { 121, 1 },
  { 99, 1 },
  { 99, 3 },
  { 122, 1 },
  { 123, 4 },
  { 100, 2 },
  { 124, 2 },
  { 125, 1 },
  { 125, 1 },
  { 125, 1 },
  { 125, 1 },
  { 125, 3 },
  { 126, 1 },
  { 126, 0 },
  { 127, 1 },
  { 127, 3 },
  { 128, 0 },
  { 128, 1 },
  { 129, 3 },
  { 130, 3 },
  { 131, 3 },
  { 101, 2 },
  { 132, 2 },
  { 133, 5 },
  { 102, 2 },
  { 103, 1 },
  { 104, 1 },
  { 90, 2 },
  { 113, 4 },
  { 113, 4 },
  { 113, 3 },
  { 134, 5 },
  { 135, 2 },
  { 135, 2 },
  { 136, 0 },
  { 98, 2 },
  { 98, 2 },
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
#line 75 "parser\\epparser.lemon"
{
    throw_error(48993, "Misplaced block statement");
}
#line 1374 "parser\\epparser.c"
        break;
      case 11: /* dottedName ::= NAME */
      case 47: /* numList_nonEmpty ::= NUMBER */ yytestcase(yyruleno==47);
      case 49: /* nameList_nonEmpty ::= NAME */ yytestcase(yyruleno==49);
      case 52: /* nameList ::= nameList_nonEmpty */ yytestcase(yyruleno==52);
      case 55: /* exprList_nonEmpty ::= expr */ yytestcase(yyruleno==55);
      case 58: /* exprList ::= exprList_nonEmpty */ yytestcase(yyruleno==58);
      case 59: /* expr ::= NUMBER */ yytestcase(yyruleno==59);
      case 64: /* fArgs_nonEmpty ::= expr */ yytestcase(yyruleno==64);
      case 65: /* fArgs_nonEmpty ::= STRING */ yytestcase(yyruleno==65);
      case 69: /* fArgs ::= fArgs_nonEmpty */ yytestcase(yyruleno==69);
      case 72: /* expr ::= funcexpr */ yytestcase(yyruleno==72);
      case 95: /* lexpr ::= expr */ yytestcase(yyruleno==95);
      case 114: /* lvalueList_nonEmpty ::= lvalue */ yytestcase(yyruleno==114);
#line 81 "parser\\epparser.lemon"
{ yygotominor.yy0 = yymsp[0].minor.yy0; }
#line 1391 "parser\\epparser.c"
        break;
      case 12: /* dottedName ::= dottedName PERIOD NAME */
#line 82 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = yymsp[-2].minor.yy0->data + "." + yymsp[0].minor.yy0->data;
    delete yymsp[-2].minor.yy0;
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1400 "parser\\epparser.c"
        break;
      case 13: /* import_chunk ::= IMPORT dottedName AS NAME */
#line 88 "parser\\epparser.lemon"
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
#line 1416 "parser\\epparser.c"
        break;
      case 14: /* import_chunk ::= IMPORT dottedName */
#line 101 "parser\\epparser.lemon"
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
#line 1432 "parser\\epparser.c"
        break;
      case 15: /* fdef_header ::= FUNCTION NAME LPAREN nameList RPAREN */
#line 115 "parser\\epparser.lemon"
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
#line 1465 "parser\\epparser.c"
        break;
      case 16: /* fdef_chunk ::= fdef_header stmt */
#line 145 "parser\\epparser.lemon"
{
    if(MAP_DEBUG){
        ps->gen << "MDBG_POPF()" << std::endl;
    }
    ps->gen.unindent(true);
    ps->closure.popScope();
    currentFunction = "";
}
#line 1477 "parser\\epparser.c"
        break;
      case 17: /* fdecl_chunk ::= FUNCTION NAME LPAREN nameList RPAREN SEMICOLON */
#line 154 "parser\\epparser.lemon"
{
    // Preprocess yymsp[-4].minor.yy0
    funcNamePreprocess(yymsp[-4].minor.yy0->data);
    if(!ps->closure.declareFunction(yymsp[-4].minor.yy0->data)) {
        throw_error(72461, "Declaring function with non-function yymsp[-4].minor.yy0 " + yymsp[-4].minor.yy0->data, yymsp[-4].minor.yy0->line);
    }
}
#line 1488 "parser\\epparser.c"
        break;
      case 18: /* object_chunk ::= OBJECT NAME LBRACKET RBRACKET */
#line 165 "parser\\epparser.lemon"
{
    ps->gen << "class " << yymsp[-2].minor.yy0->data << "(EUDStruct):\n";
    ps->gen.indent();
    ps->gen << "_fields_ = [\n";
    ps->gen << "]\n";
    ps->gen.unindent(true);

    funcNamePreprocess(yymsp[-2].minor.yy0->data);
    if(!ps->closure.declareFunction(yymsp[-2].minor.yy0->data)) {
        throw_error(72461, "Declaring function with non-function yymsp[-2].minor.yy0 " + yymsp[-2].minor.yy0->data, yymsp[-2].minor.yy0->line);
    }
}
#line 1504 "parser\\epparser.c"
        break;
      case 19: /* stmt ::= error SEMICOLON */
#line 179 "parser\\epparser.lemon"
{ throw_error(6974, "Error while parsing statement", yymsp[0].minor.yy0->line); delete yymsp[0].minor.yy0; }
#line 1509 "parser\\epparser.c"
        break;
      case 22: /* lbracket ::= LBRACKET */
#line 185 "parser\\epparser.lemon"
{ ps->closure.pushScope(); }
#line 1514 "parser\\epparser.c"
        break;
      case 23: /* rbracket ::= RBRACKET */
#line 186 "parser\\epparser.lemon"
{ ps->closure.popScope(); }
#line 1519 "parser\\epparser.c"
        break;
      case 24: /* blockStmt ::= lbracket RBRACKET */
#line 188 "parser\\epparser.lemon"
{
    ps->closure.popScope();
}
#line 1526 "parser\\epparser.c"
        break;
      case 28: /* blockStmt ::= lbracket error RBRACKET */
#line 194 "parser\\epparser.lemon"
{
    throw_error(6298, "Block not terminated properly.", yymsp[0].minor.yy0->line);
    ps->closure.popScope();
    delete yymsp[0].minor.yy0;
}
#line 1535 "parser\\epparser.c"
        break;
      case 35: /* bodyStmt ::= funcexpr SEMICOLON */
#line 206 "parser\\epparser.lemon"
{ ps->gen << yymsp[-1].minor.yy0->data << std::endl; }
#line 1540 "parser\\epparser.c"
        break;
      case 43: /* bodyStmtList ::= error */
      case 46: /* bodyStmtList ::= bodyStmtList error */ yytestcase(yyruleno==46);
#line 216 "parser\\epparser.lemon"
{
    throw_error(8510, "Incomplete statement");
}
#line 1548 "parser\\epparser.c"
        break;
      case 48: /* numList_nonEmpty ::= numList_nonEmpty COMMA NUMBER */
      case 50: /* nameList_nonEmpty ::= nameList_nonEmpty COMMA NAME */ yytestcase(yyruleno==50);
      case 115: /* lvalueList_nonEmpty ::= lvalueList_nonEmpty COMMA lvalue */ yytestcase(yyruleno==115);
#line 229 "parser\\epparser.lemon"
{ yygotominor.yy0 = commaConcat(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1555 "parser\\epparser.c"
        break;
      case 51: /* nameList ::= */
      case 57: /* exprList ::= */ yytestcase(yyruleno==57);
      case 68: /* fArgs ::= */ yytestcase(yyruleno==68);
#line 232 "parser\\epparser.lemon"
{ yygotominor.yy0 = genEmpty(); }
#line 1562 "parser\\epparser.c"
        break;
      case 53: /* exprList_nonEmpty ::= funcexpr LSQBRACKET LSQBRACKET numList_nonEmpty RSQBRACKET RSQBRACKET */
#line 235 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "_SRET(" + yymsp[-5].minor.yy0->data + ", [" + yymsp[-2].minor.yy0->data + "])";
    delete yymsp[-5].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1571 "parser\\epparser.c"
        break;
      case 54: /* expr ::= funcexpr LSQBRACKET LSQBRACKET NUMBER RSQBRACKET RSQBRACKET */
#line 242 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-5].minor.yy0->data + "[" + yymsp[-2].minor.yy0->data + "]";
    delete yymsp[-5].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1580 "parser\\epparser.c"
        break;
      case 56: /* exprList_nonEmpty ::= exprList_nonEmpty COMMA exprList_nonEmpty */
#line 250 "parser\\epparser.lemon"
{ yygotominor.yy0 = new Token((yymsp[-2].minor.yy0->data) + ", " + (yymsp[0].minor.yy0->data), yymsp[0].minor.yy0); delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1585 "parser\\epparser.c"
        break;
      case 60: /* expr ::= KILLS */
#line 257 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = "4";
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1593 "parser\\epparser.c"
        break;
      case 61: /* expr ::= NAME */
#line 262 "parser\\epparser.lemon"
{
    checkIsRValue(yymsp[0].minor.yy0->data, yymsp[0].minor.yy0->line);
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1601 "parser\\epparser.c"
        break;
      case 62: /* expr ::= expr PERIOD NAME */
#line 267 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + "." + yymsp[0].minor.yy0->data;
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1610 "parser\\epparser.c"
        break;
      case 63: /* expr ::= expr LSQBRACKET expr RSQBRACKET */
#line 273 "parser\\epparser.lemon"
{
    yymsp[-3].minor.yy0->data = yymsp[-3].minor.yy0->data + "[" + yymsp[-1].minor.yy0->data + "]";
    delete yymsp[-1].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 1619 "parser\\epparser.c"
        break;
      case 66: /* fArgs_nonEmpty ::= NAME ASSIGN expr */
#line 282 "parser\\epparser.lemon"
{  // Keyword argument
    yymsp[0].minor.yy0->data = yymsp[-2].minor.yy0->data + "=" + yymsp[0].minor.yy0->data;
    yymsp[0].minor.yy0->type = TOKEN_TEMP;
    yygotominor.yy0 = yymsp[0].minor.yy0;
    delete yymsp[-2].minor.yy0;
}
#line 1629 "parser\\epparser.c"
        break;
      case 67: /* fArgs_nonEmpty ::= fArgs_nonEmpty COMMA fArgs_nonEmpty */
#line 289 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data;
    yymsp[0].minor.yy0->type = TOKEN_TEMP;
    yygotominor.yy0 = yymsp[0].minor.yy0;
    delete yymsp[-2].minor.yy0;
}
#line 1639 "parser\\epparser.c"
        break;
      case 70: /* funcexpr ::= NAME LPAREN fArgs RPAREN */
#line 299 "parser\\epparser.lemon"
{
    functionCalledInMultipleActions = true;

    // Preprocess yymsp[-3].minor.yy0
    funcNamePreprocess(yymsp[-3].minor.yy0->data);
    checkIsFunction(yymsp[-3].minor.yy0->data, yymsp[-3].minor.yy0->line);
    yymsp[-3].minor.yy0->data += "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 1652 "parser\\epparser.c"
        break;
      case 71: /* funcexpr ::= expr LPAREN fArgs RPAREN */
#line 309 "parser\\epparser.lemon"
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
#line 1676 "parser\\epparser.c"
        break;
      case 73: /* expr ::= LPAREN expr RPAREN */
      case 96: /* lexpr ::= LPAREN lexpr RPAREN */ yytestcase(yyruleno==96);
#line 337 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1685 "parser\\epparser.c"
        break;
      case 76: /* expr ::= LSQBRACKET exprList commaSkippable RSQBRACKET */
#line 345 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "_ARR(FlattenList([" + yymsp[-2].minor.yy0->data + "]))";
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1693 "parser\\epparser.c"
        break;
      case 77: /* expr ::= L2V LPAREN lexpr RPAREN */
#line 350 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "_L2V(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1701 "parser\\epparser.c"
        break;
      case 78: /* expr ::= MAPSTRING LPAREN STRING RPAREN */
#line 355 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetStringIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1709 "parser\\epparser.c"
        break;
      case 79: /* expr ::= UNIT LPAREN STRING RPAREN */
#line 360 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "EncodeUnit(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1717 "parser\\epparser.c"
        break;
      case 80: /* expr ::= SWITCH LPAREN STRING RPAREN */
#line 365 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "EncodeSwitch(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1725 "parser\\epparser.c"
        break;
      case 81: /* expr ::= LOCATION LPAREN STRING RPAREN */
#line 370 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetLocationIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1733 "parser\\epparser.c"
        break;
      case 82: /* expr ::= expr PLUS expr */
#line 376 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "+",  yymsp[0].minor.yy0); }
#line 1738 "parser\\epparser.c"
        break;
      case 83: /* expr ::= expr MINUS expr */
#line 377 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "-",  yymsp[0].minor.yy0); }
#line 1743 "parser\\epparser.c"
        break;
      case 84: /* expr ::= expr MULTIPLY expr */
#line 378 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "*",  yymsp[0].minor.yy0); }
#line 1748 "parser\\epparser.c"
        break;
      case 85: /* expr ::= expr DIVIDE expr */
#line 379 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "//", yymsp[0].minor.yy0); }
#line 1753 "parser\\epparser.c"
        break;
      case 86: /* expr ::= expr MOD expr */
#line 380 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "%",  yymsp[0].minor.yy0); }
#line 1758 "parser\\epparser.c"
        break;
      case 87: /* expr ::= expr LSHIFT expr */
#line 381 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = "_LSH(" + yymsp[-2].minor.yy0->data + "," + yymsp[0].minor.yy0->data + ")";
    delete yymsp[-2].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0);
}
#line 1767 "parser\\epparser.c"
        break;
      case 88: /* expr ::= expr RSHIFT expr */
#line 386 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, ">>", yymsp[0].minor.yy0); }
#line 1772 "parser\\epparser.c"
        break;
      case 89: /* expr ::= expr BITAND expr */
#line 387 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "&",  yymsp[0].minor.yy0); }
#line 1777 "parser\\epparser.c"
        break;
      case 90: /* expr ::= expr BITOR expr */
#line 388 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "|",  yymsp[0].minor.yy0); }
#line 1782 "parser\\epparser.c"
        break;
      case 91: /* expr ::= expr BITXOR expr */
#line 389 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "^",  yymsp[0].minor.yy0); }
#line 1787 "parser\\epparser.c"
        break;
      case 92: /* expr ::= PLUS expr */
#line 392 "parser\\epparser.lemon"
{ yymsp[0].minor.yy0->data = "+" + yymsp[0].minor.yy0->data; yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0); }
#line 1792 "parser\\epparser.c"
        break;
      case 93: /* expr ::= MINUS expr */
#line 393 "parser\\epparser.lemon"
{ yymsp[0].minor.yy0->data = "-" + yymsp[0].minor.yy0->data; yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0); }
#line 1797 "parser\\epparser.c"
        break;
      case 94: /* expr ::= BITNOT expr */
#line 394 "parser\\epparser.lemon"
{ yymsp[0].minor.yy0->data = "~" + yymsp[0].minor.yy0->data; yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0); }
#line 1802 "parser\\epparser.c"
        break;
      case 97: /* lexpr ::= expr EQ expr */
#line 404 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "==", yymsp[0].minor.yy0); }
#line 1807 "parser\\epparser.c"
        break;
      case 98: /* lexpr ::= expr NE expr */
#line 405 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genEmpty();
    yygotominor.yy0->line = yymsp[0].minor.yy0->line;

    yygotominor.yy0->type = TOKEN_NE;
    yygotominor.yy0->subToken[0] = yymsp[-2].minor.yy0;
    yygotominor.yy0->subToken[1] = yymsp[0].minor.yy0;
    yygotominor.yy0->data = yymsp[-2].minor.yy0->data + " != " + yymsp[0].minor.yy0->data;
}
#line 1820 "parser\\epparser.c"
        break;
      case 99: /* lexpr ::= expr LE expr */
#line 415 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "<=", yymsp[0].minor.yy0); }
#line 1825 "parser\\epparser.c"
        break;
      case 100: /* lexpr ::= expr LT expr */
#line 416 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "<",  yymsp[0].minor.yy0); }
#line 1830 "parser\\epparser.c"
        break;
      case 101: /* lexpr ::= expr GE expr */
#line 417 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, ">=", yymsp[0].minor.yy0); }
#line 1835 "parser\\epparser.c"
        break;
      case 102: /* lexpr ::= expr GT expr */
#line 418 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, ">" , yymsp[0].minor.yy0); }
#line 1840 "parser\\epparser.c"
        break;
      case 103: /* lexpr ::= lexpr LAND lexpr */
#line 421 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genEmpty();
    yygotominor.yy0->line = yymsp[0].minor.yy0->line;

    // Generate data!
    yygotominor.yy0->type = TOKEN_LAND;
    yygotominor.yy0->subToken[0] = yymsp[-2].minor.yy0;
    yygotominor.yy0->subToken[1] = yymsp[0].minor.yy0;
    yygotominor.yy0->data = "[" + flatListGetter(yygotominor.yy0, TOKEN_LAND) + "]";
}
#line 1854 "parser\\epparser.c"
        break;
      case 104: /* lexpr ::= lexpr LOR lexpr */
#line 433 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genEmpty();
    yygotominor.yy0->line = yymsp[0].minor.yy0->line;

    // Generate data!
    yygotominor.yy0->type = TOKEN_LOR;
    yygotominor.yy0->subToken[0] = yymsp[-2].minor.yy0;
    yygotominor.yy0->subToken[1] = yymsp[0].minor.yy0;
    yygotominor.yy0->data = "EUDOr(" + flatListGetter(yygotominor.yy0, TOKEN_LOR) + ")";
}
#line 1868 "parser\\epparser.c"
        break;
      case 105: /* lexpr ::= LNOT lexpr */
#line 444 "parser\\epparser.lemon"
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
        yygotominor.yy0->data = "EUDNot([" + yymsp[0].minor.yy0->data + "])";
        yygotominor.yy0->subToken[0] = yymsp[0].minor.yy0;
    }
}
#line 1886 "parser\\epparser.c"
        break;
      case 106: /* vdef_stmt ::= VAR nameList_nonEmpty */
#line 461 "parser\\epparser.lemon"
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
#line 1910 "parser\\epparser.c"
        break;
      case 107: /* vdefAssign_stmt ::= VAR nameList_nonEmpty ASSIGN exprList_nonEmpty */
#line 482 "parser\\epparser.lemon"
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
#line 1935 "parser\\epparser.c"
        break;
      case 108: /* vdefAssign_global_stmt ::= VAR nameList_nonEmpty ASSIGN exprList_nonEmpty */
#line 504 "parser\\epparser.lemon"
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
    ps->gen << "_IGVA(" << s << ", lambda: [" << yymsp[0].minor.yy0->data << "])" << std::endl;

    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 1955 "parser\\epparser.c"
        break;
      case 109: /* cdef_stmt ::= CONST nameList_nonEmpty ASSIGN exprList_nonEmpty */
#line 521 "parser\\epparser.lemon"
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
#line 1977 "parser\\epparser.c"
        break;
      case 110: /* cdef_global_stmt ::= CONST nameList_nonEmpty ASSIGN exprList_nonEmpty */
#line 540 "parser\\epparser.lemon"
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
#line 1999 "parser\\epparser.c"
        break;
      case 111: /* lvalue ::= NAME */
#line 560 "parser\\epparser.lemon"
{
    checkIsVariable(yymsp[0].minor.yy0->data, yymsp[0].minor.yy0->line);
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 2007 "parser\\epparser.c"
        break;
      case 112: /* lvalue ::= expr LSQBRACKET expr RSQBRACKET */
#line 565 "parser\\epparser.lemon"
{
    checkIsConstant(yymsp[-3].minor.yy0->data, yymsp[-3].minor.yy0->line);
    yymsp[-1].minor.yy0->data = "_ARRW(" + yymsp[-3].minor.yy0->data + ", " + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
    delete yymsp[-3].minor.yy0;
}
#line 2017 "parser\\epparser.c"
        break;
      case 113: /* lvalue ::= expr PERIOD NAME */
#line 572 "parser\\epparser.lemon"
{
    checkIsConstant(yymsp[-2].minor.yy0->data, yymsp[-2].minor.yy0->line);
    yymsp[0].minor.yy0->data = "_ATTW(" + yymsp[-2].minor.yy0->data + ", '" + yymsp[0].minor.yy0->data + "')";
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0);
    delete yymsp[-2].minor.yy0;
}
#line 2027 "parser\\epparser.c"
        break;
      case 116: /* assign_stmt ::= lvalue ASSIGN expr */
#line 581 "parser\\epparser.lemon"
{
    ps->gen << yymsp[-2].minor.yy0->data << " << (" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 2035 "parser\\epparser.c"
        break;
      case 117: /* assign_stmt ::= lvalueList_nonEmpty ASSIGN exprList_nonEmpty */
#line 586 "parser\\epparser.lemon"
{
    ps->gen << "_SV([" << yymsp[-2].minor.yy0->data << "], [" << yymsp[0].minor.yy0->data << "])" << std::endl;
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 2043 "parser\\epparser.c"
        break;
      case 118: /* assign_stmt ::= INC expr */
#line 594 "parser\\epparser.lemon"
{ ps->gen << yymsp[0].minor.yy0->data << ".__iadd__(1)" << std::endl; delete yymsp[0].minor.yy0; }
#line 2048 "parser\\epparser.c"
        break;
      case 119: /* assign_stmt ::= expr INC */
#line 595 "parser\\epparser.lemon"
{ ps->gen << yymsp[-1].minor.yy0->data << ".__iadd__(1)" << std::endl; delete yymsp[-1].minor.yy0; }
#line 2053 "parser\\epparser.c"
        break;
      case 120: /* assign_stmt ::= DEC expr */
#line 596 "parser\\epparser.lemon"
{ ps->gen << yymsp[0].minor.yy0->data << ".__isub__(1)" << std::endl; delete yymsp[0].minor.yy0; }
#line 2058 "parser\\epparser.c"
        break;
      case 121: /* assign_stmt ::= expr DEC */
#line 597 "parser\\epparser.lemon"
{ ps->gen << yymsp[-1].minor.yy0->data << ".__isub__(1)" << std::endl; delete yymsp[-1].minor.yy0; }
#line 2063 "parser\\epparser.c"
        break;
      case 122: /* assign_stmt ::= lvalue IADD expr */
#line 598 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__iadd__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2068 "parser\\epparser.c"
        break;
      case 123: /* assign_stmt ::= lvalue ISUB expr */
#line 599 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__isub__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2073 "parser\\epparser.c"
        break;
      case 124: /* assign_stmt ::= lvalue IMUL expr */
#line 600 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__imul__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2078 "parser\\epparser.c"
        break;
      case 125: /* assign_stmt ::= lvalue IDIV expr */
#line 601 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ifloordiv__("  << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2083 "parser\\epparser.c"
        break;
      case 126: /* assign_stmt ::= lvalue IMOD expr */
#line 602 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__imod__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2088 "parser\\epparser.c"
        break;
      case 127: /* assign_stmt ::= lvalue ILSH expr */
#line 603 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ilshift__("    << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2093 "parser\\epparser.c"
        break;
      case 128: /* assign_stmt ::= lvalue IRSH expr */
#line 604 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__irshift__("    << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2098 "parser\\epparser.c"
        break;
      case 129: /* assign_stmt ::= lvalue IBND expr */
#line 605 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__iand__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2103 "parser\\epparser.c"
        break;
      case 130: /* assign_stmt ::= lvalue IBOR expr */
#line 606 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ior__("        << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2108 "parser\\epparser.c"
        break;
      case 131: /* assign_stmt ::= lvalue IBXR expr */
#line 607 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ixor__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2113 "parser\\epparser.c"
        break;
      case 132: /* if_start ::= IF */
#line 610 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDIf()" << std::endl;
}
#line 2121 "parser\\epparser.c"
        break;
      case 133: /* if_header ::= if_start LPAREN lexpr RPAREN */
      case 136: /* elif_header ::= elif_start LPAREN lexpr RPAREN */ yytestcase(yyruleno==136);
      case 142: /* while_header ::= while_start LPAREN lexpr RPAREN */ yytestcase(yyruleno==142);
#line 615 "parser\\epparser.lemon"
{
    writeNegatableCondition(yymsp[-3].minor.yy0, yymsp[-1].minor.yy0);
    ps->gen.indent();
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 2132 "parser\\epparser.c"
        break;
      case 135: /* elif_start ::= ELSE IF */
#line 623 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen.unindent(false);
    ps->gen << yygotominor.yy0->data << " = EUDElseIf()" << std::endl;
}
#line 2141 "parser\\epparser.c"
        break;
      case 138: /* else_header ::= ELSE */
#line 637 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "if EUDElse()():" << std::endl;
    ps->gen.indent();
}
#line 2150 "parser\\epparser.c"
        break;
      case 139: /* if_stmt ::= if_block */
      case 140: /* if_stmt ::= if_block else_header stmt */ yytestcase(yyruleno==140);
#line 643 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndIf()" << std::endl;
}
#line 2159 "parser\\epparser.c"
        break;
      case 141: /* while_start ::= WHILE */
#line 655 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDWhile()" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2168 "parser\\epparser.c"
        break;
      case 143: /* while_stmt ::= while_header stmt */
#line 667 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndWhile()" << std::endl;
}
#line 2176 "parser\\epparser.c"
        break;
      case 144: /* for_opener ::= FOR LPAREN */
      case 160: /* foreach_opener ::= FOREACH LPAREN */ yytestcase(yyruleno==160);
#line 673 "parser\\epparser.lemon"
{
    ps->closure.pushScope();
}
#line 2184 "parser\\epparser.c"
        break;
      case 156: /* for_header1 ::= for_opener for_init_stmt SEMICOLON */
#line 691 "parser\\epparser.lemon"
{
    // opening for lexpr
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDWhile()" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2194 "parser\\epparser.c"
        break;
      case 157: /* for_header2 ::= for_header1 lexpr SEMICOLON */
#line 698 "parser\\epparser.lemon"
{
    writeNegatableCondition(yymsp[-2].minor.yy0, yymsp[-1].minor.yy0);
    ps->gen.indent();
    delete yymsp[-2].minor.yy0; delete yymsp[-1].minor.yy0;

    // Opening for assign_statement
    yygotominor.yy0 = genTemp(yymsp[-1].minor.yy0);
    ps->gen << "def " << yygotominor.yy0->data <<"():" << std::endl;
    ps->gen.indent();
}
#line 2208 "parser\\epparser.c"
        break;
      case 158: /* for_header ::= for_header2 for_action_stmt RPAREN */
#line 709 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-2].minor.yy0;
    ps->gen.unindent(false);
}
#line 2216 "parser\\epparser.c"
        break;
      case 159: /* for_stmt ::= for_header stmt */
#line 714 "parser\\epparser.lemon"
{
    ps->gen << "EUDSetContinuePoint()" << std::endl;
    ps->gen << yymsp[-1].minor.yy0->data << "()" << std::endl;
    ps->gen.unindent(false);
    ps->gen << "EUDEndWhile()" << std::endl;
    ps->closure.popScope();
}
#line 2227 "parser\\epparser.c"
        break;
      case 161: /* foreach_header ::= foreach_opener nameList_nonEmpty COLON exprList_nonEmpty RPAREN */
#line 729 "parser\\epparser.lemon"
{
    commaListIter(yymsp[-3].minor.yy0->data, [&](std::string& s) {
        ps->closure.defVariable(s);
    });
    ps->gen << "for " << yymsp[-3].minor.yy0->data << " in " << yymsp[-1].minor.yy0->data << ":" << std::endl;
    ps->gen.indent();
}
#line 2238 "parser\\epparser.c"
        break;
      case 162: /* foreach_stmt ::= foreach_header stmt */
#line 737 "parser\\epparser.lemon"
{
    ps->gen.unindent(true);
    ps->closure.popScope();
}
#line 2246 "parser\\epparser.c"
        break;
      case 163: /* continue_stmt ::= CONTINUE */
#line 745 "parser\\epparser.lemon"
{
    ps->gen << "EUDContinue()" << std::endl;
}
#line 2253 "parser\\epparser.c"
        break;
      case 164: /* break_stmt ::= BREAK */
#line 749 "parser\\epparser.lemon"
{
    ps->gen << "EUDBreak()" << std::endl;
}
#line 2260 "parser\\epparser.c"
        break;
      case 165: /* return_stmt ::= RETURN exprList */
#line 756 "parser\\epparser.lemon"
{
    if(MAP_DEBUG){
        ps->gen << "MDBG_POPF()" << std::endl;
    }
    ps->gen << "EUDReturn(" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2271 "parser\\epparser.c"
        break;
      case 166: /* lexpr ::= CONDITIONNAME LPAREN fArgs RPAREN */
      case 167: /* lexpr ::= KILLS LPAREN fArgs RPAREN */ yytestcase(yyruleno==167);
#line 767 "parser\\epparser.lemon"
{
    yymsp[-3].minor.yy0->data = yymsp[-3].minor.yy0->data + "(" + yymsp[-1].minor.yy0->data + ")";
    delete yymsp[-1].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 2281 "parser\\epparser.c"
        break;
      case 168: /* lexpr ::= CONDITIONNAME LPAREN RPAREN */
#line 779 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + "()";
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 2289 "parser\\epparser.c"
        break;
      case 169: /* action ::= ACTIONNAME LPAREN fArgs RPAREN SEMICOLON */
#line 784 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[-4].minor.yy0);
    yygotominor.yy0->data =  yymsp[-4].minor.yy0->data + "(" + yymsp[-2].minor.yy0->data + ")";
    delete yymsp[-4].minor.yy0; delete yymsp[-2].minor.yy0;
}
#line 2298 "parser\\epparser.c"
        break;
      case 170: /* actions ::= action action */
      case 171: /* actions ::= actions action */ yytestcase(yyruleno==171);
#line 790 "parser\\epparser.lemon"
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
#line 2321 "parser\\epparser.c"
        break;
      case 172: /* actionStmt_start ::= */
#line 828 "parser\\epparser.lemon"
{
    functionCalledInMultipleActions = false;
}
#line 2328 "parser\\epparser.c"
        break;
      case 173: /* actionStmt ::= actionStmt_start action */
#line 832 "parser\\epparser.lemon"
{
    ps->gen << "DoActions(" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2336 "parser\\epparser.c"
        break;
      case 174: /* actionStmt ::= actionStmt_start actions */
#line 837 "parser\\epparser.lemon"
{
    ps->gen << "DoActions([" << std::endl;
    ps->gen.indent();
    ps->gen << yymsp[0].minor.yy0->data << std::endl;
    ps->gen.unindent(false);
    ps->gen << "])" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2348 "parser\\epparser.c"
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
      /* (20) stmt ::= bodyStmt */ yytestcase(yyruleno==20);
      /* (21) stmt ::= return_stmt SEMICOLON */ yytestcase(yyruleno==21);
      /* (25) blockStmt ::= lbracket return_stmt SEMICOLON rbracket */ yytestcase(yyruleno==25);
      /* (26) blockStmt ::= lbracket bodyStmtList rbracket */ yytestcase(yyruleno==26);
      /* (27) blockStmt ::= lbracket bodyStmtList return_stmt SEMICOLON rbracket */ yytestcase(yyruleno==27);
      /* (29) bodyStmt ::= blockStmt */ yytestcase(yyruleno==29);
      /* (30) bodyStmt ::= SEMICOLON */ yytestcase(yyruleno==30);
      /* (31) bodyStmt ::= vdef_stmt SEMICOLON */ yytestcase(yyruleno==31);
      /* (32) bodyStmt ::= vdefAssign_stmt SEMICOLON */ yytestcase(yyruleno==32);
      /* (33) bodyStmt ::= cdef_stmt SEMICOLON */ yytestcase(yyruleno==33);
      /* (34) bodyStmt ::= assign_stmt SEMICOLON */ yytestcase(yyruleno==34);
      /* (36) bodyStmt ::= actionStmt */ yytestcase(yyruleno==36);
      /* (37) bodyStmt ::= if_stmt */ yytestcase(yyruleno==37);
      /* (38) bodyStmt ::= while_stmt */ yytestcase(yyruleno==38);
      /* (39) bodyStmt ::= for_stmt */ yytestcase(yyruleno==39);
      /* (40) bodyStmt ::= foreach_stmt */ yytestcase(yyruleno==40);
      /* (41) bodyStmt ::= continue_stmt SEMICOLON */ yytestcase(yyruleno==41);
      /* (42) bodyStmt ::= break_stmt SEMICOLON */ yytestcase(yyruleno==42);
      /* (44) bodyStmtList ::= bodyStmt */ yytestcase(yyruleno==44);
      /* (45) bodyStmtList ::= bodyStmtList bodyStmt */ yytestcase(yyruleno==45);
      /* (74) commaSkippable ::= COMMA */ yytestcase(yyruleno==74);
      /* (75) commaSkippable ::= */ yytestcase(yyruleno==75);
      /* (134) if_block ::= if_header stmt */ yytestcase(yyruleno==134);
      /* (137) if_block ::= if_block elif_header stmt */ yytestcase(yyruleno==137);
      /* (145) for_init_stmt_nonEmpty ::= vdef_stmt */ yytestcase(yyruleno==145);
      /* (146) for_init_stmt_nonEmpty ::= vdefAssign_stmt */ yytestcase(yyruleno==146);
      /* (147) for_init_stmt_nonEmpty ::= cdef_stmt */ yytestcase(yyruleno==147);
      /* (148) for_init_stmt_nonEmpty ::= assign_stmt */ yytestcase(yyruleno==148);
      /* (149) for_init_stmt_nonEmpty ::= for_init_stmt_nonEmpty COMMA for_init_stmt_nonEmpty */ yytestcase(yyruleno==149);
      /* (150) for_init_stmt ::= for_init_stmt_nonEmpty */ yytestcase(yyruleno==150);
      /* (151) for_init_stmt ::= */ yytestcase(yyruleno==151);
      /* (152) for_action_stmt_nonEmpty ::= assign_stmt */ yytestcase(yyruleno==152);
      /* (153) for_action_stmt_nonEmpty ::= for_action_stmt_nonEmpty COMMA for_action_stmt_nonEmpty */ yytestcase(yyruleno==153);
      /* (154) for_action_stmt ::= */ yytestcase(yyruleno==154);
      /* (155) for_action_stmt ::= for_action_stmt_nonEmpty */ yytestcase(yyruleno==155);
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
#line 31 "parser\\epparser.lemon"

    throw_error(-1, "Unrecoverable error");
#line 2444 "parser\\epparser.c"
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
#line 851 "parser\\epparser.lemon"


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
#line 2740 "parser\\epparser.c"
