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
#line 19 "parser/epparser.c"
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
#define YYNOCODE 80
#define YYACTIONTYPE unsigned char
#define ParseTOKENTYPE Token*
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  int yy159;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL  PyGenerator* pGen ;
#define ParseARG_PDECL , PyGenerator* pGen 
#define ParseARG_FETCH  PyGenerator* pGen  = yypParser->pGen 
#define ParseARG_STORE yypParser->pGen  = pGen 
#define YYNSTATE 155
#define YYNRULE 82
#define YYERRORSYMBOL 45
#define YYERRSYMDT yy159
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
static const YYACTIONTYPE yy_action[] = {
 /*     0 */    70,   88,   94,   55,   87,   74,  148,   98,   47,  238,
 /*    10 */     7,  101,  103,  106,  105,  107,  108,    2,  124,  118,
 /*    20 */    77,    4,  109,    3,   44,  155,  110,  112,  114,   93,
 /*    30 */    98,   45,  116,  136,   74,   15,   98,   47,   98,   49,
 /*    40 */   101,  103,  106,  105,  107,  108,   85,  147,  118,   77,
 /*    50 */     4,  109,    3,   44,  151,  110,  112,  114,   93,   71,
 /*    60 */    43,  116,   96,   74,  129,   98,   47,   40,   92,  101,
 /*    70 */   103,  106,  105,  107,  108,   73,  130,  118,   77,    4,
 /*    80 */   109,    3,   44,  100,  110,  112,  114,   93,   86,   32,
 /*    90 */   116,   82,   74,   31,   98,   47,   98,   48,  101,  103,
 /*   100 */   106,  105,  107,  108,   75,   91,  118,   77,    4,  109,
 /*   110 */     3,   44,   80,  110,  112,  114,   93,   78,   80,  116,
 /*   120 */     8,   74,   84,   98,   47,   98,   46,  101,  103,  106,
 /*   130 */   105,  107,  108,  149,  144,  118,   77,    4,  109,    3,
 /*   140 */    44,   68,  110,  112,  114,   93,   86,  135,  116,   96,
 /*   150 */    74,  152,   98,   47,   98,   52,  101,  103,  106,  105,
 /*   160 */   107,  108,  137,  126,  118,   77,    4,  109,    3,   44,
 /*   170 */    95,  110,  112,  114,   21,   18,   22,  116,  125,   34,
 /*   180 */    36,   37,   38,   39,   35,   26,   27,   25,   23,   24,
 /*   190 */    19,   20,   21,   18,   22,   10,   28,   29,   98,   45,
 /*   200 */   154,   62,   30,   97,   66,   25,   23,   24,   19,   20,
 /*   210 */    21,   18,   22,   41,   99,    1,  127,  128,  145,   83,
 /*   220 */    79,   67,    9,   28,   29,   88,   94,   55,  150,   30,
 /*   230 */    97,   66,   23,   24,   19,   20,   21,   18,   22,    8,
 /*   240 */    41,   99,    1,   11,  128,  145,   83,   79,  143,    9,
 /*   250 */    98,   45,  117,   81,   26,   27,   25,   23,   24,   19,
 /*   260 */    20,   21,   18,   22,   27,   25,   23,   24,   19,   20,
 /*   270 */    21,   18,   22,   28,   29,   98,   45,  119,  138,   30,
 /*   280 */    97,   89,   19,   20,   21,   18,   22,   69,  132,  142,
 /*   290 */   133,   26,   27,   25,   23,   24,   19,   20,   21,   18,
 /*   300 */    22,    6,   13,   98,  115,   14,   90,    5,  131,  239,
 /*   310 */   134,   42,   80,   16,  122,   28,   29,  239,   28,   29,
 /*   320 */   239,   30,   97,   89,   30,   97,   89,   31,   26,   27,
 /*   330 */    25,   23,   24,   19,   20,   21,   18,   22,   98,   45,
 /*   340 */   239,  139,  239,   98,   45,  239,   63,  135,   86,   86,
 /*   350 */    33,  121,   72,   94,   55,   98,  113,   76,   94,   55,
 /*   360 */    98,  111,  123,   80,   17,   26,   27,   25,   23,   24,
 /*   370 */    19,   20,   21,   18,   22,   12,   10,   12,   10,   98,
 /*   380 */    58,   98,   57,  141,  141,   98,   59,   98,   61,   98,
 /*   390 */   102,   98,  153,   31,   98,   65,   98,   60,  239,  239,
 /*   400 */   239,   98,   64,   98,  104,  239,  140,  239,  146,   98,
 /*   410 */    54,   98,   56,   98,   50,   98,   51,   98,   53,  239,
 /*   420 */   239,  239,  239,  239,  239,  239,  239,  239,  120,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    45,   51,   52,   53,   54,   50,   36,   52,   53,   47,
 /*    10 */    48,   56,   57,   58,   59,   60,   61,   62,   63,   64,
 /*    20 */    65,   66,   67,   68,   69,    0,   71,   72,   73,   45,
 /*    30 */    52,   53,   77,   55,   50,   33,   52,   53,   52,   53,
 /*    40 */    56,   57,   58,   59,   60,   61,   26,   63,   64,   65,
 /*    50 */    66,   67,   68,   69,   34,   71,   72,   73,   45,   50,
 /*    60 */    35,   77,   36,   50,   38,   52,   53,   33,   43,   56,
 /*    70 */    57,   58,   59,   60,   61,   26,   63,   64,   65,   66,
 /*    80 */    67,   68,   69,   25,   71,   72,   73,   45,    1,    2,
 /*    90 */    77,    1,   50,    1,   52,   53,   52,   53,   56,   57,
 /*   100 */    58,   59,   60,   61,   49,   63,   64,   65,   66,   67,
 /*   110 */    68,   69,    1,   71,   72,   73,   45,   31,    1,   77,
 /*   120 */    33,   50,   32,   52,   53,   52,   53,   56,   57,   58,
 /*   130 */    59,   60,   61,   36,   63,   64,   65,   66,   67,   68,
 /*   140 */    69,   50,   71,   72,   73,   45,    1,   36,   77,   36,
 /*   150 */    50,   34,   52,   53,   52,   53,   56,   57,   58,   59,
 /*   160 */    60,   61,   26,   63,   64,   65,   66,   67,   68,   69,
 /*   170 */    32,   71,   72,   73,   20,   21,   22,   77,   26,    7,
 /*   180 */     8,    9,   10,   11,   12,   13,   14,   15,   16,   17,
 /*   190 */    18,   19,   20,   21,   22,    4,   18,   19,   52,   53,
 /*   200 */    25,   55,   24,   25,   26,   15,   16,   17,   18,   19,
 /*   210 */    20,   21,   22,   35,   36,   37,   38,   39,   40,   41,
 /*   220 */    42,   26,   44,   18,   19,   51,   52,   53,   54,   24,
 /*   230 */    25,   26,   16,   17,   18,   19,   20,   21,   22,   33,
 /*   240 */    35,   36,   37,   33,   39,   40,   41,   42,   26,   44,
 /*   250 */    52,   53,   34,   55,   13,   14,   15,   16,   17,   18,
 /*   260 */    19,   20,   21,   22,   14,   15,   16,   17,   18,   19,
 /*   270 */    20,   21,   22,   18,   19,   52,   53,   36,   55,   24,
 /*   280 */    25,   26,   18,   19,   20,   21,   22,   50,   56,   30,
 /*   290 */    58,   13,   14,   15,   16,   17,   18,   19,   20,   21,
 /*   300 */    22,   70,    5,   52,   53,    5,   74,   75,   76,   79,
 /*   310 */    78,   31,    1,    2,   36,   18,   19,   79,   18,   19,
 /*   320 */    79,   24,   25,   26,   24,   25,   26,    1,   13,   14,
 /*   330 */    15,   16,   17,   18,   19,   20,   21,   22,   52,   53,
 /*   340 */    79,   55,   79,   52,   53,   79,   55,   36,    1,    1,
 /*   350 */     2,   36,   51,   52,   53,   52,   53,   51,   52,   53,
 /*   360 */    52,   53,   36,    1,    2,   13,   14,   15,   16,   17,
 /*   370 */    18,   19,   20,   21,   22,    3,    4,    3,    4,   52,
 /*   380 */    53,   52,   53,   36,   36,   52,   53,   52,   53,   52,
 /*   390 */    53,   52,   53,    1,   52,   53,   52,   53,   79,   79,
 /*   400 */    79,   52,   53,   52,   53,   79,   34,   79,   34,   52,
 /*   410 */    53,   52,   53,   52,   53,   52,   53,   52,   53,   79,
 /*   420 */    79,   79,   79,   79,   79,   79,   79,   79,   36,
};
#define YY_SHIFT_USE_DFLT (-31)
#define YY_SHIFT_MAX 94
static const short yy_shift_ofst[] = {
 /*     0 */   -31,  205,  178,  205,  205,  205,  205,   25,  255,  255,
 /*    10 */   297,  297,  297,  300,  300,  297,  255,  255,  255,  255,
 /*    20 */   255,  255,  255,  255,  255,  255,  255,  255,  255,  255,
 /*    30 */   255,  255,  255,  255,  255,  255,  255,  255,  255,  255,
 /*    40 */    20,  195,   58,   49,    2,  172,  241,  315,  278,  352,
 /*    50 */   352,  352,  352,  352,  352,  352,  352,  250,  190,  216,
 /*    60 */   264,  264,  372,  374,  154,  154,   87,  348,  311,  117,
 /*    70 */    26,  111,  326,  347,  362,   90,  392,  210,  280,   97,
 /*    80 */   136,  191,  175,  -30,  138,  145,  222,  218,   92,  206,
 /*    90 */    34,  259,  152,  113,   86,
};
#define YY_REDUCE_USE_DFLT (-51)
#define YY_REDUCE_MAX 44
static const short yy_reduce_ofst[] = {
 /*     0 */   -38,  -45,  100,   71,   42,   13,  -16,  232,  -50,  174,
 /*    10 */   -22,  146,  198,  223,  286,  291,  301,  306,  339,  349,
 /*    20 */   342,  337,  351,  344,  335,  333,  329,  327,  308,  303,
 /*    30 */   251,  102,   73,   44,  -14,  357,  365,  363,  361,  359,
 /*    40 */   237,   91,   55,    9,  231,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   235,  237,  237,  237,  237,  237,  237,  237,  164,  164,
 /*    10 */   237,  237,  237,  237,  237,  237,  237,  237,  237,  237,
 /*    20 */   237,  237,  237,  237,  237,  237,  237,  237,  237,  237,
 /*    30 */   237,  237,  237,  237,  237,  237,  237,  237,  237,  237,
 /*    40 */   237,  237,  237,  237,  237,  237,  237,  237,  237,  182,
 /*    50 */   186,  185,  162,  184,  183,  161,  187,  177,  178,  176,
 /*    60 */   174,  175,  237,  237,  169,  170,  166,  237,  237,  237,
 /*    70 */   237,  237,  237,  237,  237,  237,  237,  237,  237,  237,
 /*    80 */   237,  189,  237,  237,  237,  237,  237,  237,  163,  166,
 /*    90 */   237,  204,  237,  237,  168,  160,  217,  165,  168,  218,
 /*   100 */   156,  219,  172,  220,  173,  221,  222,  223,  224,  226,
 /*   110 */   227,  179,  228,  180,  229,  181,  230,  167,  231,  196,
 /*   120 */   197,  225,  193,  195,  198,  212,  199,  200,  202,  201,
 /*   130 */   215,  232,  233,  234,  236,  194,  188,  159,  190,  191,
 /*   140 */   203,  192,  205,  158,  206,  207,  208,  209,  210,  211,
 /*   150 */   216,  214,  213,  171,  157,
};
#define YY_SZ_ACTTAB (int)(sizeof(yy_action)/sizeof(yy_action[0]))

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
  "BITNOT",        "NUMBER",        "NAME",          "FUNCCALL",    
  "IFX",           "IFNOT",         "ELSE",          "LSQBRACKET",  
  "RSQBRACKET",    "LPAREN",        "RPAREN",        "VAR",         
  "SEMICOLON",     "LBRACKET",      "RBRACKET",      "IF",          
  "WHILE",         "CONTINUE",      "BREAK",         "FUNCTION",    
  "RETURN",        "error",         "nt",            "program",     
  "chunks",        "numList",       "nameList",      "exprList",    
  "funcexpr",      "expr",          "emptyableExprList",  "lexpr",       
  "vdef_stmt",     "vdefAssign_stmt",  "vdefMulti_stmt",  "vdefMultiAssign_stmt",
  "assign_stmt",   "assignMulti_stmt",  "stmtList",      "stmt",        
  "block",         "if_start",      "if_header",     "if_stmt",     
  "else_header",   "while_start",   "while_cond",    "while_stmt",  
  "continue_stmt",  "break_stmt",    "function_start",  "function_header",
  "fdef_chunk",    "return_stmt",   "chunk",       
};
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *const yyRuleName[] = {
 /*   0 */ "program ::= chunks",
 /*   1 */ "numList ::= NUMBER",
 /*   2 */ "numList ::= numList COMMA NUMBER",
 /*   3 */ "nameList ::= NAME COMMA NAME",
 /*   4 */ "nameList ::= nameList COMMA NAME",
 /*   5 */ "exprList ::= funcexpr LSQBRACKET LSQBRACKET numList RSQBRACKET RSQBRACKET",
 /*   6 */ "exprList ::= expr",
 /*   7 */ "exprList ::= exprList COMMA expr",
 /*   8 */ "emptyableExprList ::= exprList",
 /*   9 */ "emptyableExprList ::=",
 /*  10 */ "expr ::= NUMBER",
 /*  11 */ "expr ::= NAME",
 /*  12 */ "funcexpr ::= NAME LPAREN emptyableExprList RPAREN",
 /*  13 */ "expr ::= funcexpr",
 /*  14 */ "expr ::= expr PLUS expr",
 /*  15 */ "expr ::= expr MINUS expr",
 /*  16 */ "expr ::= expr MULTIPLY expr",
 /*  17 */ "expr ::= expr DIVIDE expr",
 /*  18 */ "expr ::= expr MOD expr",
 /*  19 */ "expr ::= expr LSHIFT expr",
 /*  20 */ "expr ::= expr RSHIFT expr",
 /*  21 */ "expr ::= expr BITAND expr",
 /*  22 */ "expr ::= expr BITOR expr",
 /*  23 */ "expr ::= expr BITXOR expr",
 /*  24 */ "expr ::= PLUS expr",
 /*  25 */ "expr ::= MINUS expr",
 /*  26 */ "expr ::= BITNOT expr",
 /*  27 */ "lexpr ::= expr EQ expr",
 /*  28 */ "lexpr ::= expr NE expr",
 /*  29 */ "lexpr ::= expr LE expr",
 /*  30 */ "lexpr ::= expr LT expr",
 /*  31 */ "lexpr ::= expr GE expr",
 /*  32 */ "lexpr ::= expr GT expr",
 /*  33 */ "lexpr ::= lexpr LAND lexpr",
 /*  34 */ "lexpr ::= lexpr LOR lexpr",
 /*  35 */ "lexpr ::= LNOT lexpr",
 /*  36 */ "lexpr ::= LNOT LNOT lexpr",
 /*  37 */ "vdef_stmt ::= VAR NAME SEMICOLON",
 /*  38 */ "vdefAssign_stmt ::= VAR NAME ASSIGN expr SEMICOLON",
 /*  39 */ "vdefMulti_stmt ::= VAR nameList SEMICOLON",
 /*  40 */ "vdefMultiAssign_stmt ::= VAR nameList ASSIGN exprList SEMICOLON",
 /*  41 */ "assign_stmt ::= NAME ASSIGN expr SEMICOLON",
 /*  42 */ "assignMulti_stmt ::= nameList ASSIGN exprList SEMICOLON",
 /*  43 */ "stmtList ::= stmt",
 /*  44 */ "stmtList ::= stmtList stmt",
 /*  45 */ "block ::= LBRACKET stmtList RBRACKET",
 /*  46 */ "block ::= LBRACKET error RBRACKET",
 /*  47 */ "if_start ::= IF",
 /*  48 */ "if_header ::= if_start LPAREN lexpr RPAREN",
 /*  49 */ "if_stmt ::= if_header stmt",
 /*  50 */ "else_header ::= if_header stmt ELSE",
 /*  51 */ "if_stmt ::= else_header stmt",
 /*  52 */ "while_start ::= WHILE",
 /*  53 */ "while_cond ::= LPAREN lexpr RPAREN",
 /*  54 */ "while_stmt ::= while_start while_cond stmt",
 /*  55 */ "continue_stmt ::= CONTINUE SEMICOLON",
 /*  56 */ "break_stmt ::= BREAK SEMICOLON",
 /*  57 */ "function_start ::= FUNCTION NAME",
 /*  58 */ "function_header ::= function_start LPAREN nameList RPAREN",
 /*  59 */ "function_header ::= function_start LPAREN RPAREN",
 /*  60 */ "fdef_chunk ::= function_header stmt",
 /*  61 */ "return_stmt ::= RETURN emptyableExprList",
 /*  62 */ "stmt ::= error SEMICOLON",
 /*  63 */ "stmt ::= SEMICOLON",
 /*  64 */ "stmt ::= vdef_stmt",
 /*  65 */ "stmt ::= vdefAssign_stmt",
 /*  66 */ "stmt ::= vdefMultiAssign_stmt",
 /*  67 */ "stmt ::= vdefMulti_stmt",
 /*  68 */ "stmt ::= assign_stmt",
 /*  69 */ "stmt ::= assignMulti_stmt",
 /*  70 */ "stmt ::= expr SEMICOLON",
 /*  71 */ "stmt ::= if_stmt",
 /*  72 */ "stmt ::= while_stmt",
 /*  73 */ "stmt ::= continue_stmt",
 /*  74 */ "stmt ::= break_stmt",
 /*  75 */ "stmt ::= return_stmt",
 /*  76 */ "stmt ::= block",
 /*  77 */ "chunk ::= fdef_chunk",
 /*  78 */ "chunk ::= vdef_stmt",
 /*  79 */ "chunk ::= vdefMulti_stmt",
 /*  80 */ "chunks ::=",
 /*  81 */ "chunks ::= chunks chunk",
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
    case 46: /* nt */
{
#line 21 "parser/epparser.lemon"
 delete (yypminor->yy0); 
#line 571 "parser/epparser.c"
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
 
  if( stateno>YY_SHIFT_MAX || (i = yy_shift_ofst[stateno])==YY_SHIFT_USE_DFLT ){
    return yy_default[stateno];
  }
  assert( iLookAhead!=YYNOCODE );
  i += iLookAhead;
  if( i<0 || i>=YY_SZ_ACTTAB || yy_lookahead[i]!=iLookAhead ){
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
        if( j>=0 && j<YY_SZ_ACTTAB && yy_lookahead[j]==YYWILDCARD ){
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
  if( stateno>YY_REDUCE_MAX ){
    return yy_default[stateno];
  }
#else
  assert( stateno<=YY_REDUCE_MAX );
#endif
  i = yy_reduce_ofst[stateno];
  assert( i!=YY_REDUCE_USE_DFLT );
  assert( iLookAhead!=YYNOCODE );
  i += iLookAhead;
#ifdef YYERRORSYMBOL
  if( i<0 || i>=YY_SZ_ACTTAB || yy_lookahead[i]!=iLookAhead ){
    return yy_default[stateno];
  }
#else
  assert( i>=0 && i<YY_SZ_ACTTAB );
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
  { 47, 1 },
  { 49, 1 },
  { 49, 3 },
  { 50, 3 },
  { 50, 3 },
  { 51, 6 },
  { 51, 1 },
  { 51, 3 },
  { 54, 1 },
  { 54, 0 },
  { 53, 1 },
  { 53, 1 },
  { 52, 4 },
  { 53, 1 },
  { 53, 3 },
  { 53, 3 },
  { 53, 3 },
  { 53, 3 },
  { 53, 3 },
  { 53, 3 },
  { 53, 3 },
  { 53, 3 },
  { 53, 3 },
  { 53, 3 },
  { 53, 2 },
  { 53, 2 },
  { 53, 2 },
  { 55, 3 },
  { 55, 3 },
  { 55, 3 },
  { 55, 3 },
  { 55, 3 },
  { 55, 3 },
  { 55, 3 },
  { 55, 3 },
  { 55, 2 },
  { 55, 3 },
  { 56, 3 },
  { 57, 5 },
  { 58, 3 },
  { 59, 5 },
  { 60, 4 },
  { 61, 4 },
  { 62, 1 },
  { 62, 2 },
  { 64, 3 },
  { 64, 3 },
  { 65, 1 },
  { 66, 4 },
  { 67, 2 },
  { 68, 3 },
  { 67, 2 },
  { 69, 1 },
  { 70, 3 },
  { 71, 3 },
  { 72, 2 },
  { 73, 2 },
  { 74, 2 },
  { 75, 4 },
  { 75, 3 },
  { 76, 2 },
  { 77, 2 },
  { 63, 2 },
  { 63, 1 },
  { 63, 1 },
  { 63, 1 },
  { 63, 1 },
  { 63, 1 },
  { 63, 1 },
  { 63, 1 },
  { 63, 2 },
  { 63, 1 },
  { 63, 1 },
  { 63, 1 },
  { 63, 1 },
  { 63, 1 },
  { 63, 1 },
  { 78, 1 },
  { 78, 1 },
  { 78, 1 },
  { 48, 0 },
  { 48, 2 },
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
      case 1: /* numList ::= NUMBER */
      case 6: /* exprList ::= expr */ yytestcase(yyruleno==6);
      case 8: /* emptyableExprList ::= exprList */ yytestcase(yyruleno==8);
      case 10: /* expr ::= NUMBER */ yytestcase(yyruleno==10);
      case 13: /* expr ::= funcexpr */ yytestcase(yyruleno==13);
      case 36: /* lexpr ::= LNOT LNOT lexpr */ yytestcase(yyruleno==36);
#line 53 "parser/epparser.lemon"
{ yygotominor.yy0 = yymsp[0].minor.yy0; }
#line 944 "parser/epparser.c"
        break;
      case 2: /* numList ::= numList COMMA NUMBER */
#line 54 "parser/epparser.lemon"
{
    yygotominor.yy0 = new Token(yymsp[-2].minor.yy0->data + ", " + yymsp[0].minor.yy0->data, yymsp[0].minor.yy0);
    delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 952 "parser/epparser.c"
        break;
      case 3: /* nameList ::= NAME COMMA NAME */
      case 4: /* nameList ::= nameList COMMA NAME */ yytestcase(yyruleno==4);
      case 7: /* exprList ::= exprList COMMA expr */ yytestcase(yyruleno==7);
#line 58 "parser/epparser.lemon"
{ yygotominor.yy0 = new Token((yymsp[-2].minor.yy0->data) + ", " + (yymsp[0].minor.yy0->data), yymsp[0].minor.yy0); delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 959 "parser/epparser.c"
        break;
      case 5: /* exprList ::= funcexpr LSQBRACKET LSQBRACKET numList RSQBRACKET RSQBRACKET */
#line 60 "parser/epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[-2].minor.yy0);
    (*pGen) << yygotominor.yy0->data << " = SelectReturns(" << yymsp[-5].minor.yy0->data << ", [" << yymsp[-2].minor.yy0->data << "])" << std::endl;
    delete yymsp[-5].minor.yy0; delete yymsp[-2].minor.yy0;
}
#line 968 "parser/epparser.c"
        break;
      case 9: /* emptyableExprList ::= */
#line 69 "parser/epparser.lemon"
{ yygotominor.yy0 = new Token(TOKEN_TEMP, "", -1); }
#line 973 "parser/epparser.c"
        break;
      case 11: /* expr ::= NAME */
#line 73 "parser/epparser.lemon"
{
    if(pGen->undefined(yymsp[0].minor.yy0->data)) {
        throw_error(yymsp[0].minor.yy0->line, 103, ("Undeclared variable \'" + (yymsp[0].minor.yy0->data) + "\'"));
        pGen->namedef(yymsp[0].minor.yy0->data);
    }
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 984 "parser/epparser.c"
        break;
      case 12: /* funcexpr ::= NAME LPAREN emptyableExprList RPAREN */
#line 82 "parser/epparser.lemon"
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

    yygotominor.yy0 = genTemp(yymsp[-3].minor.yy0);
    (*pGen) << yygotominor.yy0->data << " = " << yymsp[-3].minor.yy0->data << "(" << yymsp[-1].minor.yy0->data << ")" << std::endl;
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1005 "parser/epparser.c"
        break;
      case 14: /* expr ::= expr PLUS expr */
#line 103 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = " << yymsp[-2].minor.yy0->data << " + "  << yymsp[0].minor.yy0->data << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1010 "parser/epparser.c"
        break;
      case 15: /* expr ::= expr MINUS expr */
#line 104 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = " << yymsp[-2].minor.yy0->data << " - "  << yymsp[0].minor.yy0->data << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1015 "parser/epparser.c"
        break;
      case 16: /* expr ::= expr MULTIPLY expr */
#line 105 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = " << yymsp[-2].minor.yy0->data << " * "  << yymsp[0].minor.yy0->data << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1020 "parser/epparser.c"
        break;
      case 17: /* expr ::= expr DIVIDE expr */
#line 106 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = " << yymsp[-2].minor.yy0->data << " // " << yymsp[0].minor.yy0->data << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1025 "parser/epparser.c"
        break;
      case 18: /* expr ::= expr MOD expr */
#line 107 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = " << yymsp[-2].minor.yy0->data << " % "  << yymsp[0].minor.yy0->data << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1030 "parser/epparser.c"
        break;
      case 19: /* expr ::= expr LSHIFT expr */
#line 108 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = " << yymsp[-2].minor.yy0->data << " << " << yymsp[0].minor.yy0->data << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1035 "parser/epparser.c"
        break;
      case 20: /* expr ::= expr RSHIFT expr */
#line 109 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = " << yymsp[-2].minor.yy0->data << " >> " << yymsp[0].minor.yy0->data << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1040 "parser/epparser.c"
        break;
      case 21: /* expr ::= expr BITAND expr */
#line 110 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = " << yymsp[-2].minor.yy0->data << " & "  << yymsp[0].minor.yy0->data << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1045 "parser/epparser.c"
        break;
      case 22: /* expr ::= expr BITOR expr */
#line 111 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = " << yymsp[-2].minor.yy0->data << " | "  << yymsp[0].minor.yy0->data << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1050 "parser/epparser.c"
        break;
      case 23: /* expr ::= expr BITXOR expr */
#line 112 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = " << yymsp[-2].minor.yy0->data << " ^ "  << yymsp[0].minor.yy0->data << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1055 "parser/epparser.c"
        break;
      case 24: /* expr ::= PLUS expr */
#line 115 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = +" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1060 "parser/epparser.c"
        break;
      case 25: /* expr ::= MINUS expr */
#line 116 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = -" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1065 "parser/epparser.c"
        break;
      case 26: /* expr ::= BITNOT expr */
#line 117 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = ~" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 1070 "parser/epparser.c"
        break;
      case 27: /* lexpr ::= expr EQ expr */
#line 120 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = (" << yymsp[-2].minor.yy0->data << " == " << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1075 "parser/epparser.c"
        break;
      case 28: /* lexpr ::= expr NE expr */
#line 121 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = (" << yymsp[-2].minor.yy0->data << " != " << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1080 "parser/epparser.c"
        break;
      case 29: /* lexpr ::= expr LE expr */
#line 122 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = (" << yymsp[-2].minor.yy0->data << " <= " << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1085 "parser/epparser.c"
        break;
      case 30: /* lexpr ::= expr LT expr */
#line 123 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = (" << yymsp[-2].minor.yy0->data << " < "  << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1090 "parser/epparser.c"
        break;
      case 31: /* lexpr ::= expr GE expr */
#line 124 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = (" << yymsp[-2].minor.yy0->data << " >= " << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1095 "parser/epparser.c"
        break;
      case 32: /* lexpr ::= expr GT expr */
#line 125 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = (" << yymsp[-2].minor.yy0->data << " > "  << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1100 "parser/epparser.c"
        break;
      case 33: /* lexpr ::= lexpr LAND lexpr */
#line 127 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = [" << yymsp[-2].minor.yy0->data << ", " << yymsp[0].minor.yy0->data << "]" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1105 "parser/epparser.c"
        break;
      case 34: /* lexpr ::= lexpr LOR lexpr */
#line 128 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = EUDOr([" << yymsp[-2].minor.yy0->data << ", " << yymsp[0].minor.yy0->data << "])" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1110 "parser/epparser.c"
        break;
      case 35: /* lexpr ::= LNOT lexpr */
#line 129 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = EUDNot(" << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[0].minor.yy0; }
#line 1115 "parser/epparser.c"
        break;
      case 37: /* vdef_stmt ::= VAR NAME SEMICOLON */
#line 134 "parser/epparser.lemon"
{
    (*pGen) << yymsp[-1].minor.yy0->data << " = EUDVariable()" << std::endl;
    pGen->namedef(yymsp[-1].minor.yy0->data);
    delete yymsp[-1].minor.yy0;
}
#line 1124 "parser/epparser.c"
        break;
      case 38: /* vdefAssign_stmt ::= VAR NAME ASSIGN expr SEMICOLON */
#line 140 "parser/epparser.lemon"
{
    (*pGen) << yymsp[-3].minor.yy0->data << " = EUDVariable()" << std::endl;
    (*pGen) << yymsp[-3].minor.yy0->data << " << " << yymsp[-1].minor.yy0->data << std::endl;
    if(!pGen->namedef(yymsp[-3].minor.yy0->data)) {
        throw_error(yymsp[-3].minor.yy0->line, 196, ("Redeclaration of variable \'" + (yymsp[-3].minor.yy0->data) + "\'"));
    }
    delete yymsp[-3].minor.yy0;
}
#line 1136 "parser/epparser.c"
        break;
      case 39: /* vdefMulti_stmt ::= VAR nameList SEMICOLON */
#line 149 "parser/epparser.lemon"
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
#line 1153 "parser/epparser.c"
        break;
      case 40: /* vdefMultiAssign_stmt ::= VAR nameList ASSIGN exprList SEMICOLON */
#line 163 "parser/epparser.lemon"
{
    std::string& s = yymsp[-3].minor.yy0->data;
    int varCount = std::count(s.begin(), s.end(), ',') + 1;
    (*pGen) << s << " = EUDCreateVariables(" << varCount << ")" << std::endl;
    (*pGen) << "SetVariables([" << yymsp[-3].minor.yy0->data << "], [" << yymsp[-1].minor.yy0->data << "])" << std::endl;

    // Register variables.
    commaListIter(s, [&](const std::string& varname) {
        if(!pGen->namedef(varname)) {
            throw_error(yymsp[-3].minor.yy0->line, 196, ("Redeclaration of variable \'" + varname + "\'"));
        }
    });

    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1172 "parser/epparser.c"
        break;
      case 41: /* assign_stmt ::= NAME ASSIGN expr SEMICOLON */
#line 179 "parser/epparser.lemon"
{
    (*pGen) << yymsp[-3].minor.yy0->data << " << " << yymsp[-1].minor.yy0->data << std::endl;
    if(pGen->undefined(yymsp[-3].minor.yy0->data)) {
        throw_error(yymsp[-3].minor.yy0->line, 103, ("Undeclared variable \'" + (yymsp[-3].minor.yy0->data) + "\'"));
        pGen->namedef(yymsp[-3].minor.yy0->data);
    }
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1184 "parser/epparser.c"
        break;
      case 42: /* assignMulti_stmt ::= nameList ASSIGN exprList SEMICOLON */
#line 188 "parser/epparser.lemon"
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
#line 1200 "parser/epparser.c"
        break;
      case 46: /* block ::= LBRACKET error RBRACKET */
#line 205 "parser/epparser.lemon"
{
    throw_error(yymsp[0].minor.yy0->line, 6974, "General syntax error");
}
#line 1207 "parser/epparser.c"
        break;
      case 47: /* if_start ::= IF */
#line 211 "parser/epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    (*pGen) << yygotominor.yy0->data << " = Forward()" << std::endl;
}
#line 1215 "parser/epparser.c"
        break;
      case 48: /* if_header ::= if_start LPAREN lexpr RPAREN */
#line 215 "parser/epparser.lemon"
{
    (*pGen) << "EUDJumpIfNot(" << yymsp[-1].minor.yy0->data << ", " << yymsp[-3].minor.yy0->data << ")" << std::endl;
    yygotominor.yy0 = yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1223 "parser/epparser.c"
        break;
      case 49: /* if_stmt ::= if_header stmt */
      case 51: /* if_stmt ::= else_header stmt */ yytestcase(yyruleno==51);
#line 220 "parser/epparser.lemon"
{
    (*pGen) << yymsp[-1].minor.yy0->data << " << NextTrigger()" << std::endl;
    delete yymsp[-1].minor.yy0;
}
#line 1232 "parser/epparser.c"
        break;
      case 50: /* else_header ::= if_header stmt ELSE */
#line 225 "parser/epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    (*pGen) << yygotominor.yy0->data << " = Forward()" << std::endl;
    (*pGen) << "EUDJump(" << yygotominor.yy0->data << ")" << std::endl;
    (*pGen) << yymsp[-2].minor.yy0->data << " << NextTrigger()" << std::endl;
    delete yymsp[-2].minor.yy0;
}
#line 1243 "parser/epparser.c"
        break;
      case 52: /* while_start ::= WHILE */
#line 240 "parser/epparser.lemon"
{
    auto lbegin = genTemp(yymsp[0].minor.yy0);
    auto lend = genTemp(yymsp[0].minor.yy0);
    lblocks.push_back({lbegin->data, lbegin->data, lend->data});

    (*pGen) << lbegin->data << " = NextTrigger()" << std::endl;
    (*pGen) << lend->data << " = Forward()" << std::endl;
    yygotominor.yy0 = lbegin;
    delete yymsp[0].minor.yy0;
}
#line 1257 "parser/epparser.c"
        break;
      case 53: /* while_cond ::= LPAREN lexpr RPAREN */
#line 251 "parser/epparser.lemon"
{
    auto lblock = getLastBlock();
    if(!lblock) {
        throw_error(yymsp[0].minor.yy0->line, 4217, "While scope is missing");
    }
    else {
        (*pGen) << "EUDJumpIfNot(" << yymsp[-1].minor.yy0->data << ", " << lblock->lend << ")" << std::endl;
    }
    delete yymsp[-1].minor.yy0; delete yymsp[0].minor.yy0;
}
#line 1271 "parser/epparser.c"
        break;
      case 54: /* while_stmt ::= while_start while_cond stmt */
#line 262 "parser/epparser.lemon"
{
    auto lblock = getLastBlock();
    if(!lblock) {
        throw_error(yymsp[-2].minor.yy0->line, 4217, "While scope is missing");
    }
    else {
        (*pGen) << "EUDJump(" << lblock->lbegin << ")" << std::endl;
        (*pGen) << lblock->lend << " << NextTrigger()" << std::endl;
    }
    delete yymsp[-2].minor.yy0;
}
#line 1286 "parser/epparser.c"
        break;
      case 55: /* continue_stmt ::= CONTINUE SEMICOLON */
#line 275 "parser/epparser.lemon"
{
    auto lblock = getLastBlock();
    if(!lblock) {
        throw_error(yymsp[0].minor.yy0->line, 1554, "Continue inside non-loop");
    }
    else {
        (*pGen) << "EUDJump(" << lblock->lcont << ")" << std::endl;
    }
    delete yymsp[0].minor.yy0;
}
#line 1300 "parser/epparser.c"
        break;
      case 56: /* break_stmt ::= BREAK SEMICOLON */
#line 286 "parser/epparser.lemon"
{
    auto lblock = getLastBlock();
    if(!lblock) {
        throw_error(yymsp[0].minor.yy0->line, 5594, "Break inside non-loop");
    }
    else {
        (*pGen) << "EUDJump(" << lblock->lend << ")" << std::endl;
    }
    delete yymsp[0].minor.yy0;
}
#line 1314 "parser/epparser.c"
        break;
      case 57: /* function_start ::= FUNCTION NAME */
#line 298 "parser/epparser.lemon"
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
#line 1330 "parser/epparser.c"
        break;
      case 58: /* function_header ::= function_start LPAREN nameList RPAREN */
#line 311 "parser/epparser.lemon"
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
#line 1350 "parser/epparser.c"
        break;
      case 59: /* function_header ::= function_start LPAREN RPAREN */
#line 328 "parser/epparser.lemon"
{
    (*pGen) << "@EUDFunc" << std::endl;
    (*pGen) << "def " << yymsp[-2].minor.yy0->data << "():" << std::endl;
    pGen->indent();
    tmpIndex = 1;
    delete yymsp[-2].minor.yy0;
}
#line 1361 "parser/epparser.c"
        break;
      case 60: /* fdef_chunk ::= function_header stmt */
#line 336 "parser/epparser.lemon"
{
    pGen->unindent();
}
#line 1368 "parser/epparser.c"
        break;
      case 61: /* return_stmt ::= RETURN emptyableExprList */
#line 342 "parser/epparser.lemon"
{
    (*pGen) << "EUDReturn(" << yymsp[0].minor.yy0->data << ")" << std::endl;
}
#line 1375 "parser/epparser.c"
        break;
      case 62: /* stmt ::= error SEMICOLON */
#line 348 "parser/epparser.lemon"
{ throw_error(yymsp[0].minor.yy0->line, 6974, "General syntax error"); }
#line 1380 "parser/epparser.c"
        break;
      default:
      /* (0) program ::= chunks */ yytestcase(yyruleno==0);
      /* (43) stmtList ::= stmt */ yytestcase(yyruleno==43);
      /* (44) stmtList ::= stmtList stmt */ yytestcase(yyruleno==44);
      /* (45) block ::= LBRACKET stmtList RBRACKET */ yytestcase(yyruleno==45);
      /* (63) stmt ::= SEMICOLON */ yytestcase(yyruleno==63);
      /* (64) stmt ::= vdef_stmt */ yytestcase(yyruleno==64);
      /* (65) stmt ::= vdefAssign_stmt */ yytestcase(yyruleno==65);
      /* (66) stmt ::= vdefMultiAssign_stmt */ yytestcase(yyruleno==66);
      /* (67) stmt ::= vdefMulti_stmt */ yytestcase(yyruleno==67);
      /* (68) stmt ::= assign_stmt */ yytestcase(yyruleno==68);
      /* (69) stmt ::= assignMulti_stmt */ yytestcase(yyruleno==69);
      /* (70) stmt ::= expr SEMICOLON */ yytestcase(yyruleno==70);
      /* (71) stmt ::= if_stmt */ yytestcase(yyruleno==71);
      /* (72) stmt ::= while_stmt */ yytestcase(yyruleno==72);
      /* (73) stmt ::= continue_stmt */ yytestcase(yyruleno==73);
      /* (74) stmt ::= break_stmt */ yytestcase(yyruleno==74);
      /* (75) stmt ::= return_stmt */ yytestcase(yyruleno==75);
      /* (76) stmt ::= block */ yytestcase(yyruleno==76);
      /* (77) chunk ::= fdef_chunk */ yytestcase(yyruleno==77);
      /* (78) chunk ::= vdef_stmt */ yytestcase(yyruleno==78);
      /* (79) chunk ::= vdefMulti_stmt */ yytestcase(yyruleno==79);
      /* (80) chunks ::= */ yytestcase(yyruleno==80);
      /* (81) chunks ::= chunks chunk */ yytestcase(yyruleno==81);
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
#line 13 "parser/epparser.lemon"

    errorOccured = true;
#line 1468 "parser/epparser.c"
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
#line 373 "parser/epparser.lemon"


// #define PARSER_DEBUG

std::string ParseString(const std::string& code)
{
    std::istringstream is(code);
    Tokenizer tok(is);
    void* pParser = ParseAlloc (malloc);
    PyGenerator pGen;
    Token* token;
    int line = 0;

    lblocks.clear();

#ifdef PARSER_DEBUG
    std::cout << "Parsing string [[[\n" << code << "\n]]]\n";
#endif

    tmpIndex = 1;
    errorOccured = false;
    while ((token = tok.getToken()) != nullptr) {
        if (line != tok.getCurrentLine()) {
            line = tok.getCurrentLine();
            pGen << "# (Line " << line << ") " << trim(tok.getCurrentLineString()) << std::endl;
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
#line 1703 "parser/epparser.c"
