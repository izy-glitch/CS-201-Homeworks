//
// Created by İlayda Zehra Yılmaz
// Student ID: 22001769
//


#include <string>
#include "Car.h"
using namespace std;

//Default constructor
Car::Car() {
    setPlateNo( 0 );
    setCarType( "+" );
    setCarPlace("");
}

//Overloaded constructor
Car::Car( int thePlateNo, string theCarType, string theCarPlace ) {
    setPlateNo( thePlateNo );
    setCarType( theCarType );
    setCarPlace( theCarPlace );
}

//Destructor
Car::~Car(){
    setPlateNo( 0 );
    setCarType( "+" );
    setCarPlace("");
}

//Set methods
void Car::setPlateNo( const int& thePlateNo ) {
    plateNo = thePlateNo;
}

void Car::setCarType( const string& theCarType ) {
    carType = theCarType;
}

void Car::setCarPlace(const string &theCarPlace) {
    carPlace = theCarPlace;
}

//Get methods
string Car::getCarType() {
    return carType;
}

int Car::getPlateNo() {
    return plateNo;
}

string Car::getCarPlace() {
    return carPlace;
}


