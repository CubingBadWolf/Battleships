#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include "inputVerification.hpp"

using std::vector,std::string;

class Board{
private:
    char BoardOutputs[3] = {'_','|',' '}; // Grid characters
    int size; // dimensions of square board
    vector<string> ListOfShips = {"Carrier (5)", "Battleship (4)", "Cruiser (3)", "Submarine (3)", "Destroyer (2)"};

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
    void boardsInit(){
        vector<vector<char>> backendBoard(size, vector<char>(size));
        for (int q = 0; q < 2; q++){  
            for (int i = 0; i < size; i++){
                for (int j = 0; j < size; j++){
                    backendBoard[i][j] = ' ';
                }
            } //Creates a 2 dimensional vector with blank chars inside it
            if(q == 0){
                gameboard = backendBoard;
                gameboard[0][1] = '*';//showing single element can be changed in one board.

            }
            else{
                playboard = backendBoard;
            }
        } // Initalised the two boards in the class.
    }

    void shipPlacer(vector<vector<char>> Board){
        int c =0;
        while (c < 6){
            string shipType;
            printBoard(gameboard);
            std::cout << "Enter which ship you would like to place"; std::cin >> shipType;

            for(int i; i < ListOfShips.size(); i++){
                string item = ListOfShips[i];
                if (item.substr(0, shipType.size()) == shipType){
                    int lengthOfShip;
                    for(int i; i < item.size(); i++){
                        if (isdigit(item[i]) == 0){
                            continue;
                        }
                        else{
                            lengthOfShip = stoi(string(1,item[1]));
                        }
                    }
                    int xval; int yval;
                    while (true){
                        xval = verifyInputs("Enter your x coordinate to start placing");
                        if (xval < 0 || xval >= size){
                            std::cout << "Please enter a valid number (Between 0 and " << size << ")" << std::endl;
                        }
                        else{
                            break;
                        }
                    }
                    while (true){
                        yval = verifyInputs("Enter your y coordinate to start placing");
                        if (yval < 0 || yval >= size){
                            std::cout << "Please enter a valid number (Between 0 and " << size << ")" << std::endl;
                        }
                        else{
                            break;
                        }
                    }
                    string direction;
                    int directionVal; // up = 0, right = 1, down = 2, left = 3
                    while (true){
                        std::cout << "Please enter what direction to enter the ship in: ";
                        std::cin >> direction;
                        std::transform(direction.begin(), direction.end(), direction.begin(), ::tolower);

                        if (direction == "up"){
                            if (yval - lengthOfShip < 0){
                                std::cout << "Error ship can not be placed in that position";
                                continue;
                            }
                            else{
                                for(int i = 0; i < lengthOfShip; i++){
                                    gameboard[yval-i][xval] = (char(lengthOfShip)+48);
                                }
                                break;
                            }
                        }
                        else if (direction == "right"){
                            if (xval + lengthOfShip > size-1){
                                std::cout << "Error ship can not be placed in that position";
                                continue;
                            }
                            else{
                                for(int i = 0; i < lengthOfShip; i++){
                                    gameboard[yval][xval+i] = (char(lengthOfShip)+48);
                                }
                                break;
                            }
                        }
                        else if (direction == "down"){
                            if (yval + lengthOfShip > size){
                                std::cout << "Error ship can not be placed in that position";
                                continue;
                            }
                            else{
                                for(int i = 0; i < lengthOfShip; i++){
                                    gameboard[yval+i][xval] = (char(lengthOfShip)+48);
                                }
                                break;
                            }
                            
                        }
                        else if (direction == "left"){
                            if (xval - lengthOfShip < 0){
                                std::cout << "Error ship can not be placed in that position";
                                continue;
                            }
                            else{
                                for(int i = 0; i < lengthOfShip; i++){
                                    gameboard[yval][xval-i] = (char(lengthOfShip)+48);
                                }
                                break;
                            }
                            
                        }
                        else{
                            std::cout << "Please enter up, right, down or left" << std::endl;
                        }
                    }
                    ListOfShips.erase(ListOfShips.begin() + i);
                    break;
                }
                    
                else{
                    continue;
                }

            }
            std::cout << "Please enter a valid ship (Check if capitalisation is correct.)" << std::endl;
            c++;
        }
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
    

    Player1.boardsInit();
    Player1.shipPlacer(Player1.gameboard);
    Player1.printBoard(Player1.gameboard);
    Player1.printBoard(Player1.playboard);

    system("pause");
    return 0;
}