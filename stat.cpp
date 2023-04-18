#include <cstring>
#include <fstream>
#include <iostream>
#include <cctype>
#include <algorithm>
#include "stat.hpp"
#include "declaration.hpp"

static bool isBlank(char c)
{
    return (c==' '||c=='\t'||c==9);
}

static void removeSpaces(std::string& str)
{
    std::remove_if(str.begin(), str.end(), isspace);
}

static bool hasEnding(std::string const &fullString, std::string const &ending)
{
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

Stat::Stat()
{
    // Let's init all counters to zero.
    memset(this, 0, sizeof(*this));
}

void Stat::printResults() const
{
    std::cout << "commentedLines: " << commentedLines << std::endl;
    std::cout << "normalLines: " << normalLines << std::endl;
    std::cout << "emptyLines: " << emptyLines << std::endl;
    std::cout << "declaration: " << declaration << std::endl;
    std::cout << "affectation: " << affectation << std::endl;
    std::cout << "nbInstructions: " << nbInstructions << std::endl;
    std::cout << "#if: " << ifPrepr << std::endl;
    std::cout << "#ifdef: " << ifdef << std::endl;
    std::cout << "#ifndef: " << ifndef << std::endl;
    std::cout << "#undef: " << undef << std::endl;
    std::cout << "#include: " << include << std::endl;
    std::cout << "#define: " << define << std::endl;
    std::cout << "integer: " << integer << std::endl;
    std::cout << "strCharacter: " << strCharacter << std::endl;
    std::cout << "pointer: " << pointer << std::endl;
    std::cout << "whileStatement: " << whileStatement << std::endl;
    std::cout << "forStatement: " << forStatement << std::endl;
    std::cout << "ifStatement: " << ifStatement << std::endl;
    std::cout << "switchStatement: " << switchStatement << std::endl;
    std::cout << "fonction: " << fonction << std::endl;
    std::cout << "typedefs: " << typedefs << std::endl;
    std::cout << "structure: " << structure << std::endl;
    std::cout << "unions: " << unions << std::endl;
}

void Stat::analyseFile(std::string& filePath)
{
    std::ifstream file(filePath);

    std::string line;
    bool insideLongComment = false;

    // is this file a header file ?
    bool headerFile = hasEnding(filePath, ".h");

    // let's read the file line by line
    while(getline(file, line))
    {
        if(line.find("/*") != std::string::npos)
        {
            insideLongComment=true;
        }

        if(insideLongComment)
        {
            ++commentedLines;
        }

        if(insideLongComment && line.find("*/") != std::string::npos)
        {
            insideLongComment=false;
        }

        if(!insideLongComment)
        {
            analyseLine(line, headerFile);
        }
    }
}

void Stat::analyseLine(std::string& lineOfCode, bool headerFile)
{
    // If the line is a short comment
    if(lineOfCode.find("//") != std::string::npos)
    {
        ++commentedLines;

        // Let's delete the part of the line tha was commented
        lineOfCode = lineOfCode.substr(0, lineOfCode.find("//"));
    }

    // else it is a normal line of code
    else
    {
        // Let's check if the line is empty
        bool emptyLine = true;
        for(char c: lineOfCode){
            if(!isBlank(c))
                emptyLine = false;
        }
        if(emptyLine)
        {
            ++emptyLines;
            return;
        }


        // Let's remove all the spaces characters from the string
        std::string withoutSpaces = lineOfCode;
        removeSpaces(withoutSpaces);



        // If the line contains the character ; then it is an instruction.
        if(lineOfCode.find(';')!=std::string::npos && !headerFile)
            ++nbInstructions;

        std::string j = lineOfCode;
        removeSpaces(j);

        //------------
        // Preprocessor commands

        if(lineOfCode.find("#ifdef") != std::string::npos)
            ++ifdef;

        else if(lineOfCode.find("#ifndef") != std::string::npos)
            ++ifndef;

        else if(lineOfCode.find("#if") != std::string::npos)
            ++ifPrepr;

        else if(lineOfCode.find("#elif")!=std::string::npos)
        {}

        else if(j.find("if(") != std::string::npos)
            ++ifStatement;

        if(lineOfCode.find("#undef") != std::string::npos)
            ++undef;

        if(lineOfCode.find("#include") != std::string::npos)
            ++include;

        if(lineOfCode.find("#define") != std::string::npos)
            ++define;

        //----------------
        // Loop statements

        if(lineOfCode.find("while") != std::string::npos)
            ++whileStatement;

        else if(lineOfCode.find("for(") != std::string::npos
             || lineOfCode.find("for (") != std::string::npos)
            ++forStatement;

        //----------------
        // Conditions statements

        if(lineOfCode.find("switch") != std::string::npos)
            ++switchStatement;


        if(lineOfCode.find('=')!=std::string::npos
        // there must be a space or alphabet or numerical character just before
        &&(isspace(lineOfCode[lineOfCode.find('=')-1])||isalpha(lineOfCode[lineOfCode.find('=')-1]))
        // there must be space or alphabet or numerical character just after
        &&(isspace(lineOfCode[lineOfCode.find('=')+1])||isalpha(lineOfCode[lineOfCode.find('=')+1])))
            ++affectation;


        //----------------
        // Let's detect declaration of variables

        if(lineOfCode.find("typedef ")!=std::string::npos)
        {
            ++typedefs;
            return;
        }

        if(lineOfCode.find("union ")!=std::string::npos)
        {
            ++unions;
            return;
        }



        if(integerDeclaration(lineOfCode))
        {
            integer++;
            declaration++;
        }

        if(otherDeclaration(lineOfCode))
        {
            declaration++;
        }



        if(characterDetection(lineOfCode))
        {
            declaration++;
            strCharacter++;
        }

        if(pointersDetection(lineOfCode))
        {
            declaration++;
            pointer++;
        }

        if(detectStructDeclaration(lineOfCode))
        {
            ++structure;
        }

        if(headerFile
        && lineOfCode.find(");")!=std::string::npos
        && lineOfCode.find("));")==std::string::npos)
            fonction++;




        // If we are here then it is a normal line
        ++normalLines;
    }
}
