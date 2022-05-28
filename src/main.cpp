#include "Sudoku.h"

/**
  * @brief Main function that runs the sudoku program
  * @param argc number of arguments
  * @param argv vector with all the arguments
  * @return 0 if all runs correct
*/

int main(int argc, char** argv)
{
    //Sudoku sudoku;
    return Sudoku::getInstance().run(argc, argv);
}
