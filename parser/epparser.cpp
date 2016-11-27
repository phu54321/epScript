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
#include "tokenizer/tokenizer.h"

static int tmpIndex = 0;
static bool errorOccured = false;
Token* genTemp(Token* lineSrc) {
    static char output[20] = "_t";
    sprintf(output, "_t%d", tmpIndex++);
    return new Token(output, lineSrc);
}

void throw_error(int line, int code, const std::string& message) {
    std::cout << "[Error " << code << "] Line " << line << " : " << message << std::endl;
    errorOccured = true;
}

#line 28 "parser/epparser.lemon"


// Loop block related
struct LBlock {
    std::string lbegin;
    std::string lcont;
    std::string lend;
};

std::vector<LBlock> lblocks;

LBlock* getLastBlock() {
    if(lblocks.empty()) return nullptr;
    return &lblocks[lblocks.size() - 1];
}

#line 51 "parser/epparser.c"
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
#define YYNOCODE 66
#define YYACTIONTYPE unsigned char
#define ParseTOKENTYPE Token*
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  int yy131;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL  PyGenerator* pGen ;
#define ParseARG_PDECL , PyGenerator* pGen 
#define ParseARG_FETCH  PyGenerator* pGen  = yypParser->pGen 
#define ParseARG_STORE yypParser->pGen  = pGen 
#define YYNSTATE 121
#define YYNRULE 64
#define YYERRORSYMBOL 40
#define YYERRSYMDT yy131
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
 /*     0 */    74,   86,  186,   66,   65,  106,   39,  105,  108,  109,
 /*    10 */   111,  110,  112,  113,   50,  101,   69,    5,  114,    4,
 /*    20 */    36,   52,  115,   83,   90,   62,   61,   43,  119,   65,
 /*    30 */    54,   39,   53,  108,  109,  111,  110,  112,  113,    2,
 /*    40 */   101,   69,    5,  114,    4,   36,   92,  115,   83,   90,
 /*    50 */    74,   68,   12,   71,   65,   46,   39,   95,  108,  109,
 /*    60 */   111,  110,  112,  113,   96,  101,   69,    5,  114,    4,
 /*    70 */    36,   58,  115,   83,   90,   74,   38,   70,  100,   65,
 /*    80 */    80,   39,   60,  108,  109,  111,  110,  112,  113,   41,
 /*    90 */   101,   69,    5,  114,    4,   36,  106,  115,   83,   90,
 /*   100 */    74,   38,   57,  118,   65,  121,   39,  104,  108,  109,
 /*   110 */   111,  110,  112,  113,   42,  101,   69,    5,  114,    4,
 /*   120 */    36,  102,  115,   83,   90,   74,   38,   85,   93,   65,
 /*   130 */    51,   39,   91,  108,  109,  111,  110,  112,  113,   48,
 /*   140 */   101,   69,    5,  114,    4,   36,    9,  115,   83,   90,
 /*   150 */    16,   35,   34,   33,   15,   17,   27,   14,   26,   24,
 /*   160 */    25,   19,   20,   22,   21,   23,   28,   29,   24,   25,
 /*   170 */    19,   20,   22,   21,   23,   63,   99,   30,   37,  107,
 /*   180 */     1,  117,  116,   28,   29,   94,   72,   73,    6,    9,
 /*   190 */     6,    9,   63,   99,   30,   37,  107,    1,  103,  116,
 /*   200 */    38,   81,   94,   72,   73,    7,   27,   14,   26,   24,
 /*   210 */    25,   19,   20,   22,   21,   23,   19,   20,   22,   21,
 /*   220 */    23,   88,   55,   98,   76,   27,   14,   26,   24,   25,
 /*   230 */    19,   20,   22,   21,   23,   22,   21,   23,   38,   59,
 /*   240 */    38,   87,    3,   82,   27,   14,   26,   24,   25,   19,
 /*   250 */    20,   22,   21,   23,   64,   43,   67,   18,   10,   56,
 /*   260 */    44,  187,   78,   27,   14,   26,   24,   25,   19,   20,
 /*   270 */    22,   21,   23,   47,   49,   40,   45,   14,   26,   24,
 /*   280 */    25,   19,   20,   22,   21,   23,   26,   24,   25,   19,
 /*   290 */    20,   22,   21,   23,    8,   68,   13,   11,   67,   32,
 /*   300 */    31,   31,   84,   28,   29,   89,  187,   28,   29,  187,
 /*   310 */    28,   29,   97,   99,   30,  187,   97,   99,   30,   97,
 /*   320 */    99,   30,  187,  187,  187,  120,  187,  187,   77,  187,
 /*   330 */    75,   79,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    40,   46,   42,   43,   44,   31,   46,   33,   48,   49,
 /*    10 */    50,   51,   52,   53,   46,   55,   56,   57,   58,   59,
 /*    20 */    60,   46,   62,   63,   64,   40,   45,   46,   43,   44,
 /*    30 */    46,   46,   46,   48,   49,   50,   51,   52,   53,   54,
 /*    40 */    55,   56,   57,   58,   59,   60,   46,   62,   63,   64,
 /*    50 */    40,    1,    2,   43,   44,   46,   46,   46,   48,   49,
 /*    60 */    50,   51,   52,   53,   46,   55,   56,   57,   58,   59,
 /*    70 */    60,   46,   62,   63,   64,   40,   46,   47,   43,   44,
 /*    80 */    27,   46,   46,   48,   49,   50,   51,   52,   53,   46,
 /*    90 */    55,   56,   57,   58,   59,   60,   31,   62,   63,   64,
 /*   100 */    40,   46,   47,   43,   44,    0,   46,   31,   48,   49,
 /*   110 */    50,   51,   52,   53,   46,   55,   56,   57,   58,   59,
 /*   120 */    60,   31,   62,   63,   64,   40,   46,   47,   43,   44,
 /*   130 */    46,   46,   26,   48,   49,   50,   51,   52,   53,   46,
 /*   140 */    55,   56,   57,   58,   59,   60,    4,   62,   63,   64,
 /*   150 */     7,    8,    9,   10,   11,   12,   13,   14,   15,   16,
 /*   160 */    17,   18,   19,   20,   21,   22,   18,   19,   16,   17,
 /*   170 */    18,   19,   20,   21,   22,   27,   28,   29,   30,   31,
 /*   180 */    32,   33,   34,   18,   19,   37,   38,   39,    3,    4,
 /*   190 */     3,    4,   27,   28,   29,   30,   31,   32,   27,   34,
 /*   200 */    46,   47,   37,   38,   39,   35,   13,   14,   15,   16,
 /*   210 */    17,   18,   19,   20,   21,   22,   18,   19,   20,   21,
 /*   220 */    22,   36,   44,   36,   31,   13,   14,   15,   16,   17,
 /*   230 */    18,   19,   20,   21,   22,   20,   21,   22,   46,   47,
 /*   240 */    46,   47,   61,   31,   13,   14,   15,   16,   17,   18,
 /*   250 */    19,   20,   21,   22,   45,   46,    1,    2,   35,   27,
 /*   260 */    46,   65,   31,   13,   14,   15,   16,   17,   18,   19,
 /*   270 */    20,   21,   22,   46,   46,   46,   46,   14,   15,   16,
 /*   280 */    17,   18,   19,   20,   21,   22,   15,   16,   17,   18,
 /*   290 */    19,   20,   21,   22,    5,    1,    2,    5,    1,    2,
 /*   300 */     1,    1,   46,   18,   19,   46,   65,   18,   19,   65,
 /*   310 */    18,   19,   27,   28,   29,   65,   27,   28,   29,   27,
 /*   320 */    28,   29,   65,   65,   65,   31,   65,   65,   31,   65,
 /*   330 */    31,   31,
};
#define YY_SHIFT_USE_DFLT (-27)
#define YY_SHIFT_MAX 74
static const short yy_shift_ofst[] = {
 /*     0 */   165,  165,  148,  165,  165,  165,  289,  289,  292,  289,
 /*    10 */   289,  292,  285,  285,  285,  285,  285,  285,  285,  285,
 /*    20 */   285,  285,  285,  285,  285,  285,  285,  285,  285,  285,
 /*    30 */   285,  285,  285,  285,  285,  285,  223,  232,  143,  231,
 /*    40 */   193,  212,  250,  250,  250,  250,  250,  250,  250,  250,
 /*    50 */   263,  271,  152,  198,  198,  294,  297,  185,  215,  187,
 /*    60 */   215,  299,  -26,  255,  300,   50,  105,  171,   53,  170,
 /*    70 */   142,  106,   90,   76,   65,
};
#define YY_REDUCE_USE_DFLT (-46)
#define YY_REDUCE_MAX 37
static const short yy_reduce_ofst[] = {
 /*     0 */   -40,  -15,   60,   35,   85,   10,   30,   55,   80,  154,
 /*    10 */   192,  194,  209,  -19,   84,    9,   93,   68,   43,   36,
 /*    20 */    25,   18,   11,    0,  -14,  -16,  -25,  -32,  259,  -45,
 /*    30 */   256,  230,  229,  228,  227,  214,  181,  178,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   185,  185,  185,  185,  185,  185,  185,  185,  185,  185,
 /*    10 */   185,  185,  185,  185,  185,  185,  185,  185,  185,  185,
 /*    20 */   185,  185,  185,  185,  185,  185,  185,  185,  185,  185,
 /*    30 */   185,  185,  185,  185,  185,  185,  185,  185,  185,  185,
 /*    40 */   185,  185,  142,  124,  143,  125,  146,  144,  141,  145,
 /*    50 */   136,  137,  135,  133,  134,  185,  185,  185,  129,  185,
 /*    60 */   128,  185,  185,  127,  185,  185,  185,  185,  185,  185,
 /*    70 */   148,  163,  185,  185,  185,  154,  152,  151,  179,  156,
 /*    80 */   123,  147,  155,  182,  140,  149,  139,  150,  162,  138,
 /*    90 */   183,  164,  132,  165,  166,  131,  130,  127,  167,  126,
 /*   100 */   168,  184,  169,  122,  170,  160,  171,  172,  173,  174,
 /*   110 */   175,  176,  177,  178,  180,  181,  161,  159,  158,  157,
 /*   120 */   153,
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
  "IFX",           "IFNOT",         "ELSE",          "NAME",        
  "NUMBER",        "BITNOT",        "VAR",           "SEMICOLON",   
  "LBRACKET",      "RBRACKET",      "IF",            "LPAREN",      
  "RPAREN",        "WHILE",         "CONTINUE",      "BREAK",       
  "error",         "nt",            "program",       "stmt",        
  "nameList",      "exprList",      "expr",          "lexpr",       
  "vdef_stmt",     "vdefAssign_stmt",  "vdefMulti_stmt",  "vdefMultiAssign_stmt",
  "assign_stmt",   "assignMulti_stmt",  "stmtList",      "block",       
  "if_start",      "if_header",     "if_stmt",       "else_header", 
  "while_start",   "while_cond",    "while_stmt",    "continue_stmt",
  "break_stmt",  
};
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *const yyRuleName[] = {
 /*   0 */ "program ::= stmt",
 /*   1 */ "nameList ::= NAME COMMA NAME",
 /*   2 */ "nameList ::= nameList COMMA NAME",
 /*   3 */ "exprList ::= expr",
 /*   4 */ "exprList ::= exprList COMMA expr",
 /*   5 */ "expr ::= NUMBER",
 /*   6 */ "expr ::= NAME",
 /*   7 */ "expr ::= expr PLUS expr",
 /*   8 */ "expr ::= expr MINUS expr",
 /*   9 */ "expr ::= expr MULTIPLY expr",
 /*  10 */ "expr ::= expr DIVIDE expr",
 /*  11 */ "expr ::= expr MOD expr",
 /*  12 */ "expr ::= expr LSHIFT expr",
 /*  13 */ "expr ::= expr RSHIFT expr",
 /*  14 */ "expr ::= expr BITAND expr",
 /*  15 */ "expr ::= expr BITOR expr",
 /*  16 */ "expr ::= expr BITXOR expr",
 /*  17 */ "expr ::= PLUS expr",
 /*  18 */ "expr ::= MINUS expr",
 /*  19 */ "expr ::= BITNOT expr",
 /*  20 */ "lexpr ::= expr EQ expr",
 /*  21 */ "lexpr ::= expr NE expr",
 /*  22 */ "lexpr ::= expr LE expr",
 /*  23 */ "lexpr ::= expr LT expr",
 /*  24 */ "lexpr ::= expr GE expr",
 /*  25 */ "lexpr ::= expr GT expr",
 /*  26 */ "lexpr ::= lexpr LAND lexpr",
 /*  27 */ "lexpr ::= lexpr LOR lexpr",
 /*  28 */ "lexpr ::= LNOT lexpr",
 /*  29 */ "lexpr ::= LNOT LNOT lexpr",
 /*  30 */ "vdef_stmt ::= VAR NAME SEMICOLON",
 /*  31 */ "vdefAssign_stmt ::= VAR NAME ASSIGN expr SEMICOLON",
 /*  32 */ "vdefMulti_stmt ::= VAR nameList SEMICOLON",
 /*  33 */ "vdefMultiAssign_stmt ::= VAR nameList ASSIGN exprList SEMICOLON",
 /*  34 */ "assign_stmt ::= NAME ASSIGN expr SEMICOLON",
 /*  35 */ "assignMulti_stmt ::= nameList ASSIGN exprList SEMICOLON",
 /*  36 */ "stmtList ::= stmt",
 /*  37 */ "stmtList ::= stmtList stmt",
 /*  38 */ "block ::= LBRACKET stmtList RBRACKET",
 /*  39 */ "block ::= LBRACKET error RBRACKET",
 /*  40 */ "if_start ::= IF",
 /*  41 */ "if_header ::= if_start LPAREN lexpr RPAREN",
 /*  42 */ "if_stmt ::= if_header stmt",
 /*  43 */ "else_header ::= if_header stmt ELSE",
 /*  44 */ "if_stmt ::= else_header stmt",
 /*  45 */ "while_start ::= WHILE",
 /*  46 */ "while_cond ::= LPAREN lexpr RPAREN",
 /*  47 */ "while_stmt ::= while_start while_cond stmt",
 /*  48 */ "continue_stmt ::= CONTINUE SEMICOLON",
 /*  49 */ "break_stmt ::= BREAK SEMICOLON",
 /*  50 */ "stmt ::= error SEMICOLON",
 /*  51 */ "stmt ::= SEMICOLON",
 /*  52 */ "stmt ::= vdef_stmt",
 /*  53 */ "stmt ::= vdefAssign_stmt",
 /*  54 */ "stmt ::= vdefMultiAssign_stmt",
 /*  55 */ "stmt ::= vdefMulti_stmt",
 /*  56 */ "stmt ::= assign_stmt",
 /*  57 */ "stmt ::= assignMulti_stmt",
 /*  58 */ "stmt ::= expr SEMICOLON",
 /*  59 */ "stmt ::= if_stmt",
 /*  60 */ "stmt ::= while_stmt",
 /*  61 */ "stmt ::= continue_stmt",
 /*  62 */ "stmt ::= break_stmt",
 /*  63 */ "stmt ::= block",
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
    case 41: /* nt */
{
#line 54 "parser/epparser.lemon"
 delete (yypminor->yy0); 
#line 558 "parser/epparser.c"
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
  { 42, 1 },
  { 44, 3 },
  { 44, 3 },
  { 45, 1 },
  { 45, 3 },
  { 46, 1 },
  { 46, 1 },
  { 46, 3 },
  { 46, 3 },
  { 46, 3 },
  { 46, 3 },
  { 46, 3 },
  { 46, 3 },
  { 46, 3 },
  { 46, 3 },
  { 46, 3 },
  { 46, 3 },
  { 46, 2 },
  { 46, 2 },
  { 46, 2 },
  { 47, 3 },
  { 47, 3 },
  { 47, 3 },
  { 47, 3 },
  { 47, 3 },
  { 47, 3 },
  { 47, 3 },
  { 47, 3 },
  { 47, 2 },
  { 47, 3 },
  { 48, 3 },
  { 49, 5 },
  { 50, 3 },
  { 51, 5 },
  { 52, 4 },
  { 53, 4 },
  { 54, 1 },
  { 54, 2 },
  { 55, 3 },
  { 55, 3 },
  { 56, 1 },
  { 57, 4 },
  { 58, 2 },
  { 59, 3 },
  { 58, 2 },
  { 60, 1 },
  { 61, 3 },
  { 62, 3 },
  { 63, 2 },
  { 64, 2 },
  { 43, 2 },
  { 43, 1 },
  { 43, 1 },
  { 43, 1 },
  { 43, 1 },
  { 43, 1 },
  { 43, 1 },
  { 43, 1 },
  { 43, 2 },
  { 43, 1 },
  { 43, 1 },
  { 43, 1 },
  { 43, 1 },
  { 43, 1 },
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
      case 1: /* nameList ::= NAME COMMA NAME */
      case 2: /* nameList ::= nameList COMMA NAME */ yytestcase(yyruleno==2);
      case 4: /* exprList ::= exprList COMMA expr */ yytestcase(yyruleno==4);
#line 85 "parser/epparser.lemon"
{ yygotominor.yy0 = new Token((yymsp[-2].minor.yy0->data) + ", " + (yymsp[0].minor.yy0->data), yymsp[0].minor.yy0); delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 910 "parser/epparser.c"
        break;
      case 3: /* exprList ::= expr */
      case 5: /* expr ::= NUMBER */ yytestcase(yyruleno==5);
      case 29: /* lexpr ::= LNOT LNOT lexpr */ yytestcase(yyruleno==29);
#line 87 "parser/epparser.lemon"
{ yygotominor.yy0 = yymsp[0].minor.yy0; }
#line 917 "parser/epparser.c"
        break;
      case 6: /* expr ::= NAME */
#line 92 "parser/epparser.lemon"
{
    if(pGen->undefined(yymsp[0].minor.yy0->data)) {
        throw_error(yymsp[0].minor.yy0->line, 103, ("Undeclared variable \'" + (yymsp[0].minor.yy0->data) + "\'"));
        pGen->namedef(yymsp[0].minor.yy0->data);
    }
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 928 "parser/epparser.c"
        break;
      case 7: /* expr ::= expr PLUS expr */
#line 101 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = " << yymsp[-2].minor.yy0->data << " + "  << yymsp[0].minor.yy0->data << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 933 "parser/epparser.c"
        break;
      case 8: /* expr ::= expr MINUS expr */
#line 102 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = " << yymsp[-2].minor.yy0->data << " - "  << yymsp[0].minor.yy0->data << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 938 "parser/epparser.c"
        break;
      case 9: /* expr ::= expr MULTIPLY expr */
#line 103 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = " << yymsp[-2].minor.yy0->data << " * "  << yymsp[0].minor.yy0->data << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 943 "parser/epparser.c"
        break;
      case 10: /* expr ::= expr DIVIDE expr */
#line 104 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = " << yymsp[-2].minor.yy0->data << " // " << yymsp[0].minor.yy0->data << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 948 "parser/epparser.c"
        break;
      case 11: /* expr ::= expr MOD expr */
#line 105 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = " << yymsp[-2].minor.yy0->data << " % "  << yymsp[0].minor.yy0->data << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 953 "parser/epparser.c"
        break;
      case 12: /* expr ::= expr LSHIFT expr */
#line 106 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = " << yymsp[-2].minor.yy0->data << " << " << yymsp[0].minor.yy0->data << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 958 "parser/epparser.c"
        break;
      case 13: /* expr ::= expr RSHIFT expr */
#line 107 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = " << yymsp[-2].minor.yy0->data << " >> " << yymsp[0].minor.yy0->data << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 963 "parser/epparser.c"
        break;
      case 14: /* expr ::= expr BITAND expr */
#line 108 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = " << yymsp[-2].minor.yy0->data << " & "  << yymsp[0].minor.yy0->data << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 968 "parser/epparser.c"
        break;
      case 15: /* expr ::= expr BITOR expr */
#line 109 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = " << yymsp[-2].minor.yy0->data << " | "  << yymsp[0].minor.yy0->data << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 973 "parser/epparser.c"
        break;
      case 16: /* expr ::= expr BITXOR expr */
#line 110 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = " << yymsp[-2].minor.yy0->data << " ^ "  << yymsp[0].minor.yy0->data << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 978 "parser/epparser.c"
        break;
      case 17: /* expr ::= PLUS expr */
#line 113 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = +" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 983 "parser/epparser.c"
        break;
      case 18: /* expr ::= MINUS expr */
#line 114 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = -" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 988 "parser/epparser.c"
        break;
      case 19: /* expr ::= BITNOT expr */
#line 115 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = ~" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 993 "parser/epparser.c"
        break;
      case 20: /* lexpr ::= expr EQ expr */
#line 118 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = (" << yymsp[-2].minor.yy0->data << " == " << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 998 "parser/epparser.c"
        break;
      case 21: /* lexpr ::= expr NE expr */
#line 119 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = (" << yymsp[-2].minor.yy0->data << " != " << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1003 "parser/epparser.c"
        break;
      case 22: /* lexpr ::= expr LE expr */
#line 120 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = (" << yymsp[-2].minor.yy0->data << " <= " << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1008 "parser/epparser.c"
        break;
      case 23: /* lexpr ::= expr LT expr */
#line 121 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = (" << yymsp[-2].minor.yy0->data << " < "  << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1013 "parser/epparser.c"
        break;
      case 24: /* lexpr ::= expr GE expr */
#line 122 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = (" << yymsp[-2].minor.yy0->data << " >= " << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1018 "parser/epparser.c"
        break;
      case 25: /* lexpr ::= expr GT expr */
#line 123 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = (" << yymsp[-2].minor.yy0->data << " > "  << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1023 "parser/epparser.c"
        break;
      case 26: /* lexpr ::= lexpr LAND lexpr */
#line 125 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = [" << yymsp[-2].minor.yy0->data << ", " << yymsp[0].minor.yy0->data << "]" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1028 "parser/epparser.c"
        break;
      case 27: /* lexpr ::= lexpr LOR lexpr */
#line 126 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = EUDOr([" << yymsp[-2].minor.yy0->data << ", " << yymsp[0].minor.yy0->data << "])" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1033 "parser/epparser.c"
        break;
      case 28: /* lexpr ::= LNOT lexpr */
#line 127 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = EUDNot(" << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[0].minor.yy0; }
#line 1038 "parser/epparser.c"
        break;
      case 30: /* vdef_stmt ::= VAR NAME SEMICOLON */
#line 131 "parser/epparser.lemon"
{
    (*pGen) << yymsp[-1].minor.yy0->data << " = EUDVariable()" << std::endl;
    pGen->namedef(yymsp[-1].minor.yy0->data);
    delete yymsp[-1].minor.yy0;
}
#line 1047 "parser/epparser.c"
        break;
      case 31: /* vdefAssign_stmt ::= VAR NAME ASSIGN expr SEMICOLON */
#line 137 "parser/epparser.lemon"
{
    (*pGen) << yymsp[-3].minor.yy0->data << " = EUDVariable()" << std::endl;
    (*pGen) << yymsp[-3].minor.yy0->data << " << " << yymsp[-1].minor.yy0->data << std::endl;
    pGen->namedef(yymsp[-3].minor.yy0->data);
    delete yymsp[-3].minor.yy0;
}
#line 1057 "parser/epparser.c"
        break;
      case 32: /* vdefMulti_stmt ::= VAR nameList SEMICOLON */
#line 144 "parser/epparser.lemon"
{
    std::string& s = yymsp[-1].minor.yy0->data;
    int varCount = std::count(s.begin(), s.end(), ',') + 1;
    (*pGen) << s << " = EUDCreateVariables(" << varCount << ")" << std::endl;

    // Register variables.
    const char *p = s.data(), *p2 = p;
    while(1) {
        while(*p2 != '\0' && *p2 != ',') p2++;
        pGen->namedef(std::string(p, p2 - p));
        if(*p2 == '\0') break;
        p = p2 = p2 + 2;
    }

    delete yymsp[-1].minor.yy0;
}
#line 1077 "parser/epparser.c"
        break;
      case 33: /* vdefMultiAssign_stmt ::= VAR nameList ASSIGN exprList SEMICOLON */
#line 161 "parser/epparser.lemon"
{
    std::string& s = yymsp[-3].minor.yy0->data;
    int varCount = std::count(s.begin(), s.end(), ',') + 1;
    (*pGen) << s << " = EUDCreateVariables(" << varCount << ")" << std::endl;
    (*pGen) << "SetVariables([" << yymsp[-3].minor.yy0->data << "], [" << yymsp[-1].minor.yy0->data << "])" << std::endl;

    // Register variables.
    const char *p = s.data(), *p2 = p;
    while(1) {
        while(*p2 != '\0' && *p2 != ',') p2++;
        pGen->namedef(std::string(p, p2 - p));
        if(*p2 == '\0') break;
        p = p2 = p2 + 2;
    }

    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1098 "parser/epparser.c"
        break;
      case 34: /* assign_stmt ::= NAME ASSIGN expr SEMICOLON */
#line 179 "parser/epparser.lemon"
{
    (*pGen) << yymsp[-3].minor.yy0->data << " << " << yymsp[-1].minor.yy0->data << std::endl;
    if(pGen->undefined(yymsp[-3].minor.yy0->data)) {
        throw_error(yymsp[-3].minor.yy0->line, 103, ("Undeclared variable \'" + (yymsp[-3].minor.yy0->data) + "\'"));
        pGen->namedef(yymsp[-3].minor.yy0->data);
    }
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1110 "parser/epparser.c"
        break;
      case 35: /* assignMulti_stmt ::= nameList ASSIGN exprList SEMICOLON */
#line 188 "parser/epparser.lemon"
{
    (*pGen) << "SetVariables([" << yymsp[-3].minor.yy0->data << "], [" << yymsp[-1].minor.yy0->data << "])" << std::endl;

    const char *p = yymsp[-3].minor.yy0->data.data(), *p2 = p;
    while(1) {
        while(*p2 != '\0' && *p2 != ',') p2++;
        std::string varname(p, p2 - p);
        if(pGen->undefined(varname)) {
            throw_error(yymsp[-3].minor.yy0->line, 103, ("Undeclared variable \'" + varname + "\'"));
            pGen->namedef(varname);
        }
        if(*p2 == '\0') break;
        p = p2 = p2 + 2;
    }

    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1131 "parser/epparser.c"
        break;
      case 39: /* block ::= LBRACKET error RBRACKET */
#line 210 "parser/epparser.lemon"
{
    throw_error(yymsp[0].minor.yy0->line, 6974, "General syntax error");
}
#line 1138 "parser/epparser.c"
        break;
      case 40: /* if_start ::= IF */
#line 216 "parser/epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    (*pGen) << yygotominor.yy0->data << " = Forward()" << std::endl;
}
#line 1146 "parser/epparser.c"
        break;
      case 41: /* if_header ::= if_start LPAREN lexpr RPAREN */
#line 220 "parser/epparser.lemon"
{
    (*pGen) << "EUDJumpIfNot(" << yymsp[-1].minor.yy0->data << ", " << yymsp[-3].minor.yy0->data << ")" << std::endl;
    yygotominor.yy0 = yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1154 "parser/epparser.c"
        break;
      case 42: /* if_stmt ::= if_header stmt */
      case 44: /* if_stmt ::= else_header stmt */ yytestcase(yyruleno==44);
#line 225 "parser/epparser.lemon"
{
    (*pGen) << yymsp[-1].minor.yy0->data << " << NextTrigger()" << std::endl;
    delete yymsp[-1].minor.yy0;
}
#line 1163 "parser/epparser.c"
        break;
      case 43: /* else_header ::= if_header stmt ELSE */
#line 230 "parser/epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    (*pGen) << yygotominor.yy0->data << " = Forward()" << std::endl;
    (*pGen) << "EUDJump(" << yygotominor.yy0->data << ")" << std::endl;
    (*pGen) << yymsp[-2].minor.yy0->data << " << NextTrigger()" << std::endl;
    delete yymsp[-2].minor.yy0;
}
#line 1174 "parser/epparser.c"
        break;
      case 45: /* while_start ::= WHILE */
#line 245 "parser/epparser.lemon"
{
    auto lbegin = genTemp(yymsp[0].minor.yy0);
    auto lend = genTemp(yymsp[0].minor.yy0);
    lblocks.push_back({lbegin->data, lbegin->data, lend->data});

    (*pGen) << lbegin->data << " = NextTrigger()" << std::endl;
    (*pGen) << lend->data << " = Forward()" << std::endl;
    yygotominor.yy0 = lbegin;
    delete yymsp[0].minor.yy0;
}
#line 1188 "parser/epparser.c"
        break;
      case 46: /* while_cond ::= LPAREN lexpr RPAREN */
#line 256 "parser/epparser.lemon"
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
#line 1202 "parser/epparser.c"
        break;
      case 47: /* while_stmt ::= while_start while_cond stmt */
#line 267 "parser/epparser.lemon"
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
#line 1217 "parser/epparser.c"
        break;
      case 48: /* continue_stmt ::= CONTINUE SEMICOLON */
#line 280 "parser/epparser.lemon"
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
#line 1231 "parser/epparser.c"
        break;
      case 49: /* break_stmt ::= BREAK SEMICOLON */
#line 291 "parser/epparser.lemon"
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
#line 1245 "parser/epparser.c"
        break;
      case 50: /* stmt ::= error SEMICOLON */
#line 304 "parser/epparser.lemon"
{ throw_error(yymsp[0].minor.yy0->line, 6974, "General syntax error"); }
#line 1250 "parser/epparser.c"
        break;
      default:
      /* (0) program ::= stmt */ yytestcase(yyruleno==0);
      /* (36) stmtList ::= stmt */ yytestcase(yyruleno==36);
      /* (37) stmtList ::= stmtList stmt */ yytestcase(yyruleno==37);
      /* (38) block ::= LBRACKET stmtList RBRACKET */ yytestcase(yyruleno==38);
      /* (51) stmt ::= SEMICOLON */ yytestcase(yyruleno==51);
      /* (52) stmt ::= vdef_stmt */ yytestcase(yyruleno==52);
      /* (53) stmt ::= vdefAssign_stmt */ yytestcase(yyruleno==53);
      /* (54) stmt ::= vdefMultiAssign_stmt */ yytestcase(yyruleno==54);
      /* (55) stmt ::= vdefMulti_stmt */ yytestcase(yyruleno==55);
      /* (56) stmt ::= assign_stmt */ yytestcase(yyruleno==56);
      /* (57) stmt ::= assignMulti_stmt */ yytestcase(yyruleno==57);
      /* (58) stmt ::= expr SEMICOLON */ yytestcase(yyruleno==58);
      /* (59) stmt ::= if_stmt */ yytestcase(yyruleno==59);
      /* (60) stmt ::= while_stmt */ yytestcase(yyruleno==60);
      /* (61) stmt ::= continue_stmt */ yytestcase(yyruleno==61);
      /* (62) stmt ::= break_stmt */ yytestcase(yyruleno==62);
      /* (63) stmt ::= block */ yytestcase(yyruleno==63);
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
#line 46 "parser/epparser.lemon"

    errorOccured = true;
#line 1332 "parser/epparser.c"
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
#line 321 "parser/epparser.lemon"


// #define PARSER_DEBUG

std::string ParseString(const std::string& code)
{
    std::istringstream is(code);
    Tokenizer tok(is);
    void* pParser = ParseAlloc (malloc);
    PyGenerator pGen;
    Token* token;

#ifdef PARSER_DEBUG
    std::cout << "Parsing string [[[\n" << code << "\n]]]\n";
#endif

    tmpIndex = 1;
    errorOccured = false;
    while((token = tok.getToken()) != nullptr) {
        if(tokenTypeConv(token)) {
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
    else throw std::runtime_error("Invalid syntax");
}
#line 1559 "parser/epparser.c"
