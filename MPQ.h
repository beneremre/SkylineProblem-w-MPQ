#include <iostream>
#include <vector>
#include <stdio.h>

using namespace std ;

template<class Comparable>
struct identify
{
	Comparable value; //identifying height
	int order;	// identifying number that identifies a specific *id
	identify(Comparable value2=0,int order2=0){value=value2;order=order2;}
};

template<class Comparable>
class MPQ
{	 
	private:
		 int currentSize; // Number of elements in heap
		 vector<identify<Comparable>>arr; //class array
		 void percolateDown(int hole);
		 int capacity;
		 

	public:	
		vector<int>Location; //location array to let us do find operation in constant time
		MPQ(int cap) //constructer
		{
			for(int i=0;i<cap;i++)
			{
				identify<Comparable> pushed;
				arr.push_back(pushed);
			}
			currentSize=0;
			for (int j=0; j<4500; j++)
				Location.push_back(0);			
		}
		~MPQ(); //destructor
		void insert(const Comparable &value,int label);
		Comparable remove(int label);
		Comparable getMax();
		bool isEmpty();			
};

template<class Comparable>
MPQ<Comparable>::~MPQ()
{
	for (unsigned int i = 0; i < arr.size(); i++)
		arr.pop_back();
	
	currentSize=0;
}

template<class Comparable>
void MPQ<Comparable>::insert(const Comparable &value,int label ) //this function inserts an element to the class vector via finding a appropriet spot
{   
	int hole = ++currentSize;
	for( ; hole > 1 && value > arr[hole/2].value  ; hole /= 2 )
	{
		arr[ hole ] = arr[ hole/2 ];
		Location[arr[hole].order]=hole ;
	}
	arr[hole].value = value;
	arr[hole].order=label;
	Location[arr[hole].order] = hole ;
}

template<class Comparable>
Comparable MPQ<Comparable>::getMax() //this function returns the max value in array if not empty, otherwise returns 0
{
	if(currentSize==0)
		return 0;
	else
		return arr[1].value;
	return 0;
}

template<class Comparable>
bool MPQ<Comparable>::isEmpty() //if current size is 0, that means empty
{
	return (currentSize==0);
}

template<class Comparable>
Comparable MPQ<Comparable>::remove(int label) //this function removes an element from the vector
{
	int parent = Location[label]/2;
    if(parent == 0)
        parent++ ;
    
	arr[Location[label]] = arr[currentSize] ; 
	arr[currentSize].order=0;
	arr[currentSize].value=0;
    currentSize-- ;

    if (Location[label] == 1 /*x is root*/ || (arr[parent].value < arr[Location[label]].value)) /* k is root */
        percolateDown(Location[label]) ;
    
	return 0;   
}

template<class Comparable>
void MPQ<Comparable>::percolateDown(int hole) //this function percolates down until it finds the correct spot and updates location array
{
	int child;
	identify<Comparable> tmp;
	tmp.order= arr[hole].order;
	tmp.value=arr[hole].value;// tmp is the item that will 
							 // be percolated down
	for( ; hole * 2 <= currentSize; hole = child )
	{
		child = hole * 2;
		if( child != currentSize && arr[child+1].value > arr[child].value )
			child++;  // child is the minimum of the children
		if( arr[child].value > tmp.value )
		{
			arr[hole] = arr[child]; // swap hole and min child
			Location[hole]=Location[child];
		}
		else
			break;
	}
	arr[hole].value = tmp.value; 
	arr[hole].order = tmp.order;// place tmp in its final position
	Location[hole]=tmp.order; //update the location array
}   





