#include <iostream>
#include <string>
#include <vector>
#include "inputVerification.hpp"

using std::vector,std::string;

class Board{
private:
    char BoardOutputs[3] = {'_','|',' '}; // Grid characters
    int size; // dimensions of square board
    string ListOfShips[5][2] = {{"Carrier", "5"},{"Battleship", "4"},{"Submarine","3"},{"Cruiser","3"},{"Destroyer","2"}};

protected:
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
    void printMiddleRow(vector<vector<char>> ValueBoard, int rowNum){
        int space = 0;
        int collumn = 0;
        while(space < size){
            std::cout << ' '<< ValueBoard[rowNum][collumn] << ' ';
            if (space != size-1){ // If its the final row of the board it doesn't need the closing |
                std::cout << BoardOutputs[1]; 
            }
            space++;
            collumn++;
        }
    
        std::cout << std::endl;
    }
    void printGameRow(int rownNum){
        //Prints the subrows into a game row
        printRow(2);
        printMiddleRow(gameboard,rownNum);
        printRow(0);
    }
public:
    Board(int Size){
        //Class constructor
        size = Size;
    }
    vector<vector<char>> gameboard;
    void ShipPlacer(){
        vector<vector<char>> backendBoard(size, vector<char>(size));
        for (int i = 0; i < size; i++){
            for (int j = 0; j < size; j++){
                backendBoard[i][j] = '0';
            }
        } //Creates a 2 dimensional vector with blank chars inside it
        gameboard = backendBoard;
    }

    
    void printBoard(){
        //prints all the rows into a board
        int row = 0;
        while(row < size-1){
            printGameRow(row);
            row++;
        }
        printRow(2);
        printMiddleRow(gameboard,row);
        printRow(2);
    }


};

int main(){
    int size;
    size = verifyInputs("How big do you want the board to be?");
    Board Player1 = Board(size);
    Board Player2 = Board(size);
    
    Player1.ShipPlacer();
    Player1.printBoard();
    Player2.ShipPlacer();
    Player2.printBoard();
    
    system("pause");
    return 0;
}