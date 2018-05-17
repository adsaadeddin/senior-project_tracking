// 1 dimesion grid only.
#include<iostream>
#include<fstream>
#include"senserGroup.h"
#include"linkedList.h"
using namespace std;

class grid1D
{
public:
	void set(senserGroup sen);

	void setMinMax();
	void print();

private:
	

	linkedListType<int> thegrid[10];
	
	double min;
	double max;
	double jumper; // the jumper is how much it will go from the 1st range to the 2nd
	
	int numOfSen;   // numer of dimesnions, and number of sensors
	//int numOfDim;
};


void grid1D::set(senserGroup sen)
{
	nodeType<double> *p;
	int i;
	double check;
	numOfSen = sen.getSen();
	min = 10000000;
	max = 0;
	for(i=0; i<numOfSen; i++)
	{
		p = sen.sensers[i].first;
		
		if( min > p->info)
				min = p->info;
		if(max < p->info)
				max = p->info;
	}
	
	jumper = ((max - min)/10);
	
	cout<<"min"<<min<<endl;
	cout<<"max"<<max<<endl;
	cout<<"jumper"<<jumper<<endl;
	
	int r;
	


	for(i=0; i<numOfSen;i++)
	{
		p = sen.sensers[i].first;
		check = min;
		r = 0;
		do{
			if( p->info > check && p->info < (check+jumper))
			{
				thegrid[r].insertLast(i);
				r = 11;
			}
			
			else
			{
				r++;
				check += jumper;
			}
		}while(r < 10);
	}


}

void grid1D::print()
{
	ofstream fout;
	fout.open("data.txt");
	int i;
	
		cout<<"min ="<<min<<endl;
		cout<<"max ="<<max<<endl;
		cout<<"jumper ="<<jumper<<endl;
	
	nodeType<int> *p;
	int counter;
	
	for(i=0; i<10; i++)
	{
			
				counter=0;
				cout<<"#"<<i<<" this grid1D has the sensors"<<endl;
				fout<<"#"<<i<<" this grid1D has the sensors"<<endl;
				p = thegrid[i].first;
			
				while(p != NULL)
				{
					cout<<p->info<<" ";
					fout<<p->info<<" ";
					p = p->link;
					counter++;
				}
			cout<<endl;
			fout<<endl;			
			cout<<"the number of sensors in this part is : "<<counter<<endl;
			fout<<"the number of sensors in this part is : "<<counter<<endl;

		
	}
		

}