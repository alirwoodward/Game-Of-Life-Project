// Ali Woodward
// 2385718
// alwoodwadr@chapman.edu
// CPSC 350 Section 03
// Assignment	3- Game of life

#include "Simulation.h"
#include <unistd.h>
#include <stdexcept>

Simulation::Simulation(){
  //empty constructor
}

Simulation::~Simulation(){
   for(int i = 0; i < numRows; ++i) {
     delete[] currGen[i];
     delete[] newArray[i];
   }
   delete [] currGen;
   delete [] newArray;
}

//begin game is a method that runs all of the starting processes of the game
void Simulation::beginGame(){
  //choose starting map type
  getMapType();

  //if statements depending on what the previous answer was
  if(ogMapType == 1){
    //get text file with map
    getTextFile();
    //get game mode
    chooseGameMode();
    getPrinting();
    grid = new Grid();

    grid->createGrid(mapText);
    numRows = grid->getDimensions('r');
    numCols = grid->getDimensions('c');


  }else if(ogMapType == 2){
    // get row num, column num, and denisity of randomly generated map
    getNumRows();
    getNumCols();
    getDensity();
    //get game mode
    chooseGameMode();
    getPrinting();
    grid = new Grid(numRows, numCols);
    //cout << gameCount << endl;
    //++gameCount;
    grid->createGrid(numRows, numCols, popDensity);

  }else{
    cout << "Sorry! The number you have input is not a valid response... please try again and input option 1 or 2" << endl ;
    beginGame();
  }

  playGame();
}

//method that asks user for map type input
void Simulation::getMapType(){
  cout << "Please choose an option for your starting map: " << endl ;
  cout << "1. Import map from a text file \n2. Random assignment " << endl ;
   // Type a number and press enter
  cin >> ogMapType;
}

//method that asks user for file name
void Simulation::getTextFile(){

  cout << "Please enter the name of the text file that includes your starting map: " << endl ;
  cin >> mapText;

}

//method that asks user for game mode
void Simulation::chooseGameMode(){
  gameMode == 0;
  while(gameMode < 1 || gameMode > 3){
    cout << "What game mode would you like to execute?: " << endl;
    cout << "1. Classic \n2. Donut \n3. Mirror " << endl;
    cin >> gameMode;
    if(gameMode < 1 || gameMode > 3){
      cout<<"Invalid input! Please try again." << endl;
    }
  }
}

//method that asks user number of rows
void Simulation::getNumRows(){
  cout << "Enter the number of rows you would like your grid to have: " << endl ;
  cin >> numRows;
}

//method that asks user for number of rows
void Simulation::getNumCols(){
  cout << "Enter the number of columns you would like your grid to have: " << endl ;
  cin >> numCols;
}

//method that asks user for denisty of starting graph
void Simulation::getDensity(){
  cout << "Enter a number between 0 and 1 to represent the population density of your grid: " << endl ;
  cin >> popDensity;
}

//method that asks user for how they would like their output to be handled
void Simulation::getPrinting(){
  cout << "Enter how you would like your output to run: " << endl;
  cout << "1. Brief pause in between generations \n2. Press enter for next generation \n3. Print entire output to a file" << endl;
  cin >> printing;
  if(printing == 3){
    cout << "Please enter the name of the file you would like to print your output to: ";
    cin >> newFileName;
    outputFile.open(newFileName, ios::out);
  }
  if(printing > 3){
    cout << "Sorry! That is not a valid option. Please try again." << endl;
    getPrinting();
  }
}

//method that prints the generation number and entire grid
void Simulation::printArray(){

  if(printing == 1){
    sleep(1);
    cout << "Generation ";
    cout << gameCount << endl;

    char** array = grid->getArrayG();
    for(int i = 0; i < numRows; ++i){
      for(int j = 0; j < numCols; ++j){
          cout << array[i][j];
      }
      cout << "\n";
    }
  }else if(printing == 2){
    cin.get();
    cout << "Generation ";
    cout << gameCount << endl;

    char** array = grid->getArrayG();
    for(int i = 0; i < numRows; ++i){
      for(int j = 0; j < numCols; ++j){
          cout << array[i][j];
      }
      cout << "\n";
    }
  }else{

    outputFile << "Generation ";
    outputFile << gameCount << endl;

    char** array = grid->getArrayG();
    for(int i = 0; i < numRows; ++i){
      for(int j = 0; j < numCols; ++j){
          outputFile << array[i][j];
      }
      outputFile << "\n";
    }
  }
}

//method that carrys out the game as long as it can be played
void Simulation::playGame(){
  bool different = false;
  Game g;

  if(gameCount < 2){
    printArray();
    ++gameCount;
    playGame();
  }else{
    currGen = grid->getArrayG();
    newArray = g.play(currGen, gameMode, numRows, numCols);
    for(int i = 0; i < numRows; ++i){
      for(int j = 0; j < numCols; ++j){
        if(currGen[i][j] != newArray[i][j]){
          different = true;
          break;
        }
      }
      if(different == true){
        break;
      }
    }
    if(different == true){
      //copy and replce printing rn, need to add conditions to my print function
      grid->copyAndReplace(newArray);
      printArray();
      gameCount += 1;
      playGame();
    }else{
      endGame();
    }
  }

}

//method that is called when the grid is stabalized or empty to end the game
void Simulation::endGame(){
  if(printing == 2){
    cout << "Your game has ended! Please press enter to exit the program." << endl;
    cin.get();
    cout << "Program exited." << endl;
  }else{
    cout << "Your game has ended! Please press enter to exit the program." << endl;
    cin.get();
    cin.get();
    cout << "Program exited." << endl;
  }

}
