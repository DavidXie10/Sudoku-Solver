#ifndef CONVERT_H
#define CONVERT_H

#include <string>

#include "Arguments.h"
#include "Common.h"
#include "SudokuLevel.h"

/**
 * @class Convert
 * @brief This class has two functions, the first one is when a sudoku level needs to be solve, it loads into
 * the SudokuLevel matrix, the input values from stdin or a input file either
 * in binary or textual, if it is in binary, it converts each value into
 * textual and store them into the matrix. If it is textual and there is a dot,
 * it becomes a 0. Also converts the solved sudoku to either binary or textual to
 * display in the stdout or to put it into the outputFilename
 * indicated. The second function is that, converts, from an input text case file to
 * binary file or vice versa.
 * An example of usage:
 * @code
 * SudokuLevel sudoku;
 * Arguments args(argc, argv);
 * Convert convert(args);
 * convert.loadSudokuLevel(sudoku);
 * convert.printSudoku(sudoku);
 * @endcode
 */
class Convert
{
public:
      DECLARE_RULE5(Convert, default);
private:
    bool standarIn;
    bool standarOut;
    std::string inputFilename;
    std::string outputFilename;
    fileType_t inputMode;
    fileType_t outputMode;

public:
    /**
     * @brief Constructor of class Convert
     * @param arguments Initialize Convert atributes with the analysis made by arguments with the invocation of sudoku in command line
     */
    Convert(Arguments& arguments);

public:
    /**
     * @brief Decide which method to call to load the matrix of the sudoku according to the input mode(TEXT or BINARY)
     * @param sudoku in which the input values will be loaded
     * @return An error code, 0 for sucess
     */
    int loadSudokuLevel(SudokuLevel& sudoku)const;

    /**
     * @brief Loads input text values from stdin or archive
     * @param sudoku in which the input values will be loaded from text data
     * @return An error code, 0 for sucess
     */
    int loadSudokuFromText(SudokuLevel& sudoku)const;

    /**
     * @brief Loads input binary values from stdin or archive
     * @param sudoku in which the input values will be loaded from binary data
     * @return An error code, 0 for sucess
     */
    int loadSudokuFromBinary(SudokuLevel& sudoku)const;

    /**
     * @brief Decide which method to call to print the matrix of the sudoku according to the output mode (TEXT or BINARY)
     * @param sudoku to be printed in stdout or file in text form or binary acoording to the arguments provided
     * @return An error code, 0 for sucess
     */
    int printSudoku(const SudokuLevel& sudoku)const;

    /**
     * @brief Prints the matrix of the sudoku in text form to stdout or to a file
     * @param sudoku to be printed in stdout or file in text form with format
     * @return An error code, 0 for sucess
     */
    int printSudokuInText(const SudokuLevel& sudoku)const;

    /**
     * @brief Prints the matrix of the sudoku in binary form to stdout or to a file
     * @param sudoku to be printed in stdout or file in binary form
     * @param printDimension indicates that if it is only convert (do not solve the sudoku level), then print also the sudoku dimension at the beginning, if not do not print the dimension
     * @return An error code, 0 for sucess
     */
    int printSudokuInBinary(const SudokuLevel& sudoku, const bool printDimension)const;

    /**
     * @brief Convert an input test case in text format to its binary format or viceversa. If both input and output format are the same, just moves the contents of one origin(file or stdin) to its destination provided (file or stdout)
     * @return An error code, 0 for success
     */
    int convertTestCase()const;

    /**
     * @brief Reports unsolvable if output is textual and the dimension 0 if the output is binary, according to the destination provided
     */
    void reportUnsolvable()const;
};

#endif // CONVERT_H
