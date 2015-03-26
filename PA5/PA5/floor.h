/*
Name: Cory Elswick
Section: 2
Date: 4/3/13
Assignment 5: Floor Class and Methods
*/

#include <iostream>
#include <ctime>
#include <cstdlib>
#include "linkedQueue.h"

using namespace std;

//CLASS Floor
template <class Type>
class Floor: public linkedQueueType<int>{
public:
	//default constructor
    Floor() {
        length = 0;
        boardedPeople = 0;
        boardedWait = 0;
        floorNum = -1;
    }
   
	//arriveAt method. When called, this adds randomly between 0-3
	//elements to the queue
    void arriveAt(int step=0){

        int result = (rand()%4); 
         
		


    //this while loop will call addQueue result number of times,
    //where result is a random number between 0-3
        for(int i = 0; i < result; i++){
        addQueue(step);
		length++;           
        }

    }
      
	//leaveAt method. It deletes x elements from queue 
    void leaveAt(int x){
        int i = 0;
		if (x > getLength()) x=getLength();

        while(i < x){
        deleteFloorQueue();
        length--;
        i++;
        } 
		 
    }
      
	//getBoardedPeople
    int getBoardedPeople(){
        return boardedPeople;
    }
      
	//setBoardedPeople
    void setBoardedPeople(int s){
        boardedPeople = s;
    }
      
	//getBoardedWait
    double getBoardedWait(){
        return boardedWait;
    }
      
	//setBoardedWait
    void setBoardedWait(int s){
        boardedWait = s;
    }
   
	//getLength
    int getLength(){
        return length;
    }
      
	//setLength
    void setLength(int s){
        length = s;
    }
   	
	//getFloorNum
    int getFloorNum(){
        return floorNum;
    }
   		
	//setFloorNum
    void setFloorNum(int s){
        floorNum = s;
    }
      
	//boardAverage method. the average wait time of the people who have boarded
    double boardAverage(){
        double average = 0;
        average = (double)boardedWait/boardedPeople;
		if (boardedPeople==0) average = 0;
        return average;
    }
      	
	//queueWaitIncrement method. This increments the integer value
	//in each node by 1
    void queueWaitIncrement(){
        nodeType<Type> *current;
        current = queueFront;
        while(current != NULL){
        current->info += 1;                       
        current = current->next;    
        } 
    } 
   
	//print method. prints info of all nodes in the queue
    void print(){
        nodeType<Type> *current;
        current = queueFront;
        while(current != NULL){
        cout<<current->info<<" ";                       
        current = current->next;    
        } 
    } 
   	
	//deleteQueue method. removes an element from the
	//front of the queue
    void deleteFloorQueue(){
        boardedWait += queueFront->info; 
        deleteQueue();
        boardedPeople++;  
    }

	//Overload equality comparison operator.
	bool operator==(const Floor<Type>& right) const
	{
		return (getFloorNum == right.getFloorNum());
	}

    //Overload anti-equality comparison operator.
	bool operator!=(const Floor<Type>& right) const{
		return !(this==right);
	}
   
     
//private data members.
//length will keep track of the number of elements in the queue
//boardedPeople is the number of people who have boarded the elevator
//boardedWait is how long the people who have boarded the elevatoar had to wait
protected:
    int length;
    int floorNum;
    int boardedPeople;
    int boardedWait;
};
