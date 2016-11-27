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
#define YYNOCODE 61
#define YYACTIONTYPE unsigned char
#define ParseTOKENTYPE Token*
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  int yy121;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL  PyGenerator* pGen ;
#define ParseARG_PDECL , PyGenerator* pGen 
#define ParseARG_FETCH  PyGenerator* pGen  = yypParser->pGen 
#define ParseARG_STORE yypParser->pGen  = pGen 
#define YYNSTATE 105
#define YYNRULE 55
#define YYERRORSYMBOL 39
#define YYERRSYMDT yy121
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
 /*     0 */    57,   61,   12,  103,   56,   95,   37,   94,   97,   96,
 /*    10 */     2,   90,   62,    5,   98,    4,   34,   95,   99,   72,
 /*    20 */    79,   67,   93,  161,   59,   56,   38,   37,   91,   97,
 /*    30 */    96,   80,   90,   62,    5,   98,    4,   34,   42,   99,
 /*    40 */    72,   79,   33,   15,   16,   32,   31,   14,   13,   26,
 /*    50 */    25,   23,   24,   18,   19,   21,   20,   22,   67,   60,
 /*    60 */    17,   82,   56,    6,   37,    9,   97,   96,   46,   90,
 /*    70 */    62,    5,   98,    4,   34,   40,   99,   72,   79,   67,
 /*    80 */    58,   39,   64,   56,  105,   37,   48,   97,   96,   30,
 /*    90 */    90,   62,    5,   98,    4,   34,   92,   99,   72,   79,
 /*   100 */    47,   67,   35,   74,  102,   56,   78,   37,   75,   97,
 /*   110 */    96,   73,   90,   62,    5,   98,    4,   34,  104,   99,
 /*   120 */    72,   79,   67,   35,   52,   89,   56,   69,   37,   10,
 /*   130 */    97,   96,   41,   90,   62,    5,   98,    4,   34,   43,
 /*   140 */    99,   72,   79,   44,   27,   28,    3,   18,   19,   21,
 /*   150 */    20,   22,   50,   55,   88,   29,   49,    1,  101,  100,
 /*   160 */    35,   63,   83,   65,   66,   35,   54,   13,   26,   25,
 /*   170 */    23,   24,   18,   19,   21,   20,   22,   81,   21,   20,
 /*   180 */    22,   35,   76,   84,   71,   13,   26,   25,   23,   24,
 /*   190 */    18,   19,   21,   20,   22,    8,    6,    8,    6,  162,
 /*   200 */    35,   70,   68,   13,   26,   25,   23,   24,   18,   19,
 /*   210 */    21,   20,   22,   27,   28,   85,   53,  162,   51,   36,
 /*   220 */    45,  162,   55,   88,   29,  162,    1,   87,  100,   77,
 /*   230 */   162,   83,   65,   66,  162,  162,  162,   26,   25,   23,
 /*   240 */    24,   18,   19,   21,   20,   22,  162,   25,   23,   24,
 /*   250 */    18,   19,   21,   20,   22,   23,   24,   18,   19,   21,
 /*   260 */    20,   22,   11,   27,   28,    7,  162,  162,  162,  162,
 /*   270 */   162,  162,   86,   88,   29,   27,   28,  162,   27,   28,
 /*   280 */   162,  162,  162,  162,   86,   88,   29,   86,   88,   29,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    39,    1,    2,   42,   43,   30,   45,   32,   47,   48,
 /*    10 */    49,   50,   51,   52,   53,   54,   55,   30,   57,   58,
 /*    20 */    59,   39,   30,   41,   42,   43,   45,   45,   30,   47,
 /*    30 */    48,   26,   50,   51,   52,   53,   54,   55,   45,   57,
 /*    40 */    58,   59,    7,    8,    9,   10,   11,   12,   13,   14,
 /*    50 */    15,   16,   17,   18,   19,   20,   21,   22,   39,    1,
 /*    60 */     2,   42,   43,    4,   45,   34,   47,   48,   45,   50,
 /*    70 */    51,   52,   53,   54,   55,   45,   57,   58,   59,   39,
 /*    80 */    44,   45,   42,   43,    0,   45,   45,   47,   48,    1,
 /*    90 */    50,   51,   52,   53,   54,   55,   27,   57,   58,   59,
 /*   100 */    45,   39,   45,   46,   42,   43,   45,   45,   45,   47,
 /*   110 */    48,   45,   50,   51,   52,   53,   54,   55,   30,   57,
 /*   120 */    58,   59,   39,   45,   46,   42,   43,   27,   45,   34,
 /*   130 */    47,   48,   45,   50,   51,   52,   53,   54,   55,   45,
 /*   140 */    57,   58,   59,   45,   18,   19,   56,   18,   19,   20,
 /*   150 */    21,   22,   45,   27,   28,   29,   45,   31,   32,   33,
 /*   160 */    45,   46,   36,   37,   38,   45,   46,   13,   14,   15,
 /*   170 */    16,   17,   18,   19,   20,   21,   22,   45,   20,   21,
 /*   180 */    22,   45,   46,   45,   30,   13,   14,   15,   16,   17,
 /*   190 */    18,   19,   20,   21,   22,    3,    4,    3,    4,   60,
 /*   200 */    45,   46,   30,   13,   14,   15,   16,   17,   18,   19,
 /*   210 */    20,   21,   22,   18,   19,   45,   45,   60,   45,   45,
 /*   220 */    45,   60,   27,   28,   29,   60,   31,   35,   33,   35,
 /*   230 */    60,   36,   37,   38,   60,   60,   60,   14,   15,   16,
 /*   240 */    17,   18,   19,   20,   21,   22,   60,   15,   16,   17,
 /*   250 */    18,   19,   20,   21,   22,   16,   17,   18,   19,   20,
 /*   260 */    21,   22,    5,   18,   19,    5,   60,   60,   60,   60,
 /*   270 */    60,   60,   27,   28,   29,   18,   19,   60,   18,   19,
 /*   280 */    60,   60,   60,   60,   27,   28,   29,   27,   28,   29,
};
#define YY_SHIFT_USE_DFLT (-26)
#define YY_SHIFT_MAX 67
static const short yy_shift_ofst[] = {
 /*     0 */   195,  195,  126,  195,  195,  195,  260,  257,  260,  260,
 /*    10 */   260,  257,  245,  245,  245,  245,  245,  245,  245,  245,
 /*    20 */   245,  245,  245,  245,  245,  245,  245,  245,  245,  245,
 /*    30 */   245,  245,  245,  245,   95,   35,  154,  172,  190,  190,
 /*    40 */   190,  190,  190,  190,  190,  190,  223,  232,  239,  129,
 /*    50 */   129,  158,  192,  158,  194,   58,    0,  -25,   88,   84,
 /*    60 */    69,  100,   31,   59,    5,   -2,   -8,  -13,
};
#define YY_REDUCE_USE_DFLT (-40)
#define YY_REDUCE_MAX 34
static const short yy_reduce_ofst[] = {
 /*     0 */   -18,  -39,   62,   83,   19,   40,  155,   57,  115,  120,
 /*    10 */    78,  136,   36,   23,   -7,  -19,  175,  174,  173,  171,
 /*    20 */   170,  138,  132,  111,  107,   41,   55,   61,   63,   66,
 /*    30 */    30,   87,   94,   98,   90,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   160,  160,  160,  160,  160,  160,  160,  160,  160,  160,
 /*    10 */   160,  160,  160,  160,  160,  160,  160,  160,  160,  160,
 /*    20 */   160,  160,  160,  160,  160,  160,  160,  160,  160,  160,
 /*    30 */   160,  160,  160,  160,  160,  160,  160,  160,  127,  108,
 /*    40 */   109,  130,  126,  129,  125,  128,  120,  121,  119,  117,
 /*    50 */   118,  112,  160,  113,  160,  111,  160,  160,  160,  160,
 /*    60 */   160,  160,  160,  132,  143,  160,  160,  160,  152,  107,
 /*    70 */   131,  135,  157,  124,  133,  123,  134,  142,  122,  158,
 /*    80 */   144,  116,  145,  146,  115,  114,  111,  147,  110,  148,
 /*    90 */   159,  149,  106,  150,  140,  151,  153,  154,  155,  156,
 /*   100 */   141,  139,  138,  137,  136,
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
  "NUMBER",        "BITNOT",        "SEMICOLON",     "LBRACKET",    
  "RBRACKET",      "IF",            "LPAREN",        "RPAREN",      
  "WHILE",         "CONTINUE",      "BREAK",         "error",       
  "nt",            "program",       "stmt",          "nameList",    
  "exprList",      "expr",          "lexpr",         "stmt_assignSingle",
  "stmt_assignMulti",  "stmtList",      "block",         "if_start",    
  "if_header",     "if_stmt",       "else_header",   "while_start", 
  "while_cond",    "while_stmt",    "continue_stmt",  "break_stmt",  
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
 /*  30 */ "stmt_assignSingle ::= NAME ASSIGN expr SEMICOLON",
 /*  31 */ "stmt_assignMulti ::= nameList ASSIGN exprList SEMICOLON",
 /*  32 */ "stmtList ::= stmt",
 /*  33 */ "stmtList ::= stmtList stmt",
 /*  34 */ "block ::= LBRACKET stmtList RBRACKET",
 /*  35 */ "block ::= LBRACKET error RBRACKET",
 /*  36 */ "if_start ::= IF",
 /*  37 */ "if_header ::= if_start LPAREN lexpr RPAREN",
 /*  38 */ "if_stmt ::= if_header stmt",
 /*  39 */ "else_header ::= if_header stmt ELSE",
 /*  40 */ "if_stmt ::= else_header stmt",
 /*  41 */ "while_start ::= WHILE",
 /*  42 */ "while_cond ::= LPAREN lexpr RPAREN",
 /*  43 */ "while_stmt ::= while_start while_cond stmt",
 /*  44 */ "continue_stmt ::= CONTINUE SEMICOLON",
 /*  45 */ "break_stmt ::= BREAK SEMICOLON",
 /*  46 */ "stmt ::= error SEMICOLON",
 /*  47 */ "stmt ::= expr SEMICOLON",
 /*  48 */ "stmt ::= stmt_assignMulti",
 /*  49 */ "stmt ::= stmt_assignSingle",
 /*  50 */ "stmt ::= if_stmt",
 /*  51 */ "stmt ::= while_stmt",
 /*  52 */ "stmt ::= continue_stmt",
 /*  53 */ "stmt ::= break_stmt",
 /*  54 */ "stmt ::= block",
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
    case 40: /* nt */
{
#line 54 "parser/epparser.lemon"
 delete (yypminor->yy0); 
#line 534 "parser/epparser.c"
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
  { 41, 1 },
  { 43, 3 },
  { 43, 3 },
  { 44, 1 },
  { 44, 3 },
  { 45, 1 },
  { 45, 1 },
  { 45, 3 },
  { 45, 3 },
  { 45, 3 },
  { 45, 3 },
  { 45, 3 },
  { 45, 3 },
  { 45, 3 },
  { 45, 3 },
  { 45, 3 },
  { 45, 3 },
  { 45, 2 },
  { 45, 2 },
  { 45, 2 },
  { 46, 3 },
  { 46, 3 },
  { 46, 3 },
  { 46, 3 },
  { 46, 3 },
  { 46, 3 },
  { 46, 3 },
  { 46, 3 },
  { 46, 2 },
  { 46, 3 },
  { 47, 4 },
  { 48, 4 },
  { 49, 1 },
  { 49, 2 },
  { 50, 3 },
  { 50, 3 },
  { 51, 1 },
  { 52, 4 },
  { 53, 2 },
  { 54, 3 },
  { 53, 2 },
  { 55, 1 },
  { 56, 3 },
  { 57, 3 },
  { 58, 2 },
  { 59, 2 },
  { 42, 2 },
  { 42, 2 },
  { 42, 1 },
  { 42, 1 },
  { 42, 1 },
  { 42, 1 },
  { 42, 1 },
  { 42, 1 },
  { 42, 1 },
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
#line 877 "parser/epparser.c"
        break;
      case 3: /* exprList ::= expr */
      case 5: /* expr ::= NUMBER */ yytestcase(yyruleno==5);
      case 29: /* lexpr ::= LNOT LNOT lexpr */ yytestcase(yyruleno==29);
#line 87 "parser/epparser.lemon"
{ yygotominor.yy0 = yymsp[0].minor.yy0; }
#line 884 "parser/epparser.c"
        break;
      case 6: /* expr ::= NAME */
#line 92 "parser/epparser.lemon"
{
    if(pGen->undefined(yymsp[0].minor.yy0->data)) {
        throw_error(yymsp[0].minor.yy0->line, 103, ("Undefined name \'" + (yymsp[0].minor.yy0->data) + "\'"));
        pGen->namedef(yymsp[0].minor.yy0->data);
    }
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 895 "parser/epparser.c"
        break;
      case 7: /* expr ::= expr PLUS expr */
#line 101 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = " << yymsp[-2].minor.yy0->data << " + "  << yymsp[0].minor.yy0->data << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 900 "parser/epparser.c"
        break;
      case 8: /* expr ::= expr MINUS expr */
#line 102 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = " << yymsp[-2].minor.yy0->data << " - "  << yymsp[0].minor.yy0->data << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 905 "parser/epparser.c"
        break;
      case 9: /* expr ::= expr MULTIPLY expr */
#line 103 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = " << yymsp[-2].minor.yy0->data << " * "  << yymsp[0].minor.yy0->data << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 910 "parser/epparser.c"
        break;
      case 10: /* expr ::= expr DIVIDE expr */
#line 104 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = " << yymsp[-2].minor.yy0->data << " // " << yymsp[0].minor.yy0->data << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 915 "parser/epparser.c"
        break;
      case 11: /* expr ::= expr MOD expr */
#line 105 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = " << yymsp[-2].minor.yy0->data << " % "  << yymsp[0].minor.yy0->data << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 920 "parser/epparser.c"
        break;
      case 12: /* expr ::= expr LSHIFT expr */
#line 106 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = " << yymsp[-2].minor.yy0->data << " << " << yymsp[0].minor.yy0->data << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 925 "parser/epparser.c"
        break;
      case 13: /* expr ::= expr RSHIFT expr */
#line 107 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = " << yymsp[-2].minor.yy0->data << " >> " << yymsp[0].minor.yy0->data << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 930 "parser/epparser.c"
        break;
      case 14: /* expr ::= expr BITAND expr */
#line 108 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = " << yymsp[-2].minor.yy0->data << " & "  << yymsp[0].minor.yy0->data << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 935 "parser/epparser.c"
        break;
      case 15: /* expr ::= expr BITOR expr */
#line 109 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = " << yymsp[-2].minor.yy0->data << " | "  << yymsp[0].minor.yy0->data << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 940 "parser/epparser.c"
        break;
      case 16: /* expr ::= expr BITXOR expr */
#line 110 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = " << yymsp[-2].minor.yy0->data << " ^ "  << yymsp[0].minor.yy0->data << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 945 "parser/epparser.c"
        break;
      case 17: /* expr ::= PLUS expr */
#line 113 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = +" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 950 "parser/epparser.c"
        break;
      case 18: /* expr ::= MINUS expr */
#line 114 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = -" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 955 "parser/epparser.c"
        break;
      case 19: /* expr ::= BITNOT expr */
#line 115 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = ~" << yymsp[0].minor.yy0->data << std::endl; delete yymsp[0].minor.yy0; }
#line 960 "parser/epparser.c"
        break;
      case 20: /* lexpr ::= expr EQ expr */
#line 118 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = (" << yymsp[-2].minor.yy0->data << " == " << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 965 "parser/epparser.c"
        break;
      case 21: /* lexpr ::= expr NE expr */
#line 119 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = (" << yymsp[-2].minor.yy0->data << " != " << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 970 "parser/epparser.c"
        break;
      case 22: /* lexpr ::= expr LE expr */
#line 120 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = (" << yymsp[-2].minor.yy0->data << " <= " << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 975 "parser/epparser.c"
        break;
      case 23: /* lexpr ::= expr LT expr */
#line 121 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = (" << yymsp[-2].minor.yy0->data << " < "  << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 980 "parser/epparser.c"
        break;
      case 24: /* lexpr ::= expr GE expr */
#line 122 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = (" << yymsp[-2].minor.yy0->data << " >= " << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 985 "parser/epparser.c"
        break;
      case 25: /* lexpr ::= expr GT expr */
#line 123 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = (" << yymsp[-2].minor.yy0->data << " > "  << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 990 "parser/epparser.c"
        break;
      case 26: /* lexpr ::= lexpr LAND lexpr */
#line 125 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = [" << yymsp[-2].minor.yy0->data << ", " << yymsp[0].minor.yy0->data << "]" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 995 "parser/epparser.c"
        break;
      case 27: /* lexpr ::= lexpr LOR lexpr */
#line 126 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = EUDOr([" << yymsp[-2].minor.yy0->data << ", " << yymsp[0].minor.yy0->data << "])" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 1000 "parser/epparser.c"
        break;
      case 28: /* lexpr ::= LNOT lexpr */
#line 127 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(yymsp[0].minor.yy0); (*pGen) << yygotominor.yy0->data << " = EUDNot(" << yymsp[0].minor.yy0->data << ")" << std::endl; delete yymsp[0].minor.yy0; }
#line 1005 "parser/epparser.c"
        break;
      case 30: /* stmt_assignSingle ::= NAME ASSIGN expr SEMICOLON */
#line 131 "parser/epparser.lemon"
{
    (*pGen) << yymsp[-3].minor.yy0->data << " << " << yymsp[-1].minor.yy0->data << std::endl;
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1013 "parser/epparser.c"
        break;
      case 31: /* stmt_assignMulti ::= nameList ASSIGN exprList SEMICOLON */
#line 136 "parser/epparser.lemon"
{
    (*pGen) << "SetVariables([" << yymsp[-3].minor.yy0->data << "], [" << yymsp[-1].minor.yy0->data << "])" << std::endl;
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1021 "parser/epparser.c"
        break;
      case 35: /* block ::= LBRACKET error RBRACKET */
#line 146 "parser/epparser.lemon"
{
    throw_error(yymsp[0].minor.yy0->line, 6974, "General syntax error");
}
#line 1028 "parser/epparser.c"
        break;
      case 36: /* if_start ::= IF */
#line 152 "parser/epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    (*pGen) << yygotominor.yy0->data << " = Forward()" << std::endl;
}
#line 1036 "parser/epparser.c"
        break;
      case 37: /* if_header ::= if_start LPAREN lexpr RPAREN */
#line 156 "parser/epparser.lemon"
{
    (*pGen) << "EUDJumpIfNot(" << yymsp[-1].minor.yy0->data << ", " << yymsp[-3].minor.yy0->data << ")" << std::endl;
    yygotominor.yy0 = yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 1044 "parser/epparser.c"
        break;
      case 38: /* if_stmt ::= if_header stmt */
      case 40: /* if_stmt ::= else_header stmt */ yytestcase(yyruleno==40);
#line 161 "parser/epparser.lemon"
{
    (*pGen) << yymsp[-1].minor.yy0->data << " << NextTrigger()" << std::endl;
    delete yymsp[-1].minor.yy0;
}
#line 1053 "parser/epparser.c"
        break;
      case 39: /* else_header ::= if_header stmt ELSE */
#line 166 "parser/epparser.lemon"
{
    yygotominor.yy0 = genTemp(yymsp[0].minor.yy0);
    (*pGen) << yygotominor.yy0->data << " = Forward()" << std::endl;
    (*pGen) << "EUDJump(" << yygotominor.yy0->data << ")" << std::endl;
    (*pGen) << yymsp[-2].minor.yy0->data << " << NextTrigger()" << std::endl;
    delete yymsp[-2].minor.yy0;
}
#line 1064 "parser/epparser.c"
        break;
      case 41: /* while_start ::= WHILE */
#line 181 "parser/epparser.lemon"
{
    auto lbegin = genTemp(yymsp[0].minor.yy0);
    auto lend = genTemp(yymsp[0].minor.yy0);
    lblocks.push_back({lbegin->data, lbegin->data, lend->data});

    (*pGen) << lbegin->data << " = NextTrigger()" << std::endl;
    (*pGen) << lend->data << " = Forward()" << std::endl;
    yygotominor.yy0 = lbegin;
    delete yymsp[0].minor.yy0;
}
#line 1078 "parser/epparser.c"
        break;
      case 42: /* while_cond ::= LPAREN lexpr RPAREN */
#line 192 "parser/epparser.lemon"
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
#line 1092 "parser/epparser.c"
        break;
      case 43: /* while_stmt ::= while_start while_cond stmt */
#line 203 "parser/epparser.lemon"
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
#line 1107 "parser/epparser.c"
        break;
      case 44: /* continue_stmt ::= CONTINUE SEMICOLON */
#line 216 "parser/epparser.lemon"
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
#line 1121 "parser/epparser.c"
        break;
      case 45: /* break_stmt ::= BREAK SEMICOLON */
#line 227 "parser/epparser.lemon"
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
#line 1135 "parser/epparser.c"
        break;
      case 46: /* stmt ::= error SEMICOLON */
#line 240 "parser/epparser.lemon"
{ throw_error(yymsp[0].minor.yy0->line, 6974, "General syntax error"); }
#line 1140 "parser/epparser.c"
        break;
      default:
      /* (0) program ::= stmt */ yytestcase(yyruleno==0);
      /* (32) stmtList ::= stmt */ yytestcase(yyruleno==32);
      /* (33) stmtList ::= stmtList stmt */ yytestcase(yyruleno==33);
      /* (34) block ::= LBRACKET stmtList RBRACKET */ yytestcase(yyruleno==34);
      /* (47) stmt ::= expr SEMICOLON */ yytestcase(yyruleno==47);
      /* (48) stmt ::= stmt_assignMulti */ yytestcase(yyruleno==48);
      /* (49) stmt ::= stmt_assignSingle */ yytestcase(yyruleno==49);
      /* (50) stmt ::= if_stmt */ yytestcase(yyruleno==50);
      /* (51) stmt ::= while_stmt */ yytestcase(yyruleno==51);
      /* (52) stmt ::= continue_stmt */ yytestcase(yyruleno==52);
      /* (53) stmt ::= break_stmt */ yytestcase(yyruleno==53);
      /* (54) stmt ::= block */ yytestcase(yyruleno==54);
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
#line 1217 "parser/epparser.c"
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
#line 251 "parser/epparser.lemon"

std::string ParseString(const std::string& code)
{
    std::istringstream is(code);
    Tokenizer tok(is);
    void* pParser = ParseAlloc (malloc);
    PyGenerator pGen;
    Token* token;

    tmpIndex = 1;
    errorOccured = false;
    while((token = tok.getToken()) != nullptr) {
        if(tokenTypeConv(token)) Parse (pParser, token->type, token, &pGen);
        else {
            throw_error(token->line, 8104, "Invalid token");
        }
    }
    Parse (pParser, 0, nullptr, &pGen);
    ParseFree(pParser, free );

    if(!errorOccured) return pGen.str();
    else throw std::runtime_error("Invalid syntax");
}
#line 1432 "parser/epparser.c"
