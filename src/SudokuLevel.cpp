#include <cmath>
#include <iomanip>
#include <vector>

#include "SudokuLevel.h"

SudokuLevel::SudokuLevel(const unsigned int dimension)
    : dimension(dimension == 0? 2:dimension)
    , matrixDimension(this->dimension * this->dimension)
    , needSolving(true)
    , matrix(matrixDimension, std::vector<unsigned int>(matrixDimension))
{
}

bool SudokuLevel::solve(bool isPosibleToContinueBranch)
{
    bool isSolved;
    bool newInformation = true;
    unsigned int rangeGuess = this->matrixDimension;
    long int posibilityToTry = 0;
    while (newInformation)
    {
        newInformation = false;
        isPosibleToContinueBranch = sweep(newInformation, false, rangeGuess, posibilityToTry);
        if (!isPosibleToContinueBranch)
            return false;
        isSolved = checkCompletitude();
        if (isSolved) {
            return true;
        }
    }
    std::vector<std::vector<unsigned int>> matrixClone = this->matrix;
    while (posibilityToTry < rangeGuess)
    {
        this->matrix = matrixClone;
        isPosibleToContinueBranch = sweep(newInformation, true, rangeGuess, posibilityToTry);
        if (isPosibleToContinueBranch)
        {
            isSolved = solve(isPosibleToContinueBranch);
            if (isSolved)
            {
                return true;
            }
        }
        posibilityToTry++;
    }
    return false;
}

bool SudokuLevel::sweep(bool& newInformation, bool guessPhase, unsigned int& rangeGuess, unsigned int posibilityToTry)
{
    bool isGuessSet = false;
    for (unsigned int currentRow = 0; currentRow < this->matrixDimension; currentRow++)
    {
        for ( unsigned int currentCol = 0; currentCol < this->matrixDimension; currentCol++)
        {
            if (matrix[currentRow][currentCol] == 0)
            {
                std::vector<long int> posibleNumbersVector(this->matrixDimension);
                for (unsigned int index = 0; index < (this->matrixDimension); index++)
                    posibleNumbersVector[index] = index + 1;
                checkRowCol(currentRow, currentCol, posibleNumbersVector);
                checkBox(currentRow, currentCol, posibleNumbersVector);
                if (!guessPhase)
                {
                    if (posibleNumbersVector.size() == 1){
                        matrix[currentRow][currentCol] = posibleNumbersVector[0];
                        newInformation = true;
                        rangeGuess = this->matrixDimension + 1;
                    }
                    if (posibleNumbersVector.size() < rangeGuess && posibleNumbersVector.size())
                        rangeGuess = posibleNumbersVector.size();
                    if (posibleNumbersVector.size() == 0)
                        return false;
                }

                if (guessPhase)
                {
                    if (posibleNumbersVector.size() == 0)
                    {
                        return false;
                    }
                    if (posibleNumbersVector.size() == rangeGuess && !isGuessSet)
                    {
                        matrix[currentRow][currentCol] = posibleNumbersVector[posibilityToTry];
                        newInformation = true;
                        isGuessSet = true;
                    }
                }
            }
        }
    }
    return true;
}

int checksIfNumberIsInVector(int number, std::vector<long int> vector)
{
    for (unsigned int index = 0; index < vector.size(); index++)
    {
        if (number == vector[index])
        {
            return index;
        }
    }
    return -1;
}

void SudokuLevel::checkRowCol(long int currentRow, long int currentCol, std::vector<long int>& posibleNumbersVector)
{
    for (unsigned int col = 0; col < matrixDimension; col++)
    {
        int coincideNumber = checksIfNumberIsInVector(matrix[currentRow][col], posibleNumbersVector);
        if (coincideNumber > -1)
            posibleNumbersVector.erase(posibleNumbersVector.begin() + coincideNumber);
    }
    for (unsigned int row = 0; row < matrixDimension; row++)
    {
        int coincideNumber = checksIfNumberIsInVector(matrix[row][currentCol], posibleNumbersVector);
        if (coincideNumber > -1)
            posibleNumbersVector.erase(posibleNumbersVector.begin() + coincideNumber);
    }
}



