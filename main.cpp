#include <iostream>

#include "filesystem.hpp"
#include "stat.hpp"

using namespace std;

static bool hasEnding(std::string const &fullString, std::string const &ending)
{
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

int main()
{
    cout << "Welcome to C code syntax analyser.\n" << std::endl;

    std::string folderName;

    // Contains stats about the files
    Stat stat;
    unsigned nbHeaderFile=0;
    unsigned nbSourceFile=0;
    unsigned nbFiles=0;

    do
    {

    cout << "Please enter the path to a directory you would like to analyse (or nothing to continue):" << std::endl;

    // let's get an input line from the user
    std::getline(std::cin, folderName);


    // if the directory exists
    if(directoryExists(folderName.c_str()))
    {
        // a list of string
        std::vector<std::string> fileList;

        // let's list all the files in that directory
        explore_directory(folderName, fileList);

        for(std::string& s: fileList)
        {
            // If it is a source or a header file
            if(hasEnding(s, ".h") || hasEnding(s, ".c") // let's analyse C files
            || hasEnding(s, ".cpp") || hasEnding(s, ".hpp")) // CPP files too
            {
                // log trace
                //std::cout << "Evaluating: " << s << std::endl;

                // let's evaluate the comments contained in that file
                stat.analyseFile(s);

                if(hasEnding(s, ".h") )
                    ++nbHeaderFile;
                else if(hasEnding(s, ".c"))
                    ++nbSourceFile;
            }
        }

        nbFiles += fileList.size();
    }


    }
    while(!folderName.empty());

    // Finally, let's show the result to the end user

    stat.printResults();

    // Let's now pirnt stats related to the filesystem
    std::cout << "nbFiles: " << nbFiles << std::endl;
    std::cout << "sourceFiles: " << nbSourceFile << std::endl;
    std::cout << "headerFiles: " << nbHeaderFile << std::endl;

    return 0;
}
