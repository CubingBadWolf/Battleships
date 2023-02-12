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
    void printGameRow(vector<vector<char>> Board,int rownNum){
        //Prints the subrows into a game row
        printRow(2);
        printMiddleRow(Board,rownNum);
        printRow(0);
    }
public:
    Board(int Size){
        //Class constructor
        size = Size;
    }
    vector<vector<char>> gameboard;
    vector<vector<char>> playboard;
    void ShipPlacer(){
        vector<vector<char>> backendBoard(size, vector<char>(size));
        for (int q = 0; q < 2; q++){  
            for (int i = 0; i < size; i++){
                for (int j = 0; j < size; j++){
                    backendBoard[i][j] = '0';
                }
            } //Creates a 2 dimensional vector with blank chars inside it
            if(q == 0){
                gameboard = backendBoard;
                gameboard[size/2][size/2] = '*';//showing single element can be changed in one board.

            }
            else{
                playboard = backendBoard;
            }
        } // Initalised the two boards in the class.


    }

    
    void printBoard(vector<vector<char>> Board){
        //prints all the rows into a board
        int row = 0;
        while(row < size-1){
            printGameRow(Board, row);
            row++;
        }
        printRow(2);
        printMiddleRow(Board,row);
        printRow(2);
    }


};

int main(){
    int size;
    size = verifyInputs("How big do you want the board to be?");
    Board Player1 = Board(size);
    Board Player2 = Board(size);
    
    Player1.ShipPlacer();
    std::cout << "GameBoard" << std::endl;
    Player1.printBoard(Player1.gameboard);
    std::cout << "PlayingBoard" << std::endl;
    Player1.printBoard(Player1.playboard);

    system("pause");
    return 0;
}