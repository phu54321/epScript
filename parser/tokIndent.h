//
// Created by 박현우 on 2016. 11. 27..
//

#ifndef EPSCRIPT_TOKINDENT_H
#define EPSCRIPT_TOKINDENT_H

#include <vector>

class TokIndent {
public:
    TokIndent();
    ~TokIndent();

    /// Set indentation level of current line
    /// \param indent Intentation level
    /// \return True if specified indentation is allowed
    bool setCurrentLineIndent(int indent);

    /// Remaining indents to do
    /// \return Positive if should indent, Negative if should unindent, Zero if should not
    int remainingIndentTokens() const;

    /// Does indent
    void indent();

    /// Does unindent
    void unindent();

private:
    int getLastIndentLevel() const;
    std::vector<int> indentStacks;
    int currentIndent;
};

#endif //EPSCRIPT_TOKINDENT_H
