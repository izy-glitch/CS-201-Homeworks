//
// Created by İlayda Zehra Yılmaz on 13.05.2022.
//

#include "Solutions.h"

using namespace std;
#include <iostream>
#include <sstream>

bool isOperand( char character ){
    int i = character - '0';
    if( i == 0 || i == 1 || i == 2 || i == 3 || i == 4 || i == 5 || i == 6 || i == 7 || i == 8 || i == 9 ){
        return true;
    }
    else{
        return false;
    }
}
string infix2postfix(string expression){
    Stack S;
    string postfix = "";
    char ch;
    StackItemType stackTop;
    for( int i = 0; i < expression.size(); i++ ){
        ch = expression[i];
       if(isOperand(ch) ){
            postfix += ch;
       }
       else if( expression[i] == '(' ){
           S.push(ch);
       }
       else if( expression[i] == ')'){
           S.getTop(stackTop);
           while( stackTop != '('){
               postfix += stackTop;
               S.pop();
               S.getTop(stackTop);
           }
           S.pop(); //remove '('
       }
       else{ //It is an operator
           S.getTop(stackTop);
           if(!isOperand(stackTop)){
               while( !S.isEmpty() && stackTop != '(' && checkPrecedence(ch) <= checkPrecedence(stackTop) ){
                   postfix += stackTop;
                   S.pop();
                   S.getTop(stackTop);
               }
               S.push(ch); //save new operator
           }
       }
    }

    S.getTop(stackTop);
    while(!S.isEmpty()){
        postfix += stackTop;
        S.pop();
        S.getTop(stackTop);
    }
    return postfix;
}

int checkPrecedence( char character ){
    if( character == '*' || character == '/'){
        return 2;
    }
    else if( character == '+' || character == '-'){
        return 1;
    }
}

string reverseString(string expression){
    Stack S;
    int ch;
    string reversedStr = "";
    StackItemType stackTop;
    for( int i = 0; i < expression.size(); i++ ){
        ch = expression[i];
        S.push(ch);
    }
    S.getTop(stackTop);
    while(!S.isEmpty()){
        reversedStr += stackTop;
        S.pop();
        S.getTop(stackTop);
    }

    for( int i = 0; i < reversedStr.size(); i++ ){
        if( reversedStr[i] == '('){
            reversedStr[i] = ')';
        }
        else if( reversedStr[i] == ')' ){
            reversedStr[i] = '(';
        }
    }

    return reversedStr;
}

string infix2prefix(string expression){
    string infix = reverseString( expression );
    string postfix = infix2postfix( infix );
    string prefix = reverseString( postfix );
    return prefix;
}

void evaluatePrefix(string expression){
    Stack S;

    cout<<"Result of "<<expression<< " is: ";
    for( int i = expression.size() - 1; i >= 0; i--){
        if(isOperand(expression[i])){
            S.push( expression[i] );
        }
        else{
            StackItemType operand1;
            StackItemType operand2;
            S.pop(operand1);
            S.pop(operand2);

            int op1 = operand1 - '0';
            int op2 = operand2 - '0';
            double result;
            StackItemType resCh;
            if( expression[i] == '+'){
                result = op1 + op2;
                resCh = result + '0';
                S.push(resCh);
            }
            else if( expression[i] == '-'){
                result = op1 - op2;
                resCh = result + '0';
                S.push(resCh);
            }
            else if( expression[i] == '/'){
                result = op1 / op2;
                resCh = result + '0';
                S.push(resCh);
            }
            else if( expression[i] == '*'){
                result = op1 * op2;
                resCh = result + '0';
                S.push(resCh);
            }
        }
    }
    StackItemType top;
    S.getTop(top);
    cout<< top<<endl;
}

double recursiveEvaluatePrefix(string expression){
    char ch = expression[0];
    expression = deleteFirstWithStack( expression );
    if(isOperand(ch)){
        return ch - '0';
    }
    else if( ch == '+' || ch == '-' || ch == '/' || ch == '*' ){ //if ch is an operator
        double operand1;
        double operand2;
        if( ch == '+' ){
            operand1 = recursiveEvaluatePrefix(expression);
            operand2 = recursiveEvaluatePrefix(expression);
            return (operand1 + operand2);
        }
        else if( ch == '-' ){
            operand1 = recursiveEvaluatePrefix(expression);
            operand2 = recursiveEvaluatePrefix(expression);
            return (operand1 - operand2);
        }
        else if( ch == '/' ){
            operand1 = recursiveEvaluatePrefix(expression);
            operand2 = recursiveEvaluatePrefix(expression);
            return (operand1 / operand2);
        }
        else if( ch == '*' ){
            operand1 = recursiveEvaluatePrefix(expression);
            operand2 = recursiveEvaluatePrefix(expression);
            return (operand1 * operand2);
        }
    }
    return -1;
}

