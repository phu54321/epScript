#include "../../parser/parser.h"
#include "../../utils.h"
#include "../catch.hpp"
#include <stdexcept>
#include <string.h>
#include <vector>
#include "test_parser.hpp"


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
