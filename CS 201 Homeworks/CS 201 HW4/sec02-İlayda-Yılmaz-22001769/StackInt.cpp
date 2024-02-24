//
// Created by İlayda Zehra Yılmaz on 14.05.2022.
//

#include "StackInt.h"
using namespace std;
#include <iostream>

// default constructor
StackInt ::StackInt () : topPtr(NULL){}

//copy constructor
StackInt ::StackInt (const StackInt & aStack ){
    if(aStack.topPtr == NULL){
        topPtr = NULL;
    }
    else{
        // copy first node
        topPtr = new StackNodeInt ;
        topPtr->item = aStack.topPtr->item;

        // copy rest of stack
        StackNodeInt  *newPtr = topPtr;
        for(StackNodeInt  *origPtr = aStack.topPtr->next; origPtr != NULL; origPtr = origPtr->next ){
            newPtr->next = new StackNodeInt ;
            newPtr = newPtr->next;
            newPtr->item = origPtr->item;
        }
        newPtr->next = NULL;
    }
}

// destructor
StackInt ::~StackInt () {

    // pop until stack is empty
    while(!isEmptyInt ())
        popInt ();
}

bool StackInt ::isEmptyInt () const{
    return topPtr == NULL;
}

bool StackInt ::pushInt (IntStackItemType newItem){

    //Create a new node
    StackNodeInt  *newPtr = new StackNodeInt ;

    //Set data portion of new node
    newPtr->item = newItem;

    //Insert the new node
    newPtr->next = topPtr;
    topPtr = newPtr;

    return true;
}

bool StackInt ::popInt (){

    if(isEmptyInt ()){
        return false;
    }

        // stack is not empty; delete top
    else{
        StackNodeInt  *temp = topPtr;
        topPtr = topPtr->next;

        // return deleted node to system safeguard
        temp->next = NULL;
        delete temp;
        return true;
    }
}

bool StackInt ::popInt (IntStackItemType& stackTop){
    if(isEmptyInt ()){
        return false;
    }

        // stack is not empty; retrieve and delete top
    else{
        stackTop = topPtr->item;
        StackNodeInt  *temp = topPtr;
        topPtr = topPtr->next;

        // return deleted node to system safeguard
        temp->next = NULL;
        delete temp;
        return true;
    }
}

bool StackInt ::getTopInt (IntStackItemType & stackTop) const {

    if (isEmptyInt ()) {
        return false;
    }
        // stack is not empty; retrieve top
    else {
        stackTop = topPtr->item;
        return true;
    }
}