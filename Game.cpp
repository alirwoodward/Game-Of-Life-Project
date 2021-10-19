// Ali Woodward
// 2385718
// alwoodwadr@chapman.edu
// CPSC 350 Section 03
// Assignment	3- Game of life

// Game.cpp is an abstract class that provides the main methods for the execution of rules to play the game of life
// the Game class provides features that are later inherited by Classic, Donut, and Mirror

#include "Game.h"

Game::Game(){
  //constructor empty
}

Game::~Game(){
  //empty destructor
}


//the playInside method will be used in every mode and finds the next generation of cells only for the inside cells
//Parameters- currGen = current generation of cells, r = number of rows in grid, c = number of cols in grid
//No return, simply assigns the cell in the next generation to be empty or full
void Game::playInside(char** currGen, int r, int c){


  rows = r;
  cols = c;


  nextGen = new char*[rows];
  for (int i = 0; i < rows; i++)
	{
		nextGen[i] = new char[cols];
	}

  //this for loop goes through the inside cells and counts the neighbors for each cell to decide whether it will be full or empty in the next generation
  for (int i = 0; i < rows; ++i)
  {
     for (int j = 0; j < cols; ++j)
     {
         if((i >= 1 && i < rows-1) && (j >= 1 && j < cols-1)){
           int neighborCount = 0;
           if(currGen[i-1][j-1] == 'X'){
             ++neighborCount;
           }
           if(currGen[i-1][j] == 'X'){
             ++neighborCount;
           }
           if(currGen[i-1][j+1] == 'X'){
             ++neighborCount;
           }

           if(currGen[i][j-1] == 'X'){
             ++neighborCount;
           }
           if(currGen[i][j+1] == 'X'){
             ++neighborCount;
           }
           if(currGen[i+1][j-1] == 'X'){
             ++neighborCount;
           }
           if(currGen[i+1][j] == 'X'){
             ++neighborCount;
           }
           if(currGen[i+1][j+1] == 'X'){
             ++neighborCount;
           }

           nextGen[i][j] = newCell(neighborCount, i, j, currGen);
         }else{
           nextGen[i][j] = ' ';
         }
     }
  }
}


//the playOutside method will be used in every mode and finds the next generation of cells only for the cells on the outside of the grid
//the outside cells of the grid have very different roles depending on the mode that they are being played, this method only does the very simplest neighbors that can be found inside the realm of the basic grid.
//Parameters- currGen = current grid, int rIndex = current row index, cIndex = current column index, string classifyEdge = string classifier to know if we are looking at the top row, bottom row, left column, right column, or a particular corner
//returns an int of the basic neighbor count for the current outside cell being looked at
int Game::playOutside(char** currGen, int rIndex, int cIndex, string classifyEdge){
  int topRow = 0;
  int bottomRow = 0;
  int leftCol = 0;
  int rightCol = 0;
  int cornerCounter = 0;

  //top row general neighbors (not on outside of grid)
  if(classifyEdge == "TR"){
    if(currGen[0][cIndex-1] == 'X'){
      ++topRow;
    }
    if(currGen[0][cIndex+1] == 'X'){
      ++topRow;
    }
    if(currGen[1][cIndex+1] == 'X'){
      ++topRow;
    }
    if(currGen[1][cIndex] == 'X'){
      ++topRow;
    }
    if(currGen[1][cIndex-1] == 'X'){
      ++topRow;
    }
    return topRow;
  }

    //bottom row general neighbors (not on outside of grid)
  if(classifyEdge == "BR"){
    if(currGen[rows-1][cIndex-1] == 'X'){
      ++bottomRow;
    }
    if(currGen[rows-1][cIndex+1] == 'X'){
      ++bottomRow;
    }
    if(currGen[rows-2][cIndex+1] == 'X'){
      ++bottomRow;
    }
    if(currGen[rows-2][cIndex] == 'X'){
      ++bottomRow;
    }
    if(currGen[rows-2][cIndex-1] == 'X'){
      ++bottomRow;
    }
    return bottomRow;
  }

  if(classifyEdge == "LC"){
    if(currGen[rIndex+1][0] == 'X'){
      ++leftCol;
    }
    if(currGen[rIndex-1][0] == 'X'){
      ++leftCol;
    }
    if(currGen[rIndex-1][1] == 'X'){
      ++leftCol;
    }
    if(currGen[rIndex][1] == 'X'){
      ++leftCol;
    }
    if(currGen[rIndex+1][1] == 'X'){
      ++leftCol;
    }
    return leftCol;
  }

  if(classifyEdge == "RC"){
    if(currGen[rIndex+1][cols-1] == 'X'){
      ++rightCol;
    }
    if(currGen[rIndex-1][cols-1] == 'X'){
      ++rightCol;
    }
    if(currGen[rIndex-1][cols-2] == 'X'){
      ++rightCol;
    }
    if(currGen[rIndex][cols-2] == 'X'){
      ++rightCol;
    }
    if(currGen[rIndex+1][cols-2] == 'X'){
      ++rightCol;
    }
    return rightCol;
  }

  if(classifyEdge == "TLC"){
    cornerCounter == 0;
    if(currGen[0][1] == 'X'){
      ++cornerCounter;
    }
    if(currGen[1][1] == 'X'){
      ++cornerCounter;
    }
    if(currGen[1][0] == 'X'){
      ++cornerCounter;
    }
    return cornerCounter;
  }

  if(classifyEdge == "TRC"){
    cornerCounter == 0;
    if(currGen[0][cols-2] == 'X'){
      ++cornerCounter;
    }
    if(currGen[1][cols-1] == 'X'){
      ++cornerCounter;
    }
    if(currGen[1][cols-2] == 'X'){
      ++cornerCounter;
    }
    return cornerCounter;
  }

  if(classifyEdge == "BRC"){
    cornerCounter = 0;
    if(currGen[rows-1][cols-2] == 'X'){
      ++cornerCounter;
    }
    if(currGen[rows-2][cols-1] == 'X'){
      ++cornerCounter;
    }
    if(currGen[rows-2][cols-2] == 'X'){
      ++cornerCounter;
    }
    return cornerCounter;
  }

  if(classifyEdge == "BLC"){
    cornerCounter = 0;
    if(currGen[rows-1][1] == 'X'){
      ++cornerCounter;
    }
    if(currGen[rows-2][1] == 'X'){
      ++cornerCounter;
    }
    if(currGen[rows-2][0] == 'X'){
      ++cornerCounter;
    }
    return cornerCounter;
  }
}

//new cell is a class that assigns the cel in the next generation depending on the neighbor count
char Game::newCell(int neighbors, int row, int col, char** currGen){
  if(neighbors < 1){
    return '-';
  }else if(neighbors == 2){
    return currGen[row][col];
  }else if(neighbors == 3){
    return 'X';
  }else{
    return '-';
  }
}


//play is a method that simply takes in the neccesary information for the game class to run properly and calls the correct class based on which game mode is being used
//Parameters- currGen = current generation of cells, mode = game mode being played, rows = rows in grid, cols = cols in grid
char** Game::play(char** currGen, int mode, int rows, int cols){

  Classic c;
  Donut d;
  Mirror m;
  if(mode == 1){
    return (c.playClassic(currGen, rows, cols));
  } else if(mode == 2){
    return (d.playDonut(currGen, rows, cols));
  }else{
    return ( m.playMirror(currGen, rows, cols));
  }
}
