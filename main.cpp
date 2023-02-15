#include <iostream>
#include <string>
#include <vector>
#include "inputVerification.hpp"

using std::vector,std::string;

class Board{
private:
    char BoardOutputs[3] = {'_','|',' '}; // Grid characters
    int size; // dimensions of square board

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
    vector<vector<string>> ListOfShips = {{"Carrier", "C", "5"},{"Battleship", "B", "4"},{"Submarine", "S","3"},{"Cruiser", "c", "3"},{"Destroyer", "D", "2"}};
    Board(int Size){
        //Class constructor
        size = Size;
    }
    vector<vector<char>> gameboard;
    vector<vector<char>> playboard;
    void BoardInit(){
        vector<vector<char>> backendBoard(size, vector<char>(size));
        for (int q = 0; q < 2; q++){  
            for (int i = 0; i < size; i++){
                for (int j = 0; j < size; j++){
                    backendBoard[i][j] = ' ';
                }
            } //Creates a 2 dimensional vector with blank chars inside it
            if(q == 0){
                gameboard = backendBoard;

            }
            else{
                playboard = backendBoard;
            }
        } // Initalised the two boards in the class.
    }

    int PlaceShip(vector<string> ship, int direction){ //direction keys = -2 down, 2 up, -1 left, 1 right
        int xval;int yval;
        while (true){
            xval = verifyInputs("Enter the x coordinate to begin placing: ");
            if (xval < 0 || xval > size -1){
                std::cout << "Please enter a valid number" << std::endl;
            }
            else{
                break;
            }
        }
        while (true){
            yval = verifyInputs("Enter the y coordinate to begin placing: ");
            if (yval < 0 || yval > size -1){
                std::cout << "Please enter a valid number" << std::endl;
            }
            else{
                break;
            }
        }

        if (direction % 2 == 0){
            if (yval -(direction/2 * std::stoi(ship[2])) < 0){
                std::cout << "Ship cannot be placed at those coords with that direction, please try again" << std::endl;
                return 0;
                }                 

            for(int i = 0; i <std::stoi(ship[2]); i++){
                if (direction < 0){
                    gameboard[yval+i][xval] = char(ship[1][0]);
                }
                else{
                    gameboard[yval-i][xval] = char(ship[1][0]);
                }
            }
        }
        else{
            try{
                if (xval +(direction/2 * std::stoi(ship[2]) < 0)){
                    throw(418);
                }
            }
            catch(...){
                std::cout << "Ship cannot be placed at those coords with that direction, please try again" << std::endl;
                return 0;
            }
            for(int i = 0; i <std::stoi(ship[2]); i++){
                if (direction < 0){
                    gameboard[yval][xval-i] = char(ship[1][0]);
                }
                else{
                    gameboard[yval][xval-i] = char(ship[1][0]);
                }
            }
        }
       return 1;
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
    
    Player1.BoardInit();
    std::cout << "GameBoard" << std::endl;
    Player1.printBoard(Player1.gameboard);
    Player1.PlaceShip(Player1.ListOfShips[0], -2);
    Player1.printBoard(Player1.gameboard);

    /*std::cout << "PlayingBoard" << std::endl;
    Player1.printBoard(Player1.playboard);*/

    system("pause");
    return 0;
}