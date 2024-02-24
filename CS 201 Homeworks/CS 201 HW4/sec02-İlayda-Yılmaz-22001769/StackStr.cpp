//
// Created by İlayda Zehra Yılmaz on 14.05.2022.
//

#include "StackStr.h"

using namespace std;
#include <iostream>

// default constructor
StackStr::StackStr() : topPtr(NULL){}

//copy constructor
StackStr::StackStr(const StackStr& aStack ){
    if(aStack.topPtr == NULL){
        topPtr = NULL;
    }
    else{
        // copy first node
        topPtr = new StrStackNode;
        topPtr->item = aStack.topPtr->item;

        // copy rest of stack
        StrStackNode *newPtr = topPtr;
        for( StrStackNode *origPtr = aStack.topPtr->next; origPtr != NULL; origPtr = origPtr->next ){
            newPtr->next = new StrStackNode;
            newPtr = newPtr->next;
            newPtr->item = origPtr->item;
        }
        newPtr->next = NULL;
    }
}

// destructor
StackStr::~StackStr() {

    // pop until stack is empty
    while(!isEmptyStr())
        popStr();
}

bool StackStr::isEmptyStr() const{
    return topPtr == NULL;
}

bool StackStr::pushStr(StrStackItemType newItem){

    //Create a new node
    StrStackNode *newPtr = new StrStackNode;

    //Set data portion of new node
    newPtr->item = newItem;

    //Insert the new node
    newPtr->next = topPtr;
    topPtr = newPtr;

    return true;
}

bool StackStr::popStr(){

    if(isEmptyStr()){
        return false;
    }

        // stack is not empty; delete top
    else{
        StrStackNode *temp = topPtr;
        topPtr = topPtr->next;

        // return deleted node to system safeguard
        temp->next = NULL;
        delete temp;
        return true;
    }
}

bool StackStr::popStr(StrStackItemType& stackTop){
    if(isEmptyStr()){
        return false;
    }

        // stack is not empty; retrieve and delete top
    else{
        stackTop = topPtr->item;
        StrStackNode *temp = topPtr;
        topPtr = topPtr->next;

        // return deleted node to system safeguard
        temp->next = NULL;
        delete temp;
        return true;
    }
}

bool StackStr::getTopStr(StrStackItemType& stackTop) const{

    if(isEmptyStr()){
        return false;
    }
        // stack is not empty; retrieve top
    else{
        stackTop = topPtr->item;
        return true;
    }
}