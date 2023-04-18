#ifndef DECLARATION_HPP
#define DECLARATION_HPP

#include <string>
#include <cstring>

/// The point of the functions declared here is to detect variable declaration
/// from a string that is a line of code

bool integerDeclaration(const std::string& lineOfCode);

bool otherDeclaration(const std::string& lineOfCode);

bool detectDeclaration(const char *listOfTypesWithSpaces[], size_t length, const std::string& lineOfCode);

bool pointersDetection(const std::string& lineOfCode);

bool characterDetection(const std::string& lineOfCode);

bool detectStructDeclaration(const std::string& structDeclar);

#endif // DECLARATION_HPP
