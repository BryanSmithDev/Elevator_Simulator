/*################################################
 Name: Bryan Smith
 Course: CSC 2180-02 Data Structures
 Date: 4/3/13
 Assignment: Programming Assignment #5
 Description: SimMain contains a main function to
			  drive the SimBuilding class.
###############################################*/

#include <iostream>
#include "SimBuilding.h"

using namespace std;

int main(){
	//Run 10 simulations
	for(int x=0;x<10;x++){
		cout<<endl<<"############################################"<<endl;
		cout<<"Simulation Set "<<x+1<<endl;
		cout<<"############################################"<<endl<<endl;
		cout<<"Elevator Config          Avg Sim Steps"<<endl;
		cout<<"========================================"<<endl;
		for(int i=0;i<10;i++){ //On all 10 elevator configurations
			switch(i){
				case 0:
					cout<<"AAAAA"<<"                    ";
					break;
				case 1:
					cout<<"AOAOA"<<"                    ";
					break;
				case 2:
					cout<<"AEAEA"<<"                    ";
					break;
				case 3:
					cout<<"OEOEO"<<"                    ";
					break;
				case 4:
					cout<<"OAOAO"<<"                    ";
					break;
				case 5:
					cout<<"EOEOE"<<"                    ";
					break;
				case 6:
					cout<<"EAEAE"<<"                    ";
					break;
				case 7:
					cout<<"EEAAO"<<"                    ";
					break;
				case 8:
					cout<<"OOAAE"<<"                    ";
					break;
				case 9:
					cout<<"OEAAA"<<"                    ";
					break;
			}
			SimBuilding sim1(i,33,5,60);
			double temp = sim1.run();
			cout<<temp<<"    ("<<temp/2<<" minutes)"<<endl;
		}
	}

	system("PAUSE");
	return 0;
}