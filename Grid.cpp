// Ali Woodward
// 2385718
// alwoodwadr@chapman.edu
// CPSC 350 Section 03
// Assignment	3- Game of life

#include "Grid.h"
#include <iomanip>

// Grid.cpp is a class that is charge on managing the main grid for the game
// the Grid class contains methods called createGrid, copyAndReplace, getDimensions, and getArrayG

Grid::Grid(){
//default empty

}

Grid::Grid(int rows, int cols){
  //initialize 2d array now that we have row and column numbers
  currGen = new char*[rows];
  for (int i = 0; i <  rows; i++){
     currGen[i] = new char[cols];
  }
}

Grid::~Grid(){
  //destructor
  for(int i = 0; i < rows; ++i) {
        delete[] currGen[i];
    }
  delete [] currGen;

}

//creates the starting grid from a text file input
void Grid::createGrid(string gridFile){

   //game = new Game();
   //open file for reading
   fstream grid;
   grid.open(gridFile, ios::in);

   if (grid.is_open())
   {
     //get row and column numbers from first two lines of the code
     std::string numRows;
     std::string numCols;
     getline (grid, numRows);
     getline(grid, numCols);
     rows = stoi(numRows);
     cols = stoi(numCols);

     //initialize 2d array now that we have row and column numbers
     currGen = new char*[rows];
     for (int i = 0; i <  rows; i++){
        currGen[i] = new char[cols];
     }

     //while loop will go through rest of the file (lines with actual mapped cells)
     string currLine;
     //count initialized to keep track of what row it should be adding to
     int count = 0;
     while ( getline (grid,currLine) ){
        //for each char in the current file line, added to correct index of the 2d array
         for(int i = 0; i < currLine.size(); i++){
           currGen[count][i] = currLine[i];
          }
          ++count;
       }

    }

    //return currGen;
}

//creates a starting grid with dimension and density inputs
void Grid::createGrid(int row, int col, double density){
  rows = row;
  cols = col;


  int numElements = rows*cols; //number of elemnts in the array
  int numFill = numElements*density; //number of elements that need to be filled with a cell

  int randRow;
  int randCol;
  srand(time(0));
  for(int a = 0; a < numFill; ++a){
    randRow = rand() % (rows); // maybe +1
    randCol = rand() % (cols);
    if(currGen[randRow][randCol] == 'X'){
      --a;
      continue;
    }else{
      currGen[randRow][randCol] = 'X';
    }
  }

  for (int i = 0; i < rows; i++)
  {
     for (int j = 0; j < cols; j++)
     {
         if(currGen[i][j] == 'X'){
         }else{
           currGen[i][j] = '-';
         }
     }
  }

}


//this function takes in a new array and and copies it over to the actual grid
void Grid::copyAndReplace(char **newArray){


  for (int a = 0; a < rows; a++)
  {
     for (int b = 0; b < cols; b++)
     {
      currGen[a][b] = newArray[a][b];

     }
  }
}


//this returns the dimensiosn for row and col
int Grid::getDimensions(char rowOrCol){
  if(rowOrCol == 'r'){
    return rows;
  }else{
    return cols;
  }
}

//this returns the current array
char** Grid::getArrayG(){
  return currGen;
}