void SudokuLevel::checkBox (long int currentRow, long int currentCol, std::vector<long int>& posibleNumbersVector)
{
    long int boxRowCoordinate = std::floor(currentRow / this->dimension);
    long int boxColCoordinate = std::floor(currentCol / this->dimension);
    for (unsigned int row = boxRowCoordinate * this->dimension; row < (boxRowCoordinate * this->dimension) + this->dimension; row++)
    {
        for (unsigned int col = boxColCoordinate * this->dimension; col < (boxColCoordinate * this->dimension) + this->dimension; col++)
        {
            int coincide_number = checksIfNumberIsInVector(matrix[row][col], posibleNumbersVector);
            if (coincide_number > -1)
                posibleNumbersVector.erase(posibleNumbersVector.begin() + coincide_number);
        }
    }
}

bool SudokuLevel::checkCompletitude()
{
    for (unsigned int row = 0; row < matrixDimension; row++)
    {
        for (unsigned int col = 0; col < matrixDimension; col++)
        {
            if (matrix[row][col] == 0)
                return false;
        }
    }
    return true;
}

#if 0
bool SudokuLevel::checksPosibleToContinue()
{
    for (long int row = 0; row < matrixDimension; row++) {
        for (long int col = 0; col < matrixDimension; col++){
            if (matrix[row][col] == 0) {
                std::vector<long int> posibleNumbersVector(matrixDimension);
                for (int index = 0; index < (matrixDimension); index++)
                    posibleNumbersVector[index] = index + 1;
                posibleNumbersVector.shrink_to_fit();
                checkRow_Col(row, col, posibleNumbersVector);
                checkBox(row, col, posibleNumbersVector);
                if (posibleNumbersVector.size() == 0)
                    return false;
                }
            }
        }
    return true;
}
#endif

#if 0
void print_matrix(std::vector<std::vector<unsigned int>> matrix, unsigned int matrixDimension)
{
    for (int r = 0; r < matrixDimension; r++){
        for (int c = 0; c < matrixDimension; c++){
            if (c % 3 == 0)
                std::cout << " ";
            std::cout << matrix[r][c];
        }
        if ((r + 1) % 3 == 0)
            std::cout << std::endl;
        std::cout << std::endl;
    }
}
#endif

void SudokuLevel::resizeMatrix(const unsigned int newDimension)
{
    this->dimension = newDimension;
    this->matrixDimension = newDimension * newDimension;
    this->matrix.resize(this->matrixDimension);
    for(unsigned int row = 0; row < this->matrixDimension; ++row)
        this->matrix[row].resize(this->matrixDimension);
}

std::istream &operator>>(std::istream &input, SudokuLevel &sudokuLevel)
{
    // Create character what to see what represents
    char what = '\0';
    // Read dimension from input file
    unsigned int newDimension = 0;
    input >> newDimension;
    
    sudokuLevel.dimension = newDimension;
    if(newDimension == 0)
        throw std::runtime_error("invalid dimension 0");

    sudokuLevel.resizeMatrix(newDimension);

    // skip whitespaces
    input >> std::ws;

    // Repeat while there are characters in input file
    for(size_t row = 0; row < sudokuLevel.matrixDimension; ++row){
        for(size_t column = 0; column < sudokuLevel.matrixDimension; ++column)
        {
            what = input.peek();
            // if what is a number then
            if( std::isdigit(what))
            {
                // Read value
                input >> sudokuLevel(row, column);
            }
            // else if it is a dot
            else if( what == '.')
            {
                sudokuLevel(row, column) = 0;
                input.ignore();
            }
            // Juan exception
            else
            {
                //throw 3;
                //return input;
                throw std::runtime_error("reading values");
            }
            // extract ws until a character is reached
            input >> std::ws;
        }
    }
    // Close files
    return input;
}

