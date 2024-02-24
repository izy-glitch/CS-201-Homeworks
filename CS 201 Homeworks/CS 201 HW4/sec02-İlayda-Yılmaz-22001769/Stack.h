//
// Created by İlayda Zehra Yılmaz on 13.05.2022.
//

#ifndef CS201_HW4_SPRING_STACK_H
#define CS201_HW4_SPRING_STACK_H
using namespace std;
#include <iostream>
typedef char StackItemType;


class Stack {
public:
    Stack();
    Stack(const Stack &aStack);
    ~Stack();
    bool isEmpty() const;
    bool push(StackItemType newItem);
    bool pop();
    bool pop(StackItemType& stackTop);
    bool getTop(StackItemType& stackTop)  const;
private:
    struct StackNode{
        StackItemType item;
        StackNode *next;
    };
    StackNode *topPtr;
};


#endif //CS201_HW4_SPRING_STACK_H
