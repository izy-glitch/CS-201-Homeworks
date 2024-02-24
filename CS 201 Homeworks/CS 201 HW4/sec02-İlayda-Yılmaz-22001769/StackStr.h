//
// Created by İlayda Zehra Yılmaz on 14.05.2022.
//

#ifndef CS201_HW4_SPRING_STACKSTR_H
#define CS201_HW4_SPRING_STACKSTR_H
using namespace std;
#include <iostream>
typedef string StrStackItemType;

using namespace std;
#include <iostream>

class StackStr {
public:
    StackStr();
    StackStr(const StackStr &aStack);
    ~StackStr();
    bool isEmptyStr() const;
    bool pushStr(StrStackItemType newItem);
    bool popStr();
    bool popStr(StrStackItemType& stackTop);
    bool getTopStr(StrStackItemType& stackTop)  const;
private:
    struct StrStackNode{
        StrStackItemType item;
        StrStackNode *next;
    };
    StrStackNode *topPtr;
};


#endif //CS201_HW4_SPRING_STACKSTR_H
