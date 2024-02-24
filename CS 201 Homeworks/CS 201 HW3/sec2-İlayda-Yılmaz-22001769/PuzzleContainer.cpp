//
// Created by İlayda Zehra Yılmaz on 23.04.2022.
//

#include "PuzzleContainer.h"
#include <iostream>

using namespace std;
PuzzleContainer::PuzzleContainer(int h, int w) {
    height = h;
    width = w;
    curHeight = 0;
    rowLists = NULL;
}

PuzzleContainer::~PuzzleContainer() {
    for( int i = 1; i <= getHeight(); i++){
        if( rowLists != NULL && getRow(i) !=NULL ){
            removeRow(i);
        }
    }

}

int PuzzleContainer::getHeight() {
    return height;
}
int PuzzleContainer::getWidth() {
    return width;
}

bool PuzzleContainer::insertRow(int index) {
    if ( (index < 1) || (index > height) ){
        return false;
    }
    PuzzleRow* prev;
    PuzzleRow* cur;
    for(prev = NULL, cur = rowLists; ( cur!= NULL) && ( index > cur->getRowIndex() ); prev = cur, cur = cur->getNext());

    if( cur != NULL && cur->getRowIndex() == index ){
        return false;
    }

    if ( index == 1 ){
        if( (rowLists == NULL || rowLists->getRowIndex() > index) ){
            PuzzleRow* newRow = new PuzzleRow( width, index );
            newRow->setNext(rowLists);
            rowLists = newRow;
            curHeight++;
            return true;
        }
    }
    else{
        if( rowLists == NULL ){
            PuzzleRow* newRow = new PuzzleRow( width, index );
            newRow->setNext(rowLists);
            rowLists = newRow;
            curHeight++;
            return true;
        }
        else{
            if( prev == NULL ){
                PuzzleRow* newRow = new PuzzleRow( width, index );
                newRow->setNext(rowLists);
                rowLists = newRow;
                curHeight++;
                return true;
            }
            else{
                PuzzleRow* newRow = new PuzzleRow( width, index );
                newRow->setNext(prev->getNext());
                prev->setNext(newRow);
                curHeight++;

            }
        }
    }
    return true;
}

bool PuzzleContainer::removeRow( int index ){
    PuzzleRow* cur;

    if( ( index < 1 ) || ( index > height) ){
        return false;
    }
    if( rowLists == NULL ) {
        return false;
    }
    PuzzleRow* prev;
    for( prev = NULL, cur = rowLists; ( cur!= NULL) && ( index > cur->getRowIndex() ); prev = cur, cur = cur->getNext() );

    if( cur == NULL || cur->getRowIndex() != index ){
        return false;
    }
    if( index == 1 ){
        cur = rowLists;
        rowLists = rowLists->getNext();
        curHeight--;
    }
    else{
        if( cur == rowLists ) {
            rowLists = rowLists->getNext();
        }
        else{
            cur = prev->getNext();
            prev->setNext(cur->getNext());
        }
        curHeight--;
    }
    cur->setNext(NULL);
    delete cur;
    cur = NULL;
    //cout<< "curHeight: " <<curHeight<<endl;
    return true;
}

PuzzleRow *PuzzleContainer::getRow(int index) {
    if(!this){
        return NULL;
    }
    if( ( index < 1 ) || ( index > getHeight() ) ){
        return NULL;
    }
    else{
        PuzzleRow* prev;
        PuzzleRow* cur;
        for( prev = NULL, cur = rowLists; ( cur!= NULL) && ( index > cur->getRowIndex() ); prev = cur, cur = cur->getNext());
        if( cur == NULL ){
            return NULL;
        }
        if( cur->getRowIndex() == index ){
            return cur;
        }
        else{
            return NULL;
        }
    }
}

//Checks if the PuzzleContainer is empty
bool PuzzleContainer::isEmptyContainer() {
    return rowLists == NULL;
}

bool PuzzleContainer::addPiece(int row, int col, unsigned char shape) {

    bool isInserted;
    if ( row < 1 || row > getHeight() || col < 1 || col > getWidth() ){
        cout<<"(" << row << "," << col << ") is out of frame, it cannot be added"<< endl;
        return false;
    }
    else if( !(isEmptyContainer()) && getRow( row ) != NULL && !(getRow(row)->isEmpty()) && getRow(row)->find(col) != NULL ){
        cout<<"(" << row << "," << col << ") has already been occupied, it cannot be added"<<endl;
        return false;

    }
    else if( isColSuitable( row, col, shape) ){
        isInserted = insertRow(row);
        if( getRow(row)->insert(col,shape) ){
            cout<<"A piece is added to (" << row << "," << col << ")"<<endl;
            return true;

        }
        else{
            if( isInserted ){
                removeRow(row);
            }
            cout<<"Shape doesn't fit into (" << row << "," << col << "), it cannot be added"<<endl;
            return false;

        }
    }
    else{
        cout<<"Shape doesn't fit into (" << row << "," << col << "), it cannot be added"<<endl;
        return false;

    }
}

