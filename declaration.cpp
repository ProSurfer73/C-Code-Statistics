#include <cctype>
#include "declaration.hpp"

static const char *integerTypes[] = {
    "int ",
    "unsigned ",
    "int8_t ",
    "int16_t ",
    "int32_t ",
    "int64_t "
};

static const char *otherTypes[] = {
    "char ",
    "float ",
    "double "
};

static const char *pointers[] = {
    "int* ",
    "unsigned* ",
    "int8_t* ",
    "int16_t* ",
    "int32_t* ",
    "int64_t* ",
    "float* ",
    "double* ",
    "long* "
};

static const char *characters[] = {
    "char* ",
    "char *"
    "char[] "
};



bool integerDeclaration(const std::string& lineOfCode)
{
    detectDeclaration(integerTypes, sizeof(integerTypes)/sizeof(integerTypes[0]), lineOfCode);
}

bool otherDeclaration(const std::string& lineOfCode)
{
    detectDeclaration(otherTypes, sizeof(otherTypes)/sizeof(otherTypes[0]), lineOfCode);
}

bool pointersDetection(const std::string& lineOfCode)
{
    detectDeclaration(pointers, sizeof(pointers)/sizeof(pointers[0]), lineOfCode);
}

bool characterDetection(const std::string& lineOfCode)
{
    detectDeclaration(characters, sizeof(characters)/sizeof(characters[0]), lineOfCode);
}

bool detectDeclaration(const char* listOfTypes[], size_t length, const std::string& lineOfCode)
{
    for(unsigned i=0;i<length; ++i)
    {
        auto found = lineOfCode.find(integerTypes[i]);

        if(found!=std::string::npos)
        {
            // We look at the next character while skiping spaces
            // It must be a alphabet character, so hat it corresponds to he name of a variable
            unsigned j=found+strlen(integerTypes[i]);
            while(j<lineOfCode.size() && isspace(lineOfCode[j])) ++j;

            // if the next non-space character is alphabet character, then it is declaration
            return isalpha(lineOfCode[j]);
        }
    }
    return false;
}

bool detectStructDeclaration(const std::string& lineOfCode)
{
    return(lineOfCode.find("struct ")!=std::string::npos // there must be the keyword struct
    && lineOfCode.find('(')==std::string::npos // without '('
    && lineOfCode.find(';')==std::string::npos); // without ';'
}
