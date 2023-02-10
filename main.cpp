#include <iostream>
#include <string>
#include <vector>
#include "inputVerification.hpp"

using std::vector,std::string;

class Board{
private:
    char BoardOutputs[3] = {'_','|',' '};
    int size;
public:
    Board(int Size){
        size = Size;
    }
    vector<int> ShipPositions(){

    }
    void printRow(int out){
        int space = 0;
        for (int i = 0; i < 3; i++){ 
            while(space < size){
                std::cout << string(3, BoardOutputs[out]);
                if (space != size-1){
                    std::cout << BoardOutputs[1];
                }
                space++;
            }
        }
        std::cout << std::endl;

    }
    void printGameRow(){
        printRow(2);
        printRow(2);
        printRow(0);
    }
    void printBoard(){
    
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