#ifndef SUDOKU_H
#define SUDOKU_H

#include "Arguments.h"
#include "Common.h"
#include "Convert.h"
#include "SudokuLevel.h"

/**
 * @brief The Sudoku class is the controller. It initiates all the other classes.
 * An example of usage:
 * @code
 * Sudoku::getInstance().run(argc, argv);
 * @endcode
 */
class Sudoku
{
public:
      DECLARE_RULE5(Sudoku, default);
public:
    /**
     * @brief Constructor of Sudoku class
     */
    Sudoku();

    /**
     * @brief Creats object of Arguments, object of Convert, and object of SudokuLevel if the user desires. Prints Helps, prints Version, converts the file
     * or solves the sudoku depending which the user wants.
     * @param argc number of arguments
     * @param argv vector with all the arguments
     * @return 0 if all runs correct
     */
    int run(const int argc, char** argv)const;

    /**
     * @brief Implements the Singleton pattern
     * @return
     */
    static Sudoku& getInstance();
};

#endif // SUDOKU_H
