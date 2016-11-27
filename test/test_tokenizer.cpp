#include "doctest.hpp"
#include "../parser/tokenizer.h"
#include <sstream>

TEST_CASE("Tokenizing arithmetic operators") {
    std::stringstream test_input("+-*/");
    Tokenizer tok(test_input);
    REQUIRE(tok.getToken()->type == TOKEN_PLUS);
    REQUIRE(tok.getToken()->type == TOKEN_MINUS);
    REQUIRE(tok.getToken()->type == TOKEN_MULTIPLY);
    REQUIRE(tok.getToken()->type == TOKEN_DIVIDE);
    REQUIRE(tok.getToken() == nullptr);
}
