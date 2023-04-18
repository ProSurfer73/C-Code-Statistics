#ifndef FILESYSTEM_HPP
#define FILESYSTEM_HPP

#include <vector>
#include <string>

// to list all the files in that directory
void explore_directory(std::string dirname, std::vector<std::string>& files);

// to check if the direcotyr exists
bool directoryExists(const char* basepath);

#endif // FILESYSTEM_HPP

