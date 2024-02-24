//
// Created by İlayda Zehra Yılmaz on 14.05.2022.
//

#ifndef CS201_HW4_SPRING_STACKINT_H
#define CS201_HW4_SPRING_STACKINT_H

using namespace std;
#include <iostream>
typedef int IntStackItemType;


class StackInt {
public:
    StackInt();
    StackInt(const StackInt &aStack);
    ~StackInt();
    bool isEmptyInt() const;
    bool pushInt(IntStackItemType newItem);
    bool popInt();
    bool popInt(IntStackItemType& stackTop);
    bool getTopInt(IntStackItemType& stackTop)  const;
private:
    struct StackNodeInt{
        IntStackItemType item;
        StackNodeInt *next;
    };
    StackNodeInt *topPtr;
};




#endif //CS201_HW4_SPRING_STACKINT_H
