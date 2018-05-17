#ifndef H_senserGroup
#define H_senserGroup

#include<cstdlib>
#include <iostream>
#include <cmath>
#include <stack>
#include <fstream>
#include "linkedList.h"
using namespace std;


class senserGroup
{
public:
	void set(int numSen, int numClus, int numDim);
	// the set function : it receive the number of sensers
	// and the number of clusters and number of dimension for each senser has.
	// and store them in the class, then it will use the random fuction to 
	// generate the values of the sensers.

	void get(int& numSen, int& numClus, int& numDim);
	// the get function :
	//  it get the values number of sensers, number of clusters
	// number of dimensions

	int getSen();
	//return the number of sensors 
	
	int getDim();
	// return the number of dimesnion 

	void random();
	//the function random:
	// is the function which has the ability of putting the random valuable in the
	// array of linked list of the Sensors

	double randDouble(double low, double high);
	// its the function that produce the random double number

	void print() const;
	// the print function : print all the number in the linked list

	linkedListType<double> *sensers;

protected:
	int numOfSensers;       // number of Sensers in this group
	int numOfClusters;		// number of Clusters in this group
	int numOfDimensions;    // number of Dimesions in this group

	

};



int senserGroup::getDim()
{
	return numOfDimensions;
}


int senserGroup::getSen()
{
	return numOfSensers;
}


void senserGroup::print() const // to print the value of the sensers 
{
	ofstream fout;
	ofstream out;
	fout.open("output.xls");
	out.open("output.txt");
	nodeType<double> *p;
		
	for(int i=0; i<numOfSensers; i++)
		{
			p = sensers[i].first;
			cout<<i+1<<" :";
			fout<<i+1<<"\t";
			for(int j=0; j<numOfDimensions; j++)
			{	
				cout<<p->info<<" ";
				fout<<p->info<<"\t";
				out<<p->info<<" ";
				p = p->link;
			}
			cout<<endl;
			fout<<"\n";
			out<<"\n";
		}

	fout.close();
	out.close();
	
}


void senserGroup::set(int numSen, int numClus, int numDim)
{
	 numOfSensers  = numSen;
	 numOfClusters = numClus;
	 numOfDimensions = numDim;
	 sensers = new linkedListType<double>[numOfSensers];
	 int  j=0; 
	 
	 while(j< numDim)
	 {
		 
		for(int i=0; i<numOfSensers;i++)
		sensers[i].insertLast(-1);
		j++;	
	 }
	
	 random();

}

void senserGroup::get(int& numSen, int& numClus, int& numDim)
{
	 numSen = numOfSensers;
	 numClus = numOfClusters;
	 numDim = numOfDimensions;
}



void senserGroup::random()
{	
	cout<<"enter the Ranges and Percentage of each cluster"<<endl;
	cout<<"and for each dimension"<<endl;
	cout<<endl<<endl;
	
	nodeType<double> *p;
	double percentage, totalPer=0, temp;
	int clusCounter=0;  // the counter of the sensors of the cluster
	int dimCounter=0;  // Dimesion counter, for every sensor.
	int numClus;
	int RanNum=0;
	int k=0,i;
	double *range;
	range = new double[(2*numOfDimensions)];
	
	cout<<"enter the Range and Percentage of each cluster"<<endl;
	
	while( clusCounter < numOfClusters)
	{	
		dimCounter = 0;
		
		cout<<"Cluster #"<<clusCounter+1<<endl;
		cout<<"percentage :";
		
		cin>>percentage;
		
		totalPer += percentage;
		numClus  = (percentage / 100)*numOfSensers;
		
		cout<<"numer of cluster:"<<numClus<<endl;
		
		while(dimCounter < numOfDimensions)
		{	
			k = 0;
			
			cout<<"enter the range of the of the Dimension number "<<dimCounter+1<<endl;
			cout<<"from :";
			
			cin>>range[k];
			cout<<"to :";
			cin>>range[k+1];
			
			k+=2;
			dimCounter++;
		}
		
		for(i =0; i<numClus; i++)
		{
			do{
				RanNum = rand()%numOfSensers;
			}while((sensers[RanNum].first)->info != -1);
			p =sensers[RanNum].first;
			
			for(int s=0; s<dimCounter; s++)
			{
				int ranCount =0;
				p->info = randDouble(range[ranCount], range[ranCount+1]);
				p = p->link;
				ranCount+=2;
			}
		}
		clusCounter++;
	}

	percentage = 100 - totalPer;
	numClus  = (percentage / 100)*numOfSensers;
	
	cout<<"number of total sensors:"<<numClus<<endl;
	
	dimCounter=0;
	
	while(dimCounter < numOfDimensions)
	{
		p = sensers[0].first;
		k = 0;
		
		cout<<"enter the range of the of the Rest of the Sensor number "<<dimCounter+1<<endl;
		cout<<"from :";
		cin>>range[0];
		cout<<"to :";
		cin>>range[1];
		temp = randDouble(range[0], range[1]);
		while( k < numOfSensers )
		{
			p = sensers[k].first;
			for(i=0; i < dimCounter;i++)
				p= p->link;
			if(p->info == -1)
			{
				p->info = randDouble(range[0], range[1]);
			}
			k++;
		}
		dimCounter++;
	}
}



double senserGroup::randDouble(double low, double high)
{
	double temp;
	// swap low & high around if the user makes no sense 
	if (low > high)
	{
		temp = low;
		low = high;
		high = temp;
	}
	// calculate the random number & return it 
	temp = (rand() / (static_cast<double>(RAND_MAX) + 1.0))*(high - low) + low;
	return temp;
}

#endif