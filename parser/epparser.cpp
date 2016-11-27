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

std::string* genTemp() {
    static char output[20] = "_t";
    sprintf(output, "_t%d", tmpIndex++);
    return new std::string(output);
}

void throw_error(int code, const std::string& message) {
    std::cout << "[Error " << code << "] " << message << std::endl;
}

#line 32 "parser/epparser.c"
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
#define YYNOCODE 45
#define YYACTIONTYPE unsigned char
#define ParseTOKENTYPE std::string*
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL  PyGenerator* pGen ;
#define ParseARG_PDECL , PyGenerator* pGen 
#define ParseARG_FETCH  PyGenerator* pGen  = yypParser->pGen 
#define ParseARG_STORE yypParser->pGen  = pGen 
#define YYNSTATE 77
#define YYNRULE 40
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
 /*     0 */     9,   25,   24,   22,   14,   26,   18,   19,   17,   15,
 /*    10 */    16,   11,    8,   12,   28,   13,   11,    8,   12,   28,
 /*    20 */    13,   33,   55,    9,   25,   24,   22,   14,   26,   18,
 /*    30 */    19,   17,   15,   16,   11,    8,   12,   28,   13,   18,
 /*    40 */    19,   17,   15,   16,   11,    8,   12,   28,   13,   12,
 /*    50 */    28,   13,    3,   27,   61,   71,   18,   19,   17,   15,
 /*    60 */    16,   11,    8,   12,   28,   13,    5,   70,   30,   57,
 /*    70 */    19,   17,   15,   16,   11,    8,   12,   28,   13,   20,
 /*    80 */    21,   68,   30,   62,   30,   60,  119,   49,   59,   23,
 /*    90 */    77,    1,   65,   63,   47,   32,   29,   50,   67,   66,
 /*   100 */     2,   69,   30,   54,   45,  118,   53,   47,   40,   29,
 /*   110 */    50,   67,   66,    5,   69,   17,   15,   16,   11,    8,
 /*   120 */    12,   28,   13,   48,   37,  119,   20,   21,   52,    7,
 /*   130 */    51,   10,   31,   34,   49,   59,   23,   35,    1,    6,
 /*   140 */     3,   64,   47,   42,   29,   50,   67,   66,    5,   69,
 /*   150 */    73,   15,   16,   11,    8,   12,   28,   13,   44,    4,
 /*   160 */    46,   20,   21,   72,  119,  119,   20,   21,   43,   58,
 /*   170 */    59,   23,   20,   21,   58,   59,   23,   74,   36,   38,
 /*   180 */    58,   59,   23,   75,   41,   39,  119,   56,   76,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */     7,    8,    9,   10,   11,   12,   13,   14,   15,   16,
 /*    10 */    17,   18,   19,   20,   21,   22,   18,   19,   20,   21,
 /*    20 */    22,   38,   29,    7,    8,    9,   10,   11,   12,   13,
 /*    30 */    14,   15,   16,   17,   18,   19,   20,   21,   22,   13,
 /*    40 */    14,   15,   16,   17,   18,   19,   20,   21,   22,   20,
 /*    50 */    21,   22,    4,    1,   26,   29,   13,   14,   15,   16,
 /*    60 */    17,   18,   19,   20,   21,   22,    5,   26,   38,   39,
 /*    70 */    14,   15,   16,   17,   18,   19,   20,   21,   22,   18,
 /*    80 */    19,   29,   38,   39,   38,   39,   44,   26,   27,   28,
 /*    90 */     0,   30,   31,   35,   36,   38,   38,   39,   40,   41,
 /*   100 */    42,   43,   38,   39,   38,   34,   35,   36,   38,   38,
 /*   110 */    39,   40,   41,    5,   43,   15,   16,   17,   18,   19,
 /*   120 */    20,   21,   22,   37,   38,   44,   18,   19,    1,    2,
 /*   130 */     1,    2,   38,   38,   26,   27,   28,   38,   30,    3,
 /*   140 */     4,   35,   36,   38,   38,   39,   40,   41,    5,   43,
 /*   150 */    38,   16,   17,   18,   19,   20,   21,   22,   38,    5,
 /*   160 */    38,   18,   19,   38,   44,   44,   18,   19,   38,   26,
 /*   170 */    27,   28,   18,   19,   26,   27,   28,   38,   38,   38,
 /*   180 */    26,   27,   28,   38,   38,   38,   44,   38,   38,
};
#define YY_SHIFT_USE_DFLT (-8)
#define YY_SHIFT_MAX 54
static const short yy_shift_ofst[] = {
 /*     0 */   108,  108,   61,  143,  154,  154,  143,  148,  148,  148,
 /*    10 */   148,  148,  148,  148,  148,  148,  148,  148,  148,  148,
 /*    20 */   148,  148,  148,  148,  148,  148,  148,  148,  148,   -7,
 /*    30 */    16,   26,   43,   43,   43,   43,   43,   43,   43,   43,
 /*    40 */    56,  100,  135,   -2,   -2,   29,   29,  127,   52,  129,
 /*    50 */   136,   28,   41,   90,   48,
};
#define YY_REDUCE_USE_DFLT (-18)
#define YY_REDUCE_MAX 28
static const short yy_reduce_ofst[] = {
 /*     0 */    71,   58,  106,   30,   44,   46,   64,   86,  122,   99,
 /*    10 */    94,   66,  150,  145,  140,  130,  120,  105,   70,  146,
 /*    20 */   139,  112,   57,  125,  141,   95,  -17,  147,  149,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   117,  117,  117,  117,  117,  117,  117,  117,  117,  117,
 /*    10 */   117,  117,  117,  117,  117,  117,  117,  117,  117,  117,
 /*    20 */   117,  117,  117,  117,  117,  117,  117,  117,  117,  117,
 /*    30 */   117,  117,  101,   98,   99,   97,  102,   80,  100,   81,
 /*    40 */    92,   93,   91,   89,   90,   84,   85,  117,  117,   83,
 /*    50 */   115,  117,  117,  117,  104,  112,   86,  103,   83,   82,
 /*    60 */   105,   78,  106,  109,  110,  111,  113,  114,  108,  116,
 /*    70 */    79,  107,   96,   95,   94,   88,   87,
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
  "IFX",           "ELSE",          "NAME",          "NUMBER",      
  "BITNOT",        "SEMICOLON",     "LBRACKET",      "RBRACKET",    
  "error",         "nt",            "program",       "stmt",        
  "nameList",      "exprList",      "expr",          "lexpr",       
  "stmt_assignSingle",  "stmt_assignMulti",  "stmtList",      "multilineBlock",
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
 /*  34 */ "multilineBlock ::= LBRACKET stmtList RBRACKET",
 /*  35 */ "stmt ::= expr SEMICOLON",
 /*  36 */ "stmt ::= stmt_assignMulti",
 /*  37 */ "stmt ::= stmt_assignSingle",
 /*  38 */ "stmt ::= lexpr",
 /*  39 */ "stmt ::= multilineBlock",
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
    case 33: /* nt */
{
#line 34 "parser/epparser.lemon"
 delete (yypminor->yy0); 
#line 468 "parser/epparser.c"
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
  { 34, 1 },
  { 36, 3 },
  { 36, 3 },
  { 37, 1 },
  { 37, 3 },
  { 38, 1 },
  { 38, 1 },
  { 38, 3 },
  { 38, 3 },
  { 38, 3 },
  { 38, 3 },
  { 38, 3 },
  { 38, 3 },
  { 38, 3 },
  { 38, 3 },
  { 38, 3 },
  { 38, 3 },
  { 38, 2 },
  { 38, 2 },
  { 38, 2 },
  { 39, 3 },
  { 39, 3 },
  { 39, 3 },
  { 39, 3 },
  { 39, 3 },
  { 39, 3 },
  { 39, 3 },
  { 39, 3 },
  { 39, 2 },
  { 39, 3 },
  { 40, 4 },
  { 41, 4 },
  { 42, 1 },
  { 42, 2 },
  { 43, 3 },
  { 35, 2 },
  { 35, 1 },
  { 35, 1 },
  { 35, 1 },
  { 35, 1 },
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
#line 63 "parser/epparser.lemon"
{ yygotominor.yy0 = new std::string((*yymsp[-2].minor.yy0) + ", " + (*yymsp[0].minor.yy0)); delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 796 "parser/epparser.c"
        break;
      case 3: /* exprList ::= expr */
      case 5: /* expr ::= NUMBER */ yytestcase(yyruleno==5);
      case 29: /* lexpr ::= LNOT LNOT lexpr */ yytestcase(yyruleno==29);
#line 65 "parser/epparser.lemon"
{ yygotominor.yy0 = yymsp[0].minor.yy0; }
#line 803 "parser/epparser.c"
        break;
      case 6: /* expr ::= NAME */
#line 70 "parser/epparser.lemon"
{
    if(pGen->undefined(*yymsp[0].minor.yy0)) {
        throw_error(103, ("Undefined name \'" + (*yymsp[0].minor.yy0) + "\'"));
        pGen->namedef(*yymsp[0].minor.yy0);
    }
    yygotominor.yy0 = yymsp[0].minor.yy0;
}
#line 814 "parser/epparser.c"
        break;
      case 7: /* expr ::= expr PLUS expr */
#line 79 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(); (*pGen) << *yygotominor.yy0 << " = " << *yymsp[-2].minor.yy0 << " + "  << *yymsp[0].minor.yy0 << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 819 "parser/epparser.c"
        break;
      case 8: /* expr ::= expr MINUS expr */
#line 80 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(); (*pGen) << *yygotominor.yy0 << " = " << *yymsp[-2].minor.yy0 << " - "  << *yymsp[0].minor.yy0 << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 824 "parser/epparser.c"
        break;
      case 9: /* expr ::= expr MULTIPLY expr */
#line 81 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(); (*pGen) << *yygotominor.yy0 << " = " << *yymsp[-2].minor.yy0 << " * "  << *yymsp[0].minor.yy0 << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 829 "parser/epparser.c"
        break;
      case 10: /* expr ::= expr DIVIDE expr */
#line 82 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(); (*pGen) << *yygotominor.yy0 << " = " << *yymsp[-2].minor.yy0 << " // " << *yymsp[0].minor.yy0 << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 834 "parser/epparser.c"
        break;
      case 11: /* expr ::= expr MOD expr */
#line 83 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(); (*pGen) << *yygotominor.yy0 << " = " << *yymsp[-2].minor.yy0 << " % "  << *yymsp[0].minor.yy0 << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 839 "parser/epparser.c"
        break;
      case 12: /* expr ::= expr LSHIFT expr */
#line 84 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(); (*pGen) << *yygotominor.yy0 << " = " << *yymsp[-2].minor.yy0 << " << " << *yymsp[0].minor.yy0 << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 844 "parser/epparser.c"
        break;
      case 13: /* expr ::= expr RSHIFT expr */
#line 85 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(); (*pGen) << *yygotominor.yy0 << " = " << *yymsp[-2].minor.yy0 << " >> " << *yymsp[0].minor.yy0 << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 849 "parser/epparser.c"
        break;
      case 14: /* expr ::= expr BITAND expr */
#line 86 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(); (*pGen) << *yygotominor.yy0 << " = " << *yymsp[-2].minor.yy0 << " & "  << *yymsp[0].minor.yy0 << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 854 "parser/epparser.c"
        break;
      case 15: /* expr ::= expr BITOR expr */
#line 87 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(); (*pGen) << *yygotominor.yy0 << " = " << *yymsp[-2].minor.yy0 << " | "  << *yymsp[0].minor.yy0 << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 859 "parser/epparser.c"
        break;
      case 16: /* expr ::= expr BITXOR expr */
#line 88 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(); (*pGen) << *yygotominor.yy0 << " = " << *yymsp[-2].minor.yy0 << " ^ "  << *yymsp[0].minor.yy0 << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 864 "parser/epparser.c"
        break;
      case 17: /* expr ::= PLUS expr */
#line 91 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(); (*pGen) << *yygotominor.yy0 << " = +" << *yymsp[0].minor.yy0 << std::endl; delete yymsp[0].minor.yy0; }
#line 869 "parser/epparser.c"
        break;
      case 18: /* expr ::= MINUS expr */
#line 92 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(); (*pGen) << *yygotominor.yy0 << " = -" << *yymsp[0].minor.yy0 << std::endl; delete yymsp[0].minor.yy0; }
#line 874 "parser/epparser.c"
        break;
      case 19: /* expr ::= BITNOT expr */
#line 93 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(); (*pGen) << *yygotominor.yy0 << " = ~" << *yymsp[0].minor.yy0 << std::endl; delete yymsp[0].minor.yy0; }
#line 879 "parser/epparser.c"
        break;
      case 20: /* lexpr ::= expr EQ expr */
#line 96 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(); (*pGen) << *yygotominor.yy0 << " = (" << *yymsp[-2].minor.yy0 << " == " << *yymsp[0].minor.yy0 << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 884 "parser/epparser.c"
        break;
      case 21: /* lexpr ::= expr NE expr */
#line 97 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(); (*pGen) << *yygotominor.yy0 << " = (" << *yymsp[-2].minor.yy0 << " != " << *yymsp[0].minor.yy0 << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 889 "parser/epparser.c"
        break;
      case 22: /* lexpr ::= expr LE expr */
#line 98 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(); (*pGen) << *yygotominor.yy0 << " = (" << *yymsp[-2].minor.yy0 << " <= " << *yymsp[0].minor.yy0 << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 894 "parser/epparser.c"
        break;
      case 23: /* lexpr ::= expr LT expr */
#line 99 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(); (*pGen) << *yygotominor.yy0 << " = (" << *yymsp[-2].minor.yy0 << " < "  << *yymsp[0].minor.yy0 << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 899 "parser/epparser.c"
        break;
      case 24: /* lexpr ::= expr GE expr */
#line 100 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(); (*pGen) << *yygotominor.yy0 << " = (" << *yymsp[-2].minor.yy0 << " >= " << *yymsp[0].minor.yy0 << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 904 "parser/epparser.c"
        break;
      case 25: /* lexpr ::= expr GT expr */
#line 101 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(); (*pGen) << *yygotominor.yy0 << " = (" << *yymsp[-2].minor.yy0 << " > "  << *yymsp[0].minor.yy0 << ")" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 909 "parser/epparser.c"
        break;
      case 26: /* lexpr ::= lexpr LAND lexpr */
#line 103 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(); (*pGen) << *yygotominor.yy0 << " = [" << *yymsp[-2].minor.yy0 << ", " << *yymsp[0].minor.yy0 << "]" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 914 "parser/epparser.c"
        break;
      case 27: /* lexpr ::= lexpr LOR lexpr */
#line 104 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(); (*pGen) << *yygotominor.yy0 << " = EUDOr([" << *yymsp[-2].minor.yy0 << ", " << *yymsp[0].minor.yy0 << "])" << std::endl; delete yymsp[-2].minor.yy0; delete yymsp[0].minor.yy0; }
#line 919 "parser/epparser.c"
        break;
      case 28: /* lexpr ::= LNOT lexpr */
#line 105 "parser/epparser.lemon"
{ yygotominor.yy0 = genTemp(); (*pGen) << *yygotominor.yy0 << " = EUDNot(" << *yymsp[0].minor.yy0 << ")" << std::endl; delete yymsp[0].minor.yy0; }
#line 924 "parser/epparser.c"
        break;
      case 30: /* stmt_assignSingle ::= NAME ASSIGN expr SEMICOLON */
#line 109 "parser/epparser.lemon"
{
    (*pGen) << *yymsp[-3].minor.yy0 << " << " << *yymsp[-1].minor.yy0 << std::endl;
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 932 "parser/epparser.c"
        break;
      case 31: /* stmt_assignMulti ::= nameList ASSIGN exprList SEMICOLON */
#line 114 "parser/epparser.lemon"
{
    (*pGen) << "SetVariables([" << *yymsp[-3].minor.yy0 << "], [" << *yymsp[-1].minor.yy0 << "])" << std::endl;
    delete yymsp[-3].minor.yy0; delete yymsp[-1].minor.yy0;
}
#line 940 "parser/epparser.c"
        break;
      default:
      /* (0) program ::= stmt */ yytestcase(yyruleno==0);
      /* (32) stmtList ::= stmt */ yytestcase(yyruleno==32);
      /* (33) stmtList ::= stmtList stmt */ yytestcase(yyruleno==33);
      /* (34) multilineBlock ::= LBRACKET stmtList RBRACKET */ yytestcase(yyruleno==34);
      /* (35) stmt ::= expr SEMICOLON */ yytestcase(yyruleno==35);
      /* (36) stmt ::= stmt_assignMulti */ yytestcase(yyruleno==36);
      /* (37) stmt ::= stmt_assignSingle */ yytestcase(yyruleno==37);
      /* (38) stmt ::= lexpr */ yytestcase(yyruleno==38);
      /* (39) stmt ::= multilineBlock */ yytestcase(yyruleno==39);
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
#line 26 "parser/epparser.lemon"

    printf("Syntax error!\n");
#line 1014 "parser/epparser.c"
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
#line 141 "parser/epparser.lemon"

std::string ParseString(const std::string& code)
{
    std::istringstream is(code);
    Tokenizer tok(is);
    void* pParser = ParseAlloc (malloc);
    PyGenerator pGen;
    TokenPtr token;

    tmpIndex = 1;
    while((token = tok.getToken()) != nullptr) {
        int tokenType = tokenTypeConv(token->type);
        Parse (pParser, tokenType, new std::string(token->data), &pGen);
    }
    Parse (pParser, 0, nullptr, &pGen);
    ParseFree(pParser, free );
    return pGen.str();
}
#line 1224 "parser/epparser.c"
