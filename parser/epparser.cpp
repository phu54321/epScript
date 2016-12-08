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
#define YYNOCODE 134
#define YYACTIONTYPE unsigned short int
#define ParseTOKENTYPE Token*
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  int yy267;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL  ParserStruct* ps ;
#define ParseARG_PDECL , ParserStruct* ps 
#define ParseARG_FETCH  ParserStruct* ps  = yypParser->ps 
#define ParseARG_STORE yypParser->ps  = ps 
#define YYNSTATE 327
#define YYNRULE 170
#define YYERRORSYMBOL 71
#define YYERRSYMDT yy267
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
#define YY_ACTTAB_COUNT (1230)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   213,  197,  241,  199,  296,   18,   27,   28,  209,   74,
 /*    10 */   207,  302,  325,  205,   90,  312,  310,  212,    2,  121,
 /*    20 */   143,  208,  206,  148,  294,  293,  292,  291,  290,  201,
 /*    30 */   200,  322,  157,  156,   90,  196,  270,  193,  317,  121,
 /*    40 */   143,  164,    8,   39,  321,  278,  114,  161,    6,   10,
 /*    50 */   316,  221,  213,  220,   22,   13,    5,   81,    4,   75,
 /*    60 */   209,   76,  207,  302,  162,    7,    3,  256,  310,  212,
 /*    70 */     2,   38,  192,  208,  206,  148,  294,  293,  292,  291,
 /*    80 */   290,  201,  200,  320,   27,   28,   90,  199,   27,   28,
 /*    90 */    19,  121,  143,  164,    8,   39,   27,   28,   96,  161,
 /*   100 */     6,   10,  236,  259,  218,  196,   22,   13,    5,   81,
 /*   110 */     4,  213,  199,   76,  265,  191,  114,  171,  257,  209,
 /*   120 */   242,  207,  302,  115,  216,  276,  253,  310,  212,    2,
 /*   130 */    77,  199,  208,  206,  148,  294,  293,  292,  291,  290,
 /*   140 */   201,  200,   89,   37,  214,   90,  132,   36,  214,  214,
 /*   150 */   121,  143,  164,    8,   39,   34,   35,  217,  161,    6,
 /*   160 */    10,   32,  214,  213,  313,   22,   13,    5,   81,    4,
 /*   170 */   315,  209,   76,  207,  302,  215,   80,   79,  250,  310,
 /*   180 */   212,    2,  311,  199,  208,  206,  148,  294,  293,  292,
 /*   190 */   291,  290,  201,  200,  116,   27,   28,   90,  196,   27,
 /*   200 */    28,  309,  121,  143,  164,    8,   39,   86,  165,  114,
 /*   210 */   161,    6,   10,  498,   11,   85,  196,   22,   13,    5,
 /*   220 */    81,    4,  213,  214,   76,  254,  191,  114,  232,  251,
 /*   230 */   209,  196,  207,  302,  300,  299,  298,  238,  310,  212,
 /*   240 */     2,  167,  114,  208,  206,  148,  294,  293,  292,  291,
 /*   250 */   290,  201,  200,  297,  204,  199,   90,  199,  203,  202,
 /*   260 */   295,  121,  143,  164,    8,   39,   93,   19,  127,  161,
 /*   270 */     6,   10,  289,  288,  213,  205,   22,   13,    5,   81,
 /*   280 */     4,  283,  209,   76,  207,  302,   33,  195,   84,  235,
 /*   290 */   310,  212,    2,  280,  199,  208,  206,  148,  294,  293,
 /*   300 */   292,  291,  290,  201,  200,   88,  279,  199,   90,  133,
 /*   310 */    38,   30,   17,  121,  143,  164,    8,   39,  126,   31,
 /*   320 */   186,  161,    6,   10,  185,  199,  199,  275,   22,   13,
 /*   330 */     5,   81,    4,  213,  199,   76,  115,  139,  188,  169,
 /*   340 */   182,  209,  196,  207,  302,  138,  274,  183,  228,  310,
 /*   350 */   212,    2,  166,  114,  208,  206,  148,  294,  293,  292,
 /*   360 */   291,  290,  201,  200,  180,  177,  199,   90,  179,  273,
 /*   370 */   176,  272,  121,  143,  164,    8,   39,  137,  271,   28,
 /*   380 */   161,    6,   10,  267,   15,  151,  199,   22,   13,    5,
 /*   390 */    81,    4,  264,  209,   76,  207,  302,  115,  263,  188,
 /*   400 */   170,  226,  211,    2,  262,    1,  208,  206,  148,  294,
 /*   410 */   293,  292,  291,  290,  201,  200,  119,   25,  199,   90,
 /*   420 */   196,  255,   12,   24,  121,  143,  164,    8,   39,  125,
 /*   430 */   141,  114,  161,    6,   10,   23,  199,  199,  249,   22,
 /*   440 */    13,    5,   81,    4,  286,  199,   76,  115,  124,  188,
 /*   450 */   175,  243,  209,  199,  207,  302,  115,   14,  188,  153,
 /*   460 */   287,  210,    2,  304,  123,  208,  206,  148,  294,  293,
 /*   470 */   292,  291,  290,  201,  200,  239,  237,  199,   90,   16,
 /*   480 */   231,  152,  149,  121,  143,  164,    8,   39,  120,  227,
 /*   490 */   305,  161,    6,   10,  318,  306,  146,  303,   22,   13,
 /*   500 */     5,   81,    4,   62,   61,   76,   70,   71,   69,   60,
 /*   510 */   285,  117,  301,  199,  197,  194,  145,   63,   18,  308,
 /*   520 */   307,   21,   74,  284,  122,  314,  190,  187,  184,  181,
 /*   530 */   178,   83,   82,   41,   40,  199,   62,   61,  144,  142,
 /*   540 */   230,  154,   60,  285,  117,  258,   92,  252,  160,  155,
 /*   550 */    63,  234,  233,   20,   21,  229,  284,  163,  196,  190,
 /*   560 */   187,  184,  181,  178,   62,   61,   41,   40,  150,  114,
 /*   570 */    60,  285,  117,  301,  499,  140,  499,  499,   63,  499,
 /*   580 */   308,  306,   21,  499,  284,  499,  499,  190,  187,  184,
 /*   590 */   181,  178,   83,   82,   41,   40,   65,   64,   66,   68,
 /*   600 */    67,   73,   72,   70,   71,   69,  258,  199,  252,  160,
 /*   610 */   155,  197,  234,  233,   20,   18,  199,  199,   89,   74,
 /*   620 */   282,  499,  269,  499,  199,   62,   61,  115,  136,  188,
 /*   630 */   172,   60,  285,  117,  301,  135,  499,  499,  499,   63,
 /*   640 */   499,  308,  499,   21,  499,  284,  199,  499,  190,  187,
 /*   650 */   184,  181,  178,   83,   82,   41,   40,  134,   73,   72,
 /*   660 */    70,   71,   69,  499,  499,  499,  499,  258,  197,  252,
 /*   670 */   160,  155,   18,  234,  233,   20,   74,   59,   57,   56,
 /*   680 */    55,   54,   58,   65,   64,   66,   68,   67,   73,   72,
 /*   690 */    70,   71,   69,  199,  199,  499,  199,  499,  197,  499,
 /*   700 */   499,  499,   18,  281,   89,   89,   74,  113,  174,  268,
 /*   710 */    59,   57,   56,   55,   54,   58,   65,   64,   66,   68,
 /*   720 */    67,   73,   72,   70,   71,   69,  499,  499,  241,  199,
 /*   730 */   199,  197,  499,  499,  499,   18,   62,   61,  199,   74,
 /*   740 */    90,  112,   60,  285,  117,  121,  143,  499,  499,   89,
 /*   750 */    63,  499,  499,  131,   21,  499,  284,  499,  240,  190,
 /*   760 */   187,  184,  181,  178,   83,   82,   41,   40,   65,   64,
 /*   770 */    66,   68,   67,   73,   72,   70,   71,   69,  199,   26,
 /*   780 */   499,  499,  499,  168,  199,  199,  199,   18,  499,  111,
 /*   790 */   499,   53,   62,   61,  499,  110,  109,   89,   60,  285,
 /*   800 */   198,  130,  199,  261,  260,  499,   29,  499,  499,  499,
 /*   810 */    21,  499,  189,  108,  499,  190,  187,  184,  181,  178,
 /*   820 */   326,  225,  324,  323,  224,  223,  222,  319,  499,    9,
 /*   830 */   199,   62,   61,  199,    2,  499,  199,   60,  285,  147,
 /*   840 */   499,   91,  499,  173,   89,   63,  266,  107,  129,   21,
 /*   850 */   499,  284,  277,  499,  190,  187,  184,  181,  178,   65,
 /*   860 */    64,   66,   68,   67,   73,   72,   70,   71,   69,  199,
 /*   870 */   199,  499,  199,  499,  197,  499,  499,  499,   18,  281,
 /*   880 */    89,  106,   74,  105,  128,  499,  499,  199,   65,   64,
 /*   890 */    66,   68,   67,   73,   72,   70,   71,   69,  104,  433,
 /*   900 */   433,  499,  499,  197,  499,  499,  499,   18,   62,   61,
 /*   910 */   199,   74,  118,  327,   60,  285,  147,  499,  499,  499,
 /*   920 */   499,  103,   63,  499,  499,  199,   21,  199,  284,  277,
 /*   930 */    19,  190,  187,  184,  181,  178,  102,  499,  101,  499,
 /*   940 */   499,  499,   87,  499,  219,  499,  499,  308,  433,  433,
 /*   950 */   433,  433,  433,  433,  433,  433,  433,  433,  499,   78,
 /*   960 */    82,  199,   65,   64,   66,   68,   67,   73,   72,   70,
 /*   970 */    71,   69,  100,  199,  499,  199,  199,  197,  199,  199,
 /*   980 */   499,   18,  499,  499,   99,   74,   98,   97,  499,   95,
 /*   990 */    94,   65,   64,   66,   68,   67,   73,   72,   70,   71,
 /*  1000 */    69,  499,  499,  499,  499,  499,  168,  499,  499,  499,
 /*  1010 */    18,   62,   61,  499,   53,  499,  499,   60,  285,  198,
 /*  1020 */   499,  499,  499,  499,  499,   63,  499,  499,  499,   21,
 /*  1030 */   499,  284,  499,  499,  190,  187,  184,  181,  178,  499,
 /*  1040 */   499,  499,  499,  499,   62,   61,  499,  435,  435,  499,
 /*  1050 */    60,  285,  117,  499,  499,  499,  499,  499,   63,  499,
 /*  1060 */   499,  499,   21,  499,  284,  499,  499,  190,  187,  184,
 /*  1070 */   181,  178,  499,   64,   66,   68,   67,   73,   72,   70,
 /*  1080 */    71,   69,  434,  434,  499,  499,  499,  197,  499,  499,
 /*  1090 */   499,   18,  499,  499,  499,   74,  435,  435,  435,  435,
 /*  1100 */   435,  435,  435,  435,  435,  435,   52,   66,   68,   67,
 /*  1110 */    73,   72,   70,   71,   69,  499,  499,  499,  499,  499,
 /*  1120 */   197,  499,  499,  499,   18,  499,  499,  499,   74,  499,
 /*  1130 */   499,  434,  434,  434,  434,  434,  434,  434,  434,  434,
 /*  1140 */   434,  499,  499,  499,  499,  499,  499,  499,  499,  499,
 /*  1150 */   499,  499,  499,  499,  499,   51,   50,   49,   48,   47,
 /*  1160 */    46,   45,   44,   43,   42,  499,  499,  248,  499,  246,
 /*  1170 */   499,  499,   68,   67,   73,   72,   70,   71,   69,  499,
 /*  1180 */   247,  245,  199,  499,  197,  499,  499,  248,   18,  246,
 /*  1190 */   499,  499,   74,   90,  499,  499,  499,  499,  121,  143,
 /*  1200 */   247,  245,  199,  499,  499,  499,  499,  499,  499,  159,
 /*  1210 */   158,  499,  499,   90,  499,  499,  499,  499,  121,  143,
 /*  1220 */   499,  499,  499,  499,  499,  499,  499,  499,  499,  244,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    71,   28,   93,   94,   27,   32,    3,    4,   79,   36,
 /*    10 */    81,   82,   27,   36,  105,   86,   87,   88,   89,  110,
 /*    20 */   111,   92,   93,   94,   95,   96,   97,   98,   99,  100,
 /*    30 */   101,   27,  123,  124,  105,   94,   33,    2,   26,  110,
 /*    40 */   111,  112,  113,  114,   27,  104,  105,  118,  119,  120,
 /*    50 */    26,   28,   71,   30,  125,  126,  127,  128,  129,    1,
 /*    60 */    79,  132,   81,   82,  115,  116,  117,   86,   87,   88,
 /*    70 */    89,    2,   37,   92,   93,   94,   95,   96,   97,   98,
 /*    80 */    99,  100,  101,   27,    3,    4,  105,   94,    3,    4,
 /*    90 */    32,  110,  111,  112,  113,  114,    3,    4,  105,  118,
 /*   100 */   119,  120,   33,  110,   26,   94,  125,  126,  127,  128,
 /*   110 */   129,   71,   94,  132,   33,  104,  105,  106,   33,   79,
 /*   120 */    27,   81,   82,  105,   33,  107,   86,   87,   88,   89,
 /*   130 */    32,   94,   92,   93,   94,   95,   96,   97,   98,   99,
 /*   140 */   100,  101,  105,    1,    2,  105,  109,    1,    2,    2,
 /*   150 */   110,  111,  112,  113,  114,    1,    2,   85,  118,  119,
 /*   160 */   120,    1,    2,   71,   26,  125,  126,  127,  128,  129,
 /*   170 */    27,   79,  132,   81,   82,  103,  130,  131,   86,   87,
 /*   180 */    88,   89,   27,   94,   92,   93,   94,   95,   96,   97,
 /*   190 */    98,   99,  100,  101,  105,    3,    4,  105,   94,    3,
 /*   200 */     4,   27,  110,  111,  112,  113,  114,   27,  104,  105,
 /*   210 */   118,  119,  120,   73,   74,   27,   94,  125,  126,  127,
 /*   220 */   128,  129,   71,    2,  132,   33,  104,  105,  106,   33,
 /*   230 */    79,   94,   81,   82,   27,   27,   27,   86,   87,   88,
 /*   240 */    89,  104,  105,   92,   93,   94,   95,   96,   97,   98,
 /*   250 */    99,  100,  101,   27,   36,   94,  105,   94,   25,   37,
 /*   260 */    37,  110,  111,  112,  113,  114,  105,   32,  105,  118,
 /*   270 */   119,  120,   27,   27,   71,   36,  125,  126,  127,  128,
 /*   280 */   129,   26,   79,  132,   81,   82,   65,   36,   36,   86,
 /*   290 */    87,   88,   89,   25,   94,   92,   93,   94,   95,   96,
 /*   300 */    97,   98,   99,  100,  101,  105,   37,   94,  105,  109,
 /*   310 */     2,   32,   32,  110,  111,  112,  113,  114,  105,    2,
 /*   320 */    32,  118,  119,  120,   39,   94,   94,   33,  125,  126,
 /*   330 */   127,  128,  129,   71,   94,  132,  105,  105,  107,  108,
 /*   340 */    39,   79,   94,   81,   82,  105,   33,   32,   86,   87,
 /*   350 */    88,   89,  104,  105,   92,   93,   94,   95,   96,   97,
 /*   360 */    98,   99,  100,  101,   32,   32,   94,  105,   39,   33,
 /*   370 */    39,   33,  110,  111,  112,  113,  114,  105,   33,    4,
 /*   380 */   118,  119,  120,   33,   32,   71,   94,  125,  126,  127,
 /*   390 */   128,  129,   37,   79,  132,   81,   82,  105,   33,  107,
 /*   400 */   108,   87,   88,   89,   33,   91,   92,   93,   94,   95,
 /*   410 */    96,   97,   98,   99,  100,  101,   26,   32,   94,  105,
 /*   420 */    94,   60,    2,   32,  110,  111,  112,  113,  114,  105,
 /*   430 */   104,  105,  118,  119,  120,   32,   94,   94,   32,  125,
 /*   440 */   126,  127,  128,  129,   71,   94,  132,  105,  105,  107,
 /*   450 */   108,   27,   79,   94,   81,   82,  105,    2,  107,  108,
 /*   460 */    87,   88,   89,   90,  105,   92,   93,   94,   95,   96,
 /*   470 */    97,   98,   99,  100,  101,   33,   32,   94,  105,   32,
 /*   480 */    27,   33,   83,  110,  111,  112,  113,  114,  105,   35,
 /*   490 */    90,  118,  119,  120,   26,   35,  102,   90,  125,  126,
 /*   500 */   127,  128,  129,   18,   19,  132,   20,   21,   22,   24,
 /*   510 */    25,   26,   27,   94,   28,   25,  103,   32,   32,   34,
 /*   520 */    35,   36,   36,   38,  105,   26,   41,   42,   43,   44,
 /*   530 */    45,   46,   47,   48,   49,   94,   18,   19,  103,  103,
 /*   540 */   130,   70,   24,   25,   26,   60,  105,   62,   63,   64,
 /*   550 */    32,   66,   67,   68,   36,  130,   38,   61,   94,   41,
 /*   560 */    42,   43,   44,   45,   18,   19,   48,   49,  104,  105,
 /*   570 */    24,   25,   26,   27,  133,  103,  133,  133,   32,  133,
 /*   580 */    34,   35,   36,  133,   38,  133,  133,   41,   42,   43,
 /*   590 */    44,   45,   46,   47,   48,   49,   13,   14,   15,   16,
 /*   600 */    17,   18,   19,   20,   21,   22,   60,   94,   62,   63,
 /*   610 */    64,   28,   66,   67,   68,   32,   94,   94,  105,   36,
 /*   620 */    37,  133,  109,  133,   94,   18,   19,  105,  105,  107,
 /*   630 */   108,   24,   25,   26,   27,  105,  133,  133,  133,   32,
 /*   640 */   133,   34,  133,   36,  133,   38,   94,  133,   41,   42,
 /*   650 */    43,   44,   45,   46,   47,   48,   49,  105,   18,   19,
 /*   660 */    20,   21,   22,  133,  133,  133,  133,   60,   28,   62,
 /*   670 */    63,   64,   32,   66,   67,   68,   36,    7,    8,    9,
 /*   680 */    10,   11,   12,   13,   14,   15,   16,   17,   18,   19,
 /*   690 */    20,   21,   22,   94,   94,  133,   94,  133,   28,  133,
 /*   700 */   133,  133,   32,   33,  105,  105,   36,  105,  109,  109,
 /*   710 */     7,    8,    9,   10,   11,   12,   13,   14,   15,   16,
 /*   720 */    17,   18,   19,   20,   21,   22,  133,  133,   93,   94,
 /*   730 */    94,   28,  133,  133,  133,   32,   18,   19,   94,   36,
 /*   740 */   105,  105,   24,   25,   26,  110,  111,  133,  133,  105,
 /*   750 */    32,  133,  133,  109,   36,  133,   38,  133,  123,   41,
 /*   760 */    42,   43,   44,   45,   46,   47,   48,   49,   13,   14,
 /*   770 */    15,   16,   17,   18,   19,   20,   21,   22,   94,    5,
 /*   780 */   133,  133,  133,   28,   94,   94,   94,   32,  133,  105,
 /*   790 */   133,   36,   18,   19,  133,  105,  105,  105,   24,   25,
 /*   800 */    26,  109,   94,   48,   49,  133,   32,  133,  133,  133,
 /*   810 */    36,  133,   38,  105,  133,   41,   42,   43,   44,   45,
 /*   820 */    75,   76,   77,   78,   79,   80,   81,   82,  133,   84,
 /*   830 */    94,   18,   19,   94,   89,  133,   94,   24,   25,   26,
 /*   840 */   133,  105,  133,   69,  105,   32,   33,  105,  109,   36,
 /*   850 */   133,   38,   39,  133,   41,   42,   43,   44,   45,   13,
 /*   860 */    14,   15,   16,   17,   18,   19,   20,   21,   22,   94,
 /*   870 */    94,  133,   94,  133,   28,  133,  133,  133,   32,   33,
 /*   880 */   105,  105,   36,  105,  109,  133,  133,   94,   13,   14,
 /*   890 */    15,   16,   17,   18,   19,   20,   21,   22,  105,    1,
 /*   900 */     2,  133,  133,   28,  133,  133,  133,   32,   18,   19,
 /*   910 */    94,   36,   37,    0,   24,   25,   26,  133,  133,  133,
 /*   920 */   133,  105,   32,  133,  133,   94,   36,   94,   38,   39,
 /*   930 */    32,   41,   42,   43,   44,   45,  105,  133,  105,  133,
 /*   940 */   133,  133,   29,  133,   31,  133,  133,   34,   50,   51,
 /*   950 */    52,   53,   54,   55,   56,   57,   58,   59,  133,   46,
 /*   960 */    47,   94,   13,   14,   15,   16,   17,   18,   19,   20,
 /*   970 */    21,   22,  105,   94,  133,   94,   94,   28,   94,   94,
 /*   980 */   133,   32,  133,  133,  105,   36,  105,  105,  133,  105,
 /*   990 */   105,   13,   14,   15,   16,   17,   18,   19,   20,   21,
 /*  1000 */    22,  133,  133,  133,  133,  133,   28,  133,  133,  133,
 /*  1010 */    32,   18,   19,  133,   36,  133,  133,   24,   25,   26,
 /*  1020 */   133,  133,  133,  133,  133,   32,  133,  133,  133,   36,
 /*  1030 */   133,   38,  133,  133,   41,   42,   43,   44,   45,  133,
 /*  1040 */   133,  133,  133,  133,   18,   19,  133,    1,    2,  133,
 /*  1050 */    24,   25,   26,  133,  133,  133,  133,  133,   32,  133,
 /*  1060 */   133,  133,   36,  133,   38,  133,  133,   41,   42,   43,
 /*  1070 */    44,   45,  133,   14,   15,   16,   17,   18,   19,   20,
 /*  1080 */    21,   22,    1,    2,  133,  133,  133,   28,  133,  133,
 /*  1090 */   133,   32,  133,  133,  133,   36,   50,   51,   52,   53,
 /*  1100 */    54,   55,   56,   57,   58,   59,    1,   15,   16,   17,
 /*  1110 */    18,   19,   20,   21,   22,  133,  133,  133,  133,  133,
 /*  1120 */    28,  133,  133,  133,   32,  133,  133,  133,   36,  133,
 /*  1130 */   133,   50,   51,   52,   53,   54,   55,   56,   57,   58,
 /*  1140 */    59,  133,  133,  133,  133,  133,  133,  133,  133,  133,
 /*  1150 */   133,  133,  133,  133,  133,   50,   51,   52,   53,   54,
 /*  1160 */    55,   56,   57,   58,   59,  133,  133,   79,  133,   81,
 /*  1170 */   133,  133,   16,   17,   18,   19,   20,   21,   22,  133,
 /*  1180 */    92,   93,   94,  133,   28,  133,  133,   79,   32,   81,
 /*  1190 */   133,  133,   36,  105,  133,  133,  133,  133,  110,  111,
 /*  1200 */    92,   93,   94,  133,  133,  133,  133,  133,  133,  121,
 /*  1210 */   122,  133,  133,  105,  133,  133,  133,  133,  110,  111,
 /*  1220 */   133,  133,  133,  133,  133,  133,  133,  133,  133,  121,
};
#define YY_SHIFT_USE_DFLT (-28)
#define YY_SHIFT_COUNT (225)
#define YY_SHIFT_MIN   (-27)
#define YY_SHIFT_MAX   (1156)
static const short yy_shift_ofst[] = {
 /*     0 */   -28,  546,  485,  607,  607,  607,  607,  607,  607,  607,
 /*    10 */   718,  913,  718,  518,  518,  813,  890,  890,  890,  890,
 /*    20 */   993,  993,  774,  774,  774,  774,  774,  774,  774,  774,
 /*    30 */   774,  890,  993,  993,  993, 1026,  993,  993,  993,  496,
 /*    40 */   993,  993,  993,  993,  993,  993,  993,  993,  993,  993,
 /*    50 */   993,  993,  993,  993,  993,  993,  993,  993,  993,  993,
 /*    60 */   993,  993,  993,  993,  993,  993,  993,  993,  993,  993,
 /*    70 */   993,  993,  993,  993,  993,  993,  471,  499,  499,  471,
 /*    80 */   471,  499,  499,  499,  490,  460,  460,  468,  670,  703,
 /*    90 */   755,  875,  846,  583,  949,  949,  978,  949,  949,  949,
 /*   100 */   949,  949,  949,  949,  949,  949,  949,  949,  949,  949,
 /*   110 */   949,  949,  949,  949,  949,  949,  949,  898, 1081, 1046,
 /*   120 */  1059, 1105, 1092, 1156,  640,  640,  486,  486,   93,  196,
 /*   130 */   192,   85,   81,    3,  -27,  -27,  -27,  -27,  -27,  -27,
 /*   140 */   160,   69,  221,  154,  146,  142,   35,   58,  -23,   23,
 /*   150 */   308,  454,  453,  448,  447,  444,  442,  455,  424,  420,
 /*   160 */   406,  403,  391,  361,  385,  308,  308,  308,  390,  371,
 /*   170 */   365,  355,  350,  352,  375,  345,  338,  331,  333,  336,
 /*   180 */   329,  332,  313,  301,  315,  294,  285,  288,  317,  280,
 /*   190 */   279,  308,  269,  268,  222,  252,  251,  255,  235,  239,
 /*   200 */   246,  245,  223,  222,  233,  218,  226,  209,  208,  207,
 /*   210 */   188,  180,  174,  155,  138,  147,  143,   91,   98,   78,
 /*   220 */    24,   12,   56,   17,    4,  -15,
};
#define YY_REDUCE_USE_DFLT (-92)
#define YY_REDUCE_COUNT (87)
#define YY_REDUCE_MIN   (-91)
#define YY_REDUCE_MAX   (1108)
static const short yy_reduce_ofst[] = {
 /*     0 */   140,  373,  314,  262,  203,  151,   92,   40,  -19,  -71,
 /*    10 */  1088,  745, 1108,  -91,  635,  522,  351,  342,  292,  231,
 /*    20 */   122,   11,  775,  739,  692,  644,  600,  599,  513,  200,
 /*    30 */    37,   18,  464,  326,  104,   -7,  248,  137,  -59,  -51,
 /*    40 */   885,  884,  882,  881,  879,  867,  833,  831,  816,  793,
 /*    50 */   778,  776,  742,  736,  708,  691,  690,  684,  636,  602,
 /*    60 */   552,  530,  523,  441,  419,  383,  359,  343,  324,  272,
 /*    70 */   240,  232,  213,  163,  161,   89,   46,   72,  472,  425,
 /*    80 */   410,  436,  435,  413,  394,  407,  400,  399,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   328,  494,  494,  494,  494,  494,  494,  494,  494,  494,
 /*    10 */   473,  497,  497,  476,  497,  497,  393,  393,  393,  393,
 /*    20 */   382,  382,  497,  497,  497,  497,  497,  497,  497,  497,
 /*    30 */   497,  497,  497,  497,  497,  497,  497,  497,  497,  461,
 /*    40 */   497,  497,  497,  497,  497,  497,  497,  497,  497,  497,
 /*    50 */   497,  497,  497,  497,  497,  497,  497,  497,  497,  497,
 /*    60 */   497,  497,  497,  497,  497,  497,  497,  497,  497,  497,
 /*    70 */   497,  497,  497,  497,  497,  497,  497,  376,  497,  496,
 /*    80 */   495,  497,  497,  497,  497,  497,  497,  497,  418,  418,
 /*    90 */   497,  497,  497,  497,  442,  440,  497,  453,  452,  451,
 /*   100 */   450,  449,  448,  447,  446,  445,  444,  438,  425,  424,
 /*   110 */   423,  422,  421,  420,  380,  389,  391,  386,  388,  387,
 /*   120 */   413,  436,  414,  412,  411,  410,  406,  405,  497,  497,
 /*   130 */   497,  497,  497,  497,  417,  416,  415,  409,  408,  407,
 /*   140 */   429,  497,  497,  497,  497,  429,  497,  386,  397,  340,
 /*   150 */   431,  368,  497,  497,  497,  497,  497,  477,  497,  472,
 /*   160 */   497,  497,  497,  460,  497,  439,  432,  430,  497,  497,
 /*   170 */   497,  497,  497,  497,  427,  497,  497,  497,  497,  497,
 /*   180 */   497,  497,  497,  497,  497,  497,  497,  497,  394,  385,
 /*   190 */   497,  383,  497,  497,  372,  497,  397,  497,  386,  397,
 /*   200 */   497,  497,  497,  497,  497,  497,  497,  497,  497,  497,
 /*   210 */   497,  497,  497,  497,  497,  377,  341,  497,  497,  497,
 /*   220 */   497,  497,  497,  497,  497,  497,  369,  353,  462,  493,
 /*   230 */   492,  491,  487,  486,  485,  484,  483,  482,  481,  480,
 /*   240 */   475,  474,  479,  478,  471,  470,  469,  468,  467,  466,
 /*   250 */   465,  464,  463,  459,  458,  457,  456,  455,  454,  437,
 /*   260 */   443,  441,  395,  396,  399,  400,  490,  488,  428,  426,
 /*   270 */   419,  489,  404,  403,  402,  401,  392,  390,  381,  378,
 /*   280 */   373,  398,  388,  387,  385,  384,  371,  370,  367,  366,
 /*   290 */   365,  364,  363,  362,  361,  379,  360,  359,  358,  357,
 /*   300 */   356,  355,  354,  352,  351,  350,  348,  349,  347,  346,
 /*   310 */   345,  344,  342,  375,  374,  343,  339,  338,  337,  336,
 /*   320 */   335,  334,  333,  332,  331,  330,  329,
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
  "LPAREN",        "RPAREN",        "LBRACKET",      "RBRACKET",    
  "LSQBRACKET",    "RSQBRACKET",    "KILLS",         "STRING",      
  "FUNCCALL",      "L2V",           "MAPSTRING",     "UNIT",        
  "SWITCH",        "LOCATION",      "VAR",           "CONST",       
  "INC",           "DEC",           "IADD",          "ISUB",        
  "IMUL",          "IDIV",          "IMOD",          "ILSH",        
  "IRSH",          "IBND",          "IBOR",          "IBXR",        
  "IF",            "ELSE",          "WHILE",         "FOR",         
  "FOREACH",       "COLON",         "CONTINUE",      "BREAK",       
  "RETURN",        "CONDITIONNAME",  "ACTIONNAME",    "error",       
  "nt",            "program",       "chunks",        "chunk",       
  "import_chunk",  "fdef_chunk",    "fdecl_chunk",   "vdef_stmt",   
  "vdefAssign_global_stmt",  "cdef_stmt",     "blockStmt",     "dottedName",  
  "fdef_header",   "nameList",      "stmt",          "bodyStmt",    
  "return_stmt",   "lbracket",      "rbracket",      "bodyStmtList",
  "vdefAssign_stmt",  "assign_stmt",   "funcexpr",      "actionStmt",  
  "if_stmt",       "while_stmt",    "for_stmt",      "foreach_stmt",
  "continue_stmt",  "break_stmt",    "numList_nonEmpty",  "nameList_nonEmpty",
  "exprList_nonEmpty",  "expr",          "exprList",      "fArgs_nonEmpty",
  "fArgs",         "lexpr",         "lvalue",        "lvalueList_nonEmpty",
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
 /*   6 */ "chunk ::= vdef_stmt SEMICOLON",
 /*   7 */ "chunk ::= vdefAssign_global_stmt SEMICOLON",
 /*   8 */ "chunk ::= cdef_stmt SEMICOLON",
 /*   9 */ "chunk ::= blockStmt",
 /*  10 */ "dottedName ::= NAME",
 /*  11 */ "dottedName ::= dottedName PERIOD NAME",
 /*  12 */ "import_chunk ::= IMPORT dottedName AS NAME",
 /*  13 */ "import_chunk ::= IMPORT dottedName",
 /*  14 */ "fdef_header ::= FUNCTION NAME LPAREN nameList RPAREN",
 /*  15 */ "fdef_chunk ::= fdef_header stmt",
 /*  16 */ "fdecl_chunk ::= FUNCTION NAME LPAREN nameList RPAREN SEMICOLON",
 /*  17 */ "stmt ::= error SEMICOLON",
 /*  18 */ "stmt ::= bodyStmt",
 /*  19 */ "stmt ::= return_stmt SEMICOLON",
 /*  20 */ "lbracket ::= LBRACKET",
 /*  21 */ "rbracket ::= RBRACKET",
 /*  22 */ "blockStmt ::= lbracket RBRACKET",
 /*  23 */ "blockStmt ::= lbracket return_stmt SEMICOLON rbracket",
 /*  24 */ "blockStmt ::= lbracket bodyStmtList rbracket",
 /*  25 */ "blockStmt ::= lbracket bodyStmtList return_stmt SEMICOLON rbracket",
 /*  26 */ "blockStmt ::= lbracket error RBRACKET",
 /*  27 */ "bodyStmt ::= blockStmt",
 /*  28 */ "bodyStmt ::= SEMICOLON",
 /*  29 */ "bodyStmt ::= vdef_stmt SEMICOLON",
 /*  30 */ "bodyStmt ::= vdefAssign_stmt SEMICOLON",
 /*  31 */ "bodyStmt ::= cdef_stmt SEMICOLON",
 /*  32 */ "bodyStmt ::= assign_stmt SEMICOLON",
 /*  33 */ "bodyStmt ::= funcexpr SEMICOLON",
 /*  34 */ "bodyStmt ::= actionStmt",
 /*  35 */ "bodyStmt ::= if_stmt",
 /*  36 */ "bodyStmt ::= while_stmt",
 /*  37 */ "bodyStmt ::= for_stmt",
 /*  38 */ "bodyStmt ::= foreach_stmt",
 /*  39 */ "bodyStmt ::= continue_stmt SEMICOLON",
 /*  40 */ "bodyStmt ::= break_stmt SEMICOLON",
 /*  41 */ "bodyStmtList ::= error",
 /*  42 */ "bodyStmtList ::= bodyStmt",
 /*  43 */ "bodyStmtList ::= bodyStmtList bodyStmt",
 /*  44 */ "bodyStmtList ::= bodyStmtList error",
 /*  45 */ "numList_nonEmpty ::= NUMBER",
 /*  46 */ "numList_nonEmpty ::= numList_nonEmpty COMMA NUMBER",
 /*  47 */ "nameList_nonEmpty ::= NAME",
 /*  48 */ "nameList_nonEmpty ::= nameList_nonEmpty COMMA NAME",
 /*  49 */ "nameList ::=",
 /*  50 */ "nameList ::= nameList_nonEmpty",
 /*  51 */ "exprList_nonEmpty ::= funcexpr LSQBRACKET LSQBRACKET numList_nonEmpty RSQBRACKET RSQBRACKET",
 /*  52 */ "expr ::= funcexpr LSQBRACKET LSQBRACKET NUMBER RSQBRACKET RSQBRACKET",
 /*  53 */ "exprList_nonEmpty ::= expr",
 /*  54 */ "exprList_nonEmpty ::= exprList_nonEmpty COMMA exprList_nonEmpty",
 /*  55 */ "exprList ::=",
 /*  56 */ "exprList ::= exprList_nonEmpty",
 /*  57 */ "expr ::= NUMBER",
 /*  58 */ "expr ::= KILLS",
 /*  59 */ "expr ::= NAME",
 /*  60 */ "expr ::= expr PERIOD NAME",
 /*  61 */ "expr ::= expr LSQBRACKET expr RSQBRACKET",
 /*  62 */ "fArgs_nonEmpty ::= expr",
 /*  63 */ "fArgs_nonEmpty ::= STRING",
 /*  64 */ "fArgs_nonEmpty ::= NAME ASSIGN expr",
 /*  65 */ "fArgs_nonEmpty ::= fArgs_nonEmpty COMMA fArgs_nonEmpty",
 /*  66 */ "fArgs ::=",
 /*  67 */ "fArgs ::= fArgs_nonEmpty",
 /*  68 */ "funcexpr ::= NAME LPAREN fArgs RPAREN",
 /*  69 */ "funcexpr ::= expr LPAREN fArgs RPAREN",
 /*  70 */ "expr ::= funcexpr",
 /*  71 */ "expr ::= LPAREN expr RPAREN",
 /*  72 */ "expr ::= LSQBRACKET exprList RSQBRACKET",
 /*  73 */ "expr ::= L2V LPAREN lexpr RPAREN",
 /*  74 */ "expr ::= MAPSTRING LPAREN STRING RPAREN",
 /*  75 */ "expr ::= UNIT LPAREN STRING RPAREN",
 /*  76 */ "expr ::= SWITCH LPAREN STRING RPAREN",
 /*  77 */ "expr ::= LOCATION LPAREN STRING RPAREN",
 /*  78 */ "expr ::= expr PLUS expr",
 /*  79 */ "expr ::= expr MINUS expr",
 /*  80 */ "expr ::= expr MULTIPLY expr",
 /*  81 */ "expr ::= expr DIVIDE expr",
 /*  82 */ "expr ::= expr MOD expr",
 /*  83 */ "expr ::= expr LSHIFT expr",
 /*  84 */ "expr ::= expr RSHIFT expr",
 /*  85 */ "expr ::= expr BITAND expr",
 /*  86 */ "expr ::= expr BITOR expr",
 /*  87 */ "expr ::= expr BITXOR expr",
 /*  88 */ "expr ::= PLUS expr",
 /*  89 */ "expr ::= MINUS expr",
 /*  90 */ "expr ::= BITNOT expr",
 /*  91 */ "lexpr ::= expr",
 /*  92 */ "lexpr ::= LPAREN lexpr RPAREN",
 /*  93 */ "lexpr ::= expr EQ expr",
 /*  94 */ "lexpr ::= expr NE expr",
 /*  95 */ "lexpr ::= expr LE expr",
 /*  96 */ "lexpr ::= expr LT expr",
 /*  97 */ "lexpr ::= expr GE expr",
 /*  98 */ "lexpr ::= expr GT expr",
 /*  99 */ "lexpr ::= lexpr LAND lexpr",
 /* 100 */ "lexpr ::= lexpr LOR lexpr",
 /* 101 */ "lexpr ::= LNOT lexpr",
 /* 102 */ "vdef_stmt ::= VAR nameList_nonEmpty",
 /* 103 */ "vdefAssign_stmt ::= VAR nameList_nonEmpty ASSIGN exprList_nonEmpty",
 /* 104 */ "vdefAssign_global_stmt ::= VAR nameList_nonEmpty ASSIGN exprList_nonEmpty",
 /* 105 */ "cdef_stmt ::= CONST nameList_nonEmpty ASSIGN exprList_nonEmpty",
 /* 106 */ "lvalue ::= NAME",
 /* 107 */ "lvalue ::= expr LSQBRACKET expr RSQBRACKET",
 /* 108 */ "lvalue ::= expr PERIOD NAME",
 /* 109 */ "lvalueList_nonEmpty ::= lvalue",
 /* 110 */ "lvalueList_nonEmpty ::= lvalueList_nonEmpty COMMA lvalue",
 /* 111 */ "assign_stmt ::= lvalue ASSIGN expr",
 /* 112 */ "assign_stmt ::= lvalueList_nonEmpty ASSIGN exprList_nonEmpty",
 /* 113 */ "assign_stmt ::= INC expr",
 /* 114 */ "assign_stmt ::= expr INC",
 /* 115 */ "assign_stmt ::= DEC expr",
 /* 116 */ "assign_stmt ::= expr DEC",
 /* 117 */ "assign_stmt ::= lvalue IADD expr",
 /* 118 */ "assign_stmt ::= lvalue ISUB expr",
 /* 119 */ "assign_stmt ::= lvalue IMUL expr",
 /* 120 */ "assign_stmt ::= lvalue IDIV expr",
 /* 121 */ "assign_stmt ::= lvalue IMOD expr",
 /* 122 */ "assign_stmt ::= lvalue ILSH expr",
 /* 123 */ "assign_stmt ::= lvalue IRSH expr",
 /* 124 */ "assign_stmt ::= lvalue IBND expr",
 /* 125 */ "assign_stmt ::= lvalue IBOR expr",
 /* 126 */ "assign_stmt ::= lvalue IBXR expr",
 /* 127 */ "if_start ::= IF",
 /* 128 */ "if_header ::= if_start LPAREN lexpr RPAREN",
 /* 129 */ "if_block ::= if_header stmt",
 /* 130 */ "elif_start ::= ELSE IF",
 /* 131 */ "elif_header ::= elif_start LPAREN lexpr RPAREN",
 /* 132 */ "if_block ::= if_block elif_header stmt",
 /* 133 */ "else_header ::= ELSE",
 /* 134 */ "if_stmt ::= if_block",
 /* 135 */ "if_stmt ::= if_block else_header stmt",
 /* 136 */ "while_start ::= WHILE",
 /* 137 */ "while_header ::= while_start LPAREN lexpr RPAREN",
 /* 138 */ "while_stmt ::= while_header stmt",
 /* 139 */ "for_opener ::= FOR LPAREN",
 /* 140 */ "for_init_stmt_nonEmpty ::= vdef_stmt",
 /* 141 */ "for_init_stmt_nonEmpty ::= vdefAssign_stmt",
 /* 142 */ "for_init_stmt_nonEmpty ::= cdef_stmt",
 /* 143 */ "for_init_stmt_nonEmpty ::= assign_stmt",
 /* 144 */ "for_init_stmt_nonEmpty ::= for_init_stmt_nonEmpty COMMA for_init_stmt_nonEmpty",
 /* 145 */ "for_init_stmt ::= for_init_stmt_nonEmpty",
 /* 146 */ "for_init_stmt ::=",
 /* 147 */ "for_action_stmt_nonEmpty ::= assign_stmt",
 /* 148 */ "for_action_stmt_nonEmpty ::= for_action_stmt_nonEmpty COMMA for_action_stmt_nonEmpty",
 /* 149 */ "for_action_stmt ::=",
 /* 150 */ "for_action_stmt ::= for_action_stmt_nonEmpty",
 /* 151 */ "for_header1 ::= for_opener for_init_stmt SEMICOLON",
 /* 152 */ "for_header2 ::= for_header1 lexpr SEMICOLON",
 /* 153 */ "for_header ::= for_header2 for_action_stmt RPAREN",
 /* 154 */ "for_stmt ::= for_header stmt",
 /* 155 */ "foreach_opener ::= FOREACH LPAREN",
 /* 156 */ "foreach_header ::= foreach_opener nameList_nonEmpty COLON exprList_nonEmpty RPAREN",
 /* 157 */ "foreach_stmt ::= foreach_header stmt",
 /* 158 */ "continue_stmt ::= CONTINUE",
 /* 159 */ "break_stmt ::= BREAK",
 /* 160 */ "return_stmt ::= RETURN exprList",
 /* 161 */ "lexpr ::= CONDITIONNAME LPAREN fArgs RPAREN",
 /* 162 */ "lexpr ::= KILLS LPAREN fArgs RPAREN",
 /* 163 */ "lexpr ::= CONDITIONNAME LPAREN RPAREN",
 /* 164 */ "action ::= ACTIONNAME LPAREN fArgs RPAREN SEMICOLON",
 /* 165 */ "actions ::= action action",
 /* 166 */ "actions ::= actions action",
 /* 167 */ "actionStmt_start ::=",
 /* 168 */ "actionStmt ::= actionStmt_start action",
 /* 169 */ "actionStmt ::= actionStmt_start actions",
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
    case 72: /* nt */
{
#line 39 "parser\\epparser.lemon"
 delete (yypminor->yy0); 
#line 889 "parser\\epparser.c"
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
  { 73, 1 },
  { 74, 0 },
  { 74, 2 },
  { 75, 2 },
  { 75, 1 },
  { 75, 1 },
  { 75, 2 },
  { 75, 2 },
  { 75, 2 },
  { 75, 1 },
  { 83, 1 },
  { 83, 3 },
  { 76, 4 },
  { 76, 2 },
  { 84, 5 },
  { 77, 2 },
  { 78, 6 },
  { 86, 2 },
  { 86, 1 },
  { 86, 2 },
  { 89, 1 },
  { 90, 1 },
  { 82, 2 },
  { 82, 4 },
  { 82, 3 },
  { 82, 5 },
  { 82, 3 },
  { 87, 1 },
  { 87, 1 },
  { 87, 2 },
  { 87, 2 },
  { 87, 2 },
  { 87, 2 },
  { 87, 2 },
  { 87, 1 },
  { 87, 1 },
  { 87, 1 },
  { 87, 1 },
  { 87, 1 },
  { 87, 2 },
  { 87, 2 },
  { 91, 1 },
  { 91, 1 },
  { 91, 2 },
  { 91, 2 },
  { 102, 1 },
  { 102, 3 },
  { 103, 1 },
  { 103, 3 },
  { 85, 0 },
  { 85, 1 },
  { 104, 6 },
  { 105, 6 },
  { 104, 1 },
  { 104, 3 },
  { 106, 0 },
  { 106, 1 },
  { 105, 1 },
  { 105, 1 },
  { 105, 1 },
  { 105, 3 },
  { 105, 4 },
  { 107, 1 },
  { 107, 1 },
  { 107, 3 },
  { 107, 3 },
  { 108, 0 },
  { 108, 1 },
  { 94, 4 },
  { 94, 4 },
  { 105, 1 },
  { 105, 3 },
  { 105, 3 },
  { 105, 4 },
  { 105, 4 },
  { 105, 4 },
  { 105, 4 },
  { 105, 4 },
  { 105, 3 },
  { 105, 3 },
  { 105, 3 },
  { 105, 3 },
  { 105, 3 },
  { 105, 3 },
  { 105, 3 },
  { 105, 3 },
  { 105, 3 },
  { 105, 3 },
  { 105, 2 },
  { 105, 2 },
  { 105, 2 },
  { 109, 1 },
  { 109, 3 },
  { 109, 3 },
  { 109, 3 },
  { 109, 3 },
  { 109, 3 },
  { 109, 3 },
  { 109, 3 },
  { 109, 3 },
  { 109, 3 },
  { 109, 2 },
  { 79, 2 },
  { 92, 4 },
  { 80, 4 },
  { 81, 4 },
  { 110, 1 },
  { 110, 4 },
  { 110, 3 },
  { 111, 1 },
  { 111, 3 },
  { 93, 3 },
  { 93, 3 },
  { 93, 2 },
  { 93, 2 },
  { 93, 2 },
  { 93, 2 },
  { 93, 3 },
  { 93, 3 },
  { 93, 3 },
  { 93, 3 },
  { 93, 3 },
  { 93, 3 },
  { 93, 3 },
  { 93, 3 },
  { 93, 3 },
  { 93, 3 },
  { 112, 1 },
  { 113, 4 },
  { 114, 2 },
  { 115, 2 },
  { 116, 4 },
  { 114, 3 },
  { 117, 1 },
  { 96, 1 },
  { 96, 3 },
  { 118, 1 },
  { 119, 4 },
  { 97, 2 },
  { 120, 2 },
  { 121, 1 },
  { 121, 1 },
  { 121, 1 },
  { 121, 1 },
  { 121, 3 },
  { 122, 1 },
  { 122, 0 },
  { 123, 1 },
  { 123, 3 },
  { 124, 0 },
  { 124, 1 },
  { 125, 3 },
  { 126, 3 },
  { 127, 3 },
  { 98, 2 },
  { 128, 2 },
  { 129, 5 },
  { 99, 2 },
  { 100, 1 },
  { 101, 1 },
  { 88, 2 },
  { 109, 4 },
  { 109, 4 },
  { 109, 3 },
  { 130, 5 },
  { 131, 2 },
  { 131, 2 },
  { 132, 0 },
  { 95, 2 },
  { 95, 2 },
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
      case 9: /* chunk ::= blockStmt */
#line 74 "parser\\epparser.lemon"
{
    throw_error(48993, "Misplaced block statement");
}
#line 1356 "parser\\epparser.c"
        break;
      case 10: /* dottedName ::= NAME */
      case 45: /* numList_nonEmpty ::= NUMBER */ yytestcase(yyruleno==45);
      case 47: /* nameList_nonEmpty ::= NAME */ yytestcase(yyruleno==47);
      case 50: /* nameList ::= nameList_nonEmpty */ yytestcase(yyruleno==50);
      case 53: /* exprList_nonEmpty ::= expr */ yytestcase(yyruleno==53);
      case 56: /* exprList ::= exprList_nonEmpty */ yytestcase(yyruleno==56);
      case 57: /* expr ::= NUMBER */ yytestcase(yyruleno==57);
      case 62: /* fArgs_nonEmpty ::= expr */ yytestcase(yyruleno==62);
      case 63: /* fArgs_nonEmpty ::= STRING */ yytestcase(yyruleno==63);
      case 67: /* fArgs ::= fArgs_nonEmpty */ yytestcase(yyruleno==67);
      case 70: /* expr ::= funcexpr */ yytestcase(yyruleno==70);
      case 91: /* lexpr ::= expr */ yytestcase(yyruleno==91);
      case 109: /* lvalueList_nonEmpty ::= lvalue */ yytestcase(yyruleno==109);
#line 80 "parser\\epparser.lemon"
{ yygotominor.yy0 = yymsp[0].minor.yy0; }
#line 1373 "parser\\epparser.c"
        break;
      case 11: /* dottedName ::= dottedName PERIOD NAME */
#line 81 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = yymsp[-2].minor.yy0->data + "." + yymsp[0].minor.yy0->data;
    delete yymsp[-2].minor.yy0;
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1382 "parser\\epparser.c"
        break;
      case 12: /* import_chunk ::= IMPORT dottedName AS NAME */
#line 87 "parser\\epparser.lemon"
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
#line 1398 "parser\\epparser.c"
        break;
      case 13: /* import_chunk ::= IMPORT dottedName */
#line 100 "parser\\epparser.lemon"
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
#line 1414 "parser\\epparser.c"
        break;
      case 14: /* fdef_header ::= FUNCTION NAME LPAREN nameList RPAREN */
#line 114 "parser\\epparser.lemon"
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
#line 1447 "parser\\epparser.c"
        break;
      case 15: /* fdef_chunk ::= fdef_header stmt */
#line 144 "parser\\epparser.lemon"
{
    if(MAP_DEBUG){
        ps->gen << "MDBG_POPF()" << std::endl;
    }
    ps->gen.unindent(true);
    ps->closure.popScope();
    currentFunction = "";
}
#line 1459 "parser\\epparser.c"
        break;
      case 16: /* fdecl_chunk ::= FUNCTION NAME LPAREN nameList RPAREN SEMICOLON */
#line 153 "parser\\epparser.lemon"
{
    // Preprocess yymsp[-4].minor.yy0
    funcNamePreprocess(yymsp[-4].minor.yy0->data);
    if(!ps->closure.declareFunction(yymsp[-4].minor.yy0->data)) {
        throw_error(72461, "Declaring function with non-function yymsp[-4].minor.yy0 " + yymsp[-4].minor.yy0->data, yymsp[-4].minor.yy0->line);
    }
}
#line 1470 "parser\\epparser.c"
        break;
      case 17: /* stmt ::= error SEMICOLON */
#line 162 "parser\\epparser.lemon"
{ throw_error(6974, "Error while parsing statement", yymsp[0].minor.yy0->line); delete yymsp[0].minor.yy0; }
#line 1475 "parser\\epparser.c"
        break;
      case 20: /* lbracket ::= LBRACKET */
#line 168 "parser\\epparser.lemon"
{ ps->closure.pushScope(); }
#line 1480 "parser\\epparser.c"
        break;
      case 21: /* rbracket ::= RBRACKET */
#line 169 "parser\\epparser.lemon"
{ ps->closure.popScope(); }
#line 1485 "parser\\epparser.c"
        break;
      case 22: /* blockStmt ::= lbracket RBRACKET */
#line 171 "parser\\epparser.lemon"
{
    ps->closure.popScope();
}
#line 1492 "parser\\epparser.c"
        break;
      case 26: /* blockStmt ::= lbracket error RBRACKET */
#line 177 "parser\\epparser.lemon"
{
    throw_error(6298, "Block not terminated properly.", yymsp[0].minor.yy0->line);
    ps->closure.popScope();
    delete yymsp[0].minor.yy0;
}
#line 1501 "parser\\epparser.c"
        break;
      case 33: /* bodyStmt ::= funcexpr SEMICOLON */
#line 189 "parser\\epparser.lemon"
{ ps->gen << yymsp[-1].minor.yy0->data << std::endl; }
#line 1506 "parser\\epparser.c"
        break;
      case 41: /* bodyStmtList ::= error */
      case 44: /* bodyStmtList ::= bodyStmtList error */ yytestcase(yyruleno==44);
#line 199 "parser\\epparser.lemon"
{
    throw_error(8510, "Incomplete statement");
}
#line 1514 "parser\\epparser.c"
        break;
      case 46: /* numList_nonEmpty ::= numList_nonEmpty COMMA NUMBER */
      case 48: /* nameList_nonEmpty ::= nameList_nonEmpty COMMA NAME */ yytestcase(yyruleno==48);
      case 110: /* lvalueList_nonEmpty ::= lvalueList_nonEmpty COMMA lvalue */ yytestcase(yyruleno==110);
#line 212 "parser\\epparser.lemon"
{ yygotominor.yy0 = commaConcat(yymsp[-2].minor.yy0, yymsp[0].minor.yy0); }
#line 1521 "parser\\epparser.c"
        break;
      case 49: /* nameList ::= */
      case 55: /* exprList ::= */ yytestcase(yyruleno==55);
      case 66: /* fArgs ::= */ yytestcase(yyruleno==66);
#line 215 "parser\\epparser.lemon"
{ yygotominor.yy0 = genEmpty(); }
#line 1528 "parser\\epparser.c"
        break;
      case 51: /* exprList_nonEmpty ::= funcexpr LSQBRACKET LSQBRACKET numList_nonEmpty RSQBRACKET RSQBRACKET */
#line 218 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = "_SRET(" + yymsp[-5].minor.yy0->data + ", [" + yymsp[-2].minor.yy0->data + "])";
    delete yymsp[-5].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1537 "parser\\epparser.c"
        break;
      case 52: /* expr ::= funcexpr LSQBRACKET LSQBRACKET NUMBER RSQBRACKET RSQBRACKET */
#line 225 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-5].minor.yy0->data + "[" + yymsp[-2].minor.yy0->data + "]";
    delete yymsp[-5].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1546 "parser\\epparser.c"
        break;
      case 54: /* exprList_nonEmpty ::= exprList_nonEmpty COMMA exprList_nonEmpty */
#line 233 "parser\\epparser.lemon"
{ yygotominor.yy0 = new Token((yymsp[-2].minor.yy0->data) + ", " + (yymsp[0].minor.yy0->data), yymsp[0].minor.yy0); delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1551 "parser\\epparser.c"
        break;
      case 58: /* expr ::= KILLS */
#line 240 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = "4";
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1559 "parser\\epparser.c"
        break;
      case 59: /* expr ::= NAME */
#line 245 "parser\\epparser.lemon"
{
    checkIsRValue(yymsp[0].minor.yy0->data, yymsp[0].minor.yy0->line);
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1567 "parser\\epparser.c"
        break;
      case 60: /* expr ::= expr PERIOD NAME */
#line 250 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + "." + yymsp[0].minor.yy0->data;
    delete yymsp[0].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 1576 "parser\\epparser.c"
        break;
      case 61: /* expr ::= expr LSQBRACKET expr RSQBRACKET */
#line 256 "parser\\epparser.lemon"
{
    yymsp[-3].minor.yy0->data = yymsp[-3].minor.yy0->data + "[" + yymsp[-1].minor.yy0->data + "]";
    delete yymsp[-1].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 1585 "parser\\epparser.c"
        break;
      case 64: /* fArgs_nonEmpty ::= NAME ASSIGN expr */
#line 265 "parser\\epparser.lemon"
{  // Keyword argument
    yymsp[0].minor.yy0->data = yymsp[-2].minor.yy0->data + "=" + yymsp[0].minor.yy0->data;
    yymsp[0].minor.yy0->type = TOKEN_TEMP;
    yygotominor.yy0 = yymsp[0].minor.yy0;
    delete yymsp[-2].minor.yy0;
}
#line 1595 "parser\\epparser.c"
        break;
      case 65: /* fArgs_nonEmpty ::= fArgs_nonEmpty COMMA fArgs_nonEmpty */
#line 272 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data;
    yymsp[0].minor.yy0->type = TOKEN_TEMP;
    yygotominor.yy0 = yymsp[0].minor.yy0;
    delete yymsp[-2].minor.yy0;
}
#line 1605 "parser\\epparser.c"
        break;
      case 68: /* funcexpr ::= NAME LPAREN fArgs RPAREN */
#line 282 "parser\\epparser.lemon"
{
    functionCalledInMultipleActions = true;

    // Preprocess yymsp[-3].minor.yy0
    funcNamePreprocess(yymsp[-3].minor.yy0->data);
    checkIsFunction(yymsp[-3].minor.yy0->data, yymsp[-3].minor.yy0->line);
    yymsp[-3].minor.yy0->data += "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 1618 "parser\\epparser.c"
        break;
      case 69: /* funcexpr ::= expr LPAREN fArgs RPAREN */
#line 292 "parser\\epparser.lemon"
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
#line 1642 "parser\\epparser.c"
        break;
      case 71: /* expr ::= LPAREN expr RPAREN */
      case 92: /* lexpr ::= LPAREN lexpr RPAREN */ yytestcase(yyruleno==92);
#line 316 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1651 "parser\\epparser.c"
        break;
      case 72: /* expr ::= LSQBRACKET exprList RSQBRACKET */
#line 321 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "EUDArray(FlattenList([" + yymsp[-1].minor.yy0->data + "]))";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1659 "parser\\epparser.c"
        break;
      case 73: /* expr ::= L2V LPAREN lexpr RPAREN */
#line 326 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "_L2V(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1667 "parser\\epparser.c"
        break;
      case 74: /* expr ::= MAPSTRING LPAREN STRING RPAREN */
#line 331 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetStringIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1675 "parser\\epparser.c"
        break;
      case 75: /* expr ::= UNIT LPAREN STRING RPAREN */
#line 336 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "EncodeUnit(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1683 "parser\\epparser.c"
        break;
      case 76: /* expr ::= SWITCH LPAREN STRING RPAREN */
#line 341 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "EncodeSwitch(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1691 "parser\\epparser.c"
        break;
      case 77: /* expr ::= LOCATION LPAREN STRING RPAREN */
#line 346 "parser\\epparser.lemon"
{
    yymsp[-1].minor.yy0->data = "GetLocationIndex(" + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
}
#line 1699 "parser\\epparser.c"
        break;
      case 78: /* expr ::= expr PLUS expr */
#line 352 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "+",  yymsp[0].minor.yy0); }
#line 1704 "parser\\epparser.c"
        break;
      case 79: /* expr ::= expr MINUS expr */
#line 353 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "-",  yymsp[0].minor.yy0); }
#line 1709 "parser\\epparser.c"
        break;
      case 80: /* expr ::= expr MULTIPLY expr */
#line 354 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "*",  yymsp[0].minor.yy0); }
#line 1714 "parser\\epparser.c"
        break;
      case 81: /* expr ::= expr DIVIDE expr */
#line 355 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "//", yymsp[0].minor.yy0); }
#line 1719 "parser\\epparser.c"
        break;
      case 82: /* expr ::= expr MOD expr */
#line 356 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "%",  yymsp[0].minor.yy0); }
#line 1724 "parser\\epparser.c"
        break;
      case 83: /* expr ::= expr LSHIFT expr */
#line 357 "parser\\epparser.lemon"
{
    yymsp[0].minor.yy0->data = "_LSH(" + yymsp[-2].minor.yy0->data + "," + yymsp[0].minor.yy0->data + ")";
    delete yymsp[-2].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0);
}
#line 1733 "parser\\epparser.c"
        break;
      case 84: /* expr ::= expr RSHIFT expr */
#line 362 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, ">>", yymsp[0].minor.yy0); }
#line 1738 "parser\\epparser.c"
        break;
      case 85: /* expr ::= expr BITAND expr */
#line 363 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "&",  yymsp[0].minor.yy0); }
#line 1743 "parser\\epparser.c"
        break;
      case 86: /* expr ::= expr BITOR expr */
#line 364 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "|",  yymsp[0].minor.yy0); }
#line 1748 "parser\\epparser.c"
        break;
      case 87: /* expr ::= expr BITXOR expr */
#line 365 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "^",  yymsp[0].minor.yy0); }
#line 1753 "parser\\epparser.c"
        break;
      case 88: /* expr ::= PLUS expr */
#line 368 "parser\\epparser.lemon"
{ yymsp[0].minor.yy0->data = "+" + yymsp[0].minor.yy0->data; yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0); }
#line 1758 "parser\\epparser.c"
        break;
      case 89: /* expr ::= MINUS expr */
#line 369 "parser\\epparser.lemon"
{ yymsp[0].minor.yy0->data = "-" + yymsp[0].minor.yy0->data; yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0); }
#line 1763 "parser\\epparser.c"
        break;
      case 90: /* expr ::= BITNOT expr */
#line 370 "parser\\epparser.lemon"
{ yymsp[0].minor.yy0->data = "~" + yymsp[0].minor.yy0->data; yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0); }
#line 1768 "parser\\epparser.c"
        break;
      case 93: /* lexpr ::= expr EQ expr */
#line 380 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "==", yymsp[0].minor.yy0); }
#line 1773 "parser\\epparser.c"
        break;
      case 94: /* lexpr ::= expr NE expr */
#line 381 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "!=", yymsp[0].minor.yy0); }
#line 1778 "parser\\epparser.c"
        break;
      case 95: /* lexpr ::= expr LE expr */
#line 382 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "<=", yymsp[0].minor.yy0); }
#line 1783 "parser\\epparser.c"
        break;
      case 96: /* lexpr ::= expr LT expr */
#line 383 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, "<",  yymsp[0].minor.yy0); }
#line 1788 "parser\\epparser.c"
        break;
      case 97: /* lexpr ::= expr GE expr */
#line 384 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, ">=", yymsp[0].minor.yy0); }
#line 1793 "parser\\epparser.c"
        break;
      case 98: /* lexpr ::= expr GT expr */
#line 385 "parser\\epparser.lemon"
{ yygotominor.yy0 = binopConcat(yymsp[-2].minor.yy0, ">" , yymsp[0].minor.yy0); }
#line 1798 "parser\\epparser.c"
        break;
      case 99: /* lexpr ::= lexpr LAND lexpr */
#line 388 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genEmpty();
    yygotominor.yy0->line = yymsp[0].minor.yy0->line;

    // Generate data!
    yygotominor.yy0->type = TOKEN_AST_LEXPR_AND;
    yygotominor.yy0->subToken[0] = yymsp[-2].minor.yy0;
    yygotominor.yy0->subToken[1] = yymsp[0].minor.yy0;
    yygotominor.yy0->data = "[" + flatListGetter(yygotominor.yy0, TOKEN_AST_LEXPR_AND) + "]";
}
#line 1812 "parser\\epparser.c"
        break;
      case 100: /* lexpr ::= lexpr LOR lexpr */
