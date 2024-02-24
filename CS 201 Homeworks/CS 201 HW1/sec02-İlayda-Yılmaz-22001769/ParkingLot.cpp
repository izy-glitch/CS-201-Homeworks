//
// Created by İlayda Zehra Yılmaz
// Student ID: 22001769
//

#include <iostream>
#include <string>
#include "ParkingLot.h"
using namespace std;

//Default constructor
ParkingLot::ParkingLot() {
    //Set the default values

    setLotID(0);
    setLotRows( 0 );
    setLotColumns( 0);
    setLotSize(0, 0);
    parkingLot = NULL;

}

//Overloaded constructor
ParkingLot::ParkingLot(int theLotID, int theLotRows, int theLotColumns) {

    setLotID( theLotID );
    setLotRows( theLotRows );
    setLotColumns( theLotColumns );
    setLotSize( theLotRows, theLotColumns);

    //Create lot as a dynamic array
    parkingLot = new Car* [ lotRows ];

    for ( int i = 0; i < lotRows; i++){
        parkingLot[ i ] = new Car [ lotColumns ];
    }

}

//Copy constructor
ParkingLot::ParkingLot( const ParkingLot& pLot ) : lotSize( pLot.lotSize ){

    //Set lot variables
    setLotID(pLot.lotID);
    setLotColumns(pLot.lotColumns);
    setLotRows(pLot.lotRows);
    setLotSize(pLot.lotRows, pLot.lotColumns);

    //Create lot
    if( lotSize > 0 ){
        parkingLot = new Car* [ lotRows ];
        for( int i = 0; i < lotRows; i++ ){
            parkingLot[i] = new Car [ lotColumns ];
        }
    }
    else{
        parkingLot = NULL;
    }

}

//Assignment operator
ParkingLot& ParkingLot::operator=( const ParkingLot & rhs ) {

    if( &rhs != this ){ //to avoid self-assignment

        //If any of lot variables are different delete the lot and set it variables to rhs. Create the lot again.
        if ( lotSize != rhs.lotSize || lotRows != rhs.lotRows || lotColumns != rhs.lotColumns || lotID != rhs.lotID ){

            //Delete
            if ( lotSize > 0 ){
                if ( parkingLot ){
                    for ( int i = 0; i < lotRows; i++){
                        delete [] parkingLot[i];
                    }
                    delete [] parkingLot;
                }
            }

            //Create the new row which will be the copy of the rhs
            lotSize = rhs.lotSize;
            lotRows = rhs.lotRows;
            lotColumns = rhs.lotColumns;
            lotID = rhs.lotID;
            if ( lotSize > 0 ){

                parkingLot = new Car* [ lotRows ];
                for( int i = 0; i < lotRows; i++ ){
                    parkingLot[i] = new Car [ lotColumns ];
                }
            }
            else {
                parkingLot = NULL;
            }
        }

        //Set lot contents to rhs
        for( int i = 0; i < lotRows; i++ ){
            for( int j = 0; j < lotColumns; j++ ){
                parkingLot[i][j] = rhs.parkingLot[i][j];
            }
        }
    }

    return *this; // to allow cascading
}

//Destructor
ParkingLot::~ParkingLot() {

    //Destroy the lot and its variables
    if ( parkingLot ){
        for ( int i = 0; i < lotRows; i++){
            delete [] parkingLot[i];
        }
        delete [] parkingLot;

        setLotID(0);
        setLotRows( 0 );
        setLotColumns( 0);
        setLotSize(0, 0);

    }

}

//Set methods
void ParkingLot::setLotID(const int& theLotID) {
    lotID = theLotID;
}

void ParkingLot::setLotRows(const int& theLotRows) {
    lotRows = theLotRows;
}

void ParkingLot::setLotColumns(const int& theLotColumns) {
    lotColumns = theLotColumns;
}

void ParkingLot::setLotSize(const int& theLotRows, const int& theLotColumns) {
    lotSize = theLotRows * theLotColumns;
}

//Get methods
int ParkingLot::getLotID() {
    return lotID;
}

int ParkingLot::getLotRows() {
    return lotRows;
}

int ParkingLot::getLotColumns() {
    return lotColumns;
}

int ParkingLot::getLotSize() {
    return lotSize;
}

//Gets the empty slots in the parking lot
int ParkingLot::getEmptySlots() {

    int emptySlots = 0;

    //Counts empty slots
    for( int i = 0; i < lotRows; i++){
        for( int j = 0; j < lotColumns; j++){
            if( parkingLot[i][j].getCarType() == "+" ){
                emptySlots++;
            }
        }
    }

    return emptySlots;
}

//Gets the car type (to use in the parking system)
string ParkingLot::getCarTypeInParkingLot( int i, int j) {
    return parkingLot[i][j].getCarType();
}

