//
// Created by İlayda Zehra Yılmaz
// Student ID: 22001769
//

#ifndef PARKINGLOT_CPP_PARKINGSYSTEM_H
#define PARKINGLOT_CPP_PARKINGSYSTEM_H

#include <iostream>
#include <string>
#include "Car.h"
#include "ParkingLot.h"
using namespace std;

class ParkingSystem {
public:
    ParkingSystem();
    ~ParkingSystem();

    void createLot( int id, int rows, int columns );
    void removeLot( int id );
    void listLots();
    void lotContents( int id );
    void parkCar(int lotId, string location, string carType, int plateNumber);
    void findCar( int plateNumber );
    void removeCar( int plateNumber );

private:
    ParkingLot* parkingSystem;
    int parkSysSize;
};


#endif //PARKINGLOT_CPP_PARKINGSYSTEM_H
