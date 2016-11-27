#include "../parser/tokenizer/tokenizer.h"
#include <sstream>
#include "doctest.hpp"

TEST_SUITE("Basic tokenization");
TEST_CASE("Tokenizing arithmetic operators") {
    std::stringstream test_input("+-*/");
    Tokenizer tok(test_input);
            REQUIRE(tok.getToken()->type == PLUS);
            REQUIRE(tok.getToken()->type == MINUS);
            REQUIRE(tok.getToken()->type == MULTIPLY);
            REQUIRE(tok.getToken()->type == DIVIDE);
            REQUIRE(tok.getToken() == nullptr);
}


TEST_CASE("Tokenizing comparison operators") {
    std::stringstream test_input("==!=<=>=<>");
    Tokenizer tok(test_input);
            REQUIRE(tok.getToken()->type == EQ);
            REQUIRE(tok.getToken()->type == NE);
            REQUIRE(tok.getToken()->type == LE);
            REQUIRE(tok.getToken()->type == GE);
            REQUIRE(tok.getToken()->type == LT);
            REQUIRE(tok.getToken()->type == GT);
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
            REQUIRE(tok.getToken()->dataString == "forvar");  // forvar
            REQUIRE(tok.getToken()->dataString == "test");  // test
            REQUIRE(tok.getToken()->type == VAR);  // var
            REQUIRE(tok.getToken()->type == FOR);  // for
            REQUIRE(tok.getToken()->type == FUNCTION);  // function
            REQUIRE(tok.getToken()->type == IF);  // if
            REQUIRE(tok.getToken()->type == ELIF);  // elif
            REQUIRE(tok.getToken()->type == ELSE);  // else
            REQUIRE(tok.getToken()->type == WHILE);  // while
            REQUIRE(tok.getToken()->type == BREAK);  // break
            REQUIRE(tok.getToken()->type == CONTINUE);  // continue
            REQUIRE(tok.getToken()->type == NAME);  // v1
            REQUIRE(tok.getToken() == nullptr);  // v1
}

TEST_CASE("Tokenizing mixed names/operators") {
    std::stringstream test_input("var v1 = a + b");
    Tokenizer tok(test_input);
            REQUIRE(tok.getToken()->type == VAR);
            REQUIRE(tok.getToken()->dataString == "v1");
            REQUIRE(tok.getToken()->type == ASSIGN);
            REQUIRE(tok.getToken()->dataString == "a");
            REQUIRE(tok.getToken()->type == PLUS);
            REQUIRE(tok.getToken()->dataString == "b");
            REQUIRE(tok.getToken() == nullptr);
}


TEST_CASE("Tokenizing complex operators") {
    std::stringstream test_input("(a & b) || (c ^ b) && x + y[]");
    Tokenizer tok(test_input);
            REQUIRE(tok.getToken()->dataString == "(");
            REQUIRE(tok.getToken()->dataString == "a");
            REQUIRE(tok.getToken()->dataString == "&");
            REQUIRE(tok.getToken()->dataString == "b");
            REQUIRE(tok.getToken()->dataString == ")");
            REQUIRE(tok.getToken()->dataString == "||");
            REQUIRE(tok.getToken()->dataString == "(");
            REQUIRE(tok.getToken()->dataString == "c");
            REQUIRE(tok.getToken()->dataString == "^");
            REQUIRE(tok.getToken()->dataString == "b");
            REQUIRE(tok.getToken()->dataString == ")");
            REQUIRE(tok.getToken()->dataString == "&&");
            REQUIRE(tok.getToken()->dataString == "x");
            REQUIRE(tok.getToken()->dataString == "+");
            REQUIRE(tok.getToken()->dataString == "y");
            REQUIRE(tok.getToken()->dataString == "[");
            REQUIRE(tok.getToken()->dataString == "]");
            REQUIRE(tok.getToken() == nullptr);
}

TEST_CASE("Tokenizing numbers") {
    std::stringstream test_input("0x123 + 456");
    Tokenizer tok(test_input);
            REQUIRE(tok.getToken()->dataNumber == 0x123);
            REQUIRE(tok.getToken()->type == PLUS);
            REQUIRE(tok.getToken()->dataNumber == 456);
            REQUIRE(tok.getToken() == nullptr);
}

TEST_CASE("Indentation") {
    SUBCASE("Checking basic indentations") {
        std::stringstream test_input(
                "a\n"
                "   b\n"
                "       c\n"
                "   d\n"
                "   e\n"
                "       f\n"
                "g\n"
        );
        Tokenizer tok(test_input);
                REQUIRE(tok.getToken()->dataString == "a");
                REQUIRE(tok.getToken()->type == TOKEN_INDENT);
                REQUIRE(tok.getToken()->dataString == "b");
                REQUIRE(tok.getToken()->type == TOKEN_INDENT);
                REQUIRE(tok.getToken()->dataString == "c");
                REQUIRE(tok.getToken()->type == TOKEN_UNINDENT);
                REQUIRE(tok.getToken()->dataString == "d");
                REQUIRE(tok.getToken()->dataString == "e");
                REQUIRE(tok.getToken()->type == TOKEN_INDENT);
                REQUIRE(tok.getToken()->dataString == "f");
                REQUIRE(tok.getToken()->type == TOKEN_UNINDENT);
                REQUIRE(tok.getToken()->type == TOKEN_UNINDENT);
                REQUIRE(tok.getToken()->dataString == "g");
                REQUIRE(tok.getToken() == nullptr);
    }

    SUBCASE("Checking indentation after newline") {
        std::stringstream test_input(
                "a\n"
                "\n"
                "   b\n"
                "\n"
                "       c\n"
                "\n"
                "d\n"
        );
        Tokenizer tok(test_input);
                REQUIRE(tok.getToken()->dataString == "a");
                REQUIRE(tok.getToken()->type == TOKEN_INDENT);
                REQUIRE(tok.getToken()->dataString == "b");
                REQUIRE(tok.getToken()->type == TOKEN_INDENT);
                REQUIRE(tok.getToken()->dataString == "c");
                REQUIRE(tok.getToken()->type == TOKEN_UNINDENT);
                REQUIRE(tok.getToken()->type == TOKEN_UNINDENT);
                REQUIRE(tok.getToken()->dataString == "d");
                REQUIRE(tok.getToken() == nullptr);
    }

    SUBCASE("Checking invalid indentation") {
        std::stringstream test_input(
                "a\n"
                "\n"
                "   b\n"
                "\n"
                "       c\n"
                "\n"
                " d\n"
        );
        Tokenizer tok(test_input);
                REQUIRE(tok.getToken()->dataString == "a");
                REQUIRE(tok.getToken()->type == TOKEN_INDENT);
                REQUIRE(tok.getToken()->dataString == "b");
                REQUIRE(tok.getToken()->type == TOKEN_INDENT);
                REQUIRE(tok.getToken()->dataString == "c");
                REQUIRE(tok.getToken()->type == TOKEN_INVALIDINDENT);
                REQUIRE(tok.getToken() == nullptr);  // d line ignored
    }
}

TEST_SUITE_END();

