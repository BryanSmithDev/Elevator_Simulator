/*################################################
 Name: Bryan Smith
 Course: CSC 2180-02 Data Structures
 Date: 4/3/13
 Assignment: Programming Assignment #5
 Description: SimBuilding contains linkedLists 
			  of Floors and Elevators, and manages
			  the number of simulation steps
###############################################*/

#include <iostream>
#include <ctime>
#include <cstdlib>
#include "unorderedLinkedList.h"
#include "floor.h"
#include "elevator.h"
#include "allElevators.h"
#include "evenElevators.h"
#include "oddElevators.h"


using namespace std;


class SimBuilding {

private:
	unorderedLinkedList<Floor<int>*> floors;		//Linked List of Floor Elements
	linkedListIterator<Floor<int>*> FloorIter;		//Linked List Iterator to traverse the floors list
	
	unorderedLinkedList<Elevator*> elevators;		//Linked List of Elevator Elements
	linkedListIterator<Elevator*> ElevIter;		//Linked List Iterator to traverse the elevator list
	
	int currentStep;							//The current simulation step
	double avgWaitTime;							//The average wait time of people waiting on elevators
	double totalWaitTime;						//The total time people wait on elevators
	int numberOfIterations;						//The length of time to run the simulation (30min = 60iter)
	int numberOfFloors;							//The number of floors the building has
	int numberOfElevators;						//The number of elevators the building has
	int elevatorConfig;							//The configuration number that determines elevator setip

public:
	//================
	// Constructor
	//================
	SimBuilding(int elevConfig, int numberOfFloors=33, int numberOfElev=5,int time=60){
		//Initialize variables
		elevatorConfig=elevConfig;
		numberOfIterations=time;
		this->numberOfFloors = numberOfFloors;
		numberOfElevators = numberOfElev;
		avgWaitTime=0.0;
		totalWaitTime=0;
		currentStep=0;

		loadFloors();
		loadElevators();
		
	}

	//========================================
	//Simulates one time interation per call.
	//========================================
	int step() {

		//For all floors
		for(int x=0;x<=numberOfFloors-1;x++){
				
			//A random number of people 0-3 added to it's queue
			(**FloorIter).arriveAt();

			//Each persons wait time is updated
			(**FloorIter).queueWaitIncrement();

			//Increment the Floor iterator
			++FloorIter;
		}
		FloorIter = floors.begin();//Reset the floors iterator to the beginning

		//For all elevators
		for(int e=0;e<=numberOfElevators-1;e++){

			//Move the elevator
			(**ElevIter).move();

			//Unload random about of people 0-3
			(**ElevIter).unloadPeople();

			//Take in all people from current floor that can be held
			(**ElevIter).loadPeople();

			//Increment the Elevator Iterator
			++ElevIter;
		}
		ElevIter = elevators.begin();//Reset the elevators iterator to the beginning

		return currentStep;
	}


	//==================================================
	//Runs the simulation for the number of iterations.
	//==================================================
	double run() {
		srand(time(0));						//Setup random, seeding with current system millisecs
		FloorIter = floors.begin();			//Reset the floors iterator to the beginning
		ElevIter = elevators.begin();		//Reset the elevators iterator to the beginning

		//For the number of simulation steps
		for(int i=0;i<=numberOfIterations-1;i++){
			step();									//Step through the simulation
			currentStep++;							//Increment the step count
		}

		//Iterate thorugh all floors, totaling the wait time
		FloorIter = floors.begin();			
		for(int f=0;f<=numberOfFloors-1;f++){
			totalWaitTime+=(**FloorIter).boardAverage();
			++FloorIter;
		}

		avgWaitTime=totalWaitTime/numberOfFloors; //Calculate the total wait time

		return avgWaitTime;
	}

	//=======================================================
	//Populate floors linked list with the number of floors
	//======================================================
	void loadFloors(){
		floors.initializeList();					//Clear list and set first and last to NULL
		for (int i=1;i<=numberOfFloors;i++){		//For number of floors
				Floor<int>* temp = new Floor<int>;	//Create new floor objects
				temp->initializeQueue();
				temp->setFloorNum(i);
				floors.insertLast(temp);			//And insert them into the floors list
		}
		FloorIter = floors.begin();					//Reset the floors iterator to the beginning
	}


