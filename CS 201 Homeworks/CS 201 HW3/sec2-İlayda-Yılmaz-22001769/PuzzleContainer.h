//
// Created by İlayda Zehra Yılmaz on 23.04.2022.
//

#ifndef CS201_HW3_PUZZLECONTAINER_PUZZLECONTAINER_H
#define CS201_HW3_PUZZLECONTAINER_PUZZLECONTAINER_H
#include <iostream>
#include "PuzzleRow.h"

using namespace std;

class PuzzleContainer{
private:
    PuzzleRow* rowLists;
    int height;
    int width;
    int curHeight; //the current amount of non-empty rows in the linked list
public:
    PuzzleContainer( int h, int w);
    ~PuzzleContainer();
    PuzzleRow* getRow( int index );
    bool insertRow( int index );
    bool removeRow( int index );
    bool addPiece( int row, int col , unsigned char shape );
    bool removePiece(int row, int col);
    int getHeight();
    int getWidth();
    void showPiece(int row, int col);
    void displayContainer();
    void showColumn(int col);
    void showRow(int row);
    void findPiece(unsigned char shape);
    bool isEmptyContainer();
    bool isColSuitable( int row, int col, unsigned char shape );
    void printPattern( int pattern );
};


#endif //CS201_HW3_PUZZLECONTAINER_PUZZLECONTAINER_H
