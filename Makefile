#Adpated from <http://jeisson.ecci.ucr.ac.cr/progra2/2019b/ejemplos/>
CXX=g++
FLAGS=-g -Wall -Wextra
CXXFLAGS=$(FLAGS) -std=c++11

all: bin/sudoku

bin/sudoku: build/main.o build/Arguments.o build/Sudoku.o lib/libSudokuLevel.so lib/libConvert.so | bin/.
	$(CXX) $(CXXFLAGS) $^  -o  $@

lib/libConvert.so: build/dyn/Convert.o | lib/.
	$(CXX) -shared $^ -o $@

lib/libSudokuLevel.so: build/dyn/SudokuLevel.o | lib/.
	$(CXX) -shared $^ -o $@

build/%.o: src/%.cpp | build/.
	$(CXX) -c $(CXXFLAGS) $^ -o $@

build/dyn/%.o: src/%.cpp | build/dyn/.
	$(CXX) -c -fPIC $(CXXFLAGS) $^ -o $@

.PRECIOUS: %/.
%/.:
	mkdir -p $(dir $@)

.PHONY: clean
clean:
	rm -rf bin build doc lib
