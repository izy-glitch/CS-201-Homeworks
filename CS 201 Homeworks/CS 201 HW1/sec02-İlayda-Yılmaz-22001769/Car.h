//
// Created by İlayda Zehra Yılmaz
// Student ID: 22001769
//

#ifndef CS_201_SPRING_HW1_PARKINGSYSTEM_CAR_H
#define CS_201_SPRING_HW1_PARKINGSYSTEM_CAR_H

#include <iostream>
#include <string>

using namespace std;

class Car {
public:
    Car();
    Car( int thePlateNo, string theCarType, string theCarPlace );
    ~Car();
    string getCarType();
    int getPlateNo();
    string getCarPlace();

private:
    int plateNo;
    string carType;
    string carPlace;
    void setCarType( const string& theCarType );
    void setPlateNo( const int& thePlateNo );
    void setCarPlace( const string& theCarPlace);
};


#endif //CS_201_SPRING_HW1_PARKINGSYSTEM_CAR_H
