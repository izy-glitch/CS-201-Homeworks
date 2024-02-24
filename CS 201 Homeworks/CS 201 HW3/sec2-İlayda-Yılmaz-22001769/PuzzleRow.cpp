//
// Created by İlayda Zehra Yılmaz on 23.04.2022.
//

#include "PuzzleContainer.h"
#include <iostream>

using namespace std;

PuzzleRow::PuzzleRow(int size, int rowindex){
    maxSize = size;
    curSize = 0;
    this->rowindex = rowindex;
    head = NULL;
    next = NULL;
}

PuzzleRow::~PuzzleRow() {
    for( int i = 1; i <= maxSize; i++){
        PuzzlePiece* prev;
        PuzzlePiece* cur;
        for( prev = NULL, cur = head; ( cur!= NULL) && ( i > cur->colindex ); prev = cur, cur = cur->next );
        if( cur != NULL && cur->colindex == i ){
            remove(i);
        }
    }
}

int PuzzleRow::getRowIndex() {
    return rowindex;
}

void PuzzleRow::setNext(PuzzleRow *next) {
    this->next = next;
}

PuzzleRow* PuzzleRow::getNext() {
    return next;
}

bool PuzzleRow::insert(int index, unsigned char shape) {

    if ( (index < 1) || (index > maxSize) ){
        //cout<< "curSize: " <<curSize<<endl;
        return false;
    }

    PuzzlePiece* prev;
    PuzzlePiece* cur;
    for( prev = NULL, cur = head; ( cur!= NULL) && ( index > cur->colindex ); prev = cur, cur = cur->next );

    if( cur != NULL && cur->colindex == index ){
        //cout<< "curSize: " <<curSize<<endl;
        return false;
    }


    if ( index == 1 ){
        if( (head == NULL || head->colindex > index) && isRowSuitable(index, shape) ){

            PuzzlePiece* newPuzzle = new PuzzlePiece;
            newPuzzle->shape = shape;
            newPuzzle->colindex = index;
            newPuzzle->rowindex = rowindex;
            newPuzzle->next = NULL;

            newPuzzle->next = head;
            head = newPuzzle;
            curSize++;
            //cout<< "curSize: " <<curSize<<endl;
            return true;
        }
    }
    else{
        if( head == NULL && isRowSuitable(index, shape) ){

            PuzzlePiece* newPuzzle = new PuzzlePiece;
            newPuzzle->shape = shape;
            newPuzzle->colindex = index;
            newPuzzle->rowindex = rowindex;
            newPuzzle->next = NULL;

            newPuzzle->next = head;
            head = newPuzzle;
            curSize++;
            //cout<< "curSize: " <<curSize<<endl;
            return true;
        }
        else{
            if( prev == NULL && isRowSuitable(index, shape) ){

                PuzzlePiece* newPuzzle = new PuzzlePiece;
                newPuzzle->shape = shape;
                newPuzzle->colindex = index;
                newPuzzle->rowindex = rowindex;
                newPuzzle->next = NULL;

                newPuzzle->next = head;
                head = newPuzzle;
                curSize++;
                //cout<< "curSize: " <<curSize<<endl;
                return true;
            }
            else{
                if( isRowSuitable(index, shape) ){

                    PuzzlePiece* newPuzzle = new PuzzlePiece;
                    newPuzzle->shape = shape;
                    newPuzzle->colindex = index;
                    newPuzzle->rowindex = rowindex;
                    newPuzzle->next = NULL;

                    newPuzzle->next = prev->next;
                    prev->next = newPuzzle;
                    curSize++;
                    //cout<< "curSize: " <<curSize<<endl;
                    return true;
                }
            }
        }
    }
    return false;
}

//Finds and returns the linked list of the given column index in this row
PuzzleRow::PuzzlePiece* PuzzleRow::find(int index) {
    if( ( index < 1 ) || ( index > maxSize ) ){ //check out of bounds
        return NULL;
    }
    else{

        //curse through link list until we have found the node
        PuzzlePiece* prev;
        PuzzlePiece* cur;
        for( prev = NULL, cur = head; ( cur!= NULL) && ( index > cur->colindex ); prev = cur, cur = cur->next );
        if( cur == NULL ){
            return NULL;
        }
        else if( cur->colindex == index ){
            return cur;
        }
        else{
            return NULL;
        }
    }
}


bool PuzzleRow::remove( int index ){
    PuzzlePiece* cur;

    if( ( index < 1 ) || ( index > maxSize) ){
        return false;
    }
    if( head == NULL ) {
        return false;
    }
    PuzzlePiece* prev;
    for( prev = NULL, cur = head; ( cur!= NULL) && ( index > cur->colindex ); prev = cur, cur = cur->next );

    if( cur == NULL || cur->colindex != index ){
        return false;
    }
    if( index == 1 ){
        cur = head;
        head = head->next;
        curSize--;
    }
    else{
        if( cur == head ) {
            head = head->next;
        }
        else{
            cur = prev->next;
            prev->next = cur->next;
        }
        curSize--;
    }
    cur->next = NULL;
    delete cur;
    cur = NULL;
    //cout<< "curSize: " <<curSize<<endl;
    return true;
}

bool PuzzleRow::isEmpty() {
    return head == NULL;
}