// operator <<, prints the sudoku
std::ostream& operator<<(std::ostream& output, const SudokuLevel& sudokuLevel)
{
    if(!sudokuLevel.needSolving)
        output << sudokuLevel.dimension << std::endl;
    output << std::endl;
    unsigned int sudokuDimension = sudokuLevel.dimension;
    // Create width as if the dimension of the sudoku is greater than 3 then it is 2
    unsigned int width = sudokuDimension >= 4?2:1;
    // Repeat for each row's matrix
    for(unsigned int row = 0; row < sudokuLevel.matrixDimension; ++row)
    {
        // Repeat for each number in column's matrix
        for(unsigned int column = 0; column < sudokuLevel.matrixDimension; ++column)
        {
            // Set output width as width
            output << std::setw(width);
            // if number is 0 then
            if((sudokuLevel(row, column) == 0))
            {
                // print a dot
                output << '.';
            }
            // else
            else
            {
                // print the number
                output << sudokuLevel(row, column);
            }
            // if column % dimension == 0 then
                // print one whitespace,
            // else set width as width + 1 and print a white space
            output << std::setw( (!((column+1) % sudokuDimension)) ? width + 2:1);
            output << ' ';
        }
        // if row % dimension == 0 then print 2 end line, else print one
        output << ( (!( ( row + 1 ) % sudokuDimension)) ? "\n\n":"\n");
    }
    return output;
}

std::istream &SudokuLevel::readBinary(std::istream &input)
{
    // Create value to go though all the values
    unsigned int value = 0;

    // Read dimension from input file
    if(!input.read(reinterpret_cast<char*>(&value), sizeof(value)))
    {
        //throw Juan, "could not read value\n";
        throw std::runtime_error("could not read value");
    }

   this->dimension = value;

    if(this->dimension == 0)
        throw std::runtime_error("invalid dimension 0");

    // if(value != this->dimension)
    this->resizeMatrix(value);
    
    // Repeat while for each number in input file
    for(unsigned int row = 0; row < this->matrixDimension; ++row){
        for(unsigned int column = 0; column < this->matrixDimension; ++column)
        {
            if(! input.read(reinterpret_cast<char*>(&value), sizeof(value)) )
            {
                //throw Juan,  "could not read value\n";
                throw std::runtime_error("could not read value");
            }
            this->matrix[row][column] = value;
        }
    }
    return input;
}

std::ostream &SudokuLevel::writeBinary(std::ostream &output, const bool displayDimension)const
{
    if(displayDimension)
    {
        // Write dimension to output in binary form
        if( ! output.write(reinterpret_cast<const char*>(&this->dimension), sizeof(this->dimension)) )
        {
            //throw Juan, "could not write value\n";
            throw std::runtime_error("could not write value");
        }
    }

    // Repeat for each number in matrix
    for(size_t row = 0; row < this->matrixDimension; ++row){
        for(size_t column = 0; column < this->matrixDimension; ++column)
        {
            // Write matrix element to output in binary form
            if( ! output.write(reinterpret_cast<const char*>(&this->matrix[row][column]), sizeof(this->matrix[row][column])) )
            {
                //throw Juan, "could not write value\n";
                throw std::runtime_error("could not write value");
            }
        }
    }
    return output;
}

bool SudokuLevel::verify()
{
    for (size_t row = 0; row < this->matrixDimension; row++)
    {
        for (size_t col = 0; col < this->matrixDimension; col++)
        {
            if (this->matrix[row][col] != 0)
            {
                std::vector<long int> number;
                for (int index = 0; index < 4; index++)
                    number.push_back(this->matrix[row][col]);
                checkRowCol(row, col, number);
                checkBox(row, col , number);
                if (number.size() == 0)
                    return false;
            }
        }
    }
    return true;
}

