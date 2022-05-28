#include "Convert.h"
#include <fstream>

Convert::Convert(Arguments& arguments)
    :standarIn(arguments.getStdin()), standarOut(arguments.getStdout())
    , inputFilename(arguments.getInputFilename())
    , outputFilename(arguments.getOutputFilename())
    , inputMode(arguments.getInputMode())
    , outputMode(arguments.getOutputMode())
{
}

int Convert::loadSudokuLevel(SudokuLevel &sudoku)const
{
    // if inputMode is in text then
    if ( this->inputMode == TEXT )
    {
        // load sudoku from text mode
        return loadSudokuFromText(sudoku);
    }
    // else if inputMode is in binary then
    else if ( this->inputMode == BINARY )
    {
        // load sudoku from binary
        return loadSudokuFromBinary(sudoku);
    }
    // else
    else
    {
        // report error
        //return std::cerr << "error: unknown file type " << this->inputMode << std::endl, 2;
        throw std::runtime_error("inputMode");
    }
}

// Loads input text values from stdin or archive
int Convert::loadSudokuFromText(SudokuLevel& sudoku)const
{
    // If it is from stdin then
    if(this->standarIn)
    {
        // it is read with std::cin
        std::cin >> sudoku;
    }
    // else
    else
    {
        // Create object ifstream to input values
        std::ifstream input(this->inputFilename);
        // If could not open then return error code
        if(!input)
            //return std::cerr << "error: convert: Could not open file " << this->inputFilename << std::endl, 3;
            throw std::runtime_error(this->inputFilename);
        // read values into the sudoku
        input >> sudoku;
        // close file
        input.close();
    }
    return 0;
}

// Carga la matriz del sudoku de un input binario
int Convert::loadSudokuFromBinary(SudokuLevel& sudoku)const
{
    // If it is from stdin then
    if(this->standarIn)
    {
        // reopen stdin for binary reading
        freopen(NULL, "rb", stdin);
        // it is read with std::cin
        sudoku.readBinary(std::cin);
    }
    // else
    else
    {
        // Create object ifstream to input values
        std::ifstream input(this->inputFilename, std::ios::binary);
        // If could not open then return error code
        if(!input)
            //return std::cerr << "error: convert: Could not open file " << this->inputFilename << std::endl, 4;
            throw std::runtime_error(this->inputFilename);
        // read values into the sudoku
        sudoku.readBinary(input);
        // close file
        input.close();
    }
    return 0;
}

int Convert::printSudoku(const SudokuLevel &sudoku) const
{
    // if outputMode is to text then
    if ( this->outputMode == TEXT )
    {
        // print to text
        return printSudokuInText(sudoku);
    }
    // else if outputMode is to binary
    else if ( this->outputMode == BINARY )
    {
        // print to binary
        return printSudokuInBinary(sudoku, false);
    }
    // else
    else
    {
        // report error
        //return std::cerr << "error: unknown file type " << this->outputMode << std::endl, 5;
        throw std::runtime_error("outputMode");
    }
}

int Convert::printSudokuInText(const SudokuLevel& sudoku) const
{
    // If it is to stdout then
    if(this->standarOut)
    {
        // it is print with std::cout
        std::cout << sudoku;
    }
    // else it is to file
    else
    {
        // Create object ofstream to output values to file
        std::ofstream output(this->outputFilename);
        // If could not open then return error code
        if(!output)
            //return std::cerr << "error: convert: Could not open file " << this->outputFilename << std::endl, 5;
            throw std::runtime_error(this->outputFilename);
        // print values to file
        output << sudoku;
        // close file
        output.close();
    }
    return 0;
}

int Convert::printSudokuInBinary(const SudokuLevel& sudoku, const bool printDimension) const
{
    // If it is to stdout then
    if(this->standarOut)
    {
        // reopen stdout for binary writing
        freopen(NULL, "wb", stdout);
        // it is print with std::cout to stdout
        sudoku.writeBinary(std::cout, printDimension);
    }
    // else it is to a file
    else
    {
        // Create object ofstream to output values in binary form
        std::ofstream output(this->outputFilename, std::ios::binary);
        // If could not open then return error code
        if(!output)
            //return std::cerr << "error: convert: Could not open file " << this->inputFilename << std::endl, 6;
            throw std::runtime_error(this->inputFilename);
        // write values to file
        sudoku.writeBinary(output, printDimension);
        // close file
        output.close();
    }
    return 0;
}

// convert test case, if both input and output type is the same, doesn't need Convert
int Convert::convertTestCase()const
{
    SudokuLevel sudoku;
    int error = 0;

    // Load sudoku
    if (this->inputMode == TEXT )
        error = loadSudokuFromText(sudoku);
    else if(this->inputMode == BINARY)
        error = loadSudokuFromBinary(sudoku);
    else
    {
        // report error
        //return std::cerr << "error: unknown file type " << this->inputMode << std::endl, 7;
        throw std::runtime_error("inputMode");
    }

    if(error)
        //return error;
        throw std::runtime_error("loadSudokuFromText or loadSudokuFromBinary");

    sudoku.setNeedSolving() = false;

    // Print sudoku
    if(this->outputMode == TEXT)
        error = this->printSudokuInText(sudoku);
    else if(this->outputMode == BINARY)
        error = this->printSudokuInBinary(sudoku, true);
    else
    {
        // report error
        //return std::cerr << "error: unknown file type " << this->outputMode << std::endl, 8;
        throw std::runtime_error("outputMode");
    }

    if(error)
        //return error;
        throw std::runtime_error("printSudokuInText or printSudokuInBinary");

    return 0;
}

void Convert::reportUnsolvable() const
{
    if (this->outputMode == TEXT)
    {
        if(this->standarOut)
            std::cout << "unsolvable\n";
        else
        {
            std::ofstream output(this->outputFilename);
            if(!output)
                throw std::runtime_error(this->outputFilename);
            output << "unsolvable\n";
            output.close();
        }
    }
    else
    {
        int dimension = 0;
        if(this->standarOut)
        {
            freopen(NULL, "wb", stdout);
            if( ! std::cout.write(reinterpret_cast<const char*>(&dimension), sizeof(dimension)) )
                throw std::runtime_error("could not write value");
        }
        else
        {
            std::ofstream output(this->outputFilename, std::ios::binary);
            if(!output)
                throw std::runtime_error(this->inputFilename);
            if( ! output.write(reinterpret_cast<const char*>(&dimension), sizeof(dimension)) )
                throw std::runtime_error("could not write value");
            output.close();
        }
    }
}