unsigned char PuzzleRow::getPiece( int index ) {
    if( ( index < 1 ) || ( index > maxSize) ){
        return 255;
    }
    if( head == NULL) {
        return 255;
    }
    PuzzlePiece* prev;
    PuzzlePiece* cur;
    for( prev = NULL, cur = head; ( cur!= NULL) && ( index > cur->colindex ); prev = cur, cur = cur->next );
    if( cur == NULL || cur->colindex != index ){
        return 255;
    }
    else{
        return cur->shape;
    }
}

void PuzzleRow::printRow() {
    if(!this){
       return;
    }
    if( isEmpty() ){
        for( int i = 1; i <= maxSize; i++){
            cout<< " O ";
        }
        return;
    }
    for( int i = 1; i <= maxSize; i++){
        PuzzlePiece* prev;
        PuzzlePiece* cur;
        for( prev = NULL, cur = head; ( cur!= NULL) && ( i > cur->colindex ); prev = cur, cur = cur->next );
        if( cur == NULL || cur->colindex != i ){
            cout<< " O ";
        }
        else{
            cout<< " X ";
        }
    }
    cout<<endl;
}

//This method is not used and only written for test purposes
//Prints the column index for every linked list currently in the row
void PuzzleRow::printRowColIndex(struct PuzzlePiece *head) {
    while ( head != NULL ){
        cout<< head->colindex;
        cout<<"->";
        head = head->next;
    }

    cout<<"NULL";
}

//Gets the curSize which is the current amount of non-empty rows in the linked list
int PuzzleRow::getCurSize() {
    return curSize;
}

//Checks if the shape is suitable in its row by checking right and left patterns of the piece
// and comparing them with the same column's puzzle pieces in the previous and next row
bool PuzzleRow::isRowSuitable(int index, unsigned char shape) {

    int down, up, right, left;
    int curDown, curUp, curRight, curLeft;
    int prevDown, prevUp, prevRight, prevLeft;

    //curses through the sorted linked list to find the place that this piece should fit
    PuzzlePiece* prev;
    PuzzlePiece* cur;
    for( prev = NULL, cur = head; ( cur!= NULL) && ( index > cur->colindex ); prev = cur, cur = cur->next );

    shapeConverter( shape, down, up, right, left );
    if( cur != NULL ){ //to not dereference the NULL node
        shapeConverter( cur->shape, curDown, curUp, curRight, curLeft );
    }
    if( prev != NULL ){ //to not dereference the NULL node
        shapeConverter( prev->shape, prevDown, prevUp, prevRight, prevLeft );
    }

    //NULL checks that are in the ifs and elses below enables us to put the piece in if there is no adjoining
    //puzzle piece to check
    //Rest of the checks are checking the conditions for the puzzle to fit by looking at its patterns

    if( maxSize == 1 ){ //special case for maxSize 1
       if( left == 2 && right == 2 ){
           return true;
       }
    }
    else if ( index == 1 ){ //special case for the 1st column
        if( left == 2 && right != 2 ){
            if( cur == NULL ){
                return true;
            }
            else if( cur->colindex == 2 ){
                if( (right == 0 && curLeft == 1) || (right == 1 && curLeft == 0)){
                    return true;
                }
                else{
                    return false;
                }
            }
            else{
                return true;
            }
        }
        else{
            return false;
        }
    }
    else if ( index == maxSize ){ //special case for the last column
        if( right == 2 && left != 2 ){
            if( prev==NULL ){
                return true;
            }
            else if( prev->colindex == maxSize - 1 ){
                if( (left == 0 && prevRight == 1) || (left == 1 && prevRight == 0) ){
                    return true;
                }
                else{
                    return false;
                }
            }
            else{
                return true;
            }
        }
        else{
            return false;
        }
    }
    else if( right != 2 && left != 2 ){ // if it is an inside puzzle (non-border)

        if( prev == NULL && cur==NULL ){
            return true;
        }
        else if( prev==NULL ){
            if( cur->colindex == index + 1 ){
                if( (right == 0 && curLeft == 1) || (right == 1 && curLeft == 0) ){
                    return true;
                }
                else{
                    return false;
                }
            }
            else{
                return true;
            }

        }
        else if( cur == NULL ){
            if( prev->colindex == index - 1 ){
                if( (left == 0 && prevRight == 1) || (left == 1 && prevRight == 0) ){
                    return true;
                }
                else{
                    return false;
                }
            }
            else{
                return true;
            }
        }
        else{
            if( (prev->colindex == index - 1) && (cur->colindex == index + 1)){
                if( (prevRight == 1 && left == 0 && right == 0 && curLeft == 1) ||
                    (prevRight == 1 && left == 0 && right == 1 && curLeft == 0) ||
                    (prevRight == 0 && left == 1 && right == 1 && curLeft == 0) ||
                    (prevRight == 0 && left == 1 && right == 0 && curLeft == 1)){
                    return true;
                }
                else{
                    return false;
                }
            }
            else if ( prev->colindex == index - 1 ){
                if( (left == 0 && prevRight == 1) || (left == 1 && prevRight == 0) ){
                    return true;
                }
                else{
                    return false;
                }
            }
            else if( cur->colindex == index + 1 ){
                if( (right == 0 && curLeft == 1) || (right == 1 && curLeft == 0) ){
                    return true;
                }
                else{
                    return false;
                }
            }
            else {
                return false;
            }

        }

    }

    return false;

}
