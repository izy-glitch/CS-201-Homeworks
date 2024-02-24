//
// Created by İlayda Zehra Yılmaz
// Student ID: 22001769
//

#include "ParkingSystem.h"
#include <iostream>
#include <string>
#include "ParkingLot.h"
using namespace std;

ParkingSystem::ParkingSystem() {
    parkSysSize = 0;
    parkingSystem = NULL;
}

ParkingSystem::~ParkingSystem() {
    delete[] parkingSystem;
    parkSysSize = 0;
}

void ParkingSystem::createLot( int id, int rows, int columns ) {

    //Check id exists
    int idExists = 0;

    for( int i = 0; i < parkSysSize; i++ ){
        if( parkingSystem[i].getLotID() == id ){
            idExists++;
        }
    }

    //If id doesn't exist and rows <= 12 and columns <= 12, add lot
    if( idExists == 0 ){
        if( rows <= 12 && columns <= 12 ){

            //If conditions satisfied add Lot
            ParkingLot pL( id, rows, columns);

            //If this is the first lot for the system, create system and add lot
            if( parkSysSize == 0 ){
                parkingSystem = new ParkingLot[ 1 ];
                parkingSystem[ 0 ] = pL;
                parkSysSize++;
            }
            else{
                //If not, expand the system and add the lot
                ParkingLot* temp = new ParkingLot[ parkSysSize + 1 ];
                for( int i = 0; i < parkSysSize; i++){
                    temp[i] = parkingSystem[i];
                }
                delete[] parkingSystem;
                parkingSystem = NULL;
                parkingSystem = temp;
                parkingSystem[parkSysSize] = pL;
                parkSysSize++;
            }

            //Success message
            cout<<"Parking lot with ID "<< id <<" and dimensions ("<< rows << "," << columns
                << ") has been added to the system"<<endl;
        }
        else{
            //Warning message
            cout<<"Cannot create the parking lot "<< id <<", dimensions exceed acceptable bounds"<<endl;
        }
    }
    else{
        //Warning message
        cout<<"Cannot create the parking lot "<< id <<", a lot with this ID already exists"<<endl;
    }

}

void ParkingSystem::removeLot( int id ) {

    //Checks if id exists and takes the index of the lot in the system
    int idExists = 0;
    int index = 0;
    for( int i = 0; i < parkSysSize; i++ ){
        if( parkingSystem[i].getLotID() == id ){
            idExists++;
            index = i;
        }
    }

    //If id exists remove lot
    if ( idExists != 0 ) {

        //First remove all the cars
        for (int i = 0; i < parkingSystem[index].getLotRows(); i++) {

            for (int j = 0; j < parkingSystem[index].getLotColumns(); j++) {

                if( parkingSystem[index].getCarTypeInParkingLot( i, j ) == "a" ){
                    //Remove car
                    parkingSystem[index].removeCarInParkingLot( i, j );

                } else if( parkingSystem[index].getCarTypeInParkingLot( i, j ) == "b" ){

                    if( i != parkingSystem[index].getLotRows() - 1 ){

                        if( parkingSystem[index].getPlateNoInParkingLot( i, j )
                            == parkingSystem[index].getPlateNoInParkingLot( i + 1 , j ) ){

                            //Remove car
                            parkingSystem[index].removeCarInParkingLot( i + 1 , j );
                        }
                    }
                }
            }
        }

        //Then remove the Parking Lot
        parkingSystem[index].removeTheParkingLotInParkingLot();

        parkSysSize--;

        ParkingLot* temp = new ParkingLot[ parkSysSize ];
        for( int i = 0; i < parkSysSize; i++){
            if( i < index ){
                temp[i] = parkingSystem[i];
            }
            else{
                temp[i] = parkingSystem[ i + 1 ];
            }
        }
        delete[] parkingSystem;
        parkingSystem = NULL;
        parkingSystem = temp;

        //Success message
        cout << "Lot " << id << " has been successfully removed from the system" << endl;
    }
    else{
        //Warning message
        cout<<"Lot " << id << " is not in the system"<<endl;

    }
}

