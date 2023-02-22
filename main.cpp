#include <iostream>
#include <string>
#include <vector>
#include "inputVerification.hpp"
#include <set>
#include <algorithm>

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
    int sunken = 0;

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
        int ValidDirections[4] = {-2,-1,1,2};
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
            }
            if (!check){
                break;
            }
            else{
                std::cout << "Enter a valid direction {-2,-1,1,2}" << std::endl;
            }
        }
        if (direction % 2 == 0){
            std::cout << yval -(direction/2 * std::stoi(ship[2]));
            if (yval -(direction/2 * std::stoi(ship[2]) -1) < 0 || yval - (direction/2 * std::stoi(ship[2])) > size){
                std::cout << "Ship cannot be placed at those coords with that direction, please try again" << std::endl;
                return 0;
                }                 
            for (int i = 0; i <std::stoi(ship[2]); i++){
                if (direction < 0){
                    if (gameboard[yval+i][xval] != ' '){
                        std::cout << "Ships can not be placed over each other" << std::endl;
                        return 0;
                    }
                }
                else{
                   if (gameboard[yval-i][xval] != ' '){
                        std::cout << "Ships can not be placed over each other" << std::endl;
                        return 0;
                    } 
                }
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
            std::cout << xval+1 + (direction * std::stoi(ship[2]) );
            if (xval+1 + (direction * std::stoi(ship[2]) ) < 0 || xval + (direction * std::stoi(ship[2]) ) > size){
                std::cout << "Ship cannot be placed at those coords with that direction, please try again" << std::endl;
                return 0;
            }
            for (int i = 0; i <std::stoi(ship[2]); i++){
                if (direction < 0){
                    if (gameboard[yval][xval-i] != ' '){
                        std::cout << "Ships can not be placed over each other" << std::endl;
                        return 0;
                    }
                }
                else{
                   if (gameboard[yval][xval+i] != ' '){
                        std::cout << "Ships can not be placed over each other" << std::endl;
                        return 0;
                    } 
                }
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
    
    vector<int> Fire(vector<vector<char>> OpposingBoard){ 
        int xval;int yval;
        while (true){
            xval = verifyInputs("Enter the x coordinate to fire at: ");
            if (xval < 0 || xval > size -1){
                std::cout << "Please enter a valid number" << std::endl;
            }
            else{
                break;
            }
        }
        while (true){
            yval = verifyInputs("Enter the y coordinate to fire at: ");
            if (yval < 0 || yval > size -1){
                std::cout << "Please enter a valid number" << std::endl;
            }
            else{
                break;
            }
        }
        std::cout << "Ships firing at " << xval << ',' << yval << std::endl;
        vector<int> coords = {xval,yval};
        if (OpposingBoard[yval][xval] == '0' || OpposingBoard[yval][xval] == '*'){
            std::cout << "You have already fired there" << std::endl;
            return Fire(OpposingBoard);
        }
        else if(OpposingBoard[yval][xval] != ' '){
            std::cout << "HIT" << std::endl;
            playboard[yval][xval] = '*';
        }
        else{
            std::cout << "MISS" << std::endl;
            playboard[yval][xval] = '0';

        }
        return coords;  
    }
    void ReceiveFire(vector<int> coords){
        vector<char> temp;
        char checker;
        
        //take input coods and return make changes based on hits /misses if no chars of type remain return sunk for that ship
        if(gameboard[coords[1]][coords[0]] != ' '){
            checker = gameboard[coords[1]][coords[0]];
            gameboard[coords[1]][coords[0]] = '*';
            for (int i = 0; i < gameboard.size(); i++){
                for (int j = 0; j < gameboard.size(); j++){
                    temp.push_back(gameboard[i][j]);
            }
            }
            if (std::count(temp.begin(),temp.end(),checker) == 0){
                std::cout << "Ship is sunk" << std::endl;
                sunken++;
            }
        }
        else{
            gameboard[coords[1]][coords[0]] == '0';
        }
    }
    
    void printBoard(vector<vector<char>> Board){
        //prints all the rows into a board11
        std::cout << std::endl;
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
    while (true){
        size = verifyInputs("How big do you want the board to be? min 5x5");
        if (size < 5){
            std::cout << "Board too small" << std::endl;
        }
        else{
            break;
        }
    }
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
                if (Player1.PlaceShip(Player1.ListOfShips[choice]) != 0){
                    Player1.ListOfShips.erase(Player1.ListOfShips.begin()+choice);
                }
                else{
                    continue;
                }
                Player1.printBoard(Player1.gameboard);
                break;
            }
        }
    }

    Player2.BoardInit();
    std::cout << "GameBoard" << std::endl;
    Player2.printBoard(Player2.gameboard);
    while(Player2.ListOfShips.size() != 0){
        std::cout << "Here are the available ships {Name, Character, Size}" << std::endl;
        for (int i = 0; i < Player2.ListOfShips.size(); i++){
            std::cout << i << ": "; for (string c: Player2.ListOfShips[i]){std::cout << c; }; std::cout << std::endl;
        }
        while (true){
            int choice; 
            choice = verifyInputs("Player 1 please select which ship you would like to place");
            if (choice < 0 || choice > Player2.ListOfShips.size()){
                std::cout << "Please enter a valid choice" << std::endl;
            }
            else{
                if (Player2.PlaceShip(Player2.ListOfShips[choice]) != 0){
                    Player2.ListOfShips.erase(Player2.ListOfShips.begin()+choice);
                }
                else{
                    continue;
                }
                Player2.printBoard(Player2.gameboard);
                break;
            }
        }
    }

    while(Player1.sunken != 5 || Player2.sunken != 5){
        vector<int> coordinates;
        std::cout << "Player 1 here is your board to play on" << std::endl;
        Player1.printBoard(Player1.playboard);
        coordinates = Player1.Fire(Player2.gameboard);
        Player2.ReceiveFire(coordinates);
        if (Player2.sunken == 5){
            std::cout << "Player 1 wins" << std::endl;
            break;
        }
        std::cout << "Player 2 here is your board to play on" << std::endl;
        Player2.printBoard(Player2.playboard);
        coordinates = Player2.Fire(Player1.gameboard);
        Player1.ReceiveFire(coordinates);
        if (Player1.sunken == 5){
            std::cout << "Player 2 wins" << std::endl;
            break;
        }
    }

    /*std::cout << "PlayingBoard" << std::endl;
    Player1.printBoard(Player1.playboard);*/
    system("pause");
    return 0;
}