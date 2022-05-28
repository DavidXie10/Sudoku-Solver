#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include <string>
#include "Common.h"

/**
 * @typedef filetypes enumerator
 */
typedef enum
{
    TEXT,   /**< Text file */
    BINARY,  /**< Binary file */
    UNKNOWN  /**< Unknown file type*/
}fileType_t;

/**
 * @class Arguments
 * @brief This is a class to analize the command line arguments of the program sudoku. An example of usage:
 *
 * @code
 * int main (int argc, char* argv[])
 * {
 *      Arguments arguments();
 *      arguments.analyzeArguments(argc, argv);
 *      return arguments.printHelp();
 * }
 * @endcode
 */
class Arguments
{
public:
      DECLARE_RULE5(Arguments, default);

private:
    fileType_t inputMode;           // Default: TEXT
    fileType_t outputMode;          // Default: TEXT
    bool helpAsked;                 // If help is asked, finishes the program
    bool versionAsked;              // If version is asked, finishes the program
    std::string inputFilename;      // Name of the inputFile if provided, if not, input is from stdin
    std::string outputFilename;     // Name of the outputFile if provided, if not, output to stdout
    bool standardInput;             // Default: true, if there is no inputFile
    bool standardOutput;            // Default: true, if there is no outputFile
    bool onlyConvert;               // -c is a flag to indicate that only convert TEXT file to BINARY or vice versa, without solving the level

public:
    /**
     * @brief Default constructor of class Arguments, initialize it's atributes to the default values.
     */
    Arguments();

    /**
     * @brief Go though all the arguments provided by the invocation line of the program and assign the corresponding values to it's atributes.
     * @param argc The number of arguments invoked along the command
     * @param argv Access to every argument along the command
     * @return error code: 0 for success, 1 for error
     * @pre it is assumed that the input file format matches the input mode indicated.
    */
    int analyzeArguments(const int argc, char* argv[]);

    /**
     * @brief Prints program usage and exit.
     * @return 0 for success.
     */
    int printHelp(void);

    /**
     * @brief Prints program version and exit.
     * @return 0 for success.
     */
    int printVersion(void);

public:
    /**
     * @brief Gets the input filename if the input is not from stdin
     * @return The input file name as a string
     */
    inline std::string getInputFilename()const{return this->inputFilename;}

    /**
     * @brief Gets the output filename if the output is not to stdout
     * @return The output file name as a string
     */
    inline std::string getOutputFilename()const{return this->outputFilename;}

    /**
     * @brief Gets either if the input is seen as text or binary
     * @return The input mode as TEXT(-it) or BINARY(-ib)
     */
    inline fileType_t getInputMode()const{return this->inputMode;}

    /**
     * @brief Gets either if the output is represented as text or binary
     * @return The output mode as TEXT(-ot) or BINARY(-ob)
     */
    inline fileType_t getOutputMode()const{return this->outputMode;}

    /**
     * @brief Indicates if the user asked for help
     * @return True if --help was asked, false otherwise
     */
    inline bool getHelpAsked()const{return this->helpAsked;}

    /**
     * @brief Indicates if the user asked for the version of the program
     * @return True if --version was provided, false otherwise
     */
    inline bool getVersionAsked()const{return this->versionAsked;}

    /**
     * @brief Indicates if the user only wants to convert the input test case, i.e. without solving the sudoku
     * @return True if -c parameter was provided, false otherwise
     */
    inline bool getOnlyConvert()const{return this->onlyConvert;}

    /**
     * @brief Indicates if the data will come from stdin
     * @return True if no input files were provided, false otherwise
     */
    inline bool getStdin()const{return this->standardInput;}
    /**
     * @brief Indicates if the data will be printed to stdout
     * @return True if no output files were provided, false otherwise
     */
    inline bool getStdout()const{return this->standardOutput;}

};

#endif // ARGUMENTS_H