//Checks if the shape is suitable in its column by checking up and down patterns of the piece
// and comparing them with the same column's puzzle pieces in the previous and next row
bool PuzzleContainer::isColSuitable(int row, int col, unsigned char shape) {

    int down, up, right, left;
    int curDown, curUp, curRight, curLeft;
    int prevDown, prevUp, prevRight, prevLeft;

    //curses through the sorted linked list to find the place that this piece should fit
    PuzzleRow* prev;
    PuzzleRow* cur;
    for( prev = NULL, cur = rowLists; ( cur!= NULL) && ( row > cur->getRowIndex() ); prev = cur, cur = cur->getNext() );

    shapeConverter( shape, down, up, right, left );
    if( cur != NULL && cur->find(col) != NULL ){ //to not dereference the NULL node
        shapeConverter( cur->getPiece(col), curDown, curUp, curRight, curLeft );
    }
    if( prev != NULL && prev->find(col) != NULL ){ //to not dereference the NULL node
        shapeConverter( prev->getPiece(col), prevDown, prevUp, prevRight, prevLeft );
    }

    //NULL checks that are in the ifs and elses below enables us to put the piece in if there is no adjoining
    //puzzle piece to check
    //Rest of the checks are checking the conditions for the puzzle to fit by looking at its patterns
    if( getHeight() == 1 ){ // special case of height 1
        if( up == 2 && down == 2 ){
            return true;
        }
    }
    else if ( row == 1 ){ //special case for 1st row
        if( up == 2 && down != 2 ){
            if( cur == NULL || cur->find(col) == NULL){
                return true;
            }
            else if( cur->getRowIndex() == 2 ){
                if( (down == 0 && curUp == 1) || (down == 1 && curDown == 0)){
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
    else if ( row == getHeight() ){ //special case for last row
        if( down == 2 && up != 2 ){
            if( prev==NULL || prev->find(col) == NULL){
                return true;
            }
            else if( prev->getRowIndex() == getHeight() - 1 ){
                if( (up == 0 && prevDown == 1) || (up == 1 && prevDown == 0) ){
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
    else if( down != 2 && up != 2 ){ //if it is an inside puzzle piece (non-border)

        if( (prev == NULL|| prev->find(col) == NULL) && (cur==NULL || cur->find(col) == NULL)){
            return true;
        }
        else if( prev==NULL || prev->find(col) == NULL ){
            if( cur->getRowIndex() == row + 1 ){
                if( (down == 0 && curUp == 1) || (down == 1 && curUp == 0) ){
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
        else if( cur == NULL || cur->find(col) == NULL){
            if( prev->getRowIndex() == row - 1 ){
                if( (up == 0 && prevDown == 1) || (up == 1 && prevDown == 0) ){
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
            if( (prev->getRowIndex() == row - 1) && (cur->getRowIndex() == row + 1)){
                if( (prevDown == 1 && up == 0 && down == 0 && curUp == 1) ||
                    (prevDown == 1 && up == 0 && down == 1 && curUp == 0) ||
                    (prevDown == 0 && up == 1 && down == 1 && curUp == 0) ||
                    (prevDown == 0 && up == 1 && down == 0 && curUp == 1)){
                    return true;
                }
                else{
                    return false;
                }
            }
            else if ( prev->getRowIndex() == row - 1 ){
                if( (up == 0 && prevDown == 1) || (up == 1 && prevDown == 0) ){
                    return true;
                }
                else{
                    return false;
                }
            }
            else if( cur->getRowIndex() == row + 1 ){
                if( (down == 0 && curUp == 1) || (down == 1 && curUp == 0) ){
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

void PuzzleContainer::displayContainer() {
    if(!this){
        return;
    }
    cout<< "Container " << getHeight() <<"x" << getWidth() <<":"<<endl;
    if( isEmptyContainer() ){

        cout<<"  ";

        for(int j = 1; j <= getWidth(); j++){
            cout<< " " <<j <<" ";
        }
        cout<<endl;
        for( int i = 1; i <= getHeight(); i++){
            cout<< i <<" ";
            for(int j = 1; j <= getWidth(); j++){
                cout<<" O ";
            }
            cout<<endl;
        }
        return;
    }

    cout<<"  ";

    for(int j = 1; j <= getWidth(); j++){
        cout<< " " <<j <<" ";
    }
    cout<<endl;
    for( int i = 1; i <= getHeight(); i++){
        PuzzleRow* prev;
        PuzzleRow* cur;
        for( prev = NULL, cur = rowLists; ( cur!= NULL) && ( i > cur->getRowIndex() ); prev = cur, cur = cur->getNext() );
        cout<< i <<" ";
        if( cur == NULL || cur->getRowIndex() != i ){
            for(int j = 1; j <= getWidth(); j++){
                cout<<" O ";
            }
            cout<<endl;
        }
        else{
            cur->printRow();
        }
    }
    cout<<endl;
}

void PuzzleContainer::showRow(int row) {
    if( ( row < 1 ) || ( row > getHeight() ) ){
        cout<<"Row "<< row << " is out of border"<<endl;
        return;
    }

    cout<<"Row "<< row << ":"<<endl;
    if( getRow(row) == NULL ){
        for(int j = 1; j <= getWidth(); j++){
            cout<<" O ";
        }
        cout<<endl;
    }
    else{
        getRow(row)->printRow();
    }

}

void PuzzleContainer::showColumn(int col) {
    if( ( col < 1 ) || ( col > getWidth() ) ){
        cout<<"Column "<< col << " is out of border"<<endl;
        return;
    }
    cout<<"Column "<< col << ":"<<endl;
    for( int i = 1; i <= getHeight(); i++){
        PuzzleRow* prev;
        PuzzleRow* cur;
        for( prev = NULL, cur = rowLists; ( cur!= NULL) && ( i > cur->getRowIndex() ); prev = cur, cur = cur->getNext() );
        if( cur == NULL || cur->getRowIndex() != i ){
            cout<<" O ";
        }
        else{
            if( cur->getPiece(col) != 255){
                cout<<" X ";
            }
            else{
                cout<<" O ";
            }
        }
        cout<<endl;
    }
}


void PuzzleContainer::showPiece(int row, int col) {

    if( ( col < 1 ) || ( col > getWidth() ) ){ //If col is out of bounds
        cout<<"("<<row<<","<<col<<") is out of frame, it cannot be shown"<<endl;
        return;
    }
    if( ( row < 1 ) || ( row > getHeight() ) ){ //If row is out of bounds
        cout<<"("<<row<<","<<col<<") is out of frame, it cannot be shown"<<endl;
        return;
    }
    if( getRow(row) == NULL ){ //If there is no row like this
        cout<<"There is no piece on ("<<row<<","<<col<<"), it cannot be shown"<<endl;
        return;
    }
    if((getRow(row)->getPiece(col)) == 255 ){ //If there is no piece
        cout<<"There is no piece on ("<<row<<","<<col<<"), it cannot be shown"<<endl;
        return;
    }
    else{ //If there is piece
        cout<<"Piece on ("<<row<<","<<col<<") as following:"<<endl;
        int down, up, right, left;

        //Prints the shape
        shapeConverter( getRow(row)->getPiece(col), down, up, right, left);
        cout<<"Down: ";
        printPattern(down);
        cout<<"Up: ";
        printPattern(up);
        cout<<"Right: ";
        printPattern(right);
        cout<<"Left: ";
        printPattern(left);
    }
}

//Prints what the input pattern is by looking at the input value
void PuzzleContainer::printPattern(int pattern) {
    if( pattern == 0 ){
        cout<<"Hole"<<endl;
    }
    else if( pattern == 1 ){
        cout<<"Knob"<<endl;
    }
    else if( pattern == 2 ){
        cout<<"Border"<<endl;
    }
}

void PuzzleContainer::findPiece(unsigned char shape) {
    int shapeCount = 0;

    //gets all the pieces like this in this loops
    for( int i = 1; i <= getHeight(); i++){
        if( getRow(i) != NULL ){
            for(int j = 1; j <= getWidth(); j++){
                if( getRow(i)->getPiece(j) == shape ){
                    if( shapeCount == 0 ){ //to align the comma
                        cout<<"("<<i<<","<<j<<")";
                    }
                    else{
                        cout<<",("<<i<<","<<j<<")";
                    }
                    shapeCount++;
                }
            }
        }
    }

    if( shapeCount != 0 ){
        cout<<" contain the piece that has shape"<<endl;

        //Prints the shape
        int down, up, right, left;
        shapeConverter( shape, down, up, right, left);
        cout<<"Down: ";
        printPattern(down);
        cout<<"Up: ";
        printPattern(up);
        cout<<"Right: ";
        printPattern(right);
        cout<<"Left: ";
        printPattern(left);
    }
    else{
        cout<<"There is no piece that has shape"<<endl;

        //Prints the shape
        int down, up, right, left;
        shapeConverter( shape, down, up, right, left);
        cout<<"Down: ";
        printPattern(down);
        cout<<"Up: ";
        printPattern(up);
        cout<<"Right: ";
        printPattern(right);
        cout<<"Left: ";
        printPattern(left);
    }
}

bool PuzzleContainer::removePiece(int row, int col) {

    if( ( row < 1 ) || ( row > getHeight()) || ( col < 1 ) || ( col > getWidth())){
        cout<<"("<<row<<","<<col<<") is out of frame, it cannot be removed"<<endl;
        return false;
    }

    if( rowLists == NULL || getRow(row) == NULL || getRow(row)->find(col) == NULL ){
        cout<<"There is no piece on ("<<row<<","<<col<<"), it cannot be removed"<<endl;
        return false;
    }
    else{ //If there is piece like this remove it
        getRow(row)->remove(col);
        if( getRow(row)->getCurSize() == 0 ){ //If there is no piece left remove row
            removeRow(row);
        }
    }
    cout<<"The piece on ("<<row<<","<<col<<") is removed"<<endl;
    return true;
}