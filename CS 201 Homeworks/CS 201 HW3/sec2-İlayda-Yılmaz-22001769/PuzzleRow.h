//
// Created by İlayda Zehra Yılmaz on 26.04.2022.
//

#ifndef CS201_HW3_PUZZLECONTAINER_PUZZLEROW_H
#define CS201_HW3_PUZZLECONTAINER_PUZZLEROW_H

#include <iostream>
using namespace std;
namespace{
    void shapeConverter(unsigned char shape, int& down, int& up, int& right, int& left){
        down = shape%4;
        up = (shape/4)%4;
        right= (shape/16)%4;
        left= shape/64;
    }
}

class PuzzleRow{
private:
    struct PuzzlePiece{
        unsigned char shape;
        int rowindex;
        int colindex;
        PuzzlePiece* next;
    };
    PuzzlePiece* head;
    PuzzleRow* next;
    int rowindex;
    int maxSize; //equals to puzzleContainer width
    int curSize; //the current amount of non-empty rows in the linked list

public:
    PuzzleRow( int size, int rowindex);
    ~PuzzleRow();
    int getRowIndex();
    void setNext( PuzzleRow* next );
    PuzzleRow* getNext();
    bool insert( int index, unsigned char shape );
    bool remove( int index );
    bool isEmpty();
    unsigned char getPiece(int index );
    void printRow();
    void printRowColIndex( struct PuzzlePiece* head );
    bool isRowSuitable( int index, unsigned char shape );
    PuzzlePiece* find( int index );
    int getCurSize();
};


#endif //CS201_HW3_PUZZLECONTAINER_PUZZLEROW_H
