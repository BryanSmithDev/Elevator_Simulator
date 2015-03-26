/*
Name: Scott Arnette
Section: 2
Date: 4/5/13
Assignment 5: Elevator Simulation: All Elevators Class
*/
#include<iostream>
using namespace std;

class allFloorsElevator: public Elevator{
public:
//[Default contructor]
    allFloorsElevator(){};
   
//[Method to move elevator that will hit all floors]
    void move(){

        if(currentFloor->next == NULL && movingUp == true){
        currentFloor = currentFloor->back;
        movingUp = false;		
        }
        else if(currentFloor->back == NULL && movingUp == false){
        currentFloor = currentFloor->next;
        movingUp = true;
        }
        else if(movingUp){
        currentFloor = currentFloor->next;
        }
        else{
        currentFloor = currentFloor->back;
        }
		int n = currentFloor->info->getFloorNum();

    }
};
