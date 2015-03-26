/*
Name: Scott Arnette
Section: 2
Date: 4/5/13
Assignment 5: Elevator Simulation: Even Only Elevator Movement
*/
#include<iostream>
using namespace std;

class evenFloorsElevator: public Elevator{
public:
   
	//[Default constructor]
    evenFloorsElevator(){};
   
	//[Method to move elevator for only even floors]
    void move(){
        if((currentFloor->next == NULL||currentFloor->next->next == NULL) && movingUp == true){
        currentFloor = currentFloor->back->back;
        movingUp = false;
        }
        else if((currentFloor->back == NULL||currentFloor->back->back == NULL) && movingUp == false){
        currentFloor = currentFloor->next->next;
        movingUp = true;
        }
        else if(movingUp){
        currentFloor = currentFloor->next->next;
        }
        else{
        currentFloor = currentFloor->back->back;
        }
    }
};