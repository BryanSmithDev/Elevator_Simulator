/*
Name: Scott Arnette
Section: 2
Date: 4/3/13
Assignment 5: Elevator Simulation: Elevator Class and Methods
*/

//[Typical headers]
#include<iostream>
#include<ctime>

using namespace std;

//[Elevator class definition]
   class Elevator{
   public:
	 //[Method prototypes]
      Elevator();
      void setCurrentFloor(nodeType<Floor<int>*> *curFloor);
      virtual void move() = 0;
      void loadPeople();
      void unloadPeople();
      void setElevatorNumber(int x);
      int getCurrentLoad();
      int getElevatorNumber();
   
   private:
	 //[Variables for max and current load values, elevator number and count of last amount of people on the elevator]
      int maxCapacity;
      int currentLoad;
      int elevatorNumb;
      int lastLoadNumPeople;
   
   protected:
      nodeType<Floor<int>*> *currentFloor;
      bool movingUp;
   
   };

//[Constructor]
   Elevator::Elevator(){
      currentLoad = 0;
      maxCapacity = 15;
      movingUp = true;
      elevatorNumb=-1;
   }

//[Method to set the current floor via pointer]
   void Elevator::setCurrentFloor(nodeType<Floor<int>*> *curFloor){
      currentFloor = curFloor;
   }

//[Load method that takes number of people generated from floor and "moves" to elevator until max capacity is reached]
   void Elevator::loadPeople(){
      lastLoadNumPeople = 0;
   	
      while(currentLoad < maxCapacity && currentFloor->info->getLength()>0){
         currentLoad++;
         currentFloor->info->leaveAt(1);
         lastLoadNumPeople++;
      }
   }

//[Method to unload a random number of people]
   void Elevator::unloadPeople(){
      if (getCurrentLoad() >0){
         int unloadNum=0;
      
         int lowerbound = 0;
         int upperbound = 3;
         int range = upperbound - lowerbound+1; 
         int result;
         result = rand()%range; 
         result += lowerbound;
         unloadNum = (result);
      
      
         if(currentLoad >= unloadNum){
            currentLoad -= unloadNum;
         }
         else{
            currentLoad = 0;
         }
      }
   }

//[Method to set elevator number]
   void Elevator::setElevatorNumber(int x){
      elevatorNumb=x;
   }

//[Method to return current number of people]
   int Elevator::getCurrentLoad(){
      return currentLoad;
   }

//[Method to return elevator number]
   int Elevator::getElevatorNumber(){
      return elevatorNumb;
   }
