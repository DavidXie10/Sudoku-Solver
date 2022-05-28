#include <cstring>
#include <iostream>
#include "Arguments.h"

const char* const sudokuHelp =
"\nUsage: sudoku [options] [file]\n"
"Solves sudokus and displays the solution or converts input text cases files to binary and vice\n"
"versa, without solving the level. When there are no arguments provided, sudoku reads\n"
"data from stdin and displays to stdout.\n\n"
        "Option           Meaning\n"
        "  -c             Only convert the input case, does not solve the sudoku level\n"
        "  -ib            The input data will be seen as binary\n"
        "  -it            The input data will be seen as text\n"
        "  -ob            The output data is display in binary either to a file or stdout\n"
        "  -ot            The output data is display in text either to a file or stdout\n"
        "  -h or --help   Print Help (this message) and exit\n"
        "  --version      Print version information and exit\n";

Arguments::Arguments()
    :inputMode(TEXT), outputMode(TEXT)
    , helpAsked(false), versionAsked(false)
    , inputFilename(std::string()), outputFilename(std::string())
    , standardInput(true), standardOutput(true)
    , onlyConvert(false)
{
}

int Arguments::analyzeArguments(const int argc, char* argv[])
{
    // Repeat for each argumentIndex in argc
    for ( int argumentIndex = 1; argumentIndex < argc && !(this->helpAsked) && !(this->versionAsked); ++argumentIndex )
    {
        std::string actualArgument = argv[argumentIndex];
        // If the argument starts with '-', then it is an option
        if(*argv[argumentIndex] == '-')
        {
            // If it is --help then
            if( strcmp(actualArgument.c_str(), "--help") == 0 || strcmp(actualArgument.c_str(), "-h") == 0 )
            {
                // exit program
                this->helpAsked = true;
            }
            // else if it is --version then
            else if( strcmp(actualArgument.c_str(), "--version") == 0)
            {
                // exit program
                this->versionAsked = true;
            }
            // else if starts with -i then
            else if( actualArgument[1] == 'i')
            {
                // change input mode, t fot TEXT or b for BINARY
                this->inputMode = (actualArgument[2] == 't')?TEXT:(actualArgument[2] == 'b')?BINARY:UNKNOWN;
            }
            // else if starts with -o then
            else if( actualArgument[1] == 'o' )
            {
                // change output mode, t fot TEXT or b for BINARY
                this->outputMode = (actualArgument[2] == 't')?TEXT:(actualArgument[2] == 'b')?BINARY:UNKNOWN;
            }
            //else if starts with -c then
            else if(actualArgument[1] == 'c')
            {
                // onlyConvert := true
                this->onlyConvert = true;
            }
            // else report unknowk option
            else
                //return std::cerr << "error: sudoku: "<< actualArgument <<" unknown option\n", 1;
                throw std::runtime_error(actualArgument);
        }
        // Else it is a file
        else
        {
            // if the previus argument is -ot || -ob then
            if( strcmp(argv[argumentIndex - 1], "-ot") == 0 || strcmp(argv[argumentIndex - 1], "-ob") == 0 )
            {
                // outputFilename := actualArgument
                this->outputFilename = actualArgument;
                this->standardOutput = false;
            }
            // Else
            else
            {
                // inputFilename := actualArgument
                this->inputFilename = actualArgument;
                this->standardInput = false;
            }
        }
    }
    return 0;
}

int Arguments::printHelp()
{
    return std::cout << sudokuHelp, 0;
}

int Arguments::printVersion()
{
    std::cout << "sudoku v1.0 20200627 ECCI-UCR\n"
              << "This is free software. Use it at your own risk\n";
    return 0;
}