string deleteFirstWithStack(string expression){
    char ch;
    Stack S;
    string deletedStr = "";
    StackItemType stackTop;

    for( int i = expression.size() - 1; i >= 0; i-- ){
        ch = expression[i];
        S.push(ch);
    }
    S.pop(); // delete first
    while(!S.isEmpty()){
        S.getTop(stackTop);
        deletedStr += stackTop;
        S.pop();
    }

    return deletedStr;
}

void subset(string intervals, int length){
    StackStr firstStack;
    StackStr lastStack;
    int firstLength = length;
    int lastLength = 0;

    string curNum = "";
    intervals = intervals + ',';

    for( int i = 0; i < intervals.size(); i++ ){
        char ch = intervals[i];
        if(isOperand(ch) ){
            curNum += ch;
        }
        else if( intervals[i] == ',' ){
            firstStack.pushStr(curNum);
            curNum = "";
        }
    }
    while( firstLength >= 4 ){
        string subInterval[4];
        for( int i = 0; i < 4; i++ ){
            StrStackItemType num;
            firstStack.popStr(num);
            subInterval[i] = num;
        }
        stringstream ss(subInterval[2]);
        int leftInterNum = 0;
        ss>>leftInterNum;
        stringstream ss1(subInterval[1]);
        int rightInterNum = 0;
        ss1>>rightInterNum;

        if( length == firstLength ){
            if( leftInterNum >= rightInterNum ){

                firstStack.pushStr(subInterval[3]);

                lastStack.pushStr(subInterval[0]);
                lastStack.pushStr(subInterval[3]);
                firstLength -= 3;
                lastLength += 2;
            }
            else{
                firstStack.pushStr(subInterval[3]);
                firstStack.pushStr(subInterval[2]);
                firstStack.pushStr(subInterval[1]);

                firstLength -= 1;

                lastStack.pushStr(subInterval[0]);
                lastStack.pushStr(subInterval[1]);
                lastStack.pushStr(subInterval[2]);
                lastStack.pushStr(subInterval[3]);
                lastLength +=4;
            }
        }else{
            if( leftInterNum >= rightInterNum ){

                firstStack.pushStr(subInterval[3]);

                lastStack.pushStr(subInterval[3]);
                firstLength -= 3;
                lastLength += 1;
            }
            else{
                firstStack.pushStr(subInterval[3]);
                firstStack.pushStr(subInterval[2]);
                firstStack.pushStr(subInterval[1]);

                firstLength -= 1;

                lastStack.pushStr(subInterval[1]);
                lastStack.pushStr(subInterval[2]);
                lastStack.pushStr(subInterval[3]);
                lastLength +=3;
            }
        }
    }

    StrStackItemType stackTop;
    string lastInter[lastLength];
    int c;
    while(!lastStack.isEmptyStr()){
        c = 0;
        lastStack.popStr(stackTop);
        lastInter[c] = stackTop;
        c++;
    }

    cout<<"Joined subset: ";

    int lastSize = c + 1;
    cout<<"("<< lastInter[0]<< ":" << lastInter[ 1 ]<< ")";
    for( int i = 2; i < lastSize; i+=2 ){
        cout<<", ("<< lastInter[i]<< ":" << lastInter[ i + 1 ]<< ")";
    }
    cout<<endl;
}

void fantabulous(string list, int length){
    StackStr listStack;

    string curNum = "";
    list = list + ',';

    for( int i = 0; i < list.size(); i++ ){
        char ch = list[i];
        if(isOperand(ch) ){
            curNum += ch;
        }
        else if( list[i] == ',' ){
            listStack.pushStr(curNum);
            curNum = "";
        }
    }
    /*
    int listArr[50];
    for( int i = length - 1; i >= 0 ; i++ ){
        StrStackItemType stackTop;
        listStack.popStr( stackTop );
        stringstream ss3(stackTop);
        int num = 0;
        ss3>>num;
        listArr[i] = num;
    }
    */

    int fantabulousSubsets = 0;
    /*
    for( int i = 2; i < length; i++ ){
        for( int j = 0; j < length - (i - 1); j++ ){
            int* subset = new int[i];
            subset = findSubset( listArr, j, i );

            int firstMax = 0;
            int secondMax = 0;

            findMaximums( subset, firstMax, secondMax, i);

            StackInt numStack;
            for( int k = 0; k < i; k++){
                numStack.pushInt(subset[k]);
            }


            IntStackItemType intTop;
            while( intTop != firstMax){ //?
                numStack.popInt(intTop);
            }

            while( intTop != secondMax){ //?
                numStack.popInt(intTop);
            }

            if( !numStack.isEmptyInt() ){
                fantabulousSubsets++;
            }

            delete[] subset;
        }
    }
     */
    cout<< "The number of Fantabulous subsequences: "<< fantabulousSubsets<<endl;

}

int findMaximums(int* arr, int& firstMax, int& secondMax, int length){
    int i;
    firstMax = arr[0];
    for (i = 1; i < length; i++)
        if (arr[i] > firstMax){
            firstMax = arr[i];
        }
    secondMax = 0;
}