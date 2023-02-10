#include <iostream>
#include <string>
#include <vector>
#include "inputVerification.hpp"

using std::vector,std::string;

class Board{
private:
    char BoardOutputs[3] = {'_','|',' '}; // Grid characters
    int size; // dimensions of square board
public:
    Board(int Size){
        //Class constructor
        size = Size;
    }
    
    vector<vector<int>> ShipPositions(){
        //Will be a function to place ships
        vector<vector<int>> coords;
        return coords;
    }

    void printRow(int out){
        //prints the individual subrows of the gameboard
        int space = 0;
        while(space < size){
            std::cout << string(3, BoardOutputs[out]);
            if (space != size-1){ // If its the final row of the board it doesn't need the closing |
                std::cout << BoardOutputs[1]; 
            }
            space++;
        }
    
        std::cout << std::endl;

    }
    void printGameRow(){
        //Prints the subrows into a game row
        printRow(2);
        printRow(2);
        printRow(0);
    }
    void printBoard(){
        //prints all the rows into a board
        int row = 0;
        while(row < size-1){
            printGameRow();
            row++;
        }
        printRow(2);
        printRow(2);
        printRow(2);
    }


};

int main(){
    int size;
    size = verifyInputs("How big do you want the board to be?");
    Board Player1 = Board(size);
    Player1.printBoard();
    system("pause");
    return 0;
}