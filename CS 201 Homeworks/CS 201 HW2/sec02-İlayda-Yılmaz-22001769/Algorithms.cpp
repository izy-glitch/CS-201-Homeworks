//
// Created by İlayda Zehra Yılmaz on 2.04.2022.
//
#include <iostream>
#include "Algorithms.h"
#include <cmath>
using namespace std;

long long Algorithms::naiveAlgorithm( long long a,  long long n,  long long p) {

    long long result = 0;
    long long aValue = a;
    result = ( a % p );

    //if n = 0 mod will be 1 always
    if( n == 0 ){
        return 1;
    }
    for( long long i = 1; i <= n; i++ ){
        result = a % p;
        a *= aValue;
    }

    return result;
}

long long Algorithms::naiveAlgorithmWithShortcut( long long a,  long long n,  long long p) {
    long long result = 0; //if n = 0 mod will be 1 always
    long long aValue = a;
    long long index = n; //if it can't find the index it should go to the end

    //if n = 0 mod will be 1 always
    if( n == 0 ){
        return 1;
    }

    for( long long i = 1; i <= n; i++ ){
        if( (a % p) == 1 ) {
            index = i;
        }
        a *= aValue;
    }

    a = aValue;

    for( long long i = 1; i <= index; i++ ){
        result = a % p;
        a *= aValue;
    }
    long long exp = 0;
    exp = n % index; //when this is 0, because the result should be 1 and it is so it won't enter the loop but
    // result is set to 1, so we don't have to set it again
    a = aValue;

    for( long long i = 1; i <= exp; i++ ){
        result = a % p;
        a *= aValue;
    }

    return result;
}

long long Algorithms::recursiveModAlgorithm( long long a, long long n, long long p ) {

    if( n == 1 ){
        return a % p;
    }
    else{
        long long int tempMod;

        if ( (n % 2) == 0){
            tempMod = recursiveModAlgorithm( a, n/2, p );
            return ( tempMod * tempMod ) % p;
        }
        else{
            tempMod = recursiveModAlgorithm( a, (n - 1)/2, p );
            return ( a * tempMod * tempMod ) % p;
        }

    }
}

int main(){

    double duration;
    clock_t startTime = clock();
    Algorithms A;

    long long int a = 3;
    long long int n = 10* pow(10, 9);
    long long int p = 10007;

    cout<< "Result of Algorithm 1 is " << A.naiveAlgorithm( a, n, p )<<endl;


    cout<< "Result of Algorithm 2 is " <<A.naiveAlgorithmWithShortcut( a, n, p )<<endl;

    int recRes = 0 ;
    for ( int i = 0; i < 200000000; i++){
        recRes = A.recursiveModAlgorithm( a, n, p );
    }
    cout<< "Result of Algorithm 3 is " << recRes <<endl;

    duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
    cout << "Execution took " << duration << " milliseconds." << endl;
}