void ParkingSystem::listLots() {

    //If there are no lots in the system, print warning message else list them
    if ( parkingSystem == NULL ){
        cout<<"No lots to list"<<endl;
    }
    else{
        cout<<"List of lots: "<<endl;
        for ( int i = 0; i < parkSysSize; i++){
            cout<< "ID: " << parkingSystem[i].getLotID() << ", Dim: (" << parkingSystem[i].getLotRows() << ","
                << parkingSystem[i].getLotColumns() << "), number of empty parking spaces: "
                << parkingSystem[i].getEmptySlots()<<endl;
        }
    }

}

void ParkingSystem::lotContents( int id ) {

    //Letter array to use while printing the rows
    string letterArr[] = {" ", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L"};

    //Checks if id exists and takes the index of the lot in the system
    int idExists = 0;
    int index = 0;
    for( int i = 0; i < parkSysSize; i++ ){
        if( parkingSystem[i].getLotID() == id ){
            idExists++;
            index = i;
        }
    }

    //If id exists print the lot
    if ( idExists != 0 ){

        //Print lot information
        cout<< "ID: " << parkingSystem[index].getLotID() << ", (" << parkingSystem[index].getLotRows() << ","
            << parkingSystem[index].getLotColumns() << "), empty slots: "
            << parkingSystem[index].getEmptySlots()<< ", parked cars: ";

        parkingSystem[index].getParkedCars();
        cout<<endl;
        cout<<endl;

        //Print lot with columns and rows
        for ( int i = 0; i < parkingSystem[index].getLotRows() + 1 ; i++){

            cout<< letterArr[i] << " ";
            if ( i == 0 ){
                for ( int j = 0; j < parkingSystem[index].getLotColumns(); j++){
                    cout<< " " << j + 1 << " ";
                }
            }
            else{
                for ( int j = 0; j < parkingSystem[index].getLotColumns(); j++){

                    if( j > 9 ){ //to align th columns with the numbers
                        cout<< "  " << parkingSystem[index].getCarTypeInParkingLot( i - 1, j ) << " ";
                    }
                    else{
                        cout<< " " << parkingSystem[index].getCarTypeInParkingLot( i - 1, j ) << " ";
                    }
                }
            }
            cout<<endl;
        }
    }
    else{
        //Warning message
        cout<<"Lot " << id << " does not exist in the system"<<endl;
    }
}

void ParkingSystem::parkCar(int lotId, string location, string carType, int plateNumber) {

    //Get lot index in the Parking System and check if lotId exists
    int idExists = 0;
    int index = 0;

    for( int i = 0; i < parkSysSize; i++ ){
        if( parkingSystem[i].getLotID() == lotId ){
            idExists++;
            index = i;
        }
    }

    //Get the row index
    char rowLetter = location[0];
    int rowIndex = 0;

    if ( rowLetter == 'A' ){
        rowIndex = 0;
    }
    else if ( rowLetter == 'B'){
        rowIndex = 1;
    }
    else if ( rowLetter == 'C' ){
        rowIndex = 2;
    }
    else if ( rowLetter == 'D'){
        rowIndex = 3;
    }
    else if ( rowLetter == 'E' ){
        rowIndex = 4;
    }
    else if ( rowLetter == 'F'){
        rowIndex = 5;
    }
    else if ( rowLetter == 'G' ){
        rowIndex = 6;
    }
    else if ( rowLetter == 'H'){
        rowIndex = 7;
    }
    else if ( rowLetter == 'I' ){
        rowIndex = 8;
    }
    else if( rowLetter == 'J' ){
        rowIndex = 9;
    }
    else if( rowLetter == 'K' ){
        rowIndex = 10;
    }
    else if( rowLetter == 'L' ){
        rowIndex = 11;
    }
    else{
        rowIndex = -1;
    }

    //Get the column Index
    char columnNo = location[1];
    int columnIndex = (columnNo - 48) - 1;

    //Check plateNo
    int plateNoExists = 0;
    for( int i = 0; i < parkSysSize; i++ ){
        plateNoExists = plateNoExists + parkingSystem[i].checkPlateNoExists( plateNumber );
    }

    //If id exist continue
    if( idExists != 0 ){

        //If plateNo is unique continue
        if( plateNoExists == 0 ){

            if( carType == "a" ){
                //If the space is empty park the car
                if( parkingSystem[index].getCarTypeInParkingLot( rowIndex, columnIndex ) == "+" ){

                    //Parking
                    parkingSystem[index].parkCarInParkingLot( rowIndex, columnIndex, location,
                                                              carType, plateNumber);
                    //Success message
                    cout<< "Light-duty car with number plate "<< plateNumber <<" has been parked at location "
                        << location <<", lot "<< lotId <<endl;
                }
                else{
                    //Warning message
                    cout<<"Cannot park light-duty car with number plate " << plateNumber << " at location "
                        << location << ", already occupied" << endl;
                }
            }
            else if ( carType == "b" ){

                //If it is not the first column continue parking (because space won't be enough for a b type car)
                if( rowIndex != 0
                    && parkingSystem[index].getCarTypeInParkingLot( rowIndex - 1, columnIndex ) == "+" ){

                    //If that parking space and the space above it is not occupied park the car
                    if( parkingSystem[index].getCarTypeInParkingLot( rowIndex, columnIndex ) == "+" ){

                        //Parking
                        parkingSystem[index].parkCarInParkingLot( rowIndex, columnIndex, location,
                                                                  carType, plateNumber);

                        parkingSystem[index].parkCarInParkingLot( rowIndex - 1 , columnIndex, location,
                                                                  carType, plateNumber);

                        //Success message
                        cout<< "Heavy-duty car with number plate "<< plateNumber <<" has been parked at location "
                            << location <<", lot "<< lotId << endl;

                    }
                    else{
                        //Warning message
                        cout<<"Cannot park heavy-duty car with number plate " << plateNumber << " at location "
                            << location << ", already occupied" << endl;
                    }
                }
                else{
                    //Warning message
                    cout<<"Cannot park heavy-duty car with number plate " << plateNumber << " at location "
                        << location << ", not enough space" << endl;
                }
            }
        }
        else{
            //Warning message
            cout<<"Cannot park the car, car with plate number " << plateNumber <<" already exists in the system"<<endl;
        }
    }
    else{
        //Warning message
        cout<<"Lot " << lotId << " is not in the system"<<endl;
    }
}

void ParkingSystem::findCar( int plateNumber ) {

    int rowIndex = 0;
    int columnIndex = 0;

    //Check plateNo and get the index
    int plateNoExists = 0;
    int index = -1;

    for( int i = 0; i < parkSysSize; i++ ){
        plateNoExists = parkingSystem[i].checkPlateNoExists( plateNumber );
        if( plateNoExists != 0 ){
            index = i;
        }
    }

    if( index != -1 ){
        rowIndex = parkingSystem[ index ].getRowIndex( plateNumber );
        columnIndex =  parkingSystem[ index ].getColumnIndex( plateNumber );
        if( parkingSystem[index].getCarTypeInParkingLot( rowIndex, columnIndex ) == "a" ){

            //Message
            cout<<"Light-duty car with number plate "<< plateNumber << " is at the location "
                << parkingSystem[index].getCarPlaceInParkingLot( rowIndex, columnIndex ) << ", lot "
                << parkingSystem[ index ].getLotID() <<endl;
        }
        else if ( parkingSystem[index].getCarTypeInParkingLot(rowIndex, columnIndex) == "b" ){

            //Message
            cout<<"Heavy-duty car with number plate "<< plateNumber << " is at the location "
                << parkingSystem[index].getCarPlaceInParkingLot( rowIndex, columnIndex ) << ", lot "
                << parkingSystem[ index ].getLotID() <<endl;
        }

    }
    else{
        //Warning message
        cout<< "The car with number plate "<< plateNumber << " is not in the system"<<endl;
    }
}

void ParkingSystem::removeCar( int plateNumber ) {
    int rowIndex = 0;
    int columnIndex = 0;

    //Check plateNo and get the index
    int plateNoExists = 0;
    int index = -1;

    for( int i = 0; i < parkSysSize; i++ ){
        plateNoExists = parkingSystem[i].checkPlateNoExists( plateNumber );
        if( plateNoExists != 0 ){
            index = i;
        }
    }

    if( index != -1 ){
        rowIndex = parkingSystem[ index ].getRowIndex( plateNumber );
        columnIndex =  parkingSystem[ index ].getColumnIndex( plateNumber );

        //Remove car
        parkingSystem[ index ].removeCarInParkingLot( rowIndex, columnIndex );
    }
    else{
        //Warning message
        cout<< "The car with number plate "<< plateNumber << " is not in the system"<<endl;
    }

}
