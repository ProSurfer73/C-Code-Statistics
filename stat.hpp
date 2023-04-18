#ifndef STAT_HPP
#define STAT_HPP

#include <string>


class Stat
{
public:
    Stat();

    void printResults() const;

    void analyseFile(std::string& filepath);

private:
    // to analyse a specific line of code
    void analyseLine(std::string& lineOfCode, bool headerFile);

    // Lines of code
    unsigned commentedLines;
    unsigned normalLines;
    unsigned emptyLines;

    // Instruction types
    unsigned declaration;
    unsigned affectation;
    unsigned nbInstructions;

    // Preprocessor instructions
    unsigned ifPrepr;
    unsigned ifdef;
    unsigned ifndef;
    unsigned undef;
    unsigned include;
    unsigned define;

    // Variable types
    unsigned integer;
    unsigned character;
    unsigned strCharacter;
    unsigned pointer;

    // Loops
    unsigned whileStatement;
    unsigned forStatement;

    // Conditions
    unsigned ifStatement;
    unsigned switchStatement;

    // Definitions
    unsigned fonction;
    unsigned typedefs;
    unsigned structure;
    unsigned unions;
};


#endif // STAT_HPP
