#include "../parser/tokenizer/tokenizer.h"
#include <sstream>
#include "doctest.hpp"

TEST_SUITE("Basic tokenization");
TEST_CASE("Tokenizing arithmetic operators") {
    std::stringstream test_input("+-*/");
    Tokenizer tok(test_input);
            REQUIRE(tok.getToken()->type == TOKEN_PLUS);
            REQUIRE(tok.getToken()->type == TOKEN_MINUS);
            REQUIRE(tok.getToken()->type == TOKEN_MULTIPLY);
            REQUIRE(tok.getToken()->type == TOKEN_DIVIDE);
            REQUIRE(tok.getToken() == nullptr);
}


TEST_CASE("Tokenizing comparison operators") {
    std::stringstream test_input("==!=<=>=<>");
    Tokenizer tok(test_input);
            REQUIRE(tok.getToken()->type == TOKEN_EQ);
            REQUIRE(tok.getToken()->type == TOKEN_NE);
            REQUIRE(tok.getToken()->type == TOKEN_LE);
            REQUIRE(tok.getToken()->type == TOKEN_GE);
            REQUIRE(tok.getToken()->type == TOKEN_LT);
            REQUIRE(tok.getToken()->type == TOKEN_GT);
            REQUIRE(tok.getToken() == nullptr);
}

TEST_CASE("Tokenizing brackets") {
    std::stringstream test_input("()[]");
    Tokenizer tok(test_input);
            REQUIRE(tok.getToken()->type == TOKEN_LPAREN);
            REQUIRE(tok.getToken()->type == TOKEN_RPAREN);
            REQUIRE(tok.getToken()->type == TOKEN_LSQBRACKET);
            REQUIRE(tok.getToken()->type == TOKEN_RSQBRACKET);
            REQUIRE(tok.getToken() == nullptr);
}


TEST_CASE("Tokenizing names") {
    std::stringstream test_input("forvar test var for function if elif else while break continue v1");
    Tokenizer tok(test_input);
            REQUIRE(tok.getToken()->data == "forvar");  // forvar
            REQUIRE(tok.getToken()->data == "test");  // test
            REQUIRE(tok.getToken()->type == TOKEN_VAR);  // var
            REQUIRE(tok.getToken()->type == TOKEN_FOR);  // for
            REQUIRE(tok.getToken()->type == TOKEN_FUNCTION);  // function
            REQUIRE(tok.getToken()->type == TOKEN_IF);  // if
            REQUIRE(tok.getToken()->type == TOKEN_ELIF);  // elif
            REQUIRE(tok.getToken()->type == TOKEN_ELSE);  // else
            REQUIRE(tok.getToken()->type == TOKEN_WHILE);  // while
            REQUIRE(tok.getToken()->type == TOKEN_BREAK);  // break
            REQUIRE(tok.getToken()->type == TOKEN_CONTINUE);  // continue
            REQUIRE(tok.getToken()->type == TOKEN_NAME);  // v1
            REQUIRE(tok.getToken() == nullptr);  // v1
}

TEST_CASE("Tokenizing mixed names/operators") {
    std::stringstream test_input("var v1 = a + b");
    Tokenizer tok(test_input);
            REQUIRE(tok.getToken()->type == TOKEN_VAR);
            REQUIRE(tok.getToken()->data == "v1");
            REQUIRE(tok.getToken()->type == TOKEN_ASSIGN);
            REQUIRE(tok.getToken()->data == "a");
            REQUIRE(tok.getToken()->type == TOKEN_PLUS);
            REQUIRE(tok.getToken()->data == "b");
            REQUIRE(tok.getToken() == nullptr);
}


TEST_CASE("Tokenizing complex operators") {
    std::stringstream test_input("(a & b) || (c ^ b) && x + y[]");
    Tokenizer tok(test_input);
            REQUIRE(tok.getToken()->data == "(");
            REQUIRE(tok.getToken()->data == "a");
            REQUIRE(tok.getToken()->data == "&");
            REQUIRE(tok.getToken()->data == "b");
            REQUIRE(tok.getToken()->data == ")");
            REQUIRE(tok.getToken()->data == "||");
            REQUIRE(tok.getToken()->data == "(");
            REQUIRE(tok.getToken()->data == "c");
            REQUIRE(tok.getToken()->data == "^");
            REQUIRE(tok.getToken()->data == "b");
            REQUIRE(tok.getToken()->data == ")");
            REQUIRE(tok.getToken()->data == "&&");
            REQUIRE(tok.getToken()->data == "x");
            REQUIRE(tok.getToken()->data == "+");
            REQUIRE(tok.getToken()->data == "y");
            REQUIRE(tok.getToken()->data == "[");
            REQUIRE(tok.getToken()->data == "]");
            REQUIRE(tok.getToken() == nullptr);
}

TEST_CASE("Tokenizing numbers") {
    std::stringstream test_input("0x123 + 456");
    Tokenizer tok(test_input);
            REQUIRE(tok.getToken()->data == "0x123");
            REQUIRE(tok.getToken()->type == TOKEN_PLUS);
            REQUIRE(tok.getToken()->data == "456");
            REQUIRE(tok.getToken() == nullptr);
}

TEST_CASE("Brackets") {
    std::stringstream test_input(
            "a { \n"
                    "   b {\n"
                    "       c\n"
                    "   }\n"
                    "   d\n"
                    "   e {\n"
                    "       f\n"
                    "   }\n"
                    "}\n"
                    "g\n"
    );
    Tokenizer tok(test_input);
            REQUIRE(tok.getToken()->data == "a");
            REQUIRE(tok.getToken()->type == TOKEN_LBRACKET);
            REQUIRE(tok.getToken()->data == "b");
            REQUIRE(tok.getToken()->type == TOKEN_LBRACKET);
            REQUIRE(tok.getToken()->data == "c");
            REQUIRE(tok.getToken()->type == TOKEN_RBRACKET);
            REQUIRE(tok.getToken()->data == "d");
            REQUIRE(tok.getToken()->data == "e");
            REQUIRE(tok.getToken()->type == TOKEN_LBRACKET);
            REQUIRE(tok.getToken()->data == "f");
            REQUIRE(tok.getToken()->type == TOKEN_RBRACKET);
            REQUIRE(tok.getToken()->type == TOKEN_RBRACKET);
            REQUIRE(tok.getToken()->data == "g");
            REQUIRE(tok.getToken() == nullptr);
}

TEST_SUITE_END();

