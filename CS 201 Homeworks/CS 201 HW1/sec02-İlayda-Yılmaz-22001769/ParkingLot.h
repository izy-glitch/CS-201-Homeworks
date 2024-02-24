//
// Created by İlayda Zehra Yılmaz
// Student ID: 22001769
//

#ifndef CAR_H_PARKINGLOT_H
#define CAR_H_PARKINGLOT_H

#include <iostream>
#include <string>
#include "Car.h"
using namespace std;

class ParkingLot {
public:

    ParkingLot();
    ParkingLot( int theLotID, int theLotRows, int theLotColumns );
    ParkingLot( const ParkingLot& );
    ParkingLot& operator=( const ParkingLot& );
    ~ParkingLot();
    int getLotID();
    int getLotRows();
    int getLotColumns();
    int getLotSize();
    int getEmptySlots();
    void getParkedCars();
    int checkPlateNoExists( int plateNumber );
    void parkCarInParkingLot( int rowIndex, int columnIndex, string location, string carType, int plateNumber);
    int getRowIndex( int plateNumber );
    int getColumnIndex( int plateNumber );
    void removeCarInParkingLot( int rowIndex, int columnIndex );
    void removeTheParkingLotInParkingLot();
    string getCarPlaceInParkingLot( int rowIndex, int columnIndex );
    int getPlateNoInParkingLot( int rowIndex, int columnIndex );
    string getCarTypeInParkingLot( int i, int j);


private:
    int lotID;
    int lotRows;
    int lotColumns;
    int lotSize;
    Car** parkingLot;
    void setLotID( const int& theLotID );
    void setLotRows( const int& theLotRows );
    void setLotColumns( const int& theLotColumns );
    void setLotSize( const int& theLotRows, const int& theLotColumns );

};


#endif //CAR_H_PARKINGLOT_H
