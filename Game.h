// Ali Woodward
// 2385718
// alwoodwadr@chapman.edu
// CPSC 350 Section 03
// Assignment	3- Game of life

#ifndef GAME_H //header guard
#define GAME_H //header guard

//header file for the Game class

#include <iostream>
#include <exception>

using namespace std;

//abstract game class
class Game{
  public:
    Game(); //default constructor
    ~Game(); //destructor

    char** currGen;

    void playInside(char** currGen, int rows, int cols);
    int playOutside(char** currGen, int rows, int cols, string classifyEdge);
    char newCell(int neighbors, int row, int col, char** currGen);
    char** play(char** currGen, int gameMode, int rows, int cols);

    char **nextGen;
    int gameCount = 0;
    //Grid g;
    int rows;
    int cols;
    int mode;

};

//class for classic mode
class Classic : public Game
{
  public:

    char** playClassic(char** currGen, int numRows, int numCols);

};

//class for donut mode
class Donut : public Game
{
  public:

      char** playDonut(char** currGen, int numRows, int numCols);

};

//class for mirror mode
class Mirror : public Game
{
  public:

      char** playMirror(char** curGen, int numRows, int numCols);

};
#endif
