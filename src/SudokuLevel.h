#ifndef SUDOKULEVEL_H
#define SUDOKULEVEL_H

#include <iostream>
#include <vector>

#include "Common.h"

/**
 * @class SudokuLevel
 * @brief This class has two main functions. The first one is the solving of the Sudoku, it receives the matrix
 * and it return the Sudoku solved. Also it works as a placeholder for the Sudoku matrix in case the user
 * only wants to convert to binary or text. An example of usage:
 *
 * @code
 * SudokuLevel sudoku;
 * isSudokuLegal = sudoku.verify();
 * if (isSudokuLegal)
 *     isSolvable = sudoku.solve(true);
 * @endcode
 */
class SudokuLevel
{
public:
      DECLARE_RULE5(SudokuLevel, default);
private:
    unsigned int dimension;
    unsigned int matrixDimension;
    bool needSolving;
    std::vector<std::vector<unsigned int>> matrix;
public:
    /**
     * @brief Constructor of SudokuLevel class
     * @param dimension of a square of the Sudoku matrix
     */
    SudokuLevel(const unsigned int dimension = 2);

public:
    /**
     * @return the matrix of SudokuLevel object
     */
    inline std::vector<std::vector<unsigned int>>& getSudokuMatrix() {return this->matrix;}

    /**
     * @brief Sets up the main backtracking that goes solving the sudoku.
     * @param isPosibleToContinueBranch if its posible to continue through a certain branch of posibilities.
     * @return true if the sudoku is solved, false if the sudoku is yet to be solved, and false in the Sudoku.cpp means that it cant be solved
     */
    bool solve(bool isPosibleToContinueBranch);

    /**
     * @brief sweep basically checks every cell and does two main things depending on  the phase. If the guessPhase is false it goes adding new information that is necesarry
     * (it doesn't require guessing), also checks the cell with the lowest posibilites. If the guessPhase is true it goes searching the lowest cell with posibilites and tries
     * the posibility depending on posibilityToTry. If by any means it reaches a cell that cannot have any value returns false.
     * @param newInformation defines if new information has been gathered so it can go through sweep again and gather more information or enter guessPhase
     * @param guessPhase defines if sweep is searching for restricted spots or its going to enter a posibility in the lowest posibility cell
     * @param rangeGuess the number of the first cell with lowest posibilities
     * @param posibilityToTry the number of the guess its going  to try in the cell of lowest posibilities.
     * @return true if it can continue, false if one cell absolutely imposible to insert a value
     */
    bool sweep(bool& newInformation, bool guessPhase, unsigned int &rangeGuess, unsigned int posibilityToTry);

    /**
     * @brief Goes through the matrix checking if the are still 0
     * @return true if the matrix is complete (there are no 0), false it finds a spot that is yet to be filled
     */
    bool checkCompletitude();

    /**
     * @brief Gets a vector with all the posibilities that the cell can be (matrixDimension) and checks which one is repetead in the row and in the col to discard it.
     * @param currentRow the row of the cell in which the vector comes from
     * @param currentCol the col of the cell in which the vector comes from
     * @param posibleNumbersVector vector with all the posibilites the cell can be
     */
    void checkRowCol(long int currentRow, long int currentCol, std::vector<long int>& posibleNumbersVector);

    /**
     * @brief Gets a vector with all the posibilities that the cell can be (matrixDimension) and checks which one is repetead through the box it is in to discard it.
     * @param currentRow the row of the cell in which the vector comes from
     * @param currentCol the col of the cell in which the vector comes from
     * @param posibleNumbersVector vector with all the posibilites the cell can be
     */
    void checkBox (long int currentRow, long int currentCol, std::vector<long int>& posibleNumbersVector);

    /**
     * @brief goes through each cell that has a number and compares it against all the other cells in the same col, row and box,
     * if it matches it means the sudoku is not legal.
     * @return true if sudoku starting position is correct, false if sudoku starting position has an invalid position
     */
    bool verify();

    /**
     * @brief Access non const value of matrix at row, column cell so that it can be modified
     * @return The element at row, column position of this object's matrix
     */
    inline unsigned int& operator()(const unsigned int row, const unsigned int column){ return this->matrix[row][column];}

    /**
     * @brief Access const value of matrix at row, column cell so that it can be seen and used, but not modified
     * @return The element at row, column position of this object's matrix
     */
    inline const unsigned int& operator()(const unsigned int row, const unsigned int column)const{ return this->matrix[row][column]; }

public:
    // Loads the data into the sudoku
    /**
     * @brief Reads the input values into the soduku level, first reads the dimension and then one by one the text values of the matrix,
     * replaces the dots for zeros.
     * @param input a reference to an object of type istream, either std::cin or std::ifstream that allows input data in text format
     * @param sudokuLevel a reference to an object of SudokuLevel class to be loaded
     * @return The same istream object that entered as a reference
     */
    friend std::istream& operator>>(std::istream& input, SudokuLevel& sudokuLevel);

    /**
     * @brief Prints the values of the soduku level, if the needSolving variable is true, doesn't print the dimension, else it prints it
     *  and then one by one prints every value in the matrix. If it is for only convert a test case, instead of zeros prints dots.
     * @param output a reference to an object of type ostream, either std::cout or std::ofstream that allows output data in text format
     * @param sudokuLevel a reference to an object of SudokuLevel class to be printed in file or stdout
     * @return The same ostream object that entered as a reference
     */
    friend std::ostream& operator<<(std::ostream& output, const SudokuLevel& sudokuLevel);

    /**
     * @brief Reads the input values into the soduku level, after converting it's binary representation. Note that the binary zeros represent a dot in a text case
     * @param input a reference to an object of type istream, either std::cin or std::ifstream that allows input data in binary format
     * @return The same istream object that entered as a reference
     */
    std::istream& readBinary(std::istream& input);

    /**
     * @brief Writes the values of the soduku level to its binary representation
     * @param output a reference to an object of type ostream, either std::cout or std::ofstream that allows output data in binary format
     * @param displayDimension a boolean flag that indicates if this method is used for only convert a test case, if true, also prints it's dimension in binary format, else it doesn't
     * @return The same ostream object that entered as a reference
     */
    std::ostream& writeBinary(std::ostream& output, const bool displayDimension)const;

public:
    /**
     * @brief Get method of dimension atribute
     * @return A copy to this object's dimension
     */
    inline int getDimension()const{return this->dimension;}

    /**
     * @brief Get method of needSolving atribute so that it can be change, indicates if the level only
     * @return The element at row, column position of this object's matrix
     */
    inline bool& setNeedSolving(){return this->needSolving;}

private:
    /**
     * @brief Receives the new dimension of this object's matrix and also updates the size of it's matrix according to the dimension provided
     * @param newDimension the new dimension to update the SudokuLevel after the dimension is read
     */
    void resizeMatrix(const unsigned int newDimension);

};
/**
 * @brief Goes through the vector to see if a number matches.
 * @param number number to be compared against
 * @param vector posibilities the cell can be
 * @return number that matches with a number of the vector. -1 if no number matches.
 */
int checksIfNumberIsInVector(int number, std::vector<int> vector);

#if 0
void print_matrix(std::vector<std::vector<unsigned int>> matrix, unsigned int matrixDimension);
#endif

#endif // SUDOKULEVEL_H

