//
// Created by İlayda Zehra Yılmaz on 13.05.2022.
//

#include "Stack.h"
using namespace std;
#include <iostream>

// default constructor
Stack::Stack() : topPtr(NULL){}

//copy constructor
Stack::Stack(const Stack& aStack ){
    if(aStack.topPtr == NULL){
        topPtr = NULL;
    }
    else{
        // copy first node
        topPtr = new StackNode;
        topPtr->item = aStack.topPtr->item;

        // copy rest of stack
        StackNode *newPtr = topPtr;
        for(StackNode *origPtr = aStack.topPtr->next; origPtr != NULL; origPtr = origPtr->next ){
            newPtr->next = new StackNode;
            newPtr = newPtr->next;
            newPtr->item = origPtr->item;
        }
        newPtr->next = NULL;
    }
}

// destructor
Stack::~Stack() {

    // pop until stack is empty
    while(!isEmpty())
        pop();
}

bool Stack::isEmpty() const{
    return topPtr == NULL;
}

bool Stack::push(StackItemType newItem){

    //Create a new node
    StackNode *newPtr = new StackNode;

    //Set data portion of new node
    newPtr->item = newItem;

    //Insert the new node
    newPtr->next = topPtr;
    topPtr = newPtr;

    return true;
}

bool Stack::pop(){

    if(isEmpty()){
        return false;
    }

    // stack is not empty; delete top
    else{
        StackNode *temp = topPtr;
        topPtr = topPtr->next;

        // return deleted node to system safeguard
        temp->next = NULL;
        delete temp;
        return true;
    }
}

bool Stack::pop(StackItemType& stackTop){
    if(isEmpty()){
        return false;
    }

    // stack is not empty; retrieve and delete top
    else{
        stackTop = topPtr->item;
        StackNode *temp = topPtr;
        topPtr = topPtr->next;

        // return deleted node to system safeguard
        temp->next = NULL;
        delete temp;
        return true;
    }
}

bool Stack::getTop(StackItemType& stackTop) const{

    if(isEmpty()){
        return false;
    }
    // stack is not empty; retrieve top
    else{
        stackTop = topPtr->item;
        return true;
    }
}