	//===========================================================
	//Populate elevators linked list with the number of elevators
	//===========================================================
	void loadElevators(){
		elevators.initializeList();					//Clear list and set first and last to NULL

		//For the number of elevators
		for (int i=1;i<=numberOfElevators;i++){
			//Create the elevator objects based on the specified configuration number
			switch(elevatorConfig){
				case 0: {//AAAAA
						allFloorsElevator* temp = new allFloorsElevator;
						temp->setElevatorNumber(i);
						temp->setCurrentFloor(FloorIter.getCurrentNode());
						elevators.insertFirst(temp);
					break;
						}
				case 1: //AOAOA
						if (i%2==1) {
							allFloorsElevator* temp1 = new allFloorsElevator;
							temp1->setCurrentFloor(FloorIter.getCurrentNode());
							temp1->setElevatorNumber(i);
							elevators.insertFirst(temp1);
						} else {
							oddFloorsElevator* temp1 = new oddFloorsElevator;
							temp1->setCurrentFloor(FloorIter.getCurrentNode()->next);
							temp1->setElevatorNumber(i);
							elevators.insertFirst(temp1);
						}
						
						
					break;
				
				case 2: //AEAEA
						if (i%2==1) {
							allFloorsElevator* temp2 = new allFloorsElevator;
							temp2->setCurrentFloor(FloorIter.getCurrentNode());
							temp2->setElevatorNumber(i);
							elevators.insertFirst(temp2);
						} else {
							evenFloorsElevator* temp2 = new evenFloorsElevator;
							temp2->setCurrentFloor(FloorIter.getCurrentNode());
							temp2->setElevatorNumber(i);
							elevators.insertFirst(temp2);
						}

					break;
					   
				case 3: //OEOEO
						if (i%2==1) {
							oddFloorsElevator* temp3 = new oddFloorsElevator;
							temp3->setCurrentFloor(FloorIter.getCurrentNode()->next);
							temp3->setElevatorNumber(i);
							elevators.insertFirst(temp3);
						} else {
							evenFloorsElevator* temp3 = new evenFloorsElevator;
							temp3->setCurrentFloor(FloorIter.getCurrentNode());
							temp3->setElevatorNumber(i);
							elevators.insertFirst(temp3);
						}
					break;
				case 4: //OAOAO
						if (i%2==1) {
							oddFloorsElevator* temp4 = new oddFloorsElevator;
							temp4->setCurrentFloor(FloorIter.getCurrentNode()->next);
							temp4->setElevatorNumber(i);
							elevators.insertFirst(temp4);
						} else {
							allFloorsElevator* temp4 = new allFloorsElevator;
							temp4->setCurrentFloor(FloorIter.getCurrentNode());
							temp4->setElevatorNumber(i);
							elevators.insertFirst(temp4);
						}
					break;
				case 5: //EOEOE
						if (i%2==1) {
							evenFloorsElevator* temp5 = new evenFloorsElevator;
							temp5->setCurrentFloor(FloorIter.getCurrentNode());
							temp5->setElevatorNumber(i);
							elevators.insertFirst(temp5);
						} else {
							oddFloorsElevator* temp5 = new oddFloorsElevator;
							temp5->setCurrentFloor(FloorIter.getCurrentNode()->next);
							temp5->setElevatorNumber(i);
							elevators.insertFirst(temp5);
						}
					break;
				case 6: //EAEAE
						if (i%2==1) {
							evenFloorsElevator* temp6 = new evenFloorsElevator;
							temp6->setCurrentFloor(FloorIter.getCurrentNode());
							temp6->setElevatorNumber(i);
							elevators.insertFirst(temp6);
						} else {
							allFloorsElevator* temp6 = new allFloorsElevator;
							temp6->setCurrentFloor(FloorIter.getCurrentNode());
							temp6->setElevatorNumber(i);
							elevators.insertFirst(temp6);
						}
					break;
				case 7: //EEAAO
						if (i%5==1 || i%5==2) {
							evenFloorsElevator* temp7 = new evenFloorsElevator;
							temp7->setCurrentFloor(FloorIter.getCurrentNode());
							temp7->setElevatorNumber(i);
							elevators.insertFirst(temp7);
						} else if (i%5==3 || i%5==4) {
							allFloorsElevator* temp7 = new allFloorsElevator;
							temp7->setCurrentFloor(FloorIter.getCurrentNode());
							temp7->setElevatorNumber(i);
							elevators.insertFirst(temp7);
						} else {
							oddFloorsElevator* temp7 = new oddFloorsElevator;
							temp7->setCurrentFloor(FloorIter.getCurrentNode()->next);
							temp7->setElevatorNumber(i);
							elevators.insertFirst(temp7);
						}
					break;
				case 8: //OOAAE
						if (i%5==1 || i%5==2) {
							oddFloorsElevator* temp8 = new oddFloorsElevator;
							temp8->setCurrentFloor(FloorIter.getCurrentNode()->next);
							temp8->setElevatorNumber(i);
							elevators.insertFirst(temp8);
						} else if (i%5==3 || i%5==4) {
							allFloorsElevator* temp8 = new allFloorsElevator;
							temp8->setCurrentFloor(FloorIter.getCurrentNode());
							temp8->setElevatorNumber(i);
							elevators.insertFirst(temp8);
						} else {
							evenFloorsElevator* temp8 = new evenFloorsElevator;
							temp8->setCurrentFloor(FloorIter.getCurrentNode());
							temp8->setElevatorNumber(i);
							elevators.insertFirst(temp8);
						}
					break;
				case 9: //OEAAA
						if (i%5==1) {
							oddFloorsElevator* temp9 = new oddFloorsElevator;
							temp9->setCurrentFloor(FloorIter.getCurrentNode()->next);
							temp9->setElevatorNumber(i);
							elevators.insertFirst(temp9);
						} else if (i%5==2) {
							evenFloorsElevator* temp9 = new evenFloorsElevator;
							temp9->setCurrentFloor(FloorIter.getCurrentNode());
							temp9->setElevatorNumber(i);
							elevators.insertFirst(temp9);
						} else {
							allFloorsElevator* temp9 = new allFloorsElevator;
							temp9->setCurrentFloor(FloorIter.getCurrentNode());
							temp9->setElevatorNumber(i);
							elevators.insertFirst(temp9);
						}
					break;
			}
					
		}
	}

}; //End Class

