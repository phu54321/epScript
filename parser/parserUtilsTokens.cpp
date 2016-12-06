#include "parserUtilities.h"
#include "tokenizer/tokenizer.h"

extern int currentTokenizingLine;

void checkIsConstant(std::string& objName, int line) {
    // Python function should pass through.
    if(strncmp(objName.c_str(), "py_", 3) == 0) {
        objName = objName.substr(3);
        return;
    }

    if (!closure->getConstant(objName)) {
        if(closure->defConstant(objName)) {
            throw_error(8200, ("Undefined constant " + objName), line);
        }
        else {
            throw_error(553, ("Not a constant : " + objName), line);
        }
    }
}

void checkIsVariable(std::string& objName, int line) {
    // Python function should pass through.
    if(strncmp(objName.c_str(), "py_", 3) == 0) {
        objName = objName.substr(3);
        return;
    }

    if (!closure->getVariable(objName)) {
        if(closure->defVariable(objName)) {
            throw_error(9571, ("Undefined variable " + objName), line);
        }
        else {
            throw_error(7364, ("Not a variable : " + objName), line);
        }
    }
}

void checkIsFunction(std::string& objName, int line) {
    // Python function should pass through.
    if(strncmp(objName.c_str(), "py_", 3) == 0) {
        objName = objName.substr(3);
        return;
    }

    if (!closure->getFunction(objName)) {
        if(closure->defFunction(objName)) {
            throw_error(7041, ("Undefined function " + objName), line);
        }
        else {
            throw_error(3967, ("Not a function : " + objName), line);
        }
    }
}

void checkIsRValue(std::string& objName, int line) {
    if (!closure->getVariable(objName) && !closure->getConstant(objName)) {
        if(closure->defVariable(objName)) {
            throw_error(9571, ("Undefined rvalue " + objName + " : assuming as variable"), line);
        }
        else {
            throw_error(7364, ("Not an rvalue : " + objName), line);
        }
    }
}





////

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

Token* binopConcat(Token* a, const std::string& opstr, Token* b) {
    b->data = a->data + (" " + opstr + " ") + b->data;
    delete a;
    return mkTokenTemp(b);
}

Token* commaConcat(Token* a, Token* b) {
    b->data = a->data + ", " + b->data;
    delete a;
    return b;
}

std::string flatListGetter(const Token* t, TokenType astType) {
    if(t->type == astType) {
        return (
                flatListGetter(t->subToken[0], astType) +
                ", " +
                flatListGetter(t->subToken[1], astType)
        );
    }
    else return t->data;
}

////
