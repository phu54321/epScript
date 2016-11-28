//
// Created by 박현우 on 2016. 11. 27..
//

#include "tokIndent.h"
#include "../../test/doctest.hpp"
#include <stdexcept>

TokIndent::TokIndent() : currentIndent(0) {
    indentStacks.push_back(0);
}

TokIndent::~TokIndent() {}

bool TokIndent::setCurrentLineIndent(int indent) {
    if (indent < 0) throw std::domain_error("Negative indent");
    int prevIndent = getLastIndentLevel();
    if(prevIndent != currentIndent) throw std::logic_error("Previous indentation not yet resolved");

    // Ignore if this is invalid indentation
    currentIndent = indent;

    // Unindent needed -> check invalid unindentation
    if(currentIndent < prevIndent) {
        for (auto itr = indentStacks.rbegin(); itr != indentStacks.rend(); itr++) {
            if (*itr == currentIndent) break;
            else if (*itr < currentIndent) {  // Indentation error.
                currentIndent = prevIndent;  // Revert to previous indent setting
                return false;
            }
        }
    }
    return true;
}

int TokIndent::remainingIndentTokens() const {
    int prevIndent = getLastIndentLevel();
    if(prevIndent == currentIndent) return 0;
    else if (prevIndent < currentIndent) return 1; // Should indent
    else {
        int matchingIndentDepth = 0;
        for (auto itr = indentStacks.rbegin() ; itr != indentStacks.rend() ; itr++, matchingIndentDepth++) {
            if(*itr == currentIndent) return -matchingIndentDepth;
            else if(*itr < currentIndent) {  // Indentation error.
                throw std::logic_error("Indentation error");
            }
        }
        throw std::runtime_error("Unexpected Error");
    }
}

void TokIndent::indent() {
    if (currentIndent <= getLastIndentLevel()) {
        throw std::logic_error("Indenting over allowed range");
    }
    indentStacks.push_back(currentIndent);
}

void TokIndent::unindent() {
    if (currentIndent >= getLastIndentLevel()) {
        throw std::logic_error("Unindenting under allowed range");
    }
    indentStacks.pop_back();
}

int TokIndent::getLastIndentLevel() const {
    return indentStacks[indentStacks.size() - 1];
}


TEST_CASE("Indent use case") {
    TokIndent indenter;

    REQUIRE_THROWS_AS(indenter.setCurrentLineIndent(-1), std::domain_error);


    indenter.setCurrentLineIndent(4);
            REQUIRE(indenter.remainingIndentTokens() > 0);
    indenter.indent();
            REQUIRE(indenter.remainingIndentTokens() == 0);
            REQUIRE_THROWS_AS(indenter.indent(), std::logic_error);  // Indenting occur.

    indenter.setCurrentLineIndent(4);
            REQUIRE(indenter.remainingIndentTokens() == 0);

    indenter.setCurrentLineIndent(8);
            REQUIRE(indenter.remainingIndentTokens() > 0);
    indenter.indent();
            REQUIRE(indenter.remainingIndentTokens() == 0);

    indenter.setCurrentLineIndent(0);
            REQUIRE(indenter.remainingIndentTokens() < 0);
            REQUIRE_THROWS_AS(indenter.setCurrentLineIndent(4), std::logic_error);  // Indent is not yet resolved.
    indenter.unindent();
            REQUIRE(indenter.remainingIndentTokens() < 0);
    indenter.unindent();
            REQUIRE(indenter.remainingIndentTokens() == 0);
}
