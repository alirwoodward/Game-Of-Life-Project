// Ali Woodward
// 2385718
// alwoodwadr@chapman.edu
// CPSC 350 Section 03
// Assignment	3- Game of life

#ifndef SIMULATION_H //header guard
#define SIMULATION_H //header guard

#include <iostream>
#include <exception>
#include <fstream>

#include "Grid.h"
#include "Game.h"
//#include "Simulation.h"


using namespace std;

class Simulation{
  public:
    Simulation(); //default constructor
    ~Simulation(); //destructor

    void printArray();
    void getMapType();
    void getTextFile();
    void chooseGameMode();
    void getNumRows();
    void getNumCols();
    void getDensity();
    void getPrinting();
    void beginGame();
    void playGame();
    void endGame();
    //Grid *grid;

  private:
    char** currGen;
    char** newArray;
    Grid *grid;
    int gameCount = 0;
    int ogMapType;
    string mapText;
    int gameMode;
    int speed;
    int numRows;
    int numCols;
    double popDensity;
    int printing;
    string newFileName;
    fstream outputFile;

};

#endif