#line 400 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genEmpty();
    yygotominor.yy0->line = yymsp[0].minor.yy0->line;

    // Generate data!
    yygotominor.yy0->type = TOKEN_AST_LEXPR_OR;
    yygotominor.yy0->subToken[0] = yymsp[-2].minor.yy0;
    yygotominor.yy0->subToken[1] = yymsp[0].minor.yy0;
    yygotominor.yy0->data = "EUDOr(" + flatListGetter(yygotominor.yy0, TOKEN_AST_LEXPR_OR) + ")";
}
#line 1826 "parser\\epparser.c"
        break;
      case 101: /* lexpr ::= LNOT lexpr */
#line 411 "parser\\epparser.lemon"
{
    if(yymsp[0].minor.yy0->type == TOKEN_AST_LEXPR_NOT) {
        yygotominor.yy0 = yymsp[0].minor.yy0->subToken[0];
        yymsp[0].minor.yy0->subToken[0] = nullptr;
        delete yymsp[0].minor.yy0;
    }
    else {
        yygotominor.yy0 = genEmpty();
        yygotominor.yy0->line = yymsp[0].minor.yy0->line;
        yygotominor.yy0->type = TOKEN_AST_LEXPR_NOT;
        yygotominor.yy0->data = "EUDNot([" + yymsp[0].minor.yy0->data + "])";
        yygotominor.yy0->subToken[0] = yymsp[0].minor.yy0;
    }
}
#line 1844 "parser\\epparser.c"
        break;
      case 102: /* vdef_stmt ::= VAR nameList_nonEmpty */
