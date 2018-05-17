
#include<iostream>
#include"senserGroup.h"
#include"grid1D.h"
#include"grid2D.h"
#include"grid3D.h"
#include"grid4D.h"
#include"grid5D.h"
#include"linkedList.h"
using namespace std;

int main()
{
	int numOfClus;
	senserGroup test; // first we define 
	int numOfSens,  numDim; 
	
	cout<<"enter the total number of sensers"<<endl;

	cin>>numOfSens;
	cout<<"enter the number of clusters"<<endl;
	cout<<"maxmum number is 100 clusters"<<endl;
	cin>>numOfClus;
	cout<<"enter how many Dimension each senser will have"<<endl;
	cin>>numDim;

	test.set(numOfSens, numOfClus, numDim);
	
	//test.set(300,1,2);
	//test.print();
	
	grid2D newGrid;
	newGrid.set(test);
	
	newGrid.print();
	newGrid.detect();
	cin>>numOfClus;
	return 0;
}