//Gets the plateNo's of parked cars
void ParkingLot::getParkedCars() {

    int carNo = 0;

    //If there ara no cars in the lot, warning message, else print
    if( getEmptySlots() == getLotSize() ){
        cout<<"no cars yet ";
    }
    else{
        for( int i = 0; i < lotRows; i++){
            for( int j = 0; j < lotColumns; j++){
                if( parkingLot[i][j].getCarType() != "+" ){

                    //It will start putting comma after the first car in the array
                    if( carNo == 0 ){

                        //If it is a normal print
                        if( parkingLot[i][j].getCarType() == "a" ){
                            cout<< parkingLot[i][j].getPlateNo();
                            carNo++;
                        }
                        else if( parkingLot[i][j].getCarType() == "b" ){

                            //If it is b, check if it is the lowest row. If not print just once by printing the lower
                            // location of the b car
                            if( i != lotRows - 1 ){
                                if( parkingLot[i][j].getPlateNo() == parkingLot[ i + 1 ][j].getPlateNo() ){
                                    cout<< parkingLot[ i + 1 ][j].getPlateNo();
                                    carNo++;
                                }
                            }

                        }
                    }
                    else{
                        if( parkingLot[i][j].getCarType() == "a" ){

                            //If it is a normal print
                            cout<< ", " << parkingLot[i][j].getPlateNo();
                            carNo++;
                        }
                        else if( parkingLot[i][j].getCarType() == "b" ){

                            //If it is b, check if it is the lowest row. If not print just once by printing the lower
                            // location of the b car
                            if( i != lotRows - 1 ){
                                if( parkingLot[i][j].getPlateNo() == parkingLot[ i + 1 ][j].getPlateNo() ){
                                    cout<< ", " << parkingLot[ i + 1 ][j].getPlateNo();
                                    carNo++;
                                }
                            }

                        }
                    }
                }
            }
        }
    }
}

//Returns the number of times that plateNo is in the parking lot
int ParkingLot::checkPlateNoExists( int plateNumber ) {

    int thePlateNoExists = 0;
    for( int i = 0; i < lotRows; i++){
        for( int j = 0; j < lotColumns; j++){
            if( parkingLot[i][j].getPlateNo() == plateNumber ){
                thePlateNoExists++;
            }
        }
    }

    return thePlateNoExists;
}

//Gets the row number of the car with the plate number
int ParkingLot::getRowIndex( int plateNumber ) {

    int rowIndex = 0;
    for( int i = 0; i < lotRows; i++){
        for( int j = 0; j < lotColumns; j++){
            if( parkingLot[i][j].getPlateNo() == plateNumber ){
                rowIndex = i;
            }
        }
    }

    return rowIndex;
}

//Gets the column number of the car with the plate number
int ParkingLot::getColumnIndex( int plateNumber ) {

    int columnIndex = 0;
    for( int i = 0; i < lotRows; i++){
        for( int j = 0; j < lotColumns; j++){
            if( parkingLot[i][j].getPlateNo() == plateNumber ){
                columnIndex = j;
            }
        }
    }

    return columnIndex;
}

//Parks the car in ParkingLot in a special space
void ParkingLot::parkCarInParkingLot( int rowIndex, int columnIndex, string location, string carType, int plateNumber ){
    parkingLot[rowIndex][columnIndex] = Car( plateNumber, carType, location);
}

//Remove car in ParkingLot that is parked in a special space
void ParkingLot::removeCarInParkingLot( int rowIndex, int columnIndex ) {

    int plateNumber = parkingLot[ rowIndex ][ columnIndex ].getPlateNo();
    string carPlace = parkingLot[ rowIndex ][ columnIndex ].getCarPlace();

    if ( parkingLot[ rowIndex ][ columnIndex ].getCarType() == "a" ){

        //Remove car
        parkingLot[ rowIndex ][ columnIndex ] = Car( 0, "+", "");

        //Success message
        cout<< "Light-duty car with number plate "<< plateNumber << " car has been removed from slot "<< carPlace
            << ", lot " << lotID << endl;
    }
    else if ( parkingLot[rowIndex][columnIndex].getCarType() == "b" ){

        //Remove car
        parkingLot[ rowIndex ][ columnIndex ] = Car( 0, "+", "");
        parkingLot[ rowIndex - 1 ][ columnIndex ] = Car( 0, "+", "");

        //Success message
        cout<< "Heavy-duty car with number plate "<< plateNumber << " car has been removed from slot "<< carPlace
            << ", lot " << lotID << endl;
    }
}

//Gets the location of the car that is in the stated row and column
string ParkingLot::getCarPlaceInParkingLot(int rowIndex, int columnIndex) {
    return parkingLot[ rowIndex ][ columnIndex ].getCarPlace();
}

void ParkingLot::removeTheParkingLotInParkingLot() {

    //Destroy the lot and its variables
    if ( parkingLot ){
        for ( int i = 0; i < lotRows; i++){
            delete [] parkingLot[i];
        }
        delete [] parkingLot;

        setLotID(0);
        setLotRows( 0 );
        setLotColumns( 0);
        setLotSize(0, 0);

        parkingLot = NULL;
    }
}
int ParkingLot::getPlateNoInParkingLot(int rowIndex, int columnIndex) {
    return parkingLot[ rowIndex ][ columnIndex ].getPlateNo();
}