#line 428 "parser\\epparser.lemon"
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
#line 1868 "parser\\epparser.c"
        break;
      case 103: /* vdefAssign_stmt ::= VAR nameList_nonEmpty ASSIGN exprList_nonEmpty */
#line 449 "parser\\epparser.lemon"
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
#line 1893 "parser\\epparser.c"
        break;
      case 104: /* vdefAssign_global_stmt ::= VAR nameList_nonEmpty ASSIGN exprList_nonEmpty */
#line 471 "parser\\epparser.lemon"
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
        ps->gen << s << " = EUDVariable(" << yymsp[0].minor.yy0->data << ")" << std::endl;
    }
    else {
        ps->gen << s << " = [EUDVariable(v) for v in FlattenList([" << yymsp[0].minor.yy0->data << "])]" << std::endl;
    }

    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 1917 "parser\\epparser.c"
        break;
      case 105: /* cdef_stmt ::= CONST nameList_nonEmpty ASSIGN exprList_nonEmpty */
#line 492 "parser\\epparser.lemon"
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
#line 1939 "parser\\epparser.c"
        break;
      case 106: /* lvalue ::= NAME */
#line 512 "parser\\epparser.lemon"
{
    checkIsVariable(yymsp[0].minor.yy0->data, yymsp[0].minor.yy0->line);
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 1947 "parser\\epparser.c"
        break;
      case 107: /* lvalue ::= expr LSQBRACKET expr RSQBRACKET */
#line 517 "parser\\epparser.lemon"
{
    checkIsConstant(yymsp[-3].minor.yy0->data, yymsp[-3].minor.yy0->line);
    yymsp[-1].minor.yy0->data = "_ARRW(" + yymsp[-3].minor.yy0->data + ", " + yymsp[-1].minor.yy0->data + ")";
    yygotominor.yy0 = mkTokenTemp(yymsp[-1].minor.yy0);
    delete yymsp[-3].minor.yy0;
}
#line 1957 "parser\\epparser.c"
        break;
      case 108: /* lvalue ::= expr PERIOD NAME */
#line 524 "parser\\epparser.lemon"
{
    checkIsConstant(yymsp[-2].minor.yy0->data, yymsp[-2].minor.yy0->line);
    yymsp[0].minor.yy0->data = "_ATTW(" + yymsp[-2].minor.yy0->data + ", '" + yymsp[0].minor.yy0->data + "')";
    yygotominor.yy0 = mkTokenTemp(yymsp[0].minor.yy0);
    delete yymsp[-2].minor.yy0;
}
#line 1967 "parser\\epparser.c"
        break;
      case 111: /* assign_stmt ::= lvalue ASSIGN expr */
#line 533 "parser\\epparser.lemon"
{
    ps->gen << yymsp[-2].minor.yy0->data << " << (" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 1975 "parser\\epparser.c"
        break;
      case 112: /* assign_stmt ::= lvalueList_nonEmpty ASSIGN exprList_nonEmpty */
#line 538 "parser\\epparser.lemon"
{
    ps->gen << "_SV([" << yymsp[-2].minor.yy0->data << "], [" << yymsp[0].minor.yy0->data << "])" << std::endl;
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 1983 "parser\\epparser.c"
        break;
      case 113: /* assign_stmt ::= INC expr */
#line 546 "parser\\epparser.lemon"
{ ps->gen << yymsp[0].minor.yy0->data << ".__iadd__(1)" << std::endl; delete yymsp[0].minor.yy0; }
#line 1988 "parser\\epparser.c"
        break;
      case 114: /* assign_stmt ::= expr INC */
#line 547 "parser\\epparser.lemon"
{ ps->gen << yymsp[-1].minor.yy0->data << ".__iadd__(1)" << std::endl; delete yymsp[-1].minor.yy0; }
#line 1993 "parser\\epparser.c"
        break;
      case 115: /* assign_stmt ::= DEC expr */
#line 548 "parser\\epparser.lemon"
{ ps->gen << yymsp[0].minor.yy0->data << ".__isub__(1)" << std::endl; delete yymsp[0].minor.yy0; }
#line 1998 "parser\\epparser.c"
        break;
      case 116: /* assign_stmt ::= expr DEC */
#line 549 "parser\\epparser.lemon"
{ ps->gen << yymsp[-1].minor.yy0->data << ".__isub__(1)" << std::endl; delete yymsp[-1].minor.yy0; }
#line 2003 "parser\\epparser.c"
        break;
      case 117: /* assign_stmt ::= lvalue IADD expr */
#line 550 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__iadd__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2008 "parser\\epparser.c"
        break;
      case 118: /* assign_stmt ::= lvalue ISUB expr */
#line 551 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__isub__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2013 "parser\\epparser.c"
        break;
      case 119: /* assign_stmt ::= lvalue IMUL expr */
#line 552 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__imul__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2018 "parser\\epparser.c"
        break;
      case 120: /* assign_stmt ::= lvalue IDIV expr */
#line 553 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ifloordiv__("  << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2023 "parser\\epparser.c"
        break;
      case 121: /* assign_stmt ::= lvalue IMOD expr */
#line 554 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__imod__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2028 "parser\\epparser.c"
        break;
      case 122: /* assign_stmt ::= lvalue ILSH expr */
#line 555 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ilshift__("    << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2033 "parser\\epparser.c"
        break;
      case 123: /* assign_stmt ::= lvalue IRSH expr */
#line 556 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__irshift__("    << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2038 "parser\\epparser.c"
        break;
      case 124: /* assign_stmt ::= lvalue IBND expr */
#line 557 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__iand__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2043 "parser\\epparser.c"
        break;
      case 125: /* assign_stmt ::= lvalue IBOR expr */
#line 558 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ior__("        << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2048 "parser\\epparser.c"
        break;
      case 126: /* assign_stmt ::= lvalue IBXR expr */
#line 559 "parser\\epparser.lemon"
{ ps->gen << yymsp[-2].minor.yy0->data << ".__ixor__("       << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 2053 "parser\\epparser.c"
        break;
      case 127: /* if_start ::= IF */
#line 562 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDIf()" << std::endl;
}
#line 2061 "parser\\epparser.c"
        break;
      case 128: /* if_header ::= if_start LPAREN lexpr RPAREN */
      case 131: /* elif_header ::= elif_start LPAREN lexpr RPAREN */ yytestcase(yyruleno==131);
      case 137: /* while_header ::= while_start LPAREN lexpr RPAREN */ yytestcase(yyruleno==137);
#line 567 "parser\\epparser.lemon"
{
    writeNegatableCondition(yymsp[-3].minor.yy0, yymsp[-1].minor.yy0);
    ps->gen.indent();
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 2072 "parser\\epparser.c"
        break;
      case 130: /* elif_start ::= ELSE IF */
#line 575 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen.unindent(false);
    ps->gen << yygotominor.yy0->data << " = EUDElseIf()" << std::endl;
}
#line 2081 "parser\\epparser.c"
        break;
      case 133: /* else_header ::= ELSE */
#line 589 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "if EUDElse()():" << std::endl;
    ps->gen.indent();
}
#line 2090 "parser\\epparser.c"
        break;
      case 134: /* if_stmt ::= if_block */
      case 135: /* if_stmt ::= if_block else_header stmt */ yytestcase(yyruleno==135);
#line 595 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndIf()" << std::endl;
}
#line 2099 "parser\\epparser.c"
        break;
      case 136: /* while_start ::= WHILE */
#line 607 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDWhile()" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2108 "parser\\epparser.c"
        break;
      case 138: /* while_stmt ::= while_header stmt */
#line 619 "parser\\epparser.lemon"
{
    ps->gen.unindent(false);
    ps->gen << "EUDEndWhile()" << std::endl;
}
#line 2116 "parser\\epparser.c"
        break;
      case 139: /* for_opener ::= FOR LPAREN */
      case 155: /* foreach_opener ::= FOREACH LPAREN */ yytestcase(yyruleno==155);
#line 625 "parser\\epparser.lemon"
{
    ps->closure.pushScope();
}
#line 2124 "parser\\epparser.c"
        break;
      case 151: /* for_header1 ::= for_opener for_init_stmt SEMICOLON */
#line 643 "parser\\epparser.lemon"
{
    // opening for lexpr
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    ps->gen << yygotominor.yy0->data << " = EUDWhile()" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2134 "parser\\epparser.c"
        break;
      case 152: /* for_header2 ::= for_header1 lexpr SEMICOLON */
#line 650 "parser\\epparser.lemon"
{
    writeNegatableCondition(yymsp[-2].minor.yy0, yymsp[-1].minor.yy0);
    ps->gen.indent();
    delete yymsp[-2].minor.yy0; delete yymsp[-1].minor.yy0;

    // Opening for assign_statement
    yygotominor.yy0 = genTemp(yymsp[-1].minor.yy0);
    ps->gen << "def " << yygotominor.yy0->data <<"():" << std::endl;
    ps->gen.indent();
}
#line 2148 "parser\\epparser.c"
        break;
      case 153: /* for_header ::= for_header2 for_action_stmt RPAREN */
#line 661 "parser\\epparser.lemon"
{
    yygotominor.yy0 = yymsp[-2].minor.yy0;
    ps->gen.unindent(false);
}
#line 2156 "parser\\epparser.c"
        break;
      case 154: /* for_stmt ::= for_header stmt */
#line 666 "parser\\epparser.lemon"
{
    ps->gen << "EUDSetContinuePoint()" << std::endl;
    ps->gen << yymsp[-1].minor.yy0->data << "()" << std::endl;
    ps->gen.unindent(false);
    ps->gen << "EUDEndWhile()" << std::endl;
    ps->closure.popScope();
}
#line 2167 "parser\\epparser.c"
        break;
      case 156: /* foreach_header ::= foreach_opener nameList_nonEmpty COLON exprList_nonEmpty RPAREN */
#line 681 "parser\\epparser.lemon"
{
    commaListIter(yymsp[-3].minor.yy0->data, [&](std::string& s) {
        ps->closure.defVariable(s);
    });
    ps->gen << "for " << yymsp[-3].minor.yy0->data << " in " << yymsp[-1].minor.yy0->data << ":" << std::endl;
    ps->gen.indent();
}
#line 2178 "parser\\epparser.c"
        break;
      case 157: /* foreach_stmt ::= foreach_header stmt */
#line 689 "parser\\epparser.lemon"
{
    ps->gen.unindent(true);
    ps->closure.popScope();
}
#line 2186 "parser\\epparser.c"
        break;
      case 158: /* continue_stmt ::= CONTINUE */
#line 697 "parser\\epparser.lemon"
{
    ps->gen << "EUDContinue()" << std::endl;
}
#line 2193 "parser\\epparser.c"
        break;
      case 159: /* break_stmt ::= BREAK */
#line 701 "parser\\epparser.lemon"
{
    ps->gen << "EUDBreak()" << std::endl;
}
#line 2200 "parser\\epparser.c"
        break;
      case 160: /* return_stmt ::= RETURN exprList */
#line 708 "parser\\epparser.lemon"
{
    if(MAP_DEBUG){
        ps->gen << "MDBG_POPF()" << std::endl;
    }
    ps->gen << "EUDReturn(" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2211 "parser\\epparser.c"
        break;
      case 161: /* lexpr ::= CONDITIONNAME LPAREN fArgs RPAREN */
      case 162: /* lexpr ::= KILLS LPAREN fArgs RPAREN */ yytestcase(yyruleno==162);
#line 719 "parser\\epparser.lemon"
{
    yymsp[-3].minor.yy0->data = yymsp[-3].minor.yy0->data + "(" + yymsp[-1].minor.yy0->data + ")";
    delete yymsp[-1].minor.yy0;
    yygotominor.yy0 = mkTokenTemp(yymsp[-3].minor.yy0);
}
#line 2221 "parser\\epparser.c"
        break;
      case 163: /* lexpr ::= CONDITIONNAME LPAREN RPAREN */
#line 731 "parser\\epparser.lemon"
{
    yymsp[-2].minor.yy0->data = yymsp[-2].minor.yy0->data + "()";
    yygotominor.yy0 = mkTokenTemp(yymsp[-2].minor.yy0);
}
#line 2229 "parser\\epparser.c"
        break;
      case 164: /* action ::= ACTIONNAME LPAREN fArgs RPAREN SEMICOLON */
#line 736 "parser\\epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[-4].minor.yy0);
    yygotominor.yy0->data =  yymsp[-4].minor.yy0->data + "(" + yymsp[-2].minor.yy0->data + ")";
    delete yymsp[-4].minor.yy0; delete yymsp[-2].minor.yy0;
}
#line 2238 "parser\\epparser.c"
        break;
      case 165: /* actions ::= action action */
      case 166: /* actions ::= actions action */ yytestcase(yyruleno==166);
#line 742 "parser\\epparser.lemon"
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
#line 2261 "parser\\epparser.c"
        break;
      case 167: /* actionStmt_start ::= */
#line 780 "parser\\epparser.lemon"
{
    functionCalledInMultipleActions = false;
}
#line 2268 "parser\\epparser.c"
        break;
      case 168: /* actionStmt ::= actionStmt_start action */
#line 784 "parser\\epparser.lemon"
{
    ps->gen << "DoActions(" << yymsp[0].minor.yy0->data << ")" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2276 "parser\\epparser.c"
        break;
      case 169: /* actionStmt ::= actionStmt_start actions */
#line 789 "parser\\epparser.lemon"
{
    ps->gen << "DoActions([" << std::endl;
    ps->gen.indent();
    ps->gen << yymsp[0].minor.yy0->data << std::endl;
    ps->gen.unindent(false);
    ps->gen << "])" << std::endl;
    delete yymsp[0].minor.yy0;
}
#line 2288 "parser\\epparser.c"
        break;
      default:
      /* (0) program ::= chunks */ yytestcase(yyruleno==0);
      /* (1) chunks ::= */ yytestcase(yyruleno==1);
      /* (2) chunks ::= chunks chunk */ yytestcase(yyruleno==2);
      /* (3) chunk ::= import_chunk SEMICOLON */ yytestcase(yyruleno==3);
      /* (4) chunk ::= fdef_chunk */ yytestcase(yyruleno==4);
      /* (5) chunk ::= fdecl_chunk */ yytestcase(yyruleno==5);
      /* (6) chunk ::= vdef_stmt SEMICOLON */ yytestcase(yyruleno==6);
      /* (7) chunk ::= vdefAssign_global_stmt SEMICOLON */ yytestcase(yyruleno==7);
      /* (8) chunk ::= cdef_stmt SEMICOLON */ yytestcase(yyruleno==8);
      /* (18) stmt ::= bodyStmt */ yytestcase(yyruleno==18);
      /* (19) stmt ::= return_stmt SEMICOLON */ yytestcase(yyruleno==19);
      /* (23) blockStmt ::= lbracket return_stmt SEMICOLON rbracket */ yytestcase(yyruleno==23);
      /* (24) blockStmt ::= lbracket bodyStmtList rbracket */ yytestcase(yyruleno==24);
      /* (25) blockStmt ::= lbracket bodyStmtList return_stmt SEMICOLON rbracket */ yytestcase(yyruleno==25);
      /* (27) bodyStmt ::= blockStmt */ yytestcase(yyruleno==27);
      /* (28) bodyStmt ::= SEMICOLON */ yytestcase(yyruleno==28);
      /* (29) bodyStmt ::= vdef_stmt SEMICOLON */ yytestcase(yyruleno==29);
      /* (30) bodyStmt ::= vdefAssign_stmt SEMICOLON */ yytestcase(yyruleno==30);
      /* (31) bodyStmt ::= cdef_stmt SEMICOLON */ yytestcase(yyruleno==31);
      /* (32) bodyStmt ::= assign_stmt SEMICOLON */ yytestcase(yyruleno==32);
      /* (34) bodyStmt ::= actionStmt */ yytestcase(yyruleno==34);
      /* (35) bodyStmt ::= if_stmt */ yytestcase(yyruleno==35);
      /* (36) bodyStmt ::= while_stmt */ yytestcase(yyruleno==36);
      /* (37) bodyStmt ::= for_stmt */ yytestcase(yyruleno==37);
      /* (38) bodyStmt ::= foreach_stmt */ yytestcase(yyruleno==38);
      /* (39) bodyStmt ::= continue_stmt SEMICOLON */ yytestcase(yyruleno==39);
      /* (40) bodyStmt ::= break_stmt SEMICOLON */ yytestcase(yyruleno==40);
      /* (42) bodyStmtList ::= bodyStmt */ yytestcase(yyruleno==42);
      /* (43) bodyStmtList ::= bodyStmtList bodyStmt */ yytestcase(yyruleno==43);
      /* (129) if_block ::= if_header stmt */ yytestcase(yyruleno==129);
      /* (132) if_block ::= if_block elif_header stmt */ yytestcase(yyruleno==132);
      /* (140) for_init_stmt_nonEmpty ::= vdef_stmt */ yytestcase(yyruleno==140);
      /* (141) for_init_stmt_nonEmpty ::= vdefAssign_stmt */ yytestcase(yyruleno==141);
      /* (142) for_init_stmt_nonEmpty ::= cdef_stmt */ yytestcase(yyruleno==142);
      /* (143) for_init_stmt_nonEmpty ::= assign_stmt */ yytestcase(yyruleno==143);
      /* (144) for_init_stmt_nonEmpty ::= for_init_stmt_nonEmpty COMMA for_init_stmt_nonEmpty */ yytestcase(yyruleno==144);
      /* (145) for_init_stmt ::= for_init_stmt_nonEmpty */ yytestcase(yyruleno==145);
      /* (146) for_init_stmt ::= */ yytestcase(yyruleno==146);
      /* (147) for_action_stmt_nonEmpty ::= assign_stmt */ yytestcase(yyruleno==147);
      /* (148) for_action_stmt_nonEmpty ::= for_action_stmt_nonEmpty COMMA for_action_stmt_nonEmpty */ yytestcase(yyruleno==148);
      /* (149) for_action_stmt ::= */ yytestcase(yyruleno==149);
      /* (150) for_action_stmt ::= for_action_stmt_nonEmpty */ yytestcase(yyruleno==150);
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
#line 2381 "parser\\epparser.c"
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
#line 803 "parser\\epparser.lemon"


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
#line 2677 "parser\\epparser.c"
