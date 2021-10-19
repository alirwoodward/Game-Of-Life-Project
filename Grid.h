// Ali Woodward
// 2385718
// alwoodwadr@chapman.edu
// CPSC 350 Section 03
// Assignment	3- Game of life

#ifndef GRID_H //header guard
#define GRID_H //header guard

#include <fstream>
#include <sstream>
#include <cstdlib>

#include <iostream>
#include <exception>

using namespace std;

class Grid{
  public:
    Grid();
    Grid(int rows, int cols); //default constructor
    ~Grid(); //destructor

    void createGrid(string gridFile);
    void createGrid(int rowNum, int colNum, double popDensity);
    char** getArrayG();
    void copyAndReplace(char **newArray);

    int getDimensions(char rowOrCol);


    int gameCount = 0;
    int rows;
    int cols;
    int mode;
    char **currGen;


};

#endif
