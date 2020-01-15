#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "MPQ.h"
#include <vector>

using namespace std;

enum Wall {LEFT, RIGHT ,NON}; //enum type to identify which wall is which

struct building //struct to read data from given input file
{
	int value;
	int height;
	int readOrder;
	Wall direction;
	building(int readValue=0 ,int heightVal=0 ,int orderVal=0) :direction(NON), value(readValue), height(heightVal),readOrder(orderVal) {}
};

bool compareValue(const building& obj, const building &obj2) //for sorting
{
	return obj.value<obj2.value;
}

int main()
{
	ifstream file; //input file stream
	file.open("input.txt");

	string takenInput ;
    file>>takenInput ; // #number of buildings = first read data from file
    int NumberofBuildings = stoi(takenInput) ;

	int leftCoordinate;
    int inputHeight;
    int rightCoordinate;
    vector<building> forCoordinates; //vector to keep info of buildings

	int order=0;
	while(getline(file,takenInput)) 
	{
		if(takenInput!= "")
		{
			order=order+1;
			istringstream iss(takenInput);
			iss >> leftCoordinate;
			iss >> inputHeight;
			building temp; //struct object
			temp.direction = LEFT ;
			temp.value =  int(leftCoordinate);			
			temp.height = inputHeight;
			temp.readOrder = order;
            
			forCoordinates.push_back(temp);

			iss >> rightCoordinate;
			temp.direction = RIGHT;
			temp.value =  int(rightCoordinate);
			temp.readOrder = order;
			temp.height=inputHeight;
			forCoordinates.push_back(temp);
		}
	}	
	sort(forCoordinates.begin(),forCoordinates.end(),compareValue); //sorting vector in ascending order with respect to their x coordinates
	
	MPQ<int> outputHeap(NumberofBuildings+2); //Modified Priority Queue Class object creation
	int MaxH=-1;
	struct output //struct for output
	{
		int high;	//for the height of object
		int xCord;	// identifying number that identifies a specific *id
		output(int high2=0,int xCord2=0){high=high2;xCord=xCord2;}
	};
	
	vector<output>outputVec;  //for output vec                               
	for(unsigned int i=0;i<forCoordinates.size();i++)                               
	{  
		output temp;
		temp.high=forCoordinates[i].height;
		temp.xCord=forCoordinates[i].readOrder;

		if(forCoordinates[i].value!=0 && i==0)   //if first iteration, cout 0 0                                 
			cout<<0<<" "<<0<<endl;
		
		if(forCoordinates[i].direction==LEFT)    //if direction is left, insert it to class vector              
		{
			outputHeap.insert(temp.high,temp.xCord); //inserts to vector
			if(i<forCoordinates.size()-1) //checks if its last node or not
			{                                              
				if(forCoordinates[i].value!=forCoordinates[i+1].value)      //compares the x values are the same or not with next index of vector              
					 if(outputHeap.getMax()!=MaxH) //checks max height whether changed or not
					 {   
						 temp.xCord=forCoordinates[i].value;
						 MaxH=outputHeap.getMax(); 
						 temp.high=MaxH;
						 outputVec.push_back(temp);             
					 }
			}
			else //that means we are at last node
			{
				 if(outputHeap.getMax()!=MaxH)
				 {
					temp.xCord=forCoordinates[i].value;
					MaxH=outputHeap.getMax(); 
					temp.high=MaxH;
					outputVec.push_back(temp);
				 }
			}			 
		}
		else //if direction is right, that means building is over, remove it from class vector
		{			
			outputHeap.remove(forCoordinates[i].readOrder); //removes it from vector
			if(i<forCoordinates.size()-1)
			{                                              
				if(forCoordinates[i].value!=forCoordinates[i+1].value)  //checks x values are the same or not                       
				{
					 if(outputHeap.getMax()!=MaxH) //checks height has changed or not
					 {    
						 temp.xCord=forCoordinates[i].value;
						 MaxH=outputHeap.getMax();
						 temp.high=outputHeap.getMax();
						 outputVec.push_back(temp);            
					 }
				}	
			}
			else //last node of vector
			{
				 if(outputHeap.getMax()!=MaxH)
				 {
					temp.xCord=forCoordinates[i].value;
					MaxH=outputHeap.getMax();
					temp.high=MaxH;
					outputVec.push_back(temp);
				 }
			}
		}	
		
	}	
	for (unsigned int j = 0; j < outputVec.size(); j++) //cout from the vector that we have pushed in above cases
			cout << outputVec[j].xCord << " " << outputVec[j].high << endl;
	
	return 0;
}
