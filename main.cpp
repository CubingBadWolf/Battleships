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

    int PlaceShip(vector<string> ship){ //direction keys = -2 down, 2 up, -1 left, 1 right
    //TODO placed ships cant overlap other ships already placed
        int xval;int yval;
        int direction;
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
        int ValidDirections[4] = {-2,-1,1,-2};
        string Directions[4] = {"down", "left", "right", "up"};
        bool check = true;
        while (check){
            std::cout << "Enter the direction you want to enter the ship in from the coords " << xval << ',' << yval << std::endl;
            for (int i =0; i < 4; i++){
                std::cout << ValidDirections[i] << ": " << Directions[i] << std::endl;
            }
            direction = verifyInputs("");
            for(int i = 0; i < 4; i++){
                if(ValidDirections[i] == direction){
                    check = false;
                    break;
                }
            std::cout << "Enter a valid direction {-2,-1,1,2}" << std::endl;
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
            if (xval -(direction * std::stoi(ship[2]) < 0)){
                std::cout << "Ship cannot be placed at those coords with that direction, please try again" << std::endl;
                return 0;
            }
            
            for(int i = 0; i <std::stoi(ship[2]); i++){
                if (direction < 0){
                    gameboard[yval][xval-i] = char(ship[1][0]);
                }
                else{
                    gameboard[yval][xval+i] = char(ship[1][0]);
                }
            }
        }
       return 1;
    }
    void printBoard(vector<vector<char>> Board){
        //prints all the rows into a board11
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
    while(Player1.ListOfShips.size() != 0){
        std::cout << "Here are the available ships {Name, Character, Size}" << std::endl;
        for (int i = 0; i < Player1.ListOfShips.size(); i++){
            std::cout << i << ": "; for (string c: Player1.ListOfShips[i]){std::cout << c; }; std::cout << std::endl;
        }
        while (true){
        int choice; 
        choice = verifyInputs("Player 1 please select which ship you would like to place");
        if (choice < 0 || choice > Player1.ListOfShips.size()){
            std::cout << "Please enter a valid choice" << std::endl;
        }
        else{
            Player1.PlaceShip(Player1.ListOfShips[choice]);
            Player1.ListOfShips.erase(Player1.ListOfShips.begin()+choice);
            break;
        }
        }
    }
    Player1.printBoard(Player1.gameboard);

    /*std::cout << "PlayingBoard" << std::endl;
    Player1.printBoard(Player1.playboard);*/
    system("pause");
    return 0;
}