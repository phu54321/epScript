#include "parserUtilities.h"
#include "tokenizer/tokenizer.h"

extern int currentTokenizingLine;
const int LENGTH_LIMIT = 60;

Token* genEmpty() {
    return new Token(TOKEN_TEMP, currentTokenizingLine);
}


int tmpIndex = 0;
Token* genTemp(Token* lineSrc) {
    static char output[20] = "_t";
    sprintf(output, "_t%d", tmpIndex++);
    return new Token(output, lineSrc);
}

Token* mkTokenTemp(Token* a) {
    if(a->data.size() > LENGTH_LIMIT) {
        Token* t = genTemp(a);
        (*pGen) << t->data << " = " << a->data << std::endl;
        delete a;
        return t;
    }
    else {
        a->type = TOKEN_TEMP;
        return a;
    }
}

Token* binaryMerge(Token* a, const std::string& opstr, Token* b) {
    b->data = a->data + (" " + opstr + " ") + b->data;
    delete a;
    return mkTokenTemp(b);
}

////
