//
// Created by İlayda Zehra Yılmaz on 13.05.2022.
//

#ifndef CS201_HW4_SPRING_SOLUTIONS_H
#define CS201_HW4_SPRING_SOLUTIONS_H

using namespace std;
#include <iostream>
#pragma once
#include "Stack.h"
#include "StackStr.h"
#include "StackInt.h"

class Solutions {
public:
private:
};

void fantabulous(string list, int length);
void subset(string intervals, int length);
string infix2prefix(string expression);
void evaluatePrefix(string expression);
bool isOperand( char character );
string infix2postfix(string expression);
int checkPrecedence( char character );
string reverseString(string expression);
double recursiveEvaluatePrefix(string expression);
string deleteFirstWithStack(string expression);
int* findSubset(int* arr, int index, int length );
int findMaximums(int* arr, int& firstMax, int& secondMax, int length);
#endif //CS201_HW4_SPRING_SOLUTIONS_H
